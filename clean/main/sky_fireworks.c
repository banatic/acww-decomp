/* The fireworks show in the town's sky (sky_fireworks.h). */
#include "sky_fireworks.h"

#include "clean.h"
#include "event_announce.h"
#include "main_random.h"
#include "scene_lights.h"
#include "sky_objects.h"

#define SKY_FIREWORKS_FIRST_ENTRY 46 /* the entries a place's launches are looked for in */
#define SKY_FIREWORKS_LAST_ENTRY 59  /* (not included) */
#define SKY_FIREWORKS_LAUNCH_SPREAD 0x1e
#define SKY_FIREWORKS_LAUNCH_MIN 0x41
#define SKY_FIREWORKS_PICKS 13
#define SKY_FIREWORKS_PICK_DEFAULT 5
#define SKY_FIREWORKS_LOOK_BASE 0x1d
/* The programs whose first launch is on the common countdown (1-3, 15, 16 and 19); the others
 * draw the four places' timers. */
#define SKY_FIREWORKS_COUNTDOWN_PROGRAMS 0x4c007u

extern const u8 data_020d2315[SKY_FIREWORKS_PICKS];   /* the programs' shares out of 100, summed */
extern const u8 data_020d2378[];                      /* per program: the range of its first launches */
extern const s32 data_020d2354[SKY_FIREWORKS_PLACES]; /* per place: its objects' look, plus 0x1d */

/* The program's timer: below 0 the program is started (its delay, and a length of `length`
 * plus a random part below `length_spread`); at 0 program `next` is asked for. */
static void run_program(SkyObjects *objects, int delay, int length, int length_spread, int next)
{
    if (objects->program_timer < 0) {
        SkyFireworks_StartProgram(objects, delay, length, length_spread);
    } else if (objects->program_timer == 0) {
        SkyFireworks_SetProgram(objects, next);
    }
}

/* func_020bc5c4: 100 frames of large marked launches, then program 16. */
void SkyFireworks_LargeMarkedThen16(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 16);
    SkyFireworks_LaunchLargeMarked(objects);
}
CLEAN_AS(func_020bc5c4, SkyFireworks_LargeMarkedThen16)

/* func_020bc5f8: 225 frames without launches, then program 19. */
void SkyFireworks_WaitThen19(SkyObjects *objects)
{
    run_program(objects, 0, 225, 0, 19);
}
CLEAN_AS(func_020bc5f8, SkyFireworks_WaitThen19)

/* func_020bc624: 100 frames of launches from each place, then program 1. */
void SkyFireworks_EachThen1(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 1);
    SkyFireworks_LaunchEach(objects);
}
CLEAN_AS(func_020bc624, SkyFireworks_EachThen1)

/* func_020bc658: 100 frames of large launches, then program 17. */
void SkyFireworks_LargeThen17(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 17);
    SkyFireworks_LaunchLarge(objects);
}
CLEAN_AS(func_020bc658, SkyFireworks_LargeThen17)

/* func_020bc68c: 200 frames of large launches, then program 4. */
void SkyFireworks_LargeThen4(SkyObjects *objects)
{
    run_program(objects, 0, 200, 0, 4);
    SkyFireworks_LaunchLarge(objects);
}
CLEAN_AS(func_020bc68c, SkyFireworks_LargeThen4)

/* func_020bc6c0: 100 frames of launches from each place, then program 15. */
void SkyFireworks_EachThen15(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 15);
    SkyFireworks_LaunchEach(objects);
}
CLEAN_AS(func_020bc6c0, SkyFireworks_EachThen15)

/* func_020bc6f4: 100 to 249 frames without launches, then a program drawn. */
void SkyFireworks_WaitThenAny(SkyObjects *objects)
{
    run_program(objects, 0, 100, 150, SKY_FIREWORKS_ANY_PROGRAM);
}
CLEAN_AS(func_020bc6f4, SkyFireworks_WaitThenAny)

/* func_020bc720: volleys of three, 140 frames apart and more, for 150 to 749 frames. */
void SkyFireworks_ThreesDelay140(SkyObjects *objects)
{
    run_program(objects, 140, 150, 600, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchThrees(objects);
}
CLEAN_AS(func_020bc720, SkyFireworks_ThreesDelay140)

/* func_020bc758: volleys of three, 80 frames apart and more, for 150 to 649 frames. */
void SkyFireworks_ThreesDelay80(SkyObjects *objects)
{
    run_program(objects, 80, 150, 500, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchThrees(objects);
}
CLEAN_AS(func_020bc758, SkyFireworks_ThreesDelay80)

/* func_020bc790: volleys of three, 40 frames apart and more, for 150 to 549 frames. */
void SkyFireworks_ThreesDelay40(SkyObjects *objects)
{
    run_program(objects, 40, 150, 400, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchThrees(objects);
}
CLEAN_AS(func_020bc790, SkyFireworks_ThreesDelay40)

/* func_020bc7c8: volleys of two, 100 frames apart and more, for 150 to 749 frames. */
void SkyFireworks_PairsDelay100(SkyObjects *objects)
{
    run_program(objects, 100, 150, 600, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchPairs(objects);
}
CLEAN_AS(func_020bc7c8, SkyFireworks_PairsDelay100)

/* func_020bc800: volleys of two, 60 frames apart and more, for 150 to 649 frames. */
void SkyFireworks_PairsDelay60(SkyObjects *objects)
{
    run_program(objects, 60, 150, 500, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchPairs(objects);
}
CLEAN_AS(func_020bc800, SkyFireworks_PairsDelay60)

/* func_020bc838: volleys of two, 30 frames apart and more, for 150 to 549 frames. */
void SkyFireworks_PairsDelay30(SkyObjects *objects)
{
    run_program(objects, 30, 150, 400, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchPairs(objects);
}
CLEAN_AS(func_020bc838, SkyFireworks_PairsDelay30)

/* func_020bc870: launches from each place, 0x41 to 0x16c frames apart, for 100 to 699 frames. */
void SkyFireworks_EachDelay300(SkyObjects *objects)
{
    run_program(objects, 300, 100, 600, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchEach(objects);
}
CLEAN_AS(func_020bc870, SkyFireworks_EachDelay300)

/* func_020bc8ac: launches from each place, 0x41 to 0xe0 frames apart, for 100 to 599 frames. */
void SkyFireworks_EachDelay160(SkyObjects *objects)
{
    run_program(objects, 160, 100, 500, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchEach(objects);
}
CLEAN_AS(func_020bc8ac, SkyFireworks_EachDelay160)

/* func_020bc8e4: launches from each place, 0x41 to 0x72 frames apart, for 100 to 499 frames. */
void SkyFireworks_EachDelay50(SkyObjects *objects)
{
    run_program(objects, 50, 100, 400, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchEach(objects);
}
CLEAN_AS(func_020bc8e4, SkyFireworks_EachDelay50)

/* func_020bc91c: large launches, 0x41 to 0x108 frames apart, for 100 to 699 frames. */
void SkyFireworks_LargeDelay200(SkyObjects *objects)
{
    run_program(objects, 200, 100, 600, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchLarge(objects);
}
CLEAN_AS(func_020bc91c, SkyFireworks_LargeDelay200)

/* func_020bc954: large launches, 0x41 to 0xa4 frames apart, for 100 to 599 frames. */
void SkyFireworks_LargeDelay100(SkyObjects *objects)
{
    run_program(objects, 100, 100, 500, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchLarge(objects);
}
CLEAN_AS(func_020bc954, SkyFireworks_LargeDelay100)

/* func_020bc98c: large launches, 0x41 to 0x54 frames apart, for 100 to 499 frames. */
void SkyFireworks_LargeDelay20(SkyObjects *objects)
{
    run_program(objects, 20, 100, 400, SKY_FIREWORKS_ANY_PROGRAM);
    SkyFireworks_LaunchLarge(objects);
}
CLEAN_AS(func_020bc98c, SkyFireworks_LargeDelay20)

/* func_020bc9c4: program `program` set (SKY_FIREWORKS_ANY_PROGRAM: one of 1 to 13 drawn by the shares
 * of data_020d2315, 5 when the draw passes them all), and when it has a range its first
 * launches drawn below it: the common countdown's for the programs of
 * SKY_FIREWORKS_COUNTDOWN_PROGRAMS, else the four places' timers.
 * REQUIRES: the program is one of the table's (0 to 20). */
void SkyFireworks_SetProgram(SkyObjects *objects, int program)
{
    if (program == SKY_FIREWORKS_ANY_PROGRAM) {
        u32 draw = MainRandom_Below(100);
        int picked = SKY_FIREWORKS_PICK_DEFAULT;
        for (int i = 1; i < 1 + SKY_FIREWORKS_PICKS; i++) {
            if (draw < data_020d2315[i - 1]) {
                picked = i;
                break;
            }
        }
        objects->program = picked;
    } else {
        objects->program = program;
    }

    u32 current = (u32) objects->program;
    int range = data_020d2378[current];
    if (range <= 0) {
        return;
    }
    u32 bit = current - 1;
    if (bit <= 18 && ((1u << bit) & SKY_FIREWORKS_COUNTDOWN_PROGRAMS) != 0) {
        objects->countdown = (s32) MainRandom_Below(range);
    } else {
        objects->launch_timers[0] = (s32) MainRandom_Below(range);
        objects->launch_timers[1] = (s32) MainRandom_Below(range);
        objects->launch_timers[2] = (s32) MainRandom_Below(range);
        objects->launch_timers[3] = (s32) MainRandom_Below(range);
    }
}
CLEAN_AS(func_020bc9c4, SkyFireworks_SetProgram)

/* func_020bca80: a program started: the delay between its launches, and its length, `length`
 * plus a random part below `length_spread` when that is positive. */
void SkyFireworks_StartProgram(SkyObjects *objects, int delay, int length, int length_spread)
{
    objects->launch_delay = delay;
    objects->program_timer = length + (length_spread > 0 ? (int) MainRandom_Below(length_spread) : 0);
}
CLEAN_AS(func_020bca80, SkyFireworks_StartProgram)

/* The places' timers run down: a place whose timer reaches 0 launches when it is free, else
 * tries again at the next frame; 1 when all four are idle afterwards. */
static int run_place_timers(SkyObjects *objects)
{
    int all_idle = 1;
    for (int place = 0; place < SKY_FIREWORKS_PLACES; place++) {
        s32 *timer = &objects->launch_timers[place];
        if (*timer > 0) {
            (*timer)--;
            if (*timer <= 0) {
                if (SkyFireworks_PlaceFree(objects, place)) {
                    SkyFireworks_Launch(objects, place, 0, 0);
                } else {
                    *timer = 1;
                }
            }
        }
        all_idle = all_idle && *timer <= 0;
    }
    return all_idle;
}

/* A place's timer set to the delay plus a random part below 30 frames. */
static void set_place_timer(SkyObjects *objects, int place)
{
    objects->launch_timers[place] = objects->launch_delay + (s32) MainRandom_Below(SKY_FIREWORKS_LAUNCH_SPREAD);
}

/* func_020bcab0: launches by the places' timers; once all four are idle, three of them (all but
 * one drawn at random) set to launch after the delay. */
void SkyFireworks_LaunchThrees(SkyObjects *objects)
{
    if (!run_place_timers(objects)) {
        return;
    }
    int skipped = (int) MainRandom_Below(SKY_FIREWORKS_PLACES);
    for (int place = 0; place < SKY_FIREWORKS_PLACES; place++) {
        if (place != skipped) {
            set_place_timer(objects, place);
        }
    }
}
CLEAN_AS(func_020bcab0, SkyFireworks_LaunchThrees)

/* func_020bcb84: launches by the places' timers; once all four are idle, two of them (one drawn
 * at random, another drawn among the three others) set to launch after the delay. */
void SkyFireworks_LaunchPairs(SkyObjects *objects)
{
    if (!run_place_timers(objects)) {
        return;
    }
    int first = (int) MainRandom_Below(SKY_FIREWORKS_PLACES);
    int second = (first + 1 + (int) MainRandom_Below(3)) & 3;
    for (int place = 0; place < SKY_FIREWORKS_PLACES; place++) {
        if (place == first || place == second) {
            set_place_timer(objects, place);
        }
    }
}
CLEAN_AS(func_020bcb84, SkyFireworks_LaunchPairs)

/* func_020bcc70: each place on its own timer: when it runs out and the place is free, a launch
 * and the next one's time; else it stays run out and is tried again at the next frame. */
void SkyFireworks_LaunchEach(SkyObjects *objects)
{
    for (int place = 0; place < SKY_FIREWORKS_PLACES; place++) {
        s32 *timer = &objects->launch_timers[place];
        (*timer)--;
        if (*timer > 0) {
            continue;
        }
        if (SkyFireworks_PlaceFree(objects, place)) {
            SkyFireworks_Launch(objects, place, 0, 0);
            SkyFireworks_NextLaunchTime(objects, timer);
        }
    }
}
CLEAN_AS(func_020bcc70, SkyFireworks_LaunchEach)

/* The common countdown: when it runs out, a large launch (`marked` or not) from a place drawn at
 * random when that place can take one (func_020bce60), and the next one's time. */
static void launch_large(SkyObjects *objects, int marked)
{
    objects->countdown--;
    if (objects->countdown > 0) {
        return;
    }
    int place = (int) MainRandom_Below(SKY_FIREWORKS_PLACES);
    if (!SkyFireworks_PlaceFreeForLarge(objects, place)) {
        return;
    }
    SkyFireworks_Launch(objects, place, 1, marked);
    SkyFireworks_NextLaunchTime(objects, &objects->countdown);
}

/* func_020bcce4: large marked launches on the common countdown. */
void SkyFireworks_LaunchLargeMarked(SkyObjects *objects)
{
    launch_large(objects, 1);
}
CLEAN_AS(func_020bcce4, SkyFireworks_LaunchLargeMarked)

/* func_020bcd30: large launches on the common countdown. */
void SkyFireworks_LaunchLarge(SkyObjects *objects)
{
    launch_large(objects, 0);
}
CLEAN_AS(func_020bcd30, SkyFireworks_LaunchLarge)

/* func_020bcd7c: the time to the next launch: 0x41 frames plus a random part below the delay
 * when that is positive. */
void SkyFireworks_NextLaunchTime(SkyObjects *objects, s32 *timer)
{
    s32 delay = objects->launch_delay;
    *timer = (delay > 0 ? (s32) MainRandom_Below(delay) : 0) + SKY_FIREWORKS_LAUNCH_MIN;
}
CLEAN_AS(func_020bcd7c, SkyFireworks_NextLaunchTime)

/* func_020bcda0: a launch from `place`: with the sky drawn an object of kind SKY_OBJECT_FIREWORK
 * added (its look from the place, the place, `large` and `marked` in its parameter); else
 * SceneLights_StartFlash given place + 5 for a large one, place + 1 for another.
 * REQUIRES: place is 0 to 3. */
void SkyFireworks_Launch(SkyObjects *objects, int place, int large, int marked)
{
    if (data_021f6cd8 != 0) {
        u32 param = ((u32) (data_020d2354[place] - SKY_FIREWORKS_LOOK_BASE) & SKY_FIREWORKS_PARAM_LOOK) |
                    (((u32) place & 3) << 8) | ((u32) large << 31) | ((u32) marked << 28);
        SkyObjects_Add(objects, SKY_OBJECT_FIREWORK, SKY_OBJECT_COUNT, NULL, param);
    } else if (large != 0) {
        SceneLights_StartFlash(place + 5);
    } else {
        SceneLights_StartFlash(place + 1);
    }
}
CLEAN_AS(func_020bcda0, SkyFireworks_Launch)

/* func_020bcdf8: 1 when `place` may launch: none of entries 46 to 58 is an object of the show
 * launched from it, nor a large one whose bit 29 is clear. */
int SkyFireworks_PlaceFree(SkyObjects *objects, int place)
{
    for (int i = SKY_FIREWORKS_FIRST_ENTRY; i < SKY_FIREWORKS_LAST_ENTRY; i++) {
        const SkyObject *object = &objects->entries[i];
        if (object->kind != SKY_OBJECT_FIREWORK) {
            continue;
        }
        u32 param = object->param;
        if (((param & SKY_FIREWORKS_PARAM_PLACE) >> 8) == (u32) place) {
            return 0;
        }
        if ((param & SKY_FIREWORKS_PARAM_LARGE) != 0 && (param & SKY_FIREWORKS_PARAM_BIT29) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020bcdf8, SkyFireworks_PlaceFree)

/* ---- When the show runs, and its programs */

#include "date_time.h"
#include "event_calendar.h"
#include "ov004/member_pointer.h"
#include "scene_query.h"
#include "session.h"

#define SKY_FIREWORKS_PROGRAMS 20
#define SKY_FIREWORKS_EVENT 0x13 /* the calendar event of the show */
#define SKY_FIREWORKS_EVENT_F 0xf
#define SKY_FIREWORKS_UNTIL_HOUR 2 /* with event 0x13 the show runs until 1:59 */
#define SKY_FIREWORKS_SCENE_2C 0x2c
#define SKY_FIREWORKS_MIDNIGHT_PROGRAM 18
#define SKY_FIREWORKS_FIRST_PROGRAM 14 /* or SKY_FIREWORKS_SECOND_FIRST_PROGRAM, at random */
#define SKY_FIREWORKS_SECOND_FIRST_PROGRAM 16

extern NetSession *data_020ccf94;
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u32 data_021f6ccc; /* the programs' table was filled */
extern MemberPointer data_021f6ed0[SKY_FIREWORKS_PROGRAMS];
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_020e5a20, data_020e5ad0, data_020e59d0, data_020e5c20, data_020e59e8, data_020e5cf0,
    data_020e59f0, data_020e59e0, data_020e5b18, data_020e5b20, data_020e5d80, data_020e5b10, data_020e5b08, data_020e5a08,
    data_020e5cd0, data_020e5b40, data_020e5a88, data_020e5a10, data_020e5a40;

/* The programs, 1 to 19 (SkyFireworks_LargeDelay20 to SkyFireworks_LargeMarkedThen16). */
static const MemberPointer *const sky_fireworks_program_constants[SKY_FIREWORKS_PROGRAMS] = {
    &__ptmf_null,   &data_020e5a20, &data_020e5ad0, &data_020e59d0, &data_020e5c20, &data_020e59e8, &data_020e5cf0,
    &data_020e59f0, &data_020e59e0, &data_020e5b18, &data_020e5b20, &data_020e5d80, &data_020e5b10, &data_020e5b08,
    &data_020e5a08, &data_020e5cd0, &data_020e5b40, &data_020e5a88, &data_020e5a10, &data_020e5a40,
};

/* func_020bce60: 1 when `place` may launch a large object: none of entries 46 to 58 is an
 * object of the show launched from it, nor one whose bit 29 is clear. */
int SkyFireworks_PlaceFreeForLarge(SkyObjects *objects, int place)
{
    for (int i = SKY_FIREWORKS_FIRST_ENTRY; i < SKY_FIREWORKS_LAST_ENTRY; i++) {
        const SkyObject *object = &objects->entries[i];
        if (object->kind != SKY_OBJECT_FIREWORK) {
            continue;
        }
        u32 param = object->param;
        if ((int) ((param & SKY_FIREWORKS_PARAM_PLACE) >> 8) == place || (param & SKY_FIREWORKS_PARAM_BIT29) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020bce60, SkyFireworks_PlaceFreeForLarge)

/* Whether the show runs now: while calendar event 0x13 is on, until 1:59 (`midnight` set at
 * 0:00:00 exactly); else while the event of func_02041614 is 0xf: in scene 0x31 or in a
 * session while calendar event 0xf is on, otherwise always; else in scene 0x2c while event 0xf
 * is running. */
static int sky_fireworks_is_on(SkyObjects *objects, int *midnight)
{
    u32 event = EventAnnounce_MusicEvent();
    DateTime now = {0};
    DateTime when;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &when, sizeof(DateTime));
    if (EventCalendar_State(SKY_FIREWORKS_EVENT, &when, 1) != EVENT_CALENDAR_OFF) {
        int hour = objects->time.hour;
        if (hour >= SKY_FIREWORKS_UNTIL_HOUR) {
            return 0;
        }
        *midnight = hour == 0 && objects->time.minute == 0 && objects->second == 0;
        return 1;
    }
    if (event == SKY_FIREWORKS_EVENT_F) {
        if (SceneQuery_CurrentIs31() || Session_IsLinked(data_020ccf94)) {
            MI_CpuCopy8(&now, &when, sizeof(DateTime));
            return EventCalendar_State(SKY_FIREWORKS_EVENT_F, &when, 0) != EVENT_CALENDAR_OFF;
        }
        return 1;
    }
    if (SceneQuery_Current() != SKY_FIREWORKS_SCENE_2C) {
        return 0;
    }
    MI_CpuCopy8(&now, &when, sizeof(DateTime));
    return EventCalendar_State(SKY_FIREWORKS_EVENT_F, &when, 1) == EVENT_CALENDAR_ON;
}

/* func_020bd3b4: a frame of the show. While it runs: without a program one is set (18 when it
 * starts at midnight, else 14 or 16 at random) with its timer at 0; the timer counts down and
 * the program's function runs (from the table of members data_021f6ed0, filled once). While it
 * does not run, the program, its timers and the delay are cleared.
 * REQUIRES: SkyObjects.program is 0 to 19. */
void SkyFireworks_Run(SkyObjects *objects)
{
    int midnight = 0;
    if (!sky_fireworks_is_on(objects, &midnight)) {
        objects->program = 0;
        objects->program_timer = 0;
        objects->countdown = 0;
        for (int place = 0; place < SKY_FIREWORKS_PLACES; place++) {
            objects->launch_timers[place] = 0;
        }
        objects->launch_delay = 0;
        return;
    }
    MemberTable_InitOnce(&data_021f6ccc, data_021f6ed0, sky_fireworks_program_constants, SKY_FIREWORKS_PROGRAMS);
    if (objects->program == 0) {
        int program = SKY_FIREWORKS_MIDNIGHT_PROGRAM;
        if (!midnight) {
            program = MainRandom_Below(2) == 0 ? SKY_FIREWORKS_FIRST_PROGRAM : SKY_FIREWORKS_SECOND_FIRST_PROGRAM;
        }
        SkyFireworks_SetProgram(objects, program);
        objects->program_timer = 0;
    }
    objects->program_timer--;
    MemberPointer member = data_021f6ed0[objects->program];
    MemberPointer_CallVoid(&member, objects);
}
CLEAN_AS(func_020bd3b4, SkyFireworks_Run)
