@ Load Data
.macro load_shootem_labels
    @ Game Events
    .set WAIT_FOR_INPUT, 0x00
    .set START_LOOP, 0x01
    .set END_LOOP, 0x02
    .set SET_CUE_POS, 0x03

    @ Cues
    .set CUE_TARGET, 0x00
    .set CUE_ENEMY, 0x01
.endm


@ Load Game: Shoot-'em-up
.macro load_shootem
    load_shootem_labels
    load_game shootem_engine, 0
.endm


@ Run Game Event
.macro shootem_event event, args
    game_event shootem_engine, \event, \args
.endm

@ [Event 0x00]
.macro shootem_wait_for_input
    shootem_event WAIT_FOR_INPUT, 0
.endm

@ [Event 0x01]
.macro shootem_start_loop
    shootem_event START_LOOP, 0
.endm

@ [Event 0x02]
.macro shootem_end_loop
    shootem_event END_LOOP, 0
.endm

@ [Event 0x02]
.macro shootem_set_cue_pos pos_idx
    shootem_event SET_CUE_POS, \pos_idx
.endm

.macro shootem_spawn_cue_pos cue_idx, pos_idx
    shootem_set_cue_pos \pos_idx
    spawn_cue \cue_idx
.endm
