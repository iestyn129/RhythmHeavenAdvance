#pragma once

#include "global.h"
#include "engines.h"
#include "src/main.h"
#include "games/lockstep/graphics/lockstep_graphics.h"

enum LockstepAnimType {
	LOCKSTEP_ANIM_IDLE,
	LOCKSTEP_ANIM_BEAT,
	LOCKSTEP_ANIM_SHOT_L,
	LOCKSTEP_ANIM_SHOT_R,
	LOCKSTEP_ANIM_MISS_L,
	LOCKSTEP_ANIM_MISS_R,

	LOCKSTEP_NUM_ANIMS
};

enum LockstepZoomLevel {
	LOCKSTEP_ZOOM_LEVEL_PRACTICE,
	LOCKSTEP_ZOOM_LEVEL_1,
	//LOCKSTEP_ZOOM_LEVEL_2,
	//LOCKSTEP_ZOOM_LEVEL_3,
	//LOCKSTEP_ZOOM_LEVEL_4,
	//LOCKSTEP_ZOOM_LEVEL_5,

	LOCKSTEP_NUM_ZOOM_LEVELS
};

enum LockstepCuesEnum {
	LOCKSTEP_CUE_L,
	LOCKSTEP_CUE_R
};

struct LockstepEngineData {
	u8 version;
	u8 awaitingInput;

	struct SwitchStepper {
		s16 sprite;
		s16 sprite2;
		u8 animState;
		u8 isCrowd;
	} stepper;
	struct SwitchStepper crowd;

	u8 zoomLevel;
	u8 isBgOff;
};

struct LockstepCue {
	u32 type;
	u8 hasStepped;
};

extern struct CompressedData *lockstep_buffered_textures[];
extern struct GraphicsTable *lockstep_gfx_tables[];

extern struct Animation* lockstep_stepper_animations[LOCKSTEP_NUM_ZOOM_LEVELS][LOCKSTEP_NUM_ANIMS];
extern struct Animation* lockstep_crowd_animations_lower[LOCKSTEP_NUM_ZOOM_LEVELS][LOCKSTEP_NUM_ANIMS];
extern struct Animation* lockstep_crowd_animations_higher[LOCKSTEP_NUM_ZOOM_LEVELS][LOCKSTEP_NUM_ANIMS];
extern struct Animation* (*lockstep_animations[3])[LOCKSTEP_NUM_ANIMS];
extern u8 lockstep_bg_palettes[];

extern void lockstep_init_gfx3(void);
extern void lockstep_init_gfx2(void);
extern void lockstep_init_gfx1(void);

extern void lockstep_engine_start(u32 version);
extern void lockstep_engine_stop(void);
extern void lockstep_engine_update(void);

extern void lockstep_common_init_tutorial(struct Scene*);

extern void stepper_init(struct SwitchStepper* stepper, u8 isCrowd);
extern void stepper_delete(struct SwitchStepper* stepper);
extern void stepper_update(struct SwitchStepper* stepper);
extern void stepper_set_anim(struct SwitchStepper* stepper, u8 animIdx);

extern void lockstep_wait_for_input(void);
extern void lockstep_beat_anim(u8 play_sfx);
extern void lockstep_flip_bg(void);
extern void lockstep_set_zoom(u8 zoomLevel);

extern void lockstep_input_event(u32 pressed, u32 released);

extern void lockstep_cue_spawn(struct Cue *cue, struct LockstepCue *info, u32 type);
extern u32 lockstep_cue_update(struct Cue *cue, struct LockstepCue *info, u32 runningTime, u32 duration);
extern void lockstep_cue_despawn(struct Cue *cue, struct LockstepCue *info);
extern void lockstep_cue_hit(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released);
extern void lockstep_cue_barely(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released);
extern void lockstep_cue_miss(struct Cue *cue, struct LockstepCue *info);

extern void lockstep_update_bg_palette(void);
