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
    gShootem->loopCounter = 0;
    gShootem->shootCooldown = 0;
    gShootem->cueX = 0;
    gShootem->cueY = 0;
    gShootem->cueBarelyDirection = 0;

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
    if (D_03004afc & SELECT_BUTTON) {
        gShootem->loopCounter++;

        if (gShootem->awaitingInput) {
            gameplay_set_input_buttons(A_BUTTON, 0);
            set_pause_beatscript_scene(FALSE);
            gShootem->awaitingInput = FALSE;
        }
    }

    if (gShootem->shootCooldown != 0) {
        gShootem->shootCooldown--;
        if (gShootem->shootCooldown == 0 && !gShootem->awaitingInput) {
            gameplay_set_input_buttons(A_BUTTON, 0);
        }
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
        120, 80, 0x4A00,
        1, 0, 0
    );
}


void cannon_delete(struct Cannon* cannon) {
    sprite_delete(gSpriteHandler, cannon->cannonSprite);
    sprite_delete(gSpriteHandler, cannon->faceSprite);
    sprite_delete(gSpriteHandler, cannon->laserSprite);
}


void cannon_update(struct Cannon* cannon) {}


void cannon_shoot(const struct Cannon* cannon) {
    gShootem->shootCooldown = ticks_to_frames(4);
    gameplay_set_input_buttons(0, 0);

    sprite_set_anim(gSpriteHandler,
        cannon->cannonSprite, anim_shootem_cannon_shoot,
        0, 1, 0x7f, 0
    );
    sprite_set_anim(gSpriteHandler,
        cannon->laserSprite, anim_shootem_laser_shoot,
        0, 1, 0x7f, 0
    );

    play_sound(&s_f_shootem_shot_seqData);
}


void shootem_wait_for_input() {
    gameplay_set_input_buttons(0, 0);
    set_pause_beatscript_scene(TRUE);

    gShootem->awaitingInput = TRUE;
}


void shootem_start_loop() {
    gShootem->loopCounter = 0;
}


void shootem_end_loop() {
    if (gShootem->loopCounter == 0) {
        beatscript_enable_loops();
    }
}


void shootem_set_cue_pos(const u16 pos_idx) {
    gShootem->cueX = shootem_cue_positions[pos_idx][0];
    gShootem->cueY = shootem_cue_positions[pos_idx][1];
}


void shootem_input_event(const u32 pressed, u32 released) {
    struct Cannon* cannon = &gShootem->cannon;

    cannon_shoot(cannon);
}


void shootem_cue_spawn(struct Cue *cue, struct ShootemCue *info, u32 type) {
    info->type = type;
    info->sprite = sprite_create(gSpriteHandler,
        anim_shootem_cue_target_idle, 0,
        (s16)(120 + gShootem->cueX), (s16)(80 + gShootem->cueY), 0x4700,
        1, 0, 1
    );

    info->state = SHOOTEM_CUE_STATE_FAR;
    info->barelyXOffset = 0;
    info->barelyYOffset = 0;
    info->barelyXAcceleration = 0;
    info->barelyYAcceleration = 0;
}


u32 shootem_cue_update(struct Cue *cue, struct ShootemCue *info, u32 runningTime, u32 duration) {
    s32 cueX, cueY;

    switch (info->state) {
        case SHOOTEM_CUE_STATE_NEAR:
            if (sprite_get_anim_cel(gSpriteHandler, info->sprite) == 0x03) {
                info->state = SHOOTEM_CUE_STATE_BARELY;

                info->barelyXAcceleration = 0x20;
                info->barelyYAcceleration = 0x14;

                if (gShootem->cueBarelyDirection) {
                    info->barelyXAcceleration *= -1;
                }

                sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
                sprite_set_anim(gSpriteHandler,
                    info->sprite, anim_shootem_cue_target_barely,
                    0, 1, 0x7f, 3
                );

                gShootem->cueBarelyDirection = !gShootem->cueBarelyDirection;
            }

            break;
        case SHOOTEM_CUE_STATE_BARELY:
            cueX = info->barelyXOffset + INT_TO_FIXED(sprite_get_x(gSpriteHandler, info->sprite));
            cueY = info->barelyYOffset + INT_TO_FIXED(sprite_get_y(gSpriteHandler, info->sprite));

            sprite_set_x_y(gSpriteHandler,
                info->sprite, FIXED_TO_INT(cueX), FIXED_TO_INT(cueY)
            );

            info->barelyXOffset += info->barelyXAcceleration;
            info->barelyYOffset += info->barelyYAcceleration;
        default:
            break;
    }

    return sprite_is_invalid(gSpriteHandler, info->sprite);
}


void shootem_cue_despawn(struct Cue *cue, struct ShootemCue *info) {
    sprite_delete(gSpriteHandler, info->sprite);
}


void shootem_cue_hit(struct Cue *cue, struct ShootemCue *info, u32 pressed, u32 released) {
    struct Cannon* cannon = &gShootem->cannon;
    cannon_shoot(cannon);

    info->state = SHOOTEM_CUE_STATE_HIT;
    sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->sprite, anim_shootem_cue_target_hit,
        0, 1, 0x7f, 3
    );
}


void shootem_cue_barely(struct Cue *cue, struct ShootemCue *info, u32 pressed, u32 released) {
    struct Cannon* cannon = &gShootem->cannon;
    cannon_shoot(cannon);

    info->state = SHOOTEM_CUE_STATE_NEAR;
    sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->sprite, anim_shootem_cue_target_near,
        0, 1, 0x03, 2
    );
}


void shootem_cue_miss(struct Cue *cue, struct ShootemCue *info) {
    info->state = SHOOTEM_CUE_STATE_MISS;
    sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->sprite, anim_shootem_cue_target_miss,
        0, 1, 0x7f, 3
    );
}
