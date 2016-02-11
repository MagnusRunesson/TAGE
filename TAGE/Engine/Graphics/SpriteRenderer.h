//
//  SpriteRenderer.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-26.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef SpriteRenderer_hpp
#define SpriteRenderer_hpp

#include "Engine/Types.h"
#include "Engine/Graphics/Sprite.h"

class Image;

#define MAX_SPRITES (64)

class SpriteRenderer
{
public:
	Sprite* m_scanlineSprites[ MAX_SPRITES+1 ];		// This list is NULL terminated, so we need to have room for a trailing NULL in case all sprites should be in this list
	Sprite* m_potentialSprites[ MAX_SPRITES+1 ];	// And so is this
	
	Sprite m_sprite[ MAX_SPRITES ];
	Sprite* m_collisionSprites[ 8 ];

	uint8 m_currentScanline;
	
	SpriteRenderer();
	void Reboot();
	void debugPrintStats();
	
	Sprite* AllocateSprite( const Image* _image );
	void FreeSprite( Sprite* _spriteInstance );

	//
	void FrameStart();
	void NextScanline( bool _debugPrint = false );
	bool RenderPixel( int _x, uint16* _pOutPixel, uint8* _pOutCollisionMask );
	bool HejFest( int _x, uint16* _pOutPixel, uint8* _pOutCollisionMask );
	bool ReturnFalse();
	void RenderScanline( uint16* _targetBuffer );
};

extern SpriteRenderer spriteRenderer;

#endif /* SpriteRenderer_hpp */
