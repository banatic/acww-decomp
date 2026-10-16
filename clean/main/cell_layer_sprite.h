/* A sprite of main drawn as a cell animation with an optional second layer (vtable
 * data_020e2314, 0x4c bytes, derived from main's screen sprite base, screen_sprite.h); the menu
 * scenes' gliders (ov002/glide.h), the message window's marker (mes_bg.h) and the cursors of
 * the pockets screens build on it.
 *
 * Its animation number picks the pair of animations of the table data_020d6fcc (from the entry
 * of data_020d0b08, the second layer the next entry), whether the second layer is shown
 * (data_020d0ae0) and whether they loop (data_020d0af4; otherwise they hold their last frame).
 * Animation 0 is not drawn and not animated. Vtable slot 2 draws it, slot 3 animates it.
 *
 * It is drawn at the base class's place plus `offset`, on the main screen or the sub screen,
 * and when `window` is set drawn again as OBJ window. */
#ifndef CLEAN_MAIN_CELL_LAYER_SPRITE_H
#define CLEAN_MAIN_CELL_LAYER_SPRITE_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

#define CELL_LAYER_SPRITE_NONE 0

typedef struct CellLayerSprite {
    ScreenSprite base; /* vtable data_020e2314, or a derived class's */
    CellAnim anim;     /* 0x0c */
    int offset_x;      /* 0x20: added to the base class's place */
    int offset_y;      /* 0x24 */
    int priority;      /* 0x28: the OBJs' priority, -1 for the cells' own */
    CellAnim layer2;   /* 0x2c: the second layer, played when `has_layer2` */
    int anim_number;   /* 0x40: CELL_LAYER_SPRITE_NONE or the animation shown */
    int unk_44;        /* 0x44: 0x16 from the constructor; not read by this class */
    u8 on_main;        /* 0x48: drawn on the main screen, else on the sub screen */
    u8 has_layer2;     /* 0x49 */
    u8 window;         /* 0x4a: also drawn as OBJ window */
    u8 pad_4b;
} CellLayerSprite;

int CellLayerSprite_IsDone(CellLayerSprite *sprite);
int CellLayerSprite_AnimNumber(CellLayerSprite *sprite);
void CellLayerSprite_SetAnimAtEnd(CellLayerSprite *sprite, int number);
void CellLayerSprite_SetAnim(CellLayerSprite *sprite, int number);
void CellLayerSprite_SetOffset(CellLayerSprite *sprite, int x, int y);
void CellLayerSprite_ClearWindow(CellLayerSprite *sprite);
void CellLayerSprite_SetWindow(CellLayerSprite *sprite);
void CellLayerSprite_Update(CellLayerSprite *sprite);
void CellLayerSprite_Draw(CellLayerSprite *sprite);
CellLayerSprite *CellLayerSprite_DestructCopy(CellLayerSprite *sprite);
CellLayerSprite *CellLayerSprite_Delete(CellLayerSprite *sprite);
CellLayerSprite *CellLayerSprite_Destruct(CellLayerSprite *sprite);
void *CellLayerSprite_ConstructCopy(CellLayerSprite *sprite, u8 on_main);
void *CellLayerSprite_Construct(CellLayerSprite *sprite, u8 on_main);

#endif
