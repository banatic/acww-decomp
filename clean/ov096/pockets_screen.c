/* The pockets scene of overlay 096 (pockets_screen.h): its destructors, its flags, the cursor's
 * moves, the choices it opens and the actions they run. */
#include "pockets_screen.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/process.h"
#include "clean.h"
#include "main/group_params.h"
#include "main/player_messages.h"
#include "main/session.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(PocketsScreen, flags) == 0x94, "flags");
static_assert(offsetof(PocketsScreen, menu_x) == 0xa4 && offsetof(PocketsScreen, item) == 0xac, "place");
static_assert(offsetof(PocketsScreen, cursor) == 0xb5 && offsetof(PocketsScreen, action) == 0xbb, "cursor");
static_assert(offsetof(PocketsScreen, choice_code) == 0xbe && offsetof(PocketsScreen, unk_c4) == 0xc4, "choice");
static_assert(offsetof(PocketsScreen, grid) == 0x358 && offsetof(PocketsScreen, letters) == 0xdb8, "ov094 objects");
static_assert(offsetof(PocketsScreen, popup) == 0x2418 && offsetof(PocketsScreen, glide) == 0x24e8, "popup");
static_assert(offsetof(PocketsScreen, cursor_sprite) == 0x2500 && offsetof(PocketsScreen, choice) == 0x2564, "sprite");
static_assert(offsetof(PocketsScreen, entries) == 0x294c && offsetof(PocketsScreen, unk_2958) == 0x2958, "entries");
static_assert(offsetof(PocketsScreen, unk_2a74) == 0x2a74 && offsetof(PocketsScreen, button) == 0x2d9c, "button");
static_assert(offsetof(PocketsScreen, unk_2e28) == 0x2e28 && offsetof(PocketsScreen, unk_2f28) == 0x2f28, "tail");

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
extern void *func_0206e35c(void *object);
extern void *func_ov002_0220ba0c(void *object);
extern void *func_ov094_0229a2d0(void *object);
extern void func_ov094_0229bc30(void *object);
extern void *func_ov094_0229afe0(void *object);

/* The current player's record and its items. */
extern int func_020984e8(void);
extern u16 *func_020993a8(int record); /* the item at 0x2410 */
extern void func_0206f190(u16 *item, void *a1, void *a2, void *a3);
extern int func_0209a1e8(void); /* the first free letter, or -1 */

/* Item codes (main/item_code.h: ItemCode_PileItem, ItemCode_PileCount, ItemCode_MakePile). */
extern int func_0204bd5c(u16 *item);
extern unsigned int func_0204bd40(u16 *item);
extern int func_0204bd20(int item, int count);
extern int func_0204c120(int bells, int a1, int *a2);

/* Letters (0x100 bytes; kind at 0xfa, attached item at 0xfc). */
extern void func_020665f0(void *letter, int pile_item);
extern void func_020665b8(void *letter);
extern u8 func_02065ec0(void *letter);
extern u16 func_02065f18(void *letter);

/* Others of main's. */
extern int CARD_IsEnabled(void); /* the byte at 0x1f4 of the object at data_021c67a4 is set */
extern int func_0203ac2c(void);
extern int func_0203ac44(void);
extern int func_0206fe54(void); /* state flag 2 is set */
extern int func_0208b500(void);
extern unsigned int func_0208d12c(int object);
extern int func_020b67d4(void);
extern int func_020435fc(int slot, int item);
extern void func_0208f0c4(LabelButton *button, int anim);
extern void RtcSendPxiCommand(int command); /* func_020f1fb4(&data_021fd1bc, command) */

/* Other overlays'. */
extern void func_ov090_022993cc(void *process, int value);
extern int func_ov094_02299a90(int item);
extern void func_ov094_0229b1d8(void *letters);
extern void func_ov094_0229a47c(void *grid, int item, int value);
extern void func_ov094_0229aa58(void *grid, int value);
extern void func_ov097_022a28e4(PocketsScreen *self, int item);
extern int func_ov097_022a27c0(PocketsScreen *self);
extern int func_ov097_022a27fc(PocketsScreen *self, int item);
extern void func_ov098_022a3060(PocketsScreen *self);
extern void func_ov098_022a30a4(PocketsScreen *self, int item);
extern int func_ov098_022a31d8(PocketsScreen *self, unsigned int item);

/* The scene's own, outside these functions. */
extern int func_ov096_0229f054(PocketsScreen *self, int place); /* the letter at a place, or 0 */
extern int func_ov096_0229f088(PocketsScreen *self, int place);
extern u16 func_ov096_0229f0dc(PocketsScreen *self, int place); /* the item code at a place */
extern int func_ov096_0229f200(PocketsScreen *self, int place); /* a place's y */
extern int func_ov096_0229f290(PocketsScreen *self, int place); /* a place's x */
extern int func_ov096_0229f800(PocketsScreen *self, int place); /* 0x22-0x25 */
extern int func_ov096_0229f810(PocketsScreen *self, int place); /* the row of eight */
extern int func_ov096_0229f820(PocketsScreen *self, int place); /* the letters */
extern int func_ov096_0229f830(PocketsScreen *self, int place); /* the grid */
extern int func_ov096_0229ee10(PocketsScreen *self, int mode);
extern int func_ov096_0229ee38(PocketsScreen *self, int mode);
extern int func_ov096_0229ee50(PocketsScreen *self, int mode);
extern int func_ov096_0229e158(PocketsScreen *self); /* the player's bells */
extern int func_ov096_0229e4a4(PocketsScreen *self, int record_slot);
extern int func_ov096_0229f55c(PocketsScreen *self); /* a free pocket slot, or POCKETS_NO_PLACE */
extern int func_ov096_0229f7ac(PocketsScreen *self, int place);
extern void func_ov096_0229e82c(PocketsScreen *self, int a);
extern void func_ov096_0229e6a0(PocketsScreen *self);
extern void func_ov096_0229e67c(PocketsScreen *self);
extern void func_ov096_0229e0f8(PocketsScreen *self, int item);
extern void func_ov096_0229e95c(PocketsScreen *self, int place);
extern void func_ov096_0229e9a0(PocketsScreen *self, int place);
extern void func_ov096_0229f5ac(PocketsScreen *self, int place);
extern void func_ov096_0229f5e0(PocketsScreen *self, int place, int item, int a3);
extern void func_ov096_0229f7e0(PocketsScreen *self);
extern void func_ov096_0229f874(PocketsScreen *self, int a, int b, int c);
extern u8 *func_ov096_0229f8cc(PocketsScreen *self, int place, int slot, int item, int a4);
extern void func_ov096_0229fb9c(PocketsScreen *self);
extern u8 *func_ov096_0229fdb0(PocketsScreen *self);
extern void func_ov096_0229ddd8(PocketsScreen *self);
extern int func_ov096_0229ddfc(PocketsScreen *self); /* the cursor sprite's y */
extern int func_ov096_0229de0c(PocketsScreen *self); /* its x */
extern int func_ov096_022a18dc(PocketsScreen *self, int a);
extern void func_ov096_022a1540(PocketsScreen *self);

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
    func_02066688(self->unk_2e28);
    LabelButton0_Destroy(&self->button);
    func_0206e35c(self->unk_2a74);
    func_ov002_0220ba0c(self->unk_2958);
    PagedChoice_Destroy(choice_of(self));
    Glider0_Destroy(&self->cursor_sprite);
    Glide_Destroy(&self->glide);
    Popup_Destroy(&self->popup);
    func_ov094_0229a2d0(self->unk_de0);
    /* The ROM calls 0x0229bc30, ov094's function (ov094 is the overlay of the objects next to
     * it); the matching source of func_ov096_0229c180 names ov128's at the same address. */
    func_ov094_0229bc30(self->letters);
    func_ov094_0229afe0(self->grid);
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
    return self->unk_b1 == 2 && self->unk_b0 == 0 && self->item >= ITEM_RECORD_2410_FIRST &&
           self->item <= ITEM_RECORD_2410_LAST;
}
CLEAN_AS(func_ov096_0229c310, PocketsScreen_CanReachPlace21)

/* func_ov096_0229c348: hands the scene's item to func_0206f190 (which may store it as the
 * player record's item at 0x2410); when the record's item was in 0x11a8-0x12a7 before, it
 * becomes the scene's item. Then command 0x6b. */
void PocketsScreen_SwapRecordItem(PocketsScreen *self)
{
    u16 old = *func_020993a8(func_020984e8());
    u16 given = self->item;
    func_0206f190(&given, self->unk_320, self->unk_e8, self->unk_c8);
    if (old >= ITEM_RECORD_2410_FIRST && old <= ITEM_RECORD_2410_LAST) {
        self->item = old;
        func_ov096_0229e82c(self, 1);
    } else {
        func_ov096_0229e6a0(self);
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
            func_0203ac2c();
        }
    } else {
        if (PocketsScreen_TestFlags(self, POCKETS_FLAG_SWITCH_ON)) {
            func_0203ac44();
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
    u16 pile = func_ov096_0229f0dc(self, self->prev_slot);
    int pile_item = func_0204bd5c(&pile);
    func_020665f0((void *) (uintptr_t) letter, (u8) pile_item);
    PagedChoice_Apply(choice_of(self), (void *) (uintptr_t) letter, self->choice_code);
    GroupParams_SetPointer((u32) letter);
    func_ov096_022a18dc(self, 8);
    func_ov096_022a1540(self);
    unsigned int count = func_0204bd40(&pile);
    int left = count <= 1 ? ITEM_NONE : func_0204bd20(pile_item, (int) (count - 1));
    func_ov096_0229f5e0(self, self->prev_slot, left, 0);
}
CLEAN_AS(func_ov096_0229c454, PocketsScreen_PutPileInLetter)

/* func_ov096_0229c4dc: the letter at the place picked, or 0 when it is not a letter's. */
int PocketsScreen_SlotLetter(PocketsScreen *self)
{
    return func_ov096_0229f054(self, self->slot);
}
CLEAN_AS(func_ov096_0229c4dc, PocketsScreen_SlotLetter)

/* func_ov096_0229c4ec */
void PocketsScreen_ExitToParent(PocketsScreen *self)
{
    PocketsScreen_PressButton(self);
    func_ov090_022993cc(Process_GetParent((Process *) (void *) self), 7);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_EXITING);
}
CLEAN_AS(func_ov096_0229c4ec, PocketsScreen_ExitToParent)

/* func_ov096_0229c514: sub state 0x21, the button's animation 2, command 0x29. */
void PocketsScreen_PressButton(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), 0x21);
    func_0208f0c4(&self->button, 2);
    RtcSendPxiCommand(0x29);
}
CLEAN_AS(func_ov096_0229c514, PocketsScreen_PressButton)

/* func_ov096_0229c538 (action 3) */
void PocketsScreen_FinishScene(PocketsScreen *self)
{
    MenuScene_SetState(scene_of(self), 5);
    MenuScene_SetPhase(scene_of(self), MENU_SCENE_PHASE_1);
    PocketsScreen_SetFlags(self, POCKETS_FLAG_80);
    func_ov096_022a1540(self);
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
    if (func_ov096_0229f830(self, self->cursor)) {
        PocketsScreen_MoveCursorInGrid(self, keys, (unsigned int) mode);
    } else if (func_ov096_0229f820(self, self->cursor)) {
        PocketsScreen_MoveCursorInLetters(self, keys, mode);
    } else if (func_ov096_0229f810(self, self->cursor)) {
        PocketsScreen_MoveCursorInRow(self, keys, mode);
    } else if (func_ov096_0229f800(self, self->cursor)) {
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
            if (func_ov096_0229ee10(self, mode)) {
                self->cursor = POCKETS_PLACE_BELLS;
            } else {
                PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
                self->cursor = 0x10;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor = 0x0f;
        } else if (KeyRepeat_HasUp(keys)) {
            if (mode == 0) {
                func_ov096_0229f7e0(self);
                Glider_TurnToSetC(&self->cursor_sprite);
            }
        } else if (KeyRepeat_HasDown(keys)) {
            self->cursor = func_ov096_0229ee38(self, mode) ? POCKETS_PLACE_22 : 0x04;
        }
    } else if (place == POCKETS_PLACE_22 || place == POCKETS_PLACE_23) {
        if (KeyRepeat_HasLeft(keys)) {
            if (func_ov096_0229ee10(self, mode)) {
                self->cursor = POCKETS_PLACE_BELLS;
            } else {
                PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_LEFT);
                self->cursor = 0x12;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            self->cursor = 0x11;
        } else if (KeyRepeat_HasUp(keys)) {
            if (func_ov096_0229ee50(self, mode)) {
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
            if (func_ov096_0229ee38(self, mode)) {
                self->cursor = POCKETS_PLACE_22;
            } else if (func_ov096_0229ee50(self, mode)) {
                self->cursor = POCKETS_PLACE_PLAYER;
            } else {
                self->cursor = 0x11;
            }
        } else if (KeyRepeat_HasUp(keys)) {
            if (mode == 0) {
                func_ov096_0229f7e0(self);
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

/* From the letters' rows 0 and 1 to the places 0x22-0x25, as func_ov096_0229ee38 and
 * func_ov096_0229ee50 (both asked) allow; whether either did.
 * QUIRK: "both" is the bitwise and of their results, as in the game. */
static int letters_to_places(PocketsScreen *self, int row, int mode)
{
    int to_22 = func_ov096_0229ee38(self, mode);
    int to_player = func_ov096_0229ee50(self, mode);
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
 * mode is 0 calling func_ov096_0229f7e0 and turning the cursor sprite; not after a wrap.
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
                self->cursor = func_ov096_0229ee10(self, mode) != 0 ? POCKETS_PLACE_BELLS : 0x04;
            }
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (column == 0) {
            self->cursor++;
        } else if (mode != 2) {
            PocketsScreen_SetFlags(self, POCKETS_FLAG_WRAPPED_RIGHT);
            if (row < 2) {
                if (func_ov096_0229ee10(self, mode) != 0) {
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

    if (!func_ov096_0229f820(self, self->cursor) || PocketsScreen_TestFlags(self, POCKETS_FLAGS_WRAPPED)) {
        return;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= 2;
        } else if (mode == 0) {
            func_ov096_0229f7e0(self);
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

    if (!func_ov096_0229f830(self, self->cursor) || PocketsScreen_TestFlags(self, POCKETS_FLAGS_WRAPPED)) {
        return;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (row > 0) {
            self->cursor -= POCKETS_GRID_COLUMNS;
            return;
        }
        if (column <= 2 && func_ov096_0229ee10(self, (int) mode) != 0) {
            self->cursor = POCKETS_PLACE_BELLS;
            return;
        }
        if (func_ov096_0229ee38(self, (int) mode) != 0) {
            self->cursor = POCKETS_PLACE_22;
            return;
        }
        if (func_ov096_0229ee50(self, (int) mode) != 0) {
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
    func_ov096_0229ddd8(self);
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

    if (func_ov096_0229f830(self, place)) {
        PocketsScreen_AddGridEntries(self, place);
    } else if (func_ov096_0229f820(self, place)) {
        PocketsScreen_AddLetterEntries(self, place);
    } else if (place == POCKETS_PLACE_BELLS) {
        PocketsScreen_AddBellEntries(self);
    } else if (place == POCKETS_PLACE_PLAYER) {
        PocketsScreen_AddPlayerEntries(self);
    } else if (place != POCKETS_PLACE_27) {
        return;
    }

    if (ChoiceEntries_Count(&self->entries) == 0) {
        if (func_ov096_0229f830(self, place) || func_ov096_0229f820(self, place)) {
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

    func_ov096_0229ddd8(self);
    if (above_popup == 0) {
        Popup_Hide(&self->popup, 1);
    }
    PocketsScreen_ShowChoice(self, above_popup);
    if (!func_ov096_0229f830(self, place) && place != POCKETS_PLACE_PLAYER) {
        PocketsScreen_RequestSwitchOff(self);
    }
}
CLEAN_AS(func_ov096_0229cc74, PocketsScreen_OpenSlotMenu)

/* func_ov096_0229cd8c: a row for each of the record's items 5, 4 and 3 that is not nothing
 * (texts 0x75-0x77, actions 0x11-0x0f). */
void PocketsScreen_AddPlayerEntries(PocketsScreen *self)
{
    if (func_ov096_0229e4a4(self, 5) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x75, 0x11);
    }
    if (func_ov096_0229e4a4(self, 4) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x76, 0x10);
    }
    if (func_ov096_0229e4a4(self, 3) != ITEM_NONE) {
        ChoiceEntries_Add(&self->entries, 0x77, 0x0f);
    }
}
CLEAN_AS(func_ov096_0229cd8c, PocketsScreen_AddPlayerEntries)

/* func_ov096_0229cdec: the amounts the player's bells allow (texts 0x6e-0x71, actions
 * 0x0b-0x0e: all of them, 100, 1000, 10000). */
void PocketsScreen_AddBellEntries(PocketsScreen *self)
{
    int bells = func_ov096_0229e158(self);
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
    int letter = func_ov096_0229f054(self, place);
    void *letter_ptr = (void *) (uintptr_t) letter;
    if (func_0206fe54() != 0) {
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
                func_ov098_022a3060(self);
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

/* func_ov096_0229cf84: the rows for the grid's `place`, by what func_ov096_0229f088 says of
 * it (0-2) and its item. */
void PocketsScreen_AddGridEntries(PocketsScreen *self, int place)
{
    if (func_0206fe54() != 0) {
        ChoiceEntries_Add(&self->entries, 0, 0);
    }
    int kind = func_ov096_0229f088(self, place);
    u16 item = func_ov096_0229f0dc(self, place);
    if (kind == 0 && item == ITEM_156C) {
        if (func_0208d12c(func_0208b500()) != 0) {
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
                func_ov098_022a30a4(self, item);
            } else if (func_020b67d4() != 0) {
                func_ov097_022a28e4(self, item);
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
            if (func_ov094_02299a90(item) == 0) {
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
    func_ov096_0229ddd8(self);
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
    int x = func_ov096_0229f290(self, self->slot);
    int y = func_ov096_0229f200(self, self->slot);
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
 * 0, 0x0f-0x11, 0x1a or the cancel; the cancel ends with func_ov096_0229fb9c, any other action
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
        func_ov096_0229fb9c(self);
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
    func_ov096_0229fb9c(self);
}
CLEAN_AS(func_ov096_0229d4d4, PocketsScreen_ActionSendMessage)

/* func_ov096_0229d4f0 (action 28) */
void PocketsScreen_ActionSendMessage0(PocketsScreen *self)
{
    PocketsScreen_SendMessage(self, 0);
    func_ov096_0229fb9c(self);
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
            if (is_zero != func_0208d12c(func_0208b500())) {
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
    func_ov096_0229ddd8(self);
    PocketsScreen_ShowChoice(self, 0);
}
CLEAN_AS(func_ov096_0229d570, PocketsScreen_ActionMessageMenu)

/* func_ov096_0229d5d4 (action 26) */
int PocketsScreen_ActionSubState31(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), 0x31);
    return (int) (uintptr_t) func_ov096_0229fdb0(self);
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
    self->menu_x = func_ov096_0229f290(self, place);
    self->menu_y = func_ov096_0229f200(self, place);
    if (func_0206fe54()) {
        self->menu_x -= 2;
        self->menu_y -= 2;
    }
}

/* func_ov096_0229d5f4 (action 9): sub state 0x2a, with the letters' object. */
void PocketsScreen_ActionLetterSubState2a(PocketsScreen *self)
{
    u8 place = self->slot;
    func_ov096_0229e95c(self, place);
    set_menu_place(self, place);
    MenuScene_SetSubState(scene_of(self), 0x2a);
    func_ov094_0229b1d8(self->letters);
}
CLEAN_AS(func_ov096_0229d5f4, PocketsScreen_ActionLetterSubState2a)

/* func_ov096_0229d664 (action 20): sub state 0x2b, with the grid's object, the item and 0xb0. */
void PocketsScreen_ActionGridSubState2b(PocketsScreen *self)
{
    u8 place = self->slot;
    func_ov096_0229e9a0(self, place);
    set_menu_place(self, place);
    MenuScene_SetSubState(scene_of(self), 0x2b);
    func_ov094_0229a47c(self->grid, self->item, self->unk_b0);
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
            item = (u16) func_ov096_0229e4a4(self, 4);
            if (item >= ITEM_SLOT4_FIRST && item <= ITEM_SLOT4_LAST) {
                need_slot = 0;
            }
            break;
        case 0x11:
            self->record_slot = 5;
            item = (u16) func_ov096_0229e4a4(self, 5);
            if (item >= ITEM_SLOT5_FIRST && item <= ITEM_SLOT5_LAST) {
                need_slot = 0;
            }
            break;
        default:
            func_ov096_0229fb9c(self);
            return;
    }

    int free_slot = func_ov096_0229f55c(self);
    if (need_slot && free_slot == POCKETS_NO_PLACE) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0x0a, 0xff, 0);
        RtcSendPxiCommand(0x73);
    } else {
        self->free_slot = (u8) free_slot;
        func_ov096_0229e6a0(self);
        self->item = ITEM_NONE;
        func_ov096_0229e67c(self);
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
            item = func_0204c120(func_ov096_0229e158(self), 0, NULL);
            break;
        case 0x0c:
            item = func_0204c120(100, 0, NULL);
            break;
        case 0x0d:
            item = func_0204c120(1000, 0, NULL);
            break;
        case 0x0e:
            item = func_0204c120(10000, 0, NULL);
            break;
    }
    int free_slot = func_ov096_0229f55c(self);
    if (free_slot == POCKETS_NO_PLACE) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0x0c, 0xff, 1);
    } else {
        func_ov096_0229e0f8(self, item);
        func_ov096_0229f8cc(self, POCKETS_PLACE_BELLS, free_slot, item, 0);
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
        func_ov096_0229f5ac(self, self->prev_slot);
        func_ov096_022a18dc(self, 8);
        func_ov096_022a1540(self);
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
    int letter = func_0209a1e8();
    if (letter == -1) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 2, 0xff, 1);
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
    int free_slot = func_ov096_0229f55c(self);
    if (free_slot == POCKETS_NO_PLACE) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0x0b, 0xff, 1);
        return;
    }
    int kind = func_ov096_0229f088(self, self->slot);
    int item = func_ov096_0229f0dc(self, self->slot);
    func_ov096_0229f5ac(self, self->slot);
    func_ov096_0229f8cc(self, self->slot, free_slot, item, kind);
}
CLEAN_AS(func_ov096_0229d93c, PocketsScreen_ActionToFreeSlot)

/* func_ov096_0229d9a0 (action 5) */
void PocketsScreen_ActionLetter05(PocketsScreen *self)
{
    GroupParams_SetC50((char) self->slot);
    GroupParams_SetPointer((u32) PocketsScreen_SlotLetter(self));
    func_ov096_022a18dc(self, 8);
    func_ov096_022a1540(self);
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
    int item = func_ov096_0229f0dc(self, place);
    if (PocketsScreen_CanUseItem(self, (unsigned int) item) == 0) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 9, 0xff, 1);
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
        func_ov094_0229aa58(self->grid, func_ov096_0229f7ac(self, place));
        func_ov096_0229fb9c(self);
    }
}
CLEAN_AS(func_ov096_0229d9f0, PocketsScreen_ActionUseItem)

/* func_ov096_0229da6c: the ov098 way asks func_020435fc (with this system's session slot): -1
 * ends the action with message 3 and command 0x73 and answers 0, else 2. The ov097 way, when
 * func_020b67d4 allows it, answers func_ov097_022a27fc; else 0. */
int PocketsScreen_CheckUseItem(PocketsScreen *self, int item)
{
    if (data_020e54a8 == 0) {
        self->unk_c4 = func_020435fc(data_020ccf94->local_slot, item);
        if (self->unk_c4 == -1) {
            func_ov096_0229fb9c(self);
            func_ov096_0229f874(self, 3, 0xff, 0);
            RtcSendPxiCommand(0x73);
            return 0;
        }
        return 2;
    }
    if (func_020b67d4() != 0) {
        return func_ov097_022a27fc(self, item);
    }
    return 0;
}
CLEAN_AS(func_ov096_0229da6c, PocketsScreen_CheckUseItem)

/* func_ov096_0229daec: by func_ov098_022a31d8 the ov098 way, by func_ov097_022a27c0 the ov097
 * way when func_020b67d4 allows it, else no. */
int PocketsScreen_CanUseItem(PocketsScreen *self, unsigned int item)
{
    if (data_020e54a8 == 0) {
        return func_ov098_022a31d8(self, item);
    }
    if (func_020b67d4() != 0) {
        return func_ov097_022a27c0(self) != 0;
    }
    return 0;
}
CLEAN_AS(func_ov096_0229daec, PocketsScreen_CanUseItem)

/* func_ov096_0229db30: the popup hidden, the sub state kept at 0xba, `value` at 0xb7, the
 * cursor sprite's animation 6, sub state 0x15. */
void PocketsScreen_BeginSubState15(PocketsScreen *self, u8 value)
{
    Popup_Hide(&self->popup, 1);
    self->unk_ba = self->base.sub_state;
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

/* func_ov096_0229dc48: the cursor sprite put at the cursor (func_ov096_0229de0c,
 * func_ov096_0229ddfc), animation 1. */
void PocketsScreen_PlaceCursorSprite(PocketsScreen *self)
{
    int x = func_ov096_0229de0c(self);
    int y = func_ov096_0229ddfc(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
}
CLEAN_AS(func_ov096_0229dc48, PocketsScreen_PlaceCursorSprite)
