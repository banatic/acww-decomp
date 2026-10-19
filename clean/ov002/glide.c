/* The objects of the menu scenes that glide to a point (glide.h). */
#include "glide.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/cell_anim.h"
#include "main/cell_layer_sprite.h"
#include "main/screen_sprite.h"
#include "main/sound.h"

static_assert(sizeof(Glide) == 0x18 && offsetof(Glide, mode) == 0x15, "glide");
static_assert(offsetof(Glider, anim) == 0x0c && offsetof(Glider, offset_x) == 0x20, "glider");
static_assert(offsetof(Glider, anim2) == 0x2c && offsetof(Glider, anim_id) == 0x40, "glider");
static_assert(offsetof(Glider, has_anim2) == 0x49 && offsetof(Glider, glide) == 0x4c, "glider");

extern const u8 data_ov002_0220bc40[]; /* the Glide's vtable */
extern const u8 data_ov002_0220bc88[]; /* the Glider's vtable */
extern const u8 data_ov002_0220bc50[]; /* Glider0's vtable */
extern const u8 data_ov002_0220bc6c[]; /* Glider1's vtable */

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

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
    Glider_Destroy(glider);
    Heap_OperatorDeleteB(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209c40, Glider1_Delete)

/* func_ov002_02209c60 (vtable entry 0) */
Glider *Glider1_Destroy(Glider *glider)
{
    glider->vtable = data_ov002_0220bc6c;
    Glider_Destroy(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209c60, Glider1_Destroy)

/* func_ov002_02209c78 */
Glider *Glider1_Construct(Glider *glider)
{
    Glider_Construct(glider, 1);
    glider->vtable = data_ov002_0220bc6c;
    return glider;
}
CLEAN_AS(func_ov002_02209c78, Glider1_Construct)

/* func_ov002_02209c94 (vtable entry 1) */
Glider *Glider0_Delete(Glider *glider)
{
    glider->vtable = data_ov002_0220bc50;
    Glider_Destroy(glider);
    Heap_OperatorDeleteB(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209c94, Glider0_Delete)

/* func_ov002_02209cb4 (vtable entry 0) */
Glider *Glider0_Destroy(Glider *glider)
{
    glider->vtable = data_ov002_0220bc50;
    Glider_Destroy(glider);
    return glider;
}
CLEAN_AS(func_ov002_02209cb4, Glider0_Destroy)

/* func_ov002_02209ccc */
Glider *Glider0_Construct(Glider *glider)
{
    Glider_Construct(glider, 0);
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

/* The width of the screen in 1/16 pixels: glides wrap around it horizontally. */
#define GLIDE_WRAP_WIDTH 0x1000
/* The screen's centre, from which a Glider's place is its sprite's offset. */
#define SCREEN_CENTER_X 0x80
#define SCREEN_CENTER_Y 0x60
/* Glider_DrawWrapped: a sprite drawn right of this x is drawn again one screen to the left. */
#define WRAP_DRAW_X 0xe0
#define SCREEN_WIDTH 0x100
/* Glider_EaseToByDistance: the distance, in pixels on each axis, that counts as near. */
#define NEAR_DISTANCE 0x30

/* func_ov002_02209d84: x in whole pixels, rounded down. */
int Glide_X(Glide *glide)
{
    return glide->x >> 4;
}
CLEAN_AS(func_ov002_02209d84, Glide_X)

/* func_ov002_02209d8c: one step of a linear or easing glide; returns 1 when the glide is over
 * (or is no glide), else 0. An easing glide halves its step after each one but the last two.
 * QUIRK: x wraps into 0 to GLIDE_WRAP_WIDTH, both included; y does not wrap. */
int Glide_Step(Glide *glide)
{
    if (glide->mode != GLIDE_LINEAR && glide->mode != GLIDE_EASE) {
        return 1;
    }
    if (glide->steps != 0) {
        glide->steps--;
        glide->x = add32(glide->x, glide->dx);
        glide->y = add32(glide->y, glide->dy);
        if (glide->mode == GLIDE_EASE && glide->steps > 1) {
            glide->dx >>= 1;
            glide->dy >>= 1;
        }
        while (glide->x < 0) {
            glide->x += GLIDE_WRAP_WIDTH;
        }
        while (glide->x > GLIDE_WRAP_WIDTH) {
            glide->x -= GLIDE_WRAP_WIDTH;
        }
    }
    return glide->steps == 0;
}
CLEAN_AS(func_ov002_02209d8c, Glide_Step)

/* func_ov002_02209e18 */
void Glide_Stop(Glide *glide)
{
    glide->mode = GLIDE_IDLE;
}
CLEAN_AS(func_ov002_02209e18, Glide_Stop)

/* func_ov002_02209e20 (vtable entry 1) */
Glide *Glide_Delete(Glide *glide)
{
    glide->vtable = data_ov002_0220bc40;
    Heap_OperatorDeleteB(glide);
    return glide;
}
CLEAN_AS(func_ov002_02209e20, Glide_Delete)

/* func_ov002_02209e38 (vtable entry 0) */
void Glide_Destroy(Glide *glide)
{
    glide->vtable = data_ov002_0220bc40;
}
CLEAN_AS(func_ov002_02209e38, Glide_Destroy)

/* func_ov002_02209e44 */
void Glide_Construct(Glide *glide)
{
    glide->vtable = data_ov002_0220bc40;
}
CLEAN_AS(func_ov002_02209e44, Glide_Construct)

/* func_ov002_02209e50 (vtable entry 3): steps the glide and follows it; turns 5 and 11 go
 * back to 1 and 7 once they end; advances the animations. */
void Glider_Update(Glider *glider)
{
    Glide_Step(&glider->glide);
    int x = Glide_X(&glider->glide);
    int y = Glide_Y(&glider->glide);
    Glider_SetCenter(glider, x, y);
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) glider)) {
        if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_TURN_A + 1) {
            CellLayerSprite_SetAnim((CellLayerSprite *) (void *) glider, GLIDER_ANIM_SET_A);
        } else if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_TURN_B + 1) {
            CellLayerSprite_SetAnim((CellLayerSprite *) (void *) glider, GLIDER_ANIM_SET_B);
        }
    }
    CellLayerSprite_Update((CellLayerSprite *) (void *) glider);
}
CLEAN_AS(func_ov002_02209e50, Glider_Update)

/* func_ov002_02209eb8: draws; a sprite right of WRAP_DRAW_X is drawn a second time one screen
 * width to the left, so that it shows on both edges while it wraps. */
void Glider_DrawWrapped(Glider *glider)
{
    CellLayerSprite_Draw((CellLayerSprite *) (void *) glider);
    int offset_x = glider->offset_x;
    if (add32(offset_x, ScreenSprite_X((ScreenSprite *) (void *) glider)) > WRAP_DRAW_X) {
        glider->offset_x = sub32(glider->offset_x, SCREEN_WIDTH);
        CellLayerSprite_Draw((CellLayerSprite *) (void *) glider);
        glider->offset_x = offset_x;
    }
}
CLEAN_AS(func_ov002_02209eb8, Glider_DrawWrapped)

/* func_ov002_02209eec: y on the screen, the place plus the offset. */
int Glider_ScreenY(Glider *glider)
{
    int y = ScreenSprite_Y((ScreenSprite *) (void *) glider);
    return add32(glider->offset_y, y);
}
CLEAN_AS(func_ov002_02209eec, Glider_ScreenY)

/* func_ov002_02209f00 */
int Glider_ScreenX(Glider *glider)
{
    int x = ScreenSprite_X((ScreenSprite *) (void *) glider);
    return add32(glider->offset_x, x);
}
CLEAN_AS(func_ov002_02209f00, Glider_ScreenX)

/* func_ov002_02209f14: y on the screen of the current frame of the animation. */
int Glider_FrameY(Glider *glider)
{
    int frame_y = CellAnim_FrameY(&glider->anim, -1);
    int y = ScreenSprite_Y((ScreenSprite *) (void *) glider);
    return add32(frame_y, add32(glider->offset_y, y));
}
CLEAN_AS(func_ov002_02209f14, Glider_FrameY)

/* func_ov002_02209f3c */
int Glider_FrameX(Glider *glider)
{
    int frame_x = CellAnim_FrameX(&glider->anim, -1);
    int x = ScreenSprite_X((ScreenSprite *) (void *) glider);
    return add32(frame_x, add32(glider->offset_x, x));
}
CLEAN_AS(func_ov002_02209f3c, Glider_FrameX)

/* func_ov002_02209f64 */
int Glider_IsMoving(Glider *glider)
{
    return Glide_IsMoving(&glider->glide);
}
CLEAN_AS(func_ov002_02209f64, Glider_IsMoving)

/* func_ov002_02209f70: during turn 6 or 12, whether the animation is at its frame 2; 1 for
 * any other animation. */
int Glider_IsTurnAtFrame2(Glider *glider)
{
    int anim = CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider);
    if (anim == GLIDER_ANIM_TURN_A + 2 || anim == GLIDER_ANIM_TURN_B + 2) {
        return CellAnim_Frame(&glider->anim) == 2;
    }
    return 1;
}
CLEAN_AS(func_ov002_02209f70, Glider_IsTurnAtFrame2)

/* func_ov002_02209f9c: for a turn, whether it has gone far enough: turns 4 and 10 from their
 * frame 4, turns 5 and 11 before their frame 3, turns 6 and 12 always; 0 for the other
 * animations. */
int Glider_IsTurnSettled(Glider *glider)
{
    switch (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider)) {
        case GLIDER_ANIM_TURN_A:
        case GLIDER_ANIM_TURN_B:
            return CellAnim_Frame(&glider->anim) >= 4;
        case GLIDER_ANIM_TURN_A + 1:
        case GLIDER_ANIM_TURN_B + 1:
            return CellAnim_Frame(&glider->anim) < 3;
        case GLIDER_ANIM_TURN_A + 2:
        case GLIDER_ANIM_TURN_B + 2:
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov002_02209f9c, Glider_IsTurnSettled)

/* func_ov002_0220a000: sends command 0xb and eases to the pixel (x, y) in `steps` steps, or
 * in `near_steps` when it is within NEAR_DISTANCE pixels of the glider on both axes. */
void Glider_EaseToByDistance(Glider *glider, int x, int y, int steps, u8 near_steps)
{
    int place_x = ScreenSprite_X((ScreenSprite *) (void *) glider);
    int dx = sub32(x, add32(glider->offset_x, place_x));
    SoundSys_PlaySe(0xb);
    if (dx >= -NEAR_DISTANCE && dx <= NEAR_DISTANCE) {
        int place_y = ScreenSprite_Y((ScreenSprite *) (void *) glider);
        int dy = sub32(y, add32(glider->offset_y, place_y));
        if (dy >= -NEAR_DISTANCE && dy <= NEAR_DISTANCE) {
            steps = near_steps;
        }
    }
    Glide_EaseTo(&glider->glide, x, y, steps);
}
CLEAN_AS(func_ov002_0220a000, Glider_EaseToByDistance)

/* func_ov002_0220a05c: eases to the pixel (x, y), sending command 0xb first when `cue`. */
void Glider_EaseTo(Glider *glider, int x, int y, int steps, int cue)
{
    if (cue) {
        SoundSys_PlaySe(0xb);
    }
    Glide_EaseTo(&glider->glide, x, y, steps);
}
CLEAN_AS(func_ov002_0220a05c, Glider_EaseTo)

/* func_ov002_0220a08c: sends command 0xb and glides to the pixel (x, y) in equal steps;
 * returns the vertical step. */
int Glider_MoveTo(Glider *glider, int x, int y, int steps)
{
    SoundSys_PlaySe(0xb);
    return Glide_MoveTo(&glider->glide, x, y, steps);
}
CLEAN_AS(func_ov002_0220a08c, Glider_MoveTo)

/* func_ov002_0220a0b4: puts the glider at the pixel (x, y) at once. */
void Glider_PlaceAt(Glider *glider, int x, int y)
{
    Glide_SetPlaced(&glider->glide);
    Glide_SetPlace(&glider->glide, x, y);
    Glider_SetCenter(glider, x, y);
}
CLEAN_AS(func_ov002_0220a0b4, Glider_PlaceAt)

/* func_ov002_0220a0e0: the sprite's offset for the pixel (x, y), from the screen's centre. */
void Glider_SetCenter(Glider *glider, int x, int y)
{
    CellLayerSprite_SetOffset((CellLayerSprite *) (void *) glider, sub32(x, SCREEN_CENTER_X), sub32(y, SCREEN_CENTER_Y));
}
CLEAN_AS(func_ov002_0220a0e0, Glider_SetCenter)

/* The set an animation belongs to, its first animation; 0 for none and -1 for a turn or a
 * number outside the sets. */
static int set_of(int anim)
{
    switch (anim) {
        case GLIDER_ANIM_NONE:
            return 0;
        case 1:
        case 2:
        case 3:
            return GLIDER_ANIM_SET_A;
        case 7:
        case 8:
        case 9:
            return GLIDER_ANIM_SET_B;
        case 13:
        case 14:
        case 15:
            return GLIDER_ANIM_SET_C;
        case 16:
        case 17:
        case 18:
            return GLIDER_ANIM_SET_D;
        default:
            return -1;
    }
}

/* Starts the animation `index` (0-2) of the current animation's set, or `otherwise` for a turn
 * or a number outside the sets; nothing while there is no animation. */
static void show_of_set(Glider *glider, int index, int otherwise)
{
    int set = set_of(CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider));
    if (set == 0) {
        return;
    }
    CellLayerSprite_SetAnim((CellLayerSprite *) (void *) glider, set < 0 ? otherwise : set + index);
}

/* func_ov002_0220a0ec: the first animation of the current one's set.
 * QUIRK: a turn, or any number outside the sets, gives 9, the last of set B. */
void Glider_ShowFirstOfSet(Glider *glider)
{
    show_of_set(glider, 0, GLIDER_ANIM_SET_B + 2);
}
CLEAN_AS(func_ov002_0220a0ec, Glider_ShowFirstOfSet)

/* func_ov002_0220a164: the third animation of the current one's set.
 * QUIRK: a turn, or any number outside the sets, gives 9. */
void Glider_ShowThirdOfSet(Glider *glider)
{
    show_of_set(glider, 2, GLIDER_ANIM_SET_B + 2);
}
CLEAN_AS(func_ov002_0220a164, Glider_ShowThirdOfSet)

/* func_ov002_0220a1dc: the second animation of the current one's set.
 * QUIRK: a turn, or any number outside the sets, gives 8. */
void Glider_ShowSecondOfSet(Glider *glider)
{
    show_of_set(glider, 1, GLIDER_ANIM_SET_B + 1);
}
CLEAN_AS(func_ov002_0220a1dc, Glider_ShowSecondOfSet)

/* Puts the glider (dx, dy) from the place of its animation's current frame. */
static void place_from_frame(Glider *glider, int dx, int dy)
{
    int x = Glider_FrameX(glider);
    int y = Glider_FrameY(glider);
    Glider_PlaceAt(glider, add32(x, dx), add32(y, dy));
}

/* func_ov002_0220a254: switches to animation 13, moving from 1 by (12, -24) and from 7 by
 * (-4, -24) from the current frame's place. */
void Glider_TurnToSetC(Glider *glider)
{
    if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_SET_A) {
        place_from_frame(glider, 0xc, -0x18);
    } else if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_SET_B) {
        place_from_frame(glider, -4, -0x18);
    }
    Glider_SetAnim(glider, GLIDER_ANIM_SET_C);
}
CLEAN_AS(func_ov002_0220a254, Glider_TurnToSetC)

/* func_ov002_0220a2b4: switches to animation 1, moving from 7 by (-16, 0) and from 13 by
 * (-12, 24) from the current frame's place. */
void Glider_TurnToSetA(Glider *glider)
{
    if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_SET_B) {
        place_from_frame(glider, -0x10, 0);
    } else if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_SET_C) {
        place_from_frame(glider, -0xc, 0x18);
    }
    Glider_SetAnim(glider, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov002_0220a2b4, Glider_TurnToSetA)

/* func_ov002_0220a314: switches to animation 7, moving from 1 by (16, 0) and from 13 by
 * (4, 24) from the current frame's place. */
void Glider_TurnToSetB(Glider *glider)
{
    if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_SET_A) {
        place_from_frame(glider, 0x10, 0);
    } else if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) == GLIDER_ANIM_SET_C) {
        place_from_frame(glider, 4, 0x18);
    }
    Glider_SetAnim(glider, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov002_0220a314, Glider_TurnToSetB)

/* func_ov002_0220a374: starts `anim` unless it is playing already; turns 6 and 12 always
 * start again. */
void Glider_SetAnim(Glider *glider, int anim)
{
    if (anim != CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) glider) || anim == GLIDER_ANIM_TURN_A + 2 ||
        anim == GLIDER_ANIM_TURN_B + 2) {
        CellLayerSprite_SetAnim((CellLayerSprite *) (void *) glider, anim);
    }
}
CLEAN_AS(func_ov002_0220a374, Glider_SetAnim)

/* func_ov002_0220a39c: the destructor the derived classes call. */
Glider *Glider_Destroy(Glider *glider)
{
    glider->vtable = data_ov002_0220bc88;
    Glide_Destroy(&glider->glide);
    CellLayerSprite_DestructCopy((CellLayerSprite *) (void *) glider);
    return glider;
}
CLEAN_AS(func_ov002_0220a39c, Glider_Destroy)

/* func_ov002_0220a3c0 (vtable entry 1) */
Glider *Glider_Delete(Glider *glider)
{
    glider->vtable = data_ov002_0220bc88;
    Glide_Destroy(&glider->glide);
    CellLayerSprite_DestructCopy((CellLayerSprite *) (void *) glider);
    Heap_OperatorDeleteB(glider);
    return glider;
}
CLEAN_AS(func_ov002_0220a3c0, Glider_Delete)

/* func_ov002_0220a3e8 (vtable entry 0): the same as Glider_Destroy. */
Glider *Glider_DestroyVirtual(Glider *glider)
{
    glider->vtable = data_ov002_0220bc88;
    Glide_Destroy(&glider->glide);
    CellLayerSprite_DestructCopy((CellLayerSprite *) (void *) glider);
    return glider;
}
CLEAN_AS(func_ov002_0220a3e8, Glider_DestroyVirtual)

/* func_ov002_0220a40c: main's sprite with `kind`, without an animation, standing still. */
Glider *Glider_Construct(Glider *glider, u8 kind)
{
    CellLayerSprite_Construct((CellLayerSprite *) (void *) glider, kind);
    glider->vtable = data_ov002_0220bc88;
    Glide_Construct(&glider->glide);
    CellLayerSprite_SetAnim((CellLayerSprite *) (void *) glider, GLIDER_ANIM_NONE);
    Glide_Stop(&glider->glide);
    glider->unk_28 = 0;
    CellLayerSprite_SetWindow((CellLayerSprite *) (void *) glider);
    return glider;
}
CLEAN_AS(func_ov002_0220a40c, Glider_Construct)
