/* Buildings (codes 0x5000-0x5021, town_objects.h) that come and go with the calendar's events
 * (func_0203fc78, checked by func_02047730 and func_02047898):
 *
 * - the event spot, tile (10, 9) of the first acre of the town whose model has flag 0x200 (the
 *   one made for building 0x5000), takes building 0x5012 (the fox's tent), 0x5013 or 0x5021
 *   while events 0x3d (the fox), 0x3f and 0x60 are on (state 2 or 3) and gives it up when they are over (state 0); building
 *   0x501e is put and removed the same way;
 * - the crashed spaceship, building 0x5020, stands in place of one of the free plots 0x500a
 *   (villager_plots.h) of an acre in the town's inner acres (1-4 each way) once the spaceship
 *   crossing the sky is shot down (sky_visitors.h): EventBuildings_PlaceSpaceship picks the
 *   acre, nearest a position first, and a random one of its free plots, and clears the count of
 *   spaceship parts found (spaceship_parts.h); once event 0x44 is over it turns back into a
 *   free plot (EventBuildings_RevertSpaceship). */
#ifndef CLEAN_MAIN_EVENT_BUILDINGS_H
#define CLEAN_MAIN_EVENT_BUILDINGS_H

#include "autoload_2/vector.h"
#include "types.h"

int EventBuildings_RevertSpaceship(void);
int EventBuildings_PlaceSpaceship(const Vec3 *position, int lower_first);
int EventBuildings_TurnRandomFreePlot(u8 *acre, int code);
int EventBuildings_TurnFreePlot(u8 *acre, int index, int code);
int EventBuildings_CountFreePlots(u8 *acre);
void EventBuildings_Remove501e(void);
void EventBuildings_Put501e(void);
void EventBuildings_Remove5021(void);
void EventBuildings_Put5021(void);
void EventBuildings_Remove5013(void);
void EventBuildings_Put5013(void);
int EventBuildings_RemoveFoxTent(void);
void EventBuildings_PutFoxTent(void);
int EventBuildings_RemoveAtSpot(int code);
void EventBuildings_PutAtSpot(int code);
u16 *EventBuildings_FindSpot(int *tile_x, int *tile_z);
void EventBuildings_ClearSpaceshipParts(void);

#endif
