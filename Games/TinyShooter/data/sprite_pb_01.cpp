#include "Types.h"
#include "Image.h"

uint16 sprite_pb_01_pixels[] =
{
	0x90e4,0xf626,0xffff,
};

uint8 sprite_pb_01_alpha[] =
{
	0xff,0xff,0xff,
};

Image sprite_pb_01 =
{
	3,1,
	(uint16*)&sprite_pb_01_pixels,
	(uint8*)&sprite_pb_01_alpha,
	(uint8*)"sprite_pb_01",
};
