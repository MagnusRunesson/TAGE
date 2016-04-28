#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_hud_weapon_bomb_pixels[] =
{
	0x8250,0x05d1,0x8250,
	0xe3f4,0xffff,0xe3f4,
	0x8250,0x05d1,0x8250,
};

const uint8 sprite_hud_weapon_bomb_alpha[] =
{
	0xff,0xff,0xff,
	0xff,0xff,0xff,
	0xff,0xff,0xff,
};

extern "C" const Image sprite_hud_weapon_bomb;
const Image sprite_hud_weapon_bomb =
{
	3,3,
	(uint16*)&sprite_hud_weapon_bomb_pixels,
	(uint8*)&sprite_hud_weapon_bomb_alpha,
	(uint8*)"sprite_hud_weapon_bomb",
};
