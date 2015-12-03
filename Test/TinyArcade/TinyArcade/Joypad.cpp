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


uint8 getPad( sint8* _x, sint8* _y )
{
	gkeys <<= 4;
	gkeys |= gKeyBuff;
	
	*_x = 0;
	*_y = 0;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_UP ))	*_y -= 1;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_DOWN ))	*_y += 1;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_LEFT ))	*_x -= 1;
	if( HasBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_RIGHT ))	*_x += 1;

	return gkeys;
}

