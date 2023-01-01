#include <driver/i2c.h>
#include <esp_log.h>
#include <esp_err.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "sdkconfig.h"
#include "esp_timer.h"
#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter

#define PIN_SDA 21
#define PIN_CLK 22

Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
uint16_t packetSize = 42;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
MPU6050 mpu = MPU6050();
#define PRINT_INTERVAL	10
int16_t accel[3], gyro[3];
int16_t accel_buf[PRINT_INTERVAL][3], gyro_buf[PRINT_INTERVAL][3];


#define COMPLEMENTARY_ALPHA		0.93
float RAD_TO_DEG = 57.295779513082320876798154814105f;

#define RESTRICT_PITCH // Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf

Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;

double gyroXangle, gyroYangle; // Angle calculate using the gyro only
double compAngleX, compAngleY; // Calculated angle using a complementary filter
double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter

void task_initI2C(void *ignore) {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = (gpio_num_t)PIN_SDA;
	conf.scl_io_num = (gpio_num_t)PIN_CLK;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 400000;
	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
	vTaskDelete(NULL);
}


bool read_mpu6050(void)
{
	mpuIntStatus = mpu.getIntStatus();
	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		return false;
	} else if (mpuIntStatus & 0x02) {
		// otherwise, check for DMP data ready interrupt frequently)
		// wait for correct available data length, should be a VERY short wait
		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);
		return true;
	}
	return false;
}

void compute_kalman_filter()
{
	double accX, accY, accZ;
	double gyroX, gyroY;

	static int64_t prev_micros;
	int64_t now = esp_timer_get_time();
	double dt = (double)(now - prev_micros) / 1000000; // Calculate delta time
	prev_micros = now;

	accX = accel[0];
	accY = accel[1];
	accZ = accel[2];
	gyroX = gyro[0];
	gyroY = gyro[1];

	// Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
	// atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
	// It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
	double roll  = atan2(accY, accZ) * RAD_TO_DEG;
	double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
	double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
	double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

	double gyroXrate = gyroX / 131.0; // Convert to deg/s
	double gyroYrate = gyroY / 131.0; // Convert to deg/s
									  //
#ifdef RESTRICT_PITCH
	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
	if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
		kalmanX.setAngle(roll);
		compAngleX = roll;
		kalAngleX = roll;
		gyroXangle = roll;
	} else
		kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

	if (abs(kalAngleX) > 90)
		gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
	kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
#else
	// This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
	if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
		kalmanY.setAngle(pitch);
		compAngleY = pitch;
		kalAngleY = pitch;
		gyroYangle = pitch;
	} else
		kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

	if (abs(kalAngleY) > 90)
		gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
	kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif

	gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
	gyroYangle += gyroYrate * dt;
	//gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
	//gyroYangle += kalmanY.getRate() * dt;

	compAngleX = COMPLEMENTARY_ALPHA * (compAngleX + gyroXrate * dt) + (1 - COMPLEMENTARY_ALPHA) * roll; // Calculate the angle using a Complimentary filter
	compAngleY = COMPLEMENTARY_ALPHA * (compAngleY + gyroYrate * dt) + (1 - COMPLEMENTARY_ALPHA) * pitch;

	// Reset the gyro angle when it has drifted too much
	if (gyroXangle < -180 || gyroXangle > 180)
		gyroXangle = kalAngleX;
	if (gyroYangle < -180 || gyroYangle > 180)
		gyroYangle = kalAngleY;
}

void task_display(void*)
{
	int64_t start_usec, prev_print_usec = 0, elapsed_usec = 0, sum_elapsed_usec = 0;
	mpu.initialize();
	mpu.dmpInitialize();

	// This need to be setup individually
	// mpu.setXGyroOffset(220);
	// mpu.setYGyroOffset(76);
	// mpu.setZGyroOffset(-85);
	// mpu.setZAccelOffset(1788);
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);

	mpu.setDMPEnabled(true);

	int i = 0;

	while (1) {
		start_usec = esp_timer_get_time();

		if (read_mpu6050()) {
#if 1
	 		mpu.dmpGetQuaternion(&q, fifoBuffer);
			mpu.dmpGetGravity(&gravity, &q);
			mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
#endif
			mpu.dmpGetAccel(accel, fifoBuffer);
			mpu.dmpGetGyro(gyro, fifoBuffer);
			accel_buf[i][0] = accel[0];
			accel_buf[i][1] = accel[1];
			accel_buf[i][2] = accel[2];
			gyro_buf[i][0] = gyro[0];
			gyro_buf[i][1] = gyro[1];
			gyro_buf[i][2] = gyro[2];

			compute_kalman_filter();

			if (i == (PRINT_INTERVAL - 1))
			{
				printf("%d.%06d: ", (int)(start_usec / 1000000), (int)(start_usec % 1000000));
				//printf("%d loop", PRINT_INTERVAL);
				printf(" %d us", (int)elapsed_usec);
				//printf(" = %d us", (int)sum_elapsed_usec / PRINT_INTERVAL);
				//printf(" (err %d)", (int)(start_usec - prev_print_usec - sum_elapsed_usec) / PRINT_INTERVAL);

				//printf("\t%d\t%d\t%d\t%d\t%d\t%d",
				//		accel[0], accel[1], accel[2],
				//		gyro[0], gyro[1], gyro[2]);
				printf("\tDMP:");
				//printf("\t%3.2f", ypr[0] * 180/M_PI);
				printf("\t%3.2f", ypr[1] * 180/M_PI);
				//printf("\t%3.2f", ypr[2] * 180/M_PI);
				printf("\tK:");
				//printf("\t%3.2f", kalAngleX);
				printf("\t%3.2f", kalAngleY);
				printf("\tC:");
				//printf("\t%3.2f", compAngleX);
				printf("\t%3.2f", compAngleY);
#if 0
				for (int j = 0; j < PRINT_INTERVAL; j++) {
					printf(" %d", accel_buf[j][0]);
				}
#endif
				sum_elapsed_usec = 0;
				prev_print_usec = start_usec;
				printf("\n");
			}
			i++;
			i %= PRINT_INTERVAL;
	    }

		elapsed_usec = esp_timer_get_time() - start_usec;
		sum_elapsed_usec += elapsed_usec;
	}

	vTaskDelete(NULL);
}
