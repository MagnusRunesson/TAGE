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

const AnimationFrameDefinition animation_explosion_medium_frames[] =
{
	{
		&sprite_explosion_medium_00,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_03,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_04,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_05,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_06,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_07,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_explosion_medium_08,
		5,
		0,
		0,
		0,
	},
};

const AnimationSequenceDefinition animation_explosion_medium =
{
	9,
	false,
	animation_explosion_medium_frames,
};

