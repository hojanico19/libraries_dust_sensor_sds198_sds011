// SDS198 dust sensor example
// EYE3

#ifdef ESP32
#error ESP32 does not work with SoftSerial, use HardwareSerial example instead
#endif


#include <SDS198.h>

float pm100;
int error;

SDS198 my_sds;

void setup() {
	my_sds.begin(D1, D2); //RX, TX
	Serial.begin(9600);
}

void loop() {
	error = my_sds.read(&pm100);
	if (!error) {
		Serial.println("PM100:  " + String(pm100));
	}
	delay(100);
}
