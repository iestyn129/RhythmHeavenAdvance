#include "engines/lockstep.h"

#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gLockstep ((struct LockstepEngineData*)gCurrentEngineData)


void lockstep_init_gfx3(void) {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
}


void lockstep_init_gfx2(void) {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), lockstep_gfx_tables[gLockstep->version], 0x2000);
    run_func_after_task(temp, lockstep_init_gfx3, 0);
}


void lockstep_init_gfx1(void) {
    u32 temp;
    
    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), lockstep_buffered_textures);
    run_func_after_task(temp, lockstep_init_gfx2, 0);
}


void lockstep_engine_start(const u32 ver) {
    gLockstep->version = ver;
    gLockstep->awaitingInput = FALSE;

    lockstep_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 24, 1);

    stepper_init(&gLockstep->stepper);

    gameplay_set_input_buttons(A_BUTTON | B_BUTTON, 0);
}


void lockstep_engine_stop(void) {
    scene_hide_bg_layer(1);
}


void lockstep_engine_update(void) {
    if (gLockstep->awaitingInput && D_03004afc & SELECT_BUTTON) {
        set_pause_beatscript_scene(FALSE);
        gLockstep->awaitingInput = FALSE;
    }

    stepper_update(&gLockstep->stepper);
}


void stepper_init(struct SwitchStepper* stepper) {
    stepper->sprite = sprite_create(gSpriteHandler,
    anim_lockstep_stepper_idle, 0,
        72, 48, 0x4800,
        1, 0, 0
    );
}

void stepper_delete(struct SwitchStepper* stepper) {
    sprite_delete(gSpriteHandler, stepper->sprite);
}


void stepper_update(struct SwitchStepper* stepper) {}


void lockstep_wait_for_input(void) {
    set_pause_beatscript_scene(TRUE);
    gLockstep->awaitingInput = TRUE;
}


void lockstep_input_event(const u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (pressed) {
        case A_BUTTON:
            sprite_set_anim(gSpriteHandler,
                stepper->sprite, anim_lockstep_stepper_shot_r,
                0, 1, 0x7f, 0
            );

            play_sound(&s_f_lockstep_step_seqData);
            play_sound(&s_f_lockstep_shot_r_seqData);
            break;
        case B_BUTTON:
            sprite_set_anim(gSpriteHandler,
                stepper->sprite, anim_lockstep_stepper_shot_l,
                0, 1, 0x7f, 0
            );

            play_sound(&s_f_lockstep_step_seqData);
            play_sound(&s_f_lockstep_shot_l_seqData);
            break;
        default:
            break;
    }
}
