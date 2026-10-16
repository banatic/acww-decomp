/* Things the player does that the town's villagers take note of. Each event has a kind (0-7);
 * VillagerEvent_Spread adds to every villager's count of that kind, which the villager's record
 * at 0x734 keeps from 0 to 10 (func_0209bee8, the bytes at its 0x19). A villager counts the
 * event only when its record's date is at least seven days from today (func_0209c1c0). The
 * count goes up by 1, or by 2 for a villager whose actor stands near the place of the event.
 *
 * The events are reported from where the game sees them, and not while this system is linked
 * with others (Session_IsLinked). Kind 7 is reported when nothing else was for 1200 frames: the
 * table's word 0x168 (villager_state.h) counts the frames and VillagerEvent_Spread restarts it. */
#ifndef CLEAN_MAIN_VILLAGER_EVENTS_H
#define CLEAN_MAIN_VILLAGER_EVENTS_H

#include "autoload_2/vector.h"
#include "types.h"

enum VillagerEventKind {
    VILLAGER_EVENT_INSECT_CAUGHT = 0, /* an insect caught (overlay 3's state 0x57) */
    VILLAGER_EVENT_FISH_CAUGHT = 1,   /* a fish of kind below 0x38 caught (overlay 3's state 0x54) */
    VILLAGER_EVENT_ITEM_1549 = 2,     /* item 0x1549 in overlay 3's state 0x5f */
    VILLAGER_EVENT_3 = 3,             /* from overlay 49 */
    VILLAGER_EVENT_4 = 4,             /* from overlay 50 */
    VILLAGER_EVENT_5 = 5,             /* from func_02042ff8, with a place */
    VILLAGER_EVENT_MARKED_TILE = 6,   /* items 0x1554-0x155c on a tile with bit 8 (state 0x19) */
    VILLAGER_EVENT_IDLE = 7           /* nothing else reported for 1200 frames */
};

#define VILLAGER_EVENT_IDLE_FRAMES 1200

void VillagerEvent_CountIdleFrame(void);
void VillagerEvent_Idle(void);
void VillagerEvent_AtMarkedTile(const Vec3 *position);
int VillagerEvent_IsMarkedTile(const Vec3 *position);
void VillagerEvent_Report5(const Vec3 *position);
void VillagerEvent_Report4(void);
void VillagerEvent_Report3(void);
void VillagerEvent_Item1549(const Vec3 *position);
void VillagerEvent_InsectCaught(const Vec3 *position);
void VillagerEvent_FishCaught(const Vec3 *position);
void VillagerEvent_Spread(int kind, const Vec3 *position);
int VillagerEvent_ActorInBox(const u16 *code, int min_x, int max_x, int min_z, int max_z);

#endif
