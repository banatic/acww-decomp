/* A show of objects of kind SKY_OBJECT_SHOW launched into the town's sky from four places
 * (sky_objects.h), run each frame by func_020bd3b4 while calendar event 0x13 is on (or, in some
 * scenes, event 0xf).
 *
 * The show runs a program at a time (SkyObjects.program, 1 to 19; 20 asks for one drawn from a
 * table): func_020bd3b4 counts the program's timer down and calls the program's function (from
 * a table of pointers to members). When the timer goes below 0 the program starts it again
 * (SkyShow_StartProgram: its length and the delay between launches); when it reaches 0 the
 * program asks for the next one (SkyShow_SetProgram), which draws the first launches' times.
 * Between, the program launches objects one of five ways: from each place on its own timer
 * (SkyShow_LaunchEach), three places at once or two at once when all four are idle
 * (SkyShow_LaunchThrees, SkyShow_LaunchPairs), or large ones from a random place on a common
 * countdown (SkyShow_LaunchLarge, SkyShow_LaunchLargeMarked).
 *
 * A place launches only when no object it launched is still in the last 13 entries, nor a large
 * one whose bit 29 is clear. Without the sky drawn, a launch only hands its number to
 * func_02065268. */
#ifndef CLEAN_MAIN_SKY_SHOW_H
#define CLEAN_MAIN_SKY_SHOW_H

#include "sky_objects.h"

#define SKY_SHOW_PLACES 4
#define SKY_SHOW_ANY_PROGRAM 20 /* SkyShow_SetProgram: one drawn from data_020d2315 */

/* SkyObject.param of a launched object. */
#define SKY_SHOW_PARAM_LOOK 0x0000000fu   /* from data_020d2354, by place */
#define SKY_SHOW_PARAM_PLACE 0x00000300u  /* the place it was launched from */
#define SKY_SHOW_PARAM_MARKED 0x10000000u /* SkyShow_LaunchLargeMarked's */
#define SKY_SHOW_PARAM_BIT29 0x20000000u  /* set later, not by these functions */
#define SKY_SHOW_PARAM_LARGE 0x80000000u

void SkyShow_LargeMarkedThen16(SkyObjects *objects);
void SkyShow_WaitThen19(SkyObjects *objects);
void SkyShow_EachThen1(SkyObjects *objects);
void SkyShow_LargeThen17(SkyObjects *objects);
void SkyShow_LargeThen4(SkyObjects *objects);
void SkyShow_EachThen15(SkyObjects *objects);
void SkyShow_WaitThenAny(SkyObjects *objects);
void SkyShow_ThreesDelay140(SkyObjects *objects);
void SkyShow_ThreesDelay80(SkyObjects *objects);
void SkyShow_ThreesDelay40(SkyObjects *objects);
void SkyShow_PairsDelay100(SkyObjects *objects);
void SkyShow_PairsDelay60(SkyObjects *objects);
void SkyShow_PairsDelay30(SkyObjects *objects);
void SkyShow_EachDelay300(SkyObjects *objects);
void SkyShow_EachDelay160(SkyObjects *objects);
void SkyShow_EachDelay50(SkyObjects *objects);
void SkyShow_LargeDelay200(SkyObjects *objects);
void SkyShow_LargeDelay100(SkyObjects *objects);
void SkyShow_LargeDelay20(SkyObjects *objects);
void SkyShow_SetProgram(SkyObjects *objects, int program);
void SkyShow_StartProgram(SkyObjects *objects, int delay, int length, int length_spread);
void SkyShow_LaunchThrees(SkyObjects *objects);
void SkyShow_LaunchPairs(SkyObjects *objects);
void SkyShow_LaunchEach(SkyObjects *objects);
void SkyShow_LaunchLargeMarked(SkyObjects *objects);
void SkyShow_LaunchLarge(SkyObjects *objects);
void SkyShow_NextLaunchTime(SkyObjects *objects, s32 *timer);
void SkyShow_Launch(SkyObjects *objects, int place, int large, int marked);
int SkyShow_PlaceFree(SkyObjects *objects, int place);
int SkyShow_PlaceFreeForLarge(SkyObjects *objects, int place);
void SkyShow_Run(SkyObjects *objects);

#endif
