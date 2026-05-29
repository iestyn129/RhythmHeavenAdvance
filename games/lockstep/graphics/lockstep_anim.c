#include "global.h"
#include "graphics.h"

#include "lockstep_anim_cells.inc.c"

struct Animation anim_lockstep_stepper_idle[] = {
    { lockstep_stepper_idle_cel, 24 },
    END_ANIMATION
};

struct Animation anim_lockstep_stepper_beat[] = {
    { lockstep_stepper_beat_cel00, 8 },
    { lockstep_stepper_beat_cel01, 2 },
    { lockstep_stepper_beat_cel02, 4 },
    { lockstep_stepper_beat_cel03, 10 },
    END_ANIMATION
};

struct Animation anim_lockstep_stepper_shot_r[] = {
    { lockstep_stepper_shot_r_cel00, 3 },
    { lockstep_stepper_shot_r_cel01, 9 },
    { lockstep_stepper_shot_r_cel02, 1 },
    { lockstep_stepper_shot_r_cel03, 1 },
    { lockstep_stepper_idle_cel, 10 },
    END_ANIMATION
};

struct Animation anim_lockstep_stepper_shot_l[] = {
    { lockstep_stepper_shot_l_cel00, 3 },
    { lockstep_stepper_shot_l_cel01, 9 },
    { lockstep_stepper_shot_l_cel02, 1 },
    { lockstep_stepper_shot_l_cel03, 1 },
    { lockstep_stepper_idle_cel, 10 },
    END_ANIMATION
};

struct Animation anim_lockstep_stepper_miss_r[] = {
    { lockstep_stepper_miss_r_cel00, 4 },
    { lockstep_stepper_miss_r_cel01, 20 },
    END_ANIMATION
};

struct Animation anim_lockstep_stepper_miss_l[] = {
    { lockstep_stepper_miss_l_cel00, 4 },
    { lockstep_stepper_miss_l_cel01, 20 },
    END_ANIMATION
};


struct Animation anim_lockstep_crowd_idle[] = {
    { lockstep_crowd_idle_cel, 24 },
    END_ANIMATION
};

struct Animation anim_lockstep_crowd_beat[] = {
    { lockstep_crowd_beat_cel00, 8 },
    { lockstep_crowd_beat_cel01, 2 },
    { lockstep_crowd_beat_cel02, 4 },
    { lockstep_crowd_beat_cel03, 10 },
    END_ANIMATION
};

struct Animation anim_lockstep_crowd_shot_r[] = {
    { lockstep_crowd_shot_r_cel00, 3 },
    { lockstep_crowd_shot_r_cel01, 9 },
    { lockstep_crowd_shot_r_cel02, 1 },
    { lockstep_crowd_shot_r_cel03, 1 },
    { lockstep_crowd_idle_cel, 10 },
    END_ANIMATION
};

struct Animation anim_lockstep_crowd_shot_l[] = {
    { lockstep_crowd_shot_l_cel00, 3 },
    { lockstep_crowd_shot_l_cel01, 9 },
    { lockstep_crowd_shot_l_cel02, 1 },
    { lockstep_crowd_shot_l_cel03, 1 },
    { lockstep_crowd_idle_cel, 10 },
    END_ANIMATION
};
