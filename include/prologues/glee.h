#pragma once

#include "global.h"
#include "games/glee/graphics/glee_prologue_graphics.h"

struct GleePrologueEngineData {
	u8 ver;
	s16 sprite;
};

extern struct CompressedData* glee_prologue_buffered_textures[];
extern struct GraphicsTable glee_prologue_gfx_table[];

extern void glee_gfx_init_02();
extern void glee_gfx_init_01();
extern void glee_gfx_init_00();
extern void glee_prologue_engine_start(u32);
extern void glee_stub();
extern void glee_prologue_engine_update();
extern void glee_prologue_engine_stop();
