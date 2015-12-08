#include "Image.h"

unsigned short rotest_pixels[] =
{
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
	0xffff,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0xffe0,0x0000,0x0000,0x0000,0xffe0,0xffe0,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0x0000,0xffe0,0x0000,0x0000,0xffe0,0xffe0,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0xffe0,0x0000,0x0000,0x0000,0xffe0,0xffe0,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0xffe0,0xffe0,0xffe0,0x0000,0x0000,0x0000,0xffe0,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x4208,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0x7bef,0xbdf7,0xffff,
	0xffff,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xbdf7,0xffff,
	0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,
};

Image rotest =
{
	16,16,
	(unsigned short*)&rotest_pixels,
	(unsigned char*)0,
};
