//
//  GameObjectManager.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-27.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/BitHelpers.h"

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
		if( HasBit( go->m_systemFlags, GO_SYSTEMFLAG_ENABLED ))
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
		if( HasBit( go->m_systemFlags, GO_SYSTEMFLAG_ENABLED ))
		{
			go->Render();
		}
	}
}

const char* stringFromBool( bool _value )
{
	if( _value )
		return "YES";
	
	return "NO";
}

void GameObjectManager::debugPrintStats()
{
	printf( "----------[ GameObjectManager ]----------\n" );
	int numUsed = 0;
	int i;
	for( i=0; i<MAX_GAMEOBJECTS; i++ )
	{
		GameObject* gameObject = &m_gameObjects[ i ];
		printf("Game object %3i - ", i );
		printf("Used: %s", stringFromBool( gameObject->IsUsed()));
		if( gameObject->IsUsed())
		{
			numUsed++;
			printf(" - Enabled: %s", stringFromBool( gameObject->IsEnabled()));
		}
		printf("\n");
	}
	
	printf("Num objects used: %i / %i\n", numUsed, MAX_GAMEOBJECTS );
}
