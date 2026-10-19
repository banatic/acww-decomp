/* Overlay 100's scene (pockets_box.h). */
#include "pockets_box.h"

#include "clean.h"
#include "main/calendar.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/player_messages.h"
#include "main/pockets.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_label.h"
#include "ov002/key_repeat.h"
#include "ov094/pockets_common.h"
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"

/* The class's vtable. */
extern const u8 data_ov100_0229ecb8[];

/* The members' destructors. The labels' is handed to __cxa_vec_cleanup, so it is the game's
 * symbol (TextLabel_Destruct in Clean). */
extern int **func_02070be8(int **label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The multiplayer session (main/session.h) and the lists of player messages 3 and 4. */
extern NetSession *data_020ccf94;
extern u8 data_021f3a68[];
extern u8 data_021f3a86[];

/* The touch (main's bytes, as ov099/pockets_view.c reads them). */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;

/* Main's. */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The answers for a place outside the slots (PocketsBox_PlaceItem, PocketsBox_PlaceItemState). */
#define NO_ITEM_STATE 0xf1

/* Where messages 3 and 4 are sent (as ov098/pockets_town.c sends its player messages). */
#define MESSAGE_TO 4

/* The sound effects of the two ends (SoundSys_PlaySe). */
#define SE_CONFIRM 0x27
#define SE_CANCEL 0x28

/* The scene's sub states (MenuScene_SetSubState) set here. */
#define SUB_WAIT_SPRITE 0x08 /* back to `return_state` after the cursor sprite's move */
#define SUB_09 0x09
#define SUB_10 0x0a
#define SUB_PICK_UP 0x0b
#define SUB_PUT_DOWN 0x0d
#define SUB_SWAP 0x0e
#define SUB_CHOICE_CLOSE 0x12
#define SUB_CHOICE_CLOSING 0x13
#define SUB_CLOSED 0x15 /* the scene has ended; waits for PocketsBox_CanLeave */

/* The values of the choice rows (`action`). */
#define ACTION_PICK_UP 0
#define ACTION_CLOSE 1

/* The cursor sprite's animations beyond glide.h's names. */
#define CURSOR_ANIM_PUT_DOWN 5
#define CURSOR_ANIM_SWAP 6
#define CURSOR_ANIM_LAST_ROW 8

/* The closing labels: a text box of style 4 at a tile, 6 cells, colour 15 (lit) or 1 and 9, with
 * a message of the menu archive. */
#define LABEL_STYLE 4
#define LABEL_CELLS 6
#define LABEL_COLOUR_LIT 15
#define LABEL_COLOUR_DIM 1
#define LABEL_COLOUR_39 9
#define CANCEL_LABEL_TILE 0x1d6
#define CANCEL_LABEL_MESSAGE 101
#define CONFIRM_LABEL_TILE 0x1ca
#define CONFIRM_LABEL_MESSAGE 0x21

/* The two end places' x and y (PocketsBox_PlaceX, PocketsBox_PlaceY). */
#define BUTTONS_X 0xc4
#define CONFIRM_Y 0x58
#define CANCEL_Y 0x68

static MenuScene *scene_of(PocketsBox *self)
{
    return &self->base;
}

static PagedChoice *choice_of(PocketsBox *self)
{
    return (PagedChoice *) (void *) self->choice;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void update_cursor_sprite(PocketsBox *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* Whether `place` is one of the grid's slots: a pocket's, else the box's (asked only when it is
 * not a pocket's). */
static int is_slot(PocketsBox *self, int place)
{
    return PocketsBox_IsPocketPlace(self, (unsigned int) place) || PocketsBox_IsBoxPlace(self, (unsigned int) place);
}

static int is_button(PocketsBox *self, int place)
{
    return PocketsBox_IsButtonPlace(self, place);
}

/* The row and column of an offset in a part of 5 columns, counted as the game does: an offset
 * below 0 is row 0 and that offset as the column (callers give only places of the part). */
static void row_and_column(int offset, int *row, int *column)
{
    int r = 0;
    while (offset >= POCKETS_BOX_COLUMNS) {
        offset -= POCKETS_BOX_COLUMNS;
        r++;
    }
    *row = r;
    *column = offset;
}

static int in_range(u16 code, u16 first, u16 last)
{
    return code >= first && code <= last;
}

/* The members' destructors, last member first, then the base's. */
static void destroy_members(PocketsBox *self)
{
    self->base.vtable = data_ov100_0229ecb8;
    __cxa_vec_cleanup(self->labels, POCKETS_BOX_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(choice_of(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct((PocketsWallet *) (void *) self->wallet);
    PocketsLetters_Destruct((PocketsLetters *) (void *) self->letters);
    PocketsGrid_Destruct((PocketsGrid *) (void *) self->grid);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov100_0229c180 */
PocketsBox *PocketsBox_Destroy(PocketsBox *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov100_0229c180, PocketsBox_Destroy)

/* func_ov100_0229c20c */
PocketsBox *PocketsBox_Delete(PocketsBox *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov100_0229c20c, PocketsBox_Delete)

/* func_ov100_0229c2a0 */
void PocketsBox_ClearFlags(PocketsBox *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov100_0229c2a0, PocketsBox_ClearFlags)

/* func_ov100_0229c2b0 */
void PocketsBox_SetFlags(PocketsBox *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov100_0229c2b0, PocketsBox_SetFlags)

/* func_ov100_0229c2c0: whether any of `flags` is set. */
int PocketsBox_TestFlags(PocketsBox *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov100_0229c2c0, PocketsBox_TestFlags)

/* func_ov100_0229c2d8: whether the ended scene may leave: unless main's byte 0xc4c is 1 and the
 * box was sent, at once; else only once a linked session has reached the frame it was sent in. */
int PocketsBox_CanLeave(PocketsBox *self)
{
    if (!GroupParams_C4CIs1()) {
        return 1;
    }
    if (!PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_SENT)) {
        return 1;
    }
    if (Session_IsLinked(data_020ccf94) && !Session_HasReachedSequence(self->sent_frame)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov100_0229c2d8, PocketsBox_CanLeave)

/* func_ov100_0229c324: in a linked session, player message `type` (3 or 4) with the box's 15
 * codes, sent to the others; the frame it went out in is kept. */
void PocketsBox_SendBox(PocketsBox *self, int type)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_SENT);
    u8 message[0x20];
    message[0] = (u8) type;
    MI_CpuCopy8(self->box, &message[1], sizeof self->box);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, 1 + (int) sizeof self->box);
    Session_EndMessage(session, PLAYER_MESSAGE_CATEGORY, MESSAGE_TO);
    self->sent_frame = Session_GetFrameSequence(session);
}
CLEAN_AS(func_ov100_0229c324, PocketsBox_SendBox)

/* func_ov100_0229c390: the 15 codes of `items` moved to the front in order, the empty ones
 * (ITEM_CODE_NONE) after them; the number of items. */
int PocketsBox_Compact(PocketsBox *self, u16 *items)
{
    (void) self;
    int count = 0;
    for (int i = 0; i < POCKETS_BOX_SLOTS; i++) {
        if (items[i] == ITEM_CODE_NONE) {
            continue;
        }
        if (i != count) {
            items[count] = items[i];
            items[i] = ITEM_CODE_NONE;
        }
        count++;
    }
    return count;
}
CLEAN_AS(func_ov100_0229c390, PocketsBox_Compact)

/* func_ov100_0229c3c0 (the confirm place picked): the scene ends with its sound, its label and
 * the box compacted, which the mode then uses:
 * - 0x1d, 0x1e: the box given to Pockets_SetList when it holds anything (byte 0xc4c 1), else
 *   byte 0xc4c 0;
 * - 0x1f: the items taken out (those of the start no longer in the box) compacted; when there
 *   are any, byte 0xc4c 1, their number as the group's argument, them to Pockets_SetList, and
 *   the box written to list A and sent (message 3); else byte 0xc4c 0;
 * - 0x20: the box written to list B and sent (message 4), byte 0xc4c 1. */
void PocketsBox_Confirm(PocketsBox *self)
{
    PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_SENT);
    SoundSys_PlaySe(SE_CONFIRM);
    self->close_delay = 5;
    MenuScene_SetSubState(scene_of(self), SUB_CLOSED);
    PocketsBox_ShowConfirmLabel(self, 1);
    int count = PocketsBox_Compact(self, self->box);

    switch (GroupParams_Mode()) {
        case POCKETS_BOX_MODE_1D:
        case POCKETS_BOX_MODE_1E:
            if (count == 0) {
                GroupParams_SetC4C(0);
                break;
            }
            GroupParams_SetC4C(1);
            Pockets_SetList(self->box);
            break;
        case POCKETS_BOX_MODE_1F:
            for (int i = 0; i < POCKETS_BOX_SLOTS; i++) {
                if (self->box[i] == ITEM_CODE_NONE) {
                    continue;
                }
                for (int j = 0; j < POCKETS_BOX_SLOTS; j++) {
                    if (self->box[i] == self->box_start[j]) {
                        self->box_start[j] = ITEM_CODE_NONE;
                        break;
                    }
                }
            }
            count = PocketsBox_Compact(self, self->box_start);
            if (count == 0) {
                GroupParams_SetC4C(0);
                break;
            }
            GroupParams_SetC4C(1);
            GroupParams_SetArg((u8) count);
            Pockets_SetList(self->box_start);
            MI_CpuCopy8(self->box, data_021f3a68, sizeof self->box);
            PocketsBox_SendBox(self, PLAYER_MESSAGE_BYTES_A);
            break;
        case POCKETS_BOX_MODE_20:
            MI_CpuCopy8(self->box, data_021f3a86, sizeof self->box);
            PocketsBox_SendBox(self, PLAYER_MESSAGE_BYTES_B);
            GroupParams_SetC4C(1);
            break;
    }
}
CLEAN_AS(func_ov100_0229c3c0, PocketsBox_Confirm)

/* func_ov100_0229c4ec (the cancel place picked): the scene ends with its sound and its label,
 * byte 0xc4c 0, and the pockets restored from the copy taken at the start. */
void PocketsBox_Cancel(PocketsBox *self)
{
    PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_SENT);
    SoundSys_PlaySe(SE_CANCEL);
    self->close_delay = 5;
    MenuScene_SetSubState(scene_of(self), SUB_CLOSED);
    PocketsBox_ShowCancelLabel(self, 1);
    GroupParams_SetC4C(0);
    Pockets_Restore();
}
CLEAN_AS(func_ov100_0229c4ec, PocketsBox_Cancel)

/* Opens the next label's box at `tile` and shows menu message `message` in it. */
static void show_label(PocketsBox *self, int lit, int tile, int message)
{
    int colour = lit ? LABEL_COLOUR_LIT : LABEL_COLOUR_DIM;
    TextLabel *label = PocketsBox_NextLabel(self);
    TextLabel_OpenStyledBox2(label, LABEL_STYLE, tile, LABEL_CELLS, (u8) colour, LABEL_COLOUR_39, 0);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) message);
    TextLabel_Show(label, 1, 1);
}

/* func_ov100_0229c528 */
void PocketsBox_ShowCancelLabel(PocketsBox *self, int lit)
{
    show_label(self, lit, CANCEL_LABEL_TILE, CANCEL_LABEL_MESSAGE);
}
CLEAN_AS(func_ov100_0229c528, PocketsBox_ShowCancelLabel)

/* func_ov100_0229c56c */
void PocketsBox_ShowConfirmLabel(PocketsBox *self, int lit)
{
    show_label(self, lit, CONFIRM_LABEL_TILE, CONFIRM_LABEL_MESSAGE);
}
CLEAN_AS(func_ov100_0229c56c, PocketsBox_ShowConfirmLabel)

/* func_ov100_0229c5b0: the next free label; once both are in use, the second again. */
TextLabel *PocketsBox_NextLabel(PocketsBox *self)
{
    if (self->label_count >= POCKETS_BOX_LABELS) {
        return &self->labels[POCKETS_BOX_LABELS - 1];
    }
    self->label_count++;
    return &self->labels[self->label_count - 1];
}
CLEAN_AS(func_ov100_0229c5b0, PocketsBox_NextLabel)

/* func_ov100_0229c5e0: no label in use, both labels' boxes closed. */
void PocketsBox_CloseLabels(PocketsBox *self)
{
    self->label_count = 0;
    for (int i = 0; i < POCKETS_BOX_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov100_0229c5e0, PocketsBox_CloseLabels)

/* func_ov100_0229c60c: the cursor moved by the repeated d-pad keys `keys` (the wrap flags of
 * the last move and the sprite-set flag cleared first); whether it moved. When the cursor
 * moved between the end places and the slots, the cursor sprite turns to the other set (B at
 * the end places, A at the slots) and PocketsBox_GlideToCursor updates it. */
int PocketsBox_MoveCursor(PocketsBox *self, int keys, int wrap_in_row)
{
    u8 before = self->cursor;
    PocketsBox_ClearFlags(self, POCKETS_BOX_FLAGS_WRAPPED);
    PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_SPRITE_SET);
    if (keys == 0) {
        return 0;
    }

    if (PocketsBox_IsPocketPlace(self, self->cursor)) {
        PocketsBox_MoveCursorInPockets(self, keys, wrap_in_row);
    } else if (PocketsBox_IsBoxPlace(self, self->cursor)) {
        PocketsBox_MoveCursorInBox(self, keys, wrap_in_row);
    } else if (is_button(self, self->cursor)) {
        PocketsBox_MoveCursorAtButtons(self, keys);
    }

    int at_button = is_button(self, self->cursor);
    int was_at_button = is_button(self, before);
    if (at_button != was_at_button) {
        if (is_button(self, self->cursor)) {
            Glider_TurnToSetB(&self->cursor_sprite);
        } else {
            Glider_TurnToSetA(&self->cursor_sprite);
        }
        PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_SPRITE_SET);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov100_0229c60c, PocketsBox_MoveCursor)

/* func_ov100_0229c6dc: the cursor moved at the end places: up and down pick one of the two;
 * right then wraps to the first column (the box's last row from the confirm place, the first
 * pocket from the cancel place) and says so in the flags, left goes to the last column (the
 * box's last place from the confirm place, the first pocket row's last from the cancel one). */
void PocketsBox_MoveCursorAtButtons(PocketsBox *self, int keys)
{
    if (KeyRepeat_HasUp(keys)) {
        self->cursor = POCKETS_BOX_CONFIRM;
    } else if (KeyRepeat_HasDown(keys)) {
        self->cursor = POCKETS_BOX_CANCEL;
    }

    if (KeyRepeat_HasRight(keys)) {
        if (self->cursor == POCKETS_BOX_CONFIRM) {
            self->cursor = POCKETS_BOX_BOX_FIRST + 2 * POCKETS_BOX_COLUMNS;
        } else {
            self->cursor = POCKETS_BOX_POCKETS_FIRST;
        }
        PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_WRAPPED_RIGHT);
    } else if (KeyRepeat_HasLeft(keys)) {
        if (self->cursor == POCKETS_BOX_CONFIRM) {
            self->cursor = POCKETS_BOX_BOX_LAST;
        } else {
            self->cursor = POCKETS_BOX_COLUMNS - 1;
        }
    }
}
CLEAN_AS(func_ov100_0229c6dc, PocketsBox_MoveCursorAtButtons)

/* func_ov100_0229c758: the cursor moved in the box. Left and right move one column; past the
 * first or last column the cursor wraps in its row (`wrap_in_row` 1, saying so in the flags) or
 * goes to the confirm place (saying so only for left). Unless that ended the move, up moves one
 * row (none from the first) and down one row, or from the last row to the pocket of the same
 * column.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void PocketsBox_MoveCursorInBox(PocketsBox *self, int keys, int wrap_in_row)
{
    int row;
    int column;
    row_and_column(self->cursor - POCKETS_BOX_BOX_FIRST, &row, &column);

    if (KeyRepeat_HasLeft(keys)) {
        if (!KeyRepeat_HasUp(keys) || row == 0) {
            if (column == 0) {
                if (wrap_in_row == 1) {
                    self->cursor += POCKETS_BOX_COLUMNS - 1;
                } else {
                    self->cursor = POCKETS_BOX_CONFIRM;
                }
                PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_WRAPPED_LEFT);
                return;
            }
            self->cursor -= 1;
            column--;
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == POCKETS_BOX_COLUMNS - 1) {
            if (wrap_in_row == 1) {
                self->cursor -= POCKETS_BOX_COLUMNS - 1;
                PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_WRAPPED_RIGHT);
            } else {
                self->cursor = POCKETS_BOX_CONFIRM;
            }
            return;
        }
        self->cursor += 1;
        column++;
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= POCKETS_BOX_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < POCKETS_BOX_ROWS - 1) {
            self->cursor += POCKETS_BOX_COLUMNS;
        } else {
            self->cursor = (u8) (POCKETS_BOX_POCKETS_FIRST + column);
        }
    }
}
CLEAN_AS(func_ov100_0229c758, PocketsBox_MoveCursorInBox)

/* func_ov100_0229c84c: the cursor moved in the pockets, as in the box (PocketsBox_MoveCursorInBox)
 * but towards the cancel place, and with up from the first row going to the box's last row of
 * the same column and down stopping at the last row.
 * QUIRK: the same keys are ignored as in the box. */
void PocketsBox_MoveCursorInPockets(PocketsBox *self, int keys, int wrap_in_row)
{
    int row;
    int column;
    row_and_column(self->cursor, &row, &column);

    if (KeyRepeat_HasLeft(keys)) {
        if (!KeyRepeat_HasUp(keys) || row == 0) {
            if (column == 0) {
                if (wrap_in_row == 1) {
                    self->cursor += POCKETS_BOX_COLUMNS - 1;
                } else {
                    self->cursor = POCKETS_BOX_CANCEL;
                }
                PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_WRAPPED_LEFT);
                return;
            }
            self->cursor -= 1;
            column--;
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == POCKETS_BOX_COLUMNS - 1) {
            if (wrap_in_row == 1) {
                self->cursor -= POCKETS_BOX_COLUMNS - 1;
                PocketsBox_SetFlags(self, POCKETS_BOX_FLAG_WRAPPED_RIGHT);
            } else {
                self->cursor = POCKETS_BOX_CANCEL;
            }
            return;
        }
        self->cursor += 1;
        column++;
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= POCKETS_BOX_COLUMNS;
        } else {
            self->cursor = (u8) (POCKETS_BOX_BOX_FIRST + 2 * POCKETS_BOX_COLUMNS + column);
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < POCKETS_BOX_ROWS - 1) {
            self->cursor += POCKETS_BOX_COLUMNS;
        }
    }
}
CLEAN_AS(func_ov100_0229c84c, PocketsBox_MoveCursorInPockets)

/* func_ov100_0229c940: the choice closed without a pick: the closing action, the cursor
 * sprite back at the cursor, sub state 0x13. */
void PocketsBox_CancelChoice(PocketsBox *self)
{
    self->action = ACTION_CLOSE;
    PocketsBox_PlaceCursorSprite(self);
    PagedChoice_RequestClose(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), SUB_CHOICE_CLOSING);
}
CLEAN_AS(func_ov100_0229c940, PocketsBox_CancelChoice)

/* func_ov100_0229c970: the picked row's action: the pick-up, or the end of the action. */
void PocketsBox_RunAction(PocketsBox *self)
{
    if (self->action == ACTION_PICK_UP) {
        PocketsBox_StartPickUp(self);
    } else {
        PocketsBox_EndAction(self);
    }
}
CLEAN_AS(func_ov100_0229c970, PocketsBox_RunAction)

/* func_ov100_0229c994: a swap of the held item with `place`'s begins: the popup hidden, the sub
 * state kept, the cursor sprite's animation 6, sub state 0x0e. */
void PocketsBox_StartSwap(PocketsBox *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, CURSOR_ANIM_SWAP);
    MenuScene_SetSubState(scene_of(self), SUB_SWAP);
}
CLEAN_AS(func_ov100_0229c994, PocketsBox_StartSwap)

/* func_ov100_0229c9e0: the held item is put down on `place`: the popup hidden, the cursor
 * sprite's animation 5, sub state 0x0d. */
void PocketsBox_StartPutDown(PocketsBox *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, CURSOR_ANIM_PUT_DOWN);
    MenuScene_SetSubState(scene_of(self), SUB_PUT_DOWN);
}
CLEAN_AS(func_ov100_0229c9e0, PocketsBox_StartPutDown)

/* func_ov100_0229ca1c (action 0): the cursor sprite's animation 4, sub state 0x0b, which
 * picks up the cursor's item once it ends. */
void PocketsBox_StartPickUp(PocketsBox *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_TURN_A);
    MenuScene_SetSubState(scene_of(self), SUB_PICK_UP);
}
CLEAN_AS(func_ov100_0229ca1c, PocketsBox_StartPickUp)

/* func_ov100_0229ca3c */
void PocketsBox_BeginSubState10(PocketsBox *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), SUB_10);
}
CLEAN_AS(func_ov100_0229ca3c, PocketsBox_BeginSubState10)

/* func_ov100_0229ca5c */
void PocketsBox_BeginSubState9(PocketsBox *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), SUB_09);
}
CLEAN_AS(func_ov100_0229ca5c, PocketsBox_BeginSubState9)

/* func_ov100_0229ca7c: the first animation of the cursor sprite's set, then its update. */
void PocketsBox_ShowCursorFirstOfSet(PocketsBox *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov100_0229ca7c, PocketsBox_ShowCursorFirstOfSet)

/* func_ov100_0229ca9c: the cursor sprite put at the cursor, animation 1. */
void PocketsBox_PlaceCursorSprite(PocketsBox *self)
{
    int x = PocketsBox_CursorSpriteX(self);
    int y = PocketsBox_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov100_0229ca9c, PocketsBox_PlaceCursorSprite)

/* func_ov100_0229cad0: the cursor sprite put at the choice's first row, animation 7. */
void PocketsBox_PointAtFirstRow(PocketsBox *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov100_0229cad0, PocketsBox_PointAtFirstRow)

/* func_ov100_0229cb1c: the closing action, the choice's last row picked (with its sound) and
 * the cursor sprite put there at the last frame of animation 8; sub state 0x12. */
void PocketsBox_PointAtLastRow(PocketsBox *self)
{
    self->action = ACTION_CLOSE;
    self->choice_row = PagedChoice_PickLastRow(choice_of(self), 1);
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, CURSOR_ANIM_LAST_ROW);
    MenuScene_SetSubState(scene_of(self), SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov100_0229cb1c, PocketsBox_PointAtLastRow)

/* func_ov100_0229cb80: the cursor sprite moves to the choice row in 2 steps; the sub state is
 * kept and sub state 8 waits for the move. */
void PocketsBox_GlideToRow(PocketsBox *self)
{
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), SUB_WAIT_SPRITE);
}
CLEAN_AS(func_ov100_0229cb80, PocketsBox_GlideToRow)

/* func_ov100_0229cbd4: the cursor sprite eased to the cursor in 3 steps (cue 1), the sub state
 * kept and sub state 8 waiting for the move; a sprite whose set just changed is updated. */
void PocketsBox_GlideToCursor(PocketsBox *self)
{
    int x = PocketsBox_CursorSpriteX(self);
    int y = PocketsBox_CursorSpriteY(self);
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), SUB_WAIT_SPRITE);
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_SPRITE_SET)) {
        update_cursor_sprite(self);
        PocketsBox_ClearFlags(self, POCKETS_BOX_FLAG_SPRITE_SET);
    }
}
CLEAN_AS(func_ov100_0229cbd4, PocketsBox_GlideToCursor)

/* func_ov100_0229cc3c: the cursor sprite's animation 0, then its update. */
void PocketsBox_HideCursorSprite(PocketsBox *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    update_cursor_sprite(self);
}
CLEAN_AS(func_ov100_0229cc3c, PocketsBox_HideCursorSprite)

/* func_ov100_0229cc60: the cursor sprite's y, the cursor's place's. */
int PocketsBox_CursorSpriteY(PocketsBox *self)
{
    return PocketsBox_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov100_0229cc60, PocketsBox_CursorSpriteY)

/* func_ov100_0229cc70: the cursor sprite's x: the cursor's place's plus 8, and a screen width
 * (256) further right or left when this move wrapped over the right or left edge. */
int PocketsBox_CursorSpriteX(PocketsBox *self)
{
    int x = PocketsBox_PlaceX(self, self->cursor);
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_WRAPPED_RIGHT)) {
        x += 0x100;
    } else if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_WRAPPED_LEFT)) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov100_0229cc70, PocketsBox_CursorSpriteX)

/* func_ov100_0229ccb8: the cursor sprite put at the cursor, animation 7 at an end place and 1
 * at a slot, then the first of its set. */
void PocketsBox_ShowCursorSprite(PocketsBox *self)
{
    int x = PocketsBox_CursorSpriteX(self);
    int y = PocketsBox_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (is_button(self, self->cursor)) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    PocketsBox_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov100_0229ccb8, PocketsBox_ShowCursorSprite)

/* func_ov100_0229cd10: when an item is held, the item at `place` is picked up and the one held
 * before put there. */
void PocketsBox_SwapHeldWith(PocketsBox *self, int place)
{
    if (self->held_kind == POCKETS_BOX_HELD_ITEM) {
        u16 item = self->item;
        u8 state = self->held_state;
        PocketsBox_PickUpItem(self, place);
        PocketsBox_SetSlotItem(self, place, item, state);
    }
}
CLEAN_AS(func_ov100_0229cd10, PocketsBox_SwapHeldWith)

/* func_ov100_0229cd4c: the held item (if any) put at `place`; nothing is held after. */
void PocketsBox_PutHeldAt(PocketsBox *self, int place)
{
    if (self->held_kind == POCKETS_BOX_HELD_ITEM) {
        PocketsBox_SetSlotItem(self, place, self->item, self->held_state);
    }
    self->held_kind = POCKETS_BOX_HELD_NONE;
}
CLEAN_AS(func_ov100_0229cd4c, PocketsBox_PutHeldAt)

/* func_ov100_0229cd7c: the item of slot place `place` taken from its slot and held, its sprite
 * given to the grid's object. */
void PocketsBox_PickUpItem(PocketsBox *self, int place)
{
    if (!is_slot(self, place)) {
        return;
    }
    int slot = PocketsBox_SlotOfPlace(self, place);
    self->held_kind = POCKETS_BOX_HELD_ITEM;
    self->item = PocketsGrid_Item((PocketsGrid *) (void *) self->grid, slot);
    self->held_state = PocketsGrid_ItemState((PocketsGrid *) (void *) self->grid, slot);
    PocketsGrid_EmptyPlace((PocketsGrid *) (void *) self->grid, slot);
    PocketsGrid_SetHeldIcon((PocketsGrid *) (void *) self->grid, self->item, self->held_state);
}
CLEAN_AS(func_ov100_0229cd7c, PocketsBox_PickUpItem)

/* func_ov100_0229cdf4: the held item drawn where the glide is. */
void PocketsBox_FollowGlide(PocketsBox *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov100_0229cdf4, PocketsBox_FollowGlide)

/* func_ov100_0229ce24: the held item drawn at the cursor sprite's frame, 2 left and 4 up. */
void PocketsBox_FollowCursorSprite(PocketsBox *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov100_0229ce24, PocketsBox_FollowCursorSprite)

/* func_ov100_0229ce58: the held item drawn at the touch, kept at the offset it was grabbed at.
 * QUIRK: the sums wrap at 32 bits (done unsigned, as the ROM's code does). */
void PocketsBox_FollowTouch(PocketsBox *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov100_0229ce58, PocketsBox_FollowTouch)

/* func_ov100_0229ce90: the held item drawn by the grid's object, unless it is hidden. */
void PocketsBox_DrawHeld(PocketsBox *self)
{
    if (PocketsBox_TestFlags(self, POCKETS_BOX_FLAG_HELD_HIDDEN)) {
        return;
    }
    if (self->held_kind == POCKETS_BOX_HELD_ITEM) {
        PocketsGrid_DrawHeld((PocketsGrid *) (void *) self->grid, self->held_x, self->held_y);
    }
}
CLEAN_AS(func_ov100_0229ce90, PocketsBox_DrawHeld)

/* func_ov100_0229cecc: the popup tells of the cursor's place: queued for a slot that holds an
 * item (kept as `popup_place`), its queue cleared for an empty slot or another place. */
void PocketsBox_UpdatePopup(PocketsBox *self)
{
    if (is_slot(self, self->cursor) && !PocketsBox_PlaceIsEmpty(self, self->cursor)) {
        self->popup_place = self->cursor;
        Popup_Queue(&self->popup);
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov100_0229cecc, PocketsBox_UpdatePopup)

/* func_ov100_0229cf30: the popup put above its place (0x6d left and 0x78 up of it, 8 more up
 * when state flag 2 is set), or below it (0x50 up of it, the window's byte 0x5a set) when that
 * would be more than 92 pixels above; filled by the grid's object for a slot. */
void PocketsBox_PlacePopup(PocketsBox *self)
{
    int x = PocketsBox_PlaceX(self, self->popup_place) - 0x6d;
    int y = PocketsBox_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    if (y < -92) {
        SlidingWindow_SetSlideFlip((SlidingWindow *) (void *) &self->popup);
        y = PocketsBox_PlaceY(self, self->popup_place) - 0x50;
    } else {
        SlidingWindow_ClearSlideFlip((SlidingWindow *) (void *) &self->popup);
    }
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (is_slot(self, self->popup_place)) {
        PocketsGrid_ShowItemText((PocketsGrid *) (void *) self->grid, &self->popup,
                                 PocketsBox_SlotOfPlace(self, self->popup_place));
    }
}
CLEAN_AS(func_ov100_0229cf30, PocketsBox_PlacePopup)

/* The distance between two coordinates. */
static int distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

/* func_ov100_0229cfd0: whether the touch at data_021f6c60/5c is more than 8 pixels from the
 * one at data_021f6c58/54, in x or in y. */
int PocketsBox_TouchMoved(PocketsBox *self)
{
    (void) self;
    return distance(data_021f6c60, data_021f6c58) > 8 || distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov100_0229cfd0, PocketsBox_TouchMoved)

/* func_ov100_0229d014: slot place `place` marked in the grid's object. */
void PocketsBox_HighlightPlace(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        PocketsGrid_MarkPlace((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
}
CLEAN_AS(func_ov100_0229d014, PocketsBox_HighlightPlace)

/* func_ov100_0229d04c: no place marked in either object. */
void PocketsBox_ClearHighlights(PocketsBox *self)
{
    PocketsGrid_ClearMarks((PocketsGrid *) (void *) self->grid);
    PocketsLetters_ClearMarks((PocketsLetters *) (void *) self->letters);
}
CLEAN_AS(func_ov100_0229d04c, PocketsBox_ClearHighlights)

/* func_ov100_0229d068: slot place `place` selected in the grid's object (the letters'
 * selection cleared); at an end place both cleared; for other places nothing. */
void PocketsBox_SelectPlace(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        PocketsGrid_Lift((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
        PocketsLetters_Unlift((PocketsLetters *) (void *) self->letters);
    } else if (is_button(self, place)) {
        PocketsBox_ClearSelection(self);
    }
}
CLEAN_AS(func_ov100_0229d068, PocketsBox_SelectPlace)

/* func_ov100_0229d0c0 */
void PocketsBox_ClearSelection(PocketsBox *self)
{
    PocketsGrid_Unlift((PocketsGrid *) (void *) self->grid);
    PocketsLetters_Unlift((PocketsLetters *) (void *) self->letters);
}
CLEAN_AS(func_ov100_0229d0c0, PocketsBox_ClearSelection)

/* func_ov100_0229d0dc: the state of the item at slot place `place`, else 0xf1. */
int PocketsBox_PlaceItemState(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        return PocketsGrid_ItemState((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
    return NO_ITEM_STATE;
}
CLEAN_AS(func_ov100_0229d0dc, PocketsBox_PlaceItemState)

/* func_ov100_0229d118: the item at slot place `place`, else none (ITEM_CODE_NONE). */
int PocketsBox_PlaceItem(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        return PocketsGrid_Item((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
    return ITEM_CODE_NONE;
}
CLEAN_AS(func_ov100_0229d118, PocketsBox_PlaceItem)

/* func_ov100_0229d158: whether slot place `place` is empty; other places count as empty. */
int PocketsBox_PlaceIsEmpty(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        return PocketsGrid_IsEmpty((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov100_0229d158, PocketsBox_PlaceIsEmpty)

/* func_ov100_0229d194: whether slot place `place` is locked (PocketsBox_LockSlots); other
 * places are not. */
int PocketsBox_PlaceIsLocked(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        return PocketsGrid_IsDimmed((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov100_0229d194, PocketsBox_PlaceIsLocked)

/* func_ov100_0229d1d0: the pocket slots whose item may not move locked in the grid's object. */
void PocketsBox_LockSlots(PocketsBox *self)
{
    for (u8 place = POCKETS_BOX_POCKETS_FIRST; place <= POCKETS_BOX_POCKETS_LAST; place++) {
        if (PocketsBox_SlotMustLock(self, place)) {
            PocketsGrid_DimPlace((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
        }
    }
}
CLEAN_AS(func_ov100_0229d1d0, PocketsBox_LockSlots)

/* func_ov100_0229d208: whether the item at `place` may not move, by the mode: never an empty
 * place; always an item in a state other than 0 or one func_ov094_02299a54 refuses. Then by
 * the item's code:
 * - 0x1e: locked in 0x1492-0x14fd; free in 0x11a8-0x12a7, 0x1380-0x139f, 0x13a8-0x1407,
 *   0x1408-0x1428 and 0x1431-0x1491; locked otherwise;
 * - 0x1d: locked in 0x1492-0x14fd, and in 0x1531-0x153a while word 0xc of data_021dc744 is 0;
 *   free otherwise;
 * - 0x1f: always locked;
 * - 0x20: for an item func_ov094_02299b04 accepts, free in 0x1531-0x1541 and 0x154a-0x1553 and
 *   locked otherwise; free for other items;
 * - other modes: free. */
int PocketsBox_SlotMustLock(PocketsBox *self, int place)
{
    if (PocketsBox_PlaceIsEmpty(self, place) != 0) {
        return 0;
    }
    if (PocketsBox_PlaceItemState(self, place) != 0) {
        return 1;
    }
    int item = PocketsBox_PlaceItem(self, place);
    if (PocketsItem_Is155d((u16) item) != 0) {
        return 1;
    }
    u16 code = (u16) item;

    switch (GroupParams_Mode()) {
        case POCKETS_BOX_MODE_1E:
            if (in_range(code, 0x1492, 0x14fd)) {
                return 1;
            }
            if (in_range(code, 0x11a8, 0x12a7) || in_range(code, 0x13c8, 0x1407) || in_range(code, 0x13a8, 0x13c7) ||
                in_range(code, 0x1408, 0x1428) || in_range(code, 0x1431, 0x1470) || in_range(code, 0x1471, 0x1491) ||
                in_range(code, 0x1380, 0x139f)) {
                return 0;
            }
            return 1;
        case POCKETS_BOX_MODE_1D:
            if (in_range(code, 0x1492, 0x14fd)) {
                return 1;
            }
            if (Calendar_TodayWeekday() == 0 && in_range(code, 0x1531, 0x153a)) {
                return 1;
            }
            return 0;
        case POCKETS_BOX_MODE_1F:
            return 1;
        case POCKETS_BOX_MODE_20:
            if (PocketsItem_InLetterRefusedRanges((unsigned int) item) == 0) {
                return 0;
            }
            if (in_range(code, 0x1531, 0x153a) || in_range(code, 0x153b, 0x1541) || in_range(code, 0x154a, 0x1553)) {
                return 0;
            }
            return 1;
    }
    return 0;
}
CLEAN_AS(func_ov100_0229d208, PocketsBox_SlotMustLock)

/* func_ov100_0229d3d8: the y of `place`: a slot's by the grid's object, 0x58 for the confirm
 * place, 0x68 for the cancel place, 0 for others. */
int PocketsBox_PlaceY(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        return PocketsGrid_PlaceY((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
    if (is_button(self, place)) {
        return place == POCKETS_BOX_CONFIRM ? CONFIRM_Y : CANCEL_Y;
    }
    return 0;
}
CLEAN_AS(func_ov100_0229d3d8, PocketsBox_PlaceY)

/* func_ov100_0229d42c: the x of `place`: a slot's by the grid's object, 0xc4 for the end
 * places, 0 for others. */
int PocketsBox_PlaceX(PocketsBox *self, int place)
{
    if (is_slot(self, place)) {
        return PocketsGrid_PlaceX((PocketsGrid *) (void *) self->grid, PocketsBox_SlotOfPlace(self, place));
    }
    return is_button(self, place) ? BUTTONS_X : 0;
}
CLEAN_AS(func_ov100_0229d42c, PocketsBox_PlaceX)

/* func_ov100_0229d478: the place of the grid's box slot `slot` (15-29, the same number), else
 * POCKETS_BOX_NO_PLACE. */
int PocketsBox_BoxPlaceOfSlot(PocketsBox *self, unsigned int slot)
{
    (void) self;
    if (slot >= POCKETS_BOX_BOX_FIRST && slot <= POCKETS_BOX_BOX_LAST) {
        return (int) slot;
    }
    return POCKETS_BOX_NO_PLACE;
}
CLEAN_AS(func_ov100_0229d478, PocketsBox_BoxPlaceOfSlot)

/* func_ov100_0229d48c: the grid's slot of box place `place` (the low byte of the same number),
 * else the box's first slot. */
int PocketsBox_BoxSlot(PocketsBox *self, int place)
{
    if (PocketsBox_IsBoxPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    return POCKETS_BOX_BOX_FIRST;
}
CLEAN_AS(func_ov100_0229d48c, PocketsBox_BoxSlot)

/* func_ov100_0229d4a8: for a slot place, its slot set to `item` in `state` (the grid's object
 * writes the pocket slot too) and redrawn. */
void PocketsBox_SetSlotItem(PocketsBox *self, int place, int item, int state)
{
    if (!is_slot(self, place)) {
        return;
    }
    int slot = PocketsBox_SlotOfPlace(self, place);
    PocketsGrid_SetItem((PocketsGrid *) (void *) self->grid, slot, item, state);
    PocketsGrid_RefreshPlace((PocketsGrid *) (void *) self->grid, (unsigned int) slot);
}
CLEAN_AS(func_ov100_0229d4a8, PocketsBox_SetSlotItem)

/* func_ov100_0229d4f4: the held item put down at slot place `place`, the item there (if any)
 * moved to the place the held item came from; whether `place` is a slot. */
int PocketsBox_DropHeld(PocketsBox *self, int place)
{
    if (!is_slot(self, place)) {
        return 0;
    }
    int item = PocketsBox_PlaceItem(self, place);
    if (item != ITEM_CODE_NONE) {
        int state = PocketsBox_PlaceItemState(self, place);
        PocketsBox_SetSlotItem(self, self->held_place, item, state);
    }
    PocketsBox_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov100_0229d4f4, PocketsBox_DropHeld)

/* The grid's answer for a slot found by its place (PocketsBox_PlaceAtTouch): with
 * `items_only`, none for an empty slot. */
static int pockets_box_touched(PocketsBox *self, int slot, int items_only)
{
    return items_only != 0 && PocketsGrid_IsEmpty((PocketsGrid *) (void *) self->grid, slot) != 0;
}

/* func_ov100_0229d550: the place at touch position (x, y): a pocket's, else the box's, else
 * POCKETS_BOX_NO_PLACE; with `items_only`, an empty slot counts as none. */
int PocketsBox_PlaceAtTouch(PocketsBox *self, int x, int y, int items_only)
{
    PocketsGrid *grid = (PocketsGrid *) (void *) self->grid;
    int slot = PocketsGrid_PocketPlaceAtTouch(grid, x, y);
    if (slot != POCKETS_GRID_NO_PLACE) {
        if (pockets_box_touched(self, slot, items_only)) {
            return POCKETS_BOX_NO_PLACE;
        }
        return PocketsBox_PocketPlaceOfSlot(self, (unsigned int) slot);
    }
    slot = PocketsGrid_BoxPlaceAtTouch(grid, x, y);
    if (slot != POCKETS_GRID_NO_PLACE) {
        if (pockets_box_touched(self, slot, items_only)) {
            return POCKETS_BOX_NO_PLACE;
        }
        return PocketsBox_BoxPlaceOfSlot(self, (unsigned int) slot);
    }
    return POCKETS_BOX_NO_PLACE;
}
CLEAN_AS(func_ov100_0229d550, PocketsBox_PlaceAtTouch)

/* func_ov100_0229d5c4: the place of the grid's pocket slot `slot` (0-14, the same number),
 * else POCKETS_BOX_NO_PLACE. */
unsigned char PocketsBox_PocketPlaceOfSlot(PocketsBox *self, unsigned int slot)
{
    (void) self;
    if (slot <= POCKETS_BOX_POCKETS_LAST) {
        return (unsigned char) slot;
    }
    return POCKETS_BOX_NO_PLACE;
}
CLEAN_AS(func_ov100_0229d5c4, PocketsBox_PocketPlaceOfSlot)

/* func_ov100_0229d5d4: the grid's slot of a slot place (its low byte), else 0. */
int PocketsBox_SlotOfPlace(PocketsBox *self, int place)
{
    if (PocketsBox_IsPocketPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    if (PocketsBox_IsBoxPlace(self, (unsigned int) place)) {
        return PocketsBox_BoxSlot(self, place);
    }
    return 0;
}
CLEAN_AS(func_ov100_0229d5d4, PocketsBox_SlotOfPlace)

/* func_ov100_0229d60c: whether `place` is the confirm or the cancel place, by its low byte. */
int PocketsBox_IsButtonPlace(PocketsBox *self, int place)
{
    (void) self;
    u8 low = (u8) place;
    return low == POCKETS_BOX_CONFIRM || low == POCKETS_BOX_CANCEL;
}
CLEAN_AS(func_ov100_0229d60c, PocketsBox_IsButtonPlace)

/* func_ov100_0229d620 */
int PocketsBox_IsBoxPlace(PocketsBox *self, unsigned int place)
{
    (void) self;
    return place >= POCKETS_BOX_BOX_FIRST && place <= POCKETS_BOX_BOX_LAST;
}
CLEAN_AS(func_ov100_0229d620, PocketsBox_IsBoxPlace)

/* func_ov100_0229d630 */
int PocketsBox_IsPocketPlace(PocketsBox *self, unsigned int place)
{
    (void) self;
    return place <= POCKETS_BOX_POCKETS_LAST;
}
CLEAN_AS(func_ov100_0229d630, PocketsBox_IsPocketPlace)

/* func_ov100_0229d63c: the scene's layer load task taken off the main loop's queue and reset. */
void PocketsBox_EndLayerTask(PocketsBox *self)
{
    LayerTask_End(&self->layer_task.first);
}
CLEAN_AS(func_ov100_0229d63c, PocketsBox_EndLayerTask)

/* func_ov100_0229d648: the box's first empty place, else POCKETS_BOX_NO_PLACE. */
unsigned char PocketsBox_FirstEmptyBoxPlace(PocketsBox *self)
{
    for (int i = 0; i < POCKETS_BOX_SLOTS; i++) {
        if (self->box[i] == ITEM_CODE_NONE) {
            return (unsigned char) (POCKETS_BOX_BOX_FIRST + i);
        }
    }
    return POCKETS_BOX_NO_PLACE;
}
CLEAN_AS(func_ov100_0229d648, PocketsBox_FirstEmptyBoxPlace)

/* func_ov100_0229d67c: the place of the current player's first free pocket slot, else
 * POCKETS_BOX_NO_PLACE. */
int PocketsBox_FreePocketPlace(PocketsBox *self)
{
    (void) self;
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        return POCKETS_BOX_NO_PLACE;
    }
    return (u8) slot;
}
CLEAN_AS(func_ov100_0229d67c, PocketsBox_FreePocketPlace)
