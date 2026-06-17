#pragma once

#include "global.h"
#include "engines.h"
#include "games/glee/graphics/glee_graphics.h"

struct GleeEngineData {
	u8 version;
};

extern struct CompressedData* glee_buffered_textures[];
extern struct GraphicsTable* glee_gfx_tables[];

extern void glee_init_gfx3();
extern void glee_init_gfx2();
extern void glee_init_gfx1();

extern void glee_engine_start(u32 version);
extern void glee_engine_stop();
extern void glee_engine_update();

extern void glee_input_event(u32 pressed, u32 released);
