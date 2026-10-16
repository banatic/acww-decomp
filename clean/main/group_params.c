/* Values for the overlay groups' screens (group_params.h). */
#include "group_params.h"

#include <stdint.h>

#include "clean.h"
#include "overlay_groups.h"

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
