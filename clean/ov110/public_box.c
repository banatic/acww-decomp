/* The box scene of overlay 110 (public_box.h): its destructors, its flags, the end of the scene,
 * the cursor's moves, the held item and the places. */
#include "public_box.h"

#include <stdint.h>

#include "autoload_2/input.h"
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
#include "ov002/key_repeat.h"
#include "ov094/pockets_common.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(PublicBox, flags) == 0x94, "flags");
static_assert(offsetof(PublicBox, grab_dx) == 0xa0 && offsetof(PublicBox, held_x) == 0xa8, "places");
static_assert(offsetof(PublicBox, box) == 0xb0 && offsetof(PublicBox, box_start) == 0xce, "lists");
static_assert(offsetof(PublicBox, item) == 0xec && offsetof(PublicBox, held_kind) == 0xf1, "held");
static_assert(offsetof(PublicBox, cursor) == 0xf5 && offsetof(PublicBox, close_delay) == 0xfc, "bytes");
static_assert(offsetof(PublicBox, task) == 0x100 && offsetof(PublicBox, grid) == 0x138, "task");
static_assert(offsetof(PublicBox, letters) == 0xb98 && offsetof(PublicBox, wallet) == 0xbc0, "ov094 objects");
static_assert(offsetof(PublicBox, popup) == 0x21f8 && offsetof(PublicBox, glide) == 0x22c8, "popup");
static_assert(offsetof(PublicBox, cursor_sprite) == 0x22e0 && offsetof(PublicBox, choice) == 0x2344, "sprite");
static_assert(offsetof(PublicBox, entries) == 0x272c && offsetof(PublicBox, error) == 0x2738, "choice");
static_assert(offsetof(PublicBox, labels) == 0x2854 && sizeof(TextLabel) == 0x6c, "labels");
static_assert(sizeof(PublicBox) == 0x292c, "size (func_ov110_0229eaf0)");

/* The class's vtable. */
extern const u8 data_ov110_0229ecb8[];

/* The labels' destructor, handed to __cxa_vec_cleanup (so the game's symbol, TextLabel_Destruct
 * in Clean). */
extern int **func_02070be8(int **label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The multiplayer session (main/session.h) and the town's lists A and B
 * (main/town_item_lists.h), which player messages 3 and 4 carry. */
extern NetSession *data_020ccf94;
extern u16 data_021f3a68[PUBLIC_BOX_SLOTS];
extern u16 data_021f3a86[PUBLIC_BOX_SLOTS];

/* The touch (main's bytes, as ov099/pockets_view.c reads them): now and when it went down. */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* Where messages 3 and 4 are sent (as ov098/pockets_town.c sends its player messages). */
#define PUBLIC_BOX_MESSAGE_TO 4

/* The end's sound effects (SoundSys_PlaySe): the recycle bin's, any other mode's. */
#define PUBLIC_BOX_SE_RECYCLE 0x28
#define PUBLIC_BOX_SE_DONE 0x27

/* The frames before the ended scene wipes out, when it ends by a choice of the player's. */
#define PUBLIC_BOX_CLOSE_DELAY 5

/* The end place's label: a text box of style 4 at tile 0x1ca, 6 cells, colour 15 (lit) or 1 and
 * 9, with menu message 0x88. */
#define PUBLIC_BOX_LABEL_STYLE 4
#define PUBLIC_BOX_LABEL_TILE 0x1ca
#define PUBLIC_BOX_LABEL_CELLS 6
#define PUBLIC_BOX_LABEL_COLOUR_LIT 15
#define PUBLIC_BOX_LABEL_COLOUR_DIM 1
#define PUBLIC_BOX_LABEL_COLOUR_39 9
#define PUBLIC_BOX_LABEL_MESSAGE 0x88

/* The end place's x and y (PublicBox_PlaceX, PublicBox_PlaceY). */
#define PUBLIC_BOX_DONE_X 0xc4
#define PUBLIC_BOX_DONE_Y 0x68

/* The cursor sprite's animations beyond glide.h's names. */
#define PUBLIC_BOX_ANIM_PUT_DOWN 5
#define PUBLIC_BOX_ANIM_SWAP 6
#define PUBLIC_BOX_ANIM_LAST_ROW 8

/* The answer of PublicBox_PlaceItemState for a place outside the slots. */
#define PUBLIC_BOX_NO_STATE 0xf1

static MenuScene *pbox_scene(PublicBox *self)
{
    return &self->base;
}

static PagedChoice *pbox_choice(PublicBox *self)
{
    return (PagedChoice *) (void *) self->choice;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void pbox_update_cursor_sprite(PublicBox *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* Whether `place` is one of the grid's slots: a pocket's, else the box's (asked only when it is
 * not a pocket's). */
static int pbox_is_slot(PublicBox *self, int place)
{
    return PublicBox_IsPocketPlace(self, (unsigned int) place) || PublicBox_IsBoxPlace(self, (unsigned int) place);
}

/* The row and column of an offset in a part of 5 columns, counted as the game does (callers give
 * only places of the part, so the offset is 0-14). */
static void pbox_row_and_column(int offset, int *row, int *column)
{
    int r = 0;
    while (offset >= PUBLIC_BOX_COLUMNS) {
        offset -= PUBLIC_BOX_COLUMNS;
        r++;
    }
    *row = r;
    *column = offset;
}

static int pbox_in_range(u16 code, u16 first, u16 last)
{
    return code >= first && code <= last;
}

/* The members' destructors, last member first, then the base's. */
static void pbox_destroy_members(PublicBox *self)
{
    self->base.vtable = data_ov110_0229ecb8;
    __cxa_vec_cleanup(self->labels, PUBLIC_BOX_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(pbox_choice(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct(&self->wallet);
    PocketsLetters_Destruct(&self->letters);
    PocketsGrid_Destruct(&self->grid);
    MenuScene_DestroyBase(pbox_scene(self));
}

/* func_ov110_0229c180 (vtable slot 0x40) */
PublicBox *PublicBox_Destroy(PublicBox *self)
{
    pbox_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov110_0229c180, PublicBox_Destroy)

/* func_ov110_0229c210 (vtable slot 0x44) */
PublicBox *PublicBox_Delete(PublicBox *self)
{
    pbox_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov110_0229c210, PublicBox_Delete)

/* func_ov110_0229c2a8 */
void PublicBox_ClearFlags(PublicBox *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov110_0229c2a8, PublicBox_ClearFlags)

/* func_ov110_0229c2b8 */
void PublicBox_SetFlags(PublicBox *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov110_0229c2b8, PublicBox_SetFlags)

/* func_ov110_0229c2c8: whether any of `flags` is set. */
int PublicBox_TestFlags(PublicBox *self, int flags)
{
    return (self->flags & (u32) flags) != 0;
}
CLEAN_AS(func_ov110_0229c2c8, PublicBox_TestFlags)

/* func_ov110_0229c2dc: whether the ended scene may wipe out: at once unless main's byte 0xc4c is
 * 1 and the box was sent; else only once a linked session has reached the frame it was sent in. */
int PublicBox_CanLeave(PublicBox *self)
{
    if (!GroupParams_C4CIs1()) {
        return 1;
    }
    if (!PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_SENT)) {
        return 1;
    }
    if (Session_IsLinked(data_020ccf94) && !Session_HasReachedSequence(self->sent_frame)) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov110_0229c2dc, PublicBox_CanLeave)

/* func_ov110_0229c324: in a linked session, player message `type` (3 or 4) with the box's 15
 * codes, sent to the others; the frame it went out in is kept. */
void PublicBox_SendBox(PublicBox *self, u8 type)
{
    if (!Session_IsLinked(data_020ccf94)) {
        return;
    }
    PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_SENT);
    u8 message[1 + sizeof self->box];
    message[0] = type;
    MI_CpuCopy8(self->box, &message[1], sizeof self->box);
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, (int) sizeof message);
    Session_EndMessage(session, PLAYER_MESSAGE_CATEGORY, PUBLIC_BOX_MESSAGE_TO);
    self->sent_frame = Session_GetFrameSequence(session);
}
CLEAN_AS(func_ov110_0229c324, PublicBox_SendBox)

/* func_ov110_0229c388: the 15 codes of `items` moved to the front in order, the empty ones
 * (ITEM_CODE_NONE) after them; the number of items. */
int PublicBox_Compact(PublicBox *self, u16 *items)
{
    (void) self;
    int count = 0;
    for (int i = 0; i < PUBLIC_BOX_SLOTS; i++) {
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
CLEAN_AS(func_ov110_0229c388, PublicBox_Compact)

/* func_ov110_0229c3b8: the scene ends (sub state 0x15, after 5 frames when `with_delay`, at once
 * when the menu is closing) with its sound and its label lit, and the box compacted, which the
 * mode then uses:
 * - 0x1d, 0x1e: the box given to Pockets_SetList when it holds anything (byte 0xc4c 1), else
 *   byte 0xc4c 0;
 * - 0x1f: the items taken out (those of the start no longer in the box) compacted; when there
 *   are any, byte 0xc4c 1, their number as the group's argument, them to Pockets_SetList, and the
 *   box written to list A and sent (message 3); else byte 0xc4c 0;
 * - 0x20: the box written to list B and sent (message 4), byte 0xc4c 1. */
void PublicBox_Finish(PublicBox *self, int with_delay)
{
    PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_SENT);
    int mode = GroupParams_Mode();
    if (mode == PUBLIC_BOX_MODE_RECYCLE) {
        SoundSys_PlaySe(PUBLIC_BOX_SE_RECYCLE);
    } else {
        SoundSys_PlaySe(PUBLIC_BOX_SE_DONE);
    }
    self->close_delay = with_delay != 0 ? PUBLIC_BOX_CLOSE_DELAY : 0;
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CLOSED);
    PublicBox_ShowDoneLabel(self, 1);
    int count = PublicBox_Compact(self, self->box);

    switch (mode) {
        case PUBLIC_BOX_MODE_1D:
        case PUBLIC_BOX_MODE_1E:
            if (count == 0) {
                GroupParams_SetC4C(0);
                break;
            }
            GroupParams_SetC4C(1);
            Pockets_SetList(self->box);
            break;
        case PUBLIC_BOX_MODE_LOST:
            for (int i = 0; i < PUBLIC_BOX_SLOTS; i++) {
                if (self->box[i] == ITEM_CODE_NONE) {
                    continue;
                }
                for (int j = 0; j < PUBLIC_BOX_SLOTS; j++) {
                    if (self->box[i] == self->box_start[j]) {
                        self->box_start[j] = ITEM_CODE_NONE;
                        break;
                    }
                }
            }
            count = PublicBox_Compact(self, self->box_start);
            if (count == 0) {
                GroupParams_SetC4C(0);
                break;
            }
            GroupParams_SetC4C(1);
            GroupParams_SetArg((u8) count);
            Pockets_SetList(self->box_start);
            MI_CpuCopy8(self->box, data_021f3a68, sizeof self->box);
            PublicBox_SendBox(self, PLAYER_MESSAGE_BYTES_A);
            break;
        case PUBLIC_BOX_MODE_RECYCLE:
            MI_CpuCopy8(self->box, data_021f3a86, sizeof self->box);
            PublicBox_SendBox(self, PLAYER_MESSAGE_BYTES_B);
            GroupParams_SetC4C(1);
            break;
    }
}
CLEAN_AS(func_ov110_0229c3b8, PublicBox_Finish)

/* func_ov110_0229c4f8: the end place's label opened in the next label and shown, lit or not. */
void PublicBox_ShowDoneLabel(PublicBox *self, int lit)
{
    int colour = lit != 0 ? PUBLIC_BOX_LABEL_COLOUR_LIT : PUBLIC_BOX_LABEL_COLOUR_DIM;
    TextLabel *label = PublicBox_NextLabel(self);
    TextLabel_OpenStyledBox2(label, PUBLIC_BOX_LABEL_STYLE, PUBLIC_BOX_LABEL_TILE, PUBLIC_BOX_LABEL_CELLS, (u8) colour,
                             PUBLIC_BOX_LABEL_COLOUR_39, 0);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) PUBLIC_BOX_LABEL_MESSAGE);
    TextLabel_Show(label, 1, 1);
}
CLEAN_AS(func_ov110_0229c4f8, PublicBox_ShowDoneLabel)

/* func_ov110_0229c53c: the next free label; once both are in use, the second again. */
TextLabel *PublicBox_NextLabel(PublicBox *self)
{
    if (self->label_count >= PUBLIC_BOX_LABELS) {
        return &self->labels[PUBLIC_BOX_LABELS - 1];
    }
    self->label_count++;
    return &self->labels[self->label_count - 1];
}
CLEAN_AS(func_ov110_0229c53c, PublicBox_NextLabel)

/* func_ov110_0229c574: no label in use, both labels' boxes closed. */
void PublicBox_CloseLabels(PublicBox *self)
{
    self->label_count = 0;
    for (int i = 0; i < PUBLIC_BOX_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov110_0229c574, PublicBox_CloseLabels)

/* func_ov110_0229c5a0: the cursor moved by the repeated d-pad keys `keys` (the wrap flags of the
 * last move and the sprite-set flag cleared first); whether it moved. When the cursor moved
 * between the end place and the slots, the cursor sprite turns to the other set (B at the end
 * place, A at the slots) and PublicBox_GlideToCursor updates it. */
int PublicBox_MoveCursor(PublicBox *self, int keys, int wrap_in_row)
{
    u8 before = self->cursor;
    PublicBox_ClearFlags(self, PUBLIC_BOX_FLAGS_WRAPPED);
    PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_SPRITE_SET);
    if (keys == 0) {
        return 0;
    }

    if (PublicBox_IsPocketPlace(self, self->cursor)) {
        PublicBox_MoveCursorInPockets(self, keys, wrap_in_row);
    } else if (PublicBox_IsBoxPlace(self, self->cursor)) {
        PublicBox_MoveCursorInBox(self, keys, wrap_in_row);
    } else if (PublicBox_IsButtonPlace(self, self->cursor)) {
        PublicBox_MoveCursorAtButton(self, keys);
    }

    int at_button = PublicBox_IsButtonPlace(self, self->cursor);
    if (at_button != PublicBox_IsButtonPlace(self, before)) {
        if (PublicBox_IsButtonPlace(self, self->cursor)) {
            Glider_TurnToSetB(&self->cursor_sprite);
        } else {
            Glider_TurnToSetA(&self->cursor_sprite);
        }
        PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_SPRITE_SET);
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov110_0229c5a0, PublicBox_MoveCursor)

/* func_ov110_0229c678: the cursor moved from the end place: right wraps to the first column (the
 * box's last row with up held, else the first pocket) and says so in the flags; left goes to the
 * last column (the box's last place with up held, else the first pocket row's last); up alone to
 * the box's last place. */
void PublicBox_MoveCursorAtButton(PublicBox *self, int keys)
{
    if (KeyRepeat_HasRight(keys)) {
        if (KeyRepeat_HasUp(keys)) {
            self->cursor = PUBLIC_BOX_BOX_FIRST + 2 * PUBLIC_BOX_COLUMNS;
        } else {
            self->cursor = PUBLIC_BOX_POCKETS_FIRST;
        }
        PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_WRAPPED_RIGHT);
    } else if (KeyRepeat_HasLeft(keys)) {
        if (KeyRepeat_HasUp(keys)) {
            self->cursor = PUBLIC_BOX_BOX_LAST;
        } else {
            self->cursor = PUBLIC_BOX_COLUMNS - 1;
        }
    } else if (KeyRepeat_HasUp(keys)) {
        self->cursor = PUBLIC_BOX_BOX_LAST;
    }
}
CLEAN_AS(func_ov110_0229c678, PublicBox_MoveCursorAtButton)

/* func_ov110_0229c6ec: the cursor moved in the box. Left and right move one column; past the
 * first or last column the cursor wraps in its row (`wrap_in_row` 1, saying so in the flags) or
 * goes to the end place (saying so only for left). Unless that ended the move, up moves one row
 * (none from the first) and down one row, or from the last row to the pocket of the same column.
 * QUIRK: left is ignored when up is held too and the cursor is below the first row; right is
 * ignored whenever down is held too. */
void PublicBox_MoveCursorInBox(PublicBox *self, int keys, int wrap_in_row)
{
    int row;
    int column;
    pbox_row_and_column(self->cursor - PUBLIC_BOX_BOX_FIRST, &row, &column);

    if (KeyRepeat_HasLeft(keys)) {
        if (!KeyRepeat_HasUp(keys) || row == 0) {
            if (column == 0) {
                if (wrap_in_row == 1) {
                    self->cursor += PUBLIC_BOX_COLUMNS - 1;
                } else {
                    self->cursor = PUBLIC_BOX_DONE;
                }
                PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_WRAPPED_LEFT);
                return;
            }
            self->cursor -= 1;
            column--;
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == PUBLIC_BOX_COLUMNS - 1) {
            if (wrap_in_row == 1) {
                self->cursor -= PUBLIC_BOX_COLUMNS - 1;
                PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_WRAPPED_RIGHT);
            } else {
                self->cursor = PUBLIC_BOX_DONE;
            }
            return;
        }
        self->cursor += 1;
        column++;
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= PUBLIC_BOX_COLUMNS;
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < PUBLIC_BOX_ROWS - 1) {
            self->cursor += PUBLIC_BOX_COLUMNS;
        } else {
            self->cursor = (u8) (PUBLIC_BOX_POCKETS_FIRST + column);
        }
    }
}
CLEAN_AS(func_ov110_0229c6ec, PublicBox_MoveCursorInBox)

/* func_ov110_0229c7f0: the cursor moved in the pockets, as in the box
 * (PublicBox_MoveCursorInBox), with up from the first row going to the box's last row of the same
 * column and down stopping at the last row.
 * QUIRK: the same keys are ignored as in the box. */
void PublicBox_MoveCursorInPockets(PublicBox *self, int keys, int wrap_in_row)
{
    int row;
    int column;
    pbox_row_and_column(self->cursor, &row, &column);

    if (KeyRepeat_HasLeft(keys)) {
        if (!KeyRepeat_HasUp(keys) || row == 0) {
            if (column == 0) {
                if (wrap_in_row == 1) {
                    self->cursor += PUBLIC_BOX_COLUMNS - 1;
                } else {
                    self->cursor = PUBLIC_BOX_DONE;
                }
                PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_WRAPPED_LEFT);
                return;
            }
            self->cursor -= 1;
            column--;
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == PUBLIC_BOX_COLUMNS - 1) {
            if (wrap_in_row == 1) {
                self->cursor -= PUBLIC_BOX_COLUMNS - 1;
                PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_WRAPPED_RIGHT);
            } else {
                self->cursor = PUBLIC_BOX_DONE;
            }
            return;
        }
        self->cursor += 1;
        column++;
    }

    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= PUBLIC_BOX_COLUMNS;
        } else {
            self->cursor = (u8) (PUBLIC_BOX_BOX_FIRST + 2 * PUBLIC_BOX_COLUMNS + column);
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < PUBLIC_BOX_ROWS - 1) {
            self->cursor += PUBLIC_BOX_COLUMNS;
        }
    }
}
CLEAN_AS(func_ov110_0229c7f0, PublicBox_MoveCursorInPockets)

/* func_ov110_0229c8f4: the choice closed without a pick: the closing action, the cursor sprite
 * back at the cursor, sub state 0x13. */
void PublicBox_CancelChoice(PublicBox *self)
{
    self->action = PUBLIC_BOX_ACTION_CLOSE;
    PublicBox_PlaceCursorSprite(self);
    PagedChoice_RequestClose(pbox_choice(self), 0);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_RUN);
}
CLEAN_AS(func_ov110_0229c8f4, PublicBox_CancelChoice)

/* func_ov110_0229c920: the picked row's action: the pick-up, or (any other value) the end of the
 * action. */
void PublicBox_RunAction(PublicBox *self)
{
    if (self->action == PUBLIC_BOX_ACTION_PICK_UP) {
        PublicBox_StartPickUp(self);
    } else {
        PublicBox_EndAction(self);
    }
}
CLEAN_AS(func_ov110_0229c920, PublicBox_RunAction)

/* func_ov110_0229c944: a swap of the held item with `place`'s begins: the popup hidden, the sub
 * state kept, the cursor sprite's animation 6, sub state 0x0e. */
void PublicBox_StartSwap(PublicBox *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, PUBLIC_BOX_ANIM_SWAP);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_SWAP);
}
CLEAN_AS(func_ov110_0229c944, PublicBox_StartSwap)

/* func_ov110_0229c98c: the held item is put down on `place`: the popup hidden, the cursor
 * sprite's animation 5, sub state 0x0d. */
void PublicBox_StartPutDown(PublicBox *self, u8 place)
{
    Popup_Hide(&self->popup, 1);
    self->target = place;
    Glider_SetAnim(&self->cursor_sprite, PUBLIC_BOX_ANIM_PUT_DOWN);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_PUT_DOWN);
}
CLEAN_AS(func_ov110_0229c98c, PublicBox_StartPutDown)

/* func_ov110_0229c9c8 (action 0): the cursor sprite's animation 4, sub state 0x0b, which picks
 * up the cursor's item once the sprite has turned. */
void PublicBox_StartPickUp(PublicBox *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_TURN_A);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_PICK_UP);
}
CLEAN_AS(func_ov110_0229c9c8, PublicBox_StartPickUp)

/* func_ov110_0229c9e8: the third animation of the cursor sprite's set, sub state 0x0a. */
void PublicBox_BeginButtonEnd(PublicBox *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_BUTTON_END);
}
CLEAN_AS(func_ov110_0229c9e8, PublicBox_BeginButtonEnd)

/* func_ov110_0229ca08: the second animation of the cursor sprite's set, sub state 9. */
void PublicBox_BeginButtonPress(PublicBox *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_BUTTON_PRESS);
}
CLEAN_AS(func_ov110_0229ca08, PublicBox_BeginButtonPress)

/* func_ov110_0229ca28: the first animation of the cursor sprite's set, then its update. */
void PublicBox_ShowCursorFirstOfSet(PublicBox *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    pbox_update_cursor_sprite(self);
}
CLEAN_AS(func_ov110_0229ca28, PublicBox_ShowCursorFirstOfSet)

/* func_ov110_0229ca48: the cursor sprite put at the cursor, animation 1. */
void PublicBox_PlaceCursorSprite(PublicBox *self)
{
    int x = PublicBox_CursorSpriteX(self);
    int y = PublicBox_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov110_0229ca48, PublicBox_PlaceCursorSprite)

/* func_ov110_0229ca7c: the cursor sprite put at the choice's first row, animation 7. */
void PublicBox_PointAtFirstRow(PublicBox *self)
{
    self->choice_row = 0;
    int x = PagedChoice_TextX(pbox_choice(self));
    int y = PagedChoice_RowY(pbox_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov110_0229ca7c, PublicBox_PointAtFirstRow)

/* func_ov110_0229cac8: the closing action, the choice's last row picked (with its sound) and the
 * cursor sprite put there at the last frame of animation 8; sub state 0x12. */
void PublicBox_PointAtLastRow(PublicBox *self)
{
    self->action = PUBLIC_BOX_ACTION_CLOSE;
    self->choice_row = PagedChoice_PickLastRow(pbox_choice(self), 1);
    int x = PagedChoice_TextX(pbox_choice(self));
    int y = PagedChoice_RowY(pbox_choice(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, PUBLIC_BOX_ANIM_LAST_ROW);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_CHOICE_CLOSE);
}
CLEAN_AS(func_ov110_0229cac8, PublicBox_PointAtLastRow)

/* func_ov110_0229cb28: the cursor sprite moves to the choice row in 2 steps; the sub state is
 * kept and sub state 8 waits for the move. */
void PublicBox_GlideToRow(PublicBox *self)
{
    int x = PagedChoice_TextX(pbox_choice(self));
    int y = PagedChoice_RowY(pbox_choice(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov110_0229cb28, PublicBox_GlideToRow)

/* func_ov110_0229cb78: the cursor sprite eased to the cursor in 3 steps (cue 1), the sub state
 * kept and sub state 8 waiting for the move; a sprite whose set just changed is updated. */
void PublicBox_GlideToCursor(PublicBox *self)
{
    int x = PublicBox_CursorSpriteX(self);
    int y = PublicBox_CursorSpriteY(self);
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_SPRITE_MOVE);
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_SPRITE_SET)) {
        pbox_update_cursor_sprite(self);
        PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_SPRITE_SET);
    }
}
CLEAN_AS(func_ov110_0229cb78, PublicBox_GlideToCursor)

/* func_ov110_0229cbe0: the cursor sprite's animation 0, then its update. */
void PublicBox_HideCursorSprite(PublicBox *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    pbox_update_cursor_sprite(self);
}
CLEAN_AS(func_ov110_0229cbe0, PublicBox_HideCursorSprite)

/* func_ov110_0229cc04: the cursor sprite's y, the cursor's place's. */
int PublicBox_CursorSpriteY(PublicBox *self)
{
    return PublicBox_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov110_0229cc04, PublicBox_CursorSpriteY)

/* func_ov110_0229cc14: the cursor sprite's x: the cursor's place's plus 8, and a screen width
 * (256) further right or left when this move wrapped over the right or left edge, so the sprite
 * slides there. */
int PublicBox_CursorSpriteX(PublicBox *self)
{
    int x = PublicBox_PlaceX(self, self->cursor);
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_WRAPPED_RIGHT)) {
        x += 0x100;
    } else if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_WRAPPED_LEFT)) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov110_0229cc14, PublicBox_CursorSpriteX)

/* func_ov110_0229cc58: the cursor sprite put at the cursor, animation 7 at the end place and 1
 * at a slot, then the first of its set. */
void PublicBox_ShowCursorSprite(PublicBox *self)
{
    int x = PublicBox_CursorSpriteX(self);
    int y = PublicBox_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (PublicBox_IsButtonPlace(self, self->cursor)) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    PublicBox_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov110_0229cc58, PublicBox_ShowCursorSprite)

/* func_ov110_0229ccb0: when an item is held, the item at `place` is picked up and the one held
 * before put there. */
void PublicBox_SwapHeldWith(PublicBox *self, int place)
{
    if (self->held_kind == PUBLIC_BOX_HELD_ITEM) {
        u16 item = self->item;
        u8 state = self->held_state;
        PublicBox_PickUpItem(self, place);
        PublicBox_SetSlotItem(self, place, item, state);
    }
}
CLEAN_AS(func_ov110_0229ccb0, PublicBox_SwapHeldWith)

/* func_ov110_0229cce8: the held item (if any) put at `place`; nothing is held after. Answers 0. */
int PublicBox_PutHeldAt(PublicBox *self, int place)
{
    if (self->held_kind == PUBLIC_BOX_HELD_ITEM) {
        PublicBox_SetSlotItem(self, place, self->item, self->held_state);
    }
    self->held_kind = PUBLIC_BOX_HELD_NONE;
    return 0;
}
CLEAN_AS(func_ov110_0229cce8, PublicBox_PutHeldAt)

/* func_ov110_0229cd14: the item of slot place `place` taken from its slot and held, its sprite
 * given to the grid's object. */
void PublicBox_PickUpItem(PublicBox *self, int place)
{
    if (!pbox_is_slot(self, place)) {
        return;
    }
    int slot = PublicBox_GridSlot(self, place);
    self->held_kind = PUBLIC_BOX_HELD_ITEM;
    self->item = PocketsGrid_Item(&self->grid, slot);
    self->held_state = PocketsGrid_ItemState(&self->grid, slot);
    PocketsGrid_EmptyPlace(&self->grid, slot);
    PocketsGrid_SetHeldIcon(&self->grid, self->item, self->held_state);
}
CLEAN_AS(func_ov110_0229cd14, PublicBox_PickUpItem)

/* func_ov110_0229cd8c: the held item drawn where the glide is. */
void PublicBox_FollowGlide(PublicBox *self)
{
    self->held_x = Glide_X(&self->glide);
    self->held_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov110_0229cd8c, PublicBox_FollowGlide)

/* func_ov110_0229cdb4: the held item drawn at the cursor sprite's frame, 2 left and 4 up. */
void PublicBox_FollowCursorSprite(PublicBox *self)
{
    self->held_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->held_y = Glider_FrameY(&self->cursor_sprite) - 4;
}
CLEAN_AS(func_ov110_0229cdb4, PublicBox_FollowCursorSprite)

/* func_ov110_0229cde0: the held item drawn at the touch, kept at the offset it was grabbed at.
 * QUIRK: the sums wrap at 32 bits (done unsigned, as the ROM's code does). */
void PublicBox_FollowTouch(PublicBox *self)
{
    self->held_x = (s32) ((u32) self->grab_dx + data_021f6c58);
    self->held_y = (s32) ((u32) self->grab_dy + data_021f6c54);
}
CLEAN_AS(func_ov110_0229cde0, PublicBox_FollowTouch)

/* func_ov110_0229ce0c: the held item drawn by the grid's object, unless it is hidden. */
void PublicBox_DrawHeld(PublicBox *self)
{
    if (PublicBox_TestFlags(self, PUBLIC_BOX_FLAG_HELD_HIDDEN)) {
        return;
    }
    if (self->held_kind == PUBLIC_BOX_HELD_ITEM) {
        PocketsGrid_DrawHeld(&self->grid, self->held_x, self->held_y);
    }
}
CLEAN_AS(func_ov110_0229ce0c, PublicBox_DrawHeld)

/* func_ov110_0229ce44: the popup tells of the cursor's place: queued for a slot that holds an
 * item (kept as `popup_place`), its queue cleared for an empty slot or another place. */
void PublicBox_UpdatePopup(PublicBox *self)
{
    if (pbox_is_slot(self, self->cursor)) {
        if (PublicBox_PlaceIsEmpty(self, self->cursor)) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    } else {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov110_0229ce44, PublicBox_UpdatePopup)

/* func_ov110_0229cea8: the popup put above its place (0x6d left and 0x78 up of it, 8 more up when
 * state flag 2 is set), or below it (0x50 up of it, the window's slide flipped) when that would
 * be more than 92 pixels above; filled by the grid's object for a slot. */
void PublicBox_PlacePopup(PublicBox *self)
{
    SlidingWindow *window = (SlidingWindow *) (void *) &self->popup;
    int x = PublicBox_PlaceX(self, self->popup_place) - 0x6d;
    int y = PublicBox_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2()) {
        y -= 8;
    }
    if (y < -92) {
        SlidingWindow_SetSlideFlip(window);
        y = PublicBox_PlaceY(self, self->popup_place) - 0x50;
    } else {
        SlidingWindow_ClearSlideFlip(window);
    }
    SlidingWindow_SetPlace(window, x, y);
    if (pbox_is_slot(self, self->popup_place)) {
        PocketsGrid_ShowItemText(&self->grid, &self->popup, PublicBox_GridSlot(self, self->popup_place));
    }
}
CLEAN_AS(func_ov110_0229cea8, PublicBox_PlacePopup)

/* The distance between two coordinates. */
static int pbox_distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

/* func_ov110_0229cf54: whether the touch is more than 8 pixels, in x or in y, from where it went
 * down. */
int PublicBox_TouchMoved(PublicBox *self)
{
    (void) self;
    return pbox_distance(data_021f6c60, data_021f6c58) > 8 || pbox_distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov110_0229cf54, PublicBox_TouchMoved)

/* func_ov110_0229cf98: slot place `place` marked in the grid's object. */
void PublicBox_HighlightPlace(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        PocketsGrid_MarkPlace(&self->grid, PublicBox_GridSlot(self, place));
    }
}
CLEAN_AS(func_ov110_0229cf98, PublicBox_HighlightPlace)

/* func_ov110_0229cfd4: no place marked in either object. */
void PublicBox_ClearHighlights(PublicBox *self)
{
    PocketsGrid_ClearMarks(&self->grid);
    PocketsLetters_ClearMarks(&self->letters);
}
CLEAN_AS(func_ov110_0229cfd4, PublicBox_ClearHighlights)

/* func_ov110_0229cff8: slot place `place` lifted in the grid's object (the letters' lift
 * cleared); at the end place both cleared; for other places nothing. */
void PublicBox_SelectPlace(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        PocketsGrid_Lift(&self->grid, PublicBox_GridSlot(self, place));
        PocketsLetters_Unlift(&self->letters);
    } else if (PublicBox_IsButtonPlace(self, place)) {
        PublicBox_ClearSelection(self);
    }
}
CLEAN_AS(func_ov110_0229cff8, PublicBox_SelectPlace)

/* func_ov110_0229d054 */
void PublicBox_ClearSelection(PublicBox *self)
{
    PocketsGrid_Unlift(&self->grid);
    PocketsLetters_Unlift(&self->letters);
}
CLEAN_AS(func_ov110_0229d054, PublicBox_ClearSelection)

/* func_ov110_0229d078: the state of the item at slot place `place`, else 0xf1. */
int PublicBox_PlaceItemState(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        return PocketsGrid_ItemState(&self->grid, PublicBox_GridSlot(self, place));
    }
    return PUBLIC_BOX_NO_STATE;
}
CLEAN_AS(func_ov110_0229d078, PublicBox_PlaceItemState)

/* func_ov110_0229d0b8: the item at slot place `place`, else none (ITEM_CODE_NONE). */
int PublicBox_PlaceItem(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        return PocketsGrid_Item(&self->grid, PublicBox_GridSlot(self, place));
    }
    return ITEM_CODE_NONE;
}
CLEAN_AS(func_ov110_0229d0b8, PublicBox_PlaceItem)

/* func_ov110_0229d0fc: whether slot place `place` is empty; other places count as empty. */
int PublicBox_PlaceIsEmpty(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        return PocketsGrid_IsEmpty(&self->grid, PublicBox_GridSlot(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov110_0229d0fc, PublicBox_PlaceIsEmpty)

/* func_ov110_0229d13c: whether slot place `place` is locked (PublicBox_LockSlots); other places
 * are not. */
int PublicBox_PlaceIsLocked(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        return PocketsGrid_IsDimmed(&self->grid, PublicBox_GridSlot(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov110_0229d13c, PublicBox_PlaceIsLocked)

/* func_ov110_0229d17c: the pocket slots whose item may not move locked (dimmed) in the grid's
 * object. */
void PublicBox_LockSlots(PublicBox *self)
{
    for (u8 place = PUBLIC_BOX_POCKETS_FIRST; place <= PUBLIC_BOX_POCKETS_LAST; place++) {
        if (PublicBox_SlotMustLock(self, place)) {
            PocketsGrid_DimPlace(&self->grid, PublicBox_GridSlot(self, place));
        }
    }
}
CLEAN_AS(func_ov110_0229d17c, PublicBox_LockSlots)

/* func_ov110_0229d1b8: whether the item at `place` may not move, by the mode: never an empty
 * place; always an item in a state other than 0 or one PocketsItem_Is155d accepts. Then by the
 * item's code:
 * - 0x1e: locked in 0x1492-0x14fd; free in 0x11a8-0x12a7, 0x1380-0x139f, 0x13a8-0x1428 and
 *   0x1431-0x1491; locked otherwise;
 * - 0x1d: locked in 0x1492-0x14fd, and in 0x1531-0x153a on Sundays (Calendar_TodayWeekday 0);
 *   free otherwise;
 * - 0x1f (the lost and found): always locked;
 * - 0x20 (the recycle bin): for an item PocketsItem_InLetterRefusedRanges accepts, free in
 *   0x1531-0x1541 and 0x154a-0x1553 and locked otherwise; free for other items;
 * - other modes: free. */
int PublicBox_SlotMustLock(PublicBox *self, int place)
{
    if (PublicBox_PlaceIsEmpty(self, place) != 0) {
        return 0;
    }
    if (PublicBox_PlaceItemState(self, place) != 0) {
        return 1;
    }
    int item = PublicBox_PlaceItem(self, place);
    if (PocketsItem_Is155d((u16) item) != 0) {
        return 1;
    }
    u16 code = (u16) item;

    switch (GroupParams_Mode()) {
        case PUBLIC_BOX_MODE_1E:
            if (pbox_in_range(code, 0x1492, 0x14fd)) {
                return 1;
            }
            if (pbox_in_range(code, 0x11a8, 0x12a7) || pbox_in_range(code, 0x13c8, 0x1407) ||
                pbox_in_range(code, 0x13a8, 0x13c7) || pbox_in_range(code, 0x1408, 0x1428) ||
                pbox_in_range(code, 0x1431, 0x1470) || pbox_in_range(code, 0x1471, 0x1491) ||
                pbox_in_range(code, 0x1380, 0x139f)) {
                return 0;
            }
            return 1;
        case PUBLIC_BOX_MODE_1D:
            if (pbox_in_range(code, 0x1492, 0x14fd)) {
                return 1;
            }
            if (Calendar_TodayWeekday() == 0 && pbox_in_range(code, 0x1531, 0x153a)) {
                return 1;
            }
            return 0;
        case PUBLIC_BOX_MODE_LOST:
            return 1;
        case PUBLIC_BOX_MODE_RECYCLE:
            if (PocketsItem_InLetterRefusedRanges((unsigned int) item) == 0) {
                return 0;
            }
            if (pbox_in_range(code, 0x1531, 0x153a) || pbox_in_range(code, 0x153b, 0x1541) ||
                pbox_in_range(code, 0x154a, 0x1553)) {
                return 0;
            }
            return 1;
    }
    return 0;
}
CLEAN_AS(func_ov110_0229d1b8, PublicBox_SlotMustLock)

/* func_ov110_0229d388: the y of `place`: a slot's by the grid's object, 0x68 for the end place,
 * 0 for others. */
int PublicBox_PlaceY(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        return PocketsGrid_PlaceY(&self->grid, PublicBox_GridSlot(self, place));
    }
    return PublicBox_IsButtonPlace(self, place) ? PUBLIC_BOX_DONE_Y : 0;
}
CLEAN_AS(func_ov110_0229d388, PublicBox_PlaceY)

/* func_ov110_0229d3d8: the x of `place`: a slot's by the grid's object, 0xc4 for the end place,
 * 0 for others. */
int PublicBox_PlaceX(PublicBox *self, int place)
{
    if (pbox_is_slot(self, place)) {
        return PocketsGrid_PlaceX(&self->grid, PublicBox_GridSlot(self, place));
    }
    return PublicBox_IsButtonPlace(self, place) ? PUBLIC_BOX_DONE_X : 0;
}
CLEAN_AS(func_ov110_0229d3d8, PublicBox_PlaceX)

/* func_ov110_0229d428: the place of the grid's box slot `slot` (15-29, the same number), else
 * PUBLIC_BOX_NO_PLACE. */
u8 PublicBox_BoxPlaceOfSlot(PublicBox *self, unsigned int slot)
{
    (void) self;
    if (slot >= PUBLIC_BOX_BOX_FIRST && slot <= PUBLIC_BOX_BOX_LAST) {
        return (u8) slot;
    }
    return PUBLIC_BOX_NO_PLACE;
}
CLEAN_AS(func_ov110_0229d428, PublicBox_BoxPlaceOfSlot)

/* func_ov110_0229d43c: the grid's slot of box place `place` (the low byte of the same number),
 * else the box's first slot. */
int PublicBox_BoxSlot(PublicBox *self, int place)
{
    if (PublicBox_IsBoxPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    return PUBLIC_BOX_BOX_FIRST;
}
CLEAN_AS(func_ov110_0229d43c, PublicBox_BoxSlot)

/* func_ov110_0229d458: for a slot place, its slot set to `item` in `state` (the grid's object
 * writes the pocket slot too) and redrawn. */
void PublicBox_SetSlotItem(PublicBox *self, int place, int item, int state)
{
    if (!pbox_is_slot(self, place)) {
        return;
    }
    int slot = PublicBox_GridSlot(self, place);
    PocketsGrid_SetItem(&self->grid, slot, item, state);
    PocketsGrid_RefreshPlace(&self->grid, (unsigned int) slot);
}
CLEAN_AS(func_ov110_0229d458, PublicBox_SetSlotItem)

/* func_ov110_0229d4a8: the held item put down at slot place `place`: an item already there goes
 * to the place the held one came from, then the held one is put down. Whether `place` is a slot
 * (nothing is done for other places). */
int PublicBox_PutHeldAtPlace(PublicBox *self, int place)
{
    if (!pbox_is_slot(self, place)) {
        return 0;
    }
    int item = PublicBox_PlaceItem(self, place);
    if (item != ITEM_CODE_NONE) {
        int state = PublicBox_PlaceItemState(self, place);
        PublicBox_SetSlotItem(self, self->held_place, item, state);
    }
    PublicBox_PutHeldAt(self, place);
    return 1;
}
CLEAN_AS(func_ov110_0229d4a8, PublicBox_PutHeldAtPlace)

/* func_ov110_0229d504: the place under the touch at (x, y): a pocket slot, else a box slot (the
 * grid's object answers 0x23 for none); with `need_item`, an empty slot counts as none. Else
 * PUBLIC_BOX_NO_PLACE. */
int PublicBox_PlaceAtTouch(PublicBox *self, int x, int y, int need_item)
{
    int slot = PocketsGrid_PocketPlaceAtTouch(&self->grid, x, y);
    if (slot != 0x23) {
        if (need_item != 0 && PocketsGrid_IsEmpty(&self->grid, slot) != 0) {
            return PUBLIC_BOX_NO_PLACE;
        }
        return PublicBox_PocketPlaceOfSlot(self, (unsigned int) slot);
    }
    slot = PocketsGrid_BoxPlaceAtTouch(&self->grid, x, y);
    if (slot != 0x23) {
        if (need_item != 0 && PocketsGrid_IsEmpty(&self->grid, slot) != 0) {
            return PUBLIC_BOX_NO_PLACE;
        }
        return PublicBox_BoxPlaceOfSlot(self, (unsigned int) slot);
    }
    return PUBLIC_BOX_NO_PLACE;
}
CLEAN_AS(func_ov110_0229d504, PublicBox_PlaceAtTouch)

/* func_ov110_0229d580: the place of the grid's pocket slot `slot` (0-14, the same number), else
 * PUBLIC_BOX_NO_PLACE. */
int PublicBox_PocketPlaceOfSlot(PublicBox *self, unsigned int slot)
{
    (void) self;
    if (slot <= PUBLIC_BOX_POCKETS_LAST) {
        return (u8) slot;
    }
    return PUBLIC_BOX_NO_PLACE;
}
CLEAN_AS(func_ov110_0229d580, PublicBox_PocketPlaceOfSlot)

/* func_ov110_0229d590: the grid's slot of `place`: a pocket's low byte, a box place's
 * (PublicBox_BoxSlot), else 0. */
int PublicBox_GridSlot(PublicBox *self, int place)
{
    if (PublicBox_IsPocketPlace(self, (unsigned int) place)) {
        return (u8) place;
    }
    if (PublicBox_IsBoxPlace(self, (unsigned int) place)) {
        return PublicBox_BoxSlot(self, place);
    }
    return 0;
}
CLEAN_AS(func_ov110_0229d590, PublicBox_GridSlot)

/* func_ov110_0229d5c8 */
int PublicBox_IsButtonPlace(PublicBox *self, int place)
{
    (void) self;
    return place == PUBLIC_BOX_DONE;
}
CLEAN_AS(func_ov110_0229d5c8, PublicBox_IsButtonPlace)

/* func_ov110_0229d5d4 */
int PublicBox_IsBoxPlace(PublicBox *self, unsigned int place)
{
    (void) self;
    return place >= PUBLIC_BOX_BOX_FIRST && place <= PUBLIC_BOX_BOX_LAST;
}
CLEAN_AS(func_ov110_0229d5d4, PublicBox_IsBoxPlace)

/* func_ov110_0229d5e4 */
int PublicBox_IsPocketPlace(PublicBox *self, unsigned int place)
{
    (void) self;
    return place <= PUBLIC_BOX_POCKETS_LAST;
}
CLEAN_AS(func_ov110_0229d5e4, PublicBox_IsPocketPlace)

/* func_ov110_0229d5f0: the layer task taken off the main loop's queue and reset. */
void PublicBox_EndLayerTask(PublicBox *self)
{
    LayerTask_End(&self->task.first);
}
CLEAN_AS(func_ov110_0229d5f0, PublicBox_EndLayerTask)

/* func_ov110_0229d600: the place of the box's first empty slot, else PUBLIC_BOX_NO_PLACE. */
u16 PublicBox_FirstEmptyBoxPlace(PublicBox *self)
{
    for (int i = 0; i < PUBLIC_BOX_SLOTS; i++) {
        if (self->box[i] == ITEM_CODE_NONE) {
            return (u8) (i + PUBLIC_BOX_BOX_FIRST);
        }
    }
    return PUBLIC_BOX_NO_PLACE;
}
CLEAN_AS(func_ov110_0229d600, PublicBox_FirstEmptyBoxPlace)

/* func_ov110_0229d628: the place of the current player's first free pocket slot
 * (CurrentPockets_FreeSlot), else PUBLIC_BOX_NO_PLACE. */
u8 PublicBox_FreePocketPlace(PublicBox *self)
{
    (void) self;
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        return PUBLIC_BOX_NO_PLACE;
    }
    return (u8) slot;
}
CLEAN_AS(func_ov110_0229d628, PublicBox_FreePocketPlace)

/* func_ov110_0229d648: the item at `from` picked up where it is and glided to `to` in 4 steps. */
void PublicBox_HoldAndGlide(PublicBox *self, int from, int to)
{
    PublicBox_PickUpItem(self, from);
    self->held_x = PublicBox_PlaceX(self, from);
    self->held_y = PublicBox_PlaceY(self, from);
    PublicBox_GlideHeldTo(self, (u8) to, 4);
}
CLEAN_AS(func_ov110_0229d648, PublicBox_HoldAndGlide)

/* func_ov110_0229d680: the held item let go at height `y` (8 below the item's corner): let go
 * low (y 0x6c or more) after coming from the box, it glides to a free pocket slot; let go high
 * after coming from the pockets, to the box's first empty slot; else (or with no such slot) back
 * to `place`. In 4 steps.
 * QUIRK: answers what MenuScene_SetSubState answers (an address), as an int. */
int PublicBox_DropHeldAtTouch(PublicBox *self, int place, int y)
{
    int to = PUBLIC_BOX_NO_PLACE;
    if (y >= 0x6c) {
        if (PublicBox_IsBoxPlace(self, (unsigned int) place)) {
            to = PublicBox_FreePocketPlace(self);
        }
    } else {
        if (PublicBox_IsPocketPlace(self, (unsigned int) place)) {
            to = PublicBox_FirstEmptyBoxPlace(self);
        }
    }
    if (to != PUBLIC_BOX_NO_PLACE) {
        place = to;
    }
    return (int) (uintptr_t) PublicBox_GlideHeldTo(self, (u8) place, 4);
}
CLEAN_AS(func_ov110_0229d680, PublicBox_DropHeldAtTouch)

/* func_ov110_0229d6c4: the held item glides from where it is drawn to `place` in `steps` steps
 * (the place kept as `held_place`), its first step taken; sub state 0x10. Answers what
 * MenuScene_SetSubState answers. */
u8 *PublicBox_GlideHeldTo(PublicBox *self, u8 place, int steps)
{
    self->held_place = place;
    Glide_SetPlace(&self->glide, self->held_x, self->held_y);
    int x = PublicBox_PlaceX(self, place);
    int y = PublicBox_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    PublicBox_FollowGlide(self);
    return MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_HELD_GLIDE);
}
CLEAN_AS(func_ov110_0229d6c4, PublicBox_GlideHeldTo)

/* func_ov110_0229d728: the item at `place` picked up by the cursor: the popup hidden; when an
 * item was taken, sub state 5 (moving it) once the cursor sprite's move ends; the item drawn at
 * the cursor sprite, sound 0x0d. */
void PublicBox_PickUpWithCursor(PublicBox *self, char place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PublicBox_PickUpItem(self, place);
    if (self->held_kind == PUBLIC_BOX_HELD_ITEM) {
        self->return_state = PUBLIC_BOX_SUB_HOLD;
    }
    PublicBox_FollowCursorSprite(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov110_0229d728, PublicBox_PickUpWithCursor)

/* func_ov110_0229d770: the item at `place` picked up by the touch: the popup hidden; when an item
 * was taken, sub state 3 (dragging it); the item drawn at the touch, sound 0x0d. */
void PublicBox_PickUpWithTouch(PublicBox *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PublicBox_PickUpItem(self, place);
    if (self->held_kind == PUBLIC_BOX_HELD_ITEM) {
        MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_DRAG);
    }
    PublicBox_FollowTouch(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov110_0229d770, PublicBox_PickUpWithTouch)

/* func_ov110_0229d7b8: `place` touched: sub state 1, the offset from the touch to the place kept,
 * the popup queued for it; a place not locked may be dragged (PUBLIC_BOX_FLAG_TOUCHED_FREE, with
 * sound 0x0c). */
void PublicBox_TouchPlace(PublicBox *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_TOUCH_HOLD);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = PublicBox_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = PublicBox_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    if (PublicBox_PlaceIsLocked(self, place)) {
        PublicBox_ClearFlags(self, PUBLIC_BOX_FLAG_TOUCHED_FREE);
    } else {
        PublicBox_SetFlags(self, PUBLIC_BOX_FLAG_TOUCHED_FREE);
        PocketsSound_Play0c();
    }
}
CLEAN_AS(func_ov110_0229d7b8, PublicBox_TouchPlace)

/* func_ov110_0229d840: the end of an action: back to the cursor (sub state 4) while state flag 2
 * is set, else to the touch (sub state 0). */
void PublicBox_EndAction(PublicBox *self)
{
    if (StateFlags_IsClear2()) {
        PublicBox_EndActionHidden(self);
    } else {
        PublicBox_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov110_0229d840, PublicBox_EndAction)

/* func_ov110_0229d860: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup updated, sub state 4 and the cursor's place lifted. */
void PublicBox_EndActionAtCursor(PublicBox *self)
{
    self->popup_place = PUBLIC_BOX_NO_PLACE;
    PublicBox_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(pbox_scene(self));
    PublicBox_UpdatePopup(self);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_BROWSE);
    PublicBox_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov110_0229d860, PublicBox_EndActionAtCursor)

/* func_ov110_0229d894: the cursor sprite hidden, nothing lifted, sub state 0. */
void PublicBox_EndActionHidden(PublicBox *self)
{
    PublicBox_HideCursorSprite(self);
    PublicBox_ClearSelection(self);
    MenuScene_SetSubState(pbox_scene(self), PUBLIC_BOX_SUB_TOUCH_IDLE);
}
CLEAN_AS(func_ov110_0229d894, PublicBox_EndActionHidden)
