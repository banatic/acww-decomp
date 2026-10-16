/* The hands of a clock model, turned by the time of day (clock_hands.h). */
#include "clock_hands.h"

#include "clean.h"
#include "main/calendar.h" /* Time */

static_assert(offsetof(ClockHandsJoint, rotation) == 0x28, "rotation");
static_assert(offsetof(ClockHandsRenderState, joint) == 0xb4, "joint");

/* A full turn, as the angle the sine table is indexed by (16 bits, 4096 entries). */
#define CLOCK_HANDS_TURN 0xffff
/* How far the hour hand moves in an hour: a twelfth of a turn. */
#define CLOCK_HANDS_HOUR_TURN 0x1555

extern const fx16 FX_SinCosTable_[4096 * 2];
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void MTX_RotZ33_(Mtx33 *mtx, fx32 sin, fx32 cos);
extern void MTX_Concat33(const Mtx33 *a, const Mtx33 *b, Mtx33 *ab);
/* The time of day (calendar.h's Calendar_Now, which is not registered). */
extern void func_0209def4(Time *now);

/* The frame count, and the frame the hour hand's sine and cosine were worked out in. */
extern int data_021fbdd0;
extern int data_021f4b30;
extern int data_021f4b34;
extern int data_020e50d0; /* 0x1000 at start */

/* The entry of the sine table for an angle: only its low 16 bits count, so the 20.12 value's
 * bits 12-27 are all that is used and the shift may be unsigned. */
static u32 clock_hands_entry(u32 angle)
{
    return ((u16) angle >> 4) * 2;
}

/* The joint's rotation turned by `rotation`: replaced while it is the identity, else
 * multiplied by it; then it is no longer the identity. */
static void clock_hands_apply(ClockHandsJoint *joint, const Mtx33 *rotation)
{
    if ((joint->flags & CLOCK_HANDS_ROTATION_ZERO) != 0) {
        joint->rotation = *rotation;
    } else {
        MTX_Concat33(&joint->rotation, rotation, &joint->rotation);
    }
    joint->flags &= ~(u32) CLOCK_HANDS_ROTATION_ZERO;
}

/* func_020b3188: the minute hand, a turn clockwise (negative about z) per hour. */
void ClockHands_TurnMinuteHand(ClockHandsRenderState *state)
{
    ClockHandsJoint *joint = state->joint;
    Time now;
    func_0209def4(&now);
    fx32 part = FX_Div((now.minute % 60) << 12, 60 << 12);
    u32 angle = 0u - (((u32) CLOCK_HANDS_TURN * (u32) part) >> 12);
    u32 entry = clock_hands_entry(angle);
    Mtx33 rotation;
    MTX_RotZ33_(&rotation, FX_SinCosTable_[entry], FX_SinCosTable_[entry + 1]);
    clock_hands_apply(joint, &rotation);
}
CLEAN_AS(func_020b3188, ClockHands_TurnMinuteHand)

/* func_020b3220: the hour hand, a turn clockwise per twelve hours, moved on by the minutes.
 * QUIRK: the minute is not taken modulo 60 here, unlike for the minute hand. */
void ClockHands_TurnHourHand(ClockHandsRenderState *state)
{
    ClockHandsJoint *joint = state->joint;
    Time now;
    func_0209def4(&now);
    if (data_021f4b30 != data_021fbdd0) {
        fx32 hours = FX_Div((now.hour % 12) << 12, 12 << 12);
        u32 hour_angle = 0u - (((u32) CLOCK_HANDS_TURN * (u32) hours) >> 12);
        fx32 minutes = FX_Div(now.minute << 12, 60 << 12);
        u32 minute_angle = ((u32) CLOCK_HANDS_HOUR_TURN * (u32) minutes) >> 12;
        u32 entry = clock_hands_entry(hour_angle - minute_angle);
        data_021f4b34 = FX_SinCosTable_[entry];
        data_020e50d0 = FX_SinCosTable_[entry + 1];
        data_021f4b30 = data_021fbdd0;
    }
    Mtx33 rotation;
    MTX_RotZ33_(&rotation, data_021f4b34, data_020e50d0);
    clock_hands_apply(joint, &rotation);
}
CLEAN_AS(func_020b3220, ClockHands_TurnHourHand)
