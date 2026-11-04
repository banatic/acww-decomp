/* The count of spaceship parts 0x1568 the gull has taken (spaceship_parts.h). */
#include "spaceship_parts.h"

#include "clean.h"

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_0208716c */
void SpaceshipParts_SetMark(u8 *count)
{
    *count |= SPACESHIP_PARTS_MARK;
}
CLEAN_AS(func_0208716c, SpaceshipParts_SetMark)

/* func_02087178 */
int SpaceshipParts_HasMark(const u8 *count)
{
    return (*count & SPACESHIP_PARTS_MARK) != 0;
}
CLEAN_AS(func_02087178, SpaceshipParts_HasMark)

/* func_0208718c: one more, in three bits (7 wraps to 0; its callers stop at 5). */
void SpaceshipParts_Increment(u8 *count)
{
    *count = (u8) ((*count & ~SPACESHIP_PARTS_COUNT_MASK) | ((*count + 1) & SPACESHIP_PARTS_COUNT_MASK));
}
CLEAN_AS(func_0208718c, SpaceshipParts_Increment)

/* func_020871a8 */
int SpaceshipParts_Get(const u8 *count)
{
    return *count & SPACESHIP_PARTS_COUNT_MASK;
}
CLEAN_AS(func_020871a8, SpaceshipParts_Get)

/* func_020871b0: the town's setting up clears it. */
void SpaceshipParts_SetUp(u8 *count)
{
    SpaceshipParts_Clear(count);
}
CLEAN_AS(func_020871b0, SpaceshipParts_SetUp)

/* func_020871b8 */
void SpaceshipParts_Clear(u8 *count)
{
    MI_CpuFill8(count, 0, sizeof(*count));
}
CLEAN_AS(func_020871b8, SpaceshipParts_Clear)

/* func_020871c4: the destructor does nothing. */
void SpaceshipParts_Destruct(u8 *count)
{
    (void) count;
}
CLEAN_AS(func_020871c4, SpaceshipParts_Destruct)

/* func_020871c8: the constructor does nothing. */
void SpaceshipParts_Construct(u8 *count)
{
    (void) count;
}
CLEAN_AS(func_020871c8, SpaceshipParts_Construct)
