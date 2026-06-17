@ Load Data
.macro load_glee_labels
    @ Game Events
    @.set WAIT_FOR_INPUT, 0x00

    @ Cues
    @.set CUE_POT, 0x00
.endm


@ Load Game: Glee CLub
.macro load_glee
    load_glee_labels
    load_game glee_engine, 0
.endm


@ Run Game Event
.macro glee_event event, args
    game_event glee_engine, \event, \args
.endm

@ [Event 0x00]
@.macro glee_wait_for_input
@    glee_event WAIT_FOR_INPUT, 0
@.endm
