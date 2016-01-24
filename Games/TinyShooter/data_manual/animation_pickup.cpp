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

const AnimationFrameDefinition animation_pickup_frames[] =
{
	{
		&sprite_pickup_00,
		65,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_03,
		5,
		0,
		0,
		0,
	},
};

extern "C" const AnimationSequenceDefinition animation_pickup;
const AnimationSequenceDefinition animation_pickup =
{
	4,
	animation_pickup_frames,
};

