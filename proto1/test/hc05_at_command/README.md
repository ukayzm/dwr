# Test HC-05 in AT mode

This tests HC-05 bluetooth serial module in AT mode. Basically it reads byte from bluetooth and write to serial port, and vice versa.
By this way, we can send AT command from serial port to HC-05, and print response from HC-05 to serial port.

In addition, the time taken to write to bluetooth is measured and displayed.

## Baud rate

* The baud rate in AT mode is always 38400, a fixed value.
* In the test code, the baud rate of serial port is 115200.

This difference can cause a data overflow when writing byte from serial port to bluetooth in real time. 
To avoid overflow, the byte read from serial port is saved to `line_buf`, and written to bluetooth later.

## Change HC-05 to AT mode

With the Arduino on, do the following

* Remove the 5V connection to HC-05 VCC
* Press and hold the button switch on the HC-05 module
* Re-connect HC-05 VCC to 5V (while still pressing the button switch), the LED should come
on.
* Release the button switch and the LED should be blinking slowly on/off once every couple
of seconds. This indicates AT mode. 

## Prepare serial port in host PC

Set the baud rate of serial port to 115200

```bash
$ stty -F /dev/ttyACM0 cs8 115200  ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
```

## Sending AT command with linux terminal

You can send AT command like this
```bash
$ printf "AT\r\n" > /dev/ttyACM0
$ printf "AT+VERSION\r\n" > /dev/ttyACM0
$ printf "AT+NAME\r\n" > /dev/ttyACM0
$ printf "AT+UART\r\n" > /dev/ttyACM0
$ printf "AT+ROLE\r\n" > /dev/ttyACM0
$ printf "AT+ROLE=1\r\n" > /dev/ttyACM0
```

## Receiving response

Open another terminal and monitor the response.
```bash
$ cat /dev/ttyACM0
SketchSketch:   /home/rostude/work/dwr/proto1/test_hc05_at_command/test_hc05_at_command.ino
Uploaded: May 18 2020

BTserial started at 38400
> AT
4 chars sent in 1084 usec
OK
> AT+UART
9 chars sent in 2432 usec
+UART:9600,0,0
> OK
> AT+UART=115200,0,0
20 chars sent in 5400 usec
OK
> AT+UART
9 chars sent in 2436 usec
+UART:115200,0,0
> OK
```

## Useful AT commands

* AT
* AT+ROLE
* AT+UART
* AT+UART=115200,0,0


## Change HC-05 back to data mode

Just power off and on without pressing button switch on HC-05, then it will return to data mode.

## LED status of HC-05

* Blink once in 2 sec: Module has entered Command Mode
* Repeated Blinking: Waiting for connection in Data Mode
* Blink twice in 1 sec: Connection successful in Data Mode

## HC-05 Default Settings

* Default Bluetooth Name: HC-05
* Default Password: 1234 or 0000
* Default Communication: Slave
* Default Mode: Data Mode
* Data Mode Baud Rate: 9600, 8, N, 1
* Command Mode Baud Rate: 38400, 8, N, 1
* Default firmware: LINVOR

