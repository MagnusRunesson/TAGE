//
//  animation_explosion_big.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 24/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Engine/Graphics/Animation.h"
#include "data/alldata.h"

const AnimationFrameDefinition animation_impact_bullet_frames[] =
{
	{
		&sprite_impact_bullet_00,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_impact_bullet_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_impact_bullet_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_impact_bullet_03,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_impact_bullet_04,
		5,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( impact_bullet, false );
