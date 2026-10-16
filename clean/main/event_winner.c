/* A record of who won one of the town's events (event_winner.h). */
#include "event_winner.h"

#include "acre_tile.h"
#include "clean.h"
#include "field_collision.h"
#include "player_record.h"
#include "player_records.h"
#include "state_block.h"
#include "town_villager.h"
#include "villager_home.h"
#include "villager_roster.h"
#include "villager_town.h"

static_assert(offsetof(EventWinner, villager) == 0x1e && offsetof(EventWinner, npc_2e) == 0x2e, "EventWinner");
static_assert(offsetof(EventWinner, item) == 0x3e && offsetof(EventWinner, size) == 0x40, "EventWinner");
static_assert(offsetof(EventWinner, date) == 0x44 && sizeof(EventWinner) == 0x48, "EventWinner");

extern u8 data_020e54a8;           /* 0 outdoors, 1 in a room */
extern AcreMap *data_021c80bc;     /* the map of the scene */
extern VillagerTown data_021e5a2c; /* the town's villagers */
extern u32 data_021dc7a8[];        /* the state block */
extern u8 data_021dc7bc[];         /* the four players' records */

/* The eight neighbours EventWinner_IsNearAttr4 looks at and the 14 tiles around a house
 * EventWinner_ScoreAroundHome counts, as offsets in tiles. */
extern const EventWinnerTile data_021d27e0[8];
extern const EventWinnerTile data_021d2820[14];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern u32 func_020644b4(int bound); /* the same from another generator */
/* The days since the town's event `event` this year, -1 without one. */
extern int func_0203fdc4(int event);
/* The record's parts (set by the functions after this file's). */
extern NpcId *func_020867a0(EventWinner *record);
extern DesignCreator *func_020867e0(EventWinner *record);
extern void func_020867a4(EventWinner *record, const NpcId *villager);
extern void func_020867e4(EventWinner *record, const DesignCreator *player);
extern void func_0208683c(EventWinner *record);
/* A player's name cleared. */
extern void func_02095238(DesignCreator *player);
/* The value of a creature item 0x12e8-0x131f and of an item 0x12b0-0x12e7. */
extern int func_0204c380(u16 *item);
extern int func_0204c308(u16 *item);
/* What the record's reset does to a player's field at 0x2416 (PlayerRecord_Field2416). */
extern void func_02088aa0(u8 *field);
extern void func_02088ac0(u8 *field);
extern void func_02088b1c(u8 *field, int value);
extern void func_02088b38(u8 *field, int value);

#define EVENT_WINNER_VILLAGERS 8
#define EVENT_WINNER_PLAYERS 4

/* The buildings EventWinner_ScoreAroundBuilding looks for, in a tile with flag 1, and the
 * tiles around it it counts: x from -5 to 4 and z from -1 to 8 of its tile. */
#define EVENT_WINNER_BUILDING_FIRST 0x5014
#define EVENT_WINNER_BUILDING_LAST 0x501a
#define EVENT_WINNER_BUILDING_FLAGS 1
#define EVENT_WINNER_AREA_LEFT 5
#define EVENT_WINNER_AREA_RIGHT 5
#define EVENT_WINNER_AREA_BACK 1
#define EVENT_WINNER_AREA_FRONT 9

#define EVENT_WINNER_GROUND_ATTR 4 /* CollisionGround's attribute EventWinner_IsNearAttr4 wants */

#define EVENT_WINNER_ITEM_SKIPPED 27

/* The creature items EventWinner_RandomSize sizes. */
#define EVENT_WINNER_CREATURES_FIRST 0x12e8
#define EVENT_WINNER_CREATURES_LAST 0x131f
#define EVENT_WINNER_OTHERS_FIRST 0x12b0
#define EVENT_WINNER_OTHERS_LAST 0x12e7
#define EVENT_WINNER_SCALE_MIN 0xccd   /* 0.8 */
#define EVENT_WINNER_SCALE_RANGE 0x666 /* up to 0.4 more */

/* The events EventWinner_ExpireForEvent's `event` 0-2 stand for (func_0203fdc4), the state
 * block's flag it clears for event 1 and the player flag for event 2; a record lasts a week. */
#define EVENT_WINNER_EVENT_0 0x0e
#define EVENT_WINNER_EVENT_1 0x11
#define EVENT_WINNER_EVENT_2 0x10
#define EVENT_WINNER_BLOCK_FLAG 0x11
#define EVENT_WINNER_PLAYER_FLAG 0x0f
#define EVENT_WINNER_DAYS 7

/* Rounding down as the ARM's arithmetic shift does. */
static int event_winner_shift(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The item at world tile (x, z) of the map's layer 0, or NULL. */
static u16 *event_winner_item_at(AcreMap *map, int x, int z)
{
    int acre_x = event_winner_shift(x, 4);
    int acre_z = event_winner_shift(z, 4);
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
}

/* func_020861dc: outdoors, the record's winner cleared, then on the scene's map each valid
 * villager's score (EventWinner_ScoreAroundHome) set against the player's
 * (EventWinner_ScoreAroundBuilding). The player wins with no villager, with a higher score, or
 * with an equal score above 0 on a coin toss; else one of the villagers of the best score, at
 * random (VillagerRoster_PickBit), when still valid. */
void EventWinner_JudgeGardens(EventWinner *record)
{
    VillagerTown *town = &data_021e5a2c;
    if (data_020e54a8 != 0) {
        return;
    }
    AcreMap *map = data_021c80bc;
    NpcId_Clear(func_020867a0(record));
    func_02095238(func_020867e0(record));
    if (map == NULL) {
        return;
    }

    u8 best_villagers = 0;
    int best = -1;
    int count = 0;
    for (int i = 0; i < EVENT_WINNER_VILLAGERS; i++) {
        u8 *villager = VillagerRoster_At(town, i);
        if (villager == NULL || NpcId_IsValid(TownVillager_NpcId(villager)) == 0) {
            continue;
        }
        int score = EventWinner_ScoreAroundHome(villager, map);
        if (score > best) {
            best_villagers = (u8) (1u << i);
            count = 1;
            best = score;
        } else if (score == best) {
            best_villagers = (u8) (best_villagers | (1u << i));
            count++;
        }
    }

    int player = EventWinner_ScoreAroundBuilding(record, map);
    if (count == 0 || player > best || (player > 0 && player == best && func_020644cc(2) == 0)) {
        func_020867e4(record, PlayerRecord_Player(PlayerRecords_Current()));
        return;
    }
    u8 *winner = VillagerRoster_At(town, VillagerRoster_PickBit(best_villagers, count, EVENT_WINNER_VILLAGERS));
    if (winner != NULL && NpcId_IsValid(TownVillager_NpcId(winner)) != 0) {
        func_020867a4(record, TownVillager_NpcId(winner));
    }
}
CLEAN_AS(func_020861dc, EventWinner_JudgeGardens)

/* func_020862ec: around the first building 0x5014-0x501a (in a tile with flag 1), the tiles
 * from 5 left to 4 right and from 1 back to 8 ahead whose item has a kind
 * (EventWinner_ItemKind) and that are near ground of attribute 4: their number times the
 * number of kinds among them, divided by 3 rounded up. 0 without the building. `record` is
 * not used. */
int EventWinner_ScoreAroundBuilding(EventWinner *record, AcreMap *map)
{
    (void) record;
    int acre_x = 0;
    int acre_z = 0;
    int x = 0;
    int z = 0;
    u16 first = EVENT_WINNER_BUILDING_FIRST;
    u16 last = EVENT_WINNER_BUILDING_LAST;
    if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &first, &last, EVENT_WINNER_BUILDING_FLAGS, 0) == 0) {
        return 0;
    }
    u32 kinds = 0;
    int tile_x = 0;
    int tile_z = 0;
    int count = 0;
    u32 kind = 0;
    AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
    for (int tz = tile_z - EVENT_WINNER_AREA_BACK; tz < tile_z + EVENT_WINNER_AREA_FRONT; tz++) {
        for (int tx = tile_x - EVENT_WINNER_AREA_LEFT; tx < tile_x + EVENT_WINNER_AREA_RIGHT; tx++) {
            u16 *item = event_winner_item_at(map, tx, tz);
            if (item == NULL || EventWinner_ItemKind(&kind, item) == 0) {
                continue;
            }
            EventWinnerTile tile = {tx, tz};
            if (EventWinner_IsNearAttr4(&tile) == 0) {
                continue;
            }
            if (kind < 32) {
                kinds |= 1u << kind;
            }
            count++;
        }
    }
    int score = count * EventWinner_CountBits(kinds);
    return (score + 2) / 3;
}
CLEAN_AS(func_020862ec, EventWinner_ScoreAroundBuilding)

/* func_020863dc: whether one of the eight tiles data_021d27e0 offsets from `tile` has ground of
 * attribute 4. */
int EventWinner_IsNearAttr4(const EventWinnerTile *tile)
{
    for (int i = 0; i < 8; i++) {
        const EventWinnerTile *offset = &data_021d27e0[i];
        CollisionGround ground;
        CollisionGround_InitAtUnit(&ground, tile->x + offset->x, tile->z + offset->z, 0, 0);
        if (ground.attr == EVENT_WINNER_GROUND_ATTR) {
            CollisionGround_Destroy(&ground);
            return 1;
        }
        CollisionGround_Destroy(&ground);
    }
    return 0;
}
CLEAN_AS(func_020863dc, EventWinner_IsNearAttr4)

/* func_0208642c: for a valid villager, of the 14 tiles data_021d2820 offsets from its house's
 * tile, those whose item has a kind: their number times the number of kinds among them. */
int EventWinner_ScoreAroundHome(u8 *villager, AcreMap *map)
{
    if (NpcId_IsValid(TownVillager_NpcId(villager)) == 0) {
        return 0;
    }
    u32 kinds = 0;
    const VillagerPlot *home = VillagerHome_Tile(villager);
    int x = home->x;
    int z = home->z;
    int count = 0;
    for (int i = 0; i < 14; i++) {
        const EventWinnerTile *offset = &data_021d2820[i];
        u16 *item = event_winner_item_at(map, x + offset->x, z + offset->z);
        u32 kind = 0;
        if (item != NULL && EventWinner_ItemKind(&kind, item) != 0) {
            if (kind < 32) {
                kinds |= 1u << kind;
            }
            count++;
        }
    }
    return count * EventWinner_CountBits(kinds);
}
CLEAN_AS(func_0208642c, EventWinner_ScoreAroundHome)

/* func_020864cc: the number of bits set. */
int EventWinner_CountBits(u32 bits)
{
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if ((bits >> i) & 1) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_020864cc, EventWinner_CountBits)

/* func_020864f4: the item's kind (EVENT_WINNER_ITEM_KINDS) into `kind`; 0 and nothing written
 * for an item without one. */
int EventWinner_ItemKind(u32 *kind, const u16 *item)
{
    u16 code = *item;
    if (code > 30 || code == EVENT_WINNER_ITEM_SKIPPED) {
        return 0;
    }
    *kind = code > EVENT_WINNER_ITEM_SKIPPED ? (u32) code - 1 : code;
    return 1;
}
CLEAN_AS(func_020864f4, EventWinner_ItemKind)

/* func_02086564: the item's value (func_0204c380 for creatures 0x12e8-0x131f, func_0204c308
 * for items 0x12b0-0x12e7) as fx32 times a random 0.8 to 1.2; 0 for other items. The random
 * number is drawn for any item. */
fx32 EventWinner_RandomSize(u16 *item)
{
    fx32 scale = (fx32) func_020644b4(EVENT_WINNER_SCALE_RANGE) + EVENT_WINNER_SCALE_MIN;
    u16 code = *item;
    if (code >= EVENT_WINNER_CREATURES_FIRST && code <= EVENT_WINNER_CREATURES_LAST) {
        return FX_MulFunc((fx32) ((u32) func_0204c380(item) << 12), scale);
    }
    if (code >= EVENT_WINNER_OTHERS_FIRST && code <= EVENT_WINNER_OTHERS_LAST) {
        return FX_MulFunc((fx32) ((u32) func_0204c308(item) << 12), scale);
    }
    return 0;
}
CLEAN_AS(func_02086564, EventWinner_RandomSize)

/* func_020865d8: the record kept while it is of this year, the town's event `event` stands for
 * (0, 1, 2: events 0x0e, 0x11, 0x10; any other: none) has been this year and the record is at
 * most 7 days old and not from before the event's day. Else, for event 1, flag 0x11 of the
 * state block cleared; for events 0 and 2, each player of the town has its field at 0x2416
 * reset (func_02088aa0, or for event 2 func_02088ac0 and player flag 0x0f cleared); then the
 * record started afresh (func_0208683c).
 * QUIRK: "not from before the event's day" compares days of the month: today's day less the
 * days since the event, against the record's day. */
void EventWinner_ExpireForEvent(EventWinner *record, int event)
{
    Date today;
    Calendar_Today(&today);
    int since_event = 0;
    switch (event) {
        case 0:
            since_event = func_0203fdc4(EVENT_WINNER_EVENT_0);
            break;
        case 1:
            since_event = func_0203fdc4(EVENT_WINNER_EVENT_1);
            break;
        case 2:
            since_event = func_0203fdc4(EVENT_WINNER_EVENT_2);
            break;
        default:
            break;
    }
    int age = Calendar_DaysFrom(&today, &record->date);
    if (today.year == record->date.year && since_event != -1 && age <= EVENT_WINNER_DAYS && age >= 0 &&
        today.day - since_event <= record->date.day) {
        return;
    }

    switch (event) {
        case 1:
            StateBlock_ClearFlag(data_021dc7a8, EVENT_WINNER_BLOCK_FLAG);
            break;
        case 0:
        case 2:
            for (int i = 0; i < EVENT_WINNER_PLAYERS; i++) {
                u8 *player = PlayerRecords_TownRecord(data_021dc7bc, i);
                if (player == NULL || PlayerRecord_HasPlayer(player) == 0) {
                    continue;
                }
                if (event == 2) {
                    func_02088ac0(PlayerRecord_Field2416(player));
                    PlayerRecord_ClearFlag(player, EVENT_WINNER_PLAYER_FLAG);
                } else {
                    func_02088aa0(PlayerRecord_Field2416(player));
                }
            }
            break;
        default:
            break;
    }
    func_0208683c(record);
}
CLEAN_AS(func_020865d8, EventWinner_ExpireForEvent)

/* func_020866b8: unless the record is of today, it is started afresh (func_0208683c) and each
 * player of the town has its field at 0x2416 told (func_02088b38 for mode 1, func_02088b1c for
 * mode 2, with 0; nothing for other modes). */
void EventWinner_ResetIfNotToday(EventWinner *record, int mode)
{
    Date today;
    Calendar_Today(&today);
    if (record->date.year == today.year && record->date.month == today.month && record->date.day == today.day) {
        return;
    }
    func_0208683c(record);
    for (int i = 0; i < EVENT_WINNER_PLAYERS; i++) {
        u8 *player = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (player == NULL || PlayerRecord_HasPlayer(player) == 0) {
            continue;
        }
        if (mode == 1) {
            func_02088b38(PlayerRecord_Field2416(player), 0);
        } else if (mode == 2) {
            func_02088b1c(PlayerRecord_Field2416(player), 0);
        }
    }
}
CLEAN_AS(func_020866b8, EventWinner_ResetIfNotToday)

/* func_02086744 */
int EventWinner_Size(const EventWinner *record)
{
    return record->size;
}
CLEAN_AS(func_02086744, EventWinner_Size)

/* func_02086748 */
void EventWinner_SetSize(EventWinner *record, int size)
{
    record->size = size;
}
CLEAN_AS(func_02086748, EventWinner_SetSize)

/* func_0208674c */
void EventWinner_GetItem(u16 *item, const EventWinner *record)
{
    *item = record->item;
}
CLEAN_AS(func_0208674c, EventWinner_GetItem)

/* func_02086754 */
void EventWinner_SetItem(EventWinner *record, const u16 *item)
{
    record->item = *item;
}
CLEAN_AS(func_02086754, EventWinner_SetItem)

/* func_0208675c */
NpcId *EventWinner_Npc2E(EventWinner *record)
{
    return (NpcId *) (uintptr_t) ((uintptr_t) record + offsetof(EventWinner, npc_2e));
}
CLEAN_AS(func_0208675c, EventWinner_Npc2E)
