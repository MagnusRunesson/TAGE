#include "Engine/Graphics/Tilebank.h"

const uint16 tilebank_spacebase_pixels[] =
{
	// Tile 0
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	// Tile 1
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 2
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x1da7,0x941c,0x941c,0x941c,

	// Tile 3
	0x0000,0x0000,0x0000,0x1da7,
	0x0000,0x0000,0x1da7,0x941c,
	0x0000,0x1da7,0x941c,0x941c,
	0x1da7,0x941c,0x941c,0x941c,

	// Tile 4
	0x1da7,0x941c,0x941c,0x941c,
	0x1da7,0x941c,0x941c,0x941c,
	0x1da7,0x941c,0x941c,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 5
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,

	// Tile 6
	0xffff,0x7b6e,0x7b6e,0x941c,
	0x7b6e,0xe490,0x8250,0x2e13,
	0x7b6e,0x8250,0x8250,0x2e13,
	0x941c,0x2e13,0x2e13,0x4a0a,

	// Tile 7
	0xffff,0x7b6e,0x7b6e,0x941c,
	0x7b6e,0x96fd,0xf0fb,0x2e13,
	0x7b6e,0xf0fb,0xf0fb,0x2e13,
	0x941c,0x2e13,0x2e13,0x4a0a,

	// Tile 8
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x941c,0x0000,0x941c,

	// Tile 9
	0x0e03,0x0e03,0x0e03,0x0e03,
	0x0e03,0x0e03,0x0e03,0x0e03,
	0x0e03,0x0e03,0x0e03,0x0e03,
	0x0e03,0x0e03,0x0e03,0x0e03,

	// Tile 10
	0x0e03,0x0e03,0x0e03,0x0e03,
	0x941c,0x0e03,0x0e03,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 11
	0x941c,0xb84d,0x941c,0x941c,
	0x941c,0xb84d,0x941c,0x941c,
	0x941c,0x941c,0xb84d,0xb84d,
	0x941c,0x941c,0x941c,0x941c,

	// Tile 12
	0x941c,0xb84d,0x941c,0x941c,
	0x941c,0xb84d,0x941c,0x941c,
	0x941c,0x941c,0xb84d,0x941c,
	0x941c,0x941c,0xb84d,0x941c,

	// Tile 13
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x5dd5,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,

	// Tile 14
	0xffff,0x7b6e,0x7b6e,0x941c,
	0x7b6e,0x941c,0x941c,0x2e13,
	0x7b6e,0x941c,0x941c,0x2e13,
	0x941c,0x2e13,0x2e13,0x4a0a,

	// Tile 15
	0x941c,0x7b6e,0x941c,0x7b6e,
	0x941c,0x7b6e,0x941c,0x7b6e,
	0x941c,0x7b6e,0x941c,0x7b6e,
	0x941c,0x7b6e,0x941c,0x7b6e,

	// Tile 16
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	// Tile 17
	0x5b66,0x7404,0x7304,0x5b66,
	0x7304,0x7304,0x7404,0x2e03,
	0x7304,0x7304,0x2e03,0x4a02,
	0x7304,0x7304,0x7304,0x7404,

	// Tile 18
	0x5b66,0x2e03,0x4a02,0x7404,
	0x2e03,0x4a02,0x7404,0x7304,
	0x4a02,0x7304,0x7304,0x7304,
	0x7304,0x7304,0x7404,0x7404,

	// Tile 19
	0x0000,0x0000,0x0000,0x2152,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	// Tile 20
	0x0000,0x0000,0x0000,0x0000,
	0xcdf6,0x0000,0x0000,0x0000,
	0x0000,0x26f6,0x55ff,0x55ff,
	0x0000,0x0000,0x0000,0xcdf6,

	// Tile 21
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x55ff,0x55ff,
	0x55ff,0x55ff,0x55ff,0x55ff,
	0x55ff,0x55ff,0x26f6,0x0000,

	// Tile 22
	0x55ff,0x55ff,0xcdf6,0x0000,
	0x55ff,0x55ff,0x0000,0x0000,
	0xcdf6,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	// Tile 23
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0xffff,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	// Tile 24
	0x0000,0x0000,0x3523,0x0000,
	0x0000,0x3523,0xffff,0x3523,
	0x0000,0x0000,0x3523,0x0000,
	0x0000,0x0000,0x0000,0x0000,

	// Tile 25
	0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x8630,0x0000,
	0x0000,0x8630,0xb9d4,0x8630,
	0x0000,0x0000,0x8630,0x0000,

	// Tile 26
	0x941c,0x7b6e,0x941c,0x7b6e,
	0x941c,0x7b6e,0x941c,0x7b6e,
	0x941c,0x941c,0x941c,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 27
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x5dd5,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 28
	0x941c,0x941c,0x0e03,0x0e03,
	0x941c,0x941c,0x941c,0x941c,
	0x941c,0x941c,0x941c,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 29
	0x941c,0xb84d,0x941c,0x941c,
	0x941c,0x941c,0xb84d,0x941c,
	0x941c,0x941c,0xb84d,0x941c,
	0x1da7,0x1da7,0x1da7,0x1da7,

	// Tile 30
	0x7304,0x7304,0xffff,0x5b66,
	0x7404,0xffff,0x5b66,0x5b66,
	0xffff,0x5b66,0x2e03,0x2e03,
	0x5b66,0x5b66,0x2e03,0x0000,

	// Tile 31
	0x5b66,0x7304,0x7304,0x7304,
	0x7304,0x7304,0x7304,0x7404,
	0x7304,0x7304,0x2e03,0x7404,
	0x5b66,0x2e03,0x4a02,0x7304,

};

const uint8 tilebank_spacebase_alpha[] __attribute__ ((aligned (4))) =
{
	// Tile 0
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,

	// Tile 1
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 2
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 3
	0x00,0x00,0x00,0xff,
	0x00,0x00,0xff,0xff,
	0x00,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 4
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 5
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 6
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 7
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 8
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x00,0xff,0x00,0xff,

	// Tile 9
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 10
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 11
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 12
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 13
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 14
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 15
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 16
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 17
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 18
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 19
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 20
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 21
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 22
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 23
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 24
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 25
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 26
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 27
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 28
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 29
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 30
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

	// Tile 31
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,

};

extern "C" const CTileBank tilebank_spacebase;
const CTileBank tilebank_spacebase =
{
	4,4,
	32,
	(uint16*)&tilebank_spacebase_pixels,
	(uint8*)&tilebank_spacebase_alpha,
	(uint8*)"tilebank_spacebase",
};
