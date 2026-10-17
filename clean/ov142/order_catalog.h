/* The scene of overlay 142 (vtable 0x0229c3e8, include/cpp/ov142/Obj_ov142_0229c3e8.h;
 * constructor OrderCatalog_New, 0x30e0 bytes, named by the profile at 0x0229c2c8): a menu
 * scene (ov002/menu_scene.h) that shows the catalog of the items the current player has had and
 * takes an order from it, as the evidence says:
 *
 * - overlay 92's dispatcher opens it as overlay group 0x23 for GroupParams' mode 0x3e
 *   (ov092/menu_dispatch.c), which the shop's clerk asks for when the player orders from the
 *   catalog (ov050/nook_clerk_talk.c, NOOK_CLERK_SCREEN_ORDER);
 * - its files are "menu/catalog/..." (OrderCatalog_LoadObjGraphics, OrderCatalog_LoadBgGraphics);
 * - the item ordered is handed back through GroupParams_SetItemB, with GroupParams_SetC4C(1)
 *   (OrderCatalog_Accept), which the clerk reads; a quit hands back GroupParams_SetC4C(0);
 * - each list holds the item codes of one category the player's item record (main/item_record.h)
 *   has, among those ItemTraits_FlagBit3 lists (OrderCatalog_CollectItems); the picked item shows
 *   its member price (ItemTraits_MemberPrice), or message 0x53 when ItemTraits_FlagBit4 is set,
 *   and then cannot be ordered;
 * - in a room the picked item is also shown in the room (ov004/room_preview.h).
 *
 * The screen: nine category tabs down the left (cursor places 0-8), nine rows of the category's
 * list in the middle (places 9-17), a scroll bar on the right with its thumb (a push button) and
 * two arrows, the order button (place 18) and the panel's quit button (button 6, place 19). An
 * order asks for a confirmation with the panel's buttons 3 (accept) and 4 (decline). */
#ifndef CLEAN_OV142_ORDER_CATALOG_H
#define CLEAN_OV142_ORDER_CATALOG_H

#include "main/layer_load_task.h"
#include "main/text_label.h"
#include "ov002/button_panel.h"
#include "ov002/glide.h"
#include "ov002/menu_scene.h"
#include "ov002/push_button.h"
#include "types.h"

#define ORDER_CATALOG_CATEGORIES 9
#define ORDER_CATALOG_ROWS 9 /* rows of the list on screen */
#define ORDER_CATALOG_LABELS 14
#define ORDER_CATALOG_TASKS 4

/* The loads of `tasks`. */
enum OrderCatalogTask {
    ORDER_CATALOG_TASK_LIST_SCREEN = 0,   /* layer 4's screen */
    ORDER_CATALOG_TASK_FRAME_SCREEN = 1,  /* layer 6's screen */
    ORDER_CATALOG_TASK_ROW_PALETTE = 2,   /* layer 4's palette 3 */
    ORDER_CATALOG_TASK_PICKED_PALETTE = 3 /* layer 4's palette 4 */
};

/* The item code of no item (main/item_code.h). */
#define ORDER_CATALOG_NO_ITEM 0xfff1

/* The categories (`category`) and the item codes each list takes. */
enum OrderCatalogCategory {
    ORDER_CATALOG_CATEGORY_0 = 0, /* 0x3000-0x4ba3, every fourth, but the ranges of 3-5, 7, 8 and
                                   * 0x42a4-0x4463 */
    ORDER_CATALOG_CATEGORY_1 = 1, /* the wallpaper, 0x1100-0x1143 */
    ORDER_CATALOG_CATEGORY_2 = 2, /* the carpets, 0x1144-0x1187 */
    ORDER_CATALOG_CATEGORY_3 = 3, /* 0x3984-0x3d83, every fourth */
    ORDER_CATALOG_CATEGORY_4 = 4, /* 0x3e24-0x3ea3, every fourth */
    ORDER_CATALOG_CATEGORY_5 = 5, /* 0x3fa4-0x40a3, 0x40a4-0x4123 and 0x4124-0x4223, every fourth */
    ORDER_CATALOG_CATEGORY_6 = 6, /* the items in piles, 0x1003-0x10ff, every fourth */
    ORDER_CATALOG_CATEGORY_7 = 7, /* 0x45dc-0x47d7, every fourth */
    ORDER_CATALOG_CATEGORY_8 = 8, /* 0x450c-0x45db, every fourth */
    ORDER_CATALOG_NO_CATEGORY = 9 /* `category` and `picked_category` at the setup */
};

/* In `flags`. */
enum OrderCatalogFlag {
    ORDER_CATALOG_FLAG_DRAWN = 0x0001,        /* the scene is drawn (OrderCatalog_Draw) */
    ORDER_CATALOG_FLAG_LIST_SCREEN = 0x0002,  /* the list's screen is to be queued */
    ORDER_CATALOG_FLAG_ROWS = 0x0004,         /* the rows' labels are to be set */
    ORDER_CATALOG_FLAG_COUNTS = 0x0008,       /* the counts' labels are to be set */
    ORDER_CATALOG_FLAG_FRAME_SCREEN = 0x0010, /* the frame's screen is to be queued */
    ORDER_CATALOG_FLAG_ORDERABLE = 0x0020,    /* the picked item can be ordered */
    ORDER_CATALOG_FLAG_PREVIEW = 0x0040,      /* the picked item is shown in the room */
    ORDER_CATALOG_FLAG_KEEP_CURSOR = 0x0080,  /* the browse by keys keeps the cursor once */
    ORDER_CATALOG_FLAG_NO_BAR = 0x0100,       /* the list does not scroll: no scroll bar */
    ORDER_CATALOG_FLAG_DIMMED = 0x0200,       /* the list is dimmed (the confirmation) */
    ORDER_CATALOG_FLAG_AT_TOP = 0x0400,       /* the list is scrolled to its top */
    ORDER_CATALOG_FLAG_AT_BOTTOM = 0x0800,    /* ... to its bottom */
    ORDER_CATALOG_FLAG_UP_HELD = 0x1000,      /* the up arrow is held */
    ORDER_CATALOG_FLAG_DOWN_HELD = 0x2000     /* the down arrow is held */
};

/* The places of the cursor (`cursor`), and what OrderCatalog_TouchedPlace answers. */
enum OrderCatalogPlace {
    ORDER_CATALOG_PLACE_TAB = 0, /* 0-8: the tab of category n */
    ORDER_CATALOG_PLACE_LAST_TAB = 8,
    ORDER_CATALOG_PLACE_ROW = 9, /* 9-17: the row n - 9 on screen */
    ORDER_CATALOG_PLACE_LAST_ROW = 0x11,
    ORDER_CATALOG_PLACE_ORDER = 0x12,   /* the order button */
    ORDER_CATALOG_PLACE_QUIT = 0x13,    /* the panel's button 6 */
    ORDER_CATALOG_PLACE_THUMB = 0x14,   /* the scroll bar's thumb */
    ORDER_CATALOG_PLACE_UP = 0x15,      /* the up arrow */
    ORDER_CATALOG_PLACE_DOWN = 0x16,    /* the down arrow */
    ORDER_CATALOG_PLACE_ACCEPT = 0x17,  /* the panel's button 3 (the confirmation) */
    ORDER_CATALOG_PLACE_DECLINE = 0x18, /* the panel's button 4 */
    ORDER_CATALOG_PLACE_NONE = 0x19
};

/* The fade of the rows' text (colour 15 of the rows' palettes, towards colour 8) on a change of
 * category (`fade_state`). */
enum OrderCatalogFade {
    ORDER_CATALOG_FADE_NONE = 0,
    ORDER_CATALOG_FADE_OUT = 1, /* down to step 0, then the category changes */
    ORDER_CATALOG_FADE_IN = 2   /* up to step 3 */
};

/* The states, run from the table of OrderCatalog_RunState (MenuScene_SetState). */
enum OrderCatalogState {
    ORDER_CATALOG_STATE_START = 0,          /* OrderCatalog_StartWipeIn */
    ORDER_CATALOG_STATE_WIPE_IN = 1,        /* OrderCatalog_WipeIn */
    ORDER_CATALOG_STATE_START_WIPE_OUT = 2, /* OrderCatalog_StartWipeOut */
    ORDER_CATALOG_STATE_WIPE_OUT = 3,       /* OrderCatalog_WipeOut */
    ORDER_CATALOG_STATE_CONFIRM_OUT = 4,    /* OrderCatalog_PanelOutToConfirm */
    ORDER_CATALOG_STATE_CONFIRM_IN = 5,     /* OrderCatalog_PanelInToConfirm */
    ORDER_CATALOG_STATE_BACK_OUT = 6,       /* OrderCatalog_PanelOutToBrowse */
    ORDER_CATALOG_STATE_BACK_IN = 7,        /* OrderCatalog_PanelInToBrowse */
    ORDER_CATALOG_STATES = 8
};

/* The sub states, run from the table of OrderCatalog_RunSubState (MenuScene_SetSubState). */
enum OrderCatalogSubState {
    ORDER_CATALOG_SUB_TOUCH_BROWSE = 0,   /* OrderCatalog_BrowseByTouch */
    ORDER_CATALOG_SUB_THUMB_DRAG = 1,     /* OrderCatalog_DragThumbByTouch */
    ORDER_CATALOG_SUB_TRACK_PRESS = 2,    /* OrderCatalog_PressTrackByTouch */
    ORDER_CATALOG_SUB_ARROW_TOUCH = 3,    /* OrderCatalog_HoldArrowByTouch */
    ORDER_CATALOG_SUB_BROWSE = 4,         /* OrderCatalog_BrowseByKeys */
    ORDER_CATALOG_SUB_THUMB_KEYS = 5,     /* OrderCatalog_MoveThumbByKeys */
    ORDER_CATALOG_SUB_THUMB_RELEASE = 6,  /* OrderCatalog_WaitThumbRelease */
    ORDER_CATALOG_SUB_ARROW_KEYS = 7,     /* OrderCatalog_HoldArrowByKeys */
    ORDER_CATALOG_SUB_SPRITE_MOVE = 8,    /* OrderCatalog_WaitCursorSprite */
    ORDER_CATALOG_SUB_PRESS = 9,          /* OrderCatalog_WaitPressThenAct */
    ORDER_CATALOG_SUB_PRESS_END = 10,     /* OrderCatalog_WaitPressEnd */
    ORDER_CATALOG_SUB_TOUCH_CONFIRM = 11, /* OrderCatalog_ConfirmByTouch */
    ORDER_CATALOG_SUB_CONFIRM = 12,       /* OrderCatalog_ConfirmByKeys */
    ORDER_CATALOG_SUB_PANEL_PRESSED = 13, /* OrderCatalog_FollowPanelPress */
    ORDER_CATALOG_SUB_STATES = 14
};

typedef struct OrderCatalog {
    MenuScene base;                         /* 0x0000 */
    s32 wipe_y;                             /* 0x0094: MenuScene_WipeOffsetY's at OrderCatalog_ScrollWithWipe */
    s32 panel_wipe_y;                       /* 0x0098: the same, also each frame of the panel's wipes */
    s32 scroll;                             /* 0x009c: the list's scroll, in pixels (16 a row) */
    s32 scroll_target;                      /* 0x00a0: where OrderCatalog_StepScroll takes it */
    s32 scroll_max;                         /* 0x00a4: (rows - 8) * 16, at least 0 */
    s32 thumb;                              /* 0x00a8: the thumb's place on the bar, 0-90 */
    s32 grab_offset;                        /* 0x00ac: the thumb's place less the touch's y when grabbed */
    s32 thumb_cued;                         /* 0x00b0: the thumb's place at its last scroll cue */
    s16 top_row;                            /* 0x00b4: the list's row at the top (scroll / 16) */
    u16 flags;                              /* 0x00b6: OrderCatalogFlag */
    s16 picked_row;                         /* 0x00b8: the row of the picked item in its list, -1 for none */
    u8 return_sub_state;                    /* 0x00ba: the sub state to go back to */
    u8 labels_used;                         /* 0x00bb: the labels handed out this frame (OrderCatalog_NextLabel) */
    u8 category;                            /* 0x00bc: the category shown, OrderCatalogCategory */
    u8 tab;                                 /* 0x00bd: the tab highlighted (the category to show) */
    u8 picked_category;                     /* 0x00be: the category of the picked item */
    u8 order_palette;                       /* 0x00bf: the order button's palette: 5 orderable, 6 not, 7 ordered */
    u8 cursor;                              /* 0x00c0: OrderCatalogPlace */
    u8 fade_step;                           /* 0x00c1: the rows' fade, 0 (faded) to 3 */
    u8 fade_state;                          /* 0x00c2: OrderCatalogFade */
    u8 pad_c3;                              /* 0x00c3 */
    u16 counts[ORDER_CATALOG_CATEGORIES];   /* 0x00c4: the items in each list */
    u16 listed[ORDER_CATALOG_CATEGORIES];   /* 0x00d6: the items ItemTraits_FlagBit3 lists */
    Glider cursor_sprite;                   /* 0x00e8: a Glider0 */
    PushButton thumb_button;                /* 0x014c: the scroll bar's thumb */
    ButtonPanel panel;                      /* 0x0194 */
    TextLabel labels[ORDER_CATALOG_LABELS]; /* 0x0360 */
    LayerTask tasks[ORDER_CATALOG_TASKS];   /* 0x0948: the list's screen, the frame's screen and
                                                * the two faded palettes (ORDER_CATALOG_TASK_*) */
    u16 list0[0x400];                       /* 0x09d8: the lists of item codes */
    u16 list1[0x44];                        /* 0x11d8 */
    u16 list2[0x44];                        /* 0x1260 */
    u16 list3[0x100];                       /* 0x12e8 */
    u16 list4[0x20];                        /* 0x14e8 */
    u16 list5[0xa0];                        /* 0x1528 */
    u16 list6[0x40];                        /* 0x1668 */
    u16 list7[0x7f];                        /* 0x16e8 */
    u16 list8[0x34];                        /* 0x17e6 */
    u16 shown[ORDER_CATALOG_ROWS];          /* 0x184e: the item each row's label shows, by the
                                                * row's place in the screen's ring */
    u16 rows_screen[0x400];                 /* 0x1860: "b_bg.bsc", the list's rows */
    u16 list_screen[0x400];                 /* 0x2060: the list's screen, built from it */
    u16 frame_screen[0x400];                /* 0x2860: "a_bg.bsc" */
    u16 row_palette[0x10];                  /* 0x3060: "bg_3.bpl", the rows' (layer 4's palette 3) */
    u16 row_palette_shown[0x10];            /* 0x3080: as faded */
    u16 picked_palette[0x10];               /* 0x30a0: "bg_4.bpl", the picked row's (palette 4) */
    u16 picked_palette_shown[0x10];         /* 0x30c0: as faded */
} OrderCatalog;

#endif
