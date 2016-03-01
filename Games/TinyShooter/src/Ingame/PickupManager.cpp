//
//  PickupManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 02/02/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/Animation.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioMixer.h"
#include "src/Ingame/PickupManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/Player.h"
#include "data/alldata.h"

GameObject* pickupGO;
AudioSource* sfxPlayerPickup;
int currentPickupType;

void pickupInit()
{
	// Setup game object
	pickupGO = gameObjectManager.CreateGameObject( &animation_pickup_pew );
	pickupGO->SetEnabled( false );
	pickupGO->GetAnimation()->Play();
	pickupGO->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PICKUP;
	
	// Setup sound effect
	sfxPlayerPickup = audioMixer.GetChannel( 1 );
	sfxPlayerPickup->SetData( &sfx_player_pickup );
}

void pickupSpawn( int _type, int _worldX, int _worldY )
{
	currentPickupType = _type;
	
	if( _type == PICKUP_TYPE_DOUBLEPEW )
		pickupGO->GetAnimation()->SetSequence( &animation_pickup_pew );
	else if( _type == PICKUP_TYPE_BOMB )
		pickupGO->GetAnimation()->SetSequence( &animation_pickup_bomb );
	else if( _type == PICKUP_TYPE_LASER )
		pickupGO->GetAnimation()->SetSequence( &animation_pickup_laser );
	
	pickupGO->SetEnabled( true );
	pickupGO->SetWorldPosition( _worldX, _worldY );
}

// Call when the player collide with the pickup
void pickupTake( GameObject* _pickupGO )
{
	// There is only one pickup game object for now, so let's just deactivate that one
	pickupGO->SetEnabled( false );
	sfxPlayerPickup->PlayFromBeginning();
	playerPickup( currentPickupType );
}
