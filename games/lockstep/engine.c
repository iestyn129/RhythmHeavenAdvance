#include "engines/lockstep.h"

extern struct CueDefinition *lockstep_cue_index[];

EngineEvent lockstep_common_events[] = {
	END_OF_COMMON_EVENT_LIST
};

EngineEvent lockstep_engine_events[] = {
	lockstep_wait_for_input
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
		lockstep_pal,
		BG_PALETTE_BUFFER(0), // bg palette 0
		0x20
	},
	{
		lockstep_pal,
		OBJ_PALETTE_BUFFER(0), // obj palette 0
		0x20
	},
	END_OF_GRAPHICS_TABLE
};

struct GraphicsTable *lockstep_gfx_tables[] = {
	lockstep_gfx_table
};

struct CueDefinition *lockstep_cue_index[] = {
	END_OF_CUE_INDEX
};
