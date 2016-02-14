#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_bullet_00_pixels[] =
{
	0xc8fa,
};

extern "C" const Image sprite_enemy_bullet_00;
const Image sprite_enemy_bullet_00 =
{
	1,1,
	(uint16*)&sprite_enemy_bullet_00_pixels,
	(uint8*)0,
	(uint8*)"sprite_enemy_bullet_00",
};
