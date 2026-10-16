/* The objects of the menu scenes that glide to a point (glide.h). */
#include "glide.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"

static_assert(sizeof(Glide) == 0x18 && offsetof(Glide, mode) == 0x15, "glide");
static_assert(offsetof(Glider, glide) == 0x4c, "glider");

extern const u8 data_ov002_0220bc50[];                   /* Glider0's vtable */
extern const u8 data_ov002_0220bc6c[];                   /* Glider1's vtable */
extern void *func_ov002_0220a39c(void *glider);          /* the base's destructor */
extern void *func_ov002_0220a40c(void *glider, u8 kind); /* the base's constructor */
extern void func_020edb3c(void *block);                  /* operator delete */

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

/* `pixels` in 1/16 pixels. */
static int sixteenths(int pixels)
{
    return (int) ((u32) pixels << 4);
}

/* func_ov002_02209c40 (vtable entry 1) */
Glider *Glider1_Delete(Glider *glider)
{
    glider->vtable = data_ov002_0220bc6c;
    func_ov002_0220a39c(glider);
    func_020edb3c(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209c40, Glider1_Delete)

/* func_ov002_02209c60 (vtable entry 0) */
Glider *Glider1_Destroy(Glider *glider)
{
    glider->vtable = data_ov002_0220bc6c;
    func_ov002_0220a39c(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209c60, Glider1_Destroy)

/* func_ov002_02209c78 */
Glider *Glider1_Construct(Glider *glider)
{
    func_ov002_0220a40c(glider, 1);
    glider->vtable = data_ov002_0220bc6c;
    return glider;
}
CLEAN_AS(func_ov002_02209c78, Glider1_Construct)

/* func_ov002_02209c94 (vtable entry 1) */
Glider *Glider0_Delete(Glider *glider)
{
    glider->vtable = data_ov002_0220bc50;
    func_ov002_0220a39c(glider);
    func_020edb3c(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209c94, Glider0_Delete)

/* func_ov002_02209cb4 (vtable entry 0) */
Glider *Glider0_Destroy(Glider *glider)
{
    glider->vtable = data_ov002_0220bc50;
    func_ov002_0220a39c(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209cb4, Glider0_Destroy)

/* func_ov002_02209ccc */
Glider *Glider0_Construct(Glider *glider)
{
    func_ov002_0220a40c(glider, 0);
    glider->vtable = data_ov002_0220bc50;
    return glider;
}
CLEAN_AS(func_ov002_02209ccc, Glider0_Construct)

/* func_ov002_02209ce8: whether a glide is under way. */
int Glide_IsMoving(Glide *glide)
{
    return (glide->mode == GLIDE_LINEAR || glide->mode == GLIDE_EASE) && glide->steps != 0;
}
CLEAN_AS(func_ov002_02209ce8, Glide_IsMoving)

/* func_ov002_02209d08: glides to the pixel (x, y) easing in `steps` steps: the first goes half
 * the way and each next one half the last, but for the last two, which are equal, so the
 * glide ends at the target (less the rounding). One step is a linear glide. */
void Glide_EaseTo(Glide *glide, int x, int y, int steps)
{
    if (steps == 1) {
        Glide_MoveTo(glide, x, y, 1);
        return;
    }
    glide->mode = GLIDE_EASE;
    glide->dx = sub32(sixteenths(x), glide->x) >> 1;
    glide->dy = sub32(sixteenths(y), glide->y) >> 1;
    glide->steps = (u8) steps;
}
CLEAN_AS(func_ov002_02209d08, Glide_EaseTo)

/* func_ov002_02209d38: glides to the pixel (x, y) in `steps` equal steps (the distance
 * divided by `steps`, rounded towards 0). Returns the vertical step.
 * REQUIRES: steps != 0 (the callers pass 1 and up); the distance in 1/16 pixels is not
 * -0x80000000 when steps is -1. */
int Glide_MoveTo(Glide *glide, int x, int y, int steps)
{
    glide->mode = GLIDE_LINEAR;
    glide->dx = sub32(sixteenths(x), glide->x) / steps;
    glide->dy = sub32(sixteenths(y), glide->y) / steps;
    glide->steps = (u8) steps;
    return glide->dy;
}
CLEAN_AS(func_ov002_02209d38, Glide_MoveTo)

/* func_ov002_02209d68: the place, in pixels. */
void Glide_SetPlace(Glide *glide, int x, int y)
{
    glide->x = sixteenths(x);
    glide->y = sixteenths(y);
}
CLEAN_AS(func_ov002_02209d68, Glide_SetPlace)

/* func_ov002_02209d74 */
void Glide_SetPlaced(Glide *glide)
{
    glide->mode = GLIDE_PLACED;
}
CLEAN_AS(func_ov002_02209d74, Glide_SetPlaced)

/* func_ov002_02209d7c: y in whole pixels, rounded down. */
int Glide_Y(Glide *glide)
{
    return glide->y >> 4;
}
CLEAN_AS(func_ov002_02209d7c, Glide_Y)
