//
//  EnemyDefinitions.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Graphics/Image.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/EnemyDefinition.h"
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
