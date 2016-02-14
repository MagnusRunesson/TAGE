#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_turret_02_pixels[] =
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xdbd6,
	0x0000,0x0000,0xdbd6,0xdbd6,0xae6b,0xdbd6,0x0000,
	0x0000,0xdbd6,0xdbd6,0xdbd6,0xdbd6,0xae6b,0x0000,
	0x0000,0xdbd6,0xdbd6,0xdbd6,0xdbd6,0xdbd6,0x0000,
};

const uint8 sprite_enemy_turret_02_alpha[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0xff,
	0x00,0x00,0xff,0xff,0xff,0xff,0x00,
	0x00,0xff,0xff,0xff,0xff,0xff,0x00,
	0x00,0xff,0xff,0xff,0xff,0xff,0x00,
};

extern "C" const Image sprite_enemy_turret_02;
const Image sprite_enemy_turret_02 =
{
	7,4,
	(uint16*)&sprite_enemy_turret_02_pixels,
	(uint8*)&sprite_enemy_turret_02_alpha,
	(uint8*)"sprite_enemy_turret_02",
};
