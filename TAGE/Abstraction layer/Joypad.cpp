//
//  Joypad.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Abstraction Layer/Joypad.h"
#include "Engine/BitHelpers.h"

extern int gKeyDPadBuff;


uint8 gkeys;
int gKeyBuff;

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
