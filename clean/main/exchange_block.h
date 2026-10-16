/* An exchange block (0x950 bytes): what one town hands another in a visit (exchange_blocks.h).
 * The town's own is part_11c70 of the state block (data_021ee418); the host keeps one more for
 * each of the three other slots, in an array at data_021d36d4. A block holds:
 *   - a letter in a bottle (mail.h), with how many times it has drifted (up to 5) and a flag
 *     that lets it arrive at once (bottle_mail.h);
 *   - a constellation being designed (constellations.h);
 *   - a villager moving between towns (villager_copy.h);
 *   - a paired town (paired_town.h);
 *   - its checksum, a halfword (card_save.c).
 * Its parts are classes of their own: the block's constructor and destructor
 * (func_020901d8, func_020901a0) call theirs. */
#ifndef CLEAN_MAIN_EXCHANGE_BLOCK_H
#define CLEAN_MAIN_EXCHANGE_BLOCK_H

#include "mail.h" /* MailLetter */
#include "types.h"

#define EXCHANGE_BLOCK_VISITORS 3   /* the blocks kept for the other slots */
#define EXCHANGE_BLOCK_MAX_DRIFTS 5 /* ExchangeBlock.drifts stops there */

typedef struct ExchangeBlock {
    MailLetter bottle_letter; /* 0x000 */
    u8 constellation[0x4c];   /* 0x100: Constellation */
    u8 villager[0x7ec];       /* 0x14c: a villager (villager_copy.h) */
    u8 drifts;                /* 0x938: times the bottle drifted */
    u8 flags;                 /* 0x939: bit 0: the bottle arrives at once */
    u8 paired_town[0x10];     /* 0x93a: PairedTown */
    u16 checksum;             /* 0x94a */
    u8 pad_94c[4];
} ExchangeBlock;

int ExchangeBlock_OfSlot(int slot);
int ExchangeBlock_Visitor(int index);
int ExchangeBlock_DestructVisitors(ExchangeBlock *blocks);
int ExchangeBlock_ConstructVisitors(ExchangeBlock *blocks);
int ExchangeBlock_Villager(ExchangeBlock *block);
int ExchangeBlock_Constellation(ExchangeBlock *block);
MailLetter *ExchangeBlock_BottleLetter(ExchangeBlock *block);
u8 ExchangeBlock_Drifts(ExchangeBlock *block);
void ExchangeBlock_ClearDrifts(ExchangeBlock *block);
void ExchangeBlock_AddDrift(ExchangeBlock *block);
int ExchangeBlock_PairedTown(ExchangeBlock *block);
int ExchangeBlock_ArrivesAtOnce(ExchangeBlock *block);
void ExchangeBlock_SetArrivesAtOnce(ExchangeBlock *block, unsigned int value);
int ExchangeBlock_IsSendable(ExchangeBlock *block);
u16 ExchangeBlock_Checksum(ExchangeBlock *block);
void ExchangeBlock_SetChecksum(ExchangeBlock *block, u16 checksum);
void ExchangeBlock_Clear(ExchangeBlock *block);
void ExchangeBlock_SetUp(ExchangeBlock *block);
ExchangeBlock *ExchangeBlock_Destruct(ExchangeBlock *block);
ExchangeBlock *ExchangeBlock_Construct(ExchangeBlock *block);

#endif
