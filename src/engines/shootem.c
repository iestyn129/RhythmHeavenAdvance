#include "engines/shootem.h"

#include "syscall.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gShootem ((struct ShootemEngineData*)gCurrentEngineData)


void shootem_init_gfx3() {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
}


void shootem_init_gfx2() {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), shootem_gfx_tables[gShootem->version], 0x2000);
    run_func_after_task(temp, shootem_init_gfx3, 0);
}


void shootem_init_gfx1() {
    u32 temp;

    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), shootem_buffered_textures);
    run_func_after_task(temp, shootem_init_gfx2, 0);
}


void shootem_engine_start(const u32 ver) {
    gShootem->version = ver;

    shootem_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 24, 1);

    gameplay_set_input_buttons(A_BUTTON, 0);
}


void shootem_engine_stop() {
    scene_hide_bg_layer(1);
}


void shootem_engine_update() {}


void shootem_input_event(const u32 pressed, u32 released) {
    play_sound(&s_witch_donats_seqData);
}
