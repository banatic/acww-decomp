/* What adds the sky's objects (sky_objects.h) by the weather, the time and the calendar, run
 * each frame by SkyObjects_RunWeather and SkyObjects_RunEvents:
 *
 * - the rain and the snow (SkyEvents_Rain, SkyEvents_Snow): drops added at a rate that grows
 *   towards the heavier levels; with heavy rain the thunder (SkyEvents_Thunder), sometimes with
 *   an object of kind 8;
 * - the moon at night, 19:00 to 3:59 (SkyEvents_UpdateMoon), and kind 10 in the hour of the
 *   day's weather pattern 0x13 to 0x17 that data_020d22b5 gives, with the clouds' blending;
 * - kind 3 at night when no show runs: one chance at second 30 of each minute (1 in 4 on days
 *   of weather pattern 0, else 1 in 256) to appear up to 600 frames later;
 * - kinds 5, 6 and 7 in entry 45, unless this system is in a session: kind 5 at minutes ending
 *   in 4 from 10:00 to 15:59, kind 6 at minutes ending in 2 or 7 while calendar event 0x44 is
 *   on, kind 7 at 9:00 and 17:00 while event 0x45 is, each when a part of data_021d27ac
 *   (block_021d27ac.h) was not served yet; kinds 5 and 6 at odds that grow from a random
 *   start each minute they do not come, to 8 in 8;
 * - three objects of kind 12 once, from 6:00 to 8:59 between March 16 and September 15 when
 *   nothing falls.
 *
 * When func_0204714c asks for it (SkyEvents_Refresh), each player whose record has flag 0x32
 * (set when kind 3 is marked, Block020ba298_SetPlayerFlag32) gets a letter
 * (SkyEvents_PostFlag32Letters). */
#ifndef CLEAN_MAIN_SKY_EVENTS_H
#define CLEAN_MAIN_SKY_EVENTS_H

#include "sky_objects.h"

void SkyEvents_AddKind12(SkyObjects *objects);
void SkyEvents_UpdateKind10(SkyObjects *objects);
void SkyEvents_AddKind7(SkyObjects *objects);
void SkyEvents_AddKind6(SkyObjects *objects);
void SkyEvents_AddKind5(SkyObjects *objects);
void SkyEvents_UpdateMoon(SkyObjects *objects);
void SkyEvents_AddKind3(SkyObjects *objects);
void SkyEvents_Snow(SkyObjects *objects);
void SkyEvents_Rain(SkyObjects *objects);
void SkyEvents_Thunder(SkyObjects *objects);
void SkyEvents_HeavyThunder(SkyObjects *objects);
void SkyEvents_StartFalling(SkyObjects *objects);
void SkyEvents_PostFlag32Letters(SkyObjects *objects);
void SkyEvents_Refresh(SkyObjects *objects, int refresh);
void SkyEvents_ReadCalendar(SkyObjects *objects);

#endif
