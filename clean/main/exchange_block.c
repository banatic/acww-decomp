/* An exchange block and its parts (exchange_block.h). */
#include "exchange_block.h"

#include "clean.h"

static_assert(offsetof(ExchangeBlock, constellation) == 0x100 && offsetof(ExchangeBlock, villager) == 0x14c, "ExchangeBlock");
static_assert(offsetof(ExchangeBlock, drifts) == 0x938 && offsetof(ExchangeBlock, paired_town) == 0x93a, "ExchangeBlock");
static_assert(offsetof(ExchangeBlock, checksum) == 0x94a && sizeof(ExchangeBlock) == 0x950, "ExchangeBlock");

/* The town's own block, and the other slots' blocks. */
extern ExchangeBlock data_021ee418;
extern ExchangeBlock data_021d36d4[EXCHANGE_BLOCK_VISITORS];

/* A block's constructor and destructor, handed to the C++ runtime's array helpers. */
extern void *func_020901d8(void *block);
extern char *func_020901a0(char *block);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

#define EXCHANGE_BLOCK_ARRIVES_AT_ONCE 0x01

static int exchange_block_address(const ExchangeBlock *block)
{
    return (int) (uintptr_t) block;
}

/* func_02090040: the block of a slot: the kept ones for slots 1-3, the town's own for any
 * other number. */
int ExchangeBlock_OfSlot(int slot)
{
    switch (slot) {
        case 1:
            return ExchangeBlock_Visitor(0);
        case 2:
            return ExchangeBlock_Visitor(1);
        case 3:
            return ExchangeBlock_Visitor(2);
        default:
            return exchange_block_address(&data_021ee418);
    }
}
CLEAN_AS(func_02090040, ExchangeBlock_OfSlot)

/* func_02090078: the kept block `index` (0-2; not checked). */
int ExchangeBlock_Visitor(int index)
{
    return (int) ((u32) exchange_block_address(data_021d36d4) + (u32) index * sizeof(ExchangeBlock));
}
CLEAN_AS(func_02090078, ExchangeBlock_Visitor)

/* func_0209008c: the kept blocks' array destructed. */
int ExchangeBlock_DestructVisitors(ExchangeBlock *blocks)
{
    __cxa_vec_cleanup(blocks, EXCHANGE_BLOCK_VISITORS, sizeof(ExchangeBlock), (void (*)(void *))(uintptr_t) func_020901a0);
    return exchange_block_address(blocks);
}
CLEAN_AS(func_0209008c, ExchangeBlock_DestructVisitors)

/* func_020900ac: the kept blocks' array constructed. */
int ExchangeBlock_ConstructVisitors(ExchangeBlock *blocks)
{
    __cxa_vec_ctor(blocks, EXCHANGE_BLOCK_VISITORS, sizeof(ExchangeBlock), (void (*)(void *))(uintptr_t) func_020901d8,
                   (void (*)(void *))(uintptr_t) func_020901a0);
    return exchange_block_address(blocks);
}
CLEAN_AS(func_020900ac, ExchangeBlock_ConstructVisitors)

/* func_020900d8 */
int ExchangeBlock_Villager(ExchangeBlock *block)
{
    return (int) (uintptr_t) block->villager;
}
CLEAN_AS(func_020900d8, ExchangeBlock_Villager)

/* func_020900e4 */
int ExchangeBlock_Constellation(ExchangeBlock *block)
{
    return (int) (uintptr_t) block->constellation;
}
CLEAN_AS(func_020900e4, ExchangeBlock_Constellation)

/* func_020900f0 */
MailLetter *ExchangeBlock_BottleLetter(ExchangeBlock *block)
{
    return &block->bottle_letter;
}
CLEAN_AS(func_020900f0, ExchangeBlock_BottleLetter)

/* func_020900f4 */
u8 ExchangeBlock_Drifts(ExchangeBlock *block)
{
    return block->drifts;
}
CLEAN_AS(func_020900f4, ExchangeBlock_Drifts)

/* func_02090100 */
void ExchangeBlock_ClearDrifts(ExchangeBlock *block)
{
    block->drifts = 0;
}
CLEAN_AS(func_02090100, ExchangeBlock_ClearDrifts)

/* func_0209010c: one drift more, up to 5. */
void ExchangeBlock_AddDrift(ExchangeBlock *block)
{
    int drifts = block->drifts + 1;
    if (drifts > EXCHANGE_BLOCK_MAX_DRIFTS) {
        drifts = EXCHANGE_BLOCK_MAX_DRIFTS;
    }
    block->drifts = (u8) drifts;
}
CLEAN_AS(func_0209010c, ExchangeBlock_AddDrift)

/* func_02090124 */
int ExchangeBlock_PairedTown(ExchangeBlock *block)
{
    return (int) (uintptr_t) block->paired_town;
}
CLEAN_AS(func_02090124, ExchangeBlock_PairedTown)

/* func_02090130: 1 when the bottle arrives at once, else 0. */
int ExchangeBlock_ArrivesAtOnce(ExchangeBlock *block)
{
    return block->flags & EXCHANGE_BLOCK_ARRIVES_AT_ONCE;
}
CLEAN_AS(func_02090130, ExchangeBlock_ArrivesAtOnce)

/* func_02090140: the flag set from bit 0 of `value`; the other bits of the byte kept. */
void ExchangeBlock_SetArrivesAtOnce(ExchangeBlock *block, unsigned int value)
{
    block->flags = (u8) ((block->flags & ~EXCHANGE_BLOCK_ARRIVES_AT_ONCE) | (value & EXCHANGE_BLOCK_ARRIVES_AT_ONCE));
}
CLEAN_AS(func_02090140, ExchangeBlock_SetArrivesAtOnce)

/* func_02090158: whether the block may be sent: always. */
int ExchangeBlock_IsSendable(ExchangeBlock *block)
{
    (void) block;
    return 1;
}
CLEAN_AS(func_02090158, ExchangeBlock_IsSendable)

/* func_0209015c */
u16 ExchangeBlock_Checksum(ExchangeBlock *block)
{
    return block->checksum;
}
CLEAN_AS(func_0209015c, ExchangeBlock_Checksum)

/* func_02090168 */
void ExchangeBlock_SetChecksum(ExchangeBlock *block, u16 checksum)
{
    block->checksum = checksum;
}
CLEAN_AS(func_02090168, ExchangeBlock_SetChecksum)
