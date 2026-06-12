#include "engines/karate_kicks.h"

extern struct CueDefinition *karate_kicks_cue_index[];

EngineEvent karate_kicks_common_events[] = {
	END_OF_COMMON_EVENT_LIST
};

EngineEvent karate_kicks_engine_events[] = {
	karate_kicks_wait_for_input
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

struct CompressedData *karate_kicks_buffered_textures[] = {
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

struct GraphicsTable *karate_kicks_gfx_tables[] = {
	karate_kicks_gfx_table
};

struct CueDefinition *karate_kicks_cue_index[] = {
	END_OF_CUE_INDEX
};
