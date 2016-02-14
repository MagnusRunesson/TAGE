#include "Engine/Types.h"
#include "Engine/Graphics/Image.h"

const uint16 sprite_pb_01_pixels[] =
{
	0xe490,0x26f6,0xffff,
};

const uint8 sprite_pb_01_alpha[] =
{
	0xff,0xff,0xff,
};

extern "C" const Image sprite_pb_01;
const Image sprite_pb_01 =
{
	3,1,
	(uint16*)&sprite_pb_01_pixels,
	(uint8*)&sprite_pb_01_alpha,
	(uint8*)"sprite_pb_01",
};
