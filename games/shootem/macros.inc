@ Load Data
.macro load_shootem_labels
    @ Game Events
    .set WAIT_FOR_INPUT, 0x00

    @ Cues
    @.set CUE, 0x00
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
