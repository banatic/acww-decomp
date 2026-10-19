/* The paged list of choices of the menu scenes (paged_choice.h). */
#include "paged_choice.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "key_repeat.h"
#include "label_button.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/label_sprite.h"
#include "main/message_reader.h"
#include "main/npc_id.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/sliding_window.h"
#include "main/state_flags.h"
#include "main/text_base.h"
#include "main/town_villager.h"
#include "main/villager_memories.h"
#include "main/villager_roster.h"
#include "message_window.h"

static_assert(sizeof(PagedChoiceRow) == 0x74 && offsetof(PagedChoice, rows) == 0x28, "choice rows");
static_assert(offsetof(PagedChoice, flags) == 0x14 && offsetof(PagedChoice, page) == 0x20, "choice fields");
static_assert(offsetof(PagedChoice, page_label) == 0x26c && offsetof(PagedChoice, wipe) == 0x3b0, "choice objects");
static_assert(offsetof(PagedChoice, codes) == 0x3cc, "choice codes");
static_assert(offsetof(PagedChoice, priority) == 0x10 && offsetof(PagedChoice, screen_file) == 0x24, "choice setup");
static_assert(offsetof(PagedChoice, window_delay) == 0x21 && offsetof(PagedChoice, window) == 0x2e4, "choice window");
static_assert(offsetof(PagedChoiceRow, first_tile) == 0x6c && offsetof(PagedChoiceRow, colour_39) == 0x70, "choice row");
static_assert(offsetof(ChoiceEntries, text_rows) == 0x0a, "choice entries");

/* The full-width slash (U+FF0F), between the page and the page count. */
extern const u16 data_ov002_0220ba50[];

/* The effects of the picking codes: 13, 1-4 and 5-12. */
extern void func_02066514(void *target);
extern void func_02066560(int target, int index);
extern void func_0206658c(void *target, int index);
extern void RtcSendPxiCommand(int command); /* func_020f1fb4(&data_021fd1bc, command) */

#define FULLWIDTH_ZERO 0xff10

typedef void (*LabelMethod)(void *self);

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int neg32(int a)
{
    return (int) (0u - (u32) a);
}

/* func_ov002_022089ec: asks for the text of `row` by `code` (func_020b4980, with its default
 * table). The choice is not read. */
void PagedChoice_RequestRowText(PagedChoice *choice, PagedChoiceRow *row, char code)
{
    unsigned char byte = (unsigned char) code;
    (void) choice;
    MessageReader_LoadMenuMessage((int) (uintptr_t) row, &byte, NULL);
}
CLEAN_AS(func_ov002_022089ec, PagedChoice_RequestRowText)

/* func_ov002_02208a04 */
void PagedChoice_ClearFlags(PagedChoice *choice, int flags)
{
    choice->flags = (u16) (choice->flags & ~flags);
}
CLEAN_AS(func_ov002_02208a04, PagedChoice_ClearFlags)

/* func_ov002_02208a0c */
void PagedChoice_SetFlags(PagedChoice *choice, int flags)
{
    choice->flags = (u16) (choice->flags | flags);
}
CLEAN_AS(func_ov002_02208a0c, PagedChoice_SetFlags)

/* func_ov002_02208a14: whether any of `flags` is set. */
int PagedChoice_TestFlags(PagedChoice *choice, int flags)
{
    return (choice->flags & flags) != 0;
}
CLEAN_AS(func_ov002_02208a14, PagedChoice_TestFlags)

/* func_ov002_02208a24: applies the choice `code` to `target`; returns what the code did
 * (PagedChoiceKind), CHOICE_KIND_NONE for a code that is none of the game's. The choice is
 * not read. */
int PagedChoice_Apply(PagedChoice *choice, void *target, unsigned int code)
{
    (void) choice;
    switch (code) {
        case CHOICE_LEAVE:
            return CHOICE_KIND_LEAVE;
        case CHOICE_NEXT_PAGE:
            return CHOICE_KIND_NEXT_PAGE;
        case CHOICE_SPECIAL:
            func_02066514(target);
            return CHOICE_KIND_PICK;
    }
    if (code >= CHOICE_LIST_A && code < CHOICE_LIST_B) {
        func_02066560((int) (uintptr_t) target, (int) (code - CHOICE_LIST_A));
        return CHOICE_KIND_PICK;
    }
    if (code >= CHOICE_LIST_B && code < CHOICE_SPECIAL) {
        func_0206658c(target, (int) (code - CHOICE_LIST_B));
        return CHOICE_KIND_PICK;
    }
    return CHOICE_KIND_NONE;
}
CLEAN_AS(func_ov002_02208a24, PagedChoice_Apply)

/* func_ov002_02208a78: what `code` does, any code but the two others counting as a pick. */
int PagedChoice_CodeKind(PagedChoice *choice, int code)
{
    (void) choice;
    switch (code) {
        case CHOICE_LEAVE:
            return CHOICE_KIND_LEAVE;
        case CHOICE_NEXT_PAGE:
            return CHOICE_KIND_NEXT_PAGE;
        default:
            return CHOICE_KIND_PICK;
    }
}
CLEAN_AS(func_ov002_02208a78, PagedChoice_CodeKind)

/* func_ov002_02208a8c: decides the choice at `row` of `page`: but for a page turn, has the
 * window close by a wipe (CHOICE_FLAG_WIPE_SHUT); sends command 0x28 for leaving, 0x29 for a page turn, 0x27 for the rest,
 * and returns the code.
 * REQUIRES: the code read lies in the table (page < page_count, row < 5). */
int PagedChoice_Decide(PagedChoice *choice, int page, int row)
{
    u8 code = choice->codes[add32(row, (int) ((u32) page * PAGED_CHOICE_ROWS))];

    if (code != CHOICE_NEXT_PAGE) {
        PagedChoice_SetFlags(choice, CHOICE_FLAG_WIPE_SHUT);
    }
    switch (code) {
        case CHOICE_LEAVE:
            RtcSendPxiCommand(0x28);
            break;
        case CHOICE_NEXT_PAGE:
            RtcSendPxiCommand(0x29);
            break;
        default:
            RtcSendPxiCommand(0x27);
            break;
    }
    return code;
}
CLEAN_AS(func_ov002_02208a8c, PagedChoice_Decide)

/* func_ov002_02208ad0 */
int PagedChoice_PageCount(PagedChoice *choice)
{
    return choice->page_count;
}
CLEAN_AS(func_ov002_02208ad0, PagedChoice_PageCount)

/* func_ov002_02208ad4 */
int PagedChoice_RowCount(PagedChoice *choice)
{
    return choice->row_count;
}
CLEAN_AS(func_ov002_02208ad4, PagedChoice_RowCount)

/* func_ov002_02208ad8: the screen y of `row`: 16 pixels a row, the first 16 below the
 * window's top. */
int PagedChoice_RowY(PagedChoice *choice, int row)
{
    return sub32((int) (((u32) row + 1u) * 16u), choice->scroll_y);
}
CLEAN_AS(func_ov002_02208ad8, PagedChoice_RowY)

/* func_ov002_02208ae4: the screen x of the rows' text, 16 pixels in from the window's left. */
int PagedChoice_TextX(PagedChoice *choice)
{
    return sub32(16, choice->scroll_x);
}
CLEAN_AS(func_ov002_02208ae4, PagedChoice_TextX)

/* func_ov002_02208aec: the row at the screen point (x, y), -1 outside the window. */
int PagedChoice_RowAtOrNone(PagedChoice *choice, int x, int y)
{
    return PagedChoice_RowAt(choice, x, y, -1);
}
CLEAN_AS(func_ov002_02208aec, PagedChoice_RowAtOrNone)

/* func_ov002_02208b00: the row at the screen point (x, y), the last row outside the window. */
int PagedChoice_RowAtOrLast(PagedChoice *choice, int x, int y)
{
    return PagedChoice_RowAt(choice, x, y, choice->row_count - 1);
}
CLEAN_AS(func_ov002_02208b00, PagedChoice_RowAtOrLast)

/* func_ov002_02208b14: the row at the screen point (x, y), or `outside` when the point is
 * outside the window (edges included in it). A row reaches down to 24 pixels below the
 * window's top plus 16 a row; the last row takes everything below.
 * QUIRK: with no rows the answer inside the window is 0. */
int PagedChoice_RowAt(PagedChoice *choice, int x, int y, int outside)
{
    int left = neg32(choice->scroll_x);
    int top = neg32(choice->scroll_y);
    int right = add32(left, PagedChoice_Width(choice));
    int bottom = add32(top, PagedChoice_Height(choice));
    int last = choice->row_count - 1;
    int edge;
    int row;

    if (left > x || right < x) {
        return outside;
    }
    if (top > y || bottom < y) {
        return outside;
    }

    edge = add32(top, 0x18);
    for (row = 0; row < last; row++) {
        if (edge > y) {
            return row;
        }
        edge = add32(edge, 16);
    }
    return row;
}
CLEAN_AS(func_ov002_02208b14, PagedChoice_RowAt)

/* func_ov002_02208b74: fills the rows from the codes of page `*page` (up to the first 0), sets
 * the width, and shows "page/pages" (counting from 1, in full-width digits) in the page
 * label.
 * QUIRK: each number is written as one character, the digit's code plus the number, which is
 * right only for single digits. */
void PagedChoice_ShowPage(PagedChoice *choice, const u8 *page)
{
    const u8 *codes = &choice->codes[*page * PAGED_CHOICE_ROWS];
    u16 page_digit[2];
    u16 count_digit[2];
    u32 text[0x6c / 4];  /* main's text label */
    u32 digit[0x70 / 4]; /* another */
    int i;

    choice->row_count = 0;
    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        if (codes[i] == CHOICE_NONE) {
            break;
        }
        PagedChoice_SetRowText(choice, &choice->rows[i], codes[i]);
        choice->row_count++;
    }
    PagedChoice_MeasureWidth(choice);

    page_digit[0] = (u16) (*page + FULLWIDTH_ZERO + 1);
    page_digit[1] = 0;
    count_digit[0] = (u16) (choice->page_count + FULLWIDTH_ZERO);
    count_digit[1] = 0;

    TextLabel_Construct((TextLabel *) (void *) text);
    TextLabel_Construct((TextLabel *) (void *) digit);
    TextLabel_SetFromWide(digit, page_digit, (void *) (uintptr_t) 2);
    TextBase_Copy((TextBase *) (void *) text, (TextBase *) (void *) digit);
    TextBase_AppendChars((TextBase *) (void *) text, (const char *) (void *) data_ov002_0220ba50);
    TextLabel_SetFromWide(digit, count_digit, (void *) (uintptr_t) 2);
    TextBase_AppendText(text, (TextBase *) (void *) digit);
    LabelSprite_SetText((LabelSprite *) (void *) choice->page_label, (TextBase *) (void *) text);
    {
        u32 vtable = *(const u32 *) (const void *) choice->page_label;
        ((LabelMethod) (uintptr_t) *(const u32 *) (uintptr_t) (vtable + 0x0c))(choice->page_label);
    }
    choice->page = *page;
    TextLabel_Destruct((TextLabel *) (void *) digit);
    TextLabel_Destruct((TextLabel *) (void *) text);
}
CLEAN_AS(func_ov002_02208b74, PagedChoice_ShowPage)

/* func_ov002_02208c58: fills the rows from `entries` (up to the first empty one), asking for
 * the text of each but the rows given whole; with `mark_first_row` sets the first row apart.
 * Then sets the width. */
void PagedChoice_ShowEntries(PagedChoice *choice, const ChoiceEntries *entries, int mark_first_row)
{
    int count = 0;
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        u8 id = entries->ids[i];
        if (id == CHOICE_ENTRY_EMPTY) {
            break;
        }
        if (!(entries->text_rows & (1 << i))) {
            PagedChoice_RequestRowText(choice, &choice->rows[count], (char) id);
        }
        count++;
    }

    if (mark_first_row) {
        PagedChoice_SetFlags(choice, CHOICE_FLAG_FIRST_ROW);
    } else {
        PagedChoice_ClearFlags(choice, CHOICE_FLAG_FIRST_ROW);
    }
    choice->row_count = (u8) count;
    PagedChoice_MeasureWidth(choice);
}
CLEAN_AS(func_ov002_02208c58, PagedChoice_ShowEntries)

/* func_ov002_02208ccc: puts the text of the label `text` in the row of the first empty entry
 * and keeps `value` with it. Returns 0 when all five are taken. */
int PagedChoice_AddTextEntry(PagedChoice *choice, ChoiceEntries *entries, const void *text, u8 value)
{
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        if (entries->ids[i] == CHOICE_ENTRY_EMPTY) {
            TextBase_Copy((TextBase *) (void *) &choice->rows[i], (TextBase *) text);
            entries->values[i] = value;
            entries->text_rows |= (u8) (1 << i);
            entries->ids[i] = CHOICE_ENTRY_TEXT;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov002_02208ccc, PagedChoice_AddTextEntry)

/* func_ov002_02208d18: the number of entries before the first empty one. */
int ChoiceEntries_Count(ChoiceEntries *entries)
{
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        if (entries->ids[i] == CHOICE_ENTRY_EMPTY) {
            break;
        }
    }
    return i;
}
CLEAN_AS(func_ov002_02208d18, ChoiceEntries_Count)

/* func_ov002_02208d30: empties all five, `value` kept with each. */
void ChoiceEntries_Clear(ChoiceEntries *entries, u8 value)
{
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        entries->ids[i] = CHOICE_ENTRY_EMPTY;
        entries->values[i] = value;
    }
    entries->text_rows = 0;
}
CLEAN_AS(func_ov002_02208d30, ChoiceEntries_Clear)

/* func_ov002_02208d4c: puts `id` and `value` in the first empty entry. Returns 0 when all five
 * are taken. */
int ChoiceEntries_Add(ChoiceEntries *entries, u8 id, u8 value)
{
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        if (entries->ids[i] == CHOICE_ENTRY_EMPTY) {
            entries->ids[i] = id;
            entries->values[i] = value;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov002_02208d4c, ChoiceEntries_Add)

/* func_ov002_02208d74: draws the rows in their own colours, then hands each row shown to
 * func_02070a04 with 1, or 0 for the first row when it is set apart. */
void PagedChoice_RefreshRows(PagedChoice *choice)
{
    int i;

    PagedChoice_DrawRows(choice);
    for (i = 0; i < choice->row_count; i++) {
        int apart = i == 0 && PagedChoice_TestFlags(choice, CHOICE_FLAG_FIRST_ROW);
        TextLabel_Show((TextLabel *) (void *) &choice->rows[i], 0, apart ? 0 : 1);
    }
}
CLEAN_AS(func_ov002_02208d74, PagedChoice_RefreshRows)

/* func_ov002_02208dd0: draws all five rows in their own colours. */
void PagedChoice_DrawRows(PagedChoice *choice)
{
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        ChoiceRow_Draw(&choice->rows[i], -1);
    }
}
CLEAN_AS(func_ov002_02208dd0, PagedChoice_DrawRows)

/* func_ov002_02208df8: frees what the five rows' labels hold. */
void PagedChoice_ReleaseRows(PagedChoice *choice)
{
    int i;

    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        TextLabel_CloseBox(&choice->rows[i]);
    }
}
CLEAN_AS(func_ov002_02208df8, PagedChoice_ReleaseRows)

/* func_ov002_02208e18 */
int PagedChoice_IsIdle(PagedChoice *choice)
{
    return choice->state == 0;
}
CLEAN_AS(func_ov002_02208e18, PagedChoice_IsIdle)

/* ---- The window: the page table, picking, placing, opening and closing ---- */

#define PLAYERS 4
#define LIST_B_ENTRIES 8
#define PAGE_TABLE_PAGES 5
#define PICK_COLOUR 15
#define ROW_CELLS 13     /* the width of a row's text box, in cells */
#define ROW_TILES 0x1a   /* the character tiles a row's text box takes */
#define FRAME_COLUMNS 13 /* the text width the screen file's frame is drawn for */
#define SCREEN_ROW 0x40  /* the bytes a row of the 32-cell screen takes */
#define FRAME_BOTTOM 10  /* the screen file's row holding the frame's bottom edge */
#define FRAME_RIGHT 14   /* its column holding the frame's right edge */

/* the town's players */
extern u8 data_021dc7bc[]; /* the four players' records */
/* the eight entries of the list at data_021e5a2c (0x7ec bytes each) */
extern u8 data_021e5a2c[];

/* files */
extern Heap *data_021fbe94; /* the heap files are loaded on */
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);
extern const char data_ov002_0220bbb8[]; /* "menu/friend/bg1.bpl" */
extern const char data_ov002_0220bbcc[]; /* "menu/friend/bg1.bch" */
extern const char data_ov002_0220bbe0[]; /* "menu/inventory/b_itm.bpl" */
extern const char data_ov002_0220bbfc[]; /* "menu/inventory/b_choice.bch" */
extern const char data_ov002_0220bc18[]; /* "menu/inventory/b_itm_bg_b.bsc" */

/* the classes */
extern const u8 data_ov002_0220bb98[];  /* the choice's vtable */
extern const u8 data_ov002_0220bba8[];  /* a row's */
extern const int data_ov002_0220bb84[]; /* the pop's offsets: -5, 1, 0 */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void *func_ov002_02209bf0(void *row); /* ChoiceRow_Destroy, for the array */
extern void *func_ov002_02209c08(void *row); /* ChoiceRow_Construct, for the array */

typedef void (*ObjectMethod)(void *self);
typedef void (*ObjectMethod2)(void *self, int a, int b);

/* The virtual function at `offset` in the object's vtable. */
static u32 virtual_at(const void *object, u32 offset)
{
    u32 vtable = *(const u32 *) object;
    return *(const u32 *) (uintptr_t) (vtable + offset);
}

/* Row `index`, past the five for a larger index, as the original computes it. */
static PagedChoiceRow *row_at(PagedChoice *choice, unsigned int index)
{
    return (PagedChoiceRow *) ((uintptr_t) choice->rows + (uintptr_t) index * sizeof(PagedChoiceRow));
}

static u8 *screen_cell(u8 *screen, int row, int column)
{
    return (u8 *) ((uintptr_t) screen + (uintptr_t) (u32) (row * SCREEN_ROW + column * 2));
}

/* func_ov002_02208e28 */
int PagedChoice_IsShown(PagedChoice *choice)
{
    return choice->state == CHOICE_SHOWN;
}
CLEAN_AS(func_ov002_02208e28, PagedChoice_IsShown)

/* func_ov002_02208e38: fills the page table: the town's other players (codes 1-4), then the
 * entries in use of the second list that func_020807a8 accepts with the current player's
 * name (codes 5-12), four to a page with a page turn in each full page's last row and one ending the last of these
 * pages. A page of its own follows with the special code and leave, and a page turn back to
 * the first page when there are pages before it.
 * The table is cleared for five pages; the lists fill at most four. */
void PagedChoice_BuildPages(PagedChoice *choice)
{
    void *name;
    int self;
    int count = 0;
    int i;

    choice->page_count = 0;
    for (i = 0; i < PAGE_TABLE_PAGES * PAGED_CHOICE_ROWS; i++) {
        choice->codes[i] = CHOICE_NONE;
    }

    name = (void *) PlayerRecord_Player((void *) PlayerRecords_Current());
    self = PlayerRecords_FindIndex(data_021dc7bc, name);
    for (i = 0; i < PLAYERS; i++) {
        if (i != self && PlayerRecords_TownExists(data_021dc7bc, i)) {
            choice->codes[count++] = (u8) (CHOICE_LIST_A + i);
        }
    }
    if (count % PAGED_CHOICE_ROWS == PAGED_CHOICE_ROWS - 1) {
        choice->codes[count++] = CHOICE_NEXT_PAGE;
    }
    for (i = 0; i < LIST_B_ENTRIES; i++) {
        if (VillagerRoster_IsFilled((VillagerTown *) (void *) data_021e5a2c, i) &&
            (int) (uintptr_t) VillagerMemory_Of((void *) VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, i),
                                                name)) {
            choice->codes[count++] = (u8) (CHOICE_LIST_B + i);
        }
        if (count % PAGED_CHOICE_ROWS == PAGED_CHOICE_ROWS - 1) {
            choice->codes[count++] = CHOICE_NEXT_PAGE;
        }
    }

    if (count % PAGED_CHOICE_ROWS != 0) {
        choice->codes[count++] = CHOICE_NEXT_PAGE;
    }
    while (count % PAGED_CHOICE_ROWS != 0) {
        choice->codes[count++] = CHOICE_NONE;
    }
    choice->codes[count] = CHOICE_SPECIAL;
    choice->codes[count + 1] = CHOICE_LEAVE;
    count += 2;
    if (count > 2) {
        choice->codes[count++] = CHOICE_NEXT_PAGE;
    }
    choice->page_count = (u8) ((count + PAGED_CHOICE_ROWS - 1) / PAGED_CHOICE_ROWS);
}
CLEAN_AS(func_ov002_02208e38, PagedChoice_BuildPages)

/* func_ov002_02208f58: gives `row` the text of `code`: a player's name, the text of an entry
 * of the second list, or messages 0x25 (special), 0x1e (page turn) and 0x27 (leave). Other
 * codes leave the row as it is. */
void PagedChoice_SetRowText(PagedChoice *choice, PagedChoiceRow *row, unsigned int code)
{
    if (code >= CHOICE_LIST_A && code < CHOICE_LIST_B) {
        ChoiceRow_SetPlayerName(row, (int) (code - CHOICE_LIST_A));
    } else if (code >= CHOICE_LIST_B && code < CHOICE_SPECIAL) {
        ChoiceRow_SetListBName(row, (int) (code - CHOICE_LIST_B));
    } else {
        switch (code) {
            case CHOICE_SPECIAL:
                PagedChoice_RequestRowText(choice, row, 0x25);
                break;
            case CHOICE_NEXT_PAGE:
                PagedChoice_RequestRowText(choice, row, 0x1e);
                break;
            case CHOICE_LEAVE:
                PagedChoice_RequestRowText(choice, row, 0x27);
                break;
        }
    }
}
CLEAN_AS(func_ov002_02208f58, PagedChoice_SetRowText)

/* func_ov002_02208fac: the text of entry `index` of the second list. */
int ChoiceRow_SetListBName(PagedChoiceRow *row, int index)
{
    return ChoiceRow_SetTextFrom(
        row, (void *) TownVillager_NpcId((void *) VillagerRoster_At((VillagerTown *) (void *) data_021e5a2c, index)));
}
CLEAN_AS(func_ov002_02208fac, ChoiceRow_SetListBName)

/* func_ov002_02208fcc: the row's text from `source` (by func_02003618, through a string
 * object). Returns what destroying the string object returns. */
int ChoiceRow_SetTextFrom(PagedChoiceRow *row, const void *source)
{
    u8 text[0x24];

    PlayerIdText_Construct((PlayerIdText *) (void *) text);
    NpcId_FormatName(source, (char *) text);
    TextBase_Copy((TextBase *) (void *) row, (TextBase *) (void *) text);
    return (int) (uintptr_t) PlayerIdText_Destruct((PlayerIdText *) (void *) text);
}
CLEAN_AS(func_ov002_02208fcc, ChoiceRow_SetTextFrom)

/* func_ov002_02208ff8: the name of the town's player `player`. */
int ChoiceRow_SetPlayerName(PagedChoiceRow *row, int player)
{
    return ChoiceRow_SetName(row, (void *) PlayerRecord_Player((void *) PlayerRecords_TownRecord(data_021dc7bc, player)));
}
CLEAN_AS(func_ov002_02208ff8, ChoiceRow_SetPlayerName)

/* func_ov002_02209018: the row's text from a player's name. Returns what destroying the
 * string object returns. */
int ChoiceRow_SetName(PagedChoiceRow *row, const void *name)
{
    u8 text[0x24];

    PlayerIdText_Construct((PlayerIdText *) (void *) text);
    PlayerId_NameToText((DesignCreator *) name, (TextBase *) (void *) text);
    TextBase_Copy((TextBase *) (void *) row, (TextBase *) (void *) text);
    return (int) (uintptr_t) PlayerIdText_Destruct((PlayerIdText *) (void *) text);
}
CLEAN_AS(func_ov002_02209018, ChoiceRow_SetName)

/* func_ov002_02209044: moves the cursor `*row` by the latched keys `keys`: up to the row
 * above, from `first` round to the last row; down to the row below, from the last round to
 * `first`. Returns whether it moved. */
int PagedChoice_MoveCursor(PagedChoice *choice, int keys, u8 *row, u8 first)
{
    if (keys == 0) {
        return 0;
    }
    if (KeyRepeat_HasUp(keys)) {
        if (*row > first) {
            *row = (u8) (*row - 1);
        } else {
            *row = (u8) (choice->row_count - 1);
        }
        return 1;
    }
    if (KeyRepeat_HasDown(keys)) {
        if (*row + 1 < choice->row_count) {
            *row = (u8) (*row + 1);
        } else {
            *row = first;
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov002_02209044, PagedChoice_MoveCursor)

/* func_ov002_0220909c: counts the delay after a pick down; whether it had run out. */
int PagedChoice_CountDown(PagedChoice *choice)
{
    if (choice->delay != 0) {
        choice->delay--;
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov002_0220909c, PagedChoice_CountDown)

/* func_ov002_022090b0: picks `row` of the page shown: highlights it and decides its code
 * (PagedChoice_Decide, given the row's low byte), then sends command 0x2a when the code
 * leaves, else 0x29. */
void PagedChoice_PickRow(PagedChoice *choice, int row)
{
    PagedChoice_Highlight(choice, (u8) row);
    if (PagedChoice_Decide(choice, choice->page, (u8) row) == CHOICE_LEAVE) {
        RtcSendPxiCommand(0x2a);
    } else {
        RtcSendPxiCommand(0x29);
    }
}
CLEAN_AS(func_ov002_022090b0, PagedChoice_PickRow)

/* func_ov002_022090e4: highlights the last row; with `sound` sends command 0x2a, else has the
 * next close request play nothing. Returns the row. */
u8 PagedChoice_PickLastRow(PagedChoice *choice, int sound)
{
    int last = choice->row_count - 1;

    PagedChoice_Highlight(choice, (u8) last);
    if (sound == 0) {
        PagedChoice_SetFlags(choice, CHOICE_FLAG_QUIET);
    } else {
        RtcSendPxiCommand(0x2a);
    }
    return (u8) last;
}
CLEAN_AS(func_ov002_022090e4, PagedChoice_PickLastRow)

/* func_ov002_02209114: highlights `row`; with `sound` sends command 0x2a for the last row,
 * 0x29 for the others, else has the next close request play nothing. */
void PagedChoice_PickRowWithSound(PagedChoice *choice, int row, int sound)
{
    PagedChoice_Highlight(choice, (u8) row);
    if (sound == 0) {
        PagedChoice_SetFlags(choice, CHOICE_FLAG_QUIET);
    } else if (choice->row_count - 1 == row) {
        RtcSendPxiCommand(0x2a);
    } else {
        RtcSendPxiCommand(0x29);
    }
}
CLEAN_AS(func_ov002_02209114, PagedChoice_PickRowWithSound)

/* func_ov002_0220914c: has `row` drawn once in the pick colour and starts the delay: 2
 * frames while state flag 2 is set, else 5. */
void PagedChoice_Highlight(PagedChoice *choice, u8 row)
{
    PagedChoice_SetFlags(choice, CHOICE_FLAG_HIGHLIGHT);
    if (StateFlags_Test2()) {
        choice->delay = 2;
    } else {
        choice->delay = 5;
    }
    choice->highlighted = row;
}
CLEAN_AS(func_ov002_0220914c, PagedChoice_Highlight)

/* func_ov002_02209178: closes the window at once (hiding its layer unless it was closed),
 * drops any request and frees the rows' text boxes. */
void PagedChoice_Dismiss(PagedChoice *choice)
{
    choice->request = CHOICE_REQUEST_NONE;
    if (choice->state != CHOICE_CLOSED) {
        DisplayLayer_Hide(choice->layer);
        choice->state = CHOICE_CLOSED;
    }
    PagedChoice_ReleaseRows(choice);
}
CLEAN_AS(func_ov002_02209178, PagedChoice_Dismiss)

/* func_ov002_0220919c: while CHOICE_FLAG_OBJECTS is set, runs the virtual function at 0x08 of
 * the page label and of the window. */
void PagedChoice_Draw(PagedChoice *choice)
{
    if (PagedChoice_TestFlags(choice, CHOICE_FLAG_OBJECTS)) {
        ((ObjectMethod) (uintptr_t) virtual_at(choice->page_label, 0x08))(choice->page_label);
        ((ObjectMethod) (uintptr_t) virtual_at(choice->window, 0x08))(choice->window);
    }
}
CLEAN_AS(func_ov002_0220919c, PagedChoice_Draw)

/* func_ov002_022091cc: a frame of the window. The rows' text boxes are freed (a highlighted
 * row gets one again, in the pick colour), then the request is taken:
 * - open: a closed window starts opening and draws its rows; one opening drops the request;
 *   a shown one starts closing and keeps the request, to open again once closed;
 * - close: a shown window starts closing; one popping open is hidden at once; others drop it.
 * Then the state runs. */
void PagedChoice_Update(PagedChoice *choice)
{
    PagedChoice_ReleaseRows(choice);
    if (PagedChoice_TestFlags(choice, CHOICE_FLAG_HIGHLIGHT)) {
        PagedChoiceRow *row = row_at(choice, choice->highlighted);

        PagedChoice_ClearFlags(choice, CHOICE_FLAG_HIGHLIGHT);
        ChoiceRow_Draw(row, PICK_COLOUR);
        TextLabel_Show(&row->label, 0, 1);
    }

    switch (choice->request) {
        case CHOICE_REQUEST_OPEN:
            switch (choice->state) {
                case CHOICE_CLOSED:
                    PagedChoice_SetState(choice, CHOICE_POPPING_OPEN);
                    choice->request = CHOICE_REQUEST_NONE;
                    PagedChoice_RefreshRows(choice);
                    break;
                case CHOICE_POPPING_OPEN:
                case CHOICE_WIPING_OPEN:
                    choice->request = CHOICE_REQUEST_NONE;
                    break;
                case CHOICE_SHOWN:
                    PagedChoice_SetState(choice, CHOICE_SLIDING_SHUT);
                    break;
            }
            break;
        case CHOICE_REQUEST_CLOSE:
            switch (choice->state) {
                case CHOICE_SHOWN:
                    PagedChoice_SetState(choice, CHOICE_SLIDING_SHUT);
                    choice->request = CHOICE_REQUEST_NONE;
                    break;
                case CHOICE_POPPING_OPEN:
                    DisplayLayer_Hide(choice->layer);
                    PagedChoice_SetState(choice, CHOICE_CLOSED);
                    choice->request = CHOICE_REQUEST_NONE;
                    break;
                case CHOICE_CLOSED:
                case CHOICE_WIPING_OPEN:
                    choice->request = CHOICE_REQUEST_NONE;
                    break;
            }
            break;
    }

    switch (choice->state) {
        case CHOICE_POPPING_OPEN:
            PagedChoice_PopOpen(choice);
            break;
        case CHOICE_SLIDING_SHUT:
            PagedChoice_SlideShut(choice);
            break;
        case CHOICE_WIPING_OPEN:
            PagedChoice_WipeOpen(choice);
            break;
        case CHOICE_WIPING_SHUT:
            PagedChoice_WipeShut(choice);
            break;
    }
}
CLEAN_AS(func_ov002_022091cc, PagedChoice_Update)

/* func_ov002_022092e0: `width` from the widest row shown, in cells rounded up. */
void PagedChoice_MeasureWidth(PagedChoice *choice)
{
    int widest = 0;
    int i;

    for (i = 0; i < choice->row_count; i++) {
        int width = TextLabel_TextWidth(&choice->rows[i]);
        if (width > widest) {
            widest = width;
        }
    }
    choice->width = (u8) ((widest + 7) >> 3);
}
CLEAN_AS(func_ov002_022092e0, PagedChoice_MeasureWidth)

/* func_ov002_02209318: the window's height in pixels: two cells a row and one at each edge. */
int PagedChoice_Height(PagedChoice *choice)
{
    return (choice->row_count * 2 + 2) * 8;
}
CLEAN_AS(func_ov002_02209318, PagedChoice_Height)

/* func_ov002_02209324: the window's width in pixels: the text and four cells. */
int PagedChoice_Width(PagedChoice *choice)
{
    return (choice->width + 4) * 8;
}
CLEAN_AS(func_ov002_02209324, PagedChoice_Width)

/* func_ov002_0220932c: CHOICE_WIPING_SHUT. Its first frame starts a 3-frame wipe from the top
 * over the layer, on the sub screen's window 0. When the wipe is through, the sub screen's
 * darkening ends, the objects are no longer drawn, the layer is hidden and the window closed. */
void PagedChoice_WipeShut(PagedChoice *choice)
{
    if (choice->step == 0) {
        Wipe_StartOnWindow2(&choice->wipe, DisplayLayer_PlaneMaskInt(choice->layer), 3, WIPE_TOP, 0x30);
        PagedChoice_ApplyWipe(choice);
        choice->step++;
    }
    if (Wipe_Step(&choice->wipe, WIPE_ON_SUB)) {
        DisplayShadow_EndSubObjWindowBrightness();
        PagedChoice_ClearFlags(choice, CHOICE_FLAG_OBJECTS);
        DisplayLayer_Hide(choice->layer);
        PagedChoice_SetState(choice, CHOICE_CLOSED);
    } else {
        PagedChoice_ApplyWipe(choice);
    }
}
CLEAN_AS(func_ov002_0220932c, PagedChoice_WipeShut)

/* func_ov002_02209398: CHOICE_WIPING_OPEN. Its first frame draws the frame, darkens the sub
 * screen (brightness -6) but for the layer and inside the OBJ window, starts a 5-frame wipe
 * back from the top, shows the layer and the objects, and has the window redrawn two frames
 * on. Then the wipe runs until it is through, and the window is shown. */
void PagedChoice_WipeOpen(PagedChoice *choice)
{
    if (choice->step == 0) {
        PagedChoice_DrawFrame(choice);
        DisplayShadow_BeginSubObjWindowBrightness();
        DisplayShadow_ExcludeSubBrightnessPlanes(DisplayLayer_PlaneMask(choice->layer));
        DisplayShadow_SetSubBrightness((u8) -6);
        Wipe_StartCoveredOnWindow2(&choice->wipe, DisplayLayer_PlaneMaskInt(choice->layer), 5, WIPE_TOP, 0x30);
        DisplayLayer_Show(choice->layer);
        PagedChoice_SetFlags(choice, CHOICE_FLAG_OBJECTS);
        choice->window_delay = 2;
        PagedChoice_ApplyWipe(choice);
        choice->step++;
        return;
    }

    if (Wipe_StepBack(&choice->wipe, WIPE_ON_SUB)) {
        PagedChoice_SetState(choice, CHOICE_SHOWN);
        if (choice->window_delay != 0) {
            choice->window_delay = 1;
        }
    }
    if (choice->window_delay != 0) {
        choice->window_delay--;
        if (choice->window_delay == 0) {
            SlidingWindow_RefreshText((SlidingWindow *) (void *) choice->window, 0);
        }
    }
    PagedChoice_ApplyWipe(choice);
}
CLEAN_AS(func_ov002_02209398, PagedChoice_WipeOpen)

/* func_ov002_02209464: the wipe's offsets on the layer at the window's place, and its
 * vertical offset on the page label (whole) and the window (a quarter, the other way). */
void PagedChoice_ApplyWipe(PagedChoice *choice)
{
    int offset;

    Wipe_ApplyScroll(&choice->wipe, choice->layer, neg32(choice->scroll_x), neg32(choice->scroll_y));
    offset = Wipe_OffsetY(&choice->wipe);
    LabelSprite_SetOffset((LabelSprite *) (void *) choice->page_label, 0, offset);
    SlidingWindow_SetPlace((SlidingWindow *) (void *) choice->window, 0, neg32(offset >> 2));
}
CLEAN_AS(func_ov002_02209464, PagedChoice_ApplyWipe)

/* The horizontal scroll for the window's place moved by `offset` (the other way when the
 * window was put on the left), kept from 0 down to the window's width less 255. */
static int nudged_x(PagedChoice *choice, int offset)
{
    int x = choice->on_left ? sub32(choice->scroll_x, offset) : add32(choice->scroll_x, offset);

    if (x > 0) {
        x = 0;
    }
    if (add32(neg32(x), PagedChoice_Width(choice)) > 0xff) {
        x = PagedChoice_Width(choice) - 0xff;
    }
    return x;
}

/* func_ov002_022094b4: CHOICE_SLIDING_SHUT: one frame with the layer moved by 11 pixels from
 * the window's place, then hidden and closed. */
void PagedChoice_SlideShut(PagedChoice *choice)
{
    if (choice->step == 0) {
        PagedChoice_Scroll(choice, nudged_x(choice, 0xb), sub32(choice->scroll_y, 0xb));
        choice->step++;
    } else {
        DisplayLayer_Hide(choice->layer);
        PagedChoice_SetState(choice, CHOICE_CLOSED);
    }
}
CLEAN_AS(func_ov002_022094b4, PagedChoice_SlideShut)

/* func_ov002_02209518: CHOICE_POPPING_OPEN: draws the frame and shows the layer, then for
 * three frames moves the layer by -5, 1 and 0 pixels from the window's place; then the
 * window is shown. REQUIRES: `step` < 3, as the state leaves it (it indexes the offsets). */
void PagedChoice_PopOpen(PagedChoice *choice)
{
    int offset;

    if (choice->step == 0) {
        PagedChoice_DrawFrame(choice);
        DisplayLayer_Show(choice->layer);
    }
    offset = data_ov002_0220bb84[choice->step];
    PagedChoice_Scroll(choice, nudged_x(choice, offset), sub32(choice->scroll_y, offset));
    choice->step++;
    if (choice->step >= 3) {
        PagedChoice_SetState(choice, CHOICE_SHOWN);
    }
}
CLEAN_AS(func_ov002_02209518, PagedChoice_PopOpen)

/* func_ov002_0220958c: draws the window's frame on its layer. The screen file holds the frame
 * for five rows and 13 cells of text; the bottom edge is moved up under the rows shown and
 * the rows below it blanked (with the cell at (0, 17)), the right edge moved left to the
 * text's width, and the result loaded into the layer's screen. */
void PagedChoice_DrawFrame(PagedChoice *choice)
{
    Heap *heap;
    u8 *screen;

    DisplayLayer_SetPriority(choice->layer, choice->priority);
    DisplayLayer_SetBgControl(choice->layer, 0, 0, 0);
    heap = data_021fbe94;
    screen = RomFile_Load(choice->screen_file, heap, -4, NULL);

    if (choice->row_count != PAGED_CHOICE_ROWS) {
        int rows = choice->row_count;
        u16 blank = *(u16 *) screen_cell(screen, 0, 0x11);
        u16 *edge = (u16 *) screen_cell(screen, FRAME_BOTTOM, 0);
        u16 *under = (u16 *) screen_cell(screen, rows * 2, 0);

        /* the frame's two cells at each side of the row under the rows */
        under[0] = edge[0];
        under[1] = edge[1];
        under[15] = edge[15];
        under[16] = edge[16];
        MIi_CpuCopy16(screen_cell(screen, FRAME_BOTTOM + 1, 0), screen_cell(screen, rows * 2 + 1, 0), SCREEN_ROW);
        MIi_CpuClear16(blank, screen_cell(screen, rows * 2 + 2, 0), (u32) (PAGED_CHOICE_ROWS - rows) * 2 * SCREEN_ROW);
    }

    if (choice->width != FRAME_COLUMNS) {
        int rows = choice->row_count * 2 + 2;
        int column = choice->width + 1;
        int i;

        /* the top and bottom rows from the corner on, the rows between from past the edge */
        MIi_CpuCopy16(screen_cell(screen, 0, FRAME_RIGHT), screen_cell(screen, 0, column), 0x1e);
        for (i = 1; i < rows - 1; i++) {
            MIi_CpuCopy16(screen_cell(screen, i, FRAME_RIGHT + 1), screen_cell(screen, i, column + 1), 0x1e);
        }
        MIi_CpuCopy16(screen_cell(screen, rows - 1, FRAME_RIGHT), screen_cell(screen, rows - 1, column), 0x1e);
    }

    DisplayLayer_LoadScreen(screen, choice->layer, 0x800, 0);
    Heap_Free(heap, screen);
}
CLEAN_AS(func_ov002_0220958c, PagedChoice_DrawFrame)

/* func_ov002_0220968c: enters `state` at its first frame. Opening or closing becomes the wipe
 * when its flag is set, and the flag is taken. */
void PagedChoice_SetState(PagedChoice *choice, int state)
{
    if (PagedChoice_TestFlags(choice, CHOICE_FLAG_WIPE_OPEN) && state == CHOICE_POPPING_OPEN) {
        state = CHOICE_WIPING_OPEN;
        PagedChoice_ClearFlags(choice, CHOICE_FLAG_WIPE_OPEN);
    } else if (PagedChoice_TestFlags(choice, CHOICE_FLAG_WIPE_SHUT) && state == CHOICE_SLIDING_SHUT) {
        state = CHOICE_WIPING_SHUT;
        PagedChoice_ClearFlags(choice, CHOICE_FLAG_WIPE_SHUT);
    }
    choice->state = (u8) state;
    choice->step = 0;
}
CLEAN_AS(func_ov002_0220968c, PagedChoice_SetState)

/* func_ov002_022096d8: asks to close (by a wipe with `wipe`), sending command 0x14 unless a
 * pick asked for quiet. */
void PagedChoice_RequestClose(PagedChoice *choice, int wipe)
{
    choice->request = CHOICE_REQUEST_CLOSE;
    if (wipe) {
        PagedChoice_SetFlags(choice, CHOICE_FLAG_WIPE_SHUT);
    }
    if (PagedChoice_TestFlags(choice, CHOICE_FLAG_QUIET)) {
        PagedChoice_ClearFlags(choice, CHOICE_FLAG_QUIET);
    } else {
        RtcSendPxiCommand(0x14);
    }
}
CLEAN_AS(func_ov002_022096d8, PagedChoice_RequestClose)

/* func_ov002_0220970c: asks to open (by a wipe with `wipe`), hiding the layer meanwhile, and
 * sends command 0x13. */
void PagedChoice_RequestOpen(PagedChoice *choice, int wipe)
{
    choice->request = CHOICE_REQUEST_OPEN;
    DisplayLayer_Hide(choice->layer);
    if (wipe != 0) {
        PagedChoice_SetFlags(choice, CHOICE_FLAG_WIPE_OPEN);
    }
    RtcSendPxiCommand(0x13);
    PagedChoice_ClearFlags(choice, CHOICE_FLAG_QUIET);
}
CLEAN_AS(func_ov002_0220970c, PagedChoice_RequestOpen)

/* func_ov002_02209740: shows page `page` (its low byte), places the window centred 12 pixels
 * above the screen's centre and asks to open. */
void PagedChoice_OpenPageCentered(PagedChoice *choice, int page, int wipe)
{
    u8 shown = (u8) page;

    PagedChoice_ShowPage(choice, &shown);
    PagedChoice_PlaceCentered(choice, 0, -0xc);
    PagedChoice_RequestOpen(choice, wipe);
}
CLEAN_AS(func_ov002_02209740, PagedChoice_OpenPageCentered)

/* func_ov002_02209770: loads palette 14 and the character tiles 0x26e-0x27d of
 * "menu/friend/bg1" into the layer. Returns what loading the tiles returns. */
int PagedChoice_LoadFriendGraphics(PagedChoice *choice)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov002_0220bbb8, heap, choice->layer, 0xe, 0xe, 0xe);
    return DisplayLayer_LoadCharsFromFile(data_ov002_0220bbcc, heap, choice->layer, 0x26e, 0x26e, 0x27d);
}
CLEAN_AS(func_ov002_02209770, PagedChoice_LoadFriendGraphics)

/* func_ov002_022097b8: loads palette 0 of "menu/inventory/b_itm.bpl" as palette 3, and the
 * character tiles 0x242-0x2d7 of "menu/inventory/b_choice.bch", into the layer. */
void PagedChoice_LoadChoiceGraphics(PagedChoice *choice)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov002_0220bbe0, heap, choice->layer, 0, 3, 3);
    DisplayLayer_LoadCharsFromFile(data_ov002_0220bbfc, heap, choice->layer, 0x242, 0x242, 0x2d7);
}
CLEAN_AS(func_ov002_022097b8, PagedChoice_LoadChoiceGraphics)

/* func_ov002_02209804: moves the window to (x, y) kept on the screen: x from 0, y from 10,
 * the right edge at most 255 and the bottom at most 182. */
void PagedChoice_PlaceClamped(PagedChoice *choice, int x, int y)
{
    int width = PagedChoice_Width(choice);
    int height = PagedChoice_Height(choice);

    if (x < 0) {
        x = 0;
    }
    if (y < 0xa) {
        y = 0xa;
    }
    if (add32(x, width) > 0xff) {
        x = sub32(0xff, width);
    }
    if (add32(y, height) > 0xb6) {
        y = sub32(0xb6, height);
    }
    PagedChoice_MoveTo(choice, x, y);
}
CLEAN_AS(func_ov002_02209804, PagedChoice_PlaceClamped)

/* func_ov002_0220984c: scrolls the layer to (x, y) and keeps the place as (-x, -y). Returns
 * -y. */
int PagedChoice_MoveTo(PagedChoice *choice, int x, int y)
{
    PagedChoice_Scroll(choice, x, y);
    choice->scroll_x = neg32(x);
    choice->scroll_y = neg32(y);
    return neg32(y);
}
CLEAN_AS(func_ov002_0220984c, PagedChoice_MoveTo)

/* func_ov002_02209868 */
void PagedChoice_Scroll(PagedChoice *choice, int x, int y)
{
    DisplayLayer_SetScroll(choice->layer, x, y);
}
CLEAN_AS(func_ov002_02209868, PagedChoice_Scroll)

/* func_ov002_02209874: places the window above a sliding window of main's (whose place counts
 * from the screen's centre): centred over it 2 pixels to the left, the centre first moved so
 * that the other window would lie within the screen; its bottom at the other's y, or its top
 * 16 pixels below that y when the top would be above 10. */
void PagedChoice_PlaceAboveWindow(PagedChoice *choice, void *window)
{
    int x;
    int y;
    int height;
    int half;
    int edge;

    choice->on_left = 0;
    x = add32(SlidingWindow_X(window), 0x80);
    y = add32(SlidingWindow_Y(window), 0x60);
    height = PagedChoice_Height(choice);
    half = SlidingWindow_Width(window) >> 1;
    edge = add32(x, half);
    if (edge > 0x100) {
        x = sub32(x, sub32(edge, 0x100));
    } else {
        edge = sub32(x, half);
        if (edge < 0) {
            x = sub32(x, edge);
        }
    }
    x = sub32(x, 2);
    x = sub32(x, PagedChoice_Width(choice) >> 1);
    edge = sub32(y, height);
    if (edge < 0xa) {
        y = add32(y, 0x10);
    } else {
        y = edge;
    }
    PagedChoice_PlaceClamped(choice, x, y);
}
CLEAN_AS(func_ov002_02209874, PagedChoice_PlaceAboveWindow)

/* func_ov002_022098ec: places the window with its bottom at `bottom`, kept on the screen. */
void PagedChoice_PlaceAbove(PagedChoice *choice, int x, int bottom)
{
    int y = sub32(bottom, PagedChoice_Height(choice));

    PagedChoice_PlaceClamped(choice, x, y);
}
CLEAN_AS(func_ov002_022098ec, PagedChoice_PlaceAbove)

/* func_ov002_02209908 */
void PagedChoice_Place(PagedChoice *choice, int x, int y)
{
    PagedChoice_PlaceClamped(choice, x, y);
}
CLEAN_AS(func_ov002_02209908, PagedChoice_Place)

/* func_ov002_02209910: places the window beside the point (x, y), its bottom 4 pixels above
 * it (the top at least at 10): on the left, ending 32 pixels right of the point, when its
 * left edge stays right of 0; else starting 16 pixels left of the point. Not kept on the
 * screen. */
void PagedChoice_PlaceBeside(PagedChoice *choice, int x, int y)
{
    int width = PagedChoice_Width(choice);
    int height = PagedChoice_Height(choice);
    int left = add32(sub32(x, width), 0x20);
    int top;

    if (left > 0) {
        choice->on_left = 1;
    } else {
        left = sub32(x, 0x10);
        choice->on_left = 0;
    }
    top = sub32(sub32(y, height), 4);
    if (top < 0xa) {
        top = 0xa;
    }
    PagedChoice_MoveTo(choice, left, top);
}
CLEAN_AS(func_ov002_02209910, PagedChoice_PlaceBeside)

/* func_ov002_02209954: places the window centred on (x, y) counted from the screen's centre.
 * Not kept on the screen. */
void PagedChoice_PlaceCentered(PagedChoice *choice, int x, int y)
{
    int width;
    int height;

    x = add32(x, 0x80);
    y = add32(y, 0x60);
    width = PagedChoice_Width(choice);
    height = PagedChoice_Height(choice);
    PagedChoice_MoveTo(choice, sub32(x, width >> 1), sub32(y, height >> 1));
}
CLEAN_AS(func_ov002_02209954, PagedChoice_PlaceCentered)

/* func_ov002_02209984: sets the window up on `layer` with `priority` and the screen file
 * `screen_file` (data_ov002_0220bc18 for NULL). The rows' text boxes take 26 tiles each from
 * the tile the file's cell at row 1, column 2 names; the page label is set up and the window
 * shows message 0x1f. */
void PagedChoice_Init(PagedChoice *choice, u8 layer, int priority, const char *screen_file)
{
    Heap *heap;
    u8 *screen;
    u16 tile;
    int i;

    choice->layer = layer;
    choice->priority = priority;
    choice->scroll_x = 0;
    choice->scroll_y = 0;
    choice->state = CHOICE_CLOSED;
    choice->request = CHOICE_REQUEST_NONE;
    choice->step = 0;
    choice->on_left = 0;
    choice->width = FRAME_COLUMNS;
    choice->row_count = PAGED_CHOICE_ROWS;
    choice->screen_file = screen_file != NULL ? screen_file : data_ov002_0220bc18;

    heap = data_021fbe94;
    screen = RomFile_Load(choice->screen_file, heap, -4, NULL);
    choice->first_tile = *(u16 *) screen_cell(screen, 1, 2) & 0x3ff;
    Heap_Free(heap, screen);

    tile = (u16) choice->first_tile;
    for (i = 0; i < PAGED_CHOICE_ROWS; i++) {
        ChoiceRow_SetStyle(&choice->rows[i], layer, tile, 1, 9);
        tile = (u16) (tile + ROW_TILES);
    }

    ((ObjectMethod2) (uintptr_t) virtual_at(choice->page_label, 0x10))(choice->page_label, 0x60, 0x8c);
    LabelSprite_SetOffset((LabelSprite *) (void *) choice->page_label, 0, 0);
    LabelSprite_HideSecond((LabelSprite *) (void *) choice->page_label);
    LabelSprite_SetWindow((LabelSprite *) (void *) choice->page_label);
    LabelSprite_SetState((LabelSprite *) (void *) choice->page_label, 1);
    MessageWindow_Close((MessageWindow *) (void *) choice->window);
    MessageWindow_Open((MessageWindow *) (void *) choice->window, 0x1f, 0x80, 0xc);
    SlidingWindow_SetObjWindow((SlidingWindow *) (void *) choice->window);
    choice->flags = 0;
}
CLEAN_AS(func_ov002_02209984, PagedChoice_Init)

/* The members in the reverse of their order. */
static void destroy_members(PagedChoice *choice)
{
    choice->vtable = data_ov002_0220bb98;
    Wipe_Destroy(&choice->wipe);
    MessageWindow_Destroy((MessageWindow *) (void *) choice->window);
    LabelButton0_Destroy((LabelButton *) (void *) choice->page_label);
    __cxa_vec_cleanup(choice->rows, PAGED_CHOICE_ROWS, sizeof(PagedChoiceRow), (void (*)(void *)) func_ov002_02209bf0);
}

/* func_ov002_02209a78 (vtable entry 1) */
PagedChoice *PagedChoice_Delete(PagedChoice *choice)
{
    destroy_members(choice);
    Heap_OperatorDeleteB(choice);
    return choice;
}
CLEAN_AS(func_ov002_02209a78, PagedChoice_Delete)

/* func_ov002_02209ac8 (vtable entry 0) */
PagedChoice *PagedChoice_Destroy(PagedChoice *choice)
{
    destroy_members(choice);
    return choice;
}
CLEAN_AS(func_ov002_02209ac8, PagedChoice_Destroy)

/* func_ov002_02209b14 */
PagedChoice *PagedChoice_Construct(PagedChoice *choice)
{
    choice->vtable = data_ov002_0220bb98;
    __cxa_vec_ctor(choice->rows, PAGED_CHOICE_ROWS, sizeof(PagedChoiceRow), (void (*)(void *)) func_ov002_02209c08,
                   (void (*)(void *)) func_ov002_02209bf0);
    LabelButton0_Construct((LabelButton *) (void *) choice->page_label);
    MessageWindow_Construct((MessageWindow *) (void *) choice->window);
    Wipe_Construct(&choice->wipe);
    return choice;
}
CLEAN_AS(func_ov002_02209b14, PagedChoice_Construct)

/* func_ov002_02209b6c */
void ChoiceRow_SetStyle(PagedChoiceRow *row, u8 style, u16 first_tile, u8 colour, u8 colour_39)
{
    row->style = style;
    row->first_tile = first_tile;
    row->colour = colour;
    row->colour_39 = colour_39;
}
CLEAN_AS(func_ov002_02209b6c, ChoiceRow_SetStyle)

/* func_ov002_02209b94: opens the row's text box, 13 cells wide, in `colour` (its low four
 * bits), or in the row's own colour when `colour` is negative. */
void ChoiceRow_Draw(PagedChoiceRow *row, int colour)
{
    u8 drawn = row->colour;

    if (colour >= 0) {
        drawn = (u8) (colour & 0xf);
    }
    TextLabel_OpenStyledBox2(&row->label, row->style, row->first_tile, ROW_CELLS, drawn, row->colour_39, 0);
}
CLEAN_AS(func_ov002_02209b94, ChoiceRow_Draw)

/* func_ov002_02209bd0 (vtable entry 1) */
PagedChoiceRow *ChoiceRow_Delete(PagedChoiceRow *row)
{
    row->label.vtable = (const TextVtable *) (const void *) data_ov002_0220bba8;
    TextLabel_DestructCopy(&row->label);
    Heap_OperatorDeleteB(row);
    return row;
}
CLEAN_AS(func_ov002_02209bd0, ChoiceRow_Delete)

/* func_ov002_02209bf0 (vtable entry 0) */
PagedChoiceRow *ChoiceRow_Destroy(PagedChoiceRow *row)
{
    row->label.vtable = (const TextVtable *) (const void *) data_ov002_0220bba8;
    TextLabel_DestructCopy(&row->label);
    return row;
}
CLEAN_AS(func_ov002_02209bf0, ChoiceRow_Destroy)

/* func_ov002_02209c08: an empty label drawn with style 3 from tile 0 in colours 1 and 9. */
PagedChoiceRow *ChoiceRow_Construct(PagedChoiceRow *row)
{
    TextLabel_ConstructCopy(&row->label);
    row->label.vtable = (const TextVtable *) (const void *) data_ov002_0220bba8;
    row->style = 3;
    row->first_tile = 0;
    row->colour = 1;
    row->colour_39 = 9;
    return row;
}
CLEAN_AS(func_ov002_02209c08, ChoiceRow_Construct)
