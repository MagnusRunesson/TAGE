//
//  BulletManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioMixer.h"
#include "Engine/Math/fp2d.h"
#include "Engine/Graphics/Screen.h"
#include "Engine/Debug.h"
#include "src/Ingame/BulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "data/alldata.h"

#define NUM_PLAYER_BULLETS	(14)

PlayerBullet playerBullets[ NUM_PLAYER_BULLETS ];
int nextPlayerBullet;
int pbMapScroll;
AudioSource* sfxPlayerFire;

void playerBulletsInit()
{
	//
	int i;
	for( i=0; i<NUM_PLAYER_BULLETS; i++ )
	{
		GameObject* pb = gameObjectManager.CreateGameObject( &animation_playerbullet_bomb );
		pb->SetWorldPosition( 0, -1 );
		pb->m_flags = GO_FLAGS_PLAYERBULLET;
		pb->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PLAYERBULLET;
		playerBullets[ i ].pGameObject = pb;
	}
	nextPlayerBullet = 0;

	// Setup sound effect for player bullets
	sfxPlayerFire = audioMixer.GetChannel( 0 );
	sfxPlayerFire->SetData( &sfx_player_fire_canon );
}

void playerBulletUpdate_pew( void* );
void playerBulletUpdate_bomb( void* );
void playerBulletUpdate_bombdebris( void* );

void playerBulletSpawn( int _worldX, int _worldY, int _type )
{
	//
	PlayerBullet* rpb = &playerBullets[ nextPlayerBullet ];
	rpb->type = (uint8)_type;

	GameObject* pb = rpb->pGameObject;
	pb->SetWorldPosition( _worldX, _worldY );
	pb->SetEnabled( true );
	pb->m_customObject = rpb;
	
	Animation* pAnimation;
	
	switch( _type )
	{
		case PLAYERBULLET_TYPE_PEW:
			pb->m_customUpdate = &playerBulletUpdate_pew;
			pb->GetAnimation()->Stop();
			pb->SetImage( &sprite_pb_01 );
			break;

		case PLAYERBULLET_TYPE_BOMB:
			rpb->vec0 = fp2d( _worldX, _worldY );
			rpb->vec1 = fp2d( 1, 0 );
			pb->m_customUpdate = &playerBulletUpdate_bomb;
			pAnimation = pb->GetAnimation();
			pAnimation->pSequence = &animation_playerbullet_bomb;
			pAnimation->Reset();
			pAnimation->Play();
			break;

		case PLAYERBULLET_TYPE_BOMBDEBRIS:
			pb->m_customUpdate = &playerBulletUpdate_bombdebris;
			rpb->timeout = 45;
			pAnimation = pb->GetAnimation();
			pAnimation->pSequence = &animation_explosion_medium;
			pAnimation->Reset();
			pAnimation->Play();
			break;
	}

	// Play sound effect
	sfxPlayerFire->PlayFromBeginning();

	// Go to next bullet instance in a ring buffer of bullets
	nextPlayerBullet++;
	if( nextPlayerBullet >= NUM_PLAYER_BULLETS )
		nextPlayerBullet = 0;
}

void playerBulletsUpdate( int _mapScroll )
{
	pbMapScroll = _mapScroll;
}

void playerBulletUpdate_pew( void* _pPlayerBullet )
{
	PlayerBullet* pPlayerBullet = (PlayerBullet*)_pPlayerBullet;
	GameObject* pGO = pPlayerBullet->pGameObject;

	int x = pGO->GetWorldPositionX()+2;
	if( x >= pbMapScroll+99 )
	{
		pGO->SetEnabled( false );
	}
	else
	{
		pGO->SetWorldPosition( x, pGO->GetWorldPositionY());
	}
}

void playerBulletUpdate_bomb( void* _pPlayerBullet )
{
	FixedPoint DampX = FixedPoint( 0, 2 );
	FixedPoint AccY = FixedPoint( 0, 4 );
	
	PlayerBullet* pPlayerBullet = (PlayerBullet*)_pPlayerBullet;
	GameObject* pGO = pPlayerBullet->pGameObject;

	if( pPlayerBullet->vec1.x > DampX )
		pPlayerBullet->vec1.x -= DampX;
	
	pPlayerBullet->vec1.y = pPlayerBullet->vec1.y + AccY;
	
	pPlayerBullet->vec0 += pPlayerBullet->vec1;
	if( pPlayerBullet->vec0.y > SCREEN_HEIGHT )
	{
		pGO->SetEnabled( false );
	}
	else
	{
		pGO->SetWorldPosition( pPlayerBullet->vec0.x.GetInteger(), pPlayerBullet->vec0.y.GetInteger());
	}
}

void playerBulletUpdate_bombdebris( void* _pPlayerBullet )
{
	PlayerBullet* pBullet = (PlayerBullet*)_pPlayerBullet;
	pBullet->timeout--;
	
	if( pBullet->timeout == 0 )
		pBullet->pGameObject->SetEnabled( false );
}

void playerBulletKill( GameObject* _pb )
{
	//_pb->SetWorldPosition( 0, -1 );
	_pb->SetEnabled( false );

	//
	PlayerBullet* pBullet = (PlayerBullet*)_pb->m_customObject;
	debugLog( "Killing bullet of type %i\n", pBullet->type );
	if( pBullet->type == PLAYERBULLET_TYPE_BOMB )
	{
		playerBulletSpawn( _pb->GetWorldPositionX(), _pb->GetWorldPositionY(), PLAYERBULLET_TYPE_BOMBDEBRIS );
	}
	
}
