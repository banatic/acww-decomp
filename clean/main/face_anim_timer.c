/* The timer of a face's first animation (face_anim_timer.h). */
#include "face_anim_timer.h"

#include "autoload_2/fx_math.h"
#include "clean.h"

static_assert(sizeof(FaceAnimTimer) == 2, "FaceAnimTimer size");

/* The game's main generator (main_random.h). */
extern Random data_021cb5a0;

/* A pause lasts 30 steps and a number below 90 more. */
#define FACE_ANIM_TIMER_PAUSE_RANGE 90
#define FACE_ANIM_TIMER_PAUSE_MIN 30

/* func_020645bc: no pause; new repeats when none are left. */
void FaceAnimTimer_Restart(FaceAnimTimer *timer)
{
    timer->pause = 0;
    if (timer->repeats == 0) {
        FaceAnimTimer_NewRepeats(timer);
    }
}
CLEAN_AS(func_020645bc, FaceAnimTimer_Restart)

/* func_020645d4: no repeats and no pause. */
void FaceAnimTimer_Reset(FaceAnimTimer *timer)
{
    timer->repeats = 0;
    timer->pause = 0;
}
CLEAN_AS(func_020645d4, FaceAnimTimer_Reset)

/* func_020645e0: one step. During a pause it counts down and answers 0; after it, each step
 * spends a repeat and answers 1 (go on); with none left, it draws new repeats and a new pause
 * and answers 0. */
int FaceAnimTimer_Step(FaceAnimTimer *timer)
{
    if (timer->pause != 0) {
        timer->pause--;
        return 0;
    }
    if (timer->repeats != 0) {
        timer->repeats--;
        return 1;
    }
    FaceAnimTimer_NewRepeats(timer);
    timer->pause = (u8) (Random_Below(&data_021cb5a0, FACE_ANIM_TIMER_PAUSE_RANGE) + FACE_ANIM_TIMER_PAUSE_MIN);
    return 0;
}
CLEAN_AS(func_020645e0, FaceAnimTimer_Step)

/* func_0206461c: one or two repeats at random (the top bit of a number of the main
 * generator). */
void FaceAnimTimer_NewRepeats(FaceAnimTimer *timer)
{
    timer->repeats = (u8) ((Random_Next(&data_021cb5a0) >> 31) + 1);
}
CLEAN_AS(func_0206461c, FaceAnimTimer_NewRepeats)

/* func_02064638: the destructor: nothing to do. */
void FaceAnimTimer_Destruct(void *timer)
{
    (void) timer;
}
CLEAN_AS(func_02064638, FaceAnimTimer_Destruct)

/* func_0206463c: the constructor: nothing to do. */
void FaceAnimTimer_Construct(void *timer)
{
    (void) timer;
}
CLEAN_AS(func_0206463c, FaceAnimTimer_Construct)
