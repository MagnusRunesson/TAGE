//
//  Timer.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

//#include "SDL2/SDL.h"
#include <chrono>

#include "Timer.h"
#include "Types.h"

uint32 timerStartMicros;
uint32 timerStartMillis;

uint32 micros()
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
	uint32 ret = (uint32)std::chrono::duration_cast<std::chrono::microseconds>(now).count();
	return ret - timerStartMicros;
}

uint32 millis()
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
	uint32 ret = (uint32)std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
	return ret - timerStartMillis;
}

uint32 nanos()
{
	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
	uint32 ret = (uint32)std::chrono::duration_cast<std::chrono::nanoseconds>( now ).count();
	return ret;
}

void delay( uint32 milliseconds )
{
	//SDL_Delay( milliseconds );
}

void delayMicroseconds( uint32 microseconds )
{
	//delay( microseconds / 1000 );
}

void timerInit()
{
	timerStartMicros = 0;
	timerStartMicros = micros();
	
	timerStartMillis = 0;
	timerStartMillis = millis();
}

