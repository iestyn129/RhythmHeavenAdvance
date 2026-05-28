#include "global.h"
#include "graphics.h"

#include "lockstep_anim_cells.inc.c"

struct Animation anim_lockstep_stepper_idle[] = {
    { lockstep_stepper_idle_cel, 24 },
    END_ANIMATION,
};

struct Animation anim_lockstep_stepper_shot_r[] = {
    { lockstep_stepper_shot_r_cel00, 3 },
    { lockstep_stepper_shot_r_cel01, 9 },
    { lockstep_stepper_shot_r_cel02, 1 },
    { lockstep_stepper_shot_r_cel03, 1 },
    { lockstep_stepper_idle_cel, 10 },
    END_ANIMATION,
};

struct Animation anim_lockstep_stepper_shot_l[] = {
    { lockstep_stepper_shot_l_cel00, 3 },
    { lockstep_stepper_shot_l_cel01, 9 },
    { lockstep_stepper_shot_l_cel02, 1 },
    { lockstep_stepper_shot_l_cel03, 1 },
    { lockstep_stepper_idle_cel, 10 },
    END_ANIMATION,
};
