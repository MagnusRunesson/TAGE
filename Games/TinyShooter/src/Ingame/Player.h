//
//  Player.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef Player_h
#define Player_h

#define PLAYERWEAPON_NONE		(0)
#define PLAYERWEAPON_PEW		(1)
#define PLAYERWEAPON_BOMB		(2)
#define PLAYERWEAPON_LASER		(3)

void playerReset( int _mapscroll );
void playerInit( int _startX );
void playerDisable();
void playerCameraMove( int _cameraMoveDistance );
void playerUpdate();
void playerUpgrade();
void playerPickup( int _type );
bool playerHit( bool _forceKill );
void playerSetRespawnY( int _y );
int playerGetNumLives();

#endif /* Player_h */
