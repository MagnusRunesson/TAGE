//
//  Image.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <stdio.h>

class Image
{
public:
	unsigned short w;
	unsigned short h;
	unsigned short* pixels;
	unsigned char* alpha;
	void(*blitFunc)( Image* image, int _scrX, int _scrY );

	void Draw( int _screenX, int _screenY );
};

void imageBlitFullScreen( Image* _this, int _scrX, int _scrY );
void imageBlitNoAlpha( Image* _this, int _scrX, int _scrY );
void imageBlitAlpha( Image *_this, int _scrX, int _scrY );

#endif /* Image_hpp */
