/* The scene of overlay 096 (vtable 0x022a23e8, include/cpp/ov096/Obj_ov096_022a23e8.h): a
 * menu scene (ov002/menu_scene.h) that shows the current player's pockets, as the evidence
 * says: a cursor walks a grid of 15 slots in 3 rows of 5 (the 15 pocket slots,
 * main/pockets.h), a list of 10 letters in 2 columns of 5 (the player's 10 letters of 0x100
 * bytes, a kind at 0xfa and an attached item at 0xfc), a row of 8 more slots and a few single
 * places, among them one for the player's bells (choices of 100, 1000 and 10000) and one for
 * the items the player record keeps at 0x2406-0x240c.
 *
 * Moving the cursor across the left or right edge wraps it to the other side (letters to the
 * right of the grid, the grid to the right of the letters), and the scene remembers which way
 * it wrapped for that move so the cursor sprite slides 256 pixels to get there.
 *
 * Picking a place opens a choice (ov002/paged_choice.h) whose rows carry an action: the action
 * is kept at 0xbb and run through a table of member functions (PocketsScreen_RunAction). The
 * scene's sub states (MenuScene_SetSubState) are run by PocketsScreen_RunSubState in phase 2,
 * its states (MenuScene_SetState: the setup, the wipes, a letter read on layers 3 and 4 by the
 * letter view at 0x2a74) by PocketsScreen_RunState in the run phase.
 *
 * The scene is a tab of the menu its parent process (ov090's) keeps: the row of eight places
 * is the tab bar, R and L go to the next and previous tab, and PocketsScreen_SwitchTab leaves
 * for another tab or closes the menu (tab 7).
 *
 * An item or a letter can be picked up from its place and held (PocketsHeldKind) until it is
 * put down, swapped or sent back to the place it came from (`held_place`). The bells' place
 * is the wallet: a bell bag put there adds its bells, one taken from it removes them. Items
 * put on the player's place go to slots of the player's record (PocketsScreen_HeldRecordSlot,
 * PocketsScreen_SwapRecordSlot). */
#ifndef CLEAN_OV096_POCKETS_SCREEN_H
#define CLEAN_OV096_POCKETS_SCREEN_H

#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/label_button.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "ov094/pockets_letters.h"
#include "types.h"

/* In `flags`. */
enum PocketsScreenFlag {
    POCKETS_FLAG_DRAWN = 0x01,         /* the scene is drawn (PocketsScreen_Draw) */
    POCKETS_FLAG_OBJECTS_DRAWN = 0x02, /* the grid, the letters and the wallet are drawn */
    POCKETS_FLAG_04 = 0x04,            /* the place touched holds nothing (PocketsScreen_TouchPlace) */
    POCKETS_FLAG_08 = 0x08,            /* cleared and tested by PocketsScreen_AddLetterEntries */
    POCKETS_FLAG_WRAPPED_LEFT = 0x10,  /* this move wrapped the cursor over the left edge */
    POCKETS_FLAG_WRAPPED_RIGHT = 0x20, /* this move wrapped it over the right edge */
    POCKETS_FLAG_40 = 0x40,            /* the held thing is not drawn */
    POCKETS_FLAG_80 = 0x80,            /* the picked letter is read once the pockets have wiped out */
    POCKETS_FLAG_BUTTON_DRAWN = 0x100, /* the letter reader's button is drawn */
    POCKETS_FLAG_200 = 0x200,
    POCKETS_FLAG_SWITCH_ON = 0x400,      /* see PocketsScreen_ApplySwitch */
    POCKETS_FLAG_SWITCH_PENDING = 0x800, /* see PocketsScreen_ApplySwitch */
    POCKETS_FLAG_1000 = 0x1000,
    POCKETS_FLAG_2000 = 0x2000, /* the held thing glides on to `unk_b9` (PocketsScreen_SettleHeld) */
    POCKETS_FLAG_4000 = 0x4000, /* a touch on the bells' place finds no place (PocketsScreen_PlaceAtTouch) */
    POCKETS_FLAG_8000 = 0x8000,
    POCKETS_FLAG_NO_ENTRIES = 0x10000,    /* the touched place of the grid offers no choice row */
    POCKETS_FLAG_EXITING = 0x20000,       /* set by PocketsScreen_ExitToParent */
    POCKETS_FLAG_FIXED_MENU = 0x40000,    /* the choice is PocketsScreen_OpenFixedMenu's */
    POCKETS_FLAG_STEPWISE_SETUP = 0x80000 /* states 0-2 of the setup take a frame each (the
                                           * parent's byte 0x98 was set, PocketsScreen_Setup) */
};

#define POCKETS_FLAGS_WRAPPED (POCKETS_FLAG_WRAPPED_LEFT | POCKETS_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`). */
enum PocketsScreenPlace {
    POCKETS_GRID_FIRST = 0x00, /* 0-14: the grid, row * 5 + column */
    POCKETS_GRID_LAST = 0x0e,
    POCKETS_LETTERS_FIRST = 0x0f, /* 15-24: the letters, 15 + row * 2 + column */
    POCKETS_LETTERS_LAST = 0x18,
    POCKETS_ROW_FIRST = 0x19, /* 25-32: a row of eight: the menu's tabs 0-7 (PocketsScreen_SwitchTab) */
    POCKETS_ROW_LAST = 0x20,
    POCKETS_PLACE_21 = 0x21, /* left of the grid's last row, when PocketsScreen_CanReachPlace21 */
    POCKETS_PLACE_22 = 0x22,
    POCKETS_PLACE_23 = 0x23,
    POCKETS_PLACE_PLAYER = 0x24, /* its choice offers the record's items at 0x240c, 0x240a, 0x2406 */
    POCKETS_PLACE_BELLS = 0x25,
    POCKETS_PLACE_27 = 0x27, /* given to PocketsScreen_OpenSlotMenu; becomes the bells' place */
    POCKETS_NO_PLACE = 0x26  /* PocketsScreen_FreePocketSlot: no free pocket slot */
};

/* What the scene holds (`held_kind`): a thing picked up from a place moves with the stylus or
 * the cursor until it is put down. */
enum PocketsHeldKind {
    POCKETS_HELD_NONE = 0,
    POCKETS_HELD_LETTER = 1, /* a copy of the letter is at `held_letter` */
    POCKETS_HELD_ITEM = 2    /* `item` and `held_state` */
};

#define POCKETS_GRID_COLUMNS 5
#define POCKETS_GRID_ROWS 3
#define POCKETS_LETTER_ROWS 5

/* Actions (`action`): the values of the choice rows, run by PocketsScreen_RunAction. */
#define POCKETS_ACTION_COUNT 34
#define POCKETS_ACTION_CANCEL 0x22 /* the value of every row added without one */

typedef struct PocketsScreen {
    MenuScene base;  /* 0x00 */
    u32 flags;       /* 0x94: PocketsScreenFlag */
    s32 wipe_y;      /* 0x98: the wipe's vertical offset, where the objects are drawn */
    s32 grab_dx;     /* 0x9c: from the touch to the held thing (PocketsScreen_FollowTouch) */
    s32 grab_dy;     /* 0xa0 */
    s32 menu_x;      /* 0xa4: where the held thing (or the menu) is drawn */
    s32 menu_y;      /* 0xa8 */
    u16 item;        /* 0xac: the held item's code */
    u16 place_item;  /* 0xae: the item code of places 0x22-0x25 (PocketsScreen_PlaceItem) */
    u8 held_state;   /* 0xb0: the held item's state (PocketsScreen_PlaceItemState) */
    u8 held_kind;    /* 0xb1: PocketsHeldKind */
    u8 touch_place;  /* 0xb2: the place touched (PocketsScreen_TouchPlace) */
    u8 popup_place;  /* 0xb3: the place the popup tells of (PocketsScreen_UpdatePopup) */
    u8 held_place;   /* 0xb4: the place the held thing goes back to; a free pocket slot when
                      * taken from the record or the wallet (PocketsScreen_FreePocketSlot) */
    u8 cursor;       /* 0xb5: PocketsScreenPlace */
    u8 slot;         /* 0xb6: the place picked */
    u8 unk_b7;       /* 0xb7 */
    u8 prev_slot;    /* 0xb8 */
    u8 unk_b9;       /* 0xb9 */
    u8 return_state; /* 0xba: the sub state to go back to (PocketsScreen_ShowError,
                      * PocketsScreen_BeginSubState15) */
    u8 action;       /* 0xbb: see POCKETS_ACTION_COUNT */
    u8 choice_row;   /* 0xbc: the choice row the cursor sprite points at */
    u8 choice_page;  /* 0xbd */
    u8 choice_code;  /* 0xbe: the code given to PagedChoice_Apply */
    u8 bell_choice;  /* 0xbf: 1, 2, 3 for 100, 1000, 10000 bells (PocketsScreen_BellAmountAtTouch) */
    u8 record_slot;  /* 0xc0: 3-5, of func_ov096_0229e4a4 */
    u8 blink;        /* 0xc1: frames left of PocketsScreen_BlinkSlot */
    u8 open_delay;   /* 0xc2: frames before a touched place's choice opens (2) */
    u8 pad_c3;
    s32 unk_c4;             /* 0xc4: func_020435fc's result */
    u8 unk_c8[0x20];        /* 0xc8 */
    u8 unk_e8[0x200];       /* 0xe8 */
    u8 unk_2e8[0x38];       /* 0x2e8: an object of main's class (PocketsScreen_UpdateObjects2e8) */
    u8 unk_320[0x38];       /* 0x320: one more (PocketsScreen_UpdateObjects2e8) */
    u8 grid[0xa60];         /* 0x358: an object of ov094's (destructor func_ov094_0229afe0) */
    PocketsLetters letters; /* 0xdb8: ov094's letters object */
    u8 unk_de0[0x1638];     /* 0xde0: an object of ov094's (destructor func_ov094_0229a2d0) */
    Popup popup;            /* 0x2418 */
    Glide glide;            /* 0x24e8 */
    Glider cursor_sprite;   /* 0x2500 */
    u8 choice[0x3e8];       /* 0x2564: a PagedChoice */
    ChoiceEntries entries;  /* 0x294c */
    u8 pad_2957;            /* 0x2957 */
    ErrorMessage error;     /* 0x2958 */
    u8 unk_2a74[0x328];     /* 0x2a74: main's letter view (constructor func_0206e388, destructor
                            * func_0206e35c): shows a letter on layers 3 and 4 */
    LabelButton button;     /* 0x2d9c: a LabelButton0 */
    u8 pad_2e14[0xc];       /* 0x2e14 */
    u32 unk_2e20;           /* 0x2e20: cleared by PocketsScreen_New */
    u32 unk_2e24;           /* 0x2e24 */
    Letter held_letter;     /* 0x2e28: the held letter's copy */
    Letter unk_2f28;        /* 0x2f28: a second letter copy (Letter_Assign) */
} PocketsScreen;

PocketsScreen *PocketsScreen_Destroy(PocketsScreen *self);
PocketsScreen *PocketsScreen_Delete(PocketsScreen *self);
void PocketsScreen_ClearFlags(PocketsScreen *self, unsigned int flags);
void PocketsScreen_SetFlags(PocketsScreen *self, unsigned int flags);
int PocketsScreen_TestFlags(PocketsScreen *self, unsigned int flags);
int PocketsScreen_CanReachPlace21(PocketsScreen *self);
void PocketsScreen_SwapRecordItem(PocketsScreen *self);
void PocketsScreen_ApplySwitch(PocketsScreen *self);
void PocketsScreen_RequestSwitchOff(PocketsScreen *self);
void PocketsScreen_RequestSwitchOn(PocketsScreen *self);
void PocketsScreen_PutPileInLetter(PocketsScreen *self);
int PocketsScreen_SlotLetter(PocketsScreen *self);
void PocketsScreen_ExitToParent(PocketsScreen *self);
void PocketsScreen_PressButton(PocketsScreen *self);
void PocketsScreen_FinishScene(PocketsScreen *self);
int PocketsScreen_MoveCursor(PocketsScreen *self, int keys, int mode);
void PocketsScreen_MoveCursorAtPlaces(PocketsScreen *self, int keys, int mode);
void PocketsScreen_MoveCursorInRow(PocketsScreen *self, int keys, int mode);
void PocketsScreen_MoveCursorInLetters(PocketsScreen *self, int keys, int mode);
void PocketsScreen_MoveCursorInGrid(PocketsScreen *self, int keys, unsigned int mode);
u8 PocketsScreen_LocalSlotIfTaken(PocketsScreen *self);
u8 *PocketsScreen_OpenChoicePage(PocketsScreen *self, int wipe);
int PocketsScreen_OpenFirstChoicePage(PocketsScreen *self);
void PocketsScreen_OpenFixedMenu(PocketsScreen *self);
void PocketsScreen_OpenSlotMenu(PocketsScreen *self, int place, int above_popup);
void PocketsScreen_AddPlayerEntries(PocketsScreen *self);
void PocketsScreen_AddBellEntries(PocketsScreen *self);
void PocketsScreen_AddLetterEntries(PocketsScreen *self, int place);
void PocketsScreen_AddGridEntries(PocketsScreen *self, int place);
int PocketsScreen_CueAction(PocketsScreen *self);
void PocketsScreen_CloseChoiceToLeave(PocketsScreen *self);
void PocketsScreen_CancelChoice(PocketsScreen *self);
void PocketsScreen_ShowChoice(PocketsScreen *self, int above_popup);
void PocketsScreen_RunAction(PocketsScreen *self);
void PocketsScreen_ActionSendMessage(PocketsScreen *self);
void PocketsScreen_ActionSendMessage0(PocketsScreen *self);
void PocketsScreen_SendMessage(PocketsScreen *self, int message);
void PocketsScreen_ActionMessageMenu(PocketsScreen *self);
int PocketsScreen_ActionSubState31(PocketsScreen *self);
void PocketsScreen_ActionFixedMenu(PocketsScreen *self);
void PocketsScreen_ActionLetterSubState2a(PocketsScreen *self);
void PocketsScreen_ActionGridSubState2b(PocketsScreen *self);
void PocketsScreen_ActionTakeRecordItem(PocketsScreen *self);
void PocketsScreen_ActionTakeBells(PocketsScreen *self);
void PocketsScreen_ActionNewLetterFromSlot(PocketsScreen *self);
void PocketsScreen_ActionNewLetterChoice(PocketsScreen *self);
int PocketsScreen_MoveToFreeLetter(PocketsScreen *self);
void PocketsScreen_ActionToFreeSlot(PocketsScreen *self);
void PocketsScreen_ActionLetter05(PocketsScreen *self);
void PocketsScreen_ActionLetterChoice(PocketsScreen *self);
void PocketsScreen_ActionUseItem(PocketsScreen *self);
int PocketsScreen_CheckUseItem(PocketsScreen *self, int item);
int PocketsScreen_CanUseItem(PocketsScreen *self, unsigned int item);
void PocketsScreen_BeginSubState15(PocketsScreen *self, u8 value);
void PocketsScreen_BeginSubState14(PocketsScreen *self, int value);
void PocketsScreen_BeginSubState12(PocketsScreen *self);
void PocketsScreen_BeginSubState11(PocketsScreen *self);
void PocketsScreen_BeginSubState10(PocketsScreen *self);
void PocketsScreen_ShowCursorFirstOfSet(PocketsScreen *self);
void PocketsScreen_PlaceCursorSprite(PocketsScreen *self);

void PocketsScreen_PointAtDefaultRow(PocketsScreen *self);
void PocketsScreen_PointAtCancelRow(PocketsScreen *self);
void PocketsScreen_GlideToRow(PocketsScreen *self);
void PocketsScreen_GlideToCursor(PocketsScreen *self);
void PocketsScreen_HideCursorSprite(PocketsScreen *self);
int PocketsScreen_CursorSpriteY(PocketsScreen *self);
int PocketsScreen_CursorSpriteX(PocketsScreen *self);
void PocketsScreen_PointAtLastRow(PocketsScreen *self);
void PocketsScreen_ShowCursorSprite(PocketsScreen *self);
int PocketsScreen_MergeItems(PocketsScreen *self, u16 *onto, int held_state, u16 *other, u8 other_state);
int PocketsScreen_AddBagToWallet(PocketsScreen *self, u16 bag);
void PocketsScreen_TakeBagFromWallet(PocketsScreen *self, u16 bag);
void PocketsScreen_SetWallet(PocketsScreen *self, int bells);
int PocketsScreen_Wallet(PocketsScreen *self);
int PocketsScreen_HoldsBellBag(PocketsScreen *self, int fits_wallet);
int PocketsScreen_PutBagInWallet(PocketsScreen *self);
void PocketsScreen_PublishHeldBells(PocketsScreen *self);
void PocketsScreen_RefuseRecordSlot(PocketsScreen *self);
int PocketsScreen_ActorReadyForSlot(PocketsScreen *self, int record_slot);
int PocketsScreen_ActorTakeSlotItem(PocketsScreen *self, unsigned int record_slot, u16 item);
int PocketsScreen_SwapRecordSlot(PocketsScreen *self, int record_slot, int item);
int PocketsScreen_RecordSlotItem(PocketsScreen *self, int record_slot);
int PocketsScreen_HeldRecordSlot(PocketsScreen *self);
void PocketsScreen_BeginSubState25(PocketsScreen *self);
void PocketsScreen_DropHeld(PocketsScreen *self);
int PocketsScreen_CanUseHeld(PocketsScreen *self);
int PocketsScreen_UseHeld(PocketsScreen *self);
int PocketsScreen_PutHeldAt(PocketsScreen *self, int place);
void PocketsScreen_SwapHeldWith(PocketsScreen *self, int place);
void PocketsScreen_ReturnHeld(PocketsScreen *self, int drop);
void PocketsScreen_PlaceHeldAt(PocketsScreen *self, int place, int drop);
void PocketsScreen_PickUpItemAt(PocketsScreen *self, int place);
void PocketsScreen_PickUpAt(PocketsScreen *self, int place);
void PocketsScreen_PickUpLetter(PocketsScreen *self, unsigned int place);
void PocketsScreen_PickUpItem(PocketsScreen *self, int place);
void PocketsScreen_HoldItem(PocketsScreen *self, u16 item, u8 state);
void PocketsScreen_FollowGlide(PocketsScreen *self);
int PocketsScreen_FollowCursorSprite(PocketsScreen *self);
void PocketsScreen_FollowTouch(PocketsScreen *self);
void PocketsScreen_DrawHeld(PocketsScreen *self);
void PocketsScreen_UpdatePopup(PocketsScreen *self);
void PocketsScreen_PlacePopup(PocketsScreen *self);
int PocketsScreen_Byte6c30AtLeast(PocketsScreen *self, int value);
int PocketsScreen_TouchMoved(PocketsScreen *self);
void PocketsScreen_HighlightPlace(PocketsScreen *self, unsigned int place);
void PocketsScreen_ClearHighlights(PocketsScreen *self);
void PocketsScreen_SelectPlace(PocketsScreen *self, int place);
void PocketsScreen_ClearSelection(PocketsScreen *self);
int PocketsScreen_CanReachBells(PocketsScreen *self, int mode);
int PocketsScreen_CanReachPlace22(PocketsScreen *self, int mode);
int PocketsScreen_CanReachPlayer(PocketsScreen *self, int mode);
int PocketsScreen_CheckReturnHeld(PocketsScreen *self, int place);
int PocketsScreen_CheckSwap(PocketsScreen *self, int place, int to);
int PocketsScreen_CheckDrop(PocketsScreen *self, int place, int item, int state);
int PocketsScreen_PlaceLetter(PocketsScreen *self, int place);
int PocketsScreen_PlaceItemState(PocketsScreen *self, int place);
u16 PocketsScreen_PlaceItem(PocketsScreen *self, int place);
int PocketsScreen_PlaceIsEmpty(PocketsScreen *self, int place);
int PocketsScreen_PlaceIsTaken(PocketsScreen *self, int place);
int PocketsScreen_PlaceY(PocketsScreen *self, int place);
int PocketsScreen_PlaceX(PocketsScreen *self, int place);
int PocketsScreen_BellAmountAtTouch(PocketsScreen *self, int x, int y);
int PocketsScreen_TouchOnBells(PocketsScreen *self, int x, int y);
int PocketsScreen_TouchOnPlayer(PocketsScreen *self, int x, int y);
int PocketsScreen_PlaceAtTouch(PocketsScreen *self, int x, int y);
int PocketsScreen_TouchOnPlace21(PocketsScreen *self, int x, int y);
void PocketsScreen_PutLetterAt(PocketsScreen *self, int place, void *letter);
int PocketsScreen_PutHeldLetterAt(PocketsScreen *self, int place);
int PocketsScreen_LetterPlaceAtTouch(PocketsScreen *self, int x, int y, int with_letter);
u8 PocketsScreen_LetterPlace(PocketsScreen *self, unsigned int index);
int PocketsScreen_LetterIndex(PocketsScreen *self, unsigned int place);
int PocketsScreen_FreePocketSlot(PocketsScreen *self);
void PocketsScreen_RemoveLetterAt(PocketsScreen *self, int place);
void PocketsScreen_EmptyPlace(PocketsScreen *self, int place);
void PocketsScreen_SetPlaceItem(PocketsScreen *self, int place, int item, int state);
int PocketsScreen_PutHeldItemAt(PocketsScreen *self, int place);
int PocketsScreen_GridPlaceAtTouch(PocketsScreen *self, int x, int y, int with_item);
unsigned int PocketsScreen_GridPlace(PocketsScreen *self, unsigned int index);
u8 PocketsScreen_GridIndex(u16 self_low, u16 place);
void PocketsScreen_CursorToSpriteColumn(PocketsScreen *self);
int PocketsScreen_IsTopPlace(PocketsScreen *self, unsigned int place);
int PocketsScreen_IsRowPlace(PocketsScreen *self, unsigned int place);
int PocketsScreen_IsLetterPlace(PocketsScreen *self, unsigned int place);
int PocketsScreen_IsGridPlace(PocketsScreen *self, unsigned int place);
void PocketsScreen_UpdateObjects2e8(PocketsScreen *self);
u8 *PocketsScreen_StartBlinkSlot(PocketsScreen *self);
void PocketsScreen_ShowError(PocketsScreen *self, int message, int return_state, unsigned int flag);
u8 *PocketsScreen_HoldAndGlide(PocketsScreen *self, int from, int to, int item, u8 state);
u8 *PocketsScreen_GlideHeldTo(PocketsScreen *self, u8 place, int steps);
void PocketsScreen_PickUpWithCursor(PocketsScreen *self, int place);
void PocketsScreen_PickUpWithTouch(PocketsScreen *self, int place);
void PocketsScreen_TouchPlace(PocketsScreen *self, int place);
void PocketsScreen_FillTouchedEntries(PocketsScreen *self);
void PocketsScreen_BeginSubState08Or19(PocketsScreen *self);
int PocketsScreen_BeginSubState19(PocketsScreen *self);
int PocketsScreen_BeginSubState08(PocketsScreen *self);
void PocketsScreen_EndAction(PocketsScreen *self);
void PocketsScreen_EndActionAtCursor(PocketsScreen *self);
void PocketsScreen_EndActionHidden(PocketsScreen *self);
void PocketsScreen_WaitUseRequest29(PocketsScreen *self);
void PocketsScreen_WaitUseRequest28(PocketsScreen *self);
void PocketsScreen_BlinkSlot(PocketsScreen *self);
u8 *PocketsScreen_HandSlotItemToActor(PocketsScreen *self);
void PocketsScreen_WaitActorState(PocketsScreen *self);
void PocketsScreen_WaitGridObject(PocketsScreen *self);
void PocketsScreen_WaitLettersObject(PocketsScreen *self);
void PocketsScreen_WaitActorForRecord(PocketsScreen *self);
void PocketsScreen_WaitRecordBlink(PocketsScreen *self);
void PocketsScreen_GiveToRecordSlot(PocketsScreen *self);
void PocketsScreen_RunChoice(PocketsScreen *self);
void PocketsScreen_CloseChoiceThenRun(PocketsScreen *self);
void PocketsScreen_WaitChoiceShown(PocketsScreen *self);
void PocketsScreen_FollowButton(PocketsScreen *self);
void PocketsScreen_WaitError(PocketsScreen *self);
void PocketsScreen_RunActionWhenIdle(PocketsScreen *self);
void PocketsScreen_CloseChoiceToAction(PocketsScreen *self);
int PocketsScreen_CloseChoice(PocketsScreen *self);
void PocketsScreen_WaitChoiceToPoint(PocketsScreen *self);
void PocketsScreen_SettleHeld(PocketsScreen *self);
void PocketsScreen_StepHeldGlide(PocketsScreen *self);

void PocketsScreen_DecideCodeRow(PocketsScreen *self);
void PocketsScreen_CodeChoiceByKeys(PocketsScreen *self);
void PocketsScreen_ReaderPressAfterAnim(PocketsScreen *self);
void PocketsScreen_ReaderByKeys(PocketsScreen *self);
void PocketsScreen_FinishSwapWithCursor(PocketsScreen *self);
void PocketsScreen_SwapWithCursor(PocketsScreen *self);
void PocketsScreen_PutDownWithCursor(PocketsScreen *self);
int PocketsScreen_FinishPickUp(PocketsScreen *self);
void PocketsScreen_PickUpOnTurn(PocketsScreen *self);
void PocketsScreen_WaitCursorAnim(PocketsScreen *self);
void PocketsScreen_SwitchToCursorTab(PocketsScreen *self);
void PocketsScreen_WaitCursorGlide(PocketsScreen *self);
void PocketsScreen_PickActionRow(PocketsScreen *self);
void PocketsScreen_ActionChoiceByKeys(PocketsScreen *self);
void PocketsScreen_MoveHeldLetterByKeys(PocketsScreen *self);
void PocketsScreen_MoveHeldItemByKeys(PocketsScreen *self);
void PocketsScreen_IdleByKeys(PocketsScreen *self);
void PocketsScreen_HoldBellDigit(PocketsScreen *self);
void PocketsScreen_CodeChoiceByTouch(PocketsScreen *self);
void PocketsScreen_ReaderByTouch(PocketsScreen *self);
void PocketsScreen_DragHeldLetter(PocketsScreen *self);
void PocketsScreen_DragHeldItem(PocketsScreen *self);
void PocketsScreen_ActionChoiceByTouch(PocketsScreen *self);
void PocketsScreen_WaitPopupToOpenChoice(PocketsScreen *self);
void PocketsScreen_HoldTouchWithChoice(PocketsScreen *self);
void PocketsScreen_HoldTouchOnPlace(PocketsScreen *self);
void PocketsScreen_IdleByTouch(PocketsScreen *self);
int PocketsScreen_StepWalletSetup(PocketsScreen *self);
void PocketsScreen_SetUpLayer6(void);
void PocketsScreen_EndFrame(PocketsScreen *self);
void PocketsScreen_BeginFrame(PocketsScreen *self);
void PocketsScreen_EndInteractiveFrame(PocketsScreen *self);
void PocketsScreen_BeginInteractiveFrame(PocketsScreen *self);
void PocketsScreen_Teardown(PocketsScreen *self);
void PocketsScreen_Setup(PocketsScreen *self);
void PocketsScreen_ClearParentByte94(PocketsScreen *self);
void PocketsScreen_WipeOutReader(PocketsScreen *self);
void PocketsScreen_StartWipeOutReader(PocketsScreen *self);
void PocketsScreen_WipeInReader(PocketsScreen *self);
void PocketsScreen_OpenReader(PocketsScreen *self);
void PocketsScreen_WipeOut(PocketsScreen *self);
void PocketsScreen_StartWipeOut(PocketsScreen *self);
void PocketsScreen_WipeIn(PocketsScreen *self);
void PocketsScreen_StartWipeIn(PocketsScreen *self);
void PocketsScreen_SetupWalletStep(PocketsScreen *self);
void PocketsScreen_SetupWallet(PocketsScreen *self);
void PocketsScreen_StartSetup(PocketsScreen *self);
int PocketsScreen_SwitchTab(PocketsScreen *self, int tab);
int PocketsScreen_TakeTabSwitch(PocketsScreen *self);
int PocketsScreen_RequestDelete(PocketsScreen *self);
int PocketsScreen_Phase1Idle(void);
int PocketsScreen_Phase0Idle(void);
int PocketsScreen_RunInteractive(PocketsScreen *self);
void PocketsScreen_RunSubState(PocketsScreen *self);
int PocketsScreen_RunState(PocketsScreen *self);
int PocketsScreen_Draw(PocketsScreen *self);
int PocketsScreen_Close(PocketsScreen *self);
int PocketsScreen_Start(PocketsScreen *self);
PocketsScreen *PocketsScreen_New(void);

#endif
