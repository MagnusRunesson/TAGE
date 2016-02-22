#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_bomb_01_pixels[] =
{
	0xcdf6,0xcdf6,
	0xcdf6,0xcdf6,
};

extern "C" const Image sprite_playerbullet_bomb_01;
const Image sprite_playerbullet_bomb_01 =
{
	2,2,
	(uint16*)&sprite_playerbullet_bomb_01_pixels,
	(uint8*)0,
	(uint8*)"sprite_playerbullet_bomb_01",
};
