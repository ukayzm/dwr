# MPU6050

This test measures the pitch angle and the elapsed time to get it from MPU6050. It uses Kalman filter to calculate the angle as precise as possible.

You can measure the time by uncommenting CHECK_ELAPSED_TIME in mpu6050.h.

The target of the loop time is max 2000 usec. If the loop time exceeds this value, `! xxxx > 2000 us` is printed.

The example of output with CHECK_ELAPSED_TIME uncommented is as the following. You can see that although the time to get the angle is around 1280 usec but `! xxxx > 2000 us` is printed because it printed too many characters.

```
8888240: 600 + 344 + 356 + 84 = 1392 usec, 1.14 ! 3992 > 2000 us
8893848: 572 + 356 + 352 + 88 = 1376 usec, 1.14 ! 3996 > 2000 us
8899460: 568 + 356 + 360 + 88 = 1380 usec, 1.13 ! 3992 > 2000 us
8905068: 572 + 360 + 348 + 88 = 1376 usec, 1.12 ! 3996 > 2000 us
8910680: 572 + 360 + 356 + 84 = 1380 usec, 1.12 ! 3992 > 2000 us
8916288: 572 + 360 + 352 + 84 = 1376 usec, 1.12 ! 3996 > 2000 us
8921900: 572 + 356 + 356 + 88 = 1380 usec, 1.12 ! 3992 > 2000 us
8927508: 572 + 360 + 348 + 88 = 1372 usec, 1.13 ! 3996 > 2000 us
8933120: 580 + 344 + 356 + 88 = 1376 usec, 1.13 ! 3992 > 2000 us
8938728: 572 + 364 + 352 + 88 = 1384 usec, 1.12 ! 3996 > 2000 us
8944340: 572 + 352 + 352 + 92 = 1376 usec, 1.12 ! 3992 > 2000 us
```

If you comment CHECK_ELAPSED_TIME out, only the pitch angle is printed and `! 4844 > 2000 us` is not printed, which means the loop time is within 2000 usec.

```
1.14
1.14
1.13
1.12
1.12
1.12
1.12
1.13
1.13
1.12
1.12
```
