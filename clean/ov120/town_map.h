/* The scene of overlay 120 (vtable 0x0229c650; constructor TownMap_New, 0x2770 bytes): the town
 * map. Overlay 92's dispatcher (ov092/menu_dispatch.h) opens it as overlay group 0x1b for
 * GroupParams mode 0x2f; it is a menu scene (ov002/menu_scene.h) drawn on the sub screen from
 * the files of "menu/map/" (b_map_bg.bpl, b_map_bg_0.bch, b_map_bg_1.bch, b_map_a_bg.bsc,
 * b_map_b_bg.bsc and the OBJs' b_map_obj.bpl, b_map_obj_0.bch, b_map_obj_1.bch).
 *
 * Overlay 117, loaded with it, draws the town's map into a block of characters for sub BG1
 * (TownMap_LoadMap) and fills a table of 17 places on it; the scene keeps them as marks: 3
 * extra marks (`extra_marks`) and 14 marks of houses and places (`marks`, TownMapMark).
 *
 * Beside the map, on sub BG3, the scene lists either the town's people (the current player,
 * the other players, the villagers) or five places, behind two tabs, as rows of a screen it
 * builds (TownMap_BuildListScreen) with a name label per row; with more than six rows the list
 * scrolls with a knob (a push button, ov002/push_button.h) on a bar. Picking a row makes the
 * mark it names blink and picking a mark highlights its row (TownMap_Select).
 *
 * QUIRK: as the overlay is, the wipe in always ends with the cursor on the map
 * (TOWN_MAP_FLAG_ON_MAP, which nothing clears) and so in TOWN_MAP_SUB_ON_MAP, where A, B, X or
 * a touch closes the scene; the list's key and touch handling (sub states 0-8) is not reached
 * from there. */
#ifndef CLEAN_OV120_TOWN_MAP_H
#define CLEAN_OV120_TOWN_MAP_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/push_button.h"
#include "ov117/town_map_image.h"
#include "types.h"

/* In `flags`. */
enum TownMapFlag {
    TOWN_MAP_FLAG_PLACES = 0x0001,       /* the places' list is shown, else the people's */
    TOWN_MAP_FLAG_LIST_UPLOAD = 0x0002,  /* `list_shown` is to be queued for sub BG3 */
    TOWN_MAP_FLAG_DRAWN = 0x0004,        /* the scene's OBJs are drawn (TownMap_Draw) */
    TOWN_MAP_FLAG_SCROLLABLE = 0x0008,   /* the list has more rows than fit: the knob is shown */
    TOWN_MAP_FLAG_SCROLLING = 0x0010,    /* `scroll` moves to `scroll_target` */
    TOWN_MAP_FLAG_MAP_UPLOAD = 0x0020,   /* `map_screen` is to be queued for sub BG1 */
    TOWN_MAP_FLAG_BLINK = 0x0040,        /* the picked row or mark blinks */
    TOWN_MAP_FLAG_LIST_DIRTY = 0x0080,   /* `list_shown` is to be made again from `list_screen` */
    TOWN_MAP_FLAG_BLINK_OFF = 0x0100,    /* the picked mark is in the off half of its blink */
    TOWN_MAP_FLAG_PICKED_ROW = 0x0200,   /* the pick was a row: its mark blinks, else the row does */
    TOWN_MAP_FLAG_ON_MAP = 0x0800,       /* the cursor is on the map at (`map_x`, `map_y`) */
    TOWN_MAP_FLAG_KNOB_HELD = 0x1000,    /* the knob was pressed with A and is held */
    TOWN_MAP_FLAG_PLACE_POINTER = 0x4000 /* the pointer is put at the cursor at once, once (nothing
                                            * in the overlay sets it) */
};

/* The scene's states (MenuScene.state, phase 1) and sub states (MenuScene.sub_state, phase 2),
 * in the order of their tables. */
enum TownMapState {
    TOWN_MAP_STATE_LOAD_BG = 0,    /* TownMap_StateLoadBg */
    TOWN_MAP_STATE_LOAD_MAP = 1,   /* TownMap_StateLoadMap */
    TOWN_MAP_STATE_SHOW_LIST = 2,  /* TownMap_StateShowList */
    TOWN_MAP_STATE_START_WIPE = 3, /* TownMap_StateStartWipeIn */
    TOWN_MAP_STATE_WIPE_IN = 4,    /* TownMap_StateWipeIn */
    TOWN_MAP_STATE_CLOSE = 5,      /* TownMap_StateStartWipeOut */
    TOWN_MAP_STATE_WIPE_OUT = 6,   /* TownMap_StateWipeOut */
    TOWN_MAP_STATES = 7
};

enum TownMapSubState {
    TOWN_MAP_SUB_TOUCH = 0,        /* TownMap_SubTouch: the pen picks */
    TOWN_MAP_SUB_DRAG = 1,         /* TownMap_SubDrag: the knob follows the pen */
    TOWN_MAP_SUB_KEYS = 2,         /* TownMap_SubKeys: the keys move the cursor */
    TOWN_MAP_SUB_GLIDE = 3,        /* TownMap_SubGlide: the pointer glides to the cursor */
    TOWN_MAP_SUB_PRESS = 4,        /* TownMap_SubPress: the pointer's press, then the pick */
    TOWN_MAP_SUB_RELEASE = 5,      /* TownMap_SubRelease: the pointer's release */
    TOWN_MAP_SUB_KNOB_PRESS = 6,   /* TownMap_SubKnobPress */
    TOWN_MAP_SUB_KNOB_HOLD = 7,    /* TownMap_SubKnobHold: up and down scroll while A is held */
    TOWN_MAP_SUB_KNOB_RELEASE = 8, /* TownMap_SubKnobRelease */
    TOWN_MAP_SUB_ON_MAP = 9,       /* TownMap_SubOnMap: A, B, X or a touch closes */
    TOWN_MAP_SUB_STATES = 10
};

/* The places of the key cursor (`cursor`). */
enum TownMapCursor {
    TOWN_MAP_CURSOR_PEOPLE_TAB = 0, /* at (0xd8, 0x40) */
    TOWN_MAP_CURSOR_PLACES_TAB = 1, /* at (0xbc, 0x40) */
    TOWN_MAP_CURSOR_ROW_FIRST = 2,  /* 2-7: the six rows in view, at (0xa0, 0x58 + 16 each) */
    TOWN_MAP_CURSOR_ROW_LAST = 7,
    TOWN_MAP_CURSOR_KNOB = 8 /* at the knob's face */
};

/* The values of a list's rows (`people`, `places`). */
enum TownMapRowValue {
    TOWN_MAP_ROW_NONE = 0,
    TOWN_MAP_ROW_SELF = 1,           /* the current player */
    TOWN_MAP_ROW_PLAYER_FIRST = 2,   /* 2-5: the town's player 0-3 */
    TOWN_MAP_ROW_VILLAGER_FIRST = 6, /* 6-13: the villager of place 0-7 (VillagerRoster) */
    TOWN_MAP_ROW_PLACE_FIRST = 14,   /* 14-18: place 0-4, named by menu message 0x96 + place */
    TOWN_MAP_ROW_PLACE_LAST = 18
};

/* What TownMap_Select is given: none, a mark (1 + its index) or a row of the list shown
 * (15 + the row). */
enum TownMapTarget {
    TOWN_MAP_TARGET_NONE = 0,
    TOWN_MAP_TARGET_MARK_FIRST = 1,  /* 1-14 */
    TOWN_MAP_TARGET_HOUSES_LAST = 9, /* 1-9: the marks of the people's houses */
    TOWN_MAP_TARGET_MARK_LAST = 14,
    TOWN_MAP_TARGET_ROW_FIRST = 15, /* 15-27 */
    TOWN_MAP_TARGET_ROW_LAST = 27
};

/* The marks (`marks`): 0-7 the villagers' houses, 8 the players' house, 9-13 places. A row
 * index of 13 (`picked_row`) stands for the players' rows together; 14 is none, also for a
 * mark. */
#define TOWN_MAP_MARKS 14
#define TOWN_MAP_EXTRA_MARKS 3
#define TOWN_MAP_MARK_PLAYERS_HOUSE 8
#define TOWN_MAP_ROW_PLAYERS 13
#define TOWN_MAP_NONE 14
#define TOWN_MAP_ROWS 13
#define TOWN_MAP_ROWS_IN_VIEW 6
#define TOWN_MAP_LABELS 13

/* The pad's keys (PadState). */
#define TOWN_MAP_KEY_A 0x0001
#define TOWN_MAP_KEY_B 0x0002
#define TOWN_MAP_KEY_UP 0x0040
#define TOWN_MAP_KEY_DOWN 0x0080
#define TOWN_MAP_KEY_X 0x0400
#define TOWN_MAP_KEY_Y 0x0800

/* A mark's kind of none (not drawn, not touched). */
#define TOWN_MAP_KIND_NONE 0x0c

/* A mark on the map: its OBJ's place and kind (TownMap_DrawMark draws OBJ 0xc0 + 2 * kind; in
 * the extra marks bit 7 of the kind flips it). */
typedef struct TownMapMark {
    u8 x;
    u8 y;
    u8 kind;
} TownMapMark;

typedef struct TownMap {
    MenuScene base;                                /* 0x00 */
    s32 wipe_y;                                    /* 0x94: MenuScene_WipeOffsetY's, the OBJs are drawn that far down */
    u16 scroll;                                    /* 0x98: the list's scroll in pixels (16 a row) */
    u16 scroll_target;                             /* 0x9a */
    u16 flags;                                     /* 0x9c: TownMapFlag */
    u8 player_x;                                   /* 0x9e: where the player's mark is drawn */
    u8 player_y;                                   /* 0x9f */
    u8 label_count;                                /* 0xa0: the labels taken this frame (TownMap_TakeLabel) */
    u8 people_count;                               /* 0xa1: rows of `people` */
    u8 place_count;                                /* 0xa2: rows of `places` */
    u8 first_row;                                  /* 0xa3: the row at the top of `list_shown`; 0xff to make it again */
    u8 knob_pos;                                   /* 0xa4: the knob on its bar, 0-0x58 */
    u8 drag_y;                                     /* 0xa5: the pen's y when the knob was taken */
    u8 drag_knob_pos;                              /* 0xa6: `knob_pos` then */
    u8 blink_timer;                                /* 0xa7: frames of the blink, from 15 */
    u8 picked_mark;                                /* 0xa8: the mark picked, TOWN_MAP_NONE for none */
    u8 picked_row;                                 /* 0xa9: its row, TOWN_MAP_ROW_PLAYERS or TOWN_MAP_NONE */
    u8 return_sub_state;                           /* 0xaa: where TownMap_SubGlide goes back to */
    u8 cursor;                                     /* 0xab: TownMapCursor */
    u8 map_mark;                                   /* 0xac: the mark under the cursor on the map */
    u8 map_x;                                      /* 0xad: the cursor on the map */
    u8 map_y;                                      /* 0xae */
    u8 blink_frame;                                /* 0xaf: the player's mark is drawn in 12 of each 16 frames */
    LayerTask list_task;                           /* 0xb0: `list_shown` to sub BG3 */
    LayerTask map_task;                            /* 0xd4: `map_screen` to sub BG1 */
    TextLabel labels[TOWN_MAP_LABELS];             /* 0xf8: the rows' names and the title */
    PushButton knob;                               /* 0x674: the list's knob */
    Glider pointer;                                /* 0x6bc: the pointing hand at the cursor */
    u16 map_screen[0x400];                         /* 0x720: sub BG1's screen (b_map_a_bg.bsc), its bar coloured */
    u16 list_shown[0x400];                         /* 0xf20: sub BG3's screen: `list_screen` without the rows out of view */
    u16 list_screen[0x400];                        /* 0x1720: the list's rows with their icons and highlight */
    u16 list_template[0x400];                      /* 0x1f20: b_map_b_bg.bsc, holding the icons at the rows */
    u8 people[TOWN_MAP_ROWS];                      /* 0x2720: TownMapRowValue */
    u8 places[TOWN_MAP_ROWS];                      /* 0x272d */
    TownMapMark extra_marks[TOWN_MAP_EXTRA_MARKS]; /* 0x273a: places 0-2 of overlay 117's table */
    TownMapMark marks[TOWN_MAP_MARKS];             /* 0x2743: its places 3-16 */
    TownMapMark past_marks; /* 0x276d: padding; mark TOWN_MAP_NONE reads it (TownMap_MapCursorFromRow) */
} TownMap;

/* town_map.c: the scene */
TownMap *TownMap_Destroy(TownMap *self);
TownMap *TownMap_Delete(TownMap *self);
void TownMap_MarkDestruct(void *mark);
void TownMap_MarkConstruct(void *mark);
void TownMap_ClearFlags(TownMap *self, unsigned short mask);
void TownMap_SetFlags(TownMap *self, unsigned short mask);
int TownMap_TestFlags(TownMap *self, unsigned short mask);
int TownMap_Pick(TownMap *self);
int TownMap_MoveCursor(TownMap *self, u32 keys);
void TownMap_ShowPointer(TownMap *self);
void TownMap_PressPointer(TownMap *self);
void TownMap_ReleasePointer(TownMap *self);
void TownMap_GlideToCursor(TownMap *self);
void TownMap_HidePointer(TownMap *self);
int TownMap_CursorY(TownMap *self);
int TownMap_CursorX(TownMap *self);
void TownMap_EnterCursor(TownMap *self);
void TownMap_EnterKeys(TownMap *self);
void TownMap_EnterTouch(TownMap *self);
void TownMap_SubOnMap(TownMap *self);
void TownMap_SubKnobRelease(TownMap *self);
void TownMap_SubKnobHold(TownMap *self);
void TownMap_SubKnobPress(TownMap *self);
void TownMap_SubRelease(TownMap *self);
void TownMap_SubPress(TownMap *self);
void TownMap_SubGlide(TownMap *self);
void TownMap_SubKeys(TownMap *self);
void TownMap_SubDrag(TownMap *self);
void TownMap_SubTouch(TownMap *self);
void TownMap_LoadObjFiles(void);
void TownMap_LoadMap(TownMap *self);
void TownMap_LoadBg(TownMap *self);
void TownMap_SetUpLayers(void);
void TownMap_EndFrame(TownMap *self);
void TownMap_BeginInteractive(TownMap *self);
void TownMap_UpdateScreens(TownMap *self);
void TownMap_BeginFrame(TownMap *self);
void TownMap_Teardown(TownMap *self);
void TownMap_Setup(TownMap *self);
void TownMap_StateWipeOut(TownMap *self);
void TownMap_StateStartWipeOut(TownMap *self);
void TownMap_StateWipeIn(TownMap *self);
void TownMap_StateStartWipeIn(TownMap *self);
void TownMap_StateShowList(TownMap *self);
void TownMap_StateLoadMap(TownMap *self, int unused_op, u32 unused_0, u32 unused_1);
void TownMap_StateLoadBg(TownMap *self);
int TownMap_RequestClose(TownMap *self);
int TownMap_RequestDelete(TownMap *self);
int TownMap_Phase4(void);
int TownMap_Phase3(void);
int TownMap_RunInteractive(TownMap *self);
void TownMap_RunSubState(TownMap *self);
int TownMap_RunState(TownMap *self);
int TownMap_Draw(TownMap *self);
int TownMap_End(TownMap *self);
int TownMap_Start(TownMap *self);
TownMap *TownMap_New(void);

/* town_map_list.c: the list, its scroll, the marks and the pick */
void TownMap_MapCursorFromRow(TownMap *self);
void TownMap_StopBlink(TownMap *self);
void TownMap_StartBlink(TownMap *self);
void TownMap_StepBlink(TownMap *self);
int TownMap_TouchTabs(TownMap *self);
void TownMap_ScrollByKeys(TownMap *self);
void TownMap_ScrollByDrag(TownMap *self);
int TownMap_TouchKnob(TownMap *self);
void TownMap_StepScroll(TownMap *self);
int TownMap_IsScrolling(TownMap *self);
void TownMap_SetScrollTarget(TownMap *self, unsigned short scroll);
void TownMap_SetScroll(TownMap *self, unsigned short scroll);
void TownMap_ScrollToPickedRow(TownMap *self);
int TownMap_ScrollToSwitchedRow(TownMap *self);
unsigned char TownMap_MarkOfTarget(TownMap *self, unsigned int target);
unsigned char TownMap_RowOfTarget(TownMap *self, unsigned int target);
void TownMap_HighlightRow(TownMap *self, int row);
void TownMap_Select(TownMap *self, unsigned int target);
unsigned char TownMap_FindMarkAt(TownMap *self, int x, int y);
int TownMap_TouchMap(TownMap *self);
void TownMap_ReadMarks(TownMap *self, TownMapMarker *places);
void TownMap_DrawMark(TownMap *self, int x, int y, int kind, int flip, int palette);
int TownMap_TouchList(TownMap *self);
unsigned int TownMap_MaxScroll(TownMap *self);
unsigned char TownMap_RowCount(TownMap *self);
u8 *TownMap_Rows(TownMap *self);
void TownMap_ShowList(TownMap *self);
void TownMap_ShowPlaces(TownMap *self);
void TownMap_ShowPeople(TownMap *self);
void TownMap_SetRowText(TownMap *self, TextLabel *label, unsigned int value);
void TownMap_MakeLabels(TownMap *self, u8 *rows);
void TownMap_MakeShownLabels(TownMap *self);
void TownMap_BuildLists(TownMap *self);
TextLabel *TownMap_TakeLabel(TownMap *self);
void TownMap_ReleaseLabels(TownMap *self);
unsigned int TownMap_RowIcon(TownMap *self, unsigned int value, int row);
void TownMap_BuildListScreen(TownMap *self);
void TownMap_MakeShownList(TownMap *self);

#endif
