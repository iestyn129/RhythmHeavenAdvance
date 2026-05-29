#pragma once

#include "global.h"
#include "engines.h"
#include "src/main.h"

#include "games/lockstep/graphics/lockstep_graphics.h"

enum LockstepCuesEnum {
	LOCKSTEP_CUE_L,
	LOCKSTEP_CUE_R
};

enum StepperMissState {
	MISS_L,
	MISS_R,
	MISS_NONE
};

struct LockstepEngineData {
	u8 version;
	u8 awaitingInput;

	struct SwitchStepper {
		s16 sprite;
		u8 missState;
	} stepper;
	s16 crowdSprite;

	u8 isBgOff;
	u8 direction;
	u8 markingCriteria;
};

struct LockstepCue {
	u32 type;
	u8 hasStepped;
};

extern struct CompressedData *lockstep_buffered_textures[];
extern struct GraphicsTable *lockstep_gfx_tables[];
extern u8 lockstep_palettes[];

extern void lockstep_init_gfx3(void);
extern void lockstep_init_gfx2(void);
extern void lockstep_init_gfx1(void);

extern void lockstep_engine_start(u32 version);
extern void lockstep_engine_stop(void);
extern void lockstep_engine_update(void);

extern void stepper_init(struct SwitchStepper* stepper);
extern void stepper_delete(struct SwitchStepper* stepper);
extern void stepper_update(struct SwitchStepper* stepper);
extern void stepper_set_anim(struct SwitchStepper* stepper, struct Animation* anim);

extern void lockstep_wait_for_input(void);
extern void lockstep_beat_anim(u8 play_sfx);
extern void lockstep_flip_bg(void);
extern void lockstep_set_direction(u8 direction);
extern void lockstep_set_marking_criteria(u8 criteria);

extern void lockstep_input_event(u32 pressed, u32 released);

extern void lockstep_cue_spawn(struct Cue *cue, struct LockstepCue *info, u32 type);
extern u32 lockstep_cue_update(struct Cue *cue, struct LockstepCue *info, u32 runningTime, u32 duration);
extern void lockstep_cue_despawn(struct Cue *cue, struct LockstepCue *info);
extern void lockstep_cue_hit(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released);
extern void lockstep_cue_barely(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released);
extern void lockstep_cue_miss(struct Cue *cue, struct LockstepCue *info);

extern void lockstep_update_bg_palette(void);
