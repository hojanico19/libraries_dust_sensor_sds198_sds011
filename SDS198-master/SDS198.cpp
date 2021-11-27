// SDS198 dust sensor PM100
// EYE3


#include "SDS198.h"

static const byte SLEEPCMD[19] = {
	0xAA,	// head
	0xB4,	// command id
	0x06,	// data byte 1
	0x01,	// data byte 2 (set mode)
	0x00,	// data byte 3 (sleep)
	0x00,	// data byte 4
	0x00,	// data byte 5
	0x00,	// data byte 6
	0x00,	// data byte 7
	0x00,	// data byte 8
	0x00,	// data byte 9
	0x00,	// data byte 10
	0x00,	// data byte 11
	0x00,	// data byte 12
	0x00,	// data byte 13
	0xFF,	// data byte 14 (device id byte 1)
	0xFF,	// data byte 15 (device id byte 2)
	0x05,	// checksum
	0xAB	// tail
};

SDS198::SDS198(void) {

}

// --------------------------------------------------------
// SDS198:read
// --------------------------------------------------------
int SDS198::read(float *p100) {
	byte buffer;
	int value;
	int len = 0;
	int bypass=0;
	int pm100_serial = 0;
	int checksum_is;
	int checksum_ok = 0;
	int error = 1;
	int bp = 1;
	while ((sds_data->available() > 0) && (sds_data->available() >= (10-len))) {
		buffer = sds_data->read();
		value = int(buffer);
		switch (len) {
			case (0): if (value != 170) { len = -1; }; break; //Verifica encabezado aa
			case (1): if (value != 207) { len = -1; }; break; //Verifica encabezado cf //Difiere que sensor esta usando
			case (2): bypass = value; checksum_is = value; break;
			case (3): bypass += (value << 8); checksum_is += value; break;
			case (4): pm100_serial = value; checksum_is += value; break;
			case (5): pm100_serial += (value << 8); checksum_is += value; break;
			case (6): checksum_is += value; break;
			case (7): checksum_is += value; break;
			case (8): bp=1; break;
			case (9): if (value != 171) { len = -1; }; break;
		}
		len++;
		if (len == 10) {
			*p100 = (float)pm100_serial/10.0;
			len = 0; checksum_ok = 0; pm100_serial = 0.0; bypass = 0.0; checksum_is = 0;
			error = 0;
		}
		yield();
	}
	return error;
}

// --------------------------------------------------------
// SDS198:sleep
// --------------------------------------------------------
void SDS198::sleep() {
	for (uint8_t i = 0; i < 19; i++) {
		sds_data->write(SLEEPCMD[i]);
	}
	sds_data->flush();
	while (sds_data->available() > 0) {
		sds_data->read();
	}
}

// --------------------------------------------------------
// SDS198:wakeup
// --------------------------------------------------------
void SDS198::wakeup() {
	sds_data->write(0x01);
	sds_data->flush();
}

#ifndef ESP32
void SDS198::begin(uint8_t pin_rx, uint8_t pin_tx) {
	_pin_rx = pin_rx;
	_pin_tx = pin_tx;

	SoftwareSerial *softSerial = new SoftwareSerial(_pin_rx, _pin_tx);

	softSerial->begin(9600);

	sds_data = softSerial;
}
#endif

void SDS198::begin(HardwareSerial* serial) {
	serial->begin(9600);
	sds_data = serial;
}

#ifndef ESP32
void SDS198::begin(SoftwareSerial* serial) {
	serial->begin(9600);
	sds_data = serial;
}
#endif
