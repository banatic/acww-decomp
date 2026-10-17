/* The menu of overlay 90 (overlay group 0; vtable 0x02299820, include/cpp/ov090/Obj_ov090_02299820.h;
 * constructor MenuTabs_New, 0x1280 bytes): a menu scene (ov002/menu_scene.h) that keeps the
 * bar of tabs at the top of the sub screen ("menu/tag/obj1.bch", "obj2.bch", "obj.bpl" and
 * "obj%d.bpl") and starts the scene of each tab as an overlay group of its own. Its child
 * scenes call it as their parent process: the pockets (ov096/pockets_screen.h), the letter
 * writing (ov122/letter_write_scene.h) and the scenes of overlays 119, 126 and 133.
 *
 * - A child asks for another tab with MenuTabs_SelectTab (MENU_TAB_CLOSE closes the menu); the
 *   bar then shows that tab and, while a switch between the bar's tabs is under way, R and L
 *   still move it (MenuTabs_RunInteractive). When the child has closed (MenuTabs_ChildClosed),
 *   sub state 1 (MenuTabs_RequestTabGroup) asks for the tab's overlay group once ten frames
 *   have passed since the last R or L.
 * - The bar slides in by 2 pixels a frame while `shown` is set and out by 4 while it is not,
 *   up to 16 pixels below its place (MenuTabs_Draw).
 * - A child that changed the friend roster says so (MenuTabs_MarkRosterChanged); closing the
 *   menu then writes it to the card, and a failed write shows error message 31, which never
 *   closes. */
#ifndef CLEAN_OV090_MENU_TABS_H
#define CLEAN_OV090_MENU_TABS_H

#include "main/layer_load_task.h"
#include "ov002/error_message.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* The tabs (the base's byte MENU_TABS_BYTE_TAB). 0-6 are the bar's places, each the overlay
 * group given (MenuTabs_RequestTabGroup); 8-14 are scenes the bar does not show. */
enum MenuTab {
    MENU_TAB_POCKETS = 0,      /* group 1 in a room (data_020e54a8 set), else group 2 */
    MENU_TAB_1 = 1,            /* group 3 (overlay 121) */
    MENU_TAB_2 = 2,            /* group 4 (overlays 115, 114) */
    MENU_TAB_3 = 3,            /* group 5 (overlays 116, 114) */
    MENU_TAB_4 = 4,            /* group 6 (overlays 111, 95) */
    MENU_TAB_5 = 5,            /* group 7 (overlays 118, 117) */
    MENU_TAB_6 = 6,            /* group 36 (overlay 119) */
    MENU_TAB_CLOSE = 7,        /* the menu closes */
    MENU_TAB_LETTER_WRITE = 8, /* group 8 (overlays 122, 95) */
    MENU_TAB_9 = 9,            /* 9-12: group 15 (overlays 124, 126) in GroupParams mode tab + 15 */
    MENU_TAB_12 = 12,
    MENU_TAB_13 = 13, /* 13-14: group 43 (overlay 133) in GroupParams mode tab */
    MENU_TAB_14 = 14,
    MENU_TAB_NONE = 0xff /* `loaded_tab` before any */
};

#define MENU_TABS_LAST_BAR_TAB MENU_TAB_6
#define MENU_TABS_PLACES 8 /* the tab under an x: the bar's seven tabs and the close place */

/* The base's bytes 0x91-0x93 (MenuScene.unk_91) are the bar's. */
enum MenuTabsBaseByte {
    MENU_TABS_BYTE_DRAWN = 0, /* 0x91: the bar is drawn */
    MENU_TABS_BYTE_SLIDE = 1, /* 0x92: how far below its place, 0-16 pixels */
    MENU_TABS_BYTE_TAB = 2    /* 0x93: the current tab (MenuTab) */
};

#define MENU_TABS_SLIDE_IN 16

/* The friend roster (`roster`). */
enum MenuTabsRoster {
    MENU_TABS_ROSTER_SAVED = 0,
    MENU_TABS_ROSTER_CHANGED = 1, /* MenuTabs_MarkRosterChanged */
    MENU_TABS_ROSTER_WRITE = 2,   /* the menu closes: written next frame */
    MENU_TABS_ROSTER_FAILED = 3   /* the write failed; error message 31 is up */
};

/* The states (MenuScene.state), run by MenuTabs_RunState, and the sub states
 * (MenuScene.sub_state), run by MenuTabs_RunInteractive. */
enum MenuTabsState {
    MENU_TABS_STATE_SETUP = 0, /* MenuTabs_Setup */
    MENU_TABS_STATE_SHOW = 1,  /* MenuTabs_Show */
    MENU_TABS_STATE_HIDE = 2,  /* MenuTabs_Hide */
    MENU_TABS_STATES = 3
};

enum MenuTabsSubState {
    MENU_TABS_SUB_IDLE = 0,    /* MenuTabs_Idle */
    MENU_TABS_SUB_REQUEST = 1, /* MenuTabs_RequestTabGroup */
    MENU_TABS_SUB_ERROR = 2,   /* MenuTabs_UpdateError */
    MENU_TABS_SUB_STATES = 3
};

/* The phases the menu sets (MenuScene.phase; menu_scene.c's MenuScene_Update runs phase 0 by
 * the vtable's slot 0x48, 1 by 0x4c, 2 by 0x50 and 5 by 0x5c). */
enum MenuTabsPhase {
    MENU_TABS_PHASE_WAIT = 0,       /* the base's wait */
    MENU_TABS_PHASE_STATES = 1,     /* MenuTabs_RunState */
    MENU_TABS_PHASE_INTERACTIVE = 2 /* MenuTabs_RunInteractive */
};

#define MENU_TABS_TASKS 3

typedef struct MenuTabs {
    MenuScene base;                       /* 0x00: its bytes 0x91-0x93 are MenuTabsBaseByte's */
    u8 shown;                             /* 0x94: the bar slides in, else out */
    u8 switching;                         /* 0x95: a switch between the bar's tabs is under way */
    u8 loaded_tab;                        /* 0x96: the tab whose look is loaded (MENU_TAB_NONE) */
    u8 roster;                            /* 0x97: MenuTabsRoster */
    u8 opening;                           /* 0x98: no tab was selected since the menu started */
    u8 pad_99[3];                         /* 0x99 */
    LayerTaskPair tasks[MENU_TABS_TASKS]; /* 0x9c: the bar's characters, the tab's and its palette */
    u8 bar_chars[0x800];                  /* 0x144: "menu/tag/obj1.bch" */
    u8 tab_chars[0x800];                  /* 0x944: "menu/tag/obj2.bch": three characters a tab
                                            * (0x60 bytes), the lower row 0x400 bytes on */
    u8 palette[0x20];                     /* 0x1144: "menu/tag/obj%d.bpl" of the tab */
    ErrorMessage error;                   /* 0x1164 */
} MenuTabs;

MenuTabs *MenuTabs_Destroy(MenuTabs *self);
MenuTabs *MenuTabs_Delete(MenuTabs *self);
int MenuTabs_IsOpening(MenuTabs *self);
int MenuTabs_TabAtX(int x);
void MenuTabs_MarkRosterChanged(MenuTabs *self);
void MenuTabs_ShowTab(MenuTabs *self, int tab);
void MenuTabs_EndTasks(MenuTabs *self);
u8 MenuTabs_NextTab(u8 tab);
u8 MenuTabs_PreviousTab(u8 tab);
int MenuTabs_TabX(int tab);
void MenuTabs_SlideOut(MenuTabs *self);
void MenuTabs_SlideIn(MenuTabs *self);
int MenuTabs_TabAtTouch(void);
void MenuTabs_EndTasksOnClose(MenuTabs *self);
void MenuTabs_ResetBar(MenuTabs *self);
void MenuTabs_Hide(MenuTabs *self);
void MenuTabs_Show(MenuTabs *self);
void MenuTabs_Setup(MenuTabs *self);
int MenuTabs_UpdateError(MenuTabs *self);
void MenuTabs_RequestTabGroup(MenuTabs *self);
void MenuTabs_Idle(MenuTabs *self);
void MenuTabs_Close(MenuTabs *self);
u8 MenuTabs_ChildClosed(MenuTabs *self);
void MenuTabs_SelectTab(MenuTabs *self, u32 tab);
int MenuTabs_RequestDelete(MenuTabs *self);
int MenuTabs_Phase4(void);
int MenuTabs_Phase3(void);
int MenuTabs_RunInteractive(MenuTabs *self);
int MenuTabs_RunState(MenuTabs *self);
int MenuTabs_Draw(MenuTabs *self);
int MenuTabs_End(MenuTabs *self);
int MenuTabs_Start(MenuTabs *self);
MenuTabs *MenuTabs_New(void);

#endif
