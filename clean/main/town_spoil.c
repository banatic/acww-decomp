/* The counted items going bad (town_spoil.h). */
#include "town_spoil.h"

#include "acre_tile.h"
#include "clean.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"

extern u8 data_021dc7bc[];  /* the town's four players' records */
extern u16 data_021f3a68[]; /* the town's item list A (town_item_lists.h) */
extern u16 data_021f3a86[]; /* the town's item list B */

#define TOWN_SPOIL_PLAYERS 4
#define TOWN_SPOIL_POCKET_SLOTS 15

static int TownSpoil_Spoils(unsigned int item)
{
    return item >= TOWN_SPOIL_FIRST && item <= TOWN_SPOIL_LAST;
}

/* The spoiled item for a counted one. */
static u16 TownSpoil_Spoiled(unsigned int item)
{
    return (u16) (TOWN_SPOIL_SPOILED + (item - TOWN_SPOIL_FIRST));
}

/* func_02046c2c: the counted items spoiled everywhere: pockets, the town, the rooms, list B,
 * then list A. */
void TownSpoil_All(TownDay *town)
{
    TownSpoil_Pockets();
    TownSpoil_Town((int) (uintptr_t) town);
    TownSpoil_Rooms((int) (uintptr_t) town);
    TownSpoil_ListB();
    for (int i = 0; i < TOWN_SPOIL_LIST_PLACES; i++) {
        if (TownSpoil_Spoils(data_021f3a68[i])) {
            data_021f3a68[i] = TownSpoil_Spoiled(data_021f3a68[i]);
        }
    }
}
CLEAN_AS(func_02046c2c, TownSpoil_All)

/* func_02046cac: the counted items of the town's item list B spoiled. */
void TownSpoil_ListB(void)
{
    for (int i = 0; i < TOWN_SPOIL_LIST_PLACES; i++) {
        if (TownSpoil_Spoils(data_021f3a86[i])) {
            data_021f3a86[i] = TownSpoil_Spoiled(data_021f3a86[i]);
        }
    }
}
CLEAN_AS(func_02046cac, TownSpoil_ListB)

/* func_02046d14: the counted items on the five rooms' maps spoiled. */
void TownSpoil_Rooms(int unused)
{
    for (int room = 0; room < TOWN_SPOIL_ROOMS; room++) {
        TownSpoil_Map(unused, (AcreMap *) (uintptr_t) AcreMap_Room(room));
    }
}
CLEAN_AS(func_02046d14, TownSpoil_Rooms)

/* func_02046d38: the counted items on the town's map spoiled. */
void TownSpoil_Town(int unused)
{
    TownSpoil_Map(unused, (AcreMap *) (uintptr_t) AcreMap_Town());
}
CLEAN_AS(func_02046d38, TownSpoil_Town)

/* func_02046d50: the counted items in the pockets of each of the town's players spoiled. */
void TownSpoil_Pockets(void)
{
    for (int player = 0; player < TOWN_SPOIL_PLAYERS; player++) {
        if (PlayerRecords_TownExists(data_021dc7bc, player) == 0) {
            continue;
        }
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, player);
        for (int slot = 0; slot < TOWN_SPOIL_POCKET_SLOTS; slot++) {
            PlayerPockets *pockets = PlayerRecord_Pockets(record);
            const u16 *item = PlayerPockets_Slot(pockets, slot);
            if (item != NULL && TownSpoil_Spoils(*item)) {
                u16 spoiled = TownSpoil_Spoiled(*item);
                PlayerPockets_SetSlot(pockets, &spoiled, slot, 0);
            }
        }
    }
}
CLEAN_AS(func_02046d50, TownSpoil_Pockets)

/* func_02046df4: the counted items on both layers of the map spoiled, if there is a map. */
void TownSpoil_Map(int unused, AcreMap *map)
{
    (void) unused;
    if (map == NULL) {
        return;
    }
    int wide = map->tiles_wide;
    int high = map->tiles_high;
    for (u8 layer = 0; layer < 2; layer++) {
        for (int z = 0; z < high; z++) {
            for (int x = 0; x < wide; x++) {
                const u16 *item = AcreTile_ItemInAcre(map, (u32) (x >> 4), (u32) (z >> 4), x & 15, z & 15, layer);
                if (item != NULL && TownSpoil_Spoils(*item)) {
                    u16 spoiled = TownSpoil_Spoiled(*item);
                    AcreTile_SetItem(map, &spoiled, x, z, layer);
                }
            }
        }
    }
}
CLEAN_AS(func_02046df4, TownSpoil_Map)
