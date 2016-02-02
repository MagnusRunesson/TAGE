//
//  PickupManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 02/02/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioMixer.h"
#include "src/Ingame/PickupManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/Player.h"
#include "data/alldata.h"

GameObject* pickupGO;
AudioSource* sfxPlayerPickup;

void pickupInit()
{
	// Setup game object
	pickupGO = gameObjectManager.CreateGameObject( &animation_pickup );
	pickupGO->SetEnabled( false );
	pickupGO->GetAnimation()->Play();
	pickupGO->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PICKUP;
	
	// Setup sound effect
	sfxPlayerPickup = audioMixer.GetChannel( 1 );
	sfxPlayerPickup->SetData( &sfx_player_pickup );
}

void pickupSpawn( int _type, int _worldX, int _worldY )
{
	pickupGO->SetEnabled( true );
	pickupGO->SetWorldPosition( _worldX, _worldY );
}

// Call when the player collide with the pickup
void pickupTake( GameObject* _pickupGO )
{
	// There is only one pickup game object for now, so let's just deactivate that one
	pickupGO->SetEnabled( false );
	sfxPlayerPickup->PlayFromBeginning();
	playerUpgrade();
}
