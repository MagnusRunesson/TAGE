//
//  GameObjectManager.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-27.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "GameObjectManager.h"

GameObjectManager gameObjectManager;

void GameObjectManager::Reboot()
{
	// Do a full reset of the game object manager. This means to throw out all known game objects, for example
	
	int i;
	for( i=0; i<MAX_GAMEOBJECTS; i++ )
	{
		GameObject* gameObject = &m_gameObjects[ i ];
		gameObject->Reboot();
	}
}

GameObject* GameObjectManager::CreateGameObject( const Image* _image )
{
	int i;
	for( i=0; i<MAX_GAMEOBJECTS; i++ )
	{
		GameObject* gameObject = &m_gameObjects[ i ];
		if( gameObject->IsUsed() == false )
		{
			gameObject->Create( _image );
			return gameObject;
		}
	}
	
	printf( "No free game objects!\n" );
	return NULL;
}

GameObject* GameObjectManager::CreateGameObject( const AnimationSequenceDefinition* _animationSequenceDefinition )
{
	int i;
	for( i=0; i<MAX_GAMEOBJECTS; i++ )
	{
		GameObject* gameObject = &m_gameObjects[ i ];
		if( gameObject->IsUsed() == false )
		{
			gameObject->Create( _animationSequenceDefinition );
			return gameObject;
		}
	}
	
	printf( "No free game objects!\n" );
	return NULL;
}

void GameObjectManager::FreeGameObject( GameObject* _gameObjectInstance )
{
	_gameObjectInstance->Destroy();
}

void GameObjectManager::Update()
{
	int i;
	for( i=0; i<MAX_GAMEOBJECTS; i++ )
	{
		GameObject* go = &m_gameObjects[ i ];
		if( go->GetSprite() != NULL )
		{
			go->Update();
		}
	}
}

void GameObjectManager::Render()
{
	int i;
	for( i=0; i<MAX_GAMEOBJECTS; i++ )
	{
		GameObject* go = &m_gameObjects[ i ];
		if( go->GetSprite() != NULL )
		{
			go->Render();
		}
	}
}