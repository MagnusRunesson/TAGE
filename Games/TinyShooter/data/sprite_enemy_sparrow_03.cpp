#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_sparrow_03_pixels[] =
{
	0x0000,0x0000,0x0000,
	0x23ea,0x23e9,0x1c09,
	0x0000,0x0000,0x0000,
};

const uint8 sprite_enemy_sparrow_03_alpha[] =
{
	0x00,0x00,0x00,
	0xff,0xff,0xff,
	0x00,0x00,0x00,
};

extern "C" const Image sprite_enemy_sparrow_03;
const Image sprite_enemy_sparrow_03 =
{
	3,3,
	(uint16*)&sprite_enemy_sparrow_03_pixels,
	(uint8*)&sprite_enemy_sparrow_03_alpha,
	(uint8*)"sprite_enemy_sparrow_03",
};
