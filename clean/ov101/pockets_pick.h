/* The scene of overlay 101 (vtable 0x0229e078, include/cpp/ov101/Obj_ov101_0229e078.h; constructor
 * PocketsPick_New, 0x29dc bytes): the screen on which the player picks one of their pocket
 * slots for someone who asked for an item. It is the screen of overlay group 0x12, which ov092's
 * dispatcher (ov092/menu_dispatch.h) starts for GroupParams mode 0x21, the mode that
 * GroupParams_OpenWithMask opens group 9 in (main/group_params.h). Its callers ask for an item and
 * pass a mask of the pocket slots that may be given (Pockets_Select): a sick villager asking for
 * medicine (ov004/sick_villager.c), a birthday villager's present (ov004/birthday_villager.c), a
 * room object that takes an item (ov004/room_object_02253058.c) and the scene commands
 * (main/scene_command.c). As the evidence says:
 *
 * - the slots whose bit is clear in the mask (GroupParams_Mask) are dimmed and cannot be picked
 *   (PocketsPick_DimUnselectable);
 * - picking a slot opens a choice (ov002/paged_choice.h) of two rows: the text GroupParams_MaskArg
 *   names (the caller's, e.g. 0xd for the sick and birthday villagers) and text 2; the first
 *   picks the slot: GroupParams_SetArg(slot) and GroupParams_SetC4C(1), and the scene closes
 *   (PocketsPick_Choose). Closing any other way leaves GroupParams_SetC4C(0) (PocketsPick_Cancel);
 *   the sick villager then empties the slot picked (CurrentPockets_Empty(GroupParams_Arg())) or
 *   says nothing was picked;
 * - there is one more place below the grid, the button panel's close button (button 9,
 *   PICK_PLACE_CLOSE), which B presses too;
 * - the code that moves a held item between the slots (picked up, dragged, put down, swapped,
 *   as in ov099/pockets_view.h) is here too, but nothing in this overlay enters it: no function
 *   sets sub states 5, 7, 0x0c or 0x0d, and the others of that code are reached only from them.
 *
 * It is built on the three objects of ov094's that the pockets scenes of overlays 096-106 use (the
 * grid of the 15 pocket slots at 0xf4, the letters at 0xb54, drawn dimmed, and the wallet at
 * 0xb7c) and on the menu scene's helpers of ov002. The scene runs in two ways, as state flag 2
 * says (StateFlags_Test2/StateFlags_IsClear2): by the touch (sub states 0-5, the cursor sprite
 * hidden) or by the keys (sub states 6-9, the cursor sprite shown). */
#ifndef CLEAN_OV101_POCKETS_PICK_H
#define CLEAN_OV101_POCKETS_PICK_H

#include "clean.h"
#include "main/layer_load_task.h"
#include "ov002/button_panel.h"
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
enum PocketsPickFlag {
    PICK_FLAG_DRAWN = 0x01,         /* the scene is drawn (PocketsPick_Draw) */
    PICK_FLAG_OBJECTS_DRAWN = 0x02, /* the panel and the objects of ov094's are drawn */
    PICK_FLAG_JUMP = 0x04,          /* the cursor sprite jumps to the cursor instead of easing
                                     * (PocketsPick_GlideToCursor), once; never set here */
    PICK_FLAG_WRAPPED_LEFT = 0x08,  /* this move wrapped the cursor from the first column to the last */
    PICK_FLAG_WRAPPED_RIGHT = 0x10, /* this move wrapped it from the last column to the first */
    PICK_FLAG_SWAPPING = 0x20       /* set by a swap until the cursor sprite's turn settles
                                     * (PocketsPick_Swap, PocketsPick_FinishSwap); nothing in this
                                     * overlay reads it */
};

#define PICK_FLAGS_WRAPPED (PICK_FLAG_WRAPPED_LEFT | PICK_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). */
enum PocketsPickPlace {
    PICK_PLACE_GRID_FIRST = 0x00, /* 0-14: the pocket slots, row * 5 + column */
    PICK_PLACE_GRID_LAST = 0x0e,
    PICK_PLACE_CLOSE = 0x0f, /* below the grid: the panel's close button (at 0xbc, 0xb6) */
    PICK_PLACE_NONE = 0x10   /* no place (`popup_place` before any, a touch on no slot) */
};

#define PICK_GRID_COLUMNS 5
#define PICK_GRID_ROWS 3
#define PICK_GRID_SLOTS 15

/* What the scene holds (`held_kind`). */
enum PocketsPickHeldKind {
    PICK_HELD_NONE = 0,
    PICK_HELD_ITEM = 1 /* `item` and `held_state` */
};

/* The values of the choice's rows (`action`), run by PocketsPick_RunAction. */
enum PocketsPickAction {
    PICK_ACTION_CHOOSE = 0, /* the slot is picked: PocketsPick_Choose */
    PICK_ACTION_CANCEL = 1  /* PocketsPick_EndAction (so is any other value) */
};

/* The states, run from the table of PocketsPick_RunState (MenuScene_SetState). */
enum PocketsPickState {
    PICK_STATE_START_SETUP = 0,    /* PocketsPick_StartSetup */
    PICK_STATE_START_WIPE_IN = 1,  /* PocketsPick_StartWipeIn */
    PICK_STATE_WIPE_IN = 2,        /* PocketsPick_WipeIn */
    PICK_STATE_START_WIPE_OUT = 3, /* PocketsPick_StartWipeOut */
    PICK_STATE_WIPE_OUT = 4,       /* PocketsPick_WipeOut */
    PICK_STATES = 5
};

/* The sub states, run from the table of PocketsPick_RunSubState (MenuScene_SetSubState). */
enum PocketsPickSubState {
    PICK_SUB_IDLE_BY_TOUCH = 0x00,   /* PocketsPick_IdleByTouch */
    PICK_SUB_HOLD_TOUCH = 0x01,      /* PocketsPick_HoldTouchOnPlace */
    PICK_SUB_WAIT_PEN_UP = 0x02,     /* PocketsPick_WaitPenUp */
    PICK_SUB_OPEN_TOUCHED = 0x03,    /* PocketsPick_OpenTouchedChoice */
    PICK_SUB_CHOICE_BY_TOUCH = 0x04, /* PocketsPick_ChooseByTouch */
    PICK_SUB_DRAG = 0x05,            /* PocketsPick_DragHeld; not set by this overlay */
    PICK_SUB_IDLE_BY_KEYS = 0x06,    /* PocketsPick_IdleByKeys */
    PICK_SUB_HOLD_BY_KEYS = 0x07,    /* PocketsPick_MoveHeldByKeys; never entered */
    PICK_SUB_CHOICE_BY_KEYS = 0x08,  /* PocketsPick_ChooseByKeys */
    PICK_SUB_PICK_ROW = 0x09,        /* PocketsPick_PickChoiceRow */
    PICK_SUB_WAIT_SPRITE = 0x0a,     /* PocketsPick_WaitCursorSprite */
    PICK_SUB_PRESS_CLOSE = 0x0b,     /* PocketsPick_PressCloseWhenDone */
    PICK_SUB_WAIT_ANIM = 0x0c,       /* PocketsPick_WaitCursorAnim; not set by this overlay */
    PICK_SUB_PICK_UP = 0x0d,         /* PocketsPick_PickUpOnTurn; not set by this overlay */
    PICK_SUB_PICKED_UP = 0x0e,       /* PocketsPick_FinishPickUp */
    PICK_SUB_PUT_DOWN = 0x0f,        /* PocketsPick_PutDownWithCursor */
    PICK_SUB_SWAP = 0x10,            /* PocketsPick_Swap */
    PICK_SUB_SWAPPED = 0x11,         /* PocketsPick_FinishSwap */
    PICK_SUB_HELD_GLIDE = 0x12,      /* PocketsPick_StepHeldGlide */
    PICK_SUB_CHOICE_OPENING = 0x13,  /* PocketsPick_WaitChoiceShown */
    PICK_SUB_CHOICE_CLOSE = 0x14,    /* PocketsPick_CloseChoice */
    PICK_SUB_CHOICE_CLOSING = 0x15,  /* PocketsPick_RunActionWhenIdle */
    PICK_SUB_ERROR = 0x16,           /* PocketsPick_WaitError; not set by this overlay */
    PICK_SUB_CLOSE_PRESSED = 0x17,   /* PocketsPick_FollowClosePress */
    PICK_SUB_STATES = 0x18
};

typedef struct PocketsPick {
    MenuScene base;           /* 0x00 */
    u32 flags;                /* 0x94: PocketsPickFlag */
    s32 wipe_y;               /* 0x98: MenuScene_WipeOffsetY's, where the panel and objects are drawn */
    s32 grab_dx;              /* 0x9c: from the touch to the touched place */
    s32 grab_dy;              /* 0xa0 */
    s32 held_x;               /* 0xa4: where the held item is */
    s32 held_y;               /* 0xa8 */
    u16 item;                 /* 0xac: the held item's code */
    u8 held_state;            /* 0xae: the held item's state (PocketsGrid_ItemState) */
    u8 held_kind;             /* 0xaf: PocketsPickHeldKind */
    u8 touch_place;           /* 0xb0: the place touched */
    u8 popup_place;           /* 0xb1: the place the popup tells of */
    u8 held_place;            /* 0xb2: the place the held item came from */
    u8 cursor;                /* 0xb3: PocketsPickPlace */
    u8 slot;                  /* 0xb4: the place whose choice is open */
    u8 target;                /* 0xb5: the place the held item is put down on or swapped at */
    u8 return_state;          /* 0xb6: the sub state to go back to */
    u8 action;                /* 0xb7: PocketsPickAction, the value of the row picked */
    u8 choice_row;            /* 0xb8: the choice row the cursor sprite points at */
    u8 open_delay;            /* 0xb9: frames before a touched place's choice opens (2) */
    u8 pad_ba[2];             /* 0xba */
    LayerTaskPair layer_task; /* 0xbc: ended each frame (PocketsPick_EndLayerTask) */
    PocketsGrid grid;         /* 0xf4: the 15 pocket slots */
    PocketsLetters letters;   /* 0xb54 */
    PocketsWallet wallet;     /* 0xb7c */
    Popup popup;              /* 0x21b4: tells of the item at `popup_place` */
    Glide glide;              /* 0x2284: the held item's glide to a place */
    Glider cursor_sprite;     /* 0x229c: a Glider0 */
    u8 choice[0x3e8];         /* 0x2300: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;    /* 0x26e8 */
    u8 pad_26f3;              /* 0x26f3 */
    ErrorMessage error;       /* 0x26f4 */
    ButtonPanel panel;        /* 0x2810: its button 9 closes the scene */
} PocketsPick;

PocketsPick *PocketsPick_Destroy(PocketsPick *self);
PocketsPick *PocketsPick_Delete(PocketsPick *self);
void PocketsPick_ClearFlags(PocketsPick *self, unsigned int flags);
void PocketsPick_SetFlags(PocketsPick *self, int flags);
int PocketsPick_TestFlags(PocketsPick *self, int flags);
int PocketsPick_MoveCursor(PocketsPick *self, int keys);
void PocketsPick_MoveCursorInGrid(PocketsPick *self, int keys);
void PocketsPick_OpenChoice(PocketsPick *self, int place, int above_popup);
void PocketsPick_AddEntries(PocketsPick *self);
void PocketsPick_Cancel(PocketsPick *self);
void PocketsPick_Choose(PocketsPick *self);
void PocketsPick_CancelChoice(PocketsPick *self);
void PocketsPick_ShowChoice(PocketsPick *self, int above_popup);
void PocketsPick_RunAction(PocketsPick *self);
void PocketsPick_StartSwap(PocketsPick *self, u8 place);
void PocketsPick_StartPutDown(PocketsPick *self, u8 place);
void PocketsPick_PressClose(PocketsPick *self);
void PocketsPick_ShowCursorFirstOfSet(PocketsPick *self);
void PocketsPick_PlaceCursorSprite(PocketsPick *self);
void PocketsPick_PointAtFirstRow(PocketsPick *self);
void PocketsPick_PointAtLastRow(PocketsPick *self);
void PocketsPick_GlideToRow(PocketsPick *self);
void PocketsPick_GlideToCursor(PocketsPick *self);
void PocketsPick_HideCursorSprite(PocketsPick *self);
int PocketsPick_CursorSpriteY(PocketsPick *self);
int PocketsPick_CursorSpriteX(PocketsPick *self);
void PocketsPick_ShowCursorSprite(PocketsPick *self);
void PocketsPick_SwapHeldWith(PocketsPick *self, int place);
void PocketsPick_PutHeldAt(PocketsPick *self, int place);
void PocketsPick_PickUpItem(PocketsPick *self, int place);
void PocketsPick_FollowGlide(PocketsPick *self);
void PocketsPick_FollowCursorSprite(PocketsPick *self);
void PocketsPick_FollowTouch(PocketsPick *self);
void PocketsPick_UpdatePopup(PocketsPick *self);
void PocketsPick_PlacePopup(PocketsPick *self);
void PocketsPick_MarkPlace(PocketsPick *self, int place);
void PocketsPick_ClearMarks(PocketsPick *self);
void PocketsPick_SelectPlace(PocketsPick *self, int place);
void PocketsPick_ClearSelection(PocketsPick *self);
int PocketsPick_PlaceItemState(PocketsPick *self, int place);
int PocketsPick_PlaceItem(PocketsPick *self, int place);
int PocketsPick_PlaceIsEmpty(PocketsPick *self, int place);
int PocketsPick_PlaceIsDimmed(PocketsPick *self, int place);
void PocketsPick_DimUnselectable(PocketsPick *self);
int PocketsPick_PlaceY(PocketsPick *self, int place);
int PocketsPick_PlaceX(PocketsPick *self, int place);
void PocketsPick_SetSlotItem(PocketsPick *self, int place, int item, int state);
int PocketsPick_DropHeldAt(PocketsPick *self, int place);
int PocketsPick_GridPlaceAtTouch(PocketsPick *self, int x, int y, int with_item);
u8 PocketsPick_GridPlace(PocketsPick *self, unsigned int index);
int PocketsPick_GridIndex(PocketsPick *self, int place);
int PocketsPick_IsGridPlace(PocketsPick *self, unsigned int place);
void PocketsPick_EndLayerTask(PocketsPick *self);
void PocketsPick_GlideHeldTo(PocketsPick *self, int place, int steps);
void PocketsPick_PickUpWithCursor(PocketsPick *self, int place);
void PocketsPick_TouchPlace(PocketsPick *self, int place);
void PocketsPick_EndAction(PocketsPick *self);
void PocketsPick_EndActionAtCursor(PocketsPick *self);
void PocketsPick_EndActionHidden(PocketsPick *self);

void PocketsPick_FollowClosePress(PocketsPick *self);
void PocketsPick_WaitError(PocketsPick *self);
void PocketsPick_RunActionWhenIdle(PocketsPick *self);
void PocketsPick_CloseChoice(PocketsPick *self);
void PocketsPick_WaitChoiceShown(PocketsPick *self);
void PocketsPick_StepHeldGlide(PocketsPick *self);
void PocketsPick_FinishSwap(PocketsPick *self);
void PocketsPick_Swap(PocketsPick *self);
void PocketsPick_PutDownWithCursor(PocketsPick *self);
void PocketsPick_FinishPickUp(PocketsPick *self);
void PocketsPick_PickUpOnTurn(PocketsPick *self);
void PocketsPick_WaitCursorAnim(PocketsPick *self);
void PocketsPick_PressCloseWhenDone(PocketsPick *self);
void PocketsPick_WaitCursorSprite(PocketsPick *self);
void PocketsPick_PickChoiceRow(PocketsPick *self);
void PocketsPick_ChooseByKeys(PocketsPick *self);
void PocketsPick_MoveHeldByKeys(PocketsPick *self);
void PocketsPick_IdleByKeys(PocketsPick *self);
void PocketsPick_DragHeld(PocketsPick *self);
void PocketsPick_ChooseByTouch(PocketsPick *self);
void PocketsPick_OpenTouchedChoice(PocketsPick *self);
void PocketsPick_WaitPenUp(PocketsPick *self);
void PocketsPick_HoldTouchOnPlace(PocketsPick *self);
void PocketsPick_IdleByTouch(PocketsPick *self);

void PocketsPick_LoadWalletAndPanel(PocketsPick *self);
void PocketsPick_PrepareWallet(PocketsPick *self);
void PocketsPick_SetUpLayer6(void);
void PocketsPick_EndFrame(PocketsPick *self);
void PocketsPick_BeginFrame(PocketsPick *self);
void PocketsPick_EndInteractiveFrame(PocketsPick *self);
void PocketsPick_BeginInteractiveFrame(PocketsPick *self);
void PocketsPick_Teardown(PocketsPick *self);
void PocketsPick_Setup(PocketsPick *self);
void PocketsPick_WipeOut(PocketsPick *self);
void PocketsPick_StartWipeOut(PocketsPick *self);
void PocketsPick_WipeIn(PocketsPick *self);
void PocketsPick_StartWipeIn(PocketsPick *self);
void PocketsPick_StartSetup(PocketsPick *self);
int PocketsPick_RequestDelete(PocketsPick *self);
int PocketsPick_Phase4Idle(void);
int PocketsPick_Phase3Idle(void);
int PocketsPick_RunInteractive(PocketsPick *self);
void PocketsPick_RunSubState(PocketsPick *self);
int PocketsPick_RunState(PocketsPick *self);
int PocketsPick_Draw(PocketsPick *self);
int PocketsPick_Close(PocketsPick *self);
int PocketsPick_Start(PocketsPick *self);
PocketsPick *PocketsPick_New(void);

#endif
