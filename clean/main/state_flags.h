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
void StateFlags_SetValue(u32 value);
void StateFlags_Reset(void);

/* Flag 0x80 asks the open menu to close (menu_tab.c, the pockets screen); a delay, counted
 * down while it is set, holds the asking back (StateFlags_MenuCloseAsked). */
BOOL StateFlags_MenuCloseAsked(void);
void StateFlags_CountMenuCloseDelay(void);
void StateFlags_EndMenuClose(void);
void StateFlags_AskMenuClose(void);

void StateFlags_Clear200(void);
void StateFlags_Set200(void);
BOOL StateFlags_Test200(void);
BOOL StateFlags_Test100(void);
void StateFlags_Clear100(void);
void StateFlags_Set100(void);
void StateFlags_Clear8And20And40(void);
void StateFlags_Set40(void);
void StateFlags_Set20(void);
void StateFlags_Set8(void);
BOOL StateFlags_Test40(void);
BOOL StateFlags_Test20(void);
BOOL StateFlags_Test8(void);

#endif
