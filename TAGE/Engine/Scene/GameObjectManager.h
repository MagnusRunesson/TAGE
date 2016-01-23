//
//  GameObjectManager.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-27.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include "Types.h"
#include "GameObject.h"

class Animation;

#define MAX_GAMEOBJECTS (64)

class GameObjectManager
{
public:
	void Reboot();

	GameObject* CreateGameObject( const Image* _image );
	GameObject* CreateGameObject( const AnimationSequenceDefinition* _animationSequenceDefinition );
	void FreeGameObject( GameObject* _gameObjectInstance );
	
	void Update();
	void Render();
	
	GameObject m_gameObjects[ MAX_GAMEOBJECTS ];
};

extern GameObjectManager gameObjectManager;

#endif /* GameObjectManager_hpp */
