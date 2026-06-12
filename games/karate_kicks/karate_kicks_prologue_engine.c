#include "prologues/karate_kicks.h"
#include "engines.h"

struct CompressedData *karate_kicks_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable karate_kicks_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &karate_kicks_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_kicks_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(28 * 0x800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &karate_kicks_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ karate_kicks_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    /* OBJ Palette */ {
        /* Src.  */ karate_kicks_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    END_OF_GRAPHICS_TABLE
};

EngineEvent karate_kicks_prologue_engine_events[] = {
    karate_kicks_stub
};

struct GameEngine karate_kicks_prologue_engine = {
    /* Size in Memory */ sizeof(struct KarateKicksPrologueEngineData),
    /* Start Engine   */ karate_kicks_prologue_engine_start,
    /* Update Engine  */ karate_kicks_prologue_engine_update,
    /* Stop Engine    */ karate_kicks_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ karate_kicks_prologue_engine_events,
    /* Input Event    */ NULL
};
