@ Load Data
.macro load_karate_kicks_labels
    @ Game Events
    .set WAIT_FOR_INPUT, 0x00
    .set START_LOOP, 0x01
    .set END_LOOP, 0x02
    .set SET_TARGET_SNOW_AMOUNT, 0x03
    .set SET_TARGET_SNOW_SPEED_X, 0x04
    .set SET_TARGET_SNOW_SPEED_Y, 0x05

    @ Cues
    .set CUE_POT, 0x00
    .set CUE_BULB, 0x01
    .set CUE_BARREL, 0x02
    .set CUE_BOMB, 0x03
    .set CUE_POT_OFF, 0x04
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

@ [Event 0x01]
.macro karate_kicks_start_loop
    karate_kicks_event START_LOOP, 0
.endm

@ [Event 0x02]
.macro karate_kicks_end_loop
    karate_kicks_event END_LOOP, 0
.endm

@ [Event 0x03]
.macro karate_kicks_set_target_snow_amount targetAmount
    karate_kicks_event SET_TARGET_SNOW_AMOUNT, \targetAmount
.endm

@ [Event 0x04]
.macro karate_kicks_set_target_snow_speed_x targetSpeedX
    karate_kicks_event SET_TARGET_SNOW_SPEED_X, \targetSpeedX
.endm

@ [Event 0x05]
.macro karate_kicks_set_target_snow_speed_y targetSpeedY
    karate_kicks_event SET_TARGET_SNOW_SPEED_Y, \targetSpeedY
.endm
