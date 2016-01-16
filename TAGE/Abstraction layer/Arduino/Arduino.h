#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <cstdint>
#include <cstddef>
#include <cstdlib>

#include <inttypes.h>

#include "types.h"

#define _BV(x) (1u<<(x))


typedef uint8 byte;

class Print
{
public:
};


class  SimSerial
{
public:
	void begin(uint32_t speed);
	void println(uint32_t speed);
};

extern SimSerial Serial;

//extern void putString(int row, int col, int color, const char* msg, const FONT_INFO fontInfo);

extern uint32 micros();
extern uint32 millis();
extern void delay( uint32 millis );
extern void delayMicroseconds( uint32 microseconds );

#endif
