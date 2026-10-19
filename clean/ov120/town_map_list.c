/* The town map's list, its scroll, the marks on the map and what is picked (town_map.h). */
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "main/oam_buffer.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/screen_map.h"
#include "main/text_base.h"
#include "main/text_label.h"
#include "main/villager_roster.h"
#include "ov002/paged_choice.h"
#include "ov002/push_button.h"
#include "town_map.h"

/* The pad and the touch (main's bytes, as ov106's mailbox_scene.c reads them). */
extern PadState data_021fbe40;
extern u8 data_021f6c58; /* the touch's x */
extern u8 data_021f6c54; /* the touch's y */

/* The town's four players' records and its villagers. */
extern u8 data_021dc7bc[];
extern VillagerTown data_021e5a2c;

/* The kinds of marks 9-13 (overlay 117's places 12-16) and the marks of places 0-4 (rows 14-18). */
extern const u8 data_ov120_0229c500[5];
extern const u8 data_ov120_0229c508[5];

/* The OBJ every mark is drawn with: its tile and flips are changed for each (TownMap_DrawMark). */
extern OamEntry data_ov120_0229c558;

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

#define TOWN_MAP_BLINK_FRAMES 15
#define TOWN_MAP_BLINK_OFF_AT 5
#define TOWN_MAP_SCROLL_STEP 8
#define TOWN_MAP_KEY_SCROLL_STEP 4
#define TOWN_MAP_KNOB_TRAVEL 0x58 /* the knob's bar */
#define TOWN_MAP_ROW_HEIGHT 16

/* The list's screens: a row is two lines of 32 cells; its icon is the 2x2 cells at column 19,
 * its name from there to column 28. */
#define TOWN_MAP_SCREEN_LINE 0x20
#define TOWN_MAP_ROW_CELLS 0x40
#define TOWN_MAP_ICON_COLUMN 0x13
#define TOWN_MAP_ROW_LAST_COLUMN 0x1c
#define TOWN_MAP_BLANK_CELL 0x10
#define TOWN_MAP_BLANK_BYTES 0x14 /* ten cells */
#define TOWN_MAP_SCREEN_BYTES 0x800

/* The palettes of the list's rows and of the knob's bar. */
#define TOWN_MAP_PALETTE_PLAIN 4
#define TOWN_MAP_PALETTE_HIGHLIGHT 3

/* The places touched (inclusive unless said). */
#define TOWN_MAP_TABS_TOP 0x38
#define TOWN_MAP_TABS_BOTTOM 0x4c
#define TOWN_MAP_PEOPLE_TAB_LEFT 0xcc
#define TOWN_MAP_PEOPLE_TAB_RIGHT 0xe4
#define TOWN_MAP_PLACES_TAB_LEFT 0xb0
#define TOWN_MAP_PLACES_TAB_RIGHT 0xc8
#define TOWN_MAP_LIST_LEFT 0x98
#define TOWN_MAP_LIST_RIGHT 0xe8
#define TOWN_MAP_LIST_TOP 0x50
#define TOWN_MAP_LIST_END 0xb0 /* exclusive */
#define TOWN_MAP_MARK_REACH 8  /* a mark is touched less than this far from its place */

/* The map cursor's place when its mark has none. */
#define TOWN_MAP_CENTRE_X 0x58
#define TOWN_MAP_CENTRE_Y 0x70

/* The mark of `index`; TOWN_MAP_NONE is the padding after the marks. */
static TownMapMark *town_map_mark(TownMap *self, int index)
{
    return index < TOWN_MAP_MARKS ? &self->marks[index] : &self->past_marks;
}

/* func_ov120_0229a45c: the map cursor at the mark of the row under the cursor, or at the map's
 * centre when that mark is not on it.
 * QUIRK: the row's target is computed in a byte (`first_row` is 0xff until the list is made);
 * a row with no mark gives mark TOWN_MAP_NONE, read from the padding after the marks (zero), so
 * the cursor goes to (0, 0). */
void TownMap_MapCursorFromRow(TownMap *self)
{
    u8 target = (u8) (self->first_row + self->cursor + (TOWN_MAP_TARGET_ROW_FIRST - TOWN_MAP_CURSOR_ROW_FIRST));
    const TownMapMark *mark = town_map_mark(self, TownMap_MarkOfTarget(self, target));

    if (mark->kind == TOWN_MAP_KIND_NONE) {
        self->map_x = TOWN_MAP_CENTRE_X;
        self->map_y = TOWN_MAP_CENTRE_Y;
    } else {
        self->map_x = mark->x;
        self->map_y = mark->y;
    }
}
CLEAN_AS(func_ov120_0229a45c, TownMap_MapCursorFromRow)

/* func_ov120_0229a8e8: the blink stops, on. */
void TownMap_StopBlink(TownMap *self)
{
    TownMap_ClearFlags(self, TOWN_MAP_FLAG_BLINK);
    TownMap_ClearFlags(self, TOWN_MAP_FLAG_BLINK_OFF);
}
CLEAN_AS(func_ov120_0229a8e8, TownMap_StopBlink)

/* func_ov120_0229a904: the blink starts, on, for 15 frames. */
void TownMap_StartBlink(TownMap *self)
{
    TownMap_SetFlags(self, TOWN_MAP_FLAG_BLINK);
    TownMap_ClearFlags(self, TOWN_MAP_FLAG_BLINK_OFF);
    self->blink_timer = TOWN_MAP_BLINK_FRAMES;
}
CLEAN_AS(func_ov120_0229a904, TownMap_StartBlink)

/* func_ov120_0229a928: a frame of the blink. Each 15 frames it comes on and 10 frames later goes
 * off: for a picked row its mark (TOWN_MAP_FLAG_BLINK_OFF), else the picked mark's row (its
 * highlight, all rows plain when off). */
void TownMap_StepBlink(TownMap *self)
{
    if (!TownMap_TestFlags(self, TOWN_MAP_FLAG_BLINK)) {
        return;
    }
    if (self->blink_timer != 0) {
        self->blink_timer--;
    }
    if (self->blink_timer == 0) {
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PICKED_ROW) != 0) {
            TownMap_ClearFlags(self, TOWN_MAP_FLAG_BLINK_OFF);
        } else {
            TownMap_HighlightRow(self, self->picked_row);
        }
        self->blink_timer = TOWN_MAP_BLINK_FRAMES;
    } else if (self->blink_timer == TOWN_MAP_BLINK_OFF_AT) {
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PICKED_ROW) != 0) {
            TownMap_SetFlags(self, TOWN_MAP_FLAG_BLINK_OFF);
        } else {
            TownMap_HighlightRow(self, TOWN_MAP_NONE);
        }
    }
}
CLEAN_AS(func_ov120_0229a928, TownMap_StepBlink)

/* func_ov120_0229a9b4: a touch on the other list's tab switches to it, with nothing picked and
 * the list at its top; 1 when it did. */
int TownMap_TouchTabs(TownMap *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    if (y < TOWN_MAP_TABS_TOP || y > TOWN_MAP_TABS_BOTTOM) {
        return 0;
    }
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES)) {
        if (x < TOWN_MAP_PEOPLE_TAB_LEFT || x > TOWN_MAP_PEOPLE_TAB_RIGHT) {
            return 0;
        }
        TownMap_Select(self, TOWN_MAP_TARGET_NONE);
        TownMap_ShowPeople(self);
    } else {
        if (x < TOWN_MAP_PLACES_TAB_LEFT || x > TOWN_MAP_PLACES_TAB_RIGHT) {
            return 0;
        }
        TownMap_Select(self, TOWN_MAP_TARGET_NONE);
        TownMap_ShowPlaces(self);
    }
    TownMap_SetScroll(self, 0);
    self->first_row = 0xff;
    return 1;
}
CLEAN_AS(func_ov120_0229a9b4, TownMap_TouchTabs)

/* func_ov120_0229aa30: up or down held move the list 4 pixels from where it is going, within its
 * scroll. */
void TownMap_ScrollByKeys(TownMap *self)
{
    int scroll = self->scroll_target;
    int max;

    if (data_021fbe40.held & TOWN_MAP_KEY_UP) {
        scroll -= TOWN_MAP_KEY_SCROLL_STEP;
    } else if (data_021fbe40.held & TOWN_MAP_KEY_DOWN) {
        scroll += TOWN_MAP_KEY_SCROLL_STEP;
    }
    max = (int) TownMap_MaxScroll(self);
    if (scroll < 0) {
        scroll = 0;
    } else if (scroll > max) {
        scroll = max;
    }
    TownMap_SetScroll(self, (unsigned short) scroll);
}
CLEAN_AS(func_ov120_0229aa30, TownMap_ScrollByKeys)

/* func_ov120_0229aa80: the knob taken at `drag_y` follows the pen up and down its bar; the list
 * scrolls as far along its scroll. */
void TownMap_ScrollByDrag(TownMap *self)
{
    int pos = self->drag_knob_pos + (data_021f6c54 - self->drag_y);

    if (pos < 0) {
        pos = 0;
    } else if (pos > TOWN_MAP_KNOB_TRAVEL) {
        pos = TOWN_MAP_KNOB_TRAVEL;
    }
    TownMap_SetScroll(self, (unsigned short) ((int) TownMap_MaxScroll(self) * pos / TOWN_MAP_KNOB_TRAVEL));
}
CLEAN_AS(func_ov120_0229aa80, TownMap_ScrollByDrag)

/* func_ov120_0229aacc: with the knob shown, a touch on it takes it (where the pen and the knob
 * are kept); 1 when it did. */
int TownMap_TouchKnob(TownMap *self)
{
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLABLE) == 0) {
        return 0;
    }
    if (PushButton_Contains(&self->knob, data_021f6c58, data_021f6c54) == 0) {
        return 0;
    }
    self->drag_y = data_021f6c54;
    self->drag_knob_pos = self->knob_pos;
    return 1;
}
CLEAN_AS(func_ov120_0229aacc, TownMap_TouchKnob)

/* func_ov120_0229ab20: the scroll moves 8 pixels toward its target (straight to it from below
 * 8), and the knob follows; a list that does not scroll stops with the knob at its top. */
void TownMap_StepScroll(TownMap *self)
{
    int max = (int) TownMap_MaxScroll(self);

    if (max == 0) {
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_SCROLLING);
        self->knob_pos = 0;
        return;
    }
    if (self->scroll == self->scroll_target) {
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_SCROLLING);
    } else if (self->scroll < self->scroll_target) {
        self->scroll = (u16) (self->scroll + TOWN_MAP_SCROLL_STEP);
        if (self->scroll > self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    } else if (self->scroll < TOWN_MAP_SCROLL_STEP) {
        self->scroll = self->scroll_target;
    } else {
        self->scroll = (u16) (self->scroll - TOWN_MAP_SCROLL_STEP);
        if (self->scroll < self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    }
    self->knob_pos = (u8) (self->scroll * TOWN_MAP_KNOB_TRAVEL / max);
}
CLEAN_AS(func_ov120_0229ab20, TownMap_StepScroll)

/* func_ov120_0229abd0 */
int TownMap_IsScrolling(TownMap *self)
{
    return TownMap_TestFlags(self, TOWN_MAP_FLAG_SCROLLING);
}
CLEAN_AS(func_ov120_0229abd0, TownMap_IsScrolling)

/* func_ov120_0229abdc: the list scrolls to `scroll`. */
void TownMap_SetScrollTarget(TownMap *self, unsigned short scroll)
{
    self->scroll_target = scroll;
    TownMap_SetFlags(self, TOWN_MAP_FLAG_SCROLLING);
}
CLEAN_AS(func_ov120_0229abdc, TownMap_SetScrollTarget)

/* func_ov120_0229abec: the list at `scroll` at once (the knob follows on the next step). */
void TownMap_SetScroll(TownMap *self, unsigned short scroll)
{
    self->scroll = scroll;
    self->scroll_target = self->scroll;
    TownMap_SetFlags(self, TOWN_MAP_FLAG_SCROLLING);
}
CLEAN_AS(func_ov120_0229abec, TownMap_SetScroll)

/* func_ov120_0229ac08: the list scrolls to bring the picked row into view: up to it when it is
 * above, down to it when it is below the six rows in view; the players' rows to the top. */
void TownMap_ScrollToPickedRow(TownMap *self)
{
    int row = self->picked_row;
    int lowest_top;

    if (row == TOWN_MAP_NONE) {
        return;
    }
    if (row == TOWN_MAP_ROW_PLAYERS) {
        TownMap_SetScrollTarget(self, 0);
        return;
    }
    if (row < (self->scroll + TOWN_MAP_ROW_HEIGHT - 1) / TOWN_MAP_ROW_HEIGHT) {
        TownMap_SetScrollTarget(self, (unsigned short) (row * TOWN_MAP_ROW_HEIGHT));
    }
    row = self->picked_row;
    lowest_top = row <= TOWN_MAP_ROWS_IN_VIEW - 1 ? 0 : row - (TOWN_MAP_ROWS_IN_VIEW - 1);
    if (self->scroll / TOWN_MAP_ROW_HEIGHT < lowest_top) {
        TownMap_SetScrollTarget(self, (unsigned short) (lowest_top * TOWN_MAP_ROW_HEIGHT));
    }
}
CLEAN_AS(func_ov120_0229ac08, TownMap_ScrollToPickedRow)

/* func_ov120_0229ac60: after a switch of list, the list at once where the picked row is at its
 * bottom (at the top for the players' rows or the first six), to be made again. Returns 0xff. */
int TownMap_ScrollToSwitchedRow(TownMap *self)
{
    int row = self->picked_row;
    int scroll;

    if (row <= TOWN_MAP_ROWS_IN_VIEW - 1 || row == TOWN_MAP_ROW_PLAYERS) {
        scroll = 0;
    } else {
        scroll = (row - (TOWN_MAP_ROWS_IN_VIEW - 1)) * TOWN_MAP_ROW_HEIGHT;
    }
    TownMap_SetScroll(self, (unsigned short) scroll);
    self->first_row = 0xff;
    return 0xff;
}
CLEAN_AS(func_ov120_0229ac60, TownMap_ScrollToSwitchedRow)

/* func_ov120_0229ac8c: the mark a target stands for: a mark itself, or a row's by its value (a
 * player's: the players' house; a villager's: their house; a place's: from data_ov120_0229c508).
 * TOWN_MAP_NONE for none. */
unsigned char TownMap_MarkOfTarget(TownMap *self, unsigned int target)
{
    if (target >= TOWN_MAP_TARGET_MARK_FIRST && target <= TOWN_MAP_TARGET_MARK_LAST) {
        return (unsigned char) (target - TOWN_MAP_TARGET_MARK_FIRST);
    }
    if (target >= TOWN_MAP_TARGET_ROW_FIRST && target <= TOWN_MAP_TARGET_ROW_LAST) {
        unsigned int value = TownMap_Rows(self)[target - TOWN_MAP_TARGET_ROW_FIRST];
        if (value == TOWN_MAP_ROW_NONE) {
            return TOWN_MAP_NONE;
        }
        if (value < TOWN_MAP_ROW_VILLAGER_FIRST) {
            return TOWN_MAP_MARK_PLAYERS_HOUSE;
        }
        if (value < TOWN_MAP_ROW_PLACE_FIRST) {
            return (unsigned char) (value - TOWN_MAP_ROW_VILLAGER_FIRST);
        }
        if (value <= TOWN_MAP_ROW_PLACE_LAST) {
            return data_ov120_0229c508[value - TOWN_MAP_ROW_PLACE_FIRST];
        }
    }
    return TOWN_MAP_NONE;
}
CLEAN_AS(func_ov120_0229ac8c, TownMap_MarkOfTarget)

/* func_ov120_0229acf4: the row a target stands for: a row itself; for a villager's house the
 * people's row with that villager; for the players' house TOWN_MAP_ROW_PLAYERS; for a place's
 * mark (9-13) row 0-4 of the places. TOWN_MAP_NONE for none. */
unsigned char TownMap_RowOfTarget(TownMap *self, unsigned int target)
{
    if (target == TOWN_MAP_MARK_PLAYERS_HOUSE + 1) {
        return TOWN_MAP_ROW_PLAYERS;
    }
    if (target >= 1 && target <= TOWN_MAP_MARK_PLAYERS_HOUSE) {
        unsigned int value = target + (TOWN_MAP_ROW_VILLAGER_FIRST - 1);
        for (int i = 0; i < self->people_count; i++) {
            if (self->people[i] == value) {
                return (unsigned char) i;
            }
        }
        return TOWN_MAP_NONE;
    }
    if (target >= TOWN_MAP_MARK_PLAYERS_HOUSE + 2 && target <= TOWN_MAP_TARGET_MARK_LAST) {
        return (unsigned char) (target - (TOWN_MAP_MARK_PLAYERS_HOUSE + 2));
    }
    if (target >= TOWN_MAP_TARGET_ROW_FIRST && target <= TOWN_MAP_TARGET_ROW_LAST) {
        return (unsigned char) (target - TOWN_MAP_TARGET_ROW_FIRST);
    }
    return TOWN_MAP_NONE;
}
CLEAN_AS(func_ov120_0229acf4, TownMap_RowOfTarget)

/* func_ov120_0229ad5c: a row of `list_screen` highlighted (its two lines, columns 19-28):
 * TOWN_MAP_ROW_PLAYERS highlights the first four rows, TOWN_MAP_NONE makes every row plain. The
 * shown list is made again. */
void TownMap_HighlightRow(TownMap *self, int row)
{
    TownMap_SetFlags(self, TOWN_MAP_FLAG_LIST_DIRTY);
    if (row == TOWN_MAP_NONE) {
        ScreenMap_SetPalette(self->list_screen, TOWN_MAP_ICON_COLUMN, 0, TOWN_MAP_ROW_LAST_COLUMN, 0x19,
                             TOWN_MAP_PALETTE_PLAIN);
    } else if (row == TOWN_MAP_ROW_PLAYERS) {
        ScreenMap_SetPalette(self->list_screen, TOWN_MAP_ICON_COLUMN, 0, TOWN_MAP_ROW_LAST_COLUMN, 7,
                             TOWN_MAP_PALETTE_HIGHLIGHT);
    } else {
        ScreenMap_SetPalette(self->list_screen, TOWN_MAP_ICON_COLUMN, row * 2, TOWN_MAP_ROW_LAST_COLUMN, row * 2 + 1,
                             TOWN_MAP_PALETTE_HIGHLIGHT);
    }
}
CLEAN_AS(func_ov120_0229ad5c, TownMap_HighlightRow)

/* func_ov120_0229adc4: `target` picked (TownMapTarget), or nothing for 0. A mark of the list not
 * shown switches the list (people for the houses' marks 1-9, places for the others) with the
 * picked row in view; else the list scrolls to the picked row, which is highlighted, and the
 * blink starts. */
void TownMap_Select(TownMap *self, unsigned int target)
{
    if (target == TOWN_MAP_TARGET_NONE) {
        self->picked_mark = TOWN_MAP_NONE;
        self->picked_row = TOWN_MAP_NONE;
        TownMap_StopBlink(self);
        return;
    }
    TownMap_StartBlink(self);
    self->picked_row = TownMap_RowOfTarget(self, target);
    self->picked_mark = TownMap_MarkOfTarget(self, target);
    if (target >= TOWN_MAP_TARGET_MARK_FIRST && target <= TOWN_MAP_TARGET_MARK_LAST) {
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_PICKED_ROW);
        if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES)) {
            if (target <= TOWN_MAP_TARGET_HOUSES_LAST) {
                TownMap_ShowPeople(self);
                TownMap_ScrollToSwitchedRow(self);
                return;
            }
        } else if (target > TOWN_MAP_TARGET_HOUSES_LAST) {
            TownMap_ShowPlaces(self);
            TownMap_ScrollToSwitchedRow(self);
            return;
        }
    } else {
        TownMap_SetFlags(self, TOWN_MAP_FLAG_PICKED_ROW);
    }
    TownMap_ScrollToPickedRow(self);
    TownMap_HighlightRow(self, TOWN_MAP_NONE);
    TownMap_HighlightRow(self, self->picked_row);
}
CLEAN_AS(func_ov120_0229adc4, TownMap_Select)

/* func_ov120_0229ae78: the first mark less than 8 pixels from (x, y) both ways, or
 * TOWN_MAP_NONE. */
unsigned char TownMap_FindMarkAt(TownMap *self, int x, int y)
{
    for (int i = 0; i < TOWN_MAP_MARKS; i++) {
        const TownMapMark *mark = &self->marks[i];
        if (mark->kind == TOWN_MAP_KIND_NONE) {
            continue;
        }
        if (mark->x - TOWN_MAP_MARK_REACH >= x || mark->x + TOWN_MAP_MARK_REACH <= x) {
            continue;
        }
        if (mark->y - TOWN_MAP_MARK_REACH >= y || mark->y + TOWN_MAP_MARK_REACH <= y) {
            continue;
        }
        return (unsigned char) i;
    }
    return TOWN_MAP_NONE;
}
CLEAN_AS(func_ov120_0229ae78, TownMap_FindMarkAt)

/* func_ov120_0229aed8: a touch on a mark picks it; 1 when it did. */
int TownMap_TouchMap(TownMap *self)
{
    int mark = TownMap_FindMarkAt(self, data_021f6c58, data_021f6c54);

    if (mark == TOWN_MAP_NONE) {
        return 0;
    }
    TownMap_Select(self, (unsigned char) (mark + TOWN_MAP_TARGET_MARK_FIRST));
    return 1;
}
CLEAN_AS(func_ov120_0229aed8, TownMap_TouchMap)

/* The kinds of the extra marks by overlay 117's kind of their place (bit 7: flipped). */
static u8 town_map_extra_kind(unsigned int kind)
{
    switch (kind) {
        case 0:
            return 8;
        case 1:
            return 7;
        case 2:
            return 9;
        case 3:
            return 0x89;
        default:
            return TOWN_MAP_KIND_NONE;
    }
}

/* func_ov120_0229af10: the marks from overlay 117's places, 8 pixels left of and 16 below each
 * place (in a byte): places 0-2 the extra marks, 3-10 the villagers' houses (kind 0), 11 the
 * players' house (kind 1), 12-16 places (data_ov120_0229c500). A place not set is no mark. */
void TownMap_ReadMarks(TownMap *self, TownMapMarker *places)
{
    for (unsigned int i = 0; i < TOWN_MAP_EXTRA_MARKS; i++) {
        TownMapMark *mark = &self->extra_marks[i];
        const TownMapMarker *place = TownMapMarkers_Get(places, i);
        if (place != NULL) {
            mark->kind = town_map_extra_kind(TownMapMarkers_Kind(places, i));
            mark->x = (u8) (place->x - 8);
            mark->y = (u8) (place->y + 0x10);
        } else {
            mark->kind = TOWN_MAP_KIND_NONE;
        }
    }
    for (unsigned int i = 0; i < TOWN_MAP_MARKS; i++) {
        unsigned int index = i + TOWN_MAP_EXTRA_MARKS;
        TownMapMark *mark = &self->marks[i];
        const TownMapMarker *place = TownMapMarkers_Get(places, index);
        if (place != NULL) {
            if (i < TOWN_MAP_MARK_PLAYERS_HOUSE) {
                mark->kind = 0;
            } else if (i == TOWN_MAP_MARK_PLAYERS_HOUSE) {
                mark->kind = 1;
            } else {
                mark->kind = data_ov120_0229c500[i - (TOWN_MAP_MARK_PLAYERS_HOUSE + 1)];
            }
            mark->x = (u8) (place->x - 8);
            mark->y = (u8) (place->y + 0x10);
        } else {
            mark->kind = TOWN_MAP_KIND_NONE;
        }
    }
}
CLEAN_AS(func_ov120_0229af10, TownMap_ReadMarks)

/* func_ov120_0229b06c: a mark of `kind` drawn on the sub screen at (x, y) in `palette` (-1 for
 * the OBJ's own), flipped across when `flip` is set: OBJ 0xc0 + 2 * kind with priority 1. The
 * scene is not read.
 * QUIRK: the shared OBJ keeps the tile of the last mark; after a flipped one its horizontal flip
 * is cleared, whatever it was before. */
void TownMap_DrawMark(TownMap *self, int x, int y, int kind, int flip, int palette)
{
    OamEntry *obj = &data_ov120_0229c558;
    unsigned int flags = 0;

    (void) self;
    obj->attr2 = (u16) ((obj->attr2 & 0xfc00) | ((u16) (kind * 2 + 0xc0) & 0x3ff));
    if (flip) {
        /* attr1's bits 9-13, of which bit 12 is the horizontal flip */
        flags = (u16) (((unsigned int) (obj->attr1 >> 9) & 0x1f) | 8);
        obj->attr1 = (u16) ((obj->attr1 & 0xc1ff) | ((flags & 0x1f) << 9));
    }
    OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, obj, x, y, palette, 1, NULL);
    if (flip) {
        obj->attr1 = (u16) ((obj->attr1 & 0xc1ff) | ((flags & 0x17) << 9));
    }
}
CLEAN_AS(func_ov120_0229b06c, TownMap_DrawMark)

/* func_ov120_0229b100: a touch on the list picks the row under it; 1 when it did. */
int TownMap_TouchList(TownMap *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    if (x < TOWN_MAP_LIST_LEFT || x > TOWN_MAP_LIST_RIGHT) {
        return 0;
    }
    if (y < TOWN_MAP_LIST_TOP || y >= TOWN_MAP_LIST_END) {
        return 0;
    }
    TownMap_Select(self, (unsigned char) (((y + self->scroll - TOWN_MAP_LIST_TOP) >> 4) + TOWN_MAP_TARGET_ROW_FIRST));
    return 1;
}
CLEAN_AS(func_ov120_0229b100, TownMap_TouchList)

/* func_ov120_0229b14c: how far the list shown scrolls: 16 pixels a row past the six in view. */
unsigned int TownMap_MaxScroll(TownMap *self)
{
    unsigned int rows = TownMap_RowCount(self);

    if (rows <= TOWN_MAP_ROWS_IN_VIEW) {
        return 0;
    }
    return (rows - TOWN_MAP_ROWS_IN_VIEW) * TOWN_MAP_ROW_HEIGHT;
}
CLEAN_AS(func_ov120_0229b14c, TownMap_MaxScroll)

/* func_ov120_0229b168: the rows of the list shown. */
unsigned char TownMap_RowCount(TownMap *self)
{
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES) != 0) {
        return self->place_count;
    }
    return self->people_count;
}
CLEAN_AS(func_ov120_0229b168, TownMap_RowCount)

/* func_ov120_0229b188: the values of the list shown. */
u8 *TownMap_Rows(TownMap *self)
{
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES) != 0) {
        return self->places;
    }
    return self->people;
}
CLEAN_AS(func_ov120_0229b188, TownMap_Rows)

/* func_ov120_0229b1b0: the list shown made again: its screen, its labels, the knob shown (and
 * the bar coloured on the map's screen) when it scrolls, the picked row highlighted. */
void TownMap_ShowList(TownMap *self)
{
    int bar_palette;

    TownMap_BuildListScreen(self);
    TownMap_MakeShownLabels(self);
    if (TownMap_MaxScroll(self) == 0) {
        TownMap_ClearFlags(self, TOWN_MAP_FLAG_SCROLLABLE);
        bar_palette = TOWN_MAP_PALETTE_PLAIN;
    } else {
        TownMap_SetFlags(self, TOWN_MAP_FLAG_SCROLLABLE);
        bar_palette = TOWN_MAP_PALETTE_HIGHLIGHT;
    }
    ScreenMap_SetPalette(self->map_screen, 0x1d, 0x0a, 0x1d, 0x15, (u32) bar_palette);
    TownMap_SetFlags(self, TOWN_MAP_FLAG_MAP_UPLOAD);
    TownMap_HighlightRow(self, self->picked_row);
}
CLEAN_AS(func_ov120_0229b1b0, TownMap_ShowList)

/* func_ov120_0229b214 */
void TownMap_ShowPlaces(TownMap *self)
{
    TownMap_SetFlags(self, TOWN_MAP_FLAG_PLACES);
    TownMap_ShowList(self);
}
CLEAN_AS(func_ov120_0229b214, TownMap_ShowPlaces)

/* func_ov120_0229b22c */
void TownMap_ShowPeople(TownMap *self)
{
    TownMap_ClearFlags(self, TOWN_MAP_FLAG_PLACES);
    TownMap_ShowList(self);
}
CLEAN_AS(func_ov120_0229b22c, TownMap_ShowPeople)

/* func_ov120_0229b244: a row's label given the name its value stands for (TownMapRowValue);
 * empty for none or a value past the places. The scene is not read. */
void TownMap_SetRowText(TownMap *self, TextLabel *label, unsigned int value)
{
    PagedChoiceRow *row = (PagedChoiceRow *) (void *) label;

    (void) self;
    if (value == TOWN_MAP_ROW_NONE) {
        TextBase_Clear(label);
    } else if (value == TOWN_MAP_ROW_SELF) {
        ChoiceRow_SetName(row, PlayerRecord_Player(PlayerRecords_Current()));
    } else if (value < TOWN_MAP_ROW_VILLAGER_FIRST) {
        ChoiceRow_SetPlayerName(row, (int) (value - TOWN_MAP_ROW_PLAYER_FIRST));
    } else if (value < TOWN_MAP_ROW_PLACE_FIRST) {
        ChoiceRow_SetListBName(row, (int) (value - TOWN_MAP_ROW_VILLAGER_FIRST));
    } else if (value <= TOWN_MAP_ROW_PLACE_LAST) {
        /* menu messages 0x96-0x9a */
        TextLabel_LoadMenuMessage(label, (char) (value + 0x88));
    } else {
        TextBase_Clear(label);
    }
}
CLEAN_AS(func_ov120_0229b244, TownMap_SetRowText)

/* func_ov120_0229b2b0: a label for each of the 13 rows of `rows`, 16 pixels apart, with its
 * name. */
void TownMap_MakeLabels(TownMap *self, u8 *rows)
{
    for (int i = 0; i < TOWN_MAP_ROWS; i++) {
        TextLabel *label = TownMap_TakeLabel(self);
        TextLabel_OpenStyledBox2(label, 6, 0x160 + i * 16, 8, 1, 0xf, 0);
        TownMap_SetRowText(self, label, rows[i]);
        TextLabel_Show(label, 0, 0);
    }
}
CLEAN_AS(func_ov120_0229b2b0, TownMap_MakeLabels)

/* func_ov120_0229b308: the labels of the list shown. */
void TownMap_MakeShownLabels(TownMap *self)
{
    if (TownMap_TestFlags(self, TOWN_MAP_FLAG_PLACES) != 0) {
        TownMap_MakeLabels(self, self->places);
    } else {
        TownMap_MakeLabels(self, self->people);
    }
}
CLEAN_AS(func_ov120_0229b308, TownMap_MakeShownLabels)

/* func_ov120_0229b33c: the two lists: the people (the current player when found among the
 * town's four, the other players there are, the villagers there are) and the five places.
 * QUIRK: the people's rows past the last are not cleared: the loop meant for them clears the
 * places' rows from that index (which are written next anyway). */
void TownMap_BuildLists(TownMap *self)
{
    int n = 0;
    int current = PlayerRecords_FindIndex(data_021dc7bc,
                                          (const PlayerRecordsId *) (void *) PlayerRecord_Player(PlayerRecords_Current()));

    if (current != -1) {
        self->people[0] = TOWN_MAP_ROW_SELF;
        n++;
    }
    for (int i = 0; i < 4; i++) {
        if (i != current && PlayerRecords_TownExists(data_021dc7bc, i) != 0) {
            self->people[n] = (u8) (i + TOWN_MAP_ROW_PLAYER_FIRST);
            n++;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (VillagerRoster_IsFilled(&data_021e5a2c, i) != 0) {
            self->people[n] = (u8) (i + TOWN_MAP_ROW_VILLAGER_FIRST);
            n++;
        }
    }
    self->people_count = (u8) n;
    for (; n < TOWN_MAP_ROWS; n++) {
        self->places[n] = TOWN_MAP_ROW_NONE;
    }

    int k = 0;
    for (int j = 0; j < 5; j++) {
        self->places[k] = (u8) (j + TOWN_MAP_ROW_PLACE_FIRST);
        k++;
    }
    self->place_count = (u8) k;
    for (; k < TOWN_MAP_ROWS; k++) {
        self->places[k] = TOWN_MAP_ROW_NONE;
    }
}
CLEAN_AS(func_ov120_0229b33c, TownMap_BuildLists)

/* func_ov120_0229b400: the next label of the frame; past the 13th, the last again. */
TextLabel *TownMap_TakeLabel(TownMap *self)
{
    if (self->label_count >= TOWN_MAP_LABELS) {
        return &self->labels[TOWN_MAP_LABELS - 1];
    }
    self->label_count++;
    return &self->labels[self->label_count - 1];
}
CLEAN_AS(func_ov120_0229b400, TownMap_TakeLabel)

/* func_ov120_0229b434: every label's box closed, none taken. */
void TownMap_ReleaseLabels(TownMap *self)
{
    self->label_count = 0;
    for (int i = 0; i < TOWN_MAP_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov120_0229b434, TownMap_ReleaseLabels)

/* func_ov120_0229b45c: the icon of a row by its value: the template's row it is drawn at (0 the
 * players', 1 the villagers', 2-6 the places' in their own order, 7 none). The scene and the
 * row are not read. */
unsigned int TownMap_RowIcon(TownMap *self, unsigned int value, int row)
{
    (void) self;
    (void) row;
    if (value == TOWN_MAP_ROW_NONE) {
        return 7;
    }
    if (value < TOWN_MAP_ROW_VILLAGER_FIRST) {
        return 0;
    }
    if (value < TOWN_MAP_ROW_PLACE_FIRST) {
        return 1;
    }
    switch (value - TOWN_MAP_ROW_PLACE_FIRST) {
        case 0:
            return 3;
        case 1:
            return 5;
        case 2:
            return 2;
        case 3:
            return 4;
        case 4:
            return 6;
        default:
            return 7;
    }
}
CLEAN_AS(func_ov120_0229b45c, TownMap_RowIcon)

/* The cell `line`, `column` of a list screen. */
static u16 *town_map_cell(u16 *screen, int line, int column)
{
    return &screen[line * TOWN_MAP_SCREEN_LINE + column];
}

/* func_ov120_0229b4b0: `list_screen` from the template, each row given the icon of its value
 * (2x2 cells copied from the template's row of that icon); queued for sub BG3. */
void TownMap_BuildListScreen(TownMap *self)
{
    const u8 *rows;

    MIi_CpuCopy16(self->list_template, self->list_screen, TOWN_MAP_SCREEN_BYTES);
    rows = TownMap_Rows(self);
    for (int i = 0; i < TOWN_MAP_ROWS; i++) {
        int icon = (int) TownMap_RowIcon(self, rows[i], i);
        for (int line = 0; line < 2; line++) {
            for (int column = 0; column < 2; column++) {
                *town_map_cell(self->list_screen, i * 2 + line, TOWN_MAP_ICON_COLUMN + column) =
                    *town_map_cell(self->list_template, icon * 2 + line, TOWN_MAP_ICON_COLUMN + column);
            }
        }
    }
    TownMap_SetFlags(self, TOWN_MAP_FLAG_LIST_UPLOAD);
}
CLEAN_AS(func_ov120_0229b4b0, TownMap_BuildListScreen)

/* Ten cells of both lines of a row blanked. */
static void town_map_blank_row(u16 *screen, int row)
{
    MIi_CpuClear16(TOWN_MAP_BLANK_CELL, town_map_cell(screen, row * 2, TOWN_MAP_ICON_COLUMN), TOWN_MAP_BLANK_BYTES);
    MIi_CpuClear16(TOWN_MAP_BLANK_CELL, town_map_cell(screen, row * 2 + 1, TOWN_MAP_ICON_COLUMN), TOWN_MAP_BLANK_BYTES);
}

/* func_ov120_0229b548: `list_shown` from `list_screen` with the rows above the first in view
 * and from the seventh in view on blanked; queued for sub BG3. */
void TownMap_MakeShownList(TownMap *self)
{
    int first = self->scroll >> 4;

    MIi_CpuCopy16(self->list_screen, self->list_shown, TOWN_MAP_SCREEN_BYTES);
    self->first_row = (u8) first;
    for (int row = 0; row < first; row++) {
        town_map_blank_row(self->list_shown, row);
    }
    for (int row = first + TOWN_MAP_ROWS_IN_VIEW + 1; row < TOWN_MAP_ROWS; row++) {
        town_map_blank_row(self->list_shown, row);
    }
    TownMap_SetFlags(self, TOWN_MAP_FLAG_LIST_UPLOAD);
}
CLEAN_AS(func_ov120_0229b548, TownMap_MakeShownList)
