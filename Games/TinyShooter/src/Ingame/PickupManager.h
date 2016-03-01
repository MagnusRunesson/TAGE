//
//  PickupManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 02/02/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef PickupManager_h
#define PickupManager_h

#define PICKUP_TYPE_DOUBLEPEW		(0)
#define PICKUP_TYPE_BOMB			(1)
#define PICKUP_TYPE_LASER			(2)

void pickupInit();
void pickupSpawn( int _type, int _worldX, int _worldY );
void pickupTake( GameObject* _pickupGO );

#endif /* PickupManager_h */
