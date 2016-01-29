//
//  Explosions.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "src/ExplosionManager.h"
#include "src/ContextIngame.h"
#include "data/alldata.h"

#define NUM_EXPLOSIONS		(10)

GameObject* explosions[ NUM_EXPLOSIONS ];
int nextExplosion;

void explosionsInit()
{
	//
	//
	//
	int i;
	for( i=0; i<NUM_EXPLOSIONS; i++ )
	{
		GameObject* pb = gameObjectManager.CreateGameObject( &animation_explosion_medium );
		pb->SetWorldPosition( 0, -10 );
		pb->SetHotspot( 5, 4 );
		pb->m_flags = GO_FLAGS_UNIMPORTANT;
		pb->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_UNIMPORTANT;
		pb->SetEnabled( false );
		explosions[ i ] = pb;
	}
	
	nextExplosion = 0;
}


void explosionsUpdate()
{
	int i;
	for( i=0; i<NUM_EXPLOSIONS; i++ )
	{
		GameObject* exp = explosions[ i ];
		if( exp->GetAnimation()->IsPlaying == false )
		{
			exp->SetEnabled( false );
		}
	}
}


void explosionsSpawn( int _worldX, int _worldY, int _explosionType )
{
	GameObject* exp = explosions[ nextExplosion ];
	nextExplosion++;
	if( nextExplosion >= NUM_EXPLOSIONS )
		nextExplosion -= NUM_EXPLOSIONS;
	
	exp->SetEnabled( true );
	switch( _explosionType )
	{
		case EXPLOSION_TYPE_NORMAL:
			exp->GetAnimation()->pSequence = &animation_explosion_medium;
			break;
			
		case EXPLOSION_TYPE_DEBRIS:
			exp->GetAnimation()->pSequence = &animation_explosion_big;
			break;
	}
	exp->SetWorldPosition( _worldX, _worldY );
	exp->GetAnimation()->Reset();
	exp->GetAnimation()->Play();
}
