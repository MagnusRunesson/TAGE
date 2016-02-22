#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_bomb_03_pixels[] =
{
	0x26c9,0x26c9,
	0x26c9,0x26c9,
};

extern "C" const Image sprite_playerbullet_bomb_03;
const Image sprite_playerbullet_bomb_03 =
{
	2,2,
	(uint16*)&sprite_playerbullet_bomb_03_pixels,
	(uint8*)0,
	(uint8*)"sprite_playerbullet_bomb_03",
};
