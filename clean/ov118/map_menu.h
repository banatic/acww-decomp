/* The town map of the menu (overlay 118; overlay group 7, which overlay 90's bar of tabs opens
 * for its tab 5, MENU_TAB_5 in ov090/menu_tabs.h, with overlay 117 that draws the map; vtable
 * 0x0229cc08, include/cpp/ov118/Obj_ov118_0229cc08.h; constructor MapMenu_New, 0x47d8 bytes).
 * A menu scene (ov002/menu_scene.h) on the sub screen, from the files "menu/map/b_map_*":
 *
 * - layer 4 shows the town's map (its characters drawn by overlay 117 into `map_chars`) in the
 *   frame "b_map_a_bg.bsc" (`map_screen`), with a scroll bar in its column 0x1d;
 * - layer 6 shows a list of 13 rows of two tile rows each ("b_map_b_bg.bsc"), right of the map,
 *   six of them at a time, scrolled by `scroll`; each row has an icon (columns 0x13-0x14) and a
 *   text label (`labels`);
 * - OBJs show the marks of the map (houses, buildings, three more from overlay 117), the
 *   player's place (blinking), the two buttons that pick the list and the scroll bar's knob
 *   (`knob`, a push button); a pointer (`cursor`, a glider) follows the keys.
 *
 * There are two lists (MAP_MENU_FLAG_PLACES picks): the residents (the current player, the
 * town's other players, its villagers) and five places of the town. A selection (MapMenu_Select)
 * is a mark of the map or a row of the list: the other one blinks (MapMenu_StepBlink).
 *
 * With the keys, the focus (`focus`, MapMenuFocus) moves between the bar of tabs, the two list
 * buttons, the six visible rows and the knob; moving off them to the map lets the pointer move
 * freely over the map (MAP_MENU_FLAG_POINTER), which selects the mark under it. With the pen,
 * the buttons, the knob, the bar's track, the marks and the rows are touched. */
#ifndef CLEAN_OV118_MAP_MENU_H
#define CLEAN_OV118_MAP_MENU_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/push_button.h"
#include "ov117/town_map_image.h"
#include "types.h"

/* In `flags`. */
enum MapMenuFlag {
    MAP_MENU_FLAG_PLACES = 0x0001,      /* the places' list is shown, else the residents' */
    MAP_MENU_FLAG_ROWS_UPLOAD = 0x0002, /* `shown_rows` is to be loaded into layer 6 */
    MAP_MENU_FLAG_DRAWN = 0x0004,       /* the OBJs are drawn (MapMenu_Draw) */
    MAP_MENU_FLAG_SCROLLS = 0x0008,     /* the list is longer than six rows: the knob is shown */
    MAP_MENU_FLAG_SCROLLING = 0x0010,   /* `scroll` moves to `scroll_target` (MapMenu_StepScroll) */
    MAP_MENU_FLAG_MAP_UPLOAD = 0x0020,  /* `map_screen` is to be loaded into layer 4 */
    MAP_MENU_FLAG_BLINK = 0x0040,       /* the selection blinks */
    MAP_MENU_FLAG_ROWS_DIRTY = 0x0080,  /* `shown_rows` is to be made again (MapMenu_BuildShownRows) */
    MAP_MENU_FLAG_MARK_OFF = 0x0100,    /* the blinking mark is in its off half */
    MAP_MENU_FLAG_FROM_LIST = 0x0200,   /* the selection was a row: its mark blinks, else the row */
    MAP_MENU_FLAG_POINTER = 0x0800,     /* the pointer moves freely over the map */
    MAP_MENU_FLAG_ON_KNOB = 0x1000,     /* the pointer sits on the knob while it is held */
    MAP_MENU_FLAG_OPENING = 0x2000,     /* the menu is opening: the setup takes a frame a state */
    MAP_MENU_FLAG_PLACE_NOW = 0x4000    /* the next move of the pointer is a jump, not a glide */
};

/* What the keys' focus is on (`focus`). */
enum MapMenuFocus {
    MAP_MENU_FOCUS_TAB = 0, /* 0-7: the bar's places (ov090/menu_tabs.h, MenuTab) */
    MAP_MENU_FOCUS_LAST_TAB = 7,
    MAP_MENU_FOCUS_RESIDENTS = 8, /* the button that shows the residents (at 0xd8, 0x40) */
    MAP_MENU_FOCUS_PLACES = 9,    /* the button that shows the places (at 0xb4, 0x40) */
    MAP_MENU_FOCUS_ROW = 0x0a,    /* 0x0a-0x0f: the six visible rows */
    MAP_MENU_FOCUS_LAST_ROW = 0x0f,
    MAP_MENU_FOCUS_KNOB = 0x10 /* the scroll bar's knob */
};

/* The bar's tab of this menu (MenuTabs_NextTab and MenuTabs_PreviousTab start from it). */
#define MAP_MENU_TAB 5

/* What a row of a list shows (`residents`, `places`). */
enum MapMenuEntry {
    MAP_MENU_ENTRY_NONE = 0,
    MAP_MENU_ENTRY_SELF = 1,     /* the current player */
    MAP_MENU_ENTRY_PLAYER = 2,   /* 2-5: the town's player 0-3 */
    MAP_MENU_ENTRY_VILLAGER = 6, /* 6-13: the town's villager 0-7 */
    MAP_MENU_ENTRY_PLACE = 14,   /* 14-18: place 0-4, the menu message 0x96-0x9a */
    MAP_MENU_ENTRY_END = 19
};

#define MAP_MENU_ROWS 13        /* rows of a list */
#define MAP_MENU_VISIBLE_ROWS 6 /* rows shown at once */
#define MAP_MENU_ROW_HEIGHT 16  /* pixels */
#define MAP_MENU_PLACES 5

/* A selection (MapMenu_Select): 0 none, 1-14 the marks 0-13, 15-27 the rows 0-12. */
#define MAP_MENU_SELECT_NONE 0
#define MAP_MENU_SELECT_MARK 1
#define MAP_MENU_SELECT_ROW 15
#define MAP_MENU_SELECT_END 28

/* `mark` and `row` when nothing is selected; `row` 13 stands for all the players' rows. */
#define MAP_MENU_NO_MARK 14
#define MAP_MENU_NO_ROW 14
#define MAP_MENU_PLAYER_ROWS 13

/* A mark drawn on the map: its place, and what it shows (MapMenuMarkKind; bit 7 flips it). */
typedef struct MapMenuMark {
    u8 x;
    u8 y;
    u8 kind;
} MapMenuMark;

/* The kinds of marks (the OBJ's characters are 0xc0 + kind * 2). */
enum MapMenuMarkKind {
    MAP_MENU_MARK_VILLAGER = 0,  /* a villager's house */
    MAP_MENU_MARK_PLAYERS = 1,   /* the players' house */
    MAP_MENU_MARK_BUILDING = 2,  /* 2-6: buildings */
    MAP_MENU_MARK_POSITION = 10, /* where the player is */
    MAP_MENU_MARK_POINTED = 11,  /* round the mark under the pointer */
    MAP_MENU_MARK_NONE = 12,
    MAP_MENU_MARK_FLIP = 0x80
};

#define MAP_MENU_MARKS 14      /* overlay 117's spots 3-16 */
#define MAP_MENU_EXTRA_MARKS 3 /* its spots 0-2 */

/* Overlay 117's 17 spots of the map are its markers (TownMapMarker, TownMapMarkers_Get). */
#define MAP_MENU_SPOTS TOWN_MAP_MARKERS

/* The screens are 32 x 32 tiles; a row of the list is two tile rows, its icon at column 0x13
 * and its text from column 0x13 to 0x1c. */
#define MAP_MENU_SCREEN_TILES 0x400
#define MAP_MENU_SCREEN_BYTES 0x800

/* The states (MenuScene.state), run by MapMenu_RunState in phase 1. */
enum MapMenuState {
    MAP_MENU_STATE_LOAD = 0,       /* MapMenu_StateLoad */
    MAP_MENU_STATE_MAP_START = 1,  /* MapMenu_StateMapStart */
    MAP_MENU_STATE_MAP_MIDDLE = 2, /* MapMenu_StateMapMiddle */
    MAP_MENU_STATE_MAP_END = 3,    /* MapMenu_StateMapEnd */
    MAP_MENU_STATE_LIST = 4,       /* MapMenu_StateList */
    MAP_MENU_STATE_SHOW = 5,       /* MapMenu_StateShow */
    MAP_MENU_STATE_WIPE_IN = 6,    /* MapMenu_StateWipeIn */
    MAP_MENU_STATE_LEAVE = 7,      /* MapMenu_StateLeave */
    MAP_MENU_STATE_WIPE_OUT = 8,   /* MapMenu_StateWipeOut */
    MAP_MENU_STATES = 9
};

/* The sub states (MenuScene.sub_state), run by MapMenu_RunSubState in phase 2. */
enum MapMenuSubState {
    MAP_MENU_SUB_TOUCH = 0,        /* MapMenu_SubTouch */
    MAP_MENU_SUB_DRAG_KNOB = 1,    /* MapMenu_SubDragKnob */
    MAP_MENU_SUB_TRACK = 2,        /* MapMenu_SubTrack */
    MAP_MENU_SUB_KEYS = 3,         /* MapMenu_SubKeys */
    MAP_MENU_SUB_GLIDE = 4,        /* MapMenu_SubGlide */
    MAP_MENU_SUB_PRESS = 5,        /* MapMenu_SubPress */
    MAP_MENU_SUB_RELEASE = 6,      /* MapMenu_SubRelease */
    MAP_MENU_SUB_KNOB_PRESS = 7,   /* MapMenu_SubKnobPress */
    MAP_MENU_SUB_KNOB_HELD = 8,    /* MapMenu_SubKnobHeld */
    MAP_MENU_SUB_KNOB_RELEASE = 9, /* MapMenu_SubKnobRelease */
    MAP_MENU_SUB_POINTER = 10,     /* MapMenu_SubPointer */
    MAP_MENU_SUB_STATES = 11
};

/* The phases the menu sets (MenuScene.phase; the base's update runs phase 0 by the vtable's
 * slot 0x48, 1 by 0x4c, 2 by 0x50 and 5 by 0x5c). */
enum MapMenuPhase {
    MAP_MENU_PHASE_WAIT = 0,
    MAP_MENU_PHASE_STATES = 1,      /* MapMenu_RunState */
    MAP_MENU_PHASE_INTERACTIVE = 2, /* MapMenu_RunInteractive */
    MAP_MENU_PHASE_DELETE = 5       /* MapMenu_RequestDelete */
};

typedef struct MapMenu {
    MenuScene base;                                /* 0x00 */
    s32 wipe_y;                                    /* 0x94: MenuScene_WipeOffsetY's */
    u16 scroll;                                    /* 0x98: the list's scroll, in pixels */
    u16 scroll_target;                             /* 0x9a */
    u16 flags;                                     /* 0x9c: MapMenuFlag */
    u8 position_x;                                 /* 0x9e: where the player is on the map */
    u8 position_y;                                 /* 0x9f */
    u8 labels_used;                                /* 0xa0: of `labels` (MapMenu_NextLabel) */
    u8 resident_count;                             /* 0xa1 */
    u8 place_count;                                /* 0xa2 */
    u8 shown_top;                                  /* 0xa3: the first row `shown_rows` shows, 0xff to make it again */
    u8 knob;                                       /* 0xa4: the knob's place on the bar, 0-0x58 */
    u8 grab_y;                                     /* 0xa5: the pen's y when it took the knob */
    u8 knob_cued;                                  /* 0xa6: the knob's place at the last scroll sound */
    u8 grab_knob;                                  /* 0xa7: the knob's place when the pen took it */
    u8 blink;                                      /* 0xa8: frames to the next blink, from 15 */
    u8 mark;                                       /* 0xa9: the selected mark, MAP_MENU_NO_MARK */
    u8 row;                                        /* 0xaa: the selected row, MAP_MENU_NO_ROW */
    u8 return_sub_state;                           /* 0xab: after the pointer's glide */
    u8 focus;                                      /* 0xac: MapMenuFocus */
    u8 pointed_mark;                               /* 0xad: the mark under the free pointer */
    u8 pointer_x;                                  /* 0xae: the free pointer */
    u8 pointer_y;                                  /* 0xaf */
    u8 player_rows;                                /* 0xb0: the residents' rows that are players */
    u8 frame;                                      /* 0xb1: counts 0-15 for the position's blink */
    u8 pad_b2[2];                                  /* 0xb2 */
    LayerTask rows_task;                           /* 0xb4: loads `shown_rows` into layer 6 */
    LayerTask map_task;                            /* 0xd8: loads `map_screen` into layer 4 */
    TextLabel labels[MAP_MENU_ROWS];               /* 0xfc: the rows' texts and the town's name */
    PushButton knob_button;                        /* 0x678 */
    Glider cursor;                                 /* 0x6c0: a Glider0 */
    u16 map_screen[MAP_MENU_SCREEN_TILES];         /* 0x724: "b_map_a_bg.bsc" */
    u16 shown_rows[MAP_MENU_SCREEN_TILES];         /* 0xf24: `rows` with the rows out of sight blank */
    u16 rows[MAP_MENU_SCREEN_TILES];               /* 0x1724: the list's rows with their icons */
    u16 rows_template[MAP_MENU_SCREEN_TILES];      /* 0x1f24: "b_map_b_bg.bsc": icon i at rows 2i, 2i + 1 */
    u8 map_chars[0x2000];                          /* 0x2724: the map's characters 0x60-0x15f */
    TownMapMarker spots[MAP_MENU_SPOTS];           /* 0x4724: overlay 117's */
    u8 residents[MAP_MENU_ROWS];                   /* 0x478a: MapMenuEntry */
    u8 places[MAP_MENU_ROWS];                      /* 0x4797: MapMenuEntry */
    MapMenuMark extra_marks[MAP_MENU_EXTRA_MARKS]; /* 0x47a4 */
    MapMenuMark marks[MAP_MENU_MARKS];             /* 0x47ad */
    u8 pad_47d7;                                   /* 0x47d7 */
} MapMenu;

/* map_menu_list.c */
void MapMenu_ElementNoOp(void *element);
void MapMenu_ConstructMark(void *mark);
void MapMenu_ClearFlags(MapMenu *self, unsigned int flags);
void MapMenu_SetFlags(MapMenu *self, unsigned short flags);
int MapMenu_TestFlags(MapMenu *self, unsigned short flags);
void MapMenu_PlayAtMark(MapMenu *self, int sound);
void MapMenu_StopBlink(MapMenu *self);
void MapMenu_StartBlink(MapMenu *self);
void MapMenu_StepBlink(MapMenu *self);
void MapMenu_StepScroll(MapMenu *self);
int MapMenu_IsScrolling(MapMenu *self);
void MapMenu_ScrollTo(MapMenu *self, int target);
void MapMenu_JumpTo(MapMenu *self, unsigned short scroll);
void MapMenu_ScrollToRow(MapMenu *self);
void MapMenu_JumpToRow(MapMenu *self);
unsigned char MapMenu_MarkOfSelection(MapMenu *self, unsigned int selection);
unsigned char MapMenu_RowOfSelection(MapMenu *self, unsigned int selection);
void MapMenu_HighlightRow(MapMenu *self, int row);
void MapMenu_Select(MapMenu *self, unsigned int selection);
int MapMenu_MarkAt(MapMenu *self, int x, int y);
void MapMenu_FillMarks(MapMenu *self, TownMapMarker *spots);
void MapMenu_DrawMark(MapMenu *self, int x, int y, int kind, int flip, int palette);
unsigned int MapMenu_MaxScroll(MapMenu *self);
unsigned char MapMenu_ShownCount(MapMenu *self);
u8 *MapMenu_ShownList(MapMenu *self);
void MapMenu_ShowList(MapMenu *self);
void MapMenu_ShowPlaces(MapMenu *self);
void MapMenu_ShowResidents(MapMenu *self);
void MapMenu_SetRowText(MapMenu *self, TextLabel *label, unsigned int entry);
void MapMenu_FillLabels(MapMenu *self, unsigned char *entries);
void MapMenu_FillShownLabels(MapMenu *self);
void MapMenu_BuildLists(MapMenu *self);
TextLabel *MapMenu_NextLabel(MapMenu *self);
void MapMenu_ResetLabels(MapMenu *self);
unsigned int MapMenu_RowIcon(MapMenu *self, unsigned int entry, int row);
void MapMenu_BuildRows(MapMenu *self);
void MapMenu_BuildShownRows(MapMenu *self);

/* map_menu_input.c */
int MapMenu_Activate(MapMenu *self);
int MapMenu_MoveFocus(MapMenu *self, u32 keys);
void MapMenu_ShowCursor(MapMenu *self);
void MapMenu_ReleaseCursor(MapMenu *self);
void MapMenu_PressCursor(MapMenu *self);
void MapMenu_MoveCursor(MapMenu *self);
void MapMenu_HideCursor(MapMenu *self);
int MapMenu_CursorY(MapMenu *self);
int MapMenu_CursorX(MapMenu *self);
void MapMenu_PlaceCursor(MapMenu *self);
int MapMenu_TouchListButton(MapMenu *self);
void MapMenu_KnobKeys(MapMenu *self);
void MapMenu_DragKnobTo(MapMenu *self, int place);
int MapMenu_TouchKnob(MapMenu *self);
int MapMenu_TouchMark(MapMenu *self);
int MapMenu_TouchRow(MapMenu *self);
void MapMenu_LeavePointer(MapMenu *self);
void MapMenu_EnterKeys(MapMenu *self);
void MapMenu_EnterTouch(MapMenu *self);
void MapMenu_SubPointer(MapMenu *self);
void MapMenu_SubKnobRelease(MapMenu *self);
void MapMenu_SubKnobHeld(MapMenu *self);
void MapMenu_SubKnobPress(MapMenu *self);
void MapMenu_SubRelease(MapMenu *self);
void MapMenu_SubPress(MapMenu *self);
void MapMenu_SubGlide(MapMenu *self);
void MapMenu_SubKeys(MapMenu *self);
void MapMenu_SubTrack(MapMenu *self);
void MapMenu_SubDragKnob(MapMenu *self);
void MapMenu_SubTouch(MapMenu *self);
int MapMenu_SelectTab(MapMenu *self, int tab);

/* map_menu_scene.c */
MapMenu *MapMenu_Destroy(MapMenu *self);
MapMenu *MapMenu_Delete(MapMenu *self);
void MapMenu_LoadObjFiles(void);
void MapMenu_FinishMap(MapMenu *self);
void MapMenu_ContinueMap(void);
void MapMenu_StartMap(void);
void MapMenu_LoadBgFiles(MapMenu *self);
void MapMenu_SetUpLayers(void);
void MapMenu_EndFrame(MapMenu *self);
void MapMenu_BeginInteractiveFrame(MapMenu *self);
void MapMenu_EndInteractiveFrame(MapMenu *self);
void MapMenu_BeginFrame(MapMenu *self);
void MapMenu_EndMembers(MapMenu *self);
void MapMenu_Setup(MapMenu *self);
void MapMenu_StateWipeOut(MapMenu *self);
void MapMenu_StateLeave(MapMenu *self);
void MapMenu_StateWipeIn(MapMenu *self);
void MapMenu_StateShow(MapMenu *self);
void MapMenu_StateList(MapMenu *self);
void MapMenu_StateMapEnd(MapMenu *self);
void MapMenu_StateMapMiddle(MapMenu *self);
void MapMenu_StateMapStart(MapMenu *self);
void MapMenu_StateLoad(MapMenu *self);
int MapMenu_CheckTabs(MapMenu *self);
int MapMenu_RequestDelete(MapMenu *self);
int MapMenu_Phase4(void);
int MapMenu_Phase3(void);
int MapMenu_RunInteractive(MapMenu *self);
void MapMenu_RunSubState(MapMenu *self);
int MapMenu_RunState(MapMenu *self);
int MapMenu_Draw(MapMenu *self);
int MapMenu_End(MapMenu *self);
int MapMenu_Start(MapMenu *self);
MapMenu *MapMenu_New(void);

#endif
