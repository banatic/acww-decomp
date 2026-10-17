/* The mailbox scene of overlay 106 (mailbox_scene.h): its destructors, its flags, the cursor's
 * moves, the choices it opens, the held letter and its places. */
#include "mailbox_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/item_code.h"
#include "main/item_record.h"
#include "main/label_sprite.h"
#include "main/layer_load_task.h"
#include "main/lookups.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov094/pockets_common.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(MailboxScene, flags) == 0x94, "flags");
static_assert(offsetof(MailboxScene, grab_dx) == 0xa4 && offsetof(MailboxScene, held_x) == 0xac, "places");
static_assert(offsetof(MailboxScene, held_kind) == 0xb4 && offsetof(MailboxScene, cursor) == 0xb8, "bytes");
static_assert(offsetof(MailboxScene, choice_row) == 0xbd && offsetof(MailboxScene, unk_c0) == 0xc0, "bytes");
static_assert(offsetof(MailboxScene, grid) == 0xf8 && offsetof(MailboxScene, letters) == 0xb58, "ov094 objects");
static_assert(offsetof(MailboxScene, wallet) == 0xb80 && offsetof(MailboxScene, popup) == 0x21b8, "wallet");
static_assert(offsetof(MailboxScene, glide) == 0x2288 && offsetof(MailboxScene, cursor_sprite) == 0x22a0, "glide");
static_assert(offsetof(MailboxScene, choice) == 0x2304 && offsetof(MailboxScene, entries) == 0x26ec, "choice");
static_assert(offsetof(MailboxScene, error) == 0x26f8 && offsetof(MailboxScene, view) == 0x2814, "error");
static_assert(offsetof(MailboxScene, button) == 0x2b3c && offsetof(MailboxScene, mailbox) == 0x2bb4, "button");
static_assert(offsetof(MailboxScene, unk_35b4) == 0x35b4 && offsetof(MailboxScene, panel) == 0x3fb4, "panel");
static_assert(offsetof(MailboxScene, held) == 0x4180 && offsetof(MailboxScene, swapped) == 0x4280, "held");
static_assert(sizeof(MailboxScene) == 0x4380, "size (func_ov106_0229f41c)");

/* The item code of no item (main/item_code.h). */
#define MAILBOX_SCENE_NO_ITEM 0xfff1

/* The touch (main's bytes, as ov099's pockets_view.c reads them). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;

/* The scene's vtable. */
extern const u8 data_ov106_0229f6e0[];

/* The members' destructors (a letter's is handed to __cxa_vec_cleanup, so it is the game's
 * symbol). */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02066688(void *letter);

/* What the parent (overlay 92's) is told (func_ov092_02299324): the scene ends. */
extern void func_ov092_02299324(Process *parent, int code, int flag);
#define MAILBOX_SCENE_PARENT_CODE_END 0x44

static PagedChoice *mbx_choice(MailboxScene *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static MenuScene *mbx_scene(MailboxScene *self)
{
    return &self->base;
}

static int mbx_is_carried(MailboxScene *self, int place)
{
    return MailboxScene_IsCarriedPlace(self, (unsigned int) place) != 0;
}

/* The place is a letter of the letters object: carried or in the mailbox. */
static int mbx_is_letter_place(MailboxScene *self, int place)
{
    return MailboxScene_IsCarriedPlace(self, (unsigned int) place) != 0 ||
           MailboxScene_IsMailboxPlace(self, (unsigned int) place) != 0;
}

static int mbx_letter_index(MailboxScene *self, int place)
{
    return MailboxScene_LetterIndex(self, (unsigned int) place);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void mbx_update_cursor_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* The members' destructors, last member first, then the base's. */
static void mbx_destroy_members(MailboxScene *self)
{
    self->base.vtable = data_ov106_0229f6e0;
    Letter_Destruct(&self->swapped);
    Letter_Destruct(&self->held);
    ButtonPanel_Destroy(&self->panel);
    __cxa_vec_cleanup(self->unk_35b4, MAILBOX_SCENE_LETTERS, sizeof(Letter), func_02066688);
    __cxa_vec_cleanup(self->mailbox, MAILBOX_SCENE_LETTERS, sizeof(Letter), func_02066688);
    LabelButton0_Destroy(&self->button);
    LetterView_Destruct(&self->view);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(mbx_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(mbx_scene(self));
}

/* func_ov106_0229c180 */
MailboxScene *MailboxScene_Destroy(MailboxScene *self)
{
    mbx_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov106_0229c180, MailboxScene_Destroy)

/* func_ov106_0229c260 */
MailboxScene *MailboxScene_Delete(MailboxScene *self)
{
    mbx_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov106_0229c260, MailboxScene_Delete)

/* func_ov106_0229c344 */
void MailboxScene_ClearFlags(MailboxScene *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov106_0229c344, MailboxScene_ClearFlags)

/* func_ov106_0229c354 */
void MailboxScene_SetFlags(MailboxScene *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov106_0229c354, MailboxScene_SetFlags)

/* func_ov106_0229c364: 1 when any of `flags` is set. */
int MailboxScene_TestFlags(MailboxScene *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov106_0229c364, MailboxScene_TestFlags)

/* func_ov106_0229c378: sound 0x27, the panel's button 9 selected, sub state 0x23. */
void MailboxScene_PressPanelButton9(MailboxScene *self)
{
    SoundSys_PlaySe(0x27);
    ButtonPanel_Select(&self->panel, 9);
    MenuScene_SetSubState(mbx_scene(self), 0x23);
}
CLEAN_AS(func_ov106_0229c378, MailboxScene_PressPanelButton9)

/* func_ov106_0229c3a0 (action 3) */
void MailboxScene_RunActionMenu(MailboxScene *self)
{
    MailboxScene_OpenFixedMenu(self);
}
CLEAN_AS(func_ov106_0229c3a0, MailboxScene_RunActionMenu)

/* func_ov106_0229c3a8 (action 2): the letter of the place whose choice is open picked up and
 * held where that place is (2 pixels up and left when state flag 2 is set), sub state 0x26. */
void MailboxScene_PickUpSlotLetter(MailboxScene *self)
{
    u8 place = self->slot;
    MailboxScene_PickUpLetter(self, place);
    self->held_x = MailboxScene_PlaceX(self, place);
    self->held_y = MailboxScene_PlaceY(self, place);
    if (StateFlags_Test2() != 0) {
        self->held_x -= 2;
        self->held_y -= 2;
    }
    MenuScene_SetSubState(mbx_scene(self), 0x26);
    PocketsLetters_StartPickUp(&self->letters);
}
CLEAN_AS(func_ov106_0229c3a8, MailboxScene_PickUpSlotLetter)

/* func_ov106_0229c418 (when the menu is asked to close, StateFlags_MenuCloseAsked): the label
 * button pressed, MAILBOX_SCENE_FLAG_CLOSING, the cursor sprite hidden, state 9 in phase 1, and
 * the parent told the scene ends (with its sound). */
void MailboxScene_CloseOnRequest(MailboxScene *self)
{
    MailboxScene_PressLabelButton(self);
    MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_CLOSING);
    MailboxScene_HideCursorSprite(self);
    MenuScene_SetState(mbx_scene(self), 9);
    MenuScene_SetPhase(mbx_scene(self), 1);
    func_ov092_02299324(Process_GetParent((Process *) (void *) self), MAILBOX_SCENE_PARENT_CODE_END, 1);
}
CLEAN_AS(func_ov106_0229c418, MailboxScene_CloseOnRequest)

/* func_ov106_0229c458: sub state 0x22, the label button's state 2, sound 0x29. */
void MailboxScene_PressLabelButton(MailboxScene *self)
{
    MenuScene_SetSubState(mbx_scene(self), 0x22);
    /* The button's base is main's labelled sprite (label_button.h). */
    LabelSprite_SetState((LabelSprite *) (void *) &self->button, 2);
    SoundSys_PlaySe(0x29);
}
CLEAN_AS(func_ov106_0229c458, MailboxScene_PressLabelButton)

/* func_ov106_0229c47c (action 1): state 4, phase 1, flag 0x100. */
void MailboxScene_RunAction1(MailboxScene *self)
{
    MenuScene_SetState(mbx_scene(self), 4);
    MenuScene_SetPhase(mbx_scene(self), 1);
    MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_100);
}
CLEAN_AS(func_ov106_0229c47c, MailboxScene_RunAction1)

/* func_ov106_0229c4a0: the cursor moved by `keys` (KeyRepeat_Has*) in the part of the scene it
 * is in; `mode` 0 lets it go down to MAILBOX_SCENE_BELOW, `mode` 1 (a letter held) keeps a
 * carried letter out of the mailbox. The wrap flags are cleared first. 1 when the cursor changed
 * place; 0 at once when `keys` is 0. */
int MailboxScene_MoveCursor(MailboxScene *self, int keys, int mode)
{
    u8 before = self->cursor;

    MailboxScene_ClearFlags(self, MAILBOX_SCENE_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (MailboxScene_IsCarriedPlace(self, self->cursor) != 0) {
        MailboxScene_MoveCursorInCarried(self, keys, mode);
    } else if (MailboxScene_IsMailboxPlace(self, self->cursor) != 0) {
        MailboxScene_MoveCursorInMailbox(self, keys, mode);
    } else if (MailboxScene_IsBelowPlace(self, self->cursor) != 0) {
        MailboxScene_MoveCursorBelow(self, keys);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov106_0229c4a0, MailboxScene_MoveCursor)

/* func_ov106_0229c524: up from MAILBOX_SCENE_BELOW goes to the carried letters' bottom left
 * (0x13), the cursor sprite turning to set A. */
void MailboxScene_MoveCursorBelow(MailboxScene *self, int keys)
{
    if (KeyRepeat_HasUp(keys) != 0) {
        Glider_TurnToSetA(&self->cursor_sprite);
        self->cursor = 0x13;
    }
}
CLEAN_AS(func_ov106_0229c524, MailboxScene_MoveCursorBelow)

/* Up and down within a column of five rows of two (shared by the carried letters and the
 * mailbox's): up stops at the top row, down from the bottom row goes to MAILBOX_SCENE_BELOW
 * when `mode` is 0, the cursor sprite turning to set B. */
static void mbx_move_in_column(MailboxScene *self, int keys, int mode, int row)
{
    if (KeyRepeat_HasUp(keys) != 0) {
        if (row > 0) {
            self->cursor -= MAILBOX_SCENE_COLUMNS;
        }
        return;
    }
    if (KeyRepeat_HasDown(keys) != 0) {
        if (row < MAILBOX_SCENE_ROWS - 1) {
            self->cursor += MAILBOX_SCENE_COLUMNS;
            return;
        }
        if (mode == 0) {
            self->cursor = MAILBOX_SCENE_BELOW;
            Glider_TurnToSetB(&self->cursor_sprite);
        }
    }
}

/* func_ov106_0229c54c: the cursor on the mailbox's letters (5 rows of 2). Left of the left
 * column goes to the carried letters' right column of the same row
 * (MAILBOX_SCENE_FLAG_WRAPPED_LEFT), right of the right column to their left column (no flag).
 * Up and down are taken only when the move stayed in the mailbox and did not wrap. */
void MailboxScene_MoveCursorInMailbox(MailboxScene *self, int keys, int mode)
{
    int column = (int) self->cursor - MAILBOX_SCENE_MAILBOX_FIRST;
    int row = 0;
    while (column >= MAILBOX_SCENE_COLUMNS) {
        row++;
        column -= MAILBOX_SCENE_COLUMNS;
    }

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column <= 0) {
            self->cursor = (u8) (row * 2 + MAILBOX_SCENE_CARRIED_FIRST + 1);
            MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_WRAPPED_LEFT);
            return;
        }
        self->cursor--;
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column >= 1) {
            self->cursor = (u8) (row * 2 + MAILBOX_SCENE_CARRIED_FIRST);
            return;
        }
        self->cursor++;
    }

    if (MailboxScene_IsMailboxPlace(self, self->cursor) == 0 ||
        MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAGS_WRAPPED) != 0) {
        return;
    }
    mbx_move_in_column(self, keys, mode, row);
}
CLEAN_AS(func_ov106_0229c54c, MailboxScene_MoveCursorInMailbox)

/* func_ov106_0229c638: the cursor on the carried letters (5 rows of 2). Left of the left column
 * goes to the mailbox's right column of the same row (no flag), right of the right column to its
 * left column (MAILBOX_SCENE_FLAG_WRAPPED_RIGHT); in `mode` 1 with a letter taken from the
 * carried ones (`held_from`) the cursor does not leave them. Up and down are taken only when the
 * cursor is still on the carried letters and did not wrap. */
void MailboxScene_MoveCursorInCarried(MailboxScene *self, int keys, int mode)
{
    int index = (int) self->cursor - MAILBOX_SCENE_CARRIED_FIRST;
    int column = index & 1;
    /* The ROM shifts arithmetically; `index` is 0-9 for the places this is called on. */
    int row = index >> 1;

    if (KeyRepeat_HasLeft(keys) != 0) {
        if (column > 0) {
            self->cursor--;
        } else if (!(mode == 1 && mbx_is_carried(self, self->held_from))) {
            self->cursor = (u8) (row * 2 + MAILBOX_SCENE_MAILBOX_FIRST + 1);
            return;
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (column < 1) {
            self->cursor++;
        } else if (!(mode == 1 && mbx_is_carried(self, self->held_from))) {
            self->cursor = (u8) (row * 2 + MAILBOX_SCENE_MAILBOX_FIRST);
            MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_WRAPPED_RIGHT);
            return;
        }
    }

    if (MailboxScene_IsCarriedPlace(self, self->cursor) == 0 ||
        MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAGS_WRAPPED) != 0) {
        return;
    }
    mbx_move_in_column(self, keys, mode, row);
}
CLEAN_AS(func_ov106_0229c638, MailboxScene_MoveCursorInCarried)

/* func_ov106_0229c748: the fixed choice (its first row set apart): texts 0x1a and 0x19 cancel,
 * text 0x15 picks the letter up. */
void MailboxScene_OpenFixedMenu(MailboxScene *self)
{
    MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_FIXED_MENU);
    ChoiceEntries_Clear(&self->entries, MAILBOX_SCENE_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x1a, MAILBOX_SCENE_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x15, MAILBOX_SCENE_ACTION_PICK_UP);
    ChoiceEntries_Add(&self->entries, 0x19, MAILBOX_SCENE_ACTION_CANCEL);
    MailboxScene_ShowChoice(self, 0);
}
CLEAN_AS(func_ov106_0229c748, MailboxScene_OpenFixedMenu)

/* func_ov106_0229c798: the choice of the letter at `place`: text 0 (action 0) when state flag 2
 * is set; text 0x17 (state 7) or 0x14 (another state but 0) for action 1; text 0x15 for the
 * fixed menu when the letter has no item and its state is 1, 3, 4 or 6; text 2 to cancel. The
 * cursor sprite is hidden, the popup too unless the choice goes above it. */
void MailboxScene_OpenLetterMenu(MailboxScene *self, int place, int above_popup)
{
    MailboxScene_ClearFlags(self, MAILBOX_SCENE_FLAG_FIXED_MENU);
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, MAILBOX_SCENE_ACTION_CANCEL);
    Letter *letter = MailboxScene_PlaceLetter(self, place);
    if (StateFlags_Test2() != 0) {
        ChoiceEntries_Add(&self->entries, 0, MAILBOX_SCENE_ACTION_0);
    }
    int state = Letter_State(letter);
    if (state != 0) {
        if (state == 7) {
            ChoiceEntries_Add(&self->entries, 0x17, MAILBOX_SCENE_ACTION_1);
        } else {
            ChoiceEntries_Add(&self->entries, 0x14, MAILBOX_SCENE_ACTION_1);
        }
    }
    if (Letter_Item(letter) == MAILBOX_SCENE_NO_ITEM && (state == 3 || state == 6 || state == 1 || state == 4)) {
        ChoiceEntries_Add(&self->entries, 0x15, MAILBOX_SCENE_ACTION_MENU);
    }
    ChoiceEntries_Add(&self->entries, 2, MAILBOX_SCENE_ACTION_CANCEL);
    MailboxScene_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    MailboxScene_ShowChoice(self, above_popup);
}
CLEAN_AS(func_ov106_0229c798, MailboxScene_OpenLetterMenu)

/* func_ov106_0229c868: the cancel action, the cursor sprite put back at the cursor, the choice
 * asked to close, sub state 0x18. */
void MailboxScene_CancelChoice(MailboxScene *self)
{
    self->action = MAILBOX_SCENE_ACTION_CANCEL;
    MailboxScene_PlaceCursorSprite(self);
    PagedChoice_RequestClose(mbx_choice(self), 0);
    MenuScene_SetSubState(mbx_scene(self), 0x18);
}
CLEAN_AS(func_ov106_0229c868, MailboxScene_CancelChoice)

/* func_ov106_0229c894: the entries shown in the choice (the first row set apart for the fixed
 * menu), placed above the popup or beside the open place, asked to open; sub state 0x16. */
void MailboxScene_ShowChoice(MailboxScene *self, int above_popup)
{
    int fixed = MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_FIXED_MENU);
    PagedChoice_ShowEntries(mbx_choice(self), &self->entries, fixed);
    int x = MailboxScene_PlaceX(self, self->slot);
    int y = MailboxScene_PlaceY(self, self->slot);
    if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(mbx_choice(self), &self->popup);
    } else {
        PagedChoice_PlaceBeside(mbx_choice(self), x, y);
    }
    PagedChoice_RequestOpen(mbx_choice(self), 0);
    MenuScene_SetSubState(mbx_scene(self), 0x16);
}
CLEAN_AS(func_ov106_0229c894, MailboxScene_ShowChoice)

/* func_ov106_0229c910: the action picked (`action`); any value above 3 cancels. */
void MailboxScene_RunAction(MailboxScene *self)
{
    switch (self->action) {
        case MAILBOX_SCENE_ACTION_0:
            MailboxScene_RunAction0(self);
            break;
        case MAILBOX_SCENE_ACTION_1:
            MailboxScene_RunAction1(self);
            break;
        case MAILBOX_SCENE_ACTION_PICK_UP:
            MailboxScene_PickUpSlotLetter(self);
            break;
        case MAILBOX_SCENE_ACTION_MENU:
            MailboxScene_RunActionMenu(self);
            break;
        default:
            MailboxScene_EndAction(self);
            break;
    }
}
CLEAN_AS(func_ov106_0229c910, MailboxScene_RunAction)

/* func_ov106_0229c958: the popup hidden, the sub state to go back to kept, `target` kept, the
 * cursor sprite's animation 6, sub state 0x13. */
void MailboxScene_BeginSubState13(MailboxScene *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 6);
    MenuScene_SetSubState(mbx_scene(self), 0x13);
}
CLEAN_AS(func_ov106_0229c958, MailboxScene_BeginSubState13)

/* func_ov106_0229c9a0: the popup hidden, `target` kept, the cursor sprite's animation 5, sub
 * state 0x12. */
void MailboxScene_BeginSubState12(MailboxScene *self, u8 target)
{
    Popup_Hide(&self->popup, 1);
    self->target = target;
    Glider_SetAnim(&self->cursor_sprite, 5);
    MenuScene_SetSubState(mbx_scene(self), 0x12);
}
CLEAN_AS(func_ov106_0229c9a0, MailboxScene_BeginSubState12)

/* func_ov106_0229c9dc (action 0): the cursor sprite's animation 4, sub state 0x10. */
void MailboxScene_RunAction0(MailboxScene *self)
{
    Glider_SetAnim(&self->cursor_sprite, 4);
    MenuScene_SetSubState(mbx_scene(self), 0x10);
}
CLEAN_AS(func_ov106_0229c9dc, MailboxScene_RunAction0)

/* func_ov106_0229c9fc */
void MailboxScene_BeginSubState0f(MailboxScene *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(mbx_scene(self), 0x0f);
}
CLEAN_AS(func_ov106_0229c9fc, MailboxScene_BeginSubState0f)

/* func_ov106_0229ca1c */
void MailboxScene_BeginSubState0e(MailboxScene *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(mbx_scene(self), 0x0e);
}
CLEAN_AS(func_ov106_0229ca1c, MailboxScene_BeginSubState0e)

/* func_ov106_0229ca3c: the first animation of the cursor sprite's set, then its update. */
void MailboxScene_ShowCursorFirstOfSet(MailboxScene *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    mbx_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov106_0229ca3c, MailboxScene_ShowCursorFirstOfSet)

/* func_ov106_0229ca5c: the cursor sprite put at the cursor, animation 1. */
void MailboxScene_PlaceCursorSprite(MailboxScene *self)
{
    int x = MailboxScene_CursorSpriteX(self);
    int y = MailboxScene_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 1);
}
CLEAN_AS(func_ov106_0229ca5c, MailboxScene_PlaceCursorSprite)

/* func_ov106_0229ca90: the cursor sprite put at the choice's row 1 for the fixed menu (its
 * first row set apart), else at row 0; animation 7. */
void MailboxScene_PointAtDefaultRow(MailboxScene *self)
{
    self->choice_row = MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_FIXED_MENU) != 0 ? 1 : 0;
    int x = PagedChoice_TextX(mbx_choice(self));
    int y = PagedChoice_RowY(mbx_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, 7);
}
CLEAN_AS(func_ov106_0229ca90, MailboxScene_PointAtDefaultRow)

/* func_ov106_0229caf4: the cancel action, the choice's last row picked and the cursor sprite
 * put at it, showing animation 8 from its last frame; sub state 0x17. QUIRK: answers what
 * MenuScene_SetSubState answers (an address), as an int. */
int MailboxScene_PointAtLastRow(MailboxScene *self)
{
    self->action = MAILBOX_SCENE_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(mbx_choice(self), 1);
    int x = PagedChoice_TextX(mbx_choice(self));
    int y = PagedChoice_RowY(mbx_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, 8);
    return (int) (uintptr_t) MenuScene_SetSubState(mbx_scene(self), 0x17);
}
CLEAN_AS(func_ov106_0229caf4, MailboxScene_PointAtLastRow)

/* func_ov106_0229cb58: the cursor sprite moved to the choice row in 2 steps; the sub state to
 * go back to kept, sub state 0x0d. */
void MailboxScene_GlideToRow(MailboxScene *self)
{
    int x = PagedChoice_TextX(mbx_choice(self));
    int y = PagedChoice_RowY(mbx_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(mbx_scene(self), 0x0d);
}
CLEAN_AS(func_ov106_0229cb58, MailboxScene_GlideToRow)

/* func_ov106_0229cba8: the cursor sprite eased to (x, y) in 3 steps; the sub state to go back
 * to kept, sub state 0x0d. */
void MailboxScene_EaseCursorSpriteTo(MailboxScene *self, int x, int y)
{
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(mbx_scene(self), 0x0d);
}
CLEAN_AS(func_ov106_0229cba8, MailboxScene_EaseCursorSpriteTo)

/* func_ov106_0229cbdc: the cursor sprite put at the cursor at once when flag 8 is set (which
 * this clears), else eased there as MailboxScene_EaseCursorSpriteTo does. */
void MailboxScene_GlideToCursor(MailboxScene *self)
{
    if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_08) != 0) {
        int x = MailboxScene_CursorSpriteX(self);
        int y = MailboxScene_CursorSpriteY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        MailboxScene_ClearFlags(self, MAILBOX_SCENE_FLAG_08);
    } else {
        int x = MailboxScene_CursorSpriteX(self);
        int y = MailboxScene_CursorSpriteY(self);
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
        self->return_state = self->base.sub_state;
        MenuScene_SetSubState(mbx_scene(self), 0x0d);
    }
}
CLEAN_AS(func_ov106_0229cbdc, MailboxScene_GlideToCursor)

/* func_ov106_0229cc50: the cursor sprite's animation 0, then its update. */
void MailboxScene_HideCursorSprite(MailboxScene *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    mbx_update_cursor_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov106_0229cc50, MailboxScene_HideCursorSprite)

/* func_ov106_0229cc74: the cursor sprite's y, the cursor's place's. */
int MailboxScene_CursorSpriteY(MailboxScene *self)
{
    return MailboxScene_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov106_0229cc74, MailboxScene_CursorSpriteY)

/* func_ov106_0229cc84: the cursor sprite's x, the cursor's place's plus 8; a screen width (256)
 * further right when this move wrapped right, further left when it wrapped left, so the sprite
 * slides there. */
int MailboxScene_CursorSpriteX(MailboxScene *self)
{
    int x = MailboxScene_PlaceX(self, self->cursor);
    if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_WRAPPED_RIGHT) != 0) {
        x += 0x100;
    } else if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_WRAPPED_LEFT) != 0) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov106_0229cc84, MailboxScene_CursorSpriteX)

/* func_ov106_0229ccc8: the cursor sprite put at the cursor, animation 7 on MAILBOX_SCENE_BELOW
 * and 1 elsewhere, then its set's first animation shown. */
void MailboxScene_ShowCursorAtCursor(MailboxScene *self)
{
    int x = MailboxScene_CursorSpriteX(self);
    int y = MailboxScene_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (MailboxScene_IsBelowPlace(self, self->cursor) != 0) {
        Glider_SetAnim(&self->cursor_sprite, 7);
    } else {
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    MailboxScene_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov106_0229ccc8, MailboxScene_ShowCursorAtCursor)

/* func_ov106_0229cd20: when a letter is held, it changes places with the letter at `place`: the
 * held one is copied aside, the place's letter picked up and the copy put at `place`. */
void MailboxScene_SwapHeldWith(MailboxScene *self, int place)
{
    if (self->held_kind == MAILBOX_SCENE_HELD_LETTER) {
        Letter_Assign(&self->swapped, &self->held);
        MailboxScene_PickUpLetter(self, place);
        MailboxScene_PutLetterAt(self, place, &self->swapped);
    }
}
CLEAN_AS(func_ov106_0229cd20, MailboxScene_SwapHeldWith)

/* func_ov106_0229cd60: the held letter, if any, put at `place`; nothing held after. */
void MailboxScene_PutHeldAt(MailboxScene *self, int place)
{
    if (self->held_kind == MAILBOX_SCENE_HELD_LETTER) {
        MailboxScene_PutLetterAt(self, place, &self->held);
    }
    self->held_kind = MAILBOX_SCENE_HELD_NONE;
}
CLEAN_AS(func_ov106_0229cd60, MailboxScene_PutHeldAt)

/* func_ov106_0229cd88: the letter at `place` (a carried or mailbox letter; other places are left
 * alone) copied into `held` and taken from the letters object. */
void MailboxScene_PickUpLetter(MailboxScene *self, int place)
{
    if (!mbx_is_letter_place(self, place)) {
        return;
    }
    int index = mbx_letter_index(self, place);
    self->held_kind = MAILBOX_SCENE_HELD_LETTER;
    Letter_Assign(&self->held, PocketsLetters_LetterAt(&self->letters, index));
    PocketsLetters_ClearPlace(&self->letters, index);
}
CLEAN_AS(func_ov106_0229cd88, MailboxScene_PickUpLetter)

/* func_ov106_0229cde4: the held letter drawn where the glide is. */
void MailboxScene_FollowGlide(MailboxScene *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov106_0229cde4, MailboxScene_FollowGlide)

/* func_ov106_0229ce0c: the held letter drawn at the cursor sprite's frame, 2 left and 4 up. */
void MailboxScene_FollowCursorSprite(MailboxScene *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov106_0229ce0c, MailboxScene_FollowCursorSprite)

/* func_ov106_0229ce38: the held letter drawn at the touch plus the grab's offset. */
void MailboxScene_FollowTouch(MailboxScene *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov106_0229ce38, MailboxScene_FollowTouch)

/* func_ov106_0229ce64: the held letter drawn by the letters object, unless hidden. */
void MailboxScene_DrawHeld(MailboxScene *self)
{
    if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_HELD_HIDDEN) != 0) {
        return;
    }
    if (self->held_kind == MAILBOX_SCENE_HELD_LETTER) {
        PocketsLetters_DrawHeld(&self->letters, self->held_x, self->held_y, &self->held);
    }
}
CLEAN_AS(func_ov106_0229ce64, MailboxScene_DrawHeld)

/* func_ov106_0229cea8: the popup queued to tell of the cursor's letter place, when it holds a
 * letter (MailboxScene_PlaceIsEmpty is 0); cleared on any other place. */
void MailboxScene_UpdatePopup(MailboxScene *self)
{
    if (mbx_is_letter_place(self, self->cursor)) {
        if (MailboxScene_PlaceIsEmpty(self, self->cursor) != 0) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov106_0229cea8, MailboxScene_UpdatePopup)

/* func_ov106_0229cf0c: the popup's window put 0x6d left and 0x78 up of its place (8 more up
 * when state flag 2 is set), and filled by the letters object for a letter place. */
void MailboxScene_PlacePopup(MailboxScene *self)
{
    int x = MailboxScene_PlaceX(self, self->popup_place) - 0x6d;
    int y = MailboxScene_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    /* The popup's base is main's sliding window (popup.h). */
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (mbx_is_letter_place(self, self->popup_place)) {
        int index = mbx_letter_index(self, self->popup_place);
        PocketsLetters_ShowPlaceText(&self->letters, &self->popup, index);
    }
}
CLEAN_AS(func_ov106_0229cf0c, MailboxScene_PlacePopup)

/* func_ov106_0229cf8c: whether the touch at data_021f6c60/5c is more than 8 pixels from the
 * one at data_021f6c58/54, in x or in y. */
static int mbx_distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

int MailboxScene_TouchMoved(MailboxScene *self)
{
    (void) self;
    return mbx_distance(data_021f6c60, data_021f6c58) > 8 || mbx_distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov106_0229cf8c, MailboxScene_TouchMoved)

/* func_ov106_0229cfd0: a letter place highlighted by the letters object. */
void MailboxScene_HighlightPlace(MailboxScene *self, int place)
{
    if (!mbx_is_letter_place(self, place)) {
        return;
    }
    PocketsLetters_MarkPlace(&self->letters, mbx_letter_index(self, place));
}
CLEAN_AS(func_ov106_0229cfd0, MailboxScene_HighlightPlace)

/* func_ov106_0229d00c: the highlights of the grid and the letters cleared. */
void MailboxScene_ClearHighlights(MailboxScene *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov106_0229d00c, MailboxScene_ClearHighlights)

/* func_ov106_0229d028: a letter place lifted in the letters object (the grid's lift dropped);
 * any other place drops both (MailboxScene_ClearSelection). */
void MailboxScene_SelectPlace(MailboxScene *self, int place)
{
    if (mbx_is_letter_place(self, place)) {
        int index = mbx_letter_index(self, place);
        PocketsLetters_Lift(&self->letters, index);
        PocketsGrid_Unlift(&self->grid);
    } else {
        MailboxScene_ClearSelection(self);
    }
}
CLEAN_AS(func_ov106_0229d028, MailboxScene_SelectPlace)

/* func_ov106_0229d074: the lifts of the grid and the letters dropped. */
void MailboxScene_ClearSelection(MailboxScene *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov106_0229d074, MailboxScene_ClearSelection)

/* func_ov106_0229d090: whether a letter place holds no letter (by the letters object); other
 * places count as empty. */
int MailboxScene_PlaceIsEmpty(MailboxScene *self, int place)
{
    if (mbx_is_letter_place(self, place)) {
        return PocketsLetters_IsEmpty(&self->letters, mbx_letter_index(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov106_0229d090, MailboxScene_PlaceIsEmpty)

/* func_ov106_0229d0d0: whether a carried letter is dimmed by the letters object
 * (MailboxScene_DimCarriedLetters); 0 for any other place. */
int MailboxScene_PlaceIsDimmed(MailboxScene *self, int place)
{
    if (mbx_is_carried(self, place)) {
        return PocketsLetters_IsDimmed(&self->letters, mbx_letter_index(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov106_0229d0d0, MailboxScene_PlaceIsDimmed)

/* func_ov106_0229d104: the grid's places 0 to 14 dimmed, and the carried letters of the states
 * of flag 4 (PocketsLetters_DimByState). */
void MailboxScene_DimCarriedLetters(MailboxScene *self)
{
    PocketsGrid_DimPlaces(&self->grid, 0, 0xe);
    PocketsLetters_DimByState(&self->letters, 4);
}
CLEAN_AS(func_ov106_0229d104, MailboxScene_DimCarriedLetters)

/* func_ov106_0229d128: the y of `place`: a letter's by the letters object less 0x10, 0xb6 for
 * MAILBOX_SCENE_BELOW, else 0. */
int MailboxScene_PlaceY(MailboxScene *self, int place)
{
    if (mbx_is_letter_place(self, place)) {
        return PocketsLetters_PlaceY(&self->letters, mbx_letter_index(self, place)) - 0x10;
    }
    if (place == MAILBOX_SCENE_BELOW) {
        return 0xb6;
    }
    return 0;
}
CLEAN_AS(func_ov106_0229d128, MailboxScene_PlaceY)

/* func_ov106_0229d170: the x of `place`: a letter's by the letters object, 0xbc for
 * MAILBOX_SCENE_BELOW, else 0. */
int MailboxScene_PlaceX(MailboxScene *self, int place)
{
    if (mbx_is_letter_place(self, place)) {
        return PocketsLetters_PlaceX(&self->letters, mbx_letter_index(self, place));
    }
    if (place == MAILBOX_SCENE_BELOW) {
        return 0xbc;
    }
    return 0;
}
CLEAN_AS(func_ov106_0229d170, MailboxScene_PlaceX)

/* func_ov106_0229d1b8: for a letter in state 2 or 3, its paper (as the item of four sheets of
 * it, ItemCode_MakePile) marked in the current player's item record. QUIRK: the state is asked
 * for again when it is not 2. */
void MailboxScene_RecordPaper(MailboxScene *self, Letter *letter)
{
    (void) self;
    if (Letter_State(letter) == 2 || Letter_State(letter) == 3) {
        u8 *player = PlayerRecords_Current();
        ItemCode paper = ItemCode_MakePile(Letter_Paper(letter), 4);
        ItemRecord_SetBit((ItemRecord *) (void *) PlayerRecord_ItemRecord(player), &paper, 0, 1);
    }
}
CLEAN_AS(func_ov106_0229d1b8, MailboxScene_RecordPaper)

/* func_ov106_0229d20c: the letter of a letter place (the letters object's), else NULL. */
Letter *MailboxScene_PlaceLetter(MailboxScene *self, int place)
{
    if (mbx_is_letter_place(self, place)) {
        return PocketsLetters_LetterAt(&self->letters, mbx_letter_index(self, place));
    }
    return NULL;
}
CLEAN_AS(func_ov106_0229d20c, MailboxScene_PlaceLetter)

/* func_ov106_0229d24c: a copy of `letter` put at a letter place by the letters object; put among
 * the carried letters, its paper is recorded (MailboxScene_RecordPaper). */
void MailboxScene_PutLetterAt(MailboxScene *self, int place, Letter *letter)
{
    if (mbx_is_letter_place(self, place)) {
        PocketsLetters_SetPlace(&self->letters, mbx_letter_index(self, place), letter);
        if (mbx_is_carried(self, place)) {
            MailboxScene_RecordPaper(self, letter);
        }
    }
}
CLEAN_AS(func_ov106_0229d24c, MailboxScene_PutLetterAt)

/* func_ov106_0229d29c: the held letter put down at `place`; a letter there is copied aside
 * (`swapped`) and put at the held letter's place (`held_from`) first. Always 1. */
int MailboxScene_PutHeldLetterAt(MailboxScene *self, int place)
{
    if (MailboxScene_PlaceIsEmpty(self, place) == 0) {
        Letter_Assign(&self->swapped, MailboxScene_PlaceLetter(self, place));
        MailboxScene_PutLetterAt(self, self->held_from, &self->swapped);
    }
    MailboxScene_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov106_0229d29c, MailboxScene_PutHeldLetterAt)

/* func_ov106_0229d2e4: the letter place under the touch at (x, y), by the letters object (the
 * carried letters first, then the mailbox's); with `with_letter`, only one holding a letter.
 * MAILBOX_SCENE_NO_PLACE for none. QUIRK: the scene's address is handed to the byte the place
 * lookup (MailboxScene_LetterPlace) takes first and ignores. */
int MailboxScene_LetterPlaceAtTouch(MailboxScene *self, int x, int y, int with_letter)
{
    int index = PocketsLetters_PocketAtTouch(&self->letters, x, y);
    if (index == POCKETS_LETTERS_NO_PLACE) {
        index = PocketsLetters_TenAt23AtTouch(&self->letters, x, y);
    }
    if (index == POCKETS_LETTERS_NO_PLACE) {
        return MAILBOX_SCENE_NO_PLACE;
    }
    if (with_letter != 0 && PocketsLetters_IsEmpty(&self->letters, index) != 0) {
        return MAILBOX_SCENE_NO_PLACE;
    }
    return MailboxScene_LetterPlace((unsigned char) (uintptr_t) self, (unsigned char) index);
}
CLEAN_AS(func_ov106_0229d2e4, MailboxScene_LetterPlaceAtTouch)

/* func_ov106_0229d340: the place of the letters object's letter `index` (0-9 carried, 0x23-0x2c
 * the mailbox's), else MAILBOX_SCENE_NO_PLACE. The first byte is not read. */
u8 MailboxScene_LetterPlace(u8 unused, u8 index)
{
    (void) unused;
    if (index <= 9) {
        return (u8) (index + MAILBOX_SCENE_CARRIED_FIRST);
    }
    if (index >= 0x23 && index <= 0x2c) {
        return (u8) (index - 0x23 + MAILBOX_SCENE_MAILBOX_FIRST);
    }
    return MAILBOX_SCENE_NO_PLACE;
}
CLEAN_AS(func_ov106_0229d340, MailboxScene_LetterPlace)

/* func_ov106_0229d360: the letters object's index of a letter place, else 0. */
u8 MailboxScene_LetterIndex(MailboxScene *self, unsigned int place)
{
    (void) self;
    if (place >= MAILBOX_SCENE_CARRIED_FIRST && place <= MAILBOX_SCENE_CARRIED_LAST) {
        return (u8) (place - MAILBOX_SCENE_CARRIED_FIRST);
    }
    if (place >= MAILBOX_SCENE_MAILBOX_FIRST && place <= MAILBOX_SCENE_MAILBOX_LAST) {
        return (u8) (place - MAILBOX_SCENE_MAILBOX_FIRST + 0x23);
    }
    return 0;
}
CLEAN_AS(func_ov106_0229d360, MailboxScene_LetterIndex)

/* func_ov106_0229d384 */
int MailboxScene_IsBelowPlace(MailboxScene *self, int place)
{
    (void) self;
    return place == MAILBOX_SCENE_BELOW;
}
CLEAN_AS(func_ov106_0229d384, MailboxScene_IsBelowPlace)

/* func_ov106_0229d390 */
int MailboxScene_IsMailboxPlace(MailboxScene *self, unsigned int place)
{
    (void) self;
    return place >= MAILBOX_SCENE_MAILBOX_FIRST && place <= MAILBOX_SCENE_MAILBOX_LAST;
}
CLEAN_AS(func_ov106_0229d390, MailboxScene_IsMailboxPlace)

/* func_ov106_0229d3a0 */
int MailboxScene_IsCarriedPlace(MailboxScene *self, unsigned int place)
{
    (void) self;
    return place >= MAILBOX_SCENE_CARRIED_FIRST && place <= MAILBOX_SCENE_CARRIED_LAST;
}
CLEAN_AS(func_ov106_0229d3a0, MailboxScene_IsCarriedPlace)

/* func_ov106_0229d3b0: the layer load task at 0xc0 taken off the main loop's queue and reset. */
void MailboxScene_EndLayerTask(MailboxScene *self)
{
    LayerTask_End((LayerTask *) (void *) self->unk_c0);
}
CLEAN_AS(func_ov106_0229d3b0, MailboxScene_EndLayerTask)

/* The pen (autoload_2/input.c): down, and gone down or up this frame. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The pad (autoload_2/input.h) and the buttons read in `pressed`. */
extern PadState data_021fbe40;
#define MAILBOX_SCENE_PAD_A 0x0001
#define MAILBOX_SCENE_PAD_B 0x0002
#define MAILBOX_SCENE_PAD_START 0x0008
#define MAILBOX_SCENE_PAD_Y 0x0800

/* The panel's two buttons offered under a message (`panel_button` 0 and 1), the selected one,
 * and the label button's anchor the cursor sprite points at. */
#define MAILBOX_SCENE_PANEL_BUTTON_3 3
#define MAILBOX_SCENE_PANEL_BUTTON_4 4
#define MAILBOX_SCENE_PANEL_SELECTED (-1)
#define MAILBOX_SCENE_LABEL_ANCHOR 1

/* The message shown when no carried letter is free (MailboxScene_TakeNextLetter). */
#define MAILBOX_SCENE_MESSAGE_CARRIED_FULL 6

/* The sub state runner (the table of member functions, Obj_ov106_0229f6e0::func_ov106_0229ef8c). */
extern void _ZN18Obj_ov106_0229f6e019func_ov106_0229ef8cEv(MailboxScene *self);

static CellLayerSprite *mbx_cursor_cells(MailboxScene *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The pen went down this frame. */
static int mbx_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The value kept with choice row `row` (ChoiceEntries.values), read as the ROM does at
 * 0x26f1 + row. */
static u8 mbx_entry_value(MailboxScene *self, int row)
{
    const u8 *bytes = (const u8 *) self;
    return bytes[offsetof(MailboxScene, entries) + offsetof(ChoiceEntries, values) + (size_t) row];
}

/* A choice row picked with the sound of a pick, except for the row of action 2 (sound 0x24
 * instead); its action kept; sub state 0x17. */
static void mbx_pick_choice_row(MailboxScene *self, int row)
{
    self->action = mbx_entry_value(self, row);
    int with_sound = 1;
    if (self->action == MAILBOX_SCENE_ACTION_PICK_UP) {
        with_sound = 0;
        SoundSys_PlaySe(0x24);
    }
    PagedChoice_PickRowWithSound(mbx_choice(self), row, with_sound);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_CLOSE);
}

/* func_ov106_0229d3bc: sound 0x28, the panel's button 4 selected, sub state 0x1f, button 4
 * chosen. */
void MailboxScene_PressPanelButton4(MailboxScene *self)
{
    SoundSys_PlaySe(0x28);
    ButtonPanel_Select(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_4);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PANEL_PRESSED);
    self->panel_button = 1;
}
CLEAN_AS(func_ov106_0229d3bc, MailboxScene_PressPanelButton4)

/* func_ov106_0229d3e8: sound 0x27, the panel's button 3 selected, sub state 0x1f, button 3
 * chosen. */
void MailboxScene_PressPanelButton3(MailboxScene *self)
{
    SoundSys_PlaySe(0x27);
    ButtonPanel_Select(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_3);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PANEL_PRESSED);
    self->panel_button = 0;
}
CLEAN_AS(func_ov106_0229d3e8, MailboxScene_PressPanelButton3)

/* func_ov106_0229d414: message `message` of the error messages talked, sub state 0x1a, a wipe
 * started. (The ROM first copies data_021f43ec into the message's byte, then overwrites it.) */
void MailboxScene_ShowMessage(MailboxScene *self, char message)
{
    u8 text = (u8) message;
    ErrorMessage_StartTalk(&self->error, &text, 1);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_MESSAGE_UP);
    MenuScene_StartWipe(mbx_scene(self), 0, 0);
}
CLEAN_AS(func_ov106_0229d414, MailboxScene_ShowMessage)

/* func_ov106_0229d454: the place of the mailbox's first letter that holds one (its state is not
 * 0), else MAILBOX_SCENE_NO_PLACE. */
int MailboxScene_FirstMailboxLetterPlace(MailboxScene *self)
{
    for (int i = 0; i < MAILBOX_SCENE_LETTERS; i++) {
        if (Letter_State(&self->mailbox[i]) != 0) {
            return (u8) (i + MAILBOX_SCENE_MAILBOX_FIRST);
        }
    }
    return MAILBOX_SCENE_NO_PLACE;
}
CLEAN_AS(func_ov106_0229d454, MailboxScene_FirstMailboxLetterPlace)

/* func_ov106_0229d48c: the carried place of the current player's first free letter slot (their
 * pockets', not the letters object's), else MAILBOX_SCENE_NO_PLACE. */
int MailboxScene_FreeCarriedPlace(MailboxScene *self)
{
    (void) self;
    int index = CurrentPockets_FreeLetterIndex();
    if (index == -1) {
        return MAILBOX_SCENE_NO_PLACE;
    }
    return (u8) (index + MAILBOX_SCENE_CARRIED_FIRST);
}
CLEAN_AS(func_ov106_0229d48c, MailboxScene_FreeCarriedPlace)

/* func_ov106_0229d4ac: the letter at `from` picked up and drawn there, then glided to `to` in 4
 * steps. */
void MailboxScene_HoldAndGlide(MailboxScene *self, int from, int to)
{
    MailboxScene_PickUpLetter(self, from);
    self->held_x = MailboxScene_PlaceX(self, from);
    self->held_y = MailboxScene_PlaceY(self, from);
    MailboxScene_GlideHeldTo(self, to, 4);
}
CLEAN_AS(func_ov106_0229d4ac, MailboxScene_HoldAndGlide)

/* func_ov106_0229d4e4: the dragged letter let go with the touch at `x`: one from the mailbox
 * dropped over the carried letters (x from 0xc0) goes to the player's first free letter slot;
 * else, or when there is none, it glides back to `place`. 4 steps. */
void MailboxScene_DropHeldAtTouch(MailboxScene *self, int place, int x)
{
    int to = MAILBOX_SCENE_NO_PLACE;
    if (x >= 0xc0 && MailboxScene_IsMailboxPlace(self, (unsigned int) place)) {
        to = MailboxScene_FreeCarriedPlace(self);
    }
    if (to != MAILBOX_SCENE_NO_PLACE) {
        place = to;
    }
    MailboxScene_GlideHeldTo(self, place, 4);
}
CLEAN_AS(func_ov106_0229d4e4, MailboxScene_DropHeldAtTouch)

/* func_ov106_0229d518: the held letter glides from where it is drawn to `place` (kept as its
 * place, `held_from`) in `steps` steps, the first taken now. Sub state 0x15 follows it. */
void MailboxScene_GlideHeldTo(MailboxScene *self, int place, int steps)
{
    self->held_from = (u8) place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = MailboxScene_PlaceX(self, place);
    int y = MailboxScene_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    MailboxScene_FollowGlide(self);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov106_0229d518, MailboxScene_GlideHeldTo)

/* func_ov106_0229d57c: the letter at `place` picked up with the cursor, the popup hidden; when it
 * is held, the sub state to go back to is 8. It follows the cursor sprite; sound 0xd. */
void MailboxScene_PickUpWithCursor(MailboxScene *self, int place)
{
    self->held_from = (u8) place;
    Popup_Hide(&self->popup, 1);
    MailboxScene_PickUpLetter(self, place);
    if (self->held_kind == MAILBOX_SCENE_HELD_LETTER) {
        self->return_state = MAILBOX_SCENE_SUB_HOLD;
    }
    MailboxScene_FollowCursorSprite(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov106_0229d57c, MailboxScene_PickUpWithCursor)

/* func_ov106_0229d5c4: the letter at `place` picked up with the touch, the popup hidden; when it
 * is held, sub state 4 drags it. It follows the touch; sound 0xd. */
void MailboxScene_PickUpWithTouch(MailboxScene *self, int place)
{
    self->held_from = (u8) place;
    Popup_Hide(&self->popup, 1);
    MailboxScene_PickUpLetter(self, place);
    if (self->held_kind == MAILBOX_SCENE_HELD_LETTER) {
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_DRAG);
    }
    MailboxScene_FollowTouch(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov106_0229d5c4, MailboxScene_PickUpWithTouch)

/* func_ov106_0229d60c: `place` touched: sub state 1, the offset from the touch to the place
 * kept, the popup told of the place and shown, its choice opening in 2 frames; the letter may be
 * dragged (MAILBOX_SCENE_FLAG_DRAGGABLE, sound 0xc) unless it is dimmed. */
void MailboxScene_TouchPlace(MailboxScene *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = MailboxScene_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = MailboxScene_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = 2;
    if (MailboxScene_PlaceIsDimmed(self, place)) {
        MailboxScene_ClearFlags(self, MAILBOX_SCENE_FLAG_DRAGGABLE);
    } else {
        MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_DRAGGABLE);
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov106_0229d60c, MailboxScene_TouchPlace)

/* func_ov106_0229d6a4: the panel's buttons 3 and 4 offered, to the touch while state flag 2 is
 * clear, else to the keys. */
void MailboxScene_OfferPanelButtons(MailboxScene *self)
{
    if (StateFlags_IsClear2()) {
        MailboxScene_OfferPanelButtonsByTouch(self);
    } else {
        MailboxScene_OfferPanelButtonsByKeys(self);
    }
}
CLEAN_AS(func_ov106_0229d6a4, MailboxScene_OfferPanelButtons)

/* func_ov106_0229d6c4: the key repeat reset, button 4 chosen and the cursor sprite shown on it
 * (animation 1, updated); sub state 0x1d. */
void MailboxScene_OfferPanelButtonsByKeys(MailboxScene *self)
{
    MenuScene_ResetKeyRepeat(mbx_scene(self));
    self->panel_button = 1;
    Glider_SetAnim(&self->cursor_sprite, 1);
    mbx_update_cursor_sprite(&self->cursor_sprite);
    int x = ButtonPanel_ButtonX(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_4);
    int y = ButtonPanel_ButtonY(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_4);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PANEL_BY_KEYS);
}
CLEAN_AS(func_ov106_0229d6c4, MailboxScene_OfferPanelButtonsByKeys)

/* func_ov106_0229d724: the cursor sprite hidden; sub state 0x1c. */
void MailboxScene_OfferPanelButtonsByTouch(MailboxScene *self)
{
    MailboxScene_HideCursorSprite(self);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PANEL_BY_TOUCH);
}
CLEAN_AS(func_ov106_0229d724, MailboxScene_OfferPanelButtonsByTouch)

/* func_ov106_0229d73c: the action ends: back to sub state 0 with the cursor sprite hidden while
 * state flag 2 is clear, else to sub state 7 with it at the cursor. */
void MailboxScene_EndAction(MailboxScene *self)
{
    if (StateFlags_IsClear2()) {
        MailboxScene_EndActionHidden(self);
    } else {
        MailboxScene_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov106_0229d73c, MailboxScene_EndAction)

/* func_ov106_0229d75c: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 7 and the cursor's place selected. */
void MailboxScene_EndActionAtCursor(MailboxScene *self)
{
    self->popup_place = MAILBOX_SCENE_NO_PLACE;
    MailboxScene_ShowCursorAtCursor(self);
    MenuScene_ResetKeyRepeat(mbx_scene(self));
    MailboxScene_UpdatePopup(self);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_BROWSE);
    MailboxScene_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov106_0229d75c, MailboxScene_EndActionAtCursor)

/* func_ov106_0229d790 */
void MailboxScene_EndActionHidden(MailboxScene *self)
{
    MailboxScene_HideCursorSprite(self);
    MailboxScene_ClearSelection(self);
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov106_0229d790, MailboxScene_EndActionHidden)

/* func_ov106_0229d7ac (sub state 0x26, after MailboxScene_PickUpSlotLetter): once the letters
 * object's pick-up is over, the held letter is let go (nothing held) and the action ends. */
void MailboxScene_WaitLetGo(MailboxScene *self)
{
    if (PocketsLetters_StepPickUp(&self->letters)) {
        self->held_kind = MAILBOX_SCENE_HELD_NONE;
        MailboxScene_EndAction(self);
    }
}
CLEAN_AS(func_ov106_0229d7ac, MailboxScene_WaitLetGo)

/* func_ov106_0229d7d4 (sub state 0x25): the letter taken from the mailbox follows its glide;
 * when it is over, the letter is put at its place (`held_from`) and the next one is taken (sub
 * state 0x24), sound 0xe. */
void MailboxScene_StepTakenLetterGlide(MailboxScene *self)
{
    if (Glide_Step(&self->glide) != 0) {
        MailboxScene_PutHeldAt(self, self->held_from);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_TAKE_NEXT);
        PocketsSound_Play0e();
    } else {
        MailboxScene_FollowGlide(self);
    }
}
CLEAN_AS(func_ov106_0229d7d4, MailboxScene_StepTakenLetterGlide)

/* func_ov106_0229d810 (sub state 0x24): the mailbox's first letter glides to the player's first
 * free letter slot (sub state 0x25). With no letter left in the mailbox, the cursor goes to
 * MAILBOX_SCENE_BELOW and the action ends; with no free slot, message 6 is shown. */
void MailboxScene_TakeNextLetter(MailboxScene *self)
{
    int from = MailboxScene_FirstMailboxLetterPlace(self);
    if (from == MAILBOX_SCENE_NO_PLACE) {
        self->cursor = MAILBOX_SCENE_BELOW;
        MailboxScene_EndAction(self);
        return;
    }
    int to = MailboxScene_FreeCarriedPlace(self);
    if (to == MAILBOX_SCENE_NO_PLACE) {
        MailboxScene_ShowMessage(self, MAILBOX_SCENE_MESSAGE_CARRIED_FULL);
    } else {
        MailboxScene_HoldAndGlide(self, from, to);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_TAKE_GLIDE);
    }
}
CLEAN_AS(func_ov106_0229d810, MailboxScene_TakeNextLetter)

/* Places the cursor sprite (when shown) on the selected panel button, offset by its press's
 * frame. */
static void mbx_follow_selected_press(MailboxScene *self)
{
    if (CellLayerSprite_AnimNumber(mbx_cursor_cells(self)) != 0) {
        int frame = ButtonPanel_SelectedPressFrame(&self->panel);
        int x = ButtonPanel_ButtonX(&self->panel, MAILBOX_SCENE_PANEL_SELECTED);
        int y = ButtonPanel_ButtonY(&self->panel, MAILBOX_SCENE_PANEL_SELECTED);
        Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
    }
}

/* func_ov106_0229d860 (sub state 0x23, after MailboxScene_PressPanelButton9): while the selected
 * panel button's press plays, the cursor sprite (when shown) follows it; after, the sprite is
 * hidden, state 4 (written directly), MAILBOX_SCENE_FLAG_100 cleared and phase 1. */
void MailboxScene_FollowPanelPress(MailboxScene *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        mbx_follow_selected_press(self);
    } else {
        MailboxScene_HideCursorSprite(self);
        self->base.state = 4;
        MailboxScene_ClearFlags(self, MAILBOX_SCENE_FLAG_100);
        MenuScene_SetPhase(mbx_scene(self), 1);
    }
}
CLEAN_AS(func_ov106_0229d860, MailboxScene_FollowPanelPress)

/* func_ov106_0229d8e0 (sub state 0x22): while the label button's animation plays, the cursor
 * sprite (when shown) follows its anchor; after, the sprite is hidden, state 9 and phase 1. */
void MailboxScene_FollowLabelPress(MailboxScene *self)
{
    if (LabelButton_StepAnimation(&self->button) != 0) {
        if (CellLayerSprite_AnimNumber(mbx_cursor_cells(self)) != 0) {
            int x = LabelButton_AnchorX(&self->button, MAILBOX_SCENE_LABEL_ANCHOR);
            int y = LabelButton_AnchorY(&self->button, MAILBOX_SCENE_LABEL_ANCHOR);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
        }
    } else {
        MailboxScene_HideCursorSprite(self);
        MenuScene_SetState(mbx_scene(self), 9);
        MenuScene_SetPhase(mbx_scene(self), 1);
    }
}
CLEAN_AS(func_ov106_0229d8e0, MailboxScene_FollowLabelPress)

/* func_ov106_0229d948 (sub state 0x21): the wipe back after a message, its offset kept; when
 * done, the action ends. */
void MailboxScene_EndMessageWipe(MailboxScene *self)
{
    int done = MenuScene_StepWipeBack(mbx_scene(self), -1);
    self->wipe_y = MenuScene_WipeOffsetY(mbx_scene(self));
    if (done != 0) {
        MailboxScene_EndAction(self);
    }
}
CLEAN_AS(func_ov106_0229d948, MailboxScene_EndMessageWipe)

/* func_ov106_0229d978 (sub state 0x20): once the message has closed and the wipe is done (both
 * stepped every frame, the wipe's offset kept), the panel's flag 2 cleared; after button 3 a
 * covered wipe back with the panel's layout 5 and message 0x88 (sub state 0x21), after button 4
 * the panel's layout cleared, state 4 and phase 1. */
void MailboxScene_CloseMessage(MailboxScene *self)
{
    int closed = ErrorMessage_WaitClosed(&self->error);
    int wiped = MenuScene_StepWipe(mbx_scene(self), -1);
    self->wipe_y = MenuScene_WipeOffsetY(mbx_scene(self));
    if ((closed & wiped) == 0) {
        return;
    }
    ButtonPanel_ClearFlag2(&self->panel);
    if (self->panel_button == 0) {
        MenuScene_StartWipeCovered(mbx_scene(self), 0, 0);
        ButtonPanel_SetLayout5(&self->panel, 0x88);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_MESSAGE_WIPE_END);
    } else {
        ButtonPanel_ClearLayout(&self->panel);
        MenuScene_SetState(mbx_scene(self), 4);
        MenuScene_SetPhase(mbx_scene(self), 1);
    }
}
CLEAN_AS(func_ov106_0229d978, MailboxScene_CloseMessage)

/* func_ov106_0229d9fc (sub state 0x1f): while the selected panel button's press plays, the
 * cursor sprite (when shown) follows it; after, the sprite is hidden, sub state 0x20, a wipe
 * started and the message closed. */
void MailboxScene_FollowMessagePanelPress(MailboxScene *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        mbx_follow_selected_press(self);
    } else {
        MailboxScene_HideCursorSprite(self);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_MESSAGE_CLOSE);
        MenuScene_StartWipe(mbx_scene(self), 0, 0);
        ErrorMessage_Close(&self->error);
    }
}
CLEAN_AS(func_ov106_0229d9fc, MailboxScene_FollowMessagePanelPress)

/* func_ov106_0229da80 (sub state 0x1e): once the cursor sprite's animation has ended, sub state
 * 0x1f and the chosen panel button selected (button 4 with sound 0x28, button 3 with 0x27). */
void MailboxScene_PressChosenPanelButton(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self)) == 0) {
        return;
    }
    MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PANEL_PRESSED);
    if (self->panel_button != 0) {
        ButtonPanel_Select(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_4);
        SoundSys_PlaySe(0x28);
    } else {
        ButtonPanel_Select(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_3);
        SoundSys_PlaySe(0x27);
    }
}
CLEAN_AS(func_ov106_0229da80, MailboxScene_PressChosenPanelButton)

/* func_ov106_0229dad4 (sub state 0x1d): panel buttons 3 and 4 by the keys. A close of the menu
 * presses button 4 (the sprite hidden); a touch gives them to the touch; A presses the chosen
 * one (sub state 0x1e, once the sprite's second animation of its set has played), B presses
 * button 4 and START button 3 at once; left chooses button 3, right button 4 (`panel_button` 0
 * or 1), the cursor sprite easing to it. */
void MailboxScene_ChoosePanelButtonByKeys(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_HideCursorSprite(self);
        MailboxScene_PressPanelButton4(self);
        return;
    }
    if (MenuScene_TakeTouch(mbx_scene(self))) {
        MailboxScene_OfferPanelButtonsByTouch(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & MAILBOX_SCENE_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PANEL_PRESS);
        return;
    }
    if (pressed & MAILBOX_SCENE_PAD_B) {
        MailboxScene_HideCursorSprite(self);
        MailboxScene_PressPanelButton4(self);
        return;
    }
    if (pressed & MAILBOX_SCENE_PAD_START) {
        MailboxScene_HideCursorSprite(self);
        MailboxScene_PressPanelButton3(self);
        return;
    }

    u8 before = self->panel_button;
    int keys = (int) MenuScene_LatchRepeatedKeys(mbx_scene(self));
    if (KeyRepeat_HasLeft(keys)) {
        if (self->panel_button != 0) {
            self->panel_button--;
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (self->panel_button < 1) {
            self->panel_button++;
        }
    }
    if (before != self->panel_button) {
        int button = self->panel_button != 0 ? MAILBOX_SCENE_PANEL_BUTTON_4 : MAILBOX_SCENE_PANEL_BUTTON_3;
        int x = ButtonPanel_ButtonX(&self->panel, button);
        int y = ButtonPanel_ButtonY(&self->panel, button);
        MailboxScene_EaseCursorSpriteTo(self, x, y);
    }
}
CLEAN_AS(func_ov106_0229dad4, MailboxScene_ChoosePanelButtonByKeys)

/* func_ov106_0229dc04 (sub state 0x1c): panel buttons 3 and 4 by the touch. A button gives them
 * to the keys; the pen going down on button 3, else on button 4, presses it. QUIRK: a close of
 * the menu presses button 4 and goes on with the rest, so the same frame may hand the buttons to
 * the keys or press a touched one after it. */
void MailboxScene_ChoosePanelButtonByTouch(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_PressPanelButton4(self);
    }
    if (MenuScene_TakeButtons(mbx_scene(self), 1)) {
        MailboxScene_OfferPanelButtonsByKeys(self);
        return;
    }
    if (!mbx_pen_pressed()) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_3)) {
        MailboxScene_PressPanelButton3(self);
    } else if (ButtonPanel_IsTouched(&self->panel, MAILBOX_SCENE_PANEL_BUTTON_4)) {
        MailboxScene_PressPanelButton4(self);
    }
}
CLEAN_AS(func_ov106_0229dc04, MailboxScene_ChoosePanelButtonByTouch)

/* func_ov106_0229dc80 (sub state 0x1b): the covered wipe back under the message, its offset
 * kept; when done, the panel's buttons are offered. */
void MailboxScene_MessageWipeBack(MailboxScene *self)
{
    int done = MenuScene_StepWipeBack(mbx_scene(self), -1);
    self->wipe_y = MenuScene_WipeOffsetY(mbx_scene(self));
    if (done != 0) {
        MailboxScene_OfferPanelButtons(self);
    }
}
CLEAN_AS(func_ov106_0229dc80, MailboxScene_MessageWipeBack)

/* func_ov106_0229dcb0 (sub state 0x1a): once the message is up and the wipe is done (both stepped
 * every frame, the wipe's offset kept), sub state 0x1b with a covered wipe, the panel's layout 10
 * and its flag 2. */
void MailboxScene_WaitMessageUp(MailboxScene *self)
{
    int up = ErrorMessage_WaitUp(&self->error);
    int wiped = MenuScene_StepWipe(mbx_scene(self), -1);
    self->wipe_y = MenuScene_WipeOffsetY(mbx_scene(self));
    if ((up & wiped) != 0) {
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_MESSAGE_WIPE_BACK);
        MenuScene_StartWipeCovered(mbx_scene(self), 0, 0);
        ButtonPanel_SetLayout10(&self->panel);
        ButtonPanel_SetFlag2(&self->panel);
    }
}
CLEAN_AS(func_ov106_0229dcb0, MailboxScene_WaitMessageUp)

/* func_ov106_0229dd10 (sub state 0x19): once the error message is done, back to the sub state
 * kept, the cursor sprite's window flag set. */
void MailboxScene_WaitError(MailboxScene *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        MenuScene_SetSubState(mbx_scene(self), self->return_state);
        CellLayerSprite_SetWindow(mbx_cursor_cells(self));
    }
}
CLEAN_AS(func_ov106_0229dd10, MailboxScene_WaitError)

/* func_ov106_0229dd44 (sub state 0x18): the action picked runs once the choice is idle. */
void MailboxScene_RunActionWhenIdle(MailboxScene *self)
{
    if (PagedChoice_IsIdle(mbx_choice(self)) != 0) {
        MailboxScene_RunAction(self);
    }
}
CLEAN_AS(func_ov106_0229dd44, MailboxScene_RunActionWhenIdle)

/* func_ov106_0229dd64 (sub state 0x17): once the delay after the pick has run out, the choice
 * asked to close, the popup hidden, the cursor sprite (when shown) put back at the cursor; sub
 * state 0x18. */
void MailboxScene_CloseChoice(MailboxScene *self)
{
    if (PagedChoice_CountDown(mbx_choice(self)) != 0) {
        PagedChoice_RequestClose(mbx_choice(self), 0);
        Popup_Hide(&self->popup, 1);
        if (CellLayerSprite_AnimNumber(mbx_cursor_cells(self)) != 0) {
            MailboxScene_PlaceCursorSprite(self);
        }
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_RUN);
    }
}
CLEAN_AS(func_ov106_0229dd64, MailboxScene_CloseChoice)

/* func_ov106_0229ddb4 (sub state 0x16): once the choice is shown, it is run by the keys (the
 * cursor sprite at its default row, sub state 0x0b) when state flag 2 is set, else by the touch
 * (sub state 6). */
void MailboxScene_WaitChoiceShown(MailboxScene *self)
{
    if (PagedChoice_IsShown(mbx_choice(self)) != 0) {
        if (StateFlags_Test2()) {
            MailboxScene_PointAtDefaultRow(self);
            MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_BY_KEYS);
        } else {
            MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_BY_TOUCH);
        }
    }
}
CLEAN_AS(func_ov106_0229ddb4, MailboxScene_WaitChoiceShown)

/* func_ov106_0229ddf0 (sub state 0x15): the held letter follows its glide. When the glide is over
 * the letter is put at its place (`held_from`), the action ends, sound 0xe. */
void MailboxScene_StepHeldGlide(MailboxScene *self)
{
    if (Glide_Step(&self->glide) != 0) {
        MailboxScene_PutHeldAt(self, self->held_from);
        MailboxScene_EndAction(self);
        PocketsSound_Play0e();
    } else {
        MailboxScene_FollowGlide(self);
    }
}
CLEAN_AS(func_ov106_0229ddf0, MailboxScene_StepHeldGlide)

/* func_ov106_0229de28 (sub state 0x14): back to the sub state kept once the cursor sprite's
 * animation has ended; once its turn has settled, a hidden held letter is shown again (sound
 * 0xd) and follows the sprite. */
void MailboxScene_FinishSwap(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self))) {
        MenuScene_SetSubState(mbx_scene(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_HELD_HIDDEN)) {
            MailboxScene_ClearFlags(self, MAILBOX_SCENE_FLAG_HELD_HIDDEN);
            PocketsSound_Play0d();
        }
        MailboxScene_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov106_0229de28, MailboxScene_FinishSwap)

/* func_ov106_0229de78 (sub state 0x13): unless the cursor sprite's turn is at its frame 2, the
 * held letter changes places with the one at `target`, the new held letter hidden for now, the
 * popup updated; sub state 0x14. At frame 2, sub state 7. */
void MailboxScene_Swap(MailboxScene *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        MailboxScene_SwapHeldWith(self, self->target);
        MailboxScene_SetFlags(self, MAILBOX_SCENE_FLAG_HELD_HIDDEN);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_SWAP_END);
        MailboxScene_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov106_0229de78, MailboxScene_Swap)

/* func_ov106_0229dec0 (sub state 0x12): while the cursor sprite's turn has not settled, the held
 * letter is put down at `target` when the cursor is on it (the popup updated, sub state 7, sound
 * 0xe), else glided there in 4 steps; once it has, the letter follows the sprite. */
void MailboxScene_PutDown(MailboxScene *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) == 0) {
        u8 target = self->target;
        if (self->cursor == target) {
            MailboxScene_PutHeldLetterAt(self, target);
            MailboxScene_UpdatePopup(self);
            MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_BROWSE);
            PocketsSound_Play0e();
        } else {
            MailboxScene_GlideHeldTo(self, target, 4);
        }
    } else {
        MailboxScene_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov106_0229dec0, MailboxScene_PutDown)

/* func_ov106_0229df14 (sub state 0x11): back to the sub state kept once the cursor sprite's
 * animation has ended; the held letter follows the sprite. */
void MailboxScene_FinishPickUp(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self))) {
        MenuScene_SetSubState(mbx_scene(self), self->return_state);
    }
    MailboxScene_FollowCursorSprite(self);
}
CLEAN_AS(func_ov106_0229df14, MailboxScene_FinishPickUp)

/* func_ov106_0229df40 (sub state 0x10): once the cursor sprite's turn has settled, the letter at
 * the cursor is picked up; sub state 0x11. */
void MailboxScene_PickUpAtCursor(MailboxScene *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        MailboxScene_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_PICK_UP_END);
    }
}
CLEAN_AS(func_ov106_0229df40, MailboxScene_PickUpAtCursor)

/* func_ov106_0229df70 (sub state 0x0f): once the cursor sprite's animation has ended, its set's
 * first animation; sub state 7. */
void MailboxScene_FinishPlacePress(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self))) {
        MailboxScene_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_BROWSE);
    }
}
CLEAN_AS(func_ov106_0229df70, MailboxScene_FinishPlacePress)

/* func_ov106_0229df98 (sub state 0x0e): once the cursor sprite's animation has ended, the place
 * is pressed: MAILBOX_SCENE_BELOW presses panel button 9, other places go to sub state 0x0f. */
void MailboxScene_PressPlace(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self)) == 0) {
        return;
    }
    if (self->cursor == MAILBOX_SCENE_BELOW) {
        MailboxScene_PressPanelButton9(self);
    } else {
        MailboxScene_BeginSubState0f(self);
    }
}
CLEAN_AS(func_ov106_0229df98, MailboxScene_PressPlace)

/* Obj_ov106_0229f6e0::func_ov106_0229dfcc (sub state 0x0d): once the cursor sprite stops moving,
 * back to the sub state kept (the cursor's place selected for sub state 7), which runs at once;
 * the held letter follows the sprite. */
void MailboxScene_WaitCursorSprite(MailboxScene *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(mbx_scene(self), self->return_state);
        if (self->return_state == MAILBOX_SCENE_SUB_BROWSE) {
            MailboxScene_SelectPlace(self, self->cursor);
        }
        _ZN18Obj_ov106_0229f6e019func_ov106_0229ef8cEv(self);
    }
    MailboxScene_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov106_0229f6e019func_ov106_0229dfccEv, MailboxScene_WaitCursorSprite)

/* func_ov106_0229e014 (sub state 0x0c): once the cursor sprite's animation has ended, the
 * choice row it points at is picked. */
void MailboxScene_PickChoiceRow(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self)) == 0) {
        return;
    }
    mbx_pick_choice_row(self, self->choice_row);
}
CLEAN_AS(func_ov106_0229e014, MailboxScene_PickChoiceRow)

/* func_ov106_0229e078 (sub state 0x0b): the choice by the keys. A close of the menu or a touch
 * cancels it; the keys move the row (from row 1 round for the fixed menu), the cursor sprite
 * gliding to it; A plays the sprite's second animation of its set and picks the row (sub state
 * 0x0c), B points at the last row. */
void MailboxScene_ChooseByKeys(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeTouch(mbx_scene(self))) {
        MailboxScene_CancelChoice(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(mbx_scene(self));
    u8 first = (u8) MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_FIXED_MENU);
    if (PagedChoice_MoveCursor(mbx_choice(self), keys, &self->choice_row, first)) {
        MailboxScene_GlideToRow(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & MAILBOX_SCENE_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_PICK);
    } else if (pressed & MAILBOX_SCENE_PAD_B) {
        MailboxScene_PointAtLastRow(self);
    }
}
CLEAN_AS(func_ov106_0229e078, MailboxScene_ChooseByKeys)

/* func_ov106_0229e114 (sub state 0x0a): the label button pressed once the cursor sprite's
 * animation has ended. */
void MailboxScene_WaitLabelPress(MailboxScene *self)
{
    if (CellLayerSprite_IsDone(mbx_cursor_cells(self))) {
        MailboxScene_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov106_0229e114, MailboxScene_WaitLabelPress)

/* func_ov106_0229e134 (sub state 9): the label button by the keys. A close of the menu closes the
 * scene. A hidden cursor sprite is shown on the button's anchor (animation 1); a touch hides it
 * (sub state 5); A or B plays the sprite's second animation of its set, sub state 0x0a. */
void MailboxScene_LabelByKeys(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_CloseOnRequest(self);
        return;
    }
    if (CellLayerSprite_AnimNumber(mbx_cursor_cells(self)) == 0) {
        int x = LabelButton_AnchorX(&self->button, MAILBOX_SCENE_LABEL_ANCHOR);
        int y = LabelButton_AnchorY(&self->button, MAILBOX_SCENE_LABEL_ANCHOR);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        Glider_SetAnim(&self->cursor_sprite, 1);
    }
    if (MenuScene_TakeTouch(mbx_scene(self))) {
        MailboxScene_HideCursorSprite(self);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_LABEL_BY_TOUCH);
    } else if (data_021fbe40.pressed & (MAILBOX_SCENE_PAD_A | MAILBOX_SCENE_PAD_B)) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_LABEL_PRESS);
    }
}
CLEAN_AS(func_ov106_0229e134, MailboxScene_LabelByKeys)

/* func_ov106_0229e1d8 (sub state 8): a held letter moved with the cursor. A close of the menu puts
 * it back at its place and presses panel button 9. A move of the cursor updates the popup and
 * moves the sprite (the popup hidden, its queue kept). A on a letter place puts the letter down
 * there (sub state 0x12) when it is empty, else swaps (sub state 0x13); not on a dimmed place,
 * and a letter of the mailbox is not swapped with a carried one. B sends the letter back to its
 * place (sub state 0x12). Else the letter follows the sprite and a queued popup is shown. */
void MailboxScene_MoveHeldByKeys(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_PutHeldAt(self, self->held_from);
        MailboxScene_HideCursorSprite(self);
        MailboxScene_PressPanelButton9(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (MailboxScene_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(mbx_scene(self)), 1) != 0) {
        MailboxScene_UpdatePopup(self);
        MailboxScene_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & MAILBOX_SCENE_PAD_A) {
        if (MailboxScene_IsCarriedPlace(self, self->cursor) && MailboxScene_IsMailboxPlace(self, self->held_from) &&
            MailboxScene_PlaceIsEmpty(self, self->cursor) == 0) {
            return;
        }
        if (MailboxScene_PlaceIsDimmed(self, self->cursor)) {
            return;
        }
        if (MailboxScene_PlaceIsEmpty(self, self->cursor)) {
            MailboxScene_BeginSubState12(self, self->cursor);
        } else {
            MailboxScene_BeginSubState13(self, self->cursor);
        }
    } else if (pressed & MAILBOX_SCENE_PAD_B) {
        MailboxScene_BeginSubState12(self, self->held_from);
    } else {
        MailboxScene_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov106_0229e1d8, MailboxScene_MoveHeldByKeys)

/* func_ov106_0229e2dc (sub state 7): the cursor moved by the keys, nothing held. A touch ends the
 * action without the sprite. A move updates the popup and moves the sprite (the popup hidden,
 * its queue kept). Unless the cursor's letter is dimmed: A on a letter opens its choice, A below
 * presses the place; Y sends a letter of the mailbox to the player's first free letter slot.
 * Else START or B presses panel button 9, or a queued popup is shown. */
void MailboxScene_BrowseByKeys(MailboxScene *self)
{
    if (MenuScene_TakeTouch(mbx_scene(self))) {
        MailboxScene_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    if (MailboxScene_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(mbx_scene(self)), 0) != 0) {
        MailboxScene_UpdatePopup(self);
        MailboxScene_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if (MailboxScene_PlaceIsDimmed(self, self->cursor) == 0) {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & MAILBOX_SCENE_PAD_A) {
            if (mbx_is_letter_place(self, self->cursor)) {
                if (MailboxScene_PlaceIsEmpty(self, self->cursor) == 0) {
                    MailboxScene_OpenLetterMenu(self, self->cursor, 0);
                }
            } else if (MailboxScene_IsBelowPlace(self, self->cursor)) {
                MailboxScene_BeginSubState0e(self);
            }
            return;
        }
        if (pressed & MAILBOX_SCENE_PAD_Y) {
            if (MailboxScene_IsMailboxPlace(self, self->cursor) && MailboxScene_PlaceIsEmpty(self, self->cursor) == 0) {
                int to = MailboxScene_FreeCarriedPlace(self);
                if (to != MAILBOX_SCENE_NO_PLACE) {
                    MailboxScene_HoldAndGlide(self, self->cursor, to);
                    Popup_Hide(&self->popup, 1);
                }
            }
            return;
        }
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & MAILBOX_SCENE_PAD_START) || (pressed & MAILBOX_SCENE_PAD_B)) {
        MailboxScene_HideCursorSprite(self);
        MailboxScene_PressPanelButton9(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov106_0229e2dc, MailboxScene_BrowseByKeys)

/* func_ov106_0229e430 (sub state 6): the choice by the touch, once shown. A close of the menu or a
 * button cancels it; the pen going down picks the row under it (the last one outside the
 * window), but not the set apart first row of the fixed menu. */
void MailboxScene_ChooseByTouch(MailboxScene *self)
{
    if (PagedChoice_IsShown(mbx_choice(self)) == 0) {
        return;
    }
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeButtons(mbx_scene(self), 1)) {
        MailboxScene_CancelChoice(self);
        return;
    }
    if (!mbx_pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(mbx_choice(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_FIXED_MENU) != 0 && row == 0) {
        return;
    }
    mbx_pick_choice_row(self, row);
}
CLEAN_AS(func_ov106_0229e430, MailboxScene_ChooseByTouch)

/* func_ov106_0229e4fc (sub state 5): the label button by the touch. A close of the menu closes
 * the scene; a button gives it to the keys (sub state 9); a touch on it presses it. */
void MailboxScene_LabelByTouch(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_CloseOnRequest(self);
        return;
    }
    if (MenuScene_TakeButtons(mbx_scene(self), 1)) {
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_LABEL_BY_KEYS);
        return;
    }
    if (LabelButton_IsTouched(&self->button)) {
        MailboxScene_PressLabelButton(self);
    }
}
CLEAN_AS(func_ov106_0229e4fc, MailboxScene_LabelByTouch)

/* func_ov106_0229e544 (sub state 4): the held letter dragged with the touch, the highlights
 * cleared. A close of the menu puts it back at its place and presses panel button 9. The letter
 * place under it (8 right and 0x18 below where it is drawn) is highlighted while the pen is down,
 * but not the mailbox's for a carried letter. Let go, a carried letter over the mailbox, or a
 * letter of the mailbox over a carried one that holds a letter, glides back; on a place that is
 * not dimmed the letter is put down there (sound 0xe) and the action ends; let go elsewhere,
 * MailboxScene_DropHeldAtTouch sends it to its place or to a free carried slot. */
void MailboxScene_DragHeld(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MailboxScene_PutHeldAt(self, self->held_from);
        MailboxScene_PressPanelButton9(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    MailboxScene_FollowTouch(self);
    MailboxScene_ClearHighlights(self);
    int x = (int) ((u32) self->held_x + 8);
    int place = MailboxScene_LetterPlaceAtTouch(self, x, (int) ((u32) self->held_y + 0x18), 0);

    if (place == MAILBOX_SCENE_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            MailboxScene_DropHeldAtTouch(self, self->held_from, x);
        }
        return;
    }
    if (data_021fbdd8 != 0) {
        if (!(MailboxScene_IsCarriedPlace(self, self->held_from) && MailboxScene_IsMailboxPlace(self, (unsigned int) place))) {
            MailboxScene_HighlightPlace(self, place);
        }
        return;
    }
    if (MailboxScene_IsCarriedPlace(self, self->held_from) && MailboxScene_IsMailboxPlace(self, (unsigned int) place)) {
        MailboxScene_GlideHeldTo(self, self->held_from, 4);
        return;
    }
    if (MailboxScene_IsMailboxPlace(self, self->held_from) && MailboxScene_IsCarriedPlace(self, (unsigned int) place) &&
        MailboxScene_PlaceIsEmpty(self, place) == 0) {
        MailboxScene_GlideHeldTo(self, self->held_from, 4);
        return;
    }
    if (MailboxScene_PlaceIsDimmed(self, place) == 0 && MailboxScene_PutHeldLetterAt(self, place) != 0) {
        PocketsSound_Play0e();
        MailboxScene_EndAction(self);
        return;
    }
    MailboxScene_DropHeldAtTouch(self, self->held_from, x);
}
CLEAN_AS(func_ov106_0229e544, MailboxScene_DragHeld)

/* func_ov106_0229e67c (sub state 3): once the popup is up, after `open_delay` more frames, the
 * touched place's choice opens above the popup; sub state 2. */
void MailboxScene_OpenTouchedChoice(MailboxScene *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return;
    }
    if (self->open_delay != 0) {
        self->open_delay--;
    } else {
        MailboxScene_OpenLetterMenu(self, self->touch_place, 1);
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_TOUCH_CHOICE);
    }
}
CLEAN_AS(func_ov106_0229e67c, MailboxScene_OpenTouchedChoice)

/* func_ov106_0229e6c4 (sub state 2): a touched place's choice is open. A close of the menu or the
 * pen let go hands the choice to the touch (sub state 6); the pen moving off a letter that may be
 * dragged picks it up (MailboxScene_PickUpWithTouch), closing the choice and hiding the popup. */
void MailboxScene_WatchChoiceTouch(MailboxScene *self)
{
    if (StateFlags_MenuCloseAsked()) {
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_BY_TOUCH);
        return;
    }
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(mbx_scene(self), MAILBOX_SCENE_SUB_CHOICE_BY_TOUCH);
        return;
    }
    if (MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAG_DRAGGABLE) != 0 && MailboxScene_TouchMoved(self) != 0) {
        MailboxScene_PickUpWithTouch(self, self->touch_place);
        PagedChoice_RequestClose(mbx_choice(self), 0);
        Popup_Hide(&self->popup, 1);
    }
}
CLEAN_AS(func_ov106_0229e6c4, MailboxScene_WatchChoiceTouch)
