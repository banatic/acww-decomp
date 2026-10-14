/* A word of global flags, set, cleared and tested by mask, and one fixed-point value that is
 * read only while flag 4 is set. What each flag stands for is not known yet; the names give
 * their bit. */
#ifndef CLEAN_MAIN_STATE_FLAGS_H
#define CLEAN_MAIN_STATE_FLAGS_H

#include "types.h"

BOOL StateFlags_Test(u32 mask);
void StateFlags_Clear(u16 mask);
void StateFlags_Set(u16 mask);

BOOL StateFlags_Test1(void);
void StateFlags_Set1(void);
void StateFlags_Clear1(void);
BOOL StateFlags_Test2(void);
BOOL StateFlags_IsClear2(void);
BOOL StateFlags_Test4(void);
void StateFlags_Set4(void);
void StateFlags_Clear4(void);
BOOL StateFlags_Test10(void);
void StateFlags_Set10(void);
void StateFlags_Clear10(void);

fx32 StateFlags_ValueOrOne(void);
fx32 StateFlags_ValueOrZero(void);
void StateFlags_SetValue(fx32 value);
void StateFlags_Reset(void);

#endif
