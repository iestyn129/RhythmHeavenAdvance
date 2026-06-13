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

    karate_kicks_joe_init(&gKarateKicks->joe);

    gameplay_set_input_buttons(A_BUTTON, A_BUTTON);
}


void karate_kicks_engine_stop() {
    karate_kicks_joe_delete(&gKarateKicks->joe);
    scene_hide_bg_layer(0);
}


void karate_kicks_engine_update() {
    if (D_03004afc & SELECT_BUTTON) {
        if (gKarateKicks->awaitingInput) {
            gameplay_set_input_buttons(A_BUTTON, A_BUTTON);
            set_pause_beatscript_scene(FALSE);
            gKarateKicks->awaitingInput = FALSE;
        }
    }

    karate_kicks_joe_update(&gKarateKicks->joe);
}


void karate_kicks_common_beat_animation() {
    struct KarateKicksJoe* joe = &gKarateKicks->joe;

    if (
        sprite_get_current_cel(gSpriteHandler, joe->sprite) ==
        sprite_get_total_cels(gSpriteHandler, joe->sprite) - 1 &&
        !joe->skipBeat && !joe->isCharged && !joe->chargeTimer
    ) {
        sprite_set_anim(gSpriteHandler,
            joe->sprite, anim_karate_kicks_joe_beat, 0,
            1, 0x7f, 0
        );
    }

    joe->skipBeat = FALSE;
}


void karate_kicks_joe_init(struct KarateKicksJoe* joe) {
    joe->sprite = sprite_create(gSpriteHandler,
        anim_karate_kicks_joe_ready, 0,
        160, 88, 0x4800,
        1, 0x7f, 0
    );

    sprite_set_base_palette(gSpriteHandler, joe->sprite, 2);
    sprite_set_callback(gSpriteHandler, joe->sprite, karate_kicks_joe_sprite_callback, (u32)joe);

    joe->skipBeat = FALSE;
    joe->isCharged = FALSE;
    joe->chargeTimer = 0;
}


void karate_kicks_joe_delete(struct KarateKicksJoe* joe) {
	sprite_delete(gSpriteHandler, joe->sprite);
}


void karate_kicks_joe_update(struct KarateKicksJoe* joe) {
    if (joe->chargeTimer) {
        joe->chargeTimer--;

        if (joe->chargeTimer <= 0) {
            joe->isCharged = TRUE;
        }
    }
}


void karate_kicks_joe_punch(struct KarateKicksJoe* joe, struct Animation* anim) {
    sprite_set_anim(gSpriteHandler,
        joe->sprite, anim, 0,
        1, 0x7f, 4
    );

    play_sound(&s_f_karate_kicks_punch_seqData);

    joe->chargeTimer = ticks_to_frames(14);
    joe->skipBeat = TRUE;
}


void karate_kicks_joe_release(struct KarateKicksJoe* joe) {
    if (joe->isCharged) {
        sprite_set_anim(gSpriteHandler,
            joe->sprite, anim_karate_kicks_joe_kick, 0,
            1, 0x7f, 0
        );

        play_sound(&s_f_karate_kicks_kick_seqData);
    } else if (sprite_get_anim(gSpriteHandler, joe->sprite) == anim_karate_kicks_joe_charge) {
        sprite_set_anim(gSpriteHandler,
            joe->sprite, anim_karate_kicks_joe_charge_stop, 0,
            1, 0x7f, 0
        );
    }

    joe->isCharged = FALSE;
    joe->chargeTimer = 0;
    joe->skipBeat = TRUE;
}


void karate_kicks_joe_sprite_callback(struct SpriteHandler *handler, s16 id, u32 arg) {
    struct KarateKicksJoe* joe = (struct KarateKicksJoe*)arg;

    if (joe->chargeTimer) {
        sprite_set_anim(handler,
            id, anim_karate_kicks_joe_charge, 0,
            1, 0x7f, 0
        );
    } else {
        sprite_set_anim(handler,
            id, anim_karate_kicks_joe_to_ready, 0,
            1, 0x7f, 0
        );
    }
}


void karate_kicks_wait_for_input() {
    gameplay_set_input_buttons(0, 0);
    set_pause_beatscript_scene(TRUE);

    gKarateKicks->awaitingInput = TRUE;
}


void karate_kicks_input_event(const u32 pressed, u32 released) {
    struct KarateKicksJoe* joe = &gKarateKicks->joe;

    if (pressed & A_BUTTON) {
        karate_kicks_joe_punch(joe, anim_karate_kicks_joe_jab);
    }

    if (released & A_BUTTON) {
        karate_kicks_joe_release(joe);
    }
}


void karate_kicks_cue_spawn(struct Cue *cue, struct KarateKicksCue *info, u32 type) {
    struct Cue* next_cue;
    struct KarateKicksCue* next_cue_info;

    info->type = type;
    info->beenHit = FALSE;

    info->objAffineGroup = (s8)scene_affine_group_alloc();
    info->objSprite = sprite_create(gSpriteHandler,
        anim_karate_kicks_object, (s8)info->type,
        0, 0, 0x4800,
        0, 0, 0
    );
    assign_sprite_affine_param(info->objSprite, info->objAffineGroup);

    info->shadowAffineGroup = (s8)scene_affine_group_alloc();
    info->shadowSprite = sprite_create(gSpriteHandler,
        anim_karate_kicks_object_shadow, 0,
        0, 0, 0x4A00,
        0, 0, 0
    );
    assign_sprite_affine_param(info->shadowSprite, info->shadowAffineGroup);

    info->objXPosition = 0;
    info->objYPosition = 0;
    info->objZPosition = 0x4700;

    info->objScale = 0;
    info->objAngle = 0;
    info->objRotation = 0;

    info->objYLandPosition = 0;

    info->hitObjXSpeed = 0;
    info->hitObjYSpeed = 0;
    info->hitObjXAcceleration = 0;
    info->hitObjYAcceleration = 0;

    info->passedBeats = 0;

    gameplay_get_cue_info(&next_cue, (void**)&next_cue_info);

    while (next_cue != NULL) {
        if (next_cue != cue) {
            next_cue_info->objZPosition++;
        }

        gameplay_get_previous_cue_info(next_cue, &next_cue, (void**)&next_cue_info);
    }
}


u32 karate_kicks_cue_update(struct Cue *cue, struct KarateKicksCue *info, u32 runningTime, u32 duration) {
    struct KarateKicksJoe* joe = &gKarateKicks->joe;
    s32 beatsOffset, y;

    if (runningTime > ticks_to_frames(0x78)) {
        return TRUE;
    }

    if (info->beenHit) {
        info->hitObjXSpeed += info->hitObjXAcceleration;
        info->hitObjYSpeed += info->hitObjYAcceleration;

        info->objXPosition += (s32)info->hitObjXSpeed;
        info->objYPosition += (s32)info->hitObjYSpeed;
        info->objAngle += info->objRotation;

        if (FIXED_TO_INT(info->objXPosition) < -0x20) {
            return TRUE;
        }

        if (FIXED_TO_INT(info->objYPosition) > info->objYLandPosition) {
            info->objYPosition = INT_TO_FIXED(info->objYLandPosition);
            info->hitObjXSpeed = 0;
            info->hitObjYSpeed = 0;
            info->hitObjYAcceleration = 0;
            info->objRotation = 0;
        }
    } else {
        info->passedBeats = Div(INT_TO_FIXED(runningTime), (s32)duration);

        if (info->passedBeats > 0x200) {
            info->beenHit = TRUE;
            info->objAngle += agb_random(16);

            play_sound(&s_f_karate_kicks_kicks_miss_seqData);

            return FALSE;
        }

        if (info->passedBeats > 0x180) {
            if (!info->beenMissed) {
                info->beenMissed = TRUE;
                //joe->miss = ticks_to_frames(0x24);
            }
        }

        beatsOffset = info->passedBeats - 0x100;

        y = 81;
        y -= FIXED_TO_INT(FIXED_TO_INT(beatsOffset * beatsOffset * y));
        y = 53 - y;

        info->objXPosition = INT_TO_FIXED(fast_divsi3(
            INT_TO_FIXED(-30.0),
            info->passedBeats
        ) + SCREEN_CENTER_X);

        info->objYPosition = INT_TO_FIXED(fast_divsi3(
            INT_TO_FIXED(y),
            info->passedBeats
        ) + SCREEN_CENTER_Y);

        info->objYLandPosition = fast_divsi3(
            INT_TO_FIXED(53.0),
            info->passedBeats
        ) + SCREEN_CENTER_Y;

        info->objScale = (s16)Div(INT_TO_FIXED(256.0), info->passedBeats);

        if (info->objScale > 0x220) {
            info->objScale = 0x220;
        }
    }

    if (info->passedBeats < 0x80) {
        sprite_set_visible(gSpriteHandler, info->objSprite, FALSE);
        sprite_set_visible(gSpriteHandler, info->shadowSprite, FALSE);
    }

    sprite_set_x_y_z(gSpriteHandler,
        info->objSprite,
        FIXED_TO_INT(info->objXPosition),
        FIXED_TO_INT(info->objYPosition),
        info->objZPosition + info->passedBeats
    );
    sprite_set_x_y(gSpriteHandler,
        info->shadowSprite,
        FIXED_TO_INT(info->objXPosition), (s16)info->objYLandPosition
    );

    set_affine_scale_rotation(
        info->objAffineGroup,
        info->objScale, info->objAngle
    );
    set_affine_scale_rotation(
        info->shadowAffineGroup,
        info->objScale, 0
    );

    sprite_set_visible(gSpriteHandler, info->objSprite, TRUE);
    sprite_set_visible(gSpriteHandler, info->shadowSprite, TRUE);

    return FALSE;
}


void karate_kicks_cue_despawn(struct Cue *cue, struct KarateKicksCue *info) {
    sprite_delete(gSpriteHandler, info->objSprite);
    sprite_delete(gSpriteHandler, info->shadowSprite);
    func_080021b8(info->objAffineGroup);
    func_080021b8(info->shadowAffineGroup);
}


void karate_kicks_cue_hit(struct Cue *cue, struct KarateKicksCue *info, u32 pressed, u32 released) {
    struct KarateKicksJoe* joe = &gKarateKicks->joe;
    struct Animation* anim;

    if (released) {
        anim = anim_karate_kicks_joe_kick;
    } else {
        switch (info->type) {
            case KARATE_KICKS_OBJECT_POT:
            case KARATE_KICKS_OBJECT_BULB:
            default:
                anim = anim_karate_kicks_joe_jab;
                break;
        }
    }

    karate_kicks_joe_punch(joe, anim);

    info->beenHit = TRUE;
    info->hitObjXSpeed = -0x800;
    info->hitObjYSpeed = -0x200;
    info->objRotation = -0x10;
}


void karate_kicks_cue_barely(struct Cue *cue, struct KarateKicksCue *info, u32 pressed, u32 released) {
    struct KarateKicksJoe* joe = &gKarateKicks->joe;
    struct Animation* anim;

    if (released) {
        anim = anim_karate_kicks_joe_kick;
    } else {
        switch (info->type) {
            case KARATE_KICKS_OBJECT_POT:
            case KARATE_KICKS_OBJECT_BULB:
            default:
                anim = anim_karate_kicks_joe_jab;
                break;
        }
    }

    karate_kicks_joe_punch(joe, anim);

    info->beenHit = TRUE;
    info->hitObjXSpeed = -0x40;
    info->hitObjYSpeed = -0x200;
    info->hitObjYAcceleration = 0x20;
    info->objRotation = 4;
}


void karate_kicks_cue_miss(struct Cue *cue, struct KarateKicksCue *info) {}
