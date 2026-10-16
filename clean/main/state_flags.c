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

#define FLAG_8 0x08
#define FLAG_20 0x20
#define FLAG_40 0x40
#define FLAG_MENU_CLOSE 0x80
#define FLAG_100 0x100
#define FLAG_200 0x200

/* The frames StateFlags_EndMenuClose leaves before the next ask is answered. */
#define MENU_CLOSE_DELAY 0x37

extern u8 data_021cfc54; /* the menu close delay, counted down while flag 0x80 is set */

/* func_0206f50c */
void StateFlags_Clear200(void)
{
    StateFlags_Clear(FLAG_200);
}
CLEAN_AS(func_0206f50c, StateFlags_Clear200)

/* func_0206f51c */
void StateFlags_Set200(void)
{
    StateFlags_Set(FLAG_200);
}
CLEAN_AS(func_0206f51c, StateFlags_Set200)

/* func_0206f52c */
BOOL StateFlags_Test200(void)
{
    return StateFlags_Test(FLAG_200);
}
CLEAN_AS(func_0206f52c, StateFlags_Test200)

/* func_0206f53c */
BOOL StateFlags_Test100(void)
{
    return StateFlags_Test(FLAG_100);
}
CLEAN_AS(func_0206f53c, StateFlags_Test100)

/* func_0206f54c */
void StateFlags_Clear100(void)
{
    StateFlags_Clear(FLAG_100);
}
CLEAN_AS(func_0206f54c, StateFlags_Clear100)

/* func_0206f55c */
void StateFlags_Set100(void)
{
    StateFlags_Set(FLAG_100);
}
CLEAN_AS(func_0206f55c, StateFlags_Set100)

/* func_0206f56c: whether the menu is asked to close: flag 0x80 set once the delay is over.
 * The flag is not looked at while the delay runs. */
BOOL StateFlags_MenuCloseAsked(void)
{
    if (data_021cfc54 != 0) {
        return FALSE;
    }
    return StateFlags_Test(FLAG_MENU_CLOSE);
}
CLEAN_AS(func_0206f56c, StateFlags_MenuCloseAsked)

/* func_0206f58c: the delay counted down by one while flag 0x80 is set (each frame of the
 * screens that answer the ask). */
void StateFlags_CountMenuCloseDelay(void)
{
    if (StateFlags_Test(FLAG_MENU_CLOSE) && data_021cfc54 != 0) {
        data_021cfc54--;
    }
}
CLEAN_AS(func_0206f58c, StateFlags_CountMenuCloseDelay)

/* func_0206f5b0: the ask withdrawn, and the next one held back by the delay. */
void StateFlags_EndMenuClose(void)
{
    StateFlags_Clear(FLAG_MENU_CLOSE);
    data_021cfc54 = MENU_CLOSE_DELAY;
}
CLEAN_AS(func_0206f5b0, StateFlags_EndMenuClose)

/* func_0206f5cc */
void StateFlags_AskMenuClose(void)
{
    StateFlags_Set(FLAG_MENU_CLOSE);
}
CLEAN_AS(func_0206f5cc, StateFlags_AskMenuClose)

/* func_0206f74c: flags 8, 0x20 and 0x40 cleared, one at a time. */
void StateFlags_Clear8And20And40(void)
{
    StateFlags_Clear(FLAG_8);
    StateFlags_Clear(FLAG_20);
    StateFlags_Clear(FLAG_40);
}
CLEAN_AS(func_0206f74c, StateFlags_Clear8And20And40)

/* func_0206f768 */
void StateFlags_Set40(void)
{
    StateFlags_Set(FLAG_40);
}
CLEAN_AS(func_0206f768, StateFlags_Set40)

/* func_0206f774 */
void StateFlags_Set20(void)
{
    StateFlags_Set(FLAG_20);
}
CLEAN_AS(func_0206f774, StateFlags_Set20)

/* func_0206f780 */
void StateFlags_Set8(void)
{
    StateFlags_Set(FLAG_8);
}
CLEAN_AS(func_0206f780, StateFlags_Set8)

/* func_0206f78c */
BOOL StateFlags_Test40(void)
{
    return StateFlags_Test(FLAG_40);
}
CLEAN_AS(func_0206f78c, StateFlags_Test40)

/* func_0206f798: tested with flag 8 by the turnip prices and the savings (no interest). */
BOOL StateFlags_Test20(void)
{
    return StateFlags_Test(FLAG_20);
}
CLEAN_AS(func_0206f798, StateFlags_Test20)

/* func_0206f7a4 */
BOOL StateFlags_Test8(void)
{
    return StateFlags_Test(FLAG_8);
}
CLEAN_AS(func_0206f7a4, StateFlags_Test8)
