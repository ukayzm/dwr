# proto3

ESP32 to connect with Bluetooth Joystick that will control the movement of the robot.

# Hardware 

* 2 geared DC motors with encoder
* 2 wheels, 84mm in diameter
* XXX motor driver
* ESP32
* MPU6050
* IR receiver
* Xiaomi Power Bank 10400mAh
* Bluetooth Joystick

# Software

* sketch/ - main source code
* test/ - codes to test the hardware parts.
* fritzing/ - fritzing files of the hardware

## Required Library

* IRremote
* I2Cdev, MPU6050 from https://github.com/jrowberg/i2cdevlib

You can use Arduino standard IDE to compile the source code and upload. But I prefer to use linux terminal.

Refer to https://ukayzm.github.io/arduino-cli/ for how to install Arduino-CLI.

Then install the required libraries.

```bash
arduino-cli lib install IRremote
git clone https://github.com/jrowberg/i2cdevlib
cd i2cdevlib/Arduino/
cp -r I2Cdev/ MPU6050/ ~/Arduino/libraries/
```

## compile & upload

```bash
cd dwr/proto3
arduino-cli compile --fqbn esp32:esp32:esp32 -u -p /dev/ttyUSB0 sketch/
stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
cat /dev/ttyUSB0
```

