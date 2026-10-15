/* Moving values towards targets (approach.h).
 *
 * The step functions return TRUE once the value is on its target: a step that reaches or
 * passes the target leaves the value on it. Sums and differences of 32-bit values wrap as the
 * ARM's do (add32 and the others below). */
#include "approach.h"

#include "clean.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 VEC_Mag(const Vec3 *v);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
/* `out` = `a` - `b`. */
extern void func_020eaca0(Vec3 *out, const Vec3 *a, const Vec3 *b);
/* The length of `v` in the XZ plane. */
extern fx32 func_020ea9c8(const Vec3 *v);
/* `v` scaled by `scale` (20.12), each component rounded. */
extern void func_020eabc8(Vec3 *v, fx32 scale);

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int neg32(int a)
{
    return (int) (0u - (u32) a);
}

static int mul32(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

/* `value` times the 20.12 `rate`, rounded to nearest, kept to 32 bits. */
static int fx_mul(int value, fx32 rate)
{
    return (int) (u32) ((u64) ((s64) value * rate + 0x800) >> 12);
}

/* func_020e8840: one tick of a counter that stops at zero; the count left. */
u16 Countdown_Tick16(u16 *counter)
{
    if (*counter != 0) {
        *counter -= 1;
    }
    return *counter;
}
CLEAN_AS(func_020e8840, Countdown_Tick16)

/* func_020e8858 */
u8 Countdown_Tick8(u8 *counter)
{
    if (*counter != 0) {
        *counter -= 1;
    }
    return *counter;
}
CLEAN_AS(func_020e8858, Countdown_Tick8)

/* func_020e8870: `value` moved by `step` towards `target` (the step's sign is ignored); TRUE
 * once it is there. With a step of 0 only tells whether it is there.
 * QUIRK: the side the target is on is taken from the 16-bit difference, which suits angles:
 * a value and target more than half a turn apart move the short way round, and then the
 * value stops on the target only when it lands near it. */
int Approach_S16Wrapped(s16 *value, int target, s16 step)
{
    if (step == 0) {
        return *value == target;
    }
    if ((s16) sub32(*value, target) > 0) {
        step = (s16) -step;
    }
    *value = (s16) (*value + step);
    if (step * (s16) sub32(*value, target) < 0) {
        return FALSE;
    }
    *value = (s16) target;
    return TRUE;
}
CLEAN_AS(func_020e8870, Approach_S16Wrapped)

static int approach_s32(int *value, int target, int step)
{
    if (step == 0) {
        return *value == target;
    }
    if (*value > target) {
        step = neg32(step);
    }
    *value = add32(*value, step);
    if ((s64) step * sub32(*value, target) < 0) {
        return FALSE;
    }
    *value = target;
    return TRUE;
}

/* func_020e88dc: as Approach_S16Wrapped for a 32-bit value, which takes the side from the
 * full comparison. */
int Approach_S32(int *value, int target, int step)
{
    return approach_s32(value, target, step);
}
CLEAN_AS(func_020e88dc, Approach_S32)

/* func_020e895c: the same as Approach_S32; the game has both. */
int Approach_S32Again(int *value, int target, int step)
{
    return approach_s32(value, target, step);
}
CLEAN_AS(func_020e895c, Approach_S32Again)

/* func_020e89dc: as Approach_S32 for a 16-bit value.
 * QUIRK: the test for passing the target multiplies in 32 bits, so a target far outside the
 * 16-bit range can make it wrap; the callers' targets are 16-bit values. */
int Approach_S16(s16 *value, int target, s16 step)
{
    if (step == 0) {
        return *value == target;
    }
    if (*value > target) {
        step = (s16) -step;
    }
    *value = (s16) (*value + step);
    if (mul32(step, sub32(*value, target)) < 0) {
        return FALSE;
    }
    *value = (s16) target;
    return TRUE;
}
CLEAN_AS(func_020e89dc, Approach_S16)

/* func_020e8a38: as Approach_S16 for a byte. The value moves in 16 bits and is stored as a
 * byte. */
int Approach_U8(u8 *value, int target, s16 step)
{
    if (step == 0) {
        return *value == target;
    }
    if (*value > target) {
        step = (s16) -step;
    }
    s16 next = (s16) (*value + step);
    if (mul32(step, sub32(next, target)) >= 0) {
        *value = (u8) target;
        return TRUE;
    }
    *value = (u8) next;
    return FALSE;
}
CLEAN_AS(func_020e8a38, Approach_U8)

/* func_020e8a94: `value` moved by 1/`divisor` of its 16-bit distance to `target`, by at most
 * `max_step` either way. REQUIRES: divisor != 0; the callers pass 2 to 8. */
void Approach_DivideS16(s16 *value, int target, int divisor, int max_step)
{
    int step = (s16) ((s16) sub32(target, *value) / divisor);
    if (step > max_step) {
        *value = (s16) add32(*value, max_step);
    } else if (step < neg32(max_step)) {
        *value = (s16) sub32(*value, max_step);
    } else {
        *value = (s16) (*value + step);
    }
}
CLEAN_AS(func_020e8a94, Approach_DivideS16)

/* func_020e8b0c: whether `value` lies between the two bounds, both included, in either order. */
BOOL Math_IsBetween(int value, int bound1, int bound2)
{
    if (bound1 < bound2) {
        return value >= bound1 && value <= bound2;
    }
    return value >= bound2 && value <= bound1;
}
CLEAN_AS(func_020e8b0c, Math_IsBetween)

/* func_020e8b4c: the distance between two 16-bit angles, the short way round (0-0x8000). */
int Math_AbsDiff16(int a, int b)
{
    int diff = (s16) sub32(a, b);
    return diff < 0 ? -diff : diff;
}
CLEAN_AS(func_020e8b4c, Math_AbsDiff16)

/* func_020e8b60: `value` moved by the fraction `rate` (20.12) of its distance to `target`, by
 * at most `max_step` either way. */
void Approach_EaseS32(int *value, int target, fx32 rate, int max_step)
{
    if (*value == target) {
        return;
    }
    int step = fx_mul(sub32(target, *value), rate);
    if (step > max_step) {
        step = max_step;
    } else if (step < neg32(max_step)) {
        step = neg32(max_step);
    }
    *value = add32(*value, step);
}
CLEAN_AS(func_020e8b60, Approach_EaseS32)

/* func_020e8bb0: as Approach_EaseS32, and by at least `min_step` without passing the target;
 * the distance left.
 * QUIRK: a step that rounds to 0 counts as one downwards: below the target that lands on the
 * target at once. */
int Approach_EaseS32MinMax(int *value, int target, fx32 rate, int max_step, int min_step)
{
    if (*value != target) {
        int step = fx_mul(sub32(target, *value), rate);
        if (step >= min_step || step <= neg32(min_step)) {
            if (step > max_step) {
                step = max_step;
            }
            if (step < neg32(max_step)) {
                step = neg32(max_step);
            }
            *value = add32(*value, step);
        } else if (step > 0) {
            *value = add32(*value, min_step);
            if (*value > target) {
                *value = target;
            }
        } else {
            *value = sub32(*value, min_step);
            if (*value < target) {
                *value = target;
            }
        }
    }
    int left = sub32(target, *value);
    return left < 0 ? neg32(left) : left;
}
CLEAN_AS(func_020e8bb0, Approach_EaseS32MinMax)

/* func_020e908c: `point` moved in the XZ plane towards `target` by the fraction `rate` of the
 * distance, by at most `max_step` and at least `min_step`; a point closer than `min_step`, or
 * whose step rounds to nothing, lands on the target. The distance left, 0 once there. Y does
 * not move. */
int Approach_PointXZ(Vec3 *point, const Vec3 *target, fx32 rate, fx32 max_step, fx32 min_step)
{
    if (point->x == target->x && point->z == target->z) {
        return 0;
    }
    Vec3 delta;
    func_020eaca0(&delta, target, point);
    fx32 distance = func_020ea9c8(&delta);
    fx32 step = distance < min_step ? 0 : fx_mul(distance, rate);
    if (step == 0) {
        point->x = target->x;
        point->z = target->z;
        return 0;
    }
    if (step > max_step) {
        step = max_step;
    } else if (step < min_step) {
        step = min_step;
    }
    func_020eabc8(&delta, FX_Div(step, distance));
    point->x = add32(point->x, delta.x);
    point->z = add32(point->z, delta.z);
    return sub32(distance, step);
}
CLEAN_AS(func_020e908c, Approach_PointXZ)

/* func_020e91ac: as Approach_PointXZ in three dimensions.
 * QUIRK: the test for being on the target looks at X and Z only, so a point that differs from
 * it in Y alone stays where it is. */
int Approach_Point(Vec3 *point, const Vec3 *target, fx32 rate, fx32 max_step, fx32 min_step)
{
    if (point->x == target->x && point->z == target->z) {
        return 0;
    }
    Vec3 delta;
    func_020eaca0(&delta, target, point);
    fx32 distance = VEC_Mag(&delta);
    fx32 step = distance < min_step ? 0 : fx_mul(distance, rate);
    if (step == 0) {
        *point = *target;
        return 0;
    }
    if (step > max_step) {
        step = max_step;
    } else if (step < min_step) {
        step = min_step;
    }
    func_020eabc8(&delta, FX_Div(step, distance));
    VEC_Add(point, &delta, point);
    return sub32(distance, step);
}
CLEAN_AS(func_020e91ac, Approach_Point)
