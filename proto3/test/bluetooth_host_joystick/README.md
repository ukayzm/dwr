# Bluetooth

It tests Bluetooth and connect with Joystick using BLE and Bluetooth classic (so called 3.0).

The code was mainly taken from https://github.com/espressif/esp-idf/tree/master/examples/bluetooth/esp_hid_host.

## Build and Run

Change `COM4` or `/dev/cu.usbserial-1130` according to your environment.

Windows: open ESP-IDF shell (CMD or PowerShell), change to the source directory, and then:

```
idf.py set-target esp32
idf.py build
idf.py -p COM4 flash monitor
```

MacOS: open a shell, change to the source directory, and then:

```
source ~/esp/esp-idf/export.sh
idf.py set-target esp32
idf.py build
idf.py -p /dev/cu.usbserial-1130 flash monitor
```

## Results

I tried to connect with Nintendo Switch Joy-Con. I started ESP32 and pressed the pairing button on the Joy-Con. Then the connection was established.

```
I (620) ESP_HIDH_DEMO: setting hid gap, mode:3
I (620) BTDM_INIT: BT controller compile version [60aae55]
I (630) phy_init: phy_version 4670,719f9f6,Feb 18 2021,17:07:07
I (1350) ESP_HIDH_DEMO: EVENT: 5
I (1360) ESP_HIDH_DEMO: SCAN...
I (1360) main_task: Returned from app_main()
BLE: f8:1f:60:70:35:70, RSSI: -87, UUID: 0x0000, APPEARANCE: 0x0000, ADDR_TYPE: 'RANDOM'
BLE: 4f:45:41:4c:fc:77, RSSI: -40, UUID: 0x0000, APPEARANCE: 0x0000, ADDR_TYPE: 'RANDOM'
...
BT : 5c:52:1e:41:d0:d6, COD: major: PERIPHERAL, minor: 2, service: 0x001, RSSI: -71, NAME: Joy-Con (L)
BT : 5c:52:1e:41:d0:d6, COD: major: PERIPHERAL, minor: 2, service: 0x001, RSSI: -70, NAME: Joy-Con (L)
...
I (10200) ESP_HIDH_DEMO: SCAN: 1 results
  BT : 5c:52:1e:41:d0:d6, RSSI: -58, USAGE: GENERIC, COD: PERIPHERAL[GAMEPAD] srv 0x001, UUID16: 0x0000, NAME: Joy-Con (L)
I (11300) ESP_HIDH_DEMO: 5c:52:1e:41:d0:d6 OPEN:
BDA:5c:52:1e:41:d0:d6, Status: OK, Connected: YES, Handle: 0, Usage: GAMEPAD
Name: , Manufacturer: , Serial Number:
PID: 0x2006, VID: 0x057e, VERSION: 0x0001
Report Map Length: 170
    VENDOR  OUTPUT REPORT, ID:  18, Length:  48
    VENDOR  OUTPUT REPORT, ID:  17, Length:  48
    VENDOR  OUTPUT REPORT, ID:  16, Length:  48
    VENDOR  OUTPUT REPORT, ID:   1, Length:  48
    VENDOR   INPUT REPORT, ID:  63, Length:  11
    VENDOR   INPUT REPORT, ID:  51, Length: 361
    VENDOR   INPUT REPORT, ID:  50, Length: 361
    VENDOR   INPUT REPORT, ID:  49, Length: 361
    VENDOR   INPUT REPORT, ID:  48, Length:  48
   GAMEPAD   INPUT REPORT, ID:  33, Length:  48
```

After the connection has been established, I pressed some buttons or moved the stick and could get the INPUT event.

```
I (24310) ESP_HIDH_DEMO: 5c:52:1e:41:d0:d6 INPUT:   VENDOR, MAP:  0, ID:  63, Len: 11, Data:
I (24310) ESP_HIDH_DEMO: 00 00 02 00 80 00 80 00 80 00 80
I (24560) ESP_HIDH_DEMO: 5c:52:1e:41:d0:d6 INPUT:   VENDOR, MAP:  0, ID:  63, Len: 11, Data:
I (24560) ESP_HIDH_DEMO: 00 00 08 00 80 00 80 00 80 00 80
I (27280) ESP_HIDH_DEMO: 5c:52:1e:40:8b:5b INPUT:   VENDOR, MAP:  0, ID:  63, Len: 11, Data:
I (27280) ESP_HIDH_DEMO: 00 00 04 00 80 00 80 00 80 00 80
I (27580) ESP_HIDH_DEMO: 5c:52:1e:40:8b:5b INPUT:   VENDOR, MAP:  0, ID:  63, Len: 11, Data:
I (27580) ESP_HIDH_DEMO: 00 00 08 00 80 00 80 00 80 00 80
```

# Result with Another Joystick

```
BT : 0c:fc:83:78:09:fb, COD: major: PERIPHERAL, minor: 16, service: 0x001, RSSI: -57, UUID16: 0x1124
BT : 0c:fc:83:78:09:fb, COD: major: PERIPHERAL, minor: 16, service: 0x001, RSSI: -63, UUID16: 0x1124
...
I (10211) ESP_HIDH_DEMO: SCAN: 1 results
  BT : 0c:fc:83:78:09:fb, RSSI: -59, USAGE: GENERIC, COD: PERIPHERAL[KEYBOARD] srv 0x001, UUID16: 0x1124, NAME:
W (12081) BT_HCI: hcif conn complete: hdl 0x81, st 0x0
W (12091) ESP_HID_GAP: BT GAP EVENT UNKNOWN 16
W (12261) BT_SDP: process_service_attr_rsp

W (12461) BT_SDP: process_service_attr_rsp

W (12841) BT_APPL: new conn_srvc id:23, app_id:2
I (12921) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb OPEN:
BDA:0c:fc:83:78:09:fb, Status: OK, Connected: YES, Handle: 0, Usage: KEYBOARD
Name: , Manufacturer: , Serial Number:
PID: 0x0000, VID: 0x0000, VERSION: 0x0000
Report Map Length: 175
   GAMEPAD   INPUT REPORT, ID:   4, Length:   6
  CCONTROL   INPUT REPORT, ID:   3, Length:   2
     MOUSE   INPUT   BOOT, ID:   2, Length:   3
     MOUSE   INPUT REPORT, ID:   2, Length:   3
  KEYBOARD   INPUT   BOOT, ID:   1, Length:   8
  KEYBOARD   INPUT REPORT, ID:   1, Length:   7
```

After the connection has been established, I pressed some buttons or moved the stick and could get the INPUT event.

```
I (19081) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (19081) ESP_HIDH_DEMO: 00 00 02
I (19081) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (19091) ESP_HIDH_DEMO: 00 00 02
```

After some time, the connection has been closed.

```
I (29131) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (29131) ESP_HIDH_DEMO: 00 00 fc
I (29141) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (29151) ESP_HIDH_DEMO: 00 00 fd
W (43041) BT_HCI: hci cmd send: sniff: hdl 0x81, intv(30 54)
W (73031) BT_HCI: hcif mode change: hdl 0x81, mode 0, intv 0, status 0x22
E (73031) BT_APPL: bta_dm_pm_btm_status hci_status=34
I (73031) ESP_HID_GAP: BT GAP MODE_CHG_EVT mode:0
W (73101) BT_HCI: hcif disc complete: hdl 0x81, rsn 0x22
W (73101) BT_APPL: bta_hh_co_close: dev_handle = 0, app_id = 2
W (73101) BT_APPL: bta_hh_co_close: Found an existing device with the same handle dev_status = 0, dev_handle =0
W (73121) ESP_HID_GAP: BT GAP EVENT UNKNOWN 17
I (73121) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb CLOSE:
```

The details

up/down

The byte 3 changes f1 to 0f, meaning -15 to +15.

```
I (478441) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (478441) ESP_HIDH_DEMO: 00 00 fd
I (478451) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (478461) ESP_HIDH_DEMO: 00 00 fe
```

left/right

The byte 2 changes f1 to 0f, meaning -15 to +15.

```
I (510771) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (510781) ESP_HIDH_DEMO: 00 0f 00
I (510781) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (510791) ESP_HIDH_DEMO: 00 0b 00
```

button

```
I (663291) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (663291) ESP_HIDH_DEMO: 01 00 00
I (663461) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT:    MOUSE, MAP:  0, ID:   2, Len: 3, Data:
I (663461) ESP_HIDH_DEMO: 00 00 00

I (812681) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT: CCONTROL, MAP:  0, ID:   3, Len: 2, Data:
I (812681) ESP_HIDH_DEMO: e9 00
I (812811) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT: CCONTROL, MAP:  0, ID:   3, Len: 2, Data:
I (812811) ESP_HIDH_DEMO: 00 00

I (772201) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT: CCONTROL, MAP:  0, ID:   3, Len: 2, Data:
I (772201) ESP_HIDH_DEMO: 46 00
I (772391) ESP_HIDH_DEMO: 0c:fc:83:78:09:fb INPUT: CCONTROL, MAP:  0, ID:   3, Len: 2, Data:
I (772391) ESP_HIDH_DEMO: 00 00
```
