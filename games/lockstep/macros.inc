@ Load Data
.macro load_lockstep_labels
    @ Game Events
    .set WAIT_FOR_INPUT, 0x00

    @ Cues
    @.set CUE_CUE, 0x00
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

@ [Event 0x00] Event
.macro lockstep_wait_for_input
    lockstep_event WAIT_FOR_INPUT, 0
.endm
