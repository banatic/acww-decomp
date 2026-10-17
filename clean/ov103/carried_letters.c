/* The scene of overlay 103 (carried_letters.h): its destructors, its flags, the cursor's moves,
 * the choice it opens, the held letter and its places, its sub states and states. */
#include "carried_letters.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/label_sprite.h"
#include "main/sliding_window.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(CarriedLetters, tasks) == 0x94, "tasks");
static_assert(sizeof(LayerTaskPair) == 0x38 && offsetof(CarriedLetters, grid) == 0xcc, "grid");
static_assert(offsetof(CarriedLetters, letters) == 0xb2c && offsetof(CarriedLetters, wallet) == 0xb54, "ov094 objects");
static_assert(offsetof(CarriedLetters, popup) == 0x218c && offsetof(CarriedLetters, glide) == 0x225c, "popup");
static_assert(offsetof(CarriedLetters, cursor_sprite) == 0x2274 && offsetof(CarriedLetters, choice) == 0x22d8, "glider");
static_assert(offsetof(CarriedLetters, entries) == 0x26c0 && offsetof(CarriedLetters, error) == 0x26cc, "choice");
static_assert(offsetof(CarriedLetters, view) == 0x27e8 && offsetof(CarriedLetters, button) == 0x2b10, "view");
static_assert(offsetof(CarriedLetters, flags) == 0x2b88 && offsetof(CarriedLetters, held_x) == 0x2b98, "flags");
static_assert(offsetof(CarriedLetters, held) == 0x2ba0 && offsetof(CarriedLetters, swapped) == 0x2ca0, "letters");
static_assert(offsetof(CarriedLetters, held_kind) == 0x2da0 && offsetof(CarriedLetters, cursor) == 0x2da4, "bytes");
static_assert(offsetof(CarriedLetters, choice_row) == 0x2da9, "choice row");
static_assert(sizeof(CarriedLetters) == 0x2dac, "size (func_ov103_0229e0e4)");

/* The item code of no item (main/item_code.h). */
#define CARRIED_LETTERS_NO_ITEM 0xfff1

/* The touch (main's bytes, as ov099's pockets_view.c reads them), and the frames since the pen
 * went down (main/touch_history.c). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;
extern u8 data_021f6c30;

/* The pen (autoload_2/input.c): down, and gone down this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define CARRIED_LETTERS_PAD_A 0x0001
#define CARRIED_LETTERS_PAD_B 0x0002
#define CARRIED_LETTERS_PAD_Y 0x0800

/* The scene's vtable. */
extern const u8 data_ov103_0229e2e0[];

/* What the parent (overlay 92's dispatcher) is told: the scene ends. */
#define CARRIED_LETTERS_PARENT_CODE_END 0x44

/* The frames the pen is held on a letter before its choice opens. */
#define CARRIED_LETTERS_OPEN_FRAMES 9

/* The label button's anchor the cursor sprite points at, and its message. */
#define CARRIED_LETTERS_LABEL_ANCHOR 1
#define CARRIED_LETTERS_LABEL_MESSAGE 0x88

/* The layers: the scene's background, and the letter shown (its text on layer 3, its paper on
 * layer 4). */
#define CARRIED_LETTERS_SCENE_LAYER 6
#define CARRIED_LETTERS_TEXT_LAYER 3
#define CARRIED_LETTERS_PAPER_LAYER 4
#define CARRIED_LETTERS_WIPE_MARGIN 0x30

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants (the symbol table also names the sub states' table's later part, at 0x0229e410). */
extern u32 data_ov103_0229e340; /* the states' guard */
extern u32 data_ov103_0229e344; /* the sub states' guard */
extern MemberPointer data_ov103_0229e348[CARRIED_LETTERS_STATES];
extern MemberPointer data_ov103_0229e390[CARRIED_LETTERS_SUB_STATES];
extern const MemberPointer data_ov103_0229e1c0, data_ov103_0229e1c8, data_ov103_0229e1d0, data_ov103_0229e1e0,
    data_ov103_0229e1e8, data_ov103_0229e1f0, data_ov103_0229e1f8, data_ov103_0229e200, data_ov103_0229e208,
    data_ov103_0229e210, data_ov103_0229e218, data_ov103_0229e220, data_ov103_0229e228, data_ov103_0229e230,
    data_ov103_0229e238, data_ov103_0229e240, data_ov103_0229e248, data_ov103_0229e250, data_ov103_0229e258,
    data_ov103_0229e260, data_ov103_0229e268, data_ov103_0229e270, data_ov103_0229e278, data_ov103_0229e280,
    data_ov103_0229e288, data_ov103_0229e290, data_ov103_0229e298, data_ov103_0229e2a0, data_ov103_0229e2a8,
    data_ov103_0229e2b0, data_ov103_0229e2b8, data_ov103_0229e2c0, data_ov103_0229e2c8, data_ov103_0229e2d0;

static MenuScene *carried_scene(CarriedLetters *self)
{
    return &self->base;
}

static PagedChoice *carried_choice(CarriedLetters *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static CellLayerSprite *carried_cursor_cells(CarriedLetters *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *carried_parent(CarriedLetters *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

static int carried_is_letter(CarriedLetters *self, int place)
{
    return CarriedLetters_IsLetterPlace(self, (unsigned int) place) != 0;
}

/* QUIRK: the ROM hands the scene's address to the byte the index lookup takes first and
 * ignores. */
static u8 carried_index(CarriedLetters *self, int place)
{
    return CarriedLetters_LetterIndex((u8) (uintptr_t) self, (u8) place);
}

/* The pen went down this frame. */
static int carried_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void carried_update_cursor_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* A member drawn through its class (vtable slot 2). */
static void carried_draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x26c5 + row. */
static u8 carried_entry_value(CarriedLetters *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(CarriedLetters, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* A choice row picked with the sound of a pick, its action kept; sub state 0x15. */
static void carried_pick_choice_row(CarriedLetters *self, int row)
{
    PagedChoice_PickRowWithSound(carried_choice(self), row, 1);
    self->action = carried_entry_value(self, row);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_CLOSE);
}

/* The members' destructors, last member first, then the base's. */
static void carried_destroy_members(CarriedLetters *self)
{
    self->base.vtable = data_ov103_0229e2e0;
    Letter_Destruct(&self->swapped);
    Letter_Destruct(&self->held);
    LabelButton0_Destroy(&self->button);
    LetterView_Destruct(&self->view);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(carried_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    /* The ROM calls 0x0229bc30, ov094's function; the matching sources name ov128's and ov119's
     * at the same address. */
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(carried_scene(self));
}

/* func_ov103_0229c180 (vtable slot 0x40) */
CarriedLetters *CarriedLetters_Destroy(CarriedLetters *self)
{
    carried_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov103_0229c180, CarriedLetters_Destroy)

/* func_ov103_0229c228 (vtable slot 0x44) */
CarriedLetters *CarriedLetters_Delete(CarriedLetters *self)
{
    carried_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov103_0229c228, CarriedLetters_Delete)

/* func_ov103_0229c2d4 */
void CarriedLetters_ClearFlags(CarriedLetters *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov103_0229c2d4, CarriedLetters_ClearFlags)

/* func_ov103_0229c2e4 */
void CarriedLetters_SetFlags(CarriedLetters *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov103_0229c2e4, CarriedLetters_SetFlags)

/* func_ov103_0229c2f4: 1 when any of `flags` is set. */
int CarriedLetters_TestFlags(CarriedLetters *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov103_0229c2f4, CarriedLetters_TestFlags)

/* func_ov103_0229c30c: sub state 0x18, the label button's state 2. */
void CarriedLetters_PressLabelButton(CarriedLetters *self)
{
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_LABEL_PRESSED);
    /* The button's base is main's labelled sprite (label_button.h). */
    LabelSprite_SetState((LabelSprite *) (void *) &self->button, 2);
}
CLEAN_AS(func_ov103_0229c30c, CarriedLetters_PressLabelButton)

/* func_ov103_0229c32c (action 1): state 3 in phase 1, CARRIED_LETTERS_FLAG_READ. */
void CarriedLetters_RunActionRead(CarriedLetters *self)
{
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_START_WIPE_OUT);
    MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_STATES);
    CarriedLetters_SetFlags(self, CARRIED_LETTERS_FLAG_READ);
}
CLEAN_AS(func_ov103_0229c32c, CarriedLetters_RunActionRead)

/* func_ov103_0229c350: the cursor moved by `keys` (KeyRepeat_Has*) on the carried letters; the
 * wrap flags are cleared first. 1 when the cursor changed place; 0 at once when `keys` is 0.
 * `mode` is handed on and not read. */
int CarriedLetters_MoveCursor(CarriedLetters *self, int keys, int mode)
{
    u8 before = self->cursor;

    CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (CarriedLetters_IsLetterPlace(self, self->cursor) != 0) {
        CarriedLetters_MoveCursorInLetters(self, keys, mode);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov103_0229c350, CarriedLetters_MoveCursor)

/* func_ov103_0229c3a0: the cursor on the carried letters (5 rows of 2): left and right within a
 * row, then, when the cursor is still on a letter and no wrap flag is set, up and down within
 * the column; it stops at the edges. */
void CarriedLetters_MoveCursorInLetters(CarriedLetters *self, int keys, int mode)
{
    (void) mode;
    int index = (int) self->cursor - CARRIED_LETTERS_FIRST;
    int column = index & 1;
    /* The ROM shifts arithmetically; `index` is 0-9 for the places this is called on. */
    int row = index >> 1;

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column > 0) {
            self->cursor--;
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column < 1) {
            self->cursor++;
        }
    }

    if (CarriedLetters_IsLetterPlace(self, self->cursor) == 0 ||
        CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAGS_WRAPPED) != 0) {
        return;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= CARRIED_LETTERS_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        if (row < CARRIED_LETTERS_ROWS - 1) {
            self->cursor += CARRIED_LETTERS_COLUMNS;
        }
    }
}
CLEAN_AS(func_ov103_0229c3a0, CarriedLetters_MoveCursorInLetters)

/* func_ov103_0229c444: the choice of the letter at `place`: text 0 (pick up) when state flag 2 is
 * set; text 0x17 (state 7) or 0x14 (another state but 0) to read it; text 0x15 (action 2) when
 * the letter is in state 3 with an item, or in state 6 or 1; text 2 to cancel. The cursor sprite
 * and the popup are hidden. QUIRK: the letter's item is asked for whatever its state. */
void CarriedLetters_OpenLetterMenu(CarriedLetters *self, int place)
{
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, CARRIED_LETTERS_ACTION_CANCEL);
    Letter *letter = CarriedLetters_PlaceLetter(self, place);
    if (StateFlags_Test2() != 0) {
        ChoiceEntries_Add(&self->entries, 0, CARRIED_LETTERS_ACTION_HOLD);
    }
    int state = Letter_State(letter);
    if (state != 0) {
        if (state == 7) {
            ChoiceEntries_Add(&self->entries, 0x17, CARRIED_LETTERS_ACTION_READ);
        } else {
            ChoiceEntries_Add(&self->entries, 0x14, CARRIED_LETTERS_ACTION_READ);
        }
    }
    int has_item = Letter_Item(letter) != CARRIED_LETTERS_NO_ITEM;
    if ((has_item && state == 3) || state == 6 || state == 1) {
        ChoiceEntries_Add(&self->entries, 0x15, CARRIED_LETTERS_ACTION_2);
    }
    ChoiceEntries_Add(&self->entries, 2, CARRIED_LETTERS_ACTION_CANCEL);
    CarriedLetters_HideCursorSprite(self);
    Popup_Hide(&self->popup, 1);
    CarriedLetters_ShowChoice(self);
}
CLEAN_AS(func_ov103_0229c444, CarriedLetters_OpenLetterMenu)

/* func_ov103_0229c4fc: the cancel action, the cursor sprite put back at the cursor, the choice
 * asked to close, sub state 0x16. */
void CarriedLetters_CancelChoice(CarriedLetters *self)
{
    self->action = CARRIED_LETTERS_ACTION_CANCEL;
    CarriedLetters_PlaceCursorSprite(self);
    PagedChoice_RequestClose(carried_choice(self), 0);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov103_0229c4fc, CarriedLetters_CancelChoice)

/* func_ov103_0229c52c: the entries shown in the choice, placed beside the open place and asked
 * to open; sub state 0x14. */
void CarriedLetters_ShowChoice(CarriedLetters *self)
{
    PagedChoice_ShowEntries(carried_choice(self), &self->entries, 0);
    int x = CarriedLetters_PlaceX(self, self->slot);
    int y = CarriedLetters_PlaceY(self, self->slot);
    PagedChoice_PlaceBeside(carried_choice(self), x, y);
    PagedChoice_RequestOpen(carried_choice(self), 0);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_OPEN);
}
CLEAN_AS(func_ov103_0229c52c, CarriedLetters_ShowChoice)

/* func_ov103_0229c588: the action picked (`action`). QUIRK: action 2 (text 0x15) and any value
 * above 1 end the action as the cancel does. */
void CarriedLetters_RunAction(CarriedLetters *self)
{
    switch (self->action) {
        case CARRIED_LETTERS_ACTION_HOLD:
            CarriedLetters_RunActionHold(self);
            break;
        case CARRIED_LETTERS_ACTION_READ:
            CarriedLetters_RunActionRead(self);
            break;
        default:
            CarriedLetters_EndAction(self);
            break;
    }
}
CLEAN_AS(func_ov103_0229c588, CarriedLetters_RunAction)

/* func_ov103_0229c5b8: the popup hidden, the sub state to go back to kept, `target` kept, the
 * cursor sprite's animation 6, sub state 0x11. */
void CarriedLetters_BeginSwap(CarriedLetters *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 6);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_SWAP);
}
CLEAN_AS(func_ov103_0229c5b8, CarriedLetters_BeginSwap)

/* func_ov103_0229c604: the popup hidden, `target` kept, the cursor sprite's animation 5, sub
 * state 0x10. */
void CarriedLetters_BeginPutDown(CarriedLetters *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 5);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov103_0229c604, CarriedLetters_BeginPutDown)

/* func_ov103_0229c640 (action 0): the cursor sprite's animation 4, sub state 0x0e. */
void CarriedLetters_RunActionHold(CarriedLetters *self)
{
    Glider_SetAnim(&self->cursor_sprite, 4);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_PICK_UP);
}
CLEAN_AS(func_ov103_0229c640, CarriedLetters_RunActionHold)

/* func_ov103_0229c660: the third animation of the cursor sprite's set, sub state 0x0d. */
void CarriedLetters_BeginPressEnd(CarriedLetters *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_PRESS_END);
}
CLEAN_AS(func_ov103_0229c660, CarriedLetters_BeginPressEnd)

/* Obj_ov103_0229e2e0::func_ov103_0229c680: the first animation of the cursor sprite's set, then
 * its update. */
void CarriedLetters_ShowCursorFirstOfSet(CarriedLetters *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    carried_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(_ZN18Obj_ov103_0229e2e019func_ov103_0229c680Ev, CarriedLetters_ShowCursorFirstOfSet)

/* func_ov103_0229c6a0: the cursor sprite put at the cursor, animation 1. */
void CarriedLetters_PlaceCursorSprite(CarriedLetters *self)
{
    int x = CarriedLetters_CursorSpriteX(self);
    int y = CarriedLetters_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
}
CLEAN_AS(func_ov103_0229c6a0, CarriedLetters_PlaceCursorSprite)

/* func_ov103_0229c6d4: the cursor sprite put at the choice's first row, animation 7. */
void CarriedLetters_PointAtFirstRow(CarriedLetters *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(carried_choice(self));
    int y = PagedChoice_RowY(carried_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 7);
}
CLEAN_AS(func_ov103_0229c6d4, CarriedLetters_PointAtFirstRow)

/* func_ov103_0229c720: the cursor sprite moved to the choice row in 2 steps; the sub state to go
 * back to kept, sub state 0x0b. */
void CarriedLetters_GlideToRow(CarriedLetters *self)
{
    int x = PagedChoice_TextX(carried_choice(self));
    int y = PagedChoice_RowY(carried_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov103_0229c720, CarriedLetters_GlideToRow)

/* func_ov103_0229c774: the cursor sprite put at the cursor at once when flag 8 is set (which
 * this clears), else eased there in 3 steps with the sub state to go back to kept (sub state
 * 0x0b). */
void CarriedLetters_GlideToCursor(CarriedLetters *self)
{
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_08) != 0) {
        int x = CarriedLetters_CursorSpriteX(self);
        int y = CarriedLetters_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_08);
    } else {
        int x = CarriedLetters_CursorSpriteX(self);
        int y = CarriedLetters_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_SPRITE_MOVE);
    }
}
CLEAN_AS(func_ov103_0229c774, CarriedLetters_GlideToCursor)

/* func_ov103_0229c7ec: the cursor sprite's animation 0, then its update. */
void CarriedLetters_HideCursorSprite(CarriedLetters *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    carried_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov103_0229c7ec, CarriedLetters_HideCursorSprite)

/* func_ov103_0229c810: the cursor sprite's y, the cursor's place's. */
int CarriedLetters_CursorSpriteY(CarriedLetters *self)
{
    return CarriedLetters_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov103_0229c810, CarriedLetters_CursorSpriteY)

/* func_ov103_0229c820: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right or left with a wrap flag set. */
int CarriedLetters_CursorSpriteX(CarriedLetters *self)
{
    int x = CarriedLetters_PlaceX(self, self->cursor);
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov103_0229c820, CarriedLetters_CursorSpriteX)

/* Obj_ov103_0229e2e0::func_ov103_0229c868: the cursor sprite put at the cursor, animation 1, then
 * its set's first animation shown. */
void CarriedLetters_ShowCursorAtCursor(CarriedLetters *self)
{
    int x = CarriedLetters_CursorSpriteX(self);
    int y = CarriedLetters_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
    CarriedLetters_ShowCursorFirstOfSet(self);
}
CLEAN_AS(_ZN18Obj_ov103_0229e2e019func_ov103_0229c868Ev, CarriedLetters_ShowCursorAtCursor)

/* func_ov103_0229c8a4: when a letter is held, it changes places with the letter at `place`: the
 * held one is copied aside, the place's letter picked up and the copy put at `place`. */
void CarriedLetters_SwapHeldWith(CarriedLetters *self, int place)
{
    if (self->held_kind == CARRIED_LETTERS_HELD_LETTER) {
        Letter_Assign(&self->swapped, &self->held);
        CarriedLetters_PickUpLetter(self, place);
        CarriedLetters_PutLetterAt(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov103_0229c8a4, CarriedLetters_SwapHeldWith)

/* func_ov103_0229c8e8: the held letter, if any, put at `place`; nothing held after. */
void CarriedLetters_PutHeldAt(CarriedLetters *self, int place)
{
    if (self->held_kind == CARRIED_LETTERS_HELD_LETTER) {
        CarriedLetters_PutLetterAt(self, place, &self->held);
    }
    self->held_kind = CARRIED_LETTERS_HELD_NONE;
}
CLEAN_AS(func_ov103_0229c8e8, CarriedLetters_PutHeldAt)

/* func_ov103_0229c910: the letter at a letter place copied into `held` and taken from the
 * letters object; other places are left alone. */
void CarriedLetters_PickUpLetter(CarriedLetters *self, int place)
{
    if (!carried_is_letter(self, place)) {
        return;
    }
    int index = carried_index(self, place);
    self->held_kind = CARRIED_LETTERS_HELD_LETTER;
    Letter_Assign(&self->held, PocketsLetters_LetterAt(&self->letters, index));
    PocketsLetters_ClearPlace(&self->letters, index);
}
CLEAN_AS(func_ov103_0229c910, CarriedLetters_PickUpLetter)

/* func_ov103_0229c964: the held letter drawn where the glide is. */
void CarriedLetters_FollowGlide(CarriedLetters *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov103_0229c964, CarriedLetters_FollowGlide)

/* func_ov103_0229c994: the held letter drawn at the cursor sprite's frame, 2 left and 4 up. */
void CarriedLetters_FollowCursorSprite(CarriedLetters *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov103_0229c994, CarriedLetters_FollowCursorSprite)

/* func_ov103_0229c9c8: the held letter drawn at the touch plus the grab's offset. */
void CarriedLetters_FollowTouch(CarriedLetters *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov103_0229c9c8, CarriedLetters_FollowTouch)

/* func_ov103_0229ca00: the held letter drawn by the letters object, unless hidden. */
void CarriedLetters_DrawHeld(CarriedLetters *self)
{
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_HELD_HIDDEN) != 0) {
        return;
    }
    if (self->held_kind == CARRIED_LETTERS_HELD_LETTER) {
        PocketsLetters_DrawHeld(&self->letters, self->held_x, self->held_y, &self->held);
    }
}
CLEAN_AS(func_ov103_0229ca00, CarriedLetters_DrawHeld)

/* func_ov103_0229ca48: the popup queued to tell of the cursor's letter place when it holds a
 * letter; cleared otherwise. */
void CarriedLetters_UpdatePopup(CarriedLetters *self)
{
    if (carried_is_letter(self, self->cursor)) {
        if (CarriedLetters_PlaceIsEmpty(self, self->cursor) != 0) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov103_0229ca48, CarriedLetters_UpdatePopup)

/* func_ov103_0229ca9c: the popup's window put 0x6d left and 0x78 up of its place (8 more up when
 * state flag 2 is set), and filled by the letters object for a letter place. */
void CarriedLetters_PlacePopup(CarriedLetters *self)
{
    int x = CarriedLetters_PlaceX(self, self->popup_place) - 0x6d;
    int y = CarriedLetters_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (carried_is_letter(self, self->popup_place)) {
        int index = carried_index(self, self->popup_place);
        PocketsLetters_ShowPlaceText(&self->letters, &self->popup, index);
    }
}
CLEAN_AS(func_ov103_0229ca9c, CarriedLetters_PlacePopup)

/* func_ov103_0229cb08: whether the pen has been down for at least `frames` frames. */
int CarriedLetters_PenHeldFor(CarriedLetters *self, int frames)
{
    (void) self;
    return data_021f6c30 >= frames;
}
CLEAN_AS(func_ov103_0229cb08, CarriedLetters_PenHeldFor)

/* func_ov103_0229cb1c: whether the touch at data_021f6c60/5c is more than 8 pixels from the one
 * at data_021f6c58/54, in x or in y. */
static int carried_distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

int CarriedLetters_TouchMoved(CarriedLetters *self)
{
    (void) self;
    return carried_distance(data_021f6c60, data_021f6c58) > 8 || carried_distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov103_0229cb1c, CarriedLetters_TouchMoved)

/* func_ov103_0229cb60: a letter place highlighted by the letters object. */
void CarriedLetters_HighlightPlace(CarriedLetters *self, int place)
{
    if (!carried_is_letter(self, place)) {
        return;
    }
    PocketsLetters_MarkPlace(&self->letters, carried_index(self, place));
}
CLEAN_AS(func_ov103_0229cb60, CarriedLetters_HighlightPlace)

/* func_ov103_0229cb90: the highlights of the grid and the letters cleared. */
void CarriedLetters_ClearHighlights(CarriedLetters *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov103_0229cb90, CarriedLetters_ClearHighlights)

/* func_ov103_0229cbac: a letter place lifted in the letters object (the grid's lift dropped); any
 * other place drops both. */
void CarriedLetters_SelectPlace(CarriedLetters *self, int place)
{
    if (carried_is_letter(self, place)) {
        int index = carried_index(self, place);
        PocketsLetters_Lift(&self->letters, index);
        PocketsGrid_Unlift(&self->grid);
    } else {
        CarriedLetters_ClearSelection(self);
    }
}
CLEAN_AS(func_ov103_0229cbac, CarriedLetters_SelectPlace)

/* func_ov103_0229cbec: the lifts of the grid and the letters dropped. */
void CarriedLetters_ClearSelection(CarriedLetters *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov103_0229cbec, CarriedLetters_ClearSelection)

/* func_ov103_0229cc08: whether a letter place holds no letter; other places count as empty. */
int CarriedLetters_PlaceIsEmpty(CarriedLetters *self, int place)
{
    if (carried_is_letter(self, place)) {
        return PocketsLetters_IsEmpty(&self->letters, carried_index(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov103_0229cc08, CarriedLetters_PlaceIsEmpty)

/* func_ov103_0229cc3c: whether a letter place is dimmed by the letters object; 0 for any other
 * place. */
int CarriedLetters_PlaceIsDimmed(CarriedLetters *self, int place)
{
    if (carried_is_letter(self, place)) {
        return PocketsLetters_IsDimmed(&self->letters, carried_index(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov103_0229cc3c, CarriedLetters_PlaceIsDimmed)

/* func_ov103_0229cc70: the grid's places 0 to 14 (all of them) dimmed. */
void CarriedLetters_DimGrid(CarriedLetters *self)
{
    PocketsGrid_DimPlaces(&self->grid, 0, 0xe);
}
CLEAN_AS(func_ov103_0229cc70, CarriedLetters_DimGrid)

/* func_ov103_0229cc80: the y of a letter place by the letters object, else 0. */
int CarriedLetters_PlaceY(CarriedLetters *self, int place)
{
    if (carried_is_letter(self, place)) {
        return PocketsLetters_PlaceY(&self->letters, carried_index(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov103_0229cc80, CarriedLetters_PlaceY)

/* func_ov103_0229ccb4: the x of a letter place by the letters object, else 0. */
int CarriedLetters_PlaceX(CarriedLetters *self, int place)
{
    if (carried_is_letter(self, place)) {
        return PocketsLetters_PlaceX(&self->letters, carried_index(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov103_0229ccb4, CarriedLetters_PlaceX)

/* func_ov103_0229cce8: the letter of a letter place (the letters object's), else NULL. */
Letter *CarriedLetters_PlaceLetter(CarriedLetters *self, int place)
{
    if (carried_is_letter(self, place)) {
        return PocketsLetters_LetterAt(&self->letters, carried_index(self, place));
    }
    return NULL;
}
CLEAN_AS(func_ov103_0229cce8, CarriedLetters_PlaceLetter)

/* func_ov103_0229cd1c: a copy of `letter` put at a letter place by the letters object. */
void CarriedLetters_PutLetterAt(CarriedLetters *self, int place, Letter *letter)
{
    if (carried_is_letter(self, place)) {
        PocketsLetters_SetPlace(&self->letters, carried_index(self, place), letter);
    }
}
CLEAN_AS(func_ov103_0229cd1c, CarriedLetters_PutLetterAt)

/* func_ov103_0229cd4c: the held letter put down at `place`; a letter there is copied aside
 * (`swapped`) and put at the held letter's place (`held_from`) first. Always 1. */
int CarriedLetters_PutHeldLetterAt(CarriedLetters *self, int place)
{
    if (CarriedLetters_PlaceIsEmpty(self, place) == 0) {
        Letter_Assign(&self->swapped, CarriedLetters_PlaceLetter(self, place));
        CarriedLetters_PutLetterAt(self, self->held_from, &self->swapped);
    }
    CarriedLetters_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov103_0229cd4c, CarriedLetters_PutHeldLetterAt)

/* func_ov103_0229cd98: the letter place under the touch at (x, y), by the letters object; with
 * `with_letter`, only one holding a letter. CARRIED_LETTERS_NO_PLACE for none. */
int CarriedLetters_LetterPlaceAtTouch(CarriedLetters *self, int x, int y, int with_letter)
{
    int index = PocketsLetters_PocketAtTouch(&self->letters, x, y);
    if (index == POCKETS_LETTERS_NO_PLACE) {
        return CARRIED_LETTERS_NO_PLACE;
    }
    if (with_letter != 0 && PocketsLetters_IsEmpty(&self->letters, index) != 0) {
        return CARRIED_LETTERS_NO_PLACE;
    }
    return CarriedLetters_LetterPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov103_0229cd98, CarriedLetters_LetterPlaceAtTouch)

/* func_ov103_0229cdd8: the place of the letters object's letter `index` (0-9), else
 * CARRIED_LETTERS_NO_PLACE. */
u8 CarriedLetters_LetterPlace(CarriedLetters *self, unsigned int index)
{
    (void) self;
    if (index <= 9) {
        return (u8) (index + CARRIED_LETTERS_FIRST);
    }
    return CARRIED_LETTERS_NO_PLACE;
}
CLEAN_AS(func_ov103_0229cdd8, CarriedLetters_LetterPlace)

/* func_ov103_0229cde8: the letters object's index of a letter place, else 0. The first byte is
 * not read. */
u8 CarriedLetters_LetterIndex(u8 unused, u8 place)
{
    (void) unused;
    if (place >= CARRIED_LETTERS_FIRST && place <= CARRIED_LETTERS_LAST) {
        return (u8) (place - CARRIED_LETTERS_FIRST);
    }
    return 0;
}
CLEAN_AS(func_ov103_0229cde8, CarriedLetters_LetterIndex)

/* func_ov103_0229cdfc */
int CarriedLetters_IsLetterPlace(CarriedLetters *self, unsigned int place)
{
    (void) self;
    return place >= CARRIED_LETTERS_FIRST && place <= CARRIED_LETTERS_LAST;
}
CLEAN_AS(func_ov103_0229cdfc, CarriedLetters_IsLetterPlace)

/* func_ov103_0229ce0c: the layer load task at 0x94 taken off the main loop's queue and reset. */
void CarriedLetters_EndLayerTask(CarriedLetters *self)
{
    LayerTask_End(&self->tasks.first);
}
CLEAN_AS(func_ov103_0229ce0c, CarriedLetters_EndLayerTask)

/* func_ov103_0229ce18: the held letter glides from where it is drawn to `place` (kept as its
 * place, `held_from`) in `steps` steps, the first taken now. Sub state 0x13 follows it. */
void CarriedLetters_GlideHeldTo(CarriedLetters *self, int place, int steps)
{
    self->held_from = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = CarriedLetters_PlaceX(self, place);
    int y = CarriedLetters_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    CarriedLetters_FollowGlide(self);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov103_0229ce18, CarriedLetters_GlideHeldTo)

/* func_ov103_0229ce84: the letter at `place` picked up with the cursor, the popup hidden; when it
 * is held, the sub state to go back to is 6. It follows the cursor sprite. */
void CarriedLetters_PickUpWithCursor(CarriedLetters *self, int place)
{
    self->held_from = (u8) place;
    Popup_Hide(&self->popup, 1);
    CarriedLetters_PickUpLetter(self, place);
    if (self->held_kind == CARRIED_LETTERS_HELD_LETTER) {
        self->return_state = CARRIED_LETTERS_SUB_HOLD;
    }
    CarriedLetters_FollowCursorSprite(self);
}
CLEAN_AS(func_ov103_0229ce84, CarriedLetters_PickUpWithCursor)

/* func_ov103_0229ced0: the letter at `place` picked up with the touch, the popup hidden; when it
 * is held, sub state 2 drags it. It follows the touch. */
void CarriedLetters_PickUpWithTouch(CarriedLetters *self, int place)
{
    self->held_from = (u8) place;
    Popup_Hide(&self->popup, 1);
    CarriedLetters_PickUpLetter(self, place);
    if (self->held_kind == CARRIED_LETTERS_HELD_LETTER) {
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_DRAG);
    }
    CarriedLetters_FollowTouch(self);
}
CLEAN_AS(func_ov103_0229ced0, CarriedLetters_PickUpWithTouch)

/* func_ov103_0229cf18: `place` touched: sub state 1, the offset from the touch to the place kept,
 * the popup told of the place; the letter may be dragged (CARRIED_LETTERS_FLAG_DRAGGABLE) unless
 * it is dimmed. */
void CarriedLetters_TouchPlace(CarriedLetters *self, u8 place)
{
    self->touch_place = place;
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = CarriedLetters_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = CarriedLetters_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = place;
    Popup_Queue(&self->popup);
    if (CarriedLetters_PlaceIsDimmed(self, place)) {
        CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_DRAGGABLE);
    } else {
        CarriedLetters_SetFlags(self, CARRIED_LETTERS_FLAG_DRAGGABLE);
    }
}
CLEAN_AS(func_ov103_0229cf18, CarriedLetters_TouchPlace)

/* func_ov103_0229cfa0: the action ends: back to sub state 0 with the cursor sprite hidden while
 * state flag 2 is clear, else to sub state 5 with it at the cursor. */
void CarriedLetters_EndAction(CarriedLetters *self)
{
    if (StateFlags_IsClear2()) {
        CarriedLetters_EndActionHidden(self);
    } else {
        CarriedLetters_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov103_0229cfa0, CarriedLetters_EndAction)

/* func_ov103_0229cfc0: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 5 and the cursor's place selected. */
void CarriedLetters_EndActionAtCursor(CarriedLetters *self)
{
    self->popup_place = CARRIED_LETTERS_NO_PLACE;
    CarriedLetters_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(carried_scene(self));
    CarriedLetters_UpdatePopup(self);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_BROWSE);
    CarriedLetters_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov103_0229cfc0, CarriedLetters_EndActionAtCursor)

/* func_ov103_0229cffc */
void CarriedLetters_EndActionHidden(CarriedLetters *self)
{
    CarriedLetters_HideCursorSprite(self);
    CarriedLetters_ClearSelection(self);
    MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov103_0229cffc, CarriedLetters_EndActionHidden)

/* func_ov103_0229d018 (sub state 0x18): while the label button's animation plays, the cursor
 * sprite (when shown) follows its anchor; after, the sprite is hidden, state 7 and phase 1. */
void CarriedLetters_FollowLabelPress(CarriedLetters *self)
{
    if (LabelButton_StepAnimation(&self->button) != 0) {
        if (CellLayerSprite_AnimNumber(carried_cursor_cells(self)) != 0) {
            int x = LabelButton_AnchorX(&self->button, CARRIED_LETTERS_LABEL_ANCHOR);
            int y = LabelButton_AnchorY(&self->button, CARRIED_LETTERS_LABEL_ANCHOR);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
        }
    } else {
        CarriedLetters_HideCursorSprite(self);
        MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_START_LETTER_WIPE_OUT);
        MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_STATES);
    }
}
CLEAN_AS(func_ov103_0229d018, CarriedLetters_FollowLabelPress)

/* func_ov103_0229d080 (sub state 0x17): once the error message is done, back to the sub state
 * kept, the cursor sprite's window flag set. */
void CarriedLetters_WaitError(CarriedLetters *self)
{
    if (ErrorMessage_Update(&self->error, 0)) {
        MenuScene_SetSubState(carried_scene(self), self->return_state);
        CellLayerSprite_SetWindow(carried_cursor_cells(self));
    }
}
CLEAN_AS(func_ov103_0229d080, CarriedLetters_WaitError)

/* func_ov103_0229d0b8 (sub state 0x16): the action picked runs once the choice is idle. */
void CarriedLetters_RunActionWhenIdle(CarriedLetters *self)
{
    if (PagedChoice_IsIdle(carried_choice(self)) != 0) {
        CarriedLetters_RunAction(self);
    }
}
CLEAN_AS(func_ov103_0229d0b8, CarriedLetters_RunActionWhenIdle)

/* func_ov103_0229d0d8 (sub state 0x15): once the delay after the pick has run out, the choice
 * asked to close and the cursor sprite (when shown) put back at the cursor; sub state 0x16. */
void CarriedLetters_CloseChoice(CarriedLetters *self)
{
    if (PagedChoice_CountDown(carried_choice(self)) != 0) {
        PagedChoice_RequestClose(carried_choice(self), 0);
        if (CellLayerSprite_AnimNumber(carried_cursor_cells(self)) != 0) {
            CarriedLetters_PlaceCursorSprite(self);
        }
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov103_0229d0d8, CarriedLetters_CloseChoice)

/* func_ov103_0229d11c (sub state 0x14): once the choice is shown, it is run by the keys (the
 * cursor sprite at its first row, sub state 9) when state flag 2 is set, else by the touch (sub
 * state 4). */
void CarriedLetters_WaitChoiceShown(CarriedLetters *self)
{
    if (PagedChoice_IsShown(carried_choice(self)) != 0) {
        if (StateFlags_Test2()) {
            CarriedLetters_PointAtFirstRow(self);
            MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_BY_KEYS);
        } else {
            MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_BY_TOUCH);
        }
    }
}
CLEAN_AS(func_ov103_0229d11c, CarriedLetters_WaitChoiceShown)

/* func_ov103_0229d158 (sub state 0x13): the held letter follows its glide. When the glide is over
 * the letter is put at its place (`held_from`) and the action ends. */
void CarriedLetters_StepHeldGlide(CarriedLetters *self)
{
    if (Glide_Step(&self->glide) != 0) {
        CarriedLetters_PutHeldAt(self, self->held_from);
        CarriedLetters_EndAction(self);
    } else {
        CarriedLetters_FollowGlide(self);
    }
}
CLEAN_AS(func_ov103_0229d158, CarriedLetters_StepHeldGlide)

/* func_ov103_0229d190 (sub state 0x12): back to the sub state kept once the cursor sprite's
 * animation has ended; once its turn has settled, the held letter is shown again and follows the
 * sprite. */
void CarriedLetters_FinishSwap(CarriedLetters *self)
{
    if (CellLayerSprite_IsDone(carried_cursor_cells(self))) {
        MenuScene_SetSubState(carried_scene(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_HELD_HIDDEN);
        CarriedLetters_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov103_0229d190, CarriedLetters_FinishSwap)

/* func_ov103_0229d1d4 (sub state 0x11): unless the cursor sprite's turn is at its frame 2, the
 * held letter changes places with the one at `target`, the new held letter hidden for now, the
 * popup updated; sub state 0x12. At frame 2, sub state 5. */
void CarriedLetters_Swap(CarriedLetters *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        CarriedLetters_SwapHeldWith(self, self->target);
        CarriedLetters_SetFlags(self, CARRIED_LETTERS_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_SWAP_END);
        CarriedLetters_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov103_0229d1d4, CarriedLetters_Swap)

/* func_ov103_0229d21c (sub state 0x10): while the cursor sprite's turn has not settled, the held
 * letter is put down at `target` when the cursor is on it (the popup updated, sub state 5), else
 * glided there in 4 steps; once it has, the letter follows the sprite. */
void CarriedLetters_PutDown(CarriedLetters *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        u8 target = self->target;
        if (self->cursor == target) {
            CarriedLetters_PutHeldLetterAt(self, target);
            CarriedLetters_UpdatePopup(self);
            MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_BROWSE);
        } else {
            CarriedLetters_GlideHeldTo(self, target, 4);
        }
    } else {
        CarriedLetters_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov103_0229d21c, CarriedLetters_PutDown)

/* func_ov103_0229d270 (sub state 0x0f): back to the sub state kept once the cursor sprite's
 * animation has ended; the held letter follows the sprite. */
void CarriedLetters_FinishPickUp(CarriedLetters *self)
{
    if (CellLayerSprite_IsDone(carried_cursor_cells(self))) {
        MenuScene_SetSubState(carried_scene(self), self->return_state);
    }
    CarriedLetters_FollowCursorSprite(self);
}
CLEAN_AS(func_ov103_0229d270, CarriedLetters_FinishPickUp)

/* func_ov103_0229d2a0 (sub state 0x0e): once the cursor sprite's turn has settled, the letter at
 * the cursor is picked up; sub state 0x0f. */
void CarriedLetters_PickUpAtCursor(CarriedLetters *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        CarriedLetters_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_PICK_UP_END);
    }
}
CLEAN_AS(func_ov103_0229d2a0, CarriedLetters_PickUpAtCursor)

/* Obj_ov103_0229e2e0::func_ov103_0229d2d0 (sub state 0x0d): once the cursor sprite's animation
 * has ended, its set's first animation; sub state 5. */
void CarriedLetters_FinishPlacePress(CarriedLetters *self)
{
    if (CellLayerSprite_IsDone(carried_cursor_cells(self))) {
        CarriedLetters_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_BROWSE);
    }
}
CLEAN_AS(_ZN18Obj_ov103_0229e2e019func_ov103_0229d2d0Ev, CarriedLetters_FinishPlacePress)

/* func_ov103_0229d2f8 (sub state 0x0c): once the cursor sprite's animation has ended, sub state
 * 0x0d with its set's third animation. */
void CarriedLetters_PressPlace(CarriedLetters *self)
{
    if (CellLayerSprite_IsDone(carried_cursor_cells(self))) {
        CarriedLetters_BeginPressEnd(self);
    }
}
CLEAN_AS(func_ov103_0229d2f8, CarriedLetters_PressPlace)

/* Obj_ov103_0229e2e0::func_ov103_0229d318 (sub state 0x0b): once the cursor sprite stops moving,
 * back to the sub state kept (the cursor's place selected for sub state 5), which runs at once;
 * the held letter follows the sprite. */
void CarriedLetters_WaitCursorSprite(CarriedLetters *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(carried_scene(self), self->return_state);
        if (self->return_state == CARRIED_LETTERS_SUB_BROWSE) {
            CarriedLetters_SelectPlace(self, self->cursor);
        }
        CarriedLetters_RunSubState(self);
    }
    CarriedLetters_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov103_0229e2e019func_ov103_0229d318Ev, CarriedLetters_WaitCursorSprite)

/* func_ov103_0229d364 (sub state 0x0a): once the cursor sprite's animation has ended, the choice
 * row it points at is picked. */
void CarriedLetters_PickChoiceRow(CarriedLetters *self)
{
    if (CellLayerSprite_IsDone(carried_cursor_cells(self)) == 0) {
        return;
    }
    carried_pick_choice_row(self, self->choice_row);
}
CLEAN_AS(func_ov103_0229d364, CarriedLetters_PickChoiceRow)

/* func_ov103_0229d3b4 (sub state 9): the choice by the keys. A touch cancels it; the keys move
 * the row, the cursor sprite gliding to it; A plays the sprite's second animation of its set and
 * picks the row (sub state 0x0a), B cancels. */
void CarriedLetters_ChooseByKeys(CarriedLetters *self)
{
    if (MenuScene_TakeTouch(carried_scene(self))) {
        CarriedLetters_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(carried_scene(self));
    if (PagedChoice_MoveCursor(carried_choice(self), keys, &self->choice_row, 0)) {
        CarriedLetters_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & CARRIED_LETTERS_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_CHOICE_PICK);
    } else if (pressed & CARRIED_LETTERS_PAD_B) {
        CarriedLetters_CancelChoice(self);
    }
}
CLEAN_AS(func_ov103_0229d3b4, CarriedLetters_ChooseByKeys)

/* func_ov103_0229d430 (sub state 8): the label button pressed once the cursor sprite's animation
 * has ended. */
void CarriedLetters_WaitLabelPress(CarriedLetters *self)
{
    if (CellLayerSprite_IsDone(carried_cursor_cells(self))) {
        CarriedLetters_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov103_0229d430, CarriedLetters_WaitLabelPress)

/* func_ov103_0229d450 (sub state 7): the label button by the keys. A hidden cursor sprite is
 * shown on the button's anchor (animation 1); a touch hides it (sub state 3); A or B plays the
 * sprite's second animation of its set, sub state 8. */
void CarriedLetters_LabelByKeys(CarriedLetters *self)
{
    if (CellLayerSprite_AnimNumber(carried_cursor_cells(self)) == 0) {
        int x = LabelButton_AnchorX(&self->button, CARRIED_LETTERS_LABEL_ANCHOR);
        int y = LabelButton_AnchorY(&self->button, CARRIED_LETTERS_LABEL_ANCHOR);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    if (MenuScene_TakeTouch(carried_scene(self))) {
        CarriedLetters_HideCursorSprite(self);
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_LABEL_BY_TOUCH);
    } else if (data_021fbe40.pressed & (CARRIED_LETTERS_PAD_A | CARRIED_LETTERS_PAD_B)) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_LABEL_PRESS);
    }
}
CLEAN_AS(func_ov103_0229d450, CarriedLetters_LabelByKeys)

/* func_ov103_0229d4e4 (sub state 6): a held letter moved with the cursor. A move of the cursor
 * updates the popup and moves the sprite (the popup hidden, its queue kept). A puts the letter
 * down at the cursor (sub state 0x10) when its place is empty, else swaps (sub state 0x11); B
 * sends the letter back to its place (sub state 0x10). Else the letter follows the sprite and a
 * queued popup is shown. */
void CarriedLetters_MoveHeldByKeys(CarriedLetters *self)
{
    if (CarriedLetters_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(carried_scene(self)), 1) != 0) {
        CarriedLetters_UpdatePopup(self);
        CarriedLetters_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & CARRIED_LETTERS_PAD_A) {
        if (CarriedLetters_PlaceIsEmpty(self, self->cursor) != 0) {
            CarriedLetters_BeginPutDown(self, self->cursor);
        } else {
            CarriedLetters_BeginSwap(self, self->cursor);
        }
    } else if (pressed & CARRIED_LETTERS_PAD_B) {
        CarriedLetters_BeginPutDown(self, self->held_from);
    } else {
        CarriedLetters_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov103_0229d4e4, CarriedLetters_MoveHeldByKeys)

/* func_ov103_0229d580 (sub state 5): the cursor moved by the keys, nothing held. A touch ends the
 * action without the sprite. A move updates the popup and moves the sprite (the popup hidden, its
 * queue kept). A on a letter that is not dimmed opens its choice. Y closes the scene: state 3
 * (written directly) in phase 1, the popup and the cursor sprite hidden, no letter to read. Else
 * a queued popup is shown. */
void CarriedLetters_BrowseByKeys(CarriedLetters *self)
{
    if (MenuScene_TakeTouch(carried_scene(self))) {
        CarriedLetters_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (CarriedLetters_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(carried_scene(self)), 0) != 0) {
        CarriedLetters_UpdatePopup(self);
        CarriedLetters_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (CarriedLetters_PlaceIsDimmed(self, self->cursor) == 0 && (pressed & CARRIED_LETTERS_PAD_A)) {
        if (carried_is_letter(self, self->cursor) && CarriedLetters_PlaceIsEmpty(self, self->cursor) == 0) {
            CarriedLetters_OpenLetterMenu(self, self->cursor);
        }
        return;
    }
    if (pressed & CARRIED_LETTERS_PAD_Y) {
        self->base.state = CARRIED_LETTERS_STATE_START_WIPE_OUT;
        MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_STATES);
        Popup_Hide(&self->popup, 1);
        CarriedLetters_HideCursorSprite(self);
        CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_READ);
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov103_0229d580, CarriedLetters_BrowseByKeys)

/* func_ov103_0229d664 (sub state 4): the choice by the touch. A button cancels it; the pen going
 * down picks the row under it (the last one outside the window). */
void CarriedLetters_ChooseByTouch(CarriedLetters *self)
{
    if (MenuScene_TakeButtons(carried_scene(self), 1) != 0) {
        CarriedLetters_CancelChoice(self);
        return;
    }
    if (!carried_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(carried_choice(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        carried_pick_choice_row(self, row);
    }
}
CLEAN_AS(func_ov103_0229d664, CarriedLetters_ChooseByTouch)

/* func_ov103_0229d6f0 (sub state 3): the label button by the touch. A button gives it to the keys
 * (sub state 7); a touch on it presses it. */
void CarriedLetters_LabelByTouch(CarriedLetters *self)
{
    if (MenuScene_TakeButtons(carried_scene(self), 1) != 0) {
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_LABEL_BY_KEYS);
        return;
    }
    if (LabelButton_IsTouched(&self->button) != 0) {
        CarriedLetters_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov103_0229d6f0, CarriedLetters_LabelByTouch)

/* func_ov103_0229d724 (sub state 2): the held letter dragged with the touch, the highlights
 * cleared. The letter place under it (8 right and 8 below where it is drawn) is highlighted while
 * the pen is down. Let go on a place that is not dimmed, the letter is put down there and the
 * action ends; let go elsewhere, it glides back to its place in 4 steps. */
void CarriedLetters_DragHeld(CarriedLetters *self)
{
    CarriedLetters_FollowTouch(self);
    CarriedLetters_ClearHighlights(self);
    int x = (int) ((u32) self->held_x + 8);
    int y = (int) ((u32) self->held_y + 8);
    int place = CarriedLetters_LetterPlaceAtTouch(self, x, y, 0);

    if (place == CARRIED_LETTERS_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            CarriedLetters_GlideHeldTo(self, self->held_from, 4);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        CarriedLetters_HighlightPlace(self, place);
        return;
    }
    if (CarriedLetters_PlaceIsDimmed(self, place) != 0 || CarriedLetters_PutHeldLetterAt(self, place) == 0) {
        CarriedLetters_GlideHeldTo(self, self->held_from, 4);
    } else {
        CarriedLetters_EndAction(self);
    }
}
CLEAN_AS(func_ov103_0229d724, CarriedLetters_DragHeld)

/* func_ov103_0229d7bc (sub state 1): a place is touched. Let go, the scene goes back to sub state 0
 * with the popup's timer at 60 frames. Held down on a letter that may be dragged: moving off it
 * picks it up (CarriedLetters_PickUpWithTouch); held there for 9 frames, its choice opens.
 * Otherwise a queued popup is shown. */
void CarriedLetters_HoldTouchOnPlace(CarriedLetters *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_TOUCH_IDLE);
        Popup_SetTimer(&self->popup, 0x3c);
        return;
    }
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_DRAGGABLE) != 0) {
        if (CarriedLetters_TouchMoved(self) != 0) {
            CarriedLetters_PickUpWithTouch(self, self->touch_place);
            return;
        }
        if (CarriedLetters_PenHeldFor(self, CARRIED_LETTERS_OPEN_FRAMES) != 0) {
            CarriedLetters_OpenLetterMenu(self, self->touch_place);
            return;
        }
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov103_0229d7bc, CarriedLetters_HoldTouchOnPlace)

/* func_ov103_0229d82c (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 5). The pen going down touches the letter
 * place under it when it holds a letter. */
void CarriedLetters_IdleByTouch(CarriedLetters *self)
{
    if (MenuScene_TakeButtons(carried_scene(self), 1) != 0) {
        CarriedLetters_EndActionAtCursor(self);
        return;
    }
    if (!carried_pen_pressed()) {
        return;
    }
    int place = CarriedLetters_LetterPlaceAtTouch(self, data_021f6c58, data_021f6c54, 1);
    if (place != CARRIED_LETTERS_NO_PLACE) {
        CarriedLetters_TouchPlace(self, (u8) place);
    }
}
CLEAN_AS(func_ov103_0229d82c, CarriedLetters_IdleByTouch)

/* func_ov103_0229d890: a step of the wallet display's setup (PocketsWallet_LoadObjFiles). */
int CarriedLetters_LoadWalletObjFiles(CarriedLetters *self)
{
    return PocketsWallet_LoadObjFiles(&self->wallet);
}
CLEAN_AS(func_ov103_0229d890, CarriedLetters_LoadWalletObjFiles)

/* func_ov103_0229d8a0: the wallet's display started with 0. */
void CarriedLetters_PrepareWallet(CarriedLetters *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov103_0229d8a0, CarriedLetters_PrepareWallet)

/* func_ov103_0229d8b4: the scene layer at priority 2 with its plain background settings. */
void CarriedLetters_SetUpLayer(void)
{
    DisplayLayer_SetPriority(CARRIED_LETTERS_SCENE_LAYER, 2);
    DisplayLayer_SetBgControl(CARRIED_LETTERS_SCENE_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov103_0229d8b4, CarriedLetters_SetUpLayer)

/* func_ov103_0229d8d4: the end of a frame: the choice and the wallet's display updated, and the
 * popup placed when its update asks for it. */
void CarriedLetters_EndFrame(CarriedLetters *self)
{
    PagedChoice_Update(carried_choice(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup) != 0) {
        CarriedLetters_PlacePopup(self);
    }
}
CLEAN_AS(func_ov103_0229d8d4, CarriedLetters_EndFrame)

/* func_ov103_0229d90c: the start of a frame: the layer task ended and the three objects of
 * ov094's updated. */
void CarriedLetters_BeginFrame(CarriedLetters *self)
{
    CarriedLetters_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
}
CLEAN_AS(func_ov103_0229d90c, CarriedLetters_BeginFrame)

/* func_ov103_0229d93c */
void CarriedLetters_EndInteractiveFrame(CarriedLetters *self)
{
    CarriedLetters_EndFrame(self);
}
CLEAN_AS(func_ov103_0229d93c, CarriedLetters_EndInteractiveFrame)

/* func_ov103_0229d944: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void CarriedLetters_BeginInteractiveFrame(CarriedLetters *self)
{
    CarriedLetters_BeginFrame(self);
    carried_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov103_0229d944, CarriedLetters_BeginInteractiveFrame)

/* func_ov103_0229d960: the members' teardown before the scene closes. */
void CarriedLetters_Teardown(CarriedLetters *self)
{
    CarriedLetters_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(carried_choice(self));
    LetterView_ReleaseBoxes(&self->view);
}
CLEAN_AS(func_ov103_0229d960, CarriedLetters_Teardown)

/* func_ov103_0229d99c: the scene's setup: no flags, the three objects of ov094's set up, no popup
 * place, the glide stopped, nothing held, the cursor on the first letter, the choice and the
 * letter view on layer 3. */
void CarriedLetters_Setup(CarriedLetters *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 2);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, 6);
    self->popup_place = CARRIED_LETTERS_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = CARRIED_LETTERS_HELD_NONE;
    self->cursor = CARRIED_LETTERS_FIRST;
    PagedChoice_Init(carried_choice(self), CARRIED_LETTERS_TEXT_LAYER, 1, NULL);
    LetterView_Init(&self->view, CARRIED_LETTERS_TEXT_LAYER);
}
CLEAN_AS(func_ov103_0229d99c, CarriedLetters_Setup)

/* The letter's two layers (text and paper) scrolled by the wipe. */
static void carried_scroll_letter_layers(CarriedLetters *self)
{
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_TEXT_LAYER, 0, 0);
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_PAPER_LAYER, 0, 0);
}

/* func_ov103_0229da20 (state 8): the letter wipes out; when done, its layers hidden, the label
 * button no longer drawn and the scene set up again (CarriedLetters_StartSetup). Else its layers
 * follow the wipe. */
void CarriedLetters_LetterWipeOut(CarriedLetters *self)
{
    if (MenuScene_StepWipe(carried_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(CARRIED_LETTERS_TEXT_LAYER);
        DisplayLayer_HideAndResetScroll(CARRIED_LETTERS_PAPER_LAYER);
        CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_LETTER_SHOWN);
        CarriedLetters_StartSetup(self);
    } else {
        carried_scroll_letter_layers(self);
    }
}
CLEAN_AS(func_ov103_0229da20, CarriedLetters_LetterWipeOut)

/* func_ov103_0229da68 (state 7, after the label button's press): the letter starts to wipe out on
 * window 2 (state 8). */
void CarriedLetters_StartLetterWipeOut(CarriedLetters *self)
{
    MenuScene_StartWipeOnWindow2(carried_scene(self), 3, 0, 0, CARRIED_LETTERS_WIPE_MARGIN);
    carried_scroll_letter_layers(self);
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_LETTER_WIPE_OUT);
}
CLEAN_AS(func_ov103_0229da68, CarriedLetters_StartLetterWipeOut)

/* func_ov103_0229daa4 (state 6): the letter wipes in; when done, phase 2 and its label button by
 * the touch (sub state 3) while state flag 2 is clear, else by the keys (sub state 7). Else its
 * layers follow the wipe. */
void CarriedLetters_LetterWipeIn(CarriedLetters *self)
{
    if (MenuScene_StepWipeBack(carried_scene(self), 0) != 0) {
        MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_INTERACTIVE);
        if (StateFlags_IsClear2()) {
            MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_LABEL_BY_TOUCH);
        } else {
            MenuScene_SetSubState(carried_scene(self), CARRIED_LETTERS_SUB_LABEL_BY_KEYS);
        }
    } else {
        carried_scroll_letter_layers(self);
    }
}
CLEAN_AS(func_ov103_0229daa4, CarriedLetters_LetterWipeIn)

/* func_ov103_0229daf4 (state 5): the letter of the place whose choice was open is shown:
 * Letter_AdvanceReceived moves its state on, the letter view shows it (layers 3 and 4, priority
 * 1), the two layers shown and wiping in on window 2 (state 6), and the label button is shown with
 * message 0x88 and drawn. */
void CarriedLetters_ShowLetter(CarriedLetters *self)
{
    Letter *letter = CarriedLetters_PlaceLetter(self, self->slot);
    Letter_AdvanceReceived(letter);
    LetterView_Show(&self->view, (const LetterViewLetter *) (const void *) letter, CARRIED_LETTERS_TEXT_LAYER,
                    CARRIED_LETTERS_PAPER_LAYER, 1);
    MenuScene_StartWipeCoveredOnWindow2(carried_scene(self), 3, 0, 0, CARRIED_LETTERS_WIPE_MARGIN);
    DisplayLayer_Show(CARRIED_LETTERS_TEXT_LAYER);
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_TEXT_LAYER, 0, 0);
    DisplayLayer_Show(CARRIED_LETTERS_PAPER_LAYER);
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_PAPER_LAYER, 0, 0);
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_LETTER_WIPE_IN);
    LabelButton_ShowLowerRight(&self->button, CARRIED_LETTERS_LABEL_MESSAGE);
    CarriedLetters_SetFlags(self, CARRIED_LETTERS_FLAG_LETTER_SHOWN);
}
CLEAN_AS(func_ov103_0229daf4, CarriedLetters_ShowLetter)

/* func_ov103_0229db7c (state 4): the scene wipes out; when done, its layer hidden and its objects
 * no longer drawn: with CARRIED_LETTERS_FLAG_READ the letter is shown (state 5, run at once), else
 * the scene is no longer drawn and phase 5 ends it. Else the scene layer follows the wipe. The
 * wipe's offset is kept for the objects. */
void CarriedLetters_SceneWipeOut(CarriedLetters *self)
{
    if (MenuScene_StepWipe(carried_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(CARRIED_LETTERS_SCENE_LAYER);
        CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_OBJECTS_DRAWN);
        if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_READ) != 0) {
            MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_SHOW_LETTER);
            CarriedLetters_ShowLetter(self);
        } else {
            CarriedLetters_ClearFlags(self, CARRIED_LETTERS_FLAG_DRAWN);
            MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_END);
        }
    } else {
        MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_SCENE_LAYER, 0, 0);
    }
    self->objects_y = MenuScene_WipeOffsetY(carried_scene(self));
}
CLEAN_AS(func_ov103_0229db7c, CarriedLetters_SceneWipeOut)

/* func_ov103_0229dbec (state 3, Y or the read action): the popup hidden (its queue dropped) and
 * the cursor sprite hidden; the parent told the scene ends (code 0x44, with its sound) unless a
 * letter is to be read; the scene starts to wipe out on window 2 (state 4), the wipe's offset kept
 * for the objects. */
void CarriedLetters_StartWipeOut(CarriedLetters *self)
{
    Popup_Hide(&self->popup, 1);
    CarriedLetters_HideCursorSprite(self);
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_READ) == 0) {
        MenuDispatch_SetMode(carried_parent(self), CARRIED_LETTERS_PARENT_CODE_END, 1);
    }
    MenuScene_StartWipeOnWindow2(carried_scene(self), 8, 0, 0, CARRIED_LETTERS_WIPE_MARGIN);
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_SCENE_LAYER, 0, 0);
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_SCENE_WIPE_OUT);
    self->objects_y = MenuScene_WipeOffsetY(carried_scene(self));
}
CLEAN_AS(func_ov103_0229dbec, CarriedLetters_StartWipeOut)

/* func_ov103_0229dc60 (state 2): the scene wipes in; when done, phase 2 and the action ends. The
 * scene layer follows the wipe, its offset kept for the objects. */
void CarriedLetters_SceneWipeIn(CarriedLetters *self)
{
    if (MenuScene_StepWipeBack(carried_scene(self), 0) != 0) {
        MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_INTERACTIVE);
        CarriedLetters_EndAction(self);
    }
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_SCENE_LAYER, 0, 0);
    self->objects_y = MenuScene_WipeOffsetY(carried_scene(self));
}
CLEAN_AS(func_ov103_0229dc60, CarriedLetters_SceneWipeIn)

/* func_ov103_0229dc9c (state 1): a step of the wallet's setup (its answer unused), the grid's and
 * the letters' objects prepared, the grid dimmed, the scene layer shown and wiping in on window 2
 * (state 2); the scene and its objects drawn, the wipe's offset kept for them. */
void CarriedLetters_StartWipeIn(CarriedLetters *self)
{
    CarriedLetters_LoadWalletObjFiles(self);
    PocketsGrid_LoadPockets(&self->grid);
    PocketsLetters_LoadPockets(&self->letters);
    CarriedLetters_DimGrid(self);
    MenuScene_StartWipeCoveredOnWindow2(carried_scene(self), 8, 0, 0, CARRIED_LETTERS_WIPE_MARGIN);
    DisplayLayer_Show(CARRIED_LETTERS_SCENE_LAYER);
    MenuScene_ScrollWipe(carried_scene(self), CARRIED_LETTERS_SCENE_LAYER, 0, 0);
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_SCENE_WIPE_IN);
    CarriedLetters_SetFlags(self, CARRIED_LETTERS_FLAG_DRAWN);
    CarriedLetters_SetFlags(self, CARRIED_LETTERS_FLAG_OBJECTS_DRAWN);
    self->objects_y = MenuScene_WipeOffsetY(carried_scene(self));
}
CLEAN_AS(func_ov103_0229dc9c, CarriedLetters_StartWipeIn)

/* func_ov103_0229dd10 (state 0): the scene layer set up and the wallet's display prepared, then
 * state 1. */
void CarriedLetters_StartSetup(CarriedLetters *self)
{
    CarriedLetters_SetUpLayer();
    CarriedLetters_PrepareWallet(self);
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov103_0229dd10, CarriedLetters_StartSetup)

/* func_ov103_0229dd2c (vtable slot 0x5c, phase 5): the scene asks to be deleted. Answers 1. */
int CarriedLetters_End(CarriedLetters *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov103_0229dd2c, CarriedLetters_End)

/* func_ov103_0229dd3c (vtable slot 0x58, phase 4): nothing. */
int CarriedLetters_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov103_0229dd3c, CarriedLetters_Phase4Idle)

/* func_ov103_0229dd40 (vtable slot 0x54, phase 3): nothing. */
int CarriedLetters_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov103_0229dd40, CarriedLetters_Phase3Idle)

/* Obj_ov103_0229e2e0::func_ov103_0229dd44 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: the frame's start, its sub state and its end. Answers 1. */
int CarriedLetters_RunInteractive(CarriedLetters *self)
{
    CarriedLetters_BeginInteractiveFrame(self);
    CarriedLetters_RunSubState(self);
    CarriedLetters_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov103_0229e2e019func_ov103_0229dd44Ev, CarriedLetters_RunInteractive)

/* Obj_ov103_0229e2e0::func_ov103_0229dd60: the sub state's function (CarriedLettersSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x19; the game reads past the table for others. */
void CarriedLetters_RunSubState(CarriedLetters *self)
{
    static const MemberPointer *const sub_states[CARRIED_LETTERS_SUB_STATES] = {
        &data_ov103_0229e280, &data_ov103_0229e278, &data_ov103_0229e270, &data_ov103_0229e268, &data_ov103_0229e260,
        &data_ov103_0229e258, &data_ov103_0229e250, &data_ov103_0229e248, &data_ov103_0229e240, &data_ov103_0229e238,
        &data_ov103_0229e230, &data_ov103_0229e1e8, &data_ov103_0229e228, &data_ov103_0229e290, &data_ov103_0229e210,
        &data_ov103_0229e208, &data_ov103_0229e200, &data_ov103_0229e1f8, &data_ov103_0229e1f0, &data_ov103_0229e1e0,
        &data_ov103_0229e288, &data_ov103_0229e218, &data_ov103_0229e1d0, &data_ov103_0229e1c8, &data_ov103_0229e2a0,
    };
    MemberTable_InitOnce(&data_ov103_0229e344, data_ov103_0229e390, sub_states, CARRIED_LETTERS_SUB_STATES);
    MemberPointer_CallVoid(&data_ov103_0229e390[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov103_0229e2e019func_ov103_0229dd60Ev, CarriedLetters_RunSubState)

/* func_ov103_0229df14 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (CarriedLettersState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 9; the game reads past the table for others. */
int CarriedLetters_RunState(CarriedLetters *self)
{
    static const MemberPointer *const states[CARRIED_LETTERS_STATES] = {
        &data_ov103_0229e1c0, &data_ov103_0229e2d0, &data_ov103_0229e2c8, &data_ov103_0229e2c0, &data_ov103_0229e2b8,
        &data_ov103_0229e2b0, &data_ov103_0229e2a8, &data_ov103_0229e220, &data_ov103_0229e298,
    };
    MemberTable_InitOnce(&data_ov103_0229e340, data_ov103_0229e348, states, CARRIED_LETTERS_STATES);
    CarriedLetters_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov103_0229e348[self->base.state], self);
    CarriedLetters_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov103_0229df14, CarriedLetters_RunState)

/* func_ov103_0229dfec (vtable slot 0x24): the scene's draw: the choice always; while the scene is
 * drawn, the popup (through its class, slot 2), the cursor sprite (with the keys in use) and the
 * held letter; with the objects drawn, the grid, the letters and the wallet at the objects' y;
 * with a letter shown, the label button at the wipe's y (through its class, slot 2). Answers 1. */
int CarriedLetters_Draw(CarriedLetters *self)
{
    PagedChoice_Draw(carried_choice(self));
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_DRAWN) == 0) {
        return 1;
    }
    carried_draw_member(&self->popup);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    CarriedLetters_DrawHeld(self);
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_OBJECTS_DRAWN) != 0) {
        PocketsGrid_DrawPockets(&self->grid, 0, self->objects_y);
        PocketsLetters_DrawPockets(&self->letters, 0, self->objects_y);
        PocketsWallet_Draw(&self->wallet, self->objects_y);
    }
    if (CarriedLetters_TestFlags(self, CARRIED_LETTERS_FLAG_LETTER_SHOWN) != 0) {
        int y = MenuScene_WipeOffsetY(carried_scene(self));
        /* The button's base is main's labelled sprite (label_button.h). */
        LabelSprite_SetOffset((LabelSprite *) (void *) &self->button, 0, y);
        carried_draw_member(&self->button);
    }
    return 1;
}
CLEAN_AS(func_ov103_0229dfec, CarriedLetters_Draw)

/* func_ov103_0229e0a8 (vtable slot 0x0c): the scene closes: the parent told and the members torn
 * down. Answers 1. */
int CarriedLetters_Close(CarriedLetters *self)
{
    MenuDispatch_ChildClosed(carried_parent(self));
    CarriedLetters_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov103_0229e0a8, CarriedLetters_Close)

/* func_ov103_0229e0c4 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int CarriedLetters_Start(CarriedLetters *self)
{
    CarriedLetters_Setup(self);
    MenuScene_SetState(carried_scene(self), CARRIED_LETTERS_STATE_START_SETUP);
    MenuScene_SetPhase(carried_scene(self), CARRIED_LETTERS_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov103_0229e0c4, CarriedLetters_Start)

/* func_ov103_0229e0e4 (named by the profile at 0x0229e1d8): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order. */
CarriedLetters *CarriedLetters_New(void)
{
    CarriedLetters *self = MenuScene_Alloc(sizeof(CarriedLetters));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov103_0229e2e0;
    LayerTask_ConstructPair(&self->tasks);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(carried_choice(self));
    ErrorMessage_Construct(&self->error);
    LetterView_Construct(&self->view);
    LabelButton0_Construct(&self->button);
    Letter_Construct(&self->held);
    Letter_Construct(&self->swapped);
    return self;
}
CLEAN_AS(func_ov103_0229e0e4, CarriedLetters_New)
