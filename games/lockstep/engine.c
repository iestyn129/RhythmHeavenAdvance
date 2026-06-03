#include "engines/lockstep.h"

extern struct CueDefinition *lockstep_cue_index[];

EngineEvent lockstep_common_events[] = {
	NULL,
	NULL,
	lockstep_common_init_tutorial,
	END_OF_COMMON_EVENT_LIST
};

EngineEvent lockstep_engine_events[] = {
	lockstep_wait_for_input,
	lockstep_beat_anim,
	lockstep_flip_bg,
	lockstep_set_zoom
};

struct GameEngine lockstep_engine = {
	sizeof(struct LockstepEngineData),
	lockstep_engine_start,
	lockstep_engine_update,
	lockstep_engine_stop,
	lockstep_cue_index,
	lockstep_common_events,
	lockstep_engine_events,
	lockstep_input_event
};

struct CompressedData *lockstep_buffered_textures[] = {
	END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable lockstep_gfx_table[] = {
	{
		&lockstep_bg_tiles,
		BG_TILESET_BASE(0), // bg tileset 0
		COMPRESSED_GFX_SOURCE
	},
	{
		&lockstep_bg_map,
		BG_MAP_BASE(0xC000), // bg tilemap 24
		COMPRESSED_GFX_SOURCE
	},
	{
		&lockstep_obj,
		OBJ_TILESET_BASE(0), // obj tileset 0
		COMPRESSED_GFX_SOURCE
	},
	{
		lockstep_bg_pal,
		BG_PALETTE_BUFFER(0), // bg palette 0
		0x60
	},
	{
		lockstep_obj_pal,
		OBJ_PALETTE_BUFFER(0), // obj palette 0
		0x20
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable *lockstep_gfx_tables[] = {
	lockstep_gfx_table
};

struct CueDefinition lockstep_cue_l = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x18,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct LockstepCue),
	/* Func. Spawn     */ lockstep_cue_spawn,
	/* Spawn Parameter */ LOCKSTEP_CUE_L,
	/* Func. Update    */ lockstep_cue_update,
	/* Func. Despawn   */ lockstep_cue_despawn,
	/* Func. Hit       */ lockstep_cue_hit,
	/* Func. Barely    */ lockstep_cue_barely,
	/* Func. Miss      */ lockstep_cue_miss,
	/* SFX Spawn       */ NULL,
	/* SFX Hit         */ &s_f_lockstep_shot_l_seqData,
	/* SFX Barely      */ &s_tebyoushi_pati_seqData,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition lockstep_cue_r = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x18,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct LockstepCue),
	/* Func. Spawn     */ lockstep_cue_spawn,
	/* Spawn Parameter */ LOCKSTEP_CUE_R,
	/* Func. Update    */ lockstep_cue_update,
	/* Func. Despawn   */ lockstep_cue_despawn,
	/* Func. Hit       */ lockstep_cue_hit,
	/* Func. Barely    */ lockstep_cue_barely,
	/* Func. Miss      */ lockstep_cue_miss,
	/* SFX Spawn       */ NULL,
	/* SFX Hit         */ &s_f_lockstep_shot_r_seqData,
	/* SFX Barely      */ &s_tebyoushi_pati_seqData,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition *lockstep_cue_index[] = {
	&lockstep_cue_l,
	&lockstep_cue_r,
	END_OF_CUE_INDEX
};


struct Animation* lockstep_stepper_animations[LOCKSTEP_NUM_ZOOM_LEVELS][LOCKSTEP_NUM_ANIMS] = {
	{
		anim_lockstep_stepper_idle_z00,
		anim_lockstep_stepper_beat_z00,
		anim_lockstep_stepper_shot_l_z00,
		anim_lockstep_stepper_shot_r_z00,
		anim_lockstep_stepper_miss_l_z00,
		anim_lockstep_stepper_miss_r_z00
	},
	{
		anim_lockstep_stepper_idle_z00,
		anim_lockstep_stepper_beat_z00,
		anim_lockstep_stepper_shot_l_z00,
		anim_lockstep_stepper_shot_r_z00,
		anim_lockstep_stepper_miss_l_z00,
		anim_lockstep_stepper_miss_r_z00
	}
};

struct Animation* lockstep_crowd_animations_lower[LOCKSTEP_NUM_ZOOM_LEVELS][LOCKSTEP_NUM_ANIMS] = {
	{
		anim_lockstep_crowd_lower_idle_zP,
		anim_lockstep_crowd_lower_beat_zP,
		anim_lockstep_crowd_lower_shot_l_zP,
		anim_lockstep_crowd_lower_shot_r_zP,
		anim_lockstep_blank, anim_lockstep_blank
	},
	{
		anim_lockstep_crowd_lower_idle_z00,
		anim_lockstep_crowd_lower_beat_z00,
		anim_lockstep_crowd_lower_shot_l_z00,
		anim_lockstep_crowd_lower_shot_r_z00,
		anim_lockstep_blank, anim_lockstep_blank
	}
};

struct Animation* lockstep_crowd_animations_higher[LOCKSTEP_NUM_ZOOM_LEVELS][LOCKSTEP_NUM_ANIMS] = {
	{
		anim_lockstep_blank,
		anim_lockstep_blank,
		anim_lockstep_blank,
		anim_lockstep_blank,
		anim_lockstep_blank, anim_lockstep_blank
	},
	{
		anim_lockstep_crowd_higher_idle_z00,
		anim_lockstep_crowd_higher_beat_z00,
		anim_lockstep_crowd_higher_shot_l_z00,
		anim_lockstep_crowd_higher_shot_r_z00,
		anim_lockstep_blank, anim_lockstep_blank
	}
};

struct Animation* (*lockstep_animations[3])[LOCKSTEP_NUM_ANIMS] = {
	lockstep_stepper_animations,
	lockstep_crowd_animations_lower,
	lockstep_crowd_animations_higher
};

u8 lockstep_bg_palettes[] = {
	1, 2
};
