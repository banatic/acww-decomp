/* The object at data_021d27ac (block_021d27ac.h). */
#include "block_021d27ac.h"

#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "item_record.h"
#include "player_record.h"
#include "player_records.h"

static_assert(offsetof(Block021d27ac, part_04) == 0x04 && offsetof(Block021d27ac, part_0c) == 0x0c, "parts");
static_assert(offsetof(Block021d27ac, part_18) == 0x18 && offsetof(Block021d27ac, part_20) == 0x20, "parts");
static_assert(offsetof(Block021d27ac, part_24) == 0x24 && offsetof(Block021d27ac, part_30) == 0x30, "parts");
static_assert(offsetof(Block021d27ac, part_31) == 0x31 && sizeof(Block021d27ac) == 0x34, "parts");

extern Block021d27ac data_021d27ac;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* Whether `event` is on at `when` (`arg` 0). */
extern int func_0203fc78(int event, const DateTime *when, int arg);
/* Whether a player's name is set. */
extern int func_020951bc(const void *player);

/* The parts' own functions: reset, construct and destroy. */
extern void func_02087f0c(u8 *part);
extern void func_02087b78(u8 *part);
extern void func_02087a64(u8 *part);
extern void func_02087b84(u8 *part);
extern void func_02087eb8(u8 *part);
extern void func_02087e70(u8 *part);
extern void func_02087e94(u8 *part);
extern void func_02087f14(u8 *part);
extern void func_020881a4(u8 *part);
extern void func_02087a70(u8 *part);
extern void func_02087a74(u8 *part);
extern void func_020881a8(u8 *part);
extern void func_02087f18(u8 *part);
extern void func_02087e98(u8 *part);
extern void func_02087e74(u8 *part);
extern void func_02087ebc(u8 *part);
extern void func_02087b88(u8 *part);

/* The player record's flags Block021d27ac_NoteCollections reads (PlayerRecord_TestFlag). */
#define BLOCK_021D27AC_PLAYER_FLAG_1 1
#define BLOCK_021D27AC_PLAYER_FLAG_21 0x21 /* read with the fish */
#define BLOCK_021D27AC_PLAYER_FLAG_22 0x22 /* read with the insects */
#define BLOCK_021D27AC_EVENT_8 8           /* func_0203fc78's event */

/* The part at `offset`, computed from the address only. */
static u8 *block_021d27ac_part(Block021d27ac *self, size_t offset)
{
    return (u8 *) (uintptr_t) ((uintptr_t) self + offset);
}

/* func_0208602c */
Block021d27ac *Block021d27ac_Get(void)
{
    return &data_021d27ac;
}
CLEAN_AS(func_0208602c, Block021d27ac_Get)

/* func_02086034: flag 8 set when the current player has a name (func_020951bc), lacks player
 * flag 1, and has every fish without player flag 0x21 or every insect without player flag
 * 0x22, while event 8 is not on now. */
void Block021d27ac_NoteCollections(Block021d27ac *self)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return;
    }
    if (func_020951bc(PlayerRecord_Player(record)) == 0) {
        return;
    }
    if (PlayerRecord_TestFlag(record, BLOCK_021D27AC_PLAYER_FLAG_1) != 0) {
        return;
    }
    if (PlayerRecord_TestFlag(record, BLOCK_021D27AC_PLAYER_FLAG_21) != 0 || ItemRecord_HasAllFish() == 0) {
        if (PlayerRecord_TestFlag(record, BLOCK_021D27AC_PLAYER_FLAG_22) != 0 || ItemRecord_HasAllInsects() == 0) {
            return;
        }
    }
    DateTime now = {0};
    DateTime copy;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &copy, sizeof(copy));
    if (func_0203fc78(BLOCK_021D27AC_EVENT_8, &copy, 0) != 0) {
        return;
    }
    Block021d27ac_SetFlag(&self->flags, BLOCK_021D27AC_FLAG_8);
}
CLEAN_AS(func_02086034, Block021d27ac_NoteCollections)

/* func_020860b8 */
u8 *Block021d27ac_Part04(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_04));
}
CLEAN_AS(func_020860b8, Block021d27ac_Part04)

/* func_020860bc */
u8 *Block021d27ac_Part31(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_31));
}
CLEAN_AS(func_020860bc, Block021d27ac_Part31)

/* func_020860c0 */
u8 *Block021d27ac_Part24(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_24));
}
CLEAN_AS(func_020860c0, Block021d27ac_Part24)

/* func_020860c4 */
u8 *Block021d27ac_Part0C(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_0c));
}
CLEAN_AS(func_020860c4, Block021d27ac_Part0C)

/* func_020860c8 */
u8 *Block021d27ac_Part30(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_30));
}
CLEAN_AS(func_020860c8, Block021d27ac_Part30)

/* func_020860cc */
u8 *Block021d27ac_Part20(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_20));
}
CLEAN_AS(func_020860cc, Block021d27ac_Part20)

/* func_020860d0 */
u8 *Block021d27ac_Part18(Block021d27ac *self)
{
    return block_021d27ac_part(self, offsetof(Block021d27ac, part_18));
}
CLEAN_AS(func_020860d0, Block021d27ac_Part18)

/* func_020860d4 */
void Block021d27ac_ClearFlag(u32 *flags, u32 flag)
{
    if (flag < BLOCK_021D27AC_FLAGS) {
        *flags &= ~(1u << flag);
    }
}
CLEAN_AS(func_020860d4, Block021d27ac_ClearFlag)

/* func_020860f0 */
void Block021d27ac_SetFlag(u32 *flags, u32 flag)
{
    if (flag < BLOCK_021D27AC_FLAGS) {
        *flags |= 1u << flag;
    }
}
CLEAN_AS(func_020860f0, Block021d27ac_SetFlag)

/* func_02086108 */
int Block021d27ac_TestFlag(u32 *flags, u32 flag)
{
    return flag < BLOCK_021D27AC_FLAGS && (*flags & (1u << flag)) != 0;
}
CLEAN_AS(func_02086108, Block021d27ac_TestFlag)

/* func_02086130: part 0x18 reset, the flags cleared, then parts 0x31 and 0x04 reset. */
void Block021d27ac_Reset(Block021d27ac *self)
{
    func_02087f0c(self->part_18);
    MI_CpuFill8(&self->flags, 0, sizeof(self->flags));
    func_02087b78(self->part_31);
    func_02087a64(self->part_04);
}
CLEAN_AS(func_02086130, Block021d27ac_Reset)

/* func_02086158: the constructor: the parts constructed from the last to the first. */
Block021d27ac *Block021d27ac_Construct(Block021d27ac *self)
{
    func_02087b84(self->part_31);
    func_02087eb8(&self->part_30);
    func_02087e70(self->part_24);
    func_02087e94(self->part_20);
    func_02087f14(self->part_18);
    func_020881a4(self->part_0c);
    func_02087a70(self->part_04);
    return self;
}
CLEAN_AS(func_02086158, Block021d27ac_Construct)

/* func_02086198: the destructor: the parts destroyed from the first to the last. */
Block021d27ac *Block021d27ac_Destruct(Block021d27ac *self)
{
    func_02087a74(self->part_04);
    func_020881a8(self->part_0c);
    func_02087f18(self->part_18);
    func_02087e98(self->part_20);
    func_02087e74(self->part_24);
    func_02087ebc(&self->part_30);
    func_02087b88(self->part_31);
    return self;
}
CLEAN_AS(func_02086198, Block021d27ac_Destruct)
