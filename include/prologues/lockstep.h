#pragma once

#include "global.h"
#include "games/lockstep/graphics/lockstep_prologue_graphics.h"


struct LockstepPrologueEngineData {
	u8 ver;
	s16 textSprite;
};

extern struct CompressedData *lockstep_prologue_buffered_textures[];
extern struct GraphicsTable lockstep_prologue_gfx_table[];

extern void lockstep_gfx_init_02(void);
extern void lockstep_gfx_init_01(void);
extern void lockstep_gfx_init_00(void);
extern void lockstep_prologue_engine_start(u32);
extern void lockstep_stub(void);
extern void lockstep_prologue_engine_update(void);
extern void lockstep_prologue_engine_stop(void);
extern void lockstep_set_frame(u32);
