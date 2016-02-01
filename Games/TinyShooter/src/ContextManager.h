//
//  ContextManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-31.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef ContextManager_h
#define ContextManager_h

extern void(*pfnCurrentContextLoop)();
extern void(*pfnCurrentContextDebugTrigger)( int );
extern void(*pfnCurrentContextExit)();
extern void(*pfnContextSwitchTo)();

void contextInit();
void contextGotoIngame();
void contextGotoTitleScreen();

#endif /* ContextManager_h */
