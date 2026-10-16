/* A sprite of main drawn as two cell animations at one place (vtable data_020e2058, 0x44
 * bytes; constructed by CellPairSprite_Construct). It derives from main's screen sprite base
 * (vtable data_020e20c8, constructor func_0208af30, destructor func_0208af00), whose place is
 * kept relative to the screen's centre (0x80, 0x60).
 *
 * Its pose picks the pair of animations: pose 0 is not drawn and not animated; the pair comes
 * from the animation table data_020d6fcc (from the entry of data_020d0a44, six entries further
 * on in the alternate set) and is held on its last frame in the poses data_020d0a34 says.
 * Vtable slot 2 draws it, slot 3 animates it. */
#ifndef CLEAN_MAIN_CELL_PAIR_SPRITE_H
#define CLEAN_MAIN_CELL_PAIR_SPRITE_H

#include "screen_icon.h" /* CellAnim */
#include "types.h"

#define CELL_PAIR_SPRITE_HIDDEN 0

typedef struct CellPairSprite {
    const u32 *vtable; /* data_020e2058 */
    int base_x;        /* 0x04: the base class's place (func_0208aef0, func_0208aeec) */
    int base_y;        /* 0x08 */
    CellAnim first;    /* 0x0c */
    CellAnim second;   /* 0x20 */
    int pose;          /* 0x34: CELL_PAIR_SPRITE_HIDDEN or the pose shown */
    int x;             /* 0x38: added to the base class's place */
    int y;             /* 0x3c */
    u8 alternate;      /* 0x40: the poses' alternate set of animations */
    u8 on_main;        /* 0x41: drawn on the main screen, else on the sub screen */
    u8 pad_42[2];
} CellPairSprite;

int CellPairSprite_AnimsDone(CellPairSprite *sprite);
int CellPairSprite_Pose(CellPairSprite *sprite);
void CellPairSprite_SetPose(CellPairSprite *sprite, int pose);
void CellPairSprite_SetPlace(CellPairSprite *sprite, u32 x, u32 y);
void CellPairSprite_UseAlternate(CellPairSprite *sprite);
void CellPairSprite_Update(CellPairSprite *sprite);
void CellPairSprite_Draw(CellPairSprite *sprite);
CellPairSprite *CellPairSprite_Delete(CellPairSprite *sprite);
CellPairSprite *CellPairSprite_Destruct(CellPairSprite *sprite);
CellPairSprite *CellPairSprite_Construct(CellPairSprite *sprite, int on_main);

#endif
