#include "qbar.h"
#include "graphics/qbar/qbar_graphics.h"

#include "code_08001360.h"
#include "lib_0804ca80.h"


void qbar_init(struct QBarData* qbarData) {
	qbarData->isShowing = FALSE;
	qbar_init_gfx(qbarData);
}

void qbar_init_gfx(struct QBarData* qbarData) {
	u32 memID;

	dma3_set(
		qbar_obj_raw_4bpp, OBJ_TILESET_BASE(0x20 * QBAR_BASE_TILE),
		0x180, 0x10, 0x200
	);
	dma3_set(
		qbar_pal, OBJ_PALETTE_BUFFER(QBAR_BASE_PALETTE),
		0x20, 0x10, 0x200
	);

	memID = sprite_handler_get_mem_id(gSpriteHandler);
	sprite_handler_set_mem_id(gSpriteHandler, QBAR_MEM_ID);

	qbarData->barCueSprite = sprite_create(gSpriteHandler,
		anim_qbar_cue, 0,
		120, 80, 0x50,
		0, 0, 0x8000
	);

	qbarData->barMarkSprite = sprite_create(gSpriteHandler,
		anim_qbar_mark_blank, 0,
		120, 80, 0x50,
		1, 0, 0x8000
	);

	sprite_id_set_base_tile(gSpriteHandler, QBAR_MEM_ID, QBAR_BASE_TILE);
	sprite_id_set_base_palette(gSpriteHandler, QBAR_MEM_ID, QBAR_BASE_PALETTE);
	sprite_handler_set_mem_id(gSpriteHandler, memID);
}

void qbar_delete(struct QBarData* qbarData) {
	sprite_id_delete(gSpriteHandler, QBAR_MEM_ID);
}

void qbar_update(struct QBarData* qbarData, struct Cue* cues) {
    struct Cue* cue, *prev, *nearest = NULL;

	if (!qbarData->isShowing) {
		return;
	}

	cue = cues;
	while (cue != NULL) {
		prev = cue->prev;

		if (nearest == NULL || ABS(CUE_HIT_OFFSET(cue)) < ABS(CUE_HIT_OFFSET(nearest))) {
			nearest = cue;
		}

		cue = prev;
	}

	if (nearest != NULL) {
		qbar_set_cue(qbarData, nearest);
	}
}


void qbar_check_gfx(struct QBarData* qbarData) {
	u32 i;

	for (i = 0; i < 0x20; i++) {
		if (qbar_obj_raw_4bpp[i] != ((volatile u8*)OBJ_TILESET_BASE(0x20 * QBAR_BASE_TILE))[i]) {
			qbar_init_gfx(qbarData);
			break;
		}
	}
}


void qbar_show_bar(struct QBarData* qbarData, const u8 showBar) {
	qbarData->isShowing = showBar;

	if (qbarData->isShowing) {
		qbar_init_gfx(qbarData);
	}

	sprite_set_visible(gSpriteHandler, qbarData->barCueSprite, qbarData->isShowing);
	sprite_set_visible(gSpriteHandler, qbarData->barMarkSprite, qbarData->isShowing);
}

void qbar_set_marking_criteria(struct QBarData* qbarData, const u32 criteria) {
	struct Animation* anim;

	if (!qbarData->isShowing) {
		return;
	}

	qbar_check_gfx(qbarData);

	switch (criteria) {
		case 0:
			anim = anim_qbar_mark_0;
			break;
		case 1:
			anim = anim_qbar_mark_1;
			break;
		case 2:
			anim = anim_qbar_mark_2;
			break;
		case 3:
			anim = anim_qbar_mark_3;
			break;
		default:
			anim = anim_qbar_mark_overflow;
			break;
	}

	sprite_set_anim(gSpriteHandler,
		qbarData->barMarkSprite, anim,
		0, 1, 0x7f, 0
	);
}


void qbar_set_cue(struct QBarData* qbarData, struct Cue* cue) {
	const s32 cueOffset = CUE_HIT_OFFSET(cue);// + 1;
	s8 destCel = 0;

	if (!qbarData->isShowing) {
		return;
	}

	qbar_check_gfx(qbarData);

	if (cueOffset <= 5 && cueOffset >= -5) {
		destCel = (s8)(cueOffset + 6);
	}

	//*(volatile u32*)(ExternWorkRAMBase + 0x3FFE0) = destCel;
	//*(volatile u32*)(ExternWorkRAMBase + 0x3FFF0) = cueOffset;

	sprite_set_anim_cel(gSpriteHandler, qbarData->barCueSprite, destCel);
}
