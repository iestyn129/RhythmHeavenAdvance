#include "engines/karate_kicks.h"

extern struct CueDefinition *karate_kicks_cue_index[];

EngineEvent karate_kicks_common_events[] = {
	karate_kicks_common_beat_animation,
	NULL,
	NULL,
	END_OF_COMMON_EVENT_LIST
};

EngineEvent karate_kicks_engine_events[] = {
	karate_kicks_wait_for_input,
	karate_kicks_start_loop,
	karate_kicks_end_loop
};

struct GameEngine karate_kicks_engine = {
	sizeof(struct KarateKicksEngineData),
	karate_kicks_engine_start,
	karate_kicks_engine_update,
	karate_kicks_engine_stop,
	karate_kicks_cue_index,
	karate_kicks_common_events,
	karate_kicks_engine_events,
	karate_kicks_input_event
};

struct CompressedData* karate_kicks_buffered_textures[] = {
	END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable karate_kicks_gfx_table[] = {
	{
		&karate_kicks_bg_tiles,
		BG_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		&karate_kicks_bg_map,
		BG_MAP_BASE(28 * 0x800),
		COMPRESSED_GFX_SOURCE
	},
	{
		&karate_kicks_obj,
		OBJ_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		karate_kicks_bg_pal,
		BG_PALETTE_BUFFER(0),
		0x20
	},
	{
		karate_kicks_obj_pal,
		OBJ_PALETTE_BUFFER(0),
		0x120
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable* karate_kicks_gfx_tables[] = {
	karate_kicks_gfx_table
};

// type, x, y, x speed, y speed, angle, rotation
s32 karate_kicks_barrel_part_defaults[KARATE_KICKS_NUM_BARREL_PARTS][7] = {
	{ KARATE_KICKS_BARREL_PART_HOOP, -3, -19, -7, -1, 252, -1 },
	{ KARATE_KICKS_BARREL_PART_HEAD, 3, -20, -4, -2, 250, -2 },
	{ KARATE_KICKS_BARREL_PART_STAVE, -24, 0, -10, -0, 0, -1 },
	{ KARATE_KICKS_BARREL_PART_STAVE, -14, 1, -8, -1, 5, 4 },
	{ KARATE_KICKS_BARREL_PART_STAVE, -1, 2, -7, -2, 7, -3 },
	{ KARATE_KICKS_BARREL_PART_STAVE, 9, 1, -4, -2, 131, 2 },
	{ KARATE_KICKS_BARREL_PART_STAVE, 18, 0, -5, 0, 139, 4 },
	{ KARATE_KICKS_BARREL_PART_HOOP, 0, 18, -6, 1, 4, 3 },
	{ KARATE_KICKS_BARREL_PART_HEAD, 0, 19, -5, 2, 6, 2 }
};

struct CueDefinition karate_kicks_cue_pot = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x18,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct KarateKicksCue),
	/* Func. Spawn     */ karate_kicks_cue_spawn,
	/* Spawn Parameter */ KARATE_KICKS_OBJECT_POT,
	/* Func. Update    */ karate_kicks_cue_update,
	/* Func. Despawn   */ karate_kicks_cue_despawn,
	/* Func. Hit       */ karate_kicks_cue_hit,
	/* Func. Barely    */ karate_kicks_cue_barely,
	/* Func. Miss      */ karate_kicks_cue_miss,
	/* SFX Spawn       */ &s_f_karate_kicks_kicks_spawn_seqData,
	/* SFX Hit         */ &s_f_karate_kicks_kicks_hit_seqData,
	/* SFX Barely      */ &s_witch_donats_seqData,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition karate_kicks_cue_pot_off = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x18,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct KarateKicksCue),
	/* Func. Spawn     */ karate_kicks_cue_spawn,
	/* Spawn Parameter */ KARATE_KICKS_OBJECT_POT,
	/* Func. Update    */ karate_kicks_cue_update,
	/* Func. Despawn   */ karate_kicks_cue_despawn,
	/* Func. Hit       */ karate_kicks_cue_hit,
	/* Func. Barely    */ karate_kicks_cue_barely,
	/* Func. Miss      */ karate_kicks_cue_miss,
	/* SFX Spawn       */ &s_f_karate_kicks_kicks_spawn_off_seqData,
	/* SFX Hit         */ &s_f_karate_kicks_kicks_hit_seqData,
	/* SFX Barely      */ &s_witch_donats_seqData,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition karate_kicks_cue_bulb = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x18,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct KarateKicksCue),
	/* Func. Spawn     */ karate_kicks_cue_spawn,
	/* Spawn Parameter */ KARATE_KICKS_OBJECT_BULB,
	/* Func. Update    */ karate_kicks_cue_update,
	/* Func. Despawn   */ karate_kicks_cue_despawn,
	/* Func. Hit       */ karate_kicks_cue_hit,
	/* Func. Barely    */ karate_kicks_cue_barely,
	/* Func. Miss      */ karate_kicks_cue_miss,
	/* SFX Spawn       */ &s_f_karate_kicks_kicks_spawn_bulb_seqData,
	/* SFX Hit         */ &s_f_karate_kicks_kicks_hit_bulb_seqData,
	/* SFX Barely      */ &s_witch_donats_seqData,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition karate_kicks_cue_barrel = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x18,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct KarateKicksCue),
	/* Func. Spawn     */ karate_kicks_cue_spawn,
	/* Spawn Parameter */ KARATE_KICKS_OBJECT_BARREL,
	/* Func. Update    */ karate_kicks_cue_update,
	/* Func. Despawn   */ karate_kicks_cue_despawn,
	/* Func. Hit       */ karate_kicks_cue_hit,
	/* Func. Barely    */ karate_kicks_cue_barely,
	/* Func. Miss      */ karate_kicks_cue_miss,
	/* SFX Spawn       */ &s_f_karate_kicks_kicks_spawn_barrel_seqData,
	/* SFX Hit         */ &s_f_karate_kicks_kicks_hit_barrel_seqData,
	/* SFX Barely      */ &s_f_karate_kicks_kicks_hit_barrel_seqData,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition karate_kicks_cue_bomb = {
	/* Unknown Param.  */ 0,
	/* Input Buttons   */ RELEASE_BUTTON(A_BUTTON),
	/* Total Duration  */ 0x12,
	/* Hit Window      */ -0x03, 0x03,
	/* Barely Window   */ -0x05, 0x05,
	/* Tempo-Dependent */ FALSE,
	/* Force-Delete    */ FALSE,
	/* Size in Memory  */ sizeof(struct KarateKicksCue),
	/* Func. Spawn     */ karate_kicks_cue_spawn,
	/* Spawn Parameter */ KARATE_KICKS_OBJECT_BOMB,
	/* Func. Update    */ karate_kicks_cue_update,
	/* Func. Despawn   */ karate_kicks_cue_despawn,
	/* Func. Hit       */ karate_kicks_cue_hit,
	/* Func. Barely    */ karate_kicks_cue_barely,
	/* Func. Miss      */ karate_kicks_cue_miss,
	/* SFX Spawn       */ NULL,
	/* SFX Hit         */ &s_f_karate_kicks_kicks_hit_bomb_seqData,
	/* SFX Barely      */ NULL,
	/* SFX Miss        */ NULL,
	/* Miss Condition  */ NULL
};

struct CueDefinition *karate_kicks_cue_index[] = {
	&karate_kicks_cue_pot,
	&karate_kicks_cue_bulb,
	&karate_kicks_cue_barrel,
	&karate_kicks_cue_bomb,
	&karate_kicks_cue_pot_off,
	END_OF_CUE_INDEX
};
