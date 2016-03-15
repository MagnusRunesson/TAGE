//
//  spacebase_boss.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-03-14.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/Animation.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/spacebase_boss.h"
#include "data/alldata.h"

GameObject* sbbDoor[ 3 ];
GameObject* sbbWarningLights[ 3 ];
int sbbTimer;

GameObject* sbbCreateDoor( int _x, int _y )
{
	GameObject* pRet = gameObjectManager.CreateGameObject( &sprite_spacebase_boss_door );
	pRet->SetWorldPosition( _x, _y );
	return pRet;
}

GameObject* sbbCreateWarningLights( int _x, int _y )
{
	GameObject* pRet = gameObjectManager.CreateGameObject( &animation_spacebase_boss_warninglights_idle );
	pRet->SetWorldPosition( _x, _y );
	return pRet;
}

void sbbSpawn()
{
	pfnIngameCallback = &sbbUpdate;
	sbbDoor[ 0 ] = sbbCreateDoor( 944, 3 );
	sbbDoor[ 1 ] = sbbCreateDoor( 940, 27 );
	sbbDoor[ 2 ] = sbbCreateDoor( 940, 51 );

	sbbWarningLights[ 0 ] = sbbCreateWarningLights( 949, 4 );
	sbbWarningLights[ 1 ] = sbbCreateWarningLights( 945, 28 );
	sbbWarningLights[ 2 ] = sbbCreateWarningLights( 945, 52 );
	
	sbbTimer = 0;
}

void sbbUpdate()
{
	//sbbTimer++;
	//sbbDoor[ 0 ]->SetWorldPosition( 944-(sbbTimer&1), 4 );
}
