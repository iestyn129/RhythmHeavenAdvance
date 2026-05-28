#include "prologues/lockstep.h"
#include "engines.h"

struct CompressedData *lockstep_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable lockstep_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &lockstep_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &lockstep_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &lockstep_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ lockstep_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    /* OBJ Palette */ {
        /* Src.  */ lockstep_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    END_OF_GRAPHICS_TABLE
};

EngineEvent lockstep_prologue_engine_events[] = {
    lockstep_stub
};

struct GameEngine lockstep_prologue_engine = {
    /* Size in Memory */ sizeof(struct LockstepPrologueEngineData),
    /* Start Engine   */ lockstep_prologue_engine_start,
    /* Update Engine  */ lockstep_prologue_engine_update,
    /* Stop Engine    */ lockstep_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ lockstep_prologue_engine_events,
    /* Input Event    */ NULL
};
