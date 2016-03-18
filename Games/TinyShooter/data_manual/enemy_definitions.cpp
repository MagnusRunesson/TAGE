//
//  EnemyDefinitions.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Graphics/Image.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/EnemyDefinition.h"
#include "src/Ingame/Enemy.h"
#include "data/alldata.h"

const EnemyDefinition enemy_saucer_easy =
{
	&animation_enemy_saucer,
	3,
	0,
	&EnemyMovement_00_FollowDirection,
};

const EnemyDefinition enemy_sparrow =
{
	&animation_enemy_sparrow,
	1,
	0,
	&EnemyMovement_00_FollowDirection,
};

const EnemyDefinition enemy_dragonhead =
{
	&animation_enemy_dragonhead,
	2,
	0,
	&EnemyMovement_01_Sinus_MoveLeft,
};

const EnemyDefinition enemy_dragonbody =
{
	&animation_enemy_dragonbody,
	2,
	0,
	&EnemyMovement_01_Sinus_MoveLeft,
};

const EnemyDefinition enemy_cargo =
{
	&animation_enemy_cargo,
	1,
	0,
	&EnemyMovement_00_FollowDirection
};

const EnemyDefinition enemy_bullet =
{
	&animation_enemy_bullet,
	0,
	ENEMY_SPECIALFLAG_INVINCIBLE,
	&EnemyMovement_00_FollowDirection
};

const EnemyDefinition enemy_turret =
{
	&animation_enemy_turret,
	4,
	0,
	NULL
};

const EnemyDefinition enemy_tallonclaw =
{
	&animation_enemy_tallonclaw,
	1,
	0,
	&EnemyMovement_02_HalfSinus_MoveLeft
};

const EnemyDefinition enemy_spacebase_secretpassage =
{
	&animation_enemy_spacebase_secretpassage,
	15,
	0,
	NULL
};

const EnemyDefinition enemy_spacebase_door =
{
	&animation_spacebase_boss_door_idle,
	0,
	ENEMY_SPECIALFLAG_SPACEBASEBOSSDOOR,
	NULL
};

const EnemyDefinition enemy_spacebase_warninglights =
{
	&animation_spacebase_boss_warninglights_idle,
	0,
	ENEMY_SPECIALFLAG_SPACEBASEBOSSDOOR,
	NULL
};

const EnemyDefinition enemy_heidelberg =
{
	&animation_enemy_heidelberg_move,
	10,
	0,
	NULL
};

const EnemyDefinition enemy_spinloop =
{
	&animation_enemy_spinloop,
	2,
	0,
	&EnemyMovement_Rotate,
};

const EnemyDefinition enemy_wallflower =
{
	&animation_enemy_wallflower_idle,
	2,
	0,
	NULL,
};
