//
//  Screen.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include "types.h"

const int SCREEN_WIDTH = 96;
const int SCREEN_HEIGHT = 64;

const int COLORSHIFT_16_R = 11;
const int COLORSHIFT_16_G = 5;
const int COLORSHIFT_16_B = 0;
const int COLORWIDTH_16_R = 0x1f;
const int COLORWIDTH_16_G = 0x3f;
const int COLORWIDTH_16_B = 0x1f;

extern uint16* screenBuffer;

#endif /* Screen_hpp */
