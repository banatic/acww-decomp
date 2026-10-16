/* The blocks of the villagers' part of a player's record, and the part's life cycle
 * (villager_part_block.h). */
#include "villager_part_block.h"

#include "clean.h"
#include "session.h"
#include "villager_part_entry.h"
#include "villager_part_handover.h"

static_assert(sizeof(VillagerPartTypeEntry) == 20, "type entry");
static_assert(offsetof(VillagerPartTypeEntry, limit) == 0x10, "limit");
static_assert(offsetof(VillagerPartBlock, byte_2c) == 0x2c, "byte 2c");
static_assert(sizeof(VillagerPartEntry) == sizeof(((VillagerPart *) 0)->object_94), "entry");
static_assert(sizeof(VillagerPartHandover) == sizeof(((VillagerPart *) 0)->rest_a4), "handover");

/* The items the step types' setups give the block's object. */
#define VILLAGER_PART_BLOCK_ITEM_17 0x1564
#define VILLAGER_PART_BLOCK_ITEM_16 0x1561
#define VILLAGER_PART_BLOCK_ITEM_14 0x1563
#define VILLAGER_PART_BLOCK_ITEM_19 0x1565
/* The item list type 10 draws from. */
#define VILLAGER_PART_BLOCK_LIST_KIND 2
#define VILLAGER_PART_BLOCK_LIST_GROUP 0
/* The step types VillagerPartBlock_TypeFitsMode accepts, and the mode group they need. */
#define VILLAGER_PART_BLOCK_MODE_TYPE_A 10
#define VILLAGER_PART_BLOCK_MODE_TYPE_B 19
#define VILLAGER_PART_BLOCK_MODE_GROUP 1
/* The letter: the message arguments filled, its words, the resource name and the kind passed. */
#define VILLAGER_PART_LETTER_WORDS 6
#define VILLAGER_PART_LETTER_RESOURCE_SIZE 0x1e
#define VILLAGER_PART_LETTER_KIND 1

/* An item list (func_02063ccc), a player's name text (0x20 bytes) and a text label (0x60). */
typedef struct VillagerPartItemList {
    int kind;
    int group;
} VillagerPartItemList;

typedef struct VillagerPartNameText {
    u32 words[8];
} VillagerPartNameText;

typedef struct VillagerPartLabel {
    u32 words[0x18];
} VillagerPartLabel;

extern VillagerPartTypeEntry data_020e3504[VILLAGER_PART_BLOCK_STEPS]; /* by type less 10 */
extern NetSession *data_020ccf94;                                      /* the session */
extern const char data_020d1a48[];                                     /* "re_normal" */
extern const u8 data_020e3494[];

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern int func_020644cc(int bound); /* a random number below `bound` */
/* The NpcId's constructor and destructor, and the block's destructor and constructor, as the
 * array helpers are given them. */
extern void func_02003780(void *npc);
extern void func_02003750(void *npc);
extern void func_0209b594(void *block);
extern void func_0209b5b8(void *block);
/* A step type's band (0-9: 0, 10-19: 1, 20: 2, 21: 3, else 4) and its place in the band. */
extern int func_0209bc94(int type);
extern int func_0209bc54(int *place, int type);
/* An object: whether it holds something, its type, the low five bits of its byte 0x0b, its
 * type's place in its band, its item set, set to a type and item, emptied, destroyed and
 * constructed. */
extern int func_0209bd44(const u8 *object);
extern int func_0209bc40(const u8 *object);
extern u32 func_0209bba0(const u8 *object);
extern int func_0209bc44(const u8 *object, int *place);
extern void func_0209bb68(u8 *object, const u16 *item);
extern void func_0209bd30(u8 *object, u8 type, const u16 *item, u8 low_bits);
extern void func_0209bd5c(u8 *object);
extern void func_0209bd7c(u8 *object);
extern void func_0209bd80(u8 *object);
extern u32 func_0209c310(u32 mode); /* a villager mode's group: 0 for 0-4, 1 for 5-7, ... */
/* An item list: constructed, an item drawn from it, destroyed. */
extern void func_02063ccc(VillagerPartItemList *list, int kind, int group);
extern void func_020638d4(u16 *item, VillagerPartItemList *list, int a, int b, int c, int d, int e);
extern void func_02063cc8(VillagerPartItemList *list);
/* The letter's texts: a name text constructed and destroyed, a label constructed, destroyed and
 * emptied, a message argument set, a word drawn for the letter (with a number for it), a label
 * loaded, and the letter written. */
extern void *func_02094fd4(VillagerPartNameText *text);
extern void *func_02094fbc(VillagerPartNameText *text);
extern void *func_020a8228(VillagerPartLabel *label);
extern void *func_020a8210(VillagerPartLabel *label);
extern void func_020a8c1c(void *label);
extern int func_0203d7c4(int slot, void *text);
extern const char *func_0209c54c(int *number, int word);
extern int func_020b49d4(VillagerPartLabel *label, const u8 *number, const char *name);
extern void func_02066104(void *letter, u8 *a, u8 *b, u8 *c, u8 *d, char *resource, const u8 *data, const NpcId *first,
                          const NpcId *second, int kind);

/* func_0209b408 */
u8 *VillagerPartBlock_Byte2C(VillagerPartBlock *block)
{
    return &block->byte_2c;
}
CLEAN_AS(func_0209b408, VillagerPartBlock_Byte2C)

/* func_0209b40c */
void VillagerPartBlock_SetByte2C(VillagerPartBlock *block, u8 value)
{
    block->byte_2c = value;
}
CLEAN_AS(func_0209b40c, VillagerPartBlock_SetByte2C)

/* func_0209b414: VillagerPartBlock_IsPastLimit for the type the block's object holds. */
int VillagerPartBlock_IsOwnTypePastLimit(VillagerPartBlock *block)
{
    return VillagerPartBlock_IsPastLimit(block, func_0209bc40(block->object));
}
CLEAN_AS(func_0209b414, VillagerPartBlock_IsOwnTypePastLimit)

/* func_0209b42c: whether the block's object holds the step type `type` with the low bits of its
 * byte 0x0b above the type's limit. */
int VillagerPartBlock_IsPastLimit(VillagerPartBlock *block, int type)
{
    if (func_0209bd44(block->object) == 0 || func_0209bc94(type) != VILLAGER_PART_BLOCK_STEP_BAND) {
        return 0;
    }
    if (type != func_0209bc40(block->object)) {
        return 0;
    }
    int place;
    if (func_0209bc44(block->object, &place) == 0) {
        return 0;
    }
    return func_0209bba0(block->object) > data_020e3504[place].limit;
}
CLEAN_AS(func_0209b42c, VillagerPartBlock_IsPastLimit)

/* func_0209b484: whether step type `type` suits a villager in mode `mode`: types 10 and 19 for
 * the modes of group 1 (5-7), never while the session is linked. */
int VillagerPartBlock_TypeFitsMode(int type, int mode)
{
    if (Session_IsLinked(data_020ccf94)) {
        return 0;
    }
    u32 group = func_0209c310((u32) mode);
    if (type == VILLAGER_PART_BLOCK_MODE_TYPE_A || type == VILLAGER_PART_BLOCK_MODE_TYPE_B) {
        return group == VILLAGER_PART_BLOCK_MODE_GROUP;
    }
    return 0;
}
CLEAN_AS(func_0209b484, VillagerPartBlock_TypeFitsMode)

/* func_0209b4cc: the block's index-th NpcId (0x0c + 16 index). */
NpcId *VillagerPartBlock_Npc(VillagerPartBlock *block, int index)
{
    return (NpcId *) ((uintptr_t) block->npcs + ((u32) index << 4));
}
CLEAN_AS(func_0209b4cc, VillagerPartBlock_Npc)

/* func_0209b4d4: the block's object (the block itself). */
u8 *VillagerPartBlock_Object(VillagerPartBlock *block)
{
    return block->object;
}
CLEAN_AS(func_0209b4d4, VillagerPartBlock_Object)

/* func_0209b4d8: the block set to step type `type` (band 1 only): its object given the type and
 * no item, the type's setup run on it, and the NpcIds given (NULL: left alone) copied into it. 1
 * when it was set. */
int VillagerPartBlock_SetType(VillagerPartBlock *block, int type, const NpcId *first, const NpcId *second)
{
    if (func_0209bc94(type) != VILLAGER_PART_BLOCK_STEP_BAND) {
        return 0;
    }
    int place = 0;
    if (func_0209bc54(&place, type) == 0) {
        return 0;
    }

    u16 item = 0xfff1;
    func_0209bd30(block->object, (u8) type, &item, 0);
    const VillagerPartTypeEntry *entry = &data_020e3504[place];
    if (entry->setup.function != 0) {
        MemberPointer_CallVoid(&entry->setup, block);
    }
    if (first != NULL) {
        NpcId_Copy(&block->npcs[0], first);
    }
    if (second != NULL) {
        NpcId_Copy(&block->npcs[1], second);
    }
    return 1;
}
CLEAN_AS(func_0209b4d8, VillagerPartBlock_SetType)

/* func_0209b56c: the block emptied: its object, both NpcIds and byte 0x2c. */
void VillagerPartBlock_Clear(VillagerPartBlock *block)
{
    func_0209bd5c(block->object);
    for (int i = 0; i < 2; i++) {
        NpcId_Clear(&block->npcs[i]);
    }
    block->byte_2c = 0;
}
CLEAN_AS(func_0209b56c, VillagerPartBlock_Clear)

/* func_0209b594: the destructor. */
VillagerPartBlock *VillagerPartBlock_Destruct(VillagerPartBlock *block)
{
    __cxa_vec_cleanup(block->npcs, 2, sizeof(NpcId), func_02003750);
    func_0209bd7c(block->object);
    return block;
}
CLEAN_AS(func_0209b594, VillagerPartBlock_Destruct)

/* func_0209b5b8: the constructor. */
VillagerPartBlock *VillagerPartBlock_Construct(VillagerPartBlock *block)
{
    func_0209bd80(block->object);
    __cxa_vec_ctor(block->npcs, 2, sizeof(NpcId), func_02003780, func_02003750);
    return block;
}
CLEAN_AS(func_0209b5b8, VillagerPartBlock_Construct)

/* The setup of a step type that gives the block's object an item; 1. */
static int villager_part_block_give(VillagerPartBlock *block, u16 item)
{
    func_0209bb68(block->object, &item);
    return 1;
}

/* func_0209b254: type 17's setup. */
int VillagerPartBlock_SetupType17(VillagerPartBlock *block)
{
    return villager_part_block_give(block, VILLAGER_PART_BLOCK_ITEM_17);
}
CLEAN_AS(func_0209b254, VillagerPartBlock_SetupType17)

/* func_0209b270: type 16's setup. */
int VillagerPartBlock_SetupType16(VillagerPartBlock *block)
{
    return villager_part_block_give(block, VILLAGER_PART_BLOCK_ITEM_16);
}
CLEAN_AS(func_0209b270, VillagerPartBlock_SetupType16)

/* func_0209b28c: type 14's setup. */
int VillagerPartBlock_SetupType14(VillagerPartBlock *block)
{
    return villager_part_block_give(block, VILLAGER_PART_BLOCK_ITEM_14);
}
CLEAN_AS(func_0209b28c, VillagerPartBlock_SetupType14)

/* func_0209b2a8: a letter written into `letter` from the block's two villagers, when both
 * NpcIds are valid: message argument 0 the second villager's name, 1 the first's, 2-7 six
 * words (func_0209c54c, each with the number it gives, which carries over from one word to the
 * next); then the first villager's "re_normal" resource name and four random digits are handed
 * to func_02066104 with both NpcIds. */
void VillagerPartBlock_WriteLetter(VillagerPartBlock *block, void *letter)
{
    if (NpcId_IsValid(&block->npcs[0]) == 0 || NpcId_IsValid(&block->npcs[1]) == 0) {
        return;
    }

    VillagerPartNameText name;
    VillagerPartLabel label;
    u8 bytes[5];
    char resource[0x20];
    func_02094fd4(&name);
    func_020a8228(&label);
    int number = 0;
    NpcId_FormatName(&block->npcs[1], (char *) &name);
    func_0203d7c4(0, &name);
    func_020a8c1c(&name);
    NpcId_FormatName(&block->npcs[0], (char *) &name);
    func_0203d7c4(1, &name);
    for (int i = 0; i < VILLAGER_PART_LETTER_WORDS; i++) {
        const char *word = func_0209c54c(&number, i);
        func_020a8c1c(&label);
        bytes[0] = (u8) number;
        func_020b49d4(&label, bytes, word);
        func_0203d7c4(i + 2, &label);
    }

    NpcId_FormatResourceName(&block->npcs[0], resource, VILLAGER_PART_LETTER_RESOURCE_SIZE, data_020d1a48);
    for (int i = 1; i <= 4; i++) {
        bytes[i] = (u8) func_020644cc(10);
    }
    func_02066104(letter, &bytes[1], &bytes[2], &bytes[3], &bytes[4], resource, data_020e3494, &block->npcs[0],
                  &block->npcs[1], VILLAGER_PART_LETTER_KIND);
    func_020a8210(&label);
    func_02094fbc(&name);
}
CLEAN_AS(func_0209b2a8, VillagerPartBlock_WriteLetter)

/* func_0209b3b0: type 19's setup. */
int VillagerPartBlock_SetupType19(VillagerPartBlock *block)
{
    return villager_part_block_give(block, VILLAGER_PART_BLOCK_ITEM_19);
}
CLEAN_AS(func_0209b3b0, VillagerPartBlock_SetupType19)

/* func_0209b3cc: type 10's setup: the object's item drawn from item list 2, group 0. */
int VillagerPartBlock_SetupType10(VillagerPartBlock *block)
{
    u16 item;
    VillagerPartItemList list;
    func_02063ccc(&list, VILLAGER_PART_BLOCK_LIST_KIND, VILLAGER_PART_BLOCK_LIST_GROUP);
    func_020638d4(&item, &list, 0, 0, 1, 1, 0);
    func_02063cc8(&list);
    func_0209bb68(block->object, &item);
    return 1;
}
CLEAN_AS(func_0209b3cc, VillagerPartBlock_SetupType10)

/* func_0209adb0: the whole part emptied: both blocks, the picks, the entry at 0x94 and the
 * record at 0xa4. */
void VillagerPart_ClearAll(VillagerPart *part)
{
    for (int i = 0; i < VILLAGER_PART_BLOCKS; i++) {
        VillagerPartBlock_Clear(&part->blocks[i]);
    }
    VillagerPart_ClearPicks(part);
    VillagerPartEntry_Clear((VillagerPartEntry *) part->object_94);
    VillagerPartHandover_Clear((VillagerPartHandover *) part->rest_a4);
}
CLEAN_AS(func_0209adb0, VillagerPart_ClearAll)

/* func_0209ade4: the destructor. */
VillagerPart *VillagerPart_Destruct(VillagerPart *part)
{
    VillagerPartHandover_Destruct((VillagerPartHandover *) part->rest_a4);
    func_0209bd7c(part->object_94);
    __cxa_vec_cleanup(part->picks, VILLAGER_PART_PICKS, sizeof(NpcId), func_02003750);
    __cxa_vec_cleanup(part->blocks, VILLAGER_PART_BLOCKS, sizeof(VillagerPartBlock), func_0209b594);
    return part;
}
CLEAN_AS(func_0209ade4, VillagerPart_Destruct)

/* func_0209ae20: the constructor (the entry at 0x94 only has its object constructed). */
VillagerPart *VillagerPart_Construct(VillagerPart *part)
{
    __cxa_vec_ctor(part->blocks, VILLAGER_PART_BLOCKS, sizeof(VillagerPartBlock), func_0209b5b8, func_0209b594);
    __cxa_vec_ctor(part->picks, VILLAGER_PART_PICKS, sizeof(NpcId), func_02003780, func_02003750);
    func_0209bd80(part->object_94);
    VillagerPartHandover_Construct((VillagerPartHandover *) part->rest_a4);
    return part;
}
CLEAN_AS(func_0209ae20, VillagerPart_Construct)
