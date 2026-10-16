/* The kind each villager is given (villager_kinds.h). */
#include "villager_kinds.h"

#include <string.h>

#include "clean.h"
#include "session.h"
#include "villager_town.h"

/* The types of object a player's record holds itself (part 0x1e40), whose group 1 places are
 * not dealt. */
#define VILLAGER_KIND_RECORD_TYPES 13
/* The item of the object dealt: none. */
#define VILLAGER_KIND_NO_ITEM 0xfff1

extern NetSession *data_020ccf94;                     /* the game's session */
extern u8 data_021d12b4[VILLAGER_KIND_GROUP_1_COUNT]; /* which group 1 places are taken */
extern u8 data_021d1248[VILLAGER_TOWN_VILLAGERS];     /* which villagers have been dealt with */
extern const u8 data_020cd454[VILLAGER_KIND_RECORD_TYPES];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern NpcId *func_0208150c(const void *villager);         /* the villager's NpcId, at 0x7a0 */
extern int func_0207f150(const void *villager);            /* 0-3, from three tests of the villager */
extern VillagerState *func_0207f270(const void *villager); /* its entry of the state table */
extern u8 *func_0207f1c8(const void *villager);            /* the villager's record, at 0x734 */
extern int func_0207cad4(const VillagerTown *town);        /* how many villagers it has */
extern unsigned int func_020644cc(int bound);              /* a random number below `bound` */
extern void *func_020984e8(void);                          /* the current player's record, or NULL */
extern u8 *func_02099640(void *record);                    /* the record's part at 0x1e40 */
extern u8 *func_0209ad9c(u8 *part, int index);             /* its index-th block of 48 bytes; NULL past 1 */
extern u8 *func_0209b4d4(u8 *block);                       /* the block's object, the block itself */
extern NpcId *func_0209b4cc(u8 *block, int index);         /* its index-th NpcId (block + 12 + 16 index) */
extern int func_0209aebc(u8 *part, const NpcId *npc);      /* whether it holds an object for the villager */
extern u8 *func_0209a778(VillagerMove *move);              /* the plan's object */
extern NpcId *func_0209a774(VillagerMove *move);           /* the plan's NpcId */
extern u8 *func_0209b5e8(u8 *record);                      /* record + 0x24: the villager's object */
extern u8 *func_0209b5ec(u8 *object);                      /* the object itself */
extern u8 *func_0209b91c(u8 *object);                      /* the object itself */
extern int func_0209bd44(const u8 *object);                /* whether it holds something (type below 22) */
extern int func_0209bc40(const u8 *object);                /* its type, byte 0x0a */
extern int func_0209bd10(u32 type);                        /* its group: 0, 1, or 2 for none */
extern int func_0209bcd4(int *place, int type);            /* its place in group 0 or 1, else 0 */
extern int func_0209c380(const u8 *object);                /* whether its byte 0x10 is below 8 */
extern int func_0209c304(const u8 *object);                /* the group of its byte 0x10 (0 for 0-4) */
extern u8 func_0209c330(const u8 *object);                 /* its byte 0x10 */
extern void func_0209bd30(u8 *object, u8 type, const u16 *item, u8 low_bits);
extern void func_0209bd5c(u8 *object); /* type 22, no item */

static int has_villager(const u8 *villager)
{
    return NpcId_IsValid(func_0208150c(villager));
}

static int same_npc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* func_0207b57c: VillagerKind_Deal when VillagerKind_IsDealNeeded. */
void VillagerKind_DealIfNeeded(VillagerTown *town)
{
    if (VillagerKind_IsDealNeeded(town)) {
        VillagerKind_Deal(town);
    }
}
CLEAN_AS(func_0207b57c, VillagerKind_DealIfNeeded)

/* func_0207b594: types dealt to the villagers, each group 1 type to one villager at most.
 * Taken first are the group 1 places of the 13 types of data_020cd454, and of each resident
 * villager (other than the one planning to move away) that already has a group 1 type
 * (VillagerKind_Of with the current player). An empty place, a villager that is not resident
 * and the one planning to move are left out. A villager whose record's object has a group 0
 * value in its byte 0x10 (below 5) gets that as its type. Then, while villagers and group 1
 * types are left, a random villager left gets a random type left. Nothing without a current
 * player.
 * REQUIRES: the places func_0209bcd4 gives are 0-16, as they are for the types of group 1. */
void VillagerKind_Deal(VillagerTown *town)
{
    void *record = func_020984e8();
    int types_left = VILLAGER_KIND_GROUP_1_COUNT;
    int villagers_left = VILLAGER_TOWN_VILLAGERS;
    if (record == NULL) {
        return;
    }
    int place = 0;
    int moving = VillagerMove_VillagerIndex(town);
    MI_CpuFill8(data_021d12b4, 0, (u32) types_left);
    MI_CpuFill8(data_021d1248, 0, (u32) villagers_left);

    for (int i = 0; i < VILLAGER_KIND_RECORD_TYPES; i++) {
        if (func_0209bcd4(&place, data_020cd454[i])) {
            data_021d12b4[place] = 1;
            types_left--;
        }
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager) || func_0207f150(villager) != 3 || i == moving) {
            data_021d1248[i] = 1;
            villagers_left--;
            continue;
        }
        int type = VillagerKind_Of(town, villager, record);
        if ((unsigned int) type >= VILLAGER_KIND_NONE || func_0209bd10((u32) type) != VILLAGER_KIND_GROUP_1 ||
            !func_0209bcd4(&place, type)) {
            continue;
        }
        data_021d1248[i] = 1;
        villagers_left--;
        data_021d12b4[place] = 1;
        types_left--;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (data_021d1248[i] != 0) {
            continue;
        }
        const u8 *villager = town->villagers[i];
        const u8 *own = func_0209b5ec(func_0207f1c8(villager));
        if (!func_0209c380(own) || func_0209c304(own) != 0) {
            continue;
        }
        u8 *object = VillagerState_Object(func_0207f270(villager));
        u16 item = VILLAGER_KIND_NO_ITEM;
        func_0209bd30(object, func_0209c330(own), &item, 0);
        data_021d1248[i] = 1;
        villagers_left--;
    }
    while (villagers_left > 0 && types_left > 0) {
        int nth_villager = (int) func_020644cc(villagers_left);
        for (int j = 0; j < VILLAGER_TOWN_VILLAGERS; j++) {
            if (data_021d1248[j] != 0) {
                continue;
            }
            if (nth_villager != 0) {
                nth_villager--;
                continue;
            }
            u8 *object = VillagerState_Object(func_0207f270(town->villagers[j]));
            int nth_type = (int) func_020644cc(types_left);
            for (int k = 0; k < VILLAGER_KIND_GROUP_1_COUNT; k++) {
                if (data_021d12b4[k] != 0) {
                    continue;
                }
                if (nth_type == 0) {
                    u16 item = VILLAGER_KIND_NO_ITEM;
                    func_0209bd30(object, (u8) (k + VILLAGER_KIND_GROUP_1_FIRST), &item, 0);
                    data_021d12b4[k] = 1;
                    types_left--;
                    break;
                }
                nth_type--;
            }
            data_021d1248[j] = 1;
            villagers_left--;
            break;
        }
    }
}
CLEAN_AS(func_0207b594, VillagerKind_Deal)

/* func_0207b764: every entry of the state table back to no type. */
void VillagerKind_ClearAll(void)
{
    VillagerState *entry = VillagerState_Table()->entries;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        func_0209bd5c(VillagerState_Object(entry));
        entry++;
    }
}
CLEAN_AS(func_0207b764, VillagerKind_ClearAll)

/* func_0207b78c: whether the types need dealing: never while this system is linked with
 * others; else when the villagers with no type outnumber half of the villagers less those with
 * a type outside group 1. */
int VillagerKind_IsDealNeeded(VillagerTown *town)
{
    if (Session_IsLinked(data_020ccf94)) {
        return 0;
    }
    int villagers = func_0207cad4(town);
    int without = 0;
    int other_group = 0;
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        u8 *villager = town->villagers[i];
        if (!has_villager(villager)) {
            continue;
        }
        int type = VillagerKind_Of(town, villager, NULL);
        if (type == VILLAGER_KIND_NONE) {
            without++;
        } else if (func_0209bd10((u32) type) != VILLAGER_KIND_GROUP_1) {
            other_group++;
        }
    }
    if (villagers < other_group) {
        return 0;
    }
    return (villagers - other_group) / 2 < without;
}
CLEAN_AS(func_0207b78c, VillagerKind_IsDealNeeded)

/* func_0207b810: the villager's type: VillagerKind_Known when that finds one, else the type
 * of its state entry's object when it holds one; 22 for none, also without a state entry or
 * a player's record (the current player's when `record` is NULL). */
int VillagerKind_Of(VillagerTown *town, u8 *villager, void *record)
{
    VillagerState *entry = func_0207f270(villager);
    int type = VILLAGER_KIND_NONE;
    if (record == NULL) {
        record = func_020984e8();
    }
    if (entry != NULL && record != NULL) {
        unsigned int known = (unsigned int) VillagerKind_Known(town, villager, record);
        if (known < VILLAGER_KIND_NONE) {
            type = (int) known;
        } else if (func_0209bd44(VillagerState_Object(entry))) {
            type = func_0209bc40(VillagerState_Object(entry));
        }
    }
    return type;
}
CLEAN_AS(func_0207b810, VillagerKind_Of)

/* func_0207b86c: the type of the object something holds for the villager, looked for in turn
 * in: the two blocks of the player's record part (when their first NpcId is the villager's),
 * the plan to move away (when it names the villager), the object at 0xb4 of the part
 * (func_0209aebc) and the object of the villager's own record; 22 for none, or without a
 * player's record (the current player's when `record` is NULL). */
int VillagerKind_Known(VillagerTown *town, u8 *villager, void *record)
{
    const NpcId *npc = func_0208150c(villager);
    if (record == NULL) {
        record = func_020984e8();
    }
    if (record == NULL) {
        return VILLAGER_KIND_NONE;
    }
    u8 *part = func_02099640(record);
    u8 *blocks[2];
    blocks[0] = func_0209ad9c(part, 0);
    blocks[1] = func_0209ad9c(part, 1);
    part += 0xa4;

    for (int i = 0; i < 2; i++) {
        if (func_0209bd44(func_0209b4d4(blocks[i])) && same_npc(func_0209b4cc(blocks[i], 0), npc)) {
            return func_0209bc40(func_0209b4d4(blocks[i]));
        }
    }
    if (func_0209bd44(func_0209a778(&town->move)) && same_npc(func_0209a774(&town->move), npc)) {
        return func_0209bc40(func_0209a778(&town->move));
    }
    if (func_0209aebc(part, npc)) {
        return func_0209bc40(part + 0x10);
    }
    if (func_0209bd44(func_0209b91c(func_0209b5e8(func_0207f1c8(villager))))) {
        return func_0209bc40(func_0209b91c(func_0209b5e8(func_0207f1c8(villager))));
    }
    return VILLAGER_KIND_NONE;
}
CLEAN_AS(func_0207b86c, VillagerKind_Known)
