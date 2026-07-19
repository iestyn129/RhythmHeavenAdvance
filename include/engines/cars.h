#pragma once

#include "global.h"
#include "engines.h"
#include "games/cars/graphics/cars_graphics.h"

struct CarsEngineData {
	u8 version;

	struct Revlino {
		s16 carSprite;
		s16 wheelLSprite;
		s16 wheelRSprite;

		s16 offsetX;
		s16 offsetY;
	} revRed;
	struct Revlino revGrey;
	struct Revlino revBlue;
};

extern struct CompressedData* cars_buffered_textures[];
extern struct GraphicsTable* cars_gfx_tables[];

extern void cars_init_gfx3();
extern void cars_init_gfx2();
extern void cars_init_gfx1();

extern void cars_engine_start(u32 version);
extern void cars_engine_stop();
extern void cars_engine_update();

extern void revlino_init(struct Revlino* revlino, struct Animation* anim, s16 offsetX, s16 offsetY);
extern void revlino_delete(struct Revlino* revlino);
extern void revlino_update(struct Revlino* revlino);

extern void cars_input_event(u32 pressed, u32 released);
