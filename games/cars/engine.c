#include "engines/cars.h"

extern struct CueDefinition* cars_cue_index[];

EngineEvent cars_common_events[] = {
	END_OF_COMMON_EVENT_LIST
};

EngineEvent cars_engine_events[] = {};

struct GameEngine cars_engine = {
	sizeof(struct CarsEngineData),
	cars_engine_start,
	cars_engine_update,
	cars_engine_stop,
	cars_cue_index,
	cars_common_events,
	cars_engine_events,
	cars_input_event
};

struct CompressedData* cars_buffered_textures[] = {
	END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable cars_gfx_table[] = {
	{
		&cars_bg_tiles,
		BG_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		&cars_bg0_map,
		BG_MAP_BASE(28 * 0x800),
		COMPRESSED_GFX_SOURCE
	},
	{
		&cars_bg1_map,
		BG_MAP_BASE(29 * 0x800),
		COMPRESSED_GFX_SOURCE
	},
	{
		&cars_obj,
		OBJ_TILESET_BASE(0),
		COMPRESSED_GFX_SOURCE
	},
	{
		cars_bg_pal,
		BG_PALETTE_BUFFER(0),
		0x20 * 2
	},
	{
		cars_obj_pal,
		OBJ_PALETTE_BUFFER(0),
		0x20 * 3
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable* cars_gfx_tables[] = {
	cars_gfx_table
};

struct CueDefinition* cars_cue_index[] = {
	END_OF_CUE_INDEX
};
