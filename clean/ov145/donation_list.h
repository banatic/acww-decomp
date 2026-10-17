/* The scene of overlay 145 (vtable 0x0229ae00, include/cpp/ov145/Obj_ov145_0229ae00.h;
 * constructor DonationList_New, 0x2508 bytes): the list of what the town has given to the
 * museum, with who gave each item. Its files are "menu/donation/..."; ov092's dispatcher
 * (ov092/menu_dispatch.h) starts it for GroupParams mode 0x41 (overlay group 0x27), which the
 * owl opens from his line 0x3f (ov047/owl_talk.c) before he tells how far the museum is.
 *
 * - The museum's record (main/museum_record.h, data_021f38f8) is read once at the setup: the
 *   items of each of its four groups that were given are gathered, in code order, into the
 *   lists of the four tabs (DonationListTab): the paintings, the fish, the insects and the
 *   fossils. The fossils' tab is shown first.
 * - The list shows rows 16 pixels high on layer 4, each with the item's name and, beside it, the
 *   name of the player who gave it (MuseumRecord_GiverName) or menu message 0xcc. The layer
 *   scrolls by `scroll` pixels; its screen is a ring of 16 rows of two tile rows each, rebuilt
 *   from the 9 row patterns of "b_bg.bsc" (DonationList_BuildListScreen), and the 9 rows in view
 *   keep their texts in a ring of 9 too (`shown`).
 * - A handle on a track at the right (a push button, ov002/push_button.h) scrolls the list
 *   when there are more than 8 rows: dragged, by touching the track, or held with A and moved
 *   with up and down.
 * - Choosing another tab fades the list's text colour out, changes the list and fades it back
 *   in (DonationList_StepFade).
 * - The panel's button 6 (ov002/button_panel.h, layout 5 with message 0x65) or B closes the
 *   scene; it tells main so with GroupParams_SetC4C(1) and the dispatcher's mode 0x44.
 *
 * The scene is used by the touch (sub state 0 on) or by the keys (sub state 3 on), as state
 * flag 2 says (StateFlags_IsClear2); the cursor (DonationListPlace) is then drawn by a Glider0
 * sprite (ov002/glide.h). */
#ifndef CLEAN_OV145_DONATION_LIST_H
#define CLEAN_OV145_DONATION_LIST_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/push_button.h"
#include "types.h"

/* The tabs (`tab`, `selected_tab`), from the right; the group of the museum's record each one
 * lists. */
enum DonationListTab {
    DONATION_TAB_PAINTINGS = 0, /* group D: 20 items, 0x3894 on, 4 codes apart */
    DONATION_TAB_FISH = 1,      /* group B: 56 items, 0x12e8 on */
    DONATION_TAB_INSECTS = 2,   /* group C: 56 items, 0x12b0 on */
    DONATION_TAB_FOSSILS = 3,   /* group A: 52 items, 0x450c on, 4 codes apart */
    DONATION_TABS = 4
};

/* The places of the cursor (`cursor`). */
enum DonationListPlace {
    DONATION_PLACE_TAB = 0,    /* 0-3: the tabs */
    DONATION_PLACE_CLOSE = 4,  /* the panel's button 6 */
    DONATION_PLACE_HANDLE = 5, /* the scroll handle */
    DONATION_NO_TAB = 6        /* what DonationList_TabAtTouch answers for no tab */
};

/* In `flags`. */
enum DonationListFlag {
    DONATION_FLAG_DRAWN = 0x1,       /* the scene is drawn (DonationList_Draw) */
    DONATION_FLAG_FRAME_DIRTY = 0x2, /* `frame_screen` to be queued for layer 6; never set here */
    DONATION_FLAG_TEXTS_DIRTY = 0x4, /* the rows' texts to be refreshed (DonationList_RefreshRows) */
    DONATION_FLAG_LIST_DIRTY = 0x8   /* `list_screen` to be queued for layer 4, until it is */
};

/* The fade of the list's text colour (`fade_mode`); `fade` goes from 3 (the colour of the
 * file) to 0 (its colour 7) and back. */
enum DonationListFade {
    DONATION_FADE_NONE = 0,
    DONATION_FADE_OUT = 1, /* down to 0, then the selected tab is shown */
    DONATION_FADE_IN = 2   /* up to 3 */
};

#define DONATION_FADE_FULL 3

/* The phases the scene sets (MenuScene.phase; MenuScene_Update runs phase n by vtable slot
 * 0x48 + 4n). */
enum DonationListPhase {
    DONATION_PHASE_WAIT = 0,        /* the base's wait */
    DONATION_PHASE_STATES = 1,      /* DonationList_RunState */
    DONATION_PHASE_INTERACTIVE = 2, /* DonationList_RunInteractive */
    DONATION_PHASE_DELETE = 5       /* DonationList_RequestDelete */
};

/* The states (MenuScene.state), run from the table of DonationList_RunState. */
enum DonationListState {
    DONATION_STATE_START_SETUP = 0,    /* DonationList_StartSetup */
    DONATION_STATE_WIPE_IN = 1,        /* DonationList_WipeIn */
    DONATION_STATE_START_WIPE_OUT = 2, /* DonationList_StartWipeOut */
    DONATION_STATE_WIPE_OUT = 3,       /* DonationList_WipeOut */
    DONATION_STATES = 4
};

/* The sub states (MenuScene.sub_state), run from the table of DonationList_RunSubState. */
enum DonationListSubState {
    DONATION_SUB_IDLE_BY_TOUCH = 0,  /* DonationList_IdleByTouch */
    DONATION_SUB_DRAG_HANDLE = 1,    /* DonationList_DragHandle */
    DONATION_SUB_TRACK_TOUCH = 2,    /* DonationList_TrackTouch */
    DONATION_SUB_IDLE_BY_KEYS = 3,   /* DonationList_IdleByKeys */
    DONATION_SUB_HANDLE_KEYS = 4,    /* DonationList_HandleByKeys */
    DONATION_SUB_HANDLE_RELEASE = 5, /* DonationList_WaitHandleRelease */
    DONATION_SUB_CURSOR_GLIDE = 6,   /* DonationList_WaitCursorGlide */
    DONATION_SUB_PRESS = 7,          /* DonationList_FinishPress */
    DONATION_SUB_CURSOR_ANIM = 8,    /* DonationList_FinishCursorAnim */
    DONATION_SUB_CLOSE_PRESS = 9,    /* DonationList_FinishClosePress */
    DONATION_SUB_STATES = 10
};

#define DONATION_PAINTINGS 20
#define DONATION_FISH 56
#define DONATION_INSECTS 56
#define DONATION_FOSSILS 52
#define DONATION_ROWS_IN_VIEW 9   /* the rows drawn (8 whole ones and a part) */
#define DONATION_LABELS 18        /* two a row */
#define DONATION_ROW_HEIGHT 16    /* pixels */
#define DONATION_HANDLE_RANGE 120 /* `handle_y`, 0 to this */
#define DONATION_SCREEN_ENTRIES 0x400

typedef struct DonationList {
    MenuScene base;                            /* 0x0000 */
    s32 wipe_y;                                /* 0x0094: the wipe's y (MenuScene_WipeOffsetY) */
    u32 unk_98;                                /* 0x0098 */
    s32 scroll;                                /* 0x009c: the list's, in pixels */
    s32 scroll_target;                         /* 0x00a0: what `scroll` moves to, 4 pixels a frame */
    s32 max_scroll;                            /* 0x00a4: (rows - 8) * 16, at least 0 */
    int handle_y;                              /* 0x00a8: 0 to DONATION_HANDLE_RANGE */
    s32 grab_dy;                               /* 0x00ac: the handle's y less the pen's when grabbed */
    s32 cued_y;                                /* 0x00b0: `handle_y` at the last scroll sound */
    u16 flags;                                 /* 0x00b4: DonationListFlag */
    s16 first_row;                             /* 0x00b6: scroll / 16 */
    u16 counts[DONATION_TABS];                 /* 0x00b8: the rows of each tab's list */
    u8 tab;                                    /* 0x00c0: the tab shown */
    u8 selected_tab;                           /* 0x00c1: the tab chosen (shown once faded out) */
    u8 cursor;                                 /* 0x00c2: DonationListPlace */
    u8 return_sub_state;                       /* 0x00c3 */
    u8 labels_used;                            /* 0x00c4: of `labels`, this frame */
    u8 fade;                                   /* 0x00c5: 0 to DONATION_FADE_FULL */
    u8 fade_mode;                              /* 0x00c6: DonationListFade */
    u8 pad_c7;                                 /* 0x00c7 */
    Glider cursor_sprite;                      /* 0x00c8: a Glider0 */
    PushButton handle;                         /* 0x012c */
    ButtonPanel panel;                         /* 0x0174 */
    TextLabel labels[DONATION_LABELS];         /* 0x0340 */
    LayerTask list_task;                       /* 0x0ad8: `list_screen` to layer 4 */
    LayerTask frame_task;                      /* 0x0afc: `frame_screen` to layer 6 */
    LayerTask palette_task;                    /* 0x0b20: `palette` to layer 4's palette 3 */
    u16 fossils[DONATION_FOSSILS];             /* 0x0b44: the items given, of each group */
    u16 fish[DONATION_FISH];                   /* 0x0bac */
    u16 insects[DONATION_INSECTS];             /* 0x0c1c */
    u16 paintings[DONATION_PAINTINGS];         /* 0x0c8c */
    u16 shown[DONATION_ROWS_IN_VIEW];          /* 0x0cb4: the item each ring place shows, or 0xfff1 */
    u16 row_screen[DONATION_SCREEN_ENTRIES];   /* 0x0cc6: "b_bg.bsc": 9 row patterns first */
    u16 list_screen[DONATION_SCREEN_ENTRIES];  /* 0x14c6: layer 4's */
    u16 frame_screen[DONATION_SCREEN_ENTRIES]; /* 0x1cc6: "a_bg.bsc", layer 6's */
    u16 palette_file[0x10];                    /* 0x24c6: "bg_3.bpl" */
    u16 palette[0x10];                         /* 0x24e6: its copy, colour 15 faded */
    u8 pad_2506[2];
} DonationList;

DonationList *DonationList_Destroy(DonationList *self);
DonationList *DonationList_Delete(DonationList *self);
void DonationList_ClearFlags(DonationList *self, unsigned short flags);
void DonationList_SetFlags(DonationList *self, unsigned short flags);
int DonationList_TestFlags(DonationList *self, int flags);
void DonationList_StepFade(DonationList *self);
void DonationList_BlendTextColour(DonationList *self, int level);
int DonationList_MoveCursor(DonationList *self, u32 keys);
int DonationList_TabAtTouch(DonationList *self, int x, int y);
int DonationList_Choose(DonationList *self, unsigned int place);
void DonationList_SelectTab(DonationList *self, unsigned char tab);
void DonationList_ShowTab(DonationList *self, unsigned char tab);
u16 *DonationList_TabItems(DonationList *self, int row);
short DonationList_TabCount(DonationList *self);
void DonationList_StepScroll(DonationList *self);
void DonationList_UploadListScreen(DonationList *self);
void DonationList_BuildListScreen(DonationList *self);
void DonationList_SetScroll(DonationList *self, int scroll);
void DonationList_UploadPending(DonationList *self);
void DonationList_RefreshRows(DonationList *self);
void DonationList_CloseLabels(DonationList *self);
TextLabel *DonationList_NextLabel(DonationList *self);
void DonationList_StartCursorAnim(DonationList *self);
void DonationList_StartPress(DonationList *self);
void DonationList_ShowCursorFirstOfSet(DonationList *self);
void DonationList_GlideCursorTo(DonationList *self, int x, int y);
void DonationList_GlideToCursor(DonationList *self);
void DonationList_HideCursorSprite(DonationList *self);
int DonationList_CursorY(DonationList *self);
int DonationList_CursorX(DonationList *self);
void DonationList_ShowCursorSprite(DonationList *self);
void DonationList_CollectInsects(DonationList *self);
void DonationList_CollectFish(DonationList *self);
void DonationList_CollectPaintings(DonationList *self);
void DonationList_CollectFossils(DonationList *self);
int DonationList_CollectEvery4(DonationList *self, u16 *items, int first, int count);
int DonationList_CollectEach(DonationList *self, u16 *items, int first, int count);
int DonationList_Collect(DonationList *self, u16 *items, unsigned short first, int count, int step);
void DonationList_HandleFromScroll(DonationList *self);
void DonationList_ScrollFromHandle(DonationList *self);
void DonationList_PlaceHandle(DonationList *self);
int DonationList_HandleReleased(DonationList *self);
void DonationList_MoveHandleByKeys(DonationList *self);
int DonationList_ReleaseHandle(DonationList *self);
void DonationList_MoveHandleTo(DonationList *self, int y, int on_track);
int DonationList_GrabHandle(DonationList *self, int x, int y);
void DonationList_StartClose(DonationList *self);
void DonationList_StartInteractive(DonationList *self);
void DonationList_UseKeys(DonationList *self);
void DonationList_UseTouch(DonationList *self);
void DonationList_FinishClosePress(DonationList *self);
void DonationList_FinishCursorAnim(DonationList *self);
void DonationList_FinishPress(DonationList *self);
void DonationList_WaitCursorGlide(DonationList *self);
void DonationList_WaitHandleRelease(DonationList *self);
void DonationList_HandleByKeys(DonationList *self);
void DonationList_IdleByKeys(DonationList *self);
void DonationList_TrackTouch(DonationList *self);
void DonationList_DragHandle(DonationList *self);
void DonationList_IdleByTouch(DonationList *self);
void DonationList_LoadObjFiles(DonationList *self);
void DonationList_LoadBackground(DonationList *self);
void DonationList_SetUpLayers(void);
void DonationList_EndFrame(DonationList *self);
void DonationList_BeginFrame(DonationList *self);
void DonationList_EndInteractiveFrame(DonationList *self);
void DonationList_BeginInteractiveFrame(DonationList *self);
void DonationList_Teardown(DonationList *self);
void DonationList_Setup(DonationList *self);
void DonationList_FollowWipe(DonationList *self);
void DonationList_WipeOut(DonationList *self);
void DonationList_StartWipeOut(DonationList *self);
void DonationList_WipeIn(DonationList *self);
void DonationList_StartSetup(DonationList *self);
int DonationList_RequestDelete(DonationList *self);
int DonationList_Phase4Idle(void);
int DonationList_Phase3Idle(void);
int DonationList_RunInteractive(DonationList *self);
void DonationList_RunSubState(DonationList *self);
int DonationList_RunState(DonationList *self);
int DonationList_Draw(DonationList *self);
int DonationList_End(DonationList *self);
int DonationList_Start(DonationList *self);
DonationList *DonationList_New(void);

#endif
