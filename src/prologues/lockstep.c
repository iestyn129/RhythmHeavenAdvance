#include "prologues/lockstep.h"

#include "src/scenes/gameplay.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

#define gPrologueEngineData ((struct LockstepPrologueEngineData *)gCurrentEngineData)


void lockstep_gfx_init_02(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


void lockstep_gfx_init_01(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), lockstep_prologue_gfx_table, 0x2000);
    run_func_after_task(task, lockstep_gfx_init_02, 0);
}


void lockstep_gfx_init_00(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), lockstep_prologue_buffered_textures);
    run_func_after_task(task, lockstep_gfx_init_01, 0);
}


void lockstep_prologue_engine_start(const u32 ver) {
    gPrologueEngineData->ver = ver;

    lockstep_gfx_init_00();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler,
        anim_lockstep_prologue_title, 0,
        40, 121, 0,
        0, 0, 0
    );
}


void lockstep_stub(void) {}


void lockstep_prologue_engine_update(void) {}


void lockstep_prologue_engine_stop(void) {}


void lockstep_set_frame(const u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}
