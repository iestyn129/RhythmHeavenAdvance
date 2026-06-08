#pragma once

#include "global.h"
#include "engines.h"
#include "src/main.h"
#include "games/shootem/graphics/shootem_graphics.h"

struct ShootemEngineData {
	u8 version;
	u8 awaitingInput;

	struct Cannon {
		s16 cannonSprite;
		s16 faceSprite;
		s16 laserSprite;
	} cannon;
};


extern struct CompressedData *shootem_buffered_textures[];
extern struct GraphicsTable *shootem_gfx_tables[];

extern void shootem_init_gfx3();
extern void shootem_init_gfx2();
extern void shootem_init_gfx1();

extern void shootem_engine_start(u32 version);
extern void shootem_engine_stop();
extern void shootem_engine_update();

extern void cannon_init(struct Cannon* cannon);
extern void cannon_delete(struct Cannon* cannon);
extern void cannon_update(struct Cannon* cannon);

extern void shootem_wait_for_input();

extern void shootem_input_event(u32 pressed, u32 released);
