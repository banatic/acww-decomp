/* Buildings (codes 0x5000-0x5021, town_objects.h) that come and go with the calendar's events
 * (func_0203fc78, checked by func_02047730 and func_02047898):
 *
 * - the event spot, tile (10, 9) of the first acre of the town whose model has flag 0x200 (the
 *   one made for building 0x5000), takes building 0x5012, 0x5013 or 0x5021 while events 0x3d,
 *   0x3f and 0x60 are on (state 2 or 3) and gives it up when they are over (state 0); building
 *   0x501e is put and removed the same way;
 * - building 0x5020 stands in place of one of the buildings 0x500a of an acre in the town's
 *   inner acres (1-4 each way): EventBuildings_Place5020 picks the acre, nearest a position
 *   first, and a random one of its 0x500a; once event 0x44 is over it turns back into 0x500a
 *   (EventBuildings_Revert5020). */
#ifndef CLEAN_MAIN_EVENT_BUILDINGS_H
#define CLEAN_MAIN_EVENT_BUILDINGS_H

#include "autoload_2/vector.h"
#include "types.h"

int EventBuildings_Revert5020(void);
int EventBuildings_Place5020(const Vec3 *position, int lower_first);
int EventBuildings_TurnRandom500a(u8 *acre, int code);
int EventBuildings_Turn500a(u8 *acre, int index, int code);
int EventBuildings_Count500a(u8 *acre);
void EventBuildings_Remove501e(void);
void EventBuildings_Put501e(void);
void EventBuildings_Remove5021(void);
void EventBuildings_Put5021(void);
void EventBuildings_Remove5013(void);
void EventBuildings_Put5013(void);
int EventBuildings_Remove5012(void);
void EventBuildings_Put5012(void);
int EventBuildings_RemoveAtSpot(int code);
void EventBuildings_PutAtSpot(int code);
u16 *EventBuildings_FindSpot(int *tile_x, int *tile_z);

#endif
