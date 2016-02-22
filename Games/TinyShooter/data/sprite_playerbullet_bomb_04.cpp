#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_bomb_04_pixels[] =
{
	0x8250,0x8250,
	0x8250,0x8250,
};

extern "C" const Image sprite_playerbullet_bomb_04;
const Image sprite_playerbullet_bomb_04 =
{
	2,2,
	(uint16*)&sprite_playerbullet_bomb_04_pixels,
	(uint8*)0,
	(uint8*)"sprite_playerbullet_bomb_04",
};
