#include "Types.h"
#include "Image.h"

uint16 tinyracecar_50_pixels[] =
{
	0x0000,0x0000,0x0000,0x0000,0xf986,0xf965,0x0000,
	0x0000,0x0000,0x0000,0x1820,0xc125,0xf9a6,0x0000,
	0x0000,0xf924,0xf986,0x70e3,0x1000,0xb124,0x0000,
	0x0000,0xf966,0xf986,0xf9a6,0x78e3,0x80c3,0x0000,
	0x0000,0xf966,0xf966,0xf986,0xb104,0x0000,0x0000,
	0x0000,0xf924,0xf966,0xf965,0x0000,0x0000,0x0000,
	0x0000,0x0000,0xf946,0x0000,0x0000,0x0000,0x0000,
};

uint8 tinyracecar_50_alpha[] =
{
	0x00,0x00,0x00,0x00,0x74,0x0b,0x00,
	0x00,0x00,0x00,0x96,0xff,0x75,0x00,
	0x00,0x0d,0xb9,0xff,0xff,0xfc,0x00,
	0x00,0xeb,0xff,0xff,0xff,0xa9,0x00,
	0x00,0x9e,0xf6,0xff,0x79,0x00,0x00,
	0x00,0x0d,0xb9,0x58,0x00,0x00,0x00,
	0x00,0x00,0x25,0x00,0x00,0x00,0x00,
};

Image tinyracecar_50 =
{
	7,7,
	(uint16*)&tinyracecar_50_pixels,
	(uint8*)&tinyracecar_50_alpha,
	(uint8*)"tinyracecar_50",
};