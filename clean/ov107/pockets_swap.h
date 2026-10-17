/* The scene of overlay 107 (vtable 0x0229e3b8, include/cpp/ov107/Obj_ov107_0229e3b8.h;
 * constructor PocketsSwap_New, 0x29f4 bytes): a menu scene (ov002/menu_scene.h) that overlay 92's
 * dispatcher opens for modes 0x29-0x2c (ov092/menu_dispatch.c). Those are the modes main's
 * GroupParams_OpenWithItem29, ...2a, ...2b and ...WithItemAndObject open group 9 in, with an
 * item the player's actor is getting (GroupParams_ItemC): the field actor states pass a picked
 * up item (0x29, 0x2a), a caught insect (0x2b, item 0x12b0 + its kind) and a hooked fish (0x2c,
 * the fish object kept as GroupParams_C80).
 *
 * The scene shows the current player's pockets with ov094's grid of 15 places (3 rows of 5),
 * its letters and the wallet, as ov099's pockets view does (ov099/pockets_view.h), and one more
 * place below the grid (PocketsSwap_PlaceX). Picking a pocket item opens a choice
 * (ov002/paged_choice.h) of what to do with it (PocketsSwapAction, PocketsSwap_AddEntries):
 * release it when it is an insect (into the field, TownInsect_LetGo) or a fish (into water ahead,
 * PlayerFish_PlaceFromPockets), drop it on the ground (TileRequests_AskAtActorTile or
 * TileRequests_AskDrop12), or in mode 0x2a a tile operation (TileRequests_AskAtActorTileOp 2).
 * Once that is done the item the scene was opened with takes the pocket item's place
 * (PocketsSwap_TakeNewItem) and the scene closes with GroupParams_SetC4C(1); the place below the
 * grid and B close it without a swap (panel button 9, GroupParams_SetC4C(0)).
 *
 * Like ov099's, the scene runs by the touch (sub states 0-4, the cursor sprite hidden) or by the
 * keys (sub states 5-0x0a), as state flag 2 says (StateFlags_Test2, StateFlags_IsClear2). */
#ifndef CLEAN_OV107_POCKETS_SWAP_H
#define CLEAN_OV107_POCKETS_SWAP_H

#include "autoload_2/vector.h"
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
enum PocketsSwapFlag {
    POCKETS_SWAP_FLAG_DRAWN = 0x01,         /* the scene is drawn (PocketsSwap_Draw) */
    POCKETS_SWAP_FLAG_OBJECTS_DRAWN = 0x02, /* the panel, the grid, the letters and the wallet too */
    POCKETS_SWAP_FLAG_JUMP_SPRITE = 0x04,   /* the cursor sprite jumps to the cursor instead of easing,
                                             * once (PocketsSwap_GlideToCursor); never set here */
    POCKETS_SWAP_FLAG_WRAPPED_LEFT = 0x08,  /* this move wrapped the cursor over the grid's left edge */
    POCKETS_SWAP_FLAG_WRAPPED_RIGHT = 0x10, /* this move wrapped it over the right edge */
    POCKETS_SWAP_FLAG_HELD_HIDDEN = 0x20,   /* the held item is not drawn (PocketsSwap_DrawHeld) */
    POCKETS_SWAP_FLAG_WATER = 0x40          /* the setup found where a fish can go (PocketsSwap_FindWater):
                                             * fish are not dimmed */
};

#define POCKETS_SWAP_FLAGS_WRAPPED (POCKETS_SWAP_FLAG_WRAPPED_LEFT | POCKETS_SWAP_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). */
enum PocketsSwapPlace {
    POCKETS_SWAP_GRID_FIRST = 0x00, /* 0-14: the grid, row * 5 + column */
    POCKETS_SWAP_GRID_LAST = 0x0e,
    POCKETS_SWAP_BELOW = 0x0f,   /* below the grid (at 0xbc, 0xb6): panel button 9 */
    POCKETS_SWAP_NO_PLACE = 0x10 /* `popup_place` before any; PocketsSwap_PlaceAtTouch's none */
};

#define POCKETS_SWAP_COLUMNS 5
#define POCKETS_SWAP_ROWS 3

/* What the scene holds (`held_kind`): this overlay only ever clears it. */
enum PocketsSwapHeldKind {
    POCKETS_SWAP_HELD_NONE = 0,
    POCKETS_SWAP_HELD_ITEM = 1 /* drawn at `held_x`, `held_y` (PocketsSwap_DrawHeld) */
};

/* The values of the choice rows (`action`), run by PocketsSwap_RunAction. */
enum PocketsSwapAction {
    POCKETS_SWAP_ACTION_RELEASE_INSECT = 0, /* PocketsSwap_RunActionReleaseInsect */
    POCKETS_SWAP_ACTION_DROP = 1,           /* PocketsSwap_RunActionDrop */
    POCKETS_SWAP_ACTION_RELEASE_FISH = 2,   /* PocketsSwap_RunActionReleaseFish */
    POCKETS_SWAP_ACTION_TILE_OP = 3,        /* PocketsSwap_RunActionTileOp */
    POCKETS_SWAP_ACTION_CANCEL = 4          /* PocketsSwap_EndAction */
};

/* The sub states, run from the table of PocketsSwap_RunSubState (MenuScene_SetSubState), named
 * by what their handler does. */
enum PocketsSwapSubState {
    POCKETS_SWAP_SUB_TOUCH_IDLE = 0x00,      /* PocketsSwap_IdleByTouch */
    POCKETS_SWAP_SUB_TOUCH_HOLD = 0x01,      /* PocketsSwap_HoldTouchOnPlace */
    POCKETS_SWAP_SUB_TOUCH_RELEASE = 0x02,   /* PocketsSwap_WaitTouchRelease */
    POCKETS_SWAP_SUB_OPEN_TOUCHED = 0x03,    /* PocketsSwap_OpenTouchedChoice */
    POCKETS_SWAP_SUB_CHOICE_BY_TOUCH = 0x04, /* PocketsSwap_ChooseByTouch */
    POCKETS_SWAP_SUB_BROWSE = 0x05,          /* PocketsSwap_BrowseByKeys */
    POCKETS_SWAP_SUB_CHOICE_BY_KEYS = 0x06,  /* PocketsSwap_ChooseByKeys */
    POCKETS_SWAP_SUB_CHOICE_PICK = 0x07,     /* PocketsSwap_PickChoiceRow */
    POCKETS_SWAP_SUB_SPRITE_MOVE = 0x08,     /* PocketsSwap_WaitCursorSprite */
    POCKETS_SWAP_SUB_BELOW_PRESS = 0x09,     /* PocketsSwap_WaitBelowPress */
    POCKETS_SWAP_SUB_SPRITE_ANIM = 0x0a,     /* PocketsSwap_WaitSpriteAnim */
    POCKETS_SWAP_SUB_CHOICE_OPEN = 0x0b,     /* PocketsSwap_WaitChoiceShown */
    POCKETS_SWAP_SUB_CHOICE_CLOSE = 0x0c,    /* PocketsSwap_CloseChoice */
    POCKETS_SWAP_SUB_CHOICE_RUN = 0x0d,      /* PocketsSwap_RunActionWhenIdle */
    POCKETS_SWAP_SUB_ERROR = 0x0e,           /* PocketsSwap_WaitError */
    POCKETS_SWAP_SUB_PANEL_PRESSED = 0x0f,   /* PocketsSwap_FollowPanelPress */
    POCKETS_SWAP_SUB_RELEASE_INSECT = 0x10,  /* PocketsSwap_ReleaseInsect */
    POCKETS_SWAP_SUB_RELEASE_FISH = 0x11,    /* PocketsSwap_ReleaseFish */
    POCKETS_SWAP_SUB_INSECT_GONE = 0x12,     /* PocketsSwap_WaitInsectGone */
    POCKETS_SWAP_SUB_FINISH_DELAY = 0x13,    /* PocketsSwap_FinishAfterDelay */
    POCKETS_SWAP_SUB_FINISH_PLAYER = 0x14,   /* PocketsSwap_FinishWithPlayer */
    POCKETS_SWAP_SUB_DROP_CARRY = 0x15,      /* PocketsSwap_WaitDropCarried */
    POCKETS_SWAP_SUB_TILE_ANSWER = 0x16,     /* PocketsSwap_WaitTileAnswer */
    POCKETS_SWAP_SUB_TILE_PLAYER = 0x17,     /* PocketsSwap_SendPlayerToTile */
    POCKETS_SWAP_SUB_STATES = 0x18
};

/* The states, run from the table of PocketsSwap_RunState (MenuScene_SetState). */
enum PocketsSwapState {
    POCKETS_SWAP_STATE_START_SETUP = 0x00,    /* PocketsSwap_StartSetup */
    POCKETS_SWAP_STATE_START_WIPE_IN = 0x01,  /* PocketsSwap_StartWipeIn */
    POCKETS_SWAP_STATE_WIPE_IN = 0x02,        /* PocketsSwap_WipeIn */
    POCKETS_SWAP_STATE_START_WIPE_OUT = 0x03, /* PocketsSwap_StartWipeOut */
    POCKETS_SWAP_STATE_WIPE_OUT = 0x04,       /* PocketsSwap_WipeOut */
    POCKETS_SWAP_STATES = 0x05
};

/* The phases the scene sets (ov092/menu_dispatch.h's mapping: phase 1 runs the states by the
 * vtable's slot 0x4c, 2 the interactive frame by 0x50, 5 the delete by 0x5c). */
enum PocketsSwapPhase {
    POCKETS_SWAP_PHASE_START = 0,
    POCKETS_SWAP_PHASE_STATES = 1,
    POCKETS_SWAP_PHASE_INTERACTIVE = 2,
    POCKETS_SWAP_PHASE_DELETE = 5
};

typedef struct PocketsSwap {
    MenuScene base;         /* 0x00 */
    u32 flags;              /* 0x94: PocketsSwapFlag */
    s32 objects_y;          /* 0x98: MenuScene_WipeOffsetY's, where the objects are drawn */
    s32 grab_dx;            /* 0x9c: from the touch to the touched place */
    s32 grab_dy;            /* 0xa0 */
    s32 held_x;             /* 0xa4: where the held item is drawn */
    s32 held_y;             /* 0xa8 */
    s32 request;            /* 0xac: the tile request asked for (main/tile_requests.h), -1 for none */
    u8 unk_b0[5];           /* 0xb0 */
    u8 held_kind;           /* 0xb5: PocketsSwapHeldKind */
    u8 touch_place;         /* 0xb6: the place touched */
    u8 popup_place;         /* 0xb7: the place the popup tells of */
    u8 cursor;              /* 0xb8: PocketsSwapPlace */
    u8 slot;                /* 0xb9: the place whose choice is open (the pocket item given up) */
    u8 unk_ba;              /* 0xba */
    u8 return_state;        /* 0xbb: the sub state to go back to */
    u8 action;              /* 0xbc: PocketsSwapAction */
    u8 choice_row;          /* 0xbd: the choice row the cursor sprite points at */
    u8 delay;               /* 0xbe: frames before the scene finishes */
    u8 open_delay;          /* 0xbf: frames before a touched place's choice opens (2) */
    Vec3 point;             /* 0xc0: where water was found or a fish goes */
    s32 tile_x;             /* 0xcc: the tile the player is sent to (PocketsSwap_RunActionTileOp) */
    s32 tile_z;             /* 0xd0 */
    LayerTaskPair task;     /* 0xd4: ended each frame (PocketsSwap_EndLayerTask) */
    PocketsGrid grid;       /* 0x10c */
    PocketsLetters letters; /* 0xb6c */
    PocketsWallet wallet;   /* 0xb94 */
    Popup popup;            /* 0x21cc */
    Glide glide;            /* 0x229c */
    Glider cursor_sprite;   /* 0x22b4: a Glider0 */
    u8 choice[0x3e8];       /* 0x2318: a PagedChoice (whose structure is not all known) */
    ChoiceEntries entries;  /* 0x2700 */
    u8 pad_270b;            /* 0x270b */
    ErrorMessage error;     /* 0x270c */
    ButtonPanel panel;      /* 0x2828 */
} PocketsSwap;

PocketsSwap *PocketsSwap_Destroy(PocketsSwap *self);
PocketsSwap *PocketsSwap_Delete(PocketsSwap *self);
void PocketsSwap_ClearFlags(PocketsSwap *self, unsigned int flags);
void PocketsSwap_SetFlags(PocketsSwap *self, unsigned int flags);
unsigned int PocketsSwap_TestFlags(PocketsSwap *self, unsigned int flags);
void PocketsSwap_EndGetting(PocketsSwap *self, int free_tile);
int PocketsSwap_OwnSlot(PocketsSwap *self);
void PocketsSwap_SendPlayerToTile(PocketsSwap *self);
void PocketsSwap_WaitTileAnswer(PocketsSwap *self);
void PocketsSwap_RunActionTileOp(PocketsSwap *self);
void PocketsSwap_SendFishPoint(PocketsSwap *self, int kind);
void PocketsSwap_ReleaseFish(PocketsSwap *self);
void PocketsSwap_RunActionReleaseFish(PocketsSwap *self);
int PocketsSwap_FindWater(PocketsSwap *self);
void PocketsSwap_SendInsectRelease(PocketsSwap *self, int kind, int turn);
void PocketsSwap_ReleaseInsect(PocketsSwap *self);
void PocketsSwap_RunActionReleaseInsect(PocketsSwap *self);
void PocketsSwap_WaitDropCarried(PocketsSwap *self);
void PocketsSwap_RunActionDrop(PocketsSwap *self);
int PocketsSwap_MoveCursor(PocketsSwap *self, int keys);
void PocketsSwap_MoveCursorInGrid(PocketsSwap *self, int keys);
void PocketsSwap_OpenChoice(PocketsSwap *self, int place, int above_popup);
void PocketsSwap_AddEntries(PocketsSwap *self);
void PocketsSwap_TakeNewItem(PocketsSwap *self);
void PocketsSwap_PressBelow(PocketsSwap *self);
void PocketsSwap_Finish(PocketsSwap *self);
void PocketsSwap_CancelChoice(PocketsSwap *self);
void PocketsSwap_ShowChoice(PocketsSwap *self, int above_popup);
void PocketsSwap_RunAction(PocketsSwap *self);
void PocketsSwap_ShowCursorSecondOfSet(PocketsSwap *self);
void PocketsSwap_ShowCursorFirstOfSet(PocketsSwap *self);
void PocketsSwap_PlaceCursorSprite(PocketsSwap *self);
void PocketsSwap_PointAtFirstRow(PocketsSwap *self);
void PocketsSwap_PointAtLastRow(PocketsSwap *self);
void PocketsSwap_GlideToRow(PocketsSwap *self);
void PocketsSwap_GlideToCursor(PocketsSwap *self);
void PocketsSwap_HideCursorSprite(PocketsSwap *self);
int PocketsSwap_CursorSpriteY(PocketsSwap *self);
int PocketsSwap_CursorSpriteX(PocketsSwap *self);
void PocketsSwap_ShowCursorAtCursor(PocketsSwap *self);
void PocketsSwap_DrawHeld(PocketsSwap *self);
void PocketsSwap_UpdatePopup(PocketsSwap *self);
void PocketsSwap_PlacePopup(PocketsSwap *self);
void PocketsSwap_SelectPlace(PocketsSwap *self, int place);
void PocketsSwap_ClearSelection(PocketsSwap *self);
int PocketsSwap_PlaceItemState(PocketsSwap *self, int place);
int PocketsSwap_PlaceItem(PocketsSwap *self, int place);
int PocketsSwap_PlaceIsEmpty(PocketsSwap *self, int place);
int PocketsSwap_PlaceIsDimmed(PocketsSwap *self, int place);
int PocketsSwap_PlaceIsKept(PocketsSwap *self, int place);
void PocketsSwap_DimKeptPlaces(PocketsSwap *self);
int PocketsSwap_PlaceY(PocketsSwap *self, int place);
int PocketsSwap_PlaceX(PocketsSwap *self, int place);
void PocketsSwap_SetPlaceItem(PocketsSwap *self, int place, int item, int state);
int PocketsSwap_PlaceAtTouch(PocketsSwap *self, int x, int y, int with_item);
u8 PocketsSwap_GridPlace(PocketsSwap *self, unsigned int index);
int PocketsSwap_GridIndex(PocketsSwap *self, int place);
int PocketsSwap_IsGridPlace(PocketsSwap *self, unsigned int place);
void PocketsSwap_EndLayerTask(PocketsSwap *self);
void PocketsSwap_ShowMessage(PocketsSwap *self, u8 message, u8 return_state);
void PocketsSwap_TouchPlace(PocketsSwap *self, int place);
void PocketsSwap_EndAction(PocketsSwap *self);
void PocketsSwap_EndActionAtCursor(PocketsSwap *self);
void PocketsSwap_EndActionHidden(PocketsSwap *self);
void PocketsSwap_FinishWithPlayer(PocketsSwap *self);
void PocketsSwap_FinishAfterDelay(PocketsSwap *self);
void PocketsSwap_WaitInsectGone(PocketsSwap *self);
void PocketsSwap_FollowPanelPress(PocketsSwap *self);
void PocketsSwap_WaitError(PocketsSwap *self);
void PocketsSwap_RunActionWhenIdle(PocketsSwap *self);
void PocketsSwap_CloseChoice(PocketsSwap *self);
void PocketsSwap_WaitChoiceShown(PocketsSwap *self);
void PocketsSwap_WaitSpriteAnim(PocketsSwap *self);
void PocketsSwap_WaitBelowPress(PocketsSwap *self);
void PocketsSwap_WaitCursorSprite(PocketsSwap *self);
void PocketsSwap_PickChoiceRow(PocketsSwap *self);
void PocketsSwap_ChooseByKeys(PocketsSwap *self);
void PocketsSwap_BrowseByKeys(PocketsSwap *self);
void PocketsSwap_ChooseByTouch(PocketsSwap *self);
void PocketsSwap_OpenTouchedChoice(PocketsSwap *self);
void PocketsSwap_WaitTouchRelease(PocketsSwap *self);
void PocketsSwap_HoldTouchOnPlace(PocketsSwap *self);
void PocketsSwap_IdleByTouch(PocketsSwap *self);
void PocketsSwap_LoadObjFiles(PocketsSwap *self);
void PocketsSwap_PrepareWallet(PocketsSwap *self);
void PocketsSwap_SetUpLayer6(void);
void PocketsSwap_EndFrame(PocketsSwap *self);
void PocketsSwap_BeginFrame(PocketsSwap *self);
void PocketsSwap_EndInteractiveFrame(PocketsSwap *self);
void PocketsSwap_BeginInteractiveFrame(PocketsSwap *self);
void PocketsSwap_Teardown(PocketsSwap *self);
void PocketsSwap_Setup(PocketsSwap *self);
void PocketsSwap_WipeOut(PocketsSwap *self);
void PocketsSwap_StartWipeOut(PocketsSwap *self);
void PocketsSwap_WipeIn(PocketsSwap *self);
void PocketsSwap_StartWipeIn(PocketsSwap *self);
void PocketsSwap_StartSetup(PocketsSwap *self);
int PocketsSwap_RequestDelete(PocketsSwap *self);
int PocketsSwap_Phase1Idle(void);
int PocketsSwap_Phase0Idle(void);
int PocketsSwap_RunInteractive(PocketsSwap *self);
void PocketsSwap_RunSubState(PocketsSwap *self);
int PocketsSwap_RunState(PocketsSwap *self);
int PocketsSwap_Draw(PocketsSwap *self);
int PocketsSwap_Close(PocketsSwap *self);
int PocketsSwap_Start(PocketsSwap *self);
PocketsSwap *PocketsSwap_New(void);

#endif
