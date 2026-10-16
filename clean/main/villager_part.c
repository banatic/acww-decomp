/* The villagers' part of a player's record (villager_part.h). */
#include "villager_part.h"

#include <string.h>

#include "clean.h"
#include "item_code.h"
#include "player_record.h"
#include "player_records.h"
#include "villager_roster.h"

static_assert(sizeof(VillagerPartBlock) == 0x30, "block");
static_assert(offsetof(VillagerPart, picks) == 0x60, "picks");
static_assert(offsetof(VillagerPart, flag) == 0x90, "flag");
static_assert(offsetof(VillagerPart, object_94) == 0x94, "object 94");
static_assert(sizeof(VillagerPart) == 0xcc, "part");

/* The items VillagerPart_NameFor names the entry of the object at 0x94 for, when it holds
 * something. */
#define VILLAGER_PART_ENTRY_ITEM_FIRST 0x155f
#define VILLAGER_PART_ENTRY_ITEM_LAST 0x1560
/* The values of the low bits of block 0's byte 0x0b set here. */
#define VILLAGER_PART_MARKED 1
#define VILLAGER_PART_MARKED_FOR_VILLAGER 2
/* func_0209bba8's band of the step types (11-18). */
#define VILLAGER_PART_STEP_BAND 1

extern u8 data_021e5a2c[]; /* the town's villagers (VillagerTown) */

extern void *func_02137550(void *dst, u32 size);             /* clears size bytes */
extern NpcId *func_0208150c(const u8 *villager);             /* the villager's NpcId, at 0x7a0 */
extern u8 func_02065ec0(const MailLetter *letter);           /* its state; 0: no letter */
extern const NpcId *func_02065f64(const MailLetter *letter); /* its villager addressee, or NULL */
/* A block: its object (the block itself), its index-th NpcId, emptied, and set to a type with
 * the NpcIds given (NULL: none), 1 when the type has a setup. */
extern u8 *func_0209b4d4(VillagerPartBlock *block);
extern NpcId *func_0209b4cc(VillagerPartBlock *block, int index);
extern void func_0209b56c(VillagerPartBlock *block);
extern int func_0209b4d8(VillagerPartBlock *block, int type, const NpcId *first, const NpcId *second);
/* An object: whether it holds something (type below 22), its type, the low five bits of byte
 * 0x0b and their setter, the band of its type, its item. */
extern int func_0209bd44(const u8 *object);
extern int func_0209bc40(const u8 *object);
extern u32 func_0209bba0(const u8 *object);
extern void func_0209bb90(u8 *object, int value);
extern int func_0209bba8(const u8 *object);
extern u16 *func_0209bb70(u8 *object);
/* The object at 0x94: itself, and the name of its entry written into `text`. */
extern u8 *func_0209b0f0(u8 *object);
extern int func_0209b0c4(u8 *object, void *text);

static int same_npc(const NpcId *a, const NpcId *b)
{
    return a->head.id == b->head.id && memcmp(a->head.data, b->head.data, sizeof(a->head.data)) == 0 && a->number == b->number;
}

/* A resident picked at random, leaving out the `count` villagers of `excluded`. */
static u8 *villager_part_pick(const NpcId *const *excluded, int count)
{
    return VillagerRoster_PickResident((VillagerTown *) data_021e5a2c, excluded, count);
}

/* func_02099e7c: VillagerPart_NameFor for the current player. */
void VillagerPart_CurrentNameFor(void *text, u16 *item)
{
    VillagerPart *part = (VillagerPart *) PlayerRecord_VillagerPart(PlayerRecords_Current());
    VillagerPart_NameFor(part, text, item);
}
CLEAN_AS(func_02099e7c, VillagerPart_CurrentNameFor)

/* func_0209a850 */
u8 *VillagerPart_Object94(VillagerPart *part)
{
    return part->object_94;
}
CLEAN_AS(func_0209a850, VillagerPart_Object94)

/* func_0209a854: whether `npc` is valid and is the second villager picked, while block 0 holds
 * a step. */
int VillagerPart_IsSecondPick(VillagerPart *part, const NpcId *npc)
{
    if (NpcId_IsValid(npc) == 0 || VillagerPart_HasStep(part) == 0) {
        return 0;
    }
    return same_npc(npc, &part->picks[1]);
}
CLEAN_AS(func_0209a854, VillagerPart_IsSecondPick)

/* func_0209a8a4: block 0 emptied when it holds a step. */
void VillagerPart_EndStep(VillagerPart *part)
{
    if (VillagerPart_HasStep(part) != 0) {
        func_0209b56c(VillagerPart_Block(part, 0));
    }
}
CLEAN_AS(func_0209a8a4, VillagerPart_EndStep)

/* func_0209a8c4: block 0's value set to 1 when it holds type 18 with value 0. */
void VillagerPart_MarkType18(VillagerPart *part)
{
    u8 *object = func_0209b4d4(VillagerPart_Block(part, 0));
    if (func_0209bd44(object) != 0 && func_0209bc40(object) == VILLAGER_PART_TYPE_18 && func_0209bba0(object) == 0) {
        func_0209bb90(object, VILLAGER_PART_MARKED);
    }
}
CLEAN_AS(func_0209a8c4, VillagerPart_MarkType18)

/* func_0209a8fc: block 0 set to type 18, naming no villager. */
int VillagerPart_SetType18(VillagerPart *part)
{
    return func_0209b4d8(VillagerPart_Block(part, 0), VILLAGER_PART_TYPE_18, NULL, NULL);
}
CLEAN_AS(func_0209a8fc, VillagerPart_SetType18)

/* func_0209a918: block 0 set to type 17, naming the second villager picked. */
void VillagerPart_SetSecondAgain(VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    func_0209b4d8(block, VILLAGER_PART_TYPE_SECOND_AGAIN, NULL, &part->picks[1]);
}
CLEAN_AS(func_0209a918, VillagerPart_SetSecondAgain)

/* func_0209a934: block 0 set to type 16, naming a resident other than the first two picked
 * (those that are valid), who is kept as the third. QUIRK: with no resident to pick, the NpcId
 * named and kept is read at 0x7a0 (func_0208150c of NULL). */
void VillagerPart_SetThirdPick(VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    const NpcId *excluded[2];
    func_02137550(excluded, sizeof(excluded));
    int count = 0;
    for (int i = 0; i < 2; i++) {
        const NpcId *pick = &part->picks[i];
        if (NpcId_IsValid(pick)) {
            excluded[count] = pick;
            count++;
        }
    }
    u8 *villager = villager_part_pick(excluded, count);
    func_0209b4d8(block, VILLAGER_PART_TYPE_THIRD_PICK, NULL, func_0208150c(villager));
    NpcId_Copy(&part->picks[2], func_0208150c(villager));
}
CLEAN_AS(func_0209a934, VillagerPart_SetThirdPick)

/* func_0209a9a8: a letter the player sends noted in block 0, while it holds type 15; whether it
 * was. A letter to the villager the block names (a valid one) raises the block's value to 2
 * when it is below; any other letter sets it to 1 when it is 0. 0 for no letter. */
int VillagerPart_NoteLetter(VillagerPart *part, MailLetter *letter)
{
    if (letter == NULL || func_02065ec0(letter) == 0) {
        return 0;
    }
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    u8 *object = func_0209b4d4(block);
    if (func_0209bc40(object) != VILLAGER_PART_TYPE_SECOND_PICK) {
        return 0;
    }

    const NpcId *addressee = func_02065f64(letter);
    if (addressee == NULL) {
        if (func_0209bba0(object) == 0) {
            func_0209bb90(object, VILLAGER_PART_MARKED);
            return 1;
        }
        return 0;
    }

    int noted;
    NpcId npc;
    NpcId_ConstructCopy(&npc, addressee);
    if (NpcId_IsValid(&npc) != 0 && same_npc(func_0209b4cc(block, 1), &npc)) {
        noted = func_0209bba0(object) < VILLAGER_PART_MARKED_FOR_VILLAGER;
        if (noted) {
            func_0209bb90(object, VILLAGER_PART_MARKED_FOR_VILLAGER);
        }
    } else {
        noted = func_0209bba0(object) == 0;
        if (noted) {
            func_0209bb90(object, VILLAGER_PART_MARKED);
        }
    }
    NpcId_Destruct(&npc);
    return noted;
}
CLEAN_AS(func_0209a9a8, VillagerPart_NoteLetter)

/* func_0209aa80: VillagerPart_MarkSecondPick for the current player, when there is one. */
void VillagerPart_CurrentMarkSecondPick(void)
{
    u8 *record = PlayerRecords_Current();
    if (record != NULL) {
        VillagerPart_MarkSecondPick((VillagerPart *) PlayerRecord_VillagerPart(record));
    }
}
CLEAN_AS(func_0209aa80, VillagerPart_CurrentMarkSecondPick)

/* func_0209aa9c: block 0's value set to 1 when it holds type 15 with value 0. */
void VillagerPart_MarkSecondPick(VillagerPart *part)
{
    u8 *object = func_0209b4d4(VillagerPart_Block(part, 0));
    if (func_0209bc40(object) == VILLAGER_PART_TYPE_SECOND_PICK && func_0209bba0(object) == 0) {
        func_0209bb90(object, VILLAGER_PART_MARKED);
    }
}
CLEAN_AS(func_0209aa9c, VillagerPart_MarkSecondPick)

/* func_0209aacc: block 0 set to type 15, naming a resident other than the first picked (when
 * valid), who is kept as the second. QUIRK: as VillagerPart_SetThirdPick with no resident. */
void VillagerPart_SetSecondPick(VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    func_0209b4d4(block);
    const NpcId *excluded;
    func_02137550(&excluded, sizeof(excluded));
    int count = 0;
    if (NpcId_IsValid(&part->picks[0]) != 0) {
        excluded = &part->picks[0];
        count = 1;
    }
    u8 *villager = villager_part_pick(&excluded, count);
    func_0209b4d8(block, VILLAGER_PART_TYPE_SECOND_PICK, NULL, func_0208150c(villager));
    NpcId_Copy(&part->picks[1], func_0208150c(villager));
}
CLEAN_AS(func_0209aacc, VillagerPart_SetSecondPick)

/* func_0209ab34: block 0 set to type 14, naming a resident picked at random, who is kept as the
 * first. QUIRK: as VillagerPart_SetThirdPick with no resident. */
void VillagerPart_SetFirstPick(VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    u8 *villager = villager_part_pick(NULL, 0);
    func_0209b4d8(block, VILLAGER_PART_TYPE_FIRST_PICK, NULL, func_0208150c(villager));
    NpcId_Copy(&part->picks[0], func_0208150c(villager));
}
CLEAN_AS(func_0209ab34, VillagerPart_SetFirstPick)

/* func_0209ab78: block 0 set to type 13, naming no villager. */
void VillagerPart_SetType13(VillagerPart *part)
{
    func_0209b4d8(VillagerPart_Block(part, 0), VILLAGER_PART_TYPE_13, NULL, NULL);
}
CLEAN_AS(func_0209ab78, VillagerPart_SetType13)

/* func_0209ab94: block 0 set to type 12, naming no villager. */
void VillagerPart_SetType12(VillagerPart *part)
{
    func_0209b4d8(VillagerPart_Block(part, 0), VILLAGER_PART_TYPE_12, NULL, NULL);
}
CLEAN_AS(func_0209ab94, VillagerPart_SetType12)

/* func_0209abb0 */
int VillagerPart_Flag(const VillagerPart *part)
{
    return part->flag == 1;
}
CLEAN_AS(func_0209abb0, VillagerPart_Flag)

/* func_0209abc0 */
void VillagerPart_ClearFlag(VillagerPart *part)
{
    part->flag = 0;
}
CLEAN_AS(func_0209abc0, VillagerPart_ClearFlag)

/* func_0209abc8 */
void VillagerPart_SetFlag(VillagerPart *part)
{
    part->flag = 1;
}
CLEAN_AS(func_0209abc8, VillagerPart_SetFlag)

/* func_0209abd0: block 0 emptied and set to type 11, no villagers picked, the flag cleared. */
void VillagerPart_Reset(VillagerPart *part)
{
    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    func_0209b56c(block);
    func_0209b4d8(block, VILLAGER_PART_TYPE_RESET, NULL, NULL);
    VillagerPart_ClearPicks(part);
    VillagerPart_ClearFlag(part);
}
CLEAN_AS(func_0209abd0, VillagerPart_Reset)

/* func_0209ac04: whether block 0 holds one of the step types (11-18). */
int VillagerPart_HasStep(VillagerPart *part)
{
    u8 *object = func_0209b4d4(VillagerPart_Block(part, 0));
    return func_0209bd44(object) != 0 && func_0209bba8(object) == VILLAGER_PART_STEP_BAND;
}
CLEAN_AS(func_0209ac04, VillagerPart_HasStep)

/* func_0209ac30 */
void VillagerPart_ClearPicks(VillagerPart *part)
{
    for (int i = 0; i < VILLAGER_PART_PICKS; i++) {
        NpcId_Clear(&part->picks[i]);
    }
}
CLEAN_AS(func_0209ac30, VillagerPart_ClearPicks)

/* func_0209ac50: the name that goes with `*item` written into `text`; whether one was. For
 * items 0x155f and 0x1560, while the object at 0x94 holds something, the name of its entry;
 * else, when block 0 holds an object with the same item (compared without the variant for
 * codes that have one), the name of the villager the block names. QUIRK: the items
 * 0x1561-0x1564 pick block 0 as any other does. */
int VillagerPart_NameFor(VillagerPart *part, void *text, u16 *item)
{
    if (*item >= VILLAGER_PART_ENTRY_ITEM_FIRST && *item <= VILLAGER_PART_ENTRY_ITEM_LAST) {
        if (func_0209bd44(func_0209b0f0(part->object_94)) != 0) {
            return func_0209b0c4(part->object_94, text);
        }
    }

    VillagerPartBlock *block = VillagerPart_Block(part, 0);
    if (block == NULL) {
        return 0;
    }
    u8 *object = func_0209b4d4(block);
    if (func_0209bd44(object) == 0) {
        return 0;
    }
    u16 *held = func_0209bb70(object);
    int same;
    if (ItemCode_HasVariant(held)) {
        int held_item = ItemCode_VariantItem(held);
        same = held_item == ItemCode_VariantItem(item);
    } else {
        same = *held == *item;
    }
    if (!same) {
        return 0;
    }
    return NpcId_FormatName(func_0209b4cc(block, 1), (char *) text);
}
CLEAN_AS(func_0209ac50, VillagerPart_NameFor)

/* func_0209ad2c: the first block holding something whose NpcId `which` is the valid `npc`, or
 * NULL. */
VillagerPartBlock *VillagerPart_FindBlock(VillagerPart *part, const NpcId *npc, int which)
{
    if (NpcId_IsValid(npc) == 0) {
        return NULL;
    }
    for (int i = 0; i < VILLAGER_PART_BLOCKS; i++) {
        VillagerPartBlock *block = &part->blocks[i];
        if (func_0209bd44(func_0209b4d4(block)) == 0) {
            continue;
        }
        if (same_npc(func_0209b4cc(block, which), npc)) {
            return block;
        }
    }
    return NULL;
}
CLEAN_AS(func_0209ad2c, VillagerPart_FindBlock)

/* func_0209ad9c: block `index`; NULL outside 0-1. */
VillagerPartBlock *VillagerPart_Block(VillagerPart *part, int index)
{
    if (index >= 0 && index < VILLAGER_PART_BLOCKS) {
        return &part->blocks[index];
    }
    return NULL;
}
CLEAN_AS(func_0209ad9c, VillagerPart_Block)
