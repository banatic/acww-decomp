/* The letter pick scene of overlay 108 (letter_pick.h): its destructors, its flags, the cursor's
 * moves, the choice it opens, the held letter and its places. */
#include "letter_pick.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(LetterPick, flags) == 0x94, "flags");
static_assert(offsetof(LetterPick, grab_dx) == 0x9c && offsetof(LetterPick, held_x) == 0xa4, "places");
static_assert(sizeof(Letter) == 0x100 && offsetof(LetterPick, held) == 0xac, "held");
static_assert(offsetof(LetterPick, swapped) == 0x1ac && offsetof(LetterPick, held_kind) == 0x2ac, "swapped");
static_assert(offsetof(LetterPick, cursor) == 0x2b0 && offsetof(LetterPick, open_delay) == 0x2b6, "bytes");
static_assert(sizeof(LayerTaskPair) == 0x38 && offsetof(LetterPick, task) == 0x2b8, "task");
static_assert(offsetof(LetterPick, grid) == 0x2f0 && offsetof(LetterPick, letters) == 0xd50, "ov094 objects");
static_assert(offsetof(LetterPick, wallet) == 0xd78 && offsetof(LetterPick, popup) == 0x23b0, "wallet");
static_assert(offsetof(LetterPick, glide) == 0x2480 && offsetof(LetterPick, cursor_sprite) == 0x2498, "glide");
static_assert(offsetof(LetterPick, choice) == 0x24fc && offsetof(LetterPick, entries) == 0x28e4, "choice");
static_assert(offsetof(LetterPick, error) == 0x28f0 && offsetof(LetterPick, panel) == 0x2a0c, "error");
static_assert(sizeof(LetterPick) == 0x2bd8, "size (func_ov108_0229dec4)");

/* The touch (main's bytes, as ov099's pockets_view.c reads them). */
extern u8 data_021f6c58, data_021f6c54;

/* The scene's vtable. */
extern const u8 data_ov108_0229e098[];

/* What the dispatcher (overlay 92's) is told: the screen ends (MenuDispatch_SetMode). */
#define LETTER_PICK_PARENT_CODE_END 0x44

/* The choice's texts: the pick and the cancel. */
#define LETTER_PICK_TEXT_PICK 0x0d
#define LETTER_PICK_TEXT_CANCEL 0x02

/* The letter states dimmed by the setup (ov094's POCKETS_LETTERS_DIM_WRITTEN | ..._RECEIVED). */
#define LETTER_PICK_DIMMED_STATES 3

/* The panel's button below the letters. */
#define LETTER_PICK_PANEL_BUTTON_9 9

static PagedChoice *lp_choice(LetterPick *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static MenuScene *lp_scene(LetterPick *self)
{
    return &self->base;
}

static int lp_is_carried(LetterPick *self, int place)
{
    return LetterPick_IsCarriedPlace(self, (unsigned int) place) != 0;
}

static int lp_letter_index(LetterPick *self, int place)
{
    return LetterPick_LetterIndex(self, (unsigned int) place);
}

static CellLayerSprite *lp_cursor_cells(LetterPick *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static int lp_update_cursor_sprite(Glider *sprite)
{
    int (*const *vtable)(Glider *) = (int (*const *)(Glider *)) sprite->vtable;
    return vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void lp_destroy_members(LetterPick *self)
{
    self->base.vtable = data_ov108_0229e098;
    ButtonPanel_Destroy(&self->panel);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(lp_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    Letter_Destruct(&self->swapped);
    Letter_Destruct(&self->held);
    MenuScene_DestroyBase(lp_scene(self));
}

/* func_ov108_0229c180 (vtable slot 0x40) */
LetterPick *LetterPick_Destroy(LetterPick *self)
{
    lp_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov108_0229c180, LetterPick_Destroy)

/* func_ov108_0229c21c (vtable slot 0x44) */
LetterPick *LetterPick_Delete(LetterPick *self)
{
    lp_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov108_0229c21c, LetterPick_Delete)

/* func_ov108_0229c2bc */
void LetterPick_ClearFlags(LetterPick *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov108_0229c2bc, LetterPick_ClearFlags)

/* func_ov108_0229c2cc */
void LetterPick_SetFlags(LetterPick *self, int flags)
{
    self->flags |= (u32) flags;
}
CLEAN_AS(func_ov108_0229c2cc, LetterPick_SetFlags)

/* func_ov108_0229c2dc: 1 when any of `flags` is set. */
int LetterPick_TestFlags(LetterPick *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov108_0229c2dc, LetterPick_TestFlags)

/* func_ov108_0229c2f0: the cursor moved by `keys` (KeyRepeat_Has*): among the carried letters
 * (LetterPick_MoveCursorInCarried), or up from LETTER_PICK_BELOW to the bottom left letter (0x13).
 * The wrap flags are cleared first. 1 when the cursor changed place; 0 at once when `keys` is 0. */
int LetterPick_MoveCursor(LetterPick *self, int keys, int mode)
{
    u8 before = self->cursor;

    LetterPick_ClearFlags(self, LETTER_PICK_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (LetterPick_IsCarriedPlace(self, self->cursor) != 0) {
        LetterPick_MoveCursorInCarried(self, keys, mode);
    } else if (self->cursor == LETTER_PICK_BELOW && KeyRepeat_HasUp(keys) != 0) {
        self->cursor = 0x13;
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov108_0229c2f0, LetterPick_MoveCursor)

/* func_ov108_0229c358: the cursor on the carried letters (5 rows of 2): left and right stay in
 * the row; then, while it is still on a letter and no wrap flag is set, up stops at the top row
 * and down from the bottom row goes to LETTER_PICK_BELOW.
 * QUIRK: `mode` (1 with a letter held) is not read, so a held letter may be taken below too. */
void LetterPick_MoveCursorInCarried(LetterPick *self, int keys, int mode)
{
    (void) mode;
    int index = (int) self->cursor - LETTER_PICK_CARRIED_FIRST;
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

    if (LetterPick_IsCarriedPlace(self, self->cursor) == 0 || LetterPick_TestFlags(self, LETTER_PICK_FLAGS_WRAPPED) != 0) {
        return;
    }
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= LETTER_PICK_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        if (row < LETTER_PICK_ROWS - 1) {
            self->cursor += LETTER_PICK_COLUMNS;
        } else {
            self->cursor = LETTER_PICK_BELOW;
        }
    }
}
CLEAN_AS(func_ov108_0229c358, LetterPick_MoveCursorInCarried)

/* func_ov108_0229c404: the choice of the letter at `place`: text 0xd picks it, text 2 cancels
 * (the default). The cursor sprite is hidden, the popup too unless the choice goes above it.
 * QUIRK: the place's letter is looked up and not used. */
void LetterPick_OpenLetterMenu(LetterPick *self, int place, int above_popup)
{
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, LETTER_PICK_ACTION_CANCEL);
    (void) LetterPick_PlaceLetter(self, place);
    ChoiceEntries_Add(&self->entries, LETTER_PICK_TEXT_PICK, LETTER_PICK_ACTION_PICK);
    ChoiceEntries_Add(&self->entries, LETTER_PICK_TEXT_CANCEL, LETTER_PICK_ACTION_CANCEL);
    LetterPick_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    LetterPick_ShowChoice(self, above_popup);
}
CLEAN_AS(func_ov108_0229c404, LetterPick_OpenLetterMenu)

/* func_ov108_0229c468: the cancel action, the cursor sprite put back at the cursor, the choice
 * asked to close, sub state 0x15. */
void LetterPick_CancelChoice(LetterPick *self)
{
    self->action = LETTER_PICK_ACTION_CANCEL;
    LetterPick_PlaceCursorSprite(self);
    PagedChoice_RequestClose(lp_choice(self), 0);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov108_0229c468, LetterPick_CancelChoice)

/* func_ov108_0229c498: the entries shown in the choice, placed above the popup or beside the
 * open place (whose place is asked for either way), asked to open; sub state 0x13. */
void LetterPick_ShowChoice(LetterPick *self, int above_popup)
{
    PagedChoice_ShowEntries(lp_choice(self), &self->entries, 0);
    int x = LetterPick_PlaceX(self, self->slot);
    int y = LetterPick_PlaceY(self, self->slot);
    if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(lp_choice(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(lp_choice(self), x, y);
    }
    PagedChoice_RequestOpen(lp_choice(self), 0);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_OPEN);
}
CLEAN_AS(func_ov108_0229c498, LetterPick_ShowChoice)

/* func_ov108_0229c508: the action picked (`action`); any value but 0 cancels. */
void LetterPick_RunAction(LetterPick *self)
{
    if (self->action == LETTER_PICK_ACTION_PICK) {
        LetterPick_PickSlotLetter(self);
    } else {
        LetterPick_EndAction(self);
    }
}
CLEAN_AS(func_ov108_0229c508, LetterPick_RunAction)

/* func_ov108_0229c52c: the popup hidden, the sub state to go back to kept, `target` kept, the
 * cursor sprite's animation 6, sub state 0x10. */
void LetterPick_BeginSwap(LetterPick *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 6);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_SWAP);
}
CLEAN_AS(func_ov108_0229c52c, LetterPick_BeginSwap)

/* func_ov108_0229c578: the popup hidden, `target` kept, the cursor sprite's animation 5, sub
 * state 0x0f. */
void LetterPick_BeginPutDown(LetterPick *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 5);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov108_0229c578, LetterPick_BeginPutDown)

/* func_ov108_0229c5b4: the cursor sprite's set's second animation, sub state 0x0b. */
void LetterPick_BeginBelowPress(LetterPick *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_BELOW_PRESS);
}
CLEAN_AS(func_ov108_0229c5b4, LetterPick_BeginBelowPress)

/* func_ov108_0229c5d4: the first animation of the cursor sprite's set, then its update. */
void LetterPick_ShowCursorFirstOfSet(LetterPick *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    lp_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov108_0229c5d4, LetterPick_ShowCursorFirstOfSet)

/* func_ov108_0229c5f4: the cursor sprite put at the cursor, animation 1. */
void LetterPick_PlaceCursorSprite(LetterPick *self)
{
    int x = LetterPick_CursorSpriteX(self);
    int y = LetterPick_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
}
CLEAN_AS(func_ov108_0229c5f4, LetterPick_PlaceCursorSprite)

/* func_ov108_0229c628: the cursor sprite put at the choice's row 0, animation 7. */
void LetterPick_PointAtDefaultRow(LetterPick *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(lp_choice(self));
    int y = PagedChoice_RowY(lp_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 7);
}
CLEAN_AS(func_ov108_0229c628, LetterPick_PointAtDefaultRow)

/* func_ov108_0229c674: the cancel action, the choice's last row picked and the cursor sprite
 * put at it, showing animation 8 from its last frame; sub state 0x14. */
void LetterPick_PointAtLastRow(LetterPick *self)
{
    self->action = LETTER_PICK_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(lp_choice(self), 1);
    int x = PagedChoice_TextX(lp_choice(self));
    int y = PagedChoice_RowY(lp_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd(lp_cursor_cells(self), 8);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov108_0229c674, LetterPick_PointAtLastRow)

/* func_ov108_0229c6d8: the cursor sprite moved to the choice row in 2 steps; the sub state to
 * go back to kept, sub state 0x0a. */
void LetterPick_GlideToRow(LetterPick *self)
{
    int x = PagedChoice_TextX(lp_choice(self));
    int y = PagedChoice_RowY(lp_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov108_0229c6d8, LetterPick_GlideToRow)

/* func_ov108_0229c72c: the cursor sprite turned to set B on LETTER_PICK_BELOW and to set A
 * elsewhere, then eased to the cursor in 3 steps; the sub state to go back to kept, sub state
 * 0x0a. */
void LetterPick_GlideToCursor(LetterPick *self)
{
    if (self->cursor == LETTER_PICK_BELOW) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = LetterPick_CursorSpriteX(self);
    int y = LetterPick_CursorSpriteY(self);
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov108_0229c72c, LetterPick_GlideToCursor)

/* func_ov108_0229c794: the cursor sprite's animation 0, then its update. */
void LetterPick_HideCursorSprite(LetterPick *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    lp_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov108_0229c794, LetterPick_HideCursorSprite)

/* func_ov108_0229c7b8: the cursor sprite's y, the cursor's place's. */
int LetterPick_CursorSpriteY(LetterPick *self)
{
    return LetterPick_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov108_0229c7b8, LetterPick_CursorSpriteY)

/* func_ov108_0229c7c8: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right or left with a wrap flag (which nothing of the overlay sets). */
int LetterPick_CursorSpriteX(LetterPick *self)
{
    int x = LetterPick_PlaceX(self, self->cursor);
    if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov108_0229c7c8, LetterPick_CursorSpriteX)

/* func_ov108_0229c810: the cursor sprite put at the cursor, animation 7 on LETTER_PICK_BELOW and
 * 1 elsewhere, then its set's first animation shown. */
void LetterPick_ShowCursorAtCursor(LetterPick *self)
{
    int x = LetterPick_CursorSpriteX(self);
    int y = LetterPick_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == LETTER_PICK_BELOW) {
        Glider_SetAnim(&self->cursor_sprite, 7);
    } else {
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    LetterPick_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov108_0229c810, LetterPick_ShowCursorAtCursor)

/* func_ov108_0229c864: when a letter is held, it changes places with the letter at `place`: the
 * held one is copied aside, the place's letter picked up and the copy put at `place`. */
void LetterPick_SwapHeldWith(LetterPick *self, int place)
{
    if (self->held_kind == LETTER_PICK_HELD_LETTER) {
        Letter_Assign(&self->swapped, &self->held);
        LetterPick_PickUpLetter(self, place);
        LetterPick_PutLetterAt(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov108_0229c864, LetterPick_SwapHeldWith)

/* func_ov108_0229c8a4: the held letter, if any, put at `place`; nothing held after. */
void LetterPick_PutHeldAt(LetterPick *self, int place)
{
    if (self->held_kind == LETTER_PICK_HELD_LETTER) {
        LetterPick_PutLetterAt(self, place, &self->held);
    }
    self->held_kind = LETTER_PICK_HELD_NONE;
}
CLEAN_AS(func_ov108_0229c8a4, LetterPick_PutHeldAt)

/* func_ov108_0229c8c8: the letter at a carried place copied into `held` and taken from the
 * letters object; other places are left alone. */
void LetterPick_PickUpLetter(LetterPick *self, int place)
{
    if (!lp_is_carried(self, place)) {
        return;
    }
    int index = lp_letter_index(self, place);
    self->held_kind = LETTER_PICK_HELD_LETTER;
    Letter_Assign(&self->held, PocketsLetters_LetterAt(&self->letters, index));
    PocketsLetters_ClearPlace(&self->letters, index);
}
CLEAN_AS(func_ov108_0229c8c8, LetterPick_PickUpLetter)

/* func_ov108_0229c918: the held letter drawn where the glide is; answers the glide's y. */
int LetterPick_FollowGlide(LetterPick *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
    return self->held_y;
}
CLEAN_AS(func_ov108_0229c918, LetterPick_FollowGlide)

/* func_ov108_0229c940: the held letter drawn at the cursor sprite's frame, 2 left and 4 up. */
void LetterPick_FollowCursorSprite(LetterPick *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov108_0229c940, LetterPick_FollowCursorSprite)

/* func_ov108_0229c96c: the held letter drawn at the touch plus the grab's offset. */
void LetterPick_FollowTouch(LetterPick *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov108_0229c96c, LetterPick_FollowTouch)

/* func_ov108_0229c998: the held letter drawn by the letters object, unless hidden. */
void LetterPick_DrawHeld(LetterPick *self)
{
    if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_HELD_HIDDEN) != 0) {
        return;
    }
    if (self->held_kind == LETTER_PICK_HELD_LETTER) {
        PocketsLetters_DrawHeld(&self->letters, self->held_x, self->held_y, &self->held);
    }
}
CLEAN_AS(func_ov108_0229c998, LetterPick_DrawHeld)

/* func_ov108_0229c9d8: the popup queued to tell of the cursor's letter, when its place holds
 * one; cleared on an empty place and below. */
void LetterPick_UpdatePopup(LetterPick *self)
{
    if (lp_is_carried(self, self->cursor)) {
        if (LetterPick_PlaceIsEmpty(self, self->cursor) != 0) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov108_0229c9d8, LetterPick_UpdatePopup)

/* func_ov108_0229ca2c: the popup's window put 0x6d left and 0x78 up of its place (8 more up
 * when state flag 2 is set), and filled by the letters object for a carried place. */
void LetterPick_PlacePopup(LetterPick *self)
{
    int x = LetterPick_PlaceX(self, self->popup_place) - 0x6d;
    int y = LetterPick_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (lp_is_carried(self, self->popup_place)) {
        int index = lp_letter_index(self, self->popup_place);
        PocketsLetters_ShowPlaceText(&self->letters, &self->popup, index);
    }
}
CLEAN_AS(func_ov108_0229ca2c, LetterPick_PlacePopup)

/* func_ov108_0229ca98: a carried place highlighted by the letters object. */
void LetterPick_HighlightPlace(LetterPick *self, int place)
{
    if (!lp_is_carried(self, place)) {
        return;
    }
    PocketsLetters_MarkPlace(&self->letters, lp_letter_index(self, place));
}
CLEAN_AS(func_ov108_0229ca98, LetterPick_HighlightPlace)

/* func_ov108_0229cac8: the highlights of the grid and the letters cleared. */
void LetterPick_ClearHighlights(LetterPick *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov108_0229cac8, LetterPick_ClearHighlights)

/* func_ov108_0229caec: a carried place lifted in the letters object (the grid's lift dropped);
 * any other place drops both (LetterPick_ClearSelection). */
void LetterPick_SelectPlace(LetterPick *self, int place)
{
    if (lp_is_carried(self, place)) {
        int index = lp_letter_index(self, place);
        PocketsLetters_Lift(&self->letters, index);
        PocketsGrid_Unlift(&self->grid);
    } else {
        LetterPick_ClearSelection(self);
    }
}
CLEAN_AS(func_ov108_0229caec, LetterPick_SelectPlace)

/* func_ov108_0229cb30: the lifts of the grid and the letters dropped. */
void LetterPick_ClearSelection(LetterPick *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov108_0229cb30, LetterPick_ClearSelection)

/* func_ov108_0229cb54: whether a carried place holds no letter (by the letters object); other
 * places count as empty. */
int LetterPick_PlaceIsEmpty(LetterPick *self, int place)
{
    if (lp_is_carried(self, place)) {
        return PocketsLetters_IsEmpty(&self->letters, lp_letter_index(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov108_0229cb54, LetterPick_PlaceIsEmpty)

/* func_ov108_0229cb88: whether a carried letter is dimmed by the letters object
 * (LetterPick_DimLetters); 0 for any other place. */
int LetterPick_PlaceIsDimmed(LetterPick *self, int place)
{
    if (lp_is_carried(self, place)) {
        return PocketsLetters_IsDimmed(&self->letters, lp_letter_index(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov108_0229cb88, LetterPick_PlaceIsDimmed)

/* func_ov108_0229cbbc: the grid's places 0 to 14 dimmed, and the carried letters written or
 * received (PocketsLetters_DimByState): only those between villagers stay bright. */
void LetterPick_DimLetters(LetterPick *self)
{
    PocketsGrid_DimPlaces(&self->grid, 0, 0xe);
    PocketsLetters_DimByState(&self->letters, LETTER_PICK_DIMMED_STATES);
}
CLEAN_AS(func_ov108_0229cbbc, LetterPick_DimLetters)

/* func_ov108_0229cbe4: the y of `place`: a letter's by the letters object less 0x10, 0xb6 for
 * LETTER_PICK_BELOW, else 0. */
int LetterPick_PlaceY(LetterPick *self, int place)
{
    if (lp_is_carried(self, place)) {
        return PocketsLetters_PlaceY(&self->letters, lp_letter_index(self, place)) - 0x10;
    }
    if (place == LETTER_PICK_BELOW) {
        return 0xb6;
    }
    return 0;
}
CLEAN_AS(func_ov108_0229cbe4, LetterPick_PlaceY)

/* func_ov108_0229cc20: the x of `place`: a letter's by the letters object, 0xbc for
 * LETTER_PICK_BELOW, else 0. */
int LetterPick_PlaceX(LetterPick *self, int place)
{
    if (lp_is_carried(self, place)) {
        return PocketsLetters_PlaceX(&self->letters, lp_letter_index(self, place));
    }
    if (place == LETTER_PICK_BELOW) {
        return 0xbc;
    }
    return 0;
}
CLEAN_AS(func_ov108_0229cc20, LetterPick_PlaceX)

/* func_ov108_0229cc5c: the letter of a carried place (the letters object's), else NULL. */
Letter *LetterPick_PlaceLetter(LetterPick *self, int place)
{
    if (lp_is_carried(self, place)) {
        return PocketsLetters_LetterAt(&self->letters, lp_letter_index(self, place));
    }
    return NULL;
}
CLEAN_AS(func_ov108_0229cc5c, LetterPick_PlaceLetter)

/* func_ov108_0229cc90: a copy of `letter` put at a carried place by the letters object; other
 * places are left alone. */
void LetterPick_PutLetterAt(LetterPick *self, int place, Letter *letter)
{
    if (lp_is_carried(self, place)) {
        PocketsLetters_SetPlace(&self->letters, lp_letter_index(self, place), letter);
    }
}
CLEAN_AS(func_ov108_0229cc90, LetterPick_PutLetterAt)

/* func_ov108_0229ccc0: the held letter put down at `place`; a letter there is copied aside
 * (`swapped`) and put at the held letter's place (`held_from`) first. Always 1. */
int LetterPick_PutHeldLetterAt(LetterPick *self, int place)
{
    if (LetterPick_PlaceIsEmpty(self, place) == 0) {
        Letter_Assign(&self->swapped, LetterPick_PlaceLetter(self, place));
        LetterPick_PutLetterAt(self, self->held_from, &self->swapped);
    }
    LetterPick_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov108_0229ccc0, LetterPick_PutHeldLetterAt)

/* func_ov108_0229cd0c: the carried place under the touch at (x, y), by the letters object; with
 * `with_letter`, only one holding a letter. LETTER_PICK_NO_PLACE for none. */
int LetterPick_LetterPlaceAtTouch(LetterPick *self, int x, int y, int with_letter)
{
    int index = PocketsLetters_PocketAtTouch(&self->letters, x, y);
    if (index == POCKETS_LETTERS_NO_PLACE) {
        return LETTER_PICK_NO_PLACE;
    }
    if (with_letter != 0 && PocketsLetters_IsEmpty(&self->letters, index) != 0) {
        return LETTER_PICK_NO_PLACE;
    }
    return LetterPick_LetterPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov108_0229cd0c, LetterPick_LetterPlaceAtTouch)

/* func_ov108_0229cd4c: the place of the letters object's letter `index` (0-9), else
 * LETTER_PICK_NO_PLACE. */
int LetterPick_LetterPlace(LetterPick *self, unsigned int index)
{
    (void) self;
    if (index <= 9) {
        return (u8) (index + LETTER_PICK_CARRIED_FIRST);
    }
    return LETTER_PICK_NO_PLACE;
}
CLEAN_AS(func_ov108_0229cd4c, LetterPick_LetterPlace)

/* func_ov108_0229cd5c: the letters object's index of a carried place, else 0. */
int LetterPick_LetterIndex(LetterPick *self, unsigned int place)
{
    (void) self;
    if (place >= LETTER_PICK_CARRIED_FIRST && place <= LETTER_PICK_CARRIED_LAST) {
        return (u8) (place - LETTER_PICK_CARRIED_FIRST);
    }
    return 0;
}
CLEAN_AS(func_ov108_0229cd5c, LetterPick_LetterIndex)

/* func_ov108_0229cd70 */
int LetterPick_IsCarriedPlace(LetterPick *self, unsigned int place)
{
    (void) self;
    return place >= LETTER_PICK_CARRIED_FIRST && place <= LETTER_PICK_CARRIED_LAST;
}
CLEAN_AS(func_ov108_0229cd70, LetterPick_IsCarriedPlace)

/* func_ov108_0229cd80: the layer load task taken off the main loop's queue and reset. */
void LetterPick_EndLayerTask(LetterPick *self)
{
    LayerTask_End(&self->task.first);
}
CLEAN_AS(func_ov108_0229cd80, LetterPick_EndLayerTask)

/* func_ov108_0229cd90: the panel's button 9 selected, sub state 0x17, sound 0x28. */
void LetterPick_PressPanelButton9(LetterPick *self)
{
    ButtonPanel_Select(&self->panel, LETTER_PICK_PANEL_BUTTON_9);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_PANEL_PRESSED);
    SoundSys_PlaySe(0x28);
}
CLEAN_AS(func_ov108_0229cd90, LetterPick_PressPanelButton9)

/* func_ov108_0229cdb8 (action 0): the letter of the place whose choice is open is the one
 * picked: its index (0-9) handed to main (GroupParams_SetArg) with GroupParams_SetC4C(1); state 3
 * (written directly) in phase 1, the popup and the cursor sprite hidden. */
void LetterPick_PickSlotLetter(LetterPick *self)
{
    GroupParams_SetArg((u8) (self->slot - LETTER_PICK_CARRIED_FIRST));
    GroupParams_SetC4C(1);
    self->base.state = LETTER_PICK_STATE_START_WIPE_OUT;
    MenuScene_SetPhase(lp_scene(self), LETTER_PICK_PHASE_STATES);
    Popup_Hide(&self->popup, 1);
    LetterPick_HideCursorSprite(self);
}
CLEAN_AS(func_ov108_0229cdb8, LetterPick_PickSlotLetter)

/* func_ov108_0229ce00: the held letter glides from where it is drawn to `place` (kept as its
 * place, `held_from`) in `steps` steps, the first taken now. Sub state 0x12 follows it. */
void LetterPick_GlideHeldTo(LetterPick *self, int place, int steps)
{
    self->held_from = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = LetterPick_PlaceX(self, place);
    int y = LetterPick_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    LetterPick_FollowGlide(self);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov108_0229ce00, LetterPick_GlideHeldTo)

/* func_ov108_0229ce68: the letter at `place` picked up with the cursor, the popup hidden; when it
 * is held, the sub state to go back to is 7. It follows the cursor sprite. */
void LetterPick_PickUpWithCursor(LetterPick *self, int place)
{
    self->held_from = (u8) place;
    Popup_Hide(&self->popup, 1);
    LetterPick_PickUpLetter(self, place);
    if (self->held_kind == LETTER_PICK_HELD_LETTER) {
        self->return_state = LETTER_PICK_SUB_HOLD;
    }
    LetterPick_FollowCursorSprite(self);
}
CLEAN_AS(func_ov108_0229ce68, LetterPick_PickUpWithCursor)

/* func_ov108_0229ceb4: `place` touched: sub state 1, the offset from the touch to the place
 * kept, the popup told of the place and shown, its choice opening in 2 frames; the letter may be
 * picked (LETTER_PICK_FLAG_SELECTABLE) unless it is dimmed. */
void LetterPick_TouchPlace(LetterPick *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = LetterPick_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = LetterPick_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = 2;
    if (LetterPick_PlaceIsDimmed(self, place)) {
        LetterPick_ClearFlags(self, LETTER_PICK_FLAG_SELECTABLE);
    } else {
        LetterPick_SetFlags(self, LETTER_PICK_FLAG_SELECTABLE);
    }
}
CLEAN_AS(func_ov108_0229ceb4, LetterPick_TouchPlace)

/* func_ov108_0229cf4c: the action ends: back to sub state 0 with the cursor sprite hidden while
 * state flag 2 is clear, else to sub state 6 with it at the cursor. */
void LetterPick_EndAction(LetterPick *self)
{
    if (StateFlags_IsClear2()) {
        LetterPick_EndActionHidden(self);
    } else {
        LetterPick_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov108_0229cf4c, LetterPick_EndAction)

/* func_ov108_0229cf6c: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 6 and the cursor's place selected. */
void LetterPick_EndActionAtCursor(LetterPick *self)
{
    self->popup_place = LETTER_PICK_NO_PLACE;
    LetterPick_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(lp_scene(self));
    LetterPick_UpdatePopup(self);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_BROWSE);
    LetterPick_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov108_0229cf6c, LetterPick_EndActionAtCursor)

/* func_ov108_0229cfa8 */
void LetterPick_EndActionHidden(LetterPick *self)
{
    LetterPick_HideCursorSprite(self);
    LetterPick_ClearSelection(self);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov108_0229cfa8, LetterPick_EndActionHidden)

/* The pen (autoload_2/input.c): down, and gone down or up this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define LETTER_PICK_PAD_A 0x0001
#define LETTER_PICK_PAD_B 0x0002

/* The selected panel button, for ButtonPanel_ButtonX and ButtonPanel_ButtonY. */
#define LETTER_PICK_PANEL_SELECTED (-1)

/* The pen went down this frame. */
static int lp_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x28e9 + row. */
static u8 lp_entry_value(LetterPick *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(LetterPick, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* A choice row picked with the sound of a pick, its action kept; sub state 0x14. */
static void lp_pick_choice_row(LetterPick *self, int row)
{
    PagedChoice_PickRowWithSound(lp_choice(self), row, 1);
    self->action = lp_entry_value(self, row);
    MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_CLOSE);
}

/* func_ov108_0229cfc4 (sub state 0x17, after the panel's button 9): while the selected panel
 * button's press plays, the cursor sprite (when shown) follows it, offset by the press's frame;
 * after, no letter was picked (GroupParams_SetC4C(0)): state 3 (written directly) in phase 1,
 * the popup and the cursor sprite hidden. */
void LetterPick_FollowPanelPress(LetterPick *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(lp_cursor_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, LETTER_PICK_PANEL_SELECTED);
            int y = ButtonPanel_ButtonY(&self->panel, LETTER_PICK_PANEL_SELECTED);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        GroupParams_SetC4C(0);
        self->base.state = LETTER_PICK_STATE_START_WIPE_OUT;
        MenuScene_SetPhase(lp_scene(self), LETTER_PICK_PHASE_STATES);
        Popup_Hide(&self->popup, 1);
        LetterPick_HideCursorSprite(self);
    }
}
CLEAN_AS(func_ov108_0229cfc4, LetterPick_FollowPanelPress)

/* func_ov108_0229d04c (sub state 0x16, which nothing of the overlay enters): once the error
 * message is done, back to the sub state kept, the cursor sprite's window flag set. */
void LetterPick_WaitError(LetterPick *self)
{
    if (ErrorMessage_Update(&self->error, 0)) {
        MenuScene_SetSubState(lp_scene(self), self->return_state);
        CellLayerSprite_SetWindow(lp_cursor_cells(self));
    }
}
CLEAN_AS(func_ov108_0229d04c, LetterPick_WaitError)

/* func_ov108_0229d084 (sub state 0x15): the action picked runs once the choice is idle. */
void LetterPick_RunActionWhenIdle(LetterPick *self)
{
    if (PagedChoice_IsIdle(lp_choice(self)) != 0) {
        LetterPick_RunAction(self);
    }
}
CLEAN_AS(func_ov108_0229d084, LetterPick_RunActionWhenIdle)

/* func_ov108_0229d0a4 (sub state 0x14): once the delay after the pick has run out, the choice
 * asked to close, the popup hidden, the cursor sprite (when shown) put back at the cursor; sub
 * state 0x15. */
void LetterPick_CloseChoice(LetterPick *self)
{
    if (PagedChoice_CountDown(lp_choice(self)) != 0) {
        PagedChoice_RequestClose(lp_choice(self), 0);
        Popup_Hide(&self->popup, 1);
        if (CellLayerSprite_AnimNumber(lp_cursor_cells(self)) != 0) {
            LetterPick_PlaceCursorSprite(self);
        }
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov108_0229d0a4, LetterPick_CloseChoice)

/* func_ov108_0229d0f4 (sub state 0x13): once the choice is shown, it is run by the keys (the
 * cursor sprite at its first row, sub state 8) when state flag 2 is set, else by the touch (sub
 * state 5). */
void LetterPick_WaitChoiceShown(LetterPick *self)
{
    if (PagedChoice_IsShown(lp_choice(self)) == 0) {
        return;
    }
    if (StateFlags_Test2() != 0) {
        LetterPick_PointAtDefaultRow(self);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_BY_KEYS);
    } else {
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_BY_TOUCH);
    }
}
CLEAN_AS(func_ov108_0229d0f4, LetterPick_WaitChoiceShown)

/* func_ov108_0229d130 (sub state 0x12): the held letter follows its glide. When the glide is over
 * the letter is put at its place (`held_from`) and the action ends. */
void LetterPick_StepHeldGlide(LetterPick *self)
{
    if (Glide_Step(&self->glide) != 0) {
        LetterPick_PutHeldAt(self, self->held_from);
        LetterPick_EndAction(self);
    } else {
        LetterPick_FollowGlide(self);
    }
}
CLEAN_AS(func_ov108_0229d130, LetterPick_StepHeldGlide)

/* func_ov108_0229d168 (sub state 0x11): back to the sub state kept once the cursor sprite's
 * animation has ended; once its turn has settled, the held letter is shown again and follows the
 * sprite. */
void LetterPick_FinishSwap(LetterPick *self)
{
    if (CellLayerSprite_IsDone(lp_cursor_cells(self))) {
        MenuScene_SetSubState(lp_scene(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        LetterPick_ClearFlags(self, LETTER_PICK_FLAG_HELD_HIDDEN);
        LetterPick_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov108_0229d168, LetterPick_FinishSwap)

/* func_ov108_0229d1ac (sub state 0x10): unless the cursor sprite's turn is at its frame 2, the
 * held letter changes places with the one at `target`, the new held letter hidden for now, the
 * popup updated; sub state 0x11. At frame 2, sub state 6. */
void LetterPick_Swap(LetterPick *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        LetterPick_SwapHeldWith(self, self->target);
        LetterPick_SetFlags(self, LETTER_PICK_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_SWAP_END);
        LetterPick_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov108_0229d1ac, LetterPick_Swap)

/* func_ov108_0229d1f4 (sub state 0x0f): while the cursor sprite's turn has not settled, the held
 * letter is put down at `target` when the cursor is on it (the popup updated, sub state 6), else
 * glided there in 4 steps; once it has, the letter follows the sprite. */
void LetterPick_PutDown(LetterPick *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        u8 target = self->target;
        if (self->cursor == target) {
            LetterPick_PutHeldLetterAt(self, target);
            LetterPick_UpdatePopup(self);
            MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_BROWSE);
        } else {
            LetterPick_GlideHeldTo(self, target, 4);
        }
    } else {
        LetterPick_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov108_0229d1f4, LetterPick_PutDown)

/* func_ov108_0229d248 (sub state 0x0e): back to the sub state kept once the cursor sprite's
 * animation has ended; the held letter follows the sprite. */
void LetterPick_FinishPickUp(LetterPick *self)
{
    if (CellLayerSprite_IsDone(lp_cursor_cells(self))) {
        MenuScene_SetSubState(lp_scene(self), self->return_state);
    }
    LetterPick_FollowCursorSprite(self);
}
CLEAN_AS(func_ov108_0229d248, LetterPick_FinishPickUp)

/* func_ov108_0229d278 (sub state 0x0d, which nothing of the overlay enters): once the cursor
 * sprite's turn has settled, the letter at the cursor is picked up; sub state 0x0e. */
void LetterPick_PickUpAtCursor(LetterPick *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        LetterPick_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_PICK_UP_END);
    }
}
CLEAN_AS(func_ov108_0229d278, LetterPick_PickUpAtCursor)

/* func_ov108_0229d2a8 (sub state 0x0c, which nothing of the overlay enters): once the cursor
 * sprite's animation has ended, its set's first animation; sub state 6. */
void LetterPick_FinishPlacePress(LetterPick *self)
{
    if (CellLayerSprite_IsDone(lp_cursor_cells(self))) {
        LetterPick_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov108_0229d2a8, LetterPick_FinishPlacePress)

/* func_ov108_0229d2d0 (sub state 0x0b): once the cursor sprite's animation has ended, the
 * panel's button 9 selected (without the sound of LetterPick_PressPanelButton9); sub state
 * 0x17. */
void LetterPick_PressBelow(LetterPick *self)
{
    if (CellLayerSprite_IsDone(lp_cursor_cells(self)) != 0) {
        ButtonPanel_Select(&self->panel, LETTER_PICK_PANEL_BUTTON_9);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_PANEL_PRESSED);
    }
}
CLEAN_AS(func_ov108_0229d2d0, LetterPick_PressBelow)

/* func_ov108_0229d300 (sub state 0x0a): once the cursor sprite stops moving, back to the sub
 * state kept (the cursor's place selected for sub state 6), which runs at once; the held letter
 * follows the sprite. */
void LetterPick_WaitCursorSprite(LetterPick *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(lp_scene(self), self->return_state);
        if (self->return_state == LETTER_PICK_SUB_BROWSE) {
            LetterPick_SelectPlace(self, self->cursor);
        }
        LetterPick_RunSubState(self);
    }
    LetterPick_FollowCursorSprite(self);
}
CLEAN_AS(func_ov108_0229d300, LetterPick_WaitCursorSprite)

/* func_ov108_0229d34c (sub state 9): once the cursor sprite's animation has ended, the choice
 * row it points at is picked. */
void LetterPick_PickChoiceRow(LetterPick *self)
{
    if (CellLayerSprite_IsDone(lp_cursor_cells(self)) != 0) {
        lp_pick_choice_row(self, self->choice_row);
    }
}
CLEAN_AS(func_ov108_0229d34c, LetterPick_PickChoiceRow)

/* func_ov108_0229d39c (sub state 8): the choice by the keys. A touch cancels it; the keys move
 * the row, the cursor sprite gliding to it; A plays the sprite's second animation of its set and
 * picks the row (sub state 9), B points at the last row. */
void LetterPick_ChooseByKeys(LetterPick *self)
{
    if (MenuScene_TakeTouch(lp_scene(self))) {
        LetterPick_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(lp_scene(self));
    if (PagedChoice_MoveCursor(lp_choice(self), keys, &self->choice_row, 0)) {
        LetterPick_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_PICK_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_PICK);
    } else if (pressed & LETTER_PICK_PAD_B) {
        LetterPick_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov108_0229d39c, LetterPick_ChooseByKeys)

/* func_ov108_0229d418 (sub state 7, which only LetterPick_PickUpWithCursor names as the sub state
 * to go back to): a held letter moved with the cursor. A move of the cursor updates the popup and
 * moves the sprite (the popup hidden, its queue kept). A puts the letter down at the cursor (sub
 * state 0x0f) when its place is empty, else swaps (sub state 0x10); B sends the letter back to
 * its place (sub state 0x0f). Else the letter follows the sprite and a queued popup is shown.
 * QUIRK: LETTER_PICK_BELOW counts as empty, so A there puts the letter down where the letters
 * object keeps nothing. */
void LetterPick_MoveHeldByKeys(LetterPick *self)
{
    if (LetterPick_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(lp_scene(self)), 1) != 0) {
        LetterPick_UpdatePopup(self);
        LetterPick_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & LETTER_PICK_PAD_A) {
        if (LetterPick_PlaceIsEmpty(self, self->cursor) != 0) {
            LetterPick_BeginPutDown(self, self->cursor);
        } else {
            LetterPick_BeginSwap(self, self->cursor);
        }
    } else if (pressed & LETTER_PICK_PAD_B) {
        LetterPick_BeginPutDown(self, self->held_from);
    } else {
        LetterPick_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov108_0229d418, LetterPick_MoveHeldByKeys)

/* func_ov108_0229d4b4 (sub state 6): the cursor moved by the keys. A touch ends the action
 * without the sprite. A move updates the popup and moves the sprite (the popup hidden, its queue
 * kept). Unless the cursor's letter is dimmed, A on a letter opens its choice (nothing on an
 * empty place) and A below presses the place. Else B presses the panel's button 9, or a queued
 * popup is shown. */
void LetterPick_BrowseByKeys(LetterPick *self)
{
    if (MenuScene_TakeTouch(lp_scene(self)) != 0) {
        LetterPick_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (LetterPick_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(lp_scene(self)), 0) != 0) {
        LetterPick_UpdatePopup(self);
        LetterPick_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (LetterPick_PlaceIsDimmed(self, self->cursor) == 0 && (data_021fbe40.pressed & LETTER_PICK_PAD_A) != 0) {
        if (LetterPick_IsCarriedPlace(self, self->cursor) != 0) {
            if (LetterPick_PlaceIsEmpty(self, self->cursor) == 0) {
                LetterPick_OpenLetterMenu(self, self->cursor, 0);
            }
        } else {
            LetterPick_BeginBelowPress(self);
        }
        return;
    }
    if ((data_021fbe40.pressed & LETTER_PICK_PAD_B) != 0) {
        LetterPick_HideCursorSprite(self);
        LetterPick_PressPanelButton9(self);
        Popup_Hide(&self->popup, 0);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov108_0229d4b4, LetterPick_BrowseByKeys)

/* func_ov108_0229d588 (sub state 5): the choice by the touch, once shown. A button cancels it;
 * the pen going down picks the row under it (the last one outside the window). */
void LetterPick_ChooseByTouch(LetterPick *self)
{
    if (PagedChoice_IsShown(lp_choice(self)) == 0) {
        return;
    }
    if (MenuScene_TakeButtons(lp_scene(self), 1) != 0) {
        LetterPick_CancelChoice(self);
        return;
    }
    if (!lp_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(lp_choice(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    lp_pick_choice_row(self, row);
}
CLEAN_AS(func_ov108_0229d588, LetterPick_ChooseByTouch)

/* func_ov108_0229d620 (sub state 4, which nothing of the overlay enters): the held letter dragged
 * with the touch, the highlights cleared. The carried place under it (8 right and 8 below where
 * it is drawn) is highlighted while the pen is down. Let go on a place that is not dimmed, the
 * letter is put down there and the action ends; let go elsewhere, it glides back to its place in
 * 4 steps. */
void LetterPick_DragHeld(LetterPick *self)
{
    LetterPick_FollowTouch(self);
    LetterPick_ClearHighlights(self);
    int place = LetterPick_LetterPlaceAtTouch(self, (int) ((u32) self->held_x + 8), (int) ((u32) self->held_y + 8), 0);

    if (place == LETTER_PICK_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            LetterPick_GlideHeldTo(self, self->held_from, 4);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        LetterPick_HighlightPlace(self, place);
        return;
    }
    if (LetterPick_PlaceIsDimmed(self, place) == 0 && LetterPick_PutHeldLetterAt(self, place) != 0) {
        LetterPick_EndAction(self);
        return;
    }
    LetterPick_GlideHeldTo(self, self->held_from, 4);
}
CLEAN_AS(func_ov108_0229d620, LetterPick_DragHeld)

/* func_ov108_0229d6b4 (sub state 3): once the popup is up, after `open_delay` more frames, the
 * touched place's choice opens above the popup; sub state 2. */
void LetterPick_OpenTouchedChoice(LetterPick *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return;
    }
    if (self->open_delay != 0) {
        self->open_delay--;
    } else {
        LetterPick_OpenLetterMenu(self, self->touch_place, 1);
        MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_TOUCH_CHOICE);
    }
}
CLEAN_AS(func_ov108_0229d6b4, LetterPick_OpenTouchedChoice)

/* func_ov108_0229d6fc (sub state 2): a touched place's choice is open; once the pen is let go, the
 * choice is run by the touch (sub state 5).
 * QUIRK: answers what MenuScene_SetSubState answers (an address) when the pen is up, else the
 * scene's address, as an int. */
int LetterPick_WatchChoiceTouch(LetterPick *self)
{
    if (data_021fbdd8 == 0) {
        return (int) (uintptr_t) MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_CHOICE_BY_TOUCH);
    }
    return (int) (uintptr_t) self;
}
CLEAN_AS(func_ov108_0229d6fc, LetterPick_WatchChoiceTouch)

/* func_ov108_0229d718 (sub state 1): a place is touched. Let go, a letter that may be picked has
 * its choice opened (sub state 3, run at once); else the scene goes back to sub state 0 with the
 * popup's timer at 60 frames. Held down on a letter that may be picked, once the popup is up and
 * `open_delay` more frames have passed, the place's choice opens above the popup (sub state 2);
 * otherwise a queued popup is shown. */
void LetterPick_HoldTouchOnPlace(LetterPick *self)
{
    if (data_021fbdd8 == 0) {
        if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_SELECTABLE) != 0) {
            MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_OPEN_TOUCHED);
            LetterPick_RunSubState(self);
        } else {
            MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_TOUCH_IDLE);
            Popup_SetTimer(&self->popup, 0x3c);
        }
        return;
    }
    if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_SELECTABLE) != 0 && Popup_IsUp(&self->popup) != 0) {
        if (self->open_delay != 0) {
            self->open_delay--;
        } else {
            LetterPick_OpenLetterMenu(self, self->touch_place, 1);
            MenuScene_SetSubState(lp_scene(self), LETTER_PICK_SUB_TOUCH_CHOICE);
        }
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov108_0229d718, LetterPick_HoldTouchOnPlace)

/* func_ov108_0229d7ac (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor sprite back at the cursor (sub state 6). The pen going down touches the carried
 * place under it (looked for 16 pixels lower) when it holds a letter; else presses the panel's
 * button 9 when on it. */
void LetterPick_IdleByTouch(LetterPick *self)
{
    if (MenuScene_TakeButtons(lp_scene(self), 1) != 0) {
        LetterPick_EndActionAtCursor(self);
        return;
    }
    if (!lp_pen_pressed()) {
        return;
    }
    int place = LetterPick_LetterPlaceAtTouch(self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (place != LETTER_PICK_NO_PLACE) {
        LetterPick_TouchPlace(self, place);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, LETTER_PICK_PANEL_BUTTON_9) != 0) {
        LetterPick_PressPanelButton9(self);
    }
}
CLEAN_AS(func_ov108_0229d7ac, LetterPick_IdleByTouch)

/* The scene's background layer, and the margin of its wipes on window 2. */
#define LETTER_PICK_SCENE_LAYER 6
#define LETTER_PICK_WIPE_MARGIN 0x30
#define LETTER_PICK_WIPE_LAYERS 8

/* The choice's layer. */
#define LETTER_PICK_TEXT_LAYER 3

/* The panel's message under the letters. */
#define LETTER_PICK_PANEL_MESSAGE 0x65

/* The tables of member functions (member_pointer.h): the guards, the tables and their constants. */
extern u32 data_ov108_0229e100; /* the states' guard */
extern u32 data_ov108_0229e104; /* the sub states' guard */
extern MemberPointer data_ov108_0229e108[LETTER_PICK_STATES];
extern MemberPointer data_ov108_0229e130[LETTER_PICK_SUB_STATES];
extern const MemberPointer data_ov108_0229dfa0, data_ov108_0229dfa8, data_ov108_0229dfb0, data_ov108_0229dfc0,
    data_ov108_0229dfc8, data_ov108_0229dfd0, data_ov108_0229dfd8, data_ov108_0229dfe0, data_ov108_0229dfe8,
    data_ov108_0229dff0, data_ov108_0229dff8, data_ov108_0229e000, data_ov108_0229e008, data_ov108_0229e010,
    data_ov108_0229e018, data_ov108_0229e020, data_ov108_0229e028, data_ov108_0229e030, data_ov108_0229e038,
    data_ov108_0229e040, data_ov108_0229e048, data_ov108_0229e050, data_ov108_0229e058, data_ov108_0229e060,
    data_ov108_0229e068, data_ov108_0229e070, data_ov108_0229e078, data_ov108_0229e080, data_ov108_0229e088;

/* The dispatcher (overlay 92's scene), the parent process. */
static MenuDispatch *lp_parent(LetterPick *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* A member drawn through its class (vtable slot 2). */
static void lp_draw_member(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* The scene layer scrolled by the wipe (16 pixels up). */
static void lp_scroll_scene_layer(LetterPick *self)
{
    MenuScene_ScrollWipe(lp_scene(self), LETTER_PICK_SCENE_LAYER, 0, -0x10);
}

/* func_ov108_0229d82c: a step of the wallet display's setup (its answer unused) and the panel's
 * text colours loaded. */
void LetterPick_PreparePanel(LetterPick *self)
{
    PocketsWallet_LoadObjFiles(&self->wallet);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov108_0229d82c, LetterPick_PreparePanel)

/* func_ov108_0229d850: the wallet's display started with 0 and prepared. */
void LetterPick_PrepareWallet(LetterPick *self)
{
    PocketsWallet_SetUp(&self->wallet, 0);
}
CLEAN_AS(func_ov108_0229d850, LetterPick_PrepareWallet)

/* func_ov108_0229d864: the scene layer at priority 2 with its plain background settings. */
void LetterPick_SetUpLayers(void)
{
    DisplayLayer_SetPriority(LETTER_PICK_SCENE_LAYER, 2);
    DisplayLayer_SetBgControl(LETTER_PICK_SCENE_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov108_0229d864, LetterPick_SetUpLayers)

/* func_ov108_0229d884: the end of a frame: the choice and the wallet's display updated, and the
 * popup placed when its update asks for it. */
void LetterPick_EndFrame(LetterPick *self)
{
    PagedChoice_Update(lp_choice(self));
    PocketsWallet_Update(&self->wallet);
    if (Popup_Update(&self->popup) != 0) {
        LetterPick_PlacePopup(self);
    }
}
CLEAN_AS(func_ov108_0229d884, LetterPick_EndFrame)

/* func_ov108_0229d8bc: the start of a frame: the layer task ended, the three objects of ov094's
 * updated and the panel's texts closed. */
void LetterPick_BeginFrame(LetterPick *self)
{
    LetterPick_EndLayerTask(self);
    PocketsWallet_BeginFrame(&self->wallet);
    PocketsGrid_BeginFrame(&self->grid);
    PocketsLetters_BeginFrame(&self->letters);
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov108_0229d8bc, LetterPick_BeginFrame)

/* func_ov108_0229d8fc */
void LetterPick_EndInteractiveFrame(LetterPick *self)
{
    LetterPick_EndFrame(self);
}
CLEAN_AS(func_ov108_0229d8fc, LetterPick_EndInteractiveFrame)

/* func_ov108_0229d904: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3), whose answer it gives. */
int LetterPick_BeginInteractiveFrame(LetterPick *self)
{
    LetterPick_BeginFrame(self);
    return lp_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov108_0229d904, LetterPick_BeginInteractiveFrame)

/* func_ov108_0229d920: the members' teardown before the scene closes. */
void LetterPick_Teardown(LetterPick *self)
{
    LetterPick_EndLayerTask(self);
    PocketsWallet_Teardown(&self->wallet);
    PocketsGrid_Teardown(&self->grid);
    PagedChoice_Dismiss(lp_choice(self));
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov108_0229d920, LetterPick_Teardown)

/* func_ov108_0229d960: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the glide stopped, nothing held, the cursor on the first carried letter, the
 * choice on layer 3 at priority 1; no open delay. */
void LetterPick_Setup(LetterPick *self)
{
    self->flags = 0;
    PocketsGrid_Init(&self->grid, 2);
    PocketsLetters_Init(&self->letters, 2);
    PocketsWallet_Init(&self->wallet, 6);
    self->popup_place = LETTER_PICK_NO_PLACE;
    Glide_Stop(&self->glide);
    self->held_kind = LETTER_PICK_HELD_NONE;
    self->cursor = LETTER_PICK_CARRIED_FIRST;
    PagedChoice_Init(lp_choice(self), LETTER_PICK_TEXT_LAYER, 1, NULL);
    self->open_delay = 0;
}
CLEAN_AS(func_ov108_0229d960, LetterPick_Setup)

/* func_ov108_0229d9e0 (state 4): the scene wipes out; when done, its layer hidden, the scene and
 * its objects no longer drawn and the end phase begins (LetterPick_End); else the layer follows
 * the wipe. The wipe's y is kept either way. */
void LetterPick_SceneWipeOut(LetterPick *self)
{
    if (MenuScene_StepWipe(lp_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(LETTER_PICK_SCENE_LAYER);
        LetterPick_ClearFlags(self, LETTER_PICK_FLAG_OBJECTS_DRAWN);
        LetterPick_ClearFlags(self, LETTER_PICK_FLAG_DRAWN);
        MenuScene_SetPhase(lp_scene(self), LETTER_PICK_PHASE_END);
    } else {
        lp_scroll_scene_layer(self);
    }
    self->objects_y = MenuScene_WipeOffsetY(lp_scene(self));
}
CLEAN_AS(func_ov108_0229d9e0, LetterPick_SceneWipeOut)

/* func_ov108_0229da2c (state 3, after a letter was picked or the panel's button 9): the popup
 * hidden (its queue dropped) and the cursor sprite hidden; the dispatcher told the screen ends
 * (code 0x44, with its sound); the scene starts to wipe out on window 2 (state 4). */
void LetterPick_StartWipeOut(LetterPick *self)
{
    Popup_Hide(&self->popup, 1);
    LetterPick_HideCursorSprite(self);
    MenuDispatch_SetMode(lp_parent(self), LETTER_PICK_PARENT_CODE_END, 1);
    MenuScene_StartWipeOnWindow2(lp_scene(self), LETTER_PICK_WIPE_LAYERS, 0, 0, LETTER_PICK_WIPE_MARGIN);
    lp_scroll_scene_layer(self);
    MenuScene_SetState(lp_scene(self), LETTER_PICK_STATE_SCENE_WIPE_OUT);
    self->objects_y = MenuScene_WipeOffsetY(lp_scene(self));
}
CLEAN_AS(func_ov108_0229da2c, LetterPick_StartWipeOut)

/* func_ov108_0229da8c (state 2): the scene wipes in, its layer following and the wipe's y kept;
 * when done, phase 2 and the action ends (LetterPick_EndAction picks the touch or the keys). */
void LetterPick_SceneWipeIn(LetterPick *self)
{
    if (MenuScene_StepWipeBack(lp_scene(self), 0) != 0) {
        MenuScene_SetPhase(lp_scene(self), LETTER_PICK_PHASE_INTERACTIVE);
        LetterPick_EndAction(self);
    }
    lp_scroll_scene_layer(self);
    self->objects_y = MenuScene_WipeOffsetY(lp_scene(self));
}
CLEAN_AS(func_ov108_0229da8c, LetterPick_SceneWipeIn)

/* func_ov108_0229dac8 (state 1): the panel prepared with its layout 5 and message 0x65, the
 * grid's and the letters' objects prepared, the letters dimmed (LetterPick_DimLetters), the scene
 * layer shown and wiping in on window 2 (state 2); the scene and its objects drawn. */
void LetterPick_StartWipeIn(LetterPick *self)
{
    LetterPick_PreparePanel(self);
    ButtonPanel_SetLayout5(&self->panel, LETTER_PICK_PANEL_MESSAGE);
    PocketsGrid_LoadPockets(&self->grid);
    PocketsLetters_LoadPockets(&self->letters);
    LetterPick_DimLetters(self);
    MenuScene_StartWipeCoveredOnWindow2(lp_scene(self), LETTER_PICK_WIPE_LAYERS, 0, 0, LETTER_PICK_WIPE_MARGIN);
    DisplayLayer_Show(LETTER_PICK_SCENE_LAYER);
    lp_scroll_scene_layer(self);
    MenuScene_SetState(lp_scene(self), LETTER_PICK_STATE_SCENE_WIPE_IN);
    LetterPick_SetFlags(self, LETTER_PICK_FLAG_DRAWN);
    LetterPick_SetFlags(self, LETTER_PICK_FLAG_OBJECTS_DRAWN);
    self->objects_y = MenuScene_WipeOffsetY(lp_scene(self));
}
CLEAN_AS(func_ov108_0229dac8, LetterPick_StartWipeIn)

/* func_ov108_0229db4c (state 0): the layer set up and the wallet's display prepared, then
 * state 1. */
void LetterPick_StartSetup(LetterPick *self)
{
    LetterPick_SetUpLayers();
    LetterPick_PrepareWallet(self);
    MenuScene_SetState(lp_scene(self), LETTER_PICK_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov108_0229db4c, LetterPick_StartSetup)

/* func_ov108_0229db68 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int LetterPick_End(LetterPick *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov108_0229db68, LetterPick_End)

/* func_ov108_0229db78 (vtable slot 0x58, phase 4): nothing. */
int LetterPick_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov108_0229db78, LetterPick_Phase4Idle)

/* func_ov108_0229db7c (vtable slot 0x54, phase 3): nothing. */
int LetterPick_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov108_0229db7c, LetterPick_Phase3Idle)

/* func_ov108_0229db80 (vtable slot 0x50, phase 2): a frame of the scene in use: its start, its
 * sub state and its end. Answers 1. */
int LetterPick_RunInteractive(LetterPick *self)
{
    LetterPick_BeginInteractiveFrame(self);
    LetterPick_RunSubState(self);
    LetterPick_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(func_ov108_0229db80, LetterPick_RunInteractive)

/* func_ov108_0229db9c: the sub state's function (LetterPickSubState) through the table of member
 * functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x18; the game reads past the table for others. */
void LetterPick_RunSubState(LetterPick *self)
{
    static const MemberPointer *const sub_states[LETTER_PICK_SUB_STATES] = {
        &data_ov108_0229e058, &data_ov108_0229e050, &data_ov108_0229e048, &data_ov108_0229e040, &data_ov108_0229e038,
        &data_ov108_0229e030, &data_ov108_0229e028, &data_ov108_0229e020, &data_ov108_0229e018, &data_ov108_0229e010,
        &data_ov108_0229dfc8, &data_ov108_0229e008, &data_ov108_0229dff8, &data_ov108_0229e068, &data_ov108_0229dfe8,
        &data_ov108_0229dfe0, &data_ov108_0229dfd8, &data_ov108_0229dfd0, &data_ov108_0229dfc0, &data_ov108_0229e060,
        &data_ov108_0229dff0, &data_ov108_0229dfb0, &data_ov108_0229dfa8, &data_ov108_0229e080,
    };
    MemberTable_InitOnce(&data_ov108_0229e104, data_ov108_0229e130, sub_states, LETTER_PICK_SUB_STATES);
    MemberPointer_CallVoid(&data_ov108_0229e130[self->base.sub_state], self);
}
CLEAN_AS(func_ov108_0229db9c, LetterPick_RunSubState)

/* func_ov108_0229dd40 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (LetterPickState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int LetterPick_RunState(LetterPick *self)
{
    static const MemberPointer *const states[LETTER_PICK_STATES] = {
        &data_ov108_0229dfa0, &data_ov108_0229e088, &data_ov108_0229e000, &data_ov108_0229e078, &data_ov108_0229e070,
    };
    MemberTable_InitOnce(&data_ov108_0229e100, data_ov108_0229e108, states, LETTER_PICK_STATES);
    LetterPick_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov108_0229e108[self->base.state], self);
    LetterPick_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov108_0229dd40, LetterPick_RunState)

/* func_ov108_0229dde0 (vtable slot 0x24): the scene's draw: the choice always; while the scene is
 * drawn, the popup (through its class, slot 2), the cursor sprite (with the keys in use) and the
 * held letter; with the objects drawn, the panel at the wipe's y and the grid, the carried
 * letters and the wallet 16 pixels higher. Answers 1. */
int LetterPick_Draw(LetterPick *self)
{
    PagedChoice_Draw(lp_choice(self));
    if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_DRAWN) == 0) {
        return 1;
    }
    lp_draw_member(&self->popup);
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    LetterPick_DrawHeld(self);
    if (LetterPick_TestFlags(self, LETTER_PICK_FLAG_OBJECTS_DRAWN) != 0) {
        ButtonPanel_Draw(&self->panel, self->objects_y);
        int y = (int) ((u32) self->objects_y - 0x10);
        PocketsGrid_DrawPockets(&self->grid, 0, y);
        PocketsLetters_DrawPockets(&self->letters, 0, y);
        PocketsWallet_Draw(&self->wallet, y);
    }
    return 1;
}
CLEAN_AS(func_ov108_0229dde0, LetterPick_Draw)

/* func_ov108_0229de88 (vtable slot 0x0c): the scene closes: the dispatcher told and the members
 * torn down. Answers 1. */
int LetterPick_Close(LetterPick *self)
{
    MenuDispatch_ChildClosed(lp_parent(self));
    LetterPick_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov108_0229de88, LetterPick_Close)

/* func_ov108_0229dea4 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 0.
 * Answers 1. */
int LetterPick_Start(LetterPick *self)
{
    LetterPick_Setup(self);
    MenuScene_SetState(lp_scene(self), LETTER_PICK_STATE_START_SETUP);
    MenuScene_SetPhase(lp_scene(self), LETTER_PICK_PHASE_WAIT);
    return 1;
}
CLEAN_AS(func_ov108_0229dea4, LetterPick_Start)

/* func_ov108_0229dec4: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed in order. */
LetterPick *LetterPick_New(void)
{
    LetterPick *self = MenuScene_Alloc(sizeof(LetterPick));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov108_0229e098;
    Letter_Construct(&self->held);
    Letter_Construct(&self->swapped);
    LayerTask_ConstructPair(&self->task);
    PocketsGrid_Construct(&self->grid);
    PocketsLetters_Construct(&self->letters);
    PocketsWallet_Construct(&self->wallet);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(lp_choice(self));
    ErrorMessage_Construct(&self->error);
    ButtonPanel_Construct(&self->panel);
    return self;
}
CLEAN_AS(func_ov108_0229dec4, LetterPick_New)
