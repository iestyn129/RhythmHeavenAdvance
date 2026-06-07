#include "prologues/shootem.h"
#include "engines.h"

struct CompressedData *shootem_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

struct GraphicsTable shootem_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &shootem_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &shootem_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &shootem_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ shootem_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    /* OBJ Palette */ {
        /* Src.  */ shootem_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    END_OF_GRAPHICS_TABLE
};

EngineEvent shootem_prologue_engine_events[] = {
    shootem_stub
};

struct GameEngine shootem_prologue_engine = {
    /* Size in Memory */ sizeof(struct ShootemPrologueEngineData),
    /* Start Engine   */ shootem_prologue_engine_start,
    /* Update Engine  */ shootem_prologue_engine_update,
    /* Stop Engine    */ shootem_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ shootem_prologue_engine_events,
    /* Input Event    */ NULL
};
