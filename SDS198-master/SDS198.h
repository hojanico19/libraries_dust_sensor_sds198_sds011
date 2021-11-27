// SDS198 dust sensor PM100
// EYE3

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef ESP32
#include <SoftwareSerial.h>
#endif

class SDS198 {
	public:
		SDS198(void);
		void begin(HardwareSerial* serial);
#ifndef ESP32
		void begin(SoftwareSerial* serial);
		void begin(uint8_t pin_rx, uint8_t pin_tx);
#endif
		int read(float *p100);
		void sleep();
		void wakeup();
	private:
		uint8_t _pin_rx, _pin_tx;
		Stream *sds_data;
};
