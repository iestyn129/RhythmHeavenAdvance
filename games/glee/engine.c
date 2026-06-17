#include "engines/glee.h"

extern struct CueDefinition* glee_cue_index[];

EngineEvent glee_common_events[] = {
	END_OF_COMMON_EVENT_LIST
};

EngineEvent glee_engine_events[] = {};

struct GameEngine glee_engine = {
	sizeof(struct GleeEngineData),
	glee_engine_start,
	glee_engine_update,
	glee_engine_stop,
	glee_cue_index,
	glee_common_events,
	glee_engine_events,
	glee_input_event
};

struct CompressedData* glee_buffered_textures[] = {
	END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable glee_gfx_table[] = {
	{
		&glee_bg_tiles,
		BG_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		&glee_bg_map,
		BG_MAP_BASE(28 * 0x800),
		COMPRESSED_GFX_SOURCE
	},
	{
		&glee_obj,
		OBJ_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		glee_bg_pal,
		BG_PALETTE_BUFFER(0),
		0x20 * 1
	},
	{
		glee_obj_pal,
		OBJ_PALETTE_BUFFER(0),
		0x20 * 9
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable* glee_gfx_tables[] = {
	glee_gfx_table
};

struct CueDefinition* glee_cue_index[] = {
	END_OF_CUE_INDEX
};
