/* Three small parts of the object at data_021d27ac (block_021d27ac_parts.h). */
#include "block_021d27ac_parts.h"

#include "clean.h"
#include "date_time.h"

static_assert(sizeof(Block021d27acPart20) == 4, "part 0x20");
static_assert(sizeof(DateTime) == 8, "part 0x18");

/* ---- part 0x20 */

/* func_02087e78: the halfword, signed. */
int Block021d27acPart20_Value(const Block021d27acPart20 *part)
{
    int value = part->value;
    return value >= 0x8000 ? value - 0x10000 : value;
}
CLEAN_AS(func_02087e78, Block021d27acPart20_Value)

/* func_02087e80: QUIRK: `value` truncated to 16 bits. */
void Block021d27acPart20_SetValue(Block021d27acPart20 *part, int value)
{
    part->value = (u16) value;
}
CLEAN_AS(func_02087e80, Block021d27acPart20_SetValue)

/* func_02087e84 */
int Block021d27acPart20_Kind(const Block021d27acPart20 *part)
{
    return part->kind;
}
CLEAN_AS(func_02087e84, Block021d27acPart20_Kind)

/* func_02087e88: QUIRK: `kind` truncated to 8 bits. */
void Block021d27acPart20_SetKind(Block021d27acPart20 *part, int kind)
{
    part->kind = (u8) kind;
}
CLEAN_AS(func_02087e88, Block021d27acPart20_SetKind)

/* func_02087e8c */
void Block021d27acPart20_ClearKind(Block021d27acPart20 *part)
{
    part->kind = 0;
}
CLEAN_AS(func_02087e8c, Block021d27acPart20_ClearKind)

/* func_02087e94: the constructor does nothing. */
void Block021d27acPart20_Construct(Block021d27acPart20 *part)
{
    (void) part;
}
CLEAN_AS(func_02087e94, Block021d27acPart20_Construct)

/* func_02087e98: the destructor does nothing. */
void Block021d27acPart20_Destruct(Block021d27acPart20 *part)
{
    (void) part;
}
CLEAN_AS(func_02087e98, Block021d27acPart20_Destruct)

/* ---- part 0x30 */

/* func_02087e9c: QUIRK: `value` truncated to 8 bits. */
void Block021d27acPart30_Set(u8 *part, int value)
{
    *part = (u8) value;
}
CLEAN_AS(func_02087e9c, Block021d27acPart30_Set)

/* func_02087ea0 */
int Block021d27acPart30_IsSet(const u8 *part)
{
    return *part != 0;
}
CLEAN_AS(func_02087ea0, Block021d27acPart30_IsSet)

/* func_02087eb0 */
void Block021d27acPart30_Clear(u8 *part)
{
    *part = 0;
}
CLEAN_AS(func_02087eb0, Block021d27acPart30_Clear)

/* func_02087eb8: the constructor does nothing. */
void Block021d27acPart30_Construct(u8 *part)
{
    (void) part;
}
CLEAN_AS(func_02087eb8, Block021d27acPart30_Construct)

/* func_02087ebc: the destructor does nothing. */
void Block021d27acPart30_Destruct(u8 *part)
{
    (void) part;
}
CLEAN_AS(func_02087ebc, Block021d27acPart30_Destruct)

/* ---- part 0x18 */

/* func_02087ec0: whether the time is before now, comparing every field from the year to the
 * second. */
int Block021d27acPart18_HasPassed(const DateTime *part)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return DateTime_Compare(part, &now,
                            DATE_TIME_SECOND | DATE_TIME_MINUTE | DATE_TIME_HOUR | DATE_TIME_DAY | DATE_TIME_MONTH |
                                DATE_TIME_YEAR) == -1;
}
CLEAN_AS(func_02087ec0, Block021d27acPart18_HasPassed)

/* func_02087ef0: today at 23:00:00 (the hour, minute and second written in that order). */
void Block021d27acPart18_SetToday(DateTime *part)
{
    DateTime_Now(part);
    part->hour = BLOCK_021D27AC_PART18_HOUR;
    part->minute = 0;
    part->second = 0;
}
CLEAN_AS(func_02087ef0, Block021d27acPart18_SetToday)

/* func_02087f08 */
DateTime *Block021d27acPart18_Get(DateTime *part)
{
    return part;
}
CLEAN_AS(func_02087f08, Block021d27acPart18_Get)

/* func_02087f0c: both words cleared. */
void Block021d27acPart18_Clear(DateTime *part)
{
    *part = (DateTime){0};
}
CLEAN_AS(func_02087f0c, Block021d27acPart18_Clear)

/* func_02087f14: the constructor does nothing. */
void Block021d27acPart18_Construct(DateTime *part)
{
    (void) part;
}
CLEAN_AS(func_02087f14, Block021d27acPart18_Construct)

/* func_02087f18: the destructor clears it, as Block021d27acPart18_Clear. */
void Block021d27acPart18_Destruct(DateTime *part)
{
    *part = (DateTime){0};
}
CLEAN_AS(func_02087f18, Block021d27acPart18_Destruct)
