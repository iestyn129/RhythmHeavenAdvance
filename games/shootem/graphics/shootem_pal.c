#include "global.h"
#include "graphics.h"
#include "shootem_graphics.h"

Palette shootem_obj_pal[] = {
	/* palette 00 */ {
		/* 00 */ TO_RGB555(0x7088f8),
		/* 01 */ TO_RGB555(0x202028),
		/* 02 */ TO_RGB555(0x3838e8),
		/* 03 */ TO_RGB555(0xd028d0),
		/* 04 */ TO_RGB555(0x606060),
		/* 05 */ TO_RGB555(0xf84848),
		/* 06 */ TO_RGB555(0x08a800),
		/* 07 */ TO_RGB555(0x909090),
		/* 08 */ TO_RGB555(0x00e800),
		/* 09 */ TO_RGB555(0xa8a8f8),
		/* 10 */ TO_RGB555(0xf0a068),
		/* 11 */ TO_RGB555(0xb0b0b8),
		/* 12 */ TO_RGB555(0x30e8f8),
		/* 13 */ TO_RGB555(0xf80000),
		/* 14 */ TO_RGB555(0x000000),
		/* 15 */ TO_RGB555(0xf8f8f8)
	},
	/* palette 01 */ {
		/* 00 */ TO_RGB555(0x7088f8),
		/* 01 */ TO_RGB555(0x202028),
		/* 02 */ TO_RGB555(0x3838e8),
		/* 03 */ TO_RGB555(0xd028d0),
		/* 04 */ TO_RGB555(0xe0f0f8),
		/* 05 */ TO_RGB555(0xf84848),
		/* 06 */ TO_RGB555(0x08a800),
		/* 07 */ TO_RGB555(0xa8d8f8),
		/* 08 */ TO_RGB555(0x00e800),
		/* 09 */ TO_RGB555(0xa8a8f8),
		/* 10 */ TO_RGB555(0xf0a068),
		/* 11 */ TO_RGB555(0xb0b0b8),
		/* 12 */ TO_RGB555(0x30e8f8),
		/* 13 */ TO_RGB555(0xf80000),
		/* 14 */ TO_RGB555(0x000000),
		/* 15 */ TO_RGB555(0xf8f8f8)
	},
	/* palette 02 */ {
		/* 00 */ TO_RGB555(0x7088f8),
		/* 01 */ TO_RGB555(0x880000),
		/* 02 */ TO_RGB555(0x881848),
		/* 03 */ TO_RGB555(0x383840),
		/* 04 */ TO_RGB555(0xb05080),
		/* 05 */ TO_RGB555(0xf84848),
		/* 06 */ TO_RGB555(0x707028),
		/* 07 */ TO_RGB555(0xa0a0b0),
		/* 08 */ TO_RGB555(0xa8b0b8),
		/* 09 */ TO_RGB555(0xb8b8b8),
		/* 10 */ TO_RGB555(0xc8f060),
		/* 11 */ TO_RGB555(0xf8f800),
		/* 12 */ TO_RGB555(0xe0f8b0),
		/* 13 */ TO_RGB555(0xf80000),
		/* 14 */ TO_RGB555(0x000000),
		/* 15 */ TO_RGB555(0xf8f8f8)
	},
	/* palette 03 */ {
		/* 00 */ TO_RGB555(0x7088f8),
		/* 01 */ TO_RGB555(0x202028),
		/* 02 */ TO_RGB555(0x606880),
		/* 03 */ TO_RGB555(0x383840),
		/* 04 */ TO_RGB555(0xf87878),
		/* 05 */ TO_RGB555(0xf84848),
		/* 06 */ TO_RGB555(0x08a800),
		/* 07 */ TO_RGB555(0xf8c0c0),
		/* 08 */ TO_RGB555(0x00e800),
		/* 09 */ TO_RGB555(0x9898a8),
		/* 10 */ TO_RGB555(0xd0d0d0),
		/* 11 */ TO_RGB555(0x404050),
		/* 12 */ TO_RGB555(0x30e8f8),
		/* 13 */ TO_RGB555(0xf80000),
		/* 14 */ TO_RGB555(0x000000),
		/* 15 */ TO_RGB555(0xf8f800)
	},
	/* palette 04 */ {
		/* 00 */ TO_RGB555(0x7088f8),
		/* 01 */ TO_RGB555(0x202028),
		/* 02 */ TO_RGB555(0xd0d0d0),
		/* 03 */ TO_RGB555(0x383840),
		/* 04 */ TO_RGB555(0xf87878),
		/* 05 */ TO_RGB555(0x9898a8),
		/* 06 */ TO_RGB555(0x08a800),
		/* 07 */ TO_RGB555(0xf8c0c0),
		/* 08 */ TO_RGB555(0x08a800),
		/* 09 */ TO_RGB555(0x9898a8),
		/* 10 */ TO_RGB555(0xd0d0d0),
		/* 11 */ TO_RGB555(0x404050),
		/* 12 */ TO_RGB555(0x30e8f8),
		/* 13 */ TO_RGB555(0xf80000),
		/* 14 */ TO_RGB555(0x000000),
		/* 15 */ TO_RGB555(0xf8f800)
	}
};

Palette shootem_bg_pal[] = {
	/* palette 00 */ {
		/* 00 */ TO_RGB555(0x000000),
		/* 01 */ TO_RGB555(0x3840c0),
		/* 02 */ TO_RGB555(0x101068),
		/* 03 */ TO_RGB555(0x9090e0),
		/* 04 */ TO_RGB555(0x7878d8),
		/* 05 */ TO_RGB555(0x081090),
		/* 06 */ TO_RGB555(0x6068d0),
		/* 07 */ TO_RGB555(0x98a0e0),
		/* 08 */ TO_RGB555(0x081030),
		/* 09 */ TO_RGB555(0x880000),
		/* 10 */ TO_RGB555(0x000000),
		/* 11 */ TO_RGB555(0x000000),
		/* 12 */ TO_RGB555(0x000000),
		/* 13 */ TO_RGB555(0x000000),
		/* 14 */ TO_RGB555(0x000000),
		/* 15 */ TO_RGB555(0x000000)
	}
};
