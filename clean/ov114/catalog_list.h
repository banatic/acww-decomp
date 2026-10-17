/* Overlay 114's catalog list (0x12c0 bytes, constructor CatalogList_Construct): the list of the
 * fish or the insects the menu's two catalog tabs show (overlay 115, tab 2, and overlay 116, tab
 * 3, which keep it at 0xf8 of their scene, ov115/catalog_scene.h). Overlay groups 4 and 5 load it
 * with either.
 *
 * - The list's 56 entries (`count`) are the item codes 0x12e8-0x131f for the fish (kind 0) and
 *   0x12b0-0x12e7 for the insects (kind 1, main/item_record.h). The entries the current player
 *   has had (ItemRecord_Has) are `caught`; only those are drawn with their icon and can be
 *   picked.
 * - A row of 9 entries 27 pixels apart is drawn at a time, scrolled by `scroll` pixels; the
 *   icons of the 9 in view are kept in a ring of 9 OBJ places (`entries`, `icon_chars`). The row
 *   scrolls by the two scroll buttons, by the handle on the track under it (a push button,
 *   ov002/push_button.h) or by moving the cursor past either end.
 * - The entry picked (`selected`) is shown: its name in a label, its picture on layer C
 *   ("menu/fish_pic" or "menu/bug_pic", 12 pictures a folder), faded in by the sub engine's
 *   blending, and its description (archive "obj_etc_fish" or "obj_etc_insect") three lines a
 *   page, turned by two page arrows.
 *
 * The cursor (`cursor`, CatalogListPlace) is a place of the list, of the menu bar's (overlay 90,
 * ov090/menu_tabs.h) or an entry. */
#ifndef CLEAN_OV114_CATALOG_LIST_H
#define CLEAN_OV114_CATALOG_LIST_H

#include "main/item_record.h"
#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "main/text_label.h"
#include "ov002/push_button.h"
#include "ov094/pockets_icons.h"
#include "types.h"

/* The kinds of list (CatalogList.kind). */
enum CatalogListKind { CATALOG_LIST_FISH = 0, CATALOG_LIST_INSECTS = 1 };

#define CATALOG_LIST_ENTRIES ITEM_RECORD_CREATURE_KINDS /* 56 */
#define CATALOG_LIST_IN_VIEW 9                          /* the ring of entries drawn */
#define CATALOG_LIST_ENTRY_WIDTH 27                     /* pixels */
#define CATALOG_LIST_LABELS 4
#define CATALOG_LIST_HANDLE_RANGE 0x8c /* the handle's x, 0 to this */
#define CATALOG_LIST_NONE 0xff         /* no entry shown or selected */
#define CATALOG_LIST_FADE_FULL 0x10    /* `fade` of a picture fully shown */

/* The places of the cursor (CatalogList.cursor). */
enum CatalogListPlace {
    CATALOG_LIST_PLACE_NEXT_PAGE = 0,     /* the page arrow on the right */
    CATALOG_LIST_PLACE_PREVIOUS_PAGE = 1, /* the page arrow on the left */
    CATALOG_LIST_PLACE_SCROLL_LEFT = 2,   /* the scroll button on the left */
    CATALOG_LIST_PLACE_SCROLL_RIGHT = 3,  /* the scroll button on the right */
    CATALOG_LIST_PLACE_HANDLE = 4,        /* the scroll handle */
    CATALOG_LIST_PLACE_TAB = 5,           /* 5-12: the menu bar's place cursor - 5 */
    CATALOG_LIST_PLACE_LAST_TAB = 12,
    CATALOG_LIST_PLACE_ENTRY = 13 /* 13 on: entry cursor - 13 */
};

/* How the row is being scrolled (CatalogList.scroll_mode). */
enum CatalogListScrollMode {
    CATALOG_LIST_SCROLL_LEFT = 0,  /* by the left button, 2 pixels of the handle a frame */
    CATALOG_LIST_SCROLL_RIGHT = 1, /* by the right button */
    CATALOG_LIST_SCROLL_DRAG = 2,  /* by the handle, held (the d-pad moves it when by keys) */
    CATALOG_LIST_SCROLL_TRACK = 3, /* the track touched: the handle approaches the pen */
    CATALOG_LIST_SCROLL_NONE = 4
};

/* The flags (CatalogList.flags). */
#define CATALOG_LIST_FLAG_PALETTE_DIRTY 0x0001 /* `palette` is queued for layer A at the frame's end */

/* An entry of the ring: a copy of the cell data_ov114_0229dac0 with its own characters and
 * palette, and the icon whose characters they are. */
typedef struct CatalogListEntry {
    OamEntry obj; /* 0x0: tile 0xc0 + 2 * place, the icon's palette */
    s32 icon;     /* 0x8: ItemTraits_Unk02 of the item, -1 for none */
} CatalogListEntry;

/* The description's text class (vtable data_ov114_0229daf0) on main's text base: 266 8-bit
 * characters, a message of the archives loaded into it (MessageReader_LoadMessage). */
#define CATALOG_TEXT_CAPACITY 266

typedef struct CatalogText {
    const TextVtable *vtable; /* data_ov114_0229daf0 */
    u8 base_04[0xe];          /* the text base's */
    char text[CATALOG_TEXT_CAPACITY];
} CatalogText;

typedef struct CatalogList {
    PocketsIcons icons;                             /* 0x0000: the item icons */
    CatalogText description;                        /* 0x0808 */
    LayerTask palette_task;                         /* 0x0924: `palette` to layer A */
    u16 palette_file[0x10];                         /* 0x0948: "menu/fish/bg4.bpl" */
    u16 palette[0x10];                              /* 0x0968: its copy, colour 2 faded */
    u8 icon_chars[CATALOG_LIST_IN_VIEW][0x80];      /* 0x0988: an icon's two rows of 0x40 */
    LayerTaskPair icon_tasks[CATALOG_LIST_IN_VIEW]; /* 0x0e08 */
    CatalogListEntry entries[CATALOG_LIST_IN_VIEW]; /* 0x1000 */
    TextLabel labels[CATALOG_LIST_LABELS];          /* 0x106c: the name, the description's lines */
    PushButton handle;                              /* 0x121c */
    u32 caught[3];                                  /* 0x1264: a bit an entry */
    int handle_x;                                   /* 0x1270: 0 to CATALOG_LIST_HANDLE_RANGE */
    s32 grab_dx;                                    /* 0x1274: the handle's x less the pen's */
    s32 cued_x;                                     /* 0x1278: the handle's x at its last cue */
    s32 scroll;                                     /* 0x127c: 0 to max_scroll pixels */
    s32 scroll_left;                                /* 0x1280: to scroll yet, by 11 a frame */
    s32 first_x;                                    /* 0x1284: the x of the first entry drawn */
    s32 row_y;                                      /* 0x1288 */
    s32 first_entry;                                /* 0x128c: the first entry drawn */
    s32 first_slot;                                 /* 0x1290: its place in the ring */
    s32 count;                                      /* 0x1294: CATALOG_LIST_ENTRIES */
    s32 max_scroll;                                 /* 0x1298: (count - 8) * 27 */
    s32 page_arrow_palette[2];                      /* 0x129c: next, previous: 5, or 4 at an end */
    u32 planes_b;                                   /* 0x12a4: DisplayLayer_PlaneMask(layer_b) */
    u32 planes_c;                                   /* 0x12a8: DisplayLayer_PlaneMask(layer_c) */
    u16 flags;                                      /* 0x12ac */
    u8 page_arrow_flash[2];                         /* 0x12ae: frames left drawn in palette 6 */
    u8 pages;                                       /* 0x12b0: the description's, 1-4 */
    u8 layer_a;                                     /* 0x12b1: the text and the background */
    u8 layer_b;                                     /* 0x12b2 */
    u8 layer_c;                                     /* 0x12b3: the picture */
    u8 icon_slots;                                  /* 0x12b4: the ring places queued this frame */
    u8 page;                                        /* 0x12b5 */
    u8 labels_used;                                 /* 0x12b6: this frame */
    u8 kind;                                        /* 0x12b7: CatalogListKind */
    u8 shown;                                       /* 0x12b8: the entry shown, or CATALOG_LIST_NONE */
    u8 selected;                                    /* 0x12b9: the entry picked, or CATALOG_LIST_NONE */
    u8 fade;                                        /* 0x12ba: the picture's, 0 to 16 */
    u8 scroll_mode;                                 /* 0x12bb: CatalogListScrollMode */
    u8 cursor;                                      /* 0x12bc: CatalogListPlace */
    u8 cursor_up;                                   /* 0x12bd: the bar's place above the page arrows */
    u8 pad_12be[2];                                 /* 0x12be */
} CatalogList;

void CatalogList_ClearFlags(CatalogList *self, u16 flags);
void CatalogList_SetFlags(CatalogList *self, u16 flags);
int CatalogList_TestFlags(CatalogList *self, u16 flags);
int CatalogList_IsCaught(CatalogList *self, int entry);
void CatalogList_LoadCaught(CatalogList *self);
int CatalogList_RunAction(CatalogList *self);
u8 CatalogList_EntryUnderCursor(CatalogList *self);
void CatalogList_KeepCursorInView(CatalogList *self);
int CatalogList_MoveCursor(CatalogList *self, u32 keys);
int CatalogList_OnPageArrow(CatalogList *self);
int CatalogList_TabUnderCursor(CatalogList *self);
int CatalogList_CursorY(CatalogList *self);
int CatalogList_CursorX(CatalogList *self);
void CatalogList_Select(CatalogList *self, u8 entry);
void CatalogList_UpdatePicture(CatalogList *self);
void CatalogList_LoadPicture(CatalogList *self);
void CatalogList_ShowSelected(CatalogList *self);
void CatalogList_HoldPicture(CatalogList *self);
void CatalogList_ResetPicture(CatalogList *self);
void CatalogList_LoadIcon(CatalogList *self, const ItemCode *item, int slot);
void CatalogList_InitEntries(CatalogList *self);
int CatalogList_TouchEntry(CatalogList *self, int x, int y);
void CatalogList_FillEntries(CatalogList *self);
int CatalogList_SetScroll(CatalogList *self, int scroll);
void CatalogList_DrawEntries(CatalogList *self, int y);
void CatalogList_ShowName(CatalogList *self, u16 entry);
TextLabel *CatalogList_NextLabel(CatalogList *self);
void CatalogList_CloseLabels(CatalogList *self);
u8 CatalogList_NextIconSlot(CatalogList *self);
void CatalogList_EndIconTasks(CatalogList *self);
void CatalogList_FadePalette(CatalogList *self, int step, int steps);
int CatalogList_PreviousPage(CatalogList *self);
int CatalogList_NextPage(CatalogList *self);
void CatalogList_ShowPage(CatalogList *self);
int CatalogList_CountPages(CatalogList *self);
void CatalogList_LoadDescription(CatalogList *self);
int CatalogText_Buffer(int text);
int CatalogText_Capacity(void);
CatalogText *CatalogText_DestructDelete(CatalogText *text);
CatalogText *CatalogText_Destruct(CatalogText *text);
CatalogText *CatalogText_Construct(CatalogText *text);
void CatalogList_ApplyScroll(CatalogList *self);
int CatalogList_FinishHandle(CatalogList *self);
void CatalogList_ReleaseHandle(CatalogList *self);
void CatalogList_ScrollByKeys(CatalogList *self);
int CatalogList_HandleSettled(CatalogList *self);
void CatalogList_EndDrag(CatalogList *self);
void CatalogList_Drag(CatalogList *self, int x);
int CatalogList_TouchHandle(CatalogList *self, int x, int y);
void CatalogList_ScrollFromHandle(CatalogList *self);
void CatalogList_HandleFromScroll(CatalogList *self);
void CatalogList_PlaceHandle(CatalogList *self, int y);
void CatalogList_DrawHandle(CatalogList *self);
int CatalogList_TouchPageArrow(CatalogList *self, int x, int y);
void CatalogList_DrawArrows(CatalogList *self, int y);
void CatalogList_LoadObjFiles(CatalogList *self);
void CatalogList_LoadBackground(CatalogList *self);
void CatalogList_EndFrame(CatalogList *self);
void CatalogList_BeginFrame(CatalogList *self);
void CatalogList_Teardown(CatalogList *self);
void CatalogList_Start(CatalogList *self, u8 layer_a, u8 layer_b, u8 layer_c, u8 kind);
CatalogList *CatalogList_Destroy(CatalogList *self);
CatalogList *CatalogList_Construct(CatalogList *self);

#endif
