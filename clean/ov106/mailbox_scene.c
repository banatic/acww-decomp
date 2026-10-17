/* The mailbox scene of overlay 106 (mailbox_scene.h): its destructors, its flags, the cursor's
 * moves, the choices it opens, the held letter and its places. */
#include "mailbox_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/item_code.h"
#include "main/item_record.h"
#include "main/label_sprite.h"
#include "main/lookups.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"

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

/* The scene's own place tests and the letters object's place of a letter place, and back. */
extern int func_ov106_0229d3a0(MailboxScene *self, unsigned int place); /* a carried letter */
extern int func_ov106_0229d390(MailboxScene *self, unsigned int place); /* a mailbox letter */
extern int func_ov106_0229d384(MailboxScene *self, int place);          /* MAILBOX_SCENE_BELOW */
extern unsigned char func_ov106_0229d360(MailboxScene *self, unsigned int place);
extern unsigned char func_ov106_0229d340(unsigned char unused, unsigned char index);
/* The cancel action: the choice is left (func_ov106_0229d73c). */
extern void func_ov106_0229d73c(MailboxScene *self);

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
    return func_ov106_0229d3a0(self, (unsigned int) place) != 0;
}

/* The place is a letter of the letters object: carried or in the mailbox. */
static int mbx_is_letter_place(MailboxScene *self, int place)
{
    return func_ov106_0229d3a0(self, (unsigned int) place) != 0 || func_ov106_0229d390(self, (unsigned int) place) != 0;
}

static int mbx_letter_index(MailboxScene *self, int place)
{
    return func_ov106_0229d360(self, (unsigned int) place);
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
    if (func_ov106_0229d3a0(self, self->cursor) != 0) {
        MailboxScene_MoveCursorInCarried(self, keys, mode);
    } else if (func_ov106_0229d390(self, self->cursor) != 0) {
        MailboxScene_MoveCursorInMailbox(self, keys, mode);
    } else if (func_ov106_0229d384(self, self->cursor) != 0) {
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

    if (func_ov106_0229d390(self, self->cursor) == 0 || MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAGS_WRAPPED) != 0) {
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

    if (func_ov106_0229d3a0(self, self->cursor) == 0 || MailboxScene_TestFlags(self, MAILBOX_SCENE_FLAGS_WRAPPED) != 0) {
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
            func_ov106_0229d73c(self);
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
    if (func_ov106_0229d384(self, self->cursor) != 0) {
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
 * lookup (func_ov106_0229d340) takes first and ignores. */
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
    return func_ov106_0229d340((unsigned char) (uintptr_t) self, (unsigned char) index);
}
CLEAN_AS(func_ov106_0229d2e4, MailboxScene_LetterPlaceAtTouch)
