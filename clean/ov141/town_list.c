/* The town list of overlay 141 (town_list.h): its destructors, its flags, the scan of the
 * parents found and the rows' fades, the cursor and its sprite. */
#include "town_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/library_overlay.h"
#include "main/session_link.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(TownList, rows) == 0x94, "rows");
static_assert(offsetof(TownList, cursor_sprite) == 0xa38 && offsetof(TownList, panel) == 0xa9c, "sprite");
static_assert(offsetof(TownList, screen_task) == 0xc68 && offsetof(TownList, parents) == 0xc8c, "parents");
static_assert(offsetof(TownList, data) == 0x11cc && offsetof(TownList, wipe_y) == 0x1268, "data");
static_assert(offsetof(TownList, picked) == 0x1270 && offsetof(TownList, quit_palette) == 0x1278, "buttons");
static_assert(offsetof(TownList, screen) == 0x127c && offsetof(TownList, flags) == 0x1a7c, "screen");
static_assert(offsetof(TownList, row_state) == 0x1a7f && offsetof(TownList, fade) == 0x1a85, "rows' bytes");
static_assert(offsetof(TownList, countdown) == 0x1a8b && offsetof(TownList, cursor) == 0x1a8c, "cursor");
static_assert(sizeof(TownList) == 0x1a90, "size (func_ov141_0229ae80)");

/* The scene's vtable. */
extern const u8 data_ov141_0229af48[];

/* Overlay 139's object (the rows): its destructor, a row's colour set to `level` of `full`
 * (palette entry `index`), a row's texts cleared or set from a parent's data (the town's name,
 * then the player's 12 bytes on). */
extern void *func_ov139_02299b30(void *rows);
extern void func_ov139_02299888(void *rows, int row, int level, int full, int index);
extern void func_ov139_02299798(void *rows, int row);
extern void func_ov139_022997c0(void *rows, int row, const void *data);

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The pad (autoload_2/input.c). */
extern PadState data_021fbe40;
#define TOWN_LIST_PAD_A 0x0001
#define TOWN_LIST_PAD_B 0x0002
#define TOWN_LIST_PAD_START 0x0008

/* The sounds: a row picked, the scene quit, the OK button. */
#define TOWN_LIST_SOUND_PICK 0x29
#define TOWN_LIST_SOUND_QUIT 0x28
#define TOWN_LIST_SOUND_OK 0x27

/* The palette entry the rows' colours fade towards, and the frames before the scene closes. */
#define TOWN_LIST_FADE_INDEX 14
#define TOWN_LIST_CLOSE_FRAMES 5

/* The cursor sprite's animations (glide.h): hidden, and at a row or a button. */
#define TOWN_LIST_ANIM_HIDDEN 0
#define TOWN_LIST_ANIM_CURSOR 7

static MenuScene *town_list_scene(TownList *self)
{
    return &self->base;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void town_list_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void town_list_destroy_members(TownList *self)
{
    self->base.vtable = data_ov141_0229af48;
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    func_ov139_02299b30(self->rows);
    MenuScene_DestroyBase(town_list_scene(self));
}

/* func_ov141_02299ee0 (vtable slot 0x40) */
TownList *TownList_Destroy(TownList *self)
{
    town_list_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov141_02299ee0, TownList_Destroy)

/* func_ov141_02299f1c (vtable slot 0x44) */
TownList *TownList_Delete(TownList *self)
{
    town_list_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov141_02299f1c, TownList_Delete)

/* func_ov141_02299f5c */
void TownList_ClearFlags(TownList *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov141_02299f5c, TownList_ClearFlags)

/* func_ov141_02299f6c */
void TownList_SetFlags(TownList *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov141_02299f6c, TownList_SetFlags)

/* func_ov141_02299f7c */
int TownList_TestFlags(TownList *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov141_02299f7c, TownList_TestFlags)

/* func_ov141_02299f94: `row` picked (-1 for none); whether that changed the row picked. The
 * OK button is greyed while none is. */
int TownList_SetPicked(TownList *self, int row)
{
    int changed = self->picked != row;
    self->picked = row;
    self->ok_palette = row == -1 ? TOWN_LIST_BUTTON_GREY : TOWN_LIST_BUTTON_NORMAL;
    return changed;
}
CLEAN_AS(func_ov141_02299f94, TownList_SetPicked)

/* func_ov141_02299fc8: called as the wipe out starts; nothing. */
void TownList_BeforeWipeOut(void) {}
CLEAN_AS(func_ov141_02299fc8, TownList_BeforeWipeOut)

/* func_ov141_02299fcc: called once the wipe in has ended; nothing. */
void TownList_AfterWipeIn(TownList *self)
{
    (void) self;
}
CLEAN_AS(func_ov141_02299fcc, TownList_AfterWipeIn)

/* func_ov141_02299fd0: `parent` kept as row `row`'s, the row found in this scan. */
void TownList_StoreParent(TownList *self, int row, const LocalParent *parent)
{
    MI_CpuCopy8(parent, &self->parents[row], sizeof(LocalParent));
    self->row_state[row] = TOWN_LIST_ROW_FOUND;
}
CLEAN_AS(func_ov141_02299fd0, TownList_StoreParent)

/* func_ov141_0229a004: the first empty row, -1 for none. */
int TownList_FreeRow(const TownList *self)
{
    for (int row = 0; row < TOWN_LIST_ROWS; row++) {
        if (self->row_state[row] == TOWN_LIST_ROW_EMPTY) {
            return row;
        }
    }
    return -1;
}
CLEAN_AS(func_ov141_0229a004, TownList_FreeRow)

/* func_ov141_0229a028: the first row whose parent has `parent`'s address, -1 for none. Only
 * the stale rows are searched: those not found yet in this scan. */
int TownList_FindParent(const TownList *self, const LocalParent *parent)
{
    for (int row = 0; row < TOWN_LIST_ROWS; row++) {
        if (self->row_state[row] != TOWN_LIST_ROW_STALE) {
            continue;
        }
        int same = 1;
        for (int i = 0; i < 6; i++) {
            if (parent->mac[i] != self->parents[row].mac[i]) {
                same = 0;
                break;
            }
        }
        if (same) {
            return row;
        }
    }
    return -1;
}
CLEAN_AS(func_ov141_0229a028, TownList_FindParent)

/* func_ov141_0229a0dc: a step of each row's fade: a row found fades in up to full, a stale one
 * fades out down to 1 and then empties (its texts cleared, and no longer picked if it was). */
void TownList_StepFades(TownList *self)
{
    for (int row = 0; row < TOWN_LIST_ROWS; row++) {
        switch (self->row_state[row]) {
            case TOWN_LIST_ROW_FOUND:
                if (self->fade[row] < TOWN_LIST_FADE_FULL) {
                    self->fade[row]++;
                    func_ov139_02299888(self->rows, row, self->fade[row], TOWN_LIST_FADE_FULL, TOWN_LIST_FADE_INDEX);
                }
                break;
            case TOWN_LIST_ROW_STALE:
                if (self->fade[row] > 1) {
                    self->fade[row]--;
                    func_ov139_02299888(self->rows, row, self->fade[row], TOWN_LIST_FADE_FULL, TOWN_LIST_FADE_INDEX);
                } else {
                    self->row_state[row] = TOWN_LIST_ROW_EMPTY;
                    func_ov139_02299798(self->rows, row);
                    if (self->picked == row) {
                        TownList_SetPicked(self, -1);
                    }
                }
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov141_0229a0dc, TownList_StepFades)

/* func_ov141_0229a174: the rows rescanned: every row found before is made stale, then each
 * parent the local wireless library lists (up to Net_CountJoinable's count) that carries this
 * game's data with the town open is found again in its row, or else given the first empty row
 * (its data kept and shown, its fade from 0). Then the fades step.
 * QUIRK: the count is walked with an 8-bit counter. */
void TownList_Scan(TownList *self)
{
    Session_SendNothing();
    int count = Net_CountJoinable();

    for (int row = 0; row < TOWN_LIST_ROWS; row++) {
        if (self->row_state[row] == TOWN_LIST_ROW_FOUND) {
            self->row_state[row] = TOWN_LIST_ROW_STALE;
        }
    }

    LibraryOverlay_Require66();
    void **entries = Local_ListEntries();

    for (u8 i = 0; i < count; i = (u8) (i + 1)) {
        LocalParent *parent = entries[i];
        if (parent == NULL) {
            continue;
        }
        LibraryOverlay_Require66();
        int size = Local_EntryDataSize(parent);
        if (size != TOWN_LIST_DATA_SIZE) {
            continue;
        }
        u8 data[TOWN_LIST_DATA_SIZE + 1];
        LibraryOverlay_Require66();
        MI_CpuCopy8(Local_EntryData(parent), data, (u32) size);
        if (data[TOWN_LIST_DATA_CLOSED] != 0) {
            continue;
        }

        int row = TownList_FindParent(self, parent);
        if (row != -1) {
            TownList_StoreParent(self, row, parent);
            continue;
        }
        row = TownList_FreeRow(self);
        if (row == -1) {
            continue;
        }
        TownList_StoreParent(self, row, parent);
        LibraryOverlay_Require66();
        int data_size = Local_EntryDataSize(parent);
        LibraryOverlay_Require66();
        MI_CpuCopy8(Local_EntryData(parent), self->data[row], (u32) data_size);
        func_ov139_022997c0(self->rows, row, self->data[row]);
        self->fade[row] = 0;
    }

    TownList_StepFades(self);
}
CLEAN_AS(func_ov141_0229a174, TownList_Scan)

/* func_ov141_0229a280: `screen` queued for layer 6 when it changed (cleared once queued). */
void TownList_QueueScreen(TownList *self)
{
    if (TownList_TestFlags(self, TOWN_LIST_FLAG_SCREEN_DIRTY)) {
        if (LayerTask_QueueScreen(&self->screen_task, (int) (uintptr_t) self->screen, 6, sizeof(self->screen), 0)) {
            TownList_ClearFlags(self, TOWN_LIST_FLAG_SCREEN_DIRTY);
        }
    }
}
CLEAN_AS(func_ov141_0229a280, TownList_QueueScreen)

/* func_ov141_0229a2c4: the cursor moved by the d-pad keys `keys`; whether it moved. On the rows
 * up and down step (down from the last row goes to the quit button); on the buttons up goes to
 * the last row, left to the quit button and right to the OK button. */
int TownList_MoveCursor(TownList *self, int keys)
{
    u8 before = self->cursor;
    if (before <= TOWN_LIST_ROW_LAST) {
        if (KeyRepeat_HasUp(keys)) {
            if (self->cursor != TOWN_LIST_ROW_FIRST) {
                self->cursor--;
            }
        } else if (KeyRepeat_HasDown(keys)) {
            if (self->cursor < TOWN_LIST_ROW_LAST) {
                self->cursor++;
            } else {
                self->cursor = TOWN_LIST_QUIT;
            }
        }
    } else {
        if (KeyRepeat_HasUp(keys)) {
            self->cursor = TOWN_LIST_ROW_LAST;
        } else if (KeyRepeat_HasLeft(keys)) {
            self->cursor = TOWN_LIST_QUIT;
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor = TOWN_LIST_OK;
        }
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov141_0229a2c4, TownList_MoveCursor)

/* func_ov141_0229a358: the cursor sprite pressed (the third of its set) until its animation
 * ends (sub state 4), then back to the sub state it was in. */
void TownList_PressCursor(TownList *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_PRESS);
}
CLEAN_AS(func_ov141_0229a358, TownList_PressCursor)

/* func_ov141_0229a384: A pressed: the cursor sprite shows the second of its set and the place
 * under the cursor acts once its animation ends (sub state 3). */
void TownList_PressA(TownList *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_A_PRESS);
}
CLEAN_AS(func_ov141_0229a384, TownList_PressA)

/* func_ov141_0229a3a4: the cursor sprite shown (the first of its set) and updated. */
void TownList_ShowCursorSprite(TownList *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    town_list_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov141_0229a3a4, TownList_ShowCursorSprite)

/* func_ov141_0229a3c4: the cursor sprite eased to (x, y) in 3 steps, with a cue unless
 * TOWN_LIST_FLAG_EASE_NO_CUE is set (it is cleared), while the scene waits for it (sub
 * state 2) to go back to the sub state it was in. */
void TownList_EaseTo(TownList *self, int x, int y)
{
    if (TownList_TestFlags(self, TOWN_LIST_FLAG_EASE_NO_CUE)) {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 0);
        TownList_ClearFlags(self, TOWN_LIST_FLAG_EASE_NO_CUE);
    } else {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    }
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov141_0229a3c4, TownList_EaseTo)

/* func_ov141_0229a428: the cursor sprite eased to the cursor's place. */
void TownList_GlideToCursor(TownList *self)
{
    int x = TownList_CursorSpriteX(self);
    int y = TownList_CursorSpriteY(self);
    TownList_EaseTo(self, x, y);
}
CLEAN_AS(func_ov141_0229a428, TownList_GlideToCursor)

/* func_ov141_0229a44c: the cursor sprite hidden (animation 0) and updated. */
void TownList_HideCursorSprite(TownList *self)
{
    Glider_SetAnim(&self->cursor_sprite, TOWN_LIST_ANIM_HIDDEN);
    town_list_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov141_0229a44c, TownList_HideCursorSprite)

/* func_ov141_0229a470: the cursor sprite's y at the cursor: below the rows for the buttons,
 * else 16 lines a row from 0x46. */
int TownList_CursorSpriteY(TownList *self)
{
    u8 cursor = self->cursor;
    if (cursor == TOWN_LIST_QUIT || cursor == TOWN_LIST_OK) {
        return 0xae;
    }
    return (cursor << 4) + 0x46;
}
CLEAN_AS(func_ov141_0229a470, TownList_CursorSpriteY)

/* func_ov141_0229a490: the cursor sprite's x at the cursor. */
int TownList_CursorSpriteX(TownList *self)
{
    u8 cursor = self->cursor;
    if (cursor == TOWN_LIST_QUIT) {
        return 0x43;
    }
    if (cursor == TOWN_LIST_OK) {
        return 0x95;
    }
    return 0x2c;
}
CLEAN_AS(func_ov141_0229a490, TownList_CursorSpriteX)

/* func_ov141_0229a4ac: the cursor sprite put at the cursor's place, in its animation, shown. */
void TownList_ShowCursorAtCursor(TownList *self)
{
    int x = TownList_CursorSpriteX(self);
    int y = TownList_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, TOWN_LIST_ANIM_CURSOR);
    TownList_ShowCursorSprite(self);
}
CLEAN_AS(func_ov141_0229a4ac, TownList_ShowCursorAtCursor)

/* func_ov141_0229a4e8: the scene quit: the quit button pressed, and the scene closes after a
 * few frames (sub state 5, then state 3). */
void TownList_Quit(TownList *self)
{
    TownList_SetFlags(self, TOWN_LIST_FLAG_QUIT);
    self->quit_palette = TOWN_LIST_BUTTON_PRESSED;
    self->countdown = TOWN_LIST_CLOSE_FRAMES;
    MenuScene_SetState(town_list_scene(self), TOWN_LIST_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_CLOSING);
    SoundSys_PlaySe(TOWN_LIST_SOUND_QUIT);
}
CLEAN_AS(func_ov141_0229a4e8, TownList_Quit)

/* func_ov141_0229a524: the row picked confirmed: the OK button pressed, and the scene closes
 * after a few frames (sub state 5, then state 3). */
void TownList_Confirm(TownList *self)
{
    TownList_ClearFlags(self, TOWN_LIST_FLAG_QUIT);
    self->ok_palette = TOWN_LIST_BUTTON_PRESSED;
    self->countdown = TOWN_LIST_CLOSE_FRAMES;
    MenuScene_SetState(town_list_scene(self), TOWN_LIST_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_CLOSING);
    SoundSys_PlaySe(TOWN_LIST_SOUND_OK);
}
CLEAN_AS(func_ov141_0229a524, TownList_Confirm)

/* func_ov141_0229a560: the scene goes on by touch or by the keys, as state flag 2 says. */
void TownList_Resume(TownList *self)
{
    if (StateFlags_IsClear2()) {
        TownList_ResumeByTouch(self);
    } else {
        TownList_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov141_0229a560, TownList_Resume)

/* func_ov141_0229a580: on by the keys: the cursor sprite shown at the cursor, the key repeat
 * reset (sub state 1). */
void TownList_ResumeByKeys(TownList *self)
{
    TownList_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(town_list_scene(self));
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_KEYS);
}
CLEAN_AS(func_ov141_0229a580, TownList_ResumeByKeys)

/* func_ov141_0229a59c: on by touch: the cursor sprite hidden (sub state 0). */
void TownList_ResumeByTouch(TownList *self)
{
    TownList_HideCursorSprite(self);
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_TOUCH);
}
CLEAN_AS(func_ov141_0229a59c, TownList_ResumeByTouch)

/* func_ov141_0229a5b4 (sub state 5): the frames counted down, then the cursor sprite hidden and
 * the states run again (phase 1: the wipe out). */
void TownList_CountDownToClose(TownList *self)
{
    if (self->countdown != 0) {
        self->countdown--;
    } else {
        TownList_HideCursorSprite(self);
        MenuScene_SetPhase(town_list_scene(self), TOWN_LIST_PHASE_STATES);
    }
}
CLEAN_AS(func_ov141_0229a5b4, TownList_CountDownToClose)

/* func_ov141_0229a5e0 (sub state 4): once the press's animation ends the sprite is shown again
 * and the sub state it was in comes back; after a row was picked the cursor then goes to the OK
 * button. */
void TownList_WaitPress(TownList *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) == 0) {
        return;
    }
    TownList_ShowCursorSprite(self);
    MenuScene_SetSubState(town_list_scene(self), self->return_sub_state);
    if (TownList_TestFlags(self, TOWN_LIST_FLAG_TO_OK)) {
        TownList_ClearFlags(self, TOWN_LIST_FLAG_TO_OK);
        self->cursor = TOWN_LIST_OK;
        TownList_GlideToCursor(self);
    }
}
CLEAN_AS(func_ov141_0229a5e0, TownList_WaitPress)

/* func_ov141_0229a634 (sub state 3): once the A press's animation ends the place under the
 * cursor acts: the OK button confirms (when a row is picked), the quit button quits, a row
 * that is not empty is picked (with the sound; the cursor then goes to the OK button with no
 * cue). Else, and after a row, the sprite is pressed and the keys go on (sub state 1).
 * REQUIRES: the cursor is a TownListPlace (0-7); the game reads past the rows for others. */
void TownList_ActOnPress(TownList *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) == 0) {
        return;
    }
    u8 cursor = self->cursor;
    if (cursor == TOWN_LIST_OK) {
        if (self->ok_palette == TOWN_LIST_BUTTON_NORMAL) {
            TownList_Confirm(self);
            return;
        }
    } else if (cursor == TOWN_LIST_QUIT) {
        TownList_Quit(self);
        return;
    } else if (self->row_state[cursor] != TOWN_LIST_ROW_EMPTY) {
        TownList_SetPicked(self, cursor);
        SoundSys_PlaySe(TOWN_LIST_SOUND_PICK);
        TownList_SetFlags(self, TOWN_LIST_FLAG_TO_OK);
        TownList_SetFlags(self, TOWN_LIST_FLAG_EASE_NO_CUE);
    }
    MenuScene_SetSubState(town_list_scene(self), TOWN_LIST_SUB_KEYS);
    TownList_PressCursor(self);
}
CLEAN_AS(func_ov141_0229a634, TownList_ActOnPress)

/* Obj_ov141_0229af48::func_ov141_0229a6b4 (sub state 2): once the cursor sprite stops, the sub
 * state it was in comes back and runs at once. */
void TownList_WaitCursorSprite(TownList *self)
{
    if (Glider_IsMoving(&self->cursor_sprite)) {
        return;
    }
    MenuScene_SetSubState(town_list_scene(self), self->return_sub_state);
    TownList_RunSubState(self);
}
CLEAN_AS(_ZN18Obj_ov141_0229af4819func_ov141_0229a6b4Ev, TownList_WaitCursorSprite)

/* func_ov141_0229a6e4 (sub state 1): the list by the keys. A touch goes on by touch; a d-pad
 * move eases the sprite to the new place; A presses the cursor, B quits, Start confirms (when a
 * row is picked). Else the rows are rescanned. */
void TownList_BrowseByKeys(TownList *self)
{
    if (MenuScene_TakeTouch(town_list_scene(self))) {
        TownList_ResumeByTouch(self);
        return;
    }
    if (TownList_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(town_list_scene(self)))) {
        TownList_GlideToCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & TOWN_LIST_PAD_A) {
        TownList_PressA(self);
        return;
    }
    if (pressed & TOWN_LIST_PAD_B) {
        TownList_HideCursorSprite(self);
        TownList_Quit(self);
        return;
    }
    if ((pressed & TOWN_LIST_PAD_START) && self->ok_palette == TOWN_LIST_BUTTON_NORMAL) {
        TownList_HideCursorSprite(self);
        TownList_Confirm(self);
        return;
    }
    TownList_Scan(self);
}
CLEAN_AS(func_ov141_0229a6e4, TownList_BrowseByKeys)

/* The pen (autoload_2/input.c): down, gone down or up this frame, and where. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* func_ov141_0229a774 (sub state 0): the list by touch. A button goes on by the keys. While
 * the pen goes down on a row that is not empty that row is picked (with the sound, when that
 * changed it); on the quit button the scene quits, on the OK button it confirms (when a row is
 * picked). When the pen does not go down the rows are rescanned. */
void TownList_BrowseByTouch(TownList *self)
{
    if (MenuScene_TakeButtons(town_list_scene(self), 1)) {
        TownList_ResumeByKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        TownList_Scan(self);
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54 - 0x10;
    if (x >= 0x28 && x < 0xd0 && y >= 0x30 && y < 0x90) {
        int row = (y - 0x30) >> 4;
        if (self->row_state[row] == TOWN_LIST_ROW_EMPTY) {
            return;
        }
        if (!TownList_SetPicked(self, row)) {
            return;
        }
        SoundSys_PlaySe(TOWN_LIST_SOUND_PICK);
    } else if (y >= 0x96 && y < 0xa7) {
        if (x >= 0x37 && x < 0x7b) {
            TownList_Quit(self);
        } else if (x >= 0x89 && x < 0xc5) {
            if (self->ok_palette == TOWN_LIST_BUTTON_NORMAL) {
                TownList_Confirm(self);
            }
        }
    }
}
CLEAN_AS(func_ov141_0229a774, TownList_BrowseByTouch)
