//
//  ContextManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-31.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "src/ContextManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/TitleScreen/ContextTitleScreen.h"

void(*pfnCurrentContextLoop)();
void(*pfnCurrentContextDebugTrigger)( int );
void(*pfnCurrentContextExit)();

void contextInit()
{
	/*

	//
	// Initialize function pointers with the title screen as the initial context
	//
	pfnCurrentContextDebugTrigger = &titlescreen_debugTrigger;
	pfnCurrentContextLoop = &titlescreen_loop;
	pfnCurrentContextExit = &titlescreen_exit;
	 
	titlescreen_setup();

	/*/
	
	//
	// Initialize function pointers with ingame for the initial context
	//
	
	pfnCurrentContextDebugTrigger = &ingame_debugTrigger;
	pfnCurrentContextLoop = &ingame_loop;
	pfnCurrentContextExit = &ingame_exit;
	
	ingame_setup();

	/**/
}

void contextGotoIngame()
{
	// Clean up previous context
	pfnCurrentContextExit();
	
	// Setup new context function pointesr
	pfnCurrentContextDebugTrigger = &ingame_debugTrigger;
	pfnCurrentContextLoop = &ingame_loop;
	pfnCurrentContextExit = &ingame_exit;
	
	// Also initialize the ingame context
	ingame_setup();
}

void contextGotoTitleScreen()
{
	// Clean up previous context
	pfnCurrentContextExit();
	
	// Setup new context function pointesr
	pfnCurrentContextDebugTrigger = &titlescreen_debugTrigger;
	pfnCurrentContextLoop = &titlescreen_loop;
	pfnCurrentContextExit = &titlescreen_exit;
	
	// Also initialize the title screen context
	titlescreen_setup();
}