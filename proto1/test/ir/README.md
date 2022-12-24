# Test IR (Infra Red) receiver

Press button of IR transmitter (e.g., TV remote control). The received IR code is printed to serial port.

The example of the output from my RCU.

```
IR code = 98E965A3
IR code = D7D018EC
IR code = F49B208A
IR code = F49B208A
IR code = F49B208A
IR code = F49B208A
IR code = D7D018EC
IR code = D7D018EC
IR code = D7D018EC
IR code = D7D018EC
IR code = D7D018EC
```

# IRRemote

It uses the old version (2.x.x) of IRRemote library in https://github.com/Arduino-IRremote/Arduino-IRremote

You can get the old version like this:

```
git clone https://github.com/Arduino-IRremote/Arduino-IRremote.git
cd Arduino-IRremote
git checkout 2.8.0
cd ..
cp -r Arduino-IRremote ~/Arduino/library/IRRemote
```

