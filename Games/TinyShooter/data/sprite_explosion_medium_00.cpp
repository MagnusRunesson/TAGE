#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_explosion_medium_00_pixels[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0xdef7,0x0000,0x0000,0x0000,0x0000,0xdef7,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x24cb,0xe490,0x24ff,0xe490,0x24cb,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0xe490,0x24ff,0xdef7,0x24ff,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0xe490,0x24ff,0x24cb,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x24cb,0x0000,0x0000,0x24ff,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0xdef7,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

const uint8 sprite_explosion_medium_00_alpha[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xff,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,
	0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
	0x00,0x00,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xff,0x00,0x00,0xff,0x00,0x00,0x00,
	0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

extern "C" const Image sprite_explosion_medium_00;
const Image sprite_explosion_medium_00 =
{
	11,11,
	(uint16*)&sprite_explosion_medium_00_pixels,
	(uint8*)&sprite_explosion_medium_00_alpha,
	(uint8*)"sprite_explosion_medium_00",
};
