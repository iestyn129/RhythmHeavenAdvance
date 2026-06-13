@ Load Data
.macro load_karate_kicks_labels
    @ Game Events
    .set WAIT_FOR_INPUT, 0x00

    @ Cues
    .set CUE_POT, 0x00
    .set CUE_BULB, 0x01
.endm


@ Load Game: Karate Man Kicks!
.macro load_karate_kicks
    load_karate_kicks_labels
    load_game karate_kicks_engine, 0
.endm


@ Run Game Event
.macro karate_kicks_event event, args
    game_event karate_kicks_engine, \event, \args
.endm

@ [Event 0x00]
.macro karate_kicks_wait_for_input
    karate_kicks_event WAIT_FOR_INPUT, 0
.endm
