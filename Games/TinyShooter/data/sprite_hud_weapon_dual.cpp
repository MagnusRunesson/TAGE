#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_hud_weapon_dual_pixels[] =
{
	0x0000,0xe490,0x26f6,0xffff,
	0x0000,0x0000,0x0000,0x0000,
	0xe490,0x26f6,0xffff,0x0000,
};

const uint8 sprite_hud_weapon_dual_alpha[] =
{
	0x00,0xff,0xff,0xff,
	0x00,0x00,0x00,0x00,
	0xff,0xff,0xff,0x00,
};

extern "C" const Image sprite_hud_weapon_dual;
const Image sprite_hud_weapon_dual =
{
	4,3,
	(uint16*)&sprite_hud_weapon_dual_pixels,
	(uint8*)&sprite_hud_weapon_dual_alpha,
	(uint8*)"sprite_hud_weapon_dual",
};
