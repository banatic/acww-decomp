/* The villagers' part of a player's record (0xcc bytes at 0x1e40, PlayerRecord_VillagerPart).
 *
 * It holds two blocks of 48 bytes (VillagerPart_Block), each an object (12 bytes: its item at
 * 8, its type at 0x0a, a five-bit value in byte 0x0b) and two NpcIds; three NpcIds of villagers
 * picked in turn; a flag (0x90); an object at 0x94 (12 bytes, then the index at 0x0c of an
 * entry of data_020d1a54 whose name func_0209b0c4 writes); and an NpcId with an object of its
 * own at 0xa4 (villager_town.c).
 *
 * Overlay 50 takes block 0 through a sequence of types, which VillagerPart_HasStep tests for
 * (types 11-18): 11 resets it (VillagerPart_Reset), 12 and 13 name no villager, 14 names a
 * resident picked at random (kept as the first pick), 15 a second one other than the first,
 * 16 a third other than the first two, 17 the second again, and 18 none. A type is set by
 * func_0209b4d8, which also runs that type's setup and copies the NpcIds given into the block.
 * Letters a player sends are noted in block 0 while it holds type 15 (VillagerPart_NoteLetter). */
#ifndef CLEAN_MAIN_VILLAGER_PART_H
#define CLEAN_MAIN_VILLAGER_PART_H

#include "mail.h"
#include "npc_id.h"
#include "types.h"

#define VILLAGER_PART_BLOCKS 2
#define VILLAGER_PART_PICKS 3

/* The types of block 0's object. */
#define VILLAGER_PART_TYPE_RESET 0x0b
#define VILLAGER_PART_TYPE_12 0x0c
#define VILLAGER_PART_TYPE_13 0x0d
#define VILLAGER_PART_TYPE_FIRST_PICK 0x0e
#define VILLAGER_PART_TYPE_SECOND_PICK 0x0f
#define VILLAGER_PART_TYPE_THIRD_PICK 0x10
#define VILLAGER_PART_TYPE_SECOND_AGAIN 0x11
#define VILLAGER_PART_TYPE_18 0x12

typedef struct VillagerPartBlock {
    u8 object[12]; /* 0x00 */
    NpcId npcs[2]; /* 0x0c: the second (0x1c) is the villager the type names */
    u8 byte_2c;    /* 0x2c: cleared with the block (func_0209b56c) */
    u8 unused_2d[3];
} VillagerPartBlock;

typedef struct VillagerPart {
    VillagerPartBlock blocks[VILLAGER_PART_BLOCKS]; /* 0x00 */
    NpcId picks[VILLAGER_PART_PICKS];               /* 0x60 */
    u8 flag;                                        /* 0x90 */
    u8 unused_91[3];
    u8 object_94[16]; /* 0x94 */
    u8 rest_a4[0x28]; /* 0xa4: an NpcId and an object at 0xb4 */
} VillagerPart;

void VillagerPart_CurrentNameFor(void *text, u16 *item);
u8 *VillagerPart_Object94(VillagerPart *part);
int VillagerPart_IsSecondPick(VillagerPart *part, const NpcId *npc);
void VillagerPart_EndStep(VillagerPart *part);
void VillagerPart_MarkType18(VillagerPart *part);
int VillagerPart_SetType18(VillagerPart *part);
void VillagerPart_SetSecondAgain(VillagerPart *part);
void VillagerPart_SetThirdPick(VillagerPart *part);
int VillagerPart_NoteLetter(VillagerPart *part, Letter *letter);
void VillagerPart_CurrentMarkSecondPick(void);
void VillagerPart_MarkSecondPick(VillagerPart *part);
void VillagerPart_SetSecondPick(VillagerPart *part);
void VillagerPart_SetFirstPick(VillagerPart *part);
void VillagerPart_SetType13(VillagerPart *part);
void VillagerPart_SetType12(VillagerPart *part);
int VillagerPart_Flag(const VillagerPart *part);
void VillagerPart_ClearFlag(VillagerPart *part);
void VillagerPart_SetFlag(VillagerPart *part);
void VillagerPart_Reset(VillagerPart *part);
int VillagerPart_HasStep(VillagerPart *part);
void VillagerPart_ClearPicks(VillagerPart *part);
int VillagerPart_NameFor(VillagerPart *part, void *text, u16 *item);
VillagerPartBlock *VillagerPart_FindBlock(VillagerPart *part, const NpcId *npc, int which);
VillagerPartBlock *VillagerPart_Block(VillagerPart *part, int index);

#endif
