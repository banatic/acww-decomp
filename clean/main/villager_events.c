/* Things the player does that the town's villagers take note of (villager_events.h). */
#include "villager_events.h"

#include "calendar.h"
#include "clean.h"
#include "npc_id.h"
#include "session.h"
#include "villager_state.h"
#include "acre_record.h"
#include "actor_table.h"
#include "date_time.h"
#include "scene_query.h"
#include "town_villager.h"
#include "villager_mode.h"
#include "villager_mode_record.h"
#include "villager_object.h"
#include "villager_roster.h"
#include "villager_status.h"

#define VILLAGERS 8
#define VILLAGER_SIZE 0x7ec

/* The villager actors' codes in the game's actor table: kind 0xe, the villager's index. */
#define VILLAGER_EVENT_ACTOR_CODE(index) ((u16) (0xe000 | ((index) & 0xfff)))

/* The box around the event's place a villager's actor must stand in to count it twice: 16 units
 * to either side, 26 units behind and 10 ahead (20.12 fixed point). */
#define VILLAGER_EVENT_NEAR_X 0x10000
#define VILLAGER_EVENT_NEAR_BEHIND 0x1a000
#define VILLAGER_EVENT_NEAR_AHEAD 0xa000

/* A cell of the map's grid, 0x28 bytes, of which func_02037d80 reads the bits. */
#define VILLAGER_EVENT_CELL_SIZE 0x28
#define VILLAGER_EVENT_CELL_MARK 8

/* The grid at the start of the town's map: width x height cells, one for each 32 units. */
typedef struct VillagerEventGrid {
    u8 *cells;
    u32 width;
    u32 height;
} VillagerEventGrid;

/* What VillagerEvent_ActorInBox asks of the actor: its vtable, and its position at 0x5c. */
typedef struct VillagerEventActor {
    u32 vtable;
    u8 unk_04[0x5c - 0x04];
    Vec3 position;
} VillagerEventActor;

/* The vtable slot (0xa8) of the actor's method that says whether it is there to look at. */
#define VILLAGER_EVENT_ACTOR_PRESENT_SLOT 0xa8
typedef int (*VillagerEventPresentMethod)(VillagerEventActor *actor);

extern NetSession *data_020ccf94;        /* the game's session */
extern u8 data_021e5a2c[];               /* the town's eight villagers, 0x7ec bytes each */
extern VillagerEventGrid *data_021c80bc; /* the town's map; null while there is none */

/* ---- Counting idle frames */

/* func_020795f4: in scene 0 and not linked, one more frame without an event; past 1200 such
 * frames VillagerEvent_Idle first (which restarts the count, so this frame counts as 1). */
void VillagerEvent_CountIdleFrame(void)
{
    if (SceneQuery_CurrentIs0() == 0) {
        return;
    }
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    if (VillagerState_Table()->word_168 > VILLAGER_EVENT_IDLE_FRAMES) {
        VillagerEvent_Idle();
    }
    VillagerState_Table()->word_168++;
}
CLEAN_AS(func_020795f4, VillagerEvent_CountIdleFrame)

/* func_02079640 */
void VillagerEvent_Idle(void)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_IDLE, NULL);
    }
}
CLEAN_AS(func_02079640, VillagerEvent_Idle)

/* ---- The events */

/* func_02079664: kind 6 at `position`, when the map's cell there has bit 8. */
void VillagerEvent_AtMarkedTile(const Vec3 *position)
{
    if (!Session_IsLinked(data_020ccf94) && VillagerEvent_IsMarkedTile(position)) {
        VillagerEvent_Spread(VILLAGER_EVENT_MARKED_TILE, position);
    }
}
CLEAN_AS(func_02079664, VillagerEvent_AtMarkedTile)

/* func_02079690: whether the cell of the map's grid at `position` (x and z in units of 32) has
 * bit 8; 0 without a map, outside the grid or when the grid has no cells. Negative coordinates
 * become large ones and so fall outside. */
int VillagerEvent_IsMarkedTile(const Vec3 *position)
{
    VillagerEventGrid *grid = data_021c80bc;

    if (grid == NULL) {
        return 0;
    }
    u32 z = (u32) (position->z >> 17);
    u32 x = (u32) (position->x >> 17);
    if (x >= grid->width || z >= grid->height || grid->cells == NULL) {
        return 0;
    }
    u32 offset = (x + z * grid->width) * VILLAGER_EVENT_CELL_SIZE;
    void *cell = (void *) ((uintptr_t) grid->cells + offset);
    return AcreRecord_HasAllFlags(cell, VILLAGER_EVENT_CELL_MARK) != 0;
}
CLEAN_AS(func_02079690, VillagerEvent_IsMarkedTile)

/* func_020796e4 */
void VillagerEvent_Report5(const Vec3 *position)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_5, position);
    }
}
CLEAN_AS(func_020796e4, VillagerEvent_Report5)

/* func_02079708 */
void VillagerEvent_Report4(void)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_4, NULL);
    }
}
CLEAN_AS(func_02079708, VillagerEvent_Report4)

/* func_0207972c */
void VillagerEvent_Report3(void)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_3, NULL);
    }
}
CLEAN_AS(func_0207972c, VillagerEvent_Report3)

/* func_02079750 */
void VillagerEvent_Item1549(const Vec3 *position)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_ITEM_1549, position);
    }
}
CLEAN_AS(func_02079750, VillagerEvent_Item1549)

/* func_02079774 */
void VillagerEvent_InsectCaught(const Vec3 *position)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_INSECT_CAUGHT, position);
    }
}
CLEAN_AS(func_02079774, VillagerEvent_InsectCaught)

/* func_02079798 */
void VillagerEvent_FishCaught(const Vec3 *position)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerEvent_Spread(VILLAGER_EVENT_FISH_CAUGHT, position);
    }
}
CLEAN_AS(func_02079798, VillagerEvent_FishCaught)

/* ---- Telling the villagers */

/* func_020797bc: every villager with a valid NpcId whose record allows it (func_0209c1c0, with
 * today's date) adds 1 to its count of `kind`, or 2 when `position` is given and the
 * villager's actor stands in the box around it. Then the idle frames start again from 0. */
void VillagerEvent_Spread(int kind, const Vec3 *position)
{
    int min_x = 0;
    int max_x = 0;
    int min_z = 0;
    int max_z = 0;
    DateTime now = {0};

    if (position != NULL) {
        min_x = (int) ((u32) position->x - VILLAGER_EVENT_NEAR_X);
        max_x = (int) ((u32) position->x + VILLAGER_EVENT_NEAR_X);
        min_z = (int) ((u32) position->z - VILLAGER_EVENT_NEAR_BEHIND);
        max_z = (int) ((u32) position->z + VILLAGER_EVENT_NEAR_AHEAD);
    }
    DateTime_Now(&now);
    for (int i = 0; i < VILLAGERS; i++) {
        void *villager = VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, i);
        if (villager == NULL || !NpcId_IsValid(TownVillager_NpcId(villager))) {
            continue;
        }
        if (!VillagerModeRecord_IsKindAWeekOld(
                VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager)), &now)) {
            continue;
        }
        int amount = 1;
        if (position != NULL) {
            u16 code = VILLAGER_EVENT_ACTOR_CODE(i);
            if (VillagerEvent_ActorInBox(&code, min_x, max_x, min_z, max_z)) {
                amount = 2;
            }
        }
        VillagerMode_AddCount(villager, kind, amount);
    }
    VillagerState_Table()->word_168 = 0;
}
CLEAN_AS(func_020797bc, VillagerEvent_Spread)

/* func_020798a0: whether the actor under `code` in the game's actor table is there (its
 * method at vtable slot 0xa8) and stands strictly inside the box, x between `min_x` and
 * `max_x` and z between `min_z` and `max_z`. */
int VillagerEvent_ActorInBox(const u16 *code, int min_x, int max_x, int min_z, int max_z)
{
    VillagerEventActor *actor = Actors_GetE(code);

    if (actor == NULL) {
        return 0;
    }
    u32 method = *(const u32 *) (uintptr_t) (actor->vtable + VILLAGER_EVENT_ACTOR_PRESENT_SLOT);
    if (((VillagerEventPresentMethod) (uintptr_t) method)(actor) == 0) {
        return 0;
    }
    const Vec3 *at = &actor->position;
    return at->x > min_x && at->x < max_x && at->z > min_z && at->z < max_z;
}
CLEAN_AS(func_020798a0, VillagerEvent_ActorInBox)
