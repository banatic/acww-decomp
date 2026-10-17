/* The scene of overlay 146 (vtable 0x0229b680, include/cpp/ov146/Obj_ov146_0229b680.h;
 * constructor WfcHostList_New, 0x1ffc bytes): a menu scene (ov002/menu_scene.h) that lists the
 * friends of the Nintendo Wi-Fi Connection friend list who host a game, and lets the player pick
 * one, as the evidence says:
 *
 * - ov092's dispatcher starts it for GroupParams modes 0x3c and 0x42 (overlay group 0x2d,
 *   ov092/menu_dispatch.c); its graphics are "menu/wfc/bg.bch", "bg.bpl", "bg7.bpl", "a_bg.bsc",
 *   "b_bg.bsc", "obj0.bch", "obj1.bch" and "obj.bpl";
 * - each frame it reads the friends' statuses NitroDWC reports (Wfc_GetFriendList,
 *   autoload_2/network.h): a friend with status 6 (NitroDWC's DWC_STATUS_MATCH_SC_SV, hosting a
 *   game) and a status data that does not start with 0 is listed (WfcHostList_IsHosting); one
 *   whose game has fewer than four entries can be chosen (WfcHostList_IsJoinable);
 * - a row shows the six characters at 0 of the friend's status data and the six at 0x10, which
 *   it carries in a town name's text into menu message 0x66; the count of hosts is shown in
 *   full-width digits;
 * - the choice ends the scene with GroupParams_SetC4C(1) and the friend's index in
 *   GroupParams_SetArg (WfcHostList_Choose); the quit button with GroupParams_SetC4C(0).
 *
 * The list scrolls by `scroll` pixels (0-0x1a0, 16 per row, 7 rows on screen) toward
 * `scroll_target`; the scroll bar's knob (`knob_button`) stands at `knob` (0-0x50). The rows'
 * screen is built in `rows_screen` from 7 row slots of the base screen (`screen`): the friend of
 * row r is shown in slot r % 7, whose labels have colour 14 - slot and whose palette colour 14 -
 * slot is shaded from colour 15 toward colour 14 (joinable) or 7 (full) as the friend's `fade`
 * counts to 20 (WfcHostList_ShadeRows). A friend who stops hosting fades out before leaving the
 * list. The pointer (`pointer`, a Glider0 of ov002/glide.h) stands at the cursor (`cursor`) with
 * the buttons; the pen touches the rows, the buttons and the bar. */
#ifndef CLEAN_OV146_WFC_HOST_LIST_H
#define CLEAN_OV146_WFC_HOST_LIST_H

#include "autoload_2/network.h"
#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/message_window.h"
#include "ov002/push_button.h"
#include "types.h"

/* In `flags`. */
enum WfcHostListFlag {
    WFC_HOST_LIST_FLAG_DRAWN = 0x01,         /* the scene is drawn (WfcHostList_Draw) */
    WFC_HOST_LIST_FLAG_SCREEN_DIRTY = 0x02,  /* `rows_screen` is to be queued for its layer */
    WFC_HOST_LIST_FLAG_ROWS_DIRTY = 0x04,    /* the rows' labels are to be set again */
    WFC_HOST_LIST_FLAG_PALETTE_DIRTY = 0x08, /* `shaded_palette` is to be queued for its layer */
    WFC_HOST_LIST_FLAG_CHOSE_ROW = 0x10,     /* a row was chosen by A: the cursor goes to the go button */
    WFC_HOST_LIST_FLAG_QUIET_GLIDE = 0x20,   /* the next glide of the pointer makes no sound */
    WFC_HOST_LIST_FLAG_LIST_FROZEN = 0x40    /* chosen: the list is no longer read */
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase n by
 * the vtable's slot 0x48 + 4n). */
enum WfcHostListPhase {
    WFC_HOST_LIST_PHASE_WAIT = 0,        /* the base's wait */
    WFC_HOST_LIST_PHASE_STATES = 1,      /* WfcHostList_RunState */
    WFC_HOST_LIST_PHASE_INTERACTIVE = 2, /* WfcHostList_RunInteractive */
    WFC_HOST_LIST_PHASE_END = 5          /* WfcHostList_End */
};

/* The scene's states (MenuScene.state), each run by its handler of the table of
 * WfcHostList_RunState. */
enum WfcHostListState {
    WFC_HOST_LIST_STATE_START = 0,          /* WfcHostList_StartWipeIn */
    WFC_HOST_LIST_STATE_WIPE_IN = 1,        /* WfcHostList_WipeIn: then the input */
    WFC_HOST_LIST_STATE_CLOSE = 2,          /* WfcHostList_StartWipeOut */
    WFC_HOST_LIST_STATE_CLOSE_WIPE_OUT = 3, /* WfcHostList_WipeOut: then the scene ends */
    WFC_HOST_LIST_STATES = 4
};

/* The scene's sub states (MenuScene.sub_state), each run by its handler of the table of
 * WfcHostList_RunSubState. */
enum WfcHostListSubState {
    WFC_HOST_LIST_SUB_TOUCH = 0,         /* WfcHostList_RunTouch: the pen on the rows, buttons and bar */
    WFC_HOST_LIST_SUB_KNOB_DRAG = 1,     /* WfcHostList_RunKnobDrag: the pen drags the knob */
    WFC_HOST_LIST_SUB_BAR_TOUCH = 2,     /* WfcHostList_RunBarTouch: the knob moves toward the pen */
    WFC_HOST_LIST_SUB_KEYS = 3,          /* WfcHostList_RunKeys: the cursor, by the buttons */
    WFC_HOST_LIST_SUB_KNOB_KEYS = 4,     /* WfcHostList_RunKnobKeys: up and down move the knob while A is held */
    WFC_HOST_LIST_SUB_KNOB_RELEASE = 5,  /* WfcHostList_RunKnobRelease: the knob's release plays */
    WFC_HOST_LIST_SUB_POINTER_GLIDE = 6, /* WfcHostList_RunPointerGlide: until the pointer stops, then
                                          * `return_sub_state` */
    WFC_HOST_LIST_SUB_ACTIVATE = 7,      /* WfcHostList_RunActivate: the pointer's press plays, then A acts */
    WFC_HOST_LIST_SUB_POINTER_PRESS = 8, /* WfcHostList_RunPointerPress: the pointer's press plays, then
                                          * `return_sub_state` */
    WFC_HOST_LIST_SUB_CLOSE_DELAY = 9,   /* WfcHostList_RunCloseDelay: a few frames, then the states */
    WFC_HOST_LIST_SUB_STATES = 10
};

/* What the cursor stands at (`cursor`). */
enum WfcHostListCursor {
    WFC_HOST_LIST_CURSOR_QUIT = 0,     /* the quit button, bottom left */
    WFC_HOST_LIST_CURSOR_GO = 1,       /* the go button, bottom right */
    WFC_HOST_LIST_CURSOR_BAR = 2,      /* the scroll bar's knob */
    WFC_HOST_LIST_CURSOR_FIRST_ROW = 3 /* 3-9: the rows on screen, from the top */
};

#define WFC_HOST_LIST_FRIENDS FRIEND_COUNT /* 32 */
#define WFC_HOST_LIST_NONE 0x20            /* no friend, in `list`, `row_friend` and `chosen` */
#define WFC_HOST_LIST_ROWS 7               /* rows on screen, and row slots */
#define WFC_HOST_LIST_LABELS 20
#define WFC_HOST_LIST_SCROLL_MAX 0x1a0
#define WFC_HOST_LIST_KNOB_MAX 0x50
#define WFC_HOST_LIST_FADE_FULL 0x14

/* The palettes of the two buttons' OBJs (`go_palette`, `quit_palette`). */
#define WFC_HOST_LIST_BUTTON_UP 8
#define WFC_HOST_LIST_BUTTON_DISABLED 9
#define WFC_HOST_LIST_BUTTON_PRESSED 10

/* The NitroDWC status of a friend who hosts a game, and the entries a game has room for. */
#define WFC_HOST_LIST_STATUS_HOSTING 6
#define WFC_HOST_LIST_MAX_ENTRIES 4

typedef struct WfcHostList {
    MenuScene base;                            /* 0x00 */
    s32 wipe_y;                                /* 0x94: the wipe's y */
    int knob;                                  /* 0x98: 0-0x50 */
    s32 drag_offset;                           /* 0x9c: the knob less the pen's y when the drag began */
    s32 cued_knob;                             /* 0xa0: the knob at which the scroll last cued */
    s32 scroll;                                /* 0xa4: in pixels, 0-0x1a0 */
    s32 scroll_target;                         /* 0xa8 */
    u16 flags;                                 /* 0xac: WfcHostListFlag */
    s16 first_row;                             /* 0xae: the row at the top, scroll / 16 */
    u8 go_palette;                             /* 0xb0: WFC_HOST_LIST_BUTTON_* */
    u8 quit_palette;                           /* 0xb1 */
    u8 cursor;                                 /* 0xb2: WfcHostListCursor */
    u8 return_sub_state;                       /* 0xb3 */
    u8 labels_used;                            /* 0xb4: labels taken this frame */
    u8 titles_shown;                           /* 0xb5 */
    u8 host_count;                             /* 0xb6: the friends hosting, 0x21 before the first count */
    u8 anim_delay;                             /* 0xb7: frames to the busy animation's next frame */
    u8 anim_frame;                             /* 0xb8: 0-4 */
    u8 unk_b9;                                 /* 0xb9: set to 10, not read here */
    u8 close_delay;                            /* 0xba: frames before the wipe out */
    u8 chosen;                                 /* 0xbb: the friend chosen, WFC_HOST_LIST_NONE for none */
    u8 row_friend[WFC_HOST_LIST_ROWS];         /* 0xbc: the friend each row slot shows */
    u8 row_shade[WFC_HOST_LIST_ROWS];          /* 0xc3: each slot's shade last made */
    u8 list_entries[WFC_HOST_LIST_FRIENDS];    /* 0xca: the entries of each listed friend's game */
    u8 list[WFC_HOST_LIST_FRIENDS];            /* 0xea: the friends listed, in order */
    u8 fade[WFC_HOST_LIST_FRIENDS];            /* 0x10a: by friend, 0-20 */
    FriendStatus hosts[WFC_HOST_LIST_FRIENDS]; /* 0x12a: the statuses of the friends listed */
    u16 screen[0x400];                         /* 0x58a: "b_bg.bsc" */
    u16 rows_screen[0x400];                    /* 0xd8a: the rows' screen */
    u16 palette[16];                           /* 0x158a: "bg7.bpl" */
    u16 shaded_palette[16];                    /* 0x15aa: its copy with the rows' shades */
    u8 pad_15ca[2];                            /* 0x15ca */
    Glider pointer;                            /* 0x15cc: a Glider0 */
    TextLabel labels[WFC_HOST_LIST_LABELS];    /* 0x1630 */
    LayerTask screen_task;                     /* 0x1ea0: `rows_screen` to its layer */
    LayerTask palette_task;                    /* 0x1ec4: `shaded_palette` to its layer */
    MessageWindow window;                      /* 0x1ee8: message 0x7f */
    PushButton knob_button;                    /* 0x1fb4 */
} WfcHostList;

/* wfc_host_list.c */
WfcHostList *WfcHostList_Destroy(WfcHostList *self);
WfcHostList *WfcHostList_Delete(WfcHostList *self);
void WfcHostList_ClearFlags(WfcHostList *self, u16 mask);
void WfcHostList_SetFlags(WfcHostList *self, u16 mask);
int WfcHostList_TestFlags(WfcHostList *self, u16 mask);
void WfcHostList_EndLayerTasks(WfcHostList *self);
void WfcHostList_QueueLayers(WfcHostList *self);
void WfcHostList_LoadObjFiles(WfcHostList *self);
void WfcHostList_LoadScreens(WfcHostList *self);
void WfcHostList_SetLayers(void);
void WfcHostList_UpdateList(WfcHostList *self);
void WfcHostList_BeginFrame(WfcHostList *self);
void WfcHostList_EndFrame(WfcHostList *self);
void WfcHostList_BeginInteractiveFrame(WfcHostList *self);
void WfcHostList_Release(WfcHostList *self);
void WfcHostList_Setup(WfcHostList *self);
void WfcHostList_PlaceSprites(WfcHostList *self);
void WfcHostList_WipeOut(WfcHostList *self);
void WfcHostList_StartWipeOut(WfcHostList *self);
void WfcHostList_WipeIn(WfcHostList *self);
void WfcHostList_StartWipeIn(WfcHostList *self);
int WfcHostList_End(WfcHostList *self);
int WfcHostList_Phase4Idle(void);
int WfcHostList_Phase3Idle(void);
int WfcHostList_RunInteractive(WfcHostList *self);
void WfcHostList_RunSubState(WfcHostList *self);
int WfcHostList_RunState(WfcHostList *self);
int WfcHostList_Draw(WfcHostList *self);
int WfcHostList_Close(WfcHostList *self);
int WfcHostList_Start(WfcHostList *self);
WfcHostList *WfcHostList_New(void);

/* wfc_host_list_rows.c */
void WfcHostList_ShadeRows(WfcHostList *self);
void WfcHostList_ShadeRow(WfcHostList *self, int slot, int fade, int color);
void WfcHostList_KnobFromScroll(WfcHostList *self);
void WfcHostList_ScrollFromKnob(WfcHostList *self);
void WfcHostList_PlaceKnob(WfcHostList *self);
int WfcHostList_KnobReleased(WfcHostList *self);
void WfcHostList_KnobByKeys(WfcHostList *self);
void WfcHostList_ReleaseKnob(WfcHostList *self);
void WfcHostList_DragKnob(WfcHostList *self, int y, int approach);
int WfcHostList_GrabKnob(WfcHostList *self, int x, int y);
int WfcHostList_StepScroll(WfcHostList *self);
void WfcHostList_BuildRowsScreen(WfcHostList *self);
void WfcHostList_SetScroll(WfcHostList *self, int scroll);
int WfcHostList_IsJoinable(WfcHostList *self, int friend_index);
int WfcHostList_IsHosting(WfcHostList *self, const FriendStatus *status);
int WfcHostList_RefreshList(WfcHostList *self);
void WfcHostList_UpdateHosts(WfcHostList *self);
void WfcHostList_CopyHosts(WfcHostList *self);
FriendList *WfcHostList_FriendList(WfcHostList *self);
void WfcHostList_ShowTitlesOnce(WfcHostList *self);
void WfcHostList_ShowTitles(WfcHostList *self);
void WfcHostList_RefreshRowLabels(WfcHostList *self);
void WfcHostList_CloseLabels(WfcHostList *self);
TextLabel *WfcHostList_TakeLabel(WfcHostList *self);

/* wfc_host_list_input.c */
void WfcHostList_CursorFromPointer(WfcHostList *self);
void WfcHostList_CursorToLastRow(WfcHostList *self);
int WfcHostList_MoveCursorByKeys(WfcHostList *self, u32 keys);
int WfcHostList_Activate(WfcHostList *self, unsigned int cursor);
void WfcHostList_PressPointer(WfcHostList *self);
void WfcHostList_PressA(WfcHostList *self);
int WfcHostList_ShowPointerFirst(WfcHostList *self);
void WfcHostList_GlidePointerTo(WfcHostList *self, int x, int y);
void WfcHostList_MoveCursor(WfcHostList *self);
void WfcHostList_HidePointer(WfcHostList *self);
unsigned int WfcHostList_PointerY(WfcHostList *self);
int WfcHostList_PointerX(WfcHostList *self);
void WfcHostList_PlacePointer(WfcHostList *self);
void WfcHostList_Quit(WfcHostList *self);
void WfcHostList_Choose(WfcHostList *self);
void WfcHostList_BeginInput(WfcHostList *self);
void WfcHostList_BeginKeys(WfcHostList *self);
void WfcHostList_BeginTouch(WfcHostList *self);
void WfcHostList_RunCloseDelay(WfcHostList *self);
void WfcHostList_RunPointerPress(WfcHostList *self);
void WfcHostList_RunActivate(WfcHostList *self);
void WfcHostList_RunPointerGlide(WfcHostList *self);
void WfcHostList_RunKnobRelease(WfcHostList *self);
void WfcHostList_RunKnobKeys(WfcHostList *self);
void WfcHostList_RunKeys(WfcHostList *self);
void WfcHostList_RunBarTouch(WfcHostList *self);
void WfcHostList_RunKnobDrag(WfcHostList *self);
void WfcHostList_RunTouch(WfcHostList *self);

#endif
