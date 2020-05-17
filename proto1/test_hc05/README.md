# Test HC-05 in AT mode

This tests HC-05 bluetooth serial module in AT mode.

## Baud rate

The baud rate in AT mode is always 38400, a fixed value. And in the test code, the baud rate of physical serial port is 115200. We have to consider this difference of speed. We can read the bluetooth and freely write to serial port. But in the opposite direction, the data may be overflowed due to the slow speed of Bluetooth. In the source code, `buf` is used to buffer input from serial port. 

## Change to AT mode

With the Arduino on, do the following

* Remove the 5V connection to HC-05 VCC
* Press and hold the button switch on the HC-05 module
* Re-connect HC-05 VCC to 5V (while still pressing the button switch), the LED should come
on.
* Release the button switch and the LED should be blinking slowly on/off once every couple
of seconds. This indicates AT mode. 

## Sending AT command with linux terminal

You can send AT command like this
```bash
$ printf "AT\r\n" > /dev/ttyACM0
$ printf "AT+VERSION\r\n" > /dev/ttyACM0
$ printf "AT+NAME\r\n" > /dev/ttyACM0
```

## Receiving response

Open another terminal and
```bash
$ stty -F /dev/ttyACM0 cs8 115200  ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
$ cat /dev/ttyACM0
```

## Change back to data mode

Just power off and on Arduino, then HC-05 will return to data mode.

## LED status of HC-05

* Blink once in 2 sec: Module has entered Command Mode
* Repeated Blinking: Waiting for connection in Data Mode
* Blink twice in 1 sec: Connection successful in Data Mode

## HC-05 Default Settings

* Default Bluetooth Name: “HC-05”
* Default Password: 1234 or 0000
* Default Communication: Slave
* Default Mode: Data Mode
* Data Mode Baud Rate: 9600, 8, N, 1
* Command Mode Baud Rate: 38400, 8, N, 1
* Default firmware: LINVOR
* 