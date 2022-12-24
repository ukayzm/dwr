# IR 2 - IRsmallDecoder

It uses IRsmallDecoder, which can be installed from the IDE.

InfraRed signal is received from D3 pin and generates interrupt. The builtin LED is blinked when IR signal is received.

The example of the output from my RCU

```
Waiting for a NEC remote control IR signal...
msec	 held 	 addr 	 cmd
15.81	 0	 1539	 13
110.47	 0	 1539	 15
112.38	 0	 1539	 11
112.65	 1	 1539	 11
112.76	 1	 1539	 11
114.09	 0	 1539	 12
115.49	 0	 1539	 14
116.97	 0	 1539	 1F
118.52	 0	 1539	 40
```
