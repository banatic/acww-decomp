/* Global state flags. */
#include "state_flags.h"
#include "clean.h"

extern u16 data_021cfc6c;  /* the flags */
extern fx32 data_021cfc7c; /* the value read under flag 4 */

#define FLAG_1 0x01
#define FLAG_2 0x02
#define FLAG_4 0x04
#define FLAG_10 0x10

/* func_0206fec8: are all the flags in `mask` set? A mask with bits above the 16 flags never
 * is. */
BOOL StateFlags_Test(u32 mask)
{
    return (mask & data_021cfc6c) == mask;
}
CLEAN_AS(func_0206fec8, StateFlags_Test)

/* func_0206fee0 */
void StateFlags_Clear(u16 mask)
{
    data_021cfc6c &= (u16) ~mask;
}
CLEAN_AS(func_0206fee0, StateFlags_Clear)

/* func_0206fef0 */
void StateFlags_Set(u16 mask)
{
    data_021cfc6c |= mask;
}
CLEAN_AS(func_0206fef0, StateFlags_Set)

/* func_0206fea4 */
BOOL StateFlags_Test1(void)
{
    return StateFlags_Test(FLAG_1);
}
CLEAN_AS(func_0206fea4, StateFlags_Test1)

/* func_0206feb0 */
void StateFlags_Set1(void)
{
    StateFlags_Set(FLAG_1);
}
CLEAN_AS(func_0206feb0, StateFlags_Set1)

/* func_0206febc */
void StateFlags_Clear1(void)
{
    StateFlags_Clear(FLAG_1);
}
CLEAN_AS(func_0206febc, StateFlags_Clear1)

/* func_0206fe54 */
BOOL StateFlags_Test2(void)
{
    return StateFlags_Test(FLAG_2);
}
CLEAN_AS(func_0206fe54, StateFlags_Test2)

/* func_0206fe60 */
BOOL StateFlags_IsClear2(void)
{
    return !StateFlags_Test(FLAG_2);
}
CLEAN_AS(func_0206fe60, StateFlags_IsClear2)

/* func_0206fd04 */
BOOL StateFlags_Test4(void)
{
    return StateFlags_Test(FLAG_4);
}
CLEAN_AS(func_0206fd04, StateFlags_Test4)

/* func_0206fcf8 */
void StateFlags_Set4(void)
{
    StateFlags_Set(FLAG_4);
}
CLEAN_AS(func_0206fcf8, StateFlags_Set4)

/* func_0206fcec */
void StateFlags_Clear4(void)
{
    StateFlags_Clear(FLAG_4);
}
CLEAN_AS(func_0206fcec, StateFlags_Clear4)

/* func_0206fce0 */
BOOL StateFlags_Test10(void)
{
    return StateFlags_Test(FLAG_10);
}
CLEAN_AS(func_0206fce0, StateFlags_Test10)

/* func_0206fcd4 */
void StateFlags_Set10(void)
{
    StateFlags_Set(FLAG_10);
}
CLEAN_AS(func_0206fcd4, StateFlags_Set10)

/* func_0206fcc8 */
void StateFlags_Clear10(void)
{
    StateFlags_Clear(FLAG_10);
}
CLEAN_AS(func_0206fcc8, StateFlags_Clear10)

/* func_0206fd10: the value, or 1.0 while flag 4 is clear. */
fx32 StateFlags_ValueOrOne(void)
{
    return StateFlags_Test4() ? data_021cfc7c : 0x1000;
}
CLEAN_AS(func_0206fd10, StateFlags_ValueOrOne)

/* func_0206fd34: the value, or 0 while flag 4 is clear. */
fx32 StateFlags_ValueOrZero(void)
{
    return StateFlags_Test4() ? data_021cfc7c : 0;
}
CLEAN_AS(func_0206fd34, StateFlags_ValueOrZero)

/* func_0206fd54 */
void StateFlags_SetValue(u32 value)
{
    data_021cfc7c = (fx32) value;
}
CLEAN_AS(func_0206fd54, StateFlags_SetValue)

/* func_020700b8 */
void StateFlags_Reset(void)
{
    data_021cfc6c = 0;
    data_021cfc7c = 0;
}
CLEAN_AS(func_020700b8, StateFlags_Reset)
