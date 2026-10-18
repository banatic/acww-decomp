/* The time entry screen of overlay 136 (time_screen.h): its destructors, its flags, the cursor
 * and its sprite, the fields' lists, the clock's hands, the frame and the scene's slots. */
#include "time_screen.h"

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
#include "ov134/clock_setter.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(TimeScreen, cursor_sprite) == 0x94, "cursor_sprite");
static_assert(offsetof(TimeScreen, panel) == 0xf8 && offsetof(TimeScreen, picker) == 0x2c4, "panel");
static_assert(offsetof(TimeScreen, flags) == 0x2b74 && offsetof(TimeScreen, place) == 0x2b77, "flags");
static_assert(sizeof(TimeScreen) == 0x2b78, "size (func_ov136_0229d3d4)");

/* The scene's vtable. */
extern const u8 data_ov136_0229d510[];

/* The cursor's moves from each place (TimeScreenPlace): right, left, down and up. */
extern const u8 data_ov136_0229d418[];
extern const u8 data_ov136_0229d41c[];
extern const u8 data_ov136_0229d420[];
extern const u8 data_ov136_0229d424[];

/* Where the cursor sprite points at the hour and the minute: x, and y. */
extern const s32 data_ov136_0229d428[];
extern const s32 data_ov136_0229d434[];

/* The pad, and the pen (autoload_2/input.c): down, and gone down or up this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;
#define TIME_SCREEN_PAD_A 0x0001
#define TIME_SCREEN_PAD_B 0x0002
#define TIME_SCREEN_PAD_START 0x0008

/* The panel's OK button. */
#define TIME_SCREEN_OK_BUTTON 6

/* The cursor sprite's animations (glide.h): at a field, at the OK button. */
#define TIME_SCREEN_ANIM_FIELD 1
#define TIME_SCREEN_ANIM_OK 7

/* The picker's prompt and the panel's message. */
#define TIME_SCREEN_PROMPT 0x8b
#define TIME_SCREEN_PANEL_MESSAGE 0x21

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define TIME_SCREEN_PARENT_CLOSE 0x44

static MenuScene *time_scene(TimeScreen *self)
{
    return &self->base;
}

static CellLayerSprite *time_sprite_cells(TimeScreen *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *time_parent(TimeScreen *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void time_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void time_destroy_members(TimeScreen *self)
{
    self->base.vtable = data_ov136_0229d510;
    ClockSetter_Destroy(&self->picker);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(time_scene(self));
}

/* func_ov136_0229c4e0 (vtable slot 0x40) */
TimeScreen *TimeScreen_Destroy(TimeScreen *self)
{
    time_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov136_0229c4e0, TimeScreen_Destroy)

/* func_ov136_0229c518 (vtable slot 0x44) */
TimeScreen *TimeScreen_Delete(TimeScreen *self)
{
    time_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov136_0229c518, TimeScreen_Delete)

/* func_ov136_0229c554 */
void TimeScreen_ClearFlags(TimeScreen *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov136_0229c554, TimeScreen_ClearFlags)

/* func_ov136_0229c564 */
void TimeScreen_SetFlags(TimeScreen *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov136_0229c564, TimeScreen_SetFlags)

/* func_ov136_0229c574 */
int TimeScreen_TestFlags(TimeScreen *self, int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov136_0229c574, TimeScreen_TestFlags)

/* func_ov136_0229c58c: the cursor moved by the d-pad keys `keys` through the tables of moves:
 * left or right first and, when that did not move it, up or down; whether it moved. The hour
 * and the minute share a row, OK is below them; up from OK goes to the minute.
 * REQUIRES: place < 3; the game reads its tables on for others. */
int TimeScreen_MoveCursor(TimeScreen *self, int keys)
{
    u8 before = self->place;
    if (KeyRepeat_HasLeft(keys)) {
        self->place = data_ov136_0229d41c[self->place];
    } else if (KeyRepeat_HasRight(keys)) {
        self->place = data_ov136_0229d418[self->place];
    }
    if (before != self->place) {
        return 1;
    }
    if (KeyRepeat_HasUp(keys)) {
        self->place = data_ov136_0229d424[self->place];
    } else if (KeyRepeat_HasDown(keys)) {
        self->place = data_ov136_0229d420[self->place];
    }
    return before != self->place;
}
CLEAN_AS(func_ov136_0229c58c, TimeScreen_MoveCursor)

/* func_ov136_0229c628: the cursor sprite's third animation of its set played, the sub state kept
 * to come back to once it ends (sub state 12). */
void TimeScreen_PlayReleaseAnim(TimeScreen *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_SPRITE_ANIM);
}
CLEAN_AS(func_ov136_0229c628, TimeScreen_PlayReleaseAnim)

/* func_ov136_0229c650: the cursor sprite pressed (the second of its set), sub state 11. */
void TimeScreen_PressSprite(TimeScreen *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_PRESSED);
}
CLEAN_AS(func_ov136_0229c650, TimeScreen_PressSprite)

/* func_ov136_0229c668: the cursor sprite shown (the first of its set) and updated. */
void TimeScreen_ShowCursorSprite(TimeScreen *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    time_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov136_0229c668, TimeScreen_ShowCursorSprite)

/* func_ov136_0229c684: the cursor sprite eased to (x, y), in two steps when the quick flag is
 * set, else three; the sub state kept to come back to once it stops (sub state 10), and the
 * quick flag cleared. */
void TimeScreen_GlideSpriteTo(TimeScreen *self, int x, int y)
{
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_QUICK)) {
        Glider_EaseTo(&self->cursor_sprite, x, y, 2, 1);
    } else {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    }
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_SPRITE_MOVE);
    TimeScreen_ClearFlags(self, TIME_SCREEN_FLAG_QUICK);
}
CLEAN_AS(func_ov136_0229c684, TimeScreen_GlideSpriteTo)

/* func_ov136_0229c6e4: the cursor sprite turned to the set of OK when the cursor went there
 * among the fields (else to the set of a field), and eased to the cursor. */
void TimeScreen_GlideToCursor(TimeScreen *self)
{
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_IN_LIST) == 0 && self->place == TIME_SCREEN_PLACE_OK) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = TimeScreen_CursorX(self);
    int y = TimeScreen_CursorY(self);
    TimeScreen_GlideSpriteTo(self, x, y);
}
CLEAN_AS(func_ov136_0229c6e4, TimeScreen_GlideToCursor)

/* func_ov136_0229c734: the cursor sprite hidden (no animation) and updated. */
void TimeScreen_HideCursorSprite(TimeScreen *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    time_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov136_0229c734, TimeScreen_HideCursorSprite)

/* func_ov136_0229c750: where the cursor sprite points: y. In a list, the list's cursor; at OK,
 * the panel's button 6; else the field's, from the table.
 * REQUIRES: place < 3; the game reads its table on for others. */
int TimeScreen_CursorY(TimeScreen *self)
{
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_IN_LIST) != 0) {
        return ClockSetter_CursorY(&self->picker);
    }
    u8 place = self->place;
    if (place == TIME_SCREEN_PLACE_OK) {
        return ButtonPanel_ButtonY(&self->panel, TIME_SCREEN_OK_BUTTON);
    }
    return data_ov136_0229d434[place];
}
CLEAN_AS(func_ov136_0229c750, TimeScreen_CursorY)

/* func_ov136_0229c794: ... x.
 * REQUIRES: place < 3; the game reads its table on for others. */
int TimeScreen_CursorX(TimeScreen *self)
{
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_IN_LIST) != 0) {
        return ClockSetter_CursorX(&self->picker);
    }
    u8 place = self->place;
    if (place == TIME_SCREEN_PLACE_OK) {
        return ButtonPanel_ButtonX(&self->panel, TIME_SCREEN_OK_BUTTON);
    }
    return data_ov136_0229d428[place];
}
CLEAN_AS(func_ov136_0229c794, TimeScreen_CursorX)

/* func_ov136_0229c7d8: the cursor sprite put at the cursor, with OK's animation when the cursor
 * is there among the fields (else a field's), and shown. */
void TimeScreen_ShowSpriteAtCursor(TimeScreen *self)
{
    int x = TimeScreen_CursorX(self);
    int y = TimeScreen_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_IN_LIST) == 0 && self->place == TIME_SCREEN_PLACE_OK) {
        Glider_SetAnim(&self->cursor_sprite, TIME_SCREEN_ANIM_OK);
    } else {
        Glider_SetAnim(&self->cursor_sprite, TIME_SCREEN_ANIM_FIELD);
    }
    TimeScreen_ShowCursorSprite(self);
}
CLEAN_AS(func_ov136_0229c7d8, TimeScreen_ShowSpriteAtCursor)

/* func_ov136_0229c834: on to the open list, by touch or by the keys as the player last used. */
void TimeScreen_ResumeList(TimeScreen *self)
{
    if (StateFlags_IsClear2()) {
        TimeScreen_ResumeListByTouch(self);
    } else {
        TimeScreen_ResumeListByKeys(self);
    }
}
CLEAN_AS(func_ov136_0229c834, TimeScreen_ResumeList)

/* func_ov136_0229c854: on to the list by the keys: the list's cursor row put at its own y, the
 * sprite following it (flagged), shown there, the key repeat reset (sub state 7). */
void TimeScreen_ResumeListByKeys(TimeScreen *self)
{
    int y = ClockSetter_CursorY(&self->picker);
    ClockSetter_CursorToY(&self->picker, y);
    TimeScreen_SetFlags(self, TIME_SCREEN_FLAG_IN_LIST);
    TimeScreen_ShowSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(time_scene(self));
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_LIST);
}
CLEAN_AS(func_ov136_0229c854, TimeScreen_ResumeListByKeys)

/* func_ov136_0229c890: on to the list by touch: the cursor sprite hidden (sub state 3). */
void TimeScreen_ResumeListByTouch(TimeScreen *self)
{
    TimeScreen_HideCursorSprite(self);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_TOUCH_LIST);
}
CLEAN_AS(func_ov136_0229c890, TimeScreen_ResumeListByTouch)

/* func_ov136_0229c8a8: the list closed without a value: the cursor sprite hidden and no longer
 * following it (sub state 15). */
void TimeScreen_CancelList(TimeScreen *self)
{
    TimeScreen_HideCursorSprite(self);
    TimeScreen_ClearFlags(self, TIME_SCREEN_FLAG_IN_LIST);
    ClockSetter_CancelList(&self->picker);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_LIST_CLOSE);
}
CLEAN_AS(func_ov136_0229c8a8, TimeScreen_CancelList)

/* func_ov136_0229c8d4: the list closed keeping the value under its cursor: the same as
 * TimeScreen_CancelList otherwise. */
void TimeScreen_PickInList(TimeScreen *self)
{
    TimeScreen_HideCursorSprite(self);
    TimeScreen_ClearFlags(self, TIME_SCREEN_FLAG_IN_LIST);
    ClockSetter_PickRow(&self->picker);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_LIST_CLOSE);
}
CLEAN_AS(func_ov136_0229c8d4, TimeScreen_PickInList)

/* func_ov136_0229c900: the list of picker field `field` opened, the cursor sprite hidden
 * meanwhile (sub state 14). */
void TimeScreen_OpenList(TimeScreen *self, int field)
{
    TimeScreen_HideCursorSprite(self);
    ClockSetter_OpenList(&self->picker, field);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_LIST_OPEN);
}
CLEAN_AS(func_ov136_0229c900, TimeScreen_OpenList)

/* func_ov136_0229c92c: the time confirmed: the panel's OK button selected, state 2 next (the
 * wipe out) once its press is over (sub state 13); the time entered kept as main's date and
 * time, and main told (GroupParams_SetC4C(1)). */
void TimeScreen_Confirm(TimeScreen *self)
{
    DateTime when = {0};

    ButtonPanel_Select(&self->panel, TIME_SCREEN_OK_BUTTON);
    MenuScene_SetState(time_scene(self), TIME_SCREEN_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_OK_PRESSED);
    ClockSetter_CopyValue(&self->picker, &when);
    Global021cfc98_CopyIn(&when);
    GroupParams_SetC4C(1);
}
CLEAN_AS(func_ov136_0229c92c, TimeScreen_Confirm)

/* func_ov136_0229c974: back to the fields, by touch or by the keys as the player last used. */
void TimeScreen_ResumeFields(TimeScreen *self)
{
    if (StateFlags_IsClear2()) {
        TimeScreen_ResumeFieldsByTouch(self);
    } else {
        TimeScreen_ResumeFieldsByKeys(self);
    }
}
CLEAN_AS(func_ov136_0229c974, TimeScreen_ResumeFields)

/* func_ov136_0229c994: back to the fields by the keys: the cursor sprite shown at the cursor,
 * the key repeat reset (sub state 6). */
void TimeScreen_ResumeFieldsByKeys(TimeScreen *self)
{
    TimeScreen_ShowSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(time_scene(self));
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_FIELDS);
}
CLEAN_AS(func_ov136_0229c994, TimeScreen_ResumeFieldsByKeys)

/* func_ov136_0229c9b0: back to the fields by touch: the cursor sprite hidden (sub state 0). */
void TimeScreen_ResumeFieldsByTouch(TimeScreen *self)
{
    TimeScreen_HideCursorSprite(self);
    MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_TOUCH_FIELDS);
}
CLEAN_AS(func_ov136_0229c9b0, TimeScreen_ResumeFieldsByTouch)

/* func_ov136_0229c9c8 (sub state 15): once the list has closed, the cursor at the picker's field
 * (OK for none) and back to the fields.
 * QUIRK: a field below 3 would wrap the place (u8); the picker of a time only has 3, 4 and 6. */
void TimeScreen_WaitListClosed(TimeScreen *self)
{
    if (ClockSetter_CloseListStep(&self->picker) == 0) {
        return;
    }
    int field = ClockSetter_Focus(&self->picker);
    if (field == CLOCK_SETTER_NO_FIELD) {
        self->place = TIME_SCREEN_PLACE_OK;
    } else {
        self->place = (u8) (field - TIME_SCREEN_FIELD_OF_PLACE);
    }
    TimeScreen_ResumeFields(self);
}
CLEAN_AS(func_ov136_0229c9c8, TimeScreen_WaitListClosed)

/* func_ov136_0229ca08 (sub state 14): once the list has opened, on to it. */
void TimeScreen_WaitListOpen(TimeScreen *self)
{
    if (ClockSetter_OpenListStep(&self->picker)) {
        TimeScreen_ResumeList(self);
    }
}
CLEAN_AS(func_ov136_0229ca08, TimeScreen_WaitListOpen)

/* func_ov136_0229ca28 (sub state 13): while the panel's OK button is pressed, the cursor sprite
 * (when it shows) follows the press; once it is over, the sprite hidden and the states run
 * (phase 1: the wipe out). */
void TimeScreen_FollowOkPress(TimeScreen *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        TimeScreen_HideCursorSprite(self);
        MenuScene_SetPhase(time_scene(self), 1);
        return;
    }
    if (CellLayerSprite_AnimNumber(time_sprite_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}
CLEAN_AS(func_ov136_0229ca28, TimeScreen_FollowOkPress)

/* func_ov136_0229ca8c (sub state 12): once the cursor sprite's animation is over, it is shown
 * again and the sub state kept is next. */
void TimeScreen_WaitSpriteAnim(TimeScreen *self)
{
    if (CellLayerSprite_IsDone(time_sprite_cells(self))) {
        TimeScreen_ShowCursorSprite(self);
        MenuScene_SetSubState(time_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov136_0229ca8c, TimeScreen_WaitSpriteAnim)

/* func_ov136_0229cab4 (sub state 11): once the cursor sprite's press is over. In a list: on its
 * scroll bar, the bar by the keys (sub state 8); else the value under the cursor taken when it
 * may be (the list closes), or the list kept with the release animation. Among the fields: at
 * OK the time is confirmed, at a field its list opens. */
void TimeScreen_AfterPress(TimeScreen *self)
{
    if (CellLayerSprite_IsDone(time_sprite_cells(self)) == 0) {
        return;
    }
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_IN_LIST) != 0) {
        if (ClockSetter_PressThumbByKey(&self->picker) != 0) {
            MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_BAR);
        } else if (ClockSetter_PickCursorRow(&self->picker) != 0) {
            TimeScreen_PickInList(self);
        } else {
            MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_LIST);
            TimeScreen_PlayReleaseAnim(self);
        }
    } else if (self->place == TIME_SCREEN_PLACE_OK) {
        TimeScreen_Confirm(self);
    } else {
        TimeScreen_OpenList(self, self->place + TIME_SCREEN_FIELD_OF_PLACE);
    }
}
CLEAN_AS(func_ov136_0229cab4, TimeScreen_AfterPress)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov136_0229d580; /* the states' guard */
extern u32 data_ov136_0229d584; /* the sub states' guard */
extern MemberPointer data_ov136_0229d588[TIME_SCREEN_STATES];
extern MemberPointer data_ov136_0229d5a8[TIME_SCREEN_SUB_STATES];
extern const MemberPointer data_ov136_0229d460, data_ov136_0229d468, data_ov136_0229d470, data_ov136_0229d478,
    data_ov136_0229d480, data_ov136_0229d488, data_ov136_0229d490, data_ov136_0229d498, data_ov136_0229d4a0,
    data_ov136_0229d4a8, data_ov136_0229d4b0, data_ov136_0229d4b8, data_ov136_0229d4c0, data_ov136_0229d4c8,
    data_ov136_0229d4d0, data_ov136_0229d4d8, data_ov136_0229d4e0, data_ov136_0229d4e8, data_ov136_0229d4f8,
    data_ov136_0229d500;

/* func_ov136_0229cb30 (sub state 10): once the cursor sprite stops, the sub state kept is run
 * again, this frame. */
void TimeScreen_WaitCursorSprite(TimeScreen *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(time_scene(self), self->return_sub_state);
        TimeScreen_RunSubState(self);
    }
}
CLEAN_AS(func_ov136_0229cb30, TimeScreen_WaitCursorSprite)

/* func_ov136_0229cb58 (sub state 9): once the picker's cursor is back from the scroll bar, the
 * list by the keys again, after the release animation; the cursor sprite follows meanwhile. */
void TimeScreen_ReturnFromBar(TimeScreen *self)
{
    if (ClockSetter_SettleThumb(&self->picker)) {
        MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_LIST);
        TimeScreen_PlayReleaseAnim(self);
    }
    int x = TimeScreen_CursorX(self);
    int y = TimeScreen_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
}
CLEAN_AS(func_ov136_0229cb58, TimeScreen_ReturnFromBar)

/* func_ov136_0229cba0 (sub state 8): while A is held the scroll bar moves by up and down, the
 * cursor sprite following; once A is let go the bar is too (sub state 9). */
void TimeScreen_ListBarByKeys(TimeScreen *self)
{
    if ((data_021fbe40.held & TIME_SCREEN_PAD_A) != 0) {
        ClockSetter_MoveThumbByKeys(&self->picker);
        int x = TimeScreen_CursorX(self);
        int y = TimeScreen_CursorY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    } else {
        ClockSetter_ReleaseThumb(&self->picker);
        MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_BAR_RETURN);
    }
}
CLEAN_AS(func_ov136_0229cba0, TimeScreen_ListBarByKeys)

/* func_ov136_0229cbf8 (sub state 7): the list by the keys. A touch goes on by touch. Else the
 * picker takes the d-pad: a step glides the cursor sprite quickly, a scroll puts it at the
 * cursor at once, a move glides it; with none of these A presses the sprite and B closes the
 * list without a value. */
void TimeScreen_ListByKeys(TimeScreen *self)
{
    if (MenuScene_TakeTouch(time_scene(self)) != 0) {
        TimeScreen_ResumeListByTouch(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(time_scene(self));
    switch (ClockSetter_ListKeys(&self->picker, keys)) {
        case CLOCK_SETTER_KEYS_STEPPED:
            TimeScreen_SetFlags(self, TIME_SCREEN_FLAG_QUICK);
            TimeScreen_GlideToCursor(self);
            break;
        case CLOCK_SETTER_KEYS_FAST: {
            int x = TimeScreen_CursorX(self);
            int y = TimeScreen_CursorY(self);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
            break;
        }
        case CLOCK_SETTER_KEYS_NONE: {
            u16 pressed = data_021fbe40.pressed;
            if ((pressed & TIME_SCREEN_PAD_A) != 0) {
                TimeScreen_PressSprite(self);
            } else if ((pressed & TIME_SCREEN_PAD_B) != 0) {
                TimeScreen_CancelList(self);
            }
            break;
        }
        default:
            TimeScreen_GlideToCursor(self);
            break;
    }
}
CLEAN_AS(func_ov136_0229cbf8, TimeScreen_ListByKeys)

/* func_ov136_0229cc90 (sub state 6): the fields by the keys. A touch goes on by touch; a move of
 * the cursor glides the sprite there; else A presses the sprite and START confirms the time. */
void TimeScreen_FieldsByKeys(TimeScreen *self)
{
    if (MenuScene_TakeTouch(time_scene(self)) != 0) {
        TimeScreen_ResumeFieldsByTouch(self);
        return;
    }
    if (TimeScreen_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(time_scene(self))) != 0) {
        TimeScreen_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & TIME_SCREEN_PAD_A) != 0) {
        TimeScreen_PressSprite(self);
    } else if ((pressed & TIME_SCREEN_PAD_START) != 0) {
        TimeScreen_HideCursorSprite(self);
        TimeScreen_Confirm(self);
    }
}
CLEAN_AS(func_ov136_0229cc90, TimeScreen_FieldsByKeys)

/* func_ov136_0229ccf4 (sub state 5): while the pen is down on the scroll bar off its thumb, the
 * thumb moves toward it (ClockSetter_ThumbTowardPen); once it is up, the thumb let go and back to
 * the list by touch (sub state 3). */
void TimeScreen_ThumbTowardPen(TimeScreen *self)
{
    if (data_021fbdd8 != 0) {
        ClockSetter_ThumbTowardPen(&self->picker, data_021f6c54);
    } else {
        ClockSetter_ReleaseThumb(&self->picker);
        MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_TOUCH_LIST);
    }
}
CLEAN_AS(func_ov136_0229ccf4, TimeScreen_ThumbTowardPen)

/* func_ov136_0229cd30 (sub state 4): ... with the thumb held at the pen (ClockSetter_DragThumb). */
void TimeScreen_DragThumb(TimeScreen *self)
{
    if (data_021fbdd8 != 0) {
        ClockSetter_DragThumb(&self->picker, data_021f6c54);
    } else {
        ClockSetter_ReleaseThumb(&self->picker);
        MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_TOUCH_LIST);
    }
}
CLEAN_AS(func_ov136_0229cd30, TimeScreen_DragThumb)

/* func_ov136_0229cd6c (sub state 3): the list by touch. A button goes on by the keys. A touch
 * that went down or up this frame: on a value it is taken (the list closes), outside the list
 * closes without one, on the scroll bar's thumb it is held (sub state 4), on the bar off the
 * thumb the thumb moves toward the pen (sub state 5). */
void TimeScreen_ListByTouch(TimeScreen *self)
{
    if (MenuScene_TakeButtons(time_scene(self), 1) != 0) {
        TimeScreen_ResumeListByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    switch (ClockSetter_TouchList(&self->picker, data_021f6c58, data_021f6c54)) {
        case CLOCK_SETTER_TOUCH_PICKED:
            TimeScreen_PickInList(self);
            break;
        case CLOCK_SETTER_TOUCH_OUTSIDE:
            TimeScreen_CancelList(self);
            break;
        case CLOCK_SETTER_TOUCH_THUMB:
            MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_DRAG_THUMB);
            break;
        case CLOCK_SETTER_TOUCH_BAR:
            MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_THUMB_TO_PEN);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov136_0229cd6c, TimeScreen_ListByTouch)

/* func_ov136_0229ce04 (sub state 2): once the clock's hands are in their place, back to the
 * fields by touch. */
void TimeScreen_SettleHands(TimeScreen *self)
{
    if (ClockSetter_SpinHandsHome(&self->picker)) {
        MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_TOUCH_FIELDS);
    }
}
CLEAN_AS(func_ov136_0229ce04, TimeScreen_SettleHands)

/* func_ov136_0229ce28 (sub state 1): while the pen is down the clock's hands follow it; once it
 * is up they are let go, moving on to their place (sub state 2) or not (sub state 0). */
void TimeScreen_DragHands(TimeScreen *self)
{
    if (data_021fbdd8 == 0) {
        if (ClockSetter_ReleaseHand(&self->picker) != 0) {
            MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_SETTLE_HANDS);
        } else {
            MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_TOUCH_FIELDS);
        }
    } else {
        ClockSetter_DragHand(&self->picker, data_021f6c58, data_021f6c54);
    }
}
CLEAN_AS(func_ov136_0229ce28, TimeScreen_DragHands)

/* func_ov136_0229ce7c (sub state 0): the fields by touch. A button goes on by the keys. A touch
 * that went down or up this frame on OK confirms the time; else on the clock's hands it grabs
 * them (sub state 1), and on the hour or the minute it opens the field's list.
 * QUIRK: a touch that grabs the hands is still tested on the fields. */
void TimeScreen_FieldsByTouch(TimeScreen *self)
{
    if (MenuScene_TakeButtons(time_scene(self), 1) != 0) {
        TimeScreen_ResumeFieldsByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, TIME_SCREEN_OK_BUTTON) != 0) {
        TimeScreen_Confirm(self);
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (ClockSetter_GrabHand(&self->picker, x, y) != 0) {
        MenuScene_SetSubState(time_scene(self), TIME_SCREEN_SUB_DRAG_HANDS);
    }
    int field = ClockSetter_TouchedTimeField(&self->picker, x, y);
    if (field != CLOCK_SETTER_NO_FIELD) {
        TimeScreen_OpenList(self, field);
    }
}
CLEAN_AS(func_ov136_0229ce7c, TimeScreen_FieldsByTouch)

/* func_ov136_0229cf14: the picker's characters and the panel's text colours loaded. */
void TimeScreen_LoadGraphics(TimeScreen *self)
{
    ClockSetter_LoadSprites(&self->picker);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov136_0229cf14, TimeScreen_LoadGraphics)

/* func_ov136_0229cf34: the picker's texts loaded, with its prompt (message 0x8b). */
void TimeScreen_LoadTexts(TimeScreen *self)
{
    ClockSetter_LoadBackground(&self->picker);
    ClockSetter_DrawLabels(&self->picker, TIME_SCREEN_PROMPT);
}
CLEAN_AS(func_ov136_0229cf34, TimeScreen_LoadTexts)

/* func_ov136_0229cf54: the sub screen's background mode 0; layer 6 at priority 2, layers 4 and 3
 * at priority 1, each with its control reset. */
void TimeScreen_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 1);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 1);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov136_0229cf54, TimeScreen_SetUpLayers)

/* func_ov136_0229cfa0: the frame's end: the picker's. */
void TimeScreen_EndFrame(TimeScreen *self)
{
    ClockSetter_Update(&self->picker);
}
CLEAN_AS(func_ov136_0229cfa0, TimeScreen_EndFrame)

/* func_ov136_0229cfb0: the frame's start: the panel's texts closed, the picker's start. */
void TimeScreen_BeginFrame(TimeScreen *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    ClockSetter_EndFrame(&self->picker);
}
CLEAN_AS(func_ov136_0229cfb0, TimeScreen_BeginFrame)

/* func_ov136_0229cfcc */
void TimeScreen_EndInteractiveFrame(TimeScreen *self)
{
    TimeScreen_EndFrame(self);
}
CLEAN_AS(func_ov136_0229cfcc, TimeScreen_EndInteractiveFrame)

/* func_ov136_0229cfd4: the frame's start, then the cursor sprite updated. */
void TimeScreen_BeginInteractiveFrame(TimeScreen *self)
{
    TimeScreen_BeginFrame(self);
    time_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov136_0229cfd4, TimeScreen_BeginInteractiveFrame)

/* func_ov136_0229cfec: the members torn down: the picker's, then the panel's texts closed. */
void TimeScreen_Teardown(TimeScreen *self)
{
    ClockSetter_Teardown(&self->picker);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov136_0229cfec, TimeScreen_Teardown)

/* func_ov136_0229d00c: the setup: the picker for a time (on layers 6, 4 and 3), the cursor at
 * the hour, no flags. */
void TimeScreen_Setup(TimeScreen *self)
{
    ClockSetter_Init(&self->picker, CLOCK_SETTER_MODE_TIME, 6, 4, 3);
    self->place = TIME_SCREEN_PLACE_HOUR;
    self->flags = 0;
}
CLEAN_AS(func_ov136_0229d00c, TimeScreen_Setup)

/* func_ov136_0229d044: layers 6 and 4 scrolled with the wipe. */
void TimeScreen_ScrollWithWipe(TimeScreen *self)
{
    MenuScene_ScrollWipe(time_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(time_scene(self), 4, 0, 0);
}
CLEAN_AS(func_ov136_0229d044, TimeScreen_ScrollWithWipe)

/* func_ov136_0229d064 (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void TimeScreen_WipeOut(TimeScreen *self)
{
    if (MenuScene_StepWipe(time_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(time_scene(self), 5);
    } else {
        TimeScreen_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov136_0229d064, TimeScreen_WipeOut)

/* func_ov136_0229d094 (state 2): the parent told the menu closes, the wipe out started on
 * window 2 (layers 2 and 8, margin 0x30), the layers following it; state 3. */
void TimeScreen_StartWipeOut(TimeScreen *self)
{
    MenuDispatch_SetMode(time_parent(self), TIME_SCREEN_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(time_scene(self), 0xa, 0, 0, 0x30);
    TimeScreen_ScrollWithWipe(self);
    MenuScene_SetState(time_scene(self), TIME_SCREEN_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov136_0229d094, TimeScreen_StartWipeOut)

/* func_ov136_0229d0cc (state 1): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the fields. The layers follow the wipe. */
void TimeScreen_WipeIn(TimeScreen *self)
{
    if (MenuScene_StepWipeBack(time_scene(self), 0)) {
        MenuScene_SetPhase(time_scene(self), 2);
        TimeScreen_ResumeFields(self);
    }
    TimeScreen_ScrollWithWipe(self);
}
CLEAN_AS(func_ov136_0229d0cc, TimeScreen_WipeIn)

/* func_ov136_0229d0f4 (state 0): the layers set up, the picker's texts and graphics loaded, the
 * wipe in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x30), layers 6 and 4
 * shown and following it, the scene drawn, the panel in layout 5 with message 0x21; state 1. */
void TimeScreen_StartWipeIn(TimeScreen *self)
{
    TimeScreen_SetUpLayers();
    TimeScreen_LoadTexts(self);
    TimeScreen_LoadGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(time_scene(self), 0xa, 4, 0, 0x30);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    TimeScreen_ScrollWithWipe(self);
    TimeScreen_SetFlags(self, TIME_SCREEN_FLAG_DRAWN);
    ButtonPanel_SetLayout5(&self->panel, TIME_SCREEN_PANEL_MESSAGE);
    MenuScene_SetState(time_scene(self), TIME_SCREEN_STATE_WIPE_IN);
}
CLEAN_AS(func_ov136_0229d0f4, TimeScreen_StartWipeIn)

/* func_ov136_0229d150 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int TimeScreen_End(TimeScreen *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov136_0229d150, TimeScreen_End)

/* func_ov136_0229d160 (vtable slot 0x58, phase 4): nothing. */
int TimeScreen_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov136_0229d160, TimeScreen_Phase4Idle)

/* func_ov136_0229d164 (vtable slot 0x54, phase 3): nothing. */
int TimeScreen_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov136_0229d164, TimeScreen_Phase3Idle)

/* func_ov136_0229d168 (vtable slot 0x50, phase 2): a frame of the scene in use: its start, its
 * sub state and its end. Answers 1. */
int TimeScreen_RunInteractive(TimeScreen *self)
{
    TimeScreen_BeginInteractiveFrame(self);
    TimeScreen_RunSubState(self);
    TimeScreen_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov136_0229d168, TimeScreen_RunInteractive)

/* func_ov136_0229d184: the sub state's function (TimeScreenSubState) through the table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 16; the game reads past the table for others. */
void TimeScreen_RunSubState(TimeScreen *self)
{
    static const MemberPointer *const sub_states[TIME_SCREEN_SUB_STATES] = {
        &data_ov136_0229d4e8, &data_ov136_0229d4e0, &data_ov136_0229d4d8, &data_ov136_0229d4d0,
        &data_ov136_0229d4c8, &data_ov136_0229d4a0, &data_ov136_0229d4b0, &data_ov136_0229d4b8,
        &data_ov136_0229d4c0, &data_ov136_0229d4f8, &data_ov136_0229d498, &data_ov136_0229d490,
        &data_ov136_0229d488, &data_ov136_0229d480, &data_ov136_0229d478, &data_ov136_0229d4a8,
    };
    MemberTable_InitOnce(&data_ov136_0229d584, data_ov136_0229d5a8, sub_states, TIME_SCREEN_SUB_STATES);
    MemberPointer_CallVoid(&data_ov136_0229d5a8[self->base.sub_state], self);
}
CLEAN_AS(func_ov136_0229d184, TimeScreen_RunSubState)

/* func_ov136_0229d2b0 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (TimeScreenState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int TimeScreen_RunState(TimeScreen *self)
{
    static const MemberPointer *const states[TIME_SCREEN_STATES] = {
        &data_ov136_0229d468,
        &data_ov136_0229d460,
        &data_ov136_0229d470,
        &data_ov136_0229d500,
    };
    MemberTable_InitOnce(&data_ov136_0229d580, data_ov136_0229d588, states, TIME_SCREEN_STATES);
    TimeScreen_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov136_0229d588[self->base.state], self);
    TimeScreen_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov136_0229d2b0, TimeScreen_RunState)

/* func_ov136_0229d344 (vtable slot 0x24): the scene's draw: the cursor sprite (with the keys in
 * use), then, while the scene is drawn (else answers 0), the picker and the panel with the
 * wipe. Answers 1. */
int TimeScreen_Draw(TimeScreen *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (TimeScreen_TestFlags(self, TIME_SCREEN_FLAG_DRAWN) == 0) {
        return 0;
    }
    ClockSetter_Draw(&self->picker, 0, MenuScene_WipeOffsetY(time_scene(self)));
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(time_scene(self)));
    return 1;
}
CLEAN_AS(func_ov136_0229d344, TimeScreen_Draw)

/* func_ov136_0229d398 (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int TimeScreen_Close(TimeScreen *self)
{
    MenuDispatch_ChildClosed(time_parent(self));
    TimeScreen_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov136_0229d398, TimeScreen_Close)

/* func_ov136_0229d3b4 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int TimeScreen_Start(TimeScreen *self)
{
    TimeScreen_Setup(self);
    self->base.state = TIME_SCREEN_STATE_START_WIPE_IN;
    MenuScene_SetPhase(time_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov136_0229d3b4, TimeScreen_Start)

/* func_ov136_0229d3d4 (named by the profile at 0x0229d4f0): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
TimeScreen *TimeScreen_New(void)
{
    TimeScreen *self = MenuScene_Alloc(sizeof(TimeScreen));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov136_0229d510;
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    ClockSetter_Construct(&self->picker);
    return self;
}
CLEAN_AS(func_ov136_0229d3d4, TimeScreen_New)
