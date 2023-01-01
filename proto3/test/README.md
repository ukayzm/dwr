# Test

Codes to test and calibrate the hardware of proto3 and measure the performance.

* BuiltInLED_Serial - Blink the built-in LED and measure the delay or printf() through serial using ESP-IDF.
* bluetooth_host_joystick - Connect to the joystick through BLE or Bluetooth classic.
* mpu6050-i2cdevlib - Test MPU6050 with i2cdevlib library.
* mpu6050-filter - Apply Kalman filter and complementary filter to i2cdevlib.

# Compile and Upload

All tests except Arduino_BuiltInLED_Serial uses ESP-IDF.

```bash
cd TEST_DIR
idf.py build
idf.py flash
idf.py monitor
```

# Compile and Upload with Arduino-CLI

Arduino_BuiltInLED_Serial is the same as BuiltInLED_Serial except that it uses Arduino compiler.

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 -u -p /dev/ttyUSB0 BuiltInLED_Serial/
stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
cat /dev/ttyUSB0
```

