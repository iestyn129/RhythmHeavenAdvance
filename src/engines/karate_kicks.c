#include "engines/karate_kicks.h"

#include "syscall.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gKarateKicks ((struct KarateKicksEngineData*)gCurrentEngineData)


void karate_kicks_init_gfx3() {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
}


void karate_kicks_init_gfx2() {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), karate_kicks_gfx_tables[gKarateKicks->version], 0x2000);
    run_func_after_task(temp, karate_kicks_init_gfx3, 0);
}


void karate_kicks_init_gfx1() {
    u32 temp;

    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), karate_kicks_buffered_textures);
    run_func_after_task(temp, karate_kicks_init_gfx2, 0);
}


void karate_kicks_engine_start(const u32 version) {
    gKarateKicks->version = version;

    karate_kicks_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, 0, 0, 28, BGCNT_PRIORITY(3));

    gameplay_set_input_buttons(A_BUTTON, A_BUTTON);
}


void karate_kicks_engine_stop() {
    scene_hide_bg_layer(0);
}


void karate_kicks_engine_update() {
    if (D_03004afc & SELECT_BUTTON) {
        if (gKarateKicks->awaitingInput) {
            gameplay_set_input_buttons(A_BUTTON, 0);
            set_pause_beatscript_scene(FALSE);
            gKarateKicks->awaitingInput = FALSE;
        }
    }
}


void karate_kicks_wait_for_input() {
    gameplay_set_input_buttons(0, 0);
    set_pause_beatscript_scene(TRUE);

    gKarateKicks->awaitingInput = TRUE;
}


void karate_kicks_input_event(const u32 pressed, u32 released) {}


void karate_kicks_cue_spawn(struct Cue *cue, struct KarateKicksCue *info, u32 type) {
    info->type = type;
}


u32 karate_kicks_cue_update(struct Cue *cue, struct KarateKicksCue *info, u32 runningTime, u32 duration) {
    return FALSE;//sprite_is_invalid(gSpriteHandler, info->sprite);
}


void karate_kicks_cue_despawn(struct Cue *cue, struct KarateKicksCue *info) {}


void karate_kicks_cue_barely(struct Cue *cue, struct KarateKicksCue *info, u32 pressed, u32 released) {}


void karate_kicks_cue_miss(struct Cue *cue, struct KarateKicksCue *info) {}
