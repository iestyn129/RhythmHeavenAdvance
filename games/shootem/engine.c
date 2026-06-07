#include "engines/shootem.h"

extern struct CueDefinition *shootem_cue_index[];

EngineEvent shootem_common_events[] = {
	END_OF_COMMON_EVENT_LIST
};

EngineEvent shootem_engine_events[] = {};

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
		BG_TILESET_BASE(0), // bg tileset 0
		COMPRESSED_GFX_SOURCE
	},
	{
		&shootem_bg_map,
		BG_MAP_BASE(0xC000), // bg tilemap 24
		COMPRESSED_GFX_SOURCE
	},
	{
		&shootem_obj,
		OBJ_TILESET_BASE(0), // obj tileset 0
		COMPRESSED_GFX_SOURCE
	},
	{
		shootem_bg_pal,
		BG_PALETTE_BUFFER(0), // bg palette 0
		0x60
	},
	{
		shootem_obj_pal,
		OBJ_PALETTE_BUFFER(0), // obj palette 0
		0x20
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable *shootem_gfx_tables[] = {
	shootem_gfx_table
};

struct CueDefinition *shootem_cue_index[] = {
	END_OF_CUE_INDEX
};
