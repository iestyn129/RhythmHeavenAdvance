#include "engines/glee.h"

#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gGlee ((struct GleeEngineData*)gCurrentEngineData)


void glee_init_gfx3() {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
}


void glee_init_gfx2() {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), glee_gfx_tables[gGlee->version], 0x2000);
    run_func_after_task(temp, glee_init_gfx3, 0);
}


void glee_init_gfx1() {
    u32 temp;

    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), glee_buffered_textures);
    run_func_after_task(temp, glee_init_gfx2, 0);
}


void glee_engine_start(const u32 version) {
    gGlee->version = version;

    glee_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, 0, 0, 28, BGCNT_PRIORITY(3));

    gameplay_set_input_buttons(A_BUTTON, A_BUTTON);
}


void glee_engine_stop() {
    scene_hide_bg_layer(0);
}


void glee_engine_update() {}


void glee_input_event(const u32 pressed, u32 released) {}
