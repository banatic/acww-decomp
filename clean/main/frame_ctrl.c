/* Animation frame counters. */
#include "frame_ctrl.h"

#include <assert.h>
#include <stddef.h>

#define ONE_FRAME 0x1000

/* func_02056fcc: start a sequence of `frames` frames at frame `start`, or at the last frame
 * when `start` is 0xffff (the callers that play backwards pass that).
 * QUIRK: the frame count is shifted into 20.12 without a check, so counts of 0x80000 and more
 * wrap; the game's sequences are a few hundred frames. */
void FrameCtrl_Init(FrameCtrl *ctrl, u32 frames, u8 flags, fx32 speed, u16 start)
{
    if (start == 0xffff) {
        start = (u16) (frames - 1);
    }
    ctrl->end = (fx32) (frames << 12);
    ctrl->frame = (fx32) start << 12;
    ctrl->previous = ctrl->frame;
    ctrl->speed = speed;
    ctrl->flags = flags;
}

/* func_02056f28: did the last step reach whole frame `frame`? Moving forwards that is the
 * range (previous, frame], backwards [frame, previous), and a step that wrapped round the end
 * covers the two pieces outside the range it skipped. */
BOOL FrameCtrl_Passed(const FrameCtrl *ctrl, int frame)
{
    fx32 at = frame << 12;
    fx32 now = ctrl->frame;
    fx32 before = ctrl->previous;

    if (before == now) {
#ifdef BUGFIX
        return now == at;
#else
        /* BUG: a counter that did not move compares the frame number with the 20.12 position
         * without converting it, so only frame 0 is ever found there. */
        return now == frame;
#endif
    }
    if (ctrl->flags & FRAME_CTRL_REVERSE) {
        if (before > now) {
            return at >= now && at < before;
        }
        return !(at >= before && at < now);
    }
    if (before < now) {
        return at > before && at <= now;
    }
    return !(at <= before && at > now);
}

/* func_02056f94: has a sequence that plays once reached its end? Looping sequences never do.
 * QUIRK: only the exact flag values 1 and 3 count, so another bit set in the flags makes a
 * sequence that plays once never finish. */
BOOL FrameCtrl_IsDone(const FrameCtrl *ctrl)
{
    switch (ctrl->flags) {
        case FRAME_CTRL_ONCE:
            return ctrl->frame >= ctrl->end - ONE_FRAME;
        case FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE:
            return ctrl->frame == 0;
        default:
            return FALSE;
    }
}

/* func_02056ffc: move by one step of the speed, starting again at the other end of a looping
 * sequence and stopping on the first or last frame of one that plays once. */
void FrameCtrl_Step(FrameCtrl *ctrl)
{
    fx32 frame = ctrl->frame;
    ctrl->previous = frame;
    if (ctrl->flags & FRAME_CTRL_REVERSE) {
        if (frame >= ctrl->speed) {
            frame -= ctrl->speed;
        } else if (ctrl->flags & FRAME_CTRL_ONCE) {
            frame = 0;
        } else {
            frame += ctrl->end - ctrl->speed;
        }
    } else {
        frame += ctrl->speed;
        if (frame >= ctrl->end) {
            if (ctrl->flags & FRAME_CTRL_ONCE) {
                frame = ctrl->end - ONE_FRAME;
            } else {
                frame -= ctrl->end;
            }
        }
    }
    ctrl->frame = frame;
}

/* func_02056e84: one step of the weight; TRUE once it is 1.0, including when it was never
 * started (a rate of 0). */
BOOL Ramp_Step(Ramp *ramp)
{
    if (ramp->rate == 0) {
        return TRUE;
    }
    ramp->weight += ramp->rate;
    if (ramp->weight >= ONE_FRAME) {
        ramp->weight = ONE_FRAME;
        ramp->rate = 0;
        return TRUE;
    }
    return FALSE;
}

static_assert(sizeof(FrameCtrl) == 0x18 && offsetof(FrameCtrl, flags) == 0x14, "FrameCtrl layout");
static_assert(offsetof(Ramp, weight) == 0x34 && offsetof(Ramp, rate) == 0x38, "Ramp layout");
