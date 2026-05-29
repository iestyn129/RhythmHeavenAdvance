#include "engines/lockstep.h"

#include "syscall.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gLockstep ((struct LockstepEngineData*)gCurrentEngineData)


void lockstep_init_gfx3(void) {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
    lockstep_update_bg_palette();
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
    gLockstep->isBgOff = FALSE;

    lockstep_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 24, 1);

    stepper_init(&gLockstep->stepper);
    gLockstep->crowdSprite = sprite_create(gSpriteHandler,
        anim_lockstep_crowd_idle, 0,
        0, 0, 0x4800,
        1, 0, 0
    );

    gameplay_set_input_buttons(A_BUTTON, 0);
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
        72, 40, 0x4900,
        1, 0, 0
    );
    stepper->missState = MISS_NONE;
}


void stepper_delete(struct SwitchStepper* stepper) {
    sprite_delete(gSpriteHandler, stepper->sprite);
}


void stepper_update(struct SwitchStepper* stepper) {}


void stepper_set_anim(struct SwitchStepper* stepper, struct Animation* anim) {
    sprite_set_anim(gSpriteHandler,
        stepper->sprite, anim,
        0, 1, 0x7f, 0
    );
    stepper->missState = MISS_NONE;
}


void lockstep_wait_for_input(void) {
    set_pause_beatscript_scene(TRUE);
    gLockstep->awaitingInput = TRUE;
}


void lockstep_beat_anim(u8 play_sfx) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    stepper_set_anim(stepper, anim_lockstep_stepper_beat);

    sprite_set_anim(gSpriteHandler,
        gLockstep->crowdSprite, anim_lockstep_crowd_beat,
        0, 1, 0x7f, 0
    );

    if (play_sfx) {
        play_sound(&s_dontan_count_seqData);
    }
}


void lockstep_flip_bg(void) {
    gLockstep->isBgOff = !gLockstep->isBgOff;
    if (gLockstep->isBgOff > 1) {
        gLockstep->isBgOff = 1;
    }

    lockstep_update_bg_palette();
}


void lockstep_set_direction(u8 direction) {
    gLockstep->direction = direction;

    if (gLockstep->direction > LOCKSTEP_CUE_R) {
        gLockstep->direction = LOCKSTEP_CUE_R;
    }
}


void lockstep_set_marking_criteria(u8 criteria) {
    gLockstep->markingCriteria = criteria;
}


void lockstep_input_event(const u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;
    struct Animation* anim;

    switch (gLockstep->direction) {
        case LOCKSTEP_CUE_R:
            anim = anim_lockstep_stepper_shot_l;
            break;
        case LOCKSTEP_CUE_L:
        default:
            anim = anim_lockstep_stepper_shot_r;
            break;
    }

    stepper_set_anim(stepper, anim);

    play_sound(&s_witch_donats_seqData);
}


void lockstep_cue_spawn(struct Cue *cue, struct LockstepCue *info, u32 type) {
    info->type = type;
    info->hasStepped = FALSE;
}


u32 lockstep_cue_update(struct Cue *cue, struct LockstepCue *info, u32 runningTime, u32 duration) {
    s32 passedBeats = Div(INT_TO_FIXED(runningTime), duration);

    if (!info->hasStepped && passedBeats >= 0xFF) {
        //*(volatile u32*)(ExternWorkRAMBase + 0x3FFF0) = passedBeats;

        play_sound(&s_f_lockstep_step_seqData);

        switch (info->type) {
            case LOCKSTEP_CUE_L:
                sprite_set_anim(gSpriteHandler,
                    gLockstep->crowdSprite, anim_lockstep_crowd_shot_l,
                    0, 1, 0x7f, 0
                );
                break;
            case LOCKSTEP_CUE_R:
                sprite_set_anim(gSpriteHandler,
                    gLockstep->crowdSprite, anim_lockstep_crowd_shot_r,
                    0, 1, 0x7f, 0
                );
                break;
            default:
                break;
        }

        info->hasStepped = TRUE;
    }

    return FALSE;
}


void lockstep_cue_despawn(struct Cue *cue, struct LockstepCue *info) {}


void lockstep_cue_hit(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (info->type) {
        case LOCKSTEP_CUE_L:
            stepper_set_anim(stepper, anim_lockstep_stepper_shot_l);
            break;
        case LOCKSTEP_CUE_R:
            stepper_set_anim(stepper, anim_lockstep_stepper_shot_r);
            break;
        default:
            break;
    }
}


void lockstep_cue_barely(struct Cue *cue, struct LockstepCue *info, u32 pressed, u32 released) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (info->type) {
        case LOCKSTEP_CUE_L:
            stepper_set_anim(stepper, anim_lockstep_stepper_shot_l);
            break;
        case LOCKSTEP_CUE_R:
            stepper_set_anim(stepper, anim_lockstep_stepper_shot_r);
            break;
        default:
            break;
    }
}


void lockstep_cue_miss(struct Cue *cue, struct LockstepCue *info) {
    struct SwitchStepper* stepper = &gLockstep->stepper;

    switch (info->type) {
        case LOCKSTEP_CUE_L:
            if (stepper->missState != MISS_L) {
                stepper_set_anim(stepper, anim_lockstep_stepper_miss_l);
                play_sound(&s_f_lockstep_miss_seqData);
            }

            stepper->missState = MISS_L;
            break;
        case LOCKSTEP_CUE_R:
            if (stepper->missState != MISS_R) {
                stepper_set_anim(stepper, anim_lockstep_stepper_miss_r);
                play_sound(&s_f_lockstep_miss_seqData);
            }

            stepper->missState = MISS_R;
            break;
        default:
            break;
    }
}


void lockstep_update_bg_palette(void) {
    (BG_PALETTE_BUFFER(0))[0] = (BG_PALETTE_BUFFER(lockstep_palettes[gLockstep->isBgOff]))[0];
}
