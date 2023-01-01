# proto3

ESP32 to connect with Bluetooth Joystick that will control the movement of the robot.

# Hardware 

* 2 geared DC motors with encoder
* 2 wheels, 84mm in diameter
* XXX motor driver
* ESP32
* MPU6050
* IR receiver
* 3S LiPo Battery
* Bluetooth Joystick
* a1602
* DHT11
* 7805

# Software

* src/ - main source code
* test/ - codes to test the hardware parts.
* fritzing/ - fritzing files of the hardware

## Required Library

You need to use ESP-IDF to compile the source code and upload.

Refer to [https://ukayzm.github.io/esp-idf/](https://ukayzm.github.io/esp-idf/) for how to install ESP-IDF.

## compile & upload

```bash
cd src
idf.py set-target esp32
idf.py build
idf.py flash
idf.py monitor
```

