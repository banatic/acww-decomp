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
static_assert(offsetof(PocketsScreen, held_letter) == 0x2e28 && offsetof(PocketsScreen, unk_2f28) == 0x2f28, "tail");

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
extern int func_ov096_0229f290(PocketsScreen *self, int place); /* a place's x */
extern int func_ov096_0229f800(PocketsScreen *self, int place); /* 0x22-0x25 */
extern int func_ov096_0229f810(PocketsScreen *self, int place); /* the row of eight */
extern int func_ov096_0229f820(PocketsScreen *self, int place); /* the letters */
extern int func_ov096_0229f830(PocketsScreen *self, int place); /* the grid */
extern int func_ov096_0229f55c(PocketsScreen *self);            /* a free pocket slot, or POCKETS_NO_PLACE */
extern int func_ov096_0229f7ac(PocketsScreen *self, int place);
extern void func_ov096_0229f5ac(PocketsScreen *self, int place);
extern void func_ov096_0229f5e0(PocketsScreen *self, int place, int item, int a3);
extern void func_ov096_0229f7e0(PocketsScreen *self);
extern void func_ov096_0229f874(PocketsScreen *self, int a, int b, int c);
extern u8 *func_ov096_0229f8cc(PocketsScreen *self, int place, int slot, int item, int a4);
extern void func_ov096_0229fb9c(PocketsScreen *self);
extern u8 *func_ov096_0229fdb0(PocketsScreen *self);
extern int func_ov096_0229f548(PocketsScreen *self, int place);            /* a letter place's index */
extern u8 *func_ov096_0229f90c(PocketsScreen *self, int place, int steps); /* glide back */
extern void func_ov096_0229f47c(PocketsScreen *self, int place, void *letter);
extern int func_ov096_0229f4ac(PocketsScreen *self, int place);
extern int func_ov096_0229f650(PocketsScreen *self, int place);
extern void func_ov096_0229ff54(PocketsScreen *self);

/* The touch (main's bytes; data_021f6c58/54 as overlay_task.c reads them, data_021f6c60/5c as
 * label_button.c does) and a byte of main's set to 0 by func_020b93e8. */
extern u8 data_021f6c58, data_021f6c54, data_021f6c60, data_021f6c5c;
extern u8 data_021f6c30;

/* The current player's pockets (func_02099734 of the record): the wallet at 0xa68. */
extern int func_02099734(int record);
extern int func_02098cf8(int pockets, int with_more);
extern void func_02098aa0(int pockets, int bells, int mode);
extern void func_0206f848(int bells); /* sets data_021cfc74 */

/* The record's slots 2-5 (at 0x2408, 0x240c, 0x240a, 0x2406). */
extern u16 *func_02099710(int record);
extern u16 *func_020996e0(int record);
extern u16 *func_020996f8(int record);
extern u16 *func_02099728(int record);
extern void func_02099704(int record, u16 *item);
extern void func_020996d4(int record, u16 *item);
extern void func_020996ec(int record, u16 *item);

/* Items: bells of a bag, and two tests of main's. */
extern int func_0204c878(u16 *item);
extern int func_0204c4c0(u16 *item);
extern int func_0204c4e8(u16 *item);

/* The player's field actor (func_02096718(4)): its states and requests. */
extern int func_02095f4c(void);
extern int func_02096150(void);
extern int func_02095f58(void);
extern int func_02095b9c(u16 *item);
extern int func_02095b90(u16 *item);
extern int func_02095b84(u16 *item);
extern int func_02095b1c(u16 *item);
extern int func_02095aec(u16 *item);
extern int func_02095b64(void);

/* Letters (0x100 bytes): copy, state bits. */
extern int func_02066830(void *dst, const void *src);
extern unsigned int func_02065f08(void *letter);

/* Main's sprites and windows. */
extern void func_0208e4c0(Glider *sprite, int anim);   /* starts `anim` at its last frame */
extern void func_0208aa60(Popup *popup, int x, int y); /* words 0x3c and 0x40: an offset */

/* The objects of ov094's at 0x358 (the grid and the places 0x22-0x25), 0xdb8 (the letters)
 * and 0xde0 (the wallet's display). */
extern void func_ov094_02299cd0(void *wallet, int a1);
extern void func_ov094_02299acc(void *wallet, int value);
extern void func_ov094_02299ac4(void *wallet);
extern int func_ov094_02299a54(int item);
extern int func_ov094_02299b04(int item);
extern void func_ov094_0229a99c(void *grid, int item, int state);
extern void func_ov094_0229a6bc(void *grid, int x, int y);
extern void func_ov094_0229abb8(void *grid, Popup *popup, int index);
extern void func_ov094_0229aafc(void *grid, int index);
extern void func_ov094_0229ab0c(void *grid);
extern void func_ov094_0229ab1c(void *grid, int index);
extern void func_ov094_0229ab5c(void *grid);
extern u8 func_ov094_0229aa84(void *grid, int index);
extern u16 func_ov094_0229aaac(void *grid, int index);
extern int func_ov094_0229a69c(void *grid, int index);
extern int func_ov094_0229a8bc(void *grid, int index);
extern int func_ov094_0229ab90(void *grid, int index);
extern int func_ov094_0229b8d8(void *letters, int index); /* the letter */
extern void func_ov094_0229b890(void *letters, int index);
extern void func_ov094_0229b5e8(void *letters, int x, int y, void *letter);
extern int func_ov094_0229b9b4(void *letters, Popup *popup, int index);
extern void func_ov094_0229b938(void *letters, int index);
extern void func_ov094_0229b944(void *letters);
extern void func_ov094_0229b950(void *letters, int index);
extern void func_ov094_0229b98c(void *letters);
extern int func_ov094_0229b30c(void *letters, int index);
extern int func_ov094_0229b788(void *letters, int index);
extern int func_ov094_0229b328(void *letters, int index);
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
    func_02066688(self->held_letter);
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
    return self->held_kind == POCKETS_HELD_ITEM && self->held_state == 0 && self->item >= ITEM_RECORD_2410_FIRST &&
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
    u16 pile = PocketsScreen_PlaceItem(self, self->prev_slot);
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
    return PocketsScreen_PlaceLetter(self, self->slot);
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
                func_ov096_0229f7e0(self);
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

    PocketsScreen_HideCursorSprite(self);
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

/* func_ov096_0229cf84: the rows for the grid's `place`, by what PocketsScreen_PlaceItemState says of
 * it (0-2) and its item. */
void PocketsScreen_AddGridEntries(PocketsScreen *self, int place)
{
    if (func_0206fe54() != 0) {
        ChoiceEntries_Add(&self->entries, 0, 0);
    }
    int kind = PocketsScreen_PlaceItemState(self, place);
    u16 item = PocketsScreen_PlaceItem(self, place);
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
    int x = func_ov096_0229f290(self, self->slot);
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
    PocketsScreen_HideCursorSprite(self);
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
    self->menu_y = PocketsScreen_PlaceY(self, place);
    if (func_0206fe54()) {
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
    func_ov094_0229b1d8(self->letters);
}
CLEAN_AS(func_ov096_0229d5f4, PocketsScreen_ActionLetterSubState2a)

/* func_ov096_0229d664 (action 20): sub state 0x2b, with the grid's object, the item and 0xb0. */
void PocketsScreen_ActionGridSubState2b(PocketsScreen *self)
{
    u8 place = self->slot;
    PocketsScreen_PickUpItem(self, place);
    set_menu_place(self, place);
    MenuScene_SetSubState(scene_of(self), 0x2b);
    func_ov094_0229a47c(self->grid, self->item, self->held_state);
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
            func_ov096_0229fb9c(self);
            return;
    }

    int free_slot = func_ov096_0229f55c(self);
    if (need_slot && free_slot == POCKETS_NO_PLACE) {
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 0x0a, 0xff, 0);
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
            item = func_0204c120(PocketsScreen_Wallet(self), 0, NULL);
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
        PocketsScreen_TakeBagFromWallet(self, item);
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
    int kind = PocketsScreen_PlaceItemState(self, self->slot);
    int item = PocketsScreen_PlaceItem(self, self->slot);
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
    int item = PocketsScreen_PlaceItem(self, place);
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
    func_0208e4c0(&self->cursor_sprite, 8);
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
    self->unk_ba = self->base.sub_state;
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
    self->unk_ba = self->base.sub_state;
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
    int x = func_ov096_0229f290(self, self->cursor);
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
    if (func_ov096_0229f810(self, self->cursor)) {
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
    int bells_a = func_0204c878(&a);
    int bells_b = func_0204c878(&b);
    int bells_max = func_0204c878(&biggest);
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
    *onto = (u16) func_0204c120(sum, 1, &spare);
    *other = rest == 0 ? ITEM_NONE : (u16) func_0204c120(rest, 1, &spare);
    return 0;
}
CLEAN_AS(func_ov096_0229defc, PocketsScreen_MergeItems)

/* func_ov096_0229e0a8: the bag's bells go into the wallet; what passes 99999 comes back as the
 * smallest bag holding it (func_0204c120 rounding up, the wallet giving the difference), else
 * nothing (0xfff1). Answers that bag. */
int PocketsScreen_AddBagToWallet(PocketsScreen *self, u16 bag)
{
    unsigned int bells = (unsigned int) func_0204c878(&bag);
    unsigned int total = bells + (unsigned int) PocketsScreen_Wallet(self);
    int back = ITEM_NONE;
    if (total > WALLET_MAX) {
        unsigned int over = total - WALLET_MAX;
        int extra;
        back = func_0204c120((int) over, 1, &extra);
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
    int bells = func_0204c878(&bag);
    PocketsScreen_Wallet(self);
    PocketsScreen_SetWallet(self, PocketsScreen_Wallet(self) - bells);
}
CLEAN_AS(func_ov096_0229e0f8, PocketsScreen_TakeBagFromWallet)

/* func_ov096_0229e128: the current player's wallet set (func_02098aa0 keeps it in 0-99999),
 * then the wallet's display (the object at 0xde0) told. */
void PocketsScreen_SetWallet(PocketsScreen *self, int bells)
{
    func_02098aa0(func_02099734(func_020984e8()), bells, 0);
    func_ov094_02299cd0(self->unk_de0, 0);
}
CLEAN_AS(func_ov096_0229e128, PocketsScreen_SetWallet)

/* func_ov096_0229e158: the bells in the current player's wallet. */
int PocketsScreen_Wallet(PocketsScreen *self)
{
    (void) self;
    return func_02098cf8(func_02099734(func_020984e8()), 0);
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
        int bells = func_0204c878(&bag);
        if ((unsigned int) (bells + PocketsScreen_Wallet(self)) > WALLET_MAX) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov096_0229e170, PocketsScreen_HoldsBellBag)

/* func_ov096_0229e1ec: the held bag goes into the wallet. All of it: the scene lets go and
 * ends the action (func_ov096_0229fb9c); else the bag of what is left stays held, shown by the
 * grid's object, and glides back to its place (func_ov096_0229f90c, 4 steps). Answers 1.
 * QUIRK: the bag's bells are asked once more first, the answer unused. */
int PocketsScreen_PutBagInWallet(PocketsScreen *self)
{
    u16 bag = self->item;
    func_0204c878(&bag);
    int back = PocketsScreen_AddBagToWallet(self, self->item);
    if (back == ITEM_NONE) {
        PocketsScreen_DropHeld(self);
        func_ov096_0229fb9c(self);
    } else {
        self->item = (u16) back;
        func_ov094_0229a99c(self->grid, self->item, self->held_state);
        func_ov096_0229f90c(self, self->held_place, 4);
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
        func_0206f848(func_0204c878(&bag));
        return;
    }
    func_0206f848(0);
}
CLEAN_AS(func_ov096_0229e258, PocketsScreen_PublishHeldBells)

/* func_ov096_0229e29c: the action ends, the held thing goes back (and is let go), and when the
 * held item fits no record slot (record_slot 0) message 7. */
void PocketsScreen_RefuseRecordSlot(PocketsScreen *self)
{
    func_ov096_0229fb9c(self);
    PocketsScreen_ReturnHeld(self, 1);
    if (self->record_slot == 0) {
        func_ov096_0229f874(self, 7, 0xff, 1);
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
            return func_02095f4c();
        case 7:
        case 8:
            return func_02096150() == 0;
        default:
            return func_02095f58();
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
            return func_02095b9c(&asked) != 0;
        case 3:
            return func_02095b90(&asked) != 0;
        case 6:
            if (func_02095b90(&asked) != 0) {
                asked = ITEM_NONE;
                func_02095b84(&asked);
                return 1;
            }
            return 0;
        case 4:
            return func_02095b84(&asked) != 0;
        case 5:
            return func_02095b1c(&asked) != 0;
        case 7:
            if (func_02095aec(&asked) != 0) {
                if (CARD_IsEnabled() == 0) {
                    RtcSendPxiCommand(0x40);
                }
                return 1;
            }
            return 0;
        case 8:
            return func_02095b64() != 0;
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
    int record = func_020984e8();
    u16 value = (u16) item;
    switch (record_slot) {
        case 2:
            func_02099704(record, &value);
            if (!item_in((u16) old, ITEM_RECORD_2410_FIRST, ITEM_RECORD_2410_LAST)) {
                old = ITEM_NONE;
            }
            break;
        case 3:
            func_020996d4(record, &value);
            break;
        case 6:
            func_020996d4(record, &value);
            old = PocketsScreen_RecordSlotItem(self, 4);
            value = ITEM_NONE;
            func_020996ec(record, &value);
            break;
        case 4:
            func_020996ec(record, &value);
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
    int record = func_020984e8();
    switch (record_slot) {
        case 2:
            return *func_02099710(record);
        case 3:
            return *func_020996e0(record);
        case 4:
            return *func_020996f8(record);
        case 5:
            return *func_02099728(record);
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
        if (slot4 != ITEM_NONE && item_in(slot4, 0x13a8, 0x13c7) && func_0204c4c0(&slot4) == 0) {
            return 6;
        }
        return 3;
    }
    if (item_in(item, 0x13a8, 0x13c7)) {
        if ((u16) PocketsScreen_RecordSlotItem(self, 3) != ITEM_NONE && func_0204c4c0(&item) == 0) {
            return 0;
        }
        return 4;
    }
    if (item_in(item, 0x13c8, 0x1428)) {
        return 4;
    }
    if (func_0204c4e8(&item) != 0) {
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

/* func_ov096_0229e67c: sub state 0x25, func_ov096_0229ff54, flag 0x8000 cleared. */
void PocketsScreen_BeginSubState25(PocketsScreen *self)
{
    MenuScene_SetSubState(scene_of(self), 0x25);
    func_ov096_0229ff54(self);
    PocketsScreen_ClearFlags(self, POCKETS_FLAG_8000);
}
CLEAN_AS(func_ov096_0229e67c, PocketsScreen_BeginSubState25)

/* func_ov096_0229e6a0: the scene lets go of what it holds; main's held bells (data_021cfc74)
 * become 0. */
void PocketsScreen_DropHeld(PocketsScreen *self)
{
    self->held_kind = POCKETS_HELD_NONE;
    func_0206f848(0);
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
        func_ov096_0229fb9c(self);
        func_ov096_0229f874(self, 9, 0xff, 1);
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

/* func_ov096_0229e79c: puts the held thing down at `place` (func_ov096_0229f650 for an item,
 * func_ov096_0229f4ac for a letter); whether it was put down. */
int PocketsScreen_PutHeldAt(PocketsScreen *self, int place)
{
    switch (self->held_kind) {
        case POCKETS_HELD_ITEM:
            return func_ov096_0229f650(self, place);
        case POCKETS_HELD_LETTER:
            return func_ov096_0229f4ac(self, place);
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
            func_ov096_0229f47c(self, place, self->unk_2f28);
            break;
        case POCKETS_HELD_ITEM: {
            u16 item = self->item;
            u8 state = self->held_state;
            PocketsScreen_PickUpItemAt(self, place);
            func_ov096_0229f5e0(self, place, item, state);
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
        func_ov096_0229f5e0(self, self->held_place, item, state);
        self->unk_b9 = POCKETS_NO_PLACE;
    }
}
CLEAN_AS(func_ov096_0229e82c, PocketsScreen_ReturnHeld)

/* func_ov096_0229e898: the held thing put at `place` (a letter by func_ov096_0229f47c, an item
 * by func_ov096_0229f5e0), and let go when `drop`. */
void PocketsScreen_PlaceHeldAt(PocketsScreen *self, int place, int drop)
{
    switch (self->held_kind) {
        case POCKETS_HELD_LETTER:
            func_ov096_0229f47c(self, place, self->held_letter);
            break;
        case POCKETS_HELD_ITEM:
            func_ov096_0229f5e0(self, place, self->item, self->held_state);
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
    if (func_ov096_0229f830(self, place) || func_ov096_0229f820(self, place)) {
        PocketsScreen_PickUpItem(self, place);
    }
}
CLEAN_AS(func_ov096_0229e8e0, PocketsScreen_PickUpItemAt)

/* func_ov096_0229e90c: picks up what is at `place`: the grid's item, the letter, or at the
 * bells' place the place's item, whose bells leave the wallet. */
void PocketsScreen_PickUpAt(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        PocketsScreen_PickUpItem(self, place);
    } else if (func_ov096_0229f820(self, place)) {
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
    int index = func_ov096_0229f548(self, (int) place);
    self->held_kind = POCKETS_HELD_LETTER;
    func_02066830(self->held_letter, (void *) (uintptr_t) func_ov094_0229b8d8(self->letters, index));
    func_ov094_0229b890(self->letters, index);
}
CLEAN_AS(func_ov096_0229e95c, PocketsScreen_PickUpLetter)

/* func_ov096_0229e9a0: holds the item at `place` with its state, the place emptied
 * (func_ov096_0229f5ac), the grid's object shows it and main is told its bells. */
void PocketsScreen_PickUpItem(PocketsScreen *self, int place)
{
    self->held_kind = POCKETS_HELD_ITEM;
    self->item = PocketsScreen_PlaceItem(self, place);
    self->held_state = (u8) PocketsScreen_PlaceItemState(self, place);
    func_ov096_0229f5ac(self, place);
    func_ov094_0229a99c(self->grid, self->item, self->held_state);
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
    func_ov094_0229a99c(self->grid, self->item, self->held_state);
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
            func_ov094_0229a6bc(self->grid, self->menu_x, self->menu_y);
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
    if (func_ov096_0229f830(self, self->cursor) || func_ov096_0229f820(self, self->cursor)) {
        if (PocketsScreen_PlaceIsEmpty(self, self->cursor)) {
            Popup_ClearQueued(&self->popup);
        } else {
            self->popup_place = self->cursor;
            Popup_Queue(&self->popup);
        }
    }
    if (func_ov096_0229f810(self, self->cursor) || func_ov096_0229f800(self, self->cursor)) {
        Popup_ClearQueued(&self->popup);
    }
}
CLEAN_AS(func_ov096_0229eb14, PocketsScreen_UpdatePopup)

/* func_ov096_0229eb98: the popup put above its place (0x6d left and 0x78 up of it, 8 more up
 * when state flag 2 is set) and filled by the grid's or the letters' object. */
void PocketsScreen_PlacePopup(PocketsScreen *self)
{
    int x = func_ov096_0229f290(self, self->popup_place) - 0x6d;
    int y = PocketsScreen_PlaceY(self, self->popup_place) - 0x78;
    if (func_0206fe54() != 0) {
        y -= 8;
    }
    func_0208aa60(&self->popup, x, y);
    if (func_ov096_0229f830(self, self->popup_place)) {
        func_ov094_0229abb8(self->grid, &self->popup, func_ov096_0229f7ac(self, self->popup_place));
    } else if (func_ov096_0229f820(self, self->popup_place)) {
        func_ov094_0229b9b4(self->letters, &self->popup, func_ov096_0229f548(self, self->popup_place));
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
    if (func_ov096_0229f830(self, (int) place)) {
        func_ov094_0229aafc(self->grid, func_ov096_0229f7ac(self, (int) place));
    } else if (func_ov096_0229f820(self, (int) place)) {
        func_ov094_0229b938(self->letters, func_ov096_0229f548(self, (int) place));
    } else if (func_ov096_0229f800(self, (int) place)) {
        switch (place) {
            case POCKETS_PLACE_BELLS:
                func_ov094_0229aafc(self->grid, 0x21);
                break;
            case POCKETS_PLACE_22:
            case POCKETS_PLACE_23:
                func_ov094_02299acc(self->unk_de0, 0);
                break;
            case POCKETS_PLACE_PLAYER:
                func_ov094_02299acc(self->unk_de0, 1);
                break;
        }
    } else if (place == POCKETS_PLACE_21) {
        func_ov094_0229aafc(self->grid, 0x22);
    }
}
CLEAN_AS(func_ov096_0229ec90, PocketsScreen_HighlightPlace)

/* func_ov096_0229ed44: no place marked in the three objects. */
void PocketsScreen_ClearHighlights(PocketsScreen *self)
{
    func_ov094_0229ab0c(self->grid);
    func_ov094_0229b944(self->letters);
    func_ov094_02299ac4(self->unk_de0);
}
CLEAN_AS(func_ov096_0229ed44, PocketsScreen_ClearHighlights)

/* func_ov096_0229ed74: `place` selected in its part's object, the other part's selection
 * cleared; for a place of neither, both cleared. */
void PocketsScreen_SelectPlace(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        int index = func_ov096_0229f7ac(self, place);
        func_ov094_0229b98c(self->letters);
        func_ov094_0229ab1c(self->grid, index);
    } else if (func_ov096_0229f820(self, place)) {
        int index = func_ov096_0229f548(self, place);
        func_ov094_0229ab5c(self->grid);
        func_ov094_0229b950(self->letters, index);
    } else {
        func_ov094_0229ab5c(self->grid);
        func_ov094_0229b98c(self->letters);
    }
}
CLEAN_AS(func_ov096_0229ed74, PocketsScreen_SelectPlace)

/* func_ov096_0229edec */
void PocketsScreen_ClearSelection(PocketsScreen *self)
{
    func_ov094_0229ab5c(self->grid);
    func_ov094_0229b98c(self->letters);
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
    if (func_ov096_0229f830(self, place)) {
        return 0;
    }
    if (func_ov096_0229f820(self, place)) {
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
        if (kind == 7 || kind == 8 || func_ov094_02299a54(item) != 0) {
            return 2;
        }
        if (func_ov094_02299b04(item) != 0) {
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
        if (room < func_0204c878(&bag)) {
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
    if (func_ov096_0229f820(self, place) == 0) {
        return 0;
    }
    return func_ov094_0229b8d8(self->letters, func_ov096_0229f548(self, place));
}
CLEAN_AS(func_ov096_0229f054, PocketsScreen_PlaceLetter)

/* func_ov096_0229f088: the state of what is at `place`: the pocket slot's (by the grid's
 * object), the letter's (bits 6-7 of its byte 0xfa), else 0.
 * QUIRK: for other places func_ov096_0229f800 is asked and its answer unused. */
int PocketsScreen_PlaceItemState(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        return func_ov094_0229aa84(self->grid, func_ov096_0229f7ac(self, place));
    }
    if (func_ov096_0229f820(self, place)) {
        return func_02065f08((void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place));
    }
    func_ov096_0229f800(self, place);
    return 0;
}
CLEAN_AS(func_ov096_0229f088, PocketsScreen_PlaceItemState)

/* func_ov096_0229f0dc: the item at `place`: the grid's (by its object), the item attached to
 * the letter (nothing with no letter), `place_item` at the places 0x22-0x25, else nothing. */
u16 PocketsScreen_PlaceItem(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        return func_ov094_0229aaac(self->grid, func_ov096_0229f7ac(self, place));
    }
    if (func_ov096_0229f820(self, place)) {
        if (PocketsScreen_PlaceIsEmpty(self, place)) {
            return ITEM_NONE;
        }
        return func_02065f18((void *) (uintptr_t) PocketsScreen_PlaceLetter(self, place));
    }
    if (func_ov096_0229f800(self, place)) {
        return self->place_item;
    }
    return ITEM_NONE;
}
CLEAN_AS(func_ov096_0229f0dc, PocketsScreen_PlaceItem)

/* func_ov096_0229f150: whether `place` of the grid or the letters is empty (by its part's
 * object); other places count as empty. */
int PocketsScreen_PlaceIsEmpty(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        return func_ov094_0229a69c(self->grid, func_ov096_0229f7ac(self, place));
    }
    if (func_ov096_0229f820(self, place)) {
        return func_ov094_0229b30c(self->letters, func_ov096_0229f548(self, place));
    }
    return 1;
}
CLEAN_AS(func_ov096_0229f150, PocketsScreen_PlaceIsEmpty)

/* func_ov096_0229f1a8: what the part's object answers for `place` being taken (non-zero:
 * taken, where PocketsScreen_PlaceIsEmpty says 0); 0 for other places. */
int PocketsScreen_PlaceIsTaken(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        return func_ov094_0229a8bc(self->grid, func_ov096_0229f7ac(self, place));
    }
    if (func_ov096_0229f820(self, place)) {
        return func_ov094_0229b788(self->letters, func_ov096_0229f548(self, place));
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f1a8, PocketsScreen_PlaceIsTaken)

/* func_ov096_0229f200: the y of `place`: by the grid's or the letters' object, 8 for the row
 * of eight, by the grid's object for 0x22-0x25, 0xb0 for 0x21, else 0. */
int PocketsScreen_PlaceY(PocketsScreen *self, int place)
{
    if (func_ov096_0229f830(self, place)) {
        return func_ov094_0229ab90(self->grid, func_ov096_0229f7ac(self, place));
    }
    if (func_ov096_0229f820(self, place)) {
        return func_ov094_0229b328(self->letters, func_ov096_0229f548(self, place));
    }
    if (func_ov096_0229f810(self, place)) {
        return 8;
    }
    if (func_ov096_0229f800(self, place)) {
        return func_ov094_0229ab90(self->grid, func_ov096_0229f7ac(self, place));
    }
    if (place == POCKETS_PLACE_21) {
        return 0xb0;
    }
    return 0;
}
CLEAN_AS(func_ov096_0229f200, PocketsScreen_PlaceY)
