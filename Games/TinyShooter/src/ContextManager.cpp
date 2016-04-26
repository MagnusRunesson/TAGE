//
//  ContextManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-31.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "src/ContextManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/TitleScreen/ContextTitleScreen.h"
#include "src/WinScreen/ContextWinScreen.h"

void(*pfnCurrentContextLoop)();
void(*pfnCurrentContextDebugTrigger)( int );
void(*pfnCurrentContextExit)();
void(*pfnContextSwitchTo)();

int contextSwitchTo;

void startTitle()
{
	//
	// Title screen
	//
	pfnCurrentContextDebugTrigger = &titlescreen_debugTrigger;
	pfnCurrentContextLoop = &titlescreen_loop;
	pfnCurrentContextExit = &titlescreen_exit;
	titlescreen_setup();
}

void startIngame()
{
	//
	// Ingame
	//
	pfnCurrentContextDebugTrigger = &ingame_debugTrigger;
	pfnCurrentContextLoop = &ingame_loop;
	pfnCurrentContextExit = &ingame_exit;
	ingame_setup();
}

void startWinScreen()
{
	//
	// Win screen
	//
	pfnCurrentContextDebugTrigger = &winscreen_debugTrigger;
	pfnCurrentContextLoop = &winscreen_loop;
	pfnCurrentContextExit = &winscreen_exit;
	winscreen_setup();
}

void contextInit()
{
	pfnContextSwitchTo = NULL;

	startTitle();
	//startIngame();
	//startWinScreen();
}

void _contextGotoIngame()
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

void _contextGotoTitleScreen()
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

void _contextGotoWinScreen()
{
	// Clean up previous context
	pfnCurrentContextExit();
	
	// Setup new context function pointesr
	pfnCurrentContextDebugTrigger = &winscreen_debugTrigger;
	pfnCurrentContextLoop = &winscreen_loop;
	pfnCurrentContextExit = &winscreen_exit;
	
	// Also initialize the title screen context
	winscreen_setup();
}

void contextGotoIngame()
{
	pfnContextSwitchTo = &_contextGotoIngame;
}

void contextGotoTitleScreen()
{
	pfnContextSwitchTo = &_contextGotoTitleScreen;
}

void contextGotoWinScreen()
{
	pfnContextSwitchTo = &_contextGotoWinScreen;
}