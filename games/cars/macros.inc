@ Load Data
.macro load_cars_labels
    @ Game Events
    @.set WAIT_FOR_INPUT, 0x00

    @ Cues
    @.set CUE_POT, 0x00
.endm


@ Load Game: Stop N Go N Stop
.macro load_cars
    load_cars_labels
    load_game cars_engine, 0
.endm


@ Run Game Event
.macro cars_event event, args
    game_event cars_engine, \event, \args
.endm

@ [Event 0x00]
@.macro cars_wait_for_input
@    cars_event WAIT_FOR_INPUT, 0
@.endm
