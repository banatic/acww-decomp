/* An object of the menu scenes that glides to a point (class vtable 0x0220bc88, constructor
 * func_ov002_0220a40c, destructor func_ov002_0220a39c): an object of main's class built by
 * func_0208e8d4, with a Glide at 0x4c that its update (func_ov002_02209e50) steps and
 * follows. Two classes derive from it, differing only in the byte func_0208e8d4 is given:
 * Glider0 (vtable 0x0220bc50, 0; the scenes of the overlays 096-105 keep one) and Glider1
 * (vtable 0x0220bc6c, 1; overlays 091 and 113).
 *
 * A Glide (vtable 0x0220bc40) holds a place in 1/16 pixels and moves it to a target in a
 * number of steps, by equal steps (GLIDE_LINEAR) or by halving ones (GLIDE_EASE). */
#ifndef CLEAN_OV002_GLIDE_H
#define CLEAN_OV002_GLIDE_H

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

typedef struct Glider {
    const void *vtable; /* data_ov002_0220bc88, or a derived class's */
    u8 base_04[0x48];   /* main's object (func_0208e8d4) */
    Glide glide;        /* 0x4c */
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

#endif
