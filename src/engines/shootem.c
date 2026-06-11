#include "engines/shootem.h"

#include "syscall.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gShootem ((struct ShootemEngineData*)gCurrentEngineData)


void shootem_init_gfx3() {
    u16 i;
	func_0800c604(0);

    for (i = 0; i < 32; i++) {
        shootem_init_starfield_row(i);
    }

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


void shootem_init_starfield_row(u16 row) {
    TilemapEntry* starfieldTilemap = BG_MAP_BASE(29 * 0x800);
    const s32 count = ARRAY_COUNT(shootem_stars_tile_indexes);
    s32 i;

    if (row >= 32) {
        row &= 31;
    }

    row *= 32;

    for (i = row; i < (row + 32); i++) {
        starfieldTilemap[i] =
            TILEMAP_TILE_INDEX(shootem_stars_tile_indexes[agb_random(count)]) |
            TILEMAP_HFLIP(agb_random(2)) |
            TILEMAP_VFLIP(agb_random(2)) |
            TILEMAP_PALETTE(0);
    }
}


void shootem_engine_start(const u32 version) {
    gShootem->version = version;
    gShootem->awaitingInput = FALSE;
    gShootem->loopCounter = 0;
    gShootem->shootCooldown = 0;
    gShootem->nextCuePosIdx = 0;
    gShootem->cueBarelyDirection = 0;
    gShootem->starfieldOffset = 0;

    shootem_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, 0, 0, 28, BGCNT_PRIORITY(3));
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 5, 0, 0, 29, BGCNT_PRIORITY(2));
    scene_set_bg_layer_display(BG_LAYER_2, FALSE, 0, 0, 0, 30, BGCNT_PRIORITY(1));

    cannon_init(&gShootem->cannon);

    gameplay_set_input_buttons(A_BUTTON, 0);
}


void shootem_engine_stop() {
    cannon_delete(&gShootem->cannon);
    scene_hide_bg_layer(0);
    scene_hide_bg_layer(1);
    scene_hide_bg_layer(2);
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

    gShootem->starfieldOffset--;
    scene_set_bg_layer_pos(BG_LAYER_1, 5, gShootem->starfieldOffset);

    if (!(gShootem->starfieldOffset & 7)) {
        shootem_init_starfield_row(((gShootem->starfieldOffset & 0xFF) >> 3) + 20);
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

    cannon->laserSprite = sprite_create(gSpriteHandler,
        anim_shootem_laser_idle, 0,
        120, 80, 0x4A00,
        1, 0, 0
    );

    cannon->faceSprite = sprite_create(gSpriteHandler,
        anim_shootem_cannon_face, 0,
        120, 80, 0x4700,
        0, 0, 0
    );

    cannon->hurt = 0;
}


void cannon_delete(struct Cannon* cannon) {
    sprite_delete(gSpriteHandler, cannon->cannonSprite);
    sprite_delete(gSpriteHandler, cannon->faceSprite);
    sprite_delete(gSpriteHandler, cannon->laserSprite);
}


void cannon_update(struct Cannon* cannon) {
    s32 cannonOffset, time, count, pos, index, frac;
    s8 destCel;

    if (cannon->hurt != 0) {
        cannon->hurt--;

        if (cannon->hurt <= (SHOOTEM_HURT_LEN - 2)) {
            scene_hide_bg_layer(2);
        } else {
            scene_show_bg_layer(2);
        }

        time = FIXED_POINT_DIV(cannon->hurt, SHOOTEM_HURT_LEN);
        count = ARRAY_COUNT(shootem_cannon_hurt_offsets);

        if (time <= 0) {
            cannonOffset = shootem_cannon_hurt_offsets[0];
        } else if (time >= 0x100) {
            cannonOffset = shootem_cannon_hurt_offsets[count - 1];
        } else {
            pos = FIXED_POINT_MUL(time, INT_TO_FIXED(count - 1));
            index = FIXED_TO_INT(pos);
            frac = pos - INT_TO_FIXED(index);
            
            cannonOffset = FIXED_TO_INT(
                INT_TO_FIXED(shootem_cannon_hurt_offsets[index]) + FIXED_POINT_MUL(
                    INT_TO_FIXED(
                        shootem_cannon_hurt_offsets[index + 1] -
                        shootem_cannon_hurt_offsets[index]
                    ), frac
                )
            );
        }

        sprite_set_x_y(gSpriteHandler,
            cannon->cannonSprite, (s16)(120 + cannonOffset), 80
        );
        sprite_set_x_y(gSpriteHandler,
            cannon->faceSprite, (s16)(120 + cannonOffset), 80
        );

        if (cannon->hurt == 0) {
            destCel = 0;
        } else {
            destCel = 1;
        }

        sprite_set_anim_cel(gSpriteHandler, cannon->faceSprite, destCel);
    }
}


void cannon_shoot(const struct Cannon* cannon, u32 cooldown) {
    gShootem->shootCooldown = ticks_to_frames(cooldown);
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


void shootem_set_cue_pos(const u16 posIdx) {
    gShootem->nextCuePosIdx = posIdx;
}


void shootem_input_event(const u32 pressed, u32 released) {
    struct Cannon* cannon = &gShootem->cannon;

    cannon_shoot(cannon, 6);
}


void shootem_cue_spawn(struct Cue *cue, struct ShootemCue *info, u32 type) {
    s16 cueX, cueY, trajectoryScaleY, trajectoryRotation;

    info->type = type;
    info->posIdx = gShootem->nextCuePosIdx;

    cueX = shootem_cue_positions[info->posIdx][0];
    cueY = shootem_cue_positions[info->posIdx][1];
    trajectoryScaleY = shootem_cue_trajectories[info->posIdx][0][0];
    trajectoryRotation = shootem_cue_trajectories[info->posIdx][0][1];

    info->state = SHOOTEM_CUE_STATE_FAR;

    info->sprite = sprite_create(gSpriteHandler,
        shootem_cue_animations[info->type][info->state], 0,
        (s16)(120 + cueX), (s16)(80 + cueY), 0x4700,
        1, 0, 1
    );

    info->barelyXOffset = 0;
    info->barelyYOffset = 0;
    info->barelyXAcceleration = 0;
    info->barelyYAcceleration = 0;

    info->trajectoryAffineGroup = (s8)scene_affine_group_alloc();
    info->trajectorySprite = sprite_create(gSpriteHandler,
        anim_shootem_trajectory_hit, 0,
        (s16)(120 + cueX), (s16)(80 + cueY), 0x4800,
        1, 0x7f, 0
    );
    assign_sprite_affine_param(info->trajectorySprite, info->trajectoryAffineGroup);

    set_affine_stretch_rotation(info->trajectoryAffineGroup,
        0x100, trajectoryScaleY,
        trajectoryRotation
    );
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
                    info->sprite, shootem_cue_animations[info->type][info->state],
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
    sprite_delete(gSpriteHandler, info->trajectorySprite);
    func_080021b8(info->trajectoryAffineGroup);
}


void shootem_cue_hit(struct Cue *cue, struct ShootemCue *info, u32 pressed, u32 released) {
    s16 trajectoryScaleY, trajectoryRotation;
    struct Cannon* cannon = &gShootem->cannon;
    cannon_shoot(cannon, 4);

    info->state = SHOOTEM_CUE_STATE_HIT;

    sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->sprite, shootem_cue_animations[info->type][info->state],
        0, 1, 0x7f, 3
    );

    sprite_set_x_y(gSpriteHandler, info->trajectorySprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->trajectorySprite, anim_shootem_trajectory_hit,
        0, 1, 0x7f, 3
    );

    trajectoryScaleY = shootem_cue_trajectories[info->posIdx][1][0];
    trajectoryRotation = shootem_cue_trajectories[info->posIdx][1][1];

    set_affine_stretch_rotation(info->trajectoryAffineGroup,
        0x100, trajectoryScaleY,
        trajectoryRotation
    );
}


void shootem_cue_barely(struct Cue *cue, struct ShootemCue *info, u32 pressed, u32 released) {
    s16 trajectoryScaleY, trajectoryRotation;
    struct Cannon* cannon = &gShootem->cannon;
    cannon_shoot(cannon, 4);

    info->state = SHOOTEM_CUE_STATE_NEAR;
    sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->sprite, shootem_cue_animations[info->type][info->state],
        0, 1, 0x03, 2
    );

    sprite_set_x_y(gSpriteHandler, info->trajectorySprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->trajectorySprite, anim_shootem_trajectory_hit,
        0, 1, 0x7f, 3
    );

    trajectoryScaleY = shootem_cue_trajectories[info->posIdx][1][0];
    trajectoryRotation = shootem_cue_trajectories[info->posIdx][1][1];

    set_affine_stretch_rotation(info->trajectoryAffineGroup,
        0x100, trajectoryScaleY,
        trajectoryRotation
    );
}


void shootem_cue_miss(struct Cue *cue, struct ShootemCue *info) {
    struct Cannon* cannon = &gShootem->cannon;
    s16 trajectoryScaleY, trajectoryRotation;

    info->state = SHOOTEM_CUE_STATE_MISS;

    sprite_set_x_y(gSpriteHandler, info->sprite, 120, 64);
    sprite_set_anim(gSpriteHandler,
        info->sprite, shootem_cue_animations[info->type][info->state],
        0, 1, 0x7f, 3
    );

    sprite_set_anim(gSpriteHandler,
        info->trajectorySprite, anim_shootem_trajectory_miss,
        0, 1, 0x7f, 3
    );

    trajectoryScaleY = shootem_cue_trajectories[info->posIdx][2][0];
    trajectoryRotation = shootem_cue_trajectories[info->posIdx][2][1];

    set_affine_stretch_rotation(info->trajectoryAffineGroup,
        0x100, trajectoryScaleY,
        trajectoryRotation
    );

    cannon->hurt = SHOOTEM_HURT_LEN;
}
