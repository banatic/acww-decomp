/* The date screen of overlay 138 (date_screen.h): its destructors, its flags, the cursor and
 * its sprite, the lists of the clock panel's fields, the frame's states and the scene's slots. */
#include "date_screen.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/global_021cfc98.h"
#include "main/group_params.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(DateScreen, return_sub_state) == 0x94, "bytes");
static_assert(offsetof(DateScreen, cursor) == 0x95 && offsetof(DateScreen, cursor_sprite) == 0x98, "cursor");
static_assert(sizeof(Glider) == 0x64 && offsetof(DateScreen, panel) == 0xfc, "panel");
static_assert(sizeof(ButtonPanel) == 0x1cc && offsetof(DateScreen, clock) == 0x2c8, "clock");
static_assert(sizeof(DateScreen) == 0x2b78, "size (func_ov138_0229d3a0)");

/* The scene's vtable. */
extern const u8 data_ov138_0229d4e0[];

/* Where the cursor goes from each place (DateScreenPlace) by the d-pad: left, right, down and
 * up; and the sprite's place at the fields (the buttons' places are the panel's). */
extern const u8 data_ov138_0229d3e4[];  /* left */
extern const u8 data_ov138_0229d3ec[];  /* right */
extern const u8 data_ov138_0229d3f4[];  /* down */
extern const u8 data_ov138_0229d3fc[];  /* up */
extern const s32 data_ov138_0229d404[]; /* x */
extern const s32 data_ov138_0229d418[]; /* y */

/* The pad, and the pen (autoload_2/input.c): down, and gone down this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */
#define DATE_SCREEN_PAD_A 0x0001
#define DATE_SCREEN_PAD_B 0x0002
#define DATE_SCREEN_PAD_START 0x0008

/* Overlay 134's clock panel (ov134/clock_panel.h), by symbol. */
extern void *func_ov134_0229beb0(void *clock); /* ClockPanel_Destroy */
extern void *func_ov134_0229bed4(void *clock); /* ClockPanel_Construct */
extern void func_ov134_0229bd38(void *clock, int mode, int base_layer, int panel_layer, int list_layer); /* Init */
extern void func_ov134_0229bd2c(void *clock);               /* sets CLOCK_PANEL_FLAG_HAS_MIN */
extern void func_ov134_0229bcf0(void *clock);               /* ClockPanel_Teardown */
extern void func_ov134_0229bcac(void *clock);               /* ClockPanel_EndFrame */
extern void func_ov134_0229bbe8(void *clock);               /* ClockPanel_Update */
extern void func_ov134_0229bbdc(void *clock, void *out);    /* ClockPanel_CopyValue */
extern int func_ov134_0229baec(void *clock);                /* ClockPanel_LoadBackground */
extern void func_ov134_0229ba10(void *clock, int title);    /* ClockPanel_DrawLabels */
extern int func_ov134_0229b954(void *clock);                /* ClockPanel_LoadSprites */
extern void func_ov134_0229b220(void *clock, int x, int y); /* ClockPanel_Draw */
extern int func_ov134_0229ab80(void *clock, int x, int y);  /* ClockPanel_TouchedField */
extern int func_ov134_0229a8a0(void *clock);                /* ClockPanel_Focus */
extern void func_ov134_0229a5c8(void *clock, int field);    /* ClockPanel_OpenList */
extern int func_ov134_0229a4e4(void *clock);                /* ClockPanel_OpenListStep */
extern void func_ov134_0229a3e4(void *clock);               /* ClockPanel_PickRow */
extern void func_ov134_0229a398(void *clock);               /* ClockPanel_CancelList */
extern int func_ov134_0229a24c(void *clock);                /* ClockPanel_CloseListStep */
extern int func_ov134_0229a1f0(void *clock, int x, int y);  /* ClockPanel_TouchList */
extern int func_ov134_02299b70(void *clock);                /* ClockPanel_PressThumbByKey */
extern void func_ov134_02299b18(void *clock, int pen_y);    /* ClockPanel_DragThumb */
extern void func_ov134_02299af0(void *clock, int pen_y);    /* ClockPanel_ThumbTowardPen */
extern void func_ov134_02299a90(void *clock);               /* ClockPanel_MoveThumbByKeys */
extern int func_ov134_02299a84(void *clock);                /* ClockPanel_ReleaseThumb */
extern int func_ov134_02299a60(void *clock);                /* ClockPanel_SettleThumb */
extern int func_ov134_022999e0(void *clock);                /* ClockPanel_CursorX */
extern int func_ov134_022999ac(void *clock);                /* ClockPanel_CursorY */
extern void func_ov134_02299980(void *clock, int y);        /* ClockPanel_CursorToY */
extern int func_ov134_022997dc(void *clock, int keys);      /* ClockPanel_ListKeys */
extern int func_ov134_022997b0(void *clock);                /* ClockPanel_PickCursorRow */

/* The clock panel's mode and layers (ClockPanel_Init), and its title (ClockPanel_DrawLabels). */
#define DATE_SCREEN_CLOCK_MODE 3
#define DATE_SCREEN_TITLE 0x6c

/* What ClockPanel_TouchList and ClockPanel_ListKeys answer (ov134/clock_panel.h). */
#define DATE_SCREEN_TOUCH_PICKED 0
#define DATE_SCREEN_TOUCH_OUTSIDE 1
#define DATE_SCREEN_TOUCH_BAR 2
#define DATE_SCREEN_TOUCH_THUMB 3
#define DATE_SCREEN_KEYS_NONE 0
#define DATE_SCREEN_KEYS_STEPPED 2
#define DATE_SCREEN_KEYS_FAST 3
#define DATE_SCREEN_NO_FIELD 6

/* The panel's buttons and the cursor sprite's animations (glide.h). */
#define DATE_SCREEN_CONFIRM_BUTTON 6
#define DATE_SCREEN_CANCEL_BUTTON 7
#define DATE_SCREEN_ANIM_FIELD 1
#define DATE_SCREEN_ANIM_BUTTON 7

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define DATE_SCREEN_PARENT_CLOSE 0x44

static MenuScene *date_scene(DateScreen *self)
{
    return &self->base;
}

static u16 *date_flags(DateScreen *self)
{
    return (u16 *) (void *) &self->base.unk_91[1];
}

static CellLayerSprite *date_sprite_cells(DateScreen *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *date_parent(DateScreen *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base),
 * with its answer. */
static int date_update_sprite(Glider *sprite)
{
    int (*const *vtable)(Glider *) = (int (*const *)(Glider *)) sprite->vtable;
    return vtable[3](sprite);
}

/* The cursor is at a button (and no list is open): the sprite takes the buttons' looks. */
static int date_at_button(DateScreen *self)
{
    return DateScreen_TestFlags(self, DATE_SCREEN_FLAG_LIST) == 0 &&
           (self->cursor == DATE_SCREEN_CONFIRM || self->cursor == DATE_SCREEN_CANCEL);
}

/* The members' destructors, last member first, then the base's. */
static void date_destroy_members(DateScreen *self)
{
    self->base.vtable = data_ov138_0229d4e0;
    func_ov134_0229beb0(self->clock);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(date_scene(self));
}

/* func_ov138_0229c4e0 (vtable slot 0x40) */
DateScreen *DateScreen_Destroy(DateScreen *self)
{
    date_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov138_0229c4e0, DateScreen_Destroy)

/* func_ov138_0229c518 (vtable slot 0x44) */
DateScreen *DateScreen_Delete(DateScreen *self)
{
    date_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov138_0229c518, DateScreen_Delete)

/* func_ov138_0229c554 */
void DateScreen_ClearFlags(DateScreen *self, u16 flags)
{
    *date_flags(self) = (u16) (*date_flags(self) & ~flags);
}
CLEAN_AS(func_ov138_0229c554, DateScreen_ClearFlags)

/* func_ov138_0229c564 */
void DateScreen_SetFlags(DateScreen *self, u16 flags)
{
    *date_flags(self) = (u16) (*date_flags(self) | flags);
}
CLEAN_AS(func_ov138_0229c564, DateScreen_SetFlags)

/* func_ov138_0229c574 */
int DateScreen_TestFlags(DateScreen *self, u16 flags)
{
    return (*date_flags(self) & flags) != 0;
}
CLEAN_AS(func_ov138_0229c574, DateScreen_TestFlags)

/* func_ov138_0229c588: the cursor moved by the d-pad keys `keys` through the tables of moves:
 * left or right first, and up or down only when that did not move it; whether it moved.
 * QUIRK: the tables have eight entries and are read at any cursor, as the game does. */
int DateScreen_MoveCursor(DateScreen *self, int keys)
{
    u8 before = self->cursor;
    if (KeyRepeat_HasLeft(keys)) {
        self->cursor = data_ov138_0229d3e4[self->cursor];
    } else if (KeyRepeat_HasRight(keys)) {
        self->cursor = data_ov138_0229d3ec[self->cursor];
    }
    if (before != self->cursor) {
        return 1;
    }
    if (KeyRepeat_HasUp(keys)) {
        self->cursor = data_ov138_0229d3fc[self->cursor];
    } else if (KeyRepeat_HasDown(keys)) {
        self->cursor = data_ov138_0229d3f4[self->cursor];
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov138_0229c588, DateScreen_MoveCursor)

/* func_ov138_0229c630: the sprite shows the third look of its set (a press let go) and the
 * scene waits for it (sub state 10) before going back to this sub state. */
void DateScreen_PressAndReturn(DateScreen *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_PRESS_RELEASE);
}
CLEAN_AS(func_ov138_0229c630, DateScreen_PressAndReturn)

/* func_ov138_0229c654: the sprite shows the second look of its set (pressed) and, once it has,
 * the press is acted on (sub state 9). */
void DateScreen_PressToAct(DateScreen *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_PRESS_ACT);
}
CLEAN_AS(func_ov138_0229c654, DateScreen_PressToAct)

/* func_ov138_0229c66c: the sprite shows the first look of its set and is updated. */
void DateScreen_ShowCursorSprite(DateScreen *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    date_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov138_0229c66c, DateScreen_ShowCursorSprite)

/* func_ov138_0229c688: the sprite eases to (x, y) with the move's sound, in two steps after a
 * step of the list's cursor (DATE_SCREEN_FLAG_QUICK, then cleared) and three otherwise, and the
 * scene waits for it
 * (sub state 8) before going back to this sub state. */
void DateScreen_GlideTo(DateScreen *self, int x, int y)
{
    if (DateScreen_TestFlags(self, DATE_SCREEN_FLAG_QUICK)) {
        Glider_EaseTo(&self->cursor_sprite, x, y, 2, 1);
    } else {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    }
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_SPRITE_MOVE);
    DateScreen_ClearFlags(self, DATE_SCREEN_FLAG_QUICK);
}
CLEAN_AS(func_ov138_0229c688, DateScreen_GlideTo)

/* func_ov138_0229c6e8: the sprite turns to the looks of where the cursor is (set A at a field
 * or in a list, set B at a button) and glides there. */
void DateScreen_GlideToCursor(DateScreen *self)
{
    if (!date_at_button(self)) {
        Glider_TurnToSetA(&self->cursor_sprite);
    } else {
        Glider_TurnToSetB(&self->cursor_sprite);
    }
    int x = DateScreen_CursorSpriteX(self);
    int y = DateScreen_CursorSpriteY(self);
    DateScreen_GlideTo(self, x, y);
}
CLEAN_AS(func_ov138_0229c6e8, DateScreen_GlideToCursor)

/* func_ov138_0229c738: the sprite hidden (no animation) and updated; answers the update's
 * answer. */
int DateScreen_HideCursorSprite(DateScreen *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    return date_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov138_0229c738, DateScreen_HideCursorSprite)

/* func_ov138_0229c754: the sprite's y for the cursor: the list's cursor row while a list is
 * open, else the confirm or cancel button's, or the field's from the table.
 * REQUIRES: the cursor is below DATE_SCREEN_PLACES; the game reads past the table for others. */
int DateScreen_CursorSpriteY(DateScreen *self)
{
    if (DateScreen_TestFlags(self, DATE_SCREEN_FLAG_LIST)) {
        return func_ov134_022999ac(self->clock);
    }
    switch (self->cursor) {
        case DATE_SCREEN_CONFIRM:
            return ButtonPanel_ButtonY(&self->panel, DATE_SCREEN_CONFIRM_BUTTON);
        case DATE_SCREEN_CANCEL:
            return ButtonPanel_ButtonY(&self->panel, DATE_SCREEN_CANCEL_BUTTON);
        default:
            return data_ov138_0229d418[self->cursor];
    }
}
CLEAN_AS(func_ov138_0229c754, DateScreen_CursorSpriteY)

/* func_ov138_0229c7a8: the sprite's x, as DateScreen_CursorSpriteY.
 * REQUIRES: the cursor is below DATE_SCREEN_PLACES; the game reads past the table for others. */
int DateScreen_CursorSpriteX(DateScreen *self)
{
    if (DateScreen_TestFlags(self, DATE_SCREEN_FLAG_LIST)) {
        return func_ov134_022999e0(self->clock);
    }
    switch (self->cursor) {
        case DATE_SCREEN_CONFIRM:
            return ButtonPanel_ButtonX(&self->panel, DATE_SCREEN_CONFIRM_BUTTON);
        case DATE_SCREEN_CANCEL:
            return ButtonPanel_ButtonX(&self->panel, DATE_SCREEN_CANCEL_BUTTON);
        default:
            return data_ov138_0229d404[self->cursor];
    }
}
CLEAN_AS(func_ov138_0229c7a8, DateScreen_CursorSpriteX)

/* func_ov138_0229c7fc: the sprite put at the cursor at once, with the looks of a field (set A)
 * or of a button (set B), and shown. */
void DateScreen_PlaceSpriteAtCursor(DateScreen *self)
{
    int x = DateScreen_CursorSpriteX(self);
    int y = DateScreen_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (!date_at_button(self)) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    }
    DateScreen_ShowCursorSprite(self);
}
CLEAN_AS(func_ov138_0229c7fc, DateScreen_PlaceSpriteAtCursor)

/* func_ov138_0229c858: a field's list is open: it is used by touch while the keys are not in
 * use (state flag 2 clear), else by the keys. */
void DateScreen_EnterList(DateScreen *self)
{
    if (StateFlags_IsClear2()) {
        DateScreen_EnterListByTouch(self);
    } else {
        DateScreen_EnterListByKeys(self);
    }
}
CLEAN_AS(func_ov138_0229c858, DateScreen_EnterList)

/* func_ov138_0229c878: the list used by the keys (sub state 5): the list's cursor set to its
 * own y again, the list flag set and the sprite put at the list's cursor; the key repeat
 * restarts. */
void DateScreen_EnterListByKeys(DateScreen *self)
{
    int y = func_ov134_022999ac(self->clock);
    func_ov134_02299980(self->clock, y);
    DateScreen_SetFlags(self, DATE_SCREEN_FLAG_LIST);
    DateScreen_PlaceSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(date_scene(self));
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_LIST);
}
CLEAN_AS(func_ov138_0229c878, DateScreen_EnterListByKeys)

/* func_ov138_0229c8b4: the list used by touch (sub state 1), the sprite hidden. */
void DateScreen_EnterListByTouch(DateScreen *self)
{
    DateScreen_HideCursorSprite(self);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_TOUCH_LIST);
}
CLEAN_AS(func_ov138_0229c8b4, DateScreen_EnterListByTouch)

/* func_ov138_0229c8cc: the list closed without a pick: the sprite hidden, the list flag cleared,
 * and the scene waits for the list to close (sub state 13). */
void DateScreen_CancelList(DateScreen *self)
{
    DateScreen_HideCursorSprite(self);
    DateScreen_ClearFlags(self, DATE_SCREEN_FLAG_LIST);
    func_ov134_0229a398(self->clock);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_LIST_CLOSING);
}
CLEAN_AS(func_ov138_0229c8cc, DateScreen_CancelList)

/* func_ov138_0229c8f8: as DateScreen_CancelList, with the list's row picked. */
void DateScreen_PickListRow(DateScreen *self)
{
    DateScreen_HideCursorSprite(self);
    DateScreen_ClearFlags(self, DATE_SCREEN_FLAG_LIST);
    func_ov134_0229a3e4(self->clock);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_LIST_CLOSING);
}
CLEAN_AS(func_ov138_0229c8f8, DateScreen_PickListRow)

/* func_ov138_0229c924: the list of `field` opened, the sprite hidden; the scene waits for it
 * (sub state 12). */
void DateScreen_OpenList(DateScreen *self, int field)
{
    DateScreen_HideCursorSprite(self);
    func_ov134_0229a5c8(self->clock, field);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_LIST_OPENING);
}
CLEAN_AS(func_ov138_0229c924, DateScreen_OpenList)

/* func_ov138_0229c950: cancelled: the cancel button pressed on the panel, the scene's wipe out
 * to come (state 2) once the press is over (sub state 11); main told no date was set. */
void DateScreen_Cancel(DateScreen *self)
{
    ButtonPanel_Select(&self->panel, DATE_SCREEN_CANCEL_BUTTON);
    MenuScene_SetState(date_scene(self), DATE_SCREEN_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_PANEL_PRESSED);
    GroupParams_SetC4C(0);
}
CLEAN_AS(func_ov138_0229c950, DateScreen_Cancel)

/* func_ov138_0229c978: confirmed: as DateScreen_Cancel with the confirm button, and the clock
 * panel's date copied into main's date and time; main told a date was set. */
void DateScreen_Confirm(DateScreen *self)
{
    ButtonPanel_Select(&self->panel, DATE_SCREEN_CONFIRM_BUTTON);
    MenuScene_SetState(date_scene(self), DATE_SCREEN_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_PANEL_PRESSED);
    DateTime when = {0};
    func_ov134_0229bbdc(self->clock, &when);
    Global021cfc98_CopyIn(&when);
    GroupParams_SetC4C(1);
}
CLEAN_AS(func_ov138_0229c978, DateScreen_Confirm)

/* func_ov138_0229c9c0: back to the fields, by touch while the keys are not in use (state flag
 * 2 clear), else by the keys. Answers what that answers. */
int DateScreen_Resume(DateScreen *self)
{
    if (StateFlags_IsClear2()) {
        return DateScreen_ResumeByTouch(self);
    }
    return (int) (uintptr_t) DateScreen_ResumeByKeys(self);
}
CLEAN_AS(func_ov138_0229c9c0, DateScreen_Resume)

/* func_ov138_0229c9e0: the fields by the keys (sub state 4): the sprite at the cursor, the key
 * repeat restarted. Answers MenuScene_SetSubState's answer. */
u8 *DateScreen_ResumeByKeys(DateScreen *self)
{
    DateScreen_PlaceSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(date_scene(self));
    return MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_BROWSE);
}
CLEAN_AS(func_ov138_0229c9e0, DateScreen_ResumeByKeys)

/* func_ov138_0229c9fc: the fields by touch (sub state 0), the sprite hidden. Answers
 * MenuScene_SetSubState's answer. */
int DateScreen_ResumeByTouch(DateScreen *self)
{
    DateScreen_HideCursorSprite(self);
    return (int) (uintptr_t) MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_TOUCH_BROWSE);
}
CLEAN_AS(func_ov138_0229c9fc, DateScreen_ResumeByTouch)

/* func_ov138_0229ca14 (sub state 13): once the list has closed, the cursor goes to the field
 * that has the focus (with none, to the confirm button) and the fields are used again. */
void DateScreen_WaitListClose(DateScreen *self)
{
    if (func_ov134_0229a24c(self->clock) == 0) {
        return;
    }
    int field = func_ov134_0229a8a0(self->clock);
    if (field == DATE_SCREEN_NO_FIELD) {
        self->cursor = DATE_SCREEN_CONFIRM;
    } else {
        self->cursor = (u8) field;
    }
    DateScreen_Resume(self);
}
CLEAN_AS(func_ov138_0229ca14, DateScreen_WaitListClose)

/* func_ov138_0229ca50 (sub state 12): once the list has opened, it is used. */
void DateScreen_WaitListOpen(DateScreen *self)
{
    if (func_ov134_0229a4e4(self->clock) != 0) {
        DateScreen_EnterList(self);
    }
}
CLEAN_AS(func_ov138_0229ca50, DateScreen_WaitListOpen)

/* func_ov138_0229ca70 (sub state 11): the panel's selected button pressed, a frame at a time;
 * a shown sprite follows it at its place moved by the press's frame. When the press is over the
 * sprite is hidden and the states run (phase 1), which wipe the scene out. */
void DateScreen_FollowPanelPress(DateScreen *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel)) {
        if (CellLayerSprite_AnimNumber(date_sprite_cells(self))) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        DateScreen_HideCursorSprite(self);
        MenuScene_SetPhase(date_scene(self), 1);
    }
}
CLEAN_AS(func_ov138_0229ca70, DateScreen_FollowPanelPress)

/* func_ov138_0229cad4 (sub state 10): once the sprite's look has played, it shows its first
 * look again and the scene goes back to the sub state it came from. */
void DateScreen_WaitPressRelease(DateScreen *self)
{
    if (CellLayerSprite_IsDone(date_sprite_cells(self)) != 0) {
        DateScreen_ShowCursorSprite(self);
        MenuScene_SetSubState(date_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov138_0229cad4, DateScreen_WaitPressRelease)

/* func_ov138_0229caf8 (sub state 9): once the press has played, it is acted on. In a list: on
 * the scroll thumb it is pressed (sub state 6); on a row that can be picked, the row is picked;
 * else back to the list. At the fields: the confirm or cancel button, or the field's list
 * opened. */
void DateScreen_ActOnPress(DateScreen *self)
{
    if (CellLayerSprite_IsDone(date_sprite_cells(self)) == 0) {
        return;
    }
    if (DateScreen_TestFlags(self, DATE_SCREEN_FLAG_LIST)) {
        if (func_ov134_02299b70(self->clock)) {
            MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_THUMB_KEYS);
        } else if (func_ov134_022997b0(self->clock)) {
            DateScreen_PickListRow(self);
        } else {
            MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_LIST);
            DateScreen_PressAndReturn(self);
        }
        return;
    }
    u8 cursor = self->cursor;
    if (cursor == DATE_SCREEN_CONFIRM) {
        DateScreen_Confirm(self);
    } else if (cursor == DATE_SCREEN_CANCEL) {
        DateScreen_Cancel(self);
    } else {
        DateScreen_OpenList(self, cursor);
    }
}
CLEAN_AS(func_ov138_0229caf8, DateScreen_ActOnPress)

/* Obj_ov138_0229d4e0::func_ov138_0229cb7c (sub state 8): once the sprite has stopped, back to
 * the sub state it came from, which runs at once. */
void DateScreen_WaitCursorSprite(DateScreen *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(date_scene(self), self->return_sub_state);
        DateScreen_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov138_0229d4e019func_ov138_0229cb7cEv, DateScreen_WaitCursorSprite)

/* func_ov138_0229cba4 (sub state 7): the scroll thumb let go; once it has settled, back to the
 * list (through the press's release). The sprite follows the list's cursor. */
void DateScreen_SettleThumb(DateScreen *self)
{
    if (func_ov134_02299a60(self->clock)) {
        MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_LIST);
        DateScreen_PressAndReturn(self);
    }
    int x = DateScreen_CursorSpriteX(self);
    int y = DateScreen_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
}
CLEAN_AS(func_ov138_0229cba4, DateScreen_SettleThumb)

/* func_ov138_0229cbec (sub state 6): while A is held the scroll thumb moves by the d-pad and
 * the sprite follows it; A let go releases it (sub state 7). */
void DateScreen_MoveThumbByKeys(DateScreen *self)
{
    if (data_021fbe40.held & DATE_SCREEN_PAD_A) {
        func_ov134_02299a90(self->clock);
        int x = DateScreen_CursorSpriteX(self);
        int y = DateScreen_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    } else {
        func_ov134_02299a84(self->clock);
        MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_THUMB_SETTLE);
    }
}
CLEAN_AS(func_ov138_0229cbec, DateScreen_MoveThumbByKeys)

/* func_ov138_0229cc44 (sub state 5): a list by the keys. A touch hands it to the pen; else the
 * list's keys: a step glides the sprite (quickly), a step of a held run puts it at once, a
 * switch between the thumb and the rows glides it; with no move, A presses and B cancels. */
void DateScreen_ListByKeys(DateScreen *self)
{
    if (MenuScene_TakeTouch(date_scene(self)) != 0) {
        DateScreen_EnterListByTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(date_scene(self));
    switch (func_ov134_022997dc(self->clock, keys)) {
        case DATE_SCREEN_KEYS_STEPPED:
            DateScreen_SetFlags(self, DATE_SCREEN_FLAG_QUICK);
            DateScreen_GlideToCursor(self);
            break;
        case DATE_SCREEN_KEYS_FAST: {
            int x = DateScreen_CursorSpriteX(self);
            int y = DateScreen_CursorSpriteY(self);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
            break;
        }
        case DATE_SCREEN_KEYS_NONE: {
            u16 pressed = data_021fbe40.pressed;
            if (pressed & DATE_SCREEN_PAD_A) {
                DateScreen_PressToAct(self);
            } else if (pressed & DATE_SCREEN_PAD_B) {
                DateScreen_CancelList(self);
            }
            break;
        }
        default:
            DateScreen_GlideToCursor(self);
            break;
    }
}
CLEAN_AS(func_ov138_0229cc44, DateScreen_ListByKeys)

/* func_ov138_0229ccdc (sub state 4): the fields by the keys. A touch hands them to the pen; a
 * move of the cursor glides the sprite; A presses, START confirms and B cancels at once. */
void DateScreen_BrowseByKeys(DateScreen *self)
{
    if (MenuScene_TakeTouch(date_scene(self))) {
        DateScreen_ResumeByTouch(self);
        return;
    }
    if (DateScreen_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(date_scene(self)))) {
        DateScreen_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & DATE_SCREEN_PAD_A) {
        DateScreen_PressToAct(self);
    } else if (pressed & DATE_SCREEN_PAD_START) {
        DateScreen_HideCursorSprite(self);
        DateScreen_Confirm(self);
    } else if (pressed & DATE_SCREEN_PAD_B) {
        DateScreen_HideCursorSprite(self);
        DateScreen_Cancel(self);
    }
}
CLEAN_AS(func_ov138_0229ccdc, DateScreen_BrowseByKeys)

/* func_ov138_0229cd58 (sub state 3): while the pen is down the scroll thumb moves toward its
 * y; the pen let go releases it and the list is used by touch again (sub state 1). */
void DateScreen_ThumbTowardPen(DateScreen *self)
{
    if (data_021fbdd8) {
        func_ov134_02299af0(self->clock, data_021f6c54);
    } else {
        func_ov134_02299a84(self->clock);
        MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_TOUCH_LIST);
    }
}
CLEAN_AS(func_ov138_0229cd58, DateScreen_ThumbTowardPen)

/* func_ov138_0229cd94 (sub state 2): as DateScreen_ThumbTowardPen, the thumb dragged with the
 * pen. */
void DateScreen_DragThumb(DateScreen *self)
{
    if (data_021fbdd8) {
        func_ov134_02299b18(self->clock, data_021f6c54);
    } else {
        func_ov134_02299a84(self->clock);
        MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_TOUCH_LIST);
    }
}
CLEAN_AS(func_ov138_0229cd94, DateScreen_DragThumb)

/* func_ov138_0229cdd0 (sub state 1): a list by touch. A button hands it to the keys; a touch
 * this frame picks a row, cancels outside the list, or grabs (sub state 2) or presses (sub
 * state 3) the scroll bar. */
void DateScreen_ListByTouch(DateScreen *self)
{
    if (MenuScene_TakeButtons(date_scene(self), 1)) {
        DateScreen_EnterListByKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    switch (func_ov134_0229a1f0(self->clock, data_021f6c58, data_021f6c54)) {
        case DATE_SCREEN_TOUCH_PICKED:
            DateScreen_PickListRow(self);
            break;
        case DATE_SCREEN_TOUCH_OUTSIDE:
            DateScreen_CancelList(self);
            break;
        case DATE_SCREEN_TOUCH_THUMB:
            MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_DRAG_THUMB);
            break;
        case DATE_SCREEN_TOUCH_BAR:
            MenuScene_SetSubState(date_scene(self), DATE_SCREEN_SUB_THUMB_TO_PEN);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov138_0229cdd0, DateScreen_ListByTouch)

/* func_ov138_0229ce68 (sub state 0): the fields by touch. A button hands them to the keys; a
 * touch this frame on the confirm or cancel button acts on it, and on a field opens its
 * list. */
void DateScreen_BrowseByTouch(DateScreen *self)
{
    if (MenuScene_TakeButtons(date_scene(self), 1) != 0) {
        DateScreen_ResumeByKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, DATE_SCREEN_CONFIRM_BUTTON) != 0) {
        DateScreen_Confirm(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, DATE_SCREEN_CANCEL_BUTTON) != 0) {
        DateScreen_Cancel(self);
        return;
    }
    int field = func_ov134_0229ab80(self->clock, data_021f6c58, data_021f6c54);
    if (field != DATE_SCREEN_NO_FIELD) {
        DateScreen_OpenList(self, field);
    }
}
CLEAN_AS(func_ov138_0229ce68, DateScreen_BrowseByTouch)

/* func_ov138_0229cefc: the clock panel's sprites loaded, and the panel's text colours. */
void DateScreen_LoadSprites(DateScreen *self)
{
    func_ov134_0229b954(self->clock);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov138_0229cefc, DateScreen_LoadSprites)

/* func_ov138_0229cf1c: the clock panel's background loaded and its labels drawn with the
 * screen's title. */
void DateScreen_LoadBackground(DateScreen *self)
{
    func_ov134_0229baec(self->clock);
    func_ov134_0229ba10(self->clock, DATE_SCREEN_TITLE);
}
CLEAN_AS(func_ov138_0229cf1c, DateScreen_LoadBackground)

/* func_ov138_0229cf3c: the sub screen's background mode 0; layer 6 at priority 2, layers 4 and
 * 3 at priority 1, each with its control reset. */
void DateScreen_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 1);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 1);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov138_0229cf3c, DateScreen_SetUpLayers)

/* func_ov138_0229cf88: the frame's end: the clock panel updated. */
void DateScreen_EndFrame(DateScreen *self)
{
    func_ov134_0229bbe8(self->clock);
}
CLEAN_AS(func_ov138_0229cf88, DateScreen_EndFrame)

/* func_ov138_0229cf98: the frame's start: the button panel's texts closed and the clock panel's
 * frame ended. */
void DateScreen_BeginFrame(DateScreen *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    func_ov134_0229bcac(self->clock);
}
CLEAN_AS(func_ov138_0229cf98, DateScreen_BeginFrame)

/* func_ov138_0229cfb4 */
void DateScreen_EndInteractiveFrame(DateScreen *self)
{
    DateScreen_EndFrame(self);
}
CLEAN_AS(func_ov138_0229cfb4, DateScreen_EndInteractiveFrame)

/* func_ov138_0229cfbc: the frame's start, then the cursor sprite updated; answers the update's
 * answer. */
int DateScreen_BeginInteractiveFrame(DateScreen *self)
{
    DateScreen_BeginFrame(self);
    return date_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov138_0229cfbc, DateScreen_BeginInteractiveFrame)

/* func_ov138_0229cfd4: the members torn down: the clock panel, and the button panel's texts
 * closed. */
void DateScreen_Teardown(DateScreen *self)
{
    func_ov134_0229bcf0(self->clock);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov138_0229cfd4, DateScreen_Teardown)

/* func_ov138_0229cff4: the setup: the clock panel in mode 3 (layers 6 and 4 for its base and
 * fields, 3 for its lists) bounded below, the cursor at the year, no flags. */
void DateScreen_Setup(DateScreen *self)
{
    func_ov134_0229bd38(self->clock, DATE_SCREEN_CLOCK_MODE, 6, 4, 3);
    func_ov134_0229bd2c(self->clock);
    self->cursor = DATE_SCREEN_YEAR;
    *date_flags(self) = 0;
}
CLEAN_AS(func_ov138_0229cff4, DateScreen_Setup)

/* func_ov138_0229d02c: layers 6 and 4 scrolled with the wipe. */
void DateScreen_ScrollWithWipe(DateScreen *self)
{
    MenuScene_ScrollWipe(date_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(date_scene(self), 4, 0, 0);
}
CLEAN_AS(func_ov138_0229d02c, DateScreen_ScrollWithWipe)

/* func_ov138_0229d04c (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void DateScreen_WipeOut(DateScreen *self)
{
    if (MenuScene_StepWipe(date_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(date_scene(self), 5);
    } else {
        DateScreen_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov138_0229d04c, DateScreen_WipeOut)

/* func_ov138_0229d07c (state 2): the parent told the menu closes, the wipe out started on
 * window 2 (layers 2 and 8, margin 0x30), the layers following it; state 3. */
void DateScreen_StartWipeOut(DateScreen *self)
{
    MenuDispatch_SetMode(date_parent(self), DATE_SCREEN_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(date_scene(self), 0xa, 0, 0, 0x30);
    DateScreen_ScrollWithWipe(self);
    MenuScene_SetState(date_scene(self), DATE_SCREEN_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov138_0229d07c, DateScreen_StartWipeOut)

/* func_ov138_0229d0b4 (state 1): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the fields. The layers follow the wipe. */
void DateScreen_WipeIn(DateScreen *self)
{
    if (MenuScene_StepWipeBack(date_scene(self), 0)) {
        MenuScene_SetPhase(date_scene(self), 2);
        DateScreen_Resume(self);
    }
    DateScreen_ScrollWithWipe(self);
}
CLEAN_AS(func_ov138_0229d0b4, DateScreen_WipeIn)

/* func_ov138_0229d0dc (state 0): the layers set up, the clock panel's background and sprites
 * loaded, the wipe in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x30),
 * layers 6 and 4 shown and following it, the scene drawn, the panel in layout 6 with message
 * 0x65; state 1. */
void DateScreen_StartSetup(DateScreen *self)
{
    DateScreen_SetUpLayers();
    DateScreen_LoadBackground(self);
    DateScreen_LoadSprites(self);
    MenuScene_StartWipeCoveredOnWindow2(date_scene(self), 0xa, 4, 0, 0x30);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    DateScreen_ScrollWithWipe(self);
    DateScreen_SetFlags(self, DATE_SCREEN_FLAG_DRAWN);
    ButtonPanel_SetLayout6(&self->panel, 0x65);
    MenuScene_SetState(date_scene(self), DATE_SCREEN_STATE_WIPE_IN);
}
CLEAN_AS(func_ov138_0229d0dc, DateScreen_StartSetup)

/* func_ov138_0229d138 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int DateScreen_End(DateScreen *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov138_0229d138, DateScreen_End)

/* func_ov138_0229d148 (vtable slot 0x58, phase 4): nothing. */
int DateScreen_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov138_0229d148, DateScreen_Phase4Idle)

/* func_ov138_0229d14c (vtable slot 0x54, phase 3): nothing. */
int DateScreen_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov138_0229d14c, DateScreen_Phase3Idle)

/* Obj_ov138_0229d4e0::func_ov138_0229d150 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int DateScreen_RunInteractive(DateScreen *self)
{
    DateScreen_BeginInteractiveFrame(self);
    DateScreen_RunSubState(self);
    DateScreen_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov138_0229d4e019func_ov138_0229d150Ev, DateScreen_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov138_0229d540; /* the sub states' guard */
extern u32 data_ov138_0229d544; /* the states' guard */
extern MemberPointer data_ov138_0229d548[DATE_SCREEN_STATES];
extern MemberPointer data_ov138_0229d568[DATE_SCREEN_SUB_STATES];
extern const MemberPointer data_ov138_0229d440, data_ov138_0229d448, data_ov138_0229d450, data_ov138_0229d458,
    data_ov138_0229d460, data_ov138_0229d468, data_ov138_0229d470, data_ov138_0229d478, data_ov138_0229d480,
    data_ov138_0229d488, data_ov138_0229d490, data_ov138_0229d498, data_ov138_0229d4a0, data_ov138_0229d4a8,
    data_ov138_0229d4b0, data_ov138_0229d4b8, data_ov138_0229d4c0, data_ov138_0229d4d0;

/* Obj_ov138_0229d4e0::func_ov138_0229d16c: the sub state's function (DateScreenSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 14; the game reads past the table for others. */
void DateScreen_RunSubState(DateScreen *self)
{
    static const MemberPointer *const sub_states[DATE_SCREEN_SUB_STATES] = {
        &data_ov138_0229d4b8, &data_ov138_0229d4b0, &data_ov138_0229d4a8, &data_ov138_0229d480, &data_ov138_0229d490,
        &data_ov138_0229d498, &data_ov138_0229d4a0, &data_ov138_0229d4c0, &data_ov138_0229d478, &data_ov138_0229d470,
        &data_ov138_0229d468, &data_ov138_0229d460, &data_ov138_0229d458, &data_ov138_0229d488,
    };
    MemberTable_InitOnce(&data_ov138_0229d540, data_ov138_0229d568, sub_states, DATE_SCREEN_SUB_STATES);
    MemberPointer_CallVoid(&data_ov138_0229d568[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov138_0229d4e019func_ov138_0229d16cEv, DateScreen_RunSubState)

/* Obj_ov138_0229d4e0::func_ov138_0229d27c (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (DateScreenState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int DateScreen_RunState(DateScreen *self)
{
    static const MemberPointer *const states[DATE_SCREEN_STATES] = {
        &data_ov138_0229d448,
        &data_ov138_0229d440,
        &data_ov138_0229d450,
        &data_ov138_0229d4d0,
    };
    MemberTable_InitOnce(&data_ov138_0229d544, data_ov138_0229d548, states, DATE_SCREEN_STATES);
    DateScreen_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov138_0229d548[self->base.state], self);
    DateScreen_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov138_0229d4e019func_ov138_0229d27cEv, DateScreen_RunState)

/* func_ov138_0229d310 (vtable slot 0x24): the cursor sprite drawn while the keys are in use;
 * then, while the scene is drawn (else answers 0), the clock panel and the button panel moved
 * with the wipe. Answers 1. */
int DateScreen_Draw(DateScreen *self)
{
    if (StateFlags_Test2() != 0) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (DateScreen_TestFlags(self, DATE_SCREEN_FLAG_DRAWN) == 0) {
        return 0;
    }
    func_ov134_0229b220(self->clock, 0, MenuScene_WipeOffsetY(date_scene(self)));
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(date_scene(self)));
    return 1;
}
CLEAN_AS(func_ov138_0229d310, DateScreen_Draw)

/* func_ov138_0229d364 (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int DateScreen_Close(DateScreen *self)
{
    MenuDispatch_ChildClosed(date_parent(self));
    DateScreen_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov138_0229d364, DateScreen_Close)

/* func_ov138_0229d380 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int DateScreen_Start(DateScreen *self, int unused)
{
    (void) unused;
    DateScreen_Setup(self);
    self->base.state = DATE_SCREEN_STATE_START_SETUP;
    MenuScene_SetPhase(date_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov138_0229d380, DateScreen_Start)

/* func_ov138_0229d3a0 (named by the profile at 0x0229d4c8): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
DateScreen *DateScreen_New(void)
{
    DateScreen *self = MenuScene_Alloc(sizeof(DateScreen));
    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov138_0229d4e0;
        Glider0_Construct(&self->cursor_sprite);
        ButtonPanel_Construct(&self->panel);
        func_ov134_0229bed4(self->clock);
    }
    return self;
}
CLEAN_AS(func_ov138_0229d3a0, DateScreen_New)
