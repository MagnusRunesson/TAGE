//
//  Image.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include "Types.h"

class Image
{
public:
	uint16 w;
	uint16 h;
	uint16* pixels;
	uint8* alpha;
	uint8* DEBUG_name;

	void CopyToScreen();
	void Draw( int _screenX, int _screenY );
	void DrawAlpha( int _screenX, int _screenY );
	void DrawRotated( int _scrX, int _scrY, int _angle, int _scale );
	void DrawRotatedAlpha( int _scrX, int _scrY, int _angle, int _scale );
	void DrawQRotateFlipAlpha( int _screenX, int _screenY, bool _flipX, bool _flipY, int _qrot );
};

void imageBlitFullScreen( Image* _this, int _scrX, int _scrY );
void imageBlitNoAlpha( Image* _this, int _scrX, int _scrY );
void imageBlitAlpha( Image *_this, int _scrX, int _scrY );
void imageBlitRotateNoAlpha( Image *_this, int _scrX, int _angle, int _scale );
void imageBlitRotateAlpha( Image *_this, int _scrX, int _angle, int _scale );
void imageBlitQRotateFlipAlpha( Image *_this, int _scrX, int _scrY, bool _flipX, bool _flipY, int _rotate );

#endif /* Image_hpp */
