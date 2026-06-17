#include "prologues/glee.h"
#include "engines.h"

struct CompressedData* glee_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable glee_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &glee_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &glee_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(28 * 0x800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &glee_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ glee_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x20 * 1
    },
    /* OBJ Palette */ {
        /* Src.  */ glee_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x20 * 3
    },
    END_OF_GRAPHICS_TABLE
};

EngineEvent glee_prologue_engine_events[] = {
    glee_stub
};

struct GameEngine glee_prologue_engine = {
    /* Size in Memory */ sizeof(struct GleePrologueEngineData),
    /* Start Engine   */ glee_prologue_engine_start,
    /* Update Engine  */ glee_prologue_engine_update,
    /* Stop Engine    */ glee_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ glee_prologue_engine_events,
    /* Input Event    */ NULL
};
