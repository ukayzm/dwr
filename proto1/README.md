# proto1

The simplest design - two differential wheels and a ball caster as the third wheel

# Hardware 

* 2 geared DC motors with encoder
* 2 wheels, 84mm in diameter
* L293N motor driver
* Arduino nano
* MPU6050
* IR receiver
* HC-06 Bluetooth
* Xiaomi Power Bank 10400mAh

# Software

* sketch/ - main source code
* test/ - test the hardware parts.

## Required Library

* IRremove
* I2Cdev, MPU6050 from https://github.com/jrowberg/i2cdevlib

You can use Arduino standard IDE to compile the source code and upload. But I prefer to use linux terminal.

```bash
$ arduino-cli lib install IRremote
$ git clone https://github.com/jrowberg/i2cdevlib
$ cd i2cdevlib/Arduino/
$ cp -r I2Cdev/ MPU6050/ ~/Arduino/libraries/
```
## compile & upload

### Arduino Uno board

```bash
$ cd dwr/proto1
$ arduino-cli compile --fqbn arduino:avr:uno -u -p /dev/ttyACM0 sketch/
$ stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
$ cat /dev/ttyACM0
```

### Arduino Uno clone

```bash
$ cd dwr/proto1
$ arduino-cli compile --fqbn arduino:avr:uno -u -p /dev/ttyUSB0 sketch/
$ stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
$ cat /dev/ttyUSB0
```

### Arduino Nano clone
```bash
$ cd dwr/proto1
$ arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old -u -p /dev/ttyUSB0 sketch/
$ stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
$ cat /dev/ttyUSB0
```

# Provisioning Bluetooth

The default baudrate of HC-05 bluetooth serial module is 9600. We will change it to 115200 to communicate faster.

1. Upload the code `dwr/test/hc05_at_command`.
2. Remove the 5V connection to HC-05 VCC
3. Press and hold the button switch on the HC-05 module
4. Re-connect HC-05 VCC to 5V (while still pressing the button switch), the LED should come on.
5. Release the button switch and the LED should be blinking slowly on/off once every couple of seconds. This indicates AT mode. 
6. Do the following AT commands to provision HC-05

```
AT
AT+ROLE=0
AT+UART=115200,0,0
```

7. Power off and on HC-05 without pressing button. The LED should be blinking fast on/off.

Refer to [test/hc05_at_command/README.md](test/hc05_at_command/README.md) for more information about AT command of HC-05.


