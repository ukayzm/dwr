# MPU6050-comp (Complementary Filter)

This test measures the pitch angle with Complementary Filter and compute the elapsed time.

You can measure the time by uncommenting CHECK_ELAPSED_TIME in mpu6050.h.

The target of the loop time is max 2000 usec. If the loop time exceeds this value, `! xxxx > 2000 us` is printed.

The example of output with CHECK_ELAPSED_TIME uncommented is as the following. You can see that although the time to get the angle is around 1280 usec but `! xxxx > 2000 us` is printed because it printed too many characters.

```
3962856: 596 + 556 + 4 + 256 = 1420 usec, 82.99 ! 3996 > 2000 us
3968468: 596 + 548 + 4 + 256 = 1412 usec, 82.99 ! 3992 > 2000 us
3974076: 592 + 556 + 4 + 256 = 1416 usec, 82.99 ! 3996 > 2000 us
3979688: 588 + 556 + 4 + 256 = 1412 usec, 82.97 ! 3992 > 2000 us
3985296: 592 + 552 + 4 + 256 = 1412 usec, 82.97 ! 3996 > 2000 us
3990908: 588 + 552 + 0 + 256 = 1404 usec, 83.00 ! 3992 > 2000 us
3996520: 592 + 552 + 4 + 264 = 1416 usec, 82.98 ! 3992 > 2000 us
4002128: 588 + 548 + 4 + 256 = 1404 usec, 82.96 ! 3992 > 2000 us
4007736: 592 + 548 + 4 + 264 = 1416 usec, 82.95 ! 3996 > 2000 us
4013348: 592 + 552 + 4 + 252 = 1408 usec, 82.96 ! 3992 > 2000 us
4018960: 592 + 544 + 0 + 264 = 1404 usec, 82.93 ! 3992 > 2000 us
4024568: 588 + 552 + 4 + 256 = 1408 usec, 82.97 ! 3996 > 2000 us
4030180: 596 + 544 + 4 + 264 = 1408 usec, 82.98 ! 3992 > 2000 us
```

Comparing to Kalman Filter, it uses less time by 300 usec.
