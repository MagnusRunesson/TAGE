//
//  HUD.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-30.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef PlayerHUD_h
#define PlayerHUD_h

#define HUD_WEAPON_SINGLEFIRE		(0)
#define HUD_WEAPON_DUALFIRE			(1)

void hudInit();
void hudSetWeapon( int _weapon );
void hudSetNumLives( int _numLives );

#endif /* PlayerHUD_h */
