# MPU6050

Kalman filter and complement filter are added to mpu6050-i2cdevlib.

The pin is defined in example.cpp.

* PIN_SDA 21
* PIN_CLK 22

It displays the PITCH angle from DMP, Y angle by Kalman, and Y angle by Complementary filter.

I lifted the board to make the angle 25 degree, and layed it down to the desk to make the angle 0 degree at the time 22.5.

You can see that the complementary filter got settled down at first, then Kalman filter, and then DMP.

(1) complementary filter at 22.721770
(2) Kalman filter at 23.120942
(3) DMP: drifting...

```
22.221935:  702 us	YPR:	29.69	K:	22.30	C:	24.34
22.272014:  698 us	YPR:	28.89	K:	23.62	C:	24.55
22.322147:  701 us	YPR:	27.45	K:	24.90	C:	25.12
22.372207:  699 us	YPR:	25.51	K:	25.66	C:	24.63
22.422316:  698 us	YPR:	20.42	K:	26.70	C:	25.51
22.471631:  697 us	YPR:	13.99	K:	25.60	C:	20.13
22.521666:  697 us	YPR:	8.33	K:	23.10	C:	13.67
22.571673:  697 us	YPR:	2.57	K:	20.21	C:	8.52
22.621689:  697 us	YPR:	-2.72	K:	17.32	C:	5.19
22.671730:  702 us	YPR:	-9.09	K:	14.51	C:	2.56
22.721770:  703 us	YPR:	-10.24	K:	11.55	C:	0.20
22.771811:  697 us	YPR:	-10.45	K:	9.32	C:	-0.06
22.821825:  696 us	YPR:	-10.07	K:	7.39	C:	-0.17
22.871114:  697 us	YPR:	-9.72	K:	5.76	C:	-0.17
22.921081:  697 us	YPR:	-9.37	K:	4.37	C:	-0.13
22.971061:  697 us	YPR:	-9.00	K:	3.18	C:	-0.12
23.021024:  697 us	YPR:	-8.69	K:	2.17	C:	-0.10
23.070963:  697 us	YPR:	-8.37	K:	1.32	C:	-0.10
23.120942:  696 us	YPR:	-8.10	K:	0.62	C:	-0.06
23.170917:  697 us	YPR:	-7.84	K:	0.03	C:	-0.08
23.220926:  697 us	YPR:	-7.72	K:	-0.49	C:	-0.19
23.270930:  697 us	YPR:	-7.65	K:	-0.88	C:	-0.12
23.320919:  696 us	YPR:	-6.90	K:	-1.09	C:	0.20
23.370897:  697 us	YPR:	-6.53	K:	-1.43	C:	-0.17
23.420891:  697 us	YPR:	-6.27	K:	-1.64	C:	-0.17
23.470852:  697 us	YPR:	-6.02	K:	-1.78	C:	-0.14
23.520827:  697 us	YPR:	-5.78	K:	-1.87	C:	-0.11
23.570804:  695 us	YPR:	-5.56	K:	-1.93	C:	-0.10
23.620764:  695 us	YPR:	-5.33	K:	-1.96	C:	-0.10
23.670022:  697 us	YPR:	-5.12	K:	-1.97	C:	-0.12
23.719990:  696 us	YPR:	-4.91	K:	-1.96	C:	-0.12
```

