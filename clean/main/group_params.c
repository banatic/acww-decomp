/* Values for the overlay groups' screens (group_params.h). */
#include "group_params.h"

#include <stdint.h>

#include "calendar.h"
#include "clean.h"
#include "current_pockets.h"
#include "letter.h"
#include "mail.h"
#include "overlay_groups.h"
#include "player_record.h"
#include "player_records.h"
#include "text_string.h"

extern u8 data_021cfc5c;  /* the mode group 9 is opened in */
extern u8 data_021cfc48;  /* the argument of GroupParams_OpenWithArg */
extern u16 data_021cfc64; /* the mask of GroupParams_OpenWithMask */
extern u8 data_021cfc58;  /* and its argument */
extern u8 data_021cfc4c;
extern u8 data_021cfc50;
extern void *data_021cfc8c;                        /* the pointer group 12 is opened with */
extern u16 data_021cfd28[GROUP_PARAMS_TEXT_UNITS]; /* see GroupParams_SetText */

extern void func_02051bf8(u16 *dst, int units);                 /* clear `units` 16-bit units */
extern void func_02051c08(const u16 *src, u16 *dst, int units); /* copy them */

/* func_0206f9c0 */
u8 GroupParams_MaskArg(void)
{
    return data_021cfc58;
}
CLEAN_AS(func_0206f9c0, GroupParams_MaskArg)

/* func_0206f9cc */
u16 GroupParams_Mask(void)
{
    return data_021cfc64;
}
CLEAN_AS(func_0206f9cc, GroupParams_Mask)

/* func_0206fa28: open group 9 in mode 0x21 with a mask (func_02015688 passes a fixed one or
 * one made by Pockets_Select, a bit for each pocket slot) and a byte; TRUE when the group was
 * requested. */
BOOL GroupParams_OpenWithMask(u16 mask, u8 arg)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_MASK)) {
        return FALSE;
    }
    data_021cfc58 = arg;
    data_021cfc64 = mask;
    return TRUE;
}
CLEAN_AS(func_0206fa28, GroupParams_OpenWithMask)

/* func_0206fb9c */
u8 GroupParams_C50(void)
{
    return data_021cfc50;
}
CLEAN_AS(func_0206fb9c, GroupParams_C50)

/* func_0206fba8 */
void GroupParams_SetC50(char value)
{
    data_021cfc50 = (u8) value;
}
CLEAN_AS(func_0206fba8, GroupParams_SetC50)

/* func_0206fbb4 */
void GroupParams_ClearC50(void)
{
    data_021cfc50 = 0;
}
CLEAN_AS(func_0206fbb4, GroupParams_ClearC50)

/* func_0206fbc0: can group 9 be opened now? */
BOOL GroupParams_CanOpen(void)
{
    return OverlayGroups_IsIdle() ? TRUE : FALSE;
}
CLEAN_AS(func_0206fbc0, GroupParams_CanOpen)

/* func_0206fbd8: open group 9 in `mode` with an argument; TRUE when the group was requested. */
BOOL GroupParams_OpenWithArg(int mode, int arg)
{
    if (!GroupParams_Open(mode)) {
        return FALSE;
    }
    data_021cfc48 = (u8) arg;
    return TRUE;
}
CLEAN_AS(func_0206fbd8, GroupParams_OpenWithArg)

/* func_0206fbf8: open group 9 in `mode` (its low byte); TRUE when the group was requested.
 * Nothing changes while a group is being loaded or started. */
BOOL GroupParams_Open(int mode)
{
    if (!OverlayGroups_IsIdle()) {
        return FALSE;
    }
    data_021cfc5c = (u8) mode;
    return OverlayGroups_Request(GROUP_PARAMS_GROUP);
}
CLEAN_AS(func_0206fbf8, GroupParams_Open)

/* func_0206fc1c: clear the 16 units of the text and copy `units` of `text` into it.
 * REQUIRES: units <= 16; more would write past the text, as the original does. */
void GroupParams_SetText(const u16 *text, int units)
{
    func_02051bf8(data_021cfd28, GROUP_PARAMS_TEXT_UNITS);
    func_02051c08(text, data_021cfd28, units);
}
CLEAN_AS(func_0206fc1c, GroupParams_SetText)

/* func_0206fc44 */
u16 *GroupParams_Text(void)
{
    return data_021cfd28;
}
CLEAN_AS(func_0206fc44, GroupParams_Text)

/* func_0206fc4c */
void GroupParams_SetC4C(char value)
{
    data_021cfc4c = (u8) value;
}
CLEAN_AS(func_0206fc4c, GroupParams_SetC4C)

/* func_0206fc58 */
BOOL GroupParams_C4CIs2(void)
{
    return data_021cfc4c == 2;
}
CLEAN_AS(func_0206fc58, GroupParams_C4CIs2)

/* func_0206fc6c */
BOOL GroupParams_C4CIs1(void)
{
    return data_021cfc4c == 1;
}
CLEAN_AS(func_0206fc6c, GroupParams_C4CIs1)

/* func_0206fc80 */
void GroupParams_SetArg(u8 arg)
{
    data_021cfc48 = arg;
}
CLEAN_AS(func_0206fc80, GroupParams_SetArg)

/* func_0206fc8c */
u8 GroupParams_Arg(void)
{
    return data_021cfc48;
}
CLEAN_AS(func_0206fc8c, GroupParams_Arg)

/* func_0206fc98 */
void GroupParams_SetMode(char mode)
{
    data_021cfc5c = (u8) mode;
}
CLEAN_AS(func_0206fc98, GroupParams_SetMode)

/* func_0206fca4 */
u8 GroupParams_Mode(void)
{
    return data_021cfc5c;
}
CLEAN_AS(func_0206fca4, GroupParams_Mode)

/* func_0206fcb0: the pointer as an address. */
void GroupParams_SetPointer(u32 pointer)
{
    data_021cfc8c = (void *) (uintptr_t) pointer;
}
CLEAN_AS(func_0206fcb0, GroupParams_SetPointer)

/* func_0206fcbc */
void *GroupParams_Pointer(void)
{
    return data_021cfc8c;
}
CLEAN_AS(func_0206fcbc, GroupParams_Pointer)

/* func_0206ffe8: open group 12 with a pointer; TRUE when the group was requested. */
BOOL GroupParams_OpenGroup12(void *pointer)
{
    if (!OverlayGroups_Request(GROUP_PARAMS_GROUP_12)) {
        return FALSE;
    }
    GroupParams_SetPointer((u32) (uintptr_t) pointer);
    return TRUE;
}
CLEAN_AS(func_0206ffe8, GroupParams_OpenGroup12)

/* The values below, by their address where nothing better is known. */
extern u16 data_021cfd48[GROUP_PARAMS_TEXT_UNITS]; /* a second text of 16 units */
extern u8 data_021cfc60;                           /* the index GroupParams_C90 reads for 0xff */
extern u8 data_021cfc90[GROUP_PARAMS_C90_ENTRIES];
extern u16 data_021cfc70; /* the item given to group 9 (or chosen in its menu) */
extern u32 data_021cfc80; /* a value or an object's address given to group 9 */
extern s32 data_021cfc88;
extern s32 data_021cfc78;
extern u32 data_021cfc74;      /* the bells held on the pockets screen's cursor */
extern u16 data_021cfc68;      /* the letter screen's result flags */
extern Letter data_021cfd68;   /* the letter of the letter screen (mode 0x25) */
extern DateTime data_021cfc98; /* the date and time the game keeps (global_021cfc98.h) */

/* The letter screen's result flags (data_021cfc68). */
#define LETTER_KIND_1 0x0001
#define LETTER_KIND_2 0x0002
#define LETTER_FLAG_8 0x0008
#define LETTER_BITS_6_SHIFT 6
#define LETTER_BITS_6_MASK 3
#define LETTER_FLAG_100 0x0100
#define LETTER_FLAG_200 0x0200
#define LETTER_FLAG_400 0x0400
#define LETTER_KIND_3 0x0800

/* func_0206f4e4 */
void GroupParams_ClearTextD48(void)
{
    TextString_ClearChars(data_021cfd48, GROUP_PARAMS_TEXT_UNITS);
}
CLEAN_AS(func_0206f4e4, GroupParams_ClearTextD48)

/* func_0206f4f4: the 16 units of `text` copied in. */
void GroupParams_SetTextD48(const u16 *text)
{
    TextString_CopyChars(text, data_021cfd48, GROUP_PARAMS_TEXT_UNITS);
}
CLEAN_AS(func_0206f4f4, GroupParams_SetTextD48)

/* func_0206f504 */
u16 *GroupParams_TextD48(void)
{
    return data_021cfd48;
}
CLEAN_AS(func_0206f504, GroupParams_TextD48)

/* func_0206f5d8: entry `index` of the table set.
 * REQUIRES: 0 <= index < 5 (overlay 95's states); others write past the table, as the
 * original does. */
void GroupParams_SetC90(int index, u8 value)
{
    data_021cfc90[index] = value;
}
CLEAN_AS(func_0206f5d8, GroupParams_SetC90)

/* func_0206f5e4: entry `index` of the table; for 0xff, the entry GroupParams_C60 names.
 * REQUIRES: the index (or GroupParams_C60) is below 5; others read past the table, as the
 * original does. */
u8 GroupParams_C90(u8 index)
{
    if (index == GROUP_PARAMS_C90_CURRENT) {
        index = data_021cfc60;
    }
    return data_021cfc90[index];
}
CLEAN_AS(func_0206f5e4, GroupParams_C90)

/* func_0206f5fc */
void GroupParams_SetC60(u8 index)
{
    data_021cfc60 = index;
}
CLEAN_AS(func_0206f5fc, GroupParams_SetC60)

/* func_0206f608 */
u8 GroupParams_C60(void)
{
    return data_021cfc60;
}
CLEAN_AS(func_0206f608, GroupParams_C60)

/* func_0206f614: the table back to 0, 2, 6, 7, 8 with entry 4 named for 0xff, and the second
 * text cleared (a new game, StateBlock). */
void GroupParams_ResetC90(void)
{
    data_021cfc60 = 4;
    data_021cfc90[0] = 0;
    data_021cfc90[1] = 2;
    data_021cfc90[2] = 6;
    data_021cfc90[3] = 7;
    data_021cfc90[4] = 8;
    GroupParams_ClearTextD48();
}
CLEAN_AS(func_0206f614, GroupParams_ResetC90)

/* func_0206f640: open group 9 in `mode` with `units` of `text` as its text
 * (GroupParams_SetText); TRUE when the group was requested. */
BOOL GroupParams_OpenWithText(int mode, const u16 *text, int units)
{
    if (!GroupParams_Open(mode)) {
        return FALSE;
    }
    GroupParams_SetText(text, units);
    return TRUE;
}
CLEAN_AS(func_0206f640, GroupParams_OpenWithText)

/* func_0206f668 (as are GroupParams_ItemB and GroupParams_ItemC, separate functions of the
 * game) */
u16 GroupParams_Item(void)
{
    return data_021cfc70;
}
CLEAN_AS(func_0206f668, GroupParams_Item)

/* func_0206f674 */
void GroupParams_SetItem(u16 item)
{
    data_021cfc70 = item;
}
CLEAN_AS(func_0206f674, GroupParams_SetItem)

/* func_0206f680 */
u16 GroupParams_ItemB(void)
{
    return data_021cfc70;
}
CLEAN_AS(func_0206f680, GroupParams_ItemB)

/* func_0206f68c */
void GroupParams_SetItemB(u16 item)
{
    data_021cfc70 = item;
}
CLEAN_AS(func_0206f68c, GroupParams_SetItemB)

/* func_0206f698 */
void GroupParams_SetItemC(u16 item)
{
    data_021cfc70 = item;
}
CLEAN_AS(func_0206f698, GroupParams_SetItemC)

/* func_0206f6a4 */
u16 GroupParams_ItemC(void)
{
    return data_021cfc70;
}
CLEAN_AS(func_0206f6a4, GroupParams_ItemC)

/* func_0206f6b0: open group 9 in mode 0x2a with an item; TRUE when the group was requested. */
BOOL GroupParams_OpenWithItem2a(u16 item)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_ITEM_2A)) {
        return FALSE;
    }
    data_021cfc70 = item;
    return TRUE;
}
CLEAN_AS(func_0206f6b0, GroupParams_OpenWithItem2a)

/* func_0206f6d4: open group 9 in mode 0x29 with an item (its low 16 bits); TRUE when the
 * group was requested. */
BOOL GroupParams_OpenWithItem29(int item)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_ITEM_29)) {
        return FALSE;
    }
    data_021cfc70 = (u16) item;
    return TRUE;
}
CLEAN_AS(func_0206f6d4, GroupParams_OpenWithItem29)

/* func_0206f6f8: open group 9 in mode 0x2c with an item (its low 16 bits) and an object (the
 * fishing rod passes its hooked fish); TRUE when the group was requested. */
BOOL GroupParams_OpenWithItemAndObject(int item, void *object)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_ITEM_OBJECT)) {
        return FALSE;
    }
    data_021cfc80 = (u32) (uintptr_t) object;
    data_021cfc70 = (u16) item;
    return TRUE;
}
CLEAN_AS(func_0206f6f8, GroupParams_OpenWithItemAndObject)

/* func_0206f728: open group 9 in mode 0x2b with an item (its low 16 bits); TRUE when the
 * group was requested. */
BOOL GroupParams_OpenWithItem2b(int item)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_ITEM_2B)) {
        return FALSE;
    }
    data_021cfc70 = (u16) item;
    return TRUE;
}
CLEAN_AS(func_0206f728, GroupParams_OpenWithItem2b)

/* func_0206f7b0 */
int GroupParams_C88(void)
{
    return data_021cfc88;
}
CLEAN_AS(func_0206f7b0, GroupParams_C88)

/* func_0206f7bc: the value at data_021cfc80, as an address. */
u32 *GroupParams_C80(void)
{
    return (u32 *) (uintptr_t) data_021cfc80;
}
CLEAN_AS(func_0206f7bc, GroupParams_C80)

/* func_0206f7c8 */
void GroupParams_ClearC80C88(void)
{
    data_021cfc80 = 0;
    data_021cfc88 = 0;
}
CLEAN_AS(func_0206f7c8, GroupParams_ClearC80C88)

/* func_0206f7dc: open group 9 in mode 0x3d with two values; TRUE when the group was
 * requested. */
BOOL GroupParams_OpenWithC80C88(int c80, int c88)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_C80_C88)) {
        return FALSE;
    }
    data_021cfc80 = (u32) c80;
    data_021cfc88 = c88;
    return TRUE;
}
CLEAN_AS(func_0206f7dc, GroupParams_OpenWithC80C88)

/* func_0206f830 */
void GroupParams_SetC78(int value)
{
    data_021cfc78 = value;
}
CLEAN_AS(func_0206f830, GroupParams_SetC78)

/* func_0206f83c */
int GroupParams_C78(void)
{
    return data_021cfc78;
}
CLEAN_AS(func_0206f83c, GroupParams_C78)

/* func_0206f848: the bells held on the pockets screen's cursor set (overlay 96). */
void GroupParams_SetHeldBells(int bells)
{
    data_021cfc74 = (u32) bells;
}
CLEAN_AS(func_0206f848, GroupParams_SetHeldBells)

/* func_0206f854: the bells held on the pockets screen's cursor (the bells panel adds them). */
u32 GroupParams_HeldBells(void)
{
    return data_021cfc74;
}
CLEAN_AS(func_0206f854, GroupParams_HeldBells)

/* func_0206f860 */
BOOL GroupParams_LetterFlag200(void)
{
    return (data_021cfc68 & LETTER_FLAG_200) != 0;
}
CLEAN_AS(func_0206f860, GroupParams_LetterFlag200)

/* func_0206f87c: whether flag 0x100 is clear. */
BOOL GroupParams_LetterNoFlag100(void)
{
    return (data_021cfc68 & LETTER_FLAG_100) == 0;
}
CLEAN_AS(func_0206f87c, GroupParams_LetterNoFlag100)

/* func_0206f898 */
BOOL GroupParams_LetterFlag400(void)
{
    return (data_021cfc68 & LETTER_FLAG_400) != 0;
}
CLEAN_AS(func_0206f898, GroupParams_LetterFlag400)

/* func_0206f8b4: bits 6 and 7 of the flags, 0 to 3. */
u8 GroupParams_LetterBits6(void)
{
    return (u8) ((data_021cfc68 >> LETTER_BITS_6_SHIFT) & LETTER_BITS_6_MASK);
}
CLEAN_AS(func_0206f8b4, GroupParams_LetterBits6)

/* func_0206f8c8 */
BOOL GroupParams_LetterFlag8(void)
{
    return (data_021cfc68 & LETTER_FLAG_8) != 0;
}
CLEAN_AS(func_0206f8c8, GroupParams_LetterFlag8)

/* func_0206f8e0: 2 for flag 2, else 1 for flag 1, else 3 for flag 0x800, else 0. */
int GroupParams_LetterKind(void)
{
    u16 flags = data_021cfc68;
    if (flags & LETTER_KIND_2) {
        return 2;
    }
    if (flags & LETTER_KIND_1) {
        return 1;
    }
    if (flags & LETTER_KIND_3) {
        return 3;
    }
    return 0;
}
CLEAN_AS(func_0206f8e0, GroupParams_LetterKind)

/* func_0206f910: the letter copied into the first free letter of the current pockets, if
 * there is one. */
void GroupParams_LetterToPockets(void)
{
    MailLetter *free_letter = CurrentPockets_FreeLetter();
    if (free_letter != NULL) {
        Letter_Assign((Letter *) (void *) free_letter, &data_021cfd68);
    }
}
CLEAN_AS(func_0206f910, GroupParams_LetterToPockets)

/* func_0206f92c: the letter made the current player's dated letter, marked written, and dated
 * with the day, month and year of the kept date (data_021cfc98) at hour 0. The date is first
 * set to day 1 of month 1 of year 0, then given the kept day, month and year. */
void GroupParams_LetterToDated(void)
{
    u8 *player = PlayerRecords_Current();
    MailLetter *letter = MailDated_Letter((MailDatedLetter *) (void *) PlayerRecord_DatedLetter(player));
    Letter_Assign((Letter *) (void *) letter, &data_021cfd68);
    Letter_AdvanceWritten((Letter *) (void *) letter);
    MailTime *date = MailDated_Date((MailDatedLetter *) (void *) PlayerRecord_DatedLetter(player));
    date->day = 1;
    date->month = 1;
    date->year = 0;
    date->hour = 0;
    date->day = data_021cfc98.day;
    date->month = data_021cfc98.month;
    date->year = data_021cfc98.year;
}
CLEAN_AS(func_0206f92c, GroupParams_LetterToDated)

/* func_0206f980: `letter` copied in as the letter. */
void GroupParams_SetLetter(const Letter *letter)
{
    Letter_Assign(&data_021cfd68, letter);
}
CLEAN_AS(func_0206f980, GroupParams_SetLetter)

/* func_0206f990 */
void GroupParams_SetLetterFlags(u16 flags)
{
    data_021cfc68 = flags;
}
CLEAN_AS(func_0206f990, GroupParams_SetLetterFlags)

/* func_0206f99c: open group 9 in mode 0x25, the letter screen, with its flags cleared; TRUE
 * when the group was requested. */
BOOL GroupParams_OpenLetter(void)
{
    if (!GroupParams_Open(GROUP_PARAMS_MODE_LETTER)) {
        return FALSE;
    }
    data_021cfc68 = 0;
    return TRUE;
}
CLEAN_AS(func_0206f99c, GroupParams_OpenLetter)
