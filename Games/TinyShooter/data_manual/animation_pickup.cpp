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
const AnimationFrameDefinition animation_playerbullet_laser_frames[] =
{
	{
		&sprite_playerbullet_laser_00,
		2,
		0,
		0,
		3,
	},
	{
		&sprite_playerbullet_laser_01,
		2,
		0,
		0,
		3,
	},
	{
		&sprite_playerbullet_laser_02,
		2,
		0,
		0,
		3,
	},
	{
		&sprite_playerbullet_laser_03,
		2,
		0,
		0,
		2,
	},
	{
		&sprite_playerbullet_laser_04,
		2,
		0,
		0,
		2,
	},
	{
		&sprite_playerbullet_laser_05,
		2,
		0,
		-4,
		2,
	},
	{
		&sprite_playerbullet_laser_06,
		2,
		0,
		-20,
		2,
	},
	{
		&sprite_playerbullet_laser_07,
		2,
		0,
		-33,
		2,
	},
	{
		&sprite_playerbullet_laser_08,
		2,
		0,
		-47,
		2,
	},
	{
		&sprite_playerbullet_laser_09,
		2,
		0,
		-61,
		1,
	},
};

DEFINE_ANIMATION( playerbullet_laser, true );




//
//
//
//
//
const AnimationFrameDefinition animation_pickup_pew_frames[] =
{
	{
		&sprite_pickup_pew_00,
		65,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_pew_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_pew_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_pew_03,
		5,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( pickup_pew, true );


//
//
//
//
//
const AnimationFrameDefinition animation_pickup_bomb_frames[] =
{
	{
		&sprite_pickup_bomb_00,
		65,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_bomb_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_bomb_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_bomb_03,
		5,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( pickup_bomb, true );


//
//
//
//
//
const AnimationFrameDefinition animation_pickup_laser_frames[] =
{
	{
		&sprite_pickup_laser_00,
		65,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_laser_01,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_laser_02,
		5,
		0,
		0,
		0,
	},
	{
		&sprite_pickup_laser_03,
		5,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( pickup_laser, true );
