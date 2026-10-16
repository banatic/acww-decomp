/* Where one of the town's villagers stands (villager_status.h). */
#include "villager_status.h"

#include <string.h>

#include "clean.h"
#include "npc_id.h"
#include "player_record.h"
#include "player_records.h"
#include "session.h"
#include "villager_roster.h"
#include "villager_town.h"

#define VILLAGER_STATUS_MODE_RECORD 0x734
#define VILLAGER_STATUS_CAME 0x7d6
/* The byte of a villager's data that holds its song. */
#define VILLAGER_STATUS_SONG 0x4d
/* Where a player's part (PlayerRecord_VillagerPart) keeps an NpcId with an object. */
#define VILLAGER_STATUS_PART_A4 0xa4

extern u8 data_021e5a2c[];        /* the town's villagers (VillagerTown) */
extern NetSession *data_020ccf94; /* the session */

extern NpcId *func_0208150c(const void *villager);               /* the villager's NpcId, at 0x7a0 */
extern void *func_0209b5ec(void *record);                        /* the record itself */
extern int func_0209c330(const VillagerModeRecord *record);      /* its mode, byte 0x10 */
extern unsigned func_0209c304(const VillagerModeRecord *record); /* the group of its mode (0 for 0-4) */
/* Loads the text of a mode (7 for one that is not a kind 0-7) into the label. */
extern int func_0209bff0(void *label, int mode);
extern u8 *func_0209ad9c(u8 *part, int index);     /* its index-th block of 48 bytes; NULL past 1 */
extern u8 *func_0209b4d4(u8 *block);               /* the block's object, the block itself */
extern int func_0209bd44(u8 *object);              /* whether it holds something */
extern NpcId *func_0209b4cc(u8 *block, int index); /* its index-th NpcId (block + 12 + 16 index) */
/* Whether the part's NpcId at 0x70 is in use (func_0209ac04) and is `npc`. */
extern int func_0209a854(u8 *part, const NpcId *npc);
extern int func_0209aebc(u8 *part, const NpcId *npc); /* whether it holds an object for the villager */
/* The villager's data (data_020cd884), NULL past 149. */
extern const u8 *func_02082500(int number);

static VillagerTown *VillagerStatus_Town(void)
{
    return (VillagerTown *) (void *) data_021e5a2c;
}

/* The same villager: the first halfword, the 12 bytes after it and the number agree (the
 * personality is not compared). */
static int VillagerStatus_SameNpc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* The mode of the villager's record, for a villager with a valid NpcId; -1 without one. */
static int VillagerStatus_Mode(u8 *villager)
{
    if (!NpcId_IsValid(func_0208150c(villager))) {
        return -1;
    }
    return func_0209c330(func_0209b5ec(VillagerStatus_ModeRecord(villager)));
}

/* func_0207ef3c */
void VillagerStatus_SetCame(u8 *villager, u8 came)
{
    villager[VILLAGER_STATUS_CAME] = came;
}
CLEAN_AS(func_0207ef3c, VillagerStatus_SetCame)

/* func_0207ef48 */
u8 VillagerStatus_Came(u8 *villager)
{
    return villager[VILLAGER_STATUS_CAME];
}
CLEAN_AS(func_0207ef48, VillagerStatus_Came)

/* Whether one of the two NpcIds of `block` is `npc`, when the block's object holds something. */
static int VillagerStatus_BlockNames(u8 *block, const NpcId *npc)
{
    if (!func_0209bd44(func_0209b4d4(block))) {
        return 0;
    }
    return VillagerStatus_SameNpc(func_0209b4cc(block, 0), npc) || VillagerStatus_SameNpc(func_0209b4cc(block, 1), npc);
}

/* func_0207ef54: whether the part of a player's record (PlayerRecord_VillagerPart) holds the
 * villager: in one of its two blocks, in its NpcId at 0x70 (func_0209a854), or with an object
 * at 0xa4 (func_0209aebc). 0 for a villager whose NpcId is not valid. */
int VillagerStatus_PlayerHolds(u8 *villager, u8 *part)
{
    const NpcId *npc = func_0208150c(villager);
    if (!NpcId_IsValid(npc)) {
        return 0;
    }
    u8 *first = func_0209ad9c(part, 0);
    u8 *second = func_0209ad9c(part, 1);
    return VillagerStatus_BlockNames(first, npc) || VillagerStatus_BlockNames(second, npc) || func_0209a854(part, npc) ||
           func_0209aebc(part + VILLAGER_STATUS_PART_A4, npc);
}
CLEAN_AS(func_0207ef54, VillagerStatus_PlayerHolds)

/* func_0207f074: whether the villager can be picked: it has a valid NpcId, stays as a resident,
 * is not away (status 2) and the current player's record does not hold it.
 * REQUIRES: there is a current player's record (its part is looked up first). */
int VillagerStatus_IsFree(u8 *villager)
{
    u8 *part = PlayerRecord_VillagerPart(PlayerRecords_Current());
    return NpcId_IsValid(func_0208150c(villager)) && VillagerStatus_Stay(villager) == VILLAGER_STAY_RESIDENT &&
           VillagerStatus_Get(villager) != VILLAGER_STATUS_AWAY && !VillagerStatus_PlayerHolds(villager, part);
}
CLEAN_AS(func_0207f074, VillagerStatus_IsFree)

/* func_0207f0c0: the villager has a valid NpcId and its record is in mode 11. */
int VillagerStatus_IsMode11(u8 *villager)
{
    return VillagerStatus_Mode(villager) == VILLAGER_MODE_11;
}
CLEAN_AS(func_0207f0c0, VillagerStatus_IsMode11)

/* func_0207f0f0: the villager has a valid NpcId and has just moved in (mode 10). */
int VillagerStatus_IsArrived(u8 *villager)
{
    return VillagerStatus_Mode(villager) == VILLAGER_MODE_ARRIVED;
}
CLEAN_AS(func_0207f0f0, VillagerStatus_IsArrived)

/* func_0207f120: the villager has a valid NpcId and is about to leave (mode 9). */
int VillagerStatus_IsLeaving(u8 *villager)
{
    return VillagerStatus_Mode(villager) == VILLAGER_MODE_LEAVING;
}
CLEAN_AS(func_0207f120, VillagerStatus_IsLeaving)

/* func_0207f150: VILLAGER_STAY_*, from the tests above in turn. */
int VillagerStatus_Stay(u8 *villager)
{
    if (VillagerStatus_IsLeaving(villager)) {
        return VILLAGER_STAY_LEAVING;
    }
    if (VillagerStatus_IsArrived(villager)) {
        return VILLAGER_STAY_ARRIVED;
    }
    if (VillagerStatus_IsMode11(villager)) {
        return VILLAGER_STAY_MODE_11;
    }
    return VILLAGER_STAY_RESIDENT;
}
CLEAN_AS(func_0207f150, VillagerStatus_Stay)

/* func_0207f184: the text of the villager's mode loaded into `label`: the mode itself for one
 * of groups 0 and 1, else text 7. */
int VillagerStatus_LoadModeText(u8 *villager, void *label)
{
    VillagerModeRecord *record = (VillagerModeRecord *) (villager + VILLAGER_STATUS_MODE_RECORD);
    if (func_0209c304(func_0209b5ec(record)) <= 1) {
        return func_0209bff0(label, func_0209c330(func_0209b5ec(record)));
    }
    return func_0209bff0(label, VILLAGER_STATUS_MODE_TEXT_OTHER);
}
CLEAN_AS(func_0207f184, VillagerStatus_LoadModeText)

/* func_0207f1c8 */
VillagerModeRecord *VillagerStatus_ModeRecord(u8 *villager)
{
    return (VillagerModeRecord *) (villager + VILLAGER_STATUS_MODE_RECORD);
}
CLEAN_AS(func_0207f1c8, VillagerStatus_ModeRecord)

/* func_0207f1d4: there is such a villager (always). */
int VillagerStatus_Exists(void *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_0207f1d4, VillagerStatus_Exists)

/* 1, or 2 when the entry's byte 0x01 is 2. */
static int VillagerStatus_HomeOrAway(const VillagerState *entry)
{
    return VillagerState_LinkedByte01(entry) == 2 ? VILLAGER_STATUS_AWAY : VILLAGER_STATUS_HOME;
}

/* func_0207f1d8: the villager's status (VILLAGER_STATUS_*, 0-7). */
int VillagerStatus_Get(u8 *villager)
{
    if (!NpcId_IsValid(func_0208150c(villager))) {
        return VILLAGER_STATUS_NONE;
    }
    VillagerState *entry = VillagerStatus_StateEntry(villager);
    if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return VillagerStatus_HomeOrAway(entry);
    }
    int state = VillagerState_LinkedState(entry);
    if (state == 0) {
        return VillagerStatus_HomeOrAway(entry);
    }
    if (state >= 2 && state <= 6) {
        return VILLAGER_STATUS_STATE_2 + (state - 2);
    }
    return VILLAGER_STATUS_NONE;
}
CLEAN_AS(func_0207f1d8, VillagerStatus_Get)

/* func_0207f270: the villager's entry of the state table, by its place in the town. */
VillagerState *VillagerStatus_StateEntry(u8 *villager)
{
    VillagerStates *table = VillagerState_Table();
    return VillagerState_At(table, VillagerStatus_FindIndex(villager));
}
CLEAN_AS(func_0207f270, VillagerStatus_StateEntry)

/* func_0207f294: the villager's place in the town (0-7), or -1. */
int VillagerStatus_Index(u8 *villager)
{
    return VillagerStatus_FindIndex(villager);
}
CLEAN_AS(func_0207f294, VillagerStatus_Index)

/* func_0207f29c: the place in the town of the villager with the same NpcId, or -1.
 * QUIRK: the original first tests the town's address for null, which it never is. */
int VillagerStatus_FindIndex(u8 *villager)
{
    return VillagerRoster_IndexOf(VillagerStatus_Town(), func_0208150c(villager));
}
CLEAN_AS(func_0207f29c, VillagerStatus_FindIndex)

/* func_0207f2c4: the villager's song (byte 0x4d of its data), 0 for a number without data. */
int VillagerStatus_Song(u8 *villager)
{
    const u8 *data = func_02082500(NpcId_Number(func_0208150c(villager)));
    return data != NULL ? data[VILLAGER_STATUS_SONG] : 0;
}
CLEAN_AS(func_0207f2c4, VillagerStatus_Song)
