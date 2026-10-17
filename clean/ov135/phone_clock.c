/* The clock setting screen of overlay 135 (phone_clock.h): its destructors, its flags, the
 * cursor and its sprite, the fields' editing, the clock set, its sub states and states, and its
 * scene slots. */
#include "phone_clock.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/cell_layer_sprite.h"
#include "main/clock.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/global_021cfc98.h"
#include "main/group_params.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(PhoneClock, return_sub_state) == 0x94, "bytes");
static_assert(offsetof(PhoneClock, cursor) == 0x95 && offsetof(PhoneClock, cursor_sprite) == 0x98, "sprite");
static_assert(offsetof(PhoneClock, panel) == 0xfc && offsetof(PhoneClock, editor) == 0x2c8, "panel");
static_assert(sizeof(PhoneClock) == 0x2b78, "size (func_ov135_0229d4b8)");

/* The scene's vtable. */
extern const u8 data_ov135_0229d610[];

/* The cursor's moves: the place each place goes to by left, right, down and up. */
extern const u8 data_ov135_0229d4fc[8];
extern const u8 data_ov135_0229d504[8];
extern const u8 data_ov135_0229d50c[8];
extern const u8 data_ov135_0229d514[8];

/* The fields' places of the cursor sprite: x, and y (the buttons' are the panel's). */
extern const s32 data_ov135_0229d51c[PHONE_CLOCK_PLACES];
extern const s32 data_ov135_0229d538[PHONE_CLOCK_PLACES];

/* The pad, and the pen (autoload_2/input.c): down, and gone down or up this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;
#define PHONE_CLOCK_PAD_A 0x0001
#define PHONE_CLOCK_PAD_B 0x0002
#define PHONE_CLOCK_PAD_START 0x0008

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* Overlay 134's object, the clock's fields (called by symbol; what each does is told where it
 * is used). */
extern int func_ov134_022997b0(void *editor);
extern int func_ov134_022997dc(void *editor, void *keys);
extern void func_ov134_02299980(unsigned char *editor, int value);
extern int func_ov134_022999ac(void *editor);
extern int func_ov134_022999e0(void *editor);
extern int func_ov134_02299a60(void *editor);
extern int func_ov134_02299a84(void *editor);
extern void func_ov134_02299a90(void *editor);
extern void func_ov134_02299af0(void *editor, int y);
extern void func_ov134_02299b18(int *editor, int y);
extern int func_ov134_02299b70(void *editor);
extern int func_ov134_0229a1f0(void *editor, int x, int y);
extern int func_ov134_0229a24c(void *editor);
extern void func_ov134_0229a398(void *editor);
extern void func_ov134_0229a3e4(void *editor);
extern int func_ov134_0229a4e4(void *editor);
extern void func_ov134_0229a5c8(void *editor, int field);
extern unsigned char func_ov134_0229a8a0(void *editor);
extern int func_ov134_0229abd4(void *editor, int x, int y);
extern int func_ov134_0229b014(int editor);
extern int func_ov134_0229b034(void *editor);
extern void func_ov134_0229b108(void *editor, int x, int y);
extern int func_ov134_0229b168(void *editor, int x, int y);
extern void func_ov134_0229b220(char *editor, void *b, char *y);
extern int func_ov134_0229b954(void *editor);
extern void func_ov134_0229ba10(void *editor, unsigned int message);
extern int func_ov134_0229baec(unsigned char *editor);
extern int func_ov134_0229bbbc(char *editor);
extern void func_ov134_0229bbdc(int editor, int when);
extern void func_ov134_0229bbe8(void *editor);
extern void func_ov134_0229bcac(void *editor);
extern void func_ov134_0229bcf0(void *editor);
extern void func_ov134_0229bd2c(int editor);
extern void func_ov134_0229bd38(void *editor, int a, int b, int c, u8 d);
extern char *func_ov134_0229beb0(char *editor);
extern void *func_ov134_0229bed4(void *editor);

/* The panel's buttons of the two places past the fields. */
#define PHONE_CLOCK_SET_BUTTON 6
#define PHONE_CLOCK_CANCEL_BUTTON 7

/* The cursor sprite's animations (glide.h): at a field, at a button. */
#define PHONE_CLOCK_ANIM_FIELD GLIDER_ANIM_SET_A
#define PHONE_CLOCK_ANIM_BUTTON GLIDER_ANIM_SET_B

/* overlay 134's answer of no field (PhoneClock_BrowseByTouch, PhoneClock_WaitFieldClosed). */
#define PHONE_CLOCK_NO_FIELD 6

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define PHONE_CLOCK_PARENT_CLOSE 0x44

/* GroupParams' mode of overlay 138's screen (group 0x2a), for which the setup asks overlay
 * 134's object for something more (func_ov134_0229bd2c). */
#define PHONE_CLOCK_MODE_138 0x33

static MenuScene *clock_scene(PhoneClock *self)
{
    return &self->base;
}

static u16 *clock_flags(PhoneClock *self)
{
    return (u16 *) (void *) &self->base.unk_91[1];
}

static CellLayerSprite *clock_sprite_cells(PhoneClock *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *clock_parent(PhoneClock *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void clock_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

static int clock_at_button(PhoneClock *self)
{
    return self->cursor == PHONE_CLOCK_SET || self->cursor == PHONE_CLOCK_CANCEL;
}

/* The members' destructors, last member first, then the base's. */
static void clock_destroy_members(PhoneClock *self)
{
    self->base.vtable = data_ov135_0229d610;
    func_ov134_0229beb0((char *) self->editor);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(clock_scene(self));
}

/* func_ov135_0229c4e0 (vtable slot 0x40) */
PhoneClock *PhoneClock_Destroy(PhoneClock *self)
{
    clock_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov135_0229c4e0, PhoneClock_Destroy)

/* func_ov135_0229c518 (vtable slot 0x44) */
PhoneClock *PhoneClock_Delete(PhoneClock *self)
{
    clock_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov135_0229c518, PhoneClock_Delete)

/* func_ov135_0229c554 */
void PhoneClock_ClearFlags(PhoneClock *self, u16 flags)
{
    u16 *bits = clock_flags(self);
    *bits = (u16) (*bits & ~flags);
}
CLEAN_AS(func_ov135_0229c554, PhoneClock_ClearFlags)

/* func_ov135_0229c564 */
void PhoneClock_SetFlags(PhoneClock *self, u16 flags)
{
    u16 *bits = clock_flags(self);
    *bits = (u16) (*bits | flags);
}
CLEAN_AS(func_ov135_0229c564, PhoneClock_SetFlags)

/* func_ov135_0229c574 */
int PhoneClock_TestFlags(PhoneClock *self, unsigned int flags)
{
    return (*clock_flags(self) & flags) != 0;
}
CLEAN_AS(func_ov135_0229c574, PhoneClock_TestFlags)

/* func_ov135_0229c588: the cursor moved by the d-pad keys `keys` along the tables; whether it
 * moved. Left and right are tried first; up and down only when those left it where it was.
 * REQUIRES: cursor < 8; the game reads its tables on for others. */
int PhoneClock_MoveCursor(PhoneClock *self, u32 keys)
{
    u8 before = self->cursor;
    if (KeyRepeat_HasLeft((int) keys)) {
        self->cursor = data_ov135_0229d4fc[self->cursor];
    } else if (KeyRepeat_HasRight((int) keys)) {
        self->cursor = data_ov135_0229d504[self->cursor];
    }
    if (before != self->cursor) {
        return 1;
    }
    if (KeyRepeat_HasUp((int) keys)) {
        self->cursor = data_ov135_0229d514[self->cursor];
    } else if (KeyRepeat_HasDown((int) keys)) {
        self->cursor = data_ov135_0229d50c[self->cursor];
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov135_0229c588, PhoneClock_MoveCursor)

/* func_ov135_0229c630: the cursor sprite shows the third of its set, the sub state kept to come
 * back to once it is over (sub state 12). */
void PhoneClock_ShowSpriteThird(PhoneClock *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_SHOW_SPRITE);
}
CLEAN_AS(func_ov135_0229c630, PhoneClock_ShowSpriteThird)

/* func_ov135_0229c654: the cursor sprite pressed (the second of its set), the pick waited for
 * (sub state 11). */
void PhoneClock_PressCursorSprite(PhoneClock *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_PRESS);
}
CLEAN_AS(func_ov135_0229c654, PhoneClock_PressCursorSprite)

/* func_ov135_0229c66c: the cursor sprite shown (the first of its set) and updated. */
void PhoneClock_ShowCursorSprite(PhoneClock *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    clock_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov135_0229c66c, PhoneClock_ShowCursorSprite)

/* func_ov135_0229c688: the cursor sprite eased to (x, y) in three steps (two when flagged quick,
 * the flag cleared after), the sub state kept to come back to once it stops (sub state 10). */
void PhoneClock_GlideTo(PhoneClock *self, int x, int y)
{
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_QUICK)) {
        Glider_EaseTo(&self->cursor_sprite, x, y, 2, 1);
    } else {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    }
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_SPRITE_MOVE);
    PhoneClock_ClearFlags(self, PHONE_CLOCK_FLAG_QUICK);
}
CLEAN_AS(func_ov135_0229c688, PhoneClock_GlideTo)

/* func_ov135_0229c6e8: the cursor sprite turned (to set B at a button while no field is edited,
 * else to set A) and eased to the cursor. */
void PhoneClock_GlideToCursor(PhoneClock *self)
{
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_EDITING) != 0 || !clock_at_button(self)) {
        Glider_TurnToSetA(&self->cursor_sprite);
    } else {
        Glider_TurnToSetB(&self->cursor_sprite);
    }
    int x = PhoneClock_CursorX(self);
    int y = PhoneClock_CursorY(self);
    PhoneClock_GlideTo(self, x, y);
}
CLEAN_AS(func_ov135_0229c6e8, PhoneClock_GlideToCursor)

/* func_ov135_0229c738: the cursor sprite hidden (no animation) and updated. */
void PhoneClock_HideCursorSprite(PhoneClock *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    clock_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov135_0229c738, PhoneClock_HideCursorSprite)

/* func_ov135_0229c754: where the cursor sprite points: y. While a field is edited, overlay 134's
 * (func_ov134_022999ac); at a button, the panel button's; else the field's from the table.
 * REQUIRES: cursor < 7 while no field is edited; the game reads its table on for others. */
int PhoneClock_CursorY(PhoneClock *self)
{
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_EDITING)) {
        return func_ov134_022999ac(self->editor);
    }
    switch (self->cursor) {
        case PHONE_CLOCK_SET:
            return ButtonPanel_ButtonY(&self->panel, PHONE_CLOCK_SET_BUTTON);
        case PHONE_CLOCK_CANCEL:
            return ButtonPanel_ButtonY(&self->panel, PHONE_CLOCK_CANCEL_BUTTON);
        default:
            return data_ov135_0229d538[self->cursor];
    }
}
CLEAN_AS(func_ov135_0229c754, PhoneClock_CursorY)

/* func_ov135_0229c7a8: ... x (overlay 134's by func_ov134_022999e0). */
int PhoneClock_CursorX(PhoneClock *self)
{
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_EDITING)) {
        return func_ov134_022999e0(self->editor);
    }
    switch (self->cursor) {
        case PHONE_CLOCK_SET:
            return ButtonPanel_ButtonX(&self->panel, PHONE_CLOCK_SET_BUTTON);
        case PHONE_CLOCK_CANCEL:
            return ButtonPanel_ButtonX(&self->panel, PHONE_CLOCK_CANCEL_BUTTON);
        default:
            return data_ov135_0229d51c[self->cursor];
    }
}
CLEAN_AS(func_ov135_0229c7a8, PhoneClock_CursorX)

/* func_ov135_0229c7fc: the cursor sprite put at the cursor, with a button's animation (at a
 * button while no field is edited) or a field's, and shown. */
void PhoneClock_ShowCursorAtCursor(PhoneClock *self)
{
    int x = PhoneClock_CursorX(self);
    int y = PhoneClock_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_EDITING) == 0 && clock_at_button(self)) {
        Glider_SetAnim(&self->cursor_sprite, PHONE_CLOCK_ANIM_BUTTON);
    } else {
        Glider_SetAnim(&self->cursor_sprite, PHONE_CLOCK_ANIM_FIELD);
    }
    PhoneClock_ShowCursorSprite(self);
}
CLEAN_AS(func_ov135_0229c7fc, PhoneClock_ShowCursorAtCursor)

/* func_ov135_0229c858: on to the field opened, by touch or by the keys as the player last used. */
void PhoneClock_ResumeEditing(PhoneClock *self)
{
    if (StateFlags_IsClear2()) {
        PhoneClock_ResumeEditingByTouch(self);
    } else {
        PhoneClock_ResumeEditingByKeys(self);
    }
}
CLEAN_AS(func_ov135_0229c858, PhoneClock_ResumeEditing)

/* func_ov135_0229c878: the field edited by the keys: overlay 134's object handed back its own
 * func_ov134_022999ac value (func_ov134_02299980), the field flagged as edited, the cursor
 * sprite shown at its cursor and the key repeat reset (sub state 7). */
void PhoneClock_ResumeEditingByKeys(PhoneClock *self)
{
    int value = func_ov134_022999ac(self->editor);
    func_ov134_02299980(self->editor, value);
    PhoneClock_SetFlags(self, PHONE_CLOCK_FLAG_EDITING);
    PhoneClock_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(clock_scene(self));
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_EDIT);
}
CLEAN_AS(func_ov135_0229c878, PhoneClock_ResumeEditingByKeys)

/* func_ov135_0229c8b4: the field edited by touch: the cursor sprite hidden (sub state 3). */
void PhoneClock_ResumeEditingByTouch(PhoneClock *self)
{
    PhoneClock_HideCursorSprite(self);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_EDIT);
}
CLEAN_AS(func_ov135_0229c8b4, PhoneClock_ResumeEditingByTouch)

/* func_ov135_0229c8cc: the field's editing given up: the cursor sprite hidden, no field edited,
 * overlay 134's object told (func_ov134_0229a398, which plays sound 0x2a) and its closing
 * waited for (sub state 15). */
void PhoneClock_CancelField(PhoneClock *self)
{
    PhoneClock_HideCursorSprite(self);
    PhoneClock_ClearFlags(self, PHONE_CLOCK_FLAG_EDITING);
    func_ov134_0229a398(self->editor);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_FIELD_CLOSE);
}
CLEAN_AS(func_ov135_0229c8cc, PhoneClock_CancelField)

/* func_ov135_0229c8f8: the field's editing confirmed: the same, by func_ov134_0229a3e4 (which
 * plays sound 0x29 and keeps the value). */
void PhoneClock_ConfirmField(PhoneClock *self)
{
    PhoneClock_HideCursorSprite(self);
    PhoneClock_ClearFlags(self, PHONE_CLOCK_FLAG_EDITING);
    func_ov134_0229a3e4(self->editor);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_FIELD_CLOSE);
}
CLEAN_AS(func_ov135_0229c8f8, PhoneClock_ConfirmField)

/* func_ov135_0229c924: field `field` opened: the cursor sprite hidden, overlay 134's object
 * told (func_ov134_0229a5c8), its opening waited for (sub state 14), state flag 0x40 set. */
void PhoneClock_OpenField(PhoneClock *self, int field)
{
    PhoneClock_HideCursorSprite(self);
    func_ov134_0229a5c8(self->editor, field);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_FIELD_OPEN);
    StateFlags_Set40();
}
CLEAN_AS(func_ov135_0229c924, PhoneClock_OpenField)

/* func_ov135_0229c954: the clock left as it was: the panel's button 7 selected, the wipe out
 * next (state 2) once its press is over (sub state 13), main told nothing was set
 * (GroupParams_SetC4C(0)). */
void PhoneClock_Cancel(PhoneClock *self)
{
    ButtonPanel_Select(&self->panel, PHONE_CLOCK_CANCEL_BUTTON);
    MenuScene_SetState(clock_scene(self), PHONE_CLOCK_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_PANEL_PRESSED);
    GroupParams_SetC4C(0);
}
CLEAN_AS(func_ov135_0229c954, PhoneClock_Cancel)

/* func_ov135_0229c97c: the clock set: the panel's button 6 selected, the wipe out next (state 2)
 * once its press is over (sub state 13), main told it was set (GroupParams_SetC4C(1)). The date
 * and time edited (func_ov134_0229bbdc fills them) are kept in data_021cfc98, state flag 8 or
 * 0x20 set as func_ov134_0229bbbc says, and the town's offset from the RTC (data_021f3b74, in
 * the state block) made that date and time's: its minutes and seconds from the RTC's now, each
 * computed from its own copy (MI_CpuCopy8). Then the game's clock read again (Clock_Init). */
void PhoneClock_SetClock(PhoneClock *self)
{
    ButtonPanel_Select(&self->panel, PHONE_CLOCK_SET_BUTTON);
    MenuScene_SetState(clock_scene(self), PHONE_CLOCK_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_PANEL_PRESSED);
    GroupParams_SetC4C(1);

    DateTime when = {0};
    func_ov134_0229bbdc((int) (uintptr_t) self->editor, (int) (uintptr_t) &when);
    Global021cfc98_CopyIn(&when);
    if (func_ov134_0229bbbc((char *) self->editor)) {
        StateFlags_Set8();
    } else {
        StateFlags_Set20();
    }
    DateTime for_minutes;
    MI_CpuCopy8(&when, &for_minutes, sizeof(DateTime));
    int minutes = ClockOffset_MinutesTo(&data_021f3b74, &for_minutes);
    DateTime for_seconds;
    MI_CpuCopy8(&when, &for_seconds, sizeof(DateTime));
    int seconds = ClockOffset_SecondsTo(&data_021f3b74, &for_seconds);
    data_021f3b74.minutes = minutes;
    data_021f3b74.seconds = (s16) seconds;
    Clock_Init();
}
CLEAN_AS(func_ov135_0229c97c, PhoneClock_SetClock)

/* func_ov135_0229ca1c: back to the fields, by touch or by the keys as the player last used. */
void PhoneClock_Resume(PhoneClock *self)
{
    if (StateFlags_IsClear2()) {
        PhoneClock_ResumeByTouch(self);
    } else {
        PhoneClock_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov135_0229ca1c, PhoneClock_Resume)

/* func_ov135_0229ca3c: back to the fields by the keys: the cursor sprite shown at the cursor,
 * the key repeat reset (sub state 6). */
void PhoneClock_ResumeByKeys(PhoneClock *self)
{
    PhoneClock_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(clock_scene(self));
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_BROWSE);
}
CLEAN_AS(func_ov135_0229ca3c, PhoneClock_ResumeByKeys)

/* func_ov135_0229ca58: back to the fields by touch: the cursor sprite hidden (sub state 0). */
void PhoneClock_ResumeByTouch(PhoneClock *self)
{
    PhoneClock_HideCursorSprite(self);
    MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_BROWSE);
}
CLEAN_AS(func_ov135_0229ca58, PhoneClock_ResumeByTouch)

/* func_ov135_0229ca70 (sub state 15): once overlay 134's object has closed the field
 * (func_ov134_0229a24c), the cursor at the field it answers (func_ov134_0229a8a0; its 6, no
 * field, puts it at the set button) and back to the fields. */
void PhoneClock_WaitFieldClosed(PhoneClock *self)
{
    if (func_ov134_0229a24c(self->editor) == 0) {
        return;
    }
    u8 field = func_ov134_0229a8a0(self->editor);
    if (field == PHONE_CLOCK_NO_FIELD) {
        self->cursor = PHONE_CLOCK_SET;
    } else {
        self->cursor = field;
    }
    PhoneClock_Resume(self);
}
CLEAN_AS(func_ov135_0229ca70, PhoneClock_WaitFieldClosed)

/* func_ov135_0229caac (sub state 14): once overlay 134's object has opened the field
 * (func_ov134_0229a4e4), on to editing it. */
void PhoneClock_WaitFieldOpen(PhoneClock *self)
{
    if (func_ov134_0229a4e4(self->editor)) {
        PhoneClock_ResumeEditing(self);
    }
}
CLEAN_AS(func_ov135_0229caac, PhoneClock_WaitFieldOpen)

/* func_ov135_0229cacc (sub state 13): while the panel's selected button is pressed, the cursor
 * sprite (when it shows) follows the press; once it is over, the sprite hidden and the states
 * run again (phase 1), for the wipe out. */
void PhoneClock_FollowPanelPress(PhoneClock *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        PhoneClock_HideCursorSprite(self);
        MenuScene_SetPhase(clock_scene(self), 1);
        return;
    }
    if (CellLayerSprite_AnimNumber(clock_sprite_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}
CLEAN_AS(func_ov135_0229cacc, PhoneClock_FollowPanelPress)

/* func_ov135_0229cb30 (sub state 12): once the cursor sprite's animation is over, the sprite
 * shown again and the sub state kept run from the next frame. */
void PhoneClock_ShowSpriteWhenDone(PhoneClock *self)
{
    if (CellLayerSprite_IsDone(clock_sprite_cells(self)) != 0) {
        PhoneClock_ShowCursorSprite(self);
        MenuScene_SetSubState(clock_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov135_0229cb30, PhoneClock_ShowSpriteWhenDone)

/* func_ov135_0229cb54 (sub state 11): once the cursor sprite's press is over: while a field is
 * edited, A held is followed (sub state 8) when func_ov134_02299b70 says so, else the field is
 * confirmed when func_ov134_022997b0 says so, else the sprite shows its third animation and
 * the editing goes on (sub state 7). With no field edited, the place at the cursor is picked:
 * the set button, the cancel button or a field. */
void PhoneClock_PickWhenPressed(PhoneClock *self)
{
    if (CellLayerSprite_IsDone(clock_sprite_cells(self)) == 0) {
        return;
    }
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_EDITING)) {
        if (func_ov134_02299b70(self->editor)) {
            MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_HOLD_A);
        } else if (func_ov134_022997b0(self->editor)) {
            PhoneClock_ConfirmField(self);
        } else {
            MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_EDIT);
            PhoneClock_ShowSpriteThird(self);
        }
        return;
    }
    u8 place = self->cursor;
    if (place == PHONE_CLOCK_SET) {
        PhoneClock_SetClock(self);
    } else if (place == PHONE_CLOCK_CANCEL) {
        PhoneClock_Cancel(self);
    } else {
        PhoneClock_OpenField(self, place);
    }
}
CLEAN_AS(func_ov135_0229cb54, PhoneClock_PickWhenPressed)

/* func_ov135_0229cbd8 (sub state 10): once the cursor sprite stops, the sub state kept is run
 * again, this frame. */
void PhoneClock_WaitCursorSprite(PhoneClock *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(clock_scene(self), self->return_sub_state);
        PhoneClock_RunSubState(self);
    }
}
CLEAN_AS(func_ov135_0229cbd8, PhoneClock_WaitCursorSprite)

/* func_ov135_0229cc00 (sub state 9): when overlay 134's object is done (func_ov134_02299a60), the
 * sprite shows its third animation and the editing goes on (sub state 7); either way the cursor
 * sprite put at the field's cursor. */
void PhoneClock_WaitEditor(PhoneClock *self)
{
    if (func_ov134_02299a60(self->editor) != 0) {
        MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_EDIT);
        PhoneClock_ShowSpriteThird(self);
    }
    int x = PhoneClock_CursorX(self);
    int y = PhoneClock_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
}
CLEAN_AS(func_ov135_0229cc00, PhoneClock_WaitEditor)

/* func_ov135_0229cc48 (sub state 8): while A is held, overlay 134's object stepped
 * (func_ov134_02299a90) and the cursor sprite put at its cursor; once let go, the object told
 * (func_ov134_02299a84) and waited for (sub state 9). */
void PhoneClock_HoldButtonA(PhoneClock *self)
{
    if ((data_021fbe40.held & PHONE_CLOCK_PAD_A) != 0) {
        func_ov134_02299a90(self->editor);
        int x = PhoneClock_CursorX(self);
        int y = PhoneClock_CursorY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    } else {
        func_ov134_02299a84(self->editor);
        MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_EDIT_WAIT);
    }
}
CLEAN_AS(func_ov135_0229cc48, PhoneClock_HoldButtonA)

/* func_ov135_0229cca0 (sub state 7): the field edited by the keys. A touch goes on by touch.
 * Else overlay 134's object takes the repeated keys (func_ov134_022997dc) and answers: 0, no
 * move (then A presses the cursor sprite and B gives the editing up); 3, the sprite put at its
 * cursor at once; 2, a quick glide there; any other, a glide there. */
void PhoneClock_EditByKeys(PhoneClock *self)
{
    if (MenuScene_TakeTouch(clock_scene(self)) != 0) {
        PhoneClock_ResumeEditingByTouch(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(clock_scene(self));
    switch (func_ov134_022997dc(self->editor, (void *) (uintptr_t) keys)) {
        case 0: {
            u16 pressed = data_021fbe40.pressed;
            if ((pressed & PHONE_CLOCK_PAD_A) != 0) {
                PhoneClock_PressCursorSprite(self);
            } else if ((pressed & PHONE_CLOCK_PAD_B) != 0) {
                PhoneClock_CancelField(self);
            }
            break;
        }
        case 3: {
            int x = PhoneClock_CursorX(self);
            int y = PhoneClock_CursorY(self);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
            break;
        }
        case 2:
            PhoneClock_SetFlags(self, PHONE_CLOCK_FLAG_QUICK);
            PhoneClock_GlideToCursor(self);
            break;
        default:
            PhoneClock_GlideToCursor(self);
            break;
    }
}
CLEAN_AS(func_ov135_0229cca0, PhoneClock_EditByKeys)

/* func_ov135_0229cd38 (sub state 6): the fields by the keys. A touch goes on by touch. A move of
 * the cursor glides the sprite there. Else A presses the sprite on its place, START sets the
 * clock and B leaves it as it was (the sprite hidden for both). */
void PhoneClock_BrowseByKeys(PhoneClock *self)
{
    if (MenuScene_TakeTouch(clock_scene(self)) != 0) {
        PhoneClock_ResumeByTouch(self);
        return;
    }
    if (PhoneClock_MoveCursor(self, MenuScene_LatchRepeatedKeys(clock_scene(self))) != 0) {
        PhoneClock_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & PHONE_CLOCK_PAD_A) != 0) {
        PhoneClock_PressCursorSprite(self);
    } else if ((pressed & PHONE_CLOCK_PAD_START) != 0) {
        PhoneClock_HideCursorSprite(self);
        PhoneClock_SetClock(self);
    } else if ((pressed & PHONE_CLOCK_PAD_B) != 0) {
        PhoneClock_HideCursorSprite(self);
        PhoneClock_Cancel(self);
    }
}
CLEAN_AS(func_ov135_0229cd38, PhoneClock_BrowseByKeys)

/* func_ov135_0229cdb4 (sub state 5): while the pen is down, overlay 134's object follows its y
 * (func_ov134_02299af0); once it is up, the object told (func_ov134_02299a84) and the editing by
 * touch goes on (sub state 3). */
void PhoneClock_HoldTouchA(PhoneClock *self)
{
    if (data_021fbdd8 != 0) {
        func_ov134_02299af0(self->editor, data_021f6c54);
    } else {
        func_ov134_02299a84(self->editor);
        MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_EDIT);
    }
}
CLEAN_AS(func_ov135_0229cdb4, PhoneClock_HoldTouchA)

/* func_ov135_0229cdf0 (sub state 4): the same with func_ov134_02299b18. */
void PhoneClock_HoldTouchB(PhoneClock *self)
{
    if (data_021fbdd8 != 0) {
        func_ov134_02299b18((int *) (void *) self->editor, data_021f6c54);
    } else {
        func_ov134_02299a84(self->editor);
        MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_EDIT);
    }
}
CLEAN_AS(func_ov135_0229cdf0, PhoneClock_HoldTouchB)

/* func_ov135_0229ce2c (sub state 3): the field edited by touch. A button goes on by the keys. A
 * touch that went down or up this frame is handed to overlay 134's object
 * (func_ov134_0229a1f0), which answers: 0, the field confirmed; 1, its editing given up; 3, a
 * hold (sub state 4); 2, the other hold (sub state 5); anything else, nothing. */
void PhoneClock_EditByTouch(PhoneClock *self)
{
    if (MenuScene_TakeButtons(clock_scene(self), 1) != 0) {
        PhoneClock_ResumeEditingByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    switch (func_ov134_0229a1f0(self->editor, data_021f6c58, data_021f6c54)) {
        case 0:
            PhoneClock_ConfirmField(self);
            break;
        case 1:
            PhoneClock_CancelField(self);
            break;
        case 3:
            MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_HOLD_B);
            break;
        case 2:
            MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_HOLD_A);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov135_0229ce2c, PhoneClock_EditByTouch)

/* func_ov135_0229cec4 (sub state 2): once overlay 134's object has settled (func_ov134_0229b014),
 * back to the fields by touch (sub state 0). */
void PhoneClock_WaitDragSettled(PhoneClock *self)
{
    if (func_ov134_0229b014((int) (uintptr_t) self->editor)) {
        MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_BROWSE);
    }
}
CLEAN_AS(func_ov135_0229cec4, PhoneClock_WaitDragSettled)

/* func_ov135_0229cee8 (sub state 1): while the pen is down, overlay 134's object follows it
 * (func_ov134_0229b108); once it is up, the object's func_ov134_0229b034 says whether to wait for
 * it to settle (sub state 2) or to go back to the fields by touch (sub state 0). */
void PhoneClock_DragByTouch(PhoneClock *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov134_0229b034(self->editor) != 0) {
            MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_SETTLE);
        } else {
            MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_BROWSE);
        }
    } else {
        func_ov134_0229b108(self->editor, data_021f6c58, data_021f6c54);
    }
}
CLEAN_AS(func_ov135_0229cee8, PhoneClock_DragByTouch)

/* func_ov135_0229cf3c (sub state 0): the fields by touch. A button goes on by the keys. A touch
 * that went down or up this frame on the panel's button 6 sets the clock, on its button 7
 * leaves it as it was. Else, when overlay 134's object takes the touch as a drag
 * (func_ov134_0229b168), state flag 0x40 is set and the drag followed (sub state 1); and a field
 * the touch is on (func_ov134_0229abd4) is opened.
 * QUIRK: the field test runs after a drag was taken too. */
void PhoneClock_BrowseByTouch(PhoneClock *self)
{
    if (MenuScene_TakeButtons(clock_scene(self), 1) != 0) {
        PhoneClock_ResumeByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, PHONE_CLOCK_SET_BUTTON) != 0) {
        PhoneClock_SetClock(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, PHONE_CLOCK_CANCEL_BUTTON) != 0) {
        PhoneClock_Cancel(self);
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (func_ov134_0229b168(self->editor, x, y) != 0) {
        StateFlags_Set40();
        MenuScene_SetSubState(clock_scene(self), PHONE_CLOCK_SUB_TOUCH_DRAG);
    }
    int field = func_ov134_0229abd4(self->editor, x, y);
    if (field != PHONE_CLOCK_NO_FIELD) {
        PhoneClock_OpenField(self, field);
    }
}
CLEAN_AS(func_ov135_0229cf3c, PhoneClock_BrowseByTouch)

/* func_ov135_0229cff0: the scene's graphics: overlay 134's object's (func_ov134_0229b954) and the
 * panel's text colours. */
void PhoneClock_LoadGraphics(PhoneClock *self)
{
    func_ov134_0229b954(self->editor);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov135_0229cff0, PhoneClock_LoadGraphics)

/* func_ov135_0229d010: overlay 134's object opened (func_ov134_0229baec, then
 * func_ov134_0229ba10 with message 0x6b). */
void PhoneClock_OpenEditor(PhoneClock *self)
{
    func_ov134_0229baec(self->editor);
    func_ov134_0229ba10(self->editor, 0x6b);
}
CLEAN_AS(func_ov135_0229d010, PhoneClock_OpenEditor)

/* func_ov135_0229d030: the sub screen's background mode 0; layer 6 at priority 2, layers 4 and 3
 * at priority 1, each with its control reset. */
void PhoneClock_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 1);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 1);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov135_0229d030, PhoneClock_SetUpLayers)

/* func_ov135_0229d07c: the frame's end: overlay 134's object's (func_ov134_0229bbe8). */
void PhoneClock_EndFrame(PhoneClock *self)
{
    func_ov134_0229bbe8(self->editor);
}
CLEAN_AS(func_ov135_0229d07c, PhoneClock_EndFrame)

/* func_ov135_0229d08c: the frame's start: the panel's texts closed, then overlay 134's object's
 * (func_ov134_0229bcac). */
void PhoneClock_BeginFrame(PhoneClock *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    func_ov134_0229bcac(self->editor);
}
CLEAN_AS(func_ov135_0229d08c, PhoneClock_BeginFrame)

/* func_ov135_0229d0a8 */
void PhoneClock_EndInteractiveFrame(PhoneClock *self)
{
    PhoneClock_EndFrame(self);
}
CLEAN_AS(func_ov135_0229d0a8, PhoneClock_EndInteractiveFrame)

/* func_ov135_0229d0b0: the frame's start, then the cursor sprite updated. */
void PhoneClock_BeginInteractiveFrame(PhoneClock *self)
{
    PhoneClock_BeginFrame(self);
    clock_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov135_0229d0b0, PhoneClock_BeginInteractiveFrame)

/* func_ov135_0229d0c8: the members torn down: overlay 134's object (func_ov134_0229bcf0) and the
 * panel's texts closed. */
void PhoneClock_Teardown(PhoneClock *self)
{
    func_ov134_0229bcf0(self->editor);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov135_0229d0c8, PhoneClock_Teardown)

/* func_ov135_0229d0e8: the setup: overlay 134's object set up (func_ov134_0229bd38 with 0, 6, 4
 * and 3; and func_ov134_0229bd2c in GroupParams' mode 0x33), the cursor at the first field, no
 * flags. */
void PhoneClock_Setup(PhoneClock *self)
{
    func_ov134_0229bd38(self->editor, 0, 6, 4, 3);
    if (GroupParams_Mode() == PHONE_CLOCK_MODE_138) {
        func_ov134_0229bd2c((int) (uintptr_t) self->editor);
    }
    self->cursor = 0;
    *clock_flags(self) = 0;
}
CLEAN_AS(func_ov135_0229d0e8, PhoneClock_Setup)

/* func_ov135_0229d128: layers 6 and 4 scrolled with the wipe. */
void PhoneClock_ScrollWithWipe(PhoneClock *self)
{
    MenuScene_ScrollWipe(clock_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(clock_scene(self), 4, 0, 0);
}
CLEAN_AS(func_ov135_0229d128, PhoneClock_ScrollWithWipe)

/* func_ov135_0229d148 (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void PhoneClock_WipeOut(PhoneClock *self)
{
    if (MenuScene_StepWipe(clock_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(clock_scene(self), 5);
    } else {
        PhoneClock_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov135_0229d148, PhoneClock_WipeOut)

/* func_ov135_0229d178 (state 2): the parent told the menu closes (with its sound), the wipe out
 * started on window 2 (layers 2 and 8, margin 0x30), the layers following it; state 3. */
void PhoneClock_StartWipeOut(PhoneClock *self)
{
    MenuDispatch_SetMode(clock_parent(self), PHONE_CLOCK_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(clock_scene(self), 0xa, 0, 0, 0x30);
    PhoneClock_ScrollWithWipe(self);
    MenuScene_SetState(clock_scene(self), PHONE_CLOCK_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov135_0229d178, PhoneClock_StartWipeOut)

/* func_ov135_0229d1b0 (state 1): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the fields. The layers follow the wipe. */
void PhoneClock_WipeIn(PhoneClock *self)
{
    if (MenuScene_StepWipeBack(clock_scene(self), 0)) {
        MenuScene_SetPhase(clock_scene(self), 2);
        PhoneClock_Resume(self);
    }
    PhoneClock_ScrollWithWipe(self);
}
CLEAN_AS(func_ov135_0229d1b0, PhoneClock_WipeIn)

/* func_ov135_0229d1d8 (state 0): the layers set up, overlay 134's object opened and the graphics
 * loaded, the wipe in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x30), layers
 * 6 and 4 shown and following it, the scene drawn, the panel in layout 6 with message 0x65;
 * state 1. */
void PhoneClock_StartWipeIn(PhoneClock *self)
{
    PhoneClock_SetUpLayers();
    PhoneClock_OpenEditor(self);
    PhoneClock_LoadGraphics(self);
    MenuScene_StartWipeCoveredOnWindow2(clock_scene(self), 0xa, 4, 0, 0x30);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    PhoneClock_ScrollWithWipe(self);
    PhoneClock_SetFlags(self, PHONE_CLOCK_FLAG_DRAWN);
    ButtonPanel_SetLayout6(&self->panel, 0x65);
    MenuScene_SetState(clock_scene(self), PHONE_CLOCK_STATE_WIPE_IN);
}
CLEAN_AS(func_ov135_0229d1d8, PhoneClock_StartWipeIn)

/* func_ov135_0229d234 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int PhoneClock_End(PhoneClock *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov135_0229d234, PhoneClock_End)

/* func_ov135_0229d244 (vtable slot 0x58, phase 4): nothing. */
int PhoneClock_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov135_0229d244, PhoneClock_Phase4Idle)

/* func_ov135_0229d248 (vtable slot 0x54, phase 3): nothing. */
int PhoneClock_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov135_0229d248, PhoneClock_Phase3Idle)

/* func_ov135_0229d24c (vtable slot 0x50, phase 2): a frame of the scene in use: its start, its
 * sub state and its end. Answers 1. */
int PhoneClock_RunInteractive(PhoneClock *self)
{
    PhoneClock_BeginInteractiveFrame(self);
    PhoneClock_RunSubState(self);
    PhoneClock_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov135_0229d24c, PhoneClock_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov135_0229d680; /* the states' guard */
extern u32 data_ov135_0229d684; /* the sub states' guard */
extern MemberPointer data_ov135_0229d688[PHONE_CLOCK_STATES];
extern MemberPointer data_ov135_0229d6a8[PHONE_CLOCK_SUB_STATES];
extern const MemberPointer data_ov135_0229d560, data_ov135_0229d568, data_ov135_0229d570, data_ov135_0229d578,
    data_ov135_0229d580, data_ov135_0229d588, data_ov135_0229d590, data_ov135_0229d598, data_ov135_0229d5a0,
    data_ov135_0229d5a8, data_ov135_0229d5b0, data_ov135_0229d5b8, data_ov135_0229d5c0, data_ov135_0229d5c8,
    data_ov135_0229d5d0, data_ov135_0229d5d8, data_ov135_0229d5e0, data_ov135_0229d5e8, data_ov135_0229d5f8,
    data_ov135_0229d600;

/* func_ov135_0229d268: the sub state's function (PhoneClockSubState) through the table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 16; the game reads past the table for others. */
void PhoneClock_RunSubState(PhoneClock *self)
{
    static const MemberPointer *const sub_states[PHONE_CLOCK_SUB_STATES] = {
        &data_ov135_0229d5e8, &data_ov135_0229d5e0, &data_ov135_0229d5d8, &data_ov135_0229d5d0,
        &data_ov135_0229d5c8, &data_ov135_0229d5a0, &data_ov135_0229d5b0, &data_ov135_0229d5b8,
        &data_ov135_0229d5c0, &data_ov135_0229d5f8, &data_ov135_0229d598, &data_ov135_0229d590,
        &data_ov135_0229d588, &data_ov135_0229d580, &data_ov135_0229d578, &data_ov135_0229d5a8,
    };
    MemberTable_InitOnce(&data_ov135_0229d684, data_ov135_0229d6a8, sub_states, PHONE_CLOCK_SUB_STATES);
    MemberPointer_CallVoid(&data_ov135_0229d6a8[self->base.sub_state], self);
}
CLEAN_AS(func_ov135_0229d268, PhoneClock_RunSubState)

/* Obj_ov135_0229d610::func_ov135_0229d394 (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (PhoneClockState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int PhoneClock_RunState(PhoneClock *self)
{
    static const MemberPointer *const states[PHONE_CLOCK_STATES] = {
        &data_ov135_0229d568,
        &data_ov135_0229d560,
        &data_ov135_0229d570,
        &data_ov135_0229d600,
    };
    MemberTable_InitOnce(&data_ov135_0229d680, data_ov135_0229d688, states, PHONE_CLOCK_STATES);
    PhoneClock_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov135_0229d688[self->base.state], self);
    PhoneClock_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov135_0229d61019func_ov135_0229d394Ev, PhoneClock_RunState)

/* func_ov135_0229d428 (vtable slot 0x24): the scene's draw: the cursor sprite (with the keys in
 * use, even before the scene is drawn), then while the scene is drawn (else answers 0) overlay
 * 134's object (func_ov134_0229b220) and the panel, each with the wipe's y read for it. Answers
 * 1. */
int PhoneClock_Draw(PhoneClock *self)
{
    if (StateFlags_Test2() != 0) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (PhoneClock_TestFlags(self, PHONE_CLOCK_FLAG_DRAWN) == 0) {
        return 0;
    }
    int wipe_y = MenuScene_WipeOffsetY(clock_scene(self));
    func_ov134_0229b220((char *) self->editor, NULL, (char *) (uintptr_t) (u32) wipe_y);
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(clock_scene(self)));
    return 1;
}
CLEAN_AS(func_ov135_0229d428, PhoneClock_Draw)

/* func_ov135_0229d47c (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int PhoneClock_Close(PhoneClock *self)
{
    MenuDispatch_ChildClosed(clock_parent(self));
    PhoneClock_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov135_0229d47c, PhoneClock_Close)

/* func_ov135_0229d498 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int PhoneClock_Start(PhoneClock *self)
{
    PhoneClock_Setup(self);
    self->base.state = PHONE_CLOCK_STATE_START_WIPE_IN;
    MenuScene_SetPhase(clock_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov135_0229d498, PhoneClock_Start)

/* func_ov135_0229d4b8: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order. */
PhoneClock *PhoneClock_New(void)
{
    PhoneClock *self = MenuScene_Alloc(sizeof(PhoneClock));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov135_0229d610;
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    func_ov134_0229bed4(self->editor);
    return self;
}
CLEAN_AS(func_ov135_0229d4b8, PhoneClock_New)
