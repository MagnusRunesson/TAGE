#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_laser_00_pixels[] =
{
	0x4e31,0xddc5,0xffff,0xddc5,0x4e31,
	0xddc5,0xffff,0xffff,0xffff,0xddc5,
	0xffff,0xffff,0xffff,0xffff,0xffff,
	0xddc5,0xffff,0xffff,0xffff,0xddc5,
	0x4e31,0xddc5,0xffff,0xddc5,0x4e31,
};

extern "C" const Image sprite_playerbullet_laser_00;
const Image sprite_playerbullet_laser_00 =
{
	5,5,
	(uint16*)&sprite_playerbullet_laser_00_pixels,
	(uint8*)0,
	(uint8*)"sprite_playerbullet_laser_00",
};
