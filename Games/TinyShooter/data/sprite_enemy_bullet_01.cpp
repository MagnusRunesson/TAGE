#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_bullet_01_pixels[] =
{
	0xfd0d,
};

extern "C" const Image sprite_enemy_bullet_01;
const Image sprite_enemy_bullet_01 =
{
	1,1,
	(uint16*)&sprite_enemy_bullet_01_pixels,
	(uint8*)0,
	(uint8*)"sprite_enemy_bullet_01",
};
