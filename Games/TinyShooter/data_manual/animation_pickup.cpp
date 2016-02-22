//
//  animation_pickup.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 24/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Engine/Graphics/Animation.h"
#include "data/alldata.h"



//
//
//
//
//
const AnimationFrameDefinition animation_playerbullet_bomb_frames[] =
{
	{
		&sprite_playerbullet_bomb_00,
		15,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_03,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_04,
		10,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_03,
		2,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_04,
		2,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_03,
		2,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_04,
		2,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_03,
		2,
		0,
		0,
		0,
	},
	{
		&sprite_playerbullet_bomb_04,
		2,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( playerbullet_bomb, true );




//
//
//
//
//
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

DEFINE_ANIMATION( pickup, true );
