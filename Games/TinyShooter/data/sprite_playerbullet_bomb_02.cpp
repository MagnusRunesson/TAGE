#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_playerbullet_bomb_02_pixels[] =
{
	0xe5ec,0xe5ec,
	0xe5ec,0xe5ec,
};

extern "C" const Image sprite_playerbullet_bomb_02;
const Image sprite_playerbullet_bomb_02 =
{
	2,2,
	(uint16*)&sprite_playerbullet_bomb_02_pixels,
	(uint8*)0,
	(uint8*)"sprite_playerbullet_bomb_02",
};
