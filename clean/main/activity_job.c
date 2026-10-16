/* The jobs of the activity process (activity_job.h). */
#include "activity_job.h"

#include "activity.h"
#include "clean.h"

static_assert(offsetof(Activity, unk_50) == 0x50 && offsetof(Activity, state) == 0xa1, "activity");

/* The current activity, or NULL. */
extern Activity *data_021f3c3c;
/* The job asked for next (ACTIVITY_JOB_NONE for none). */
extern s32 data_021f3c38;

/* Whether there is a current activity, running job `job`. */
static int current_job_is(u32 job)
{
    return data_021f3c3c != NULL && data_021f3c3c->unk_50 == job;
}

/* func_020a17a8: the current activity runs job 0x1f and is at step 15 or 20 of it (overlay 54
 * asks). */
int ActivityJob_Is1FAtStep15Or20(void)
{
    if (current_job_is(0x1f)) {
        u8 step = data_021f3c3c->state;
        if (step == 15 || step == 20) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020a17a8, ActivityJob_Is1FAtStep15Or20)

/* func_020a17d0: the current activity runs no job (overlay 54 asks).
 * QUIRK: func_020a1810, func_020a182c and func_020a186c are the same function. */
int ActivityJob_IsIdleForOv054(void)
{
    return current_job_is(ACTIVITY_JOB_NONE);
}
CLEAN_AS(func_020a17d0, ActivityJob_IsIdleForOv054)

/* func_020a17ec: the current activity runs job 0x13 and is at its step 3 (overlay 48 asks). */
int ActivityJob_Is13AtStep3(void)
{
    return current_job_is(0x13) && data_021f3c3c->state == 3;
}
CLEAN_AS(func_020a17ec, ActivityJob_Is13AtStep3)

/* func_020a1810: the current activity runs no job (overlay 48 asks). */
int ActivityJob_IsIdleForOv048(void)
{
    return current_job_is(ACTIVITY_JOB_NONE);
}
CLEAN_AS(func_020a1810, ActivityJob_IsIdleForOv048)

/* func_020a182c: the current activity runs no job (overlay 4 asks). */
int ActivityJob_IsIdleForOv004(void)
{
    return current_job_is(ACTIVITY_JOB_NONE);
}
CLEAN_AS(func_020a182c, ActivityJob_IsIdleForOv004)

/* func_020a1848: the current activity runs job 0x12 and is at its step 3 (overlay 54 asks). */
int ActivityJob_Is12AtStep3(void)
{
    return current_job_is(0x12) && data_021f3c3c->state == 3;
}
CLEAN_AS(func_020a1848, ActivityJob_Is12AtStep3)

/* func_020a186c: the current activity runs no job (overlays 4 and 54 ask). */
int ActivityJob_IsIdle(void)
{
    return current_job_is(ACTIVITY_JOB_NONE);
}
CLEAN_AS(func_020a186c, ActivityJob_IsIdle)

/* func_020a1888 */
void ActivityJob_Ask1C(void)
{
    data_021f3c38 = 0x1c;
}
CLEAN_AS(func_020a1888, ActivityJob_Ask1C)

/* func_020a1894 */
void ActivityJob_Ask1F(void)
{
    data_021f3c38 = 0x1f;
}
CLEAN_AS(func_020a1894, ActivityJob_Ask1F)

/* func_020a18a0 */
void ActivityJob_Ask1B(void)
{
    data_021f3c38 = 0x1b;
}
CLEAN_AS(func_020a18a0, ActivityJob_Ask1B)

/* func_020a18ac */
void ActivityJob_Ask1A(void)
{
    data_021f3c38 = 0x1a;
}
CLEAN_AS(func_020a18ac, ActivityJob_Ask1A)

/* func_020a18b8 */
void ActivityJob_Ask19(void)
{
    data_021f3c38 = 0x19;
}
CLEAN_AS(func_020a18b8, ActivityJob_Ask19)

/* func_020a18c4 */
void ActivityJob_Ask18(void)
{
    data_021f3c38 = 0x18;
}
CLEAN_AS(func_020a18c4, ActivityJob_Ask18)

/* func_020a18d0 */
void ActivityJob_Ask17(void)
{
    data_021f3c38 = 0x17;
}
CLEAN_AS(func_020a18d0, ActivityJob_Ask17)

/* func_020a18dc */
void ActivityJob_Ask16(void)
{
    data_021f3c38 = 0x16;
}
CLEAN_AS(func_020a18dc, ActivityJob_Ask16)

/* func_020a18e8 */
void ActivityJob_Ask15(void)
{
    data_021f3c38 = 0x15;
}
CLEAN_AS(func_020a18e8, ActivityJob_Ask15)

/* func_020a18f4 */
void ActivityJob_Ask14(void)
{
    data_021f3c38 = 0x14;
}
CLEAN_AS(func_020a18f4, ActivityJob_Ask14)

/* func_020a1900 */
void ActivityJob_Ask13(void)
{
    data_021f3c38 = 0x13;
}
CLEAN_AS(func_020a1900, ActivityJob_Ask13)

/* func_020a190c */
void ActivityJob_Ask12(void)
{
    data_021f3c38 = 0x12;
}
CLEAN_AS(func_020a190c, ActivityJob_Ask12)

/* func_020a1918 */
void ActivityJob_Ask3(void)
{
    data_021f3c38 = 3;
}
CLEAN_AS(func_020a1918, ActivityJob_Ask3)

/* func_020a1924 */
void ActivityJob_Ask5(void)
{
    data_021f3c38 = 5;
}
CLEAN_AS(func_020a1924, ActivityJob_Ask5)

/* func_020a1930 */
void ActivityJob_Ask6(void)
{
    data_021f3c38 = 6;
}
CLEAN_AS(func_020a1930, ActivityJob_Ask6)

/* func_020a193c */
void ActivityJob_Ask2(void)
{
    data_021f3c38 = 2;
}
CLEAN_AS(func_020a193c, ActivityJob_Ask2)

/* func_020a1948 */
void ActivityJob_Ask1(void)
{
    data_021f3c38 = 1;
}
CLEAN_AS(func_020a1948, ActivityJob_Ask1)
