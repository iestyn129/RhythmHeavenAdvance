#include "prologues/cars.h"

#include "src/scenes/gameplay.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"

#define gPrologueEngineData ((struct CarsPrologueEngineData*)gCurrentEngineData)


void cars_gfx_init_02() {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


void cars_gfx_init_01() {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), cars_prologue_gfx_table, 0x2000);
    run_func_after_task(task, cars_gfx_init_02, 0);
}


void cars_gfx_init_00() {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), cars_prologue_buffered_textures);
    run_func_after_task(task, cars_gfx_init_01, 0);
}


void cars_prologue_engine_start(const u32 ver) {
    gPrologueEngineData->ver = ver;

    cars_gfx_init_00();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, 0, 0, 28, BGCNT_PRIORITY(1));

    gPrologueEngineData->sprite = sprite_create(gSpriteHandler,
        anim_cars_prologue_title, 0,
        120, 80, 0,
        1, 0, 0
    );
}


void cars_stub() {}


void cars_prologue_engine_update() {}


void cars_prologue_engine_stop() {}
