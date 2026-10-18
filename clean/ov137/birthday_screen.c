/* The birthday entry screen of overlay 137 (birthday_screen.h): its destructors, its flags, the
 * cursor and its sprite, the fields' lists, the frame and the scene's slots. */
#include "birthday_screen.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"
#include "ov134/clock_setter.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(BirthdayScreen, cursor_sprite) == 0x94, "cursor_sprite");
static_assert(offsetof(BirthdayScreen, panel) == 0xf8 && offsetof(BirthdayScreen, picker) == 0x2c4, "panel");
static_assert(offsetof(BirthdayScreen, flags) == 0x2b74 && offsetof(BirthdayScreen, place) == 0x2b77, "flags");
static_assert(sizeof(BirthdayScreen) == 0x2b78, "size (func_ov137_0229d314)");

/* The scene's vtable. */
extern const u8 data_ov137_0229d440[];

/* The cursor's moves from each place (BirthdayScreenPlace): right, left, down and up. */
extern const u8 data_ov137_0229d358[];
extern const u8 data_ov137_0229d35c[];
extern const u8 data_ov137_0229d360[];
extern const u8 data_ov137_0229d364[];

/* Where the cursor sprite points at the month and the day: x, and y. */
extern const s32 data_ov137_0229d368[];
extern const s32 data_ov137_0229d374[];

/* The pad, and the pen (autoload_2/input.c): down, and gone down or up this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;
#define BIRTHDAY_SCREEN_PAD_A 0x0001
#define BIRTHDAY_SCREEN_PAD_B 0x0002
#define BIRTHDAY_SCREEN_PAD_START 0x0008

/* The panel's OK button. */
#define BIRTHDAY_SCREEN_OK_BUTTON 6

/* The cursor sprite's animations (glide.h): at a field, at the OK button. */
#define BIRTHDAY_SCREEN_ANIM_FIELD 1
#define BIRTHDAY_SCREEN_ANIM_OK 7

/* The picker's prompt and the panel's message. */
#define BIRTHDAY_SCREEN_PROMPT 0x6d
#define BIRTHDAY_SCREEN_PANEL_MESSAGE 0x21

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define BIRTHDAY_SCREEN_PARENT_CLOSE 0x44

static MenuScene *birthday_scene(BirthdayScreen *self)
{
    return &self->base;
}

static CellLayerSprite *birthday_sprite_cells(BirthdayScreen *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *birthday_parent(BirthdayScreen *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void birthday_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void birthday_destroy_members(BirthdayScreen *self)
{
    self->base.vtable = data_ov137_0229d440;
    ClockSetter_Destroy(&self->picker);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(birthday_scene(self));
}

/* func_ov137_0229c4e0 (vtable slot 0x40) */
BirthdayScreen *BirthdayScreen_Destroy(BirthdayScreen *self)
{
    birthday_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov137_0229c4e0, BirthdayScreen_Destroy)

/* func_ov137_0229c518 (vtable slot 0x44) */
BirthdayScreen *BirthdayScreen_Delete(BirthdayScreen *self)
{
    birthday_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov137_0229c518, BirthdayScreen_Delete)

/* func_ov137_0229c554 */
void BirthdayScreen_ClearFlags(BirthdayScreen *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov137_0229c554, BirthdayScreen_ClearFlags)

/* func_ov137_0229c564 */
void BirthdayScreen_SetFlags(BirthdayScreen *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov137_0229c564, BirthdayScreen_SetFlags)

/* func_ov137_0229c574 */
int BirthdayScreen_TestFlags(BirthdayScreen *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov137_0229c574, BirthdayScreen_TestFlags)

/* func_ov137_0229c58c: the cursor moved by the d-pad keys `keys` through the tables of moves:
 * left or right first and, when that did not move it, up or down; whether it moved. The month
 * and the day share a row, OK is below them; up from OK goes to the day.
 * REQUIRES: place < 3; the game reads its tables on for others. */
int BirthdayScreen_MoveCursor(BirthdayScreen *self, int keys)
{
    u8 before = self->place;
    if (KeyRepeat_HasLeft(keys)) {
        self->place = data_ov137_0229d35c[self->place];
    } else if (KeyRepeat_HasRight(keys)) {
        self->place = data_ov137_0229d358[self->place];
    }
    if (before != self->place) {
        return 1;
    }
    if (KeyRepeat_HasUp(keys)) {
        self->place = data_ov137_0229d364[self->place];
    } else if (KeyRepeat_HasDown(keys)) {
        self->place = data_ov137_0229d360[self->place];
    }
    return before != self->place;
}
CLEAN_AS(func_ov137_0229c58c, BirthdayScreen_MoveCursor)

/* func_ov137_0229c628: the cursor sprite's third animation of its set played, the sub state kept
 * to come back to once it ends (sub state 10). */
void BirthdayScreen_PlayReleaseAnim(BirthdayScreen *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_SPRITE_ANIM);
}
CLEAN_AS(func_ov137_0229c628, BirthdayScreen_PlayReleaseAnim)

/* func_ov137_0229c650: the cursor sprite pressed (the second of its set), sub state 9. */
void BirthdayScreen_PressSprite(BirthdayScreen *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_PRESSED);
}
CLEAN_AS(func_ov137_0229c650, BirthdayScreen_PressSprite)

/* func_ov137_0229c668: the cursor sprite shown (the first of its set) and updated. */
void BirthdayScreen_ShowCursorSprite(BirthdayScreen *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    birthday_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov137_0229c668, BirthdayScreen_ShowCursorSprite)

/* func_ov137_0229c684: the cursor sprite eased to (x, y), in two steps when the quick flag is
 * set, else three; the sub state kept to come back to once it stops (sub state 8), and the
 * quick flag cleared. */
void BirthdayScreen_GlideSpriteTo(BirthdayScreen *self, int x, int y)
{
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_QUICK)) {
        Glider_EaseTo(&self->cursor_sprite, x, y, 2, 1);
    } else {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    }
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_SPRITE_MOVE);
    BirthdayScreen_ClearFlags(self, BIRTHDAY_SCREEN_FLAG_QUICK);
}
CLEAN_AS(func_ov137_0229c684, BirthdayScreen_GlideSpriteTo)

/* func_ov137_0229c6e4: the cursor sprite turned to the set of OK when the cursor went there
 * among the fields (else to the set of a field), and eased to the cursor. */
void BirthdayScreen_GlideToCursor(BirthdayScreen *self)
{
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST) == 0 && self->place == BIRTHDAY_SCREEN_PLACE_OK) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = BirthdayScreen_CursorX(self);
    int y = BirthdayScreen_CursorY(self);
    BirthdayScreen_GlideSpriteTo(self, x, y);
}
CLEAN_AS(func_ov137_0229c6e4, BirthdayScreen_GlideToCursor)

/* func_ov137_0229c734: the cursor sprite hidden (no animation) and updated. */
void BirthdayScreen_HideCursorSprite(BirthdayScreen *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    birthday_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov137_0229c734, BirthdayScreen_HideCursorSprite)

/* func_ov137_0229c750: where the cursor sprite points: y. In a list, the list's cursor; at OK,
 * the panel's button 6; else the field's, from the table.
 * REQUIRES: place < 3; the game reads its table on for others. */
int BirthdayScreen_CursorY(BirthdayScreen *self)
{
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST) != 0) {
        return ClockSetter_CursorY(&self->picker);
    }
    u8 place = self->place;
    if (place == BIRTHDAY_SCREEN_PLACE_OK) {
        return ButtonPanel_ButtonY(&self->panel, BIRTHDAY_SCREEN_OK_BUTTON);
    }
    return data_ov137_0229d374[place];
}
CLEAN_AS(func_ov137_0229c750, BirthdayScreen_CursorY)

/* func_ov137_0229c794: ... x.
 * REQUIRES: place < 3; the game reads its table on for others. */
int BirthdayScreen_CursorX(BirthdayScreen *self)
{
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST) != 0) {
        return ClockSetter_CursorX(&self->picker);
    }
    u8 place = self->place;
    if (place == BIRTHDAY_SCREEN_PLACE_OK) {
        return ButtonPanel_ButtonX(&self->panel, BIRTHDAY_SCREEN_OK_BUTTON);
    }
    return data_ov137_0229d368[place];
}
CLEAN_AS(func_ov137_0229c794, BirthdayScreen_CursorX)

/* func_ov137_0229c7d8: the cursor sprite put at the cursor, with OK's animation when the cursor
 * is there among the fields (else a field's), and shown. */
void BirthdayScreen_ShowSpriteAtCursor(BirthdayScreen *self)
{
    int x = BirthdayScreen_CursorX(self);
    int y = BirthdayScreen_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST) == 0 && self->place == BIRTHDAY_SCREEN_PLACE_OK) {
        Glider_SetAnim(&self->cursor_sprite, BIRTHDAY_SCREEN_ANIM_OK);
    } else {
        Glider_SetAnim(&self->cursor_sprite, BIRTHDAY_SCREEN_ANIM_FIELD);
    }
    BirthdayScreen_ShowCursorSprite(self);
}
CLEAN_AS(func_ov137_0229c7d8, BirthdayScreen_ShowSpriteAtCursor)

/* func_ov137_0229c834: on to the open list, by touch or by the keys as the player last used. */
void BirthdayScreen_ResumeList(BirthdayScreen *self)
{
    if (StateFlags_IsClear2()) {
        BirthdayScreen_ResumeListByTouch(self);
    } else {
        BirthdayScreen_ResumeListByKeys(self);
    }
}
CLEAN_AS(func_ov137_0229c834, BirthdayScreen_ResumeList)

/* func_ov137_0229c854: on to the list by the keys: the list's cursor row put at its own y, the
 * sprite following it (flagged), shown there, the key repeat reset (sub state 5). */
void BirthdayScreen_ResumeListByKeys(BirthdayScreen *self)
{
    int y = ClockSetter_CursorY(&self->picker);
    ClockSetter_CursorToY(&self->picker, y);
    BirthdayScreen_SetFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST);
    BirthdayScreen_ShowSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(birthday_scene(self));
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_LIST);
}
CLEAN_AS(func_ov137_0229c854, BirthdayScreen_ResumeListByKeys)

/* func_ov137_0229c890: on to the list by touch: the cursor sprite hidden (sub state 1). */
void BirthdayScreen_ResumeListByTouch(BirthdayScreen *self)
{
    BirthdayScreen_HideCursorSprite(self);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_TOUCH_LIST);
}
CLEAN_AS(func_ov137_0229c890, BirthdayScreen_ResumeListByTouch)

/* func_ov137_0229c8a8: the list closed without a value: the cursor sprite hidden and no longer
 * following it (sub state 13). */
void BirthdayScreen_CancelList(BirthdayScreen *self)
{
    BirthdayScreen_HideCursorSprite(self);
    BirthdayScreen_ClearFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST);
    ClockSetter_CancelList(&self->picker);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_LIST_CLOSE);
}
CLEAN_AS(func_ov137_0229c8a8, BirthdayScreen_CancelList)

/* func_ov137_0229c8d4: the list closed keeping the value under its cursor: the same as
 * BirthdayScreen_CancelList otherwise. */
void BirthdayScreen_PickInList(BirthdayScreen *self)
{
    BirthdayScreen_HideCursorSprite(self);
    BirthdayScreen_ClearFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST);
    ClockSetter_PickRow(&self->picker);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_LIST_CLOSE);
}
CLEAN_AS(func_ov137_0229c8d4, BirthdayScreen_PickInList)

/* func_ov137_0229c900: the list of picker field `field` opened, the cursor sprite hidden
 * meanwhile (sub state 12). */
void BirthdayScreen_OpenList(BirthdayScreen *self, int field)
{
    BirthdayScreen_HideCursorSprite(self);
    ClockSetter_OpenList(&self->picker, field);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_LIST_OPEN);
}
CLEAN_AS(func_ov137_0229c900, BirthdayScreen_OpenList)

/* func_ov137_0229c92c: the birthday confirmed: the panel's OK button selected, state 2 next (the
 * wipe out) once its press is over (sub state 11); the month and day entered set as the
 * current player's birthday. */
void BirthdayScreen_Confirm(BirthdayScreen *self)
{
    DateTime when = {0};

    ButtonPanel_Select(&self->panel, BIRTHDAY_SCREEN_OK_BUTTON);
    MenuScene_SetState(birthday_scene(self), BIRTHDAY_SCREEN_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_OK_PRESSED);
    u8 *record = PlayerRecords_Current();
    ClockSetter_CopyValue(&self->picker, &when);
    PlayerRecord_SetBirthday(record, when.month, when.day);
}
CLEAN_AS(func_ov137_0229c92c, BirthdayScreen_Confirm)

/* func_ov137_0229c978: back to the fields, by touch or by the keys as the player last used. */
void BirthdayScreen_ResumeFields(BirthdayScreen *self)
{
    if (StateFlags_IsClear2()) {
        BirthdayScreen_ResumeFieldsByTouch(self);
    } else {
        BirthdayScreen_ResumeFieldsByKeys(self);
    }
}
CLEAN_AS(func_ov137_0229c978, BirthdayScreen_ResumeFields)

/* func_ov137_0229c998: back to the fields by the keys: the cursor sprite shown at the cursor,
 * the key repeat reset (sub state 4). */
void BirthdayScreen_ResumeFieldsByKeys(BirthdayScreen *self)
{
    BirthdayScreen_ShowSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(birthday_scene(self));
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_FIELDS);
}
CLEAN_AS(func_ov137_0229c998, BirthdayScreen_ResumeFieldsByKeys)

/* func_ov137_0229c9b4: back to the fields by touch: the cursor sprite hidden (sub state 0). */
void BirthdayScreen_ResumeFieldsByTouch(BirthdayScreen *self)
{
    BirthdayScreen_HideCursorSprite(self);
    MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_TOUCH_FIELDS);
}
CLEAN_AS(func_ov137_0229c9b4, BirthdayScreen_ResumeFieldsByTouch)

/* func_ov137_0229c9cc (sub state 13): once the list has closed, the cursor at the picker's field
 * (OK for none) and back to the fields.
 * QUIRK: a field 0 would wrap the place (u8); the picker of a month and day only has 1, 2 and 6. */
void BirthdayScreen_WaitListClosed(BirthdayScreen *self)
{
    if (ClockSetter_CloseListStep(&self->picker) == 0) {
        return;
    }
    int field = ClockSetter_Focus(&self->picker);
    if (field == CLOCK_SETTER_NO_FIELD) {
        self->place = BIRTHDAY_SCREEN_PLACE_OK;
    } else {
        self->place = (u8) (field - BIRTHDAY_SCREEN_FIELD_OF_PLACE);
    }
    BirthdayScreen_ResumeFields(self);
}
CLEAN_AS(func_ov137_0229c9cc, BirthdayScreen_WaitListClosed)

/* func_ov137_0229ca0c (sub state 12): once the list has opened, on to it. */
void BirthdayScreen_WaitListOpen(BirthdayScreen *self)
{
    if (ClockSetter_OpenListStep(&self->picker)) {
        BirthdayScreen_ResumeList(self);
    }
}
CLEAN_AS(func_ov137_0229ca0c, BirthdayScreen_WaitListOpen)

/* func_ov137_0229ca2c (sub state 11): while the panel's OK button is pressed, the cursor sprite
 * (when it shows) follows the press; once it is over, the sprite hidden and the states run
 * (phase 1: the wipe out). */
void BirthdayScreen_FollowOkPress(BirthdayScreen *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        BirthdayScreen_HideCursorSprite(self);
        MenuScene_SetPhase(birthday_scene(self), 1);
        return;
    }
    if (CellLayerSprite_AnimNumber(birthday_sprite_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}
CLEAN_AS(func_ov137_0229ca2c, BirthdayScreen_FollowOkPress)

/* func_ov137_0229ca90 (sub state 10): once the cursor sprite's animation is over, it is shown
 * again and the sub state kept is next. */
void BirthdayScreen_WaitSpriteAnim(BirthdayScreen *self)
{
    if (CellLayerSprite_IsDone(birthday_sprite_cells(self))) {
        BirthdayScreen_ShowCursorSprite(self);
        MenuScene_SetSubState(birthday_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov137_0229ca90, BirthdayScreen_WaitSpriteAnim)

/* func_ov137_0229cab8 (sub state 9): once the cursor sprite's press is over. In a list: on its
 * scroll bar, the bar by the keys (sub state 6); else the value under the cursor taken and the
 * list closed. Among the fields: at OK the birthday is confirmed, at a field its list opens.
 * QUIRK: unlike overlay 136, the list closes keeping its value whether ClockSetter_PickCursorRow took
 * one or not. */
void BirthdayScreen_AfterPress(BirthdayScreen *self)
{
    if (CellLayerSprite_IsDone(birthday_sprite_cells(self)) == 0) {
        return;
    }
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_IN_LIST) != 0) {
        if (ClockSetter_PressThumbByKey(&self->picker) != 0) {
            MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_BAR);
        } else {
            ClockSetter_PickCursorRow(&self->picker);
            BirthdayScreen_PickInList(self);
        }
    } else if (self->place == BIRTHDAY_SCREEN_PLACE_OK) {
        BirthdayScreen_Confirm(self);
    } else {
        BirthdayScreen_OpenList(self, self->place + BIRTHDAY_SCREEN_FIELD_OF_PLACE);
    }
}
CLEAN_AS(func_ov137_0229cab8, BirthdayScreen_AfterPress)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov137_0229d4a0; /* the states' guard */
extern u32 data_ov137_0229d4a4; /* the sub states' guard */
extern MemberPointer data_ov137_0229d4a8[BIRTHDAY_SCREEN_STATES];
extern MemberPointer data_ov137_0229d4c8[BIRTHDAY_SCREEN_SUB_STATES];
extern const MemberPointer data_ov137_0229d3a0, data_ov137_0229d3a8, data_ov137_0229d3b0, data_ov137_0229d3b8,
    data_ov137_0229d3c0, data_ov137_0229d3c8, data_ov137_0229d3d0, data_ov137_0229d3d8, data_ov137_0229d3e0,
    data_ov137_0229d3e8, data_ov137_0229d3f0, data_ov137_0229d3f8, data_ov137_0229d400, data_ov137_0229d408,
    data_ov137_0229d410, data_ov137_0229d418, data_ov137_0229d420, data_ov137_0229d430;

/* func_ov137_0229cb20 (sub state 8): once the cursor sprite stops, the sub state kept is run
 * again, this frame. */
void BirthdayScreen_WaitCursorSprite(BirthdayScreen *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(birthday_scene(self), self->return_sub_state);
        BirthdayScreen_RunSubState(self);
    }
}
CLEAN_AS(func_ov137_0229cb20, BirthdayScreen_WaitCursorSprite)

/* func_ov137_0229cb48 (sub state 7): once the picker's cursor is back from the scroll bar, the
 * list by the keys again, after the release animation; the cursor sprite follows meanwhile. */
void BirthdayScreen_ReturnFromBar(BirthdayScreen *self)
{
    if (ClockSetter_SettleThumb(&self->picker)) {
        MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_LIST);
        BirthdayScreen_PlayReleaseAnim(self);
    }
    int x = BirthdayScreen_CursorX(self);
    int y = BirthdayScreen_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
}
CLEAN_AS(func_ov137_0229cb48, BirthdayScreen_ReturnFromBar)

/* func_ov137_0229cb90 (sub state 6): while A is held the scroll bar moves by up and down, the
 * cursor sprite following; once A is let go the bar is too (sub state 7). */
void BirthdayScreen_ListBarByKeys(BirthdayScreen *self)
{
    if ((data_021fbe40.held & BIRTHDAY_SCREEN_PAD_A) != 0) {
        ClockSetter_MoveThumbByKeys(&self->picker);
        int x = BirthdayScreen_CursorX(self);
        int y = BirthdayScreen_CursorY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    } else {
        ClockSetter_ReleaseThumb(&self->picker);
        MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_BAR_RETURN);
    }
}
CLEAN_AS(func_ov137_0229cb90, BirthdayScreen_ListBarByKeys)

/* func_ov137_0229cbe8 (sub state 5): the list by the keys. A touch goes on by touch. Else the
 * picker takes the d-pad: a step glides the cursor sprite quickly, a scroll puts it at the
 * cursor at once, a move glides it; with none of these A presses the sprite and B closes the
 * list without a value. */
void BirthdayScreen_ListByKeys(BirthdayScreen *self)
{
    if (MenuScene_TakeTouch(birthday_scene(self)) != 0) {
        BirthdayScreen_ResumeListByTouch(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(birthday_scene(self));
    switch (ClockSetter_ListKeys(&self->picker, keys)) {
        case CLOCK_SETTER_KEYS_STEPPED:
            BirthdayScreen_SetFlags(self, BIRTHDAY_SCREEN_FLAG_QUICK);
            BirthdayScreen_GlideToCursor(self);
            break;
        case CLOCK_SETTER_KEYS_FAST: {
            int x = BirthdayScreen_CursorX(self);
            int y = BirthdayScreen_CursorY(self);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
            break;
        }
        case CLOCK_SETTER_KEYS_NONE: {
            u16 pressed = data_021fbe40.pressed;
            if ((pressed & BIRTHDAY_SCREEN_PAD_A) != 0) {
                BirthdayScreen_PressSprite(self);
            } else if ((pressed & BIRTHDAY_SCREEN_PAD_B) != 0) {
                BirthdayScreen_CancelList(self);
            }
            break;
        }
        default:
            BirthdayScreen_GlideToCursor(self);
            break;
    }
}
CLEAN_AS(func_ov137_0229cbe8, BirthdayScreen_ListByKeys)

/* func_ov137_0229cc80 (sub state 4): the fields by the keys. A touch goes on by touch; a move of
 * the cursor glides the sprite there; else A presses the sprite and START confirms the
 * birthday. */
void BirthdayScreen_FieldsByKeys(BirthdayScreen *self)
{
    if (MenuScene_TakeTouch(birthday_scene(self)) != 0) {
        BirthdayScreen_ResumeFieldsByTouch(self);
        return;
    }
    if (BirthdayScreen_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(birthday_scene(self))) != 0) {
        BirthdayScreen_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & BIRTHDAY_SCREEN_PAD_A) != 0) {
        BirthdayScreen_PressSprite(self);
    } else if ((pressed & BIRTHDAY_SCREEN_PAD_START) != 0) {
        BirthdayScreen_HideCursorSprite(self);
        BirthdayScreen_Confirm(self);
    }
}
CLEAN_AS(func_ov137_0229cc80, BirthdayScreen_FieldsByKeys)

/* func_ov137_0229cce4 (sub state 3): while the pen is down on the scroll bar off its thumb, the
 * thumb moves toward it (ClockSetter_ThumbTowardPen); once it is up, the thumb let go and back to
 * the list by touch (sub state 1). */
void BirthdayScreen_ThumbTowardPen(BirthdayScreen *self)
{
    if (data_021fbdd8 != 0) {
        ClockSetter_ThumbTowardPen(&self->picker, data_021f6c54);
    } else {
        ClockSetter_ReleaseThumb(&self->picker);
        MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_TOUCH_LIST);
    }
}
CLEAN_AS(func_ov137_0229cce4, BirthdayScreen_ThumbTowardPen)

/* func_ov137_0229cd20 (sub state 2): ... with the thumb held at the pen (ClockSetter_DragThumb). */
void BirthdayScreen_DragThumb(BirthdayScreen *self)
{
    if (data_021fbdd8 != 0) {
        ClockSetter_DragThumb(&self->picker, data_021f6c54);
    } else {
        ClockSetter_ReleaseThumb(&self->picker);
        MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_TOUCH_LIST);
    }
}
CLEAN_AS(func_ov137_0229cd20, BirthdayScreen_DragThumb)

/* func_ov137_0229cd5c (sub state 1): the list by touch. A button goes on by the keys. A touch
 * that went down or up this frame: on a value it is taken (the list closes), outside the list
 * closes without one, on the scroll bar's thumb it is held (sub state 2), on the bar off the
 * thumb the thumb moves toward the pen (sub state 3). */
void BirthdayScreen_ListByTouch(BirthdayScreen *self)
{
    if (MenuScene_TakeButtons(birthday_scene(self), 1) != 0) {
        BirthdayScreen_ResumeListByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    switch (ClockSetter_TouchList(&self->picker, data_021f6c58, data_021f6c54)) {
        case CLOCK_SETTER_TOUCH_PICKED:
            BirthdayScreen_PickInList(self);
            break;
        case CLOCK_SETTER_TOUCH_OUTSIDE:
            BirthdayScreen_CancelList(self);
            break;
        case CLOCK_SETTER_TOUCH_THUMB:
            MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_DRAG_THUMB);
            break;
        case CLOCK_SETTER_TOUCH_BAR:
            MenuScene_SetSubState(birthday_scene(self), BIRTHDAY_SCREEN_SUB_THUMB_TO_PEN);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov137_0229cd5c, BirthdayScreen_ListByTouch)

/* func_ov137_0229cdf4 (sub state 0): the fields by touch. A button goes on by the keys. A touch
 * that went down or up this frame on OK confirms the birthday; on the month or the day it opens
 * the field's list. */
void BirthdayScreen_FieldsByTouch(BirthdayScreen *self)
{
    if (MenuScene_TakeButtons(birthday_scene(self), 1) != 0) {
        BirthdayScreen_ResumeFieldsByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, BIRTHDAY_SCREEN_OK_BUTTON) != 0) {
        BirthdayScreen_Confirm(self);
        return;
    }
    int field = ClockSetter_TouchedMonthDayField(&self->picker, data_021f6c58, data_021f6c54);
    if (field != CLOCK_SETTER_NO_FIELD) {
        BirthdayScreen_OpenList(self, field);
    }
}
CLEAN_AS(func_ov137_0229cdf4, BirthdayScreen_FieldsByTouch)

/* func_ov137_0229ce70: the picker's characters and the panel's text colours loaded. */
void BirthdayScreen_LoadGraphics(BirthdayScreen *self)
{
    ClockSetter_LoadSprites(&self->picker);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov137_0229ce70, BirthdayScreen_LoadGraphics)

/* func_ov137_0229ce90: the picker's texts loaded, with its prompt (message 0x6d). */
void BirthdayScreen_LoadTexts(BirthdayScreen *self)
{
    ClockSetter_LoadBackground(&self->picker);
    ClockSetter_DrawLabels(&self->picker, BIRTHDAY_SCREEN_PROMPT);
}
CLEAN_AS(func_ov137_0229ce90, BirthdayScreen_LoadTexts)

/* func_ov137_0229ceb0: the sub screen's background mode 0; layer 6 at priority 2, layers 4 and 3
 * at priority 1, each with its control reset. */
void BirthdayScreen_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 1);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 1);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov137_0229ceb0, BirthdayScreen_SetUpLayers)

/* func_ov137_0229cefc: the frame's end: the picker's. */
void BirthdayScreen_EndFrame(BirthdayScreen *self)
{
    ClockSetter_Update(&self->picker);
}
CLEAN_AS(func_ov137_0229cefc, BirthdayScreen_EndFrame)

/* func_ov137_0229cf0c: the frame's start: the panel's texts closed, the picker's start. */
void BirthdayScreen_BeginFrame(BirthdayScreen *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    ClockSetter_EndFrame(&self->picker);
}
CLEAN_AS(func_ov137_0229cf0c, BirthdayScreen_BeginFrame)

/* func_ov137_0229cf28 */
void BirthdayScreen_EndInteractiveFrame(BirthdayScreen *self)
{
    BirthdayScreen_EndFrame(self);
}
CLEAN_AS(func_ov137_0229cf28, BirthdayScreen_EndInteractiveFrame)

/* func_ov137_0229cf30: the frame's start, then the cursor sprite updated. */
void BirthdayScreen_BeginInteractiveFrame(BirthdayScreen *self)
{
    BirthdayScreen_BeginFrame(self);
    birthday_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov137_0229cf30, BirthdayScreen_BeginInteractiveFrame)

/* func_ov137_0229cf48: the members torn down: the picker's, then the panel's texts closed. */
void BirthdayScreen_Teardown(BirthdayScreen *self)
{
    ClockSetter_Teardown(&self->picker);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov137_0229cf48, BirthdayScreen_Teardown)

/* func_ov137_0229cf68: the setup: the picker for a month and day (on layers 6, 4 and 3), the
 * cursor at the month, no flags. */
void BirthdayScreen_Setup(BirthdayScreen *self)
{
    ClockSetter_Init(&self->picker, CLOCK_SETTER_MODE_MONTH_DAY, 6, 4, 3);
    self->place = BIRTHDAY_SCREEN_PLACE_MONTH;
    self->flags = 0;
}
CLEAN_AS(func_ov137_0229cf68, BirthdayScreen_Setup)

/* func_ov137_0229cfa0: layers 6 and 4 scrolled with the wipe. */
void BirthdayScreen_ScrollWithWipe(BirthdayScreen *self)
{
    MenuScene_ScrollWipe(birthday_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(birthday_scene(self), 4, 0, 0);
}
CLEAN_AS(func_ov137_0229cfa0, BirthdayScreen_ScrollWithWipe)

/* func_ov137_0229cfc0 (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void BirthdayScreen_WipeOut(BirthdayScreen *self)
{
    if (MenuScene_StepWipe(birthday_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(birthday_scene(self), 5);
    } else {
        BirthdayScreen_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov137_0229cfc0, BirthdayScreen_WipeOut)

/* func_ov137_0229cff0 (state 2): the parent told the menu closes, the wipe out started on
 * window 2 (layers 2 and 8, margin 0x30), the layers following it; state 3. */
void BirthdayScreen_StartWipeOut(BirthdayScreen *self)
{
    MenuDispatch_SetMode(birthday_parent(self), BIRTHDAY_SCREEN_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(birthday_scene(self), 0xa, 0, 0, 0x30);
    BirthdayScreen_ScrollWithWipe(self);
    MenuScene_SetState(birthday_scene(self), BIRTHDAY_SCREEN_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov137_0229cff0, BirthdayScreen_StartWipeOut)

/* func_ov137_0229d028 (state 1): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the fields. The layers follow the wipe. */
void BirthdayScreen_WipeIn(BirthdayScreen *self)
{
    if (MenuScene_StepWipeBack(birthday_scene(self), 0)) {
        MenuScene_SetPhase(birthday_scene(self), 2);
        BirthdayScreen_ResumeFields(self);
    }
    BirthdayScreen_ScrollWithWipe(self);
}
CLEAN_AS(func_ov137_0229d028, BirthdayScreen_WipeIn)

/* func_ov137_0229d050 (state 0): the layers set up, the picker's texts and graphics loaded, the
 * wipe in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x30), layers 6 and 4
 * shown and following it, the scene drawn, the panel in layout 5 with message 0x21; state 1. */
void BirthdayScreen_StartWipeIn(BirthdayScreen *self)
{
    BirthdayScreen_SetUpLayers();
    BirthdayScreen_LoadTexts(self);
    BirthdayScreen_LoadGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(birthday_scene(self), 0xa, 4, 0, 0x30);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    BirthdayScreen_ScrollWithWipe(self);
    BirthdayScreen_SetFlags(self, BIRTHDAY_SCREEN_FLAG_DRAWN);
    ButtonPanel_SetLayout5(&self->panel, BIRTHDAY_SCREEN_PANEL_MESSAGE);
    MenuScene_SetState(birthday_scene(self), BIRTHDAY_SCREEN_STATE_WIPE_IN);
}
CLEAN_AS(func_ov137_0229d050, BirthdayScreen_StartWipeIn)

/* func_ov137_0229d0ac (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int BirthdayScreen_End(BirthdayScreen *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov137_0229d0ac, BirthdayScreen_End)

/* func_ov137_0229d0bc (vtable slot 0x58, phase 4): nothing. */
int BirthdayScreen_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov137_0229d0bc, BirthdayScreen_Phase4Idle)

/* func_ov137_0229d0c0 (vtable slot 0x54, phase 3): nothing. */
int BirthdayScreen_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov137_0229d0c0, BirthdayScreen_Phase3Idle)

/* func_ov137_0229d0c4 (vtable slot 0x50, phase 2): a frame of the scene in use: its start, its
 * sub state and its end. Answers 1. */
int BirthdayScreen_RunInteractive(BirthdayScreen *self)
{
    BirthdayScreen_BeginInteractiveFrame(self);
    BirthdayScreen_RunSubState(self);
    BirthdayScreen_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov137_0229d0c4, BirthdayScreen_RunInteractive)

/* func_ov137_0229d0e0: the sub state's function (BirthdayScreenSubState) through the table of
 * member functions, filled once from its constants.
 * REQUIRES: the sub state is below 14; the game reads past the table for others. */
void BirthdayScreen_RunSubState(BirthdayScreen *self)
{
    static const MemberPointer *const sub_states[BIRTHDAY_SCREEN_SUB_STATES] = {
        &data_ov137_0229d418, &data_ov137_0229d410, &data_ov137_0229d408, &data_ov137_0229d3e0, &data_ov137_0229d3f0,
        &data_ov137_0229d3f8, &data_ov137_0229d400, &data_ov137_0229d420, &data_ov137_0229d3d8, &data_ov137_0229d3d0,
        &data_ov137_0229d3c8, &data_ov137_0229d3c0, &data_ov137_0229d3b8, &data_ov137_0229d3e8,
    };
    MemberTable_InitOnce(&data_ov137_0229d4a4, data_ov137_0229d4c8, sub_states, BIRTHDAY_SCREEN_SUB_STATES);
    MemberPointer_CallVoid(&data_ov137_0229d4c8[self->base.sub_state], self);
}
CLEAN_AS(func_ov137_0229d0e0, BirthdayScreen_RunSubState)

/* func_ov137_0229d1f0 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (BirthdayScreenState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int BirthdayScreen_RunState(BirthdayScreen *self)
{
    static const MemberPointer *const states[BIRTHDAY_SCREEN_STATES] = {
        &data_ov137_0229d3a8,
        &data_ov137_0229d3a0,
        &data_ov137_0229d3b0,
        &data_ov137_0229d430,
    };
    MemberTable_InitOnce(&data_ov137_0229d4a0, data_ov137_0229d4a8, states, BIRTHDAY_SCREEN_STATES);
    BirthdayScreen_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov137_0229d4a8[self->base.state], self);
    BirthdayScreen_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov137_0229d1f0, BirthdayScreen_RunState)

/* func_ov137_0229d284 (vtable slot 0x24): the scene's draw: the cursor sprite (with the keys in
 * use), then, while the scene is drawn (else answers 0), the picker and the panel with the
 * wipe. Answers 1. */
int BirthdayScreen_Draw(BirthdayScreen *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (BirthdayScreen_TestFlags(self, BIRTHDAY_SCREEN_FLAG_DRAWN) == 0) {
        return 0;
    }
    ClockSetter_Draw(&self->picker, 0, MenuScene_WipeOffsetY(birthday_scene(self)));
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(birthday_scene(self)));
    return 1;
}
CLEAN_AS(func_ov137_0229d284, BirthdayScreen_Draw)

/* func_ov137_0229d2d8 (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int BirthdayScreen_Close(BirthdayScreen *self)
{
    MenuDispatch_ChildClosed(birthday_parent(self));
    BirthdayScreen_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov137_0229d2d8, BirthdayScreen_Close)

/* func_ov137_0229d2f4 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int BirthdayScreen_Start(BirthdayScreen *self)
{
    BirthdayScreen_Setup(self);
    self->base.state = BIRTHDAY_SCREEN_STATE_START_WIPE_IN;
    MenuScene_SetPhase(birthday_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov137_0229d2f4, BirthdayScreen_Start)

/* func_ov137_0229d314 (named by the profile at 0x0229d428): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
BirthdayScreen *BirthdayScreen_New(void)
{
    BirthdayScreen *self = MenuScene_Alloc(sizeof(BirthdayScreen));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov137_0229d440;
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    ClockSetter_Construct(&self->picker);
    return self;
}
CLEAN_AS(func_ov137_0229d314, BirthdayScreen_New)
