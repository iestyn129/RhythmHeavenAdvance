#pragma once

#include "global.h"
#include "games/karate_kicks/graphics/karate_kicks_prologue_graphics.h"

struct KarateKicksPrologueEngineData {
	u8 ver;
};

extern struct CompressedData *karate_kicks_prologue_buffered_textures[];
extern struct GraphicsTable karate_kicks_prologue_gfx_table[];

extern void karate_kicks_gfx_init_02();
extern void karate_kicks_gfx_init_01();
extern void karate_kicks_gfx_init_00();
extern void karate_kicks_prologue_engine_start(u32);
extern void karate_kicks_stub();
extern void karate_kicks_prologue_engine_update();
extern void karate_kicks_prologue_engine_stop();
extern void karate_kicks_set_frame(u32);
