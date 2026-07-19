#include "engines/cars.h"

#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/scenes/gameplay.h"

#define gCars ((struct CarsEngineData*)gCurrentEngineData)


void cars_init_gfx3() {
	func_0800c604(0);
	gameplay_start_screen_fade_in();
}


void cars_init_gfx2() {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), cars_gfx_tables[gCars->version], 0x2000);
    run_func_after_task(temp, cars_init_gfx3, 0);
}


void cars_init_gfx1() {
    u32 temp;

    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), cars_buffered_textures);
    run_func_after_task(temp, cars_init_gfx2, 0);
}


void cars_engine_start(const u32 version) {
    gCars->version = version;

    cars_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, 0, 0, 28, BGCNT_PRIORITY(3));
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(2));

    revlino_init(&gCars->revRed, anim_cars_revlino_red, 0, 27);
    revlino_init(&gCars->revGrey, anim_cars_revlino_grey, -76, 27);
    revlino_init(&gCars->revBlue, anim_cars_revlino_blue, 76, 27);

    gameplay_set_input_buttons(A_BUTTON | DPAD_DOWN, 0);
}


void cars_engine_stop() {
    revlino_delete(&gCars->revRed);

    scene_hide_bg_layer(0);
    scene_hide_bg_layer(1);
}


void cars_engine_update() {
    revlino_update(&gCars->revRed);
}


void revlino_init(struct Revlino* revlino, struct Animation* anim, s16 offsetX, s16 offsetY) {
    revlino->offsetX = offsetX;
    revlino->offsetY = offsetY;

    revlino->carSprite = sprite_create(gSpriteHandler,
        anim, 0,
        (s16)(120 + revlino->offsetX), (s16)(80 + revlino->offsetY), 0x4900,
        1, 0, 0
    );

    revlino->wheelLSprite = sprite_create(gSpriteHandler,
        anim_cars_wheel, 0,
        (s16)(104 + revlino->offsetX), (s16)(93 + revlino->offsetY), 0x4800,
        1, 0, 0
    );
    revlino->wheelRSprite = sprite_create(gSpriteHandler,
        anim_cars_wheel, 0,
        (s16)(136 + revlino->offsetX), (s16)(93 + revlino->offsetY), 0x4800,
        1, 0, 0
    );
}


void revlino_delete(struct Revlino* revlino) {
    sprite_delete(gSpriteHandler, revlino->carSprite);
    sprite_delete(gSpriteHandler, revlino->wheelLSprite);
    sprite_delete(gSpriteHandler, revlino->wheelRSprite);
}


void revlino_update(struct Revlino* revlino) {}


void cars_input_event(const u32 pressed, u32 released) {}
