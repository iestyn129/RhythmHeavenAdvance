#pragma once

#include "global.h"
#include "graphics.h"

/* GAMEPLAY - ANIMATIONS */

extern struct Animation anim_gameplay_pause_title[];
extern struct Animation anim_gameplay_pause_option1[];
extern struct Animation anim_gameplay_pause_option2[];
extern struct Animation anim_gameplay_skip_icon[];
extern struct Animation anim_gameplay_text_button_black[];
extern struct Animation anim_gameplay_text_button_white[];
extern struct Animation anim_gameplay_perfect_icon[];
extern struct Animation anim_gameplay_perfect_miss[];
extern struct Animation anim_gameplay_perfect_hit[];
extern struct Animation anim_gameplay_bar_idle[];
extern struct Animation anim_gameplay_bar_miss_L1[];
extern struct Animation anim_gameplay_bar_miss_L2[];
extern struct Animation anim_gameplay_bar_ok_L1[];
extern struct Animation anim_gameplay_bar_ok_L2[];
extern struct Animation anim_gameplay_bar_ok_L3[];
extern struct Animation anim_gameplay_bar_perfect[];
extern struct Animation anim_gameplay_bar_miss_R2[];
extern struct Animation anim_gameplay_bar_miss_R1[];
extern struct Animation anim_gameplay_bar_ok_R3[];
extern struct Animation anim_gameplay_bar_ok_R2[];
extern struct Animation anim_gameplay_bar_ok_R1[];

/* GAMEPLAY - COMPRESSED GRAPHICS */

extern struct CompressedData gameplay_obj;

/* GAMEPLAY - PALETTES */

extern Palette gameplay_obj_pal[];
