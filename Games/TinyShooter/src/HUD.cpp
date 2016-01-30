//
//  PlayerHUD.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-30.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Graphics/SpriteRenderer.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/Graphics/Image.h"
#include "Engine/Graphics/Screen.h"
#include "src/HUD.h"
#include "data/alldata.h"

Sprite* spriteHudWeaponsBG;
Sprite* spriteHudCurrentWeapon;

void hudInit()
{
	spriteHudWeaponsBG = spriteRenderer.AllocateSprite( &sprite_hud_weapons );
	spriteHudWeaponsBG->x = -1;//SCREEN_WIDTH-spriteHudWeaponsBG->image->w;
	spriteHudWeaponsBG->y = SCREEN_HEIGHT-spriteHudWeaponsBG->image->h;
	
	spriteHudCurrentWeapon = spriteRenderer.AllocateSprite( &sprite_pb_01 );
	
	hudSetWeapon( HUD_WEAPON_SINGLEFIRE );
}

void hudSetWeapon( int _weapon )
{
	int x, y;
	const Image* pImage = NULL;
	switch( _weapon )
	{
		case HUD_WEAPON_SINGLEFIRE:
			pImage = &sprite_pb_01;
			x = 2;
			y = SCREEN_HEIGHT-3;
			break;
			
		case HUD_WEAPON_DUALFIRE:
			pImage = &sprite_hud_weapon_dual;
			x = 1;
			y = SCREEN_HEIGHT-4;
			break;
	}
	
	// Verify that we actually found a weapon
	if( pImage == NULL )
		return;
	
	// Done and done!
	spriteHudCurrentWeapon->image = pImage;
	spriteHudCurrentWeapon->x = x;
	spriteHudCurrentWeapon->y = y;
}
