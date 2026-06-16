#pragma once

#include "global.h"
#include "engines.h"
#include "games/karate_kicks/graphics/karate_kicks_graphics.h"

#define KARATE_KICKS_NUM_BARREL_PARTS 9

enum KarateKicksObjectsEnum {
	KARATE_KICKS_OBJECT_POT,
	KARATE_KICKS_OBJECT_BULB,
	KARATE_KICKS_OBJECT_BARREL,
	KARATE_KICKS_OBJECT_BOMB,

	KARATE_KICKS_OBJECT_COUNT
};

enum KarateKicksBarrelPartsEnum {
	KARATE_KICKS_BARREL_PART_HEAD,
	KARATE_KICKS_BARREL_PART_HOOP,
	KARATE_KICKS_BARREL_PART_STAVE
};

struct KarateKicksEngineData {
	u8 version;
	u8 awaitingInput;
	u16 loopCounter;

	struct KarateKicksJoe {
		s16 sprite;

		u8 skipBeat;
		u16 chargeTimer;
		u8 isCharged;
	} joe;
};

struct KarateKicksCue {
	u32 type;
	u8 beenHit;
	u8 beenBarelied;
	u8 beenMissed;

	s8 objAffineGroup;
	s16 objSprite;
	s8 shadowAffineGroup;
	s16 shadowSprite;

	s32 objXPosition;
	s32 objYPosition;
	s16 objZPosition;

	s16 objScale;
	s8 objAngle;
	s8 objRotation;

	s32 objYLandPosition;

	s32 hitObjXSpeed;
	s32 hitObjYSpeed;
	s32 hitObjXAcceleration; // i know acceleration is a vector quantity, but there's no equivalent word for
	s32 hitObjYAcceleration; // its scalar form in the english language, and these are long enough already

	u16 passedBeats;

	struct KarateKicksBarrelPart {
		s8 affineGroup;
		s16 sprite;

		s32 xPosition;
		s32 yPosition;

		s32 xSpeed;
		s32 ySpeed;

		s8 angle;
		s8 rotation;
	} barrelParts[KARATE_KICKS_NUM_BARREL_PARTS];
};

extern struct CompressedData* karate_kicks_buffered_textures[];
extern struct GraphicsTable* karate_kicks_gfx_tables[];

extern s32 karate_kicks_barrel_part_defaults[KARATE_KICKS_NUM_BARREL_PARTS][7];

extern void karate_kicks_init_gfx3();
extern void karate_kicks_init_gfx2();
extern void karate_kicks_init_gfx1();

extern void karate_kicks_engine_start(u32 version);
extern void karate_kicks_engine_stop();
extern void karate_kicks_engine_update();

extern void karate_kicks_common_beat_animation();

extern void karate_kicks_joe_init(struct KarateKicksJoe* joe);
extern void karate_kicks_joe_delete(struct KarateKicksJoe* joe);
extern void karate_kicks_joe_update(struct KarateKicksJoe* joe);
extern void karate_kicks_joe_punch(struct KarateKicksJoe* joe, struct Animation* anim);
extern u8 karate_kicks_joe_kick(struct KarateKicksJoe* joe);
extern void karate_kicks_joe_set_palette(struct KarateKicksJoe* joe, s8 basePalette);
extern void karate_kicks_joe_sprite_callback(struct SpriteHandler *handler, s16 id, u32 arg);

extern void karate_kicks_wait_for_input();
extern void karate_kicks_start_loop();
extern void karate_kicks_end_loop();

extern void karate_kicks_input_event(u32 pressed, u32 released);

extern void karate_kicks_cue_spawn(struct Cue* cue, struct KarateKicksCue* info, u32 type);
extern u32 karate_kicks_cue_update(struct Cue* cue, struct KarateKicksCue* info, u32 runningTime, u32 duration);
extern void karate_kicks_cue_update_physics(struct KarateKicksCue* info);
extern void karate_kicks_cue_update_launched(struct KarateKicksCue* info);
extern void karate_kicks_cue_despawn(struct Cue* cue, struct KarateKicksCue* info);
extern void karate_kicks_cue_hit(struct Cue* cue, struct KarateKicksCue* info, u32 pressed, u32 released);
extern void karate_kicks_cue_barely(struct Cue* cue, struct KarateKicksCue* info, u32 pressed, u32 released);
extern void karate_kicks_cue_pressed(struct Cue* cue, struct KarateKicksCue* info, u32 pressed);
extern u8 karate_kicks_cue_released(struct Cue* cue, struct KarateKicksCue* info, u32 released);
extern void karate_kicks_cue_spawn_bomb(struct Cue* cue, struct KarateKicksCue* info);
extern void karate_kicks_cue_miss(struct Cue* cue, struct KarateKicksCue* info);

extern void karate_kicks_cue_barrel_parts_init(struct KarateKicksBarrelPart* parts);
extern void karate_kicks_cue_barrel_parts_spawn(struct KarateKicksBarrelPart* parts, s32 baseX, s32 baseY);
extern void karate_kicks_cue_barrel_parts_update(struct KarateKicksBarrelPart* parts, u32 zPosition);
extern void karate_kicks_cue_barrel_parts_delete(struct KarateKicksBarrelPart* parts);
