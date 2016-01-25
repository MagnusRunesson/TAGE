//
//  EnemyDefinition.h
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#ifndef TinyShooter_EnemyDefinition_h
#define TinyShooter_EnemyDefinition_h

#include "types.h"

class AnimationSequenceDefinition;

#define ENEMY_MOVEMENT_MASK_NOTHING	(0)

class EnemyDefinition
{
public:
	const AnimationSequenceDefinition* pAnimationDefinition;
	uint8 StartHealth;
	uint8 MovementDefinition;
};

#endif
