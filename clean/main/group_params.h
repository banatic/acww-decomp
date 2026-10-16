/* Values main keeps for the overlay groups' screens (overlay_groups.h): what group 9 is
 * opened for, the arguments some of its modes take, the pointer group 12 is opened with, and
 * a few bytes the screens set and read between them. What the modes and the bytes mean is not
 * known yet; they are named by their address where nothing better is. */
#ifndef CLEAN_MAIN_GROUP_PARAMS_H
#define CLEAN_MAIN_GROUP_PARAMS_H

#include "types.h"

/* The group GroupParams_Open requests, and the one GroupParams_OpenGroup12 does. */
#define GROUP_PARAMS_GROUP 9
#define GROUP_PARAMS_GROUP_12 12

/* The mode GroupParams_OpenWithMask opens group 9 in. */
#define GROUP_PARAMS_MODE_MASK 0x21

/* The number of 16-bit units GroupParams_SetText clears. */
#define GROUP_PARAMS_TEXT_UNITS 16

u8 GroupParams_MaskArg(void);
u16 GroupParams_Mask(void);
BOOL GroupParams_OpenWithMask(u16 mask, u8 arg);
u8 GroupParams_C50(void);
void GroupParams_SetC50(char value);
void GroupParams_ClearC50(void);
BOOL GroupParams_CanOpen(void);
BOOL GroupParams_OpenWithArg(int mode, int arg);
BOOL GroupParams_Open(int mode);
void GroupParams_SetText(const u16 *text, int units);
u16 *GroupParams_Text(void);
void GroupParams_SetC4C(char value);
BOOL GroupParams_C4CIs2(void);
BOOL GroupParams_C4CIs1(void);
void GroupParams_SetArg(u8 arg);
u8 GroupParams_Arg(void);
void GroupParams_SetMode(char mode);
u8 GroupParams_Mode(void);
void GroupParams_SetPointer(u32 pointer);
void *GroupParams_Pointer(void);
BOOL GroupParams_OpenGroup12(void *pointer);

#endif
