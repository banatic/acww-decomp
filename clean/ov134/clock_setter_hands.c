/* The clock setter's analog clock (clock_setter.h): the hands' angles from the time, dragging a
 * hand with the pen (which moves the value by the minutes it turns, kept within `min` and
 * `max`), and the hands spinning to a new time. The clock's middle is at (0x38, 0x34) of the
 * sub screen; angles are 0x10000 a turn, clockwise from twelve. */
#include "clock_setter.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/fx_math.h"
#include "clean.h"
#include "main/date_time.h"
#include "main/sound.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define CLOCK_SETTER_DIAL_X 0x38
#define CLOCK_SETTER_DIAL_Y 0x34
#define CLOCK_SETTER_DIAL_RADIUS 0x28
#define CLOCK_SETTER_TURN 0x10000

/* Twelve hours: the hour hand's turn. */
#define CLOCK_SETTER_HALF_DAY 720
/* The minute hand's angle a minute (0x10000 / 60, rounded down). */
#define CLOCK_SETTER_MINUTE_ANGLE 0x444

/* A hand is grabbed within this angle of the pen's; a tick sounds each time a dragged hand has
 * turned more than CLOCK_SETTER_TICK_ANGLE. */
#define CLOCK_SETTER_GRAB_ANGLE 0x800
#define CLOCK_SETTER_TICK_ANGLE 1000

/* A changed field stays highlighted this many frames. */
#define CLOCK_SETTER_BLINK_FRAMES 10

#define CLOCK_SETTER_SE_TICK 0x1a
#define CLOCK_SETTER_SE_SPIN_END 0x2e
#define CLOCK_SETTER_SOUND_SPIN 0x54

/* The fields the drag looks at, and what DateTime_Compare compares. */
#define CLOCK_SETTER_ALL_FIELDS 0x3f

static int hands_shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

/* func_ov134_0229ac38: the hands a step on toward `target_minutes`; 1 (with the spin's sound
 * stopped and its end played) once they are there. */
int ClockSetter_SpinHands(ClockSetter *self)
{
    int target = self->target_minutes;
    int arrived;
    if (self->clock_minutes == target) {
        arrived = 1;
    } else {
        arrived = ClockSetter_Approach(self, &self->clock_minutes, target, 0x30, 3);
        ClockSetter_HandsFromClock(self);
    }
    if (arrived == 1) {
        SoundSys_StopSound(CLOCK_SETTER_SOUND_SPIN, 1);
        SoundSys_PlaySe(CLOCK_SETTER_SE_SPIN_END);
    }
    return arrived;
}
CLEAN_AS(func_ov134_0229ac38, ClockSetter_SpinHands)

/* func_ov134_0229ac84: `*value` moved toward `target` by half the distance, within
 * `min_step`-`max_step`; 1 when it was within `min_step` and is set to `target`. */
int ClockSetter_Approach(ClockSetter *self, int *value, int target, int max_step, int min_step)
{
    (void) self;
    int now = *value;
    int distance = now > target ? now - target : target - now;
    if (distance < min_step) {
        *value = target;
        return 1;
    }
    int step = distance >> 1;
    if (step > max_step) {
        step = max_step;
    } else if (step < min_step) {
        step = min_step;
    }
    if (now > target) {
        *value -= step;
    } else {
        *value += step;
    }
    return 0;
}
CLEAN_AS(func_ov134_0229ac84, ClockSetter_Approach)

/* func_ov134_0229accc: the drag's time moved by `minutes`. Past `max` (or before `min`), when
 * they bound it, the value holds the bound (AT_MAX or AT_MIN set) and the drag's time is
 * brought back by whole half days, so the hands keep following the pen; otherwise the value is
 * the drag's time. Each field that changed is highlighted and drawn again, and a changed date
 * also does the weekday. */
void ClockSetter_AddMinutes(ClockSetter *self, int minutes)
{
    u8 before[CLOCK_SETTER_FIELDS];
    if (minutes == 0) {
        return;
    }
    for (int field = CLOCK_SETTER_YEAR; field <= CLOCK_SETTER_MINUTE; field++) {
        before[field] = (u8) ClockSetter_Field(self, field);
    }
    before[CLOCK_SETTER_WEEKDAY] = 0; /* set when a date field changed */

    if (minutes > 0) {
        DateTime_AddMinutes(&self->drag, minutes);
    } else {
        DateTime_SubtractMinutes(&self->drag, -minutes);
    }

    int within = 1;
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MAX)) {
        if (DateTime_Compare(&self->max, &self->drag, CLOCK_SETTER_ALL_FIELDS) == -1) {
            int over = DateTime_MinutesBetween(&self->max, &self->drag);
            within = 0;
            MI_CpuCopy8(&self->max, &self->value, sizeof self->value);
            ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_AT_MAX);
            while (over >= CLOCK_SETTER_HALF_DAY) {
                DateTime_SubtractHours(&self->drag, 12);
                over -= CLOCK_SETTER_HALF_DAY;
            }
        } else {
            ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_AT_MAX);
        }
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MIN)) {
        if (DateTime_Compare(&self->min, &self->drag, CLOCK_SETTER_ALL_FIELDS) == 1) {
            int under = DateTime_MinutesBetween(&self->drag, &self->min);
            within = 0;
            MI_CpuCopy8(&self->min, &self->value, sizeof self->value);
            ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_AT_MIN);
            while (under >= CLOCK_SETTER_HALF_DAY) {
                DateTime_AddHours(&self->drag, 12);
                under -= CLOCK_SETTER_HALF_DAY;
            }
        } else {
            ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_AT_MIN);
        }
    }

    if (within) {
        MI_CpuCopy8(&self->drag, &self->value, sizeof self->value);
        ClockSetter_HandsFromValue(self);
    } else {
        ClockSetter_SetHands(self, self->drag.hour, self->drag.minute);
    }

    for (int field = CLOCK_SETTER_YEAR; field <= CLOCK_SETTER_MINUTE; field++) {
        if (ClockSetter_Field(self, field) != before[field]) {
            self->blink[field] = CLOCK_SETTER_BLINK_FRAMES;
            ClockSetter_ColorField(self, field, CLOCK_SETTER_PAL_FOCUS);
            ClockSetter_DrawField(self, (unsigned int) field);
            if (field >= CLOCK_SETTER_YEAR && field <= CLOCK_SETTER_DAY) {
                before[CLOCK_SETTER_WEEKDAY] = 1;
            }
        }
    }
    if (before[CLOCK_SETTER_WEEKDAY] != 0) {
        self->blink[CLOCK_SETTER_WEEKDAY] = CLOCK_SETTER_BLINK_FRAMES;
        ClockSetter_ColorField(self, CLOCK_SETTER_WEEKDAY, CLOCK_SETTER_PAL_FOCUS);
        ClockSetter_DrawWeekday(self);
    }
}
CLEAN_AS(func_ov134_0229accc, ClockSetter_AddMinutes)

/* func_ov134_0229ae78: whether (x, y) is less than `radius` from the clock's middle. */
int ClockSetter_InDial(ClockSetter *self, int x, int y, int radius)
{
    (void) self;
    int dx = x - CLOCK_SETTER_DIAL_X;
    int dy = y - CLOCK_SETTER_DIAL_Y;
    return dx * dx + dy * dy < radius * radius;
}
CLEAN_AS(func_ov134_0229ae78, ClockSetter_InDial)

/* func_ov134_0229ae9c: the shorter turn from angle `from` to angle `to`, signed (a half turn
 * either way gives +0x8000). */
int ClockSetter_AngleDiff(ClockSetter *self, int to, int from)
{
    (void) self;
    int forward = (int) (((u32) to - (u32) from) & (CLOCK_SETTER_TURN - 1));
    int back = (int) (((u32) from - (u32) to) & (CLOCK_SETTER_TURN - 1));
    if (forward > back) {
        forward = -back;
    }
    return forward;
}
CLEAN_AS(func_ov134_0229ae9c, ClockSetter_AngleDiff)

/* func_ov134_0229aed4: the turn from `angle` to the pen at (x, y); 0 at the very middle. */
int ClockSetter_TouchTurn(ClockSetter *self, int x, int y, int angle)
{
    if (x == CLOCK_SETTER_DIAL_X && y == CLOCK_SETTER_DIAL_Y) {
        return 0;
    }
    return ClockSetter_AngleDiff(self, ClockSetter_TouchAngle(self, x, y), angle);
}
CLEAN_AS(func_ov134_0229aed4, ClockSetter_TouchTurn)

/* func_ov134_0229af00: the pen's angle round the clock's middle. */
int ClockSetter_TouchAngle(ClockSetter *self, int x, int y)
{
    (void) self;
    return Math_Atan2(hands_shl(x - CLOCK_SETTER_DIAL_X, 12), hands_shl(-(y - CLOCK_SETTER_DIAL_Y), 12));
}
CLEAN_AS(func_ov134_0229af00, ClockSetter_TouchAngle)

/* func_ov134_0229af14: the hands' angles from `clock_minutes` (taken within twelve hours). */
void ClockSetter_HandsFromClock(ClockSetter *self)
{
    int minutes = self->clock_minutes;
    while (minutes < 0) {
        minutes += CLOCK_SETTER_HALF_DAY;
    }
    while (minutes >= CLOCK_SETTER_HALF_DAY) {
        minutes -= CLOCK_SETTER_HALF_DAY;
    }
    self->hour_angle = (u16) ((minutes << 16) / CLOCK_SETTER_HALF_DAY);
    self->minute_angle = (u16) (CLOCK_SETTER_MINUTE_ANGLE * (minutes % 60));
}
CLEAN_AS(func_ov134_0229af14, ClockSetter_HandsFromClock)

/* func_ov134_0229af60 */
void ClockSetter_HandsFromValue(ClockSetter *self)
{
    ClockSetter_SetHands(self, self->value.hour, self->value.minute);
}
CLEAN_AS(func_ov134_0229af60, ClockSetter_HandsFromValue)

/* func_ov134_0229af74: the hands set to `hour`:`minute`, and `clock_minutes` to the minutes of
 * the day.
 * QUIRK: an hour past 23 is brought back by twelve once only. */
void ClockSetter_SetHands(ClockSetter *self, unsigned int hour, int minute)
{
    self->clock_minutes = (int) ((u32) minute + 60u * hour);
    if (hour >= 12) {
        hour = (u8) (hour - 12);
    }
    int angle = (int) (((u32) minute + 60u * hour) << 16);
    self->hour_angle = (u16) (angle / CLOCK_SETTER_HALF_DAY);
    self->minute_angle = (u16) (u32) (minute * CLOCK_SETTER_MINUTE_ANGLE);
}
CLEAN_AS(func_ov134_0229af74, ClockSetter_SetHands)

/* func_ov134_0229afc0: the hour hand turned to the pen at (x, y): a turn is twelve hours. */
void ClockSetter_TurnHourHand(ClockSetter *self, int x, int y)
{
    int turn = ClockSetter_TouchTurn(self, x, y, self->hour_angle);
    if (turn != 0) {
        ClockSetter_AddMinutes(self, (turn * CLOCK_SETTER_HALF_DAY) >> 16);
    }
}
CLEAN_AS(func_ov134_0229afc0, ClockSetter_TurnHourHand)

/* func_ov134_0229afec: the minute hand turned to the pen at (x, y): a turn is an hour. */
void ClockSetter_TurnMinuteHand(ClockSetter *self, int x, int y)
{
    int turn = ClockSetter_TouchTurn(self, x, y, self->minute_angle);
    if (turn != 0) {
        ClockSetter_AddMinutes(self, (turn * 60) >> 16);
    }
}
CLEAN_AS(func_ov134_0229afec, ClockSetter_TurnMinuteHand)

/* func_ov134_0229b014: the hands a step on toward their target; 1 once they show the value. */
int ClockSetter_SpinHandsHome(ClockSetter *self)
{
    if (ClockSetter_SpinHands(self)) {
        ClockSetter_HandsFromValue(self);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_0229b014, ClockSetter_SpinHandsHome)

/* func_ov134_0229b034: the pen let go of a hand: the fields coloured normally, and when the
 * drag went past a bound the hands' target set to the value (the bound) on the near side of
 * where they are, with the spin's sound; 1 then. */
int ClockSetter_ReleaseHand(ClockSetter *self)
{
    ClockSetter_ResetFieldColors(self);
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MAX) && ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_AT_MAX)) {
        int minutes = ClockSetter_Field(self, CLOCK_SETTER_MINUTE);
        minutes += 60 * ClockSetter_Field(self, CLOCK_SETTER_HOUR);
        self->target_minutes = minutes;
        while (self->target_minutes > self->clock_minutes) {
            self->target_minutes -= CLOCK_SETTER_HALF_DAY;
        }
        SoundSys_StartOnHandle38(CLOCK_SETTER_SOUND_SPIN);
        return 1;
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MIN) && ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_AT_MIN)) {
        int minutes = ClockSetter_Field(self, CLOCK_SETTER_MINUTE);
        minutes += 60 * ClockSetter_Field(self, CLOCK_SETTER_HOUR);
        self->target_minutes = minutes;
        while (self->target_minutes < self->clock_minutes) {
            self->target_minutes += CLOCK_SETTER_HALF_DAY;
        }
        SoundSys_StartOnHandle38(CLOCK_SETTER_SOUND_SPIN);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_0229b034, ClockSetter_ReleaseHand)

/* func_ov134_0229b108: the grabbed hand turned to the pen at (x, y), with a tick each time it
 * has turned far enough. */
void ClockSetter_DragHand(ClockSetter *self, int x, int y)
{
    u16 angle;
    switch (self->hand) {
        case CLOCK_SETTER_HAND_MINUTE:
            ClockSetter_TurnMinuteHand(self, x, y);
            angle = self->minute_angle;
            break;
        case CLOCK_SETTER_HAND_HOUR:
            ClockSetter_TurnHourHand(self, x, y);
            angle = self->hour_angle;
            break;
        default:
            return;
    }
    int turned = ClockSetter_AngleDiff(self, self->tick_angle, angle);
    if (turned < -CLOCK_SETTER_TICK_ANGLE || turned > CLOCK_SETTER_TICK_ANGLE) {
        SoundSys_PlaySe(CLOCK_SETTER_SE_TICK);
        self->tick_angle = angle;
    }
}
CLEAN_AS(func_ov134_0229b108, ClockSetter_DragHand)

/* func_ov134_0229b168: a hand grabbed by the pen at (x, y) on the clock: the minute hand when
 * the pen is within GRAB_ANGLE of it, else the hour hand likewise. A grab takes the focus off
 * the fields and starts the drag from the value. */
int ClockSetter_GrabHand(ClockSetter *self, int x, int y)
{
    if (ClockSetter_InDial(self, x, y, CLOCK_SETTER_DIAL_RADIUS) == 0) {
        return 0;
    }
    int pen = ClockSetter_TouchAngle(self, x, y);
    int grabbed = 0;
    int off = ClockSetter_AngleDiff(self, pen, self->minute_angle);
    if (off >= -CLOCK_SETTER_GRAB_ANGLE && off < CLOCK_SETTER_GRAB_ANGLE) {
        self->hand = CLOCK_SETTER_HAND_MINUTE;
        grabbed = 1;
        self->tick_angle = self->minute_angle;
    } else {
        off = ClockSetter_AngleDiff(self, pen, self->hour_angle);
        if (off >= -CLOCK_SETTER_GRAB_ANGLE && off < CLOCK_SETTER_GRAB_ANGLE) {
            grabbed = 1;
            self->hand = CLOCK_SETTER_HAND_HOUR;
            self->tick_angle = self->hour_angle;
        }
    }
    if (grabbed) {
        ClockSetter_SetFocus(self, CLOCK_SETTER_NO_FIELD);
        MI_CpuCopy8(&self->value, &self->drag, sizeof self->drag);
        ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_AT_MAX | CLOCK_SETTER_FLAG_AT_MIN);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_0229b168, ClockSetter_GrabHand)
