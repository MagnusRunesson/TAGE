//
//  Joypad.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "types.h"
#include "Joypad.h"
#include "bithelpers.h"

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
