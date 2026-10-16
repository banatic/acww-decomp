/* A sprite of main drawn as two cell animations played together (vtable data_020e2330, 0x48
 * bytes, derived from main's screen sprite base, screen_sprite.h); the menu scenes' push
 * buttons (ov002/push_button.h) and the message window slider's indicator (mes_bg.h) build on
 * it.
 *
 * Its state picks the pair of animations of the table data_020d6fcc (from the entry of
 * data_020d0b64, the second the next entry), both held on their last frame: state 0 is not drawn
 * and not animated, state 1 is shown still, states 2 and 3 play. Vtable slot 2 draws it, slot 3
 * animates it. It is drawn at the base class's place plus `offset`, on the main screen or the
 * sub screen. */
#ifndef CLEAN_MAIN_DUAL_CELL_SPRITE_H
#define CLEAN_MAIN_DUAL_CELL_SPRITE_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum DualCellSpriteState {
    DUAL_CELL_SPRITE_HIDDEN = 0,
    DUAL_CELL_SPRITE_STILL = 1,
    DUAL_CELL_SPRITE_PLAY_A = 2, /* DualCellSprite_Travel measures it from the first frame */
    DUAL_CELL_SPRITE_PLAY_B = 3, /* and this one back to the first frame */
};

typedef struct DualCellSprite {
    ScreenSprite base; /* vtable data_020e2330, or a derived class's */
    int offset_x;      /* 0x0c: added to the base class's place */
    int offset_y;      /* 0x10 */
    CellAnim first;    /* 0x14 */
    CellAnim second;   /* 0x28 */
    int state;         /* 0x3c: DualCellSpriteState */
    u8 on_main;        /* 0x40: drawn on the main screen, else on the sub screen */
    u8 pad_41[3];
    int priority; /* 0x44: the OBJs' priority, -1 for the cells' own */
} DualCellSprite;

int DualCellSprite_IsDone(DualCellSprite *sprite);
int DualCellSprite_State(DualCellSprite *sprite);
void *DualCellSprite_SetState(DualCellSprite *sprite, int state);
void DualCellSprite_Travel(DualCellSprite *sprite, int *dx, int *dy);
void DualCellSprite_SetPriority(DualCellSprite *sprite, int priority);
void DualCellSprite_SetOffset(DualCellSprite *sprite, int x, int y);
void DualCellSprite_Update(DualCellSprite *sprite);
void DualCellSprite_Draw(DualCellSprite *sprite);
DualCellSprite *DualCellSprite_DestructCopy(DualCellSprite *sprite);
DualCellSprite *DualCellSprite_Delete(DualCellSprite *sprite);
DualCellSprite *DualCellSprite_Destruct(DualCellSprite *sprite);
DualCellSprite *DualCellSprite_Construct(DualCellSprite *sprite, char on_main);
void *DualCellSprite_ConstructCopy(DualCellSprite *sprite, int on_main);

#endif
