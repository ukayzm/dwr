# Test the performance of Serial output

This test measures the time taken to output characters to Serial port in 115200 baud rate.

The theoretical speed is 86.8 usec/char ( = 1 / 115200 * 10 bit). And we need to consider an error of micros().

## Test Result

Serial outputs with Arduino Uno
```
1       1 character: 84 usec
1234567890      10 character: 848 usec
123456789012    12 character: 1016 usec
1234567890
        10 character + linefeed: 1020 usec
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890        120 character: 10200 usec
...
```

It shows that

* 84 usec is taken to output 1 character, similar with the theoretical value.
* 12 characters can be output in 1 milli second.
* line feed by println() outputs 2 characters.
* 120 characters can be output in 10 milli seconds.

