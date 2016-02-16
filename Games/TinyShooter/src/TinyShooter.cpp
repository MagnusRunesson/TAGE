//
//  TinyShooter.cpp
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

#ifndef TAGE_TARGET_MACOSX
void tcConfigure(uint32_t sampleRate);
void tcStart();
#endif

void tage_setup()
{
	debugInit();
	padInit();
	
#ifndef TAGE_TARGET_MACOSX
	analogWrite( A0, 0 );
	tcConfigure( 11025 );
	tcStart();
#endif

	display.begin();
	display.setBrightness( 10 );
	display.setBitDepth( 1 );
	display.setColorMode( 1 );
	display.initDMA();
	
	contextInit();
}

#ifndef TAGE_TARGET_MACOSX

bool tcIsSyncing()
{
	return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}

void tcStart()
{
	// Enable TC
	TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
	while( tcIsSyncing());
}

void tcReset()
{
	// Reset TCx
	TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
	while( tcIsSyncing());
	while( TC5->COUNT16.CTRLA.bit.SWRST );
}

void tcStop()
{
	// Disable TC5
	TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
	while( tcIsSyncing());
}

void tcConfigure(uint32_t sampleRate)
{
	// Enable GCLK for TCC2 and TC5 (timer counter input clock)
	GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5)) ;
	while (GCLK->STATUS.bit.SYNCBUSY);
	
	tcReset();
	
	// Set Timer counter Mode to 16 bits
	TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
	
	// Set TC5 mode as match frequency
	TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
	
	TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1;
	
	TC5->COUNT16.CC[0].reg = (uint16_t) (SystemCoreClock / sampleRate - 1);
	while (tcIsSyncing());
	
	// Configure interrupt request
	NVIC_DisableIRQ(TC5_IRQn);
	NVIC_ClearPendingIRQ(TC5_IRQn);
	NVIC_SetPriority(TC5_IRQn, 0);
	NVIC_EnableIRQ(TC5_IRQn);
	
	// Enable the TC5 interrupt request
	TC5->COUNT16.INTENSET.bit.MC0 = 1;
	while( tcIsSyncing());
}


#endif

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
