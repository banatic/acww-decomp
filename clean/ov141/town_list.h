/* The scene of overlay 141 (vtable 0x0229af48, include/cpp/ov141/Obj_ov141_0229af48.h;
 * constructor TownList_New, 0x1a90 bytes): a menu scene (ov002/menu_scene.h) that lists the
 * towns open for a visit over local wireless, as the evidence says:
 *
 * - overlay 92's dispatcher opens it with overlay 139 as overlay group 0x22 for GroupParams'
 *   mode 0x3d (ov092/menu_dispatch.c), which GroupParams_OpenWithC80C88 opens with the two
 *   places the town picked is copied to (main/group_params.c; scene command screen kind 4);
 * - each frame without a key it rescans the parents the local wireless library has found
 *   (TownList_Scan): a parent carrying this game's 0x1a bytes of data (the town's name, the
 *   player's name and a byte that is 0 while the town is open, ov048/gatekeeper_states.c) is
 *   kept in one of six rows; overlay 139's object at 0x94 shows the rows' texts and fades a row
 *   in when its parent is found and out when it is gone (TownList_StepFades);
 * - a row is picked by touch or with A, and the OK button (Start) closes the scene handing the
 *   picked parent and its data to main (TownList_End, GroupParams_SetC4C(1)); the quit button
 *   (B) closes it with GroupParams_SetC4C(0).
 *
 * The cursor (`cursor`) is on a row (0-5), on the quit button (6) or on the OK button (7). */
#ifndef CLEAN_OV141_TOWN_LIST_H
#define CLEAN_OV141_TOWN_LIST_H

#include "main/layer_load_task.h"
#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov066/local_search.h"
#include "types.h"

#define TOWN_LIST_ROWS 6

/* The size of the data a parent of this game carries (Local_EntryData), and its byte that is 0
 * while the town is open for a visit. */
#define TOWN_LIST_DATA_SIZE 0x1a
#define TOWN_LIST_DATA_CLOSED 0x18

/* The places of the cursor (`cursor`). */
enum TownListPlace {
    TOWN_LIST_ROW_FIRST = 0, /* 0-5: the rows */
    TOWN_LIST_ROW_LAST = 5,
    TOWN_LIST_QUIT = 6, /* the quit button */
    TOWN_LIST_OK = 7    /* the OK button */
};

/* In `flags`. */
enum TownListFlag {
    TOWN_LIST_FLAG_DRAWN = 0x01,        /* the scene is drawn (TownList_Draw) */
    TOWN_LIST_FLAG_QUIT = 0x02,         /* the scene was quit (TownList_Quit) */
    TOWN_LIST_FLAG_SCREEN_DIRTY = 0x04, /* `screen` is queued for layer 6 at the frame's end */
    TOWN_LIST_FLAG_TO_OK = 0x08,        /* a row was picked: once the press ends the cursor goes to
                                         * the OK button (TownList_WaitPress) */
    TOWN_LIST_FLAG_EASE_NO_CUE = 0x10   /* the next ease of the cursor sprite has no cue, once
                                         * (TownList_EaseTo) */
};

/* The palettes of the buttons (`quit_palette`, `ok_palette`): as drawn, greyed (no row picked:
 * the OK button does nothing) and pressed. */
#define TOWN_LIST_BUTTON_NORMAL 8
#define TOWN_LIST_BUTTON_GREY 9
#define TOWN_LIST_BUTTON_PRESSED 10

/* The states of a row (`row_state`). */
enum TownListRowState {
    TOWN_LIST_ROW_EMPTY = 0,
    TOWN_LIST_ROW_FOUND = 1, /* its parent was found in this scan: it fades in */
    TOWN_LIST_ROW_STALE = 2  /* not found since the scan before: it fades out, then empties */
};

/* The fade levels of a row (`fade`): it is shown at level / TOWN_LIST_FADE_FULL. */
#define TOWN_LIST_FADE_FULL 5

/* The states, run from the table of TownList_RunState (MenuScene_SetState). */
enum TownListState {
    TOWN_LIST_STATE_START_SETUP = 0,    /* TownList_StartSetup */
    TOWN_LIST_STATE_START_WIPE_IN = 1,  /* TownList_StartWipeIn */
    TOWN_LIST_STATE_WIPE_IN = 2,        /* TownList_WipeIn */
    TOWN_LIST_STATE_START_WIPE_OUT = 3, /* TownList_StartWipeOut */
    TOWN_LIST_STATE_WIPE_OUT = 4,       /* TownList_WipeOut */
    TOWN_LIST_STATES = 5
};

/* The sub states, run from the table of TownList_RunSubState (MenuScene_SetSubState). */
enum TownListSubState {
    TOWN_LIST_SUB_TOUCH = 0,       /* TownList_BrowseByTouch */
    TOWN_LIST_SUB_KEYS = 1,        /* TownList_BrowseByKeys */
    TOWN_LIST_SUB_SPRITE_MOVE = 2, /* TownList_WaitCursorSprite */
    TOWN_LIST_SUB_A_PRESS = 3,     /* TownList_ActOnPress */
    TOWN_LIST_SUB_PRESS = 4,       /* TownList_WaitPress */
    TOWN_LIST_SUB_CLOSING = 5,     /* TownList_CountDownToClose */
    TOWN_LIST_SUB_STATES = 6
};

/* The phases set (MenuScene_SetPhase): 0 waits (vtable slot 0x48), 1 runs the states (slot
 * 0x4c), 2 the sub states (slot 0x50) and 5 deletes the scene (slot 0x5c). */
#define TOWN_LIST_PHASE_WAIT 0
#define TOWN_LIST_PHASE_STATES 1
#define TOWN_LIST_PHASE_INTERACTIVE 2
#define TOWN_LIST_PHASE_DELETE 5

typedef struct TownList {
    MenuScene base;                               /* 0x0000 */
    u8 rows[0x9a4];                               /* 0x0094: overlay 139's object (constructor
                                                       * func_ov139_02299b54): the rows' texts
                                                       * and colours, and the cells drawn */
    Glider cursor_sprite;                         /* 0x0a38: a Glider0 */
    ButtonPanel panel;                            /* 0x0a9c */
    LayerTask screen_task;                        /* 0x0c68: `screen` to layer 6 */
    LocalParent parents[TOWN_LIST_ROWS];          /* 0x0c8c: each row's parent */
    u8 data[TOWN_LIST_ROWS][TOWN_LIST_DATA_SIZE]; /* 0x11cc: the data each row's parent carried
                                                       * when it was first found */
    s32 wipe_y;                                   /* 0x1268: MenuScene_WipeOffsetY's */
    s32 panel_offset;                             /* 0x126c: the panel's offset when drawn;
                                                       * this overlay never writes it */
    s32 picked;                                   /* 0x1270: the row picked, -1 for none */
    s32 ok_palette;                               /* 0x1274: TOWN_LIST_BUTTON_* */
    s32 quit_palette;                             /* 0x1278: TOWN_LIST_BUTTON_* */
    u16 screen[0x400];                            /* 0x127c: layer 6's screen */
    u16 flags;                                    /* 0x1a7c: TownListFlag */
    u8 return_sub_state;                          /* 0x1a7e: the sub state to go back to once
                                                       * the sprite stops or the press ends */
    u8 row_state[TOWN_LIST_ROWS];                 /* 0x1a7f: TownListRowState */
    u8 fade[TOWN_LIST_ROWS];                      /* 0x1a85 */
    u8 countdown;                                 /* 0x1a8b: frames before the scene closes */
    u8 cursor;                                    /* 0x1a8c: TownListPlace */
    u8 pad_1a8d[3];                               /* 0x1a8d */
} TownList;

TownList *TownList_Destroy(TownList *self);
TownList *TownList_Delete(TownList *self);
void TownList_ClearFlags(TownList *self, u16 flags);
void TownList_SetFlags(TownList *self, u16 flags);
int TownList_TestFlags(TownList *self, unsigned int flags);
int TownList_SetPicked(TownList *self, int row);
void TownList_BeforeWipeOut(void);
void TownList_AfterWipeIn(TownList *self);
void TownList_StoreParent(TownList *self, int row, const LocalParent *parent);
int TownList_FreeRow(const TownList *self);
int TownList_FindParent(const TownList *self, const LocalParent *parent);
void TownList_StepFades(TownList *self);
void TownList_Scan(TownList *self);
void TownList_QueueScreen(TownList *self);
int TownList_MoveCursor(TownList *self, int keys);
void TownList_PressCursor(TownList *self);
void TownList_PressA(TownList *self);
void TownList_ShowCursorSprite(TownList *self);
void TownList_EaseTo(TownList *self, int x, int y);
void TownList_GlideToCursor(TownList *self);
void TownList_HideCursorSprite(TownList *self);
int TownList_CursorSpriteY(TownList *self);
int TownList_CursorSpriteX(TownList *self);
void TownList_ShowCursorAtCursor(TownList *self);
void TownList_Quit(TownList *self);
void TownList_Confirm(TownList *self);
void TownList_Resume(TownList *self);
void TownList_ResumeByKeys(TownList *self);
void TownList_ResumeByTouch(TownList *self);
void TownList_CountDownToClose(TownList *self);
void TownList_WaitPress(TownList *self);
void TownList_ActOnPress(TownList *self);
void TownList_WaitCursorSprite(TownList *self);
void TownList_BrowseByKeys(TownList *self);
void TownList_BrowseByTouch(TownList *self);
void TownList_LoadPanelGraphics(TownList *self);
void TownList_LoadGraphics(TownList *self);
void TownList_SetUpLayers(void);
void TownList_EndFrame(TownList *self);
void TownList_BeginFrame(TownList *self);
void TownList_EndInteractiveFrame(TownList *self);
void TownList_BeginInteractiveFrame(TownList *self);
void TownList_Teardown(TownList *self);
void TownList_Setup(TownList *self);
void TownList_ScrollWithWipe(TownList *self);
void TownList_WipeOut(TownList *self);
void TownList_StartWipeOut(TownList *self);
void TownList_WipeIn(TownList *self);
void TownList_StartWipeIn(TownList *self);
void TownList_StartSetup(TownList *self);
int TownList_End(TownList *self);
int TownList_Phase4Idle(void);
int TownList_Phase3Idle(void);
int TownList_RunInteractive(TownList *self);
void TownList_RunSubState(TownList *self);
int TownList_RunState(TownList *self);
int TownList_Draw(TownList *self);
int TownList_Close(TownList *self);
int TownList_Start(TownList *self);
TownList *TownList_New(void);

#endif
