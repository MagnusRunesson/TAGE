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

void sbbSpawn()
{
	pfnIngameCallback = &sbbUpdate;
	sbbDoor[ 0 ] = gameObjectManager.CreateGameObject( &sprite_spacebase_boss_door );
	sbbDoor[ 1 ] = gameObjectManager.CreateGameObject( &sprite_spacebase_boss_door );
	sbbDoor[ 2 ] = gameObjectManager.CreateGameObject( &sprite_spacebase_boss_door );
	sbbDoor[ 0 ]->SetWorldPosition( 944, 4 );
	sbbDoor[ 1 ]->SetWorldPosition( 940, 28 );
	sbbDoor[ 2 ]->SetWorldPosition( 940, 52 );

	sbbWarningLights[ 0 ] = gameObjectManager.CreateGameObject( &animation_spacebase_boss_warninglights_blink );
	sbbWarningLights[ 1 ] = gameObjectManager.CreateGameObject( &animation_spacebase_boss_warninglights_idle );
	sbbWarningLights[ 2 ] = gameObjectManager.CreateGameObject( &animation_spacebase_boss_warninglights_idle );
	sbbWarningLights[ 0 ]->SetWorldPosition( 949, 4 );
	sbbWarningLights[ 1 ]->SetWorldPosition( 945, 28 );
	sbbWarningLights[ 2 ]->SetWorldPosition( 9459, 52 );
	sbbWarningLights[ 0 ]->GetAnimation()->Play();
	
	sbbTimer = 0;
}

void sbbUpdate()
{
	//sbbTimer++;
	//sbbDoor[ 0 ]->SetWorldPosition( 944-(sbbTimer&1), 4 );
}
