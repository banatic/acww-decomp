/* Moving a value towards a target a step at a time, the way the game animates positions,
 * angles, colours and timers: by a fixed step that stops on the target, by a fraction of the
 * distance left, and the same for points. Also the counters that run down to zero and two
 * small comparisons the same callers use. */
#ifndef CLEAN_AUTOLOAD_2_APPROACH_H
#define CLEAN_AUTOLOAD_2_APPROACH_H

#include "types.h"
#include "vector.h"

u16 Countdown_Tick16(u16 *counter);
u8 Countdown_Tick8(u8 *counter);
int Approach_S16Wrapped(s16 *value, int target, s16 step);
int Approach_S32(int *value, int target, int step);
int Approach_S32Again(int *value, int target, int step);
int Approach_S16(s16 *value, int target, s16 step);
int Approach_U8(u8 *value, int target, s16 step);
void Approach_DivideS16(s16 *value, int target, int divisor, int max_step);
BOOL Math_IsBetween(int value, int bound1, int bound2);
int Math_AbsDiff16(int a, int b);
void Approach_EaseS32(int *value, int target, fx32 rate, int max_step);
int Approach_EaseS32MinMax(int *value, int target, fx32 rate, int max_step, int min_step);
int Approach_PointXZ(Vec3 *point, const Vec3 *target, fx32 rate, fx32 max_step, fx32 min_step);
int Approach_Point(Vec3 *point, const Vec3 *target, fx32 rate, fx32 max_step, fx32 min_step);

#endif
