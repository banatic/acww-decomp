/* The scene of the two catalog tabs of the menu: the fish catalog (overlay 115, tab 2 of the
 * menu's bar, ov090/menu_tabs.h, overlay group 4 with overlay 114) and the insect catalog
 * (overlay 116, tab 3, group 5 with overlay 114). Both overlays hold the same code at the same
 * addresses (vtable 0x0229e8b8, constructor at 0x0229e7e0, 0x1430 bytes), differing only in
 * the tab they are and the kind of list they ask overlay 114 for (0 fish, "menu/fish_pic"; 1
 * insects, "menu/bug_pic"). This header holds what the two share; fish_catalog.h and
 * ov116/insect_catalog.h declare each overlay's functions.
 *
 * The scene is a menu scene (ov002/menu_scene.h) built around overlay 114's catalog list at
 * 0xf8 (its background "menu/fish/...", its entries, its page and scroll arrows, its scroll
 * handle). A cursor sprite (a Glider0, ov002/glide.h) follows the list's cursor while the scene
 * is used with the buttons; with the pen the list is touched directly.
 *
 * The list's cursor is on one of its places (byte 0x12bc of the list): 0 and 1 the page
 * arrows, 2 and 3 the scroll arrows, 4 the scroll handle, 5-12 the menu bar's eight places
 * (tab = place - 5) and 13 on the list's entries. */
#ifndef CLEAN_OV115_CATALOG_SCENE_H
#define CLEAN_OV115_CATALOG_SCENE_H

#include "main/text_label.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "types.h"

/* The kinds of list overlay 114 shows (byte 0x12b7 of the list). */
enum CatalogKind { CATALOG_KIND_FISH = 0, CATALOG_KIND_INSECTS = 1 };

/* The scene's flags (`flags`). */
enum CatalogSceneFlag {
    CATALOG_SCENE_FLAG_DRAWN = 0x0001 /* set once the setup is done: the scene draws */
};

/* The states (MenuScene.state, run in phase 1 by the scene's RunState). */
enum CatalogSceneState {
    CATALOG_SCENE_STATE_SETUP = 0,          /* _Setup */
    CATALOG_SCENE_STATE_WIPE_IN = 1,        /* _WipeIn */
    CATALOG_SCENE_STATE_START_WIPE_OUT = 2, /* _StartWipeOut (set by _SelectTab) */
    CATALOG_SCENE_STATE_WIPE_OUT = 3,       /* _WipeOut */
    CATALOG_SCENE_STATES = 4
};

/* The sub states (MenuScene.sub_state, run in phase 2 by the scene's RunSubState). */
enum CatalogSceneSubState {
    CATALOG_SCENE_SUB_TOUCH_IDLE = 0,   /* _IdleByTouch */
    CATALOG_SCENE_SUB_DRAG = 1,         /* _DragByTouch: the pen holds the scroll handle */
    CATALOG_SCENE_SUB_KEYS_IDLE = 2,    /* _IdleByKeys */
    CATALOG_SCENE_SUB_CURSOR_GLIDE = 3, /* _WaitCursorGlide */
    CATALOG_SCENE_SUB_PRESS = 4,        /* _FinishPress: A pressed on the list's cursor */
    CATALOG_SCENE_SUB_RELEASE = 5,      /* _FinishRelease */
    CATALOG_SCENE_SUB_SCROLL_START = 6, /* _StartScrollByKeys */
    CATALOG_SCENE_SUB_SCROLL_HOLD = 7,  /* _ScrollWhileHeld */
    CATALOG_SCENE_SUB_SCROLL_END = 8,   /* _EndScrollByKeys */
    CATALOG_SCENE_SUB_STATES = 9
};

/* The phases the scene sets (MenuScene.phase; MenuScene_Update runs phase 0 by the vtable's
 * slot 0x48, 1 by 0x4c, 2 by 0x50, 3 by 0x54, 4 by 0x58 and 5 by 0x5c). */
enum CatalogScenePhase {
    CATALOG_SCENE_PHASE_STATES = 1,      /* the states */
    CATALOG_SCENE_PHASE_INTERACTIVE = 2, /* the sub states */
    CATALOG_SCENE_PHASE_DELETE = 5       /* the scene asks to be deleted */
};

/* The display layers the list is drawn on (main/display_layers.h). */
#define CATALOG_SCENE_LAYER_A 3
#define CATALOG_SCENE_LAYER_B 6
#define CATALOG_SCENE_LAYER_C 4

#define CATALOG_SCENE_LIST_SIZE 0x12c0

typedef struct CatalogScene {
    MenuScene base;                   /* 0x00 */
    Glider cursor;                    /* 0x94: a Glider0 */
    u8 list[CATALOG_SCENE_LIST_SIZE]; /* 0xf8: overlay 114's catalog list (func_ov114_0229da18) */
    TextLabel label;                  /* 0x13b8 */
    s32 wipe_y;                       /* 0x1424: MenuScene_WipeOffsetY's, the list's y offset */
    u16 flags;                        /* 0x1428: CatalogSceneFlag */
    u8 unk_142a;                      /* 0x142a: cleared with the label's box */
    u8 pad_142b;                      /* 0x142b */
    u8 return_sub_state;              /* 0x142c: the sub state to go back to */
    u8 pad_142d[3];                   /* 0x142d */
} CatalogScene;

/* Overlay 114's catalog list, called with the list (0xf8 of the scene). */
extern void *func_ov114_0229da18(void *list);                                           /* constructor */
extern void *func_ov114_0229d9d8(void *list);                                           /* destructor */
extern void func_ov114_0229d8d0(u8 *list, u8 layer_a, u8 layer_b, u8 layer_c, u8 kind); /* starts */
extern int func_ov114_0229c60c(u8 *list);               /* the bar's tab under the cursor, or -1 */
extern int func_ov114_0229c5f4(u8 *list);               /* the cursor is on a page arrow */
extern int func_ov114_0229c690(void *list);             /* the cursor's x */
extern int func_ov114_0229c628(void *list);             /* the cursor's y */
extern void func_ov114_0229c3ac(void *list);            /* the cursor's entry brought into view */
extern int func_ov114_0229c410(void *list, void *keys); /* the cursor moved by the keys */
extern int func_ov114_0229c2c8(void *list);             /* A on the cursor's place */
extern int func_ov114_0229d1dc(void *list);
extern void func_ov114_0229d52c(void *list, int y); /* the scroll handle placed */
extern void func_ov114_0229d244(void *list);        /* a scroll step */
extern void func_ov114_0229d220(void *list);
extern int func_ov114_0229d2d8(void *list);
extern void func_ov114_0229d304(void *list);              /* the pen let go of the handle */
extern void func_ov114_0229d32c(void *list, int x);       /* the handle dragged to x */
extern int func_ov114_0229d564(void *list, int x, int y); /* a page arrow touched */
extern int func_ov114_0229d3f4(void *list, int x, int y); /* the handle or a scroll arrow touched */
extern int func_ov114_0229ca50(void *list, int x, int y); /* an entry touched */
extern void func_ov114_0229d688(void *list);              /* the OBJ files loaded */
extern void func_ov114_0229cadc(void *list);              /* the entries filled */
extern void func_ov114_0229d700(void *list);              /* the background files loaded */
extern void func_ov114_0229c8dc(void *list);
extern void func_ov114_0229d824(void *list);        /* the end of a frame */
extern void func_ov114_0229d87c(void *list);        /* the start of a frame */
extern void func_ov114_0229d8ac(void *list);        /* the end of the scene */
extern void func_ov114_0229c8b4(void *list);        /* the wipe out begins */
extern void func_ov114_0229d5b8(void *list, int y); /* draws the arrows and the handle */
extern void func_ov114_0229cbe4(void *list, int y); /* draws the entries */
extern void func_ov114_0229d54c(void *list);        /* draws its member at 0x121c */

#endif
