//
//  Joypad.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Joypad_hpp
#define Joypad_hpp

#include "Engine/Types.h"

const int PAD_KEYMASK_PRIMARY		= (1<<0);
const int PAD_KEYMASK_SECONDARY		= (1<<1);
const int PAD_KEYMASK_SELECT		= (1<<2);
const int PAD_KEYMASK_START			= (1<<3);
const int PAD_KEYMASK_DPAD_UP		= (1<<16);
const int PAD_KEYMASK_DPAD_DOWN		= (1<<17);
const int PAD_KEYMASK_DPAD_LEFT		= (1<<18);
const int PAD_KEYMASK_DPAD_RIGHT	= (1<<19);

//
//
//
void padUpdate();
uint8 padGet( sint8* _x, sint8* _y );
uint8 padGetKeys();
sint8 padGetX();
sint8 padGetY();
uint8 padGetPressed();
uint8 padGetReleased();

#endif /* Joypad_hpp */
