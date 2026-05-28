#pragma once

#include "global.h"
#include "engines.h"
#include "src/main.h"

#include "games/lockstep/graphics/lockstep_graphics.h"

struct LockstepEngineData {
	u8 version;
	u8 awaitingInput;
	struct SwitchStepper {
		s16 sprite;
	} stepper;
};

extern struct CompressedData *lockstep_buffered_textures[];
extern struct GraphicsTable *lockstep_gfx_tables[];

extern void lockstep_init_gfx3(void);
extern void lockstep_init_gfx2(void);
extern void lockstep_init_gfx1(void);
extern void lockstep_engine_start(u32 version);
extern void lockstep_engine_stop(void);
extern void lockstep_engine_update(void);
extern void stepper_init(struct SwitchStepper* stepper);
extern void stepper_delete(struct SwitchStepper* stepper);
extern void stepper_update(struct SwitchStepper* stepper);
extern void lockstep_wait_for_input(void);
extern void lockstep_input_event(u32 pressed, u32 released);
