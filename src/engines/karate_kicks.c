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

    gameplay_set_input_buttons(A_BUTTON | B_BUTTON, A_BUTTON);
}


void karate_kicks_engine_stop() {
    karate_kicks_joe_delete(&gKarateKicks->joe);
    scene_hide_bg_layer(0);
}


void karate_kicks_engine_update() {
    if (D_03004afc & SELECT_BUTTON) {
        if (gKarateKicks->awaitingInput) {
            gameplay_set_input_buttons(A_BUTTON | B_BUTTON, A_BUTTON);
            set_pause_beatscript_scene(FALSE);
            gKarateKicks->awaitingInput = FALSE;
        }
    }

    karate_kicks_joe_update(&gKarateKicks->joe);
}


void karate_kicks_joe_init(struct KarateKicksJoe* joe) {
    joe->sprite = sprite_create(gSpriteHandler,
        anim_karate_kicks_joe_ready, 0,
        160, 88, 0x4800,
        1, 0x7f, 0
    );

    sprite_set_base_palette(gSpriteHandler, joe->sprite, 2);
    sprite_set_callback(gSpriteHandler, joe->sprite, karate_kicks_joe_sprite_callback, (u32)joe);

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
        sprite_set_anim(gSpriteHandler,
            joe->sprite, anim_karate_kicks_joe_jab, 0,
            1, 0x7f, 4
        );
        play_sound(&s_f_karate_kicks_punch_seqData);

        joe->chargeTimer = ticks_to_frames(14);
    }

    if (pressed & B_BUTTON) {
        sprite_set_anim(gSpriteHandler,
            joe->sprite, anim_karate_kicks_joe_punch, 0,
            1, 0x7f, 4
        );
        play_sound(&s_f_karate_kicks_punch_seqData);
    }

    if (released & A_BUTTON) {
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
    }
}


void karate_kicks_cue_spawn(struct Cue *cue, struct KarateKicksCue *info, u32 type) {
    info->type = type;
}


u32 karate_kicks_cue_update(struct Cue *cue, struct KarateKicksCue *info, u32 runningTime, u32 duration) {
    return FALSE;//sprite_is_invalid(gSpriteHandler, info->sprite);
}


void karate_kicks_cue_despawn(struct Cue *cue, struct KarateKicksCue *info) {}


void karate_kicks_cue_barely(struct Cue *cue, struct KarateKicksCue *info, u32 pressed, u32 released) {}


void karate_kicks_cue_miss(struct Cue *cue, struct KarateKicksCue *info) {}
