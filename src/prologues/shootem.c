#include "prologues/shootem.h"

#include "src/scenes/gameplay.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

#define gPrologueEngineData ((struct ShootemPrologueEngineData *)gCurrentEngineData)


void shootem_gfx_init_02(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


void shootem_gfx_init_01(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), shootem_prologue_gfx_table, 0x2000);
    run_func_after_task(task, shootem_gfx_init_02, 0);
}


void shootem_gfx_init_00(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), shootem_prologue_buffered_textures);
    run_func_after_task(task, shootem_gfx_init_01, 0);
}


void shootem_prologue_engine_start(const u32 ver) {
    gPrologueEngineData->ver = ver;

    shootem_gfx_init_00();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);
}


void shootem_stub(void) {}


void shootem_prologue_engine_update(void) {}


void shootem_prologue_engine_stop(void) {}


void shootem_set_frame(const u32 frame) {
    //sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}
