//
//  EnemyDefinition.h
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#ifndef TinyShooter_EnemyDefinition_h
#define TinyShooter_EnemyDefinition_h

#include "Engine/Types.h"

class AnimationSequenceDefinition;
class Enemy;

class EnemyDefinition
{
public:
	const AnimationSequenceDefinition* pAnimationDefinition;
	uint8 StartHealth;
	uint8 SpecialFlag;
	void(*pfnMovement)( Enemy* _pTarget );
};

#endif
