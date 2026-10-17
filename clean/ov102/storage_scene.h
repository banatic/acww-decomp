/* The scene of overlay 102 (vtable 0x0229ea60, include/cpp/ov102/Obj_ov102_0229ea60.h; its
 * profile at 0x0229e9e8 names the constructor StorageScene_New, 0x25ac bytes): the screen of the
 * town's item storage (main/player_storage.h), which ov092's dispatcher (ov092/menu_dispatch.h)
 * starts for GroupParams mode 0x22 (overlay group 0x13). Overlay 4's chests open group 9 in that
 * mode (ov004/chest.h, Chest_EnterMenu). As the evidence says:
 *
 * - its setup (StorageScene_Setup) copies the 90 items of the current player's storage
 *   (PlayerStorage_Items) into `storage`; closing it (StorageScene_SaveAndClose) copies them back and
 *   tells main so (GroupParams_SetC4C(1));
 * - the 90 items are seen as six pages of 15 (`page`), each with a tab on the touch screen
 *   (StorageScene_DrawTabs, the OBJs of data_ov102_0229eac0) and its own palettes
 *   ("menu/inventory/ten%d.bpl"); its background is "menu/inventory/b_itm_bg_tra0.bsc" with the
 *   characters "menu/inventory/b_itm_chest.bch";
 * - it is built on the three objects of ov094's that the pockets scenes use (ov099/pockets_view.h):
 *   the grid at 0xcc, whose places 0-14 are the pocket slots and 15-29 the page shown
 *   (PocketsGrid_SetBox), the letters at 0xb2c (only drawn) and the wallet at 0xb54.
 *
 * The cursor walks the pockets (3 rows of 5), the page (3 rows of 5), the six tabs (2 rows of 3)
 * and a close button (StorageScenePlace). There is no choice: A picks an item up, puts the held
 * one down or swaps it; Y sends an item to the first free place of the other part; the stylus
 * drags items. Items in a state, in the ranges letters refuse, and item 0x155d are dimmed in the
 * pockets and cannot be taken (StorageScene_CannotStore). */
#ifndef CLEAN_OV102_STORAGE_SCENE_H
#define CLEAN_OV102_STORAGE_SCENE_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/popup.h"
#include "ov094/pockets_grid.h"
#include "ov094/pockets_letters.h"
#include "ov094/pockets_wallet.h"
#include "types.h"

/* In `flags`. */
enum StorageSceneFlag {
    STORAGE_SCENE_FLAG_DRAWN = 0x01,         /* the scene is drawn (StorageScene_Draw) */
    STORAGE_SCENE_FLAG_POCKETS_DRAWN = 0x02, /* the pockets, the letters and the wallet are drawn at
                                              * `objects_y` */
    STORAGE_SCENE_FLAG_DRAGGABLE = 0x04,     /* the touched place's item is not dimmed: dragging takes it
                                              * (StorageScene_TouchPlace) */
    STORAGE_SCENE_FLAG_JUMP = 0x08,          /* the cursor sprite jumps to the cursor instead of easing
                                              * (StorageScene_GlideToCursor), once; never set here */
    STORAGE_SCENE_FLAG_WRAPPED_LEFT = 0x10,  /* this move left the cursor over a left edge */
    STORAGE_SCENE_FLAG_WRAPPED_RIGHT = 0x20, /* this move right */
    STORAGE_SCENE_FLAG_HELD_HIDDEN = 0x40,   /* the held item is not drawn */
    STORAGE_SCENE_FLAG_PAGE_DRAWN = 0x80,    /* the page and the tabs are drawn at `page_y` */
    STORAGE_SCENE_FLAG_CLOSE_TURN = 0x100,   /* this move took the cursor onto or off the close button
                                              * (StorageScene_MoveCursor) */
    STORAGE_SCENE_FLAG_TO_TAB = 0x200        /* the held item glides to a tab (StorageScene_GlideHeldTo) */
};

#define STORAGE_SCENE_FLAGS_WRAPPED (STORAGE_SCENE_FLAG_WRAPPED_LEFT | STORAGE_SCENE_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `home`, ...). The grid's object knows the pockets and the
 * page by the same numbers (StorageScene_GridPlace). */
enum StorageScenePlace {
    STORAGE_SCENE_POCKET_FIRST = 0x00, /* 0x00-0x0e: the pockets, row * 5 + column */
    STORAGE_SCENE_POCKET_LAST = 0x0e,
    STORAGE_SCENE_BOX_FIRST = 0x0f, /* 0x0f-0x1d: the page, 0x0f + row * 5 + column */
    STORAGE_SCENE_BOX_LAST = 0x1d,
    STORAGE_SCENE_TAB_FIRST = 0x1e, /* 0x1e-0x23: the tabs of pages 0-5, 0x1e + row * 3 + column */
    STORAGE_SCENE_TAB_LAST = 0x23,
    STORAGE_SCENE_CLOSE = 0x24,   /* the close button (at 0xc4, 0x70) */
    STORAGE_SCENE_NO_PLACE = 0x25 /* none */
};

#define STORAGE_SCENE_COLUMNS 5
#define STORAGE_SCENE_ROWS 3
#define STORAGE_SCENE_TAB_COLUMNS 3
#define STORAGE_SCENE_PAGES 6
#define STORAGE_SCENE_PAGE_ITEMS 15
#define STORAGE_SCENE_ITEMS (STORAGE_SCENE_PAGES * STORAGE_SCENE_PAGE_ITEMS)
#define STORAGE_SCENE_TAB_OBJS 3 /* the OBJs of a tab (data_ov102_0229eac0); the first is its touch area */
#define STORAGE_SCENE_LABELS 2

/* What the scene holds (`held_kind`). */
enum StorageSceneHeldKind {
    STORAGE_SCENE_HELD_NONE = 0,
    STORAGE_SCENE_HELD_ITEM = 1 /* `held_item` in `held_state` */
};

/* The phases the scene sets (MenuScene.phase; MenuScene_Update runs phase 0 by vtable slot 0x48,
 * 1 by 0x4c, 2 by 0x50, 3 by 0x54, 4 by 0x58 and 5 by 0x5c). */
enum StorageScenePhase {
    STORAGE_SCENE_PHASE_WAIT = 0,        /* the base's wait */
    STORAGE_SCENE_PHASE_STATES = 1,      /* StorageScene_RunState */
    STORAGE_SCENE_PHASE_INTERACTIVE = 2, /* StorageScene_RunInteractive */
    STORAGE_SCENE_PHASE_DELETE = 5       /* StorageScene_RequestDelete */
};

/* The states (MenuScene.state), run from the table of StorageScene_RunState. */
enum StorageSceneState {
    STORAGE_SCENE_STATE_START_SETUP = 0,        /* StorageScene_StartSetup */
    STORAGE_SCENE_STATE_START_WIPE_IN = 1,      /* StorageScene_StartWipeIn */
    STORAGE_SCENE_STATE_POCKETS_WIPE_IN = 2,    /* StorageScene_PocketsWipeIn */
    STORAGE_SCENE_STATE_PAGE_WIPE_IN = 3,       /* StorageScene_PageWipeIn */
    STORAGE_SCENE_STATE_START_WIPE_OUT = 4,     /* StorageScene_StartWipeOut */
    STORAGE_SCENE_STATE_PAGE_WIPE_OUT = 5,      /* StorageScene_PageWipeOut */
    STORAGE_SCENE_STATE_POCKETS_WIPE_OUT = 6,   /* StorageScene_PocketsWipeOut */
    STORAGE_SCENE_STATE_TURN_PAGE = 7,          /* StorageScene_TurnPage */
    STORAGE_SCENE_STATE_TURN_PAGE_WIPE_OUT = 8, /* StorageScene_TurnPageWipeOut */
    STORAGE_SCENE_STATE_TURN_PAGE_WIPE_IN = 9,  /* StorageScene_TurnPageWipeIn */
    STORAGE_SCENE_STATES = 10
};

/* The sub states (MenuScene.sub_state), run from the table of StorageScene_RunSubState. */
enum StorageSceneSubState {
    STORAGE_SCENE_SUB_IDLE_BY_TOUCH = 0x00, /* StorageScene_IdleByTouch */
    STORAGE_SCENE_SUB_HOLD_TOUCH = 0x01,    /* StorageScene_HoldTouchOnPlace */
    STORAGE_SCENE_SUB_DRAG = 0x02,          /* StorageScene_DragHeld */
    STORAGE_SCENE_SUB_IDLE_BY_KEYS = 0x03,  /* StorageScene_IdleByKeys */
    STORAGE_SCENE_SUB_HOLD_BY_KEYS = 0x04,  /* StorageScene_MoveHeldByKeys */
    STORAGE_SCENE_SUB_SPRITE_MOVE = 0x05,   /* StorageScene_WaitCursorSprite */
    STORAGE_SCENE_SUB_BUTTON_PRESS = 0x06,  /* StorageScene_FinishButtonPress */
    STORAGE_SCENE_SUB_PRESS_END = 0x07,     /* StorageScene_FinishPressAnim */
    STORAGE_SCENE_SUB_PICK_UP = 0x08,       /* StorageScene_PickUpOnTurn */
    STORAGE_SCENE_SUB_PICK_UP_END = 0x09,   /* StorageScene_FinishPickUp */
    STORAGE_SCENE_SUB_PUT_DOWN = 0x0a,      /* StorageScene_PutDownWithCursor */
    STORAGE_SCENE_SUB_SWAP = 0x0b,          /* StorageScene_SwapWithCursor */
    STORAGE_SCENE_SUB_SWAP_END = 0x0c,      /* StorageScene_FinishSwap */
    STORAGE_SCENE_SUB_HELD_GLIDE = 0x0d,    /* StorageScene_StepHeldGlide */
    STORAGE_SCENE_SUB_ERROR = 0x0e,         /* StorageScene_WaitError; not set by this overlay */
    STORAGE_SCENE_SUB_CLOSE_DELAY = 0x0f,   /* StorageScene_WaitCloseDelay */
    STORAGE_SCENE_SUB_STATES = 0x10
};

typedef struct StorageScene {
    MenuScene base;                         /* 0x0000 */
    LayerTaskPair layer_task;               /* 0x0094: ended each frame (StorageScene_EndLayerTask) */
    PocketsGrid grid;                       /* 0x00cc */
    PocketsLetters letters;                 /* 0x0b2c */
    PocketsWallet wallet;                   /* 0x0b54 */
    Popup popup;                            /* 0x218c */
    Glide glide;                            /* 0x225c: the held item's glide to a place */
    Glider cursor_sprite;                   /* 0x2274: a Glider0 */
    ErrorMessage error;                     /* 0x22d8 */
    TextLabel labels[STORAGE_SCENE_LABELS]; /* 0x23f4: the title's (StorageScene_ShowTitle) */
    u32 flags;                              /* 0x24cc: StorageSceneFlag */
    s32 objects_y;                          /* 0x24d0: the wipe's y while the pockets wipe (layer 6) */
    s32 page_y;                             /* 0x24d4: the wipe's y while the page wipes (layer 4) */
    s32 grab_dx;                            /* 0x24d8: from the touch to the held item */
    s32 grab_dy;                            /* 0x24dc */
    s32 held_x;                             /* 0x24e0: where the held item is drawn */
    s32 held_y;                             /* 0x24e4 */
    u16 storage[STORAGE_SCENE_ITEMS];       /* 0x24e8: the storage's items, page * 15 + place */
    u16 held_item;                          /* 0x259c */
    u8 held_state;                          /* 0x259e: the held item's state (PocketsGrid_ItemState) */
    u8 held_kind;                           /* 0x259f: StorageSceneHeldKind */
    u8 touch_place;                         /* 0x25a0: the place touched */
    u8 popup_place;                         /* 0x25a1: the place the popup tells of */
    u8 home;                                /* 0x25a2: where the held item goes back to, or glides to */
    u8 from_page;                           /* 0x25a3: the page shown when the held item was taken */
    u8 from_place;                          /* 0x25a4: the place it was taken from */
    u8 cursor;                              /* 0x25a5: StorageScenePlace */
    u8 target;                              /* 0x25a6: the place the held item is put down on or swapped at */
    u8 return_state;                        /* 0x25a7: the sub state to go back to */
    u8 labels_used;                         /* 0x25a8: of `labels`, this frame */
    u8 delay;                               /* 0x25a9: frames before the wipe out or the page's wipe in */
    u8 page;                                /* 0x25aa: the page shown */
    u8 pad_25ab;
} StorageScene;

StorageScene *StorageScene_Destroy(StorageScene *self);
StorageScene *StorageScene_Delete(StorageScene *self);
void StorageScene_ClearFlags(StorageScene *self, unsigned int flags);
void StorageScene_SetFlags(StorageScene *self, unsigned int flags);
int StorageScene_TestFlags(StorageScene *self, unsigned int flags);
int StorageScene_TurnPageByKeys(StorageScene *self);
void StorageScene_ShowPage(StorageScene *self);
int StorageScene_TabAtTouch(StorageScene *self, int x, int y);
void StorageScene_DrawTabs(StorageScene *self);
void StorageScene_SaveAndClose(StorageScene *self, int with_delay);
void StorageScene_ShowTitle(StorageScene *self, int highlighted);
TextLabel *StorageScene_NextLabel(StorageScene *self);
void StorageScene_CloseLabels(StorageScene *self);
int StorageScene_MoveCursor(StorageScene *self, int keys, int holding);
void StorageScene_MoveCursorInTabs(StorageScene *self, int keys, int holding);
void StorageScene_MoveCursorFromClose(StorageScene *self, int keys);
void StorageScene_MoveCursorInBox(StorageScene *self, int keys, int holding);
void StorageScene_MoveCursorInPockets(StorageScene *self, int keys, int holding);
void StorageScene_StartSwap(StorageScene *self, int place);
void StorageScene_StartPutDown(StorageScene *self, u8 place);
void StorageScene_StartPickUp(StorageScene *self);
void StorageScene_StartPressAnim(StorageScene *self);
void StorageScene_StartButtonPress(StorageScene *self);
void StorageScene_ShowCursorFirstOfSet(StorageScene *self);
void StorageScene_GlideToCursor(StorageScene *self);
void StorageScene_HideCursorSprite(StorageScene *self);
int StorageScene_CursorSpriteY(StorageScene *self);
int StorageScene_CursorSpriteX(StorageScene *self);
void StorageScene_ShowCursorSprite(StorageScene *self);
void StorageScene_SwapHeldWith(StorageScene *self, int place);
void StorageScene_PutHeldAt(StorageScene *self, int place);
void StorageScene_PickUpItem(StorageScene *self, unsigned int place);
void StorageScene_FollowGlide(StorageScene *self);
void StorageScene_FollowCursorSprite(StorageScene *self);
void StorageScene_FollowTouch(StorageScene *self);
void StorageScene_DrawHeld(StorageScene *self);
void StorageScene_UpdatePopup(StorageScene *self);
void StorageScene_PlacePopup(StorageScene *self);
int StorageScene_TouchMoved(StorageScene *self);
void StorageScene_HighlightPlace(StorageScene *self, unsigned int place);
void StorageScene_ClearHighlights(StorageScene *self);
void StorageScene_SelectPlace(StorageScene *self, unsigned int place);
void StorageScene_ClearSelection(StorageScene *self);
int StorageScene_PlaceItemState(StorageScene *self, int place);
int StorageScene_PlaceItem(StorageScene *self, int place);
int StorageScene_PlaceIsEmpty(StorageScene *self, int place);
int StorageScene_PlaceIsDimmed(StorageScene *self, int place);
void StorageScene_DimUnstorable(StorageScene *self);
int StorageScene_CannotStore(StorageScene *self, int place);
int StorageScene_PlaceY(StorageScene *self, int place);
int StorageScene_PlaceX(StorageScene *self, int place);
u16 *StorageScene_PageItems(StorageScene *self);
unsigned int StorageScene_BoxPlace(StorageScene *self, unsigned int index);
int StorageScene_BoxIndex(StorageScene *self, int place);
void StorageScene_SetPlaceItem(StorageScene *self, unsigned int place, int item, int state);
int StorageScene_DropHeldAt(StorageScene *self, int place);
int StorageScene_PlaceAtTouch(StorageScene *self, int x, int y, int with_item);
u8 StorageScene_PocketPlace(StorageScene *self, unsigned int index);
int StorageScene_GridPlace(StorageScene *self, int place);
int StorageScene_IsClosePlace(StorageScene *self, int place);
int StorageScene_IsTabPlace(StorageScene *self, unsigned int place);
int StorageScene_IsBoxPlace(StorageScene *self, unsigned int place);
int StorageScene_IsPocketPlace(StorageScene *self, unsigned int place);
void StorageScene_EndLayerTask(StorageScene *self);
u8 StorageScene_FreeBoxPlace(StorageScene *self);
int StorageScene_FreePocketPlace(StorageScene *self);
void StorageScene_SendTo(StorageScene *self, int place, int to);
void StorageScene_DropOffPlace(StorageScene *self, int place, int y);
void StorageScene_GlideHeldTo(StorageScene *self, int place, int steps);
void StorageScene_PickUpWithCursor(StorageScene *self, u8 place);
void StorageScene_PickUpWithTouch(StorageScene *self, u8 place);
void StorageScene_TouchPlace(StorageScene *self, int place);
void StorageScene_EndAction(StorageScene *self);
void StorageScene_EndActionAtCursor(StorageScene *self);
void StorageScene_EndActionHidden(StorageScene *self);
void StorageScene_WaitCloseDelay(StorageScene *self);
void StorageScene_WaitError(StorageScene *self);
void StorageScene_StepHeldGlide(StorageScene *self);
void StorageScene_FinishSwap(StorageScene *self);
void StorageScene_SwapWithCursor(StorageScene *self);
void StorageScene_PutDownWithCursor(StorageScene *self);
void StorageScene_FinishPickUp(StorageScene *self);
void StorageScene_PickUpOnTurn(StorageScene *self);
void StorageScene_FinishPressAnim(StorageScene *self);
void StorageScene_FinishButtonPress(StorageScene *self);
void StorageScene_WaitCursorSprite(StorageScene *self);
void StorageScene_MoveHeldByKeys(StorageScene *self);
void StorageScene_IdleByKeys(StorageScene *self);
void StorageScene_DragHeld(StorageScene *self);
void StorageScene_HoldTouchOnPlace(StorageScene *self);
void StorageScene_IdleByTouch(StorageScene *self);
int StorageScene_LoadWalletFiles(StorageScene *self);
void StorageScene_LoadPage(StorageScene *self);
void StorageScene_LoadBackground(StorageScene *self);
void StorageScene_PrepareWallet(StorageScene *self);
void StorageScene_SetUpLayers(void);
void StorageScene_EndFrame(StorageScene *self);
void StorageScene_BeginFrame(StorageScene *self);
void StorageScene_EndInteractiveFrame(StorageScene *self);
void StorageScene_BeginInteractiveFrame(StorageScene *self);
void StorageScene_Teardown(StorageScene *self);
void StorageScene_Setup(StorageScene *self);
void StorageScene_TurnPageWipeIn(StorageScene *self);
void StorageScene_TurnPageWipeOut(StorageScene *self);
void StorageScene_TurnPage(StorageScene *self);
void StorageScene_PocketsWipeOut(StorageScene *self);
void StorageScene_PageWipeOut(StorageScene *self);
void StorageScene_StartWipeOut(StorageScene *self);
void StorageScene_StartPageWipeOut(StorageScene *self);
void StorageScene_PageWipeIn(StorageScene *self);
void StorageScene_PocketsWipeIn(StorageScene *self);
void StorageScene_StartWipeIn(StorageScene *self);
void StorageScene_StartSetup(StorageScene *self);
void StorageScene_StartPageWipeIn(StorageScene *self);
int StorageScene_RequestDelete(StorageScene *self);
int StorageScene_Phase4Idle(void);
int StorageScene_Phase3Idle(void);
int StorageScene_RunInteractive(StorageScene *self);
void StorageScene_RunSubState(StorageScene *self);
int StorageScene_RunState(StorageScene *self);
int StorageScene_Draw(StorageScene *self);
int StorageScene_Close(StorageScene *self);
int StorageScene_Start(StorageScene *self);
StorageScene *StorageScene_New(void);

#endif
