/* The scene of overlay 140 (vtable 0x0229b404, include/cpp/ov140/Obj_ov140_0229b404.h;
 * constructor HostPicker_New, 0x1c00 bytes): a menu scene (ov002/menu_scene.h), loaded with
 * overlay 139 as overlay group 0x21, that lists the friends who host a game and lets one be
 * picked, as the evidence says:
 *
 * - the list is NitroDWC's friend list (Wfc_GetFriendList): an entry counts when its status is
 *   6, a game hosted (as the gate's talk counts them, ov048/gatekeeper_talk.c), and its status
 *   data begins with a character; its byte 0x22 (the game's entries, `num_entry`) shows how
 *   many are in that town, and a town of 4 is full and cannot be picked;
 * - six friends a page (`page`, 0-5) in overlay 139's rows (ov139/res_rows.h, at 0x8e8), each
 *   with two names from the entry's status data (from 0x10 and from 0) and an icon of its
 *   entries; the page number, the number of pages and the number of hosts are drawn with three
 *   text labels;
 * - under the rows three buttons of the background "menu/res/d0_bg.bsc": the next page, cancel
 *   and confirm (HOST_PICKER_PAGE, _CANCEL, _CONFIRM), drawn with an OBJ palette that says
 *   whether they can be used (HOST_PICKER_PAL_*);
 * - when it ends (HostPicker_End) main is told whether a friend was picked
 *   (GroupParams_SetC4C) and which: the friend's index in the list (GroupParams_SetArg).
 *
 * The cursor (`cursor`, HostPickerPlace) is a Glider0 sprite. */
#ifndef CLEAN_OV140_HOST_PICKER_H
#define CLEAN_OV140_HOST_PICKER_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov139/res_rows.h"
#include "types.h"

#define HOST_PICKER_ROWS 6
#define HOST_PICKER_FRIENDS 32
#define HOST_PICKER_LABELS 3
#define HOST_PICKER_SCREEN_ENTRIES 0x400

/* The places of the cursor (`cursor`). */
enum HostPickerPlace {
    HOST_PICKER_FIRST_ROW = 0, /* 0-5: the rows */
    HOST_PICKER_LAST_ROW = 5,
    HOST_PICKER_PAGE = 6,   /* the next page button */
    HOST_PICKER_CANCEL = 7, /* the cancel button */
    HOST_PICKER_CONFIRM = 8 /* the confirm button */
};

/* The OBJ palettes of the buttons (`page_palette`, `cancel_palette`, `confirm_palette`). */
#define HOST_PICKER_PAL_LIT 8      /* can be used */
#define HOST_PICKER_PAL_UNLIT 9    /* cannot: one page only, or no friend selected */
#define HOST_PICKER_PAL_PRESSED 10 /* pressed */

/* In `flags`. */
enum HostPickerFlag {
    HOST_PICKER_FLAG_DRAWN = 0x01,     /* the scene is drawn (HostPicker_Draw) */
    HOST_PICKER_FLAG_CANCELLED = 0x02, /* the scene ends without a friend picked */
    HOST_PICKER_FLAG_SCREEN = 0x04,    /* `screen` changed: it is queued to layer 6 */
    HOST_PICKER_FLAG_SELECTED = 0x08,  /* a row was just selected: the cursor goes on to confirm */
    HOST_PICKER_FLAG_SILENT = 0x10,    /* the next glide of the cursor makes no sound */
    HOST_PICKER_FLAG_PAGING = 0x20     /* the page changes: the rows' icons are not drawn */
};

/* The states, run from the table of HostPicker_RunState (MenuScene_SetState). */
enum HostPickerState {
    HOST_PICKER_STATE_START_SETUP = 0,    /* HostPicker_StartSetup */
    HOST_PICKER_STATE_START_WIPE_IN = 1,  /* HostPicker_StartWipeIn */
    HOST_PICKER_STATE_WIPE_IN = 2,        /* HostPicker_WipeIn */
    HOST_PICKER_STATE_START_WIPE_OUT = 3, /* HostPicker_StartWipeOut */
    HOST_PICKER_STATE_WIPE_OUT = 4,       /* HostPicker_WipeOut */
    HOST_PICKER_STATES = 5
};

/* The sub states, run from the table of HostPicker_RunSubState (MenuScene_SetSubState). */
enum HostPickerSubState {
    HOST_PICKER_SUB_TOUCH = 0,         /* HostPicker_BrowseByTouch */
    HOST_PICKER_SUB_KEYS = 1,          /* HostPicker_BrowseByKeys */
    HOST_PICKER_SUB_SPRITE_MOVE = 2,   /* HostPicker_WaitCursorSprite */
    HOST_PICKER_SUB_PRESS_ACT = 3,     /* HostPicker_ActOnPress */
    HOST_PICKER_SUB_PRESS_RELEASE = 4, /* HostPicker_WaitPressRelease */
    HOST_PICKER_SUB_CLOSING = 5,       /* HostPicker_WaitToClose */
    HOST_PICKER_SUB_PAGE_OUT = 6,      /* HostPicker_FadeRowsOut */
    HOST_PICKER_SUB_PAGE_IN = 7,       /* HostPicker_FadeRowsIn */
    HOST_PICKER_SUB_STATES = 8
};

typedef struct HostPicker {
    MenuScene base;                         /* 0x0000 */
    s32 wipe_y;                             /* 0x0094: MenuScene_WipeOffsetY's, kept */
    s32 panel_y;                            /* 0x0098: the button panel drawn there; not
                                                       * written by this overlay */
    s32 selected;                           /* 0x009c: the row picked, or -1 */
    u32 confirm_palette;                    /* 0x00a0: HOST_PICKER_PAL_* */
    u32 cancel_palette;                     /* 0x00a4 */
    u32 page_palette;                       /* 0x00a8 */
    u16 screen[HOST_PICKER_SCREEN_ENTRIES]; /* 0x00ac: "menu/res/d0_bg.bsc" */
    u16 flags;                              /* 0x08ac: HostPickerFlag */
    u8 return_sub_state;                    /* 0x08ae: the sub state to go back to */
    u8 row_used[HOST_PICKER_ROWS];          /* 0x08af: the row shows a host */
    u8 order[HOST_PICKER_FRIENDS];          /* 0x08b5: the list's entry at each place */
    u8 row_friend[HOST_PICKER_ROWS];        /* 0x08d5: the entry each row shows */
    u8 steps;                               /* 0x08db: of the page's fades and the end */
    u8 cursor;                              /* 0x08dc: HostPickerPlace */
    u8 page;                                /* 0x08dd */
    u8 last_page;                           /* 0x08de */
    u8 host_count;                          /* 0x08df */
    u8 row_entries[HOST_PICKER_ROWS];       /* 0x08e0: each row's host's entries */
    u8 labels_used;                         /* 0x08e6: of `labels` this frame */
    u8 pad_8e7;                             /* 0x08e7 */
    ResRows rows;                           /* 0x08e8: overlay 139's */
    Glider cursor_sprite;                   /* 0x128c: a Glider0 */
    ButtonPanel panel;                      /* 0x12f0 */
    LayerTask screen_task;                  /* 0x14bc: `screen` to layer 6 */
    u8 unk_14e0[0x5dc];                     /* 0x14e0: not used here */
    TextLabel labels[HOST_PICKER_LABELS];   /* 0x1abc: handed out each frame, the last
                                                       * one shared once all are used */
} HostPicker;

HostPicker *HostPicker_Destroy(HostPicker *self);
HostPicker *HostPicker_Delete(HostPicker *self);
void HostPicker_ClearFlags(HostPicker *self, u16 flags);
void HostPicker_SetFlags(HostPicker *self, u16 flags);
int HostPicker_TestFlags(HostPicker *self, int flags);
void HostPicker_ShowPage(HostPicker *self);
void HostPicker_ShowLastPage(HostPicker *self);
void HostPicker_ShowHostCount(HostPicker *self);
void HostPicker_CloseLabels(HostPicker *self);
u8 *HostPicker_TakeLabel(HostPicker *self);
unsigned int HostPicker_FriendList(HostPicker *self);
void HostPicker_FadeRows(HostPicker *self, int step);
int HostPicker_IsHosting(int unused, const u8 *entry);
void HostPicker_InitList(HostPicker *self);
int HostPicker_CountHosts(HostPicker *self);
void HostPicker_FillRows(HostPicker *self);
int HostPicker_RefreshEntries(HostPicker *self);
void HostPicker_Select(HostPicker *self, int row);
void HostPicker_MarkRows(HostPicker *self);
void HostPicker_QueueScreen(HostPicker *self);
int HostPicker_MoveCursor(HostPicker *self, int keys);
void HostPicker_PressAndReturn(HostPicker *self);
void HostPicker_PressToAct(HostPicker *self);
void HostPicker_ShowCursorSprite(HostPicker *self);
u8 *HostPicker_GlideTo(HostPicker *self, int x, int y);
int HostPicker_GlideToCursor(HostPicker *self);
void HostPicker_HideCursorSprite(HostPicker *self);
int HostPicker_CursorSpriteY(HostPicker *self);
int HostPicker_CursorSpriteX(HostPicker *self);
void HostPicker_PlaceSpriteAtCursor(HostPicker *self);
void HostPicker_NextPage(HostPicker *self);
void HostPicker_Cancel(HostPicker *self);
void HostPicker_Confirm(HostPicker *self);
void HostPicker_Resume(HostPicker *self);
void HostPicker_ResumeByKeys(HostPicker *self);
void HostPicker_ResumeByTouch(HostPicker *self);
void HostPicker_FadeRowsIn(HostPicker *self);
void HostPicker_FadeRowsOut(HostPicker *self);
int HostPicker_WaitToClose(HostPicker *self);
void HostPicker_WaitPressRelease(HostPicker *self);
void HostPicker_ActOnPress(HostPicker *self);
void HostPicker_WaitCursorSprite(HostPicker *self);
void HostPicker_BrowseByKeys(HostPicker *self);
void HostPicker_BrowseByTouch(HostPicker *self);
void HostPicker_RefreshHosts(HostPicker *self);
void HostPicker_LoadObjFiles(HostPicker *self);
void HostPicker_LoadBackground(HostPicker *self);
void HostPicker_SetUpLayers(void);
void HostPicker_EndFrame(HostPicker *self);
void HostPicker_BeginFrame(HostPicker *self);
void HostPicker_EndInteractiveFrame(HostPicker *self);
void HostPicker_BeginInteractiveFrame(HostPicker *self);
void HostPicker_Teardown(HostPicker *self);
void HostPicker_Setup(HostPicker *self);
int HostPicker_ScrollWithWipe(HostPicker *self);
int HostPicker_WipeOut(HostPicker *self);
void HostPicker_StartWipeOut(HostPicker *self);
void HostPicker_WipeIn(HostPicker *self);
void HostPicker_StartWipeIn(HostPicker *self);
void HostPicker_StartSetup(HostPicker *self);
int HostPicker_End(HostPicker *self);
int HostPicker_Phase4Idle(void);
int HostPicker_Phase3Idle(void);
int HostPicker_RunInteractive(HostPicker *self);
void HostPicker_RunSubState(HostPicker *self);
int HostPicker_RunState(HostPicker *self);
int HostPicker_Draw(HostPicker *self);
int HostPicker_Close(HostPicker *self);
int HostPicker_Start(HostPicker *self);
HostPicker *HostPicker_New(void);

#endif
