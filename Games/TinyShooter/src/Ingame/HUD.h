//
//  HUD.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-30.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef PlayerHUD_h
#define PlayerHUD_h

#define HUD_WEAPON_NONE				(0)
#define HUD_WEAPON_SINGLEFIRE		(1)
#define HUD_WEAPON_DUALFIRE			(2)

void hudInit();
void hudSetPrimary( int _weapon );
void hudSetSecondary( int _weapon );
void hudSetNumLives( int _numLives );

#endif /* PlayerHUD_h */
