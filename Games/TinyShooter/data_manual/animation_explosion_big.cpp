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

const AnimationFrameDefinition animation_explosion_big_frames[] =
{
	{
		&sprite_explosion_big_00,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_big_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_big_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_big_03,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_big_04,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_big_05,
		5,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( explosion_big, false );
