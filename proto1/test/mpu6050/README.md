# Test MPU6050 DMP mode

This test initializes MPU6050 as DMP mode, and reads the Yaw/Pitch/Roll angle and Euler angle from MPU6050.
And measures the time between the output from DMP, and the time taken to read values.

## Test Result

This is serial output from Arduino Uno. It shows that

* the average time between the output from DMP is 10 msec, +/- 100 micro seconds.
* the maximum time to read values from DMP is 3344 micro seconds.

```
Test MPU6050 DMP6
Init mpu
Checking hardware revision...
Revision @ user[16][6] = 4D
Resetting memory bank selection to 0...
>......>......
//           X Accel  Y Accel  Z Accel   X Gyro   Y Gyro   Z Gyro
//OFFSETS     -564,   -2013,    1416,      76,    -151,     -15
DMP ready!
2494864 3124    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10212   3332    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9920    3136    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10064   3336    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9908    3120    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10080   3124    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9892    3124    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10076   3136    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10132   3348    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9924    3140    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10092   3344    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9912    3144    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10100   3352    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9928    3144    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10092   3344    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9932    3140    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10064   3340    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9912    3128    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10088   3128    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9908    3132    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10080   3132    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9920    3132    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10084   3128    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
9912    3132    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
10076   3128    ypr     0.00    -0.00   0.01    euler   0.00    -0.00   -0.01
...
```

