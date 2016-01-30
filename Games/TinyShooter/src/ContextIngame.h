//
//  ContextIngame.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-22.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Context_Ingame_h
#define Context_Ingame_h

extern void ingame_setup();
extern void ingame_loop();
extern void ingame_debugTrigger( int _i );

#define FIRE_RATE_DELAY (7)

#define GO_FLAGS_UNIMPORTANT	(0)
#define GO_FLAGS_PLAYERSHIP		(1)
#define GO_FLAGS_PLAYERBULLET	(2)
#define GO_FLAGS_ENEMY			(3)

#define SPRITE_COLLISION_INDEX_UNIMPORTANT	(0)
#define SPRITE_COLLISION_INDEX_PLAYERSHIP	(1)
#define SPRITE_COLLISION_INDEX_PLAYERBULLET	(2)
#define SPRITE_COLLISION_INDEX_ENEMY		(3)
#define SPRITE_COLLISION_INDEX_PICKUP		(4)

#define SPRITE_COLLISION_MASK_UNIMPORTANT	(1<<SPRITE_COLLISION_INDEX_UNIMPORTANT)
#define SPRITE_COLLISION_MASK_PLAYERSHIP	(1<<SPRITE_COLLISION_INDEX_PLAYERSHIP)
#define SPRITE_COLLISION_MASK_PLAYERBULLET	(1<<SPRITE_COLLISION_INDEX_PLAYERBULLET)
#define SPRITE_COLLISION_MASK_ENEMY			(1<<SPRITE_COLLISION_INDEX_ENEMY)
#define SPRITE_COLLISION_MASK_PICKUP		(1<<SPRITE_COLLISION_INDEX_PICKUP)


#endif /* TinyRaceCar_hpp */
