/* The music list of overlay 144 (music_list.h): its flags, the list's scroll and the rows it
 * builds, colours and labels, the songs it gathers, the three buttons' faces and the scroll
 * bar's knob. */
#include "music_list.h"

#include <stddef.h>
#include <stdint.h>

#include "clean.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/house_record.h"
#include "main/name_texts.h"
#include "main/screen_map.h"
#include "main/text_base.h"
#include "autoload_2/approach.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(MusicList, wipe_y) == 0x94, "wipe");
static_assert(offsetof(MusicList, scroll) == 0x9c && offsetof(MusicList, flags) == 0xb4, "scroll");
static_assert(offsetof(MusicList, playing) == 0xbc && offsetof(MusicList, cursor) == 0xc1, "rows");
static_assert(offsetof(MusicList, pointer) == 0xc4 && offsetof(MusicList, knob_button) == 0x128, "pointer");
static_assert(offsetof(MusicList, panel) == 0x170 && offsetof(MusicList, labels) == 0x33c, "panel");
static_assert(offsetof(MusicList, list_task) == 0x708 && offsetof(MusicList, error) == 0x750, "tasks");
static_assert(offsetof(MusicList, songs) == 0x86c && offsetof(MusicList, shown) == 0x8f8, "songs");
static_assert(offsetof(MusicList, row_screens) == 0x90a && offsetof(MusicList, buttons_screen) == 0x190a, "screens");
static_assert(sizeof(MusicList) == 0x210c, "size (func_ov144_0229b290)");

/* The SDK's fill and copy (the value or the source first). */
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

/* A row's screen: two lines of 32 entries. */
#define MUSIC_LIST_ROW_ENTRIES 0x40
#define MUSIC_LIST_SCREEN_ROWS 16

/* The entry the list's screen is cleared to. */
#define MUSIC_LIST_BLANK_ENTRY 0x10

/* The palettes of the rows (on the list's screen) and of the buttons (on the buttons' screen). */
#define MUSIC_LIST_PALETTE_ROWS 4
#define MUSIC_LIST_PALETTE_SELECTED 5
#define MUSIC_LIST_PALETTE_PLAYING 9
#define MUSIC_LIST_PALETTE_PLAYING_SELECTED 10
#define MUSIC_LIST_PALETTE_BUTTON 6
#define MUSIC_LIST_PALETTE_BUTTON_OFF 7
#define MUSIC_LIST_PALETTE_BUTTON_ON 8

/* The play button's faces: the first of its 16 characters. */
#define MUSIC_LIST_FACE_PLAY 0x59
#define MUSIC_LIST_FACE_STOP 0x69

/* The scroll's step per frame, and the knob's step per frame with the d-pad. */
#define MUSIC_LIST_SCROLL_STEP 6
#define MUSIC_LIST_KNOB_KEY_STEP 4

/* The pad (autoload_2/input.h): up and down move the knob while held. */
typedef struct MusicListPad {
    u16 held;
    u16 pressed;
} MusicListPad;
extern MusicListPad data_021fbe40;
#define MUSIC_LIST_PAD_UP 0x0040
#define MUSIC_LIST_PAD_DOWN 0x0080

static DualCellSprite *music_list_knob_cells(MusicList *self)
{
    /* The knob's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->knob_button;
}

/* func_ov144_02299660 */
void MusicList_ClearFlags(MusicList *self, u16 flags)
{
    self->flags &= (u16) ~flags;
}
CLEAN_AS(func_ov144_02299660, MusicList_ClearFlags)

/* func_ov144_02299670 */
void MusicList_SetFlags(MusicList *self, u16 flags)
{
    self->flags |= flags;
}
CLEAN_AS(func_ov144_02299670, MusicList_SetFlags)

/* func_ov144_02299680: 1 when any of `flags` is set. */
int MusicList_TestFlags(MusicList *self, u16 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov144_02299680, MusicList_TestFlags)

/* func_ov144_02299694: the list scrolled at once to show `row` fourth from the top, as far as
 * the list goes, and the knob put by the scroll. */
void MusicList_ScrollToRow(MusicList *self, int row)
{
    int top = row - 3;
    int last_top = self->count - MUSIC_LIST_ROWS_SHOWN;
    if (last_top < 0) {
        last_top = 0;
    }
    if (top < 0) {
        top = 0;
    } else if (top > last_top) {
        top = last_top;
    }
    MusicList_ScrollTo(self, top * MUSIC_LIST_ROW_HEIGHT);
    self->scroll_target = self->scroll;
    MusicList_KnobFromScroll(self);
}
CLEAN_AS(func_ov144_02299694, MusicList_ScrollToRow)

/* func_ov144_02299b48: `row` chosen (MUSIC_LIST_NO_ROW for none): the rows coloured again and
 * the buttons' faces refreshed. Whether the choice changed. */
int MusicList_Select(MusicList *self, int row)
{
    int changed = self->selected != row;
    self->selected = (s16) row;
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_LIST_DIRTY);
    MusicList_RefreshButtons(self);
    return changed;
}
CLEAN_AS(func_ov144_02299b48, MusicList_Select)

/* func_ov144_02299b7c: the buttons' faces by the rows: the take out button dimmed with no row
 * chosen; with no song playing the play button shows "play", dimmed with no row chosen; while
 * one plays it shows "stop" in its lit palette. */
void MusicList_RefreshButtons(MusicList *self)
{
    int none_chosen = self->selected == MUSIC_LIST_NO_ROW;
    MusicList_SetTakePalette(self, none_chosen ? MUSIC_LIST_PALETTE_BUTTON_OFF : MUSIC_LIST_PALETTE_BUTTON);
    if (self->playing == MUSIC_LIST_NO_ROW) {
        MusicList_SetPlayFace(self, MUSIC_LIST_FACE_PLAY);
        MusicList_SetPlayPalette(self, none_chosen ? MUSIC_LIST_PALETTE_BUTTON_OFF : MUSIC_LIST_PALETTE_BUTTON);
    } else {
        MusicList_SetPlayFace(self, MUSIC_LIST_FACE_STOP);
        MusicList_SetPlayPalette(self, MUSIC_LIST_PALETTE_BUTTON_ON);
    }
}
CLEAN_AS(func_ov144_02299b7c, MusicList_RefreshButtons)

/* func_ov144_02299bfc: the store button's palette (columns 2-5, lines 12-13). */
void MusicList_SetStorePalette(MusicList *self, int palette)
{
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_BUTTONS_DIRTY);
    ScreenMap_SetPalette(self->buttons_screen, 2, 12, 5, 13, (u32) palette);
}
CLEAN_AS(func_ov144_02299bfc, MusicList_SetStorePalette)

/* func_ov144_02299c2c: the take out button's palette (columns 2-5, lines 15-16). */
void MusicList_SetTakePalette(MusicList *self, int palette)
{
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_BUTTONS_DIRTY);
    ScreenMap_SetPalette(self->buttons_screen, 2, 15, 5, 16, (u32) palette);
}
CLEAN_AS(func_ov144_02299c2c, MusicList_SetTakePalette)

/* func_ov144_02299c5c: the play button's palette (columns 2-5, lines 4-7). */
void MusicList_SetPlayPalette(MusicList *self, int palette)
{
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_BUTTONS_DIRTY);
    ScreenMap_SetPalette(self->buttons_screen, 2, 4, 5, 7, (u32) palette);
}
CLEAN_AS(func_ov144_02299c5c, MusicList_SetPlayPalette)

/* func_ov144_02299c8c: the play button's face: 16 characters from `first_char` written over its
 * entries (columns 2-5, lines 4-7), a line at a time; the entries' palette bits are replaced too
 * (MusicList_RefreshButtons sets the palette after it). */
void MusicList_SetPlayFace(MusicList *self, u16 first_char)
{
    u16 value = first_char;
    for (int line = 4; line <= 7; line++) {
        for (int column = 2; column <= 5; column++) {
            self->buttons_screen[line * 32 + column] = value;
            value++;
        }
    }
}
CLEAN_AS(func_ov144_02299c8c, MusicList_SetPlayFace)

/* func_ov144_02299cc4: the scroll moved 6 pixels toward its target (not past it), then the list
 * scrolled there and the knob put by it. */
void MusicList_StepScroll(MusicList *self)
{
    if (self->scroll == self->scroll_target) {
        return;
    }
    if (self->scroll > self->scroll_target) {
        self->scroll -= MUSIC_LIST_SCROLL_STEP;
        if (self->scroll < self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    } else {
        self->scroll += MUSIC_LIST_SCROLL_STEP;
        if (self->scroll > self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    }
    MusicList_ScrollTo(self, self->scroll);
    MusicList_KnobFromScroll(self);
}
CLEAN_AS(func_ov144_02299cc4, MusicList_StepScroll)

/* func_ov144_02299d3c: the rows coloured: all in palette 4, then the playing row 9 and the chosen
 * one 5 (10 when they are the same); the list's screen queued for the sub screen's BG1, which
 * clears MUSIC_LIST_FLAG_LIST_DIRTY once the task took it. */
void MusicList_ColorRows(MusicList *self)
{
    ScreenMap_SetPalette(self->list_screen, 0, 0, 0x1f, 0x1f, MUSIC_LIST_PALETTE_ROWS);
    if (self->playing == self->selected) {
        MusicList_ColorRow(self, self->playing, MUSIC_LIST_PALETTE_PLAYING_SELECTED);
    } else {
        MusicList_ColorRow(self, self->playing, MUSIC_LIST_PALETTE_PLAYING);
        MusicList_ColorRow(self, self->selected, MUSIC_LIST_PALETTE_SELECTED);
    }
    if (LayerTask_QueueScreen(&self->list_task, (int) (uintptr_t) self->list_screen, LAYER_SUB_BG1, sizeof(self->list_screen),
                              0) != 0) {
        MusicList_ClearFlags(self, MUSIC_LIST_FLAG_LIST_DIRTY);
    }
}
CLEAN_AS(func_ov144_02299d3c, MusicList_ColorRows)

/* func_ov144_02299db4: a row's two lines of the list's screen in `palette`, when the row is one
 * of the nine built (none for MUSIC_LIST_NO_ROW). */
void MusicList_ColorRow(MusicList *self, int row, int palette)
{
    if (row == MUSIC_LIST_NO_ROW) {
        return;
    }
    int from_top = row - self->first_row;
    if (from_top < 0 || from_top >= MUSIC_LIST_ROWS) {
        return;
    }
    int line = (row & (MUSIC_LIST_SCREEN_ROWS - 1)) * 2;
    ScreenMap_SetPalette(self->list_screen, 0, line, 0x1f, line + 1, (u32) palette);
}
CLEAN_AS(func_ov144_02299db4, MusicList_ColorRow)

/* func_ov144_02299df4: the list's screen built for the rows from `first_row`: cleared to entry
 * 0x10, then nine rows copied from the row screens (row r of the list from row screen r % 9) to
 * the screen's rows (r % 16, the screen wrapping as it scrolls); MUSIC_LIST_FLAG_LIST_DIRTY. */
void MusicList_BuildRows(MusicList *self)
{
    int source = (self->first_row + MUSIC_LIST_ROWS) % MUSIC_LIST_ROWS;
    int target = self->first_row & (MUSIC_LIST_SCREEN_ROWS - 1);

    MIi_CpuClear16(MUSIC_LIST_BLANK_ENTRY, self->list_screen, sizeof(self->list_screen));
    for (int i = 0; i < MUSIC_LIST_ROWS; i++) {
        MIi_CpuCopy16(&self->row_screens[source * MUSIC_LIST_ROW_ENTRIES], &self->list_screen[target * MUSIC_LIST_ROW_ENTRIES],
                      MUSIC_LIST_ROW_ENTRIES * sizeof(u16));
        source++;
        if (source >= MUSIC_LIST_ROWS) {
            source = 0;
        }
        target = (target + 1) & (MUSIC_LIST_SCREEN_ROWS - 1);
    }
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_LIST_DIRTY);
}
CLEAN_AS(func_ov144_02299df4, MusicList_BuildRows)

/* func_ov144_02299e6c: the list scrolled to `scroll` pixels: the sub screen's BG1 scrolled (0x18
 * less), the top row kept, the rows built again and labelled at the frame's end. */
void MusicList_ScrollTo(MusicList *self, int scroll)
{
    self->scroll = scroll;
    DisplayLayer_SetScroll(LAYER_SUB_BG1, 0, self->scroll - 0x18);
    self->first_row = (s16) (scroll >> 4);
    MusicList_BuildRows(self);
    MusicList_SetFlags(self, MUSIC_LIST_FLAG_LABELS_DIRTY);
}
CLEAN_AS(func_ov144_02299e6c, MusicList_ScrollTo)

/* func_ov144_02299ea8: the scroll's end by the count (16 pixels a row past the eighth, at least
 * 0), then the playing row shown. */
void MusicList_SetupScroll(MusicList *self)
{
    self->scroll_max = (self->count - MUSIC_LIST_ROWS_SHOWN) * MUSIC_LIST_ROW_HEIGHT;
    if (self->scroll_max < 0) {
        self->scroll_max = 0;
    }
    MusicList_ScrollToRow(self, self->playing);
}
CLEAN_AS(func_ov144_02299ea8, MusicList_SetupScroll)

/* func_ov144_02299ed4: at the frame's end, what changed sent on: the rows coloured and queued,
 * the buttons' screen queued for the sub screen's BG3 (the flag kept until the task takes it),
 * the rows labelled. */
void MusicList_FlushScreens(MusicList *self)
{
    if (MusicList_TestFlags(self, MUSIC_LIST_FLAG_LIST_DIRTY)) {
        MusicList_ColorRows(self);
    }
    if (MusicList_TestFlags(self, MUSIC_LIST_FLAG_BUTTONS_DIRTY)) {
        if (LayerTask_QueueScreen(&self->buttons_task, (int) (uintptr_t) self->buttons_screen, LAYER_SUB_BG3,
                                  sizeof(self->buttons_screen), 0) != 0) {
            MusicList_ClearFlags(self, MUSIC_LIST_FLAG_BUTTONS_DIRTY);
        }
    }
    if (MusicList_TestFlags(self, MUSIC_LIST_FLAG_LABELS_DIRTY)) {
        MusicList_ClearFlags(self, MUSIC_LIST_FLAG_LABELS_DIRTY);
        MusicList_LabelRows(self);
    }
}
CLEAN_AS(func_ov144_02299ed4, MusicList_FlushScreens)

/* func_ov144_02299f44: the nine rows from the top labelled with their songs' names, each in the
 * label of its screen row % 9 (style 4, 0x184 + 0x1a per label and 0xd, colours 0xf and 7): a
 * row past the list gets no song and an empty label; a row whose song the label already shows
 * is left as it is. */
void MusicList_LabelRows(MusicList *self)
{
    NameText name;
    NameText_Construct(&name);

    int row = self->first_row;
    const u16 *song = row < 0 ? self->songs : &self->songs[row];
    int slot = (row + MUSIC_LIST_ROWS) % MUSIC_LIST_ROWS;
    int count = self->count;

    for (int i = 0; i < MUSIC_LIST_ROWS; i++) {
        TextLabel *label = NULL;
        if (row < 0 || row >= count) {
            self->shown[slot] = MUSIC_LIST_NO_ITEM;
            label = MusicList_NextLabel(self);
            TextBase_Clear(label);
        } else {
            if (*song != self->shown[slot]) {
                self->shown[slot] = *song;
                label = MusicList_NextLabel(self);
                u16 item = *song;
                NameText_SetItem(&name, &item);
                TextBase_Copy((TextBase *) (void *) label, (TextBase *) (void *) &name);
            }
            song++;
        }
        if (label != NULL) {
            TextLabel_OpenStyledBox2(label, 4, slot * 0x1a + 0x184, 0xd, 0xf, 7, 0);
            TextLabel_Show(label, 0, 0);
        }
        row++;
        slot++;
        if (slot >= MUSIC_LIST_ROWS) {
            slot = 0;
        }
    }
    NameText_Destruct(&name);
}
CLEAN_AS(func_ov144_02299f44, MusicList_LabelRows)

/* func_ov144_0229a040: no label used this frame, the nine labels' boxes closed. */
void MusicList_CloseLabels(MusicList *self)
{
    self->labels_used = 0;
    for (int i = 0; i < MUSIC_LIST_ROWS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov144_0229a040, MusicList_CloseLabels)

/* func_ov144_0229a06c: the next of the nine labels this frame; once all are used, the last
 * again. */
TextLabel *MusicList_NextLabel(MusicList *self)
{
    if (self->labels_used >= MUSIC_LIST_ROWS) {
        return &self->labels[MUSIC_LIST_ROWS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov144_0229a06c, MusicList_NextLabel)

/* func_ov144_0229a29c: the row of the song the room plays (HouseRecord_CurrentSong, read twice)
 * among the songs held, MUSIC_LIST_NO_ROW when none plays or the collection does not hold it;
 * that row is chosen too. */
void MusicList_FindPlaying(MusicList *self)
{
    self->playing = MUSIC_LIST_NO_ROW;
    if (*HouseRecord_CurrentSong() != MUSIC_LIST_NO_ITEM) {
        u16 current = *HouseRecord_CurrentSong();
        int index = -1;
        if (current >= MUSIC_LIST_FIRST_SONG && current < MUSIC_LIST_FIRST_SONG + MUSIC_LIST_SONGS) {
            index = current - MUSIC_LIST_FIRST_SONG;
        }
        u16 song = MUSIC_LIST_FIRST_SONG;
        int row = 0;
        for (int k = 0; k < MUSIC_LIST_SONGS; k++) {
            if (HouseRecord_HasSong(song)) {
                if (k == index) {
                    self->playing = (s16) row;
                    k = MUSIC_LIST_SONGS;
                }
                row++;
            }
            song++;
        }
    }
    self->selected = self->playing;
}
CLEAN_AS(func_ov144_0229a29c, MusicList_FindPlaying)

/* func_ov144_0229a328: the songs the house holds, in item order, and their count. */
void MusicList_GatherSongs(MusicList *self)
{
    u16 song = MUSIC_LIST_FIRST_SONG;
    self->count = 0;
    for (int i = 0; i < MUSIC_LIST_SONGS; i++) {
        if (HouseRecord_HasSong(song)) {
            self->songs[self->count] = song;
            self->count++;
        }
        song++;
    }
}
CLEAN_AS(func_ov144_0229a328, MusicList_GatherSongs)

/* func_ov144_0229a378: when the list scrolls, the knob put at the scroll's share of its 0x78
 * pixels. */
void MusicList_KnobFromScroll(MusicList *self)
{
    if (self->scroll_max > 0) {
        self->knob = MUSIC_LIST_KNOB_MAX * self->scroll / self->scroll_max;
        MusicList_PlaceKnob(self);
    }
}
CLEAN_AS(func_ov144_0229a378, MusicList_KnobFromScroll)

/* func_ov144_0229a3a4: the list scrolled at once to the knob's share of the scroll (within it). */
void MusicList_ScrollFromKnob(MusicList *self)
{
    int max = self->scroll_max;
    int scroll = self->knob * max / MUSIC_LIST_KNOB_MAX;
    if (scroll < 0) {
        scroll = 0;
    }
    if (scroll > max) {
        scroll = max;
    }
    MusicList_ScrollTo(self, scroll);
    self->scroll_target = scroll;
}
CLEAN_AS(func_ov144_0229a3a4, MusicList_ScrollFromKnob)

/* func_ov144_0229a3dc: the knob's sprite at x 0x4f, at the knob less 0x4b below the wipe's y. */
void MusicList_PlaceKnob(MusicList *self)
{
    DualCellSprite_SetOffset(music_list_knob_cells(self), 0x4f, self->wipe_y + (self->knob - 0x4b));
}
CLEAN_AS(func_ov144_0229a3dc, MusicList_PlaceKnob)

/* func_ov144_0229a404: once the knob's release has played, the knob at rest; whether it had. */
int MusicList_KnobSettled(MusicList *self)
{
    if (DualCellSprite_IsDone(music_list_knob_cells(self))) {
        PushButton_ShowUp(&self->knob_button);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov144_0229a404, MusicList_KnobSettled)

/* func_ov144_0229a42c: up or down held move the knob 4 pixels (up first, within 0-0x78); when it
 * moved, the list scrolled by it, the knob put there and its scroll sound cued. */
void MusicList_KnobByKeys(MusicList *self)
{
    int before = self->knob;
    u16 held = data_021fbe40.held;

    if (held & MUSIC_LIST_PAD_UP) {
        self->knob -= MUSIC_LIST_KNOB_KEY_STEP;
        if (self->knob < 0) {
            self->knob = 0;
        }
    } else if (held & MUSIC_LIST_PAD_DOWN) {
        self->knob += MUSIC_LIST_KNOB_KEY_STEP;
        if (self->knob > MUSIC_LIST_KNOB_MAX) {
            self->knob = MUSIC_LIST_KNOB_MAX;
        }
    }
    if (before != self->knob) {
        MusicList_ScrollFromKnob(self);
        MusicList_PlaceKnob(self);
        PushButton_ScrollCue(&self->knob_button);
    }
}
CLEAN_AS(func_ov144_0229a42c, MusicList_KnobByKeys)

/* func_ov144_0229a4b8: the knob let go (PushButton_Release's answer). */
int MusicList_ReleaseKnob(MusicList *self)
{
    return PushButton_Release(&self->knob_button);
}
CLEAN_AS(func_ov144_0229a4b8, MusicList_ReleaseKnob)

/* func_ov144_0229a4c8: the knob follows the touch's y: with `jump` (a touch on the bar) toward
 * y - 0x1d by at most 8 pixels a frame, else to y plus the offset it was grabbed at, within
 * 0-0x78. The list scrolled by it and the knob put there; its scroll sound cued each time it has
 * moved 4 pixels or more since the last. */
void MusicList_MoveKnob(MusicList *self, int y, int jump)
{
    int knob;
    if (jump) {
        knob = y - 0x1d;
    } else {
        knob = y + self->grab_offset;
    }
    if (knob < 0) {
        knob = 0;
    }
    if (knob > MUSIC_LIST_KNOB_MAX) {
        knob = MUSIC_LIST_KNOB_MAX;
    }
    if (jump) {
        Approach_S32Again((int *) (void *) &self->knob, knob, 8);
    } else {
        self->knob = knob;
    }
    MusicList_ScrollFromKnob(self);
    MusicList_PlaceKnob(self);

    int moved = self->knob_cued - self->knob;
    if (moved >= 4 || moved <= -4) {
        PushButton_ScrollCue(&self->knob_button);
        self->knob_cued = self->knob;
    }
}
CLEAN_AS(func_ov144_0229a4c8, MusicList_MoveKnob)

/* func_ov144_0229a540: a touch at (x, y) on the knob grabs it (pressed, the offset to the touch
 * kept); whether it did. */
int MusicList_GrabKnob(MusicList *self, int x, int y)
{
    if (PushButton_Contains(&self->knob_button, x, y)) {
        self->grab_offset = self->knob - y;
        PushButton_Press(&self->knob_button);
        self->knob_cued = self->knob;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov144_0229a540, MusicList_GrabKnob)
