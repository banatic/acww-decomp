/* An object of the menu scenes that glides to a point (class vtable 0x0220bc88, constructor
 * func_ov002_0220a40c, destructor func_ov002_0220a39c): an object of main's class built by
 * func_0208e8d4, with a Glide at 0x4c that its update (func_ov002_02209e50) steps and
 * follows. Two classes derive from it, differing only in the byte func_0208e8d4 is given:
 * Glider0 (vtable 0x0220bc50, 0; the scenes of the overlays 096-105 keep one) and Glider1
 * (vtable 0x0220bc6c, 1; overlays 091 and 113).
 *
 * Each frame the update (vtable slot 3) steps the glide and makes its place the sprite's offset
 * from the screen's centre (0x80, 0x60). The class's draw (slot 2) is main's, func_0208e600;
 * Glider_DrawWrapped also draws a glider near the right edge again 256 pixels to the left.
 *
 * A Glide (vtable 0x0220bc40) holds a place in 1/16 pixels and moves it to a target in a
 * number of steps, by equal steps (GLIDE_LINEAR) or by halving ones (GLIDE_EASE). */
#ifndef CLEAN_OV002_GLIDE_H
#define CLEAN_OV002_GLIDE_H

#include "main/screen_icon.h"
#include "types.h"

enum GlideMode {
    GLIDE_IDLE = 0,   /* as constructed */
    GLIDE_PLACED = 1, /* put at a place (func_ov002_0220a0b4) */
    GLIDE_LINEAR = 2, /* `steps` equal steps of (dx, dy) */
    GLIDE_EASE = 3    /* the first step half the way, each next one half the last */
};

typedef struct Glide {
    const void *vtable; /* data_ov002_0220bc40 */
    s32 x;              /* 0x04: in 1/16 pixels */
    s32 y;              /* 0x08 */
    s32 dx;             /* 0x0c: the next step */
    s32 dy;             /* 0x10 */
    u8 steps;           /* 0x14: steps left */
    u8 mode;            /* 0x15: GlideMode */
    u8 pad_16[2];
} Glide;

/* The animations of a Glider's sprite (func_0208e508 starts one, func_0208e4bc reads it): four
 * sets of three (1-3, 7-9, 13-15, 16-18) and two sets of turns (4-6 and 10-12); turns 5 and 11
 * go back to 1 and 7 when they end (Glider_Update). What each one shows is not known. */
enum GliderAnim {
    GLIDER_ANIM_NONE = 0,
    GLIDER_ANIM_SET_A = 1,   /* 1-3 */
    GLIDER_ANIM_TURN_A = 4,  /* 4-6 */
    GLIDER_ANIM_SET_B = 7,   /* 7-9 */
    GLIDER_ANIM_TURN_B = 10, /* 10-12 */
    GLIDER_ANIM_SET_C = 13,  /* 13-15 */
    GLIDER_ANIM_SET_D = 16   /* 16-18 */
};

typedef struct Glider {
    const void *vtable; /* data_ov002_0220bc88, or a derived class's */
    /* main's sprite (constructor func_0208e8d4, destructor func_0208e7f0) */
    s32 x;          /* 0x04: its place (func_0208aef0) */
    s32 y;          /* 0x08: (func_0208aeec) */
    CellAnim anim;  /* 0x0c */
    s32 offset_x;   /* 0x20: drawn at the place plus the offset (func_0208e594 sets both) */
    s32 offset_y;   /* 0x24 */
    u32 unk_28;     /* 0x28 */
    CellAnim anim2; /* 0x2c: a second layer, shown when has_anim2 */
    u32 anim_id;    /* 0x40: GliderAnim */
    u32 unk_44;     /* 0x44 */
    u8 kind;        /* 0x48: the byte given to func_0208e8d4 */
    u8 has_anim2;   /* 0x49 */
    u8 unk_4a;      /* 0x4a: set by func_0208e5cc */
    u8 pad_4b;
    Glide glide; /* 0x4c */
} Glider;

Glider *Glider1_Delete(Glider *glider);
Glider *Glider1_Destroy(Glider *glider);
Glider *Glider1_Construct(Glider *glider);
Glider *Glider0_Delete(Glider *glider);
Glider *Glider0_Destroy(Glider *glider);
Glider *Glider0_Construct(Glider *glider);
int Glide_IsMoving(Glide *glide);
void Glide_EaseTo(Glide *glide, int x, int y, int steps);
int Glide_MoveTo(Glide *glide, int x, int y, int steps);
void Glide_SetPlace(Glide *glide, int x, int y);
void Glide_SetPlaced(Glide *glide);
int Glide_Y(Glide *glide);
int Glide_X(Glide *glide);
int Glide_Step(Glide *glide);
void Glide_Stop(Glide *glide);
Glide *Glide_Delete(Glide *glide);
void Glide_Destroy(Glide *glide);
void Glide_Construct(Glide *glide);
void Glider_Update(Glider *glider);
void Glider_DrawWrapped(Glider *glider);
int Glider_ScreenY(Glider *glider);
int Glider_ScreenX(Glider *glider);
int Glider_FrameY(Glider *glider);
int Glider_FrameX(Glider *glider);
int Glider_IsMoving(Glider *glider);
int Glider_IsTurnAtFrame2(Glider *glider);
int Glider_IsTurnSettled(Glider *glider);
void Glider_EaseToByDistance(Glider *glider, int x, int y, int steps, u8 near_steps);
void Glider_EaseTo(Glider *glider, int x, int y, int steps, int cue);
int Glider_MoveTo(Glider *glider, int x, int y, int steps);
void Glider_PlaceAt(Glider *glider, int x, int y);
void Glider_SetCenter(Glider *glider, int x, int y);
void Glider_ShowFirstOfSet(Glider *glider);
void Glider_ShowThirdOfSet(Glider *glider);
void Glider_ShowSecondOfSet(Glider *glider);
void Glider_TurnToSetC(Glider *glider);
void Glider_TurnToSetA(Glider *glider);
void Glider_TurnToSetB(Glider *glider);
void Glider_SetAnim(Glider *glider, int anim);
Glider *Glider_Destroy(Glider *glider);
Glider *Glider_Delete(Glider *glider);
Glider *Glider_DestroyVirtual(Glider *glider);
Glider *Glider_Construct(Glider *glider, u8 kind);

#endif
