/* The scene of overlay 108 (overlay group 0x28, opened by overlay 92's dispatcher for GroupParams
 * mode 0x28; vtable 0x0229e098, constructor LetterPick_New, 0x2bd8 bytes): a menu scene
 * (ov002/menu_scene.h) on which the player picks one of the letters they carry, as the evidence
 * says:
 *
 * - it is built on three of the objects of ov094's that the pockets scenes of overlays 096-106
 *   use: the grid at 0x2f0, the letters at 0xd50 (whose places 0-9 are the carried letters) and
 *   the wallet at 0xd78; there is no other set of letters (unlike overlay 106's mailbox scene,
 *   ov106/mailbox_scene.h, which it otherwise follows closely);
 * - its setup dims the written and the received letters (PocketsLetters_DimByState with 3), so
 *   only the letters between villagers (states 7 and 8, main/letter.h) can be picked;
 * - picking one (the choice's text 0xd, LetterPick_PickSlotLetter) hands its index (0-9) to main
 *   (GroupParams_SetArg) with GroupParams_SetC4C(1); the panel's button 9, below the letters,
 *   leaves with GroupParams_SetC4C(0) (LetterPick_FollowPanelPress). Either way the dispatcher is
 *   told the screen ends (LetterPick_StartWipeOut).
 *
 * The cursor walks the carried letters (2 columns of 5) and one more place below them
 * (LetterPickPlace). The scene also keeps the code of the mailbox scene to hold, drag, put down
 * and swap letters (`held`, `swapped`, sub states 4, 7, 0x0d-0x12), but nothing of the overlay
 * enters it: the choice offers no action that picks a letter up, and a touch only opens the
 * choice. */
#ifndef CLEAN_OV108_LETTER_PICK_H
#define CLEAN_OV108_LETTER_PICK_H

#include "main/layer_load_task.h"
#include "main/letter.h"
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
enum LetterPickFlag {
    LETTER_PICK_FLAG_DRAWN = 0x01,         /* the scene is drawn (LetterPick_Draw) */
    LETTER_PICK_FLAG_OBJECTS_DRAWN = 0x02, /* with it the panel and the objects of ov094's */
    LETTER_PICK_FLAG_SELECTABLE = 0x04,    /* the touched place's letter is not dimmed (LetterPick_TouchPlace) */
    LETTER_PICK_FLAG_WRAPPED_LEFT = 0x10,  /* the cursor sprite slides from a screen to the left; cleared
                                             * by every move, set by nothing of the overlay */
    LETTER_PICK_FLAG_WRAPPED_RIGHT = 0x20, /* the same from a screen to the right */
    LETTER_PICK_FLAG_HELD_HIDDEN = 0x40    /* the held letter is not drawn (LetterPick_DrawHeld) */
};

#define LETTER_PICK_FLAGS_WRAPPED (LETTER_PICK_FLAG_WRAPPED_LEFT | LETTER_PICK_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). The letters object knows the carried letters
 * as its places 0-9 (LetterPick_LetterIndex, LetterPick_LetterPlace). */
enum LetterPickPlace {
    LETTER_PICK_CARRIED_FIRST = 0x0b, /* 0x0b-0x14: the carried letters, 0x0b + row * 2 + column */
    LETTER_PICK_CARRIED_LAST = 0x14,
    LETTER_PICK_BELOW = 0x15,   /* below the letters (at 0xbc, 0xb6): the panel's button 9 */
    LETTER_PICK_NO_PLACE = 0x16 /* `popup_place` before any, and no place under a touch */
};

#define LETTER_PICK_COLUMNS 2
#define LETTER_PICK_ROWS 5

/* What the scene holds (`held_kind`). */
enum LetterPickHeldKind {
    LETTER_PICK_HELD_NONE = 0,
    LETTER_PICK_HELD_LETTER = 1 /* a copy of the letter is at `held` */
};

/* The values of the choice rows (`action`), run by LetterPick_RunAction. */
enum LetterPickAction {
    LETTER_PICK_ACTION_PICK = 0,  /* LetterPick_PickSlotLetter */
    LETTER_PICK_ACTION_CANCEL = 1 /* LetterPick_EndAction */
};

/* The sub states, run from the table of LetterPick_RunSubState (MenuScene_SetSubState), named
 * by what their handler does. */
enum LetterPickSubState {
    LETTER_PICK_SUB_TOUCH_IDLE = 0x00,      /* LetterPick_IdleByTouch */
    LETTER_PICK_SUB_TOUCH_HOLD = 0x01,      /* LetterPick_HoldTouchOnPlace */
    LETTER_PICK_SUB_TOUCH_CHOICE = 0x02,    /* LetterPick_WatchChoiceTouch */
    LETTER_PICK_SUB_OPEN_TOUCHED = 0x03,    /* LetterPick_OpenTouchedChoice */
    LETTER_PICK_SUB_DRAG = 0x04,            /* LetterPick_DragHeld */
    LETTER_PICK_SUB_CHOICE_BY_TOUCH = 0x05, /* LetterPick_ChooseByTouch */
    LETTER_PICK_SUB_BROWSE = 0x06,          /* LetterPick_BrowseByKeys */
    LETTER_PICK_SUB_HOLD = 0x07,            /* LetterPick_MoveHeldByKeys */
    LETTER_PICK_SUB_CHOICE_BY_KEYS = 0x08,  /* LetterPick_ChooseByKeys */
    LETTER_PICK_SUB_CHOICE_PICK = 0x09,     /* LetterPick_PickChoiceRow */
    LETTER_PICK_SUB_SPRITE_MOVE = 0x0a,     /* LetterPick_WaitCursorSprite */
    LETTER_PICK_SUB_BELOW_PRESS = 0x0b,     /* LetterPick_PressBelow */
    LETTER_PICK_SUB_PRESS_END = 0x0c,       /* LetterPick_FinishPlacePress */
    LETTER_PICK_SUB_PICK_UP = 0x0d,         /* LetterPick_PickUpAtCursor */
    LETTER_PICK_SUB_PICK_UP_END = 0x0e,     /* LetterPick_FinishPickUp */
    LETTER_PICK_SUB_PUT_DOWN = 0x0f,        /* LetterPick_PutDown */
    LETTER_PICK_SUB_SWAP = 0x10,            /* LetterPick_Swap */
    LETTER_PICK_SUB_SWAP_END = 0x11,        /* LetterPick_FinishSwap */
    LETTER_PICK_SUB_HELD_GLIDE = 0x12,      /* LetterPick_StepHeldGlide */
    LETTER_PICK_SUB_CHOICE_OPEN = 0x13,     /* LetterPick_WaitChoiceShown */
    LETTER_PICK_SUB_CHOICE_CLOSE = 0x14,    /* LetterPick_CloseChoice */
    LETTER_PICK_SUB_CHOICE_RUN = 0x15,      /* LetterPick_RunActionWhenIdle */
    LETTER_PICK_SUB_ERROR = 0x16,           /* LetterPick_WaitError */
    LETTER_PICK_SUB_PANEL_PRESSED = 0x17,   /* LetterPick_FollowPanelPress */
    LETTER_PICK_SUB_STATES = 0x18
};

/* The states, run from the table of LetterPick_RunState (MenuScene_SetState). */
enum LetterPickState {
    LETTER_PICK_STATE_START_SETUP = 0x00,    /* LetterPick_StartSetup */
    LETTER_PICK_STATE_START_WIPE_IN = 0x01,  /* LetterPick_StartWipeIn */
    LETTER_PICK_STATE_SCENE_WIPE_IN = 0x02,  /* LetterPick_SceneWipeIn */
    LETTER_PICK_STATE_START_WIPE_OUT = 0x03, /* LetterPick_StartWipeOut */
    LETTER_PICK_STATE_SCENE_WIPE_OUT = 0x04, /* LetterPick_SceneWipeOut */
    LETTER_PICK_STATES = 0x05
};

/* The phases the scene sets (MenuScene.phase): menu_scene.c's MenuScene_Update runs phase 0 by
 * the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50, 3 by 0x54, 4 by 0x58 and 5 by 0x5c. */
enum LetterPickPhase {
    LETTER_PICK_PHASE_WAIT = 0,        /* the base's wait */
    LETTER_PICK_PHASE_STATES = 1,      /* LetterPick_RunState */
    LETTER_PICK_PHASE_INTERACTIVE = 2, /* LetterPick_RunInteractive */
    LETTER_PICK_PHASE_END = 5          /* LetterPick_End */
};

typedef struct LetterPick {
    MenuScene base;         /* 0x00 */
    u32 flags;              /* 0x94: LetterPickFlag */
    s32 objects_y;          /* 0x98: the wipe's y, for the panel and the objects */
    s32 grab_dx;            /* 0x9c: from the touch to the touched place */
    s32 grab_dy;            /* 0xa0 */
    s32 held_x;             /* 0xa4: where the held letter is drawn */
    s32 held_y;             /* 0xa8 */
    Letter held;            /* 0xac: the held letter's copy */
    Letter swapped;         /* 0x1ac: the letter a swap took from its place */
    u8 held_kind;           /* 0x2ac: LetterPickHeldKind */
    u8 touch_place;         /* 0x2ad: the place touched */
    u8 popup_place;         /* 0x2ae: the place the popup tells of */
    u8 held_from;           /* 0x2af: the place the held letter was taken from */
    u8 cursor;              /* 0x2b0: LetterPickPlace */
    u8 slot;                /* 0x2b1: the place whose choice is open */
    u8 target;              /* 0x2b2: the place the held letter is put down on or swapped at */
    u8 return_state;        /* 0x2b3: the sub state to go back to */
    u8 action;              /* 0x2b4: LetterPickAction */
    u8 choice_row;          /* 0x2b5: the choice row the cursor sprite points at */
    u8 open_delay;          /* 0x2b6: frames before a touched place's choice opens (2) */
    u8 pad_2b7;             /* 0x2b7 */
    LayerTaskPair task;     /* 0x2b8: a layer load task (LetterPick_EndLayerTask) */
    PocketsGrid grid;       /* 0x2f0 */
    PocketsLetters letters; /* 0xd50 */
    PocketsWallet wallet;   /* 0xd78 */
    Popup popup;            /* 0x23b0 */
    Glide glide;            /* 0x2480: the held letter's glide to a place */
    Glider cursor_sprite;   /* 0x2498: a Glider0 */
    u8 choice[0x3e8];       /* 0x24fc: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;  /* 0x28e4 */
    u8 pad_28ef;            /* 0x28ef */
    ErrorMessage error;     /* 0x28f0 */
    ButtonPanel panel;      /* 0x2a0c */
} LetterPick;

LetterPick *LetterPick_Destroy(LetterPick *self);
LetterPick *LetterPick_Delete(LetterPick *self);
void LetterPick_ClearFlags(LetterPick *self, unsigned int flags);
void LetterPick_SetFlags(LetterPick *self, int flags);
int LetterPick_TestFlags(LetterPick *self, unsigned int flags);
int LetterPick_MoveCursor(LetterPick *self, int keys, int mode);
void LetterPick_MoveCursorInCarried(LetterPick *self, int keys, int mode);
void LetterPick_OpenLetterMenu(LetterPick *self, int place, int above_popup);
void LetterPick_CancelChoice(LetterPick *self);
void LetterPick_ShowChoice(LetterPick *self, int above_popup);
void LetterPick_RunAction(LetterPick *self);
void LetterPick_BeginSwap(LetterPick *self, u8 target);
void LetterPick_BeginPutDown(LetterPick *self, u8 target);
void LetterPick_BeginBelowPress(LetterPick *self);
void LetterPick_ShowCursorFirstOfSet(LetterPick *self);
void LetterPick_PlaceCursorSprite(LetterPick *self);
void LetterPick_PointAtDefaultRow(LetterPick *self);
void LetterPick_PointAtLastRow(LetterPick *self);
void LetterPick_GlideToRow(LetterPick *self);
void LetterPick_GlideToCursor(LetterPick *self);
void LetterPick_HideCursorSprite(LetterPick *self);
int LetterPick_CursorSpriteY(LetterPick *self);
int LetterPick_CursorSpriteX(LetterPick *self);
void LetterPick_ShowCursorAtCursor(LetterPick *self);
void LetterPick_SwapHeldWith(LetterPick *self, int place);
void LetterPick_PutHeldAt(LetterPick *self, int place);
void LetterPick_PickUpLetter(LetterPick *self, int place);
int LetterPick_FollowGlide(LetterPick *self);
void LetterPick_FollowCursorSprite(LetterPick *self);
void LetterPick_FollowTouch(LetterPick *self);
void LetterPick_DrawHeld(LetterPick *self);
void LetterPick_UpdatePopup(LetterPick *self);
void LetterPick_PlacePopup(LetterPick *self);
void LetterPick_HighlightPlace(LetterPick *self, int place);
void LetterPick_ClearHighlights(LetterPick *self);
void LetterPick_SelectPlace(LetterPick *self, int place);
void LetterPick_ClearSelection(LetterPick *self);
int LetterPick_PlaceIsEmpty(LetterPick *self, int place);
int LetterPick_PlaceIsDimmed(LetterPick *self, int place);
void LetterPick_DimLetters(LetterPick *self);
int LetterPick_PlaceY(LetterPick *self, int place);
int LetterPick_PlaceX(LetterPick *self, int place);
Letter *LetterPick_PlaceLetter(LetterPick *self, int place);
void LetterPick_PutLetterAt(LetterPick *self, int place, Letter *letter);
int LetterPick_PutHeldLetterAt(LetterPick *self, int place);
int LetterPick_LetterPlaceAtTouch(LetterPick *self, int x, int y, int with_letter);
int LetterPick_LetterPlace(LetterPick *self, unsigned int index);
int LetterPick_LetterIndex(LetterPick *self, unsigned int place);
int LetterPick_IsCarriedPlace(LetterPick *self, unsigned int place);
void LetterPick_EndLayerTask(LetterPick *self);
void LetterPick_PressPanelButton9(LetterPick *self);
void LetterPick_PickSlotLetter(LetterPick *self);
void LetterPick_GlideHeldTo(LetterPick *self, int place, int steps);
void LetterPick_PickUpWithCursor(LetterPick *self, int place);
void LetterPick_TouchPlace(LetterPick *self, int place);
void LetterPick_EndAction(LetterPick *self);
void LetterPick_EndActionAtCursor(LetterPick *self);
void LetterPick_EndActionHidden(LetterPick *self);

void LetterPick_FollowPanelPress(LetterPick *self);
void LetterPick_WaitError(LetterPick *self);
void LetterPick_RunActionWhenIdle(LetterPick *self);
void LetterPick_CloseChoice(LetterPick *self);
void LetterPick_WaitChoiceShown(LetterPick *self);
void LetterPick_StepHeldGlide(LetterPick *self);
void LetterPick_FinishSwap(LetterPick *self);
void LetterPick_Swap(LetterPick *self);
void LetterPick_PutDown(LetterPick *self);
void LetterPick_FinishPickUp(LetterPick *self);
void LetterPick_PickUpAtCursor(LetterPick *self);
void LetterPick_FinishPlacePress(LetterPick *self);
void LetterPick_PressBelow(LetterPick *self);
void LetterPick_WaitCursorSprite(LetterPick *self);
void LetterPick_PickChoiceRow(LetterPick *self);
void LetterPick_ChooseByKeys(LetterPick *self);
void LetterPick_MoveHeldByKeys(LetterPick *self);
void LetterPick_BrowseByKeys(LetterPick *self);
void LetterPick_ChooseByTouch(LetterPick *self);
void LetterPick_DragHeld(LetterPick *self);
void LetterPick_OpenTouchedChoice(LetterPick *self);
int LetterPick_WatchChoiceTouch(LetterPick *self);
void LetterPick_HoldTouchOnPlace(LetterPick *self);
void LetterPick_IdleByTouch(LetterPick *self);

void LetterPick_PreparePanel(LetterPick *self);
void LetterPick_PrepareWallet(LetterPick *self);
void LetterPick_SetUpLayers(void);
void LetterPick_EndFrame(LetterPick *self);
void LetterPick_BeginFrame(LetterPick *self);
void LetterPick_EndInteractiveFrame(LetterPick *self);
int LetterPick_BeginInteractiveFrame(LetterPick *self);
void LetterPick_Teardown(LetterPick *self);
void LetterPick_Setup(LetterPick *self);
void LetterPick_SceneWipeOut(LetterPick *self);
void LetterPick_StartWipeOut(LetterPick *self);
void LetterPick_SceneWipeIn(LetterPick *self);
void LetterPick_StartWipeIn(LetterPick *self);
void LetterPick_StartSetup(LetterPick *self);
int LetterPick_End(LetterPick *self);
int LetterPick_Phase4Idle(void);
int LetterPick_Phase3Idle(void);
int LetterPick_RunInteractive(LetterPick *self);
void LetterPick_RunSubState(LetterPick *self);
int LetterPick_RunState(LetterPick *self);
int LetterPick_Draw(LetterPick *self);
int LetterPick_Close(LetterPick *self);
int LetterPick_Start(LetterPick *self);
LetterPick *LetterPick_New(void);

#endif
