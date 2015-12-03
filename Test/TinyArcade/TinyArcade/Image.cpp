//
//  Image.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <memory.h>
#include "types.h"
#include "Image.h"
#include "screen.h"

void imageBlitFullScreen( Image* _this, int _scrX, int _scrY )
{
	memcpy( screenBuffer, _this->pixels, SCREEN_HEIGHT * SCREEN_WIDTH * 2 );
}

void imageBlitNoAlpha( Image* _this, int _scrX, int _scrY )
{
	uint16* src = _this->pixels;
	uint16* dst = (uint16*)&screenBuffer[( _scrY * SCREEN_WIDTH) + _scrX ];
	int strideWrite = SCREEN_WIDTH - _this->w;
	int strideRead = 0;

	int h = _this->h;
	int w = _this->w;
	
	int overTheTop = _scrY;
	if( overTheTop < 0 )
	{
		src -= overTheTop * _this->w;
		dst -= overTheTop * SCREEN_WIDTH;
		h += overTheTop;
	}

	int farLeft = _scrX;
	if( farLeft < 0 )
	{
		src -= farLeft;
		dst -= farLeft;
		w += farLeft;
		strideWrite -= farLeft;
		strideRead -= farLeft;
	}
	
	int farRight = (w+_scrX) - SCREEN_WIDTH;
	if( farRight > 0 )
	{
		w -= farRight;
		strideRead += farRight;
		strideWrite += farRight;
	}

	int downTheHole = (h+_scrY) - SCREEN_HEIGHT;
	if( downTheHole > 0 )
		h -= downTheHole;
	
	int x, y;
	for( y=0; y<h; y++ )
	{
		for( x=0; x<w; x++ )
		{
			*dst = *src;
			src++;
			dst++;
		}
		dst += strideWrite;
		src += strideRead;
	}
}

void imageBlitAlpha( Image *_this, int _scrX, int _scrY )
{
	uint16* src = _this->pixels;
	uint16* dst = (uint16*)&screenBuffer[( _scrY * SCREEN_WIDTH) + _scrX ];
	uint8* srcalpha = _this->alpha;
	int strideWrite = SCREEN_WIDTH - _this->w;
	int strideRead = 0;
	
	int h = _this->h;
	int w = _this->w;
	
	int overTheTop = _scrY;
	if( overTheTop < 0 )
	{
		src -= overTheTop * _this->w;
		dst -= overTheTop * SCREEN_WIDTH;
		srcalpha -= overTheTop * _this->w;
		h += overTheTop;
	}
	
	int farLeft = _scrX;
	if( farLeft < 0 )
	{
		src -= farLeft;
		dst -= farLeft;
		srcalpha -= farLeft;
		w += farLeft;
		strideWrite -= farLeft;
		strideRead -= farLeft;
	}
	
	int farRight = (w+_scrX) - SCREEN_WIDTH;
	if( farRight > 0 )
	{
		w -= farRight;
		strideRead += farRight;
		strideWrite += farRight;
	}
	
	int downTheHole = (h+_scrY) - SCREEN_HEIGHT;
	if( downTheHole > 0 )
		h -= downTheHole;
	
	int x, y;
	for( y=0; y<h; y++ )
	{
		for( x=0; x<w; x++ )
		{
			uint32 srca = *srcalpha;
			if( srca == 0 )
			{
				// Do nothing
			} else if( srca == 255 )
			{
				// Use full src color
				*dst = *src;
			} else
			{
				// Blend
				uint16 srccol = *src;
				uint32 srcr = (srccol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 srcg = (srccol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 srcb = (srccol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				uint32 dsta = 255-srca;
				uint16 dstcol = *dst;
				uint32 dstr = (dstcol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 dstg = (dstcol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 dstb = (dstcol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				// Multiply
				uint32 outr = (((srcr*srca)+(dstr*dsta)) >> 8) & COLORWIDTH_16_R;
				uint32 outg = (((srcg*srca)+(dstg*dsta)) >> 8) & COLORWIDTH_16_G;
				uint32 outb = (((srcb*srca)+(dstb*dsta)) >> 8) & COLORWIDTH_16_B;
				
				/*
				// Additive
				uint32 outr = ((srcr*srca)+(dstr<<8)) >> 8;
				uint32 outg = ((srcg*srca)+(dstg<<8)) >> 8;
				uint32 outb = ((srcb*srca)+(dstb<<8)) >> 8;
				if( outr > COLORWIDTH_16_R ) outr = COLORWIDTH_16_R;
				if( outg > COLORWIDTH_16_G ) outg = COLORWIDTH_16_G;
				if( outb > COLORWIDTH_16_B ) outb = COLORWIDTH_16_B;
				 */
				
				uint16 out = (outr<<COLORSHIFT_16_R) + (outg<<COLORSHIFT_16_G) + (outb<<COLORSHIFT_16_B);
				
				*dst = out;
			}
			
			src++;
			dst++;
			srcalpha++;
		}
		dst += strideWrite;
		src += strideRead;
		srcalpha += strideRead;
	}
}

void Image::Draw( int _screenX, int _screenY )
{
	blitFunc( this, _screenX, _screenY );
}
