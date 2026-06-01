#pragma once

#include "global.h"
#include "cues.h"

#define QBAR_MEM_ID 17
#define QBAR_BASE_TILE 948
#define QBAR_BASE_PALETTE 13

struct QBarData {
	u8 isShowing;
	s16 barCueSprite;
	s16 barMarkSprite;
};

extern void qbar_init(struct QBarData* qbarData);
extern void qbar_init_gfx(struct QBarData* qbarData);
extern void qbar_delete(struct QBarData* qbarData);
extern void qbar_update(struct QBarData* qbarData, struct Cue* cues);
extern void qbar_check_gfx(struct QBarData* qbarData);

extern void qbar_show_bar(struct QBarData* qbarData, u8 showBar);
extern void qbar_set_marking_criteria(struct QBarData* qbarData, u32 criteria);
extern void qbar_set_cue(struct QBarData* qbarData, struct Cue* cue);
