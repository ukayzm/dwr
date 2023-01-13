#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "dc_motor.h"
#include "board.h"


static int16_t enc_count[48];


static void IRAM_ATTR gpio_isr_handler(void* arg) {
    gpio_num_t pin_dir = (gpio_num_t)(int) arg;
	if (pin_dir >= (sizeof(enc_count) / sizeof(int16_t))) {
		return;
	}
	if (gpio_get_level(pin_dir)) {
		enc_count[pin_dir]++;
	} else {
		enc_count[pin_dir]--;
	}
}


DcMotor motor_l = DcMotor();
DcMotor motor_r = DcMotor();

void setup_motor(void)
{
	motor_l.SetEncoderPin(M0_INTR_PIN, M0_DIR_PIN);
	motor_l.SetPin(M0_PWM_PIN, M0_CTRL0_PIN, M0_CTRL1_PIN, M0_CURRENT_PIN);
	motor_r.SetEncoderPin(M1_INTR_PIN, M1_DIR_PIN);
	motor_r.SetPin(M1_PWM_PIN, M1_CTRL0_PIN, M1_CTRL1_PIN, M1_CURRENT_PIN);
}

void DcMotor::SetEncoderPin(int intr_pin, int dir_pin)
{
	pin_intr = intr_pin;
	pin_dir = dir_pin;

    gpio_config_t conf;
	memset(&conf, 0, sizeof(conf));
    conf.intr_type = GPIO_INTR_ANYEDGE;
    conf.mode = GPIO_MODE_INPUT;
    conf.pin_bit_mask = (1 << pin_intr);
    conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&conf);

    gpio_isr_handler_add(pin_intr, gpio_isr_handler, (void*)pin_dir);
}

void DcMotor::SetPin(int pwm_pin, int ctrl0_pin, int ctrl1_pin, int cs_pin)
{
	pin_pwm = pwm_pin;
	pin_ctrl0 = ctrl0_pin;
	pin_ctrl1 = ctrl1_pin;
	pin_cs = cs_pin;

    gpio_set_direction(pin_pwm, GPIO_MODE_OUTPUT);
    gpio_set_direction(pin_ctrl0, GPIO_MODE_OUTPUT);
    gpio_set_direction(pin_ctrl1, GPIO_MODE_OUTPUT);
    gpio_set_direction(pin_cs, GPIO_MODE_INPUT);

    gpio_set_level(pin_pwm, 0);
	gpio_set_level(pin_ctrl0, LOW);
	gpio_set_level(pin_ctrl1, LOW);
}

void DcMotor::SetPwm(int16_t pwm)
{
	if (pwm > 255)
		pwm = 255;
	if (pwm < -255)
		pwm = -255;

}

void DcMotor::setMotorDir(int16_t pwm)
{
	if (pwm > 0) {
		gpio_set_level(pin_ctrl0, LOW);
		gpio_set_level(pin_ctrl1, HIGH);
	} else if (pwm < 0) {
		gpio_set_level(pin_ctrl0, HIGH);
		gpio_set_level(pin_ctrl1, LOW);
	} else {
		gpio_set_level(pin_ctrl0, LOW);
		gpio_set_level(pin_ctrl1, LOW);
	}
}

void DcMotor::setMotorPwm(int16_t pwm)
{
	nCurPwm = pwm;
	if (pwm >= 0) {
		analogWrite(pin_pwm, pwm);
	} else {
		analogWrite(pin_pwm, -pwm);
	}
}

uint16_t DcMotor::GetCurrent(void)
{
	// 5V / 1024 ADC counts / 144 mV per A = 34 mA per count
	return analogRead(pin_cs) * 34;
}

void DcMotor::UpdateRpm(void)
{
	int32_t num_intr;
	int32_t interval_us;
	int i;

	time_t cur_us = esp_timer_get_time();
	enc_count_buf[enc_count_index] = enc_count[pin_dir];
	enc_count[pin_dir] = 0;
	enc_interval_buf[enc_count_index] = cur_us - ulLastUpdateUs;
	enc_count_index++;
	enc_count_index = enc_count_index % NUM_INTR_SAVE;

	/* calculate current speed of wheel */
	num_intr = 0;
	interval_us = 0;
	for (i = 0; i < NUM_INTR_SAVE; i++) {
		num_intr += enc_count_buf[i];
		interval_us += enc_interval_buf[i];
	}
	if (interval_us && num_intr) {
		nCurRpm = num_intr * 60 * 1000 / INTR_PER_REV * 1000 / (long)interval_us;
	} else {
		nCurRpm = 0;
	}

	ulLastUpdateUs = cur_us;
}

int16_t DcMotor::GetCurPwm(void)
{
	return nCurPwm;
}

int16_t DcMotor::GetCurRpm(void)
{
	return nCurRpm;
}
