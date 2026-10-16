/* The jobs of the activity process (activity.h). The activity runs one job at a time, the one
 * in Activity.unk_50 (0 while it has none), whose functions are the entry of that number in the
 * table at data_021f3ea4 (func_020a4e94 starts one). The job the game asks for next is kept in
 * data_021f3c38: the ActivityJob_Ask* functions set it, from the overlays that start a visit
 * or a linked mode and from the session code, and func_020a4dc4 starts it once the scene it
 * belongs to is reached, then clears it. What each job does is not known yet; they are named
 * by number. */
#ifndef CLEAN_MAIN_ACTIVITY_JOB_H
#define CLEAN_MAIN_ACTIVITY_JOB_H

#include "types.h"

#define ACTIVITY_JOB_NONE 0

int ActivityJob_Is1FAtStep15Or20(void);
int ActivityJob_IsIdleForOv054(void);
int ActivityJob_Is13AtStep3(void);
int ActivityJob_IsIdleForOv048(void);
int ActivityJob_IsIdleForOv004(void);
int ActivityJob_Is12AtStep3(void);
int ActivityJob_IsIdle(void);
void ActivityJob_Ask1C(void);
void ActivityJob_Ask1F(void);
void ActivityJob_Ask1B(void);
void ActivityJob_Ask1A(void);
void ActivityJob_Ask19(void);
void ActivityJob_Ask18(void);
void ActivityJob_Ask17(void);
void ActivityJob_Ask16(void);
void ActivityJob_Ask15(void);
void ActivityJob_Ask14(void);
void ActivityJob_Ask13(void);
void ActivityJob_Ask12(void);
void ActivityJob_Ask3(void);
void ActivityJob_Ask5(void);
void ActivityJob_Ask6(void);
void ActivityJob_Ask2(void);
void ActivityJob_Ask1(void);

#endif
