#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_bomb_00_pixels[] =
{
	0xffff,0xffff,
	0xffff,0xffff,
};

extern "C" const Image sprite_playerbullet_bomb_00;
const Image sprite_playerbullet_bomb_00 =
{
	2,2,
	(uint16*)&sprite_playerbullet_bomb_00_pixels,
	(uint8*)0,
	(uint8*)"sprite_playerbullet_bomb_00",
};
