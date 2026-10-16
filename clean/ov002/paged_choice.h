/* A list of choices shown a page of up to five rows at a time, which the menu scenes of the
 * overlays 096-125 keep (at 0x2564 in ov096's scene). Each row is a text label of main's; a
 * label at 0x26c shows the page as "page/pages" in full-width digits.
 *
 * Two ways fill the rows:
 * - by page (PagedChoice_ShowPage): the table at 0x3cc holds five choice codes per page, 0
 *   ending a page. Codes 1-4 and 5-12 name entries of two of the game's lists (the text of the
 *   row and the effect of PagedChoice_Apply come from them), 13 one more kind, and 14 and 15
 *   the two codes that do not pick: 14 turns the page, 15 leaves;
 * - from a ChoiceEntries (PagedChoice_ShowEntries): up to five text codes, or texts given
 *   whole (PagedChoice_AddTextEntry).
 *
 * The window sits at (-scroll_x, -scroll_y): rows are 16 pixels apart, the first one's top
 * 16 pixels below the window's (PagedChoice_RowY), the text 16 pixels in. */
#ifndef CLEAN_OV002_PAGED_CHOICE_H
#define CLEAN_OV002_PAGED_CHOICE_H

#include "main/text_label.h"
#include "types.h"
#include "wipe.h"

#define PAGED_CHOICE_ROWS 5

/* The choice codes of the page table. */
enum PagedChoiceCode {
    CHOICE_NONE = 0,     /* ends the page */
    CHOICE_LIST_A = 1,   /* 1-4: player code - 1 of the town's four (records at data_021dc7bc) */
    CHOICE_LIST_B = 5,   /* 5-12: entry code - 5 of the list at data_021e5a2c */
    CHOICE_SPECIAL = 13, /* func_02066514's */
    CHOICE_NEXT_PAGE = 14,
    CHOICE_LEAVE = 15
};

/* What a code does (PagedChoice_CodeKind, PagedChoice_Apply). */
enum PagedChoiceKind { CHOICE_KIND_NONE = 0, CHOICE_KIND_PICK = 1, CHOICE_KIND_NEXT_PAGE = 2, CHOICE_KIND_LEAVE = 3 };

/* The window's states (`state`), run by PagedChoice_Update. */
enum PagedChoiceState {
    CHOICE_CLOSED = 0,
    CHOICE_POPPING_OPEN = 1, /* three frames of a small bounce (PagedChoice_PopOpen) */
    CHOICE_WIPING_OPEN = 2,  /* a wipe uncovers it, the rest of the sub screen darkened */
    CHOICE_SHOWN = 3,
    CHOICE_SLIDING_SHUT = 4, /* a one-frame nudge, then hidden */
    CHOICE_WIPING_SHUT = 5
};

/* What PagedChoice_Update is asked to do next (`request`). */
enum PagedChoiceRequest { CHOICE_REQUEST_NONE = 0, CHOICE_REQUEST_OPEN = 1, CHOICE_REQUEST_CLOSE = 2 };

/* In `flags`. */
enum PagedChoiceFlag {
    CHOICE_FLAG_OBJECTS = 0x01,   /* the page label and the window are drawn (PagedChoice_Draw) */
    CHOICE_FLAG_WIPE_OPEN = 0x02, /* the next opening is a wipe (PagedChoice_SetState) */
    CHOICE_FLAG_WIPE_SHUT = 0x04, /* the next closing is a wipe; deciding a code sets it */
    CHOICE_FLAG_HIGHLIGHT = 0x08, /* row `highlighted` is to be drawn once in colour 15 */
    CHOICE_FLAG_QUIET = 0x10,     /* the next close request plays no sound */
    CHOICE_FLAG_FIRST_ROW = 0x20  /* the first row is set apart (PagedChoice_RefreshRows) */
};

/* A row (vtable data_ov002_0220bba8): a text label of main's and how its text box is opened
 * (ChoiceRow_Draw passes these to TextLabel_OpenStyledBox2). */
typedef struct PagedChoiceRow {
    TextLabel label;
    u16 first_tile; /* 0x6c: the box's first character tile */
    u8 style;       /* 0x6e: PagedChoice_Init gives the choice's layer */
    u8 colour;      /* 0x6f: the palette it is drawn with */
    u8 colour_39;   /* 0x70: the box's second colour */
    u8 pad_71[3];
} PagedChoiceRow;

typedef struct PagedChoice {
    const void *vtable; /* data_ov002_0220bb98 */
    s32 first_tile;     /* 0x04: the rows' first character tile, from the screen file */
    s32 scroll_x;       /* 0x08: the window's left edge, negated */
    s32 scroll_y;       /* 0x0c: its top edge, negated */
    s32 priority;       /* 0x10: the layer's priority */
    u16 flags;          /* 0x14: PagedChoiceFlag */
    u8 state;           /* 0x16: PagedChoiceState */
    u8 request;         /* 0x17: PagedChoiceRequest */
    u8 step;            /* 0x18: frames into the state */
    u8 on_left;         /* 0x19: set by PagedChoice_PlaceBeside when it put the window left */
    u8 layer;           /* 0x1a: the display layer (display_layers.h) the window is drawn on */
    u8 width;           /* 0x1b: in 8-pixel cells, from the widest row (PagedChoice_MeasureWidth) */
    u8 row_count;       /* 0x1c */
    u8 page_count;      /* 0x1d */
    u8 delay;           /* 0x1e: frames left after a pick (PagedChoice_Highlight) */
    u8 highlighted;     /* 0x1f: see CHOICE_FLAG_HIGHLIGHT */
    u8 page;            /* 0x20: the page shown */
    u8 window_delay;    /* 0x21: frames until the wipe-in redraws the window */
    u8 pad_22[2];
    const char *screen_file;                /* 0x24: the window's screen (data_ov002_0220bc18 if none) */
    PagedChoiceRow rows[PAGED_CHOICE_ROWS]; /* 0x28 */
    u8 page_label[0x78];                    /* 0x26c: a shown label (vtable data_ov002_0220bd74) */
    u8 window[0xcc];                        /* 0x2e4: a sliding window of main's (vtable data_ov002_0220bdac) */
    Wipe wipe;                              /* 0x3b0 */
    u8 codes[];                             /* 0x3cc: PAGED_CHOICE_ROWS codes a page, five pages */
} PagedChoice;

/* Up to five rows to show, kept by the scene (ov096's at 0x294c). */
#define CHOICE_ENTRY_EMPTY 0xff /* in `ids`: the end */
#define CHOICE_ENTRY_TEXT 0xfe  /* in `ids`: a text given whole, already in the row */

typedef struct ChoiceEntries {
    u8 ids[PAGED_CHOICE_ROWS];    /* the text code of each row */
    u8 values[PAGED_CHOICE_ROWS]; /* a value kept with each row */
    u8 text_rows;                 /* 0x0a: bit n: row n's text was given whole */
} ChoiceEntries;

void PagedChoice_RequestRowText(PagedChoice *choice, PagedChoiceRow *row, char code);
void PagedChoice_ClearFlags(PagedChoice *choice, int flags);
void PagedChoice_SetFlags(PagedChoice *choice, int flags);
int PagedChoice_TestFlags(PagedChoice *choice, int flags);
int PagedChoice_Apply(PagedChoice *choice, void *target, unsigned int code);
int PagedChoice_CodeKind(PagedChoice *choice, int code);
int PagedChoice_Decide(PagedChoice *choice, int page, int row);
int PagedChoice_PageCount(PagedChoice *choice);
int PagedChoice_RowCount(PagedChoice *choice);
int PagedChoice_RowY(PagedChoice *choice, int row);
int PagedChoice_TextX(PagedChoice *choice);
int PagedChoice_RowAtOrNone(PagedChoice *choice, int x, int y);
int PagedChoice_RowAtOrLast(PagedChoice *choice, int x, int y);
int PagedChoice_RowAt(PagedChoice *choice, int x, int y, int outside);
void PagedChoice_ShowPage(PagedChoice *choice, const u8 *page);
void PagedChoice_ShowEntries(PagedChoice *choice, const ChoiceEntries *entries, int mark_first_row);
int PagedChoice_AddTextEntry(PagedChoice *choice, ChoiceEntries *entries, const void *text, u8 value);
int ChoiceEntries_Count(ChoiceEntries *entries);
void ChoiceEntries_Clear(ChoiceEntries *entries, u8 value);
int ChoiceEntries_Add(ChoiceEntries *entries, u8 id, u8 value);
void PagedChoice_RefreshRows(PagedChoice *choice);
void PagedChoice_DrawRows(PagedChoice *choice);
void PagedChoice_ReleaseRows(PagedChoice *choice);
int PagedChoice_IsIdle(PagedChoice *choice);
int PagedChoice_IsShown(PagedChoice *choice);
void PagedChoice_BuildPages(PagedChoice *choice);
void PagedChoice_SetRowText(PagedChoice *choice, PagedChoiceRow *row, unsigned int code);
int ChoiceRow_SetListBName(PagedChoiceRow *row, int index);
int ChoiceRow_SetTextFrom(PagedChoiceRow *row, const void *source);
int ChoiceRow_SetPlayerName(PagedChoiceRow *row, int player);
int ChoiceRow_SetName(PagedChoiceRow *row, const void *name);
int PagedChoice_MoveCursor(PagedChoice *choice, int keys, u8 *row, u8 first);
int PagedChoice_CountDown(PagedChoice *choice);
void PagedChoice_PickRow(PagedChoice *choice, int row);
u8 PagedChoice_PickLastRow(PagedChoice *choice, int sound);
void PagedChoice_PickRowWithSound(PagedChoice *choice, int row, int sound);
void PagedChoice_Highlight(PagedChoice *choice, u8 row);
void PagedChoice_Dismiss(PagedChoice *choice);
void PagedChoice_Draw(PagedChoice *choice);
void PagedChoice_Update(PagedChoice *choice);
void PagedChoice_MeasureWidth(PagedChoice *choice);
int PagedChoice_Height(PagedChoice *choice);
int PagedChoice_Width(PagedChoice *choice);
void PagedChoice_WipeShut(PagedChoice *choice);
void PagedChoice_WipeOpen(PagedChoice *choice);
void PagedChoice_ApplyWipe(PagedChoice *choice);
void PagedChoice_SlideShut(PagedChoice *choice);
void PagedChoice_PopOpen(PagedChoice *choice);
void PagedChoice_DrawFrame(PagedChoice *choice);
void PagedChoice_SetState(PagedChoice *choice, int state);
void PagedChoice_RequestClose(PagedChoice *choice, int wipe);
void PagedChoice_RequestOpen(PagedChoice *choice, int wipe);
void PagedChoice_OpenPageCentered(PagedChoice *choice, int page, int wipe);
int PagedChoice_LoadFriendGraphics(PagedChoice *choice);
void PagedChoice_LoadChoiceGraphics(PagedChoice *choice);
void PagedChoice_PlaceClamped(PagedChoice *choice, int x, int y);
int PagedChoice_MoveTo(PagedChoice *choice, int x, int y);
void PagedChoice_Scroll(PagedChoice *choice, int x, int y);
void PagedChoice_PlaceAboveWindow(PagedChoice *choice, void *window);
void PagedChoice_PlaceAbove(PagedChoice *choice, int x, int bottom);
void PagedChoice_Place(PagedChoice *choice, int x, int y);
void PagedChoice_PlaceBeside(PagedChoice *choice, int x, int y);
void PagedChoice_PlaceCentered(PagedChoice *choice, int x, int y);
void PagedChoice_Init(PagedChoice *choice, u8 layer, int priority, const char *screen_file);
PagedChoice *PagedChoice_Delete(PagedChoice *choice);
PagedChoice *PagedChoice_Destroy(PagedChoice *choice);
PagedChoice *PagedChoice_Construct(PagedChoice *choice);
void ChoiceRow_SetStyle(PagedChoiceRow *row, u8 style, u16 first_tile, u8 colour, u8 colour_39);
void ChoiceRow_Draw(PagedChoiceRow *row, int colour);
PagedChoiceRow *ChoiceRow_Delete(PagedChoiceRow *row);
PagedChoiceRow *ChoiceRow_Destroy(PagedChoiceRow *row);
PagedChoiceRow *ChoiceRow_Construct(PagedChoiceRow *row);

#endif
