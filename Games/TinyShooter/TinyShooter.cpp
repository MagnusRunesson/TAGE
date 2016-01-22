//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Arduino.h"

// TinyArcade game engine
#include "Screen.h"
#include "types.h"
#include "FixedPoint.h"
#include "Joypad.h"
#include "fpmath.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "TileRenderer.h"
#include "Animation.h"

// Project specifics
#include "alldata.h"

#include "ContextIngame.h"

void setup()
{
	ingame_setup();
}

void loop()
{
	ingame_loop();
}

void debugTrigger( int _trigger )
{
	ingame_debugTrigger( _trigger );
}
