#include "draw.h"
#include "lcd.h"

#define CLIP_LEFT (0)
#define CLIP_TOP (0)
#define CLIP_RIGHT (SCREEN_WIDTH-0)
#define CLIP_BOTTOM (SCREEN_HEIGHT-0)

void Cls(unsigned short _color) {
    unsigned int* fb = (unsigned int*)framebuffer;
    unsigned int color = (_color << 16) + _color;
    
    for(int i=0; i<320*240/2; i++) {
        *fb = color;
        fb++;
    }
}

void Rect(int _left, int _top, int _width, int _height, unsigned short _color) {
    int x;
    int y;
    
    int bottom = _top + _height;
    int right = _left + _width;
	
	// Draw sides
	unsigned short* pScreenTop = framebuffer + (_top*SCREEN_WIDTH) + _left;
	unsigned short* pScreenBottom = framebuffer + (bottom*SCREEN_WIDTH) + _left;

    int shouldDrawTop = ((_top >= CLIP_TOP) && (_top < CLIP_BOTTOM));
	int shouldDrawBottom = ((bottom >= CLIP_TOP) && (bottom < CLIP_BOTTOM));

	int clippedLeft = _left;
	int clippedRight = right;
	
	// Clip left
	if(clippedLeft < CLIP_LEFT) {
		pScreenTop += CLIP_LEFT - clippedLeft;
		pScreenBottom += CLIP_LEFT - clippedLeft;
		clippedLeft = CLIP_LEFT;
	}

	// Clip right
	if(clippedRight >= CLIP_RIGHT) {
		clippedRight = CLIP_RIGHT;
	}
	
	if(shouldDrawTop && shouldDrawBottom) {
		for(x=clippedLeft; x<clippedRight; x++) {
			*pScreenTop = _color;
			pScreenTop++;
			*pScreenBottom = _color;
			pScreenBottom++;
		}
	} else if(shouldDrawTop) {
		for(x=clippedLeft; x<clippedRight; x++) {
			*pScreenTop = _color;
			pScreenTop++;
		}
	} else if(shouldDrawBottom) {
		for(x=clippedLeft; x<clippedRight; x++) {
			*pScreenBottom = _color;
			pScreenBottom++;
		}
	}

	// Draw sides
	unsigned short* pScreenLeft = framebuffer + (_top*SCREEN_WIDTH) + _left;
	unsigned short* pScreenRight = framebuffer + (_top*SCREEN_WIDTH) + right;
	
	int shouldDrawLeft = ((_left >= CLIP_LEFT) && (_left < CLIP_RIGHT));
	int shouldDrawRight = ((right >= CLIP_LEFT) && (right < CLIP_RIGHT));
	
	int clippedTop = _top;
	int clippedBottom = bottom;
	
	// Clip top
	if(clippedTop < CLIP_TOP) {
		pScreenLeft += (CLIP_TOP - clippedTop) * SCREEN_WIDTH;
		pScreenRight += (CLIP_TOP - clippedTop) * SCREEN_WIDTH;
		clippedTop = CLIP_TOP;
	}
	
	// Clip bottom
	if(clippedBottom >= CLIP_BOTTOM) {
		clippedBottom = CLIP_BOTTOM;
	}
	
	if(shouldDrawLeft && shouldDrawRight) {
		for(y=clippedTop; y<clippedBottom; y++) {
			*pScreenLeft = _color;
			pScreenLeft+=SCREEN_WIDTH;
			*pScreenRight = _color;
			pScreenRight+=SCREEN_WIDTH;
		}
	} else if(shouldDrawLeft) {
		for(y=clippedTop; y<clippedBottom; y++) {
			*pScreenLeft = _color;
			pScreenLeft+=SCREEN_WIDTH;
		}
	} else if(shouldDrawRight) {
		for(y=clippedTop; y<clippedBottom; y++) {
			*pScreenRight = _color;
			pScreenRight+=SCREEN_WIDTH;
		}
	}
}
