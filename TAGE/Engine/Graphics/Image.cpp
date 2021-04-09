//
//  Image.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"
#include "Engine/Graphics/Screen.h"
#include "Engine/Math/fpmath.h"

#if 0

void imageBlitFullScreen( Image* _this )
{
	memcpy( screenBuffer, _this->pixels, SCREEN_HEIGHT * SCREEN_WIDTH * 2 );
}

bool clip( int _scrX, int _scrY, int _w, int _h, int* _cutLeft, int* _cutTop, int* _newW, int* _newH )
{
	bool doClip = false;
	
	*_cutLeft = 0;
	*_cutTop = 0;
	*_newW = _w;
	*_newH = _h;
	
	int overTheTop = _scrY;
	if( overTheTop < 0 )
	{
		//
		doClip = true;
		
		//
		*_cutTop = -overTheTop;
		*_newH += overTheTop;
		
		int downTheHole = SCREEN_HEIGHT-*_newH;
		if( downTheHole < 0 )
			*_newH += downTheHole;
	}
	else
	{
		int downTheHole = (_h+_scrY) - SCREEN_HEIGHT;
		if( downTheHole > 0 )
		{
			doClip = true;
			*_newH -= downTheHole;
		}
	}
	
	int farLeft = _scrX;
	if( farLeft < 0 )
	{
		doClip = true;
		
		*_cutLeft = -farLeft;
		*_newW += farLeft;
		
		int farRight = SCREEN_WIDTH-*_newW;
		if( farRight < 0 )
			*_newW += farRight;
	}
	else
	{
		int farRight = (_w+_scrX) - SCREEN_WIDTH;
		if( farRight > 0 )
		{
			doClip = true;
			
			*_newW -= farRight;
		}
	}
	
	return doClip;
}

void imageBlitNoAlpha( Image* _this, int _scrX, int _scrY )
{
	uint16* src = _this->pixels;
	uint16* dst = (uint16*)&screenBuffer[( _scrY * SCREEN_WIDTH) + _scrX ];
	int strideWrite = SCREEN_WIDTH - _this->w;
	int strideRead = 0;

	int h = _this->h;
	int w = _this->w;
	
	int cutLeft, cutTop;
	int newW, newH;
	if( clip( _scrX, _scrY, w, h, &cutLeft, &cutTop, &newW, &newH ))
	{
		src += (cutTop*_this->w)+cutLeft;
		dst += (cutTop*SCREEN_WIDTH)+cutLeft;
		
		int cutWidth = w-newW;
		
		strideRead += cutWidth;
		strideWrite += cutWidth;
		
		w = newW;
		h = newH;
	}
	
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

	int cutLeft, cutTop;
	int newW, newH;
	if( clip( _scrX, _scrY, w, h, &cutLeft, &cutTop, &newW, &newH ))
	{
		src += (cutTop*_this->w)+cutLeft;
		dst += (cutTop*SCREEN_WIDTH)+cutLeft;
		
		int cutWidth = w-newW;
		
		strideRead += cutWidth;
		strideWrite += cutWidth;
		
		w = newW;
		h = newH;
	}
	
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

#define SWAP( x, y ) {int t = x; x=y; y=t; }

void imageBlitQRotateFlipAlpha( Image *_this, int _scrX, int _scrY, bool _flipX, bool _flipY, int _rotate )
{
	uint16* src = _this->pixels;
	uint16* dst = (uint16*)screenBuffer;
	uint8* srcalpha = _this->alpha;
	
	_rotate &= 3;
	
	int ryx = 0;
	int ryy = 0;
	int strideReadXX = 1;
	int strideReadXY = 0;
	int strideReadYX = 0;
	int strideReadYY = 1;

	switch( _rotate )
	{
		case 1:
			ryx = 0;
			ryy = _this->h-1;
			strideReadXX = 0;
			strideReadXY = 1;
			strideReadYX = -1;
			strideReadYY = 0;
			break;

		case 2:
			ryx = _this->w-1;
			ryy = _this->h-1;
			strideReadXX = -1;
			strideReadXY = 0;
			strideReadYX = 0;
			strideReadYY = -1;
			break;
			
		case 3:
			ryx = _this->w-1;
			ryy = 0;
			strideReadXX = 0;
			strideReadXY = -1;
			strideReadYX = 1;
			strideReadYY = 0;
			break;
	}
	
	int h = _this->h;
	int w = _this->w;
	
	int x, y;
	for( y=0; y<h; y++ )
	{
		int rxx = ryx;
		int rxy = ryy;
		
		for( x=0; x<w; x++ )
		{
			int wrx = _scrX+x;
			int wry = _scrY+y;
			if( wrx <= 0 ) continue;
			if( wrx > SCREEN_WIDTH ) continue;
			if( wry <= 0 ) continue;
			if( wry > SCREEN_HEIGHT ) continue;

			rxx += strideReadXX;
			rxy += strideReadYX;
			
			int rdofs = (rxy*w)+rxx;
			int wrofs = (wry*SCREEN_WIDTH)+wrx;

			uint32 srca = srcalpha[ rdofs ];
			if( srca == 0 )
			{
				// Do nothing
			} else if( srca == 255 )
			{
				// Use full src color
				dst[ wrofs ] = src[ rdofs ];
			} else
			{
				// Blend
				uint16 srccol = src[ rdofs ];
				uint32 srcr = (srccol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 srcg = (srccol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 srcb = (srccol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				uint32 dsta = 255-srca;
				uint16 dstcol = dst[ wrofs ];
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
				
				dst[ wrofs ] = out;
			}
		}
		
		ryx += strideReadXY;
		ryy += strideReadYY;
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
	int _xx = (c * _s)>>8;
	int _xy = (s * _s)>>8;
	int _yx = (-s * _s)>>8;
	int _yy = (c * _s)>>8;

	uint16* src = _this->pixels;
	uint16* dst = screenBuffer;

	int xx, xy, yx, yy;
	xx=xy=yx=yy=0;
	
	int iw = _this->w;
	int ih = _this->h;
	int hiw = iw>>1;
	int hih = ih>>1;

	int bx = (iw << 8) / _s;
	int by = (ih << 8) / _s;
	int border = (bx>by)?bx:by;

	int left = -border;
	int top = - border;
	int right = border;
	int bottom = border;
	
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
	xy = (_xx*left)+(_xy*top) + (hiw<<8);
	yy = (_yx*left)+(_yy*top) + (hih<<8);
	int l = left;
	int t = top;
	int r = right;
	int b = bottom;
	/**/

	
//	int mostleft
	
	int x, y;
	for( y=t; y<b; y++ )
	{
		xx = xy;
		yx = yy;
		
		for( x=l; x<r; x++ )
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

void imageBlitRotateAlpha( Image* _this, int _scrX, int _scrY, int _a, int _s )
{
	int s = fpsin( _a );
	int c = fpcos( _a );
	int _xx = (c * _s)>>8;
	int _xy = (s * _s)>>8;
	int _yx = (-s * _s)>>8;
	int _yy = (c * _s)>>8;
	
	uint16* src = _this->pixels;
	uint8* srcAlpha = _this->alpha;
	uint16* dst = screenBuffer;
	
	int xx, xy, yx, yy;
	xx=xy=yx=yy=0;
	
	int iw = _this->w;
	int ih = _this->h;
	int hiw = iw>>1;
	int hih = ih>>1;
	
	int bx = (iw << 8) / _s;
	int by = (ih << 8) / _s;
	int border = (bx>by)?bx:by;
	
	int left = -border;
	int top = - border;
	int right = border;
	int bottom = border;
	
	xy = (_xx*left)+(_xy*top) + (hiw<<8);
	yy = (_yx*left)+(_yy*top) + (hih<<8);
	int l = left;
	int t = top;
	int r = right;
	int b = bottom;
	
	int x, y;
	for( y=t; y<b; y++ )
	{
		xx = xy;
		yx = yy;
		
		for( x=l; x<r; x++ )
		{
			xx += _xx;
			yx += _yx;
			int rdx = xx >> 8;
			int rdy = yx >> 8;
			
			if( rdx < 0 ) continue;
			if( rdy < 0 ) continue;
			if( rdx >= _this->w ) continue;
			if( rdy >= _this->h ) continue;
			
			int wrx = _scrX+x;
			int wry = _scrY+y;
			
			if( wrx < 0 ) continue;
			if( wry < 0 ) continue;
			if( wrx >= SCREEN_WIDTH ) continue;
			if( wry >= SCREEN_HEIGHT ) continue;
			
			int rdofs = (rdy*_this->w)+rdx;
			int wrofs = (wry*SCREEN_WIDTH)+wrx;
			
			uint32 srca = srcAlpha[ rdofs ];
			if( srca == 0 )
			{
				// Do nothing
			} else if( srca == 255 )
			{
				// Use full src color
				dst[ wrofs ] = src[ rdofs ];
			} else
			{
				// Blend
				uint16 srccol = src[ rdofs ];
				uint32 srcr = (srccol >> COLORSHIFT_16_R) & COLORWIDTH_16_R;
				uint32 srcg = (srccol >> COLORSHIFT_16_G) & COLORWIDTH_16_G;
				uint32 srcb = (srccol >> COLORSHIFT_16_B) & COLORWIDTH_16_B;
				
				uint32 dsta = 255-srca;
				uint16 dstcol = dst[ wrofs ];
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
				
				dst[ wrofs ] = out;
			}
			
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

void Image::DrawRotatedAlpha( int _scrX, int _scrY, int _angle, int _scale )
{
	imageBlitRotateAlpha( this, _scrX, _scrY, _angle, _scale );
}

void Image::DrawQRotateFlipAlpha( int _screenX, int _screenY, bool _flipX, bool _flipY, int _qrot )
{
	imageBlitQRotateFlipAlpha( this, _screenX, _screenY, _flipX, _flipY, _qrot );
}

#endif
