/* The count of item 0x1568 (item_1568_count.h). */
#include "item_1568_count.h"

#include "clean.h"

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_0208716c */
void Item1568Count_SetMark(u8 *count)
{
    *count |= ITEM_1568_COUNT_MARK;
}
CLEAN_AS(func_0208716c, Item1568Count_SetMark)

/* func_02087178 */
int Item1568Count_HasMark(const u8 *count)
{
    return (*count & ITEM_1568_COUNT_MARK) != 0;
}
CLEAN_AS(func_02087178, Item1568Count_HasMark)

/* func_0208718c: one more, in three bits (7 wraps to 0; its callers stop at 5). */
void Item1568Count_Increment(u8 *count)
{
    *count = (u8) ((*count & ~ITEM_1568_COUNT_MASK) | ((*count + 1) & ITEM_1568_COUNT_MASK));
}
CLEAN_AS(func_0208718c, Item1568Count_Increment)

/* func_020871a8 */
int Item1568Count_Get(const u8 *count)
{
    return *count & ITEM_1568_COUNT_MASK;
}
CLEAN_AS(func_020871a8, Item1568Count_Get)

/* func_020871b0: the town's setting up clears it. */
void Item1568Count_SetUp(u8 *count)
{
    Item1568Count_Clear(count);
}
CLEAN_AS(func_020871b0, Item1568Count_SetUp)

/* func_020871b8 */
void Item1568Count_Clear(u8 *count)
{
    MI_CpuFill8(count, 0, sizeof(*count));
}
CLEAN_AS(func_020871b8, Item1568Count_Clear)

/* func_020871c4: the destructor does nothing. */
void Item1568Count_Destruct(u8 *count)
{
    (void) count;
}
CLEAN_AS(func_020871c4, Item1568Count_Destruct)

/* func_020871c8: the constructor does nothing. */
void Item1568Count_Construct(u8 *count)
{
    (void) count;
}
CLEAN_AS(func_020871c8, Item1568Count_Construct)
