#include "engines/lockstep.h"

#include "syscall.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gLockstep ((struct LockstepEngineData*)gCurrentEngineData)


void lockstep_init_gfx3() {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
    lockstep_update_bg_palette();
}


void lockstep_init_gfx2() {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), lockstep_gfx_tables[gLockstep->version], 0x2000);
    run_func_after_task(temp, lockstep_init_gfx3, 0);
}


void lockstep_init_gfx1() {
    u32 temp;

    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), lockstep_buffered_textures);
    run_func_after_task(temp, lockstep_init_gfx2, 0);
}


void lockstep_engine_start(const u32 ver) {
    gLockstep->version = ver;
    gLockstep->awaitingInput = FALSE;
    gLockstep->zoomLevel = LOCKSTEP_ZOOM_LEVEL_PRACTICE;
    gLockstep->isBgOff = FALSE;

    lockstep_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 24, 1);

    stepper_init(&gLockstep->stepper, FALSE);
    stepper_init(&gLockstep->crowd, TRUE);

    gLockstep->textPrinter = text_printer_create_new(get_current_mem_id(), 2, 208, 30);
    text_printer_set_colors(gLockstep->textPrinter, 0);
    text_printer_set_x_y(gLockstep->textPrinter, 16, 16);
    text_printer_set_layer(gLockstep->textPrinter, 0x4700);
    text_printer_center_by_content(gLockstep->textPrinter, TRUE);

    gLockstep->aButtonSprite = sprite_create(gSpriteHandler,
        anim_lockstep_a_button, 0,
        120, 80, 0x4700,
        1, 0, 0x8000
    );

    gameplay_set_input_buttons(A_BUTTON, 0);
}


void lockstep_engine_stop() {
    stepper_delete(&gLockstep->stepper);
    stepper_delete(&gLockstep->crowd);
    sprite_delete(gSpriteHandler, gLockstep->aButtonSprite);
    // should i delete the textbox here?
    scene_hide_bg_layer(1);
}


void lockstep_engine_update() {
    if (gLockstep->awaitingInput && D_03004afc & A_BUTTON) {
        sprite_set_visible(gSpriteHandler, gLockstep->aButtonSprite, FALSE);
        gameplay_set_input_buttons(A_BUTTON, 0);
        set_pause_beatscript_scene(FALSE);
        gLockstep->awaitingInput = FALSE;
    }

    stepper_update(&gLockstep->stepper);
    text_printer_update(gLockstep->textPrinter);
}


void lockstep_common_init_tutorial(struct Scene *scene) {
    if (scene != NULL) {
        gameplay_enable_tutorial(TRUE);
        gameplay_set_skip_destination(scene);
        gameplay_set_skip_icon(1, TRUE);
    } else {
        gameplay_enable_tutorial(FALSE);
        gameplay_set_skip_icon(0, FALSE);
    }
}


void stepper_init(struct SwitchStepper* stepper, u8 isCrowd) {
    stepper->isCrowd = isCrowd;
    stepper->animState = LOCKSTEP_ANIM_IDLE;

    stepper->sprite = sprite_create(gSpriteHandler,
        lockstep_animations[stepper->isCrowd][gLockstep->zoomLevel][stepper->animState], 0,
        120, 80, 0x4800 + (0x100 * (!stepper->isCrowd)),
        1, 0, 0
    );

    if (stepper->isCrowd) {
        stepper->sprite2 = sprite_create(gSpriteHandler,
            lockstep_animations[2][gLockstep->zoomLevel][stepper->animState], 0,
            120, 80, 0x4A00,
            1, 0, 0
        );
    } else {
        stepper->sprite2 = -1;
    }
}


void stepper_delete(struct SwitchStepper* stepper) {
    sprite_delete(gSpriteHandler, stepper->sprite);
    sprite_delete(gSpriteHandler, stepper->sprite2);
}


void stepper_update(struct SwitchStepper* stepper) {}


void stepper_set_anim(struct SwitchStepper* stepper, u8 animIdx) {
    if (animIdx >= LOCKSTEP_NUM_ANIMS) {
        return;
    }

    stepper->animState = animIdx;

    sprite_set_anim(gSpriteHandler,
        stepper->sprite, lockstep_animations[stepper->isCrowd][gLockstep->zoomLevel][stepper->animState],
        0, 1, 0x7f, 0
    );

    if (stepper->sprite2 != -1) {
        sprite_set_anim(gSpriteHandler,
            stepper->sprite2, lockstep_animations[2][gLockstep->zoomLevel][stepper->animState],
            0, 1, 0x7f, 0
        );
    }
}


void lockstep_wait_for_input() {
    sprite_set_anim_cel(gSpriteHandler, gLockstep->aButtonSprite, 0);
    sprite_set_visible(gSpriteHandler, gLockstep->aButtonSprite, TRUE);

    gameplay_set_input_buttons(0, 0);
    set_pause_beatscript_scene(TRUE);

    gLockstep->awaitingInput = TRUE;
}


void lockstep_beat_anim(u8 play_sfx) {
    struct SwitchStepper* stepper = &gLockstep->stepper;
    struct SwitchStepper* crowd = &gLockstep->crowd;

    stepper_set_anim(stepper, LOCKSTEP_ANIM_BEAT);
    stepper_set_anim(crowd, LOCKSTEP_ANIM_BEAT);

    if (play_sfx) {
        play_sound(&s_dontan_count_seqData);
    }
}


void lockstep_flip_bg() {
    gLockstep->isBgOff = !gLockstep->isBgOff;
    if (gLockstep->isBgOff > 1) {
        gLockstep->isBgOff = 1;
    }

    lockstep_update_bg_palette();
}


void lockstep_set_zoom(u8 zoomLevel) {
    struct SwitchStepper* stepper = &gLockstep->stepper;
    struct SwitchStepper* crowd = &gLockstep->crowd;
    u8 animProgressStepper, animProgressCrowdLower, animProgressCrowdHigher;

    if (zoomLevel > LOCKSTEP_NUM_ZOOM_LEVELS) {
        zoomLevel = LOCKSTEP_NUM_ZOOM_LEVELS - 1;
    }

    animProgressStepper = sprite_get_anim_progress(gSpriteHandler, stepper->sprite);
    animProgressCrowdLower = sprite_get_anim_progress(gSpriteHandler, crowd->sprite);
    animProgressCrowdHigher = sprite_get_anim_progress(gSpriteHandler, crowd->sprite2);

    gLockstep->zoomLevel = zoomLevel;

    stepper_set_anim(stepper, stepper->animState);
    sprite_set_anim_progress(gSpriteHandler, stepper->sprite, animProgressStepper);
    stepper_set_anim(crowd, crowd->animState);
    sprite_set_anim_progress(gSpriteHandler, crowd->sprite, animProgressCrowdLower);
    sprite_set_anim_progress(gSpriteHandler, crowd->sprite2, animProgressCrowdHigher);
}


void lockstep_print_text(const char* text) {
	text_printer_set_string(gLockstep->textPrinter, text);
}


void lockstep_input_event(const u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;
    u8 isOffBeat, animIdx;

    if (gameplay_is_tutorial_enabled()) {
        return;
    }

    isOffBeat = FIXED_TO_INT(Div(
        INT_TO_FIXED(D_030053c0.runningTime),
        INT_TO_FIXED(0x0C) // divide by half a beat (in ticks)
    ) % INT_TO_FIXED(0x02)); // mod to get 0 for an on beat and 1 for an off beat

    gameplay_add_cue_result(gameplay_get_marking_criteria(), CUE_RESULT_MISS, 0);

    if (isOffBeat) {
        animIdx = LOCKSTEP_ANIM_SHOT_R;
    } else {
        animIdx = LOCKSTEP_ANIM_SHOT_L;
    }

    stepper_set_anim(stepper, animIdx);

    play_sound(&s_witch_donats_seqData);
}


void lockstep_cue_spawn(struct Cue *cue, struct LockstepCue *info, u32 type) {
    info->type = type;
    info->hasStepped = FALSE;
}


u32 lockstep_cue_update(struct Cue *cue, struct LockstepCue *info, u32 runningTime, u32 duration) {
    struct SwitchStepper* crowd = &gLockstep->crowd;
    s32 passedBeats = Div(INT_TO_FIXED(runningTime), duration);

    if (!info->hasStepped && passedBeats >= 0xFF) {
        //*(volatile u32*)(ExternWorkRAMBase + 0x3FFF0) = passedBeats;

        play_sound(&s_f_lockstep_step_seqData);

        switch (info->type) {
            case LOCKSTEP_CUE_L:
                stepper_set_anim(crowd, LOCKSTEP_ANIM_SHOT_L);
                break;
            case LOCKSTEP_CUE_R:
                stepper_set_anim(crowd, LOCKSTEP_ANIM_SHOT_R);
                break;
            default:
                break;
        }

        info->hasStepped = TRUE;
    }

    return cue->hasExpired;
}


void lockstep_cue_despawn(struct Cue *cue, struct LockstepCue *info) {}


void lockstep_cue_hit(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (info->type) {
        case LOCKSTEP_CUE_L:
            stepper_set_anim(stepper, LOCKSTEP_ANIM_SHOT_L);
            break;
        case LOCKSTEP_CUE_R:
            stepper_set_anim(stepper, LOCKSTEP_ANIM_SHOT_R);
            break;
        default:
            break;
    }
}


void lockstep_cue_barely(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (info->type) {
        case LOCKSTEP_CUE_L:
            stepper_set_anim(stepper, LOCKSTEP_ANIM_SHOT_L);
            break;
        case LOCKSTEP_CUE_R:
            stepper_set_anim(stepper, LOCKSTEP_ANIM_SHOT_R);
            break;
        default:
            break;
    }
}


void lockstep_cue_miss(struct Cue *cue, struct LockstepCue *info) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (info->type) {
        case LOCKSTEP_CUE_L:
            if (stepper->animState != LOCKSTEP_ANIM_MISS_L) {
                stepper_set_anim(stepper, LOCKSTEP_ANIM_MISS_L);
                play_sound(&s_f_lockstep_miss_seqData);
            }

            stepper->animState = LOCKSTEP_ANIM_MISS_L;
            break;
        case LOCKSTEP_CUE_R:
            if (stepper->animState != LOCKSTEP_ANIM_MISS_R) {
                stepper_set_anim(stepper, LOCKSTEP_ANIM_MISS_R);
                play_sound(&s_f_lockstep_miss_seqData);
            }

            stepper->animState = LOCKSTEP_ANIM_MISS_R;
            break;
        default:
            break;
    }
}


void lockstep_update_bg_palette() {
    (BG_PALETTE_BUFFER(0))[0] = (BG_PALETTE_BUFFER(lockstep_bg_palettes[gLockstep->isBgOff]))[0];
}
