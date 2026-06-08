#pragma once

#include "global.h"
#include "graphics.h"

extern struct Animation anim_shootem_cannon_idle[];
extern struct Animation anim_shootem_cannon_shoot[];
extern struct Animation anim_shootem_cannon_face[];
extern struct Animation anim_shootem_laser_idle[];
extern struct Animation anim_shootem_laser_shoot[];

extern struct Animation anim_shootem_cue_target_idle[];
extern struct Animation anim_shootem_cue_target_hit[];
extern struct Animation anim_shootem_cue_target_barely[];
extern struct Animation anim_shootem_cue_target_miss[];

extern struct CompressedData shootem_bg_tiles;
extern struct CompressedData shootem_bg_map;
extern struct CompressedData shootem_obj;

extern Palette shootem_obj_pal[];
extern Palette shootem_bg_pal[];
