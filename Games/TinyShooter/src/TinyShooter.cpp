//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "TinyScreen.h"
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
#include "Engine/Debug.h"

// Project specifics
#include "Data/alldata.h"

#include "src/Ingame/ContextIngame.h"
#include "src/TitleScreen/ContextTitleScreen.h"
#include "src/ContextManager.h"

TinyScreen display = TinyScreen( TinyScreenPlus );

void tage_setup()
{
	debugInit();
	padInit();
	
	display.begin();
	display.setBrightness( 10 );
	display.setBitDepth( 1 );
	//display.setColorMode( 1 );

#ifndef TAGE_TARGET_MACOSX
	uint8_t remap=(1<<5);// + (1<<2);
	remap|=(1<<6);	// Bit depth
	//remap^=(1<<2);	// Color mode
	display.startCommand();
	display.TSSPI->transfer(0xA0);//set remap
	display.TSSPI->transfer(remap);
	display.endTransfer();
	
	display.initDMA();
#endif
	
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
