/* The scene of overlay 103 (vtable 0x0229e2e0, include/cpp/ov103/Obj_ov103_0229e2e0.h; constructor
 * CarriedLetters_New, 0x2dac bytes): a menu scene (ov002/menu_scene.h) that shows the ten letters
 * the current player carries and lets them be read and moved between their places.
 *
 * - It is overlay group 20 (overlays 103 and 94, main/overlay_groups.h), the group overlay 92's
 *   dispatcher (ov092/menu_dispatch.c) opens for GroupParams mode 0x24. No code of the game opens
 *   that mode by a constant: a scene command does (SceneCommand_OpenScreen, main/scene_command.c),
 *   with the mode it was given.
 * - It is built on the three objects of ov094's that the pockets scenes of overlays 096-105 use,
 *   at the places ov099's pockets view (ov099/pockets_view.h) keeps them: the grid at 0xcc (all
 *   of its fifteen places dimmed, CarriedLetters_DimGrid), the letters at 0xb2c (its places 0-9,
 *   the carried letters) and the wallet at 0xb54. Its other members are laid out as those of
 *   ov106's mailbox scene (ov106/mailbox_scene.h) without the mailbox and the button panel.
 *
 * The cursor walks the carried letters (2 columns of 5, no wrap). Picking a letter opens a choice
 * (ov002/paged_choice.h) whose rows carry an action (CarriedLettersAction): the letter can be
 * picked up (with the keys only), held and put down on or swapped with another place's, or read:
 * the scene then wipes out and the letter is shown (main/letter_view.h) with a label button that
 * closes it and sets the scene up again. Y closes the scene. */
#ifndef CLEAN_OV103_CARRIED_LETTERS_H
#define CLEAN_OV103_CARRIED_LETTERS_H

#include "main/layer_load_task.h"
#include "main/letter.h"
#include "main/letter_view.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/label_button.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"
#include "types.h"

/* In `flags`. */
enum CarriedLettersFlag {
    CARRIED_LETTERS_FLAG_DRAWN = 0x01,         /* the scene is drawn (CarriedLetters_Draw) */
    CARRIED_LETTERS_FLAG_OBJECTS_DRAWN = 0x02, /* the grid, the letters and the wallet are drawn */
    CARRIED_LETTERS_FLAG_DRAGGABLE = 0x04,     /* the touched place's letter may be dragged, as it
                                                * is not dimmed (CarriedLetters_TouchPlace) */
    CARRIED_LETTERS_FLAG_08 = 0x08,            /* the cursor sprite jumps to the cursor instead of
                                                * easing (CarriedLetters_GlideToCursor), once; never
                                                * set by this overlay */
    CARRIED_LETTERS_FLAG_WRAPPED_LEFT = 0x10,  /* tested by CarriedLetters_CursorSpriteX, cleared by
                                                * each move; never set by this overlay */
    CARRIED_LETTERS_FLAG_WRAPPED_RIGHT = 0x20, /* the same */
    CARRIED_LETTERS_FLAG_HELD_HIDDEN = 0x40,   /* the held letter is not drawn */
    CARRIED_LETTERS_FLAG_LETTER_SHOWN = 0x80,  /* a letter is shown; its label button is drawn */
    CARRIED_LETTERS_FLAG_READ = 0x100          /* the letter of `slot` is shown once the scene has
                                                * wiped out (CarriedLetters_RunActionRead) */
};

#define CARRIED_LETTERS_FLAGS_WRAPPED (CARRIED_LETTERS_FLAG_WRAPPED_LEFT | CARRIED_LETTERS_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). The letters object of ov094's knows the
 * carried letters as its places 0-9 (CarriedLetters_LetterIndex, CarriedLetters_LetterPlace). */
enum CarriedLettersPlace {
    CARRIED_LETTERS_FIRST = 0x0b, /* 0x0b-0x14: the carried letters, 0x0b + row * 2 + column */
    CARRIED_LETTERS_LAST = 0x14,
    CARRIED_LETTERS_NO_PLACE = 0x15
};

#define CARRIED_LETTERS_COLUMNS 2
#define CARRIED_LETTERS_ROWS 5

/* What the scene holds (`held_kind`). */
enum CarriedLettersHeldKind {
    CARRIED_LETTERS_HELD_NONE = 0,
    CARRIED_LETTERS_HELD_LETTER = 1 /* a copy of the letter is at `held` */
};

/* The values of the choice rows (`action`), run by CarriedLetters_RunAction. */
enum CarriedLettersAction {
    CARRIED_LETTERS_ACTION_HOLD = 0,  /* text 0: the letter picked up with the cursor */
    CARRIED_LETTERS_ACTION_READ = 1,  /* text 0x14 or 0x17: the letter read */
    CARRIED_LETTERS_ACTION_2 = 2,     /* text 0x15: runs as the cancel does */
    CARRIED_LETTERS_ACTION_CANCEL = 3 /* text 2 */
};

/* The phases set (MenuScene.phase; MenuScene_Update runs phase 0 by the vtable's slot 0x48, 1 by
 * 0x4c, 2 by 0x50 and 5 by 0x5c, as ov092/menu_dispatch.h says). */
enum CarriedLettersPhase {
    CARRIED_LETTERS_PHASE_WAIT = 0,
    CARRIED_LETTERS_PHASE_STATES = 1,      /* CarriedLetters_RunState */
    CARRIED_LETTERS_PHASE_INTERACTIVE = 2, /* CarriedLetters_RunInteractive */
    CARRIED_LETTERS_PHASE_END = 5          /* CarriedLetters_End */
};

/* The states, run from the table of CarriedLetters_RunState (MenuScene_SetState). */
enum CarriedLettersState {
    CARRIED_LETTERS_STATE_START_SETUP = 0,           /* CarriedLetters_StartSetup */
    CARRIED_LETTERS_STATE_START_WIPE_IN = 1,         /* CarriedLetters_StartWipeIn */
    CARRIED_LETTERS_STATE_SCENE_WIPE_IN = 2,         /* CarriedLetters_SceneWipeIn */
    CARRIED_LETTERS_STATE_START_WIPE_OUT = 3,        /* CarriedLetters_StartWipeOut */
    CARRIED_LETTERS_STATE_SCENE_WIPE_OUT = 4,        /* CarriedLetters_SceneWipeOut */
    CARRIED_LETTERS_STATE_SHOW_LETTER = 5,           /* CarriedLetters_ShowLetter */
    CARRIED_LETTERS_STATE_LETTER_WIPE_IN = 6,        /* CarriedLetters_LetterWipeIn */
    CARRIED_LETTERS_STATE_START_LETTER_WIPE_OUT = 7, /* CarriedLetters_StartLetterWipeOut */
    CARRIED_LETTERS_STATE_LETTER_WIPE_OUT = 8,       /* CarriedLetters_LetterWipeOut */
    CARRIED_LETTERS_STATES = 9
};

/* The sub states, run from the table of CarriedLetters_RunSubState (MenuScene_SetSubState), named
 * by what their handler does. */
enum CarriedLettersSubState {
    CARRIED_LETTERS_SUB_TOUCH_IDLE = 0x00,      /* CarriedLetters_IdleByTouch */
    CARRIED_LETTERS_SUB_TOUCH_HOLD = 0x01,      /* CarriedLetters_HoldTouchOnPlace */
    CARRIED_LETTERS_SUB_DRAG = 0x02,            /* CarriedLetters_DragHeld */
    CARRIED_LETTERS_SUB_LABEL_BY_TOUCH = 0x03,  /* CarriedLetters_LabelByTouch */
    CARRIED_LETTERS_SUB_CHOICE_BY_TOUCH = 0x04, /* CarriedLetters_ChooseByTouch */
    CARRIED_LETTERS_SUB_BROWSE = 0x05,          /* CarriedLetters_BrowseByKeys */
    CARRIED_LETTERS_SUB_HOLD = 0x06,            /* CarriedLetters_MoveHeldByKeys */
    CARRIED_LETTERS_SUB_LABEL_BY_KEYS = 0x07,   /* CarriedLetters_LabelByKeys */
    CARRIED_LETTERS_SUB_LABEL_PRESS = 0x08,     /* CarriedLetters_WaitLabelPress */
    CARRIED_LETTERS_SUB_CHOICE_BY_KEYS = 0x09,  /* CarriedLetters_ChooseByKeys */
    CARRIED_LETTERS_SUB_CHOICE_PICK = 0x0a,     /* CarriedLetters_PickChoiceRow */
    CARRIED_LETTERS_SUB_SPRITE_MOVE = 0x0b,     /* CarriedLetters_WaitCursorSprite */
    CARRIED_LETTERS_SUB_PLACE_PRESS = 0x0c,     /* CarriedLetters_PressPlace (no code sets it) */
    CARRIED_LETTERS_SUB_PRESS_END = 0x0d,       /* CarriedLetters_FinishPlacePress */
    CARRIED_LETTERS_SUB_PICK_UP = 0x0e,         /* CarriedLetters_PickUpAtCursor */
    CARRIED_LETTERS_SUB_PICK_UP_END = 0x0f,     /* CarriedLetters_FinishPickUp */
    CARRIED_LETTERS_SUB_PUT_DOWN = 0x10,        /* CarriedLetters_PutDown */
    CARRIED_LETTERS_SUB_SWAP = 0x11,            /* CarriedLetters_Swap */
    CARRIED_LETTERS_SUB_SWAP_END = 0x12,        /* CarriedLetters_FinishSwap */
    CARRIED_LETTERS_SUB_HELD_GLIDE = 0x13,      /* CarriedLetters_StepHeldGlide */
    CARRIED_LETTERS_SUB_CHOICE_OPEN = 0x14,     /* CarriedLetters_WaitChoiceShown */
    CARRIED_LETTERS_SUB_CHOICE_CLOSE = 0x15,    /* CarriedLetters_CloseChoice */
    CARRIED_LETTERS_SUB_CHOICE_RUN = 0x16,      /* CarriedLetters_RunActionWhenIdle */
    CARRIED_LETTERS_SUB_ERROR = 0x17,           /* CarriedLetters_WaitError (no code sets it) */
    CARRIED_LETTERS_SUB_LABEL_PRESSED = 0x18,   /* CarriedLetters_FollowLabelPress */
    CARRIED_LETTERS_SUB_STATES = 0x19
};

typedef struct CarriedLetters {
    MenuScene base;         /* 0x00 */
    LayerTaskPair tasks;    /* 0x94: ended each frame (CarriedLetters_EndLayerTask) */
    PocketsGrid grid;       /* 0xcc */
    PocketsLetters letters; /* 0xb2c */
    PocketsWallet wallet;   /* 0xb54 */
    Popup popup;            /* 0x218c: tells of the place under the cursor or the touch */
    Glide glide;            /* 0x225c: the held letter's glide to a place */
    Glider cursor_sprite;   /* 0x2274: a Glider0 */
    u8 choice[0x3e8];       /* 0x22d8: a PagedChoice */
    ChoiceEntries entries;  /* 0x26c0 */
    u8 pad_26cb;            /* 0x26cb */
    ErrorMessage error;     /* 0x26cc: only updated (CarriedLetters_WaitError) */
    LetterView view;        /* 0x27e8: shows a letter */
    LabelButton button;     /* 0x2b10: a LabelButton0, shown under a letter shown */
    u32 flags;              /* 0x2b88: CarriedLettersFlag */
    s32 objects_y;          /* 0x2b8c: MenuScene_WipeOffsetY's, where the objects are drawn */
    s32 grab_dx;            /* 0x2b90: from the touch to the held letter */
    s32 grab_dy;            /* 0x2b94 */
    s32 held_x;             /* 0x2b98: where the held letter is drawn */
    s32 held_y;             /* 0x2b9c */
    Letter held;            /* 0x2ba0: the held letter's copy */
    Letter swapped;         /* 0x2ca0: the letter a swap took from its place */
    u8 held_kind;           /* 0x2da0: CarriedLettersHeldKind */
    u8 touch_place;         /* 0x2da1: the place touched */
    u8 popup_place;         /* 0x2da2: the place the popup tells of */
    u8 held_from;           /* 0x2da3: the place the held letter was taken from */
    u8 cursor;              /* 0x2da4: CarriedLettersPlace */
    u8 slot;                /* 0x2da5: the place whose choice is open */
    u8 target;              /* 0x2da6: the place the held letter is put down on or swapped at */
    u8 return_state;        /* 0x2da7: the sub state to go back to */
    u8 action;              /* 0x2da8: CarriedLettersAction */
    u8 choice_row;          /* 0x2da9: the choice row the cursor sprite points at */
    u8 pad_2daa[2];         /* 0x2daa */
} CarriedLetters;

CarriedLetters *CarriedLetters_Destroy(CarriedLetters *self);
CarriedLetters *CarriedLetters_Delete(CarriedLetters *self);
void CarriedLetters_ClearFlags(CarriedLetters *self, unsigned int flags);
void CarriedLetters_SetFlags(CarriedLetters *self, unsigned int flags);
int CarriedLetters_TestFlags(CarriedLetters *self, unsigned int flags);
void CarriedLetters_PressLabelButton(CarriedLetters *self);
void CarriedLetters_RunActionRead(CarriedLetters *self);
int CarriedLetters_MoveCursor(CarriedLetters *self, int keys, int mode);
void CarriedLetters_MoveCursorInLetters(CarriedLetters *self, int keys, int mode);
void CarriedLetters_OpenLetterMenu(CarriedLetters *self, int place);
void CarriedLetters_CancelChoice(CarriedLetters *self);
void CarriedLetters_ShowChoice(CarriedLetters *self);
void CarriedLetters_RunAction(CarriedLetters *self);
void CarriedLetters_BeginSwap(CarriedLetters *self, u8 target);
void CarriedLetters_BeginPutDown(CarriedLetters *self, u8 target);
void CarriedLetters_RunActionHold(CarriedLetters *self);
void CarriedLetters_BeginPressEnd(CarriedLetters *self);
void CarriedLetters_ShowCursorFirstOfSet(CarriedLetters *self);
void CarriedLetters_PlaceCursorSprite(CarriedLetters *self);
void CarriedLetters_PointAtFirstRow(CarriedLetters *self);
void CarriedLetters_GlideToRow(CarriedLetters *self);
void CarriedLetters_GlideToCursor(CarriedLetters *self);
void CarriedLetters_HideCursorSprite(CarriedLetters *self);
int CarriedLetters_CursorSpriteY(CarriedLetters *self);
int CarriedLetters_CursorSpriteX(CarriedLetters *self);
void CarriedLetters_ShowCursorAtCursor(CarriedLetters *self);
void CarriedLetters_SwapHeldWith(CarriedLetters *self, int place);
void CarriedLetters_PutHeldAt(CarriedLetters *self, int place);
void CarriedLetters_PickUpLetter(CarriedLetters *self, int place);
void CarriedLetters_FollowGlide(CarriedLetters *self);
void CarriedLetters_FollowCursorSprite(CarriedLetters *self);
void CarriedLetters_FollowTouch(CarriedLetters *self);
void CarriedLetters_DrawHeld(CarriedLetters *self);
void CarriedLetters_UpdatePopup(CarriedLetters *self);
void CarriedLetters_PlacePopup(CarriedLetters *self);
int CarriedLetters_PenHeldFor(CarriedLetters *self, int frames);
int CarriedLetters_TouchMoved(CarriedLetters *self);
void CarriedLetters_HighlightPlace(CarriedLetters *self, int place);
void CarriedLetters_ClearHighlights(CarriedLetters *self);
void CarriedLetters_SelectPlace(CarriedLetters *self, int place);
void CarriedLetters_ClearSelection(CarriedLetters *self);
int CarriedLetters_PlaceIsEmpty(CarriedLetters *self, int place);
int CarriedLetters_PlaceIsDimmed(CarriedLetters *self, int place);
void CarriedLetters_DimGrid(CarriedLetters *self);
int CarriedLetters_PlaceY(CarriedLetters *self, int place);
int CarriedLetters_PlaceX(CarriedLetters *self, int place);
Letter *CarriedLetters_PlaceLetter(CarriedLetters *self, int place);
void CarriedLetters_PutLetterAt(CarriedLetters *self, int place, Letter *letter);
int CarriedLetters_PutHeldLetterAt(CarriedLetters *self, int place);
int CarriedLetters_LetterPlaceAtTouch(CarriedLetters *self, int x, int y, int with_letter);
u8 CarriedLetters_LetterPlace(CarriedLetters *self, unsigned int index);
u8 CarriedLetters_LetterIndex(u8 unused, u8 place);
int CarriedLetters_IsLetterPlace(CarriedLetters *self, unsigned int place);
void CarriedLetters_EndLayerTask(CarriedLetters *self);
void CarriedLetters_GlideHeldTo(CarriedLetters *self, int place, int steps);
void CarriedLetters_PickUpWithCursor(CarriedLetters *self, int place);
void CarriedLetters_PickUpWithTouch(CarriedLetters *self, int place);
void CarriedLetters_TouchPlace(CarriedLetters *self, u8 place);
void CarriedLetters_EndAction(CarriedLetters *self);
void CarriedLetters_EndActionAtCursor(CarriedLetters *self);
void CarriedLetters_EndActionHidden(CarriedLetters *self);

void CarriedLetters_FollowLabelPress(CarriedLetters *self);
void CarriedLetters_WaitError(CarriedLetters *self);
void CarriedLetters_RunActionWhenIdle(CarriedLetters *self);
void CarriedLetters_CloseChoice(CarriedLetters *self);
void CarriedLetters_WaitChoiceShown(CarriedLetters *self);
void CarriedLetters_StepHeldGlide(CarriedLetters *self);
void CarriedLetters_FinishSwap(CarriedLetters *self);
void CarriedLetters_Swap(CarriedLetters *self);
void CarriedLetters_PutDown(CarriedLetters *self);
void CarriedLetters_FinishPickUp(CarriedLetters *self);
void CarriedLetters_PickUpAtCursor(CarriedLetters *self);
void CarriedLetters_FinishPlacePress(CarriedLetters *self);
void CarriedLetters_PressPlace(CarriedLetters *self);
void CarriedLetters_WaitCursorSprite(CarriedLetters *self);
void CarriedLetters_PickChoiceRow(CarriedLetters *self);
void CarriedLetters_ChooseByKeys(CarriedLetters *self);
void CarriedLetters_WaitLabelPress(CarriedLetters *self);
void CarriedLetters_LabelByKeys(CarriedLetters *self);
void CarriedLetters_MoveHeldByKeys(CarriedLetters *self);
void CarriedLetters_BrowseByKeys(CarriedLetters *self);
void CarriedLetters_ChooseByTouch(CarriedLetters *self);
void CarriedLetters_LabelByTouch(CarriedLetters *self);
void CarriedLetters_DragHeld(CarriedLetters *self);
void CarriedLetters_HoldTouchOnPlace(CarriedLetters *self);
void CarriedLetters_IdleByTouch(CarriedLetters *self);

int CarriedLetters_LoadWalletObjFiles(CarriedLetters *self);
void CarriedLetters_PrepareWallet(CarriedLetters *self);
void CarriedLetters_SetUpLayer(void);
void CarriedLetters_EndFrame(CarriedLetters *self);
void CarriedLetters_BeginFrame(CarriedLetters *self);
void CarriedLetters_EndInteractiveFrame(CarriedLetters *self);
void CarriedLetters_BeginInteractiveFrame(CarriedLetters *self);
void CarriedLetters_Teardown(CarriedLetters *self);
void CarriedLetters_Setup(CarriedLetters *self);
void CarriedLetters_LetterWipeOut(CarriedLetters *self);
void CarriedLetters_StartLetterWipeOut(CarriedLetters *self);
void CarriedLetters_LetterWipeIn(CarriedLetters *self);
void CarriedLetters_ShowLetter(CarriedLetters *self);
void CarriedLetters_SceneWipeOut(CarriedLetters *self);
void CarriedLetters_StartWipeOut(CarriedLetters *self);
void CarriedLetters_SceneWipeIn(CarriedLetters *self);
void CarriedLetters_StartWipeIn(CarriedLetters *self);
void CarriedLetters_StartSetup(CarriedLetters *self);
int CarriedLetters_End(CarriedLetters *self);
int CarriedLetters_Phase4Idle(void);
int CarriedLetters_Phase3Idle(void);
int CarriedLetters_RunInteractive(CarriedLetters *self);
void CarriedLetters_RunSubState(CarriedLetters *self);
int CarriedLetters_RunState(CarriedLetters *self);
int CarriedLetters_Draw(CarriedLetters *self);
int CarriedLetters_Close(CarriedLetters *self);
int CarriedLetters_Start(CarriedLetters *self);
CarriedLetters *CarriedLetters_New(void);

#endif
