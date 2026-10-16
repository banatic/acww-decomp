/* A screen wipe of the menu scenes: a position that runs over the screen's height (vertical
 * directions) or width (horizontal ones) in a number of frames, which the wipe turns into a
 * window rectangle (func_02002808) and background offsets (func_0200284c).
 *
 * The wipe derives from a small progress class (vtable 0x0220bb04): a fixed-point fraction
 * counting down from 1.0 by 1.0 / the frame count. A wipe forward puts the position at the
 * extent less the part of it still to run (linear); a wipe back puts it at the extent times
 * the square of the fraction still to run.
 *
 * The rectangle is passed as (x1, y1, x2, y2), the whole screen being (0, 0, 255, 192). */
#ifndef CLEAN_OV002_WIPE_H
#define CLEAN_OV002_WIPE_H

#include "types.h"

#define SCREEN_WIDTH 0x100
#define SCREEN_HEIGHT 0xc0

/* 1.0 in the progress's fixed point (20.12) */
#define PROGRESS_ONE 0x1000

/* The wipe's base class (vtable data_ov002_0220bb04). */
typedef struct Progress {
    const void *vtable; /* data_ov002_0220bb04, or the wipe's */
    s32 rate;           /* 0x04: 1.0 / the frame count */
    s32 left;           /* 0x08: progress still to run, from 1.0 down to 0 */
} Progress;

/* In `direction`: which edge of the window the position moves (by func_ov002_02208348). */
enum WipeDirection {
    WIPE_TOP = 0,    /* y1 = position - margin */
    WIPE_BOTTOM = 1, /* y2 = 192 + margin - position */
    WIPE_RIGHT = 2,  /* x2 = 255 - position */
    WIPE_LEFT = 3    /* x1 = position */
};

/* The screen whose window 0 a wipe's step drives: the sub engine's (window 2 of
 * func_02002808) or the main engine's (window 0). Other values drive none. */
enum WipeScreen { WIPE_ON_SUB = 0, WIPE_ON_MAIN = 1 };

typedef struct Wipe {
    Progress progress; /* its vtable data_ov002_0220baf4 */
    s32 position;      /* 0x0c: pixels */
    s32 extent;        /* 0x10: the height or width the position runs over */
    s32 margin;        /* 0x14: how far the vertical edges lag the position */
    u8 direction;      /* 0x18: WipeDirection */
    u8 pad_19[3];
} Wipe;

void Wipe_SetExtent(Wipe *wipe, int extent);
void Wipe_ApplyWindow(Wipe *wipe, int window);
void Wipe_ApplyScroll(Wipe *wipe, int layer, int x, int y);
void Wipe_Start(Wipe *wipe, int frames, u8 direction, int margin);
void Wipe_StartCovered(Wipe *wipe, int frames, u8 direction, u32 margin);
void Wipe_StartOnWindow0(Wipe *wipe, int layers, int frames, int direction, int margin);
void Wipe_StartCoveredOnWindow0(Wipe *wipe, int layers, int frames, int direction, int margin);
void Wipe_StartOnWindow2(Wipe *wipe, int layers, int frames, int direction, int margin);
void Wipe_StartCoveredOnWindow2(Wipe *wipe, int layers, int frames, int direction, int margin);
int Wipe_Step(Wipe *wipe, int screen);
void Wipe_StepHorizontal(Wipe *wipe, int screen);
void Wipe_StepVertical(Wipe *wipe, int screen);
int Wipe_StepBack(Wipe *wipe, int screen);
void Wipe_StepBackHorizontal(Wipe *wipe, int screen);
void Wipe_StepBackVertical(Wipe *wipe, int screen);
int Wipe_OffsetX(Wipe *wipe);
int Wipe_OffsetY(Wipe *wipe);
Wipe *Wipe_Delete(Wipe *wipe);
Wipe *Wipe_Destroy(Wipe *wipe);
Wipe *Wipe_Construct(Wipe *wipe);

int Progress_ScaleRemaining(Progress *progress, int value);
int Progress_ScaleRemainingSquared(Progress *progress, int value);
int Progress_Step(Progress *progress);
void Progress_Start(Progress *progress, unsigned int frames);
void Progress_Destroy(Progress *progress);
Progress *Progress_Delete(Progress *progress);
void Progress_DestroyBase(Progress *progress);
void Progress_Construct(Progress *progress);

#endif
