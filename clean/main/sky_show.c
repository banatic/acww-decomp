/* The show of objects in the town's sky (sky_show.h). */
#include "sky_show.h"

#include "clean.h"

#define SKY_SHOW_FIRST_ENTRY 46 /* the entries a place's launches are looked for in */
#define SKY_SHOW_LAST_ENTRY 59  /* (not included) */
#define SKY_SHOW_LAUNCH_SPREAD 0x1e
#define SKY_SHOW_LAUNCH_MIN 0x41
#define SKY_SHOW_PICKS 13
#define SKY_SHOW_PICK_DEFAULT 5
#define SKY_SHOW_LOOK_BASE 0x1d
/* The programs whose first launch is on the common countdown (1-3, 15, 16 and 19); the others
 * draw the four places' timers. */
#define SKY_SHOW_COUNTDOWN_PROGRAMS 0x4c007u

extern const u8 data_020d2315[SKY_SHOW_PICKS];   /* the programs' shares out of 100, summed */
extern const u8 data_020d2378[];                 /* per program: the range of its first launches */
extern const s32 data_020d2354[SKY_SHOW_PLACES]; /* per place: its objects' look, plus 0x1d */
extern u32 func_020644cc(int bound);             /* a random number below `bound` */
extern int func_020bce60(SkyObjects *objects, int place);
extern void *func_020bdc50(SkyObjects *objects, int kind, int arg2, const Vec3 *position, u32 param);
extern void func_02065268(int number);

/* The program's timer: below 0 the program is started (its delay, and a length of `length`
 * plus a random part below `length_spread`); at 0 program `next` is asked for. */
static void run_program(SkyObjects *objects, int delay, int length, int length_spread, int next)
{
    if (objects->program_timer < 0) {
        SkyShow_StartProgram(objects, delay, length, length_spread);
    } else if (objects->program_timer == 0) {
        SkyShow_SetProgram(objects, next);
    }
}

/* func_020bc5c4: 100 frames of large marked launches, then program 16. */
void SkyShow_LargeMarkedThen16(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 16);
    SkyShow_LaunchLargeMarked(objects);
}
CLEAN_AS(func_020bc5c4, SkyShow_LargeMarkedThen16)

/* func_020bc5f8: 225 frames without launches, then program 19. */
void SkyShow_WaitThen19(SkyObjects *objects)
{
    run_program(objects, 0, 225, 0, 19);
}
CLEAN_AS(func_020bc5f8, SkyShow_WaitThen19)

/* func_020bc624: 100 frames of launches from each place, then program 1. */
void SkyShow_EachThen1(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 1);
    SkyShow_LaunchEach(objects);
}
CLEAN_AS(func_020bc624, SkyShow_EachThen1)

/* func_020bc658: 100 frames of large launches, then program 17. */
void SkyShow_LargeThen17(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 17);
    SkyShow_LaunchLarge(objects);
}
CLEAN_AS(func_020bc658, SkyShow_LargeThen17)

/* func_020bc68c: 200 frames of large launches, then program 4. */
void SkyShow_LargeThen4(SkyObjects *objects)
{
    run_program(objects, 0, 200, 0, 4);
    SkyShow_LaunchLarge(objects);
}
CLEAN_AS(func_020bc68c, SkyShow_LargeThen4)

/* func_020bc6c0: 100 frames of launches from each place, then program 15. */
void SkyShow_EachThen15(SkyObjects *objects)
{
    run_program(objects, 0, 100, 0, 15);
    SkyShow_LaunchEach(objects);
}
CLEAN_AS(func_020bc6c0, SkyShow_EachThen15)

/* func_020bc6f4: 100 to 249 frames without launches, then a program drawn. */
void SkyShow_WaitThenAny(SkyObjects *objects)
{
    run_program(objects, 0, 100, 150, SKY_SHOW_ANY_PROGRAM);
}
CLEAN_AS(func_020bc6f4, SkyShow_WaitThenAny)

/* func_020bc720: volleys of three, 140 frames apart and more, for 150 to 749 frames. */
void SkyShow_ThreesDelay140(SkyObjects *objects)
{
    run_program(objects, 140, 150, 600, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchThrees(objects);
}
CLEAN_AS(func_020bc720, SkyShow_ThreesDelay140)

/* func_020bc758: volleys of three, 80 frames apart and more, for 150 to 649 frames. */
void SkyShow_ThreesDelay80(SkyObjects *objects)
{
    run_program(objects, 80, 150, 500, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchThrees(objects);
}
CLEAN_AS(func_020bc758, SkyShow_ThreesDelay80)

/* func_020bc790: volleys of three, 40 frames apart and more, for 150 to 549 frames. */
void SkyShow_ThreesDelay40(SkyObjects *objects)
{
    run_program(objects, 40, 150, 400, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchThrees(objects);
}
CLEAN_AS(func_020bc790, SkyShow_ThreesDelay40)

/* func_020bc7c8: volleys of two, 100 frames apart and more, for 150 to 749 frames. */
void SkyShow_PairsDelay100(SkyObjects *objects)
{
    run_program(objects, 100, 150, 600, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchPairs(objects);
}
CLEAN_AS(func_020bc7c8, SkyShow_PairsDelay100)

/* func_020bc800: volleys of two, 60 frames apart and more, for 150 to 649 frames. */
void SkyShow_PairsDelay60(SkyObjects *objects)
{
    run_program(objects, 60, 150, 500, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchPairs(objects);
}
CLEAN_AS(func_020bc800, SkyShow_PairsDelay60)

/* func_020bc838: volleys of two, 30 frames apart and more, for 150 to 549 frames. */
void SkyShow_PairsDelay30(SkyObjects *objects)
{
    run_program(objects, 30, 150, 400, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchPairs(objects);
}
CLEAN_AS(func_020bc838, SkyShow_PairsDelay30)

/* func_020bc870: launches from each place, 0x41 to 0x16c frames apart, for 100 to 699 frames. */
void SkyShow_EachDelay300(SkyObjects *objects)
{
    run_program(objects, 300, 100, 600, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchEach(objects);
}
CLEAN_AS(func_020bc870, SkyShow_EachDelay300)

/* func_020bc8ac: launches from each place, 0x41 to 0xe0 frames apart, for 100 to 599 frames. */
void SkyShow_EachDelay160(SkyObjects *objects)
{
    run_program(objects, 160, 100, 500, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchEach(objects);
}
CLEAN_AS(func_020bc8ac, SkyShow_EachDelay160)

/* func_020bc8e4: launches from each place, 0x41 to 0x72 frames apart, for 100 to 499 frames. */
void SkyShow_EachDelay50(SkyObjects *objects)
{
    run_program(objects, 50, 100, 400, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchEach(objects);
}
CLEAN_AS(func_020bc8e4, SkyShow_EachDelay50)

/* func_020bc91c: large launches, 0x41 to 0x108 frames apart, for 100 to 699 frames. */
void SkyShow_LargeDelay200(SkyObjects *objects)
{
    run_program(objects, 200, 100, 600, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchLarge(objects);
}
CLEAN_AS(func_020bc91c, SkyShow_LargeDelay200)

/* func_020bc954: large launches, 0x41 to 0xa4 frames apart, for 100 to 599 frames. */
void SkyShow_LargeDelay100(SkyObjects *objects)
{
    run_program(objects, 100, 100, 500, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchLarge(objects);
}
CLEAN_AS(func_020bc954, SkyShow_LargeDelay100)

/* func_020bc98c: large launches, 0x41 to 0x54 frames apart, for 100 to 499 frames. */
void SkyShow_LargeDelay20(SkyObjects *objects)
{
    run_program(objects, 20, 100, 400, SKY_SHOW_ANY_PROGRAM);
    SkyShow_LaunchLarge(objects);
}
CLEAN_AS(func_020bc98c, SkyShow_LargeDelay20)

/* func_020bc9c4: program `program` set (SKY_SHOW_ANY_PROGRAM: one of 1 to 13 drawn by the shares
 * of data_020d2315, 5 when the draw passes them all), and when it has a range its first
 * launches drawn below it: the common countdown's for the programs of
 * SKY_SHOW_COUNTDOWN_PROGRAMS, else the four places' timers.
 * REQUIRES: the program is one of the table's (0 to 20). */
void SkyShow_SetProgram(SkyObjects *objects, int program)
{
    if (program == SKY_SHOW_ANY_PROGRAM) {
        u32 draw = func_020644cc(100);
        int picked = SKY_SHOW_PICK_DEFAULT;
        for (int i = 1; i < 1 + SKY_SHOW_PICKS; i++) {
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
    if (bit <= 18 && ((1u << bit) & SKY_SHOW_COUNTDOWN_PROGRAMS) != 0) {
        objects->countdown = (s32) func_020644cc(range);
    } else {
        objects->launch_timers[0] = (s32) func_020644cc(range);
        objects->launch_timers[1] = (s32) func_020644cc(range);
        objects->launch_timers[2] = (s32) func_020644cc(range);
        objects->launch_timers[3] = (s32) func_020644cc(range);
    }
}
CLEAN_AS(func_020bc9c4, SkyShow_SetProgram)

/* func_020bca80: a program started: the delay between its launches, and its length, `length`
 * plus a random part below `length_spread` when that is positive. */
void SkyShow_StartProgram(SkyObjects *objects, int delay, int length, int length_spread)
{
    objects->launch_delay = delay;
    objects->program_timer = length + (length_spread > 0 ? (int) func_020644cc(length_spread) : 0);
}
CLEAN_AS(func_020bca80, SkyShow_StartProgram)

/* The places' timers run down: a place whose timer reaches 0 launches when it is free, else
 * tries again at the next frame; 1 when all four are idle afterwards. */
static int run_place_timers(SkyObjects *objects)
{
    int all_idle = 1;
    for (int place = 0; place < SKY_SHOW_PLACES; place++) {
        s32 *timer = &objects->launch_timers[place];
        if (*timer > 0) {
            (*timer)--;
            if (*timer <= 0) {
                if (SkyShow_PlaceFree(objects, place)) {
                    SkyShow_Launch(objects, place, 0, 0);
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
    objects->launch_timers[place] = objects->launch_delay + (s32) func_020644cc(SKY_SHOW_LAUNCH_SPREAD);
}

/* func_020bcab0: launches by the places' timers; once all four are idle, three of them (all but
 * one drawn at random) set to launch after the delay. */
void SkyShow_LaunchThrees(SkyObjects *objects)
{
    if (!run_place_timers(objects)) {
        return;
    }
    int skipped = (int) func_020644cc(SKY_SHOW_PLACES);
    for (int place = 0; place < SKY_SHOW_PLACES; place++) {
        if (place != skipped) {
            set_place_timer(objects, place);
        }
    }
}
CLEAN_AS(func_020bcab0, SkyShow_LaunchThrees)

/* func_020bcb84: launches by the places' timers; once all four are idle, two of them (one drawn
 * at random, another drawn among the three others) set to launch after the delay. */
void SkyShow_LaunchPairs(SkyObjects *objects)
{
    if (!run_place_timers(objects)) {
        return;
    }
    int first = (int) func_020644cc(SKY_SHOW_PLACES);
    int second = (first + 1 + (int) func_020644cc(3)) & 3;
    for (int place = 0; place < SKY_SHOW_PLACES; place++) {
        if (place == first || place == second) {
            set_place_timer(objects, place);
        }
    }
}
CLEAN_AS(func_020bcb84, SkyShow_LaunchPairs)

/* func_020bcc70: each place on its own timer: when it runs out and the place is free, a launch
 * and the next one's time; else it stays run out and is tried again at the next frame. */
void SkyShow_LaunchEach(SkyObjects *objects)
{
    for (int place = 0; place < SKY_SHOW_PLACES; place++) {
        s32 *timer = &objects->launch_timers[place];
        (*timer)--;
        if (*timer > 0) {
            continue;
        }
        if (SkyShow_PlaceFree(objects, place)) {
            SkyShow_Launch(objects, place, 0, 0);
            SkyShow_NextLaunchTime(objects, timer);
        }
    }
}
CLEAN_AS(func_020bcc70, SkyShow_LaunchEach)

/* The common countdown: when it runs out, a large launch (`marked` or not) from a place drawn at
 * random when that place can take one (func_020bce60), and the next one's time. */
static void launch_large(SkyObjects *objects, int marked)
{
    objects->countdown--;
    if (objects->countdown > 0) {
        return;
    }
    int place = (int) func_020644cc(SKY_SHOW_PLACES);
    if (!func_020bce60(objects, place)) {
        return;
    }
    SkyShow_Launch(objects, place, 1, marked);
    SkyShow_NextLaunchTime(objects, &objects->countdown);
}

/* func_020bcce4: large marked launches on the common countdown. */
void SkyShow_LaunchLargeMarked(SkyObjects *objects)
{
    launch_large(objects, 1);
}
CLEAN_AS(func_020bcce4, SkyShow_LaunchLargeMarked)

/* func_020bcd30: large launches on the common countdown. */
void SkyShow_LaunchLarge(SkyObjects *objects)
{
    launch_large(objects, 0);
}
CLEAN_AS(func_020bcd30, SkyShow_LaunchLarge)

/* func_020bcd7c: the time to the next launch: 0x41 frames plus a random part below the delay
 * when that is positive. */
void SkyShow_NextLaunchTime(SkyObjects *objects, s32 *timer)
{
    s32 delay = objects->launch_delay;
    *timer = (delay > 0 ? (s32) func_020644cc(delay) : 0) + SKY_SHOW_LAUNCH_MIN;
}
CLEAN_AS(func_020bcd7c, SkyShow_NextLaunchTime)

/* func_020bcda0: a launch from `place`: with the sky drawn an object of kind SKY_OBJECT_SHOW
 * added (its look from the place, the place, `large` and `marked` in its parameter); else
 * func_02065268 given place + 5 for a large one, place + 1 for another.
 * REQUIRES: place is 0 to 3. */
void SkyShow_Launch(SkyObjects *objects, int place, int large, int marked)
{
    if (data_021f6cd8 != 0) {
        u32 param = ((u32) (data_020d2354[place] - SKY_SHOW_LOOK_BASE) & SKY_SHOW_PARAM_LOOK) | (((u32) place & 3) << 8) |
                    ((u32) large << 31) | ((u32) marked << 28);
        func_020bdc50(objects, SKY_OBJECT_SHOW, SKY_OBJECT_COUNT, NULL, param);
    } else if (large != 0) {
        func_02065268(place + 5);
    } else {
        func_02065268(place + 1);
    }
}
CLEAN_AS(func_020bcda0, SkyShow_Launch)

/* func_020bcdf8: 1 when `place` may launch: none of entries 46 to 58 is an object of the show
 * launched from it, nor a large one whose bit 29 is clear. */
int SkyShow_PlaceFree(SkyObjects *objects, int place)
{
    for (int i = SKY_SHOW_FIRST_ENTRY; i < SKY_SHOW_LAST_ENTRY; i++) {
        const SkyObject *object = &objects->entries[i];
        if (object->kind != SKY_OBJECT_SHOW) {
            continue;
        }
        u32 param = object->param;
        if (((param & SKY_SHOW_PARAM_PLACE) >> 8) == (u32) place) {
            return 0;
        }
        if ((param & SKY_SHOW_PARAM_LARGE) != 0 && (param & SKY_SHOW_PARAM_BIT29) == 0) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020bcdf8, SkyShow_PlaceFree)
