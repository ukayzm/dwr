# proto1

The simplest design - two differential wheels and a ball caster as the third wheel

parts
* 2 geared DC motors with encoder
* 2 wheels, 84mm in diameter
* L293N motor driver
* Arduino nano
* MPU6050
* IR receiver
* HC-06 Bluetooth
* Xiaomi Power Bank 10400mAh

sketch/ - arduino source code
required library:
* I2Cdev, MPU6050 from https://github.com/jrowberg/i2cdevlib.
* IRremove

compile
```bash
$ cd dwr/proto1
$ arduino-cli compile --fqbn arduino:avr:uno sketch/                        # for Arduino Uno board
$ arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old sketch/      # for Arduino Nano with ATmega328P (Old Bootloader)
```

