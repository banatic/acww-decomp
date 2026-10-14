/* Animation frame counters: a frame position stepped by a speed, looping or stopping at the
 * ends, and a weight that ramps from 0 to 1. */
#ifndef CLEAN_MAIN_FRAME_CTRL_H
#define CLEAN_MAIN_FRAME_CTRL_H

#include "types.h"

enum FrameCtrlFlags {
    FRAME_CTRL_ONCE = 1 << 0,    /* stop at the end instead of starting again */
    FRAME_CTRL_REVERSE = 1 << 1, /* count down from the end towards frame 0 */
};

/* A frame position in a sequence of `end` frames, all in 20.12 fixed point. The game embeds it
 * in its animated objects (at 0x2d0 in the actors, for one); the first word is the C++ vtable. */
typedef struct FrameCtrl {
    const void *vtable;
    fx32 end;      /* the frame count */
    fx32 frame;    /* where the sequence is now */
    fx32 previous; /* where it was before the last step */
    fx32 speed;    /* frames per step */
    u8 flags;      /* FrameCtrlFlags */
} FrameCtrl;

/* A weight stepped from 0 to 1.0 (0x1000) at a fixed rate; the object around it has another
 * vtable and data the steps do not touch. */
typedef struct Ramp {
    u8 unk_00[0x34];
    fx32 weight;
    fx32 rate; /* 0 once the weight has reached 1.0 */
} Ramp;

void FrameCtrl_Init(FrameCtrl *ctrl, u32 frames, u8 flags, fx32 speed, u16 start);
BOOL FrameCtrl_Passed(const FrameCtrl *ctrl, int frame);
BOOL FrameCtrl_IsDone(const FrameCtrl *ctrl);
void FrameCtrl_Step(FrameCtrl *ctrl);
BOOL Ramp_Step(Ramp *ramp);

#endif
