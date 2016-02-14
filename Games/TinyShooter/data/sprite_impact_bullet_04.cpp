#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_impact_bullet_04_pixels[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,
	0x8250,0x0000,0x0000,0x0000,0x8250,
	0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x8250,0x0000,0x0000,0x8250,
};

const uint8 sprite_impact_bullet_04_alpha[] =
{
	0x00,0x00,0x00,0x00,0x00,
	0xff,0x00,0x00,0x00,0xff,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,
	0x00,0xff,0x00,0x00,0xff,
};

extern "C" const Image sprite_impact_bullet_04;
const Image sprite_impact_bullet_04 =
{
	5,8,
	(uint16*)&sprite_impact_bullet_04_pixels,
	(uint8*)&sprite_impact_bullet_04_alpha,
	(uint8*)"sprite_impact_bullet_04",
};
