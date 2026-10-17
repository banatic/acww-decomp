/* The scene of overlay 110 (vtable 0x0229ecb8, include/cpp/ov110/Obj_ov110_0229ecb8.h; constructor
 * PublicBox_New, 0x292c bytes): a menu scene (ov002/menu_scene.h) that overlay 92's dispatcher
 * opens as overlay group 0x2c for GroupParams' modes 0x1f and 0x20 (ov092/menu_dispatch.c). It is
 * the twin of overlay 100's scene (ov100/pockets_box.h, modes 0x1d and 0x1e, background
 * "b_itm_bg_tra1"): the same code over a layout of its own, with "menu/inventory/b_itm_bg_tra2.bsc"
 * as its background and a single end place beside the box instead of two.
 *
 * The box is a list of 15 item codes (`box`) shown above the current player's 15 pocket slots,
 * both in ov094's grid object (pockets_grid.h; slots 0-14 the pockets, 15-29 the box). In mode
 * 0x1f the box starts as the town's list A and in mode 0x20 as list B (main/town_item_lists.h: list
 * A gets a few random items each day and an item a snowman leaves, list B the items villagers
 * throw away, emptied on Mondays and Thursdays); the art each mode loads says what they are:
 * "lost.bch" for mode 0x1f (the lost and found) and "garb.bch" for mode 0x20 (the recycle bin).
 * In mode 0x1f every pocket slot is locked, so items can only be taken out; at the end the items
 * taken go to Pockets_SetList and the box is written back to its list and sent to the linked
 * consoles as player message 3 or 4 (main/player_messages.h). The code also keeps overlay 100's
 * cases for modes 0x1d and 0x1e (Nook's "tanu.bch" and the Able Sisters' "kinu.bch"), which the
 * dispatcher does not open here.
 *
 * The cursor walks the pockets (3 rows of 5), the box (3 rows of 5) and the end place right of
 * the box (PUBLIC_BOX_DONE). Items are picked up from a slot and put down on, or swapped with,
 * another, by keys or by touch; a pocket slot whose item may not move is locked
 * (PublicBox_LockSlots). The scene ends by the end place, START or B, or when the menu is asked
 * to close in mode 0x20 (PublicBox_Finish). */
#ifndef CLEAN_OV110_PUBLIC_BOX_H
#define CLEAN_OV110_PUBLIC_BOX_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"
#include "types.h"

/* In `flags`. */
enum PublicBoxFlag {
    PUBLIC_BOX_FLAG_DRAWN = 0x01,         /* the scene is drawn (PublicBox_Draw) */
    PUBLIC_BOX_FLAG_POCKETS_DRAWN = 0x02, /* the pockets, their letters and the wallet are drawn
                                             * at `pockets_y` */
    PUBLIC_BOX_FLAG_TOUCHED_FREE = 0x04,  /* the place touched is not locked (PublicBox_TouchPlace) */
    PUBLIC_BOX_FLAG_SENT = 0x08,          /* the box was sent to the other consoles
                                             * (PublicBox_SendBox) */
    PUBLIC_BOX_FLAG_WRAPPED_LEFT = 0x10,  /* this move wrapped the cursor over the left edge */
    PUBLIC_BOX_FLAG_WRAPPED_RIGHT = 0x20, /* this move wrapped it over the right edge */
    PUBLIC_BOX_FLAG_HELD_HIDDEN = 0x40,   /* the held item is not drawn (a swap is under way) */
    PUBLIC_BOX_FLAG_BOX_DRAWN = 0x80,     /* the box is drawn at `box_y` */
    PUBLIC_BOX_FLAG_SPRITE_SET = 0x100,   /* the cursor sprite's set changed; it is updated by
                                             * PublicBox_GlideToCursor */
    PUBLIC_BOX_FLAG_STARTED_EMPTY = 0x200 /* the box started empty (modes 0x1d and 0x1e) */
};

#define PUBLIC_BOX_FLAGS_WRAPPED (PUBLIC_BOX_FLAG_WRAPPED_LEFT | PUBLIC_BOX_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `target`, ...), which are also the grid object's slots
 * for the first 30. */
enum PublicBoxPlace {
    PUBLIC_BOX_POCKETS_FIRST = 0x00, /* 0-14: the pocket slots, row * 5 + column */
    PUBLIC_BOX_POCKETS_LAST = 0x0e,
    PUBLIC_BOX_BOX_FIRST = 0x0f, /* 15-29: the box, 15 + row * 5 + column */
    PUBLIC_BOX_BOX_LAST = 0x1d,
    PUBLIC_BOX_DONE = 0x1e,    /* right of the box: ends the scene (PublicBox_PressButton) */
    PUBLIC_BOX_NO_PLACE = 0x1f /* also the touch's answer when no place is under it */
};

/* What is held (`held_kind`). */
enum PublicBoxHeldKind {
    PUBLIC_BOX_HELD_NONE = 0,
    PUBLIC_BOX_HELD_ITEM = 1 /* `item` and `held_state` */
};

/* GroupParams_Mode's values the scene knows (PublicBox_Setup, PublicBox_Finish). */
enum PublicBoxMode {
    PUBLIC_BOX_MODE_1D = 0x1d,     /* the box starts empty (overlay 100's) */
    PUBLIC_BOX_MODE_1E = 0x1e,     /* the same, with another rule for locked slots */
    PUBLIC_BOX_MODE_LOST = 0x1f,   /* the box is list A, the lost and found */
    PUBLIC_BOX_MODE_RECYCLE = 0x20 /* the box is list B, the recycle bin */
};

/* The values of the choice rows (`action`), run by PublicBox_RunAction. */
enum PublicBoxAction {
    PUBLIC_BOX_ACTION_PICK_UP = 0, /* PublicBox_StartPickUp */
    PUBLIC_BOX_ACTION_CLOSE = 1    /* any other: PublicBox_EndAction */
};

/* The states, run from the table of PublicBox_RunState (MenuScene_SetState). */
enum PublicBoxState {
    PUBLIC_BOX_STATE_START_SETUP = 0,      /* PublicBox_StartSetup */
    PUBLIC_BOX_STATE_START_WIPE_IN = 1,    /* PublicBox_StartWipeIn */
    PUBLIC_BOX_STATE_POCKETS_WIPE_IN = 2,  /* PublicBox_PocketsWipeIn */
    PUBLIC_BOX_STATE_BOX_WIPE_IN = 3,      /* PublicBox_BoxWipeIn */
    PUBLIC_BOX_STATE_START_WIPE_OUT = 4,   /* PublicBox_StartWipeOut */
    PUBLIC_BOX_STATE_BOX_WIPE_OUT = 5,     /* PublicBox_BoxWipeOut */
    PUBLIC_BOX_STATE_POCKETS_WIPE_OUT = 6, /* PublicBox_PocketsWipeOut */
    PUBLIC_BOX_STATES = 7
};

/* The sub states, run from the table of PublicBox_RunSubState (MenuScene_SetSubState), named by
 * what their handler does. */
enum PublicBoxSubState {
    PUBLIC_BOX_SUB_TOUCH_IDLE = 0x00,     /* PublicBox_IdleByTouch */
    PUBLIC_BOX_SUB_TOUCH_HOLD = 0x01,     /* PublicBox_HoldTouchOnPlace */
    PUBLIC_BOX_SUB_TOUCH_CHOICE = 0x02,   /* PublicBox_WatchChoiceTouch */
    PUBLIC_BOX_SUB_DRAG = 0x03,           /* PublicBox_DragHeld */
    PUBLIC_BOX_SUB_BROWSE = 0x04,         /* PublicBox_BrowseByKeys */
    PUBLIC_BOX_SUB_HOLD = 0x05,           /* PublicBox_MoveHeldByKeys */
    PUBLIC_BOX_SUB_CHOICE_BY_KEYS = 0x06, /* PublicBox_ChooseByKeys */
    PUBLIC_BOX_SUB_CHOICE_PICK = 0x07,    /* PublicBox_PickChoiceRow */
    PUBLIC_BOX_SUB_SPRITE_MOVE = 0x08,    /* PublicBox_WaitCursorSprite */
    PUBLIC_BOX_SUB_BUTTON_PRESS = 0x09,   /* PublicBox_PressButton */
    PUBLIC_BOX_SUB_BUTTON_END = 0x0a,     /* PublicBox_FinishButtonPress */
    PUBLIC_BOX_SUB_PICK_UP = 0x0b,        /* PublicBox_PickUpAtCursor */
    PUBLIC_BOX_SUB_PICK_UP_END = 0x0c,    /* PublicBox_FinishPickUp */
    PUBLIC_BOX_SUB_PUT_DOWN = 0x0d,       /* PublicBox_PutDown */
    PUBLIC_BOX_SUB_SWAP = 0x0e,           /* PublicBox_Swap */
    PUBLIC_BOX_SUB_SWAP_END = 0x0f,       /* PublicBox_FinishSwap */
    PUBLIC_BOX_SUB_HELD_GLIDE = 0x10,     /* PublicBox_StepHeldGlide */
    PUBLIC_BOX_SUB_CHOICE_OPEN = 0x11,    /* PublicBox_WaitChoiceShown */
    PUBLIC_BOX_SUB_CHOICE_CLOSE = 0x12,   /* PublicBox_CloseChoice */
    PUBLIC_BOX_SUB_CHOICE_RUN = 0x13,     /* PublicBox_RunActionWhenIdle */
    PUBLIC_BOX_SUB_ERROR = 0x14,          /* PublicBox_WaitError */
    PUBLIC_BOX_SUB_CLOSED = 0x15,         /* PublicBox_WaitClosed */
    PUBLIC_BOX_SUB_STATES = 0x16
};

/* The phases MenuScene_Update runs (as ov092/menu_dispatch.h has them): 0 the base's wait
 * (vtable slot 0x48), 1 the states (0x4c), 2 the interactive frame (0x50), 3 and 4 nothing (0x54,
 * 0x58), 5 the end (0x5c). */
enum PublicBoxPhase {
    PUBLIC_BOX_PHASE_WAIT = 0,
    PUBLIC_BOX_PHASE_STATES = 1,      /* PublicBox_RunState */
    PUBLIC_BOX_PHASE_INTERACTIVE = 2, /* PublicBox_RunInteractive */
    PUBLIC_BOX_PHASE_END = 5          /* PublicBox_End */
};

#define PUBLIC_BOX_COLUMNS 5
#define PUBLIC_BOX_ROWS 3
#define PUBLIC_BOX_SLOTS 15
#define PUBLIC_BOX_LABELS 2

typedef struct PublicBox {
    MenuScene base;                      /* 0x00 */
    u32 flags;                           /* 0x94: PublicBoxFlag */
    s32 pockets_y;                       /* 0x98: the wipe's y the pockets are drawn at */
    s32 box_y;                           /* 0x9c: the wipe's y the box is drawn at */
    s32 grab_dx;                         /* 0xa0: from the touch to the held item */
    s32 grab_dy;                         /* 0xa4 */
    s32 held_x;                          /* 0xa8: where the held item is drawn */
    s32 held_y;                          /* 0xac */
    u16 box[PUBLIC_BOX_SLOTS];           /* 0xb0: the box's item codes */
    u16 box_start[PUBLIC_BOX_SLOTS];     /* 0xce: the box as the scene started */
    u16 item;                            /* 0xec: the held item's code */
    s16 sent_frame;                      /* 0xee: the session's frame the box was sent in */
    u8 held_state;                       /* 0xf0: the held item's state (PocketsGrid_ItemState) */
    u8 held_kind;                        /* 0xf1: PublicBoxHeldKind */
    u8 touch_place;                      /* 0xf2: the place touched (PublicBox_TouchPlace) */
    u8 popup_place;                      /* 0xf3: the place the popup tells of */
    u8 held_place;                       /* 0xf4: the place the held item came from, or glides to */
    u8 cursor;                           /* 0xf5: PublicBoxPlace */
    u8 unk_f6;                           /* 0xf6 */
    u8 target;                           /* 0xf7: the place the held item is put down on or swapped at */
    u8 return_state;                     /* 0xf8: the sub state to go back to */
    u8 action;                           /* 0xf9: PublicBoxAction, the value of the choice row picked */
    u8 choice_row;                       /* 0xfa: the choice row the cursor sprite points at */
    u8 label_count;                      /* 0xfb: the labels in use */
    u8 close_delay;                      /* 0xfc: frames before the ended scene wipes out */
    u8 pad_fd[3];                        /* 0xfd */
    LayerTaskPair task;                  /* 0x100: a layer load task (ended each frame) */
    PocketsGrid grid;                    /* 0x138 */
    PocketsLetters letters;              /* 0xb98 */
    PocketsWallet wallet;                /* 0xbc0 */
    Popup popup;                         /* 0x21f8 */
    Glide glide;                         /* 0x22c8: the held item's glide to a place */
    Glider cursor_sprite;                /* 0x22e0: a Glider0 */
    u8 choice[0x3e8];                    /* 0x2344: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;               /* 0x272c */
    u8 pad_2737;                         /* 0x2737 */
    ErrorMessage error;                  /* 0x2738 */
    TextLabel labels[PUBLIC_BOX_LABELS]; /* 0x2854: the end place's label (PublicBox_NextLabel) */
} PublicBox;

PublicBox *PublicBox_Destroy(PublicBox *self);
PublicBox *PublicBox_Delete(PublicBox *self);
void PublicBox_ClearFlags(PublicBox *self, unsigned int flags);
void PublicBox_SetFlags(PublicBox *self, unsigned int flags);
int PublicBox_TestFlags(PublicBox *self, int flags);
int PublicBox_CanLeave(PublicBox *self);
void PublicBox_SendBox(PublicBox *self, u8 type);
int PublicBox_Compact(PublicBox *self, u16 *items);
void PublicBox_Finish(PublicBox *self, int with_delay);
void PublicBox_ShowDoneLabel(PublicBox *self, int lit);
TextLabel *PublicBox_NextLabel(PublicBox *self);
void PublicBox_CloseLabels(PublicBox *self);
int PublicBox_MoveCursor(PublicBox *self, int keys, int wrap_in_row);
void PublicBox_MoveCursorAtButton(PublicBox *self, int keys);
void PublicBox_MoveCursorInBox(PublicBox *self, int keys, int wrap_in_row);
void PublicBox_MoveCursorInPockets(PublicBox *self, int keys, int wrap_in_row);
void PublicBox_CancelChoice(PublicBox *self);
void PublicBox_RunAction(PublicBox *self);
void PublicBox_StartSwap(PublicBox *self, u8 place);
void PublicBox_StartPutDown(PublicBox *self, u8 place);
void PublicBox_StartPickUp(PublicBox *self);
void PublicBox_BeginButtonEnd(PublicBox *self);
void PublicBox_BeginButtonPress(PublicBox *self);
void PublicBox_ShowCursorFirstOfSet(PublicBox *self);
void PublicBox_PlaceCursorSprite(PublicBox *self);
void PublicBox_PointAtFirstRow(PublicBox *self);
void PublicBox_PointAtLastRow(PublicBox *self);
void PublicBox_GlideToRow(PublicBox *self);
void PublicBox_GlideToCursor(PublicBox *self);
void PublicBox_HideCursorSprite(PublicBox *self);
int PublicBox_CursorSpriteY(PublicBox *self);
int PublicBox_CursorSpriteX(PublicBox *self);
void PublicBox_ShowCursorSprite(PublicBox *self);
void PublicBox_SwapHeldWith(PublicBox *self, int place);
int PublicBox_PutHeldAt(PublicBox *self, int place);
void PublicBox_PickUpItem(PublicBox *self, int place);
void PublicBox_FollowGlide(PublicBox *self);
void PublicBox_FollowCursorSprite(PublicBox *self);
void PublicBox_FollowTouch(PublicBox *self);
void PublicBox_DrawHeld(PublicBox *self);
void PublicBox_UpdatePopup(PublicBox *self);
void PublicBox_PlacePopup(PublicBox *self);
int PublicBox_TouchMoved(PublicBox *self);
void PublicBox_HighlightPlace(PublicBox *self, int place);
void PublicBox_ClearHighlights(PublicBox *self);
void PublicBox_SelectPlace(PublicBox *self, int place);
void PublicBox_ClearSelection(PublicBox *self);
int PublicBox_PlaceItemState(PublicBox *self, int place);
int PublicBox_PlaceItem(PublicBox *self, int place);
int PublicBox_PlaceIsEmpty(PublicBox *self, int place);
int PublicBox_PlaceIsLocked(PublicBox *self, int place);
void PublicBox_LockSlots(PublicBox *self);
int PublicBox_SlotMustLock(PublicBox *self, int place);
int PublicBox_PlaceY(PublicBox *self, int place);
int PublicBox_PlaceX(PublicBox *self, int place);
u8 PublicBox_BoxPlaceOfSlot(PublicBox *self, unsigned int slot);
int PublicBox_BoxSlot(PublicBox *self, int place);
void PublicBox_SetSlotItem(PublicBox *self, int place, int item, int state);
int PublicBox_PutHeldAtPlace(PublicBox *self, int place);
int PublicBox_PlaceAtTouch(PublicBox *self, int x, int y, int need_item);
int PublicBox_PocketPlaceOfSlot(PublicBox *self, unsigned int slot);
int PublicBox_GridSlot(PublicBox *self, int place);
int PublicBox_IsButtonPlace(PublicBox *self, int place);
int PublicBox_IsBoxPlace(PublicBox *self, unsigned int place);
int PublicBox_IsPocketPlace(PublicBox *self, unsigned int place);
void PublicBox_EndLayerTask(PublicBox *self);
u16 PublicBox_FirstEmptyBoxPlace(PublicBox *self);
u8 PublicBox_FreePocketPlace(PublicBox *self);
void PublicBox_HoldAndGlide(PublicBox *self, int from, int to);
int PublicBox_DropHeldAtTouch(PublicBox *self, int place, int y);
u8 *PublicBox_GlideHeldTo(PublicBox *self, u8 place, int steps);
void PublicBox_PickUpWithCursor(PublicBox *self, char place);
void PublicBox_PickUpWithTouch(PublicBox *self, int place);
void PublicBox_TouchPlace(PublicBox *self, int place);
void PublicBox_EndAction(PublicBox *self);
void PublicBox_EndActionAtCursor(PublicBox *self);
void PublicBox_EndActionHidden(PublicBox *self);

void PublicBox_WaitClosed(PublicBox *self);
void PublicBox_WaitError(PublicBox *self);
void PublicBox_RunActionWhenIdle(PublicBox *self);
void PublicBox_CloseChoice(PublicBox *self);
void PublicBox_WaitChoiceShown(PublicBox *self);
void PublicBox_StepHeldGlide(PublicBox *self);
void PublicBox_FinishSwap(PublicBox *self);
void PublicBox_Swap(PublicBox *self);
void PublicBox_PutDown(PublicBox *self);
void PublicBox_FinishPickUp(PublicBox *self);
void PublicBox_PickUpAtCursor(PublicBox *self);
void PublicBox_FinishButtonPress(PublicBox *self);
void PublicBox_PressButton(PublicBox *self);
void PublicBox_WaitCursorSprite(PublicBox *self);
void PublicBox_PickChoiceRow(PublicBox *self);
void PublicBox_ChooseByKeys(PublicBox *self);
void PublicBox_MoveHeldByKeys(PublicBox *self);
void PublicBox_BrowseByKeys(PublicBox *self);
void PublicBox_DragHeld(PublicBox *self);
void PublicBox_WatchChoiceTouch(PublicBox *self);
void PublicBox_HoldTouchOnPlace(PublicBox *self);
void PublicBox_IdleByTouch(PublicBox *self);

unsigned int PublicBox_LoadWalletFiles(PublicBox *self);
void PublicBox_LoadBoxLayer(PublicBox *self);
void PublicBox_PrepareWallet(PublicBox *self);
void PublicBox_SetUpLayers(void);
void PublicBox_EndFrame(PublicBox *self);
void PublicBox_BeginFrame(PublicBox *self);
void PublicBox_EndInteractiveFrame(PublicBox *self);
void PublicBox_BeginInteractiveFrame(PublicBox *self);
void PublicBox_Teardown(PublicBox *self);
void PublicBox_Setup(PublicBox *self);
void PublicBox_PocketsWipeOut(PublicBox *self);
void PublicBox_BoxWipeOut(PublicBox *self);
void PublicBox_StartWipeOut(PublicBox *self);
void PublicBox_BoxWipeIn(PublicBox *self);
void PublicBox_PocketsWipeIn(PublicBox *self);
void PublicBox_StartWipeIn(PublicBox *self);
void PublicBox_StartSetup(PublicBox *self);
int PublicBox_End(PublicBox *self);
int PublicBox_Phase4Idle(void);
int PublicBox_Phase3Idle(void);
int PublicBox_RunInteractive(PublicBox *self);
int PublicBox_CloseAsked(PublicBox *self);
void PublicBox_RunSubState(PublicBox *self);
int PublicBox_RunState(PublicBox *self);
int PublicBox_Draw(PublicBox *self);
int PublicBox_Close(PublicBox *self);
int PublicBox_Start(PublicBox *self);
PublicBox *PublicBox_New(void);

#endif
