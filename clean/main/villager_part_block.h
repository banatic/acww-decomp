/* The two blocks of the villagers' part of a player's record (VillagerPartBlock, villager_part.h),
 * the part's own constructor, destructor and clearing, and the table of the step types a block
 * is set to.
 *
 * A block's object takes a step type of band 1 (types 10-19, func_0209bc94); each has an entry
 * of 20 bytes in data_020e3504: a member function run when a block is set to the type
 * (VillagerPartBlock_SetType), a second member pointer, and a limit for the low bits of the
 * object's byte 0x0b (VillagerPartBlock_IsPastLimit). The member functions:
 *
 *   type 10  the object's item drawn from item list 2 (VillagerPartBlock_SetupType10)
 *   type 14  item 0x1563;  type 16  item 0x1561;  type 17  item 0x1564;  type 19  item 0x1565
 *
 * For type 19 a letter is written from the block's two villagers (VillagerPartBlock_WriteLetter).
 * Byte 0x2c of a block is set by its users (func_02027914) and read through
 * VillagerPartBlock_Byte2C. */
#ifndef CLEAN_MAIN_VILLAGER_PART_BLOCK_H
#define CLEAN_MAIN_VILLAGER_PART_BLOCK_H

#include "npc_id.h"
#include "ov004/member_pointer.h"
#include "types.h"
#include "villager_part.h"

/* The band of the step types, and its first type. */
#define VILLAGER_PART_BLOCK_STEP_BAND 1
#define VILLAGER_PART_BLOCK_FIRST_STEP 10
#define VILLAGER_PART_BLOCK_STEPS 10

/* A step type's entry in data_020e3504. */
typedef struct VillagerPartTypeEntry {
    MemberPointer setup;   /* 0x00: run on the block when it is set to the type; none when 0 */
    MemberPointer unknown; /* 0x08 */
    u8 limit;              /* 0x10 */
    u8 unused_11[3];
} VillagerPartTypeEntry;

u8 *VillagerPartBlock_Byte2C(VillagerPartBlock *block);
void VillagerPartBlock_SetByte2C(VillagerPartBlock *block, u8 value);
int VillagerPartBlock_IsOwnTypePastLimit(VillagerPartBlock *block);
int VillagerPartBlock_IsPastLimit(VillagerPartBlock *block, int type);
int VillagerPartBlock_TypeFitsMode(int type, int mode);
NpcId *VillagerPartBlock_Npc(VillagerPartBlock *block, int index);
u8 *VillagerPartBlock_Object(VillagerPartBlock *block);
int VillagerPartBlock_SetType(VillagerPartBlock *block, int type, const NpcId *first, const NpcId *second);
void VillagerPartBlock_Clear(VillagerPartBlock *block);
VillagerPartBlock *VillagerPartBlock_Destruct(VillagerPartBlock *block);
VillagerPartBlock *VillagerPartBlock_Construct(VillagerPartBlock *block);

int VillagerPartBlock_SetupType17(VillagerPartBlock *block);
int VillagerPartBlock_SetupType16(VillagerPartBlock *block);
int VillagerPartBlock_SetupType14(VillagerPartBlock *block);
void VillagerPartBlock_WriteLetter(VillagerPartBlock *block, void *letter);
int VillagerPartBlock_SetupType19(VillagerPartBlock *block);
int VillagerPartBlock_SetupType10(VillagerPartBlock *block);

void VillagerPart_ClearAll(VillagerPart *part);
VillagerPart *VillagerPart_Destruct(VillagerPart *part);
VillagerPart *VillagerPart_Construct(VillagerPart *part);

#endif
