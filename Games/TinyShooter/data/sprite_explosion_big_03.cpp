#include "Types.h"
#include "Image.h"

const uint16 sprite_explosion_big_03_pixels[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xff24,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xca60,0x0000,0xffff,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xff24,0xca60,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0xffff,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xca60,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xff24,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0xffff,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xca60,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xff24,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xffff,0x0000,
};

const uint8 sprite_explosion_big_03_alpha[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0xff,
	0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x00,
	0x00,0x00,0xff,0xff,0x00,0xff,0xff,0x00,0x00,0x00,
	0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
	0xff,0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0xff,0xff,0x00,0x00,0xff,0xff,0x00,0x00,
	0x00,0xff,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0x00,
	0x00,0xff,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,
	0x00,0xff,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,
};

extern "C" const Image sprite_explosion_big_03;
const Image sprite_explosion_big_03 =
{
	10,13,
	(uint16*)&sprite_explosion_big_03_pixels,
	(uint8*)&sprite_explosion_big_03_alpha,
	(uint8*)"sprite_explosion_big_03",
};