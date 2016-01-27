#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_logo_shooter_e_pixels[] =
{
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xf3a4,0xeba4,0xeba4,0xeba4,0xeba4,0xffff,
	0xffff,0xf3a4,0xeba4,0xeba4,0xeba4,0xeba4,0xffff,
	0xffff,0xeba5,0xeba4,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xf56c,0xeba4,0xffff,0x0000,0x0000,0x0000,
	0xffff,0xf675,0xf54c,0xffff,0xffff,0xffff,0x0000,
	0xffff,0x5161,0xf675,0xfe74,0x4981,0xffff,0x0000,
	0xffff,0x8a43,0x4981,0x5160,0x9222,0xffff,0x0000,
	0xffff,0x8a43,0x9223,0xffff,0xffff,0xffff,0x0000,
	0xffff,0xc324,0xcb24,0xffff,0x0000,0x0000,0x0000,
	0xffff,0xf3a4,0xf3a4,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xf3a4,0xeba4,0xeba4,0xeba4,0xeba4,0xffff,
	0xffff,0xf3a4,0xeba4,0xeba4,0xeba4,0xeba4,0xffff,
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
};

const uint8 sprite_logo_shooter_e_alpha[] =
{
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0x00,
	0xff,0xff,0xff,0xff,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

extern "C" const Image sprite_logo_shooter_e;
const Image sprite_logo_shooter_e =
{
	7,14,
	(uint16*)&sprite_logo_shooter_e_pixels,
	(uint8*)&sprite_logo_shooter_e_alpha,
	(uint8*)"sprite_logo_shooter_e",
};
