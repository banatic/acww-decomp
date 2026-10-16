/* Per-scene facts of main (scene_tables.h). */
#include "scene_tables.h"

#include "clean.h"
#include "main/session.h"

/* The scenes SceneTables_NoPlayerInClosedScene looks for. */
#define SCENE_TABLES_CLOSED_FIRST 0x0c
#define SCENE_TABLES_CLOSED_LAST 0x0e
#define SCENE_TABLES_CLOSED_LATE_FIRST 0x2e
#define SCENE_TABLES_CLOSED_LATE_COUNT 2

extern NetSession *data_020ccf94;
/* A byte for each scene: one ov004 reads, the heaps and blocks func_02085f08 counts, and the
 * two counts resource_pools.c takes the difference of. */
extern const u8 data_020d20e8[SCENE_TABLES_SCENES];
extern const u8 data_020d21b8[SCENE_TABLES_SCENES];
extern const u8 data_020d2184[SCENE_TABLES_SCENES];
extern const u8 data_020d211c[SCENE_TABLES_SCENES];
/* The entry record. */
extern u8 data_021f69d0[];

/* The current scene; the scene of session player `player` (0x3f for a player above 3). */
extern u8 func_020b65c4(void);
extern int func_020a7330(int player);

/* Whether `scene` is 0x0c-0x0e or 0x2e-0x2f (the last two as the ROM tests them, by the low
 * byte of the difference). */
static int scene_tables_is_closed(int scene)
{
    if (scene >= SCENE_TABLES_CLOSED_FIRST && scene <= SCENE_TABLES_CLOSED_LAST) {
        return 1;
    }
    return (u8) (scene - SCENE_TABLES_CLOSED_LATE_FIRST) < SCENE_TABLES_CLOSED_LATE_COUNT;
}

/* func_020b5d5c: 0 when a player is in one of the scenes 0x0c-0x0e and 0x2e-0x2f, else 1. Alone
 * (this system's slot not taken) that is the current scene; in a session it is the scene of
 * each other player, from slot 3 down to 0 (this system's own player is not looked at). */
int SceneTables_NoPlayerInClosedScene(void)
{
    NetSession *session = data_020ccf94;

    if (Session_IsSlotTaken(session, session->local_slot) == 0) {
        if (scene_tables_is_closed(func_020b65c4())) {
            return 0;
        }
    } else {
        for (int slot = SESSION_SLOTS - 1; slot >= 0; slot--) {
            if (Session_IsSlotTaken(session, slot) != 0 && Session_IsLocalSlot(session, slot) == 0) {
                if (scene_tables_is_closed(func_020a7330(slot))) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
CLEAN_AS(func_020b5d5c, SceneTables_NoPlayerInClosedScene)

/* func_020b5de0: the scene's byte of data_020d20e8. The tables are not bounded: the callers
 * pass the current scene. */
unsigned char SceneTables_Value20e8(unsigned int scene)
{
    return data_020d20e8[scene];
}
CLEAN_AS(func_020b5de0, SceneTables_Value20e8)

/* func_020b5dec: the scene's count of heaps (func_02085f08). */
unsigned char SceneTables_HeapCount(unsigned int scene)
{
    return data_020d21b8[scene];
}
CLEAN_AS(func_020b5dec, SceneTables_HeapCount)

/* func_020b5df8: the scene's first count (resource_pools.c). */
unsigned char SceneTables_FirstCount(unsigned int scene)
{
    return data_020d2184[scene];
}
CLEAN_AS(func_020b5df8, SceneTables_FirstCount)

/* func_020b5e04: the scene's second count, taken from the first. */
unsigned char SceneTables_SecondCount(unsigned int scene)
{
    return data_020d211c[scene];
}
CLEAN_AS(func_020b5e04, SceneTables_SecondCount)

/* func_020b5e10: the entry record, as an address. */
int SceneTables_EntryRecord(void)
{
    return (int) (uintptr_t) data_021f69d0;
}
CLEAN_AS(func_020b5e10, SceneTables_EntryRecord)
