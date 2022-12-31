# MPU6050

The code was mainy taken from https://github.com/jrowberg/i2cdevlib/tree/master/ESP32_ESP-IDF.

The pin is defined in example.cpp.

* PIN_SDA 21
* PIN_CLK 22

It displays the YAW, PITCH, and ROLL angle from DMP and the time taken.

```
6.312952: 758 usec, YAW: 0.2, PITCH: 11.2, ROLL: -2.2
6.317885: 759 usec, YAW: 0.2, PITCH: 11.2, ROLL: -2.1
6.322817: 759 usec, YAW: 0.2, PITCH: 11.2, ROLL: -2.1
6.327748: 758 usec, YAW: 0.2, PITCH: 11.1, ROLL: -2.1
6.332681: 758 usec, YAW: 0.2, PITCH: 11.1, ROLL: -2.1
6.337610: 758 usec, YAW: 0.2, PITCH: 11.0, ROLL: -2.1
6.343304: 760 usec, YAW: 0.2, PITCH: 11.0, ROLL: -2.1
6.348236: 758 usec, YAW: 0.2, PITCH: 10.9, ROLL: -2.1
6.353167: 758 usec, YAW: 0.2, PITCH: 10.9, ROLL: -2.1
6.358098: 758 usec, YAW: 0.2, PITCH: 10.9, ROLL: -2.1
```

FYI, the values from DMP is not precise to use in the balancing because it flows too much.
