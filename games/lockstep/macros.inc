@ Load Data
.macro load_lockstep_labels
    @ Game Events
    .set WAIT_FOR_INPUT, 0x00
    .set BEAT_ANIM, 0x01
    .set FLIP_BG, 0x02

    @ Cues
    .set CUE_L, 0x00
    .set CUE_R, 0x01
.endm


@ Load Game: Lockstep
.macro load_lockstep
load_lockstep_labels
    load_game lockstep_engine, 0
.endm


@ Run Game Event
.macro lockstep_event event, args
    game_event lockstep_engine, \event, \args
.endm

@ [Event 0x00] wait for input
.macro lockstep_wait_for_input
    lockstep_event WAIT_FOR_INPUT, 0
.endm

@ [Event 0x01] beat anim
.macro lockstep_beat_anim play_sfx
    lockstep_event BEAT_ANIM, \play_sfx
.endm

@ [Event 0x02] flip bg
.macro lockstep_flip_bg
    lockstep_event FLIP_BG, 0
.endm
