#pragma once

#include "global.h"
#include "graphics.h"

extern struct Animation anim_lockstep_stepper_idle_z00[];
extern struct Animation anim_lockstep_stepper_beat_z00[];
extern struct Animation anim_lockstep_stepper_shot_r_z00[];
extern struct Animation anim_lockstep_stepper_shot_l_z00[];
extern struct Animation anim_lockstep_stepper_miss_r_z00[];
extern struct Animation anim_lockstep_stepper_miss_l_z00[];

extern struct Animation anim_lockstep_crowd_idle_zP[];
extern struct Animation anim_lockstep_crowd_beat_zP[];
extern struct Animation anim_lockstep_crowd_shot_r_zP[];
extern struct Animation anim_lockstep_crowd_shot_l_zP[];

extern struct Animation anim_lockstep_crowd_idle_z00[];
extern struct Animation anim_lockstep_crowd_beat_z00[];
extern struct Animation anim_lockstep_crowd_shot_r_z00[];
extern struct Animation anim_lockstep_crowd_shot_l_z00[];

extern struct CompressedData lockstep_bg_tiles;
extern struct CompressedData lockstep_bg_map;
extern struct CompressedData lockstep_obj;
extern struct CompressedData lockstep_extra_obj;

extern Palette lockstep_obj_pal[];
extern Palette lockstep_bg_pal[];
