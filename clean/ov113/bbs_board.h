/* The scene of overlay 113 (overlay group 11, which overlay 92's dispatch opens in GroupParams
 * mode 0, ov092/menu_dispatch.h; vtable 0x0229ac00, include/cpp/ov113/Obj_ov113_0229ac00.h;
 * constructor BbsBoard_New, 0x2b84 bytes): a menu scene (ov002/menu_scene.h) that shows the
 * town's bulletin board (main/bbs.h) one post at a time, as the evidence says:
 *
 * - its background is "menu/bbs/b_bbs.bsc" (characters "...b_bbs.bch", palettes "...b_bbs.bpl")
 *   on BG 2 of the main engine; the screen is kept in `screen`, whose palettes it changes and
 *   then queues again (BBS_BOARD_FLAG_SCREEN_DIRTY);
 * - a post is shown as its date ("20YY" and "MMDD" in full-width digits), its number and its six
 *   lines of text drawn into characters of BG 2 (BbsBoard_ShowPost); showing it marks it read by
 *   the current player (BbsPost_MarkRead), and a mark on the board says whether it was;
 * - the posts' tabs (one OBJ a post, the oldest first, centred) and two arrows are drawn as OBJs
 *   over the board (BbsBoard_Draw).
 *
 * The cursor (`cursor`, BbsBoardCursor) is one of the four buttons at the bottom, the two arrows
 * or a post's tab. Picking a button, an arrow or a tab (BbsBoard_RunAction) turns the page to
 * that post (states 5-8), or ends the scene: QUIT tells the dispatch to end (mode 0x43), WRITE
 * that the screen of mode 1 comes next (the writing of a post, overlay 112). */
#ifndef CLEAN_OV113_BBS_BOARD_H
#define CLEAN_OV113_BBS_BOARD_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* What the cursor is on (BbsBoard.cursor). */
enum BbsBoardCursor {
    BBS_BOARD_CURSOR_OLDEST = 0, /* the first button: the oldest post */
    BBS_BOARD_CURSOR_NEWEST = 1, /* the second: the newest post */
    BBS_BOARD_CURSOR_WRITE = 2,  /* the third: write a post (the dispatch's mode 1) */
    BBS_BOARD_CURSOR_QUIT = 3,   /* the fourth: the scene ends */
    BBS_BOARD_CURSOR_NEWER = 4,  /* the arrow on the right (R): the next post */
    BBS_BOARD_CURSOR_OLDER = 5,  /* the arrow on the left (L): the post before */
    BBS_BOARD_CURSOR_TAB = 6,    /* 6-0x14: the tab of post cursor - 6 */
    BBS_BOARD_CURSOR_LAST_TAB = 0x14
};

#define BBS_BOARD_BUTTONS 4

/* The flags (BbsBoard.flags). */
enum BbsBoardFlag {
    BBS_BOARD_FLAG_SCREEN_DIRTY = 0x001, /* `screen` is queued for BG 2 at the frame's end */
    BBS_BOARD_FLAG_NEWER_LIT = 0x002,    /* the right arrow drawn in palette 11 */
    BBS_BOARD_FLAG_OLDER_LIT = 0x004,    /* the left arrow drawn in palette 11 */
    BBS_BOARD_FLAG_DRAWN = 0x008,        /* the scene's OBJs are drawn */
    BBS_BOARD_FLAG_WRAP_LEFT = 0x010,    /* the cursor's next place is 256 pixels to the left */
    BBS_BOARD_FLAG_WRAP_RIGHT = 0x020,   /* ... to the right */
    BBS_BOARD_FLAG_FORWARD = 0x040,      /* the tab picked is of a later post than the one shown */
    BBS_BOARD_FLAG_SNAP = 0x080,         /* the cursor is put at its next place, not glided */
    BBS_BOARD_FLAG_TURNING = 0x100       /* the page turns: the tabs follow the wipe */
};

/* The states (MenuScene.state), run by BbsBoard_RunState, and the sub states
 * (MenuScene.sub_state), run by BbsBoard_RunInteractive. */
enum BbsBoardState {
    BBS_BOARD_STATE_OPEN = 0,       /* BbsBoard_Open */
    BBS_BOARD_STATE_SHOW_FIRST = 1, /* BbsBoard_ShowFirstPost */
    BBS_BOARD_STATE_WIPE_IN = 2,    /* BbsBoard_WipeIn */
    BBS_BOARD_STATE_CLOSE = 3,      /* BbsBoard_StartWipeOut */
    BBS_BOARD_STATE_WIPE_OUT = 4,   /* BbsBoard_WipeOut */
    BBS_BOARD_STATE_TURN = 5,       /* BbsBoard_StartTurn */
    BBS_BOARD_STATE_TURN_OUT = 6,   /* BbsBoard_TurnOut */
    BBS_BOARD_STATE_TURN_SHOW = 7,  /* BbsBoard_TurnShow */
    BBS_BOARD_STATE_TURN_IN = 8,    /* BbsBoard_TurnIn */
    BBS_BOARD_STATES = 9
};

enum BbsBoardSubState {
    BBS_BOARD_SUB_TOUCH = 0,   /* BbsBoard_UpdateTouch: the cursor hidden, the pen in use */
    BBS_BOARD_SUB_KEYS = 1,    /* BbsBoard_UpdateKeys */
    BBS_BOARD_SUB_GLIDE = 2,   /* BbsBoard_WaitGlide: the cursor glides, then back */
    BBS_BOARD_SUB_PRESS = 3,   /* BbsBoard_WaitPress: A was pressed */
    BBS_BOARD_SUB_RELEASE = 4, /* BbsBoard_WaitRelease */
    BBS_BOARD_SUB_STATES = 5
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 0 by
 * the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50 and 5 by 0x5c). */
enum BbsBoardPhase {
    BBS_BOARD_PHASE_WAIT = 0,
    BBS_BOARD_PHASE_STATES = 1,      /* BbsBoard_RunState */
    BBS_BOARD_PHASE_INTERACTIVE = 2, /* BbsBoard_RunInteractive */
    BBS_BOARD_PHASE_DELETE = 5       /* BbsBoard_RequestDelete */
};

/* The modes told to the dispatch (MenuDispatch_SetMode). */
#define BBS_BOARD_MODE_WRITE 1 /* the screen that writes a post (overlay group 10, overlay 112) */

#define BBS_BOARD_LAYER 2 /* BG 2 of the main engine */
#define BBS_BOARD_SCREEN_SIZE 0x800
#define BBS_BOARD_LINES 6
#define BBS_BOARD_LINE_CHARS_SIZE 0x500 /* 40 characters of 32 bytes */
#define BBS_BOARD_DATE_LABELS 4
#define BBS_BOARD_WIPE_MARGIN 0x30

/* The labels (BbsBoard.labels). */
enum BbsBoardLabel {
    BBS_BOARD_LABEL_YEAR = 0,   /* "20YY" */
    BBS_BOARD_LABEL_DAY = 1,    /* "MMDD" */
    BBS_BOARD_LABEL_NUMBER = 2, /* the post's number, from 1 */
    BBS_BOARD_LABEL_3 = 3       /* constructed and closed, never shown */
};

typedef struct BbsBoard {
    MenuScene base;                                            /* 0x0000 */
    s32 wipe_y;                                                /* 0x0094: the wipe's y offset, followed by the OBJs */
    u16 flags;                                                 /* 0x0098: BbsBoardFlag */
    u8 post;                                                   /* 0x009a: the post shown, 0 the oldest */
    u8 cursor;                                                 /* 0x009b: BbsBoardCursor */
    u8 return_sub_state;                                       /* 0x009c: the sub state the glide goes back to */
    u8 posts;                                                  /* 0x009d: Bbs_CountTownPosts */
    u8 tabs_x;                                                 /* 0x009e: (15 - posts) * 4, the tabs centred */
    u8 pad_9f;                                                 /* 0x009f */
    u16 screen[BBS_BOARD_SCREEN_SIZE / 2];                     /* 0x00a0: "menu/bbs/b_bbs.bsc" */
    u8 line_chars[BBS_BOARD_LINES][BBS_BOARD_LINE_CHARS_SIZE]; /* 0x08a0: characters 0x11-0x100 */
    LayerTask chars_task;                                      /* 0x26a0: line_chars to BG 2 */
    LayerTask screen_task;                                     /* 0x26c4: screen to BG 2 */
    TextLabel labels[BBS_BOARD_DATE_LABELS];                   /* 0x26e8: BbsBoardLabel */
    TextLabel lines[BBS_BOARD_LINES];                          /* 0x2898 */
    Glider cursor_sprite;                                      /* 0x2b20: a Glider1 */
} BbsBoard;

BbsBoard *BbsBoard_Destroy(BbsBoard *self);
BbsBoard *BbsBoard_Delete(BbsBoard *self);
int BbsBoard_MoveCursor(BbsBoard *self, u32 keys);
void BbsBoard_ShowCursorFirstOfSet(BbsBoard *self);
void BbsBoard_CancelPress(BbsBoard *self);
void BbsBoard_Press(BbsBoard *self);
void BbsBoard_CursorMoved(BbsBoard *self);
void BbsBoard_HideCursor(BbsBoard *self);
u8 BbsBoard_CursorY(BbsBoard *self);
int BbsBoard_CursorX(BbsBoard *self);
int BbsBoard_CursorBaseX(BbsBoard *self);
void BbsBoard_PlaceCursor(BbsBoard *self);
void BbsBoard_CountPosts(BbsBoard *self);
int BbsBoard_RunAction(BbsBoard *self);
void BbsBoard_LightCursor(BbsBoard *self, int lit);
int BbsBoard_TouchCursor(BbsBoard *self);
void BbsBoard_ClearFlags(BbsBoard *self, u16 flags);
void BbsBoard_SetFlags(BbsBoard *self, u16 flags);
int BbsBoard_TestFlags(BbsBoard *self, u16 flags);
void BbsBoard_OpenLabel(BbsBoard *self, int label, int x, int y, int center, int unused);
void BbsBoard_Nothing(BbsBoard *self);
void BbsBoard_ShowPost(BbsBoard *self, int post);
void BbsBoard_ShowReadMark(BbsBoard *self, int post);
void BbsBoard_ShowNumber(BbsBoard *self, int post);
void BbsBoard_ShowDate(BbsBoard *self, int post);
void BbsBoard_ShowText(BbsBoard *self, int post);
void BbsBoard_StartKeys(BbsBoard *self);
void BbsBoard_StartTouch(BbsBoard *self);
void BbsBoard_WaitRelease(BbsBoard *self);
void BbsBoard_WaitPress(BbsBoard *self);
void BbsBoard_WaitGlide(BbsBoard *self);
void BbsBoard_UpdateKeys(BbsBoard *self);
void BbsBoard_UpdateTouch(BbsBoard *self);
void BbsBoard_LoadLayers(BbsBoard *self);
void BbsBoard_SetUpLayers(void);
void BbsBoard_QueueScreen(BbsBoard *self);
void BbsBoard_EndFrame(BbsBoard *self);
void BbsBoard_BeginFrameBody(BbsBoard *self);
void BbsBoard_BeginFrame(BbsBoard *self);
void BbsBoard_Teardown(BbsBoard *self);
void BbsBoard_Setup(BbsBoard *self);
void BbsBoard_TurnIn(BbsBoard *self);
void BbsBoard_TurnShow(BbsBoard *self);
void BbsBoard_TurnOut(BbsBoard *self);
void BbsBoard_StartTurn(BbsBoard *self);
void BbsBoard_WipeOut(BbsBoard *self);
void BbsBoard_StartWipeOut(BbsBoard *self);
void BbsBoard_WipeIn(BbsBoard *self);
void BbsBoard_ShowFirstPost(BbsBoard *self);
void BbsBoard_Open(BbsBoard *self);
int BbsBoard_RequestDelete(BbsBoard *self);
int BbsBoard_Phase4(void);
int BbsBoard_Phase3(void);
int BbsBoard_RunInteractive(BbsBoard *self);
int BbsBoard_RunState(BbsBoard *self);
int BbsBoard_Draw(BbsBoard *self);
void BbsBoard_DrawTabs(BbsBoard *self, int x, int y);
int BbsBoard_Close(BbsBoard *self);
int BbsBoard_Start(BbsBoard *self);
BbsBoard *BbsBoard_New(void);

#endif
