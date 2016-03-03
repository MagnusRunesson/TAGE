//
//  animation_enemies.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 24/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Engine/Graphics/Animation.h"
#include "Data/alldata.h"

//
//
// Big red saucer
//
//
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

DEFINE_ANIMATION( enemy_saucer, true );


//
//
// Sparrow - the little green devil
//
//
const AnimationFrameDefinition animation_enemy_sparrow_frames[] =
{
	{
		&sprite_enemy_sparrow_00,
		10,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_sparrow_01,
		10,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_sparrow_02,
		10,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_sparrow_03,
		10,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( enemy_sparrow, true );


//
//
// Dragon Head - The red space ship with the yellow tails
//
//
const AnimationFrameDefinition animation_enemy_dragonhead_frames[] = {
	{
		&sprite_enemy_dragonhead_00,
		1,
		0,
		0,
		0,
	}
};

DEFINE_ANIMATION( enemy_dragonhead, true );


//
//
// Dragon Head - The red space ship with the yellow tails
//
//
const AnimationFrameDefinition animation_enemy_dragonbody_frames[] = {
	{
		&sprite_enemy_dragonbody_00,
		1,
		0,
		0,
		0,
	}
};

DEFINE_ANIMATION( enemy_dragonbody, true );


//
//
// Cargo - The enemy that spawn pickups
//
//
const AnimationFrameDefinition animation_enemy_cargo_frames[] = {
	{
		&sprite_enemy_cargo_00,
		1,
		0,
		0,
		0,
	}
};

DEFINE_ANIMATION( enemy_cargo, true );




//
//
// Bullet - A bullet from an enemy
//
//
const AnimationFrameDefinition animation_enemy_bullet_frames[] = {
	{
		&sprite_enemy_bullet_00,
		1,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_bullet_01,
		1,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_bullet_02,
		1,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_bullet_03,
		1,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_bullet_02,
		1,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_bullet_01,
		1,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( enemy_bullet, true );




//
//
// Turret - An enemy that doesn't move, and is always aiming towards the player, firing continuously
//
//
const AnimationFrameDefinition animation_enemy_turret_frames[] = {
	{
		&sprite_enemy_turret_00,
		10,
		0,
		0,
		-1,
	},
	{
		&sprite_enemy_turret_01,
		10,
		0,
		0,
		0,
	},
	{
		&sprite_enemy_turret_02,
		10,
		0,
		0,
		-1,
	},
	{
		&sprite_enemy_turret_01,
		10,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( enemy_turret, true );





//
//
// Tallonclaw - Small yellow hook that likes to fly in group in a wave pattern
//
//
const AnimationFrameDefinition animation_enemy_tallonclaw_frames[] = {
	{
		&sprite_enemy_tallonclaw_00,
		10,
		0,
		-1,
		-1,
	},
};

DEFINE_ANIMATION( enemy_tallonclaw, true );



//
//
// Spacebase secret passage - It looks like a regular spacebase wall but it can be destroyed
//
//
const AnimationFrameDefinition animation_enemy_spacebase_secretpassage_frames[] = {
	{
		&sprite_enemy_spacebase_secretpassage,
		100,
		0,
		0,
		0,
	},
};

DEFINE_ANIMATION( enemy_spacebase_secretpassage, true );






//
//
// Heidelberg - A massive tank that fires death through its turret / exhaust pipe
//
//
const AnimationFrameDefinition animation_enemy_heidelberg_move_frames[] = {
	{
		&sprite_enemy_heidelberg_00,
		10,
		0,
		0,
		14,
	},
	{
		&sprite_enemy_heidelberg_01,
		10,
		0,
		0,
		14,
	},
};

DEFINE_ANIMATION( enemy_heidelberg_move, true );


const AnimationFrameDefinition animation_enemy_heidelberg_anticipation_frames[] = {
	{
		&sprite_enemy_heidelberg_00,
		30,
		0,
		0,
		14,
	},
};

DEFINE_ANIMATION( enemy_heidelberg_anticipation, true );


const AnimationFrameDefinition animation_enemy_heidelberg_fire_frames[] = {
	{
		&sprite_enemy_heidelberg_01,
		4,
		0,
		0,
		14,
	},
	{
		&sprite_enemy_heidelberg_02,
		4,
		0,
		0,
		14,
	},
	{
		&sprite_enemy_heidelberg_03,
		4,
		0,
		0,
		14,
	},
	{
		&sprite_enemy_heidelberg_04,
		4,
		0,
		0,
		14,
	},
	{
		&sprite_enemy_heidelberg_03,
		4,
		0,
		0,
		14,
	},
};

DEFINE_ANIMATION( enemy_heidelberg_fire, true );
