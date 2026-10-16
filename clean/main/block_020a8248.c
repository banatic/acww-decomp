/* The 12-byte record (block_020a8248.h). */
#include "block_020a8248.h"

#include "clean.h"

static_assert(offsetof(Block020a8248, kind) == 0x04, "kind");
static_assert(sizeof(Block020a8248) == 0x0c, "record");

#define BLOCK_020A8248_SIZE 0x0c

/* Per kind: 0 or 1 (func_0206741c tests for 1). */
extern const s32 data_020d1d0c[];
/* Per kind: 0, 1 or 2 (func_0206741c hands it to NNS_G2dSetRndCore3DSoftSpriteZvalue). */
extern void *const data_020d1ca8[];
/* Per kind: 0 to 6, rising with the kind. */
extern const s32 data_020d1c44[];

extern void MI_CpuFill8(void *dst, int value, unsigned int size);

/* func_020a8248 */
int Block020a8248_FlagOfKind(Block020a8248 *record)
{
    return data_020d1d0c[Block020a8248_Kind(record)];
}
CLEAN_AS(func_020a8248, Block020a8248_FlagOfKind)

/* func_020a8260 */
void *Block020a8248_ValueOfKind(Block020a8248 *record)
{
    return data_020d1ca8[Block020a8248_Kind(record)];
}
CLEAN_AS(func_020a8260, Block020a8248_ValueOfKind)

/* func_020a8278 */
int Block020a8248_GroupOfKind(Block020a8248 *record)
{
    return data_020d1c44[Block020a8248_Kind(record)];
}
CLEAN_AS(func_020a8278, Block020a8248_GroupOfKind)

/* func_020a8290 */
void Block020a8248_GetByte08(u8 *out, Block020a8248 *record)
{
    *out = record->unk_08;
}
CLEAN_AS(func_020a8290, Block020a8248_GetByte08)

/* func_020a8298 */
int Block020a8248_Byte09(Block020a8248 *record)
{
    return record->unk_09;
}
CLEAN_AS(func_020a8298, Block020a8248_Byte09)

/* func_020a829c */
int Block020a8248_Byte07(Block020a8248 *record)
{
    return record->unk_07;
}
CLEAN_AS(func_020a829c, Block020a8248_Byte07)

/* func_020a82a0 */
int Block020a8248_Byte06(Block020a8248 *record)
{
    return record->unk_06;
}
CLEAN_AS(func_020a82a0, Block020a8248_Byte06)

/* func_020a82a4 */
int Block020a8248_Byte05(Block020a8248 *record)
{
    return record->unk_05;
}
CLEAN_AS(func_020a82a4, Block020a8248_Byte05)

/* func_020a82a8 */
int Block020a8248_Kind(Block020a8248 *record)
{
    return record->kind;
}
CLEAN_AS(func_020a82a8, Block020a8248_Kind)

/* func_020a82ac: the record itself (a getter of an owner whose record is its start). */
void *Block020a8248_Self(void *record)
{
    return record;
}
CLEAN_AS(func_020a82ac, Block020a8248_Self)

/* func_020a82b0: every byte 0. */
void Block020a8248_Clear(Block020a8248 *record)
{
    MI_CpuFill8(record, 0, BLOCK_020A8248_SIZE);
}
CLEAN_AS(func_020a82b0, Block020a8248_Clear)

/* func_020a82bc: `src` copied to `dst`: the word, then the bytes one by one in order (which
 * decides the result when the two overlap). */
void Block020a8248_Copy(void *dst, const void *src)
{
    Block020a8248 *to = dst;
    const Block020a8248 *from = src;
    to->unk_00 = from->unk_00;
    to->kind = from->kind;
    to->unk_05 = from->unk_05;
    to->unk_06 = from->unk_06;
    to->unk_07 = from->unk_07;
    to->unk_08 = from->unk_08;
    to->unk_09 = from->unk_09;
    to->unk_0a = from->unk_0a;
    to->unk_0b = from->unk_0b;
}
CLEAN_AS(func_020a82bc, Block020a8248_Copy)

/* func_020a82e4: the destructor; nothing to do. */
void Block020a8248_Destruct(void *record)
{
    (void) record;
}
CLEAN_AS(func_020a82e4, Block020a8248_Destruct)

/* func_020a82e8: the constructor; a cleared record. */
Block020a8248 *Block020a8248_Construct(Block020a8248 *record)
{
    Block020a8248_Clear(record);
    return record;
}
CLEAN_AS(func_020a82e8, Block020a8248_Construct)
