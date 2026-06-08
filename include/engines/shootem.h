#pragma once

#include "global.h"
#include "engines.h"
#include "src/main.h"
#include "games/shootem/graphics/shootem_graphics.h"

enum ShootemCuesEnum {
	SHOOTEM_CUE_TARGET
};

struct ShootemEngineData {
	u8 version;
	u8 awaitingInput;
	s32 loopCounter;
	s16 cueX;
	s16 cueY;

	struct Cannon {
		s16 cannonSprite;
		s16 faceSprite;
		s16 laserSprite;
	} cannon;
};

struct ShootemCue {
	u32 type;
	s16 sprite;
};

extern struct CompressedData *shootem_buffered_textures[];
extern struct GraphicsTable *shootem_gfx_tables[];

extern s16 shootem_cue_positions[4][2];

extern void shootem_init_gfx3();
extern void shootem_init_gfx2();
extern void shootem_init_gfx1();

extern void shootem_engine_start(u32 version);
extern void shootem_engine_stop();
extern void shootem_engine_update();

extern void cannon_init(struct Cannon* cannon);
extern void cannon_delete(struct Cannon* cannon);
extern void cannon_update(struct Cannon* cannon);
extern void cannon_shoot(const struct Cannon* cannon);

extern void shootem_wait_for_input();
extern void shootem_start_loop();
extern void shootem_end_loop();
extern void shootem_set_cue_pos(u16 pos_idx);

extern void shootem_input_event(u32 pressed, u32 released);

extern void shootem_cue_spawn(struct Cue *cue, struct ShootemCue *info, u32 type);
extern u32 shootem_cue_update(struct Cue *cue, struct ShootemCue *info, u32 runningTime, u32 duration);
extern void shootem_cue_despawn(struct Cue *cue, struct ShootemCue *info);
extern void shootem_cue_hit(struct Cue *cue, struct ShootemCue *info, u32 pressed, u32 released);
extern void shootem_cue_barely(struct Cue *cue, struct ShootemCue *info, u32 pressed, u32 released);
extern void shootem_cue_miss(struct Cue *cue, struct ShootemCue *info);
