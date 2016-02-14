#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_bullet_02_pixels[] =
{
	0x95ff,
};

extern "C" const Image sprite_enemy_bullet_02;
const Image sprite_enemy_bullet_02 =
{
	1,1,
	(uint16*)&sprite_enemy_bullet_02_pixels,
	(uint8*)0,
	(uint8*)"sprite_enemy_bullet_02",
};
