#pragma once

#include "global.h"
#include "games/cars/graphics/cars_prologue_graphics.h"

struct CarsPrologueEngineData {
	u8 ver;
	s16 sprite;
};

extern struct CompressedData* cars_prologue_buffered_textures[];
extern struct GraphicsTable cars_prologue_gfx_table[];

extern void cars_gfx_init_02();
extern void cars_gfx_init_01();
extern void cars_gfx_init_00();
extern void cars_prologue_engine_start(u32);
extern void cars_stub();
extern void cars_prologue_engine_update();
extern void cars_prologue_engine_stop();
