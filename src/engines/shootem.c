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


void shootem_engine_start(const u32 version) {
    gShootem->version = version;
    gShootem->awaitingInput = FALSE;

    shootem_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 24, 1);

    cannon_init(&gShootem->cannon);

    gameplay_set_input_buttons(A_BUTTON, 0);
}


void shootem_engine_stop() {
    cannon_delete(&gShootem->cannon);
    scene_hide_bg_layer(1);
}


void shootem_engine_update() {
    if (gShootem->awaitingInput && D_03004afc & SELECT_BUTTON) {
        //gameplay_set_input_buttons(A_BUTTON, 0);
        set_pause_beatscript_scene(FALSE);
        gShootem->awaitingInput = FALSE;
    }

    cannon_update(&gShootem->cannon);
}


void cannon_init(struct Cannon* cannon) {
    cannon->cannonSprite = sprite_create(gSpriteHandler,
        anim_shootem_cannon_idle, 0,
        120, 80, 0x4800,
        1, 0, 0
    );

    cannon->faceSprite = sprite_create(gSpriteHandler,
        anim_shootem_cannon_face, 0,
        120, 80, 0x4700,
        0, 0, 0
    );

    cannon->laserSprite = sprite_create(gSpriteHandler,
        anim_shootem_laser_idle, 0,
        120, 80, 0x4900,
        1, 0, 0
    );
}


void cannon_delete(struct Cannon* cannon) {
    sprite_delete(gSpriteHandler, cannon->cannonSprite);
    sprite_delete(gSpriteHandler, cannon->faceSprite);
    sprite_delete(gSpriteHandler, cannon->laserSprite);
}


void cannon_update(struct Cannon* cannon) {}


void shootem_wait_for_input() {
    //gameplay_set_input_buttons(0, 0);
    set_pause_beatscript_scene(TRUE);

    gShootem->awaitingInput = TRUE;
}


void shootem_input_event(const u32 pressed, u32 released) {
    struct Cannon* cannon = &gShootem->cannon;

    sprite_set_anim(gSpriteHandler,
        cannon->cannonSprite, anim_shootem_cannon_shoot,
        0, 1, 0x7f, 0
    );
    sprite_set_anim(gSpriteHandler,
        cannon->laserSprite, anim_shootem_laser_shoot,
        0, 1, 0x7f, 0
    );

    //play_sound(&s_witch_donats_seqData);
}
