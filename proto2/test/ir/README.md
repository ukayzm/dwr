# IR

It uses IRLremote library, which can be installed from the IDE.

InfraRed signal is received from D3 pin and generates interrupt. The builtin LED is blinked when IR signal is received.

The example of the output from my RCU

```
Startup
receiving IR signal from PIN 3
13.80 Address: 0x18, Command: 0x1D3BC1DE
13.90 Address: 0x18, Command: 0x1D3BC1DE
19.94 Address: 0x18, Command: 0xC5600F1E
20.04 Address: 0x18, Command: 0xCEA0A1F1
23.33 Address: 0x18, Command: 0xFA35B0D4
23.43 Address: 0x18, Command: 0xFA35B0D4
26.15 Address: 0x18, Command: 0x8524F448
26.25 Address: 0x18, Command: 0x8524F448
27.38 Address: 0x18, Command: 0xF9394A99
27.48 Address: 0x18, Command: 0xF9394A99
27.70 Address: 0x18, Command: 0xF9394A99
27.80 Address: 0x18, Command: 0xF9394A99
```
