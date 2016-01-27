#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_logo_tiny_y_pixels[] =
{
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0x1c74,0x1c94,0x1c94,0x1c74,0xffff,0x1c94,0x1c94,0x1c94,0x2474,0xffff,
	0xffff,0x1d58,0x1c94,0x1c94,0x1d58,0xffff,0x1d58,0x1c94,0x1c94,0x1d58,0xffff,
	0xffff,0x6e7b,0x1d57,0x1d58,0x1d58,0x6e7b,0x1d57,0x1d58,0x1d58,0x6e5b,0xffff,
	0xffff,0xaefd,0x6e7b,0x6e5b,0x6e5b,0xaefd,0x6e7b,0x6e5b,0x6e5b,0xa73c,0xffff,
	0xffff,0xffff,0xa71c,0xa71c,0xa71c,0xa71c,0xa71c,0xa71c,0xa71c,0x1904,0xffff,
	0x0000,0xffff,0xffff,0xffff,0xffff,0xffff,0x1904,0x1904,0x1904,0x01e9,0xffff,
	0x0000,0xffff,0x01e9,0x1904,0x1904,0x1904,0x01e9,0x01e8,0x01e8,0x132e,0xffff,
	0x0000,0xffff,0x1c94,0x132e,0x132e,0x0b4e,0x134e,0x0b4e,0x0b4e,0x1c95,0xffff,
	0x0000,0xffff,0x2474,0x1c94,0x1c94,0x1c94,0x1c94,0x1c94,0x1c94,0xffff,0xffff,
	0x0000,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x0000,
};

const uint8 sprite_logo_tiny_y_alpha[] =
{
	0x4d,0xff,0xff,0xff,0xff,0x4d,0xff,0xff,0xff,0xff,0x4d,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x4d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0x4d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x4d,
	0x00,0x4d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x4d,0x00,
};

extern "C" const Image sprite_logo_tiny_y;
const Image sprite_logo_tiny_y =
{
	11,11,
	(uint16*)&sprite_logo_tiny_y_pixels,
	(uint8*)&sprite_logo_tiny_y_alpha,
	(uint8*)"sprite_logo_tiny_y",
};
