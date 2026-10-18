/* The town map of the menu (map_menu.h): its flags, the marks of the map, the two lists and
 * their rows, the selection and its blink, and the list's scroll. */
#include "map_menu.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/oam_buffer.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/text_base.h"
#include "main/villager_roster.h"
#include "ov002/paged_choice.h"
#include "ov002/push_button.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(MapMenu, wipe_y) == 0x94, "wipe_y");
static_assert(offsetof(MapMenu, flags) == 0x9c && offsetof(MapMenu, labels_used) == 0xa0, "flags");
static_assert(offsetof(MapMenu, knob) == 0xa4 && offsetof(MapMenu, mark) == 0xa9, "bytes");
static_assert(offsetof(MapMenu, focus) == 0xac && offsetof(MapMenu, frame) == 0xb1, "bytes");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(MapMenu, rows_task) == 0xb4, "tasks");
static_assert(offsetof(MapMenu, map_task) == 0xd8 && offsetof(MapMenu, labels) == 0xfc, "labels");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(MapMenu, knob_button) == 0x678, "knob");
static_assert(sizeof(PushButton) == 0x48 && offsetof(MapMenu, cursor) == 0x6c0, "cursor");
static_assert(sizeof(Glider) == 0x64 && offsetof(MapMenu, map_screen) == 0x724, "map_screen");
static_assert(offsetof(MapMenu, shown_rows) == 0xf24 && offsetof(MapMenu, rows) == 0x1724, "rows");
static_assert(offsetof(MapMenu, rows_template) == 0x1f24 && offsetof(MapMenu, map_chars) == 0x2724, "chars");
static_assert(sizeof(TownMapMarker) == 6 && offsetof(MapMenu, spots) == 0x4724, "spots");
static_assert(offsetof(MapMenu, residents) == 0x478a && offsetof(MapMenu, places) == 0x4797, "lists");
static_assert(sizeof(MapMenuMark) == 3 && offsetof(MapMenu, extra_marks) == 0x47a4, "marks");
static_assert(offsetof(MapMenu, marks) == 0x47ad && sizeof(MapMenu) == 0x47d8, "size (func_ov118_0229c9e0)");

/* The town's players' records and villagers. */
extern u8 data_021dc7bc[];
extern VillagerTown data_021e5a2c;

/* The mark of each place (MAP_MENU_ENTRY_PLACE + i), and the row of each building mark 9-13 in
 * the places' list; the kind of the marks of spots 12-16. */
extern const u8 data_ov118_0229ca90[MAP_MENU_PLACES];
extern const u8 data_ov118_0229ca98[MAP_MENU_PLACES];
extern const u8 data_ov118_0229caa0[MAP_MENU_PLACES];

/* The OBJ every mark is drawn with (only its characters and flip are changed). */
extern OamEntry data_ov118_0229cb40;

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

/* The palettes of a list row: as it is, and highlighted (also the scroll bar's when it is in
 * use). */
#define MAP_MENU_PALETTE_NORMAL 4
#define MAP_MENU_PALETTE_LIT 3

/* The rows' columns in the screens. */
#define MAP_MENU_ROW_LEFT 0x13
#define MAP_MENU_ROW_RIGHT 0x1c
#define MAP_MENU_ROW_TILES 0x40 /* two tile rows */
#define MAP_MENU_BLANK_TILE 0x10

/* The texts' boxes: 16 characters a row from tile 0x160. */
#define MAP_MENU_LABEL_STYLE 6
#define MAP_MENU_LABEL_FIRST_TILE 0x160
#define MAP_MENU_PLACE_MESSAGE 0x88 /* + the entry: menu messages 0x96-0x9a */

#define MAP_MENU_BLINK_FRAMES 0x0f
#define MAP_MENU_BLINK_HALF 5

/* func_ov118_0229a438: a mark's destructor (handed to __cxa_vec_ctor and __cxa_vec_cleanup):
 * nothing. */
void MapMenu_ElementNoOp(void *element)
{
    (void) element;
}
CLEAN_AS(func_ov118_0229a438, MapMenu_ElementNoOp)

/* func_ov118_0229a43c: a mark's constructor (handed to __cxa_vec_ctor): nothing. */
void MapMenu_ConstructMark(void *mark)
{
    (void) mark;
}
CLEAN_AS(func_ov118_0229a43c, MapMenu_ConstructMark)

/* func_ov118_0229a440 */
void MapMenu_ClearFlags(MapMenu *self, unsigned int flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov118_0229a440, MapMenu_ClearFlags)

/* func_ov118_0229a450 */
void MapMenu_SetFlags(MapMenu *self, unsigned short flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov118_0229a450, MapMenu_SetFlags)

/* func_ov118_0229a460: whether any of `flags` is set. */
int MapMenu_TestFlags(MapMenu *self, unsigned short flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov118_0229a460, MapMenu_TestFlags)

/* func_ov118_0229a474: with a mark selected, sound `sound` panned by the mark's x: -127 at
 * x 0x18, 2 a pixel to the right, at most 128. */
void MapMenu_PlayAtMark(MapMenu *self, int sound)
{
    if (self->mark == MAP_MENU_NO_MARK) {
        return;
    }
    int pan = (self->marks[self->mark].x - 0x18) * 2 - 0x7f;
    if (pan < -127) {
        pan = -127;
    } else if (pan > 128) {
        pan = 128;
    }
    SoundSys_StartIndexOnHandle38(sound, pan);
}
CLEAN_AS(func_ov118_0229a474, MapMenu_PlayAtMark)

/* func_ov118_0229aa98 */
void MapMenu_StopBlink(MapMenu *self)
{
    MapMenu_ClearFlags(self, MAP_MENU_FLAG_BLINK);
    MapMenu_ClearFlags(self, MAP_MENU_FLAG_MARK_OFF);
}
CLEAN_AS(func_ov118_0229aa98, MapMenu_StopBlink)

/* func_ov118_0229aab4: the blink starts in its on half. */
void MapMenu_StartBlink(MapMenu *self)
{
    MapMenu_SetFlags(self, MAP_MENU_FLAG_BLINK);
    MapMenu_ClearFlags(self, MAP_MENU_FLAG_MARK_OFF);
    self->blink = MAP_MENU_BLINK_FRAMES;
}
CLEAN_AS(func_ov118_0229aab4, MapMenu_StartBlink)

/* func_ov118_0229aad8: a frame of the blink: every 15 frames the selection's other half (its
 * mark when it was a row, else its row) is lit again, 5 frames before that it goes off. */
void MapMenu_StepBlink(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_BLINK) == 0) {
        return;
    }
    if (self->blink != 0) {
        self->blink--;
    }
    if (self->blink == 0) {
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_FROM_LIST) != 0) {
            MapMenu_ClearFlags(self, MAP_MENU_FLAG_MARK_OFF);
        } else {
            MapMenu_HighlightRow(self, self->row);
        }
        self->blink = MAP_MENU_BLINK_FRAMES;
    } else if (self->blink == MAP_MENU_BLINK_HALF) {
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_FROM_LIST) != 0) {
            MapMenu_SetFlags(self, MAP_MENU_FLAG_MARK_OFF);
        } else {
            MapMenu_HighlightRow(self, MAP_MENU_NO_ROW);
        }
    }
}
CLEAN_AS(func_ov118_0229aad8, MapMenu_StepBlink)

/* func_ov118_0229ad24: the scroll moves 8 pixels towards its target (from below 8 down it
 * jumps there); the knob follows: 0 at the top, 0x58 at the bottom. A list that does not
 * scroll stops it with the knob at 0. */
void MapMenu_StepScroll(MapMenu *self)
{
    int max = (int) MapMenu_MaxScroll(self);
    if (max == 0) {
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_SCROLLING);
        self->knob = 0;
        return;
    }
    if (self->scroll == self->scroll_target) {
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_SCROLLING);
    } else if (self->scroll < self->scroll_target) {
        self->scroll = (u16) (self->scroll + 8);
        if (self->scroll > self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    } else if (self->scroll < 8) {
        self->scroll = self->scroll_target;
    } else {
        self->scroll = (u16) (self->scroll - 8);
        if (self->scroll < self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    }
    self->knob = (u8) (self->scroll * 0x58 / max);
}
CLEAN_AS(func_ov118_0229ad24, MapMenu_StepScroll)

/* func_ov118_0229add4 */
int MapMenu_IsScrolling(MapMenu *self)
{
    return MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLING);
}
CLEAN_AS(func_ov118_0229add4, MapMenu_IsScrolling)

/* func_ov118_0229ade0: the scroll moves to `target`. */
void MapMenu_ScrollTo(MapMenu *self, int target)
{
    self->scroll_target = (u16) target;
    MapMenu_SetFlags(self, MAP_MENU_FLAG_SCROLLING);
}
CLEAN_AS(func_ov118_0229ade0, MapMenu_ScrollTo)

/* func_ov118_0229adf0: the scroll is put at `scroll` (the knob follows next frame). */
void MapMenu_JumpTo(MapMenu *self, unsigned short scroll)
{
    self->scroll = scroll;
    self->scroll_target = self->scroll;
    MapMenu_SetFlags(self, MAP_MENU_FLAG_SCROLLING);
}
CLEAN_AS(func_ov118_0229adf0, MapMenu_JumpTo)

/* func_ov118_0229ae0c: the selected row brought into sight: to the top when it is above
 * (partly), else so that it is the sixth row when it is below; the players' rows scroll to the
 * top. */
void MapMenu_ScrollToRow(MapMenu *self)
{
    int row = self->row;
    if (row == MAP_MENU_NO_ROW) {
        return;
    }
    if (row == MAP_MENU_PLAYER_ROWS) {
        MapMenu_ScrollTo(self, 0);
        return;
    }
    if (row < (self->scroll + 15) >> 4) {
        MapMenu_ScrollTo(self, row << 4);
    }
    int lowest_top = row <= MAP_MENU_VISIBLE_ROWS - 1 ? 0 : row - (MAP_MENU_VISIBLE_ROWS - 1);
    if (self->scroll >> 4 < lowest_top) {
        MapMenu_ScrollTo(self, lowest_top << 4);
    }
}
CLEAN_AS(func_ov118_0229ae0c, MapMenu_ScrollToRow)

/* func_ov118_0229ae64: the scroll put where the selected row is the sixth (the top for the
 * first six and the players' rows); the shown rows are made again. */
void MapMenu_JumpToRow(MapMenu *self)
{
    int row = self->row;
    int scroll;
    if (row <= MAP_MENU_VISIBLE_ROWS - 1 || row == MAP_MENU_PLAYER_ROWS) {
        scroll = 0;
    } else {
        scroll = (row - (MAP_MENU_VISIBLE_ROWS - 1)) << 4;
    }
    MapMenu_JumpTo(self, (unsigned short) scroll);
    self->shown_top = 0xff;
}
CLEAN_AS(func_ov118_0229ae64, MapMenu_JumpToRow)

/* func_ov118_0229ae90: the mark of a selection: a mark's own; for a row of the shown list, the
 * house of its player (mark 8, the players' house) or villager (marks 0-7) or the place's mark
 * (data_ov118_0229ca90); MAP_MENU_NO_MARK for an empty row or anything else. */
unsigned char MapMenu_MarkOfSelection(MapMenu *self, unsigned int selection)
{
    if (selection >= MAP_MENU_SELECT_MARK && selection < MAP_MENU_SELECT_ROW) {
        return (unsigned char) (selection - MAP_MENU_SELECT_MARK);
    }
    if (selection >= MAP_MENU_SELECT_ROW && selection < MAP_MENU_SELECT_END) {
        u8 entry = MapMenu_ShownList(self)[selection - MAP_MENU_SELECT_ROW];
        if (entry == MAP_MENU_ENTRY_NONE) {
            return MAP_MENU_NO_MARK;
        }
        if (entry < MAP_MENU_ENTRY_VILLAGER) {
            return 8;
        }
        if (entry < MAP_MENU_ENTRY_PLACE) {
            return (unsigned char) (entry - MAP_MENU_ENTRY_VILLAGER);
        }
        if (entry < MAP_MENU_ENTRY_END) {
            return data_ov118_0229ca90[entry - MAP_MENU_ENTRY_PLACE];
        }
    }
    return MAP_MENU_NO_MARK;
}
CLEAN_AS(func_ov118_0229ae90, MapMenu_MarkOfSelection)

/* func_ov118_0229aef8: the row of a selection: for the players' house all the players' rows
 * (MAP_MENU_PLAYER_ROWS), for a villager's house (marks 0-7) the villager's row among the
 * residents (MAP_MENU_NO_ROW when not there), for a building (marks 9-13) its row among the
 * places (data_ov118_0229ca98); a row's own. */
unsigned char MapMenu_RowOfSelection(MapMenu *self, unsigned int selection)
{
    if (selection == MAP_MENU_SELECT_MARK + 8) {
        return MAP_MENU_PLAYER_ROWS;
    }
    if (selection >= MAP_MENU_SELECT_MARK && selection < MAP_MENU_SELECT_MARK + 8) {
        unsigned int entry = selection - MAP_MENU_SELECT_MARK + MAP_MENU_ENTRY_VILLAGER;
        for (int i = 0; i < self->resident_count; i++) {
            if (self->residents[i] == entry) {
                return (unsigned char) i;
            }
        }
        return MAP_MENU_NO_ROW;
    }
    if (selection < MAP_MENU_SELECT_ROW && selection >= MAP_MENU_SELECT_MARK + 9) {
        return data_ov118_0229ca98[selection - (MAP_MENU_SELECT_MARK + 9)];
    }
    if (selection < MAP_MENU_SELECT_END && selection >= MAP_MENU_SELECT_ROW) {
        return (unsigned char) (selection - MAP_MENU_SELECT_ROW);
    }
    return MAP_MENU_NO_ROW;
}
CLEAN_AS(func_ov118_0229aef8, MapMenu_RowOfSelection)

/* func_ov118_0229af64: row `row` of the list lit (its text columns in palette 3), the players'
 * rows for MAP_MENU_PLAYER_ROWS; MAP_MENU_NO_ROW puts every row back in palette 4. The shown
 * rows are made again. */
void MapMenu_HighlightRow(MapMenu *self, int row)
{
    MapMenu_SetFlags(self, MAP_MENU_FLAG_ROWS_DIRTY);
    if (row == MAP_MENU_NO_ROW) {
        ScreenMap_SetPalette(self->rows, MAP_MENU_ROW_LEFT, 0, MAP_MENU_ROW_RIGHT, 25, MAP_MENU_PALETTE_NORMAL);
    } else if (row == MAP_MENU_PLAYER_ROWS) {
        ScreenMap_SetPalette(self->rows, MAP_MENU_ROW_LEFT, 0, MAP_MENU_ROW_RIGHT, self->player_rows * 2 - 1,
                             MAP_MENU_PALETTE_LIT);
    } else {
        ScreenMap_SetPalette(self->rows, MAP_MENU_ROW_LEFT, row * 2, MAP_MENU_ROW_RIGHT, row * 2 + 1, MAP_MENU_PALETTE_LIT);
    }
}
CLEAN_AS(func_ov118_0229af64, MapMenu_HighlightRow)

/* func_ov118_0229afd4: `selection` (MAP_MENU_SELECT_*) becomes the selected mark and row, and
 * blinks; MAP_MENU_SELECT_NONE selects nothing. A mark of the other list's kind (a house while
 * the places are shown, a building while the residents are) switches the list and puts its row
 * in sight at once; else the row is scrolled into sight and lit alone. */
void MapMenu_Select(MapMenu *self, unsigned int selection)
{
    if (selection == MAP_MENU_SELECT_NONE) {
        self->mark = MAP_MENU_NO_MARK;
        self->row = MAP_MENU_NO_ROW;
        MapMenu_StopBlink(self);
        return;
    }
    MapMenu_StartBlink(self);
    self->row = MapMenu_RowOfSelection(self, selection);
    self->mark = MapMenu_MarkOfSelection(self, selection);
    if (selection >= MAP_MENU_SELECT_MARK && selection < MAP_MENU_SELECT_ROW) {
        int house = selection <= MAP_MENU_SELECT_MARK + 8;
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_FROM_LIST);
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES) != 0) {
            if (house) {
                MapMenu_ShowResidents(self);
                MapMenu_JumpToRow(self);
                return;
            }
        } else if (!house) {
            MapMenu_ShowPlaces(self);
            MapMenu_JumpToRow(self);
            return;
        }
    } else {
        MapMenu_SetFlags(self, MAP_MENU_FLAG_FROM_LIST);
    }
    MapMenu_ScrollToRow(self);
    MapMenu_HighlightRow(self, MAP_MENU_NO_ROW);
    MapMenu_HighlightRow(self, self->row);
}
CLEAN_AS(func_ov118_0229afd4, MapMenu_Select)

/* func_ov118_0229b088: the first mark within 7 pixels of (x, y) both ways, or
 * MAP_MENU_NO_MARK. */
int MapMenu_MarkAt(MapMenu *self, int x, int y)
{
    for (int i = 0; i < MAP_MENU_MARKS; i++) {
        const MapMenuMark *mark = &self->marks[i];
        if (mark->kind == MAP_MENU_MARK_NONE) {
            continue;
        }
        if (mark->x - 8 >= x || mark->x + 8 <= x) {
            continue;
        }
        if (mark->y - 8 >= y || mark->y + 8 <= y) {
            continue;
        }
        return i;
    }
    return MAP_MENU_NO_MARK;
}
CLEAN_AS(func_ov118_0229b088, MapMenu_MarkAt)

/* func_ov118_0229b120: the marks from overlay 117's spots, 8 pixels left of and 16 below them.
 * Spots 0-2 are the extra marks, by the spot's kind (0: kind 8, 1: 7, 2: 9, 3: 9 flipped, others
 * none); spots 3-10 are villagers' houses, 11 the players' house, 12-16 buildings
 * (data_ov118_0229caa0). A spot without a place has no mark. */
void MapMenu_FillMarks(MapMenu *self, TownMapMarker *spots)
{
    for (int i = 0; i < MAP_MENU_EXTRA_MARKS; i++) {
        MapMenuMark *mark = &self->extra_marks[i];
        const TownMapMarker *spot = TownMapMarkers_Get(spots, (unsigned int) i);
        if (spot == NULL) {
            mark->kind = MAP_MENU_MARK_NONE;
            continue;
        }
        switch (TownMapMarkers_Kind(spots, (unsigned int) i)) {
            case 0:
                mark->kind = 8;
                break;
            case 1:
                mark->kind = 7;
                break;
            case 2:
                mark->kind = 9;
                break;
            case 3:
                mark->kind = 9 | MAP_MENU_MARK_FLIP;
                break;
            default:
                mark->kind = MAP_MENU_MARK_NONE;
                break;
        }
        mark->x = (u8) (spot->x - 8);
        mark->y = (u8) (spot->y + 0x10);
    }
    for (int i = 0; i < MAP_MENU_MARKS; i++) {
        unsigned int index = (unsigned int) i + MAP_MENU_EXTRA_MARKS;
        MapMenuMark *mark = &self->marks[i];
        const TownMapMarker *spot = TownMapMarkers_Get(spots, index);
        if (spot == NULL) {
            mark->kind = MAP_MENU_MARK_NONE;
            continue;
        }
        if (index <= 10) {
            mark->kind = MAP_MENU_MARK_VILLAGER;
        } else if (index == 11) {
            mark->kind = MAP_MENU_MARK_PLAYERS;
        } else {
            mark->kind = data_ov118_0229caa0[index - 12];
        }
        mark->x = (u8) (spot->x - 8);
        mark->y = (u8) (spot->y + 0x10);
    }
}
CLEAN_AS(func_ov118_0229b120, MapMenu_FillMarks)

/* func_ov118_0229b27c: a mark of kind `kind` (MapMenuMarkKind without its flip) drawn on the sub
 * screen at (x, y), flipped across when `flip` is set, in `palette` (-1 for its own), priority
 * 1, from the overlay's OBJ (data_ov118_0229cb40), whose characters are changed for it.
 * QUIRK: after a flipped mark the OBJ's horizontal flip is cleared, whatever it was before. */
void MapMenu_DrawMark(MapMenu *self, int x, int y, int kind, int flip, int palette)
{
    OamEntry *obj = &data_ov118_0229cb40;
    u16 field = 0;

    (void) self;
    obj->attr2 = (u16) ((obj->attr2 & 0xfc00) | ((u16) (kind * 2 + 0xc0) & 0x3ff));
    if (flip) {
        /* bits 9-13 of attribute 1; its bit 3 (bit 12) is the horizontal flip */
        field = (u16) (((obj->attr1 >> 9) & 0x1f) | 8);
        obj->attr1 = (u16) ((obj->attr1 & 0xc1ff) | ((field & 0x1f) << 9));
    }
    OamBuffer_DrawObjAffine(1, obj, x, y, palette, 1, NULL);
    if (flip) {
        obj->attr1 = (u16) ((obj->attr1 & 0xc1ff) | ((field & 0x17) << 9));
    }
}
CLEAN_AS(func_ov118_0229b27c, MapMenu_DrawMark)

/* func_ov118_0229b374: how far the shown list scrolls: 16 pixels for each row past six. */
unsigned int MapMenu_MaxScroll(MapMenu *self)
{
    unsigned int count = MapMenu_ShownCount(self);
    if (count <= MAP_MENU_VISIBLE_ROWS) {
        return 0;
    }
    return (count - MAP_MENU_VISIBLE_ROWS) << 4;
}
CLEAN_AS(func_ov118_0229b374, MapMenu_MaxScroll)

/* func_ov118_0229b390: the rows of the shown list. */
unsigned char MapMenu_ShownCount(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES)) {
        return self->place_count;
    }
    return self->resident_count;
}
CLEAN_AS(func_ov118_0229b390, MapMenu_ShownCount)

/* func_ov118_0229b3b0: the entries of the shown list. */
u8 *MapMenu_ShownList(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES)) {
        return self->places;
    }
    return self->residents;
}
CLEAN_AS(func_ov118_0229b3b0, MapMenu_ShownList)

/* func_ov118_0229b3d8: the shown list's rows and texts made; the scroll bar in use (its column
 * of the map's screen lit, the knob shown) when the list is longer than six rows; the map's
 * screen to be loaded; the selected row lit. */
void MapMenu_ShowList(MapMenu *self)
{
    u32 palette;

    MapMenu_BuildRows(self);
    MapMenu_FillShownLabels(self);
    if (MapMenu_MaxScroll(self) == 0) {
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_SCROLLS);
        palette = MAP_MENU_PALETTE_NORMAL;
    } else {
        MapMenu_SetFlags(self, MAP_MENU_FLAG_SCROLLS);
        palette = MAP_MENU_PALETTE_LIT;
    }
    ScreenMap_SetPalette(self->map_screen, 0x1d, 0x0a, 0x1d, 0x15, palette);
    MapMenu_SetFlags(self, MAP_MENU_FLAG_MAP_UPLOAD);
    MapMenu_HighlightRow(self, self->row);
}
CLEAN_AS(func_ov118_0229b3d8, MapMenu_ShowList)

/* func_ov118_0229b43c */
void MapMenu_ShowPlaces(MapMenu *self)
{
    MapMenu_SetFlags(self, MAP_MENU_FLAG_PLACES);
    MapMenu_ShowList(self);
}
CLEAN_AS(func_ov118_0229b43c, MapMenu_ShowPlaces)

/* func_ov118_0229b454 */
void MapMenu_ShowResidents(MapMenu *self)
{
    MapMenu_ClearFlags(self, MAP_MENU_FLAG_PLACES);
    MapMenu_ShowList(self);
}
CLEAN_AS(func_ov118_0229b454, MapMenu_ShowResidents)

/* func_ov118_0229b46c: a row's text: the current player's name, a player's or a villager's
 * name, a place's menu message; empty for none and anything else. */
void MapMenu_SetRowText(MapMenu *self, TextLabel *label, unsigned int entry)
{
    PagedChoiceRow *row = (PagedChoiceRow *) (void *) label;

    (void) self;
    if (entry == MAP_MENU_ENTRY_NONE) {
        TextBase_Clear(label);
    } else if (entry == MAP_MENU_ENTRY_SELF) {
        ChoiceRow_SetName(row, PlayerRecord_Player(PlayerRecords_Current()));
    } else if (entry >= MAP_MENU_ENTRY_PLAYER && entry < MAP_MENU_ENTRY_VILLAGER) {
        ChoiceRow_SetPlayerName(row, (int) (entry - MAP_MENU_ENTRY_PLAYER));
    } else if (entry >= MAP_MENU_ENTRY_VILLAGER && entry < MAP_MENU_ENTRY_PLACE) {
        ChoiceRow_SetListBName(row, (int) (entry - MAP_MENU_ENTRY_VILLAGER));
    } else if (entry >= MAP_MENU_ENTRY_PLACE && entry < MAP_MENU_ENTRY_END) {
        TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) (entry + MAP_MENU_PLACE_MESSAGE));
    } else {
        TextBase_Clear(label);
    }
}
CLEAN_AS(func_ov118_0229b46c, MapMenu_SetRowText)

/* func_ov118_0229b4d8: the 13 rows' texts from `entries`, each in a box of the next label
 * (16 tiles a row from tile 0x160). */
void MapMenu_FillLabels(MapMenu *self, unsigned char *entries)
{
    for (int i = 0; i < MAP_MENU_ROWS; i++) {
        TextLabel *label = MapMenu_NextLabel(self);
        TextLabel_OpenStyledBox2(label, MAP_MENU_LABEL_STYLE, MAP_MENU_LABEL_FIRST_TILE + i * 16, 8, 1, 0xf, 0);
        MapMenu_SetRowText(self, label, entries[i]);
        TextLabel_Show(label, 0, 0);
    }
}
CLEAN_AS(func_ov118_0229b4d8, MapMenu_FillLabels)

/* func_ov118_0229b530 */
void MapMenu_FillShownLabels(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES)) {
        MapMenu_FillLabels(self, self->places);
    } else {
        MapMenu_FillLabels(self, self->residents);
    }
}
CLEAN_AS(func_ov118_0229b530, MapMenu_FillShownLabels)

/* func_ov118_0229b564: the residents: the current player first (when found in the town), the
 * town's other players, then its villagers; the places: the five places, the rest empty.
 * BUG: the rows of the residents past the last are left as they were: the loop meant to empty
 * them empties the places' (which are then written anyway). */
void MapMenu_BuildLists(MapMenu *self)
{
    int count = 0;
    int self_index =
        PlayerRecords_FindIndex(data_021dc7bc, (const PlayerRecordsId *) PlayerRecord_Player(PlayerRecords_Current()));
    if (self_index != -1) {
        self->residents[count++] = MAP_MENU_ENTRY_SELF;
    }
    for (int i = 0; i < 4; i++) {
        if (i != self_index && PlayerRecords_TownExists(data_021dc7bc, i) != 0) {
            self->residents[count++] = (u8) (MAP_MENU_ENTRY_PLAYER + i);
        }
    }
    self->player_rows = (u8) count;
    for (int i = 0; i < 8; i++) {
        if (VillagerRoster_IsFilled(&data_021e5a2c, i) != 0) {
            self->residents[count++] = (u8) (MAP_MENU_ENTRY_VILLAGER + i);
        }
    }
    self->resident_count = (u8) count;
    for (; count < MAP_MENU_ROWS; count++) {
#ifdef BUGFIX
        self->residents[count] = MAP_MENU_ENTRY_NONE;
#else
        self->places[count] = MAP_MENU_ENTRY_NONE;
#endif
    }

    int places = 0;
    for (int i = 0; i < MAP_MENU_PLACES; i++) {
        self->places[places++] = (u8) (MAP_MENU_ENTRY_PLACE + i);
    }
    self->place_count = (u8) places;
    for (; places < MAP_MENU_ROWS; places++) {
        self->places[places] = MAP_MENU_ENTRY_NONE;
    }
}
CLEAN_AS(func_ov118_0229b564, MapMenu_BuildLists)

/* func_ov118_0229b630: the next of the 13 labels; once all are in use, the last again. */
TextLabel *MapMenu_NextLabel(MapMenu *self)
{
    if (self->labels_used >= MAP_MENU_ROWS) {
        return &self->labels[MAP_MENU_ROWS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov118_0229b630, MapMenu_NextLabel)

/* func_ov118_0229b664: no label in use, every label's box closed. */
void MapMenu_ResetLabels(MapMenu *self)
{
    self->labels_used = 0;
    for (int i = 0; i < MAP_MENU_ROWS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov118_0229b664, MapMenu_ResetLabels)

/* func_ov118_0229b68c: the icon of a row's entry (the pair of tile rows of the template it is
 * taken from): players 0, villagers 1, places 3, 5, 2, 4, 6; none and others 7. */
unsigned int MapMenu_RowIcon(MapMenu *self, unsigned int entry, int row)
{
    static const u8 place_icons[MAP_MENU_PLACES] = {3, 5, 2, 4, 6};

    (void) self;
    (void) row;
    if (entry == MAP_MENU_ENTRY_NONE) {
        return 7;
    }
    if (entry < MAP_MENU_ENTRY_VILLAGER) {
        return 0;
    }
    if (entry < MAP_MENU_ENTRY_PLACE) {
        return 1;
    }
    if (entry < MAP_MENU_ENTRY_END) {
        return place_icons[entry - MAP_MENU_ENTRY_PLACE];
    }
    return 7;
}
CLEAN_AS(func_ov118_0229b68c, MapMenu_RowIcon)

/* func_ov118_0229b6e0: the rows made from the template, each row's 2 x 2 icon tiles taken from
 * the template's rows of its entry's icon; the rows to be loaded. */
void MapMenu_BuildRows(MapMenu *self)
{
    MIi_CpuCopy16(self->rows_template, self->rows, MAP_MENU_SCREEN_BYTES);
    const u8 *entries = MapMenu_ShownList(self);
    for (int i = 0; i < MAP_MENU_ROWS; i++) {
        int from = (int) (MapMenu_RowIcon(self, entries[i], i) << 6) + MAP_MENU_ROW_LEFT;
        int to = (i << 6) + MAP_MENU_ROW_LEFT;
        self->rows[to] = self->rows_template[from];
        self->rows[to + 1] = self->rows_template[from + 1];
        self->rows[to + 0x20] = self->rows_template[from + 0x20];
        self->rows[to + 0x21] = self->rows_template[from + 0x21];
    }
    MapMenu_SetFlags(self, MAP_MENU_FLAG_ROWS_UPLOAD);
}
CLEAN_AS(func_ov118_0229b6e0, MapMenu_BuildRows)

/* The ten tiles of a row from its icon on, in both its tile rows, blank. */
static void map_menu_blank_row(MapMenu *self, int row)
{
    int first = row * MAP_MENU_ROW_TILES + MAP_MENU_ROW_LEFT;
    MIi_CpuClear16(MAP_MENU_BLANK_TILE, &self->shown_rows[first], 0x14);
    MIi_CpuClear16(MAP_MENU_BLANK_TILE, &self->shown_rows[first + 0x20], 0x14);
}

/* func_ov118_0229b778: the shown rows: the rows with those above the scroll and those from the
 * seventh below it on blank; the first row shown is noted; the rows to be loaded.
 * REQUIRES: the scroll is below 14 rows (the game keeps it at 7 rows at most). */
void MapMenu_BuildShownRows(MapMenu *self)
{
    MIi_CpuCopy16(self->rows, self->shown_rows, MAP_MENU_SCREEN_BYTES);
    int top = self->scroll >> 4;
    self->shown_top = (u8) top;
    for (int row = 0; row < top; row++) {
        map_menu_blank_row(self, row);
    }
    for (int row = top + MAP_MENU_VISIBLE_ROWS + 1; row < MAP_MENU_ROWS; row++) {
        map_menu_blank_row(self, row);
    }
    MapMenu_SetFlags(self, MAP_MENU_FLAG_ROWS_UPLOAD);
}
CLEAN_AS(func_ov118_0229b778, MapMenu_BuildShownRows)
