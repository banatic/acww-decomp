/* The scene of overlay 144 (vtable 0x0229b3f8; constructor MusicList_New, 0x210c bytes): a menu
 * scene (ov002/menu_scene.h) that shows the songs the house's music collection holds
 * (main/house_record.h, the song items 0x1323-0x1368), as the evidence says:
 *
 * - ov092's dispatcher starts it in GroupParams' mode 0x40 (overlay group 0x26,
 *   ov092/menu_dispatch.c) and starts it again when it closes in that mode; its graphics are
 *   "menu/music/bg0.bch", "bg1.bch", "bg.bpl", "b_bg.bsc", "a_bg.bsc", "obj.bch" and "obj.bpl";
 * - the list (`songs`, gathered by HouseRecord_HasSong in item order) scrolls on the
 *   sub screen's BG1 by 16 pixels a row, nine rows built at a time from the row screens of
 *   "b_bg.bsc" (`row_screens`) into `list_screen`, each row's name in one of nine labels;
 * - the row of the song the room plays now (`playing`, HouseRecord_CurrentSong) and the row
 *   chosen (`selected`) are coloured; three buttons on the left (BG3, "a_bg.bsc" in
 *   `buttons_screen`) play or stop the chosen song (the parent is given the song by
 *   GroupParams_SetItem), store a song (the scene closes into mode 0x23, overlay 109, which adds
 *   one) and take the chosen song out into the pockets (HouseRecord_RemoveSong); the panel's
 *   button 6 closes the scene;
 * - a scroll bar's knob (`knob_button`) at `knob` (0-0x78) stands for the scroll;
 * - a pointer sprite (`pointer`, a Glider0 of ov002/glide.h) points at the cursor's place while
 *   the buttons are in use (state flag 2), else the touch drives the scene. */
#ifndef CLEAN_OV144_MUSIC_LIST_H
#define CLEAN_OV144_MUSIC_LIST_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/error_message.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/push_button.h"
#include "types.h"

#define MUSIC_LIST_SONGS 70 /* the song items 0x1323-0x1368 */
#define MUSIC_LIST_FIRST_SONG 0x1323
#define MUSIC_LIST_ROWS 9          /* rows built and labelled at a time */
#define MUSIC_LIST_ROWS_SHOWN 8    /* rows that fit on the screen */
#define MUSIC_LIST_ROW_HEIGHT 0x10 /* pixels */
#define MUSIC_LIST_KNOB_MAX 0x78   /* the knob's travel */
#define MUSIC_LIST_NO_ROW (-1)     /* in `selected` and `playing` */
#define MUSIC_LIST_NO_ITEM 0xfff1  /* main/item_code.h's no item */

/* In `flags`. */
enum MusicListFlag {
    MUSIC_LIST_FLAG_DRAWN = 0x0001,         /* set up: drawn (MusicList_Draw) */
    MUSIC_LIST_FLAG_BUTTONS_DIRTY = 0x0002, /* `buttons_screen` changed: queued at the frame's end */
    MUSIC_LIST_FLAG_LABELS_DIRTY = 0x0004,  /* the list scrolled: the rows labelled at the frame's end */
    MUSIC_LIST_FLAG_LIST_DIRTY = 0x0008,    /* the list's rows coloured and queued at the frame's end */
    MUSIC_LIST_FLAG_TAKEN_OUT = 0x0010,     /* a song was taken out: the cursor stays where it was */
    MUSIC_LIST_FLAG_STORE = 0x0020          /* the scene closes into the store screen (mode 0x23) */
};

/* The cursor (`cursor`): 0-8 a row on the screen, or one of these. They are also the answers of
 * MusicList_HitTest and the commands of MusicList_Command. */
enum MusicListPlace {
    MUSIC_LIST_PLACE_LAST_ROW = 8,
    MUSIC_LIST_PLACE_CLOSE = 9,  /* the panel's button 6 */
    MUSIC_LIST_PLACE_KNOB = 10,  /* the scroll bar's knob */
    MUSIC_LIST_PLACE_PLAY = 11,  /* play the chosen song, or stop the one playing */
    MUSIC_LIST_PLACE_TAKE = 12,  /* take the chosen song out */
    MUSIC_LIST_PLACE_STORE = 13, /* store a song (overlay 109) */
    MUSIC_LIST_PLACE_NONE = 14   /* MusicList_HitTest: nothing there */
};

/* The phases the scene sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase n by
 * the vtable's slot 0x48 + 4n). */
enum MusicListPhase {
    MUSIC_LIST_PHASE_WAIT = 0,        /* the base's wait */
    MUSIC_LIST_PHASE_STATES = 1,      /* MusicList_RunState */
    MUSIC_LIST_PHASE_INTERACTIVE = 2, /* MusicList_RunInteractive */
    MUSIC_LIST_PHASE_END = 5          /* MusicList_End */
};

/* The states (MenuScene.state), run by MusicList_RunState. */
enum MusicListState {
    MUSIC_LIST_STATE_OPEN = 0,     /* MusicList_Open */
    MUSIC_LIST_STATE_WIPE_IN = 1,  /* MusicList_WipeIn */
    MUSIC_LIST_STATE_CLOSE = 2,    /* MusicList_StartClose */
    MUSIC_LIST_STATE_WIPE_OUT = 3, /* MusicList_WipeOut */
    MUSIC_LIST_STATES = 4
};

/* The sub states (MenuScene.sub_state), run by MusicList_RunSubState. */
enum MusicListSubState {
    MUSIC_LIST_SUB_TOUCH = 0,         /* MusicList_TouchInput */
    MUSIC_LIST_SUB_KNOB_DRAG = 1,     /* MusicList_DragKnob */
    MUSIC_LIST_SUB_BAR_DRAG = 2,      /* MusicList_DragBar */
    MUSIC_LIST_SUB_KEYS = 3,          /* MusicList_KeyInput */
    MUSIC_LIST_SUB_KNOB_KEYS = 4,     /* MusicList_KnobKeys */
    MUSIC_LIST_SUB_KNOB_RELEASE = 5,  /* MusicList_KnobRelease */
    MUSIC_LIST_SUB_POINTER_MOVE = 6,  /* MusicList_PointerMove */
    MUSIC_LIST_SUB_POINTER_PRESS = 7, /* MusicList_PointerPress */
    MUSIC_LIST_SUB_POINTER_ANIM = 8,  /* MusicList_PointerAnim */
    MUSIC_LIST_SUB_PANEL_PRESS = 9,   /* MusicList_PanelPress */
    MUSIC_LIST_SUB_TAKE_OUT = 10,     /* MusicList_FinishTakeOut */
    MUSIC_LIST_SUB_CLOSE_DELAY = 11,  /* MusicList_CloseDelay */
    MUSIC_LIST_SUB_ERROR = 12,        /* MusicList_ErrorWait */
    MUSIC_LIST_SUB_STATES = 13
};

typedef struct MusicList {
    MenuScene base;                    /* 0x00 */
    s32 wipe_y;                        /* 0x94: MenuScene_WipeOffsetY */
    u8 unk_98[4];                      /* 0x98 */
    s32 scroll;                        /* 0x9c: the list's scroll, pixels */
    s32 scroll_target;                 /* 0xa0: where `scroll` moves (MusicList_StepScroll) */
    s32 scroll_max;                    /* 0xa4: 16 per row past the eighth, at least 0 */
    s32 knob;                          /* 0xa8: 0-0x78 */
    s32 grab_offset;                   /* 0xac: the knob less the touch's y when grabbed */
    s32 knob_cued;                     /* 0xb0: the knob when its scroll sound last played */
    u16 flags;                         /* 0xb4: MusicListFlag */
    s16 first_row;                     /* 0xb6: the row at the top, `scroll` / 16 */
    s16 count;                         /* 0xb8: songs in `songs` */
    s16 selected;                      /* 0xba: the row chosen, or MUSIC_LIST_NO_ROW */
    s16 playing;                       /* 0xbc: the row of the song played, or MUSIC_LIST_NO_ROW */
    u8 return_sub_state;               /* 0xbe: the sub state a pointer move returns to */
    u8 labels_used;                    /* 0xbf: of `labels`, this frame */
    u8 delay;                          /* 0xc0: frames before a close or the take out's end */
    u8 cursor;                         /* 0xc1: MusicListPlace */
    u8 pad_c2[2];                      /* 0xc2 */
    Glider pointer;                    /* 0xc4: Glider0 */
    PushButton knob_button;            /* 0x128 */
    ButtonPanel panel;                 /* 0x170 */
    TextLabel labels[MUSIC_LIST_ROWS]; /* 0x33c: the rows' names */
    LayerTask list_task;               /* 0x708: `list_screen` to the sub screen's BG1 */
    LayerTask buttons_task;            /* 0x72c: `buttons_screen` to the sub screen's BG3 */
    ErrorMessage error;                /* 0x750 */
    u16 songs[MUSIC_LIST_SONGS];       /* 0x86c: the songs held, `count` of them */
    u16 shown[MUSIC_LIST_ROWS];        /* 0x8f8: the song each label shows, by screen row % 9 */
    u16 row_screens[0x400];            /* 0x90a: "b_bg.bsc": the rows' screens, 64 entries each */
    u16 list_screen[0x400];            /* 0x110a: 16 rows of 64 entries */
    u16 buttons_screen[0x400];         /* 0x190a: "a_bg.bsc" */
} MusicList;

/* music_list_view.c */
void MusicList_ClearFlags(MusicList *self, u16 flags);
void MusicList_SetFlags(MusicList *self, u16 flags);
int MusicList_TestFlags(MusicList *self, u16 flags);
void MusicList_ScrollToRow(MusicList *self, int row);
int MusicList_Select(MusicList *self, int row);
void MusicList_RefreshButtons(MusicList *self);
void MusicList_SetStorePalette(MusicList *self, int palette);
void MusicList_SetTakePalette(MusicList *self, int palette);
void MusicList_SetPlayPalette(MusicList *self, int palette);
void MusicList_SetPlayFace(MusicList *self, u16 first_char);
void MusicList_StepScroll(MusicList *self);
void MusicList_ColorRows(MusicList *self);
void MusicList_ColorRow(MusicList *self, int row, int palette);
void MusicList_BuildRows(MusicList *self);
void MusicList_ScrollTo(MusicList *self, int scroll);
void MusicList_SetupScroll(MusicList *self);
void MusicList_FlushScreens(MusicList *self);
void MusicList_LabelRows(MusicList *self);
void MusicList_CloseLabels(MusicList *self);
TextLabel *MusicList_NextLabel(MusicList *self);
void MusicList_FindPlaying(MusicList *self);
void MusicList_GatherSongs(MusicList *self);
void MusicList_KnobFromScroll(MusicList *self);
void MusicList_ScrollFromKnob(MusicList *self);
void MusicList_PlaceKnob(MusicList *self);
int MusicList_KnobSettled(MusicList *self);
void MusicList_KnobByKeys(MusicList *self);
int MusicList_ReleaseKnob(MusicList *self);
void MusicList_MoveKnob(MusicList *self, int y, int jump);
int MusicList_GrabKnob(MusicList *self, int x, int y);

/* music_list_input.c */
int MusicList_MoveCursor(MusicList *self, int keys);
void MusicList_LeaveToLeft(MusicList *self);
void MusicList_LeaveToRight(MusicList *self);
int MusicList_RowAtPointer(MusicList *self);
void MusicList_ButtonAtPointer(MusicList *self);
int MusicList_HitTest(MusicList *self, int x, int y);
int MusicList_Command(MusicList *self, unsigned int command);
void MusicList_StartPointerAnim(MusicList *self);
void MusicList_StartPointerPress(MusicList *self);
void MusicList_ShowPointer(MusicList *self);
void MusicList_GlidePointerTo(MusicList *self, int x, int y);
void MusicList_MovePointer(MusicList *self);
void MusicList_HidePointer(MusicList *self);
int MusicList_PointerY(MusicList *self);
int MusicList_PointerX(MusicList *self);
void MusicList_PlacePointer(MusicList *self);
void MusicList_ShowError(MusicList *self, char message);
void MusicList_StartStore(MusicList *self);
int MusicList_TakeOut(MusicList *self);
void MusicList_StopSong(MusicList *self);
int MusicList_PlayOrStop(MusicList *self);
void MusicList_CloseByPanel(MusicList *self);
int MusicList_StartInput(MusicList *self);
u8 *MusicList_StartKeys(MusicList *self);
u8 *MusicList_StartTouch(MusicList *self);

/* music_list_scene.c */
void MusicList_ErrorWait(MusicList *self);
void MusicList_CloseDelay(MusicList *self);
void MusicList_FinishTakeOut(MusicList *self);
void MusicList_PanelPress(MusicList *self);
void MusicList_PointerAnim(MusicList *self);
void MusicList_PointerPress(MusicList *self);
void MusicList_PointerMove(MusicList *self);
void MusicList_KnobRelease(MusicList *self);
void MusicList_KnobKeys(MusicList *self);
void MusicList_KeyInput(MusicList *self);
void MusicList_DragBar(MusicList *self);
void MusicList_DragKnob(MusicList *self);
void MusicList_TouchInput(MusicList *self);
void MusicList_LoadObjGraphics(MusicList *self);
void MusicList_LoadScreens(MusicList *self);
void MusicList_SetupLayers(void);
void MusicList_EndFrame(MusicList *self);
void MusicList_StartFrame(MusicList *self);
void MusicList_EndFrameAgain(MusicList *self);
void MusicList_StartFrameWithPointer(MusicList *self);
void MusicList_Release(MusicList *self);
void MusicList_Setup(MusicList *self);
void MusicList_ScrollWipe(MusicList *self);
void MusicList_WipeOut(MusicList *self);
void MusicList_StartClose(MusicList *self);
void MusicList_WipeIn(MusicList *self);
void MusicList_Open(MusicList *self);
int MusicList_End(MusicList *self);
int MusicList_Phase4Idle(void);
int MusicList_Phase3Idle(void);
int MusicList_RunInteractive(MusicList *self);
void MusicList_RunSubState(MusicList *self);
int MusicList_RunState(MusicList *self);
int MusicList_Draw(MusicList *self);
int MusicList_Close(MusicList *self);
int MusicList_Start(MusicList *self);
MusicList *MusicList_Destroy(MusicList *self);
MusicList *MusicList_Delete(MusicList *self);
MusicList *MusicList_New(void);

#endif
