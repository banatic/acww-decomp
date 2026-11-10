/* The town's villagers as one block (villager_town.h). */
#include "villager_town.h"

#include "clean.h"
#include "date_time.h"
#include "design.h"
#include "session.h"
#include "villager_bonds.h"
#include "actor_table.h"
#include "calendar.h"
#include "event_announce.h"
#include "event_calendar.h"
#include "villager_errand.h"
#include "letter.h"
#include "player_id.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "room_score.h"
#include "scene_query.h"
#include "town_villager.h"
#include "villager_entry.h"
#include "villager_furniture.h"
#include "villager_house_items.h"
#include "villager_mail.h"
#include "villager_memories.h"
#include "villager_memory_bits.h"
#include "villager_memory_entry.h"
#include "villager_mode.h"
#include "villager_mode_record.h"
#include "villager_sickness_record.h"
#include "villager_object.h"
#include "villager_part.h"
#include "villager_house_visit.h"
#include "villager_post.h"
#include "villager_residents.h"
#include "villager_roster.h"
#include "villager_status.h"

static_assert(offsetof(VillagerTown, bonds) == 0x3f60, "bonds");
static_assert(offsetof(VillagerTown, outdoors) == 0x3f7c, "outdoors");
static_assert(offsetof(VillagerTown, sickness) == 0x3f90, "sickness");
static_assert(offsetof(VillagerTown, nickname_date) == 0x404c, "date 0x404c");
static_assert(offsetof(VillagerTown, last_arrival) == 0x4050, "last arrival");
static_assert(offsetof(VillagerTown, last_change) == 0x4058, "last change");
static_assert(offsetof(VillagerTown, newcomer_index) == 0x4075, "newcomer");
static_assert(offsetof(VillagerTown, last_sick) == 0x4076, "last sick");
static_assert(offsetof(VillagerTown, mark) == 0x4078, "mark");
static_assert(offsetof(VillagerTown, last_day) == 0x407a, "last day");
static_assert(sizeof(VillagerTownEvent) == 12, "event");

/* The hour from which the day's events count. */
#define VILLAGER_TOWN_EVENT_HOUR 6
/* The pockets' list of a player's record, and its first free place (-1: full). */
#define VILLAGER_TOWN_POCKETS_FULL (-1)
/* The state func_0207f150 gives a villager that lives in the town as usual. */
#define VILLAGER_TOWN_RESIDENT 3
/* The days after a nickname within which VillagerTown_IsFarFromNicknameDate gives 0: no new
 * nickname is offered. */
#define VILLAGER_TOWN_NICKNAME_DAYS 14
/* The item a villager takes when it takes a design from the shop. */
#define VILLAGER_TOWN_DESIGN_ITEM 0x12a8
/* The mode VillagerModeRecord_LeaveArrived and VillagerMode_Update give for no change
 * (VILLAGER_MODE_UNCHANGED). */
#define VILLAGER_TOWN_MODE_UNCHANGED 12
/* The errand type of the house visit (villager_house_visit.h), and the progress it is set to
 * when it is over (HOUSE_VISITOR_VISIT_OVER of ov068). */
#define VILLAGER_TOWN_HOUSE_VISIT 0x15
#define VILLAGER_TOWN_HOUSE_VISIT_OVER 4
/* The lowest score VillagerTown_ClosestCompanion starts from. */
#define VILLAGER_TOWN_NO_SCORE (-100000)

extern NetSession *data_020ccf94; /* the game's session */
extern u8 data_021dc7bc[];        /* the four players' records (0x249c bytes each) */
extern const u32 data_020cd524[VILLAGER_TOWN_EVENTS];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern unsigned int func_020644cc(int bound); /* a random number below `bound` */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(TownVillager_NpcId((u8 *) villager));
}

static int is_resident(const u8 *villager)
{
    return VillagerStatus_Stay((u8 *) villager) == VILLAGER_TOWN_RESIDENT;
}

/* Bit `index` of a villager mask (index 0-7). */
static u8 bit_of(int index)
{
    return (u8) (1u << index);
}

/* ---- The marked villager */

/* func_0207a44c: bit 6 of the flags of every memory of every villager cleared. */
void VillagerTown_ClearMemoryFlags(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            VillagerEntry_ClearMemoryFlag6(town->villagers[i]);
        }
    }
}
CLEAN_AS(func_0207a44c, VillagerTown_ClearMemoryFlags)

/* func_0207a47c: whether a villager is marked and it is the one `npc` names. */
int VillagerTown_IsMarked(VillagerTown *town, const NpcId *npc)
{
    if ((town->mark & VILLAGER_TOWN_MARKED) == 0) {
        return 0;
    }
    int villager = VillagerRoster_IndexOf(town, npc);
    if (!ActorTable_IsKindESlot((u32) villager)) {
        return 0;
    }
    return ((town->mark & VILLAGER_TOWN_MARK_INDEX) >> VILLAGER_TOWN_MARK_SHIFT) == villager;
}
CLEAN_AS(func_0207a47c, VillagerTown_IsMarked)

/* func_0207a4c0: the villager `npc` names marked, when it is one of the town's. */
void VillagerTown_Mark(VillagerTown *town, const NpcId *npc)
{
    int villager = VillagerRoster_IndexOf(town, npc);
    if (ActorTable_IsKindESlot((u32) villager)) {
        town->mark = (u16) (((town->mark | VILLAGER_TOWN_MARKED) & ~VILLAGER_TOWN_MARK_INDEX) |
                            ((villager & 7) << VILLAGER_TOWN_MARK_SHIFT));
    }
}
CLEAN_AS(func_0207a4c0, VillagerTown_Mark)

/* func_0207a500: no villager marked. */
void VillagerTown_ClearMark(VillagerTown *town)
{
    town->mark &= (u16) ~(VILLAGER_TOWN_MARKED | VILLAGER_TOWN_MARK_INDEX);
}
CLEAN_AS(func_0207a500, VillagerTown_ClearMark)

/* ---- Letters and players */

/* A player id as func_0209527c constructs it (0x20 bytes). */
typedef struct VillagerTownPlayerId {
    u8 bytes[0x20];
} VillagerTownPlayerId;

/* func_0207a51c: a letter handed to the villager it is addressed to. When its sender is a
 * player of the town, that player's record takes note of it first (func_0209a9a8). Then the
 * villager reads it (func_02081144) and keeps it (func_02081418, whose result is given back);
 * 0 when the letter has no sender set or no villager of the town to go to. */
int VillagerTown_GiveLetter(VillagerTown *town, Letter *letter)
{
    if (letter == NULL) {
        return 0;
    }
    void *sender = (void *) (uintptr_t) Letter_PlayerSender(letter);
    if (sender == NULL) {
        return 0;
    }
    VillagerTownPlayerId id;
    int result = 0;
    PlayerId_CopyConstruct((DesignCreator *) &id, sender);
    if (PlayerId_IsSet((DesignCreator *) &id)) {
        void *player = PlayerRecords_Find(data_021dc7bc, (const PlayerRecordsId *) &id);
        void *addressee = Letter_VillagerAddressee(letter);
        if (player != NULL) {
            VillagerPart_NoteLetter((VillagerPart *) (void *) PlayerRecord_VillagerPart(player), letter);
        }
        if (addressee != NULL) {
            NpcId npc;
            NpcId_ConstructCopy(&npc, addressee);
            if (NpcId_IsValid(&npc)) {
                u8 *villager = VillagerRoster_Find(town, &npc);
                if (villager != NULL) {
                    VillagerMail_Reply(villager, player, letter);
                    result = VillagerMail_Receive(villager, letter);
                }
            }
            NpcId_Destruct(&npc);
        }
    }
    PlayerId_Destruct((DesignCreator *) &id);
    return result;
}
CLEAN_AS(func_0207a51c, VillagerTown_GiveLetter)

/* func_0207a5d0: whether every villager of the town knows the player; 0 when the player id is
 * not set. */
int VillagerTown_AllRemember(VillagerTown *town, const void *player)
{
    if (!PlayerId_IsSet((DesignCreator *) player)) {
        return 0;
    }
    u8 *villager = VillagerRoster_At(town, 0);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(villager) && VillagerMemory_Of(villager, player) == NULL) {
            return 0;
        }
        villager += VILLAGER_TOWN_VILLAGER_SIZE;
    }
    return 1;
}
CLEAN_AS(func_0207a5d0, VillagerTown_AllRemember)

/* func_0207a62c: the day of the last nickname (0x404c) set to `date`. */
void VillagerTown_SetNicknameDate(VillagerTown *town, const Date *date)
{
    MI_CpuCopy8(date, &town->nickname_date, sizeof(Date));
    town->nickname_date.extra = 1;
}
CLEAN_AS(func_0207a62c, VillagerTown_SetNicknameDate)

/* func_0207a650: 0 when the last nickname's day (0x404c) is set and `date` is within 13 days of it, either
 * way; otherwise 1. */
int VillagerTown_IsFarFromNicknameDate(VillagerTown *town, const Date *date)
{
    int far = 1;
    if (town->nickname_date.extra != 0) {
        int days;
        if (Calendar_IsOnOrAfter(date, &town->nickname_date)) {
            days = Calendar_DaysFrom(date, &town->nickname_date);
        } else {
            days = Calendar_DaysFrom(&town->nickname_date, date);
        }
        if (days < VILLAGER_TOWN_NICKNAME_DAYS) {
            far = 0;
        }
    }
    return far;
}
CLEAN_AS(func_0207a650, VillagerTown_IsFarFromNicknameDate)

/* func_0207a6a0: the villager that goes out first (the state table's birthday greeter, 0x16c) cleared;
 * then, in scene 6, on the date at 0x2414 of the player's record (read as the player's
 * birthday) from 6:00, when the record has not marked this year (its byte 0x2453), its flag 1 (Nook's job)
 * is clear and its pockets have room: the villager fondest of the player (VillagerTown_FondestOf)
 * goes out first, and the ones out are drawn again. `record` is the current player's when
 * NULL. */
void VillagerTown_PickBirthdayGreeter(VillagerTown *town, void *record)
{
    VillagerState_SetBirthdayGreeter((char) VILLAGER_TOWN_NONE);
    if (SceneQuery_Current() != 6) {
        return;
    }
    if (record == NULL) {
        record = PlayerRecords_Current();
    }
    if (record == NULL) {
        return;
    }
    if (PlayerRecord_TestFlag(record, PLAYER_FLAG_NOOK_JOB) != 0) {
        return;
    }
    if (PlayerPockets_FreeSlot(PlayerRecord_Pockets(record)) == VILLAGER_TOWN_POCKETS_FULL) {
        return;
    }
    u8 *player = (u8 *) PlayerRecord_Player(record);
    const u8 *date = PlayerRecord_Birthday(record);
    if ((date[0] | date[1]) == 0) {
        return;
    }
    if (!PlayerId_IsSet((DesignCreator *) (void *) player)) {
        return;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    if (PlayerRecord_BirthdayYear(record) == now.year) {
        return;
    }
    if (date[1] != now.month || date[0] != now.day || now.hour < VILLAGER_TOWN_EVENT_HOUR) {
        return;
    }
    int villager = VillagerTown_FondestOf(town, player);
    if (ActorTable_IsKindESlot((u32) villager)) {
        VillagerOutdoors_ClearTime(&town->outdoors);
    }
    VillagerState_SetBirthdayGreeter((char) villager);
}
CLEAN_AS(func_0207a6a0, VillagerTown_PickBirthdayGreeter)

/* func_0207a764: a random one of the resident villagers fondest of the player, or -1 (also
 * when the player id is not set). */
int VillagerTown_FondestOf(VillagerTown *town, const void *player)
{
    if (!PlayerId_IsSet((DesignCreator *) player)) {
        return VILLAGER_TOWN_NONE;
    }
    int best = -128;
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (!has_villager(villager) || !is_resident(villager)) {
            continue;
        }
        const u8 *memory = (const u8 *) VillagerMemory_Of((u8 *) villager, player);
        if (memory == NULL) {
            continue;
        }
        int fondness = VillagerMemoryEntry_Fondness((VillagerMemory *) (void *) memory);
        if (fondness == best) {
            candidates |= bit_of(i);
            count++;
        } else if (fondness > best) {
            best = fondness;
            candidates = bit_of(i);
            count = 1;
        }
    }
    return VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207a764, VillagerTown_FondestOf)

/* func_0207a7f8: the visitor of the player's flea market (the state table's 0x164) picked:
 * VillagerTown_PickOutsideAcquaintance. */
void VillagerTown_PickFleaMarketVisitor(VillagerTown *town)
{
    VillagerState_SetFleaMarketVisitor((unsigned char) VillagerTown_PickOutsideAcquaintance(town));
}
CLEAN_AS(func_0207a7f8, VillagerTown_PickFleaMarketVisitor)

/* func_0207a810: a random one of the villagers out walking that know the current player and
 * have not been to the player's flea market today (VILLAGER_MEMORY_FLEA_MARKET_DONE clear); -1
 * for none, or when there is no current player or its id is not set. */
int VillagerTown_PickOutsideAcquaintance(VillagerTown *town)
{
    void *record = PlayerRecords_Current();
    u8 *player = (u8 *) (record != NULL ? PlayerRecord_Player(record) : NULL);
    if (player == NULL || !PlayerId_IsSet((DesignCreator *) (void *) player)) {
        return VILLAGER_TOWN_NONE;
    }
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) && VillagerMemory_Of((u8 *) villager, (const DesignCreator *) (void *) player) != NULL &&
            VillagerMemoryBits_FleaMarketDone(VillagerMemory_Of((u8 *) villager, (const DesignCreator *) (void *) player)) ==
                0 &&
            VillagerState_LinkedPlace(VillagerStatus_StateEntry((u8 *) villager)) == VILLAGER_PLACE_OUTSIDE) {
            candidates |= bit_of(i);
            count++;
        }
    }
    return VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207a810, VillagerTown_PickOutsideAcquaintance)

/* ---- The birthday villager and its companion */

/* func_0207a8ac: every villager whose state is 3 settles; then, when the state table names a
 * birthday villager (index 0x162), that one gets state 0 and its companion (index
 * 0x163), when it is a villager, state 3. When the one at 0x162 is no villager, both indexes
 * are cleared. */
void VillagerTown_ApplyBirthdayStates(VillagerTown *town)
{
    int event_villager = VillagerState_BirthdayVillager();
    int companion = VillagerState_BirthdayCompanion();
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) && VillagerState_LinkedState(VillagerStatus_StateEntry((u8 *) villager)) == 3) {
            VillagerState_SettleState(VillagerStatus_StateEntry((u8 *) villager));
        }
    }
    if (event_villager == VILLAGER_TOWN_NONE) {
        return;
    }
    u8 *villager = VillagerRoster_At(town, event_villager);
    if (villager != NULL && has_villager(villager)) {
        VillagerState_SetState(VillagerStatus_StateEntry(villager), 0);
        villager = VillagerRoster_At(town, companion);
        if (villager != NULL && has_villager(villager)) {
            VillagerState_SetState(VillagerStatus_StateEntry(villager), 3);
        }
    } else {
        VillagerState_SetBirthdayVillager((unsigned char) VILLAGER_TOWN_NONE);
        VillagerState_SetBirthdayCompanion((unsigned char) VILLAGER_TOWN_NONE);
    }
}
CLEAN_AS(func_0207a8ac, VillagerTown_ApplyBirthdayStates)

/* func_0207a964: the state table's indexes 0x162 and 0x163 brought up to date: the villager
 * whose birthday is today (VillagerTown_FindBirthdayVillager) and the one closest to it. A new
 * birthday villager takes a new companion, and when it is the sick one, the
 * sickness record is cleared. For the same one, its companion is kept while func_02080928 accepts it. */
void VillagerTown_UpdateBirthdayVillager(VillagerTown *town)
{
    DateTime now = {0};
    int previous = VillagerState_BirthdayVillager();
    DateTime_Now(&now);
    int event_villager = VillagerTown_FindBirthdayVillager(town, &now);
    if (event_villager == VILLAGER_TOWN_NONE) {
        VillagerState_SetBirthdayVillager((unsigned char) VILLAGER_TOWN_NONE);
        VillagerState_SetBirthdayCompanion((unsigned char) VILLAGER_TOWN_NONE);
    } else if (event_villager == previous) {
        u8 *companion = VillagerRoster_At(town, VillagerState_BirthdayCompanion());
        if (companion != NULL && TownVillager_IsFreeCompanion(companion)) {
            return;
        }
        VillagerState_SetBirthdayCompanion((unsigned char) VillagerTown_ClosestCompanion(town, previous));
    } else {
        int companion = VillagerTown_ClosestCompanion(town, event_villager);
        VillagerState_SetBirthdayVillager((unsigned char) event_villager);
        VillagerState_SetBirthdayCompanion((unsigned char) companion);
        if (event_villager == VillagerSickness_VillagerIndex(town)) {
            VillagerSicknessRecord_Clear(&town->sickness);
        }
    }
}
CLEAN_AS(func_0207a964, VillagerTown_UpdateBirthdayVillager)

/* func_0207aa08: the first resident villager whose birthday is `when`'s date (an event of the
 * calendar whose id is the villager's index); -1 for none, before 6:00, or when there is no current player or its flag 1 is
 * set. */
int VillagerTown_FindBirthdayVillager(const VillagerTown *town, const DateTime *when)
{
    void *record = PlayerRecords_Current();
    if (record == NULL || PlayerRecord_TestFlag(record, PLAYER_FLAG_NOOK_JOB) != 0 || when->hour < VILLAGER_TOWN_EVENT_HOUR) {
        return VILLAGER_TOWN_NONE;
    }
    DateTime copy;
    VillagerTownEvent events[VILLAGER_TOWN_DAY_EVENTS];
    MI_CpuCopy8(when, &copy, sizeof(DateTime));
    int count = EventCalendar_ListAll((EventCalendarEvent *) events, &copy);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (!has_villager(villager) || !is_resident(villager)) {
            continue;
        }
        for (int k = 0; k < count; k++) {
            if (events[k].id == i) {
                return i;
            }
        }
    }
    return VILLAGER_TOWN_NONE;
}
CLEAN_AS(func_0207aa08, VillagerTown_FindBirthdayVillager)

/* func_0207aa8c: a random one of the villagers func_02080928 accepts, other than `villager`,
 * that get on best with it (VillagerBond_Compatibility); -1 for none. */
int VillagerTown_ClosestCompanion(VillagerTown *town, int villager)
{
    int best = VILLAGER_TOWN_NO_SCORE;
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (i == villager || !TownVillager_IsFreeCompanion(town->villagers[i])) {
            continue;
        }
        int score = VillagerBond_Compatibility(town->bonds, villager, i);
        if (score > best) {
            best = score;
            candidates = bit_of(i);
            count = 1;
        } else if (score == best) {
            candidates |= bit_of(i);
            count++;
        }
    }
    return VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
}
CLEAN_AS(func_0207aa8c, VillagerTown_ClosestCompanion)

/* func_0207ab0c: for each resident villager and each player of the town (id set, flag 1
 * clear), the villager's birthday notice: when its birthday is within seven days and the
 * player's byte for the villager (0x2454 + index) is not that birthday's year, the notice is
 * sent (VillagerPost_SendBirthdayNotice) and the year kept; 0xff when no birthday is near. */
void VillagerTown_SendBirthdayNotices(VillagerTown *town)
{
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        const NpcId *npc = TownVillager_NpcId((u8 *) villager);
        if (!NpcId_IsValid(npc) || !is_resident(villager)) {
            continue;
        }
        for (int j = 0; j < 4; j++) {
            void *record = PlayerRecords_TownRecord(data_021dc7bc, j);
            if (record == NULL) {
                continue;
            }
            u8 *player = (u8 *) PlayerRecord_Player(record);
            if (!PlayerId_IsSet((DesignCreator *) (void *) player) ||
                PlayerRecord_TestFlag(record, PLAYER_FLAG_NOOK_JOB) != 0) {
                continue;
            }
            int value = TownVillager_BirthdayYearWithin((u8 *) villager, 7, &now);
            if (value == -1) {
                PlayerRecord_SetBirthdayNoticeYear(record, (u32) i, 0xff);
            } else if (PlayerRecord_BirthdayNoticeYear(record, (u32) i) != value &&
                       VillagerPost_SendBirthdayNotice((const DesignCreator *) (void *) player, npc)) {
                PlayerRecord_SetBirthdayNoticeYear(record, (u32) i, (u8) value);
            }
        }
    }
}
CLEAN_AS(func_0207ab0c, VillagerTown_SendBirthdayNotices)

/* ---- Each villager's state entry */

/* func_0207abd4: the mood and its frames of every villager's state entry cleared. */
void VillagerTown_ClearMoods(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager)) {
            VillagerState_SetMood(VillagerStatus_StateEntry((u8 *) villager), 0);
            VillagerState_SetMoodFrames(VillagerStatus_StateEntry((u8 *) villager), 0);
        }
    }
}
CLEAN_AS(func_0207abd4, VillagerTown_ClearMoods)

/* func_0207ac20: VillagerTown_ScoreRoom for each villager index. */
void VillagerTown_ScoreAllRooms(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        VillagerTown_ScoreRoom(town, i);
    }
}
CLEAN_AS(func_0207ac20, VillagerTown_ScoreAllRooms)

/* The room RoomScore_InitRoom sets up for RoomScore_ScoreVillager (0x14 bytes, no item in its
 * two halfwords). */
typedef struct VillagerTownRoom {
    u8 bytes[0x10];
    u16 item_10;
    u16 item_12;
} VillagerTownRoom;

/* func_0207ac40: for villager `villager`, its state entry's room score and flags set from
 * RoomScore_ScoreVillager (its room scored as the player's would be). */
void VillagerTown_ScoreRoom(VillagerTown *town, int villager)
{
    u8 *found = VillagerRoster_At(town, villager);
    if (found == NULL || !has_villager(found)) {
        return;
    }
    int a = 5;
    int b = 0;
    int c = 0;
    u16 result = 0;
    if (!has_villager(found)) {
        return;
    }
    VillagerState *entry = VillagerStatus_StateEntry(found);
    if (entry == NULL) {
        return;
    }
    VillagerTownRoom search;
    RoomScore_InitRoom((RoomScoreRoom *) &search);
    entry->room_score = RoomScore_ScoreVillager((RoomScoreRoom *) &search, villager, &result, &a, &b, &c);
    entry->room_score_flags = result;
    RoomScore_DestructRoom((RoomScoreRoom *) &search);
}
CLEAN_AS(func_0207ac40, VillagerTown_ScoreRoom)

/* func_0207acbc: unless this system is linked with others, VillagerTown_PickFortuneGiver; and
 * unless it holds its slot of the session, VillagerTown_DoubleByte1E. */
void VillagerTown_UpdateAlone(VillagerTown *town, const void *player)
{
    if (!Session_IsLinked(data_020ccf94)) {
        VillagerTown_PickFortuneGiver(town, player);
    }
    if (!Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        VillagerTown_DoubleByte1E(town);
    }
}
CLEAN_AS(func_0207acbc, VillagerTown_UpdateAlone)

/* func_0207acf8: today's fortune giver picked: one villager's memory of the player is marked
 * (VILLAGER_MEMORY_FORTUNE_DUE), so that its next greeting hands the player a lucky item; a
 * random one of the villagers out walking that know the player, else of the resident villagers
 * that know it, other than the sick one. Nothing when the player id is not set. */
void VillagerTown_PickFortuneGiver(VillagerTown *town, const void *player)
{
    if (!PlayerId_IsSet((DesignCreator *) player)) {
        return;
    }
    u8 candidates = 0;
    int count = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) &&
            VillagerState_LinkedPlace(VillagerStatus_StateEntry((u8 *) villager)) == VILLAGER_PLACE_OUTSIDE &&
            VillagerMemory_Of((u8 *) villager, player) != NULL) {
            candidates |= bit_of(i);
            count++;
        }
    }
    int chosen = VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
    if (!ActorTable_IsKindESlot((u32) chosen)) {
        candidates = 0;
        count = 0;
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            const u8 *villager = town->villagers[i];
            if (has_villager(villager) && is_resident(villager) && i != VillagerSickness_VillagerIndex(town) &&
                VillagerMemory_Of((u8 *) villager, player) != NULL) {
                candidates |= bit_of(i);
                count++;
            }
        }
        chosen = VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
    }
    u8 *villager = VillagerRoster_At(town, chosen);
    if (villager != NULL && has_villager(villager)) {
        u8 *memory = (u8 *) VillagerMemory_Of(villager, player);
        if (memory != NULL) {
            VillagerMemoryBits_SetFortuneDue((VillagerMemory *) (void *) memory);
        }
    }
}
CLEAN_AS(func_0207acf8, VillagerTown_PickFortuneGiver)

/* func_0207adf4: unless this system holds its slot of the session, byte 0x1e of every
 * villager's state entry halved. */
void VillagerTown_HalveByte1E(VillagerTown *town)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            VillagerEntry_HalveByte1E(town->villagers[i]);
        }
    }
}
CLEAN_AS(func_0207adf4, VillagerTown_HalveByte1E)

/* func_0207ae34: unless this system holds its slot of the session, byte 0x1e of every
 * villager's state entry doubled (up to 32). */
void VillagerTown_DoubleByte1E(VillagerTown *town)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            VillagerEntry_DoubleByte1E(town->villagers[i]);
        }
    }
}
CLEAN_AS(func_0207ae34, VillagerTown_DoubleByte1E)

/* func_0207ae74: byte 0x1e of every villager's state entry set from its fondness of the player
 * of `record` (func_0207d2b4). */
void VillagerTown_SetByte1E(VillagerTown *town, void *record)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            VillagerEntry_SetByte1E(town->villagers[i], record);
        }
    }
}
CLEAN_AS(func_0207ae74, VillagerTown_SetByte1E)

/* ---- The calendar's events */

/* func_0207aeac: the place in data_020cd524 of the first of its events found on the days from
 * `from` (the clock's date and time when NULL) to `days` days after it, looking day by day and
 * within a day at the events in their order; 11 for none. */
int VillagerTown_NextEvent(unsigned int days, const DateTime *from)
{
    DateTime day = {0};
    if (from == NULL) {
        DateTime_Now(&day);
    } else {
        MI_CpuCopy8(from, &day, sizeof(DateTime));
    }
    for (unsigned int n = 0; n <= days; n++) {
        DateTime copy;
        VillagerTownEvent events[VILLAGER_TOWN_DAY_EVENTS];
        MI_CpuCopy8(&day, &copy, sizeof(DateTime));
        int count = EventCalendar_ListAll((EventCalendarEvent *) events, &copy);
        for (int i = 0; i < count; i++) {
            for (int k = 0; k < VILLAGER_TOWN_EVENTS; k++) {
                if (events[i].id == data_020cd524[k]) {
                    return k;
                }
            }
        }
        DateTime_AddDays(&day, 1);
    }
    return VILLAGER_TOWN_EVENTS;
}
CLEAN_AS(func_0207aeac, VillagerTown_NextEvent)

/* func_0207af30: the place in data_020cd524 of the first of its events that is on now and is
 * the event going on (func_02041608); 11 for none. */
int VillagerTown_CurrentEvent(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < VILLAGER_TOWN_EVENTS; i++) {
        u32 event = data_020cd524[i];
        DateTime copy;
        MI_CpuCopy8(&now, &copy, sizeof(DateTime));
        if (EventCalendar_State(event, &copy, 0) != 0 && event == EventAnnounce_CurrentEvent()) {
            return i;
        }
    }
    return VILLAGER_TOWN_EVENTS;
}
CLEAN_AS(func_0207af30, VillagerTown_CurrentEvent)

/* func_0207af90: the villager that tells today's password for the fox's shop (the state
 * table's byte 0x161, villager_talk_greeting.c) set to a random one of the villagers out
 * walking, else of the resident villagers other than the sick one; 0 for
 * none. */
void VillagerTown_PickFoxPasswordVillager(VillagerTown *town)
{
    u8 candidates = 0;
    int count = 0;
    u8 chosen = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        const u8 *villager = town->villagers[i];
        if (has_villager(villager) &&
            VillagerState_LinkedPlace(VillagerStatus_StateEntry((u8 *) villager)) == VILLAGER_PLACE_OUTSIDE) {
            candidates |= bit_of(i);
            count++;
        }
    }
    int pick = VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
    if (pick != VILLAGER_TOWN_NONE) {
        chosen = (u8) pick;
    } else {
        candidates = 0;
        count = 0;
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            const u8 *villager = town->villagers[i];
            if (has_villager(villager) && is_resident(villager) && i != VillagerSickness_VillagerIndex(town)) {
                candidates |= bit_of(i);
                count++;
            }
        }
        pick = VillagerRoster_PickBit(candidates, count, VILLAGER_TOWN_VILLAGERS);
        if (pick != VILLAGER_TOWN_NONE) {
            chosen = (u8) pick;
        }
    }
    VillagerState_Table()->fox_password_villager = chosen;
}
CLEAN_AS(func_0207af90, VillagerTown_PickFoxPasswordVillager)

/* ---- The updates */

/* func_0207b41c: each villager's own update. Unless `skip_designs`, a villager that takes a
 * design from the shop (Design_VillagerTakeShopDesign) gets item 0x12a8 in its halfword 0x7d2.
 * Then func_0207d71c; when the object of the villager's record holds something with the low
 * bits of its byte 0x0b clear, the player id after it (at 12) is emptied; then func_0207f454. */
void VillagerTown_UpdateVillagers(VillagerTown *town, int skip_designs)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        if (skip_designs == 0 && Design_VillagerTakeShopDesign(i, 0) != 0) {
            u16 item = VILLAGER_TOWN_DESIGN_ITEM;
            TownVillager_SetClothes(villager, &item);
        }
        VillagerMode_FinishObject(villager);
        u8 *object = (u8 *) (VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
        u8 *held = VillagerObject_Errand((VillagerObject *) (void *) object);
        if (VillagerErrand_IsInUse((VillagerErrand *) (void *) held) &&
            VillagerErrand_Progress((VillagerErrand *) (void *) held) == 0) {
            PlayerId_Clear(VillagerObject_Player((VillagerObject *) (void *) object));
        }
        VillagerFurniture_StoreItems(villager);
    }
}
CLEAN_AS(func_0207b41c, VillagerTown_UpdateVillagers)

/* func_0207b4a8: for each player of the town whose id is set, its house visit
 * (villager_house_visit.h): the object at 0xb4 of its record's part at 0x1e40 (with the NpcId
 * at 0xa4 before it), when it holds type 0x15 for a valid NpcId:
 *   - with the low bits of its byte 0x0b clear: emptied (func_0209af04) when `now` is a day
 *     before its date (its bytes 3-5);
 *   - else, with no kind in the low three bits of byte 0xc8: emptied;
 *   - else: the low bits of byte 0x0b set to 4, and when the date at 0xc0 is not `now`'s day,
 *     emptied when func_02059e1c agrees.
 * `town` is not used. */
void VillagerTown_ExpireHouseVisits(VillagerTown *town, const DateTime *now)
{
    (void) town;
    for (int i = 0; i < 4; i++) {
        void *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (!PlayerId_IsSet(PlayerRecord_Player(record))) {
            continue;
        }
        u8 *part = PlayerRecord_VillagerPart(record) + 0xa4;
        u8 *object = part + 0x10;
        if (!VillagerErrand_IsInUse((VillagerErrand *) (void *) object) ||
            VillagerErrand_Type((VillagerErrand *) (void *) object) != VILLAGER_TOWN_HOUSE_VISIT ||
            !NpcId_IsValid((const NpcId *) part)) {
            continue;
        }
        if (VillagerErrand_Progress((VillagerErrand *) (void *) object) == 0) {
            if (DateTime_DaysBetween(VillagerErrand_Date((VillagerErrand *) (void *) object), now) < 0) {
                VillagerHouseVisit_Clear((VillagerHouseVisit *) (void *) part);
            }
        } else if ((part[0x24] & 7) != 0) {
            int days = DateTime_DaysBetween((const DateTime *) (void *) (part + 0x1c), now);
            VillagerErrand_SetProgress((VillagerErrand *) (void *) object, VILLAGER_TOWN_HOUSE_VISIT_OVER);
            if (days != 0 &&
                VillagerPost_SendQ10Reply(part[0x24] & 7, PlayerRecord_Player(record), (const NpcId *) (void *) part) != 0) {
                VillagerHouseVisit_Clear((VillagerHouseVisit *) (void *) part);
            }
        } else {
            VillagerHouseVisit_Clear((VillagerHouseVisit *) (void *) part);
        }
    }
}
CLEAN_AS(func_0207b4a8, VillagerTown_ExpireHouseVisits)

/* func_0207b9d0: the state table's entry for villager index `index`, or NULL outside 0-7. */
VillagerState *VillagerTown_StateAt(int index)
{
    return VillagerState_At(VillagerState_Table(), index);
}
CLEAN_AS(func_0207b9d0, VillagerTown_StateAt)

/* func_0207bd80: on a new day (the date differs from the one at 0x407a), func_0207f5e4 for each
 * of the eight villager places, and the date kept. */
void VillagerTown_StartDay(VillagerTown *town)
{
    DateTime last;
    DateTime_Set(&last, &town->last_day, 0, 0, 0);
    DateTime now = {0};
    DateTime_Now(&now);
    if (DateTime_Compare(&now, &last, DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY) != 0) {
        for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
            VillagerHouseItems_GiveAwayOne(town->villagers[i]);
        }
        Calendar_Today(&town->last_day);
    }
}
CLEAN_AS(func_0207bd80, VillagerTown_StartDay)

static int is_set(const DateTime *when)
{
    const u8 *bytes = (const u8 *) when;
    for (size_t i = 0; i < sizeof(DateTime); i++) {
        if (bytes[i] != 0) {
            return 1;
        }
    }
    return 0;
}

/* func_0207bddc: the town's villagers brought up to date. When the clock is earlier than the
 * last arrival, that time is moved back to it, and the last departure too when it is set.
 * Then each part in turn; the players' bytes for the villagers only without `skip_designs`. */
void VillagerTown_Update(VillagerTown *town, int skip_designs)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (DateTime_Compare(&now, &town->last_arrival,
                         DATE_TIME_YEAR | DATE_TIME_MONTH | DATE_TIME_DAY | DATE_TIME_HOUR | DATE_TIME_MINUTE |
                             DATE_TIME_SECOND) == -1) {
        MI_CpuCopy8(&now, &town->last_arrival, sizeof(DateTime));
        if (is_set(&town->last_change)) {
            MI_CpuCopy8(&now, &town->last_change, sizeof(DateTime));
        }
    }
    VillagerTown_ExpireHouseVisits(town, &now);
    VillagerTown_UpdateModes(town, &now);
    VillagerResidents_Exchange(town, &now);
    VillagerTown_StartLeaving(town, &now);
    VillagerResidents_MoveInNew(town, &now);
    VillagerTown_StartDay(town);
    VillagerTown_UpdateVillagers(town, skip_designs);
    VillagerSickness_Update(town);
    if (skip_designs == 0) {
        VillagerTown_SendBirthdayNotices(town);
    }
    VillagerTown_UpdateBirthdayVillager(town);
}
CLEAN_AS(func_0207bddc, VillagerTown_Update)

/* func_0207be8c: unless this system holds its slot of the session, func_0207d840 for every
 * villager with the clock's date and time. */
void VillagerTown_UpdateWithClock(VillagerTown *town)
{
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (has_villager(town->villagers[i])) {
            VillagerMode_UpdateDaily(town->villagers[i], &now);
        }
    }
}
CLEAN_AS(func_0207be8c, VillagerTown_UpdateWithClock)

/* func_0207bee0: for every villager, its mode record's arrival settled with no date
 * (VillagerModeRecord_LeaveArrived); for a mode other than 12 (unchanged), its furniture reset
 * for that mode (VillagerFurniture_ResetForMode) with whether the record was from mode 2 (read
 * before the settling). */
void VillagerTown_SettleArrivals(VillagerTown *town)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        u8 *object = (u8 *) (VillagerObject_RecordMode((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
        int flag = VillagerModeRecord_IsFrom2((VillagerModeRecord *) (void *) object);
        int result = VillagerModeRecord_LeaveArrived((VillagerModeRecord *) (void *) object, NULL);
        if (result != VILLAGER_TOWN_MODE_UNCHANGED) {
            VillagerFurniture_ResetForMode(villager, result, flag);
        }
    }
}
CLEAN_AS(func_0207bee0, VillagerTown_SettleArrivals)

/* func_0207bf38: for every villager, its mode's dates kept (VillagerMode_KeepSinceDate,
 * _KeepCountedDate) and its mode updated with the time; when the mode changed (not 12), the
 * object of its record is cleared (VillagerObject_Clear). */
void VillagerTown_UpdateModes(VillagerTown *town, const DateTime *now)
{
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        VillagerMode_KeepSinceDate(villager, now);
        VillagerMode_KeepCountedDate(villager, now);
        if (VillagerMode_Update(villager, &town->last_arrival, &town->last_change, now) != VILLAGER_TOWN_MODE_UNCHANGED) {
            VillagerObject_Clear(VillagerObject_OfRecord((VillagerRecord *) VillagerStatus_ModeRecord(villager)));
        }
    }
}
CLEAN_AS(func_0207bf38, VillagerTown_UpdateModes)

/* func_0207bfa4: when a villager is due to leave (VillagerResidents_IsLeaveDue), the one
 * VillagerResidents_PickLeaver picks, if any, starts leaving (mode 9, VillagerMode_SetLeaving). */
void VillagerTown_StartLeaving(VillagerTown *town, const DateTime *now)
{
    if (VillagerResidents_IsLeaveDue(town, now) == 0) {
        return;
    }
    int villager = VillagerResidents_PickLeaver(town);
    if (villager != VILLAGER_TOWN_NONE) {
        VillagerMode_SetLeaving(town->villagers[villager], now);
    }
}
CLEAN_AS(func_0207bfa4, VillagerTown_StartLeaving)
