/* The pockets scene of overlay 096 (pockets_screen.h): its destructors, its flags, the cursor's
 * moves, the choices it opens and the actions they run. */
#include "pockets_screen.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/camera_control.h"
#include "main/catch_panel.h"
#include "main/cell_layer_sprite.h"
#include "main/current_pockets.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/item_traits.h"
#include "main/label_sprite.h"
#include "main/layer_load_task.h"
#include "main/letter_view.h"
#include "main/menu_backdrop.h"
#include "main/player_actor_ops.h"
#include "main/player_messages.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_kinds.h"
#include "main/screen_panels.h"
#include "main/session.h"
#include "main/sliding_window.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/tile_requests.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"
#include "ov094/pockets_common.h"
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"
#include "ov097/pockets_room.h"
#include "ov098/pockets_town.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(PocketsScreen, flags) == 0x94, "flags");
static_assert(offsetof(PocketsScreen, menu_x) == 0xa4 && offsetof(PocketsScreen, item) == 0xac, "place");
static_assert(offsetof(PocketsScreen, cursor) == 0xb5 && offsetof(PocketsScreen, action) == 0xbb, "cursor");
static_assert(offsetof(PocketsScreen, choice_code) == 0xbe && offsetof(PocketsScreen, unk_c4) == 0xc4, "choice");
static_assert(offsetof(PocketsScreen, grid) == 0x358 && offsetof(PocketsScreen, letters) == 0xdb8, "ov094 objects");
static_assert(offsetof(PocketsScreen, popup) == 0x2418 && offsetof(PocketsScreen, glide) == 0x24e8, "popup");
static_assert(offsetof(PocketsScreen, cursor_sprite) == 0x2500 && offsetof(PocketsScreen, choice) == 0x2564, "sprite");
static_assert(offsetof(PocketsScreen, entries) == 0x294c && offsetof(PocketsScreen, error) == 0x2958, "entries");
static_assert(sizeof(ErrorMessage) == 0x11c && offsetof(PocketsScreen, unk_2a74) == 0x2a74, "error");
static_assert(offsetof(PocketsScreen, blink) == 0xc1 && offsetof(PocketsScreen, unk_2e8) == 0x2e8, "blink");
static_assert(offsetof(PocketsScreen, unk_2a74) == 0x2a74 && offsetof(PocketsScreen, button) == 0x2d9c, "button");
static_assert(offsetof(PocketsScreen, held_letter) == 0x2e28 && offsetof(PocketsScreen, unk_2f28) == 0x2f28, "tail");
static_assert(offsetof(PocketsScreen, unk_2e20) == 0x2e20 && sizeof(PocketsScreen) == 0x3028, "size");
static_assert(offsetof(PocketsScreen, wipe_y) == 0x98 && offsetof(PocketsScreen, open_delay) == 0xc2, "wipe");

/* The item codes some actions test (main/item_code.h). What the ranges hold is not known. */
#define ITEM_NONE 0xfff1
#define ITEM_RECORD_2410_FIRST 0x11a8 /* the range of the player record's item at 0x2410 */
#define ITEM_RECORD_2410_LAST 0x12a7
#define ITEM_PILE_FIRST 0x1000
#define ITEM_PILE_LAST 0x10ff
#define ITEM_151F 0x151f
#define ITEM_156C 0x156c
#define ITEM_SLOT4_FIRST 0x1429 /* the record's item at 0x240a */
#define ITEM_SLOT4_LAST 0x1430
#define ITEM_SLOT5_FIRST 0x13a0 /* the record's item at 0x2406 */
#define ITEM_SLOT5_LAST 0x13a7

/* Bell bags: 108 codes whose value in bells func_0204c878 gives; func_0204c120 makes the bag
 * of an amount. Bags below 1000 bells and the others do not merge. */
#define ITEM_BAG_FIRST 0x1492
#define ITEM_BAG_LAST 0x14fd /* the biggest bag */
#define SMALL_BAG_LIMIT 1000
#define WALLET_MAX 99999 /* the most bells a wallet holds (func_02098aa0) */
/* Ten codes of one counted item, holding 1-10 of it. */
#define ITEM_COUNTED_FIRST 0x1531
#define ITEM_COUNTED_LAST 0x153a
#define COUNTED_MAX 10

/* The scene's vtable. */
extern const u8 data_ov096_022a23e8[];

/* The table of actions (member_pointer.h): its guard, the table (one array of 34 at
 * 0x022a24c4, which the symbol table cuts at 0x022a2544 and 0x022a25c4) and its constants. */
extern u32 data_ov096_022a2468;
extern MemberPointer data_ov096_022a24c4[POCKETS_ACTION_COUNT];
extern const MemberPointer data_ov096_022a21a0, data_ov096_022a2198, data_ov096_022a2190, data_ov096_022a2188,
    data_ov096_022a2100, data_ov096_022a2278, data_ov096_022a2170, data_ov096_022a2168, data_ov096_022a2160,
    data_ov096_022a2158, data_ov096_022a2150, data_ov096_022a2148, data_ov096_022a2140, data_ov096_022a2200,
    data_ov096_022a2130, data_ov096_022a2128, data_ov096_022a2120, data_ov096_022a2118, data_ov096_022a21b0,
    data_ov096_022a2108, data_ov096_022a20f8, data_ov096_022a2280, data_ov096_022a20f0, data_ov096_022a20e8,
    data_ov096_022a20e0, data_ov096_022a2138, data_ov096_022a20d0, data_ov096_022a20c8, data_ov096_022a2110,
    data_ov096_022a22d8, data_ov096_022a20b0, data_ov096_022a20d8, data_ov096_022a20b8, data_ov096_022a20c0;

/* 0: the ov098 way (func_ov098_...), else the ov097 way when func_020b67d4 allows it. */
extern u8 data_020e54a8;
extern NetSession *data_020ccf94;

/* The members' destructors, and main's. */
extern void func_02066688(void *object); /* sets the vtable data_020de760 */

/* Letters (0x100 bytes; kind at 0xfa, attached item at 0xfc). */
extern void func_020665f0(void *letter, int pile_item);
extern void func_020665b8(void *letter);
extern u8 func_02065ec0(void *letter);
extern u16 func_02065f18(void *letter);

/* Others of main's. */
extern int CARD_IsEnabled(void);            /* the byte at 0x1f4 of the object at data_021c67a4 is set */
extern void RtcSendPxiCommand(int command); /* func_020f1fb4(&data_021fd1bc, command) */

/* The scene's own, outside these functions. Its Clean version (PocketsScreen_GridIndex) takes
 * the 16-bit halves its matching source declares, so it is called by its symbol with the whole
 * scene pointer, as the ROM's callers do. */
extern int func_ov096_0229f7ac(PocketsScreen *self, int place);

/* The touch (main's bytes; data_021f6c58/54 as overlay_task.c reads them, data_021f6c60/5c as
 * label_button.c does) and a byte of main's set to 0 by func_020b93e8. */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;
extern u8 data_021f6c30;

/* Letters (0x100 bytes): copy, state bits. */
extern int func_02066830(void *dst, const void *src);
extern unsigned int func_02065f08(void *letter);

/* The objects of ov094's at 0x358 (the grid and the places 0x22-0x25), 0xdb8 (the letters)
 * and 0xde0 (the wallet's display). */
extern void func_ov094_0229b5e8(void *letters, int x, int y, void *letter);

static PagedChoice *choice_of(PocketsScreen *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static MenuScene *scene_of(PocketsScreen *self)
{
    return &self->base;
}

/* The members' destructors, last member first, then the base's. */
static void destroy_members(PocketsScreen *self)
{
    self->base.vtable = data_ov096_022a23e8;
    func_02066688(self->unk_2f28);
    func_02066688(self->held_letter);
    LabelButton0_Destroy(&self->button);
    LetterView_Destruct((LetterView *) (void *) self->unk_2a74);
    ErrorMessage_Destruct(&self->error);
    PagedChoice_Destroy(choice_of(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    PocketsWallet_Destruct((PocketsWallet *) (void *) self->unk_de0);
    /* The ROM calls 0x0229bc30, ov094's function (ov094 is the overlay of the objects next to
     * it); the matching source of func_ov096_0229c180 names ov128's at the same address. */
    PocketsLetters_Destruct((PocketsLetters *) (void *) self->letters);
    PocketsGrid_Destruct((PocketsGrid *) (void *) self->grid);
    MenuScene_DestroyBase(scene_of(self));
}

/* func_ov096_0229c180 */
PocketsScreen *PocketsScreen_Destroy(PocketsScreen *self)
{
    destroy_members(self);
    return self;
}
CLEAN_AS(func_ov096_0229c180, PocketsScreen_Destroy)

/* func_ov096_0229c22c */
PocketsScreen *PocketsScreen_Delete(PocketsScreen *self)
{
    destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov096_0229c22c, PocketsScreen_Delete)

/* func_ov096_0229c2dc */
void PocketsScreen_ClearFlags(PocketsScreen *self, unsigned int flags)
{
    self->flags &= ~flags;
}
CLEAN_AS(func_ov096_0229c2dc, PocketsScreen_ClearFlags)

/* func_ov096_0229c2ec */
void PocketsScreen_SetFlags(PocketsScreen *self, unsigned int flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov096_0229c2ec, PocketsScreen_SetFlags)

/* func_ov096_0229c2fc: whether any of `flags` is set. */
int PocketsScreen_TestFlags(PocketsScreen *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov096_0229c2fc, PocketsScreen_TestFlags)

/* func_ov096_0229c310: whether the cursor may go to place 0x21: 0xb1 is 2, 0xb0 is 0 and the
 * item is in 0x11a8-0x12a7. */
int PocketsScreen_CanReachPlace21(PocketsScreen *self)
{
    return self->held_kind == POCKETS_HELD_ITEM && self->held_state == 0 && self->item >= ITEM_RECORD_2410_FIRST &&
           self->item <= ITEM_RECORD_2410_LAST;
}
CLEAN_AS(func_ov096_0229c310, PocketsScreen_CanReachPlace21)

/* func_ov096_0229c348: hands the scene's item to func_0206f190 (which may store it as the
 * player record's item at 0x2410); when the record's item was in 0x11a8-0x12a7 before, it
 * becomes the scene's item. Then command 0x6b. */
void PocketsScreen_SwapRecordItem(PocketsScreen *self)
{
    u16 old = *PlayerRecord_Item2410((u8 *) PlayerRecords_Current());
    u16 given = self->item;
    MenuBackdrop_QueueDesign(&given, (LayerTaskPair *) (void *) self->unk_320, self->unk_e8, (u16 *) (void *) self->unk_c8);
    if (old >= ITEM_RECORD_2410_FIRST && old <= ITEM_RECORD_2410_LAST) {
        self->item = old;
        PocketsScreen_ReturnHeld(self, 1);
    } else {
        PocketsScreen_DropHeld(self);
    }
    RtcSendPxiCommand(0x6b);
}
CLEAN_AS(func_ov096_0229c348, PocketsScreen_SwapRecordItem)

/* func_ov096_0229c3c4: when a change is pending, makes the byte CARD_IsEnabled reads what
 * POCKETS_FLAG_SWITCH_ON asks: func_0203ac2c when it is set and not wanted, func_0203ac44 when
 * it is clear and wanted. */
void PocketsScreen_ApplySwitch(PocketsScreen *self)
{
    if (!PocketsScreen_TestFlags(self, POCKETS_FLAG_SWITCH_PENDING)) {
        return;
    }
    if (CARD_IsEnabled()) {
        if (!PocketsScreen_TestFlags(self, POCKETS_FLAG_SWITCH_ON)) {
            CameraControl_RestoreView();
        }
    } else {
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_SWITCH_ON)) {
            CameraControl_SaveView();
        }
    }
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_SWITCH_PENDING);
}
CLEAN_AS(func_ov096_0229c3c4, PocketsScreen_ApplySwitch)

/* func_ov096_0229c414 */
void PocketsScreen_RequestSwitchOff(PocketsScreen *self)
{
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_SWITCH_ON);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_SWITCH_PENDING);
}
CLEAN_AS(func_ov096_0229c414, PocketsScreen_RequestSwitchOff)

/* func_ov096_0229c434 */
void PocketsScreen_RequestSwitchOn(PocketsScreen *self)
{
    PocketsScreen_SetFlags(self, POCKETS_FLAG_SWITCH_ON);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_SWITCH_PENDING);
}
CLEAN_AS(func_ov096_0229c434, PocketsScreen_RequestSwitchOn)

/* func_ov096_0229c454: one item of the pile at the previous place goes with the letter at the
 * place picked: the letter is set up with the pile's item (func_020665f0), the choice code is
 * applied to it, and the previous place is left with a pile of one less (nothing when it held
 * one). */
void PocketsScreen_PutPileInLetter(PocketsScreen *self)
{
    int letter = PocketsScreen_SlotLetter(self);
    u16 pile = PocketsScreen_PlaceItem(self, self->prev_slot);
    int pile_item = ItemCode_PileItem(&pile);
    func_020665f0((void *) (uintptr_t) letter, (u8) pile_item);
    PagedChoice_Apply(choice_of(self), (void *) (uintptr_t) letter, self->choice_code);
    GroupParams_SetPointer((u32) letter);
    PocketsScreen_SwitchTab(self, 8);
    PocketsScreen_ClearParentByte94(self);
    unsigned int count = (unsigned int) ItemCode_PileCount(&pile);
    int left = count <= 1 ? ITEM_NONE : ItemCode_MakePile(pile_item, (int) (count - 1));
    PocketsScreen_SetPlaceItem(self, self->prev_slot, left, 0);
}
CLEAN_AS(func_ov096_0229c454, PocketsScreen_PutPileInLetter)

/* func_ov096_0229c4dc: the letter at the place picked, or 0 when it is not a letter's. */
int PocketsScreen_SlotLetter(PocketsScreen *self)
{
    return PocketsScreen_PlaceLetter(self, self->slot);
}
CLEAN_AS(func_ov096_0229c4dc, PocketsScreen_SlotLetter)

/* func_ov096_0229c4ec */
void PocketsScreen_ExitToParent(PocketsScreen *self)
{
    PocketsScreen_PressButton(self);
    MenuTabs_SelectTab((MenuTabs *) Process_GetParent((Process *) (void *) self), 7);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_EXITING);
}
CLEAN_AS(func_ov096_0229c4ec, PocketsScreen_ExitToParent)

/* func_ov096_0229c514: sub state 0x21, the button's animation 2, command 0x29. */
void PocketsScreen_PressButton(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), 0x21);
    LabelSprite_SetState((LabelSprite *) (void *) &self->button, 2);
    RtcSendPxiCommand(0x29);
}
CLEAN_AS(func_ov096_0229c514, PocketsScreen_PressButton)

/* func_ov096_0229c538 (action 3) */
void PocketsScreen_FinishScene(PocketsScreen *self)
{
    MenuScene_SetState(scene_of(self), 5);
    MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_STATES);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_80);
    PocketsScreen_ClearParentByte94(self);
}
CLEAN_AS(func_ov096_0229c538, PocketsScreen_FinishScene)

/* func_ov096_0229c560: moves the cursor by the d-pad keys `keys` (KeyRepeatKey) in the part it
 * is in; whether it moved. `mode` (0-2) is handed to the moves. */
int PocketsScreen_MoveCursor(PocketsScreen *self, int keys, int mode)
{
    u8 old = self->cursor;
    PocketsScreen_ClearFlags(self, POCKETS_FLAGS_WRAPPED);
    if (keys == 0) {
        return 0;
    }
    if (PocketsScreen_IsGridPlace(self, self->cursor)) {
        PocketsScreen_MoveCursorInGrid(self, keys, (unsigned int) mode);
    } else if (PocketsScreen_IsLetterPlace(self, self->cursor)) {
        PocketsScreen_MoveCursorInLetters(self, keys, mode);
    } else if (PocketsScreen_IsRowPlace(self, self->cursor)) {
        PocketsScreen_MoveCursorInRow(self, keys, mode);
    } else if (PocketsScreen_IsTopPlace(self, self->cursor)) {
        PocketsScreen_MoveCursorAtPlaces(self, keys, mode);
    } else if (self->cursor == POCKETS_PLACE_21) {
        if (KeyRepeat_HasRight(keys)) {
            self->cursor = POCKETS_GRID_LAST - POCKETS_GRID_COLUMNS + 1; /* 0x0a */
        } else if (KeyRepeat_HasLeft(keys)) {
            self->cursor = POCKETS_LETTERS_LAST;
            PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
        }
    }
    return old != self->cursor;
}
CLEAN_AS(func_ov096_0229c560, PocketsScreen_MoveCursor)

/* func_ov096_0229c63c: at places 0x22-0x25. */
void PocketsScreen_MoveCursorAtPlaces(PocketsScreen *self, int keys, int mode)
{
    u8 place = self->cursor;

    if (place == POCKETS_PLACE_PLAYER) {
        if (KeyRepeat_HasLeft(keys)) {
            if (PocketsScreen_CanReachBells(self, mode)) {
                self->cursor = POCKETS_PLACE_BELLS;
            } else {
                PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
                self->cursor = 0x10;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor = 0x0f;
        } else if (KeyRepeat_HasUp(keys)) {
            if (mode == 0) {
                PocketsScreen_CursorToSpriteColumn(self);
                Glider_TurnToSetC(&self->cursor_sprite);
            }
        } else if (KeyRepeat_HasDown(keys)) {
            self->cursor = PocketsScreen_CanReachPlace22(self, mode) ? POCKETS_PLACE_22 : 0x04;
        }
    } else if (place == POCKETS_PLACE_22 || place == POCKETS_PLACE_23) {
        if (KeyRepeat_HasLeft(keys)) {
            if (PocketsScreen_CanReachBells(self, mode)) {
                self->cursor = POCKETS_PLACE_BELLS;
            } else {
                PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
                self->cursor = 0x12;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor = 0x11;
        } else if (KeyRepeat_HasUp(keys)) {
            if (PocketsScreen_CanReachPlayer(self, mode)) {
                self->cursor = POCKETS_PLACE_PLAYER;
            }
        } else if (KeyRepeat_HasDown(keys)) {
            self->cursor = 0x04;
        }
    } else if (place == POCKETS_PLACE_BELLS) {
        if (KeyRepeat_HasLeft(keys)) {
            PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
            self->cursor = 0x12;
        } else if (KeyRepeat_HasRight(keys)) {
            if (PocketsScreen_CanReachPlace22(self, mode)) {
                self->cursor = POCKETS_PLACE_22;
            } else if (PocketsScreen_CanReachPlayer(self, mode)) {
                self->cursor = POCKETS_PLACE_PLAYER;
            } else {
                self->cursor = 0x11;
            }
        } else if (KeyRepeat_HasUp(keys)) {
            if (mode == 0) {
                PocketsScreen_CursorToSpriteColumn(self);
                Glider_TurnToSetC(&self->cursor_sprite);
            }
        } else if (KeyRepeat_HasDown(keys)) {
            self->cursor = 0x01;
        }
    }
}
CLEAN_AS(func_ov096_0229c63c, PocketsScreen_MoveCursorAtPlaces)

/* func_ov096_0229c7e0: in the row of eight: left and right stop at its ends; down leaves it,
 * to the letters from its last two places, to the bells' place from its first and to the
 * player's place from the others, and turns the cursor sprite. */
void PocketsScreen_MoveCursorInRow(PocketsScreen *self, int keys, int mode)
{
    (void) mode;
    if (KeyRepeat_HasLeft(keys)) {
        if (self->cursor > POCKETS_ROW_FIRST) {
            self->cursor--;
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (self->cursor < POCKETS_ROW_LAST) {
            self->cursor++;
        }
    }
    if (KeyRepeat_HasDown(keys)) {
        switch (self->cursor - POCKETS_ROW_FIRST) {
            case 7:
                self->cursor = 0x10;
                break;
            case 6:
                self->cursor = 0x0f;
                break;
            case 0:
                self->cursor = POCKETS_PLACE_BELLS;
                break;
            default:
                self->cursor = POCKETS_PLACE_PLAYER;
                break;
        }
        Glider_TurnToSetA(&self->cursor_sprite);
    }
}
CLEAN_AS(func_ov096_0229c7e0, PocketsScreen_MoveCursorInRow)

/* From the letters' rows 0 and 1 to the places 0x22-0x25, as PocketsScreen_CanReachPlace22 and
 * PocketsScreen_CanReachPlayer (both asked) allow; whether either did.
 * QUIRK: "both" is the bitwise and of their results, as in the game. */
static int letters_to_places(PocketsScreen *self, int row, int mode)
{
    int to_22 = PocketsScreen_CanReachPlace22(self, mode);
    int to_player = PocketsScreen_CanReachPlayer(self, mode);
    if ((to_22 & to_player) != 0) {
        self->cursor = row == 0 ? POCKETS_PLACE_PLAYER : POCKETS_PLACE_22;
    } else if (to_22 != 0) {
        self->cursor = POCKETS_PLACE_22;
    } else if (to_player != 0) {
        self->cursor = POCKETS_PLACE_PLAYER;
    } else {
        return 0;
    }
    return 1;
}

/* func_ov096_0229c888: in the letters (two columns of five rows). Left and right move between
 * the columns; past the edges rows 2-4 go to the grid's rows 0-2 and rows 0 and 1 to the
 * places 0x22-0x25 (right over the edge wraps; from the last row it may go to place 0x21).
 * Mode 2 does not leave the letters sideways. Up and down move by rows, up from row 0 when
 * mode is 0 calling PocketsScreen_CursorToSpriteColumn and turning the cursor sprite; not after a wrap.
 * The row tested by up and down is the one the cursor started in. */
void PocketsScreen_MoveCursorInLetters(PocketsScreen *self, int keys, int mode)
{
    int index = (int) self->cursor - POCKETS_LETTERS_FIRST;
    int row = index >> 1;
    int column = index & 1;

    if (KeyRepeat_HasLeft(keys)) {
        if (column == 1) {
            self->cursor--;
        } else if (mode != 2) {
            if (row >= 2) {
                self->cursor = (u8) ((row - 2) * POCKETS_GRID_COLUMNS + 4);
            } else if (!letters_to_places(self, row, mode)) {
                self->cursor = PocketsScreen_CanReachBells(self, mode) != 0 ? POCKETS_PLACE_BELLS : 0x04;
            }
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (column == 0) {
            self->cursor++;
        } else if (mode != 2) {
            PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_RIGHT);
            if (row < 2) {
                if (PocketsScreen_CanReachBells(self, mode) != 0) {
                    self->cursor = POCKETS_PLACE_BELLS;
                } else if (!letters_to_places(self, row, mode)) {
                    self->cursor = POCKETS_GRID_FIRST;
                }
            } else {
                if (row == 4 && PocketsScreen_CanReachPlace21(self)) {
                    self->cursor = POCKETS_PLACE_21;
                    return;
                }
                self->cursor = (u8) ((row - 2) * POCKETS_GRID_COLUMNS);
            }
        }
    }

    if (!PocketsScreen_IsLetterPlace(self, self->cursor) || PocketsScreen_TestFlags(self, POCKETS_FLAGS_WRAPPED)) {
        return;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= 2;
        } else if (mode == 0) {
            PocketsScreen_CursorToSpriteColumn(self);
            Glider_TurnToSetC(&self->cursor_sprite);
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (row < POCKETS_LETTER_ROWS - 1) {
            self->cursor += 2;
        }
    }
}
CLEAN_AS(func_ov096_0229c888, PocketsScreen_MoveCursorInLetters)

/* func_ov096_0229ca78: in the grid (three rows of five). Left from the first column wraps to
 * the letters' right column two rows down (from the last row it may go to place 0x21 instead);
 * right from the last column goes to their left column. Left with up held does nothing from
 * rows 1 and 2, right with down held nothing at all. Up and down move by rows, from the first
 * row up to the places 0x22-0x25; not after a wrap. */
void PocketsScreen_MoveCursorInGrid(PocketsScreen *self, int keys, unsigned int mode)
{
    int column = self->cursor % POCKETS_GRID_COLUMNS;
    int row = self->cursor / POCKETS_GRID_COLUMNS;

    if (KeyRepeat_HasLeft(keys)) {
        if (!(KeyRepeat_HasUp(keys) && row != 0)) {
            if (column == 0) {
                if (row == 2 && PocketsScreen_CanReachPlace21(self)) {
                    self->cursor = POCKETS_PLACE_21;
                    return;
                }
                self->cursor = (u8) ((row + 2) * 2 + 0x10);
                PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
            } else {
                self->cursor--;
                column--;
            }
        }
    } else if (KeyRepeat_HasRight(keys) && !KeyRepeat_HasDown(keys)) {
        if (column == POCKETS_GRID_COLUMNS - 1) {
            self->cursor = (u8) ((row + 2) * 2 + 0x0f);
        } else {
            self->cursor++;
            column++;
        }
    }

    if (!PocketsScreen_IsGridPlace(self, self->cursor) || PocketsScreen_TestFlags(self, POCKETS_FLAGS_WRAPPED)) {
        return;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= POCKETS_GRID_COLUMNS;
            return;
        }
        if (column <= 2 && PocketsScreen_CanReachBells(self, (int) mode) != 0) {
            self->cursor = POCKETS_PLACE_BELLS;
            return;
        }
        if (PocketsScreen_CanReachPlace22(self, (int) mode) != 0) {
            self->cursor = POCKETS_PLACE_22;
            return;
        }
        if (PocketsScreen_CanReachPlayer(self, (int) mode) != 0) {
            self->cursor = POCKETS_PLACE_PLAYER;
        }
    } else if (KeyRepeat_HasDown(keys) && row < POCKETS_GRID_ROWS - 1) {
        self->cursor += POCKETS_GRID_COLUMNS;
    }
}
CLEAN_AS(func_ov096_0229ca78, PocketsScreen_MoveCursorInGrid)

/* func_ov096_0229cbbc: this system's slot in the session when the session has it taken, else 0. */
u8 PocketsScreen_LocalSlotIfTaken(PocketsScreen *self)
{
    (void) self;
    int slot = data_020ccf94->local_slot;
    if (Session_IsSlotTaken(data_020ccf94, slot) != 0) {
        return (u8) slot;
    }
    return 0;
}
CLEAN_AS(func_ov096_0229cbbc, PocketsScreen_LocalSlotIfTaken)

/* func_ov096_0229cbe0: opens the choice at its page, sub state 0x22. */
u8 *PocketsScreen_OpenChoicePage(PocketsScreen *self, int wipe)
{
    PocketsScreen_HideCursorSprite(self);
    PagedChoice_OpenPageCentered(choice_of(self), self->choice_page, wipe);
    return MenuScene_SetSubState(scene_of(self), 0x22);
}
CLEAN_AS(func_ov096_0229cbe0, PocketsScreen_OpenChoicePage)

/* func_ov096_0229cc10 */
int PocketsScreen_OpenFirstChoicePage(PocketsScreen *self)
{
    self->choice_page = 0;
    return (int) (uintptr_t) PocketsScreen_OpenChoicePage(self, 1);
}
CLEAN_AS(func_ov096_0229cc10, PocketsScreen_OpenFirstChoicePage)

/* func_ov096_0229cc24 (through action 10): a fixed choice of three rows, texts 0x1a, 0x15 and
 * 0x19, the middle one running action 9. */
void PocketsScreen_OpenFixedMenu(PocketsScreen *self)
{
    PocketsScreen_SetFlags(self, POCKETS_FLAG_FIXED_MENU);
    ChoiceEntries_Clear(&self->entries, POCKETS_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x1a, POCKETS_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0x15, 9);
    ChoiceEntries_Add(&self->entries, 0x19, POCKETS_ACTION_CANCEL);
    PocketsScreen_ShowChoice(self, 0);
}
CLEAN_AS(func_ov096_0229cc24, PocketsScreen_OpenFixedMenu)

/* func_ov096_0229cc74: the choice for `place`: the rows of its part (grid, letters, bells,
 * player; place 0x27 is shown as the bells' place with no rows of its own), else for any other
 * place nothing but the cleared rows. With no row, one row text (0x7c, 0x7b or 0x7a) to cancel;
 * else a last row text 2 to cancel. The choice is put above the popup when `above_popup`, the
 * popup hidden otherwise. */
void PocketsScreen_OpenSlotMenu(PocketsScreen *self, int place, int above_popup)
{
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_FIXED_MENU);
    self->slot = (u8) place;
    ChoiceEntries_Clear(&self->entries, POCKETS_ACTION_CANCEL);

    if (PocketsScreen_IsGridPlace(self, place)) {
        PocketsScreen_AddGridEntries(self, place);
    } else if (PocketsScreen_IsLetterPlace(self, place)) {
        PocketsScreen_AddLetterEntries(self, place);
    } else if (place == POCKETS_PLACE_BELLS) {
        PocketsScreen_AddBellEntries(self);
    } else if (place == POCKETS_PLACE_PLAYER) {
        PocketsScreen_AddPlayerEntries(self);
    } else if (place != POCKETS_PLACE_27) {
        return;
    }

    if (ChoiceEntries_Count(&self->entries) == 0) {
        if (PocketsScreen_IsGridPlace(self, place) || PocketsScreen_IsLetterPlace(self, place)) {
            ChoiceEntries_Add(&self->entries, 0x7c, POCKETS_ACTION_CANCEL);
        } else if (place == POCKETS_PLACE_BELLS || place == POCKETS_PLACE_27) {
            ChoiceEntries_Add(&self->entries, 0x7b, POCKETS_ACTION_CANCEL);
            self->slot = POCKETS_PLACE_BELLS;
        } else if (place == POCKETS_PLACE_PLAYER) {
            ChoiceEntries_Add(&self->entries, 0x7a, POCKETS_ACTION_CANCEL);
        }
    } else {
        ChoiceEntries_Add(&self->entries, 2, POCKETS_ACTION_CANCEL);
    }

    PocketsScreen_HideCursorSprite(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    PocketsScreen_ShowChoice(self, above_popup);
    if (!PocketsScreen_IsGridPlace(self, place) && place != POCKETS_PLACE_PLAYER) {
        PocketsScreen_RequestSwitchOff(self);
    }
}
CLEAN_AS(func_ov096_0229cc74, PocketsScreen_OpenSlotMenu)

/* func_ov096_0229cd8c: a row for each of the record's items 5, 4 and 3 that is not nothing
 * (texts 0x75-0x77, actions 0x11-0x0f). */
void PocketsScreen_AddPlayerEntries(PocketsScreen *self)
{
    if (PocketsScreen_RecordSlotItem(self, 5) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x75, 0x11);
    }
    if (PocketsScreen_RecordSlotItem(self, 4) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x76, 0x10);
    }
    if (PocketsScreen_RecordSlotItem(self, 3) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x77, 0x0f);
    }
}
CLEAN_AS(func_ov096_0229cd8c, PocketsScreen_AddPlayerEntries)

/* func_ov096_0229cdec: the amounts the player's bells allow (texts 0x6e-0x71, actions
 * 0x0b-0x0e: all of them, 100, 1000, 10000). */
void PocketsScreen_AddBellEntries(PocketsScreen *self)
{
    int bells = PocketsScreen_Wallet(self);
    if (bells >= 100) {
        ChoiceEntries_Add(&self->entries, 0x6e, 0x0b);
        ChoiceEntries_Add(&self->entries, 0x6f, 0x0c);
    }
    if (bells >= 1000) {
        ChoiceEntries_Add(&self->entries, 0x70, 0x0d);
    }
    if (bells >= 10000) {
        ChoiceEntries_Add(&self->entries, 0x71, 0x0e);
    }
}
CLEAN_AS(func_ov096_0229cdec, PocketsScreen_AddBellEntries)

/* func_ov096_0229ce4c: the rows for the letter at `place`, by its kind; a row text 0x18
 * (action 6) when an item is attached, else for kinds 1, 3 and 6 the ov098 way's row text 0x15
 * (action 10). */
void PocketsScreen_AddLetterEntries(PocketsScreen *self, int place)
{
    int letter = PocketsScreen_PlaceLetter(self, place);
    void *letter_ptr = (void *) (uintptr_t) letter;
    if (StateFlags_Test2() != 0) {
        ChoiceEntries_Add(&self->entries, 0, 1);
    }
    unsigned int kind = func_02065ec0(letter_ptr);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_08);

    switch (kind) {
        case 0:
            break;
        case 1:
            ChoiceEntries_Add(&self->entries, 0x16, 5);
            ChoiceEntries_Add(&self->entries, 0x20, 4);
            break;
        case 4:
            if (data_020e54a8 == 0) {
                PocketsTown_AddLetterRows(self);
            }
            ChoiceEntries_Add(&self->entries, 0x16, 5);
            if (!PocketsScreen_TestFlags(self, POCKETS_FLAG_08) && func_02065f18(letter_ptr) == ITEM_NONE &&
                data_020e54a8 == 0) {
                ChoiceEntries_Add(&self->entries, 0x15, 0x0a);
            }
            break;
        case 7:
            ChoiceEntries_Add(&self->entries, 0x17, 3);
            break;
        default:
            ChoiceEntries_Add(&self->entries, 0x14, 3);
            break;
    }

    if (func_02065f18(letter_ptr) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x18, 6);
    } else if ((kind == 1 || kind == 3 || kind == 6) && data_020e54a8 == 0) {
        ChoiceEntries_Add(&self->entries, 0x15, 0x0a);
    }
}
CLEAN_AS(func_ov096_0229ce4c, PocketsScreen_AddLetterEntries)

/* func_ov096_0229cf84: the rows for the grid's `place`, by what PocketsScreen_PlaceItemState says of
 * it (0-2) and its item. */
void PocketsScreen_AddGridEntries(PocketsScreen *self, int place)
{
    if (StateFlags_Test2() != 0) {
        ChoiceEntries_Add(&self->entries, 0, 0);
    }
    int kind = PocketsScreen_PlaceItemState(self, place);
    u16 item = PocketsScreen_PlaceItem(self, place);
    if (kind == 0 && item == ITEM_156C) {
        if (CatchPanel_IsStopped((CatchPanel *) (uintptr_t) ScreenPanels_SecondPanel()) != 0) {
            ChoiceEntries_Add(&self->entries, 0xdc, 0x1b);
        } else {
            ChoiceEntries_Add(&self->entries, 0xe1, 0x1c);
        }
    }

    switch (kind) {
        case 0:
            if (PocketsScreen_CanUseItem(self, item) != 0) {
                ChoiceEntries_Add(&self->entries, data_020e54a8 == 0 ? 1 : 0x0a, 2);
            }
            if (data_020e54a8 == 0) {
                PocketsTown_AddItemRows(self, item);
            } else if (SceneKinds_CurrentIsHouseRoom() != 0) {
                PocketsRoom_AddItemRows(self, item);
            }
            if (item >= ITEM_PILE_FIRST && item <= ITEM_PILE_LAST) {
                ChoiceEntries_Add(&self->entries, 0x1c, 7);
            } else if (item == ITEM_151F) {
                ChoiceEntries_Add(&self->entries, 0x1c, 8);
            }
            break;
        case 1:
            ChoiceEntries_Add(&self->entries, 9, 0x14);
            break;
        case 2:
            if (PocketsItem_IsIn155fTo1564(item) == 0) {
                ChoiceEntries_Add(&self->entries, 0x17, 0x14);
            }
            break;
    }
}
CLEAN_AS(func_ov096_0229cf84, PocketsScreen_AddGridEntries)

/* func_ov096_0229d0e4: the command of the action picked; whether its row is to be marked as
 * picked (handed to func_ov002_02209114). */
int PocketsScreen_CueAction(PocketsScreen *self)
{
    switch (self->action) {
        case 18:
        case 19:
            RtcSendPxiCommand(0x50);
            break;
        case 20:
            RtcSendPxiCommand(0x71);
            break;
        case 9:
            RtcSendPxiCommand(0x24);
            return 0;
        case 2:
        case 22:
        case 23:
            RtcSendPxiCommand(0x25);
            return 0;
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
            return 0;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov096_0229d0e4, PocketsScreen_CueAction)

/* func_ov096_0229d16c: command 0x28, the leave code (CHOICE_LEAVE) to apply, the choice asked
 * to close, sub state 0x24. */
void PocketsScreen_CloseChoiceToLeave(PocketsScreen *self)
{
    RtcSendPxiCommand(0x28);
    self->choice_code = CHOICE_LEAVE;
    PagedChoice_RequestClose(choice_of(self), 1);
    MenuScene_SetSubState(scene_of(self), 0x24);
    PocketsScreen_HideCursorSprite(self);
}
CLEAN_AS(func_ov096_0229d16c, PocketsScreen_CloseChoiceToLeave)

/* func_ov096_0229d1a0: command 0x2a, the cancel action, the cursor sprite put back, the choice
 * asked to close, sub state 0x1f. */
void PocketsScreen_CancelChoice(PocketsScreen *self)
{
    RtcSendPxiCommand(0x2a);
    self->action = POCKETS_ACTION_CANCEL;
    PocketsScreen_PlaceCursorSprite(self);
    PagedChoice_RequestClose(choice_of(self), 0);
    MenuScene_SetSubState(scene_of(self), 0x1f);
}
CLEAN_AS(func_ov096_0229d1a0, PocketsScreen_CancelChoice)

/* func_ov096_0229d1d4: shows the rows (the first set apart for the fixed choice) and opens the
 * choice: above (0x68, 0x68) for the bells' place, else above the popup or beside the place. */
void PocketsScreen_ShowChoice(PocketsScreen *self, int above_popup)
{
    PagedChoice *choice = choice_of(self);
    PagedChoice_ShowEntries(choice, &self->entries, PocketsScreen_TestFlags(self, POCKETS_FLAG_FIXED_MENU));
    int x = PocketsScreen_PlaceX(self, self->slot);
    int y = PocketsScreen_PlaceY(self, self->slot);
    if (self->slot == POCKETS_PLACE_BELLS) {
        PagedChoice_PlaceAbove(choice, 0x68, 0x68);
    } else if (above_popup != 0) {
        PagedChoice_PlaceAboveWindow(choice, &self->popup);
    } else {
        PagedChoice_PlaceBeside(choice, x, y);
    }
    PagedChoice_RequestOpen(choice, 0);
    MenuScene_SetSubState(scene_of(self), 0x1d);
}
CLEAN_AS(func_ov096_0229d1d4, PocketsScreen_ShowChoice)

/* func_ov096_0229d268: asks for the switch off (PocketsScreen_ApplySwitch) unless the action is
 * 0, 0x0f-0x11, 0x1a or the cancel; the cancel ends with PocketsScreen_EndAction, any other action
 * runs its member function from the table (filled once):
 *   0, 1    PocketsScreen_BeginSubState12      18      func_ov097_022a2954
 *   2       PocketsScreen_ActionUseItem         19      func_ov097_022a29e4
 *   3       PocketsScreen_FinishScene           20      PocketsScreen_ActionGridSubState2b
 *   4       PocketsScreen_ActionLetterChoice    21      func_ov098_022a2e9c
 *   5       PocketsScreen_ActionLetter05        22      func_ov098_022a2b6c
 *   6       PocketsScreen_ActionToFreeSlot      23      func_ov098_022a2a0c
 *   7       PocketsScreen_ActionNewLetterChoice 24      func_ov098_022a2fa8
 *   8       PocketsScreen_ActionNewLetterFromSlot 25    func_ov098_022a29d0
 *   9       PocketsScreen_ActionLetterSubState2a  26    PocketsScreen_ActionSubState31
 *   10      PocketsScreen_ActionFixedMenu       27      PocketsScreen_ActionMessageMenu
 *   11-14   PocketsScreen_ActionTakeBells       28      PocketsScreen_ActionSendMessage0
 *   15-17   PocketsScreen_ActionTakeRecordItem  29-32   PocketsScreen_ActionSendMessage
 *                                               33      func_ov098_022a28d0
 * REQUIRES: the action is below 34; the game reads past the table for others. */
void PocketsScreen_RunAction(PocketsScreen *self)
{
    static const MemberPointer *const actions[POCKETS_ACTION_COUNT] = {
        &data_ov096_022a21a0, &data_ov096_022a2198, &data_ov096_022a2190, &data_ov096_022a2188, &data_ov096_022a2100,
        &data_ov096_022a2278, &data_ov096_022a2170, &data_ov096_022a2168, &data_ov096_022a2160, &data_ov096_022a2158,
        &data_ov096_022a2150, &data_ov096_022a2148, &data_ov096_022a2140, &data_ov096_022a2200, &data_ov096_022a2130,
        &data_ov096_022a2128, &data_ov096_022a2120, &data_ov096_022a2118, &data_ov096_022a21b0, &data_ov096_022a2108,
        &data_ov096_022a20f8, &data_ov096_022a2280, &data_ov096_022a20f0, &data_ov096_022a20e8, &data_ov096_022a20e0,
        &data_ov096_022a2138, &data_ov096_022a20d0, &data_ov096_022a20c8, &data_ov096_022a2110, &data_ov096_022a22d8,
        &data_ov096_022a20b0, &data_ov096_022a20d8, &data_ov096_022a20b8, &data_ov096_022a20c0,
    };
    u8 action = self->action;
    if (action != POCKETS_ACTION_CANCEL && action != 0 && action != 0x0f && action != 0x10 && action != 0x11 &&
        action != 0x1a) {
        PocketsScreen_RequestSwitchOff(self);
    }
    if (self->action == POCKETS_ACTION_CANCEL) {
        PocketsScreen_EndAction(self);
        return;
    }
    MemberTable_InitOnce(&data_ov096_022a2468, data_ov096_022a24c4, actions, POCKETS_ACTION_COUNT);
    MemberPointer_CallVoid(&data_ov096_022a24c4[self->action], self);
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_0229d268Ev, PocketsScreen_RunAction)

/* func_ov096_0229d4d4 (actions 29-32): message action - 28. */
void PocketsScreen_ActionSendMessage(PocketsScreen *self)
{
    PocketsScreen_SendMessage(self, self->action - 0x1c);
    PocketsScreen_EndAction(self);
}
CLEAN_AS(func_ov096_0229d4d4, PocketsScreen_ActionSendMessage)

/* func_ov096_0229d4f0 (action 28) */
void PocketsScreen_ActionSendMessage0(PocketsScreen *self)
{
    PocketsScreen_SendMessage(self, 0);
    PocketsScreen_EndAction(self);
}
CLEAN_AS(func_ov096_0229d4f0, PocketsScreen_ActionSendMessage0)

/* func_ov096_0229d508: alone, applies mode `message` (PlayerMessages_ApplyMode). Linked, slot 0
 * sends message 0x12 + `message` to player 4 and applies it when "message is 0" differs from
 * func_0208d12c's answer on the object at func_0208b500; any other slot sends 0x0d + `message`
 * to player 0. */
void PocketsScreen_SendMessage(PocketsScreen *self, int message)
{
    (void) self;
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session)) {
        if (session->local_slot == 0) {
            unsigned int is_zero = message == 0;
            if (is_zero != CatchPanel_IsStopped((CatchPanel *) (uintptr_t) ScreenPanels_SecondPanel())) {
                PlayerMessages_Send((u8) (message + 0x12), 4);
                PlayerMessages_ApplyMode(message);
            }
        } else {
            PlayerMessages_Send((u8) (message + 0x0d), 0);
        }
    } else {
        PlayerMessages_ApplyMode(message);
    }
}
CLEAN_AS(func_ov096_0229d508, PocketsScreen_SendMessage)

/* func_ov096_0229d570 (action 27): a choice of texts 0xdd-0xe0 running actions 0x1d-0x20, and
 * text 2 to cancel. */
void PocketsScreen_ActionMessageMenu(PocketsScreen *self)
{
    ChoiceEntries_Clear(&self->entries, POCKETS_ACTION_CANCEL);
    ChoiceEntries_Add(&self->entries, 0xdd, 0x1d);
    ChoiceEntries_Add(&self->entries, 0xde, 0x1e);
    ChoiceEntries_Add(&self->entries, 0xdf, 0x1f);
    ChoiceEntries_Add(&self->entries, 0xe0, 0x20);
    ChoiceEntries_Add(&self->entries, 2, POCKETS_ACTION_CANCEL);
    PocketsScreen_HideCursorSprite(self);
    PocketsScreen_ShowChoice(self, 0);
}
CLEAN_AS(func_ov096_0229d570, PocketsScreen_ActionMessageMenu)

/* func_ov096_0229d5d4 (action 26) */
int PocketsScreen_ActionSubState31(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), 0x31);
    return (int) (uintptr_t) PocketsScreen_HandSlotItemToActor(self);
}
CLEAN_AS(func_ov096_0229d5d4, PocketsScreen_ActionSubState31)

/* func_ov096_0229d5ec (action 10) */
void PocketsScreen_ActionFixedMenu(PocketsScreen *self)
{
    PocketsScreen_OpenFixedMenu(self);
}
CLEAN_AS(func_ov096_0229d5ec, PocketsScreen_ActionFixedMenu)

/* The place picked as the menu's place, two less each way when state flag 2 is set. */
static void set_menu_place(PocketsScreen *self, u8 place)
{
    self->menu_x = PocketsScreen_PlaceX(self, place);
    self->menu_y = PocketsScreen_PlaceY(self, place);
    if (StateFlags_Test2()) {
        self->menu_x -= 2;
        self->menu_y -= 2;
    }
}

/* func_ov096_0229d5f4 (action 9): sub state 0x2a, with the letters' object. */
void PocketsScreen_ActionLetterSubState2a(PocketsScreen *self)
{
    u8 place = self->slot;
    PocketsScreen_PickUpLetter(self, place);
    set_menu_place(self, place);
    MenuScene_SetSubState(scene_of(self), 0x2a);
    PocketsLetters_StartPickUp((PocketsLetters *) (void *) self->letters);
}
CLEAN_AS(func_ov096_0229d5f4, PocketsScreen_ActionLetterSubState2a)

/* func_ov096_0229d664 (action 20): sub state 0x2b, with the grid's object, the item and 0xb0. */
void PocketsScreen_ActionGridSubState2b(PocketsScreen *self)
{
    u8 place = self->slot;
    PocketsScreen_PickUpItem(self, place);
    set_menu_place(self, place);
    MenuScene_SetSubState(scene_of(self), 0x2b);
    PocketsGrid_StartPickUp((PocketsGrid *) (void *) self->grid, self->item, self->held_state);
}
CLEAN_AS(func_ov096_0229d664, PocketsScreen_ActionGridSubState2b)

/* func_ov096_0229d6dc (actions 15-17: the record's items 3, 4 and 5): with no free pocket slot
 * the action ends with message 0xa and command 0x73, unless the record's item is in its range
 * (0x1429-0x1430 for 4, 0x13a0-0x13a7 for 5); else the free slot is kept, the item cleared and
 * flag 0x8000 set. */
void PocketsScreen_ActionTakeRecordItem(PocketsScreen *self)
{
    int need_slot = 1;
    u16 item;

    switch (self->action) {
        case 0x0f:
            self->record_slot = 3;
            break;
        case 0x10:
            self->record_slot = 4;
            item = (u16) PocketsScreen_RecordSlotItem(self, 4);
            if (item >= ITEM_SLOT4_FIRST && item <= ITEM_SLOT4_LAST) {
                need_slot = 0;
            }
            break;
        case 0x11:
            self->record_slot = 5;
            item = (u16) PocketsScreen_RecordSlotItem(self, 5);
            if (item >= ITEM_SLOT5_FIRST && item <= ITEM_SLOT5_LAST) {
                need_slot = 0;
            }
            break;
        default:
            PocketsScreen_EndAction(self);
            return;
    }

    int free_slot = PocketsScreen_FreePocketSlot(self);
    if (need_slot && free_slot == POCKETS_NO_PLACE) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, 0x0a, 0xff, 0);
        RtcSendPxiCommand(0x73);
    } else {
        self->held_place = (u8) free_slot;
        PocketsScreen_DropHeld(self);
        self->item = ITEM_NONE;
        PocketsScreen_BeginSubState25(self);
        PocketsScreen_SetFlags(self, POCKETS_FLAG_8000);
    }
}
CLEAN_AS(func_ov096_0229d6dc, PocketsScreen_ActionTakeRecordItem)

/* func_ov096_0229d7d0 (actions 11-14): the item func_0204c120 makes of all the bells, 100,
 * 1000 or 10000 goes to a free pocket slot; with none, the action ends with message 0xc.
 * REQUIRES: the action is 11-14 (the game would use an unset value otherwise). */
void PocketsScreen_ActionTakeBells(PocketsScreen *self)
{
    int item = 0;
    switch (self->action) {
        case 0x0b:
            item = ItemTraits_BellBagFor(PocketsScreen_Wallet(self), 0, NULL);
            break;
        case 0x0c:
            item = ItemTraits_BellBagFor(100, 0, NULL);
            break;
        case 0x0d:
            item = ItemTraits_BellBagFor(1000, 0, NULL);
            break;
        case 0x0e:
            item = ItemTraits_BellBagFor(10000, 0, NULL);
            break;
    }
    int free_slot = PocketsScreen_FreePocketSlot(self);
    if (free_slot == POCKETS_NO_PLACE) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, 0x0c, 0xff, 1);
    } else {
        PocketsScreen_TakeBagFromWallet(self, item);
        PocketsScreen_HoldAndGlide(self, POCKETS_PLACE_BELLS, free_slot, item, 0);
    }
}
CLEAN_AS(func_ov096_0229d7d0, PocketsScreen_ActionTakeBells)

/* func_ov096_0229d878 (action 8): with a free letter, sets it up (func_020665b8) and hands it
 * on. */
void PocketsScreen_ActionNewLetterFromSlot(PocketsScreen *self)
{
    if (PocketsScreen_MoveToFreeLetter(self)) {
        int letter = PocketsScreen_SlotLetter(self);
        func_020665b8((void *) (uintptr_t) letter);
        GroupParams_SetPointer((u32) letter);
        PocketsScreen_EmptyPlace(self, self->prev_slot);
        PocketsScreen_SwitchTab(self, 8);
        PocketsScreen_ClearParentByte94(self);
    }
}
CLEAN_AS(func_ov096_0229d878, PocketsScreen_ActionNewLetterFromSlot)

/* func_ov096_0229d8bc (action 7): with a free letter, opens the choice for it. */
void PocketsScreen_ActionNewLetterChoice(PocketsScreen *self)
{
    if (PocketsScreen_MoveToFreeLetter(self) != 0) {
        GroupParams_SetPointer((u32) PocketsScreen_SlotLetter(self));
        PocketsScreen_OpenFirstChoicePage(self);
        PocketsScreen_SetFlags(self, POCKETS_FLAG_200);
    }
}
CLEAN_AS(func_ov096_0229d8bc, PocketsScreen_ActionNewLetterChoice)

/* func_ov096_0229d8ec: picks the first free letter, the place picked before kept as the
 * previous one; with none the action ends with message 2. Whether there was one. */
int PocketsScreen_MoveToFreeLetter(PocketsScreen *self)
{
    int letter = CurrentPockets_FreeLetterIndex();
    if (letter == -1) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, 2, 0xff, 1);
        return 0;
    }
    GroupParams_SetC50((char) self->slot);
    self->prev_slot = self->slot;
    self->slot = (u8) (letter + POCKETS_LETTERS_FIRST);
    return 1;
}
CLEAN_AS(func_ov096_0229d8ec, PocketsScreen_MoveToFreeLetter)

/* func_ov096_0229d93c (action 6): the place's item to a free pocket slot; with none the action
 * ends with message 0xb. */
void PocketsScreen_ActionToFreeSlot(PocketsScreen *self)
{
    int free_slot = PocketsScreen_FreePocketSlot(self);
    if (free_slot == POCKETS_NO_PLACE) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, 0x0b, 0xff, 1);
        return;
    }
    int kind = PocketsScreen_PlaceItemState(self, self->slot);
    int item = PocketsScreen_PlaceItem(self, self->slot);
    PocketsScreen_EmptyPlace(self, self->slot);
    PocketsScreen_HoldAndGlide(self, self->slot, free_slot, item, kind);
}
CLEAN_AS(func_ov096_0229d93c, PocketsScreen_ActionToFreeSlot)

/* func_ov096_0229d9a0 (action 5) */
void PocketsScreen_ActionLetter05(PocketsScreen *self)
{
    GroupParams_SetC50((char) self->slot);
    GroupParams_SetPointer((u32) PocketsScreen_SlotLetter(self));
    PocketsScreen_SwitchTab(self, 8);
    PocketsScreen_ClearParentByte94(self);
}
CLEAN_AS(func_ov096_0229d9a0, PocketsScreen_ActionLetter05)

/* func_ov096_0229d9cc (action 4) */
void PocketsScreen_ActionLetterChoice(PocketsScreen *self)
{
    GroupParams_SetPointer((u32) PocketsScreen_SlotLetter(self));
    PocketsScreen_OpenFirstChoicePage(self);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_200);
}
CLEAN_AS(func_ov096_0229d9cc, PocketsScreen_ActionLetterChoice)

/* func_ov096_0229d9f0 (action 2): when the place's item can be used (else message 9), by
 * PocketsScreen_CheckUseItem: 2 starts sub state 0x28 with flag 0x1000, any other non-zero
 * answer hands the place's grid index to the grid's object and ends the action. */
void PocketsScreen_ActionUseItem(PocketsScreen *self)
{
    u8 place = self->slot;
    int item = PocketsScreen_PlaceItem(self, place);
    if (PocketsScreen_CanUseItem(self, (unsigned int) item) == 0) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, 9, 0xff, 1);
        return;
    }
    int how = PocketsScreen_CheckUseItem(self, item);
    if (how == 0) {
        return;
    }
    if (how == 2) {
        MenuScene_SetSubState(scene_of(self), 0x28);
        PocketsScreen_SetFlags(self, POCKETS_FLAG_1000);
    } else {
        PocketsGrid_EmptyPlace((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov096_0229d9f0, PocketsScreen_ActionUseItem)

/* func_ov096_0229da6c: the ov098 way asks func_020435fc (with this system's session slot): -1
 * ends the action with message 3 and command 0x73 and answers 0, else 2. The ov097 way, when
 * func_020b67d4 allows it, answers func_ov097_022a27fc; else 0. */
int PocketsScreen_CheckUseItem(PocketsScreen *self, int item)
{
    if (data_020e54a8 == 0) {
        self->unk_c4 = TileRequests_AskDrop(data_020ccf94->local_slot, item);
        if (self->unk_c4 == -1) {
            PocketsScreen_EndAction(self);
            PocketsScreen_ShowError(self, 3, 0xff, 0);
            RtcSendPxiCommand(0x73);
            return 0;
        }
        return 2;
    }
    if (SceneKinds_CurrentIsHouseRoom() != 0) {
        return PocketsRoom_CheckUseItem(self, item);
    }
    return 0;
}
CLEAN_AS(func_ov096_0229da6c, PocketsScreen_CheckUseItem)

/* func_ov096_0229daec: by func_ov098_022a31d8 the ov098 way, by func_ov097_022a27c0 the ov097
 * way when func_020b67d4 allows it, else no. */
int PocketsScreen_CanUseItem(PocketsScreen *self, unsigned int item)
{
    if (data_020e54a8 == 0) {
        return PocketsTown_CanUseItem(self, item);
    }
    if (SceneKinds_CurrentIsHouseRoom() != 0) {
        return PocketsRoom_CanUse(self) != 0;
    }
    return 0;
}
CLEAN_AS(func_ov096_0229daec, PocketsScreen_CanUseItem)

/* func_ov096_0229db30: the popup hidden, the sub state kept at 0xba, `value` at 0xb7, the
 * cursor sprite's animation 6, sub state 0x15. */
void PocketsScreen_BeginSubState15(PocketsScreen *self, u8 value)
{
    Popup_Hide(&self->popup, 1);
    self->return_state = self->base.sub_state;
    self->unk_b7 = value;
    Glider_SetAnim(&self->cursor_sprite, 6);
    MenuScene_SetSubState(scene_of(self), 0x15);
}
CLEAN_AS(func_ov096_0229db30, PocketsScreen_BeginSubState15)

/* func_ov096_0229db78 */
void PocketsScreen_BeginSubState14(PocketsScreen *self, int value)
{
    Popup_Hide(&self->popup, 1);
    self->unk_b7 = (u8) value;
    Glider_SetAnim(&self->cursor_sprite, 5);
    MenuScene_SetSubState(scene_of(self), 0x14);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_2000);
}
CLEAN_AS(func_ov096_0229db78, PocketsScreen_BeginSubState14)

/* func_ov096_0229dbc0 (actions 0 and 1) */
void PocketsScreen_BeginSubState12(PocketsScreen *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_TURN_A);
    MenuScene_SetSubState(scene_of(self), 0x12);
    self->unk_b9 = POCKETS_NO_PLACE;
}
CLEAN_AS(func_ov096_0229dbc0, PocketsScreen_BeginSubState12)

/* func_ov096_0229dbe8 */
void PocketsScreen_BeginSubState11(PocketsScreen *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), 0x11);
}
CLEAN_AS(func_ov096_0229dbe8, PocketsScreen_BeginSubState11)

/* func_ov096_0229dc08 */
void PocketsScreen_BeginSubState10(PocketsScreen *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(scene_of(self), 0x10);
}
CLEAN_AS(func_ov096_0229dc08, PocketsScreen_BeginSubState10)

/* func_ov096_0229dc28: the first animation of the cursor sprite's set, then the sprite's update
 * through its class (vtable slot 3, Glider_Update for the base). */
void PocketsScreen_ShowCursorFirstOfSet(PocketsScreen *self)
{
    Glider *sprite = &self->cursor_sprite;
    Glider_ShowFirstOfSet(sprite);
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}
CLEAN_AS(func_ov096_0229dc28, PocketsScreen_ShowCursorFirstOfSet)

/* func_ov096_0229dc48: the cursor sprite put at the cursor (PocketsScreen_CursorSpriteX,
 * PocketsScreen_CursorSpriteY), animation 1. */
void PocketsScreen_PlaceCursorSprite(PocketsScreen *self)
{
    int x = PocketsScreen_CursorSpriteX(self);
    int y = PocketsScreen_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov096_0229dc48, PocketsScreen_PlaceCursorSprite)

/* func_ov096_0229dc7c: the cursor sprite put at the choice's row 1 when the choice is the fixed
 * one (its first row set apart), else at row 0; animation 7. */
void PocketsScreen_PointAtDefaultRow(PocketsScreen *self)
{
    self->choice_row = (u8) PocketsScreen_TestFlags(self, POCKETS_FLAG_FIXED_MENU);
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov096_0229dc7c, PocketsScreen_PointAtDefaultRow)

/* func_ov096_0229dce0: the cancel action, the choice's last row picked and the cursor sprite
 * put at it, showing animation 8 from its last frame; sub state 0x1e. */
void PocketsScreen_PointAtCancelRow(PocketsScreen *self)
{
    self->action = POCKETS_ACTION_CANCEL;
    self->choice_row = PagedChoice_PickLastRow(choice_of(self), 1);
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    CellLayerSprite_SetAnimAtEnd((CellLayerSprite *) (void *) &self->cursor_sprite, 8);
    MenuScene_SetSubState(scene_of(self), 0x1e);
}
CLEAN_AS(func_ov096_0229dce0, PocketsScreen_PointAtCancelRow)

/* func_ov096_0229dd44: the cursor sprite moves to the choice row in 2 steps; the sub state is
 * kept at 0xba and sub state 0x0f waits for the move. */
void PocketsScreen_GlideToRow(PocketsScreen *self)
{
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_MoveTo(&self->cursor_sprite, x, y, 2);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), 0x0f);
}
CLEAN_AS(func_ov096_0229dd44, PocketsScreen_GlideToRow)

/* func_ov096_0229dd94: the cursor sprite eases to the cursor in 3 steps (cue 1); the sub
 * state is kept at 0xba and sub state 0x0f waits for the move. */
void PocketsScreen_GlideToCursor(PocketsScreen *self)
{
    int x = PocketsScreen_CursorSpriteX(self);
    int y = PocketsScreen_CursorSpriteY(self);
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_state = self->base.sub_state;
    MenuScene_SetSubState(scene_of(self), 0x0f);
}
CLEAN_AS(func_ov096_0229dd94, PocketsScreen_GlideToCursor)

/* func_ov096_0229ddd8: the cursor sprite's animation 0, then its update through its class
 * (vtable slot 3). */
void PocketsScreen_HideCursorSprite(PocketsScreen *self)
{
    Glider *sprite = &self->cursor_sprite;
    Glider_SetAnim(sprite, GLIDER_ANIM_NONE);
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}
CLEAN_AS(func_ov096_0229ddd8, PocketsScreen_HideCursorSprite)

/* func_ov096_0229ddfc: the cursor sprite's y, the cursor's place's. */
int PocketsScreen_CursorSpriteY(PocketsScreen *self)
{
    return PocketsScreen_PlaceY(self, self->cursor);
}
CLEAN_AS(func_ov096_0229ddfc, PocketsScreen_CursorSpriteY)

/* func_ov096_0229de0c: the cursor sprite's x: the cursor's place's plus 8, and a screen width
 * (256) further right or left when this move wrapped over the right or left edge. */
int PocketsScreen_CursorSpriteX(PocketsScreen *self)
{
    int x = PocketsScreen_PlaceX(self, self->cursor);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_WRAPPED_RIGHT)) {
        x += 0x100;
    } else if (PocketsScreen_TestFlags(self, POCKETS_FLAG_WRAPPED_LEFT)) {
        x -= 0x100;
    }
    return x + 8;
}
CLEAN_AS(func_ov096_0229de0c, PocketsScreen_CursorSpriteX)

/* func_ov096_0229de50: the cursor sprite put at the choice's last row, animation 7.
 * QUIRK: the row is kept as a byte; with no row it is 0xff. */
void PocketsScreen_PointAtLastRow(PocketsScreen *self)
{
    self->choice_row = (u8) (PagedChoice_RowCount(choice_of(self)) - 1);
    int x = PagedChoice_TextX(choice_of(self));
    int y = PagedChoice_RowY(choice_of(self), self->choice_row);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
}
CLEAN_AS(func_ov096_0229de50, PocketsScreen_PointAtLastRow)

/* func_ov096_0229dea4: the cursor sprite put at the cursor, animation 13 in the row of eight
 * and 1 elsewhere, then the first of its set. */
void PocketsScreen_ShowCursorSprite(PocketsScreen *self)
{
    int x = PocketsScreen_CursorSpriteX(self);
    int y = PocketsScreen_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (PocketsScreen_IsRowPlace(self, self->cursor)) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_C);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    PocketsScreen_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov096_0229dea4, PocketsScreen_ShowCursorSprite)

/* Whether `item` is in first-last. */
static int item_in(u16 item, u16 first, u16 last)
{
    return item >= first && item <= last;
}

/* The count of a counted item (1-10). */
static int counted_count(u16 item)
{
    return item - ITEM_COUNTED_FIRST + 1;
}

/* func_ov096_0229defc: puts the item `*onto` (in state `held_state`) on the item `*other` (in
 * state `other_state`); only items both in state 0 merge. Two counted items make one of up to
 * 10 in `*onto` and the rest in `*other` (nothing when none is left). Two bell bags make the
 * bags of their sum (func_0204c120 rounding up), the first holding up to 1000 bells for small
 * bags or the biggest bag's value for big ones, the second the rest. Answers 0 when merged, 1
 * when the items do not merge, 2 when one bag is small (below 1000 bells) and the other not,
 * 3 when either is already the biggest bag. */
int PocketsScreen_MergeItems(PocketsScreen *self, u16 *onto, int held_state, u16 *other, u8 other_state)
{
    (void) self;
    if (held_state != 0 || other_state != 0) {
        return 1;
    }
    u16 a = *onto;
    u16 b = *other;

    if (item_in(a, ITEM_COUNTED_FIRST, ITEM_COUNTED_LAST) && item_in(b, ITEM_COUNTED_FIRST, ITEM_COUNTED_LAST)) {
        int count = counted_count(a) + counted_count(b);
        int rest = 0;
        if (count > COUNTED_MAX) {
            rest = count - COUNTED_MAX;
            count = COUNTED_MAX;
        }
        *onto = (u16) (ITEM_COUNTED_FIRST + count - 1);
        *other = rest > 0 ? (u16) (ITEM_COUNTED_FIRST + rest - 1) : ITEM_NONE;
        return 0;
    }

    if (!item_in(a, ITEM_BAG_FIRST, ITEM_BAG_LAST) || !item_in(b, ITEM_BAG_FIRST, ITEM_BAG_LAST)) {
        return 1;
    }
    u16 biggest = ITEM_BAG_LAST;
    int bells_a = ItemTraits_Price(&a);
    int bells_b = ItemTraits_Price(&b);
    int bells_max = ItemTraits_Price(&biggest);
    if ((bells_a < SMALL_BAG_LIMIT) != (bells_b < SMALL_BAG_LIMIT)) {
        return 2;
    }
    if (bells_a == bells_max || bells_b == bells_max) {
        return 3;
    }
    int limit = bells_a < SMALL_BAG_LIMIT ? SMALL_BAG_LIMIT : bells_max;
    int sum = bells_a + bells_b;
    int rest = 0;
    if (sum > limit) {
        rest = sum - limit;
        sum = limit;
    }
    int spare;
    *onto = (u16) ItemTraits_BellBagFor(sum, 1, &spare);
    *other = rest == 0 ? ITEM_NONE : (u16) ItemTraits_BellBagFor(rest, 1, &spare);
    return 0;
}
CLEAN_AS(func_ov096_0229defc, PocketsScreen_MergeItems)

/* func_ov096_0229e0a8: the bag's bells go into the wallet; what passes 99999 comes back as the
 * smallest bag holding it (func_0204c120 rounding up, the wallet giving the difference), else
 * nothing (0xfff1). Answers that bag. */
int PocketsScreen_AddBagToWallet(PocketsScreen *self, u16 bag)
{
    unsigned int bells = (unsigned int) ItemTraits_Price(&bag);
    unsigned int total = bells + (unsigned int) PocketsScreen_Wallet(self);
    int back = ITEM_NONE;
    if (total > WALLET_MAX) {
        unsigned int over = total - WALLET_MAX;
        int extra;
        back = ItemTraits_BellBagFor((int) over, 1, &extra);
        total -= over + (unsigned int) extra;
    }
    PocketsScreen_SetWallet(self, (int) total);
    return back;
}
CLEAN_AS(func_ov096_0229e0a8, PocketsScreen_AddBagToWallet)

/* func_ov096_0229e0f8: the bag's bells leave the wallet.
 * QUIRK: the wallet is read twice, the first answer unused. */
void PocketsScreen_TakeBagFromWallet(PocketsScreen *self, u16 bag)
{
    int bells = ItemTraits_Price(&bag);
    PocketsScreen_Wallet(self);
    PocketsScreen_SetWallet(self, PocketsScreen_Wallet(self) - bells);
}
CLEAN_AS(func_ov096_0229e0f8, PocketsScreen_TakeBagFromWallet)

/* func_ov096_0229e128: the current player's wallet set (func_02098aa0 keeps it in 0-99999),
 * then the wallet's display (the object at 0xde0) told. */
void PocketsScreen_SetWallet(PocketsScreen *self, int bells)
{
    PlayerPockets_SetBells((PlayerPockets *) PlayerRecord_Pockets((u8 *) PlayerRecords_Current()), bells, 0);
    PocketsWallet_StartCount((PocketsWallet *) (void *) self->unk_de0, 0);
}
CLEAN_AS(func_ov096_0229e128, PocketsScreen_SetWallet)

/* func_ov096_0229e158: the bells in the current player's wallet. */
int PocketsScreen_Wallet(PocketsScreen *self)
{
    (void) self;
    return PlayerPockets_Bells((PlayerPockets *) PlayerRecord_Pockets((u8 *) PlayerRecords_Current()), 0);
}
CLEAN_AS(func_ov096_0229e158, PocketsScreen_Wallet)

/* Whether the scene holds an item in state 0. */
static int holds_plain_item(PocketsScreen *self)
{
    return self->held_kind == POCKETS_HELD_ITEM && self->held_state == 0;
}

/* func_ov096_0229e170: whether the scene holds a bell bag in state 0 and, when `fits_wallet`,
 * the wallet can take its bells without passing 99999.
 * QUIRK: the sum is compared unsigned. */
int PocketsScreen_HoldsBellBag(PocketsScreen *self, int fits_wallet)
{
    if (!holds_plain_item(self)) {
        return 0;
    }
    u16 bag = self->item;
    if (!item_in(bag, ITEM_BAG_FIRST, ITEM_BAG_LAST)) {
        return 0;
    }
    if (fits_wallet != 0) {
        int bells = ItemTraits_Price(&bag);
        if ((unsigned int) (bells + PocketsScreen_Wallet(self)) > WALLET_MAX) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov096_0229e170, PocketsScreen_HoldsBellBag)

/* func_ov096_0229e1ec: the held bag goes into the wallet. All of it: the scene lets go and
 * ends the action (PocketsScreen_EndAction); else the bag of what is left stays held, shown by the
 * grid's object, and glides back to its place (PocketsScreen_GlideHeldTo, 4 steps). Answers 1.
 * QUIRK: the bag's bells are asked once more first, the answer unused. */
int PocketsScreen_PutBagInWallet(PocketsScreen *self)
{
    u16 bag = self->item;
    ItemTraits_Price(&bag);
    int back = PocketsScreen_AddBagToWallet(self, self->item);
    if (back == ITEM_NONE) {
        PocketsScreen_DropHeld(self);
        PocketsScreen_EndAction(self);
    } else {
        self->item = (u16) back;
        PocketsGrid_SetHeldIcon((PocketsGrid *) (void *) self->grid, self->item, self->held_state);
        PocketsScreen_GlideHeldTo(self, self->held_place, 4);
    }
    return 1;
}
CLEAN_AS(func_ov096_0229e1ec, PocketsScreen_PutBagInWallet)

/* func_ov096_0229e258: main's value at data_021cfc74 set to the held item's bells when it is a
 * bell bag, else 0. The held kind is not looked at. */
void PocketsScreen_PublishHeldBells(PocketsScreen *self)
{
    u16 bag = self->item;
    if (item_in(bag, ITEM_BAG_FIRST, ITEM_BAG_LAST)) {
        GroupParams_SetHeldBells(ItemTraits_Price(&bag));
        return;
    }
    GroupParams_SetHeldBells(0);
}
CLEAN_AS(func_ov096_0229e258, PocketsScreen_PublishHeldBells)

/* func_ov096_0229e29c: the action ends, the held thing goes back (and is let go), and when the
 * held item fits no record slot (record_slot 0) message 7. */
void PocketsScreen_RefuseRecordSlot(PocketsScreen *self)
{
    PocketsScreen_EndAction(self);
    PocketsScreen_ReturnHeld(self, 1);
    if (self->record_slot == 0) {
        PocketsScreen_ShowError(self, 7, 0xff, 1);
    }
}
CLEAN_AS(func_ov096_0229e29c, PocketsScreen_RefuseRecordSlot)

/* func_ov096_0229e2c8: whether the player's field actor (func_02096718(4)) is in a state that
 * lets record slot `record_slot` change: state 0x3f for slot 5, not state 5 for slots 7 and
 * 8, func_02095f58's test for the others. */
int PocketsScreen_ActorReadyForSlot(PocketsScreen *self, int record_slot)
{
    (void) self;
    switch (record_slot) {
        case 5:
            return PlayerActorOps_InState3F();
        case 7:
        case 8:
            return PlayerActorOps_InState5() == 0;
        default:
            return PlayerActorOps_EarlyInState7();
    }
}
CLEAN_AS(func_ov096_0229e2c8, PocketsScreen_ActorReadyForSlot)

/* func_ov096_0229e2fc: asks the player's field actor to take `item` for record slot
 * `record_slot` (main's requests of it); whether it was asked. Slot 6 also clears slot 4's
 * item; slot 7, when CARD_IsEnabled's byte is clear, sends command 0x40; slot 8 hands nothing. */
int PocketsScreen_ActorTakeSlotItem(PocketsScreen *self, unsigned int record_slot, u16 item)
{
    (void) self;
    u16 asked = item;
    switch (record_slot) {
        case 2:
            return PlayerActorOps_RequestState7Kind0Next5(&asked) != 0;
        case 3:
            return PlayerActorOps_RequestState7Kind1Next5(&asked) != 0;
        case 6:
            if (PlayerActorOps_RequestState7Kind1Next5(&asked) != 0) {
                asked = ITEM_NONE;
                PlayerActorOps_RequestState7Kind2Next5(&asked);
                return 1;
            }
            return 0;
        case 4:
            return PlayerActorOps_RequestState7Kind2Next5(&asked) != 0;
        case 5:
            return PlayerActorOps_RequestState3F(&asked) != 0;
        case 7:
            if (PlayerActorOps_RequestState85(&asked) != 0) {
                if (CARD_IsEnabled() == 0) {
                    RtcSendPxiCommand(0x40);
                }
                return 1;
            }
            return 0;
        case 8:
            return PlayerActorOps_RequestState7NoItem() != 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov096_0229e2fc, PocketsScreen_ActorTakeSlotItem)

/* func_ov096_0229e3b0: `item` goes into the current player's record slot `record_slot` (2 at
 * 0x2408, 3 at 0x240c, 4 at 0x240a; 6 puts it in slot 3 and clears slot 4; 5 writes nothing).
 * Answers the item that was there (slot 4's for 6), nothing when it is not to come back:
 * slot 2's outside 0x11a8-0x12a7, slot 4's in 0x1429-0x1430 and slot 5's in 0x13a0-0x13a7. */
int PocketsScreen_SwapRecordSlot(PocketsScreen *self, int record_slot, int item)
{
    int old = PocketsScreen_RecordSlotItem(self, record_slot);
    int record = (int) (uintptr_t) PlayerRecords_Current();
    u16 value = (u16) item;
    switch (record_slot) {
        case 2:
            PlayerRecord_SetClothes((u8 *) (uintptr_t) record, &value);
            if (!item_in((u16) old, ITEM_RECORD_2410_FIRST, ITEM_RECORD_2410_LAST)) {
                old = ITEM_NONE;
            }
            break;
        case 3:
            PlayerRecord_SetPartCItem((u8 *) (uintptr_t) record, &value);
            break;
        case 6:
            PlayerRecord_SetPartCItem((u8 *) (uintptr_t) record, &value);
            old = PocketsScreen_RecordSlotItem(self, 4);
            value = ITEM_NONE;
            PlayerRecord_SetHeadItem((u8 *) (uintptr_t) record, &value);
            break;
        case 4:
            PlayerRecord_SetHeadItem((u8 *) (uintptr_t) record, &value);
            if (item_in((u16) old, ITEM_SLOT4_FIRST, ITEM_SLOT4_LAST)) {
                old = ITEM_NONE;
            }
            break;
        case 5:
            if (item_in((u16) old, ITEM_SLOT5_FIRST, ITEM_SLOT5_LAST)) {
                old = ITEM_NONE;
            }
            break;
        default:
            break;
    }
    return old;
}
CLEAN_AS(func_ov096_0229e3b0, PocketsScreen_SwapRecordSlot)

/* func_ov096_0229e4a4: the item in the current player's record slot `record_slot` (2: 0x2408,
 * 3: 0x240c, 4: 0x240a, 5: 0x2406), nothing for the others. */
int PocketsScreen_RecordSlotItem(PocketsScreen *self, int record_slot)
{
    (void) self;
    int record = (int) (uintptr_t) PlayerRecords_Current();
    switch (record_slot) {
        case 2:
            return *PlayerRecord_Clothes((u8 *) (uintptr_t) record);
        case 3:
            return *PlayerRecord_PartCItem((u8 *) (uintptr_t) record);
        case 4:
            return *PlayerRecord_HeadItem((u8 *) (uintptr_t) record);
        case 5:
            return *PlayerRecord_HeldItem((u8 *) (uintptr_t) record);
        default:
            return ITEM_NONE;
    }
}
CLEAN_AS(func_ov096_0229e4a4, PocketsScreen_RecordSlotItem)

/* func_ov096_0229e4f8: the record slot the held item (in state 0) goes to, 1 when none:
 *   0x11a8-0x12a7                  2
 *   0x1431-0x1491                  3, or 6 (3 and clearing 4) when slot 4 holds an item of
 *                                  0x13a8-0x13c7 that func_0204c4c0 does not accept
 *   0x13a8-0x13c7                  4, or 0 when slot 3 holds something and func_0204c4c0 does
 *                                  not accept the held item
 *   0x13c8-0x1428                  4
 *   func_0204c4e8 accepts it       5
 *   0x1518-0x151c, 0x1531-0x1541   7
 *   0x155e                         8 */
int PocketsScreen_HeldRecordSlot(PocketsScreen *self)
{
    if (!holds_plain_item(self)) {
        return 1;
    }
    u16 item = self->item;
    if (item_in(item, ITEM_RECORD_2410_FIRST, ITEM_RECORD_2410_LAST)) {
        return 2;
    }
    if (item_in(item, 0x1431, 0x1491)) {
        u16 slot4 = (u16) PocketsScreen_RecordSlotItem(self, 4);
        if (slot4 != ITEM_NONE && item_in(slot4, 0x13a8, 0x13c7) && ItemTraits_IsHeadAUnk07Is8(&slot4) == 0) {
            return 6;
        }
        return 3;
    }
    if (item_in(item, 0x13a8, 0x13c7)) {
        if ((u16) PocketsScreen_RecordSlotItem(self, 3) != ITEM_NONE && ItemTraits_IsHeadAUnk07Is8(&item) == 0) {
            return 0;
        }
        return 4;
    }
    if (item_in(item, 0x13c8, 0x1428)) {
        return 4;
    }
    if (ItemTraits_HasHeldModel(&item) != 0) {
        return 5;
    }
    if (item_in(item, 0x1518, 0x151c) || item_in(item, 0x1531, 0x1541)) {
        return 7;
    }
    if (item == 0x155e) {
        return 8;
    }
    return 1;
}
CLEAN_AS(func_ov096_0229e4f8, PocketsScreen_HeldRecordSlot)

/* func_ov096_0229e67c: sub state 0x25, PocketsScreen_GiveToRecordSlot, flag 0x8000 cleared. */
void PocketsScreen_BeginSubState25(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), 0x25);
    PocketsScreen_GiveToRecordSlot(self);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_8000);
}
CLEAN_AS(func_ov096_0229e67c, PocketsScreen_BeginSubState25)

/* func_ov096_0229e6a0: the scene lets go of what it holds; main's held bells (data_021cfc74)
 * become 0. */
void PocketsScreen_DropHeld(PocketsScreen *self)
{
    self->held_kind = POCKETS_HELD_NONE;
    GroupParams_SetHeldBells(0);
}
CLEAN_AS(func_ov096_0229e6a0, PocketsScreen_DropHeld)

/* func_ov096_0229e6b0: whether the held item (in state 0) can be used
 * (PocketsScreen_CanUseItem); never a bell bag that came from the wallet. */
int PocketsScreen_CanUseHeld(PocketsScreen *self)
{
    if (!holds_plain_item(self)) {
        return 0;
    }
    if (item_in(self->item, ITEM_BAG_FIRST, ITEM_BAG_LAST) && self->held_place == POCKETS_PLACE_BELLS) {
        return 0;
    }
    return PocketsScreen_CanUseItem(self, self->item);
}
CLEAN_AS(func_ov096_0229e6b0, PocketsScreen_CanUseHeld)

/* func_ov096_0229e71c: uses the held item. When it cannot be used, message 9 and the item goes
 * back. By PocketsScreen_CheckUseItem: 1 lets go of it (answers 1), 2 starts sub state 0x28
 * with flag 0x1000 cleared, 0 and others put it back. Answers whether it was used up. */
int PocketsScreen_UseHeld(PocketsScreen *self)
{
    if (PocketsScreen_CanUseHeld(self) == 0) {
        PocketsScreen_EndAction(self);
        PocketsScreen_ShowError(self, 9, 0xff, 1);
        PocketsScreen_ReturnHeld(self, 1);
        return 0;
    }
    switch (PocketsScreen_CheckUseItem(self, self->item)) {
        case 1:
            PocketsScreen_DropHeld(self);
            return 1;
        case 2:
            MenuScene_SetSubState(scene_of(self), 0x28);
            PocketsScreen_ClearFlags(self, POCKETS_FLAG_1000);
            return 0;
        default:
            PocketsScreen_ReturnHeld(self, 1);
            return 0;
    }
}
CLEAN_AS(func_ov096_0229e71c, PocketsScreen_UseHeld)

/* func_ov096_0229e79c: puts the held thing down at `place` (PocketsScreen_PutHeldItemAt for an item,
 * PocketsScreen_PutHeldLetterAt for a letter); whether it was put down. */
int PocketsScreen_PutHeldAt(PocketsScreen *self, int place)
{
    switch (self->held_kind) {
        case POCKETS_HELD_ITEM:
            return PocketsScreen_PutHeldItemAt(self, place);
        case POCKETS_HELD_LETTER:
            return PocketsScreen_PutHeldLetterAt(self, place);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov096_0229e79c, PocketsScreen_PutHeldAt)

/* func_ov096_0229e7c4: the held thing changes places with what is at `place`: a held letter
 * (its copy kept at 0x2f28 first) picks up what is there, then the copy goes there; a held
 * item picks up the item there, then goes there. */
void PocketsScreen_SwapHeldWith(PocketsScreen *self, int place)
{
    switch (self->held_kind) {
        case POCKETS_HELD_LETTER:
            func_02066830(self->unk_2f28, self->held_letter);
            PocketsScreen_PickUpAt(self, place);
            PocketsScreen_PutLetterAt(self, place, self->unk_2f28);
            break;
        case POCKETS_HELD_ITEM: {
            u16 item = self->item;
            u8 state = self->held_state;
            PocketsScreen_PickUpItemAt(self, place);
            PocketsScreen_SetPlaceItem(self, place, item, state);
            break;
        }
    }
}
CLEAN_AS(func_ov096_0229e7c4, PocketsScreen_SwapHeldWith)

/* func_ov096_0229e82c: the held thing goes back to its place (let go when `drop`). When
 * PocketsScreen_CheckReturnHeld refuses that and a place is kept at 0xb9, the thing at 0xb9
 * goes to the held thing's place, the held thing to 0xb9 (let go), and 0xb9 is cleared. */
void PocketsScreen_ReturnHeld(PocketsScreen *self, int drop)
{
    if (PocketsScreen_CheckReturnHeld(self, self->held_place) == 0) {
        PocketsScreen_PlaceHeldAt(self, self->held_place, drop);
        return;
    }
    if (self->unk_b9 != POCKETS_NO_PLACE) {
        int item = PocketsScreen_PlaceItem(self, self->unk_b9);
        int state = PocketsScreen_PlaceItemState(self, self->unk_b9);
        PocketsScreen_PlaceHeldAt(self, self->unk_b9, 1);
        PocketsScreen_SetPlaceItem(self, self->held_place, item, state);
        self->unk_b9 = POCKETS_NO_PLACE;
    }
}
CLEAN_AS(func_ov096_0229e82c, PocketsScreen_ReturnHeld)

/* func_ov096_0229e898: the held thing put at `place` (a letter by PocketsScreen_PutLetterAt, an item
 * by PocketsScreen_SetPlaceItem), and let go when `drop`. */
void PocketsScreen_PlaceHeldAt(PocketsScreen *self, int place, int drop)
{
    switch (self->held_kind) {
        case POCKETS_HELD_LETTER:
            PocketsScreen_PutLetterAt(self, place, self->held_letter);
            break;
        case POCKETS_HELD_ITEM:
            PocketsScreen_SetPlaceItem(self, place, self->item, self->held_state);
            break;
    }
    if (drop) {
        PocketsScreen_DropHeld(self);
    }
}
CLEAN_AS(func_ov096_0229e898, PocketsScreen_PlaceHeldAt)

/* func_ov096_0229e8e0: picks up the item at a place of the grid or of the letters. */
void PocketsScreen_PickUpItemAt(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place) || PocketsScreen_IsLetterPlace(self, place)) {
        PocketsScreen_PickUpItem(self, place);
    }
}
CLEAN_AS(func_ov096_0229e8e0, PocketsScreen_PickUpItemAt)

/* func_ov096_0229e90c: picks up what is at `place`: the grid's item, the letter, or at the
 * bells' place the place's item, whose bells leave the wallet. */
void PocketsScreen_PickUpAt(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        PocketsScreen_PickUpItem(self, place);
    } else if (PocketsScreen_IsLetterPlace(self, place)) {
        PocketsScreen_PickUpLetter(self, (unsigned int) place);
    } else if (place == POCKETS_PLACE_BELLS) {
        PocketsScreen_PickUpItem(self, place);
        PocketsScreen_TakeBagFromWallet(self, self->item);
    }
}
CLEAN_AS(func_ov096_0229e90c, PocketsScreen_PickUpAt)

/* func_ov096_0229e95c: holds a copy of the letter at `place`, which the letters' object then
 * lets go of (func_ov094_0229b890). */
void PocketsScreen_PickUpLetter(PocketsScreen *self, unsigned int place)
{
    int index = PocketsScreen_LetterIndex(self, (int) place);
    self->held_kind = POCKETS_HELD_LETTER;
    func_02066830(self->held_letter, (void *) PocketsLetters_LetterAt((PocketsLetters *) (void *) self->letters, index));
    PocketsLetters_ClearPlace((PocketsLetters *) (void *) self->letters, index);
}
CLEAN_AS(func_ov096_0229e95c, PocketsScreen_PickUpLetter)

/* func_ov096_0229e9a0: holds the item at `place` with its state, the place emptied
 * (PocketsScreen_EmptyPlace), the grid's object shows it and main is told its bells. */
void PocketsScreen_PickUpItem(PocketsScreen *self, int place)
{
    self->held_kind = POCKETS_HELD_ITEM;
    self->item = PocketsScreen_PlaceItem(self, place);
    self->held_state = (u8) PocketsScreen_PlaceItemState(self, place);
    PocketsScreen_EmptyPlace(self, place);
    PocketsGrid_SetHeldIcon((PocketsGrid *) (void *) self->grid, self->item, self->held_state);
    PocketsScreen_PublishHeldBells(self);
}
CLEAN_AS(func_ov096_0229e9a0, PocketsScreen_PickUpItem)

/* func_ov096_0229e9f8: holds `item` in `state`, shown by the grid's object, main told its
 * bells. */
void PocketsScreen_HoldItem(PocketsScreen *self, u16 item, u8 state)
{
    self->held_kind = POCKETS_HELD_ITEM;
    self->item = item;
    self->held_state = state;
    PocketsGrid_SetHeldIcon((PocketsGrid *) (void *) self->grid, self->item, self->held_state);
    PocketsScreen_PublishHeldBells(self);
}
CLEAN_AS(func_ov096_0229e9f8, PocketsScreen_HoldItem)

/* func_ov096_0229ea34: the held thing drawn where the glide is. */
void PocketsScreen_FollowGlide(PocketsScreen *self)
{
    self->menu_x = Glide_X(&self->glide);
    self->menu_y = Glide_Y(&self->glide);
}
CLEAN_AS(func_ov096_0229ea34, PocketsScreen_FollowGlide)

/* func_ov096_0229ea5c: the held thing drawn at the cursor sprite's frame, 2 left and 4 up;
 * answers the y. */
int PocketsScreen_FollowCursorSprite(PocketsScreen *self)
{
    self->menu_x = Glider_FrameX(&self->cursor_sprite) - 2;
    self->menu_y = Glider_FrameY(&self->cursor_sprite) - 4;
    return self->menu_y;
}
CLEAN_AS(func_ov096_0229ea5c, PocketsScreen_FollowCursorSprite)

/* func_ov096_0229ea88: the held thing drawn at the touch, kept at the offset it was grabbed
 * at. */
void PocketsScreen_FollowTouch(PocketsScreen *self)
{
    self->menu_x = self->grab_dx + data_021f6c58;
    self->menu_y = self->grab_dy + data_021f6c54;
}
CLEAN_AS(func_ov096_0229ea88, PocketsScreen_FollowTouch)

/* func_ov096_0229eab4: draws the held thing (by the grid's object for an item, the letters'
 * for a letter), unless flag 0x40 is set. */
void PocketsScreen_DrawHeld(PocketsScreen *self)
{
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_40)) {
        return;
    }
    switch (self->held_kind) {
        case POCKETS_HELD_ITEM:
            PocketsGrid_DrawHeld((PocketsGrid *) (void *) self->grid, self->menu_x, self->menu_y);
            break;
        case POCKETS_HELD_LETTER:
            func_ov094_0229b5e8(self->letters, self->menu_x, self->menu_y, self->held_letter);
            break;
    }
}
CLEAN_AS(func_ov096_0229eab4, PocketsScreen_DrawHeld)

/* func_ov096_0229eb14: the popup tells of the cursor's place: queued for a taken place of the
 * grid or the letters (kept at 0xb3); its queue cleared for an empty one, the row of eight and
 * the places 0x22-0x25. */
void PocketsScreen_UpdatePopup(PocketsScreen *self)
{
    if (PocketsScreen_IsGridPlace(self, self->cursor) || PocketsScreen_IsLetterPlace(self, self->cursor)) {
        if (PocketsScreen_PlaceIsEmpty(self, self->cursor)) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    }
    if (PocketsScreen_IsRowPlace(self, self->cursor) || PocketsScreen_IsTopPlace(self, self->cursor)) {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov096_0229eb14, PocketsScreen_UpdatePopup)

/* func_ov096_0229eb98: the popup put above its place (0x6d left and 0x78 up of it, 8 more up
 * when state flag 2 is set) and filled by the grid's or the letters' object. */
void PocketsScreen_PlacePopup(PocketsScreen *self)
{
    int x = PocketsScreen_PlaceX(self, self->popup_place) - 0x6d;
    int y = PocketsScreen_PlaceY(self, self->popup_place) - 0x78;
    if (StateFlags_Test2() != 0) {
        y -= 8;
    }
    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->popup, x, y);
    if (PocketsScreen_IsGridPlace(self, self->popup_place)) {
        PocketsGrid_ShowItemText((PocketsGrid *) (void *) self->grid, &self->popup,
                                 func_ov096_0229f7ac(self, self->popup_place));
    } else if (PocketsScreen_IsLetterPlace(self, self->popup_place)) {
        PocketsLetters_ShowPlaceText((PocketsLetters *) (void *) self->letters, &self->popup,
                                     PocketsScreen_LetterIndex(self, self->popup_place));
    }
}
CLEAN_AS(func_ov096_0229eb98, PocketsScreen_PlacePopup)

/* func_ov096_0229ec38: whether main's byte data_021f6c30 is at least `value`. */
int PocketsScreen_Byte6c30AtLeast(PocketsScreen *self, int value)
{
    (void) self;
    return data_021f6c30 >= value;
}
CLEAN_AS(func_ov096_0229ec38, PocketsScreen_Byte6c30AtLeast)

/* The distance between two coordinates. */
static int distance(int a, int b)
{
    return a > b ? a - b : b - a;
}

/* func_ov096_0229ec4c: whether the touch at data_021f6c60/5c is more than 8 pixels from the
 * one at data_021f6c58/54, in x or in y. */
int PocketsScreen_TouchMoved(PocketsScreen *self)
{
    (void) self;
    return distance(data_021f6c60, data_021f6c58) > 8 || distance(data_021f6c5c, data_021f6c54) > 8;
}
CLEAN_AS(func_ov096_0229ec4c, PocketsScreen_TouchMoved)

/* func_ov096_0229ec90: marks `place` in its part's object: the grid's (also the place 0x25 as
 * its 0x21 and 0x21 as its 0x22), the letters', or the wallet's display (0 for 0x22 and 0x23,
 * 1 for 0x24). */
void PocketsScreen_HighlightPlace(PocketsScreen *self, unsigned int place)
{
    if (PocketsScreen_IsGridPlace(self, (int) place)) {
        PocketsGrid_MarkPlace((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, (int) place));
    } else if (PocketsScreen_IsLetterPlace(self, (int) place)) {
        PocketsLetters_MarkPlace((PocketsLetters *) (void *) self->letters, PocketsScreen_LetterIndex(self, (int) place));
    } else if (PocketsScreen_IsTopPlace(self, (int) place)) {
        switch (place) {
            case POCKETS_PLACE_BELLS:
                PocketsGrid_MarkPlace((PocketsGrid *) (void *) self->grid, 0x21);
                break;
            case POCKETS_PLACE_22:
            case POCKETS_PLACE_23:
                PocketsWallet_SetFrame((PocketsWallet *) (void *) self->unk_de0, 0);
                break;
            case POCKETS_PLACE_PLAYER:
                PocketsWallet_SetFrame((PocketsWallet *) (void *) self->unk_de0, 1);
                break;
        }
    } else if (place == POCKETS_PLACE_21) {
        PocketsGrid_MarkPlace((PocketsGrid *) (void *) self->grid, 0x22);
    }
}
CLEAN_AS(func_ov096_0229ec90, PocketsScreen_HighlightPlace)

/* func_ov096_0229ed44: no place marked in the three objects. */
void PocketsScreen_ClearHighlights(PocketsScreen *self)
{
    PocketsGrid_ClearMarks((PocketsGrid *) (void *) self->grid);
    PocketsLetters_ClearMarks((PocketsLetters *) (void *) self->letters);
    PocketsWallet_ShowPlainFrame((PocketsWallet *) (void *) self->unk_de0);
}
CLEAN_AS(func_ov096_0229ed44, PocketsScreen_ClearHighlights)

/* func_ov096_0229ed74: `place` selected in its part's object, the other part's selection
 * cleared; for a place of neither, both cleared. */
void PocketsScreen_SelectPlace(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        int index = func_ov096_0229f7ac(self, place);
        PocketsLetters_Unlift((PocketsLetters *) (void *) self->letters);
        PocketsGrid_Lift((PocketsGrid *) (void *) self->grid, index);
    } else if (PocketsScreen_IsLetterPlace(self, place)) {
        int index = PocketsScreen_LetterIndex(self, place);
        PocketsGrid_Unlift((PocketsGrid *) (void *) self->grid);
        PocketsLetters_Lift((PocketsLetters *) (void *) self->letters, index);
    } else {
        PocketsGrid_Unlift((PocketsGrid *) (void *) self->grid);
        PocketsLetters_Unlift((PocketsLetters *) (void *) self->letters);
    }
}
CLEAN_AS(func_ov096_0229ed74, PocketsScreen_SelectPlace)

/* func_ov096_0229edec */
void PocketsScreen_ClearSelection(PocketsScreen *self)
{
    PocketsGrid_Unlift((PocketsGrid *) (void *) self->grid);
    PocketsLetters_Unlift((PocketsLetters *) (void *) self->letters);
}
CLEAN_AS(func_ov096_0229edec, PocketsScreen_ClearSelection)

/* func_ov096_0229ee10: whether the cursor may go to the bells' place in move mode `mode`:
 * always in mode 0, never in 2, in mode 1 when the scene holds a bell bag. */
int PocketsScreen_CanReachBells(PocketsScreen *self, int mode)
{
    switch (mode) {
        case 0:
            return 1;
        case 1:
            return PocketsScreen_HoldsBellBag(self, 0);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov096_0229ee10, PocketsScreen_CanReachBells)

/* func_ov096_0229ee38: whether the cursor may go to place 0x22: in mode 1, when the held item
 * can be used. */
int PocketsScreen_CanReachPlace22(PocketsScreen *self, int mode)
{
    if (mode == 1) {
        return PocketsScreen_CanUseHeld(self);
    }
    return 0;
}
CLEAN_AS(func_ov096_0229ee38, PocketsScreen_CanReachPlace22)

/* func_ov096_0229ee50: whether the cursor may go to the player's place: always in mode 0, never
 * in 2, in mode 1 when the held item fits a record slot. */
int PocketsScreen_CanReachPlayer(PocketsScreen *self, int mode)
{
    switch (mode) {
        case 0:
            return 1;
        case 1:
            return PocketsScreen_HeldRecordSlot(self) != 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov096_0229ee50, PocketsScreen_CanReachPlayer)

/* func_ov096_0229ee80: PocketsScreen_CheckDrop for the held item at `place`. */
int PocketsScreen_CheckReturnHeld(PocketsScreen *self, int place)
{
    return PocketsScreen_CheckDrop(self, place, self->item, self->held_state);
}
CLEAN_AS(func_ov096_0229ee80, PocketsScreen_CheckReturnHeld)

/* func_ov096_0229ee9c: whether the held item may go to `place` and the item there to `to`
 * (PocketsScreen_CheckDrop's answers; 0 when `place` holds nothing). When `to` is the bells'
 * place, the item at `place` is merged with a copy of the held item first: a refused merge of
 * bags (2 or 3) answers 6, nothing left over answers 0. */
int PocketsScreen_CheckSwap(PocketsScreen *self, int place, int to)
{
    int answer = PocketsScreen_CheckDrop(self, place, self->item, self->held_state);
    if (answer != 0) {
        return answer;
    }
    u16 other = PocketsScreen_PlaceItem(self, place);
    if (other == ITEM_NONE) {
        return 0;
    }
    int state = PocketsScreen_PlaceItemState(self, place);
    if (to == POCKETS_PLACE_BELLS) {
        u16 held = self->item;
        int merged = PocketsScreen_MergeItems(self, &held, self->held_state, &other, (u8) state);
        if (merged == 2 || merged == 3) {
            return 6;
        }
        if (other == ITEM_NONE) {
            return 0;
        }
    }
    return PocketsScreen_CheckDrop(self, to, other, state);
}
CLEAN_AS(func_ov096_0229ee9c, PocketsScreen_CheckSwap)

/* func_ov096_0229ef30: whether `item` in `state` may be put at `place`; 0 yes.
 * A place of the grid: always. A letter's place: 6 when it holds no letter, 5 for state 1, 1
 * for state 2, 3 when the letter has an item attached, 2 when the letter is of kind 7 or 8 or
 * func_ov094_02299a54 refuses the item, 4 when func_ov094_02299b04 does, 5 for a bell bag that
 * came from the wallet. The bells' place: a bell bag in state 0 whose bells fit the wallet,
 * else 6. Other places: 6. */
int PocketsScreen_CheckDrop(PocketsScreen *self, int place, int item, int state)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        return 0;
    }
    if (PocketsScreen_IsLetterPlace(self, place)) {
        if (PocketsScreen_PlaceIsEmpty(self, place)) {
            return 6;
        }
        if (state == 1) {
            return 5;
        }
        if (state == 2) {
            return 1;
        }
        void *letter = (void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place);
        if (func_02065f18(letter) != ITEM_NONE) {
            return 3;
        }
        int kind = func_02065ec0(letter);
        if (kind == 7 || kind == 8 || PocketsItem_Is155d(item) != 0) {
            return 2;
        }
        if (PocketsItem_InLetterRefusedRanges(item) != 0) {
            return 4;
        }
        if (item_in((u16) item, ITEM_BAG_FIRST, ITEM_BAG_LAST) && self->held_place == POCKETS_PLACE_BELLS) {
            return 5;
        }
        return 0;
    }
    if (place == POCKETS_PLACE_BELLS) {
        if (state != 0) {
            return 6;
        }
        u16 bag = (u16) item;
        if (!item_in(bag, ITEM_BAG_FIRST, ITEM_BAG_LAST)) {
            return 6;
        }
        int room = WALLET_MAX - PocketsScreen_Wallet(self);
        if (room < ItemTraits_Price(&bag)) {
            return 6;
        }
        return 0;
    }
    return 6;
}
CLEAN_AS(func_ov096_0229ef30, PocketsScreen_CheckDrop)

/* func_ov096_0229f054: the letter at `place`, 0 when it is not a letter's place. */
int PocketsScreen_PlaceLetter(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsLetterPlace(self, place) == 0) {
        return 0;
    }
    return (int) (uintptr_t) PocketsLetters_LetterAt((PocketsLetters *) (void *) self->letters,
                                                     PocketsScreen_LetterIndex(self, place));
}
CLEAN_AS(func_ov096_0229f054, PocketsScreen_PlaceLetter)

/* func_ov096_0229f088: the state of what is at `place`: the pocket slot's (by the grid's
 * object), the letter's (bits 6-7 of its byte 0xfa), else 0.
 * QUIRK: for other places PocketsScreen_IsTopPlace is asked and its answer unused. */
int PocketsScreen_PlaceItemState(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        return PocketsGrid_ItemState((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (PocketsScreen_IsLetterPlace(self, place)) {
        return func_02065f08((void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place));
    }
    PocketsScreen_IsTopPlace(self, place);
    return 0;
}
CLEAN_AS(func_ov096_0229f088, PocketsScreen_PlaceItemState)

/* func_ov096_0229f0dc: the item at `place`: the grid's (by its object), the item attached to
 * the letter (nothing with no letter), `place_item` at the places 0x22-0x25, else nothing. */
u16 PocketsScreen_PlaceItem(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        return PocketsGrid_Item((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (PocketsScreen_IsLetterPlace(self, place)) {
        if (PocketsScreen_PlaceIsEmpty(self, place)) {
            return ITEM_NONE;
        }
        return func_02065f18((void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place));
    }
    if (PocketsScreen_IsTopPlace(self, place)) {
        return self->place_item;
    }
    return ITEM_NONE;
}
CLEAN_AS(func_ov096_0229f0dc, PocketsScreen_PlaceItem)

/* func_ov096_0229f150: whether `place` of the grid or the letters is empty (by its part's
 * object); other places count as empty. */
int PocketsScreen_PlaceIsEmpty(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        return PocketsGrid_IsEmpty((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (PocketsScreen_IsLetterPlace(self, place)) {
        return PocketsLetters_IsEmpty((PocketsLetters *) (void *) self->letters, PocketsScreen_LetterIndex(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov096_0229f150, PocketsScreen_PlaceIsEmpty)

/* func_ov096_0229f1a8: what the part's object answers for `place` being taken (non-zero:
 * taken, where PocketsScreen_PlaceIsEmpty says 0); 0 for other places. */
int PocketsScreen_PlaceIsTaken(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        return PocketsGrid_IsDimmed((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (PocketsScreen_IsLetterPlace(self, place)) {
        return PocketsLetters_IsDimmed((PocketsLetters *) (void *) self->letters, PocketsScreen_LetterIndex(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f1a8, PocketsScreen_PlaceIsTaken)

/* func_ov096_0229f200: the y of `place`: by the grid's or the letters' object, 8 for the row
 * of eight, by the grid's object for 0x22-0x25, 0xb0 for 0x21, else 0. */
int PocketsScreen_PlaceY(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, place)) {
        return PocketsGrid_PlaceY((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (PocketsScreen_IsLetterPlace(self, place)) {
        return PocketsLetters_PlaceY((PocketsLetters *) (void *) self->letters, PocketsScreen_LetterIndex(self, place));
    }
    if (PocketsScreen_IsRowPlace(self, place)) {
        return 8;
    }
    if (PocketsScreen_IsTopPlace(self, place)) {
        return PocketsGrid_PlaceY((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (place == POCKETS_PLACE_21) {
        return 0xb0;
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f200, PocketsScreen_PlaceY)

/* The objects of ov094's: the grid's (0x358) places under a touch and their x, its slots set
 * and redrawn; the letters' (0xdb8) places under a touch, their x, a letter put in; the
 * wallet's display (0xde0) blinking and redrawn. */
extern void func_ov094_0229b8b4(void *letters, int index, void *letter);

/* Main's. */
extern u16 func_02065ed0(void *letter, u16 item, int state);

/* The item codes PocketsScreen_WaitGridObject records. */
#define ITEM_136A 0x136a
#define ITEM_137B 0x137b

/* What the grid's and the letters' objects answer for no place. */
#define GRID_NO_INDEX 0x23
#define LETTERS_NO_INDEX 0x37

/* func_ov096_0229f290: the x of `place`: by the grid's or the letters' object, by ov090's
 * column less 8 for the row of eight, by the grid's object for 0x22-0x25, else 0. */
int PocketsScreen_PlaceX(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, (unsigned int) place)) {
        return PocketsGrid_PlaceX((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    if (PocketsScreen_IsLetterPlace(self, (unsigned int) place)) {
        return PocketsLetters_PlaceX((PocketsLetters *) (void *) self->letters,
                                     PocketsScreen_LetterIndex(self, (unsigned int) place));
    }
    if (PocketsScreen_IsRowPlace(self, (unsigned int) place)) {
        return MenuTabs_TabX(place - POCKETS_ROW_FIRST) - 8;
    }
    if (PocketsScreen_IsTopPlace(self, (unsigned int) place)) {
        return PocketsGrid_PlaceX((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f290, PocketsScreen_PlaceX)

/* func_ov096_0229f320: the amount of bells a touch on the wallet's digits asks for: the
 * ten-thousands (x 0x30-0x3f), thousands (0x40-0x47) or hundreds (0x48-0x5f), at y 0x50-0x60.
 * `bell_choice` becomes 3, 2 or 1 (0 for no digit once y is in range). Answers 0 for no digit,
 * 1 when the wallet holds less than that, else 2 with the bag of that amount in `place_item`. */
int PocketsScreen_BellAmountAtTouch(PocketsScreen *self, int x, int y)
{
    if (y < 0x50 || y > 0x60) {
        return 0;
    }
    self->bell_choice = 0;
    if (x < 0x30) {
        return 0;
    }
    int bells;
    if (x < 0x40) {
        bells = 10000;
        self->bell_choice = 3;
    } else if (x < 0x48) {
        bells = 1000;
        self->bell_choice = 2;
    } else if (x < 0x60) {
        bells = 100;
        self->bell_choice = 1;
    } else {
        return 0;
    }
    if (bells > PocketsScreen_Wallet(self)) {
        return 1;
    }
    self->place_item = (u16) ItemTraits_BellBagFor(bells, 0, NULL);
    return 2;
}
CLEAN_AS(func_ov096_0229f320, PocketsScreen_BellAmountAtTouch)

/* func_ov096_0229f39c: whether the touch is on the bells' place, by the grid's object (its
 * place 0x21). */
int PocketsScreen_TouchOnBells(PocketsScreen *self, int x, int y)
{
    return PocketsGrid_TouchOnBells((PocketsGrid *) (void *) self->grid, x, y) != 0;
}
CLEAN_AS(func_ov096_0229f39c, PocketsScreen_TouchOnBells)

/* func_ov096_0229f3bc: whether the touch is on the player's place (x 0x89-0xa7, y 0x21-0x4f). */
int PocketsScreen_TouchOnPlayer(PocketsScreen *self, int x, int y)
{
    (void) self;
    return x > 0x88 && x < 0xa8 && y > 0x20 && y < 0x50;
}
CLEAN_AS(func_ov096_0229f3bc, PocketsScreen_TouchOnPlayer)

/* func_ov096_0229f3d4: the place of the upper part under the touch: the player's; 0x22 (x
 * below 0x98) or 0x23 in x 0x6d-0xc3, y 0x51-0x67; the bells' place (its own area or x
 * 0x31-0x5f, y 0x51-0x5f) unless flag 0x4000 is set; else no place, flag 0x4000 cleared. */
int PocketsScreen_PlaceAtTouch(PocketsScreen *self, int x, int y)
{
    if (PocketsScreen_TouchOnPlayer(self, x, y)) {
        return POCKETS_PLACE_PLAYER;
    }
    if (x > 0x6c && x < 0xc4 && y > 0x50 && y < 0x68) {
        return x < 0x98 ? POCKETS_PLACE_22 : POCKETS_PLACE_23;
    }
    if (PocketsScreen_TouchOnBells(self, x, y) || (x > 0x30 && x < 0x60 && y > 0x50 && y < 0x60)) {
        return PocketsScreen_TestFlags(self, POCKETS_FLAG_4000) ? POCKETS_NO_PLACE : POCKETS_PLACE_BELLS;
    }
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_4000);
    return POCKETS_NO_PLACE;
}
CLEAN_AS(func_ov096_0229f3d4, PocketsScreen_PlaceAtTouch)

/* func_ov096_0229f460: whether the touch is on place 0x21 (x 4-0x1b, y 0xac-0xc3). */
int PocketsScreen_TouchOnPlace21(PocketsScreen *self, int x, int y)
{
    (void) self;
    return x >= 4 && x < 0x1c && y >= 0xac && y < 0xc4;
}
CLEAN_AS(func_ov096_0229f460, PocketsScreen_TouchOnPlace21)

/* func_ov096_0229f47c: a copy of `letter` put at a letter's place by the letters' object;
 * nothing for other places. */
void PocketsScreen_PutLetterAt(PocketsScreen *self, int place, void *letter)
{
    if (PocketsScreen_IsLetterPlace(self, (unsigned int) place)) {
        func_ov094_0229b8b4(self->letters, PocketsScreen_LetterIndex(self, (unsigned int) place), letter);
    }
}
CLEAN_AS(func_ov096_0229f47c, PocketsScreen_PutLetterAt)

/* func_ov096_0229f4ac: the held letter put down at `place`; a letter there is copied (to 0x2f28)
 * and goes to the held letter's place first. Answers 1. */
int PocketsScreen_PutHeldLetterAt(PocketsScreen *self, int place)
{
    if (PocketsScreen_PlaceIsEmpty(self, place) == 0) {
        func_02066830(self->unk_2f28, (void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place));
        PocketsScreen_PutLetterAt(self, self->held_place, self->unk_2f28);
    }
    PocketsScreen_PlaceHeldAt(self, place, 1);
    return 1;
}
CLEAN_AS(func_ov096_0229f4ac, PocketsScreen_PutHeldLetterAt)

/* func_ov096_0229f4f8: the letter's place under the touch, by the letters' object; with
 * `with_letter`, only one that holds a letter. POCKETS_NO_PLACE for none. */
int PocketsScreen_LetterPlaceAtTouch(PocketsScreen *self, int x, int y, int with_letter)
{
    int index = PocketsLetters_PocketAtTouch((PocketsLetters *) (void *) self->letters, x, y);
    if (index == LETTERS_NO_INDEX) {
        return POCKETS_NO_PLACE;
    }
    if (with_letter != 0 && PocketsLetters_IsEmpty((PocketsLetters *) (void *) self->letters, index) != 0) {
        return POCKETS_NO_PLACE;
    }
    return PocketsScreen_LetterPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov096_0229f4f8, PocketsScreen_LetterPlaceAtTouch)

/* func_ov096_0229f538: the place of letter `index` (0-9), else POCKETS_NO_PLACE. */
u8 PocketsScreen_LetterPlace(PocketsScreen *self, unsigned int index)
{
    (void) self;
    if (index <= 9) {
        return (u8) (index + POCKETS_LETTERS_FIRST);
    }
    return POCKETS_NO_PLACE;
}
CLEAN_AS(func_ov096_0229f538, PocketsScreen_LetterPlace)

/* func_ov096_0229f548: the letter index (0-9) of a letter's place, else 0. */
int PocketsScreen_LetterIndex(PocketsScreen *self, unsigned int place)
{
    (void) self;
    if (place >= POCKETS_LETTERS_FIRST && place <= POCKETS_LETTERS_LAST) {
        return (int) (place - POCKETS_LETTERS_FIRST);
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f548, PocketsScreen_LetterIndex)

/* func_ov096_0229f55c: the current player's first free pocket slot (a place of the grid), or
 * POCKETS_NO_PLACE. */
int PocketsScreen_FreePocketSlot(PocketsScreen *self)
{
    (void) self;
    int slot = CurrentPockets_FreeSlot();
    if (slot == -1) {
        return POCKETS_NO_PLACE;
    }
    return (u8) slot;
}
CLEAN_AS(func_ov096_0229f55c, PocketsScreen_FreePocketSlot)

/* func_ov096_0229f57c: the letters' object lets go of the letter at a letter's place. */
void PocketsScreen_RemoveLetterAt(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsLetterPlace(self, (unsigned int) place)) {
        PocketsLetters_ClearPlace((PocketsLetters *) (void *) self->letters,
                                  PocketsScreen_LetterIndex(self, (unsigned int) place));
    }
}
CLEAN_AS(func_ov096_0229f57c, PocketsScreen_RemoveLetterAt)

/* func_ov096_0229f5ac: nothing (state 0) put at a place of the grid or the letters. */
void PocketsScreen_EmptyPlace(PocketsScreen *self, int place)
{
    if (PocketsScreen_IsGridPlace(self, (unsigned int) place) || PocketsScreen_IsLetterPlace(self, (unsigned int) place)) {
        PocketsScreen_SetPlaceItem(self, place, ITEM_NONE, 0);
    }
}
CLEAN_AS(func_ov096_0229f5ac, PocketsScreen_EmptyPlace)

/* func_ov096_0229f5e0: `item` in `state` put at `place`: in the grid's slot (by its object,
 * then redrawn), attached to the letter there, or, at the bells' place, a bag whose bells go
 * into the wallet (the bag of what does not fit is dropped). */
void PocketsScreen_SetPlaceItem(PocketsScreen *self, int place, int item, int state)
{
    if (PocketsScreen_IsGridPlace(self, (unsigned int) place)) {
        int index = func_ov096_0229f7ac(self, place);
        PocketsGrid_SetItem((PocketsGrid *) (void *) self->grid, index, item, state);
        PocketsGrid_RefreshPlace((PocketsGrid *) (void *) self->grid, index);
    } else if (PocketsScreen_IsLetterPlace(self, (unsigned int) place)) {
        func_02065ed0((void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place), (u16) item, state);
    } else if (place == POCKETS_PLACE_BELLS) {
        PocketsScreen_AddBagToWallet(self, (u16) item);
    }
}
CLEAN_AS(func_ov096_0229f5e0, PocketsScreen_SetPlaceItem)

/* func_ov096_0229f650: the held item put down at `place`; whether it was.
 * The grid or a letter (not an empty letter's place): the held item merges onto the item there
 * (PocketsScreen_MergeItems); what is left of that goes to the held item's place, then the held
 * item is put down. 0x22, 0x23: PocketsScreen_UseHeld. The player's place: into the record
 * slot (PocketsScreen_BeginSubState25), refused when it fits none. The bells' place: into the
 * wallet. 0x21: PocketsScreen_SwapRecordItem.
 * QUIRK: 0x22 and 0x23 are told by the place's low byte only. */
int PocketsScreen_PutHeldItemAt(PocketsScreen *self, int place)
{
    unsigned int at = (unsigned int) place;
    if (PocketsScreen_IsLetterPlace(self, at) && PocketsScreen_PlaceIsEmpty(self, place)) {
        return 0;
    }
    if (PocketsScreen_IsGridPlace(self, at) || PocketsScreen_IsLetterPlace(self, at)) {
        u16 other = PocketsScreen_PlaceItem(self, place);
        PocketsScreen_MergeItems(self, &self->item, self->held_state, &other, (u8) PocketsScreen_PlaceItemState(self, place));
        if (other != ITEM_NONE) {
            PocketsScreen_SetPlaceItem(self, self->held_place, other, PocketsScreen_PlaceItemState(self, place));
        }
        PocketsScreen_PlaceHeldAt(self, place, 1);
        return 1;
    }
    if ((u8) (place - POCKETS_PLACE_22) <= 1) {
        return PocketsScreen_UseHeld(self) != 0;
    }
    switch (place) {
        case POCKETS_PLACE_PLAYER:
            if (self->record_slot == 0) {
                PocketsScreen_RefuseRecordSlot(self);
                return 0;
            }
            PocketsScreen_BeginSubState25(self);
            return 1;
        case POCKETS_PLACE_BELLS:
            if (PocketsScreen_PutBagInWallet(self) == 0) {
                PocketsScreen_PlaceHeldAt(self, self->held_place, 1);
            }
            return 1;
        case POCKETS_PLACE_21:
            PocketsScreen_SwapRecordItem(self);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov096_0229f650, PocketsScreen_PutHeldItemAt)

/* func_ov096_0229f75c: the grid's place under the touch, by the grid's object; with
 * `with_item`, only one that holds an item. POCKETS_NO_PLACE for none. */
int PocketsScreen_GridPlaceAtTouch(PocketsScreen *self, int x, int y, int with_item)
{
    int index = PocketsGrid_PocketPlaceAtTouch((PocketsGrid *) (void *) self->grid, x, y);
    if (index == GRID_NO_INDEX) {
        return POCKETS_NO_PLACE;
    }
    if (with_item != 0 && PocketsGrid_IsEmpty((PocketsGrid *) (void *) self->grid, index) != 0) {
        return POCKETS_NO_PLACE;
    }
    return (int) PocketsScreen_GridPlace(self, (unsigned int) index);
}
CLEAN_AS(func_ov096_0229f75c, PocketsScreen_GridPlaceAtTouch)

/* func_ov096_0229f79c: the place of grid slot `index` (0-14), else POCKETS_NO_PLACE. */
unsigned int PocketsScreen_GridPlace(PocketsScreen *self, unsigned int index)
{
    (void) self;
    if (index <= POCKETS_GRID_LAST) {
        return index;
    }
    return POCKETS_NO_PLACE;
}
CLEAN_AS(func_ov096_0229f79c, PocketsScreen_GridPlace)

/* func_ov096_0229f7ac: the index in the grid's object of a place: the grid's own (0-14), and
 * 0x1e-0x21 for the places 0x22-0x25; else 0.
 * QUIRK: the matching source declares both parameters 16-bit, so the scene arrives as the low
 * half of its address; the two tests it is handed to do not read it. */
u8 PocketsScreen_GridIndex(u16 self_low, u16 place)
{
    PocketsScreen *self = (PocketsScreen *) (uintptr_t) self_low;
    if (PocketsScreen_IsGridPlace(self, place)) {
        return (u8) place;
    }
    if (PocketsScreen_IsTopPlace(self, place)) {
        return (u8) (place - 4);
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f7ac, PocketsScreen_GridIndex)

/* func_ov096_0229f7e0: the cursor put on the row of eight, at the column under the cursor
 * sprite. */
void PocketsScreen_CursorToSpriteColumn(PocketsScreen *self)
{
    int column = MenuTabs_TabAtX(Glider_ScreenX(&self->cursor_sprite));
    self->cursor = (u8) (column + POCKETS_ROW_FIRST);
}
CLEAN_AS(func_ov096_0229f7e0, PocketsScreen_CursorToSpriteColumn)

/* func_ov096_0229f800: whether `place` is one of 0x22-0x25. */
int PocketsScreen_IsTopPlace(PocketsScreen *self, unsigned int place)
{
    (void) self;
    return place >= POCKETS_PLACE_22 && place <= POCKETS_PLACE_BELLS;
}
CLEAN_AS(func_ov096_0229f800, PocketsScreen_IsTopPlace)

/* func_ov096_0229f810: whether `place` is in the row of eight. */
int PocketsScreen_IsRowPlace(PocketsScreen *self, unsigned int place)
{
    (void) self;
    return place >= POCKETS_ROW_FIRST && place <= POCKETS_ROW_LAST;
}
CLEAN_AS(func_ov096_0229f810, PocketsScreen_IsRowPlace)

/* func_ov096_0229f820: whether `place` is a letter's. */
int PocketsScreen_IsLetterPlace(PocketsScreen *self, unsigned int place)
{
    (void) self;
    return place >= POCKETS_LETTERS_FIRST && place <= POCKETS_LETTERS_LAST;
}
CLEAN_AS(func_ov096_0229f820, PocketsScreen_IsLetterPlace)

/* func_ov096_0229f830: whether `place` is in the grid. */
int PocketsScreen_IsGridPlace(PocketsScreen *self, unsigned int place)
{
    (void) self;
    return place <= POCKETS_GRID_LAST;
}
CLEAN_AS(func_ov096_0229f830, PocketsScreen_IsGridPlace)

/* func_ov096_0229f83c: the objects at 0x2e8 and 0x320 updated by main's func_020b9ccc. */
void PocketsScreen_UpdateObjects2e8(PocketsScreen *self)
{
    LayerTask_End((LayerTask *) (void *) self->unk_2e8);
    LayerTask_End((LayerTask *) (void *) self->unk_320);
}
CLEAN_AS(func_ov096_0229f83c, PocketsScreen_UpdateObjects2e8)

/* The blink of PocketsScreen_BlinkSlot, in frames. */
#define SLOT_BLINK_FRAMES 14

/* func_ov096_0229f860: sub state 0x32, the picked place blinking for 14 frames. */
u8 *PocketsScreen_StartBlinkSlot(PocketsScreen *self)
{
    self->blink = SLOT_BLINK_FRAMES;
    return MenuScene_SetSubState(scene_of(self), 0x32);
}
CLEAN_AS(func_ov096_0229f860, PocketsScreen_StartBlinkSlot)

/* func_ov096_0229f874: the error message `message` opened (ErrorMessage_Open with `flag`) and
 * sub state 0x20 waits for it, then goes to `return_state` (0xff: the current sub state); the
 * cursor sprite's byte 0x4a is cleared. */
void PocketsScreen_ShowError(PocketsScreen *self, int message, int return_state, unsigned int flag)
{
    if (return_state == 0xff) {
        self->return_state = self->base.sub_state;
    } else {
        self->return_state = (u8) return_state;
    }
    u8 number = (u8) message;
    ErrorMessage_Open(&self->error, &number, (int) flag, 0);
    MenuScene_SetSubState(scene_of(self), 0x20);
    CellLayerSprite_ClearWindow((CellLayerSprite *) (void *) &self->cursor_sprite);
}
CLEAN_AS(func_ov096_0229f874, PocketsScreen_ShowError)

/* func_ov096_0229f8cc: holds `item` in `state`, drawn at place `from`, and glides it to `to`
 * in 4 steps. */
u8 *PocketsScreen_HoldAndGlide(PocketsScreen *self, int from, int to, int item, u8 state)
{
    PocketsScreen_HoldItem(self, (u16) item, state);
    self->menu_x = PocketsScreen_PlaceX(self, from);
    self->menu_y = PocketsScreen_PlaceY(self, from);
    return PocketsScreen_GlideHeldTo(self, (u8) to, 4);
}
CLEAN_AS(func_ov096_0229f8cc, PocketsScreen_HoldAndGlide)

/* func_ov096_0229f90c: the held thing glides from where it is drawn to `place` (kept as its
 * place) in `steps` steps, the first taken now; sub state 0x1b follows the glide. */
u8 *PocketsScreen_GlideHeldTo(PocketsScreen *self, u8 place, int steps)
{
    self->held_place = place;
    Glide_SetPlace(&self->glide, self->menu_x, self->menu_y);
    int x = PocketsScreen_PlaceX(self, place);
    int y = PocketsScreen_PlaceY(self, place);
    Glide_MoveTo(&self->glide, x, y, steps);
    Glide_Step(&self->glide);
    PocketsScreen_FollowGlide(self);
    return MenuScene_SetSubState(scene_of(self), 0x1b);
}
CLEAN_AS(func_ov096_0229f90c, PocketsScreen_GlideHeldTo)

/* func_ov096_0229f970: picks up what is at `place` with the cursor (only an item when no action
 * is kept), the popup hidden; the sub state to go back to is 0x0c for a letter, 0x0b for an
 * item. The held thing follows the cursor sprite; command 0xd. */
void PocketsScreen_PickUpWithCursor(PocketsScreen *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    if (self->action == 0) {
        PocketsScreen_PickUpItemAt(self, place);
    } else {
        PocketsScreen_PickUpAt(self, place);
    }
    switch (self->held_kind) {
        case POCKETS_HELD_LETTER:
            self->return_state = 0x0c;
            break;
        case POCKETS_HELD_ITEM:
            self->return_state = 0x0b;
            break;
    }
    PocketsScreen_FollowCursorSprite(self);
    PocketsSound_Play0d();
}
CLEAN_AS(func_ov096_0229f970, PocketsScreen_PickUpWithCursor)

/* func_ov096_0229f9dc: picks up what is at `place` with the touch, the popup hidden; sub
 * state 6 for a letter, 5 for an item. The held thing follows the touch, flag 0x4000 is
 * cleared, command 0xd, and no place is kept at 0xb9. */
void PocketsScreen_PickUpWithTouch(PocketsScreen *self, int place)
{
    self->held_place = (u8) place;
    Popup_Hide(&self->popup, 1);
    PocketsScreen_PickUpAt(self, place);
    switch (self->held_kind) {
        case POCKETS_HELD_LETTER:
            MenuScene_SetSubState(scene_of(self), 6);
            break;
        case POCKETS_HELD_ITEM:
            MenuScene_SetSubState(scene_of(self), 5);
            break;
    }
    PocketsScreen_FollowTouch(self);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_4000);
    PocketsSound_Play0d();
    self->unk_b9 = POCKETS_NO_PLACE;
}
CLEAN_AS(func_ov096_0229f9dc, PocketsScreen_PickUpWithTouch)

/* func_ov096_0229fa44: `place` touched: sub state 1, the offset from the touch to the place
 * kept, the popup told of the place and shown, the place's choice rows made, flag 4 set when
 * the place holds nothing; places other than the grid and the player's ask the switch off.
 * Command 0xc. */
void PocketsScreen_TouchPlace(PocketsScreen *self, int place)
{
    self->touch_place = (u8) place;
    MenuScene_SetSubState(scene_of(self), 1);
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    self->grab_dx = PocketsScreen_PlaceX(self, self->touch_place) - touch_x;
    self->grab_dy = PocketsScreen_PlaceY(self, self->touch_place) - touch_y;
    self->popup_place = (u8) place;
    Popup_Queue(&self->popup);
    Popup_ShowQueued(&self->popup);
    self->open_delay = 2;
    PocketsScreen_FillTouchedEntries(self);
    if (PocketsScreen_PlaceIsTaken(self, place)) {
        PocketsScreen_ClearFlags(self, POCKETS_FLAG_04);
    } else {
        PocketsScreen_SetFlags(self, POCKETS_FLAG_04);
    }
    if (!PocketsScreen_IsGridPlace(self, (unsigned int) place) && place != POCKETS_PLACE_PLAYER) {
        PocketsScreen_RequestSwitchOff(self);
    }
    PocketsSound_Play0c();
}
CLEAN_AS(func_ov096_0229fa44, PocketsScreen_TouchPlace)

/* func_ov096_0229faf8: for a touched place of the grid, its choice rows made (cancel value
 * 0x22); flag 0x10000 tells there are none. */
void PocketsScreen_FillTouchedEntries(PocketsScreen *self)
{
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_NO_ENTRIES);
    if (PocketsScreen_IsGridPlace(self, self->touch_place)) {
        ChoiceEntries_Clear(&self->entries, POCKETS_ACTION_CANCEL);
        PocketsScreen_AddGridEntries(self, self->touch_place);
        if (ChoiceEntries_Count(&self->entries) == 0) {
            PocketsScreen_SetFlags(self, POCKETS_FLAG_NO_ENTRIES);
        }
    }
}
CLEAN_AS(func_ov096_0229faf8, PocketsScreen_FillTouchedEntries)

/* func_ov096_0229fb4c: sub state 8 (cursor sprite hidden) while state flag 2 is clear, else
 * sub state 0x19 (the cursor sprite at the choice's last row). */
void PocketsScreen_BeginSubState08Or19(PocketsScreen *self)
{
    if (StateFlags_IsClear2()) {
        PocketsScreen_BeginSubState08(self);
    } else {
        PocketsScreen_BeginSubState19(self);
    }
}
CLEAN_AS(func_ov096_0229fb4c, PocketsScreen_BeginSubState08Or19)

/* func_ov096_0229fb6c */
int PocketsScreen_BeginSubState19(PocketsScreen *self)
{
    PocketsScreen_PointAtLastRow(self);
    return (int) (uintptr_t) MenuScene_SetSubState(scene_of(self), 0x19);
}
CLEAN_AS(func_ov096_0229fb6c, PocketsScreen_BeginSubState19)

/* func_ov096_0229fb84 */
int PocketsScreen_BeginSubState08(PocketsScreen *self)
{
    PocketsScreen_HideCursorSprite(self);
    return (int) (uintptr_t) MenuScene_SetSubState(scene_of(self), 8);
}
CLEAN_AS(func_ov096_0229fb84, PocketsScreen_BeginSubState08)

/* func_ov096_0229fb9c: the action ends: back to sub state 0 with the cursor sprite hidden
 * while state flag 2 is clear, else to sub state 0x0a with it at the cursor. */
void PocketsScreen_EndAction(PocketsScreen *self)
{
    if (StateFlags_IsClear2() != 0) {
        PocketsScreen_EndActionHidden(self);
    } else {
        PocketsScreen_EndActionAtCursor(self);
    }
}
CLEAN_AS(func_ov096_0229fb9c, PocketsScreen_EndAction)

/* func_ov096_0229fbbc: no popup place, the cursor sprite shown at the cursor, the key repeat
 * reset, the popup told of the cursor's place, sub state 0x0a and the cursor's place
 * selected. */
void PocketsScreen_EndActionAtCursor(PocketsScreen *self)
{
    self->popup_place = POCKETS_NO_PLACE;
    PocketsScreen_ShowCursorSprite(self);
    MenuScene_ResetKeyRepeat(scene_of(self));
    PocketsScreen_UpdatePopup(self);
    MenuScene_SetSubState(scene_of(self), 0x0a);
    PocketsScreen_SelectPlace(self, self->cursor);
}
CLEAN_AS(func_ov096_0229fbbc, PocketsScreen_EndActionAtCursor)

/* func_ov096_0229fbf0 */
void PocketsScreen_EndActionHidden(PocketsScreen *self)
{
    PocketsScreen_HideCursorSprite(self);
    PocketsScreen_ClearSelection(self);
    MenuScene_SetSubState(scene_of(self), 0);
}
CLEAN_AS(func_ov096_0229fbf0, PocketsScreen_EndActionHidden)

/* The answers of a use request (`unk_c4`, PocketsScreen_CheckUseItem). */
enum PocketsUseResult { POCKETS_USE_PENDING = 0, POCKETS_USE_DONE = 1, POCKETS_USE_FAILED = 2 };

/* What sub states 0x28 and 0x29 do once their request answered `result`: done, the item used
 * from a slot (flag 0x1000) is handed to the grid's object, one used from the hand is let go;
 * failed, one from the hand goes back, and error `message` with command 0x73. Either way the
 * action ends and the request is freed (`unk_c4` -1). Nothing while it is pending. */
static void finish_use_request(PocketsScreen *self, int result, int message)
{
    switch (result) {
        case POCKETS_USE_DONE:
            if (PocketsScreen_TestFlags(self, POCKETS_FLAG_1000)) {
                PocketsGrid_EmptyPlace((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, self->slot));
            } else {
                PocketsScreen_DropHeld(self);
            }
            PocketsScreen_EndAction(self);
            break;
        case POCKETS_USE_FAILED:
            if (PocketsScreen_TestFlags(self, POCKETS_FLAG_1000) == 0) {
                PocketsScreen_ReturnHeld(self, 1);
            }
            PocketsScreen_EndAction(self);
            PocketsScreen_ShowError(self, message, 0xff, 0);
            RtcSendPxiCommand(0x73);
            break;
        default:
            return;
    }
    TileRequests_Release(self->unk_c4);
    self->unk_c4 = -1;
}

/* func_ov096_0229fc0c (sub state 0x29): waits for the use request by func_020436a8; error 8
 * when it fails. */
void PocketsScreen_WaitUseRequest29(PocketsScreen *self)
{
    finish_use_request(self, TileRequests_Answer((unsigned int) self->unk_c4), 8);
}
CLEAN_AS(func_ov096_0229fc0c, PocketsScreen_WaitUseRequest29)

/* func_ov096_0229fca8 (sub state 0x28): waits for the use request by func_020431c8; error 3
 * when it fails. */
void PocketsScreen_WaitUseRequest28(PocketsScreen *self)
{
    finish_use_request(self, TileRequests_Carry(self->unk_c4), 3);
}
CLEAN_AS(func_ov096_0229fca8, PocketsScreen_WaitUseRequest28)

/* func_ov096_0229fd44 (sub state 0x32): the picked place blinks (marked when the frames left
 * are 3 more than a multiple of 5, unmarked on the multiples) and is emptied on the last
 * frame; the frame after, sub state 0x2f, run at once. */
void PocketsScreen_BlinkSlot(PocketsScreen *self)
{
    if (self->blink == 0) {
        MenuScene_SetSubState(scene_of(self), 0x2f);
        PocketsScreen_WaitActorState(self);
        return;
    }
    self->blink--;
    int phase = self->blink % 5;
    if (phase == 0) {
        PocketsScreen_ClearHighlights(self);
    } else if (phase == 3) {
        PocketsScreen_HighlightPlace(self, self->slot);
    }
    if (self->blink == 0) {
        PocketsScreen_EmptyPlace(self, self->slot);
    }
}
CLEAN_AS(func_ov096_0229fd44, PocketsScreen_BlinkSlot)

/* func_ov096_0229fdb0 (sub state 0x31): command 0x40 and the switch asked on; the item of the
 * picked place offered to the player's field actor (func_02095aec, record slot 7's request).
 * Taken: the place is emptied and sub state 0x2f's pointer answered; else NULL. */
u8 *PocketsScreen_HandSlotItemToActor(PocketsScreen *self)
{
    RtcSendPxiCommand(0x40);
    PocketsScreen_RequestSwitchOn(self);
    u16 item = PocketsScreen_PlaceItem(self, self->slot);
    if (PlayerActorOps_RequestState85(&item) != 0) {
        PocketsScreen_EmptyPlace(self, self->slot);
        return MenuScene_SetSubState(scene_of(self), 0x2f);
    }
    return NULL;
}
CLEAN_AS(func_ov096_0229fdb0, PocketsScreen_HandSlotItemToActor)

/* func_ov096_0229fdf8 (sub state 0x2f): the action ends once func_02096150 answers. */
void PocketsScreen_WaitActorState(PocketsScreen *self)
{
    if (PlayerActorOps_InState5() != 0) {
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov096_0229fdf8, PocketsScreen_WaitActorState)

/* func_ov096_0229fe10 (sub state 0x2b): once the grid's object is done, holding 0x136a or
 * 0x137b sets bit 0x27 or 0x28 of the current player's record; the held item, in state 0, goes
 * to the picked place and the action ends. */
void PocketsScreen_WaitGridObject(PocketsScreen *self)
{
    if (PocketsGrid_StepPickUp((PocketsGrid *) (void *) self->grid) == 0) {
        return;
    }
    int record = (int) (uintptr_t) PlayerRecords_Current();
    if (self->item == ITEM_136A) {
        PlayerRecord_SetFlag((u8 *) (uintptr_t) record, 0x27);
    } else if (self->item == ITEM_137B) {
        PlayerRecord_SetFlag((u8 *) (uintptr_t) record, 0x28);
    }
    self->held_state = 0;
    PocketsScreen_PlaceHeldAt(self, self->slot, 1);
    PocketsScreen_EndAction(self);
}
CLEAN_AS(func_ov096_0229fe10, PocketsScreen_WaitGridObject)

/* func_ov096_0229fe74 (sub state 0x2a): once the letters' object is done, the scene lets go and
 * the action ends. */
void PocketsScreen_WaitLettersObject(PocketsScreen *self)
{
    if (PocketsLetters_StepPickUp((PocketsLetters *) (void *) self->letters)) {
        PocketsScreen_DropHeld(self);
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov096_0229fe74, PocketsScreen_WaitLettersObject)

/* func_ov096_0229fe9c (sub state 0x27): once PocketsScreen_ActorReadyForSlot answers 0 for the
 * record slot, the scene lets go, the wallet's display stops blinking and the action ends. */
void PocketsScreen_WaitActorForRecord(PocketsScreen *self)
{
    if (PocketsScreen_ActorReadyForSlot(self, self->record_slot) != 0) {
        return;
    }
    PocketsScreen_DropHeld(self);
    PocketsWallet_StopBlink((PocketsWallet *) (void *) self->unk_de0);
    PocketsScreen_EndAction(self);
}
CLEAN_AS(func_ov096_0229fe9c, PocketsScreen_WaitActorForRecord)

/* func_ov096_0229fecc (sub state 0x26): once the wallet's display has blinked, the scene lets
 * go and the display is redrawn. The item that came back from the record slot (in `item`):
 * with flag 0x8000 it glides from the player's place to the held place (and this ends here);
 * else it is held in state 0 and goes back. Then sub state 0x27, run at once. */
void PocketsScreen_WaitRecordBlink(PocketsScreen *self)
{
    if (PocketsWallet_StepBlink((PocketsWallet *) (void *) self->unk_de0) == 0) {
        return;
    }
    PocketsScreen_DropHeld(self);
    PocketsWallet_LoadHeldItemPicture((PocketsWallet *) (void *) self->unk_de0);
    if (self->item != ITEM_NONE) {
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_8000)) {
            PocketsScreen_HoldAndGlide(self, POCKETS_PLACE_PLAYER, self->held_place, self->item, 0);
            return;
        }
        PocketsScreen_HoldItem(self, self->item, 0);
        PocketsScreen_ReturnHeld(self, 1);
    }
    MenuScene_SetSubState(scene_of(self), 0x27);
    PocketsScreen_WaitActorForRecord(self);
}
CLEAN_AS(func_ov096_0229fecc, PocketsScreen_WaitRecordBlink)

/* func_ov096_0229ff54 (sub state 0x25): the held thing drawn at the player's place; the switch
 * asked on unless the slot is 5 the ov097 way (data_020e54a8 set). When the player's field actor
 * takes the item for the record slot: sub state 0x26, the item swapped into the slot (`item`
 * becomes what comes back) and the wallet's display blinks. */
void PocketsScreen_GiveToRecordSlot(PocketsScreen *self)
{
    self->menu_x = PocketsScreen_PlaceX(self, POCKETS_PLACE_PLAYER);
    self->menu_y = PocketsScreen_PlaceY(self, POCKETS_PLACE_PLAYER);
    u8 record_slot = self->record_slot;
    if (record_slot != 5 || data_020e54a8 == 0) {
        PocketsScreen_RequestSwitchOn(self);
    }
    if (PocketsScreen_ActorTakeSlotItem(self, record_slot, self->item) != 0) {
        MenuScene_SetSubState(scene_of(self), 0x26);
        self->item = (u16) PocketsScreen_SwapRecordSlot(self, record_slot, self->item);
        PocketsWallet_StartBlink((PocketsWallet *) (void *) self->unk_de0, 1);
    }
}
CLEAN_AS(func_ov096_0229ff54, PocketsScreen_GiveToRecordSlot)

/* func_ov096_0229ffe0 (sub state 0x24): once the choice is idle: with flag 0x200 and a choice
 * code of kind 1, PocketsScreen_PutPileInLetter. Else the code is applied to the group's
 * parameters; answer 2 turns to the next page (back to the first after the last) and opens it,
 * others end the action. */
void PocketsScreen_RunChoice(PocketsScreen *self)
{
    PagedChoice *choice = choice_of(self);
    if (PagedChoice_IsIdle(choice) == 0) {
        return;
    }
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_200) && PagedChoice_CodeKind(choice, self->choice_code) == 1) {
        PocketsScreen_PutPileInLetter(self);
        return;
    }
    if (PagedChoice_Apply(choice, GroupParams_Pointer(), self->choice_code) == 2) {
        self->choice_page++;
        int pages = PagedChoice_PageCount(choice);
        if ((unsigned int) self->choice_page >= (unsigned int) pages) {
            self->choice_page = 0;
        }
        PocketsScreen_OpenChoicePage(self, 0);
    } else {
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov096_0229ffe0, PocketsScreen_RunChoice)

/* func_ov096_022a0074 (sub state 0x23): once the choice closes, the cursor sprite hidden and
 * sub state 0x24. */
void PocketsScreen_CloseChoiceThenRun(PocketsScreen *self)
{
    if (PocketsScreen_CloseChoice(self)) {
        PocketsScreen_HideCursorSprite(self);
        MenuScene_SetSubState(scene_of(self), 0x24);
    }
}
CLEAN_AS(func_ov096_022a0074, PocketsScreen_CloseChoiceThenRun)

/* func_ov096_022a0094 (sub state 0x22): once the choice is shown,
 * PocketsScreen_BeginSubState08Or19. */
void PocketsScreen_WaitChoiceShown(PocketsScreen *self)
{
    if (PagedChoice_IsShown(choice_of(self)) != 0) {
        PocketsScreen_BeginSubState08Or19(self);
    }
}
CLEAN_AS(func_ov096_022a0094, PocketsScreen_WaitChoiceShown)

/* func_ov096_022a00b4 (sub state 0x21): while the button's animation plays, the cursor sprite
 * (when it shows an animation) follows the button's anchor 1; then the cursor sprite is hidden,
 * state 9 and phase 1. */
void PocketsScreen_FollowButton(PocketsScreen *self)
{
    if (LabelButton_StepAnimation(&self->button) != 0) {
        if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
            int x = LabelButton_AnchorX(&self->button, 1);
            int y = LabelButton_AnchorY(&self->button, 1);
            Glider_PlaceAt(&self->cursor_sprite, x, y);
        }
    } else {
        PocketsScreen_HideCursorSprite(self);
        MenuScene_SetState(scene_of(self), 9);
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_STATES);
    }
}
CLEAN_AS(func_ov096_022a00b4, PocketsScreen_FollowButton)

/* func_ov096_022a011c (sub state 0x20): once the error message is done, back to the kept sub
 * state and the cursor sprite's byte 0x4a set. */
void PocketsScreen_WaitError(PocketsScreen *self)
{
    if (ErrorMessage_Update(&self->error, 1)) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
        CellLayerSprite_SetWindow((CellLayerSprite *) (void *) &self->cursor_sprite);
    }
}
CLEAN_AS(func_ov096_022a011c, PocketsScreen_WaitError)

/* Obj_ov096_022a23e8::func_ov096_022a0150 (sub state 0x1f): once the choice is idle, the kept
 * action runs. */
void PocketsScreen_RunActionWhenIdle(PocketsScreen *self)
{
    if (PagedChoice_IsIdle(choice_of(self))) {
        PocketsScreen_RunAction(self);
    }
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_022a0150Ev, PocketsScreen_RunActionWhenIdle)

/* func_ov096_022a0170 (sub state 0x1e): once the choice closes, sub state 0x1f. */
void PocketsScreen_CloseChoiceToAction(PocketsScreen *self)
{
    if (PocketsScreen_CloseChoice(self) != 0) {
        MenuScene_SetSubState(scene_of(self), 0x1f);
    }
}
CLEAN_AS(func_ov096_022a0170, PocketsScreen_CloseChoiceToAction)

/* func_ov096_022a018c: when the choice's delay has run out, the choice asked to close, the
 * popup hidden and the cursor sprite (when it shows an animation) put back at the cursor;
 * whether it had run out. */
int PocketsScreen_CloseChoice(PocketsScreen *self)
{
    if (PagedChoice_CountDown(choice_of(self)) == 0) {
        return 0;
    }
    PagedChoice_RequestClose(choice_of(self), 0);
    Popup_Hide(&self->popup, 1);
    if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
        PocketsScreen_PlaceCursorSprite(self);
    }
    return 1;
}
CLEAN_AS(func_ov096_022a018c, PocketsScreen_CloseChoice)

/* func_ov096_022a01dc (sub state 0x1d): once the choice is shown: with state flag 2 the cursor
 * sprite at its default row and sub state 0x0d, else sub state 4. */
void PocketsScreen_WaitChoiceToPoint(PocketsScreen *self)
{
    if (PagedChoice_IsShown(choice_of(self)) == 0) {
        return;
    }
    if (StateFlags_Test2() != 0) {
        PocketsScreen_PointAtDefaultRow(self);
        MenuScene_SetSubState(scene_of(self), 0x0d);
    } else {
        MenuScene_SetSubState(scene_of(self), 4);
    }
}
CLEAN_AS(func_ov096_022a01dc, PocketsScreen_WaitChoiceToPoint)

/* func_ov096_022a0218 (sub state 0x1c): the held thing put at its place and let go. With flag
 * 0x2000, `place_item` is then held and glides from there to 0xb9 (the flag cleared); else
 * command 0xe and the action ends. */
void PocketsScreen_SettleHeld(PocketsScreen *self)
{
    PocketsScreen_PlaceHeldAt(self, self->held_place, 1);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_2000)) {
        PocketsScreen_HoldAndGlide(self, self->held_place, self->unk_b9, self->place_item, 0);
        PocketsScreen_ClearFlags(self, POCKETS_FLAG_2000);
    } else {
        PocketsSound_Play0e();
        PocketsScreen_EndAction(self);
    }
}
CLEAN_AS(func_ov096_022a0218, PocketsScreen_SettleHeld)

/* func_ov096_022a0274 (sub state 0x1b): the held thing follows the glide; when it is over, at
 * the places 0x22-0x25 or with flag 0x2000 it is drawn at its place and sub state 0x1c follows,
 * else PocketsScreen_SettleHeld at once. */
void PocketsScreen_StepHeldGlide(PocketsScreen *self)
{
    if (Glide_Step(&self->glide) == 0) {
        PocketsScreen_FollowGlide(self);
        return;
    }
    if (PocketsScreen_IsTopPlace(self, self->held_place) || PocketsScreen_TestFlags(self, POCKETS_FLAG_2000)) {
        self->menu_x = PocketsScreen_PlaceX(self, self->held_place);
        self->menu_y = PocketsScreen_PlaceY(self, self->held_place);
        MenuScene_SetSubState(scene_of(self), 0x1c);
    } else {
        PocketsScreen_SettleHeld(self);
    }
}
CLEAN_AS(func_ov096_022a0274, PocketsScreen_StepHeldGlide)

/* The scene's frame: its sub states (run by PocketsScreen_RunSubState in phase 2), its states
 * (run by PocketsScreen_RunState in the run phase: the setup, the wipes in and out, and the
 * letter read on layers 3 and 4), its draw, its setup and its construction. */

/* The pad (autoload_2/input.h): the buttons pressed this frame. */
extern PadState data_021fbe40;
#define POCKETS_PAD_A 0x0001
#define POCKETS_PAD_B 0x0002
#define POCKETS_PAD_SELECT 0x0004
#define POCKETS_PAD_R 0x0100
#define POCKETS_PAD_L 0x0200
#define POCKETS_PAD_X 0x0400
#define POCKETS_PAD_Y 0x0800

/* The pen (main's bytes, as menu_scene.c reads them). */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

#define POCKETS_TAB_NONE (-1)
#define POCKETS_TAB_SELF 0  /* this scene's own tab */
#define POCKETS_TAB_CLOSE 7 /* the menu closes */

/* The letter view at 0x2a74 (main's): its setup and teardown, and a letter shown on two 2D
 * layers; a letter of kind 2, 5 or 7 becomes 3, 6 or 8 (func_020664a8: the letter is read). */
extern void func_020664a8(void *letter);

/* Main's: the objects at 0x2e8 and 0x320, a letter copy's constructor, the button's offset
 * (words 0x0c and 0x10), the held bells (data_021cfc74). */
extern void func_02066694(void *letter);

/* The sub state tables: the guard, the table (one array of 58 at 0x022a25d4, which the
 * symbol table cuts at 0x022a2654, 0x022a26d4 and 0x022a2754) and its constants; the state
 * table's (11) the same way. */
#define POCKETS_SUB_STATE_COUNT 58
#define POCKETS_STATE_COUNT 11
extern u32 data_ov096_022a2460;
extern MemberPointer data_ov096_022a25d4[POCKETS_SUB_STATE_COUNT];
extern const MemberPointer data_ov096_022a2380, data_ov096_022a2378, data_ov096_022a2370, data_ov096_022a2368,
    data_ov096_022a2360, data_ov096_022a2358, data_ov096_022a2350, data_ov096_022a2348, data_ov096_022a2340,
    data_ov096_022a2338, data_ov096_022a2330, data_ov096_022a2328, data_ov096_022a2320, data_ov096_022a2318,
    data_ov096_022a2310, data_ov096_022a2308, data_ov096_022a2300, data_ov096_022a22f8, data_ov096_022a22f0,
    data_ov096_022a22e8, data_ov096_022a22e0, data_ov096_022a21a8, data_ov096_022a22d0, data_ov096_022a22c8,
    data_ov096_022a22c0, data_ov096_022a22b8, data_ov096_022a22b0, data_ov096_022a22a8, data_ov096_022a22a0,
    data_ov096_022a2298, data_ov096_022a2290, data_ov096_022a2288, data_ov096_022a2178, data_ov096_022a2180,
    data_ov096_022a2270, data_ov096_022a2268, data_ov096_022a2260, data_ov096_022a2258, data_ov096_022a2250,
    data_ov096_022a2248, data_ov096_022a2240, data_ov096_022a2238, data_ov096_022a2230, data_ov096_022a2228,
    data_ov096_022a2220, data_ov096_022a2218, data_ov096_022a2210, data_ov096_022a2208, data_ov096_022a2390,
    data_ov096_022a21f8, data_ov096_022a21f0, data_ov096_022a21e8, data_ov096_022a21e0, data_ov096_022a21d8,
    data_ov096_022a21d0, data_ov096_022a21c8, data_ov096_022a21c0, data_ov096_022a21b8;
extern u32 data_ov096_022a2464;
extern MemberPointer data_ov096_022a246c[POCKETS_STATE_COUNT];
extern const MemberPointer data_ov096_022a2388, data_ov096_022a20a0, data_ov096_022a23d8, data_ov096_022a23d0,
    data_ov096_022a23c8, data_ov096_022a23c0, data_ov096_022a23b8, data_ov096_022a23b0, data_ov096_022a23a8,
    data_ov096_022a23a0, data_ov096_022a2398;

/* The wipes of the states: on window 2 with a margin of 0x30, over layer 6 (the pockets) or 3
 * and 4 (the letter read). */
#define POCKETS_WIPE_MARGIN 0x30
#define POCKETS_LAYER 6
#define READER_LAYER 3
#define READER_UNDER_LAYER 4
#define READER_BUTTON_MESSAGE 0x88

/* The parent process (the tabs' owner). */
static Process *parent_of(PocketsScreen *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* Calls the draw (vtable slot 2) or the update (slot 3) of a member object through its own
 * vtable, as the game does. */
static void call_slot(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

/* The pen went down this frame. */
static int pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* func_ov096_022a02ec (sub state 0x1a): once the cursor sprite's press animation ends, the
 * row it points at is picked and its code decided; sub state 0x23 closes the choice and
 * applies it. */
void PocketsScreen_DecideCodeRow(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite)) {
        PagedChoice_PickRow(choice_of(self), self->choice_row);
        self->choice_code = (u8) PagedChoice_Decide(choice_of(self), self->choice_page, self->choice_row);
        MenuScene_SetSubState(scene_of(self), 0x23);
    }
}
CLEAN_AS(func_ov096_022a02ec, PocketsScreen_DecideCodeRow)

/* func_ov096_022a033c (sub state 0x19): the choice of codes by the keys. A close request or B
 * leaves it; a touch goes to sub state 8 (the same choice by touch); the d-pad moves the
 * cursor sprite over the rows; A presses on the row (sub state 0x1a). */
void PocketsScreen_CodeChoiceByKeys(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked()) {
        PocketsScreen_CloseChoiceToLeave(self);
        return;
    }
    if (MenuScene_TakeTouch(scene_of(self))) {
        PocketsScreen_BeginSubState08(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PagedChoice_MoveCursor(choice_of(self), (int) keys, &self->choice_row, 0)) {
        PocketsScreen_GlideToRow(self);
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & POCKETS_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), 0x1a);
    } else if (pressed & POCKETS_PAD_B) {
        PocketsScreen_CloseChoiceToLeave(self);
    }
}
CLEAN_AS(func_ov096_022a033c, PocketsScreen_CodeChoiceByKeys)

/* func_ov096_022a03c4 (sub state 0x18): once the cursor sprite's press animation ends, the
 * reader's button is pressed. */
void PocketsScreen_ReaderPressAfterAnim(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
        PocketsScreen_PressButton(self);
    }
}
CLEAN_AS(func_ov096_022a03c4, PocketsScreen_ReaderPressAfterAnim)

/* func_ov096_022a03e4 (sub state 0x17): a letter is read and the keys are in use. A close
 * request leaves the menu; the cursor sprite, when it shows nothing, is put on the button's
 * anchor 1 with animation 1; a touch hides it and goes to sub state 7; A or B presses on the
 * button (sub state 0x18).
 * QUIRK: the close request is asked twice; the second answer, the same as the first, would
 * press the button and set POCKETS_FLAG_EXITING. */
void PocketsScreen_ReaderByKeys(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_ExitToParent(self);
        return;
    }
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_PressButton(self);
        PocketsScreen_SetFlags(self, POCKETS_FLAG_EXITING);
        return;
    }
    if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) &self->cursor_sprite) == GLIDER_ANIM_NONE) {
        int x = LabelButton_AnchorX(&self->button, 1);
        int y = LabelButton_AnchorY(&self->button, 1);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    if (MenuScene_TakeTouch(scene_of(self))) {
        PocketsScreen_HideCursorSprite(self);
        MenuScene_SetSubState(scene_of(self), 7);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & POCKETS_PAD_A) != 0 || (pressed & POCKETS_PAD_B) != 0) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), 0x18);
    }
}
CLEAN_AS(func_ov096_022a03e4, PocketsScreen_ReaderByKeys)

/* func_ov096_022a04a4 (sub state 0x16): after a swap by the cursor, back to the kept sub state
 * once the cursor sprite's animation ends. While its turn has settled, the held thing is drawn
 * again (sound 0xd when it was hidden) and follows the cursor sprite. */
void PocketsScreen_FinishSwapWithCursor(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite)) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
    }
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_40)) {
            PocketsScreen_ClearFlags(self, POCKETS_FLAG_40);
            PocketsSound_Play0d();
        }
        PocketsScreen_FollowCursorSprite(self);
    }
}
CLEAN_AS(func_ov096_022a04a4, PocketsScreen_FinishSwapWithCursor)

/* func_ov096_022a04f4 (sub state 0x15): the held thing changes places with what is at `unk_b7`
 * and is hidden while the cursor sprite turns (sub state 0x16), unless the turn is at its frame
 * 2, which goes back to sub state 0x0a instead. */
void PocketsScreen_SwapWithCursor(PocketsScreen *self)
{
    if (Glider_IsTurnAtFrame2(&self->cursor_sprite) == 0) {
        PocketsScreen_SwapHeldWith(self, self->unk_b7);
        PocketsScreen_SetFlags(self, POCKETS_FLAG_40);
        MenuScene_SetSubState(scene_of(self), 0x16);
        PocketsScreen_UpdatePopup(self);
    } else {
        MenuScene_SetSubState(scene_of(self), 0x0a);
    }
}
CLEAN_AS(func_ov096_022a04f4, PocketsScreen_SwapWithCursor)

/* func_ov096_022a053c (sub state 0x14): while the cursor sprite's turn has not settled the held
 * thing follows it. Then it is put down at `unk_b7` when the cursor is there (and with
 * POCKETS_FLAG_2000 `place_item` is held and glides on to `unk_b9`), else it glides to
 * `unk_b7`. When no glide started: the popup told of the cursor's place, sub state 0x0a and
 * sound 0xe. */
void PocketsScreen_PutDownWithCursor(PocketsScreen *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite) != 0) {
        PocketsScreen_FollowCursorSprite(self);
        return;
    }
    if (self->cursor == self->unk_b7) {
        PocketsScreen_PutHeldAt(self, self->unk_b7);
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_2000) != 0) {
            PocketsScreen_HoldItem(self, self->place_item, 0);
            PocketsScreen_GlideHeldTo(self, self->unk_b9, 4);
            PocketsScreen_ClearFlags(self, POCKETS_FLAG_2000);
        }
    } else {
        PocketsScreen_GlideHeldTo(self, self->unk_b7, 4);
    }
    if (self->base.sub_state == 0x14) {
        PocketsScreen_UpdatePopup(self);
        MenuScene_SetSubState(scene_of(self), 0x0a);
        PocketsSound_Play0e();
    }
}
CLEAN_AS(func_ov096_022a053c, PocketsScreen_PutDownWithCursor)

/* func_ov096_022a05d0 (sub state 0x13): after a pick up by the cursor, back to the kept sub
 * state once the cursor sprite's animation ends; the held thing follows the cursor sprite
 * (its answer returned). */
int PocketsScreen_FinishPickUp(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite)) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
    }
    return PocketsScreen_FollowCursorSprite(self);
}
CLEAN_AS(func_ov096_022a05d0, PocketsScreen_FinishPickUp)

/* func_ov096_022a05fc (sub state 0x12): once the cursor sprite's turn has settled, what is at
 * the cursor is picked up (sub state 0x13). */
void PocketsScreen_PickUpOnTurn(PocketsScreen *self)
{
    if (Glider_IsTurnSettled(&self->cursor_sprite)) {
        PocketsScreen_PickUpWithCursor(self, self->cursor);
        MenuScene_SetSubState(scene_of(self), 0x13);
    }
}
CLEAN_AS(func_ov096_022a05fc, PocketsScreen_PickUpOnTurn)

/* func_ov096_022a062c (sub state 0x11): once the cursor sprite's animation ends, the first of
 * its set and sub state 0x0a. */
void PocketsScreen_WaitCursorAnim(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite)) {
        PocketsScreen_ShowCursorFirstOfSet(self);
        MenuScene_SetSubState(scene_of(self), 0x0a);
    }
}
CLEAN_AS(func_ov096_022a062c, PocketsScreen_WaitCursorAnim)

/* func_ov096_022a0654 (sub state 0x10): once the cursor sprite's press animation ends, the
 * menu switches to the tab the cursor is on (the places 0x19-0x20 are tabs 0-7); for this
 * scene's own tab, sub state 0x11. */
void PocketsScreen_SwitchToCursorTab(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) != 0) {
        if (PocketsScreen_SwitchTab(self, self->cursor - POCKETS_ROW_FIRST) == 0) {
            PocketsScreen_BeginSubState11(self);
        }
    }
}
CLEAN_AS(func_ov096_022a0654, PocketsScreen_SwitchToCursorTab)

/* Obj_ov096_022a23e8::func_ov096_022a0688 (sub state 0x0f): once the cursor sprite stops, back
 * to the kept sub state, which is run at once; back to 0x0a-0x0c (the cursor's sub states), the
 * cursor's place is selected first. The held thing follows the cursor sprite. */
void PocketsScreen_WaitCursorGlide(PocketsScreen *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(scene_of(self), self->return_state);
        if ((u8) (self->return_state - 0x0a) <= 2) {
            PocketsScreen_SelectPlace(self, self->cursor);
        }
        PocketsScreen_RunSubState(self);
    }
    PocketsScreen_FollowCursorSprite(self);
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_022a0688Ev, PocketsScreen_WaitCursorGlide)

/* func_ov096_022a06d8 (sub state 0x0e): once the cursor sprite's press animation ends, the
 * action of the row it points at is kept, the row picked (with the action's command) and sub
 * state 0x1e.
 * REQUIRES: the row is below PAGED_CHOICE_ROWS (the game reads the bytes after the values). */
void PocketsScreen_PickActionRow(PocketsScreen *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->cursor_sprite) == 0) {
        return;
    }
    self->action = self->entries.values[self->choice_row];
    int sound = PocketsScreen_CueAction(self);
    PagedChoice_PickRowWithSound(choice_of(self), self->choice_row, sound);
    MenuScene_SetSubState(scene_of(self), 0x1e);
}
CLEAN_AS(func_ov096_022a06d8, PocketsScreen_PickActionRow)

/* func_ov096_022a072c (sub state 0x0d): the choice of actions by the keys. A close request or a
 * touch cancels it; the d-pad moves the cursor sprite over the rows (not to the first one set
 * apart in the fixed choice); A presses on the row (sub state 0x0e); B points at the cancel
 * row. */
void PocketsScreen_ActionChoiceByKeys(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked()) {
        PocketsScreen_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeTouch(scene_of(self))) {
        PocketsScreen_CancelChoice(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    u8 first = (u8) PocketsScreen_TestFlags(self, POCKETS_FLAG_FIXED_MENU);
    if (PagedChoice_MoveCursor(choice_of(self), (int) keys, &self->choice_row, first)) {
        PocketsScreen_GlideToRow(self);
        return;
    }
    if (data_021fbe40.pressed & POCKETS_PAD_A) {
        Glider_ShowSecondOfSet(&self->cursor_sprite);
        MenuScene_SetSubState(scene_of(self), 0x0e);
    } else if (data_021fbe40.pressed & POCKETS_PAD_B) {
        PocketsScreen_PointAtCancelRow(self);
    }
}
CLEAN_AS(func_ov096_022a072c, PocketsScreen_ActionChoiceByKeys)

/* func_ov096_022a07c8 (sub state 0x0c): a letter is held and moves with the cursor. A close
 * request puts it back and closes the menu. The d-pad moves the cursor (the popup told of the
 * new place and hidden). A puts it down at the cursor, or swaps it with what is there; B puts
 * it back. Else it follows the cursor sprite and a queued popup is shown. */
void PocketsScreen_MoveHeldLetterByKeys(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked()) {
        PocketsScreen_PlaceHeldAt(self, self->held_place, 1);
        PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PocketsScreen_MoveCursor(self, (int) keys, 2)) {
        PocketsScreen_UpdatePopup(self);
        PocketsScreen_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & POCKETS_PAD_A) {
        if (PocketsScreen_PlaceIsEmpty(self, self->cursor)) {
            PocketsScreen_BeginSubState14(self, self->cursor);
        } else {
            PocketsScreen_BeginSubState15(self, self->cursor);
        }
    } else if (pressed & POCKETS_PAD_B) {
        PocketsScreen_BeginSubState14(self, self->held_place);
    } else {
        PocketsScreen_FollowCursorSprite(self);
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov096_022a07c8, PocketsScreen_MoveHeldLetterByKeys)

/* What A does with a held item at the cursor's place among 0x21-0x25 (sub state 0x0b). */
static void put_held_item_on_top_place(PocketsScreen *self)
{
    u8 place = self->cursor;
    if (place == POCKETS_PLACE_PLAYER) {
        self->record_slot = (u8) PocketsScreen_HeldRecordSlot(self);
        PocketsScreen_BeginSubState14(self, self->cursor);
    } else if (place == POCKETS_PLACE_22) {
        PocketsScreen_RequestSwitchOff(self);
        PocketsScreen_BeginSubState14(self, self->cursor);
    } else if (place == POCKETS_PLACE_BELLS) {
        if (PocketsScreen_HoldsBellBag(self, 1) == 0 && self->held_place == POCKETS_PLACE_BELLS) {
            SoundSys_PlaySe(0x2a);
            return;
        }
        PocketsScreen_RequestSwitchOff(self);
        PocketsScreen_BeginSubState14(self, self->cursor);
    }
}

/* func_ov096_022a0880 (sub state 0x0b): an item is held and moves with the cursor. A close
 * request puts it back and closes the menu. The d-pad moves the cursor (the popup told of the
 * new place and hidden).
 * A: at place 0x21 (when it may go there) or at 0x22-0x25 it is put down there (the player's
 * place keeps the record slot it goes to; the bells' place takes only a bag that fits, a
 * refused bag from the wallet sounds 0x2a); elsewhere, when PocketsScreen_CheckDrop allows it,
 * it merges with the item of a grid place (the grid's object shown the rest), then is put down
 * on an empty place or swapped (a bell bag keeping the place and itself at `unk_b9` and
 * `place_item`).
 * B: it goes back to its place; when it may not and a place is kept at `unk_b9`, it goes there
 * and the place it came from is kept instead (POCKETS_FLAG_2000).
 * Unless A was pressed, it then follows the cursor sprite and a queued popup is shown. */
void PocketsScreen_MoveHeldItemByKeys(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_PlaceHeldAt(self, self->held_place, 1);
        PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PocketsScreen_MoveCursor(self, (int) keys, 1) != 0) {
        PocketsScreen_UpdatePopup(self);
        PocketsScreen_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    if ((data_021fbe40.pressed & POCKETS_PAD_A) != 0) {
        if (self->cursor == POCKETS_PLACE_21) {
            if (PocketsScreen_CanReachPlace21(self) == 0) {
                return;
            }
            PocketsScreen_RequestSwitchOff(self);
            PocketsScreen_BeginSubState14(self, self->cursor);
            return;
        }
        if (PocketsScreen_IsTopPlace(self, self->cursor) != 0) {
            put_held_item_on_top_place(self);
            return;
        }
        if (PocketsScreen_CheckDrop(self, self->cursor, self->item, self->held_state) != 0) {
            return;
        }
        if (PocketsScreen_IsLetterPlace(self, self->cursor) != 0) {
            PocketsScreen_RequestSwitchOff(self);
        }
        if (PocketsScreen_IsGridPlace(self, self->cursor) != 0) {
            u16 there = PocketsScreen_PlaceItem(self, self->cursor);
            int there_state = PocketsScreen_PlaceItemState(self, self->cursor);
            if (PocketsScreen_MergeItems(self, &self->item, self->held_state, &there, (u8) there_state) == 0) {
                PocketsGrid_SetItem((PocketsGrid *) (void *) self->grid, func_ov096_0229f7ac(self, self->cursor), there,
                                    there_state);
            }
        }
        if (PocketsScreen_PlaceItem(self, self->cursor) == ITEM_NONE) {
            PocketsScreen_BeginSubState14(self, self->cursor);
            return;
        }
        if (self->unk_b9 != POCKETS_NO_PLACE && PocketsScreen_HoldsBellBag(self, 1) != 0) {
            self->unk_b9 = self->cursor;
            self->place_item = self->item;
        }
        PocketsScreen_BeginSubState15(self, self->cursor);
        return;
    }
    if ((data_021fbe40.pressed & POCKETS_PAD_B) != 0) {
        if (PocketsScreen_CheckReturnHeld(self, self->held_place) == 0) {
            PocketsScreen_BeginSubState14(self, self->held_place);
        } else if (self->unk_b9 != POCKETS_NO_PLACE) {
            u8 came_from = self->held_place;
            self->held_place = self->unk_b9;
            PocketsScreen_BeginSubState14(self, self->held_place);
            self->unk_b9 = came_from;
            PocketsScreen_SetFlags(self, POCKETS_FLAG_2000);
        }
    }
    PocketsScreen_FollowCursorSprite(self);
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(func_ov096_022a0880, PocketsScreen_MoveHeldItemByKeys)

/* func_ov096_022a0af0 (sub state 0x0a): the cursor waits for the keys. A touch hides the
 * cursor sprite (sub state 0). The d-pad moves the cursor (the popup told of the new place and
 * hidden). A opens the choice of a taken grid or letter place, presses on a tab of the row
 * (sub state 0x10), or opens the choice of the bells' or the player's place; R and L switch to
 * the next and the previous tab, B closes the menu. Else a queued popup is shown. */
void PocketsScreen_IdleByKeys(PocketsScreen *self)
{
    if (MenuScene_TakeTouch(scene_of(self)) != 0) {
        PocketsScreen_EndActionHidden(self);
        Popup_Hide(&self->popup, 1);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(scene_of(self));
    if (PocketsScreen_MoveCursor(self, (int) keys, 0) != 0) {
        PocketsScreen_UpdatePopup(self);
        PocketsScreen_GlideToCursor(self);
        Popup_Hide(&self->popup, 0);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & POCKETS_PAD_A) {
        if (PocketsScreen_IsGridPlace(self, self->cursor) != 0 || PocketsScreen_IsLetterPlace(self, self->cursor) != 0) {
            if (PocketsScreen_PlaceIsEmpty(self, self->cursor) == 0) {
                PocketsScreen_OpenSlotMenu(self, self->cursor, 0);
            }
        } else if (PocketsScreen_IsRowPlace(self, self->cursor) != 0) {
            PocketsScreen_BeginSubState10(self);
        } else if (self->cursor == POCKETS_PLACE_BELLS) {
            PocketsScreen_OpenSlotMenu(self, POCKETS_PLACE_BELLS, 0);
        } else if (self->cursor == POCKETS_PLACE_PLAYER) {
            PocketsScreen_OpenSlotMenu(self, POCKETS_PLACE_PLAYER, 0);
        }
    } else if (pressed & POCKETS_PAD_R) {
        PocketsScreen_SwitchTab(self, MenuTabs_NextTab(POCKETS_TAB_SELF));
    } else if (pressed & POCKETS_PAD_L) {
        PocketsScreen_SwitchTab(self, MenuTabs_PreviousTab(POCKETS_TAB_SELF));
    } else if (pressed & POCKETS_PAD_B) {
        PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
    } else {
        Popup_ShowQueued(&self->popup);
    }
}
CLEAN_AS(func_ov096_022a0af0, PocketsScreen_IdleByKeys)

/* func_ov096_022a0c28 (sub state 9): the pen holds a digit of the wallet (the digit marked by
 * the wallet's display). A close request closes the menu; the pen lifted goes back to sub
 * state 0; once main's byte data_021f6c30 reaches 4, the bag of that amount (`place_item`,
 * PocketsScreen_BellAmountAtTouch) is picked up from the bells' place, 8 pixels up and left of
 * the pen, and POCKETS_FLAG_4000 set. */
void PocketsScreen_HoldBellDigit(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked()) {
        PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
        PocketsWallet_MarkDigits((PocketsWallet *) (void *) self->unk_de0, 0);
        return;
    }
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(scene_of(self), 0);
        PocketsWallet_MarkDigits((PocketsWallet *) (void *) self->unk_de0, 0);
        return;
    }
    if (PocketsScreen_Byte6c30AtLeast(self, 4) == 0) {
        return;
    }
    PocketsScreen_TouchPlace(self, POCKETS_PLACE_BELLS);
    self->grab_dx = -8;
    self->grab_dy = -8;
    PocketsScreen_PickUpWithTouch(self, POCKETS_PLACE_BELLS);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_4000);
    PocketsWallet_MarkDigits((PocketsWallet *) (void *) self->unk_de0, self->bell_choice);
}
CLEAN_AS(func_ov096_022a0c28, PocketsScreen_HoldBellDigit)

/* func_ov096_022a0cb8 (sub state 8): the choice of codes by touch. A close request leaves it; a
 * button goes to sub state 0x19 (the same choice by the keys); a touch on a row picks and
 * decides it (sub state 0x23), a touch elsewhere leaves the choice. */
void PocketsScreen_CodeChoiceByTouch(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_CloseChoiceToLeave(self);
        return;
    }
    if (MenuScene_TakeButtons(scene_of(self), 1) != 0) {
        PocketsScreen_BeginSubState19(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrNone(choice_of(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        PagedChoice_PickRow(choice_of(self), row);
        self->choice_code = (u8) PagedChoice_Decide(choice_of(self), self->choice_page, (u8) row);
        MenuScene_SetSubState(scene_of(self), 0x23);
    } else {
        PocketsScreen_CloseChoiceToLeave(self);
    }
}
CLEAN_AS(func_ov096_022a0cb8, PocketsScreen_CodeChoiceByTouch)

/* func_ov096_022a0d60 (sub state 7): a letter is read and the touch is in use. A close request
 * leaves the menu; a button goes to sub state 0x17 (the keys); a touch on the button presses
 * it. */
void PocketsScreen_ReaderByTouch(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked()) {
        PocketsScreen_ExitToParent(self);
    } else if (MenuScene_TakeButtons(scene_of(self), 1)) {
        MenuScene_SetSubState(scene_of(self), 0x17);
    } else if (LabelButton_IsTouched(&self->button)) {
        PocketsScreen_PressButton(self);
    }
}
CLEAN_AS(func_ov096_022a0d60, PocketsScreen_ReaderByTouch)

/* func_ov096_022a0da8 (sub state 6): a letter is held and dragged by the pen. A close request
 * puts it back and closes the menu. Else it follows the pen and the letter place under its
 * corner (8 pixels right and down) is marked; when the pen is lifted the letter is put down
 * there (sound 0xe and the action ends), or glides back to its place when there is none. */
void PocketsScreen_DragHeldLetter(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_PlaceHeldAt(self, self->held_place, 1);
        PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
        return;
    }
    PocketsScreen_FollowTouch(self);
    PocketsScreen_ClearHighlights(self);
    int place = PocketsScreen_LetterPlaceAtTouch(self, self->menu_x + 8, self->menu_y + 8, 0);
    if (place != POCKETS_NO_PLACE) {
        if (data_021fbdd8 == 0) {
            if (PocketsScreen_PutHeldLetterAt(self, place) == 0) {
                PocketsScreen_GlideHeldTo(self, self->held_place, 4);
            }
            PocketsSound_Play0e();
            PocketsScreen_EndAction(self);
        } else {
            PocketsScreen_HighlightPlace(self, (unsigned int) place);
        }
    } else if (data_021fbdd8 == 0) {
        PocketsScreen_GlideHeldTo(self, self->held_place, 4);
    }
}
CLEAN_AS(func_ov096_022a0da8, PocketsScreen_DragHeldLetter)

/* What lifting the pen over place 0x22-0x25 does with a dragged item (sub state 5). */
static void drop_dragged_item_on_top_place(PocketsScreen *self, u8 place)
{
    if (place == POCKETS_PLACE_22 || place == POCKETS_PLACE_23) {
        if (PocketsScreen_CanUseHeld(self) == 0) {
            PocketsScreen_GlideHeldTo(self, self->held_place, 4);
            return;
        }
        if (PocketsScreen_UseHeld(self) != 0) {
            PocketsScreen_EndAction(self);
        }
    } else if (place == POCKETS_PLACE_PLAYER) {
        self->record_slot = (u8) PocketsScreen_HeldRecordSlot(self);
        if (self->record_slot < 1) {
            PocketsScreen_RefuseRecordSlot(self);
            return;
        }
        if (self->record_slot == 1) {
            PocketsScreen_GlideHeldTo(self, self->held_place, 4);
            return;
        }
        PocketsScreen_BeginSubState25(self);
    } else if (place == POCKETS_PLACE_BELLS) {
        if (PocketsScreen_HoldsBellBag(self, 0) != 0) {
            PocketsScreen_PutBagInWallet(self);
            return;
        }
        PocketsScreen_GlideHeldTo(self, self->held_place, 4);
    } else {
        PocketsScreen_GlideHeldTo(self, self->held_place, 4);
    }
}

/* func_ov096_022a0e48 (sub state 5): an item is held and dragged by the pen. A close request
 * puts it back and closes the menu. Else it follows the pen and the place under its corner (8
 * pixels right and down) is marked: a grid or letter place, else one of 0x22-0x25, else 0x21.
 * When the pen is lifted:
 *   a grid or letter place     put down there when PocketsScreen_CheckSwap allows it (a
 *                              letter's place asks the switch off; the action ends when still
 *                              in this sub state; sound 0xe), else back to its place
 *   0x22, 0x23                 used when it can be (the action ends when used up)
 *   the player's place         into its record slot (PocketsScreen_BeginSubState25), refused
 *                              when it fits none, back when the slot is 1
 *   the bells' place           a bell bag goes into the wallet
 *   0x21                       swapped with the record's item when it may go there
 * and back to its place otherwise. */
void PocketsScreen_DragHeldItem(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_PlaceHeldAt(self, self->held_place, 1);
        PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
        return;
    }
    PocketsScreen_FollowTouch(self);
    PocketsScreen_ClearHighlights(self);
    int x = self->menu_x + 8;
    int y = self->menu_y + 8;

    int place = PocketsScreen_GridPlaceAtTouch(self, x, y, 0);
    if (place == POCKETS_NO_PLACE) {
        place = PocketsScreen_LetterPlaceAtTouch(self, x, y, 0);
    }
    if (place != POCKETS_NO_PLACE) {
        if (data_021fbdd8 != 0) {
            PocketsScreen_HighlightPlace(self, (unsigned int) place);
        } else if (PocketsScreen_CheckSwap(self, place, self->held_place) == 0) {
            if (PocketsScreen_IsLetterPlace(self, (unsigned int) place) != 0) {
                PocketsScreen_RequestSwitchOff(self);
            }
            PocketsScreen_PutHeldItemAt(self, place);
            if (self->base.sub_state == 5) {
                PocketsScreen_EndAction(self);
            }
            if (PocketsScreen_IsGridPlace(self, (unsigned int) place) != 0 ||
                PocketsScreen_IsLetterPlace(self, (unsigned int) place) != 0) {
                PocketsSound_Play0e();
            }
        } else {
            PocketsScreen_GlideHeldTo(self, self->held_place, 4);
        }
        return;
    }

    u8 top = (u8) PocketsScreen_PlaceAtTouch(self, x, y);
    if (top != POCKETS_NO_PLACE) {
        if (data_021fbdd8 != 0) {
            PocketsScreen_HighlightPlace(self, top);
        } else {
            drop_dragged_item_on_top_place(self, top);
        }
        return;
    }

    if (PocketsScreen_TouchOnPlace21(self, x, y) != 0) {
        if (data_021fbdd8 != 0) {
            PocketsScreen_HighlightPlace(self, POCKETS_PLACE_21);
        } else if (PocketsScreen_CanReachPlace21(self) != 0) {
            PocketsScreen_SwapRecordItem(self);
            PocketsScreen_EndAction(self);
        } else {
            PocketsScreen_GlideHeldTo(self, self->held_place, 4);
        }
        return;
    }
    if (data_021fbdd8 == 0) {
        PocketsScreen_GlideHeldTo(self, self->held_place, 4);
    }
}
CLEAN_AS(func_ov096_022a0e48, PocketsScreen_DragHeldItem)

/* func_ov096_022a1058 (sub state 4): the choice of actions by touch, once it is shown. A close
 * request or a button cancels it; a touch on a row (or below the rows: the last one; not the
 * first one set apart in the fixed choice) keeps its action, picks it with the action's
 * command and goes to sub state 0x1e.
 * REQUIRES: the row is below PAGED_CHOICE_ROWS, as PocketsScreen_PickActionRow. */
void PocketsScreen_ActionChoiceByTouch(PocketsScreen *self)
{
    if (PagedChoice_IsShown(choice_of(self)) == 0) {
        return;
    }
    if (StateFlags_MenuCloseAsked() != 0) {
        PocketsScreen_CancelChoice(self);
        return;
    }
    if (MenuScene_TakeButtons(scene_of(self), 1) != 0) {
        PocketsScreen_CancelChoice(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int row = PagedChoice_RowAtOrLast(choice_of(self), data_021f6c58, data_021f6c54);
    if (row < 0) {
        return;
    }
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_FIXED_MENU) != 0 && row == 0) {
        return;
    }
    self->action = self->entries.values[row];
    int sound = PocketsScreen_CueAction(self);
    PagedChoice_PickRowWithSound(choice_of(self), row, sound);
    MenuScene_SetSubState(scene_of(self), 0x1e);
}
CLEAN_AS(func_ov096_022a1058, PocketsScreen_ActionChoiceByTouch)

/* The pen stays on a touched place while the popup is up: `open_delay` frames, then the
 * place's choice opens above the popup (sub state 2). Whether the popup is up. */
static int open_choice_after_delay(PocketsScreen *self)
{
    if (Popup_IsUp(&self->popup) == 0) {
        return 0;
    }
    if (self->open_delay != 0) {
        self->open_delay--;
    } else {
        PocketsScreen_OpenSlotMenu(self, self->touch_place, 1);
        MenuScene_SetSubState(scene_of(self), 2);
    }
    return 1;
}

/* func_ov096_022a1118 (sub state 3): the pen was lifted from a touched place: the place's
 * choice opens once the popup is up and the delay has run out. */
void PocketsScreen_WaitPopupToOpenChoice(PocketsScreen *self)
{
    open_choice_after_delay(self);
}
CLEAN_AS(func_ov096_022a1118, PocketsScreen_WaitPopupToOpenChoice)

/* func_ov096_022a1160 (sub state 2): the choice of the touched place is open while the pen
 * stays down. A close request or the pen lifted goes to sub state 4 (the choice by touch); the
 * pen dragged more than 8 pixels from a place with POCKETS_FLAG_04 picks its thing up, the
 * choice asked to close and the popup hidden. */
void PocketsScreen_HoldTouchWithChoice(PocketsScreen *self)
{
    if (StateFlags_MenuCloseAsked() != 0) {
        MenuScene_SetSubState(scene_of(self), 4);
        return;
    }
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(scene_of(self), 4);
        return;
    }
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_04) == 0) {
        return;
    }
    if (PocketsScreen_TouchMoved(self) == 0) {
        return;
    }
    PocketsScreen_PickUpWithTouch(self, self->touch_place);
    PagedChoice_RequestClose(choice_of(self), 0);
    Popup_Hide(&self->popup, 1);
}
CLEAN_AS(func_ov096_022a1160, PocketsScreen_HoldTouchWithChoice)

/* Obj_ov096_022a23e8::func_ov096_022a11d0 (sub state 1): the pen is on a touched place
 * (PocketsScreen_TouchPlace). Lifted: back to sub state 0 with the popup closing after 60
 * frames when the place offers no choice row, else sub state 3, run at once. Held, at a place
 * with POCKETS_FLAG_04: dragged more than 8 pixels it picks the thing up; while the popup is up
 * the place's choice opens after the delay (sub state 2). Else a queued popup is shown. */
void PocketsScreen_HoldTouchOnPlace(PocketsScreen *self)
{
    if (data_021fbdd8 == 0) {
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_NO_ENTRIES) != 0) {
            MenuScene_SetSubState(scene_of(self), 0);
            Popup_SetTimer(&self->popup, 60);
        } else {
            MenuScene_SetSubState(scene_of(self), 3);
            PocketsScreen_RunSubState(self);
        }
        return;
    }
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_04) != 0) {
        if (PocketsScreen_TouchMoved(self) != 0) {
            PocketsScreen_PickUpWithTouch(self, self->touch_place);
            return;
        }
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_NO_ENTRIES) == 0 && open_choice_after_delay(self)) {
            return;
        }
    }
    Popup_ShowQueued(&self->popup);
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_022a11d0Ev, PocketsScreen_HoldTouchOnPlace)

/* func_ov096_022a128c (sub state 0): the touch is in use and the cursor sprite hidden. A button
 * puts the cursor at place 0 and shows it (sub state 0x0a). A touch on a taken grid or letter
 * place touches it (sub state 1); on the bells' place opens its choice; on a digit of the
 * wallet opens place 0x27's choice when the wallet holds less, or holds the digit (sub state
 * 9) when it holds enough; on the player's place opens its choice. */
void PocketsScreen_IdleByTouch(PocketsScreen *self)
{
    if (MenuScene_TakeButtons(scene_of(self), 1) != 0) {
        self->cursor = 0;
        PocketsScreen_EndActionAtCursor(self);
        return;
    }
    if (!pen_pressed()) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = PocketsScreen_GridPlaceAtTouch(self, x, y, 1);
    if (place != POCKETS_NO_PLACE) {
        PocketsScreen_TouchPlace(self, place);
        return;
    }
    place = PocketsScreen_LetterPlaceAtTouch(self, x, y, 1);
    if (place != POCKETS_NO_PLACE) {
        PocketsScreen_TouchPlace(self, place);
        return;
    }
    if (PocketsScreen_TouchOnBells(self, x, y) != 0) {
        PocketsScreen_OpenSlotMenu(self, POCKETS_PLACE_BELLS, 0);
        return;
    }
    switch (PocketsScreen_BellAmountAtTouch(self, x, y)) {
        case 1:
            PocketsScreen_OpenSlotMenu(self, POCKETS_PLACE_27, 0);
            break;
        case 2:
            MenuScene_SetSubState(scene_of(self), 9);
            PocketsWallet_MarkDigits((PocketsWallet *) (void *) self->unk_de0, self->bell_choice);
            break;
        default:
            if (PocketsScreen_TouchOnPlayer(self, x, y) != 0) {
                PocketsScreen_OpenSlotMenu(self, POCKETS_PLACE_PLAYER, 0);
            }
            break;
    }
}
CLEAN_AS(func_ov096_022a128c, PocketsScreen_IdleByTouch)

/* func_ov096_022a1384: a step of the wallet display's setup; its answer. */
int PocketsScreen_StepWalletSetup(PocketsScreen *self)
{
    return PocketsWallet_LoadObjFiles((PocketsWallet *) (void *) self->unk_de0);
}
CLEAN_AS(func_ov096_022a1384, PocketsScreen_StepWalletSetup)

/* func_ov096_022a1394: layer 6 at priority 2, with its plain background settings. */
void PocketsScreen_SetUpLayer6(void)
{
    DisplayLayer_SetPriority(POCKETS_LAYER, 2);
    DisplayLayer_SetBgControl(POCKETS_LAYER, 0, 0, 0);
}
CLEAN_AS(func_ov096_022a1394, PocketsScreen_SetUpLayer6)

/* func_ov096_022a13b4: the end of a frame: a pending switch applied, the choice and the
 * wallet's display updated, and the popup placed when its update asks for it. */
void PocketsScreen_EndFrame(PocketsScreen *self)
{
    PocketsScreen_ApplySwitch(self);
    PagedChoice_Update(choice_of(self));
    PocketsWallet_Update((PocketsWallet *) (void *) self->unk_de0);
    if (Popup_Update(&self->popup)) {
        PocketsScreen_PlacePopup(self);
    }
}
CLEAN_AS(func_ov096_022a13b4, PocketsScreen_EndFrame)

/* func_ov096_022a13f0: the start of a frame: the objects at 0x2e8 and the three objects of
 * ov094's updated. */
void PocketsScreen_BeginFrame(PocketsScreen *self)
{
    PocketsScreen_UpdateObjects2e8(self);
    PocketsWallet_BeginFrame((PocketsWallet *) (void *) self->unk_de0);
    PocketsGrid_BeginFrame((PocketsGrid *) (void *) self->grid);
    PocketsLetters_BeginFrame((PocketsLetters *) (void *) self->letters);
}
CLEAN_AS(func_ov096_022a13f0, PocketsScreen_BeginFrame)

/* func_ov096_022a1424 */
void PocketsScreen_EndInteractiveFrame(PocketsScreen *self)
{
    PocketsScreen_EndFrame(self);
}
CLEAN_AS(func_ov096_022a1424, PocketsScreen_EndInteractiveFrame)

/* func_ov096_022a142c: the start of a frame, then the cursor sprite's update through its class
 * (vtable slot 3). */
void PocketsScreen_BeginInteractiveFrame(PocketsScreen *self)
{
    PocketsScreen_BeginFrame(self);
    call_slot(&self->cursor_sprite, 3);
}
CLEAN_AS(func_ov096_022a142c, PocketsScreen_BeginInteractiveFrame)

/* func_ov096_022a1448: the members' teardown before the scene closes. */
void PocketsScreen_Teardown(PocketsScreen *self)
{
    PocketsScreen_UpdateObjects2e8(self);
    PocketsWallet_Teardown((PocketsWallet *) (void *) self->unk_de0);
    PocketsGrid_Teardown((PocketsGrid *) (void *) self->grid);
    PagedChoice_Dismiss(choice_of(self));
    LetterView_ReleaseBoxes((LetterView *) (void *) self->unk_2a74);
}
CLEAN_AS(func_ov096_022a1448, PocketsScreen_Teardown)

/* func_ov096_022a1488: the scene's setup: no flags, the three objects of ov094's set up, no
 * popup place, the popup's draw value 2, the glide stopped, nothing held, the cursor at main's
 * place (GroupParams_C50), the choice on layer 3, the letter view set up, no delay; when the
 * parent's byte 0x98 is set, POCKETS_FLAG_STEPWISE_SETUP. */
void PocketsScreen_Setup(PocketsScreen *self)
{
    self->flags = 0;
    PocketsGrid_Init((PocketsGrid *) (void *) self->grid, 2);
    PocketsLetters_Init((PocketsLetters *) (void *) self->letters, 2);
    PocketsWallet_Init((PocketsWallet *) (void *) self->unk_de0, 6);
    self->popup_place = POCKETS_NO_PLACE;
    Popup_SetDrawValue(&self->popup, 2);
    Glide_Stop(&self->glide);
    PocketsScreen_DropHeld(self);
    self->cursor = GroupParams_C50();
    PagedChoice_Init(choice_of(self), READER_LAYER, 1, NULL);
    PagedChoice_BuildPages(choice_of(self));
    LetterView_Init((LetterView *) (void *) self->unk_2a74, 3);
    self->open_delay = 0;
    if (MenuTabs_IsOpening((MenuTabs *) (void *) parent_of(self)) != 0) {
        PocketsScreen_SetFlags(self, POCKETS_FLAG_STEPWISE_SETUP);
    }
}
CLEAN_AS(func_ov096_022a1488, PocketsScreen_Setup)

/* func_ov096_022a1540: the parent's byte 0x94 cleared. */
void PocketsScreen_ClearParentByte94(PocketsScreen *self)
{
    MenuTabs_SlideOut((MenuTabs *) (void *) parent_of(self));
}
CLEAN_AS(func_ov096_022a1540, PocketsScreen_ClearParentByte94)

/* func_ov096_022a1554 (state 10): the letter read wipes out. When done, layers 3 and 4 hidden
 * and the button no longer drawn; leaving the menu (POCKETS_FLAG_EXITING) ends the run phase
 * and the drawing, else the parent's bytes 0x94 and 0x91 are set and the setup starts again
 * (state 0). */
void PocketsScreen_WipeOutReader(PocketsScreen *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0) == 0) {
        MenuScene_ScrollWipe(scene_of(self), READER_LAYER, 0, 0);
        MenuScene_ScrollWipe(scene_of(self), READER_UNDER_LAYER, 0, 0);
        return;
    }
    DisplayLayer_HideAndResetScroll(READER_LAYER);
    DisplayLayer_HideAndResetScroll(READER_UNDER_LAYER);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_BUTTON_DRAWN);
    Process *parent = parent_of(self);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_EXITING)) {
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_DELETE);
        PocketsScreen_ClearFlags(self, POCKETS_FLAG_DRAWN);
    } else {
        MenuTabs_SlideIn((MenuTabs *) (void *) parent);
        PocketsScreen_StartSetup(self);
    }
}
CLEAN_AS(func_ov096_022a1554, PocketsScreen_WipeOutReader)

/* func_ov096_022a15d4 (state 9): the letter read starts to wipe out (state 10). */
void PocketsScreen_StartWipeOutReader(PocketsScreen *self)
{
    MenuScene_StartWipeOnWindow2(scene_of(self), READER_LAYER, 0, 0, POCKETS_WIPE_MARGIN);
    MenuScene_ScrollWipe(scene_of(self), READER_LAYER, 0, 0);
    MenuScene_ScrollWipe(scene_of(self), READER_UNDER_LAYER, 0, 0);
    MenuScene_SetState(scene_of(self), 10);
}
CLEAN_AS(func_ov096_022a15d4, PocketsScreen_StartWipeOutReader)

/* func_ov096_022a1610 (state 8): the letter read wipes in. When done, phase 2 with sub state 7
 * (the touch in use) or 0x17 (the keys). */
void PocketsScreen_WipeInReader(PocketsScreen *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0) != 0) {
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_INTERACTIVE);
        if (StateFlags_IsClear2() != 0) {
            MenuScene_SetSubState(scene_of(self), 7);
        } else {
            MenuScene_SetSubState(scene_of(self), 0x17);
        }
    } else {
        MenuScene_ScrollWipe(scene_of(self), READER_LAYER, 0, 0);
        MenuScene_ScrollWipe(scene_of(self), READER_UNDER_LAYER, 0, 0);
    }
}
CLEAN_AS(func_ov096_022a1610, PocketsScreen_WipeInReader)

/* func_ov096_022a1660 (state 7): the letter at the picked place is read: marked read, shown by
 * the letter view on layers 3 and 4, which wipe in (state 8), and the button shown in the
 * lower right with its message 0x88 (and drawn). */
void PocketsScreen_OpenReader(PocketsScreen *self)
{
    void *letter = (void *) (uintptr_t) PocketsScreen_SlotLetter(self);
    func_020664a8(letter);
    LetterView_Show((LetterView *) (void *) self->unk_2a74, letter, READER_LAYER, READER_UNDER_LAYER, 1);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), READER_LAYER, 0, 0, POCKETS_WIPE_MARGIN);
    DisplayLayer_Show(READER_LAYER);
    MenuScene_ScrollWipe(scene_of(self), READER_LAYER, 0, 0);
    DisplayLayer_Show(READER_UNDER_LAYER);
    MenuScene_ScrollWipe(scene_of(self), READER_UNDER_LAYER, 0, 0);
    MenuScene_SetState(scene_of(self), 8);
    LabelButton_ShowLowerRight(&self->button, READER_BUTTON_MESSAGE);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_BUTTON_DRAWN);
}
CLEAN_AS(func_ov096_022a1660, PocketsScreen_OpenReader)

/* func_ov096_022a16e4 (state 6): the pockets wipe out. When done, layer 6 hidden and the
 * objects no longer drawn; with POCKETS_FLAG_80 the picked letter is read next (state 7), else
 * the run phase is set and the scene no longer drawn. The objects' offset follows the wipe. */
void PocketsScreen_WipeOut(PocketsScreen *self)
{
    if (MenuScene_StepWipe(scene_of(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(POCKETS_LAYER);
        PocketsScreen_ClearFlags(self, POCKETS_FLAG_OBJECTS_DRAWN);
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_80) != 0) {
            MenuScene_SetState(scene_of(self), 7);
        } else {
            MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_DELETE);
            PocketsScreen_ClearFlags(self, POCKETS_FLAG_DRAWN);
        }
    } else {
        MenuScene_ScrollWipe(scene_of(self), POCKETS_LAYER, 0, 0);
    }
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov096_022a16e4, PocketsScreen_WipeOut)

/* func_ov096_022a1744 (state 5): the popup and the cursor sprite hidden and the pockets start
 * to wipe out (state 6). */
void PocketsScreen_StartWipeOut(PocketsScreen *self)
{
    Popup_Hide(&self->popup, 1);
    PocketsScreen_HideCursorSprite(self);
    MenuScene_StartWipeOnWindow2(scene_of(self), 8, 0, 0, POCKETS_WIPE_MARGIN);
    MenuScene_ScrollWipe(scene_of(self), POCKETS_LAYER, 0, 0);
    MenuScene_SetState(scene_of(self), 6);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov096_022a1744, PocketsScreen_StartWipeOut)

/* func_ov096_022a1794 (state 4): the pockets wipe in; when done, phase 2 and the action ends
 * (PocketsScreen_EndAction picks the first sub state). The objects' offset follows the wipe. */
void PocketsScreen_WipeIn(PocketsScreen *self)
{
    if (MenuScene_StepWipeBack(scene_of(self), 0)) {
        MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_INTERACTIVE);
        PocketsScreen_EndAction(self);
    }
    MenuScene_ScrollWipe(scene_of(self), POCKETS_LAYER, 0, 0);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov096_022a1794, PocketsScreen_WipeIn)

/* func_ov096_022a17cc (state 3): the grid's and the letters' objects prepared, layer 6 shown and
 * wiping in (state 4); the scene and its objects drawn. */
void PocketsScreen_StartWipeIn(PocketsScreen *self)
{
    PocketsGrid_LoadPockets((PocketsGrid *) (void *) self->grid);
    PocketsLetters_LoadPockets((PocketsLetters *) (void *) self->letters);
    MenuScene_StartWipeCoveredOnWindow2(scene_of(self), 8, 3, 0, POCKETS_WIPE_MARGIN);
    DisplayLayer_Show(POCKETS_LAYER);
    MenuScene_ScrollWipe(scene_of(self), POCKETS_LAYER, 0, 0);
    MenuScene_SetState(scene_of(self), 4);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_DRAWN);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_OBJECTS_DRAWN);
    self->wipe_y = MenuScene_WipeOffsetY(scene_of(self));
}
CLEAN_AS(func_ov096_022a17cc, PocketsScreen_StartWipeIn)

/* func_ov096_022a1838 (state 2): a step of the wallet display's setup (its answer unused), then
 * state 3, run at once unless the setup goes step by step (POCKETS_FLAG_STEPWISE_SETUP).
 * QUIRK: the flag is then cleared although it is known to be clear. */
void PocketsScreen_SetupWalletStep(PocketsScreen *self)
{
    PocketsScreen_StepWalletSetup(self);
    MenuScene_SetState(scene_of(self), 3);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_STEPWISE_SETUP) == 0) {
        PocketsScreen_StartWipeIn(self);
        PocketsScreen_ClearFlags(self, POCKETS_FLAG_STEPWISE_SETUP);
    }
}
CLEAN_AS(func_ov096_022a1838, PocketsScreen_SetupWalletStep)

/* func_ov096_022a186c (state 1): the wallet's display prepared, then state 2 (at once unless
 * the setup goes step by step). */
void PocketsScreen_SetupWallet(PocketsScreen *self)
{
    PocketsWallet_SetUpContents((PocketsWallet *) (void *) self->unk_de0);
    MenuScene_SetState(scene_of(self), 2);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_STEPWISE_SETUP) == 0) {
        PocketsScreen_SetupWalletStep(self);
    }
}
CLEAN_AS(func_ov096_022a186c, PocketsScreen_SetupWallet)

/* func_ov096_022a18a0 (state 0): layer 6 set up and the wallet's display started, then state 1
 * (at once unless the setup goes step by step). */
void PocketsScreen_StartSetup(PocketsScreen *self)
{
    PocketsScreen_SetUpLayer6();
    PocketsWallet_LoadBackground((PocketsWallet *) (void *) self->unk_de0, 1);
    MenuScene_SetState(scene_of(self), 1);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_STEPWISE_SETUP) == 0) {
        PocketsScreen_SetupWallet(self);
    }
}
CLEAN_AS(func_ov096_022a18a0, PocketsScreen_StartSetup)

/* func_ov096_022a18dc: the menu switches to `tab` (POCKETS_TAB_CLOSE closes it): the parent
 * told, the pockets wipe out (state 5) after the parent's phase 1; any tab but the close one
 * asks the switch off; no letter is read. Whether it switched: not for no tab or this scene's
 * own.
 * QUIRK: the parent is asked for before the tab is checked, and gets the tab's low byte. */
int PocketsScreen_SwitchTab(PocketsScreen *self, int tab)
{
    Process *parent = parent_of(self);
    if (tab == POCKETS_TAB_NONE || tab == POCKETS_TAB_SELF) {
        return 0;
    }
    MenuTabs_SelectTab((MenuTabs *) (void *) parent, (u8) tab);
    self->base.state = 5;
    MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_STATES);
    if (tab != POCKETS_TAB_CLOSE) {
        PocketsScreen_RequestSwitchOff(self);
    }
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_80);
    return 1;
}
CLEAN_AS(func_ov096_022a18dc, PocketsScreen_SwitchTab)

/* func_ov096_022a192c: the tab switches of the frame; whether one happened. The close request's
 * count steps (func_0206f58c). A close request in sub state 0, 1 or 0x0a closes the menu.
 * Only in sub states 0 and 0x0a: with the touch in use the tab touched on the tab bar, with the
 * keys Y closes the menu, X switches to tab 5 and SELECT to tab 4. */
int PocketsScreen_TakeTabSwitch(PocketsScreen *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked() != 0) {
        u8 sub_state = self->base.sub_state;
        if (sub_state == 0 || sub_state == 1 || sub_state == 0x0a) {
            return PocketsScreen_SwitchTab(self, POCKETS_TAB_CLOSE);
        }
    }
    u8 sub_state = self->base.sub_state;
    if (sub_state != 0 && sub_state != 0x0a) {
        return 0;
    }
    int tab = POCKETS_TAB_NONE;
    if (StateFlags_IsClear2() != 0) {
        tab = MenuTabs_TabAtTouch();
    } else {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & POCKETS_PAD_Y) {
            tab = POCKETS_TAB_CLOSE;
        } else if (pressed & POCKETS_PAD_X) {
            tab = 5;
        } else if (pressed & POCKETS_PAD_SELECT) {
            tab = 4;
        }
    }
    return PocketsScreen_SwitchTab(self, tab);
}
CLEAN_AS(func_ov096_022a192c, PocketsScreen_TakeTabSwitch)

/* func_ov096_022a19c8 (vtable slot 0x5c, phase 4): the scene asks to be deleted. */
int PocketsScreen_RequestDelete(PocketsScreen *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov096_022a19c8, PocketsScreen_RequestDelete)

/* func_ov096_022a19d8 (vtable slot 0x58, phase 1): nothing. */
int PocketsScreen_Phase1Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov096_022a19d8, PocketsScreen_Phase1Idle)

/* func_ov096_022a19dc (vtable slot 0x54, phase 0): nothing. */
int PocketsScreen_Phase0Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov096_022a19dc, PocketsScreen_Phase0Idle)

/* Obj_ov096_022a23e8::func_ov096_022a19e0 (vtable slot 0x50, phase 2): a frame of the pockets in
 * use: the tab switches first; when none happened, the frame's start, its sub state and its
 * end. */
int PocketsScreen_RunInteractive(PocketsScreen *self)
{
    if (PocketsScreen_TakeTabSwitch(self)) {
        return 1;
    }
    PocketsScreen_BeginInteractiveFrame(self);
    PocketsScreen_RunSubState(self);
    PocketsScreen_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_022a19e0Ev, PocketsScreen_RunInteractive)

/* Obj_ov096_022a23e8::func_ov096_022a1a0c: runs the sub state through the table of member
 * functions (filled once from its constants):
 *   0     PocketsScreen_IdleByTouch            0x1d  PocketsScreen_WaitChoiceToPoint
 *   1     PocketsScreen_HoldTouchOnPlace       0x1e  PocketsScreen_CloseChoiceToAction
 *   2     PocketsScreen_HoldTouchWithChoice    0x1f  PocketsScreen_RunActionWhenIdle
 *   3     PocketsScreen_WaitPopupToOpenChoice  0x20  PocketsScreen_WaitError
 *   4     PocketsScreen_ActionChoiceByTouch    0x21  PocketsScreen_FollowButton
 *   5     PocketsScreen_DragHeldItem           0x22  PocketsScreen_WaitChoiceShown
 *   6     PocketsScreen_DragHeldLetter         0x23  PocketsScreen_CloseChoiceThenRun
 *   7     PocketsScreen_ReaderByTouch          0x24  PocketsScreen_RunChoice
 *   8     PocketsScreen_CodeChoiceByTouch      0x25  PocketsScreen_GiveToRecordSlot
 *   9     PocketsScreen_HoldBellDigit          0x26  PocketsScreen_WaitRecordBlink
 *   0x0a  PocketsScreen_IdleByKeys             0x27  PocketsScreen_WaitActorForRecord
 *   0x0b  PocketsScreen_MoveHeldItemByKeys     0x28  PocketsScreen_WaitUseRequest28
 *   0x0c  PocketsScreen_MoveHeldLetterByKeys   0x29  PocketsScreen_WaitUseRequest29
 *   0x0d  PocketsScreen_ActionChoiceByKeys     0x2a  PocketsScreen_WaitLettersObject
 *   0x0e  PocketsScreen_PickActionRow          0x2b  PocketsScreen_WaitGridObject
 *   0x0f  PocketsScreen_WaitCursorGlide        0x2c  func_ov098_022a2df4
 *   0x10  PocketsScreen_SwitchToCursorTab      0x2d  func_ov098_022a2b1c
 *   0x11  PocketsScreen_WaitCursorAnim         0x2e  func_ov098_022a2ac8
 *   0x12  PocketsScreen_PickUpOnTurn           0x2f  PocketsScreen_WaitActorState
 *   0x13  PocketsScreen_FinishPickUp           0x30  func_ov098_022a2f2c
 *   0x14  PocketsScreen_PutDownWithCursor      0x31  PocketsScreen_HandSlotItemToActor
 *   0x15  PocketsScreen_SwapWithCursor         0x32  PocketsScreen_BlinkSlot
 *   0x16  PocketsScreen_FinishSwapWithCursor   0x33  func_ov098_022a29b0
 *   0x17  PocketsScreen_ReaderByKeys           0x34  func_ov098_022a2994
 *   0x18  PocketsScreen_ReaderPressAfterAnim   0x35  func_ov098_022a28ac
 *   0x19  PocketsScreen_CodeChoiceByKeys       0x36  func_ov098_022a2884
 *   0x1a  PocketsScreen_DecideCodeRow          0x37  func_ov098_022a2818
 *   0x1b  PocketsScreen_StepHeldGlide          0x38  func_ov098_022a27f0
 *   0x1c  PocketsScreen_SettleHeld             0x39  func_ov098_022a27c0
 * (the ov098 entries are code of the overlay loaded after this one).
 * REQUIRES: the sub state is below 58; the game reads past the table for others. */
void PocketsScreen_RunSubState(PocketsScreen *self)
{
    static const MemberPointer *const sub_states[POCKETS_SUB_STATE_COUNT] = {
        &data_ov096_022a2380, &data_ov096_022a2378, &data_ov096_022a2370, &data_ov096_022a2368, &data_ov096_022a2360,
        &data_ov096_022a2358, &data_ov096_022a2350, &data_ov096_022a2348, &data_ov096_022a2340, &data_ov096_022a2338,
        &data_ov096_022a2330, &data_ov096_022a2328, &data_ov096_022a2320, &data_ov096_022a2318, &data_ov096_022a2310,
        &data_ov096_022a2308, &data_ov096_022a2300, &data_ov096_022a22f8, &data_ov096_022a22f0, &data_ov096_022a22e8,
        &data_ov096_022a22e0, &data_ov096_022a21a8, &data_ov096_022a22d0, &data_ov096_022a22c8, &data_ov096_022a22c0,
        &data_ov096_022a22b8, &data_ov096_022a22b0, &data_ov096_022a22a8, &data_ov096_022a22a0, &data_ov096_022a2298,
        &data_ov096_022a2290, &data_ov096_022a2288, &data_ov096_022a2178, &data_ov096_022a2180, &data_ov096_022a2270,
        &data_ov096_022a2268, &data_ov096_022a2260, &data_ov096_022a2258, &data_ov096_022a2250, &data_ov096_022a2248,
        &data_ov096_022a2240, &data_ov096_022a2238, &data_ov096_022a2230, &data_ov096_022a2228, &data_ov096_022a2220,
        &data_ov096_022a2218, &data_ov096_022a2210, &data_ov096_022a2208, &data_ov096_022a2390, &data_ov096_022a21f8,
        &data_ov096_022a21f0, &data_ov096_022a21e8, &data_ov096_022a21e0, &data_ov096_022a21d8, &data_ov096_022a21d0,
        &data_ov096_022a21c8, &data_ov096_022a21c0, &data_ov096_022a21b8,
    };
    MemberTable_InitOnce(&data_ov096_022a2460, data_ov096_022a25d4, sub_states, POCKETS_SUB_STATE_COUNT);
    MemberPointer_CallVoid(&data_ov096_022a25d4[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_022a1a0cEv, PocketsScreen_RunSubState)

/* Obj_ov096_022a23e8::func_ov096_022a1d98 (vtable slot 0x4c, the run phase): a frame of the
 * scene's states, between the frame's start and end, through the table of member functions
 * (filled once from its constants):
 *   0  PocketsScreen_StartSetup        6   PocketsScreen_WipeOut
 *   1  PocketsScreen_SetupWallet       7   PocketsScreen_OpenReader
 *   2  PocketsScreen_SetupWalletStep   8   PocketsScreen_WipeInReader
 *   3  PocketsScreen_StartWipeIn       9   PocketsScreen_StartWipeOutReader
 *   4  PocketsScreen_WipeIn            10  PocketsScreen_WipeOutReader
 *   5  PocketsScreen_StartWipeOut
 * REQUIRES: the state is below 11; the game reads past the table for others. */
int PocketsScreen_RunState(PocketsScreen *self)
{
    static const MemberPointer *const states[POCKETS_STATE_COUNT] = {
        &data_ov096_022a2388, &data_ov096_022a20a0, &data_ov096_022a23d8, &data_ov096_022a23d0,
        &data_ov096_022a23c8, &data_ov096_022a23c0, &data_ov096_022a23b8, &data_ov096_022a23b0,
        &data_ov096_022a23a8, &data_ov096_022a23a0, &data_ov096_022a2398,
    };
    MemberTable_InitOnce(&data_ov096_022a2464, data_ov096_022a246c, states, POCKETS_STATE_COUNT);
    PocketsScreen_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov096_022a246c[self->base.state], self);
    PocketsScreen_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov096_022a23e819func_ov096_022a1d98Ev, PocketsScreen_RunState)

/* func_ov096_022a1e8c (vtable slot 0x24): the scene's draw: the choice; while the scene is
 * drawn, the popup (through its class, slot 2), the cursor sprite (with the keys in use), the
 * held thing, the three objects of ov094's at the wipe's offset (POCKETS_FLAG_OBJECTS_DRAWN)
 * and the reader's button at the current wipe offset (POCKETS_FLAG_BUTTON_DRAWN, slot 2).
 * Answers 1. */
int PocketsScreen_Draw(PocketsScreen *self)
{
    PagedChoice_Draw(choice_of(self));
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_DRAWN) == 0) {
        return 1;
    }
    call_slot(&self->popup, 2);
    if (StateFlags_Test2() != 0) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    PocketsScreen_DrawHeld(self);
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_OBJECTS_DRAWN) != 0) {
        PocketsGrid_DrawPockets((PocketsGrid *) (void *) self->grid, 0, self->wipe_y);
        PocketsGrid_DrawSideMarks((PocketsGrid *) (void *) self->grid, 0, self->wipe_y);
        PocketsLetters_DrawPockets((PocketsLetters *) (void *) self->letters, 0, self->wipe_y);
        PocketsWallet_Draw((PocketsWallet *) (void *) self->unk_de0, self->wipe_y);
    }
    if (PocketsScreen_TestFlags(self, POCKETS_FLAG_BUTTON_DRAWN) != 0) {
        LabelSprite_SetOffset((LabelSprite *) (void *) &self->button, 0, MenuScene_WipeOffsetY(scene_of(self)));
        call_slot(&self->button, 2);
    }
    return 1;
}
CLEAN_AS(func_ov096_022a1e8c, PocketsScreen_Draw)

/* func_ov096_022a1f64 (vtable slot 0x0c): the scene closes: the parent told, the members torn
 * down and main's held bells 0. Answers 1. */
int PocketsScreen_Close(PocketsScreen *self)
{
    MenuTabs_ChildClosed((MenuTabs *) (void *) parent_of(self));
    PocketsScreen_Teardown(self);
    GroupParams_SetHeldBells(0);
    return 1;
}
CLEAN_AS(func_ov096_022a1f64, PocketsScreen_Close)

/* func_ov096_022a1f84 (vtable slot 0x00): the scene starts: its setup, state 0 and phase 1.
 * Answers 1. */
int PocketsScreen_Start(PocketsScreen *self)
{
    PocketsScreen_Setup(self);
    MenuScene_SetState(scene_of(self), 0);
    MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov096_022a1f84, PocketsScreen_Start)

/* func_ov096_022a1fa4: a new scene from the menu scenes' heap (NULL when it has no room): the
 * base, the scene's vtable and its members constructed, the words at 0x2e20 and 0x2e24
 * cleared. */
PocketsScreen *PocketsScreen_New(void)
{
    PocketsScreen *self = MenuScene_Alloc(sizeof(PocketsScreen));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov096_022a23e8;
    LayerTask_ConstructPair((LayerTaskPair *) (void *) self->unk_2e8);
    LayerTask_ConstructPair((LayerTaskPair *) (void *) self->unk_320);
    PocketsGrid_Construct((PocketsGrid *) (void *) self->grid);
    PocketsLetters_Construct((PocketsLetters *) (void *) self->letters);
    PocketsWallet_Construct((PocketsWallet *) (void *) self->unk_de0);
    Popup_Construct(&self->popup);
    Glide_Construct(&self->glide);
    Glider0_Construct(&self->cursor_sprite);
    PagedChoice_Construct(choice_of(self));
    ErrorMessage_Construct(&self->error);
    LetterView_Construct((LetterView *) (void *) self->unk_2a74);
    LabelButton0_Construct(&self->button);
    self->unk_2e20 = 0;
    self->unk_2e24 = 0;
    func_02066694(self->held_letter);
    func_02066694(self->unk_2f28);
    return self;
}
CLEAN_AS(func_ov096_022a1fa4, PocketsScreen_New)
