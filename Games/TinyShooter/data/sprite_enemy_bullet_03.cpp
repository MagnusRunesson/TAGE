#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_bullet_03_pixels[] =
{
	0xffff,
};

extern "C" const Image sprite_enemy_bullet_03;
const Image sprite_enemy_bullet_03 =
{
	1,1,
	(uint16*)&sprite_enemy_bullet_03_pixels,
	(uint8*)0,
	(uint8*)"sprite_enemy_bullet_03",
};
