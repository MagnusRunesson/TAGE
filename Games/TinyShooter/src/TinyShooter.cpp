//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
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

#include "src/Ingame/ContextIngame.h"
#include "src/TitleScreen/ContextTitleScreen.h"
#include "src/ContextManager.h"

void tage_setup()
{
	fp2d a( 1, 1 );
	fp2d b( 10, 1 );
	FixedPoint d = Distance( a, b );
	printf("d=%i (%i)\n", d.GetInteger(), d.GetDebugRawValue());
	
	contextInit();
}

void tage_loop()
{
	pfnCurrentContextLoop();
	
	// Maybe also switch context?
	if( pfnContextSwitchTo != NULL )
	{
		pfnContextSwitchTo();
		pfnContextSwitchTo = NULL;
	}
}

void tage_debugTrigger( int _trigger )
{
	pfnCurrentContextDebugTrigger( _trigger );
}
