/* A record of who won one of the town's events (event_winner.h). */
#include "event_winner.h"

#include <string.h>

#include "acre_tile.h"
#include "bbs.h"
#include "clean.h"
#include "date_time.h"
#include "field_collision.h"
#include "item_code.h"
#include "mail.h"
#include "mail_text.h"
#include "message_texts.h"
#include "number_text.h"
#include "player_record.h"
#include "player_records.h"
#include "state_block.h"
#include "town_villager.h"
#include "villager_home.h"
#include "villager_roster.h"
#include "villager_town.h"
#include "event_calendar.h"
#include "item_traits.h"
#include "letter.h"
#include "main_random.h"
#include "name_texts.h"
#include "player_field_2416.h"
#include "player_id.h"

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
    NpcId_Clear(EventWinner_Villager(record));
    PlayerId_Clear(EventWinner_Player(record));
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
    if (count == 0 || player > best || (player > 0 && player == best && MainRandom_Below(2) == 0)) {
        EventWinner_SetPlayer(record, PlayerRecord_Player(PlayerRecords_Current()));
        return;
    }
    u8 *winner = VillagerRoster_At(town, VillagerRoster_PickBit(best_villagers, count, EVENT_WINNER_VILLAGERS));
    if (winner != NULL && NpcId_IsValid(TownVillager_NpcId(winner)) != 0) {
        EventWinner_SetVillager(record, TownVillager_NpcId(winner));
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
    fx32 scale = (fx32) MainRandom_BelowB(EVENT_WINNER_SCALE_RANGE) + EVENT_WINNER_SCALE_MIN;
    u16 code = *item;
    if (code >= EVENT_WINNER_CREATURES_FIRST && code <= EVENT_WINNER_CREATURES_LAST) {
        return FX_MulFunc((fx32) ((u32) ItemTraits_FishValue(item) << 12), scale);
    }
    if (code >= EVENT_WINNER_OTHERS_FIRST && code <= EVENT_WINNER_OTHERS_LAST) {
        return FX_MulFunc((fx32) ((u32) ItemTraits_InsectSize(item) << 12), scale);
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
            since_event = EventCalendar_DaysSinceStart(EVENT_WINNER_EVENT_0);
            break;
        case 1:
            since_event = EventCalendar_DaysSinceStart(EVENT_WINNER_EVENT_1);
            break;
        case 2:
            since_event = EventCalendar_DaysSinceStart(EVENT_WINNER_EVENT_2);
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
                    PlayerField2416_ClearBytes0B((PlayerField2416 *) (void *) PlayerRecord_Field2416(player));
                    PlayerRecord_ClearFlag(player, EVENT_WINNER_PLAYER_FLAG);
                } else {
                    PlayerField2416_ClearGardening((PlayerField2416 *) (void *) PlayerRecord_Field2416(player));
                }
            }
            break;
        default:
            break;
    }
    EventWinner_Restart(record);
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
    EventWinner_Restart(record);
    for (int i = 0; i < EVENT_WINNER_PLAYERS; i++) {
        u8 *player = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (player == NULL || PlayerRecord_HasPlayer(player) == 0) {
            continue;
        }
        if (mode == 1) {
            PlayerField2416_SetFishing((PlayerField2416 *) (void *) PlayerRecord_Field2416(player), 0);
        } else if (mode == 2) {
            PlayerField2416_SetInsects((PlayerField2416 *) (void *) PlayerRecord_Field2416(player), 0);
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

/* ---- The record's parts, its life, and the letters and notice of its event ---- */

/* The text objects the letters and the notice fill: a player's name (func_02094fd4 makes one)
 * and an item's name (func_02062f90). */
typedef struct EventWinnerName {
    u32 words[0x20 / 4];
} EventWinnerName;
typedef struct EventWinnerItemName {
    u32 words[0x28 / 4];
} EventWinnerItemName;

/* The state block's flag of a winner to announce: set by the events' overlays when they record
 * one, cleared once the notice is posted. */
#define EVENT_WINNER_NOTICE_FLAG 0x0f
/* The game's day starts at 6:00. */
#define EVENT_WINNER_DAY_START_HOUR 6
/* A record whose day is this many days away (either way) is dropped unsent. */
#define EVENT_WINNER_STALE_DAYS 10
/* The gardening letters wait until a week after the town's event 0x0e. */
#define EVENT_WINNER_GARDENS_WAIT 7
/* The prizes the winner's letter carries, by kind. */
#define EVENT_WINNER_PRIZE_FISHING 0x3878
#define EVENT_WINNER_PRIZE_INSECTS 0x387c
#define EVENT_WINNER_PRIZE_GARDENS 0x3880
/* The text slots of the letters and the notice (MailText_SetPart*). */
#define EVENT_WINNER_SLOT_MONTH 0
#define EVENT_WINNER_SLOT_DAY 1
#define EVENT_WINNER_SLOT_ITEM 2
#define EVENT_WINNER_SLOT_SIZE 3
#define EVENT_WINNER_SLOT_NAME 4
#define EVENT_WINNER_SLOT_GARDENER 0 /* the gardening letters' and notice's name */
#define EVENT_WINNER_SIZE_DIGITS 3

/* The archives of the letters and of the notices, by kind (0 and 1 are both fishing's). */
extern const char *const data_020e1fcc[4];
extern const char *const data_020e1fbc[4];
/* The letters' kind byte (0x0f) and paper (0x10). */
extern u8 data_020e1f64[];
extern u8 data_020e1f5c[];

/* Whether the record's kind is one of the two contests (fishing, insects). */
static int event_winner_is_contest(const EventWinner *record)
{
    return record->date.unused == EVENT_WINNER_KIND_FISHING || record->date.unused == EVENT_WINNER_KIND_INSECTS;
}

/* Whether the record's kind is one of the three events. */
static int event_winner_has_kind(const EventWinner *record)
{
    return event_winner_is_contest(record) || record->date.unused == EVENT_WINNER_KIND_GARDENS;
}

/* Whether an item code is the empty one: for a code with a variant, whether its item is the
 * empty code's item. */
static int event_winner_item_is_none(u16 *item)
{
    if (ItemCode_HasVariant(item)) {
        u16 none = ITEM_CODE_NONE;
        int own = ItemCode_VariantItem(item);
        return own == ItemCode_VariantItem(&none);
    }
    return *item == ITEM_CODE_NONE;
}

/* Whether two ids name the same player: the same town, then func_0209518c. */
static int event_winner_same_player(const DesignCreator *a, const DesignCreator *b)
{
    return a->town_id == b->town_id && memcmp(a->town_name, b->town_name, sizeof(a->town_name)) == 0 &&
           PlayerId_SamePlayer(a, b) != 0;
}

/* The size into `text`: to one decimal for fishing, in whole units otherwise. */
static void event_winner_format_size(const EventWinner *record, MessageText46 *text)
{
    if (record->date.unused == EVENT_WINNER_KIND_FISHING) {
        NumberText_SetFixed(text, record->size, 1);
    } else {
        NumberText_Format(text, record->size >> 12, EVENT_WINNER_SIZE_DIGITS, 0, 0, 0);
    }
}

/* The record's item named in text slot 2, unless it has none. */
static void event_winner_name_item(EventWinner *record)
{
    if (!event_winner_item_is_none(&record->item)) {
        EventWinnerItemName item_name;
        NameText_ConstructItem((NameText *) &item_name, &record->item);
        MailText_SetPartText(EVENT_WINNER_SLOT_ITEM, &item_name);
        NameText_Destruct((NameText *) &item_name);
    }
}

/* A copy a halfword at a time from the first, as the ROM's structure copies are: when the two
 * overlap, the result is the ROM's. */
static void copy_halfwords(void *dst, const void *src, size_t size)
{
    u16 *d = dst;
    const u16 *s = src;
    for (size_t i = 0; i < size / 2; i++) {
        d[i] = s[i];
    }
}

/* func_02086760 */
void EventWinner_SetNpc2E(EventWinner *record, const NpcId *npc)
{
    copy_halfwords(&record->npc_2e, npc, sizeof record->npc_2e);
}
CLEAN_AS(func_02086760, EventWinner_SetNpc2E)

/* func_02086794 */
void EventWinner_ClearNpc2E(EventWinner *record)
{
    NpcId_Clear(&record->npc_2e);
}
CLEAN_AS(func_02086794, EventWinner_ClearNpc2E)

/* func_020867a0 */
NpcId *EventWinner_Villager(EventWinner *record)
{
    return &record->villager;
}
CLEAN_AS(func_020867a0, EventWinner_Villager)

/* func_020867a4: a villager won; the player is cleared. */
void EventWinner_SetVillager(EventWinner *record, const NpcId *villager)
{
    copy_halfwords(&record->villager, villager, sizeof record->villager);
    PlayerId_Clear(&record->player);
}
CLEAN_AS(func_020867a4, EventWinner_SetVillager)

/* func_020867e0 */
DesignCreator *EventWinner_Player(EventWinner *record)
{
    return &record->player;
}
CLEAN_AS(func_020867e0, EventWinner_Player)

/* func_020867e4: a player won; the villager is cleared. */
void EventWinner_SetPlayer(EventWinner *record, const DesignCreator *player)
{
    copy_halfwords(&record->player, player, sizeof record->player);
    NpcId_Clear(&record->villager);
}
CLEAN_AS(func_020867e4, EventWinner_SetPlayer)

/* func_02086834: the record's kind (EventWinnerKind). */
void EventWinner_SetKind(EventWinner *record, u8 kind)
{
    record->date.unused = kind;
}
CLEAN_AS(func_02086834, EventWinner_SetKind)

/* func_0208683c: the record emptied (EventWinner_Reset) and started today, of no kind. */
void EventWinner_Restart(EventWinner *record)
{
    EventWinner_Reset(record);
    Date today;
    Calendar_Today(&today);
    record->date.year = today.year;
    record->date.month = today.month;
    record->date.day = today.day;
    record->date.unused = EVENT_WINNER_KIND_NONE;
}
CLEAN_AS(func_0208683c, EventWinner_Restart)

/* func_02086874: no winner, no second villager, no item and no size; the date is kept. */
void EventWinner_Reset(EventWinner *record)
{
    PlayerId_Clear(&record->player);
    NpcId_Clear(&record->villager);
    NpcId_Clear(&record->npc_2e);
    record->item = ITEM_CODE_NONE;
    record->size = 0;
}
CLEAN_AS(func_02086874, EventWinner_Reset)

/* func_020868a0: the destructor, parts from the last. */
EventWinner *EventWinner_Destruct(EventWinner *record)
{
    NpcId_Destruct(&record->npc_2e);
    NpcId_Destruct(&record->villager);
    PlayerId_Destruct(&record->player);
    return record;
}
CLEAN_AS(func_020868a0, EventWinner_Destruct)

/* func_020868c0: the constructor; no item. The size and the date are left as they are. */
EventWinner *EventWinner_Construct(EventWinner *record)
{
    PlayerId_Construct(&record->player);
    NpcId_Construct(&record->villager);
    NpcId_Construct(&record->npc_2e);
    record->item = ITEM_CODE_NONE;
    return record;
}
CLEAN_AS(func_020868c0, EventWinner_Construct)

/* func_020868e8: once the event's day is over, its letters to the town's players and its notice
 * (EventWinner_PostNotice), then the record emptied.
 *
 * Nothing happens without a winner, for a record of no kind or without a full date. A record
 * whose day is 10 days or more from today's (the game's day, from 6:00) either way is emptied
 * and its notice dropped. A contest's letters go out on any day other than the record's; the
 * gardening letters wait until the town's event 0x0e is at least a week old (on the 7th day,
 * from 6:00) when it has been this year, and for a day after the record's. A gardening record
 * that a villager won only has its notice posted.
 *
 * For a contest, each player of the town who entered it (func_02088b48, func_02088b30) gets a
 * letter: message 0-2 for the winner, 3-5 for the others, with the record's month, day, item
 * and size and the player's name. For gardening, the winner and each player owed a letter
 * (func_02088ab8, then cleared) get message 0-2 with their own name. The winner's letter, and
 * every gardening letter, carry the prize.
 * QUIRK: a record of year 0 (2000) counts as having no date.
 * QUIRK: two more number texts are made and unmade without being used. */
void EventWinner_SendLetters(EventWinner *record)
{
    if (PlayerId_IsSet(&record->player) == 0 && NpcId_IsValid(&record->villager) == 0) {
        return;
    }
    if (!event_winner_has_kind(record)) {
        return;
    }
    u8 kind = record->date.unused;
    Date today;
    Calendar_Today(&today);
    if (record->date.year == 0 || record->date.month == 0 || record->date.day == 0) {
        return;
    }

    DateTime recorded;
    DateTime_Set(&recorded, &record->date, EVENT_WINNER_DAY_START_HOUR, 0, 0);
    DateTime now = {0};
    DateTime_Now(&now);
    /* The game's day: before 6:00 it is the day before, from 6:00. */
    if (now.hour < EVENT_WINNER_DAY_START_HOUR) {
        DateTime_SubtractDays(&now, 1);
        now.hour = EVENT_WINNER_DAY_START_HOUR;
        now.minute = 0;
        now.second = 0;
    }
    int order = DateTime_Compare(&now, &recorded, DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR);
    if ((order == 1 && DateTime_DaysBetween(&recorded, &now) >= EVENT_WINNER_STALE_DAYS) ||
        (order == -1 && DateTime_DaysBetween(&now, &recorded) >= EVENT_WINNER_STALE_DAYS)) {
        EventWinner_Reset(record);
        StateBlock_ClearFlag(data_021dc7a8, EVENT_WINNER_NOTICE_FLAG);
        return;
    }

    if (kind != EVENT_WINNER_KIND_GARDENS) {
        if (record->date.year == today.year && record->date.month == today.month && record->date.day == today.day) {
            return;
        }
    } else {
        int since_event = EventCalendar_DaysSinceStart(EVENT_WINNER_EVENT_0);
        /* The clock read again, this time as it is. */
        DateTime_Now(&now);
        if (since_event != -1) {
            if (since_event < EVENT_WINNER_GARDENS_WAIT) {
                return;
            }
            if (since_event == EVENT_WINNER_GARDENS_WAIT && now.hour < EVENT_WINNER_DAY_START_HOUR) {
                return;
            }
        }
        if (order == 1 && DateTime_DaysBetween(&recorded, &now) < 1) {
            return;
        }
    }

    if (kind == EVENT_WINNER_KIND_GARDENS && PlayerId_IsSet(&record->player) == 0) {
        EventWinner_PostNotice(record);
        EventWinner_Reset(record);
        return;
    }

    MessageText46 size_text;
    MessageText46 unused_text_a;
    MessageText46 unused_text_b;
    MailLetter letter;
    EventWinnerName name;
    MessageText46_Construct(&size_text);
    MessageText46_Construct(&unused_text_a);
    MessageText46_Construct(&unused_text_b);
    Letter_Construct((Letter *) &letter);
    PlayerIdText_Construct((PlayerIdText *) &name);

    u8 message = 0;
    for (int i = 0; i < EVENT_WINNER_PLAYERS; i++) {
        u8 *player = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (player == NULL || PlayerRecord_HasPlayer(player) == 0) {
            continue;
        }
        u8 *field = PlayerRecord_Field2416(player);
        int send = 0;
        if (event_winner_is_contest(record)) {
            MailText_SetPartNumberB(EVENT_WINNER_SLOT_MONTH, record->date.month);
            MailText_SetPartNumber(EVENT_WINNER_SLOT_DAY, record->date.day);
            event_winner_name_item(record);
            if (record->size > 0) {
                event_winner_format_size(record, &size_text);
                MailText_SetPartText(EVENT_WINNER_SLOT_SIZE, &size_text);
            }
            send = kind == EVENT_WINNER_KIND_FISHING ? PlayerField2416_Fishing((PlayerField2416 *) (void *) field)
                                                     : PlayerField2416_Insects((PlayerField2416 *) (void *) field);
        } else {
            DesignCreator *who = PlayerRecord_Player(player);
            if (event_winner_same_player(&record->player, who) ||
                PlayerField2416_Gardening((PlayerField2416 *) (void *) field) != 0) {
                message = (u8) MainRandom_Below(3);
                PlayerId_NameToText(PlayerRecord_Player(player), (TextBase *) &name);
                PlayerField2416_ClearGardening((PlayerField2416 *) (void *) field);
                MailText_SetPartText(EVENT_WINNER_SLOT_GARDENER, &name);
                send = 1;
            }
        }
        if (send == 0) {
            continue;
        }

        if (event_winner_is_contest(record)) {
            DesignCreator *who = PlayerRecord_Player(player);
            if (event_winner_same_player(&record->player, who)) {
                message = (u8) MainRandom_Below(3);
            } else {
                message = (u8) (MainRandom_Below(3) + 3);
            }
            PlayerId_NameToText(PlayerRecord_Player(player), (TextBase *) &name);
            MailText_SetPartText(EVENT_WINNER_SLOT_NAME, &name);
        }
        Letter_WriteSpecialToPlayer((Letter *) &letter, &message, data_020e1fcc[kind], data_020e1f64, data_020e1f5c,
                                    PlayerRecord_Player(player));
        DesignCreator *who = PlayerRecord_Player(player);
        if (event_winner_same_player(&record->player, who) || kind == EVENT_WINNER_KIND_GARDENS) {
            u16 prize = EVENT_WINNER_PRIZE_FISHING;
            if (kind == EVENT_WINNER_KIND_INSECTS) {
                prize = EVENT_WINNER_PRIZE_INSECTS;
            } else if (kind == EVENT_WINNER_KIND_GARDENS) {
                prize = EVENT_WINNER_PRIZE_GARDENS;
            }
            Letter_SetItem((Letter *) &letter, prize, 1);
        }
        Mail_Post(&letter);
    }

    EventWinner_PostNotice(record);
    EventWinner_Reset(record);
    PlayerIdText_Destruct((PlayerIdText *) &name);
    Letter_Destruct((Letter *) &letter);
    MessageText46_Destruct(&unused_text_b);
    MessageText46_Destruct(&unused_text_a);
    MessageText46_Destruct(&size_text);
}
CLEAN_AS(func_020868e8, EventWinner_SendLetters)

/* func_02086d24: while flag 0x0f of the state block says a winner is to be announced, the
 * event's notice on the board: message 0-2 of its archive (0-1 for gardening). A contest's has
 * the record's month, day, the winner's name (a player's, else the villager's), size (as in the
 * letters) and item; gardening's has the name only. Then the flag is cleared; it is cleared too
 * when there is no winner. */
void EventWinner_PostNotice(EventWinner *record)
{
    if (PlayerId_IsSet(&record->player) == 0 && NpcId_IsValid(&record->villager) == 0) {
        StateBlock_ClearFlag(data_021dc7a8, EVENT_WINNER_NOTICE_FLAG);
        return;
    }
    if (!event_winner_has_kind(record)) {
        return;
    }
    if (StateBlock_TestFlag(data_021dc7a8, EVENT_WINNER_NOTICE_FLAG) == 0) {
        return;
    }

    EventWinnerName name;
    PlayerIdText_Construct((PlayerIdText *) &name);
    if (PlayerId_IsSet(&record->player) != 0) {
        PlayerId_NameToText(&record->player, (TextBase *) &name);
    } else {
        NpcId_FormatName(&record->villager, (char *) &name);
    }

    if (event_winner_is_contest(record)) {
        MailText_SetPartNumberB(EVENT_WINNER_SLOT_MONTH, record->date.month);
        MailText_SetPartNumber(EVENT_WINNER_SLOT_DAY, record->date.day);
        MailText_SetPartText(EVENT_WINNER_SLOT_NAME, &name);
        if (record->size > 0) {
            MessageText46 size_text;
            MessageText46_Construct(&size_text);
            event_winner_format_size(record, &size_text);
            MailText_SetPartText(EVENT_WINNER_SLOT_SIZE, &size_text);
            MessageText46_Destruct(&size_text);
        }
        event_winner_name_item(record);
    } else {
        MailText_SetPartText(EVENT_WINNER_SLOT_GARDENER, &name);
    }

    int message = event_winner_is_contest(record) ? (int) MainRandom_Below(3) : (int) MainRandom_Below(2);
    Bbs_PostMessage(message, data_020e1fbc[record->date.unused]);
    StateBlock_ClearFlag(data_021dc7a8, EVENT_WINNER_NOTICE_FLAG);
    PlayerIdText_Destruct((PlayerIdText *) &name);
}
CLEAN_AS(func_02086d24, EventWinner_PostNotice)
