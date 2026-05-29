#pragma once

#include "global.h"
#include "graphics.h"

extern struct Animation anim_lockstep_stepper_idle[];
extern struct Animation anim_lockstep_stepper_beat[];
extern struct Animation anim_lockstep_stepper_shot_r[];
extern struct Animation anim_lockstep_stepper_shot_l[];
extern struct Animation anim_lockstep_crowd_idle[];
extern struct Animation anim_lockstep_crowd_beat[];
extern struct Animation anim_lockstep_crowd_shot_r[];
extern struct Animation anim_lockstep_crowd_shot_l[];

extern struct CompressedData lockstep_bg_tiles;
extern struct CompressedData lockstep_bg_map;
extern struct CompressedData lockstep_obj;
extern struct CompressedData lockstep_extra_obj;

extern Palette lockstep_obj_pal[];
extern Palette lockstep_bg_pal[];
