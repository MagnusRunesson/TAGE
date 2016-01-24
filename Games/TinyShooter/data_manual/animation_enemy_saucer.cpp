//
//  animation_pickup.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 24/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "types.h"
#include "animation.h"
#include "alldata.h"

const AnimationFrameDefinition animation_enemy_saucer_frames[] =
{
	{
		&sprite_enemy_saucer_00,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_saucer_01,
		5,
		0,
		0,
		0,
	},
};

extern "C" const AnimationSequenceDefinition animation_enemy_saucer;
const AnimationSequenceDefinition animation_enemy_saucer =
{
	2,
	true,
	animation_enemy_saucer_frames,
};

