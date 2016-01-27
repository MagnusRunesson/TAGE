//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Arduino.h"

// TinyArcade game engine
#include "Engine/Graphics/Screen.h"
#include "Engine/types.h"
#include "Engine/Math/FixedPoint.h"
#include "Abstraction layer/Joypad.h"
#include "Engine/Math/fpmath.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/TileRenderer.h"
#include "Engine/Graphics/Animation.h"

// Project specifics
#include "Data/alldata.h"

#include "src/ContextIngame.h"

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
