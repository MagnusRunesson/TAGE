#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_enemy_spacebase_boss_laser_00_pixels[] =
{
	0x52dc,0x0ac2,0x0000,
	0x0ac2,0xffff,0x0ac2,
	0x52dc,0x0ac2,0x0000,
};

const uint8 sprite_enemy_spacebase_boss_laser_00_alpha[] =
{
	0xff,0xff,0x00,
	0xff,0xff,0xff,
	0xff,0xff,0x00,
};

extern "C" const Image sprite_enemy_spacebase_boss_laser_00;
const Image sprite_enemy_spacebase_boss_laser_00 =
{
	3,3,
	(uint16*)&sprite_enemy_spacebase_boss_laser_00_pixels,
	(uint8*)&sprite_enemy_spacebase_boss_laser_00_alpha,
	(uint8*)"sprite_enemy_spacebase_boss_laser_00",
};
