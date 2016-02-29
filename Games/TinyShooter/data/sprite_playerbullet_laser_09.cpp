#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_laser_09_pixels[] =
{
	0x4e31,0x4e31,0x4e31,0xddc5,0xddc5,0xddc5,0xddc5,0xffff,0xffff,0xffff,0xffff,0xffff,0xddc5,0x4e31,
};

const uint8 sprite_playerbullet_laser_09_alpha[] =
{
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

extern "C" const Image sprite_playerbullet_laser_09;
const Image sprite_playerbullet_laser_09 =
{
	14,1,
	(uint16*)&sprite_playerbullet_laser_09_pixels,
	(uint8*)&sprite_playerbullet_laser_09_alpha,
	(uint8*)"sprite_playerbullet_laser_09",
};
