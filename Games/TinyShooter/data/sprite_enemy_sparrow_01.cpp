#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_sparrow_01_pixels[] =
{
	0x0000,0x0000,0x0000,
	0x23ea,0x3690,0x1c09,
	0x0000,0x0000,0x0000,
};

const uint8 sprite_enemy_sparrow_01_alpha[] =
{
	0x00,0x00,0x00,
	0xff,0xff,0xff,
	0x00,0x00,0x00,
};

extern "C" const Image sprite_enemy_sparrow_01;
const Image sprite_enemy_sparrow_01 =
{
	3,3,
	(uint16*)&sprite_enemy_sparrow_01_pixels,
	(uint8*)&sprite_enemy_sparrow_01_alpha,
	(uint8*)"sprite_enemy_sparrow_01",
};
