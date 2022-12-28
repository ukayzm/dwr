# Test

Codes to test and calibrate the hardware of proto3 and measure the performance. BuiltInLED_Serial uses Arduino CLI and all the other tests use ESP-IDF.

* BuiltInLED_Serial - Blink the built-in LED and measure the delay of Serial.print() using Arduino CLI.
* ESP_BuiltInLED_Serial - Blink the built-in LED and measure the delay or printf() through serial using ESP-IDF.

# Compile and Upload with Arduino-CLI

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 -u -p /dev/ttyUSB0 BuiltInLED_Serial/
stty -F /dev/ttyUSB0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
cat /dev/ttyUSB0
```

# Compile and Upload with ESP-IDF

```bash
cd TEST_DIR
idf.py build
idf.py flash
idf.py monitor
```
