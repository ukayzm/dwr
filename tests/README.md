# Tests

Misc


# Provision Bluetooth

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

Refer to [hc05_at_command/README.md](hc05_at_command/README.md) for more information about AT command of HC-05.


