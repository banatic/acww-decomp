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

/* The modes the functions below open group 9 in. */
#define GROUP_PARAMS_MODE_LETTER 0x25      /* GroupParams_OpenLetter */
#define GROUP_PARAMS_MODE_ITEM_29 0x29     /* GroupParams_OpenWithItem29 */
#define GROUP_PARAMS_MODE_ITEM_2A 0x2a     /* GroupParams_OpenWithItem2a */
#define GROUP_PARAMS_MODE_ITEM_2B 0x2b     /* GroupParams_OpenWithItem2b */
#define GROUP_PARAMS_MODE_ITEM_OBJECT 0x2c /* GroupParams_OpenWithItemAndObject */
#define GROUP_PARAMS_MODE_C80_C88 0x3d     /* GroupParams_OpenWithC80C88 */

/* The entries of the byte table GroupParams_C90 reads, and the index 0xff stands for. */
#define GROUP_PARAMS_C90_ENTRIES 5
#define GROUP_PARAMS_C90_CURRENT 0xff

struct Letter;

void GroupParams_ClearTextD48(void);
void GroupParams_SetTextD48(const u16 *text);
u16 *GroupParams_TextD48(void);
void GroupParams_SetC90(int index, u8 value);
u8 GroupParams_C90(u8 index);
void GroupParams_SetC60(u8 index);
u8 GroupParams_C60(void);
void GroupParams_ResetC90(void);
BOOL GroupParams_OpenWithText(int mode, const u16 *text, int units);
u16 GroupParams_Item(void);
void GroupParams_SetItem(u16 item);
u16 GroupParams_ItemB(void);
void GroupParams_SetItemB(u16 item);
void GroupParams_SetItemC(u16 item);
u16 GroupParams_ItemC(void);
BOOL GroupParams_OpenWithItem2a(u16 item);
BOOL GroupParams_OpenWithItem29(int item);
BOOL GroupParams_OpenWithItemAndObject(int item, void *object);
BOOL GroupParams_OpenWithItem2b(int item);
int GroupParams_C88(void);
u32 *GroupParams_C80(void);
void GroupParams_ClearC80C88(void);
BOOL GroupParams_OpenWithC80C88(int c80, int c88);
void GroupParams_SetC78(int value);
int GroupParams_C78(void);
void GroupParams_SetHeldBells(int bells);
u32 GroupParams_HeldBells(void);
BOOL GroupParams_LetterFlag200(void);
BOOL GroupParams_LetterNoFlag100(void);
BOOL GroupParams_LetterFlag400(void);
u8 GroupParams_LetterBits6(void);
BOOL GroupParams_LetterFlag8(void);
int GroupParams_LetterKind(void);
void GroupParams_LetterToPockets(void);
void GroupParams_LetterToDated(void);
void GroupParams_SetLetter(const struct Letter *letter);
void GroupParams_SetLetterFlags(u16 flags);
BOOL GroupParams_OpenLetter(void);

#endif
