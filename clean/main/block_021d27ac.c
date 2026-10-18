/* The object at data_021d27ac (block_021d27ac.h). */
#include "block_021d27ac.h"

#include "calendar.h"
#include "clean.h"
#include "date_time.h"
#include "item_record.h"
#include "player_record.h"
#include "player_records.h"
#include "beside_spot.h"
#include "block_021d27ac_parts.h"
#include "event_calendar.h"
#include "middle_spot.h"
#include "near_spot.h"
#include "player_id.h"
#include "town_spot.h"

static_assert(offsetof(Block021d27ac, part_04) == 0x04 && offsetof(Block021d27ac, part_0c) == 0x0c, "parts");
static_assert(offsetof(Block021d27ac, part_18) == 0x18 && offsetof(Block021d27ac, part_20) == 0x20, "parts");
static_assert(offsetof(Block021d27ac, part_24) == 0x24 && offsetof(Block021d27ac, part_30) == 0x30, "parts");
static_assert(offsetof(Block021d27ac, part_31) == 0x31 && sizeof(Block021d27ac) == 0x34, "parts");

extern Block021d27ac data_021d27ac;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

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
    if (PlayerId_IsSet(PlayerRecord_Player(record)) == 0) {
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
    if (EventCalendar_State(BLOCK_021D27AC_EVENT_8, &copy, 0) != 0) {
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
    Block021d27acPart18_Clear((DateTime *) (void *) self->part_18);
    MI_CpuFill8(&self->flags, 0, sizeof(self->flags));
    BesideSpot_Clear(self->part_31);
    TownSpot_Clear((TownSpot *) (void *) self->part_04);
}
CLEAN_AS(func_02086130, Block021d27ac_Reset)

/* func_02086158: the destructor: the parts destroyed from the last to the first. */
Block021d27ac *Block021d27ac_Destruct(Block021d27ac *self)
{
    BesideSpot_Destruct(self->part_31);
    Block021d27acPart30_Destruct(&self->part_30);
    NearSpot_Destruct((NearSpot *) (void *) self->part_24);
    Block021d27acPart20_Destruct((Block021d27acPart20 *) (void *) self->part_20);
    Block021d27acPart18_Destruct((DateTime *) (void *) self->part_18);
    MiddleSpot_Destruct((MiddleSpot *) (void *) self->part_0c);
    TownSpot_Destruct((TownSpot *) (void *) self->part_04);
    return self;
}
CLEAN_AS(func_02086158, Block021d27ac_Destruct)

/* func_02086198: the constructor: the parts constructed from the first to the last. */
Block021d27ac *Block021d27ac_Construct(Block021d27ac *self)
{
    TownSpot_Construct((TownSpot *) (void *) self->part_04);
    MiddleSpot_Construct((MiddleSpot *) (void *) self->part_0c);
    Block021d27acPart18_Construct((DateTime *) (void *) self->part_18);
    Block021d27acPart20_Construct((Block021d27acPart20 *) (void *) self->part_20);
    NearSpot_Construct((NearSpot *) (void *) self->part_24);
    Block021d27acPart30_Construct(&self->part_30);
    BesideSpot_Construct(self->part_31);
    return self;
}
CLEAN_AS(func_02086198, Block021d27ac_Construct)
