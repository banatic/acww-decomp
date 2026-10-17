/* The scene of overlay 105 (vtable 0x0229fad0, include/cpp/ov105/Obj_ov105_0229fad0.h; its
 * profile at 0x0229f998 names the constructor func_ov105_0229f760): a menu scene
 * (ov002/menu_scene.h) that shows the letters the current player keeps (main/letter_store.h)
 * beside the ten letters they carry, as the evidence says:
 *
 * - its setup (LetterStorage_Setup) copies the 50 letters of PlayerRecord_KeptLetters for the
 *   current player into `stored`, and on delete (func_ov105_0229f1d0) copies them back when
 *   LETTER_STORAGE_FLAG_CHANGED is set (telling main so with GroupParams_SetC4C);
 * - the stored letters are seen as two pages of 25 (LETTER_STORE_PAGES, `page`), each with a
 *   tab drawn at the top (LetterStorage_DrawPageTabs) and its own background characters
 *   ("menu/inventory/b_itm_post0.bch" and "...post1.bch", data_ov105_0229f890);
 * - it is built on two of the objects of ov094's that the pockets scenes of overlays 096-100
 *   use (ov096/pockets_screen.h, ov099/pockets_view.h): the letters object at 0xd5c holds the
 *   ten carried letters and the page's 25 (func_ov094_0229b288 hands it the page), the grid at
 *   0x2fc is only highlighted and cleared here.
 *
 * The cursor walks the carried letters (2 columns of 5), the page (5 rows of 5), the two tabs
 * above the page and one more place below both (LetterStoragePlace). Picking a letter opens a
 * choice (ov002/paged_choice.h) whose rows carry an action (`action`, LetterStorage_RunAction);
 * a letter can be picked up, held (`held`) and put down on or swapped with another place's. */
#ifndef CLEAN_OV105_LETTER_STORAGE_H
#define CLEAN_OV105_LETTER_STORAGE_H

#include "main/letter.h"
#include "main/letter_store.h"
#include "main/letter_view.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/label_button.h"
#include "ov002/menu_scene.h"
#include "ov002/paged_choice.h"
#include "ov002/popup.h"
#include "types.h"

/* In `flags`. */
enum LetterStorageFlag {
    LETTER_STORAGE_FLAG_08 = 0x08,            /* the cursor sprite jumps to the cursor instead of easing
                                               * (LetterStorage_GlideToCursor), once */
    LETTER_STORAGE_FLAG_WRAPPED_LEFT = 0x10,  /* this move wrapped the cursor from the page's left edge
                                               * to the carried letters */
    LETTER_STORAGE_FLAG_WRAPPED_RIGHT = 0x20, /* this move wrapped it from the carried letters' right
                                               * column to the page */
    LETTER_STORAGE_FLAG_HELD_HIDDEN = 0x40,   /* the held letter is not drawn (LetterStorage_ShowPage) */
    LETTER_STORAGE_FLAG_80 = 0x80,
    LETTER_STORAGE_FLAG_100 = 0x100,        /* set by action 1 (LetterStorage_RunAction1) */
    LETTER_STORAGE_FLAG_PAGE_WIPE = 0x200,  /* a page's wipe in is running (LetterStorage_StartPageWipeIn) */
    LETTER_STORAGE_FLAG_FIXED_MENU = 0x800, /* the choice is LetterStorage_OpenFixedMenu's: its first
                                               * row is set apart */
    LETTER_STORAGE_FLAG_CHANGED = 0x1000    /* the stored letters are written back at the end
                                               * (LetterStorage_End) */
};

#define LETTER_STORAGE_FLAGS_WRAPPED (LETTER_STORAGE_FLAG_WRAPPED_LEFT | LETTER_STORAGE_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). The letters object of ov094's knows the
 * first 35 as its letters 0-34 (place - 0x1a, func_ov105_0229d718). */
enum LetterStoragePlace {
    LETTER_STORAGE_CARRIED_FIRST = 0x1a, /* 0x1a-0x23: the carried letters, 0x1a + row * 2 + column */
    LETTER_STORAGE_CARRIED_LAST = 0x23,
    LETTER_STORAGE_PAGE_FIRST = 0x24, /* 0x24-0x3c: the page's letters, 0x24 + row * 5 + column */
    LETTER_STORAGE_PAGE_LAST = 0x3c,
    LETTER_STORAGE_BELOW = 0x3d,     /* below the carried letters and the page (at 0xbc, 0xb6) */
    LETTER_STORAGE_TAB_FIRST = 0x3e, /* 0x3e-0x3f: the tabs of pages 0 and 1 */
    LETTER_STORAGE_TAB_LAST = 0x3f,
    LETTER_STORAGE_NO_PLACE = 0x40 /* `popup_place` before any (LetterStorage_Setup) */
};

#define LETTER_STORAGE_CARRIED_COLUMNS 2
#define LETTER_STORAGE_PAGE_COLUMNS 5
#define LETTER_STORAGE_ROWS 5
#define LETTER_STORAGE_TAB_OBJS 3 /* the OBJs of a tab (data_ov105_0229fa80) */

/* What the scene holds (`held_kind`). */
enum LetterStorageHeldKind {
    LETTER_STORAGE_HELD_NONE = 0,
    LETTER_STORAGE_HELD_LETTER = 1 /* a copy of the letter is at `held` */
};

/* The values of the choice rows (`action`), run by LetterStorage_RunAction. */
enum LetterStorageAction {
    LETTER_STORAGE_ACTION_0 = 0,       /* LetterStorage_RunAction0 */
    LETTER_STORAGE_ACTION_1 = 1,       /* LetterStorage_RunAction1 */
    LETTER_STORAGE_ACTION_PICK_UP = 2, /* LetterStorage_PickUpSlotLetter */
    LETTER_STORAGE_ACTION_MENU = 3,    /* LetterStorage_OpenFixedMenu */
    LETTER_STORAGE_ACTION_CANCEL = 4   /* func_ov105_0229db14 */
};

typedef struct LetterStorage {
    MenuScene base;                      /* 0x00 */
    u32 flags;                           /* 0x94: LetterStorageFlag */
    s32 objects_y;                       /* 0x98: the offset the ov094 objects are drawn at (LetterStorage_Draw) */
    s32 wipe_y;                          /* 0x9c: MenuScene_WipeOffsetY's */
    s32 wipe_x;                          /* 0xa0: MenuScene_WipeOffsetX's (LetterStorage_ScrollPageLayer); the tabs are
                               * drawn 0x80 right of it */
    s32 grab_dx;                         /* 0xa4: from the touch to the held letter */
    s32 grab_dy;                         /* 0xa8 */
    s32 held_x;                          /* 0xac: where the held letter is drawn */
    s32 held_y;                          /* 0xb0 */
    Letter held;                         /* 0xb4: the held letter's copy */
    Letter swapped;                      /* 0x1b4: the letter a swap took from its place */
    u8 held_kind;                        /* 0x2b4: LetterStorageHeldKind */
    u8 touch_place;                      /* 0x2b5: the place touched */
    u8 popup_place;                      /* 0x2b6: the place the popup tells of */
    u8 unk_2b7;                          /* 0x2b7: set with `held_from` by func_ov105_0229d908 */
    u8 held_page;                        /* 0x2b8: the page the held letter was taken from */
    u8 held_from;                        /* 0x2b9: the place it was taken from */
    u8 cursor;                           /* 0x2ba: LetterStoragePlace */
    u8 slot;                             /* 0x2bb: the place whose choice is open */
    u8 target;                           /* 0x2bc: the place the held letter is put down on or swapped at */
    u8 return_state;                     /* 0x2bd: the sub state to go back to */
    u8 action;                           /* 0x2be: LetterStorageAction */
    u8 choice_row;                       /* 0x2bf: the choice row the cursor sprite points at */
    u8 page;                             /* 0x2c0: the page shown, 0 or 1 */
    u8 unk_2c1;                          /* 0x2c1 */
    u8 unk_2c2;                          /* 0x2c2: picks LetterStorage_PressPanelButton4 over ...3 (func_ov105_0229db8c) */
    u8 open_delay;                       /* 0x2c3: frames before a touched place's choice opens (2) */
    u8 unk_2c4[0x38];                    /* 0x2c4: an object of main's (constructor func_020b9af4) */
    u8 grid[0xa60];                      /* 0x2fc: ov094's grid object (destructor func_ov094_0229afe0) */
    u8 letters[0x28];                    /* 0xd5c: ov094's letters object (func_ov094_0229bc30) */
    u8 wallet[0x1638];                   /* 0xd84: ov094's wallet display (destructor func_ov094_0229a2d0) */
    Popup popup;                         /* 0x23bc */
    Glide glide;                         /* 0x248c: the held letter's glide to a place */
    Glider cursor_sprite;                /* 0x24a4: a Glider0 */
    u8 choice[0x3e8];                    /* 0x2508: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;               /* 0x28f0 */
    u8 pad_28fb;                         /* 0x28fb */
    ErrorMessage error;                  /* 0x28fc */
    LetterView view;                     /* 0x2a18: shows a letter */
    LabelButton button;                  /* 0x2d40: a LabelButton0 */
    Letter stored[LETTER_STORE_LETTERS]; /* 0x2db8: the kept letters, page 0 then page 1 */
    ButtonPanel panel;                   /* 0x5fb8 */
} LetterStorage;

LetterStorage *LetterStorage_Destroy(LetterStorage *self);
LetterStorage *LetterStorage_Delete(LetterStorage *self);
void LetterStorage_ClearFlags(LetterStorage *self, unsigned int flags);
void LetterStorage_SetFlags(LetterStorage *self, unsigned int flags);
int LetterStorage_TestFlags(LetterStorage *self, int flags);
int LetterStorage_TurnPageByKeys(LetterStorage *self);
void LetterStorage_EndPanelDim(LetterStorage *self);
void LetterStorage_BeginPanelDim(LetterStorage *self);
void LetterStorage_ShowPage(LetterStorage *self);
int LetterStorage_PageTabAtTouch(LetterStorage *self, int x, int y);
void LetterStorage_StartPageWipeOut(LetterStorage *self);
void LetterStorage_StartPageWipeIn(LetterStorage *self);
void LetterStorage_DrawPageTabs(LetterStorage *self);
void LetterStorage_PressPanelButton4(LetterStorage *self);
void LetterStorage_PressPanelButton3(LetterStorage *self);
void LetterStorage_PressPanelButton9(LetterStorage *self);
void LetterStorage_DoNothing(LetterStorage *self);
void LetterStorage_RunActionMenu(LetterStorage *self);
void LetterStorage_PickUpSlotLetter(LetterStorage *self);
void LetterStorage_PressLabelButton(LetterStorage *self);
void LetterStorage_RunAction1(LetterStorage *self);
int LetterStorage_MoveCursor(LetterStorage *self, int keys, int mode);
void LetterStorage_MoveCursorInTabs(LetterStorage *self, int keys);
void LetterStorage_MoveCursorBelow(LetterStorage *self, int keys);
void LetterStorage_MoveCursorInPage(LetterStorage *self, int keys, int mode);
void LetterStorage_MoveCursorInCarried(LetterStorage *self, int keys, int mode);
void LetterStorage_OpenFixedMenu(LetterStorage *self);
void LetterStorage_OpenLetterMenu(LetterStorage *self, int place, int above_popup);
void LetterStorage_CancelChoice(LetterStorage *self);
void LetterStorage_ShowChoice(LetterStorage *self, int above_popup);
void LetterStorage_RunAction(LetterStorage *self);
void LetterStorage_BeginSubState13(LetterStorage *self, u8 target);
void LetterStorage_BeginSubState12(LetterStorage *self, char target);
void LetterStorage_RunAction0(LetterStorage *self);
void LetterStorage_BeginSubState0f(LetterStorage *self);
void LetterStorage_BeginSubState0e(LetterStorage *self);
void LetterStorage_ShowCursorFirstOfSet(LetterStorage *self);
void LetterStorage_PlaceCursorSprite(LetterStorage *self);
void LetterStorage_PointAtDefaultRow(LetterStorage *self);
void LetterStorage_PointAtLastRow(LetterStorage *self);
void LetterStorage_GlideToRow(LetterStorage *self);
void LetterStorage_EaseCursorSpriteTo(LetterStorage *self, int x, int y);
void LetterStorage_GlideToCursor(LetterStorage *self);
void LetterStorage_HideCursorSprite(LetterStorage *self);
int LetterStorage_CursorSpriteY(LetterStorage *self);
int LetterStorage_CursorSpriteX(LetterStorage *self);
void LetterStorage_ShowCursorAtCursor(LetterStorage *self);
void LetterStorage_SwapHeldWith(LetterStorage *self, int place);
void LetterStorage_PutHeldAt(LetterStorage *self, int place);
void LetterStorage_PickUpLetter(LetterStorage *self, int place);
void LetterStorage_FollowGlide(LetterStorage *self);
void LetterStorage_FollowCursorSprite(LetterStorage *self);
void LetterStorage_FollowTouch(LetterStorage *self);
void LetterStorage_DrawHeld(LetterStorage *self);
void LetterStorage_UpdatePopup(LetterStorage *self);
void LetterStorage_PlacePopup(LetterStorage *self);
int LetterStorage_TouchMoved(LetterStorage *self);
void LetterStorage_HighlightPlace(LetterStorage *self, int place);
void LetterStorage_ClearHighlights(LetterStorage *self);
void LetterStorage_SelectPlace(LetterStorage *self, int place);

/* More of `flags`: the touched place's letter may be dragged, as it is not marked
 * (LetterStorage_TouchPlace); the held letter glides to a tab (LetterStorage_GlideHeldTo). */
#define LETTER_STORAGE_FLAG_DRAGGABLE 0x04
#define LETTER_STORAGE_FLAG_GLIDE_TO_TAB 0x2000

/* The sub states, run from the table of LetterStorage_RunSubState; the ones handled here are named
 * by what their handler does. */
enum LetterStorageSubState {
    LETTER_STORAGE_SUB_TOUCH_IDLE = 0x00,      /* LetterStorage_IdleByTouch */
    LETTER_STORAGE_SUB_TOUCH_HOLD = 0x01,      /* LetterStorage_HoldTouchOnPlace */
    LETTER_STORAGE_SUB_TOUCH_CHOICE = 0x02,    /* LetterStorage_WatchChoiceTouch */
    LETTER_STORAGE_SUB_OPEN_TOUCHED = 0x03,    /* LetterStorage_OpenTouchedChoice */
    LETTER_STORAGE_SUB_DRAG = 0x04,            /* LetterStorage_DragHeld */
    LETTER_STORAGE_SUB_LABEL_BY_TOUCH = 0x05,  /* LetterStorage_LabelByTouch */
    LETTER_STORAGE_SUB_CHOICE_BY_TOUCH = 0x06, /* LetterStorage_ChooseByTouch */
    LETTER_STORAGE_SUB_BROWSE = 0x07,          /* LetterStorage_BrowseByKeys */
    LETTER_STORAGE_SUB_HOLD = 0x08,            /* LetterStorage_MoveHeldByKeys */
    LETTER_STORAGE_SUB_LABEL_BY_KEYS = 0x09,   /* LetterStorage_LabelByKeys */
    LETTER_STORAGE_SUB_LABEL_PRESS = 0x0a,     /* LetterStorage_WaitLabelPress */
    LETTER_STORAGE_SUB_CHOICE_BY_KEYS = 0x0b,  /* LetterStorage_ChooseByKeys */
    LETTER_STORAGE_SUB_CHOICE_PICK = 0x0c,     /* LetterStorage_PickChoiceRow */
    LETTER_STORAGE_SUB_SPRITE_MOVE = 0x0d,     /* LetterStorage_WaitCursorSprite */
    LETTER_STORAGE_SUB_PLACE_PRESS = 0x0e,     /* LetterStorage_PressPlace */
    LETTER_STORAGE_SUB_PRESS_END = 0x0f,       /* LetterStorage_FinishPlacePress */
    LETTER_STORAGE_SUB_PICK_UP = 0x10,         /* LetterStorage_PickUpAtCursor */
    LETTER_STORAGE_SUB_PICK_UP_END = 0x11,     /* LetterStorage_FinishPickUp */
    LETTER_STORAGE_SUB_PUT_DOWN = 0x12,        /* LetterStorage_PutDown */
    LETTER_STORAGE_SUB_SWAP = 0x13,            /* LetterStorage_Swap */
    LETTER_STORAGE_SUB_SWAP_END = 0x14,        /* LetterStorage_FinishSwap */
    LETTER_STORAGE_SUB_HELD_GLIDE = 0x15,      /* LetterStorage_StepHeldGlide */
    LETTER_STORAGE_SUB_CHOICE_OPEN = 0x16,     /* LetterStorage_WaitChoiceShown */
    LETTER_STORAGE_SUB_CHOICE_CLOSE = 0x17,    /* LetterStorage_CloseChoice */
    LETTER_STORAGE_SUB_CHOICE_RUN = 0x18,      /* LetterStorage_RunActionWhenIdle */
    LETTER_STORAGE_SUB_ERROR = 0x19,           /* LetterStorage_WaitError */
    LETTER_STORAGE_SUB_LABEL_PRESSED = 0x1a,   /* LetterStorage_FollowLabelPress */
    LETTER_STORAGE_SUB_PANEL_PRESSED = 0x1b,   /* LetterStorage_FollowPanelPress */
    LETTER_STORAGE_SUB_LET_GO = 0x1c,          /* LetterStorage_WaitLetGo */
    LETTER_STORAGE_SUB_PANEL_BY_TOUCH = 0x1d,  /* LetterStorage_ChoosePanelButtonByTouch */
    LETTER_STORAGE_SUB_PANEL_BY_KEYS = 0x1e,   /* LetterStorage_ChoosePanelButtonByKeys */
    LETTER_STORAGE_SUB_PANEL_PRESS = 0x1f      /* LetterStorage_PressChosenPanelButton */
};

void LetterStorage_ClearSelection(LetterStorage *self);
int LetterStorage_PlaceIsEmpty(LetterStorage *self, int place);
int LetterStorage_PlaceIsMarked(LetterStorage *self, int place);
void LetterStorage_MarkCarriedLetters(LetterStorage *self);
int LetterStorage_PlaceY(LetterStorage *self, int place);
int LetterStorage_PlaceX(LetterStorage *self, int place);
Letter *LetterStorage_PlaceLetter(LetterStorage *self, int place);
void LetterStorage_PutLetterAt(LetterStorage *self, int place, Letter *letter);
int LetterStorage_PutHeldLetterAt(LetterStorage *self, int place);
int LetterStorage_LetterPlaceAtTouch(LetterStorage *self, int x, int y, int with_letter);
u8 LetterStorage_LetterPlace(LetterStorage *self, unsigned int index);
u8 LetterStorage_LetterIndex(LetterStorage *self, unsigned int place);
int LetterStorage_IsTabPlace(LetterStorage *self, int place);
int LetterStorage_IsBelowPlace(LetterStorage *self, int place);
int LetterStorage_IsPagePlace(LetterStorage *self, unsigned int place);
int LetterStorage_IsCarriedPlace(LetterStorage *self, unsigned int place);
void LetterStorage_EndLayerTask(LetterStorage *self);
u8 LetterStorage_FirstEmptyPagePlace(LetterStorage *self);
int LetterStorage_FreeCarriedPlace(LetterStorage *self);
void LetterStorage_HoldAndGlide(LetterStorage *self, int from, int to);
void LetterStorage_DropHeldAtTouch(LetterStorage *self, int place, int x);
void LetterStorage_GlideHeldTo(LetterStorage *self, int place, int steps);
void LetterStorage_PickUpWithCursor(LetterStorage *self, u8 place);
void LetterStorage_PickUpWithTouch(LetterStorage *self, u8 place);
void LetterStorage_TouchPlace(LetterStorage *self, int place);
void LetterStorage_OfferPanelButtons(LetterStorage *self);
void LetterStorage_OfferPanelButtonsByKeys(LetterStorage *self);
void LetterStorage_OfferPanelButtonsByTouch(LetterStorage *self);
void LetterStorage_EndAction(LetterStorage *self);
void LetterStorage_EndActionAtCursor(LetterStorage *self);
void LetterStorage_EndActionHidden(LetterStorage *self);
void LetterStorage_PressChosenPanelButton(LetterStorage *self);
void LetterStorage_ChoosePanelButtonByKeys(LetterStorage *self);
void LetterStorage_ChoosePanelButtonByTouch(LetterStorage *self);
void LetterStorage_WaitLetGo(LetterStorage *self);
void LetterStorage_FollowPanelPress(LetterStorage *self);
void LetterStorage_FollowLabelPress(LetterStorage *self);
void LetterStorage_WaitError(LetterStorage *self);
void LetterStorage_RunActionWhenIdle(LetterStorage *self);
void LetterStorage_CloseChoice(LetterStorage *self);
void LetterStorage_WaitChoiceShown(LetterStorage *self);
void LetterStorage_StepHeldGlide(LetterStorage *self);
void LetterStorage_FinishSwap(LetterStorage *self);
void LetterStorage_Swap(LetterStorage *self);
void LetterStorage_PutDown(LetterStorage *self);
void LetterStorage_FinishPickUp(LetterStorage *self);
void LetterStorage_PickUpAtCursor(LetterStorage *self);
void LetterStorage_FinishPlacePress(LetterStorage *self);
void LetterStorage_PressPlace(LetterStorage *self);
void LetterStorage_WaitCursorSprite(LetterStorage *self);
void LetterStorage_PickChoiceRow(LetterStorage *self);
void LetterStorage_ChooseByKeys(LetterStorage *self);
void LetterStorage_WaitLabelPress(LetterStorage *self);
void LetterStorage_LabelByKeys(LetterStorage *self);
void LetterStorage_MoveHeldByKeys(LetterStorage *self);
void LetterStorage_BrowseByKeys(LetterStorage *self);
void LetterStorage_ChooseByTouch(LetterStorage *self);
void LetterStorage_LabelByTouch(LetterStorage *self);
void LetterStorage_DragHeld(LetterStorage *self);
void LetterStorage_OpenTouchedChoice(LetterStorage *self);

/* Still more of `flags`: the scene is drawn (LetterStorage_Draw), and with it the panel and the
 * objects of ov094's at their offsets; FLAG_80 draws the label button over a letter shown
 * (LetterStorage_ShowLetter); FLAG_100 (action 1) shows the letter instead of ending the scene
 * once the scene has wiped out (LetterStorage_SceneWipeOut). */
#define LETTER_STORAGE_FLAG_DRAWN 0x01
#define LETTER_STORAGE_FLAG_OBJECTS_DRAWN 0x02

/* The states, run from the table of LetterStorage_RunState (MenuScene_SetState). */
enum LetterStorageState {
    LETTER_STORAGE_STATE_START_SETUP = 0x00,           /* LetterStorage_StartSetup */
    LETTER_STORAGE_STATE_START_WIPE_IN = 0x01,         /* LetterStorage_StartWipeIn */
    LETTER_STORAGE_STATE_SCENE_WIPE_IN = 0x02,         /* LetterStorage_SceneWipeIn */
    LETTER_STORAGE_STATE_PAGE_WIPE_IN = 0x03,          /* LetterStorage_PageWipeIn */
    LETTER_STORAGE_STATE_START_WIPE_OUT = 0x04,        /* LetterStorage_StartWipeOut */
    LETTER_STORAGE_STATE_PAGE_WIPE_OUT = 0x05,         /* LetterStorage_PageWipeOut */
    LETTER_STORAGE_STATE_SCENE_WIPE_OUT = 0x06,        /* LetterStorage_SceneWipeOut */
    LETTER_STORAGE_STATE_SHOW_LETTER = 0x07,           /* LetterStorage_ShowLetter */
    LETTER_STORAGE_STATE_LETTER_WIPE_IN = 0x08,        /* LetterStorage_LetterWipeIn */
    LETTER_STORAGE_STATE_START_LETTER_WIPE_OUT = 0x09, /* LetterStorage_StartLetterWipeOut */
    LETTER_STORAGE_STATE_LETTER_WIPE_OUT = 0x0a,       /* LetterStorage_LetterWipeOut */
    LETTER_STORAGE_STATE_START_PAGE_TURN = 0x0b,       /* LetterStorage_StartPageTurn */
    LETTER_STORAGE_STATE_PAGE_TURN_OUT = 0x0c,         /* LetterStorage_PageTurnOut */
    LETTER_STORAGE_STATE_PAGE_TURN_IN = 0x0d,          /* LetterStorage_PageTurnIn */
    LETTER_STORAGE_STATE_START_PROMPT = 0x0e,          /* LetterStorage_StartPrompt */
    LETTER_STORAGE_STATE_PROMPT_WIPE_OUT = 0x0f,       /* LetterStorage_PromptWipeOut */
    LETTER_STORAGE_STATE_SHOW_PROMPT = 0x10,           /* LetterStorage_ShowPrompt */
    LETTER_STORAGE_STATE_PROMPT_WIPE_IN = 0x11,        /* LetterStorage_PromptWipeIn */
    LETTER_STORAGE_STATE_CLOSE_PROMPT = 0x12,          /* LetterStorage_ClosePrompt */
    LETTER_STORAGE_STATE_PROMPT_CLOSE_WIPE = 0x13,     /* LetterStorage_PromptCloseWipe */
    LETTER_STORAGE_STATE_RESTORE_PANEL = 0x14,         /* LetterStorage_RestorePanel */
    LETTER_STORAGE_STATE_PANEL_WIPE_IN = 0x15,         /* LetterStorage_PanelWipeIn */
    LETTER_STORAGE_STATES = 0x16
};

#define LETTER_STORAGE_SUB_STATES 0x20

void LetterStorage_WatchChoiceTouch(LetterStorage *self);
void LetterStorage_HoldTouchOnPlace(LetterStorage *self);
void LetterStorage_IdleByTouch(LetterStorage *self);
void LetterStorage_PreparePanel(LetterStorage *self);
void LetterStorage_LoadPageLayer(LetterStorage *self);
void LetterStorage_PrepareWallet(LetterStorage *self);
void LetterStorage_SetUpLayers(void);
void LetterStorage_EndFrame(LetterStorage *self);
void LetterStorage_BeginFrame(LetterStorage *self);
void LetterStorage_EndInteractiveFrame(LetterStorage *self);
int LetterStorage_BeginInteractiveFrame(LetterStorage *self);
void LetterStorage_Teardown(LetterStorage *self);
void LetterStorage_Setup(LetterStorage *self);
void LetterStorage_PanelWipeIn(LetterStorage *self);
void LetterStorage_RestorePanel(LetterStorage *self);
void LetterStorage_PromptCloseWipe(LetterStorage *self);
void LetterStorage_ClosePrompt(LetterStorage *self);
void LetterStorage_PromptWipeIn(LetterStorage *self);
void LetterStorage_ShowPrompt(LetterStorage *self);
void LetterStorage_PromptWipeOut(LetterStorage *self);
void LetterStorage_StartPrompt(LetterStorage *self);
void LetterStorage_ScrollPageLayer(LetterStorage *self);
void LetterStorage_ScrollSceneLayer(LetterStorage *self);
void LetterStorage_ScrollLetterLayers(LetterStorage *self);
void LetterStorage_PageTurnIn(LetterStorage *self);
void LetterStorage_PageTurnOut(LetterStorage *self);
void LetterStorage_StartPageTurn(LetterStorage *self);
void LetterStorage_LetterWipeOut(LetterStorage *self);
void LetterStorage_StartLetterWipeOut(LetterStorage *self);
void LetterStorage_LetterWipeIn(LetterStorage *self);
void LetterStorage_ShowLetter(LetterStorage *self);
void LetterStorage_SceneWipeOut(LetterStorage *self);
void LetterStorage_PageWipeOut(LetterStorage *self);
void LetterStorage_StartWipeOut(LetterStorage *self);
void LetterStorage_PageWipeIn(LetterStorage *self);
void LetterStorage_SceneWipeIn(LetterStorage *self);
void LetterStorage_StartWipeIn(LetterStorage *self);
void LetterStorage_StartSetup(LetterStorage *self);
int LetterStorage_End(LetterStorage *self);
int LetterStorage_Phase1Idle(void);
int LetterStorage_Phase0Idle(void);
int LetterStorage_RunInteractive(LetterStorage *self);
void LetterStorage_RunSubState(LetterStorage *self);
int LetterStorage_RunState(LetterStorage *self);
int LetterStorage_Draw(LetterStorage *self);
int LetterStorage_Close(LetterStorage *self);
int LetterStorage_Start(LetterStorage *self);
LetterStorage *LetterStorage_New(void);

#endif
