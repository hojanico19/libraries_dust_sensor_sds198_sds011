# SDS198
  
Arduino library for dust Sensor SDS198 (Nova Fitness Co.,Ltd)  
This library uses SoftSerial or HardwareSerial to connect to the SDS198.  

## Usage

* Define SDS object:
i.e. ```SDS198 mySDS;```

* Start object:
```void begin(pinRX,pinTX);```
i.e. ```mySDS.begin(pinRX,pinTX);```

* Read values:
```int read(float *p100);```
i.e. ```error = mySDS(&pm100);```

Reads the PM100 values, return code is 0, if new values were read, and 1 if there were no new values.  

### Alternative with HardwareSerial
* SDS object can also be initialized with a Serial object as parameter  
i.e.
```
SDS198 mySDS;
mySDS.begin(Serial1);
```
HardwareSerial objects need to be defined if using ESP32
