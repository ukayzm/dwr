# Test

Codes to test and calibrate the hardware of proto3 and measure the performance.

* BuiltInLED_Serial - Blink the built-in LED and measure the delay of Serial.print().

# Compile and Upload with Arduino-CLI

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 -u -p /dev/ttyUSB0 BuiltInLED_Serial/
```

# Monitor the Serial Output

```bash
stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
cat /dev/ttyUSB0
```

