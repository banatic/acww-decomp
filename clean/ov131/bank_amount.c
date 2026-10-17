/* The bank's amount entry of overlay 131 (bank_amount.h): the destructors, the bells moved, the
 * cursor, the sub states of the input, the frames, the states, the vtable's slots and the
 * constructor. */
#include "bank_amount.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/house_record.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/savings.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(BankAmount, cursor) == 0x94, "cursor");
static_assert(offsetof(BankAmount, panel) == 0xf8 && offsetof(BankAmount, pad) == 0x2c4, "panel, pad");
static_assert(offsetof(BankAmount, flags) == 0x1554 && offsetof(BankAmount, return_sub_state) == 0x1556, "flags");
static_assert(sizeof(BankAmount) == 0x1558, "size (func_ov131_0229b820)");

/* The scene's vtable. */
extern const u8 data_ov131_0229b8f0[];

/* The buttons, and the pen: down, down or up since the frame before, and where. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* the touch's x */
extern u8 data_021f6c54; /* and its y */

#define BANK_AMOUNT_PAD_A 0x0001
#define BANK_AMOUNT_PAD_B 0x0002
#define BANK_AMOUNT_PAD_START 0x0008

/* The record of the player's house (main/house_record.h). */
extern u8 data_021ebcd4[];

/* The sound of a cancel (SoundSys_PlaySe). */
#define BANK_AMOUNT_SE_CANCEL 0x2a

/* What overlay 92's dispatcher is told when the scene ends (MENU_DISPATCH_MODE_CLOSE). */
#define BANK_AMOUNT_DISPATCH_CLOSE 0x44

#define BANK_AMOUNT_WIPE_MARGIN 0x30

/* What main is told of the entry (GroupParams_SetC4C). */
#define BANK_AMOUNT_OUTCOME_CANCELLED 0
#define BANK_AMOUNT_OUTCOME_DONE 1

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov131_0229b960; /* the sub states' guard */
extern u32 data_ov131_0229b964; /* the states' guard */
extern MemberPointer data_ov131_0229b968[BANK_AMOUNT_STATES];
extern MemberPointer data_ov131_0229b988[BANK_AMOUNT_SUB_STATES];
extern const MemberPointer data_ov131_0229b880, data_ov131_0229b888, data_ov131_0229b898, data_ov131_0229b8a0,
    data_ov131_0229b8a8, data_ov131_0229b8b0, data_ov131_0229b8b8, data_ov131_0229b8c0, data_ov131_0229b8c8,
    data_ov131_0229b8d0, data_ov131_0229b8d8, data_ov131_0229b8e0;

static MenuScene *scene_of(BankAmount *self)
{
    return &self->base;
}

static MenuDispatch *dispatch_of(BankAmount *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void update_cursor(BankAmount *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->cursor.vtable;
    vtable[3](&self->cursor);
}

static CellLayerSprite *cursor_cells(BankAmount *self)
{
    return (CellLayerSprite *) (void *) &self->cursor;
}

/* --- The destructors and the flags --- */

/* func_ov131_0229acc0 (vtable slot 0x40): the members' destructors, last first, then the
 * base's. */
BankAmount *BankAmount_Destroy(BankAmount *self)
{
    self->base.vtable = data_ov131_0229b8f0;
    BankPad_Destroy(&self->pad);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor);
    MenuScene_DestroyBase(scene_of(self));
    return self;
}
CLEAN_AS(func_ov131_0229acc0, BankAmount_Destroy)

/* func_ov131_0229acf8 (vtable slot 0x44): as BankAmount_Destroy, then the scene freed. */
BankAmount *BankAmount_Delete(BankAmount *self)
{
    self->base.vtable = data_ov131_0229b8f0;
    BankPad_Destroy(&self->pad);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor);
    MenuScene_DestroyBase(scene_of(self));
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov131_0229acf8, BankAmount_Delete)

/* func_ov131_0229ad34 */
void BankAmount_SetFlags(BankAmount *self, int flags)
{
    self->flags |= (u16) flags;
}
CLEAN_AS(func_ov131_0229ad34, BankAmount_SetFlags)

/* func_ov131_0229ad44 */
int BankAmount_TestFlags(BankAmount *self, u16 mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov131_0229ad44, BankAmount_TestFlags)

/* --- The bells --- */

/* func_ov131_0229ad5c: the amount entered moved as the mode says. The bells are first taken
 * from the pockets (the withdrawal takes them from the savings instead, which hold the limit;
 * the modes that only ask a number move nothing), then given: to the loan (lowered from its
 * current value), to the savings (raised from theirs) or to the pockets. */
void BankAmount_Apply(BankAmount *self)
{
    int amount = BankPad_Amount(&self->pad);
    int limit = BankPad_Limit(&self->pad);
    int current = BankPad_Current(&self->pad);
    u8 *record = PlayerRecords_Current();
    SavingsAccount *savings = PlayerRecord_Savings(record);
    int mode = GroupParams_Mode();
    switch (mode) {
        case BANK_AMOUNT_MODE_WITHDRAW:
            Savings_SetBalance(savings, limit - amount);
            break;
        case BANK_AMOUNT_MODE_NUMBER:
        case BANK_AMOUNT_MODE_POCKET_BELLS:
        case BANK_AMOUNT_MODE_SMALL_NUMBER:
            break;
        default:
            PlayerPockets_AddBells(PlayerRecord_Pockets(record), -amount, 1);
            break;
    }
    switch (mode) {
        case BANK_AMOUNT_MODE_PAY_LOAN:
            HouseRecord_SetLoan((HouseRecord *) (void *) data_021ebcd4, current - amount);
            break;
        case BANK_AMOUNT_MODE_DEPOSIT:
            Savings_SetBalance(savings, current + amount);
            break;
        case BANK_AMOUNT_MODE_WITHDRAW:
            PlayerPockets_AddBells(PlayerRecord_Pockets(record), amount, 1);
            break;
    }
}
CLEAN_AS(func_ov131_0229ad5c, BankAmount_Apply)

/* func_ov131_0229ae0c: the pad's range by the mode: the limit (9,999,999 or 99 for the numbers,
 * the savings for a withdrawal, else the pockets' bells), the current value (the loan, the
 * savings, the pockets' bells for a withdrawal, else 0) and the most that can be entered: the
 * limit, or less when the loan is smaller, the savings have less room or the pockets less
 * room. */
void BankAmount_SetUpRange(BankAmount *self)
{
    int mode = GroupParams_Mode();
    u8 *record = PlayerRecords_Current();
    SavingsAccount *savings = PlayerRecord_Savings(record);
    int limit;
    switch (mode) {
        case BANK_AMOUNT_MODE_NUMBER:
            limit = 9999999;
            break;
        case BANK_AMOUNT_MODE_SMALL_NUMBER:
            limit = 99;
            break;
        case BANK_AMOUNT_MODE_WITHDRAW:
            limit = Savings_Balance(savings);
            break;
        default:
            limit = PlayerPockets_Bells(PlayerRecord_Pockets(record), 1);
            break;
    }
    int current = 0;
    switch (mode) {
        case BANK_AMOUNT_MODE_PAY_LOAN:
            current = HouseRecord_Loan((const HouseRecord *) (const void *) data_021ebcd4);
            break;
        case BANK_AMOUNT_MODE_DEPOSIT:
            current = Savings_Balance(savings);
            break;
        case BANK_AMOUNT_MODE_WITHDRAW:
            current = PlayerPockets_Bells(PlayerRecord_Pockets(record), 1);
            break;
    }
    int most = limit;
    switch (mode) {
        case BANK_AMOUNT_MODE_PAY_LOAN:
            if (current < limit) {
                most = current;
            }
            break;
        case BANK_AMOUNT_MODE_DEPOSIT: {
            int room = BANK_AMOUNT_SAVINGS_MAX - current;
            if (room < limit) {
                most = room;
            }
            break;
        }
        case BANK_AMOUNT_MODE_WITHDRAW: {
            int room = PlayerPockets_BellsRoom(PlayerRecord_Pockets(record), 1, 0);
            if (room < limit) {
                most = room;
            }
            break;
        }
    }
    BankPad_SetRange(&self->pad, most, limit, current);
}
CLEAN_AS(func_ov131_0229ae0c, BankAmount_SetUpRange)

/* --- The cursor --- */

/* func_ov131_0229aee4: the cursor's third animation of its set, waited for (sub state 5) before
 * going back to the sub state it was in. */
void BankAmount_ShowCursorThird(BankAmount *self)
{
    Glider_ShowThirdOfSet(&self->cursor);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_CURSOR_ANIM);
}
CLEAN_AS(func_ov131_0229aee4, BankAmount_ShowCursorThird)

/* func_ov131_0229af0c: the cursor's second animation of its set, then the key under it pressed
 * (sub state 4). */
void BankAmount_ShowCursorSecond(BankAmount *self)
{
    Glider_ShowSecondOfSet(&self->cursor);
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_KEY_PRESS);
}
CLEAN_AS(func_ov131_0229af0c, BankAmount_ShowCursorSecond)

/* func_ov131_0229af24: the cursor's first animation of its set, and its update. */
void BankAmount_ShowCursorFirst(BankAmount *self)
{
    Glider_ShowFirstOfSet(&self->cursor);
    update_cursor(self);
}
CLEAN_AS(func_ov131_0229af24, BankAmount_ShowCursorFirst)

/* func_ov131_0229af40: the cursor eases to (x, y) in 3 steps (sub state 3), then goes back to
 * the sub state it was in. */
void BankAmount_GlideCursorTo(BankAmount *self, int x, int y)
{
    Glider_EaseTo(&self->cursor, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_GLIDE);
}
CLEAN_AS(func_ov131_0229af40, BankAmount_GlideCursorTo)

/* func_ov131_0229af74: the cursor turns to its set for a button or a key and glides to the key
 * the pad's cursor is on. */
void BankAmount_MoveCursor(BankAmount *self)
{
    if (BankPad_CursorOnButton(&self->pad) != 0) {
        Glider_TurnToSetB(&self->cursor);
    } else {
        Glider_TurnToSetA(&self->cursor);
    }
    int x = (int) BankAmount_CursorX(self);
    int y = BankAmount_CursorY(self);
    BankAmount_GlideCursorTo(self, x, y);
}
CLEAN_AS(func_ov131_0229af74, BankAmount_MoveCursor)

/* func_ov131_0229afbc: the cursor without an animation (not shown), and its update. */
void BankAmount_HideCursor(BankAmount *self)
{
    Glider_SetAnim(&self->cursor, GLIDER_ANIM_NONE);
    update_cursor(self);
}
CLEAN_AS(func_ov131_0229afbc, BankAmount_HideCursor)

/* func_ov131_0229afd8 */
int BankAmount_CursorY(BankAmount *self)
{
    return (int) BankPad_CursorY(&self->pad);
}
CLEAN_AS(func_ov131_0229afd8, BankAmount_CursorY)

/* func_ov131_0229afe8 */
unsigned int BankAmount_CursorX(BankAmount *self)
{
    return BankPad_CursorX(&self->pad);
}
CLEAN_AS(func_ov131_0229afe8, BankAmount_CursorX)

/* func_ov131_0229aff8: the cursor put at the pad's cursor key, in its set for a button or a
 * key, shown. */
void BankAmount_PlaceCursor(BankAmount *self)
{
    int x = (int) BankAmount_CursorX(self);
    int y = BankAmount_CursorY(self);
    Glider_PlaceAt(&self->cursor, x, y);
    if (BankPad_CursorOnButton(&self->pad) != 0) {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor, GLIDER_ANIM_SET_A);
    }
    BankAmount_ShowCursorFirst(self);
}
CLEAN_AS(func_ov131_0229aff8, BankAmount_PlaceCursor)

/* --- The panel's buttons --- */

/* func_ov131_0229b04c: cancelled: sound 0x2a, main told so, the cancel button's press played
 * (sub state 7) before the scene finishes (state 2). */
void BankAmount_Cancel(BankAmount *self)
{
    SoundSys_PlaySe(BANK_AMOUNT_SE_CANCEL);
    GroupParams_SetC4C(BANK_AMOUNT_OUTCOME_CANCELLED);
    ButtonPanel_Select(&self->panel, BANK_AMOUNT_BUTTON_CANCEL);
    MenuScene_SetState(scene_of(self), BANK_AMOUNT_STATE_FINISH);
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_PANEL_PRESS);
}
CLEAN_AS(func_ov131_0229b04c, BankAmount_Cancel)

/* func_ov131_0229b07c: OK, unless it is greyed (the amount is 0; then 0): its press played (sub
 * state 7) before the scene finishes (state 2), main told it is done and given the amount, and
 * the bells moved. */
int BankAmount_Confirm(BankAmount *self)
{
    if (ButtonPanel_HasSpriteFlag4(&self->panel, BANK_AMOUNT_BUTTON_OK) != 0) {
        return 0;
    }
    ButtonPanel_Select(&self->panel, BANK_AMOUNT_BUTTON_OK);
    MenuScene_SetState(scene_of(self), BANK_AMOUNT_STATE_FINISH);
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_PANEL_PRESS);
    GroupParams_SetC4C(BANK_AMOUNT_OUTCOME_DONE);
    GroupParams_SetC78(BankPad_Amount(&self->pad));
    BankAmount_Apply(self);
    return 1;
}
CLEAN_AS(func_ov131_0229b07c, BankAmount_Confirm)

/* --- The sub states of the input --- */

/* func_ov131_0229b0d0: the input starts by the pen, or by the buttons when main's state flag 2
 * is set. */
void BankAmount_BeginInput(BankAmount *self)
{
    if (StateFlags_IsClear2() != 0) {
        BankAmount_StartTouch(self);
    } else {
        BankAmount_StartKeys(self);
    }
}
CLEAN_AS(func_ov131_0229b0d0, BankAmount_BeginInput)

/* func_ov131_0229b0f0: the input by the buttons: the cursor shown at its key, the d-pad's
 * repeat reset (sub state 2). */
void BankAmount_StartKeys(BankAmount *self)
{
    BankAmount_PlaceCursor(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_KEYS);
}
CLEAN_AS(func_ov131_0229b0f0, BankAmount_StartKeys)

/* func_ov131_0229b10c: the input by the pen: the cursor hidden (sub state 0). */
void BankAmount_StartTouch(BankAmount *self)
{
    BankAmount_HideCursor(self);
    MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_TOUCH);
}
CLEAN_AS(func_ov131_0229b10c, BankAmount_StartTouch)

/* func_ov131_0229b124 (sub state 7): a frame of the selected button's press; the cursor, while
 * it is shown, follows the button as it is pressed. When the press is over the cursor is hidden
 * and the states run (phase 1). */
void BankAmount_PanelPress(BankAmount *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(cursor_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->cursor, frame + x, frame + y);
        }
    } else {
        BankAmount_HideCursor(self);
        MenuScene_SetPhase(scene_of(self), BANK_AMOUNT_PHASE_STATES);
    }
}
CLEAN_AS(func_ov131_0229b124, BankAmount_PanelPress)

/* func_ov131_0229b188 (sub state 6): while A is held the key repeats; when it is let go, back to
 * the buttons (sub state 2) after the cursor's third animation. */
void BankAmount_KeyHeld(BankAmount *self)
{
    if ((data_021fbe40.held & BANK_AMOUNT_PAD_A) == 0) {
        BankPad_StopRepeat(&self->pad);
        MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_KEYS);
        BankAmount_ShowCursorThird(self);
    } else {
        BankPad_StepRepeat(&self->pad);
    }
}
CLEAN_AS(func_ov131_0229b188, BankAmount_KeyHeld)

/* func_ov131_0229b1c8 (sub state 5): when the cursor's animation is over, its first one again
 * and back to `return_sub_state`. */
void BankAmount_WaitCursorAnim(BankAmount *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self))) {
        BankAmount_ShowCursorFirst(self);
        MenuScene_SetSubState(scene_of(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov131_0229b1c8, BankAmount_WaitCursorAnim)

/* func_ov131_0229b1f0 (sub state 4): when the cursor's animation is over, the key under it acts:
 * a key of the keypad is pressed and repeats while A is held (sub state 6); OK confirms (when
 * greyed, back to the buttons, sub state 2, after the cursor's third animation); cancel
 * cancels. */
void BankAmount_KeyPress(BankAmount *self)
{
    if (CellLayerSprite_IsDone(cursor_cells(self)) == 0) {
        return;
    }
    if (BankPad_PressCursorKey(&self->pad) != 0) {
        MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_KEY_HELD);
    } else if (BankPad_CursorOnOk(&self->pad) != 0) {
        if (BankAmount_Confirm(self) != 0) {
            return;
        }
        MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_KEYS);
        BankAmount_ShowCursorThird(self);
    } else {
        BankAmount_Cancel(self);
    }
}
CLEAN_AS(func_ov131_0229b1f0, BankAmount_KeyPress)

/* Obj_ov131_0229b8f0::func_ov131_0229b24c (sub state 3): when the cursor's glide is over, back
 * to `return_sub_state`, whose frame runs at once. */
void BankAmount_Glide(BankAmount *self)
{
    if (Glider_IsMoving(&self->cursor) == 0) {
        MenuScene_SetSubState(scene_of(self), self->return_sub_state);
        BankAmount_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov131_0229b8f019func_ov131_0229b24cEv, BankAmount_Glide)

/* func_ov131_0229b274 (sub state 2): the input by the buttons. The pen takes over the input; a
 * move of the d-pad (with its repeat) moves the cursor; START confirms (and hides the cursor
 * when it did), A presses the key under the cursor, B clears the amount or, when it already is
 * 0, cancels. */
void BankAmount_Keys(BankAmount *self)
{
    if (MenuScene_TakeTouch(scene_of(self)) != 0) {
        BankAmount_StartTouch(self);
        return;
    }
    if (BankPad_MoveCursor(&self->pad, (int) MenuScene_LatchRepeatedKeys(scene_of(self))) != 0) {
        BankAmount_MoveCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & BANK_AMOUNT_PAD_START) {
        if (BankAmount_Confirm(self) != 0) {
            BankAmount_HideCursor(self);
        }
        return;
    }
    if (pressed & BANK_AMOUNT_PAD_A) {
        BankAmount_ShowCursorSecond(self);
        return;
    }
    if (pressed & BANK_AMOUNT_PAD_B) {
        if (BankPad_ClearAmount(&self->pad) == 0) {
            BankAmount_HideCursor(self);
            BankAmount_Cancel(self);
        }
    }
}
CLEAN_AS(func_ov131_0229b274, BankAmount_Keys)

/* func_ov131_0229b304 (sub state 1): while the pen is down the key repeats; when it is lifted,
 * back to the pen's input (sub state 0). */
void BankAmount_TouchHeld(BankAmount *self)
{
    if (data_021fbdd8 == 0) {
        BankPad_StopRepeat(&self->pad);
        MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_TOUCH);
    } else {
        BankPad_StepRepeat(&self->pad);
    }
}
CLEAN_AS(func_ov131_0229b304, BankAmount_TouchHeld)

/* func_ov131_0229b338 (sub state 0): the input by the pen. The buttons (also command 0x3b) take
 * over the input; when the pen goes down it confirms on OK, cancels on cancel, or presses a key
 * of the keypad, which repeats while the pen stays down (sub state 1). */
void BankAmount_Touch(BankAmount *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1) != 0) {
        BankAmount_StartKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, BANK_AMOUNT_BUTTON_OK) != 0) {
        BankAmount_Confirm(self);
    } else if (ButtonPanel_IsTouched(&self->panel, BANK_AMOUNT_BUTTON_CANCEL) != 0) {
        BankAmount_Cancel(self);
    } else if (BankPad_KeyAt(&self->pad, data_021f6c58, data_021f6c54) != BANK_PAD_KEY_NONE) {
        BankPad_StartPress(&self->pad);
        MenuScene_SetSubState(scene_of(self), BANK_AMOUNT_SUB_TOUCH_HELD);
    }
}
CLEAN_AS(func_ov131_0229b338, BankAmount_Touch)

/* --- The screens and the frames --- */

/* func_ov131_0229b3d4: the pad's teller and message, and the panel's text colours. */
void BankAmount_LoadTexts(BankAmount *self)
{
    BankPad_ShowMessage(&self->pad);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov131_0229b3d4, BankAmount_LoadTexts)

/* func_ov131_0229b3f4 */
void BankAmount_LoadPad(BankAmount *self)
{
    BankPad_Load(&self->pad);
}
CLEAN_AS(func_ov131_0229b3f4, BankAmount_LoadPad)

/* func_ov131_0229b404: the sub screen in background mode 0, the pad's two layers at priority 2,
 * both in their first size with 16 colours from characters 0. */
void BankAmount_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(BANK_AMOUNT_DIGITS_LAYER, 2);
    DisplayLayer_SetBgControl(BANK_AMOUNT_DIGITS_LAYER, 0, 0, 0);
    DisplayLayer_SetPriority(BANK_AMOUNT_KEYS_LAYER, 2);
    DisplayLayer_SetBgControl(BANK_AMOUNT_KEYS_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov131_0229b404, BankAmount_SetUpLayers)

/* func_ov131_0229b43c: a frame's end: the pad's changed screens loaded, and OK greyed while the
 * amount is 0. */
void BankAmount_EndFrame(BankAmount *self)
{
    BankPad_LoadScreens(&self->pad);
    if (BankPad_Amount(&self->pad) == 0) {
        ButtonPanel_SetSpriteFlag4(&self->panel, BANK_AMOUNT_BUTTON_OK);
    } else {
        ButtonPanel_ClearSpriteFlag4(&self->panel, BANK_AMOUNT_BUTTON_OK);
    }
}
CLEAN_AS(func_ov131_0229b43c, BankAmount_EndFrame)

/* func_ov131_0229b474: a frame's start: the panel's texts closed and the pad's frame start. */
void BankAmount_BeginFrame(BankAmount *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    BankPad_BeginFrame(&self->pad);
}
CLEAN_AS(func_ov131_0229b474, BankAmount_BeginFrame)

/* func_ov131_0229b490: the input's frame end. */
void BankAmount_EndInputFrame(BankAmount *self)
{
    BankAmount_EndFrame(self);
}
CLEAN_AS(func_ov131_0229b490, BankAmount_EndInputFrame)

/* func_ov131_0229b498: the input's frame start, and the cursor updated (vtable slot 3). */
void BankAmount_BeginInputFrame(BankAmount *self)
{
    BankAmount_BeginFrame(self);
    update_cursor(self);
}
CLEAN_AS(func_ov131_0229b498, BankAmount_BeginInputFrame)

/* func_ov131_0229b4b0: the panel's texts closed and the pad's teardown. */
void BankAmount_Teardown(BankAmount *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    BankPad_Teardown(&self->pad);
}
CLEAN_AS(func_ov131_0229b4b0, BankAmount_Teardown)

/* func_ov131_0229b4cc: the pad set up for GroupParams' mode on the two layers, its range, and no
 * flags. */
void BankAmount_Setup(BankAmount *self)
{
    int mode = GroupParams_Mode();
    BankPad_Setup(&self->pad, (u8) (mode - BANK_AMOUNT_MODE_PAY_LOAN), BANK_AMOUNT_DIGITS_LAYER, BANK_AMOUNT_KEYS_LAYER);
    BankAmount_SetUpRange(self);
    self->flags = 0;
}
CLEAN_AS(func_ov131_0229b4cc, BankAmount_Setup)

/* func_ov131_0229b504: the pad's two layers follow the wipe. */
void BankAmount_ScrollWipe(BankAmount *self)
{
    MenuScene_ScrollWipe(scene_of(self), BANK_AMOUNT_DIGITS_LAYER, 0, 0);
    MenuScene_ScrollWipe(scene_of(self), BANK_AMOUNT_KEYS_LAYER, 0, 0);
}
CLEAN_AS(func_ov131_0229b504, BankAmount_ScrollWipe)

/* --- The states, from the last --- */

/* func_ov131_0229b524 (BANK_AMOUNT_STATE_WIPE_OUT): the scene wipes out, its layers following;
 * when done they are hidden and the scene ends (phase 5). */
void BankAmount_WipeOut(BankAmount *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(BANK_AMOUNT_DIGITS_LAYER);
        DisplayLayer_HideAndResetScroll(BANK_AMOUNT_KEYS_LAYER);
        MenuScene_SetPhase(scene_of(self), BANK_AMOUNT_PHASE_END);
    } else {
        BankAmount_ScrollWipe(self);
    }
}
CLEAN_AS(func_ov131_0229b524, BankAmount_WipeOut)

/* func_ov131_0229b554 (BANK_AMOUNT_STATE_FINISH): overlay 92's dispatcher told the scene
 * closes, and the scene wipes out on window 2 (state 3). */
void BankAmount_Finish(BankAmount *self)
{
    MenuDispatch_SetMode(dispatch_of(self), BANK_AMOUNT_DISPATCH_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(scene_of(self), 10, 0, 0, BANK_AMOUNT_WIPE_MARGIN);
    BankAmount_ScrollWipe(self);
    MenuScene_SetState(scene_of(self), BANK_AMOUNT_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov131_0229b554, BankAmount_Finish)

/* func_ov131_0229b58c (BANK_AMOUNT_STATE_WIPE_IN): the scene wipes in, its layers following;
 * then phase 2 and the input. */
void BankAmount_WipeIn(BankAmount *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0) != 0) {
        MenuScene_SetPhase(scene_of(self), BANK_AMOUNT_PHASE_INPUT);
        BankAmount_BeginInput(self);
    }
    BankAmount_ScrollWipe(self);
}
CLEAN_AS(func_ov131_0229b58c, BankAmount_WipeIn)

/* func_ov131_0229b5b4 (BANK_AMOUNT_STATE_LOAD): the layers set up, the pad's screens and texts
 * loaded; the layers shown and wiping in on window 2 (state 1), the scene drawn, the panel with
 * OK and cancel (layout 6, message 0x65). */
void BankAmount_LoadState(BankAmount *self)
{
    BankAmount_SetUpLayers();
    BankAmount_LoadPad(self);
    BankAmount_LoadTexts(self);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), 10, 4, 0, BANK_AMOUNT_WIPE_MARGIN);
    DisplayLayer_Show(BANK_AMOUNT_DIGITS_LAYER);
    DisplayLayer_Show(BANK_AMOUNT_KEYS_LAYER);
    BankAmount_ScrollWipe(self);
    BankAmount_SetFlags(self, BANK_AMOUNT_FLAG_DRAWN);
    ButtonPanel_SetLayout6(&self->panel, 0x65);
    MenuScene_SetState(scene_of(self), BANK_AMOUNT_STATE_WIPE_IN);
}
CLEAN_AS(func_ov131_0229b5b4, BankAmount_LoadState)

/* --- The vtable's slots --- */

/* func_ov131_0229b610 (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int BankAmount_End(BankAmount *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov131_0229b610, BankAmount_End)

/* func_ov131_0229b620 (vtable slot 0x58): nothing. Answers 1. */
int BankAmount_Slot58(void)
{
    return 1;
}
CLEAN_AS(func_ov131_0229b620, BankAmount_Slot58)

/* func_ov131_0229b624 (vtable slot 0x54): nothing. Answers 1. */
int BankAmount_Slot54(void)
{
    return 1;
}
CLEAN_AS(func_ov131_0229b624, BankAmount_Slot54)

/* Obj_ov131_0229b8f0::func_ov131_0229b628 (vtable slot 0x50, phase 2): a frame of the input:
 * its start, its sub state and its end. Answers 1. */
int BankAmount_RunInput(BankAmount *self)
{
    BankAmount_BeginInputFrame(self);
    BankAmount_RunSubState(self);
    BankAmount_EndInputFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov131_0229b8f019func_ov131_0229b628Ev, BankAmount_RunInput)

/* Obj_ov131_0229b8f0::func_ov131_0229b644: the sub state's function (BankAmountSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 8; the game reads past the table for others. */
void BankAmount_RunSubState(BankAmount *self)
{
    static const MemberPointer *const sub_states[BANK_AMOUNT_SUB_STATES] = {
        &data_ov131_0229b8b8, &data_ov131_0229b8b0, &data_ov131_0229b8a0, &data_ov131_0229b8c0,
        &data_ov131_0229b898, &data_ov131_0229b8c8, &data_ov131_0229b888, &data_ov131_0229b8e0,
    };
    MemberTable_InitOnce(&data_ov131_0229b960, data_ov131_0229b988, sub_states, BANK_AMOUNT_SUB_STATES);
    MemberPointer_CallVoid(&data_ov131_0229b988[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov131_0229b8f019func_ov131_0229b644Ev, BankAmount_RunSubState)

/* func_ov131_0229b700 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (BankAmountState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int BankAmount_RunState(BankAmount *self)
{
    static const MemberPointer *const states[BANK_AMOUNT_STATES] = {
        &data_ov131_0229b880,
        &data_ov131_0229b8a8,
        &data_ov131_0229b8d8,
        &data_ov131_0229b8d0,
    };
    MemberTable_InitOnce(&data_ov131_0229b964, data_ov131_0229b968, states, BANK_AMOUNT_STATES);
    BankAmount_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov131_0229b968[self->base.state], self);
    BankAmount_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov131_0229b700, BankAmount_RunState)

/* func_ov131_0229b794 (vtable slot 0x24): the scene's draw: the cursor (with the buttons in
 * use), then, while the scene is drawn (else 0), the panel and the pad at the wipe's y.
 * Answers 1. */
int BankAmount_Draw(BankAmount *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor);
    }
    if (BankAmount_TestFlags(self, BANK_AMOUNT_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(scene_of(self)));
    BankPad_Draw(&self->pad, MenuScene_WipeOffsetY(scene_of(self)));
    return 1;
}
CLEAN_AS(func_ov131_0229b794, BankAmount_Draw)

/* func_ov131_0229b7e4 (vtable slot 0x0c): the scene closes: overlay 92's dispatcher told, then
 * the teardown. Answers 1. */
int BankAmount_Close(BankAmount *self)
{
    MenuDispatch_ChildClosed(dispatch_of(self));
    BankAmount_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov131_0229b7e4, BankAmount_Close)

/* func_ov131_0229b800 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int BankAmount_Start(BankAmount *self)
{
    BankAmount_Setup(self);
    self->base.state = BANK_AMOUNT_STATE_LOAD;
    MenuScene_SetPhase(scene_of(self), BANK_AMOUNT_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov131_0229b800, BankAmount_Start)

/* func_ov131_0229b820: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order. */
BankAmount *BankAmount_New(void)
{
    BankAmount *self = MenuScene_Alloc(sizeof(BankAmount));
    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov131_0229b8f0;
        Glider0_Construct(&self->cursor);
        ButtonPanel_Construct(&self->panel);
        BankPad_Construct(&self->pad);
    }
    return self;
}
CLEAN_AS(func_ov131_0229b820, BankAmount_New)
