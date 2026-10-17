/* What a villager out walking in the town reads and keeps in the game's records
 * (outdoor_villager_records.h). */
#include "outdoor_villager_records.h"

#include <stdint.h>

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/event_winner.h"
#include "main/insect_draw.h"
#include "main/creature_draw.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/session_players.h"
#include "main/sky.h"
#include "main/town_villager.h"
#include "main/villager_mode.h"
#include "main/villager_mode_record.h"
#include "main/villager_object.h"
#include "main/villager_scene_object.h"
#include "main/villager_status.h"
#include "outdoor_villager.h"

/* The record of the event's winner. */
extern EventWinner data_021f3aa4;
/* The town's map (main's acre_map.h), or null. */
extern AcreMap *data_021c80bc;
/* The weights of the bands a villager in the contest draws its catch from (5 each; the two
 * tables are the same but for the weight of band 2). */
extern const u8 data_ov068_0227675c[];
extern const u8 data_ov068_02276774[];

/* The parts of the villager read here besides outdoor_villager.h's. */
#define RECORDS_MINUTE 0xa08 /* u8: the minute of the clock it last looked at */

/* The town events (VillagerSceneObject_Event) of the contests. */
#define RECORDS_EVENT_FISH 3
#define RECORDS_EVENT_INSECT 4
#define RECORDS_EVENT_5 5

/* The draw of a catch: a band (0 to 3) picked by weight; 4 draws nothing. */
#define RECORDS_BANDS 5
#define RECORDS_BAND_NONE 4
#define RECORDS_MODE_FISH 1   /* the villager's mode that draws from the second fish table */
#define RECORDS_MODE_INSECT 0 /* the villager's mode that draws from the second insect table */
#define RECORDS_FISH_FIRST 0x12e8
#define RECORDS_FISH_LAST 0x131f
#define RECORDS_INSECT_FIRST 0x12b0
#define RECORDS_INSECT_LAST 0x12e7
#define RECORDS_NO_ITEM 0xfff1

/* The acre flag of the acres where it does not take part. */
#define RECORDS_ACRE_FLAG 0x200
#define RECORDS_ACRE_SHIFT 17

/* The kinds of the moment (byte 0x1c of the state entry) given by the town events, and the one
 * kept when none is drawn. */
#define RECORDS_KIND_NONE 8
#define RECORDS_KIND_FISH 1
#define RECORDS_KIND_INSECT 0
#define RECORDS_KIND_EVENT_5 5
#define RECORDS_KIND_DAYS 3      /* the days after which the kind may change */
#define RECORDS_REDRAW_CHANCE 30 /* in 100 */

/* The held items. */
#define RECORDS_UMBRELLA_FIRST 0x1380
#define RECORDS_UMBRELLA_LAST 0x139f
#define RECORDS_ITEM_1378 0x1378
#define RECORDS_RAIN 1 /* Sky_Falling while rain falls */

static u8 *records_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

/* Its town record (its vtable slot 0x64), or null. */
static u8 *records_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    uintptr_t code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) code)(villager);
}

/* Whether a town record is of a villager (its NPC code valid). */
static int records_valid(u8 *record)
{
    return NpcId_IsValid(TownVillager_NpcId(record)) != 0;
}

/* The mode of the villager's mode record. */
static VillagerModeRecord *records_mode_record(u8 *record)
{
    return VillagerObject_RecordMode((VillagerRecord *) (void *) VillagerStatus_ModeRecord(record));
}

static int records_is_umbrella(u16 item)
{
    return item >= RECORDS_UMBRELLA_FIRST && item <= RECORDS_UMBRELLA_LAST;
}

/* func_ov068_0226cf58: the tally of the state entry of its town record, or null without a
 * record of a villager or a state entry. */
VillagerTally *OutdoorVillagerRecords_Tally(u8 *villager)
{
    u8 *record = records_record(villager);
    if (record == NULL || !records_valid(record)) {
        return NULL;
    }
    VillagerState *state = VillagerStatus_StateEntry(record);
    if (state == NULL) {
        return NULL;
    }
    return VillagerState_Tally(state);
}
CLEAN_AS(func_ov068_0226cf58, OutdoorVillagerRecords_Tally)

/* func_ov068_0226cf8c: byte 0x18 of the state entry of its town record, 0 without one. The
 * town record is asked for again for each step. */
u8 OutdoorVillagerRecords_Byte18(u8 *villager)
{
    VillagerState *state = NULL;
    if (records_record(villager) != NULL && records_valid(records_record(villager))) {
        state = VillagerStatus_StateEntry(records_record(villager));
    }
    if (state == NULL) {
        return 0;
    }
    return (u8) VillagerState_GetByte18(state);
}
CLEAN_AS(func_ov068_0226cf8c, OutdoorVillagerRecords_Byte18)

/* func_ov068_0226d01c: once a minute of the clock (the minute kept at 0xa08), unless an object
 * event runs: a villager in a contest where it may take part (OutdoorVillagerRecords_InContest)
 * draws a catch, an insect in the insect contest (event 4) or a fish in the fishing tourney
 * (event 3). */
void OutdoorVillagerRecords_EachMinute(u8 *villager)
{
    DateTime now = {0};
    DateTime_Now(&now);
    u8 *minute = records_at(villager, RECORDS_MINUTE);
    if (*minute == now.minute) {
        return;
    }
    if (EventQueue_IsObjectEvent() == 0 && OutdoorVillagerRecords_InContest(villager) != 0) {
        switch (VillagerSceneObject_Event(villager)) {
            case RECORDS_EVENT_INSECT:
                OutdoorVillagerRecords_CatchInsect(villager, (u8 *) &now);
                break;
            case RECORDS_EVENT_FISH:
                OutdoorVillagerRecords_CatchFish(villager, (u8 *) &now);
                break;
            default:
                break;
        }
    }
    *minute = now.minute;
}
CLEAN_AS(func_ov068_0226d01c, OutdoorVillagerRecords_EachMinute)

/* Makes the villager the event's winner with `item` of `size` (fx32). */
static void records_win(u8 *villager, const u16 *item, fx32 size)
{
    EventWinner_SetVillager(&data_021f3aa4, TownVillager_NpcId(records_record(villager)));
    EventWinner_SetSize(&data_021f3aa4, size);
    EventWinner_SetItem(&data_021f3aa4, item);
}

/* func_ov068_0226d080: in the fishing tourney, a fish of a band picked by weight (the second
 * table for a villager of mode 1) that swims in this month, day and hour; when it is a fish
 * (0x12e8 to 0x131f) and its random size, in tenths of a unit, beats the winner's, the villager
 * becomes the winner with it. `now` is the clock (a DateTime). */
void OutdoorVillagerRecords_CatchFish(u8 *villager, u8 *now)
{
    const DateTime *when = (const DateTime *) (const void *) now;
    const u8 *weights = data_ov068_0227675c;
    if (VillagerModeRecord_Mode(records_mode_record(records_record(villager))) == RECORDS_MODE_FISH) {
        weights = data_ov068_02276774;
    }
    unsigned int band = (unsigned int) InsectDraw_PickByWeights(weights, RECORDS_BANDS);
    if (band >= RECORDS_BAND_NONE) {
        return;
    }
    u16 item = RECORDS_NO_ITEM;
    if (CreatureDraw_FishOfBandsHours(&item, (int) band, (int) band + 1, when->month, when->day, when->hour, when->hour) ==
        0) {
        return;
    }
    if (item < RECORDS_FISH_FIRST || item > RECORDS_FISH_LAST) {
        return;
    }
    fx32 size = EventWinner_RandomSize(&item);
    s32 best = (s32) ((u32) EventWinner_Size(&data_021f3aa4) * 10u);
    if ((s32) ((u32) size * 10u) >> 12 > best >> 12) {
        records_win(villager, &item, size);
    }
}
CLEAN_AS(func_ov068_0226d080, OutdoorVillagerRecords_CatchFish)

/* func_ov068_0226d14c: in the insect contest, an insect of a band picked by weight (the second
 * table for a villager of mode 0) that is out at this hour and month; when it is an insect
 * (0x12b0 to 0x12e7) and its random size, in whole units, beats the winner's, the villager
 * becomes the winner with it. */
void OutdoorVillagerRecords_CatchInsect(u8 *villager, u8 *now)
{
    const DateTime *when = (const DateTime *) (const void *) now;
    const u8 *weights = data_ov068_0227675c;
    if (VillagerModeRecord_Mode(records_mode_record(records_record(villager))) == RECORDS_MODE_INSECT) {
        weights = data_ov068_02276774;
    }
    unsigned int band = (unsigned int) InsectDraw_PickByWeights(weights, RECORDS_BANDS);
    if (band >= RECORDS_BAND_NONE) {
        return;
    }
    u16 item = RECORDS_NO_ITEM;
    if (InsectDraw_OfBandsHours(&item, (int) band, (int) band + 1, when->hour, when->hour, when->month) == 0) {
        return;
    }
    if (item < RECORDS_INSECT_FIRST || item > RECORDS_INSECT_LAST) {
        return;
    }
    fx32 size = EventWinner_RandomSize(&item);
    if (size >> 12 > EventWinner_Size(&data_021f3aa4) >> 12) {
        records_win(villager, &item, size);
    }
}
CLEAN_AS(func_ov068_0226d14c, OutdoorVillagerRecords_CatchInsect)

/* func_ov068_0226d20c: whether it takes part in a contest now: the town event when it was made
 * is 3 or 4, and this console's player is in an acre without flag 0x200. */
int OutdoorVillagerRecords_InContest(u8 *villager)
{
    u8 event = VillagerSceneObject_Event(villager);
    if (event != RECORDS_EVENT_FISH && event != RECORDS_EVENT_INSECT) {
        return 0;
    }
    int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    AcreMap *map = data_021c80bc;
    if (player == 0 || map == NULL) {
        return 0;
    }
    const Vec3 *position =
        (const Vec3 *) (const void *) records_at((u8 *) (uintptr_t) (u32) player, OUTDOOR_VILLAGER_POSITION);
    return AcreTile_AcreHasFlags(map, (u32) (position->x >> RECORDS_ACRE_SHIFT), (u32) (position->z >> RECORDS_ACRE_SHIFT),
                                 RECORDS_ACRE_FLAG) == NULL;
}
CLEAN_AS(func_ov068_0226d20c, OutdoorVillagerRecords_InContest)

/* func_ov068_0226d264: the item its state entry says it holds, brought up to date: an umbrella
 * (0x1380 to 0x139f) put away unless rain falls; then, holding no umbrella, the item of its
 * kind of the moment (VillagerModeRecord_KindItem) unless it already holds it (for an item
 * with variants, any variant of it); then while rain falls item 0x1378 is changed for its
 * umbrella (TownVillager_Item1380). Only for a town record of a villager. */
void OutdoorVillagerRecords_RefreshItem(u8 *villager)
{
    u8 *record = records_record(villager);
    if (record == NULL || !records_valid(record)) {
        return;
    }
    VillagerState *state = VillagerStatus_StateEntry(record);
    int kind = VillagerState_GetByte1C(state);
    int sky = Sky_Falling();
    if (sky != RECORDS_RAIN && records_is_umbrella(*VillagerState_Item(state))) {
        u16 none = RECORDS_NO_ITEM;
        VillagerState_SetItem(state, &none);
    }
    if (!records_is_umbrella(*VillagerState_Item(state))) {
        u16 wanted;
        VillagerModeRecord_KindItem(&wanted, kind);
        u16 *held = VillagerState_Item(state);
        int same;
        if (ItemCode_HasVariant(held)) {
            same = ItemCode_VariantItem(held) == ItemCode_VariantItem(&wanted);
        } else {
            same = *held == wanted;
        }
        if (!same) {
            VillagerState_SetItem(state, &wanted);
        }
    }
    if (*VillagerState_Item(state) == RECORDS_ITEM_1378 && sky == RECORDS_RAIN) {
        u16 umbrella;
        TownVillager_Item1380(&umbrella, record);
        VillagerState_SetItem(state, &umbrella);
    }
}
CLEAN_AS(func_ov068_0226d264, OutdoorVillagerRecords_RefreshItem)

/* func_ov068_0226d374: its kind of the moment redrawn (OutdoorVillagerRecords_RedrawKind) when
 * it is not one the mode record allows (VillagerModeRecord_IsKindMode, or 8), when it is not the
 * record's mode and the mode is under 3 days old, or during the town events 3 to 5. Only for a
 * town record of a villager. */
void OutdoorVillagerRecords_CheckKind(u8 *villager)
{
    u8 *record = records_record(villager);
    if (record == NULL || !records_valid(record)) {
        return;
    }
    int kind = VillagerState_GetByte1C(VillagerStatus_StateEntry(record));
    VillagerModeRecord *mode = records_mode_record(record);
    DateTime now = {0};
    DateTime_Now(&now);
    int keep = (VillagerModeRecord_IsKindMode((unsigned int) kind) != 0 || kind == RECORDS_KIND_NONE) &&
               (kind == VillagerModeRecord_Mode(mode) || VillagerModeRecord_IsKindDaysOld(mode, &now, RECORDS_KIND_DAYS) != 0);
    if (!keep || VillagerSceneObject_Event(villager) == RECORDS_EVENT_FISH ||
        VillagerSceneObject_Event(villager) == RECORDS_EVENT_INSECT ||
        VillagerSceneObject_Event(villager) == RECORDS_EVENT_5) {
        OutdoorVillagerRecords_RedrawKind(villager);
    }
}
CLEAN_AS(func_ov068_0226d374, OutdoorVillagerRecords_CheckKind)

/* func_ov068_0226d408: its kind of the moment drawn again: the record's mode, or with 30 in
 * 100 when the mode is 3 days old or more a random one of 0 to 7; kept when the mode record
 * allows it (or it is 8), else 8; the town events 3, 4 and 5 give 1, 0 and 5. Only for a town
 * record of a villager. */
void OutdoorVillagerRecords_RedrawKind(u8 *villager)
{
    u8 *record = records_record(villager);
    if (record == NULL || !records_valid(record)) {
        return;
    }
    int kind = RECORDS_KIND_NONE;
    VillagerModeRecord *mode = records_mode_record(record);
    int drawn = VillagerModeRecord_Mode(mode);
    unsigned int chance = MainRandom_Below(100);
    DateTime now = {0};
    DateTime_Now(&now);
    if ((int) chance < RECORDS_REDRAW_CHANCE && VillagerModeRecord_IsKindDaysOld(mode, &now, RECORDS_KIND_DAYS) != 0) {
        drawn = (u8) MainRandom_Below(RECORDS_KIND_NONE);
    }
    if (VillagerModeRecord_IsKindMode((unsigned int) drawn) != 0 || drawn == RECORDS_KIND_NONE) {
        kind = drawn;
    }
    switch (VillagerSceneObject_Event(villager)) {
        case RECORDS_EVENT_FISH:
            kind = RECORDS_KIND_FISH;
            break;
        case RECORDS_EVENT_INSECT:
            kind = RECORDS_KIND_INSECT;
            break;
        case RECORDS_EVENT_5:
            kind = RECORDS_KIND_EVENT_5;
            break;
        default:
            break;
    }
    VillagerState_SetByte1C(VillagerStatus_StateEntry(record), kind);
}
CLEAN_AS(func_ov068_0226d408, OutdoorVillagerRecords_RedrawKind)

/* func_ov068_0226d598: its memory of this console's player (VillagerMemory_Of), or null without
 * a current player record whose player is set or without a town record of a villager. The
 * current record is asked for twice, and the town record whatever the player. */
VillagerMemory *OutdoorVillagerRecords_MemoryOfPlayer(u8 *villager)
{
    DesignCreator *player = NULL;
    if (PlayerRecords_Current() != NULL) {
        player = PlayerRecord_Player(PlayerRecords_Current());
    }
    u8 *record = records_record(villager);
    if (player == NULL || PlayerId_IsSet(player) == 0 || record == NULL || !records_valid(record)) {
        return NULL;
    }
    return VillagerMemory_Of(record, player);
}
CLEAN_AS(func_ov068_0226d598, OutdoorVillagerRecords_MemoryOfPlayer)
