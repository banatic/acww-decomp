/* The bank machine's first screen of overlay 132 (bank_menu.h): its destructors, its labels,
 * the cursor sprite, the rows' actions, its sub states and states, and its scene slots. */
#include "bank_menu.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/savings.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(BankMenu, cursor_sprite) == 0x94, "sprite");
static_assert(offsetof(BankMenu, panel) == 0xf8 && offsetof(BankMenu, labels) == 0x2c4, "panel");
static_assert(offsetof(BankMenu, screen_tasks) == 0x39c && offsetof(BankMenu, error) == 0x3e4, "tasks");
static_assert(offsetof(BankMenu, screen_a) == 0x500 && offsetof(BankMenu, screen_b) == 0xd00, "screens");
static_assert(offsetof(BankMenu, flags) == 0x1500 && offsetof(BankMenu, cursor) == 0x1502, "flags");
static_assert(offsetof(BankMenu, labels_used) == 0x1504 && offsetof(BankMenu, leave_delay) == 0x1506, "bytes");
static_assert(sizeof(BankMenu) == 0x1508, "size (func_ov132_0229b888)");

/* The scene's vtable. */
extern const u8 data_ov132_0229b990[];

/* The rows' places of the cursor sprite: x, and y (the quit place's are the panel button's). */
extern const s32 data_ov132_0229b904[];
extern const s32 data_ov132_0229b910[];

/* The two screens' files. */
extern const char data_ov132_0229b9f0[]; /* "menu/bank/c0_bg.bsc" */
extern const char data_ov132_0229ba04[]; /* "menu/bank/c1_bg.bsc" */

/* The pad, and the pen (autoload_2/input.c): down, and gone down or up this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58, data_021f6c54;
#define BANK_MENU_PAD_A 0x0001
#define BANK_MENU_PAD_B 0x0002

/* Overlay 130's: the bank's background characters and palettes loaded for `layer`. */
extern int func_ov130_0229a678(void *layer);

/* The labels' constructor and destructor (TextLabel_Construct, TextLabel_Destruct), as the game
 * hands them to the vector helpers. */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The panel's button the quit place stands for. */
#define BANK_MENU_QUIT_BUTTON 6

/* The cursor sprite's animations (glide.h): at a row, at the quit button. */
#define BANK_MENU_ANIM_ROW GLIDER_ANIM_SET_A
#define BANK_MENU_ANIM_QUIT GLIDER_ANIM_SET_B

/* What the parent (overlay 92's) is told: the deposit screen, the withdrawal screen, or the
 * menu closes. */
#define BANK_MENU_MODE_DEPOSIT 0x35
#define BANK_MENU_MODE_WITHDRAW 0x36
#define BANK_MENU_MODE_CLOSE 0x44

/* The error messages: the savings are full, the pockets have no room for Bells. */
#define BANK_MENU_ERROR_SAVINGS_FULL 14
#define BANK_MENU_ERROR_POCKETS_FULL 15
#define BANK_MENU_SAVINGS_MAX 999999999

/* The sound of a row picked. */
#define BANK_MENU_PICK_SOUND 0x29

/* The rows' text messages (menu messages) and their boxes' places. */
#define BANK_MENU_MESSAGE_DEPOSIT 0x5f
#define BANK_MENU_MESSAGE_WITHDRAW 0x60

static MenuScene *bank_scene(BankMenu *self)
{
    return &self->base;
}

static CellLayerSprite *bank_sprite_cells(BankMenu *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *bank_parent(BankMenu *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void bank_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first (the screen tasks have none), then the base's. */
static void bank_destroy_members(BankMenu *self)
{
    self->base.vtable = data_ov132_0229b990;
    ErrorMessage_Destruct(&self->error);
    __cxa_vec_cleanup(self->labels, BANK_MENU_LABELS, sizeof(TextLabel), func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(bank_scene(self));
}

/* func_ov132_0229acc0 (vtable slot 0x40) */
BankMenu *BankMenu_Destroy(BankMenu *self)
{
    bank_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov132_0229acc0, BankMenu_Destroy)

/* func_ov132_0229ad0c (vtable slot 0x44) */
BankMenu *BankMenu_Delete(BankMenu *self)
{
    bank_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov132_0229ad0c, BankMenu_Delete)

/* func_ov132_0229ad60 */
void BankMenu_SetFlags(BankMenu *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov132_0229ad60, BankMenu_SetFlags)

/* func_ov132_0229ad70 */
int BankMenu_TestFlags(BankMenu *self, int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov132_0229ad70, BankMenu_TestFlags)

/* func_ov132_0229ad88: the next of the two labels; once both are handed out, the second again.
 * QUIRK: the count stops at 2, so a third call (the game makes none) answers the second label. */
TextLabel *BankMenu_NextLabel(BankMenu *self)
{
    if (self->labels_used >= BANK_MENU_LABELS) {
        return &self->labels[1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov132_0229ad88, BankMenu_NextLabel)

/* func_ov132_0229adb8: no label handed out, and both labels' boxes closed. */
void BankMenu_CloseLabels(BankMenu *self)
{
    self->labels_used = 0;
    for (int i = 0; i < BANK_MENU_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov132_0229adb8, BankMenu_CloseLabels)

/* func_ov132_0229ade4: the cursor sprite pressed (the second of its set), the pick waited for
 * (sub state 3). */
void BankMenu_PressCursorSprite(BankMenu *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_PRESS);
}
CLEAN_AS(func_ov132_0229ade4, BankMenu_PressCursorSprite)

/* func_ov132_0229adfc: the cursor sprite shown (the first of its set) and updated. */
void BankMenu_ShowCursorSprite(BankMenu *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    bank_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov132_0229adfc, BankMenu_ShowCursorSprite)

/* func_ov132_0229ae18: the cursor sprite eased to (x, y) in three steps, the sub state kept to
 * come back to once it stops (sub state 2). */
void BankMenu_GlideTo(BankMenu *self, int x, int y)
{
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov132_0229ae18, BankMenu_GlideTo)

/* func_ov132_0229ae4c: the cursor sprite turned (to set B at the quit button, else to set A) and
 * eased to the cursor. */
void BankMenu_GlideToCursor(BankMenu *self)
{
    if (self->cursor == BANK_MENU_QUIT) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = BankMenu_CursorX(self);
    int y = BankMenu_CursorY(self);
    BankMenu_GlideTo(self, x, y);
}
CLEAN_AS(func_ov132_0229ae4c, BankMenu_GlideToCursor)

/* func_ov132_0229ae90: the cursor sprite hidden (no animation) and updated. */
void BankMenu_HideCursorSprite(BankMenu *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    bank_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov132_0229ae90, BankMenu_HideCursorSprite)

/* func_ov132_0229aeac: where the cursor sprite points at the cursor: y (the panel button's at
 * the quit place).
 * REQUIRES: cursor <= 2; the game reads its table on for others. */
int BankMenu_CursorY(BankMenu *self)
{
    if (self->cursor == BANK_MENU_QUIT) {
        return ButtonPanel_ButtonY(&self->panel, BANK_MENU_QUIT_BUTTON);
    }
    return data_ov132_0229b910[self->cursor];
}
CLEAN_AS(func_ov132_0229aeac, BankMenu_CursorY)

/* func_ov132_0229aed8: ... x. */
int BankMenu_CursorX(BankMenu *self)
{
    if (self->cursor == BANK_MENU_QUIT) {
        return ButtonPanel_ButtonX(&self->panel, BANK_MENU_QUIT_BUTTON);
    }
    return data_ov132_0229b904[self->cursor];
}
CLEAN_AS(func_ov132_0229aed8, BankMenu_CursorX)

/* func_ov132_0229af04: the cursor sprite put at the cursor, with the quit button's animation or
 * a row's, and shown. */
void BankMenu_ShowCursorAtCursor(BankMenu *self)
{
    int x = BankMenu_CursorX(self);
    int y = BankMenu_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == BANK_MENU_QUIT) {
        Glider_SetAnim(&self->cursor_sprite, BANK_MENU_ANIM_QUIT);
    } else {
        Glider_SetAnim(&self->cursor_sprite, BANK_MENU_ANIM_ROW);
    }
    BankMenu_ShowCursorSprite(self);
}
CLEAN_AS(func_ov132_0229af04, BankMenu_ShowCursorAtCursor)

/* func_ov132_0229af54: error message `message` opened (not fatal), waited for (sub state 7),
 * the cursor sprite's window cleared meanwhile. */
void BankMenu_ShowError(BankMenu *self, u8 message)
{
    ErrorMessage_Open(&self->error, &message, 1, 0);
    MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_ERROR);
    CellLayerSprite_ClearWindow(bank_sprite_cells(self));
}
CLEAN_AS(func_ov132_0229af54, BankMenu_ShowError)

/* func_ov132_0229af88: the second row picked: refused (error 15) when the current player's
 * pockets have no room for Bells; else the withdrawal screen comes next, the row's part of both
 * screens (columns 6-25, rows 12-15) turned to palette 7, and the scene leaves. */
void BankMenu_PickWithdraw(BankMenu *self)
{
    PlayerPockets *pockets = PlayerRecord_Pockets(PlayerRecords_Current());
    if (PlayerPockets_BellsRoom(pockets, 1, 0) == 0) {
        BankMenu_ShowError(self, BANK_MENU_ERROR_POCKETS_FULL);
        return;
    }
    self->next_mode = BANK_MENU_MODE_WITHDRAW;
    ScreenMap_SetPalette(self->screen_a, 6, 0xc, 0x19, 0xf, 7);
    ScreenMap_SetPalette(self->screen_b, 6, 0xc, 0x19, 0xf, 7);
    BankMenu_Leave(self);
}
CLEAN_AS(func_ov132_0229af88, BankMenu_PickWithdraw)

/* func_ov132_0229aff8: the first row picked: refused (error 14) when the current player's
 * savings are full; else the deposit screen comes next, the row's part of both screens (columns
 * 6-25, rows 7-10) turned to palette 7, and the scene leaves. */
void BankMenu_PickDeposit(BankMenu *self)
{
    SavingsAccount *savings = PlayerRecord_Savings(PlayerRecords_Current());
    if (Savings_Balance(savings) == BANK_MENU_SAVINGS_MAX) {
        BankMenu_ShowError(self, BANK_MENU_ERROR_SAVINGS_FULL);
        return;
    }
    self->next_mode = BANK_MENU_MODE_DEPOSIT;
    ScreenMap_SetPalette(self->screen_a, 6, 7, 0x19, 0xa, 7);
    ScreenMap_SetPalette(self->screen_b, 6, 7, 0x19, 0xa, 7);
    BankMenu_Leave(self);
}
CLEAN_AS(func_ov132_0229aff8, BankMenu_PickDeposit)

/* func_ov132_0229b068: the scene leaves after a pick: the wipe out next (state 2) after ten
 * frames (sub state 6), both screens queued for loading again (they show the picked row) and
 * the pick's sound played. */
void BankMenu_Leave(BankMenu *self)
{
    MenuScene_SetState(bank_scene(self), BANK_MENU_STATE_START_WIPE_OUT);
    self->leave_delay = 10;
    LayerTask_QueueScreen(&self->screen_tasks[0], (int) (uintptr_t) self->screen_a, 6, BANK_MENU_SCREEN_SIZE, 0);
    LayerTask_QueueScreen(&self->screen_tasks[1], (int) (uintptr_t) self->screen_b, 4, BANK_MENU_SCREEN_SIZE, 0);
    MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_LEAVE_DELAY);
    SoundSys_PlaySe(BANK_MENU_PICK_SOUND);
}
CLEAN_AS(func_ov132_0229b068, BankMenu_Leave)

/* func_ov132_0229b0d0: the menu quit: it closes next, main told nothing was picked
 * (GroupParams_SetC4C(0)), the panel's button 6 selected, the wipe out next (state 2) once its
 * press is over (sub state 5). */
void BankMenu_Quit(BankMenu *self)
{
    self->next_mode = BANK_MENU_MODE_CLOSE;
    GroupParams_SetC4C(0);
    ButtonPanel_Select(&self->panel, BANK_MENU_QUIT_BUTTON);
    MenuScene_SetState(bank_scene(self), BANK_MENU_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_PANEL_PRESSED);
}
CLEAN_AS(func_ov132_0229b0d0, BankMenu_Quit)

/* func_ov132_0229b104: back to the menu, by touch or by the keys as the player last used. */
void BankMenu_Resume(BankMenu *self)
{
    if (StateFlags_IsClear2()) {
        BankMenu_ResumeByTouch(self);
    } else {
        BankMenu_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov132_0229b104, BankMenu_Resume)

/* func_ov132_0229b124: back to the menu by the keys: the cursor sprite shown at the cursor, the
 * key repeat reset (sub state 1). Answers MenuScene_SetSubState's result as a number. */
int BankMenu_ResumeByKeys(BankMenu *self)
{
    BankMenu_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(bank_scene(self));
    return (int) (uintptr_t) MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_KEYS);
}
CLEAN_AS(func_ov132_0229b124, BankMenu_ResumeByKeys)

/* func_ov132_0229b140: back to the menu by touch: the cursor sprite hidden (sub state 0).
 * Answers MenuScene_SetSubState's result as a number. */
int BankMenu_ResumeByTouch(BankMenu *self)
{
    BankMenu_HideCursorSprite(self);
    return (int) (uintptr_t) MenuScene_SetSubState(bank_scene(self), BANK_MENU_SUB_TOUCH);
}
CLEAN_AS(func_ov132_0229b140, BankMenu_ResumeByTouch)

/* func_ov132_0229b158 (sub state 7): once the error message is over, back to the menu and the
 * cursor sprite's window set again. */
void BankMenu_WaitError(BankMenu *self)
{
    if (ErrorMessage_Update(&self->error, 0)) {
        BankMenu_Resume(self);
        CellLayerSprite_SetWindow(bank_sprite_cells(self));
    }
}
CLEAN_AS(func_ov132_0229b158, BankMenu_WaitError)

/* func_ov132_0229b184 (sub state 6): the delay counted down; at its end the cursor sprite hidden
 * and the states run again (phase 1), for the wipe out. */
void BankMenu_WaitToLeave(BankMenu *self)
{
    if (self->leave_delay != 0) {
        self->leave_delay--;
    } else {
        BankMenu_HideCursorSprite(self);
        MenuScene_SetPhase(bank_scene(self), 1);
    }
}
CLEAN_AS(func_ov132_0229b184, BankMenu_WaitToLeave)

/* func_ov132_0229b1b0 (sub state 5): while the panel's selected button is pressed, the cursor
 * sprite (when it shows) follows the press; once it is over, the sprite hidden and the states
 * run again (phase 1), for the wipe out. */
void BankMenu_FollowQuitPress(BankMenu *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) == 0) {
        BankMenu_HideCursorSprite(self);
        MenuScene_SetPhase(bank_scene(self), 1);
        return;
    }
    if (CellLayerSprite_AnimNumber(bank_sprite_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, -1);
        int y = ButtonPanel_ButtonY(&self->panel, -1);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}
CLEAN_AS(func_ov132_0229b1b0, BankMenu_FollowQuitPress)

/* func_ov132_0229b214 (sub state 4): once the cursor sprite's animation is over, the sprite
 * shown again and the sub state kept run from the next frame. */
void BankMenu_ShowSpriteWhenDone(BankMenu *self)
{
    if (CellLayerSprite_IsDone(bank_sprite_cells(self)) != 0) {
        BankMenu_ShowCursorSprite(self);
        MenuScene_SetSubState(bank_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov132_0229b214, BankMenu_ShowSpriteWhenDone)

/* func_ov132_0229b23c (sub state 3): once the cursor sprite's press is over, the place at the
 * cursor picked.
 * QUIRK: a cursor past the quit place (the game sets none) leaves the scene in sub state 3. */
void BankMenu_PickWhenPressed(BankMenu *self)
{
    if (CellLayerSprite_IsDone(bank_sprite_cells(self)) == 0) {
        return;
    }
    switch (self->cursor) {
        case BANK_MENU_DEPOSIT:
            BankMenu_PickDeposit(self);
            break;
        case BANK_MENU_WITHDRAW:
            BankMenu_PickWithdraw(self);
            break;
        case BANK_MENU_QUIT:
            BankMenu_Quit(self);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov132_0229b23c, BankMenu_PickWhenPressed)

/* Obj_ov132_0229b990::func_ov132_0229b27c (sub state 2): once the cursor sprite stops, the sub
 * state kept is run again, this frame. */
void BankMenu_WaitCursorSprite(BankMenu *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(bank_scene(self), self->return_sub_state);
        BankMenu_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov132_0229b99019func_ov132_0229b27cEv, BankMenu_WaitCursorSprite)

/* func_ov132_0229b2a4 (sub state 1): the menu by the keys. A touch goes on by touch. Else up and
 * down (repeated) move the cursor between the three places without wrapping; a move glides the
 * sprite there. Without one, B quits (the sprite hidden) and A presses the sprite on the place
 * (sub state 3). The repeated keys are latched though only the up and down tests use them. */
void BankMenu_BrowseByKeys(BankMenu *self)
{
    if (MenuScene_TakeTouch(bank_scene(self)) != 0) {
        BankMenu_ResumeByTouch(self);
        return;
    }
    MenuScene_LatchRepeatedKeys(bank_scene(self));
    u8 before = self->cursor;
    if (MenuScene_RepeatedUp(bank_scene(self)) != 0) {
        if (self->cursor != BANK_MENU_DEPOSIT) {
            self->cursor--;
        }
    } else if (MenuScene_RepeatedDown(bank_scene(self)) != 0) {
        if (self->cursor < BANK_MENU_QUIT) {
            self->cursor++;
        }
    }
    if (before != self->cursor) {
        BankMenu_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & BANK_MENU_PAD_B) != 0) {
        BankMenu_HideCursorSprite(self);
        BankMenu_Quit(self);
    } else if ((pressed & BANK_MENU_PAD_A) != 0) {
        BankMenu_PressCursorSprite(self);
    }
}
CLEAN_AS(func_ov132_0229b2a4, BankMenu_BrowseByKeys)

/* func_ov132_0229b340 (sub state 0): the menu by touch. A button goes on by the keys. A touch
 * that went down or up this frame on the panel's button 6 quits; one with x in 0x40-0xbf picks
 * the first row with y in 0x38-0x57, the second with y in 0x60-0x7f. */
void BankMenu_BrowseByTouch(BankMenu *self)
{
    if (MenuScene_TakeButtons(bank_scene(self), 1) != 0) {
        BankMenu_ResumeByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, BANK_MENU_QUIT_BUTTON) != 0) {
        BankMenu_Quit(self);
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (x < 0x40 || x >= 0xc0) {
        return;
    }
    if (y >= 0x38 && y < 0x58) {
        BankMenu_PickDeposit(self);
        return;
    }
    if (y >= 0x60 && y < 0x80) {
        BankMenu_PickWithdraw(self);
    }
}
CLEAN_AS(func_ov132_0229b340, BankMenu_BrowseByTouch)

/* func_ov132_0229b3cc: the panel's text colours loaded. */
void BankMenu_LoadPanelColors(BankMenu *self)
{
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov132_0229b3cc, BankMenu_LoadPanelColors)

/* func_ov132_0229b3d8: the scene's graphics: overlay 130's for layer 6; each screen read from
 * its file, its rows' part (columns 6-25, rows 7-15) set to palette 6 and loaded (c0 on layer 6,
 * c1 on layer 4); then the two rows' labels from menu messages 0x5f and 0x60, each in a box of
 * style 4 at (0x114, 0xe) and (0x130, 0xe), shown. */
void BankMenu_LoadScreens(BankMenu *self)
{
    func_ov130_0229a678((void *) (uintptr_t) 6);
    RomFile_Read(data_ov132_0229b9f0, self->screen_a, BANK_MENU_SCREEN_SIZE);
    ScreenMap_SetPalette(self->screen_a, 6, 7, 0x19, 0xf, 6);
    DisplayLayer_LoadScreen(self->screen_a, 6, BANK_MENU_SCREEN_SIZE, 0);
    RomFile_Read(data_ov132_0229ba04, self->screen_b, BANK_MENU_SCREEN_SIZE);
    ScreenMap_SetPalette(self->screen_b, 6, 7, 0x19, 0xf, 6);
    DisplayLayer_LoadScreen(self->screen_b, 4, BANK_MENU_SCREEN_SIZE, 0);

    TextLabel *deposit = BankMenu_NextLabel(self);
    TextLabel_LoadMenuMessage((int) (uintptr_t) deposit, BANK_MENU_MESSAGE_DEPOSIT);
    TextLabel_OpenStyledBox2(deposit, 4, 0x114, 0xe, 0xf, 0, 0);
    TextLabel_Show(deposit, 1, 0);
    TextLabel *withdraw = BankMenu_NextLabel(self);
    TextLabel_LoadMenuMessage((int) (uintptr_t) withdraw, BANK_MENU_MESSAGE_WITHDRAW);
    TextLabel_OpenStyledBox2(withdraw, 4, 0x130, 0xe, 0xf, 0, 0);
    TextLabel_Show(withdraw, 1, 0);
}
CLEAN_AS(func_ov132_0229b3d8, BankMenu_LoadScreens)

/* func_ov132_0229b4c0: the sub screen's background mode 0; layers 6 and 4 at priority 2, each
 * with its control reset. */
void BankMenu_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 2);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
}
CLEAN_AS(func_ov132_0229b4c0, BankMenu_SetUpLayers)

/* func_ov132_0229b4f8: the frame's end: nothing. */
void BankMenu_EndFrame(void) {}
CLEAN_AS(func_ov132_0229b4f8, BankMenu_EndFrame)

/* func_ov132_0229b4fc: the frame's start: the panel's texts and the labels' boxes closed. */
void BankMenu_BeginFrame(BankMenu *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    BankMenu_CloseLabels(self);
}
CLEAN_AS(func_ov132_0229b4fc, BankMenu_BeginFrame)

/* func_ov132_0229b514 */
void BankMenu_EndInteractiveFrame(void)
{
    BankMenu_EndFrame();
}
CLEAN_AS(func_ov132_0229b514, BankMenu_EndInteractiveFrame)

/* func_ov132_0229b51c: the frame's start, then the cursor sprite updated. */
void BankMenu_BeginInteractiveFrame(BankMenu *self)
{
    BankMenu_BeginFrame(self);
    bank_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov132_0229b51c, BankMenu_BeginInteractiveFrame)

/* func_ov132_0229b534: the members torn down: the panel's texts and the labels' boxes closed,
 * both screen tasks ended. */
void BankMenu_Teardown(BankMenu *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    BankMenu_CloseLabels(self);
    LayerTask_End(&self->screen_tasks[0]);
    LayerTask_End(&self->screen_tasks[1]);
}
CLEAN_AS(func_ov132_0229b534, BankMenu_Teardown)

/* func_ov132_0229b564: the setup: the cursor at the first row, no flags. */
void BankMenu_Setup(BankMenu *self)
{
    self->cursor = BANK_MENU_DEPOSIT;
    self->flags = 0;
}
CLEAN_AS(func_ov132_0229b564, BankMenu_Setup)

/* func_ov132_0229b578: layers 6 and 4 scrolled with the wipe. */
void BankMenu_ScrollWithWipe(BankMenu *self)
{
    MenuScene_ScrollWipe(bank_scene(self), 6, 0, 0);
    MenuScene_ScrollWipe(bank_scene(self), 4, 0, 0);
}
CLEAN_AS(func_ov132_0229b578, BankMenu_ScrollWithWipe)

/* func_ov132_0229b598 (state 3): the wipe out stepped; at its end layers 6 and 4 hidden and the
 * scene deleted (phase 5); before, the layers follow it. */
void BankMenu_WipeOut(BankMenu *self)
{
    if (MenuScene_StepWipe(bank_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(6);
        DisplayLayer_HideAndResetScroll(4);
        MenuScene_SetPhase(bank_scene(self), 5);
    } else {
        BankMenu_ScrollWithWipe(self);
    }
}
CLEAN_AS(func_ov132_0229b598, BankMenu_WipeOut)

/* func_ov132_0229b5c8 (state 2): the parent told what comes next (with its sound), the wipe out
 * started on window 2 (layers 2 and 8, margin 0x30), the layers following it; state 3. */
void BankMenu_StartWipeOut(BankMenu *self)
{
    MenuDispatch_SetMode(bank_parent(self), self->next_mode, 1);
    MenuScene_StartWipeOnWindow2(bank_scene(self), 0xa, 0, 0, 0x30);
    BankMenu_ScrollWithWipe(self);
    MenuScene_SetState(bank_scene(self), BANK_MENU_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov132_0229b5c8, BankMenu_StartWipeOut)

/* func_ov132_0229b608 (state 1): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the menu. The layers follow the wipe. */
void BankMenu_WipeIn(BankMenu *self)
{
    if (MenuScene_StepWipeBack(bank_scene(self), 0)) {
        MenuScene_SetPhase(bank_scene(self), 2);
        BankMenu_Resume(self);
    }
    BankMenu_ScrollWithWipe(self);
}
CLEAN_AS(func_ov132_0229b608, BankMenu_WipeIn)

/* func_ov132_0229b630 (state 0): the layers set up, the screens and the panel's colours loaded,
 * the wipe in started covered on window 2 (layers 2 and 8, 4 frames, margin 0x30), layers 6 and
 * 4 shown and following it, the scene drawn, the panel in layout 5 with message 0x65; state 1. */
void BankMenu_StartWipeIn(BankMenu *self)
{
    BankMenu_SetUpLayers();
    BankMenu_LoadScreens(self);
    BankMenu_LoadPanelColors(self);
    MenuScene_StartWipeCoveredOnWindow2(bank_scene(self), 0xa, 4, 0, 0x30);
    DisplayLayer_Show(6);
    DisplayLayer_Show(4);
    BankMenu_ScrollWithWipe(self);
    BankMenu_SetFlags(self, BANK_MENU_FLAG_DRAWN);
    ButtonPanel_SetLayout5(&self->panel, 0x65);
    MenuScene_SetState(bank_scene(self), BANK_MENU_STATE_WIPE_IN);
}
CLEAN_AS(func_ov132_0229b630, BankMenu_StartWipeIn)

/* func_ov132_0229b68c (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int BankMenu_End(BankMenu *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov132_0229b68c, BankMenu_End)

/* func_ov132_0229b69c (vtable slot 0x58, phase 4): nothing. */
int BankMenu_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov132_0229b69c, BankMenu_Phase4Idle)

/* func_ov132_0229b6a0 (vtable slot 0x54, phase 3): nothing. */
int BankMenu_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov132_0229b6a0, BankMenu_Phase3Idle)

/* Obj_ov132_0229b990::func_ov132_0229b6a4 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int BankMenu_RunInteractive(BankMenu *self)
{
    BankMenu_BeginInteractiveFrame(self);
    BankMenu_RunSubState(self);
    BankMenu_EndInteractiveFrame();
    return 1;
}
CLEAN_AS(_ZN18Obj_ov132_0229b99019func_ov132_0229b6a4Ev, BankMenu_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov132_0229ba20; /* the sub states' guard */
extern u32 data_ov132_0229ba24; /* the states' guard */
extern MemberPointer data_ov132_0229ba48[BANK_MENU_SUB_STATES];
extern MemberPointer data_ov132_0229ba28[BANK_MENU_STATES];
extern const MemberPointer data_ov132_0229b920, data_ov132_0229b930, data_ov132_0229b938, data_ov132_0229b940,
    data_ov132_0229b948, data_ov132_0229b950, data_ov132_0229b958, data_ov132_0229b960, data_ov132_0229b968,
    data_ov132_0229b970, data_ov132_0229b978, data_ov132_0229b980;

/* Obj_ov132_0229b990::func_ov132_0229b6c0: the sub state's function (BankMenuSubState) through
 * the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 8; the game reads past the table for others. */
void BankMenu_RunSubState(BankMenu *self)
{
    static const MemberPointer *const sub_states[BANK_MENU_SUB_STATES] = {
        &data_ov132_0229b968, &data_ov132_0229b960, &data_ov132_0229b958, &data_ov132_0229b950,
        &data_ov132_0229b940, &data_ov132_0229b970, &data_ov132_0229b978, &data_ov132_0229b930,
    };
    MemberTable_InitOnce(&data_ov132_0229ba20, data_ov132_0229ba48, sub_states, BANK_MENU_SUB_STATES);
    MemberPointer_CallVoid(&data_ov132_0229ba48[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov132_0229b99019func_ov132_0229b6c0Ev, BankMenu_RunSubState)

/* Obj_ov132_0229b990::func_ov132_0229b77c (vtable slot 0x4c, phase 1): a frame of the scene's
 * states (BankMenuState) between the frame's start and end, through the table of member
 * functions (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 4; the game reads past the table for others. */
int BankMenu_RunState(BankMenu *self)
{
    static const MemberPointer *const states[BANK_MENU_STATES] = {
        &data_ov132_0229b938,
        &data_ov132_0229b980,
        &data_ov132_0229b920,
        &data_ov132_0229b948,
    };
    MemberTable_InitOnce(&data_ov132_0229ba24, data_ov132_0229ba28, states, BANK_MENU_STATES);
    BankMenu_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov132_0229ba28[self->base.state], self);
    BankMenu_EndFrame();
    return 1;
}
CLEAN_AS(_ZN18Obj_ov132_0229b99019func_ov132_0229b77cEv, BankMenu_RunState)

/* func_ov132_0229b810 (vtable slot 0x24): the scene's draw: the cursor sprite (with the keys in
 * use, even before the scene is drawn), then while the scene is drawn (else answers 0) the
 * panel with the wipe. Answers 1. */
int BankMenu_Draw(BankMenu *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (BankMenu_TestFlags(self, BANK_MENU_FLAG_DRAWN) == 0) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, MenuScene_WipeOffsetY(bank_scene(self)));
    return 1;
}
CLEAN_AS(func_ov132_0229b810, BankMenu_Draw)

/* func_ov132_0229b84c (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int BankMenu_Close(BankMenu *self)
{
    MenuDispatch_ChildClosed(bank_parent(self));
    BankMenu_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov132_0229b84c, BankMenu_Close)

/* func_ov132_0229b868 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int BankMenu_Start(BankMenu *self)
{
    BankMenu_Setup(self);
    self->base.state = BANK_MENU_STATE_START_WIPE_IN;
    MenuScene_SetPhase(bank_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov132_0229b868, BankMenu_Start)

/* func_ov132_0229b888: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order (the labels through the vector
 * helper). */
BankMenu *BankMenu_New(void)
{
    BankMenu *self = MenuScene_Alloc(sizeof(BankMenu));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov132_0229b990;
    Glider0_Construct(&self->cursor_sprite);
    ButtonPanel_Construct(&self->panel);
    __cxa_vec_ctor(self->labels, BANK_MENU_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct(&self->screen_tasks[i]);
    }
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov132_0229b888, BankMenu_New)
