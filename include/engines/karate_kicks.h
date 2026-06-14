#pragma once

#include "global.h"
#include "engines.h"
#include "games/karate_kicks/graphics/karate_kicks_graphics.h"

enum KarateKicksObjectsEnum {
	KARATE_KICKS_OBJECT_POT,
	KARATE_KICKS_OBJECT_BULB,
	KARATE_KICKS_OBJECT_BARREL,
	KARATE_KICKS_OBJECT_BOMB,

	KARATE_KICKS_OBJECT_COUNT
};

struct KarateKicksEngineData {
	u8 version;
	u8 awaitingInput;

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
	u8 objRotation;

	s32 objYLandPosition;

	u32 hitObjXSpeed;
	u32 hitObjYSpeed;
	u32 hitObjXAcceleration;
	u32 hitObjYAcceleration;

	u16 passedBeats;
};

extern struct CompressedData* karate_kicks_buffered_textures[];
extern struct GraphicsTable* karate_kicks_gfx_tables[];

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
extern void karate_kicks_joe_sprite_callback(struct SpriteHandler *handler, s16 id, u32 arg);

extern void karate_kicks_wait_for_input();

extern void karate_kicks_input_event(u32 pressed, u32 released);

extern void karate_kicks_cue_spawn(struct Cue* cue, struct KarateKicksCue* info, u32 type);
extern u32 karate_kicks_cue_update(struct Cue* cue, struct KarateKicksCue* info, u32 runningTime, u32 duration);
extern void karate_kicks_cue_update_launched(struct KarateKicksCue* info);
extern void karate_kicks_cue_update_punched(struct KarateKicksCue* info);
extern void karate_kicks_cue_despawn(struct Cue* cue, struct KarateKicksCue* info);
extern void karate_kicks_cue_hit(struct Cue* cue, struct KarateKicksCue* info, u32 pressed, u32 released);
extern void karate_kicks_cue_barely(struct Cue* cue, struct KarateKicksCue* info, u32 pressed, u32 released);
extern void karate_kicks_cue_miss(struct Cue* cue, struct KarateKicksCue* info);
