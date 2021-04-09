//
//  Joypad.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Abstraction layer/Joypad.h"
#include "Engine/BitHelpers.h"

#ifdef TAGE_TARGET_MACOSX

extern int gKeyDPadBuff;


uint8 gkeys;
int gKeyBuff;

void padInit()
{
	
}

void padUpdate()
{
	gkeys <<= 4;
	gkeys |= gKeyBuff;
}

uint8 padGet( sint8* _x, sint8* _y )
{
	*_x = padGetX();
	*_y = padGetY();

	return gkeys;
}

uint8 padGetKeys()
{
	return gkeys;
}

sint8 padGetX()
{
	sint8 ret = 0;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_LEFT ))	ret -= 1;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_RIGHT ))	ret += 1;
	
	return ret;
}

sint8 padGetY()
{
	sint8 ret = 0;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_UP ))	ret -= 1;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_DOWN ))	ret += 1;
	
	return ret;
}

uint8 padGetPressed()
{
	uint8 prev = (gkeys>>4) & 0x0f;
	uint8 curr = (gkeys) & 0x0f;
	uint8 ret = (prev ^ curr) & curr;
	return ret;
}

uint8 padGetReleased()
{
	uint8 prev = (gkeys>>4) & 0x0f;
	uint8 curr = (gkeys) & 0x0f;
	uint8 ret = (prev ^ curr) & prev;
	return ret;
}

#else

uint8 gkeys;
int gKeyBuff;
int padX, padY;

#include <SPI.h>
#include <Wire.h>

#define TinyArcadePinX 42
#define TinyArcadePinY 1
#define TinyArcadePin1 45
#define TinyArcadePin2 44

void padInit()
{
	pinMode( TinyArcadePin1, INPUT_PULLUP );
	pinMode( TinyArcadePin2, INPUT_PULLUP );
	
	gKeyBuff = 0;
	gkeys = 0;
	padX = 0;
	padY = 0;
}

void padUpdate()
{
	const int deadzone = 125;
	padX = 0;
	padY = 0;
	int rx = analogRead( TinyArcadePinX );
	int ry = analogRead( TinyArcadePinY );
	if( rx < (512-deadzone)) padX = 1;
	if( rx > (512+deadzone)) padX = -1;
	if( ry < (512-deadzone)) padY = -1;
	if( ry > (512+deadzone)) padY = 1;
	
	gkeys <<= 4;
	if( !digitalRead( TinyArcadePin2 ))
		gkeys |= PAD_KEYMASK_PRIMARY;

	if( !digitalRead( TinyArcadePin1 ))
		gkeys |= PAD_KEYMASK_SECONDARY;
}

uint8 padGet( sint8* _x, sint8* _y )
{
	*_x = padX;
	*_y = padY;
	
	return gkeys;
}

uint8 padGetKeys()
{
	return gkeys;
}

sint8 padGetX()
{
	return padX;
}

sint8 padGetY()
{
	return padY;
}

uint8 padGetPressed()
{
	uint8 prev = (gkeys>>4) & 0x0f;
	uint8 curr = (gkeys) & 0x0f;
	uint8 ret = (prev ^ curr) & curr;
	return ret;
}

uint8 padGetReleased()
{
	uint8 prev = (gkeys>>4) & 0x0f;
	uint8 curr = (gkeys) & 0x0f;
	uint8 ret = (prev ^ curr) & prev;
	return ret;
}

uint16* screenBuffer;

uint32 nanos()
{
	return 0;
}

#endif
