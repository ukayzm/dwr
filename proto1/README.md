# proto1

The simplest design - two differential wheels and a ball caster as the third wheel

## Hardware 

* 2 geared DC motors with encoder
* 2 wheels, 84mm in diameter
* L293N motor driver
* Arduino nano
* MPU6050
* IR receiver
* HC-06 Bluetooth
* Xiaomi Power Bank 10400mAh

## Software

sketch/ - arduino source code

required library:
* IRremove
* I2Cdev, MPU6050 from https://github.com/jrowberg/i2cdevlib

You can play with Arduino standard IDE. But I prefer to use linux terminal.

```bash
$ arduino-cli lib install IRremote
$ git clone https://github.com/jrowberg/i2cdevlib
$ cd i2cdevlib/Arduino/
$ cp -r I2Cdev/ MPU6050/ ~/Arduino/libraries/
```
## compile & upload

### Arduino Uno board

```bash
$ stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
$ cd dwr/proto1
$ arduino-cli compile --fqbn arduino:avr:uno sketch/ && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno sketch/
$ cat /dev/ttyACM0
```

### Arduino Nano compatible
```bash
$ stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
$ cd dwr/proto1
$ arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old sketch/ && arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano:cpu=atmega328old sketch/
$ cat /dev/ttyUSB0
```

