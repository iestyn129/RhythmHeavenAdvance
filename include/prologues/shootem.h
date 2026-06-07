#pragma once

#include "global.h"
#include "games/shootem/graphics/shootem_prologue_graphics.h"


struct ShootemPrologueEngineData {
	u8 ver;
};

extern struct CompressedData *shootem_prologue_buffered_textures[];
extern struct GraphicsTable shootem_prologue_gfx_table[];

extern void shootem_gfx_init_02(void);
extern void shootem_gfx_init_01(void);
extern void shootem_gfx_init_00(void);
extern void shootem_prologue_engine_start(u32);
extern void shootem_stub(void);
extern void shootem_prologue_engine_update(void);
extern void shootem_prologue_engine_stop(void);
extern void shootem_set_frame(u32);
