// SDS198 dust sensor example
// EYE3


#include <SDS198.h>

float p100;
int err;

SDS198 my_sds;

#ifdef ESP32
HardwareSerial port(2);
#endif

void setup() {
	my_sds.begin(&port);
	Serial.begin(115200);
}

void loop() {
	err = my_sds.read(&p100);
	if (!err) {
		Serial.println("PM100:  " + String(p100));
	}
	delay(100);
}
