#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_logo_shooter_h_pixels[] =
{
	0xffff,0xffff,0xffff,0xffff,0x0000,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xa4eb,0xa4eb,0xffff,0x0000,0xffff,0xa4f3,0xa4eb,0xffff,
	0xffff,0xa4eb,0xa4eb,0xffff,0x0000,0xffff,0xa4f3,0xa4eb,0xffff,
	0xffff,0xa5eb,0xa4eb,0xffff,0x0000,0xffff,0xa4f3,0xa5eb,0xffff,
	0xffff,0x4df5,0xa5eb,0xffff,0xffff,0xffff,0xa4f3,0x4df5,0xffff,
	0xffff,0x75f6,0x4df5,0x4df5,0x4df5,0x4df5,0x4df5,0x74fe,0xffff,
	0xffff,0x6051,0x95f6,0x74fe,0x74fe,0x74fe,0x74fe,0x6151,0xffff,
	0xffff,0x228a,0x6151,0x6051,0x6051,0x6051,0x6051,0x438a,0xffff,
	0xffff,0x04cb,0x228a,0x228a,0x228a,0x228a,0x228a,0x23cb,0xffff,
	0xffff,0xa4f3,0x24c3,0xffff,0xffff,0xffff,0x24c3,0xa4eb,0xffff,
	0xffff,0xa5eb,0xa4f3,0xffff,0x0000,0xffff,0xa4f3,0xa4eb,0xffff,
	0xffff,0xa4eb,0xa4eb,0xffff,0x0000,0xffff,0xa4f3,0xa4eb,0xffff,
	0xffff,0xa4eb,0xa4eb,0xffff,0x0000,0xffff,0xa4f3,0xa4eb,0xffff,
	0xffff,0xffff,0xffff,0xffff,0x0000,0xffff,0xffff,0xffff,0xffff,
};

const uint8 sprite_logo_shooter_h_alpha[] =
{
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x00,0xff,0xff,0xff,0xff,
};

extern "C" const Image sprite_logo_shooter_h;
const Image sprite_logo_shooter_h =
{
	9,14,
	(uint16*)&sprite_logo_shooter_h_pixels,
	(uint8*)&sprite_logo_shooter_h_alpha,
	(uint8*)"sprite_logo_shooter_h",
};
