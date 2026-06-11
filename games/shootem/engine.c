#include "engines/shootem.h"

extern struct CueDefinition *shootem_cue_index[];

EngineEvent shootem_common_events[] = {
	END_OF_COMMON_EVENT_LIST
};

EngineEvent shootem_engine_events[] = {
	shootem_wait_for_input,
	shootem_start_loop,
	shootem_end_loop,
	shootem_set_cue_pos
};

struct GameEngine shootem_engine = {
	sizeof(struct ShootemEngineData),
	shootem_engine_start,
	shootem_engine_update,
	shootem_engine_stop,
	shootem_cue_index,
	shootem_common_events,
	shootem_engine_events,
	shootem_input_event
};

struct CompressedData *shootem_buffered_textures[] = {
	END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable shootem_gfx_table[] = {
	{
		&shootem_bg_tiles,
		BG_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		&shootem_bg0_map,
		BG_MAP_BASE(28 * 0x800),
		COMPRESSED_GFX_SOURCE
	},
	{
		&shootem_bg2_map,
		BG_MAP_BASE(30 * 0x800),
		COMPRESSED_GFX_SOURCE
	},
	{
		&shootem_obj,
		OBJ_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		shootem_bg_pal,
		BG_PALETTE_BUFFER(0),
		0x20
	},
	{
		shootem_obj_pal,
		OBJ_PALETTE_BUFFER(0),
		0xA0
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable *shootem_gfx_tables[] = {
	shootem_gfx_table
};

struct Animation* shootem_cue_animations[SHOOTEM_CUE_COUNT][SHOOTEM_CUE_STATE_COUNT] = {
	{
		anim_shootem_cue_target_idle,
		anim_shootem_cue_target_hit,
		anim_shootem_cue_target_near,
		anim_shootem_cue_target_barely,
		anim_shootem_cue_target_miss
	},
	{
		anim_shootem_cue_enemy_idle,
		anim_shootem_cue_enemy_hit,
		anim_shootem_cue_enemy_near,
		anim_shootem_cue_enemy_barely,
		anim_shootem_cue_enemy_miss
	}
};

s16 shootem_cue_positions[9][2] = {
	{ -80, -48 },
	{ 80, -48 },
	{ -80, 24 },
	{ 80, 24 },
	{ -40, -32 },
	{ 40, -32 },
	{ -40, 8 },
	{ 40, 8 },
	{ 0, -8 }
};

s16 shootem_cue_trajectories[9][3][2] = {
	{ { 0x100, 0xD8 }, { 0xB0, 0xD0 }, { 0x200, 0xD4 } },
	{ { 0x100, 0x28 }, { 0xB0, 0x30 }, { 0x200, 0x2C } },
	{ { 0x100, 0xA8 }, { 0xB0, 0xAC }, { 0x200, 0xC8 } },
	{ { 0x100, 0x58 }, { 0xB0, 0x54 }, { 0x200, 0x38 } },
	{ { 0x100, 0xF4 }, { 0x60, 0xD0 }, { 0x200, 0xE0 } },
	{ { 0x100, 0x0C }, { 0x60, 0x30 }, { 0x200, 0x20 } },
	{ { 0x100, 0xD0 }, { 0x60, 0xAC }, { 0x200, 0xD0 } },
	{ { 0x100, 0x30 }, { 0x60, 0x54 }, { 0x200, 0x30 } },
	{ { 0x100, 0x00 }, { 0x00, 0x00 }, { 0x200, 0x00 } }
};

s32 shootem_cannon_hurt_offsets[6] = {
	0, 3, -3, 2, -1, 1
};

u32 shootem_stars_tile_indexes[64] = {
	000, 000, 000, 000, 000, 000, 000, 000,
	000, 000, 000, 000, 000, 000, 000, 000,
	000, 000, 000, 000, 000, 000, 000, 000,
	000, 000, 000, 000, 000, 000, 000, 000,
	000, 000, 000, 000, 000, 000, 000, 000,
	000, 000, 000, 000, 000, 000, 000, 000,
	000, 000, 000, 000, 000, 000, 000, 103,
	104, 105, 106, 107, 108, 109, 110, 111
};

struct CueDefinition shootem_cue_target = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x60,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct ShootemCue),
	/* Func. Spawn     */ shootem_cue_spawn,
	/* Spawn Parameter */ SHOOTEM_CUE_TARGET,
	/* Func. Update    */ shootem_cue_update,
	/* Func. Despawn   */ shootem_cue_despawn,
	/* Func. Hit       */ shootem_cue_hit,
	/* Func. Barely    */ shootem_cue_barely,
	/* Func. Miss      */ shootem_cue_miss,
	/* SFX Spawn       */ &s_f_shootem_spawn_seqData,
	/* SFX Hit         */ &s_f_shootem_hit_seqData,
	/* SFX Barely      */ &s_f_shootem_hit_seqData,
	/* SFX Miss        */ &s_f_shootem_miss_seqData,
	/* Miss Condition  */ NULL
};

struct CueDefinition shootem_cue_enemy = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x60,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct ShootemCue),
	/* Func. Spawn     */ shootem_cue_spawn,
	/* Spawn Parameter */ SHOOTEM_CUE_ENEMY,
	/* Func. Update    */ shootem_cue_update,
	/* Func. Despawn   */ shootem_cue_despawn,
	/* Func. Hit       */ shootem_cue_hit,
	/* Func. Barely    */ shootem_cue_barely,
	/* Func. Miss      */ shootem_cue_miss,
	/* SFX Spawn       */ &s_f_shootem_spawn_seqData,
	/* SFX Hit         */ &s_f_shootem_hit_seqData,
	/* SFX Barely      */ &s_f_shootem_hit_seqData,
	/* SFX Miss        */ &s_f_shootem_miss_seqData,
	/* Miss Condition  */ NULL
};

struct CueDefinition *shootem_cue_index[] = {
	&shootem_cue_target,
	&shootem_cue_enemy,
	END_OF_CUE_INDEX
};
