/* The fireworks show: shells of kind SKY_OBJECT_FIREWORK launched into the town's sky from
 * four places (sky_objects.h), run each frame by func_020bd3b4 while calendar event 0x13 is on (or, in some
 * scenes, event 0xf).
 *
 * The show runs a program at a time (SkyObjects.program, 1 to 19; 20 asks for one drawn from a
 * table): func_020bd3b4 counts the program's timer down and calls the program's function (from
 * a table of pointers to members). When the timer goes below 0 the program starts it again
 * (SkyFireworks_StartProgram: its length and the delay between launches); when it reaches 0 the
 * program asks for the next one (SkyFireworks_SetProgram), which draws the first launches' times.
 * Between, the program launches objects one of five ways: from each place on its own timer
 * (SkyFireworks_LaunchEach), three places at once or two at once when all four are idle
 * (SkyFireworks_LaunchThrees, SkyFireworks_LaunchPairs), or large ones from a random place on a common
 * countdown (SkyFireworks_LaunchLarge, SkyFireworks_LaunchLargeMarked).
 *
 * A place launches only when no object it launched is still in the last 13 entries, nor a large
 * one whose bit 29 is clear. Without the sky drawn, a launch only hands its number to
 * SceneLights_StartFlash. */
#ifndef CLEAN_MAIN_SKY_FIREWORKS_H
#define CLEAN_MAIN_SKY_FIREWORKS_H

#include "sky_objects.h"

#define SKY_FIREWORKS_PLACES 4
#define SKY_FIREWORKS_ANY_PROGRAM 20 /* SkyFireworks_SetProgram: one drawn from data_020d2315 */

/* SkyObject.param of a launched object. */
#define SKY_FIREWORKS_PARAM_LOOK 0x0000000fu   /* from data_020d2354, by place */
#define SKY_FIREWORKS_PARAM_PLACE 0x00000300u  /* the place it was launched from */
#define SKY_FIREWORKS_PARAM_MARKED 0x10000000u /* SkyFireworks_LaunchLargeMarked's */
#define SKY_FIREWORKS_PARAM_BIT29 0x20000000u  /* set later, not by these functions */
#define SKY_FIREWORKS_PARAM_LARGE 0x80000000u

void SkyFireworks_LargeMarkedThen16(SkyObjects *objects);
void SkyFireworks_WaitThen19(SkyObjects *objects);
void SkyFireworks_EachThen1(SkyObjects *objects);
void SkyFireworks_LargeThen17(SkyObjects *objects);
void SkyFireworks_LargeThen4(SkyObjects *objects);
void SkyFireworks_EachThen15(SkyObjects *objects);
void SkyFireworks_WaitThenAny(SkyObjects *objects);
void SkyFireworks_ThreesDelay140(SkyObjects *objects);
void SkyFireworks_ThreesDelay80(SkyObjects *objects);
void SkyFireworks_ThreesDelay40(SkyObjects *objects);
void SkyFireworks_PairsDelay100(SkyObjects *objects);
void SkyFireworks_PairsDelay60(SkyObjects *objects);
void SkyFireworks_PairsDelay30(SkyObjects *objects);
void SkyFireworks_EachDelay300(SkyObjects *objects);
void SkyFireworks_EachDelay160(SkyObjects *objects);
void SkyFireworks_EachDelay50(SkyObjects *objects);
void SkyFireworks_LargeDelay200(SkyObjects *objects);
void SkyFireworks_LargeDelay100(SkyObjects *objects);
void SkyFireworks_LargeDelay20(SkyObjects *objects);
void SkyFireworks_SetProgram(SkyObjects *objects, int program);
void SkyFireworks_StartProgram(SkyObjects *objects, int delay, int length, int length_spread);
void SkyFireworks_LaunchThrees(SkyObjects *objects);
void SkyFireworks_LaunchPairs(SkyObjects *objects);
void SkyFireworks_LaunchEach(SkyObjects *objects);
void SkyFireworks_LaunchLargeMarked(SkyObjects *objects);
void SkyFireworks_LaunchLarge(SkyObjects *objects);
void SkyFireworks_NextLaunchTime(SkyObjects *objects, s32 *timer);
void SkyFireworks_Launch(SkyObjects *objects, int place, int large, int marked);
int SkyFireworks_PlaceFree(SkyObjects *objects, int place);
int SkyFireworks_PlaceFreeForLarge(SkyObjects *objects, int place);
void SkyFireworks_Run(SkyObjects *objects);

#endif
