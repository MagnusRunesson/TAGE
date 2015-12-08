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
#include "fpmath.h"

void imageBlitFullScreen( Image* _this )
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
		
		int downTheHole = SCREEN_HEIGHT-h;
		if( downTheHole < 0 )
			h += downTheHole;
	}
	else
	{
		int downTheHole = (h+_scrY) - SCREEN_HEIGHT;
		if( downTheHole > 0 )
			h -= downTheHole;
	}

	int farLeft = _scrX;
	if( farLeft < 0 )
	{
		src -= farLeft;
		dst -= farLeft;
		w += farLeft;
		strideWrite -= farLeft;
		strideRead -= farLeft;
		
		int farRight = SCREEN_WIDTH-w;
		if( farRight < 0 )
		{
			w += farRight;
			strideRead -= farRight;
			strideWrite -= farRight;
		}
	}
	else
	{
		int farRight = (w+_scrX) - SCREEN_WIDTH;
		if( farRight > 0 )
		{
			w -= farRight;
			strideRead += farRight;
			strideWrite += farRight;
		}
	}
	
	/*                            --> PROPER CLIPPING FOR WHEN THE LEFT OR TOP OF THE IMAGE IS ALSO OFF SCREEN (i.e. big background images) It doesn't work for images smaller than the screen though)
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
	
	int farRight = SCREEN_WIDTH-w;
	if( farRight < 0 )
	{
		w += farRight;
		strideRead -= farRight;
		strideWrite -= farRight;
	}
	
	int downTheHole = SCREEN_HEIGHT-h;
	if( downTheHole < 0 )
		h += downTheHole;
	*/
	
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

inline void calculateShit( int _x, int _y, int _xx, int _xy, int _yx, int _yy, int* _ox, int *_oy )
{
	*_ox = (_xx*_x)+(_xy*_y);
	*_oy = (_yx*_x)+(_yy*_y);
}

// xx = x add for each x moved
// xy = x add for each y moved
// yx = y add for each x moved
// yy = y add for each y moved
void imageBlitRotateNoAlpha( Image* _this, int _scrX, int _scrY, int _a, int _s )
{
	int s = fpsin( _a );
	int c = fpcos( _a );
	int _xx = c;
	int _xy = s;
	int _yx = -s;
	int _yy = c;

	uint16* src = _this->pixels;
	uint16* dst = screenBuffer;
	/*
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
	 */
	

	int xx, xy, yx, yy;
	xx=xy=yx=yy=0;
	
	int iw = _this->w;
	int ih = _this->h;

	int right = 0;
	int bottom = 0;
	//int left =(-(_xx*iw) - (_xy*ih)) >> 9;
	//int left = ((_xy*ih*2) + (_xx*iw)) >> 8;
	//int top = (-(_yx*iw) - (_yy*ih)) >> 9;
	
	int l1 = ((fpsin( 64+_a )*iw) >> 8);
	int l2 = ((fpsin( 128+_a ) * iw) >> 8);
	//int l3 = ((fpcos( )))
	int left = ((fpcos( 192+_a ) * ih) >> 8);
	/*if( left > l2 )
		left = l2;*/
	int top = -24;
	bottom = 8;
	if( left > 0 )
	{
		right = left;
		left = 0;
	}
	if( top > 0 )
	{
		bottom = top;
		top = 0;
	}

	/*
	int borderY = (_this->h>>1);
	int borderX = (_this->w>>1);
	xy = (_xx*-borderX)+(_xy*-borderY);
	yy = (_yx*-borderX)+(_yy*-borderY);
	int l = -borderX;
	int t = -borderY;
	int r = borderX;
	int b = borderY;
	/*/
	xy = (_xx*left)+(_xy*top);
	yy = (_yx*left)+(_yy*top);
	int l = left;
	int t = top;
	int r = right;
	int b = bottom;
	/**/

	
//	int mostleft
	
	int x, y;
	for( y=t; y<_this->h+b; y++ )
	{
		xx = xy;
		yx = yy;
		
		for( x=l; x<_this->w+r; x++ )
		{
			xx += _xx;
			yx += _yx;
			int rdx = xx >> 8;
			int rdy = yx >> 8;

			uint16 srccol = 0xf81f;
			
			/*
			if( rdx < 0 ) continue;
			if( rdy < 0 ) continue;
			if( rdx >= _this->w ) continue;
			if( rdy >= _this->h ) continue;
			 */
			if((rdx >= 0 ) && (rdx < _this->w) && (rdy >= 0) && (rdy < _this->h))
			{
				int rdofs = (rdy*_this->w)+rdx;
				srccol = src[ rdofs ];
			}
			
			int wrx = _scrX+x;
			int wry = _scrY+y;

			if( wrx < 0 ) continue;
			if( wry < 0 ) continue;
			if( wrx >= SCREEN_WIDTH ) continue;
			if( wry >= SCREEN_HEIGHT ) continue;
			
			//int rdofs = (rdy*_this->w)+rdx;
			int wrofs = (wry*SCREEN_WIDTH)+wrx;
			
			dst[ wrofs ] = srccol;
		}
		
		xy += _xy;
		yy += _yy;
	}
}

void Image::CopyToScreen()
{
	imageBlitFullScreen( this );
}

void Image::Draw( int _screenX, int _screenY )
{
	imageBlitNoAlpha( this, _screenX, _screenY );
}

void Image::DrawAlpha( int _screenX, int _screenY )
{
	imageBlitAlpha( this, _screenX, _screenY );
}

void Image::DrawRotated( int _scrX, int _scrY, int _angle, int _scale )
{
	imageBlitRotateNoAlpha( this, _scrX, _scrY, _angle, _scale );
}
