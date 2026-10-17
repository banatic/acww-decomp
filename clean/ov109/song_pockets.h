/* The scene of overlay 109 (vtable 0x0229dbd8; its profile at 0x0229db20 names the constructor
 * func_ov109_0229da60): a menu scene (ov002/menu_scene.h) that ov092's dispatch opens for its
 * mode 0x23 (overlay group 0x29, ov092/menu_dispatch.c). It shows the current player's pockets
 * through the three objects of ov094's that the pockets scenes of overlays 096-100 keep
 * (ov099/pockets_view.h), with a button panel (ov002/button_panel.h) below them, and lets the
 * player give one of the song items they carry to the house's songs, as the evidence says:
 *
 * - every pocket slot that holds anything but a song item (codes 0x1323-0x1368,
 *   main/house_record.h) in its plain state is dimmed (SongPockets_DimNonSongs) and cannot be
 *   picked;
 * - picking a song opens a choice of two rows (texts 0x73 and 2 of the choices); the first
 *   (SONG_POCKETS_ACTION_ADD) adds the song to the house (HouseRecord_AddSong), empties its
 *   pocket slot and closes the scene with the slot in GroupParams (GroupParams_SetArg) and
 *   GroupParams_SetC4C(1), unless the house has the song already, which shows error message
 *   17 instead;
 * - panel button 9 (or B) closes the scene with GroupParams_SetC4C(0).
 *
 * When it closes, the scene tells ov092's dispatch to go on to mode 0x40, or to close
 * (MENU_DISPATCH_MODE_CLOSE) when the menu was asked to close (StateFlags_MenuCloseAsked).
 *
 * As in ov099's scene, it runs by the touch (sub states 0-4, the cursor sprite hidden) or by
 * the keys (sub states 5-7), as state flag 2 says (StateFlags_Test2). Unlike ov099's, nothing is
 * ever picked up: the held item's fields are kept but never set. */
#ifndef CLEAN_OV109_SONG_POCKETS_H
#define CLEAN_OV109_SONG_POCKETS_H

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
enum SongPocketsFlag {
    SONG_POCKETS_FLAG_DRAWN = 0x01,         /* the scene is drawn (SongPockets_Draw) */
    SONG_POCKETS_FLAG_OBJECTS_DRAWN = 0x02, /* the panel and the objects of ov094's are drawn */
    SONG_POCKETS_FLAG_SPRITE_JUMP = 0x04,   /* the cursor sprite jumps to the cursor instead of easing
                                             * (SongPockets_GlideToCursor), once; never set here */
    SONG_POCKETS_FLAG_WRAPPED_LEFT = 0x08,  /* this move wrapped the cursor over the left edge */
    SONG_POCKETS_FLAG_WRAPPED_RIGHT = 0x10, /* this move wrapped it over the right edge */
    SONG_POCKETS_FLAG_HELD_HIDDEN = 0x20,   /* the held item is not drawn; never set here */
    SONG_POCKETS_FLAG_MENU_CLOSE = 0x40     /* the menu was asked to close: the scene ends with
                                             * MENU_DISPATCH_MODE_CLOSE */
};

#define SONG_POCKETS_FLAGS_WRAPPED (SONG_POCKETS_FLAG_WRAPPED_LEFT | SONG_POCKETS_FLAG_WRAPPED_RIGHT)

/* The places of the cursor (`cursor`, `slot`, ...). */
enum SongPocketsPlace {
    SONG_POCKETS_GRID_FIRST = 0x00, /* 0-14: the pocket slots, row * 5 + column */
    SONG_POCKETS_GRID_LAST = 0x0e,
    SONG_POCKETS_BUTTON = 0x0f,  /* below the grid: the panel's button 9 (at 0xbc, 0xb6) */
    SONG_POCKETS_NO_PLACE = 0x10 /* none (also for no slot under the touch) */
};

#define SONG_POCKETS_COLUMNS 5
#define SONG_POCKETS_ROWS 3

/* What the scene holds (`held_kind`). */
enum SongPocketsHeldKind {
    SONG_POCKETS_HELD_NONE = 0,
    SONG_POCKETS_HELD_ITEM = 1 /* drawn by SongPockets_DrawHeld; never set here */
};

/* The values of the choice's rows (`action`). */
enum SongPocketsAction {
    SONG_POCKETS_ACTION_ADD = 0,   /* row text 0x73: the song added (SongPockets_RunAction) */
    SONG_POCKETS_ACTION_CANCEL = 1 /* row text 2, B, or a touch elsewhere */
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 0 by
 * the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50, 3 by 0x54, 4 by 0x58 and 5 by 0x5c). */
enum SongPocketsPhase {
    SONG_POCKETS_PHASE_WAIT = 0,        /* the base's wait */
    SONG_POCKETS_PHASE_STATES = 1,      /* SongPockets_RunState */
    SONG_POCKETS_PHASE_INTERACTIVE = 2, /* SongPockets_RunInteractive */
    SONG_POCKETS_PHASE_DELETE = 5       /* SongPockets_RequestDelete */
};

/* The states (MenuScene_SetState; the table of SongPockets_RunState). */
enum SongPocketsState {
    SONG_POCKETS_STATE_START_SETUP = 0,    /* SongPockets_StartSetup */
    SONG_POCKETS_STATE_START_WIPE_IN = 1,  /* SongPockets_StartWipeIn */
    SONG_POCKETS_STATE_WIPE_IN = 2,        /* SongPockets_WipeIn */
    SONG_POCKETS_STATE_START_WIPE_OUT = 3, /* SongPockets_StartWipeOut */
    SONG_POCKETS_STATE_WIPE_OUT = 4,       /* SongPockets_WipeOut */
    SONG_POCKETS_STATES = 5
};

/* The sub states (MenuScene_SetSubState; the table of SongPockets_RunSubState). */
enum SongPocketsSubState {
    SONG_POCKETS_SUB_IDLE_BY_TOUCH = 0x00,    /* SongPockets_IdleByTouch */
    SONG_POCKETS_SUB_HOLD_TOUCH = 0x01,       /* SongPockets_HoldTouchOnPlace */
    SONG_POCKETS_SUB_WAIT_PEN_UP = 0x02,      /* SongPockets_WaitPenUp */
    SONG_POCKETS_SUB_OPEN_TOUCHED = 0x03,     /* SongPockets_OpenTouchedChoice */
    SONG_POCKETS_SUB_CHOICE_BY_TOUCH = 0x04,  /* SongPockets_ChooseByTouch */
    SONG_POCKETS_SUB_IDLE_BY_KEYS = 0x05,     /* SongPockets_IdleByKeys */
    SONG_POCKETS_SUB_CHOICE_BY_KEYS = 0x06,   /* SongPockets_ChooseByKeys */
    SONG_POCKETS_SUB_PICK_ROW = 0x07,         /* SongPockets_PickChoiceRow */
    SONG_POCKETS_SUB_WAIT_SPRITE = 0x08,      /* SongPockets_WaitCursorGlide */
    SONG_POCKETS_SUB_BUTTON_BY_KEYS = 0x09,   /* SongPockets_PressButtonAfterAnim */
    SONG_POCKETS_SUB_WAIT_SPRITE_ANIM = 0x0a, /* SongPockets_WaitCursorAnim */
    SONG_POCKETS_SUB_CHOICE_OPENING = 0x0b,   /* SongPockets_WaitChoiceShown */
    SONG_POCKETS_SUB_CHOICE_CLOSE = 0x0c,     /* SongPockets_CloseChoice */
    SONG_POCKETS_SUB_CHOICE_CLOSING = 0x0d,   /* SongPockets_RunActionWhenIdle */
    SONG_POCKETS_SUB_ERROR = 0x0e,            /* SongPockets_WaitError */
    SONG_POCKETS_SUB_PANEL_PRESS = 0x0f,      /* SongPockets_FollowPanelPress */
    SONG_POCKETS_SUB_STATES = 0x10
};

typedef struct SongPockets {
    MenuScene base;         /* 0x00 */
    LayerTaskPair tasks;    /* 0x94: ended each frame (SongPockets_EndLayerTask) */
    PocketsGrid grid;       /* 0xcc: the pocket slots */
    PocketsLetters letters; /* 0xb2c: the letters, all dimmed */
    PocketsWallet wallet;   /* 0xb54: the wallet's display */
    Popup popup;            /* 0x218c */
    Glide glide;            /* 0x225c: only stopped here */
    Glider cursor_sprite;   /* 0x2274: a Glider0 */
    u8 choice[0x3e8];       /* 0x22d8: a PagedChoice */
    ChoiceEntries entries;  /* 0x26c0 */
    u8 pad_26cb;            /* 0x26cb */
    ErrorMessage error;     /* 0x26cc */
    ButtonPanel panel;      /* 0x27e8 */
    u32 flags;              /* 0x29b4: SongPocketsFlag */
    s32 wipe_y;             /* 0x29b8: MenuScene_WipeOffsetY's, where the objects are drawn */
    s32 grab_dx;            /* 0x29bc: from the touch to the touched place */
    s32 grab_dy;            /* 0x29c0 */
    s32 held_x;             /* 0x29c4: where the held item is drawn */
    s32 held_y;             /* 0x29c8 */
    u8 unk_29cc[3];         /* 0x29cc */
    u8 held_kind;           /* 0x29cf: SongPocketsHeldKind */
    u8 touch_place;         /* 0x29d0: the place touched (SongPockets_TouchPlace) */
    u8 popup_place;         /* 0x29d1: the place the popup tells of */
    u8 unk_29d2;            /* 0x29d2 */
    u8 cursor;              /* 0x29d3: SongPocketsPlace */
    u8 slot;                /* 0x29d4: the place whose choice is open */
    u8 unk_29d5;            /* 0x29d5 */
    u8 return_state;        /* 0x29d6: the sub state to go back to */
    u8 action;              /* 0x29d7: SongPocketsAction */
    u8 choice_row;          /* 0x29d8: the choice row the cursor sprite points at */
    u8 open_delay;          /* 0x29d9: frames before a touched place's choice opens */
    u8 pad_29da[2];
} SongPockets;

static_assert(offsetof(SongPockets, tasks) == 0x94 && offsetof(SongPockets, grid) == 0xcc, "members");
static_assert(offsetof(SongPockets, letters) == 0xb2c && offsetof(SongPockets, wallet) == 0xb54, "ov094 objects");
static_assert(offsetof(SongPockets, popup) == 0x218c && offsetof(SongPockets, glide) == 0x225c, "popup");
static_assert(offsetof(SongPockets, cursor_sprite) == 0x2274 && offsetof(SongPockets, choice) == 0x22d8, "sprite");
static_assert(offsetof(SongPockets, entries) == 0x26c0 && offsetof(SongPockets, error) == 0x26cc, "choice");
static_assert(offsetof(SongPockets, panel) == 0x27e8 && offsetof(SongPockets, flags) == 0x29b4, "panel");
static_assert(offsetof(SongPockets, held_x) == 0x29c4 && offsetof(SongPockets, held_kind) == 0x29cf, "held");
static_assert(offsetof(SongPockets, cursor) == 0x29d3 && offsetof(SongPockets, open_delay) == 0x29d9, "bytes");
static_assert(sizeof(SongPockets) == 0x29dc, "size (func_ov109_0229da60)");

SongPockets *SongPockets_Destroy(SongPockets *self);
SongPockets *SongPockets_Delete(SongPockets *self);
void SongPockets_ClearFlags(SongPockets *self, unsigned int flags);
void SongPockets_SetFlags(SongPockets *self, unsigned int flags);
int SongPockets_TestFlags(SongPockets *self, int flags);
int SongPockets_MoveCursor(SongPockets *self, int keys);
void SongPockets_MoveCursorInGrid(SongPockets *self, int keys);
void SongPockets_OpenChoice(SongPockets *self, u8 place, int above_popup);
void SongPockets_AddEntries(SongPockets *self);
void SongPockets_CloseWithoutSong(SongPockets *self);
void SongPockets_PressPanelButton9(SongPockets *self);
void SongPockets_CloseWithSong(SongPockets *self);
void SongPockets_CancelChoice(SongPockets *self);
void SongPockets_ShowChoice(SongPockets *self, int above_popup);
void SongPockets_RunAction(SongPockets *self);
void SongPockets_PressButtonPlace(SongPockets *self);
int SongPockets_ShowCursorFirstOfSet(SongPockets *self);
void SongPockets_PlaceCursorSprite(SongPockets *self);
void SongPockets_PointAtFirstRow(SongPockets *self);
int SongPockets_PointAtLastRow(SongPockets *self);
void SongPockets_GlideToRow(SongPockets *self);
void SongPockets_GlideToCursor(SongPockets *self);
void SongPockets_HideCursorSprite(SongPockets *self);
int SongPockets_CursorSpriteY(SongPockets *self);
int SongPockets_CursorSpriteX(SongPockets *self);
void SongPockets_ShowCursorSprite(SongPockets *self);
void SongPockets_DrawHeld(SongPockets *self);
void SongPockets_UpdatePopup(SongPockets *self);
void SongPockets_PlacePopup(SongPockets *self);
void SongPockets_SelectPlace(SongPockets *self, unsigned int place);
void SongPockets_ClearSelection(SongPockets *self);
int SongPockets_PlaceItemState(SongPockets *self, int place);
int SongPockets_PlaceItem(SongPockets *self, int place);
int SongPockets_PlaceIsEmpty(SongPockets *self, int place);
int SongPockets_PlaceIsDimmed(SongPockets *self, int place);
void SongPockets_DimNonSongs(SongPockets *self);
int SongPockets_PlaceY(SongPockets *self, int place);
int SongPockets_PlaceX(SongPockets *self, int place);
void SongPockets_SetSlotItem(SongPockets *self, int place, int item, int state);
int SongPockets_GridPlaceAtTouch(SongPockets *self, int x, int y, int with_item);
int SongPockets_GridPlace(SongPockets *self, unsigned int index);
unsigned char SongPockets_GridIndex(SongPockets *self, int place);
int SongPockets_IsGridPlace(SongPockets *self, unsigned int place);
void SongPockets_EndLayerTask(SongPockets *self);
void SongPockets_ShowError(SongPockets *self, unsigned char message);
void SongPockets_TouchPlace(SongPockets *self, int place);
void SongPockets_EndAction(SongPockets *self);
void SongPockets_EndActionAtCursor(SongPockets *self);
void SongPockets_EndActionHidden(SongPockets *self);
void SongPockets_FollowPanelPress(SongPockets *self);
void SongPockets_WaitError(SongPockets *self);
void SongPockets_RunActionWhenIdle(SongPockets *self);
void SongPockets_CloseChoice(SongPockets *self);
void SongPockets_WaitChoiceShown(SongPockets *self);
void SongPockets_WaitCursorAnim(SongPockets *self);
void SongPockets_PressButtonAfterAnim(SongPockets *self);
void SongPockets_WaitCursorGlide(SongPockets *self);
void SongPockets_PickChoiceRow(SongPockets *self);
void SongPockets_ChooseByKeys(SongPockets *self);
void SongPockets_IdleByKeys(SongPockets *self);
void SongPockets_ChooseByTouch(SongPockets *self);
void SongPockets_OpenTouchedChoice(SongPockets *self);
void SongPockets_WaitPenUp(SongPockets *self);
void SongPockets_HoldTouchOnPlace(SongPockets *self);
void SongPockets_IdleByTouch(SongPockets *self);
void SongPockets_LoadGraphics(SongPockets *self);
void SongPockets_PrepareWallet(SongPockets *self);
void SongPockets_SetUpLayer6(void);
void SongPockets_EndFrame(SongPockets *self);
void SongPockets_BeginFrame(SongPockets *self);
void SongPockets_EndInteractiveFrame(SongPockets *self);
void SongPockets_BeginInteractiveFrame(SongPockets *self);
void SongPockets_Teardown(SongPockets *self);
void SongPockets_Setup(SongPockets *self);
void SongPockets_WipeOut(SongPockets *self);
void SongPockets_StartWipeOut(SongPockets *self);
void SongPockets_WipeIn(SongPockets *self);
void SongPockets_StartWipeIn(SongPockets *self);
void SongPockets_StartSetup(SongPockets *self);
int SongPockets_RequestDelete(SongPockets *self);
int SongPockets_Phase4Idle(void);
int SongPockets_Phase3Idle(void);
int SongPockets_RunInteractive(SongPockets *self);
void SongPockets_RunSubState(SongPockets *self);
int SongPockets_RunState(SongPockets *self);
int SongPockets_Draw(SongPockets *self);
int SongPockets_Close(SongPockets *self);
int SongPockets_Start(SongPockets *self);
SongPockets *SongPockets_New(void);

#endif
