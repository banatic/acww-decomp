/* The list of hosting friends of overlay 146's scene (wfc_host_list.h): the friends' statuses
 * read from the Wi-Fi Connection's friend list, the list and its rows' labels and shades, the
 * scroll and the scroll bar's knob. */
#include "wfc_host_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/message_reader.h"
#include "main/text_base.h"
#include "main/text_label.h"
#include "main/town_name.h"

/* The SDK's fills and copies (the source first). */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

/* The two texts the rows' town names pass through: function-local statics of
 * WfcHostList_RefreshRowLabels, constructed on its first call and registered with the C++
 * runtime for their destruction (the destructors handed to it are the game's symbols). */
extern TownNameWideText data_ov146_0229b7a8;
extern u32 data_ov146_0229b78c;  /* bit 0: data_ov146_0229b7a8 is constructed */
extern u8 data_ov146_0229b79c[]; /* its record for the C++ runtime */
extern TownNameText data_ov146_0229b7e4;
extern u32 data_ov146_0229b780;  /* bit 0: data_ov146_0229b7e4 is constructed */
extern u8 data_ov146_0229b790[]; /* its record */
extern void *func_02064158(void *text);
extern void *func_020641b0(void *text);
extern void __register_global_object(void *object, void *destruct, void *record);

/* The menu message of a row's town ("menu" messages, its part 0 the town's name), and the
 * labels' place in the rows: the town's at tile 0x11e + 0x14 * slot (10 cells), the name's at
 * 0x1d2 + 16 * slot (8 cells), in colour 14 - slot. */
#define WFC_HOST_LIST_TOWN_MESSAGE 0x66
#define WFC_HOST_LIST_NAME_LENGTH 6
#define WFC_HOST_LIST_TOWN_OFFSET 0x10 /* in a friend's status data */

/* The full-width digit 0 (U+FF10). */
#define WFC_HOST_LIST_WIDE_ZERO 0xff10

/* The rows' layer and the place of the 7 row slots in the base screen (two lines of 32 tiles
 * each, from line 7). */
#define WFC_HOST_LIST_ROWS_LAYER LAYER_SUB_BG1
#define WFC_HOST_LIST_SLOT_FIRST_LINE 7
#define WFC_HOST_LIST_SCREEN_LINE 0x20 /* tiles */
#define WFC_HOST_LIST_ROW_TILES (2 * WFC_HOST_LIST_SCREEN_LINE)

/* The colours the rows' shades lead to: 14 for a game with room, 7 for a full one; colour 15 is
 * where they start. */
#define WFC_HOST_LIST_COLOR_OPEN 14
#define WFC_HOST_LIST_COLOR_FULL 7
#define WFC_HOST_LIST_COLOR_BACK 15
#define WFC_HOST_LIST_SHADE_FULL 0x40 /* in `row_shade`: shaded toward the full colour */

static DualCellSprite *wfc_host_list_knob_cells(WfcHostList *self)
{
    /* The knob's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->knob_button;
}

/* Friend `index`'s status in the live list, by address.
 * REQUIRES: the connection is logged in (the list is not NULL); the game reads low memory
 * otherwise. */
static const FriendStatus *wfc_host_list_live(FriendList *list, int index)
{
    return &list->status[index];
}

/* --- The rows' shades --- */

/* func_ov146_02299684: each row slot showing a friend shaded by the friend's fade, toward the
 * full colour when the friend's game has its four entries, else toward the open one; a slot's
 * palette colour is made again only when its shade changed. */
void WfcHostList_ShadeRows(WfcHostList *self)
{
    for (int slot = 0; slot < WFC_HOST_LIST_ROWS; slot++) {
        int friend_index = self->row_friend[slot];
        if (friend_index >= WFC_HOST_LIST_FRIENDS) {
            continue;
        }
        u8 fade = self->fade[friend_index];
        u8 shade;
        int color;
        if (self->hosts[friend_index].num_entry >= WFC_HOST_LIST_MAX_ENTRIES) {
            shade = (u8) (fade | WFC_HOST_LIST_SHADE_FULL);
            color = WFC_HOST_LIST_COLOR_FULL;
        } else {
            shade = fade;
            color = WFC_HOST_LIST_COLOR_OPEN;
        }
        if (shade != self->row_shade[slot]) {
            WfcHostList_ShadeRow(self, slot, fade, color);
            self->row_shade[slot] = shade;
        }
    }
}
CLEAN_AS(func_ov146_02299684, WfcHostList_ShadeRows)

/* func_ov146_022996f4: colour 14 - `slot` of the shaded palette made `fade` twentieths of the
 * way from colour 15 to colour `color` of "bg7.bpl", by channel (each truncated to 8 bits),
 * and the palette to be queued.
 * QUIRK: the shade's index, 14 - `slot`, is taken modulo 256.
 * REQUIRES: `color` below 16 and `slot` 0-14, as the game passes them. */
void WfcHostList_ShadeRow(WfcHostList *self, int slot, int fade, int color)
{
    u16 back = self->palette[WFC_HOST_LIST_COLOR_BACK];
    u8 back_r = (u8) (back & 0x1f);
    u8 back_g = (u8) ((back & 0x3e0) >> 5);
    u8 back_b = (u8) ((back & 0x7c00) >> 10);
    int rest = WFC_HOST_LIST_FADE_FULL - fade;
    u16 front = self->palette[color];
    u8 r = (u8) (((u8) (front & 0x1f) * fade + back_r * rest) / WFC_HOST_LIST_FADE_FULL);
    u8 g = (u8) (((u8) ((front & 0x3e0) >> 5) * fade + back_g * rest) / WFC_HOST_LIST_FADE_FULL);
    u8 b = (u8) (((u8) ((front & 0x7c00) >> 10) * fade + back_b * rest) / WFC_HOST_LIST_FADE_FULL);
    self->shaded_palette[(u8) (WFC_HOST_LIST_COLOR_OPEN - slot)] = (u16) (r | g << 5 | b << 10);
    WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_PALETTE_DIRTY);
}
CLEAN_AS(func_ov146_022996f4, WfcHostList_ShadeRow)

/* --- The knob and the scroll --- */

/* func_ov146_02299af4: the knob at the scroll's place on the bar (0x50 for 0x1a0) and placed. */
void WfcHostList_KnobFromScroll(WfcHostList *self)
{
    self->knob = self->scroll * WFC_HOST_LIST_KNOB_MAX / WFC_HOST_LIST_SCROLL_MAX;
    WfcHostList_PlaceKnob(self);
}
CLEAN_AS(func_ov146_02299af4, WfcHostList_KnobFromScroll)

/* func_ov146_02299b1c: the scroll set at once to the knob's place (0-0x1a0), and made the
 * target. */
void WfcHostList_ScrollFromKnob(WfcHostList *self)
{
    int scroll = self->knob * WFC_HOST_LIST_SCROLL_MAX / WFC_HOST_LIST_KNOB_MAX;
    if (scroll < 0) {
        scroll = 0;
    }
    if (scroll > WFC_HOST_LIST_SCROLL_MAX) {
        scroll = WFC_HOST_LIST_SCROLL_MAX;
    }
    WfcHostList_SetScroll(self, scroll);
    self->scroll_target = scroll;
}
CLEAN_AS(func_ov146_02299b1c, WfcHostList_ScrollFromKnob)

/* func_ov146_02299b58: the knob drawn at x 0x62 on the bar, its y from the wipe's and the
 * knob's (0x28 above the knob's place). */
void WfcHostList_PlaceKnob(WfcHostList *self)
{
    DualCellSprite_SetOffset(wfc_host_list_knob_cells(self), 0x62, self->wipe_y + (self->knob - 0x28));
}
CLEAN_AS(func_ov146_02299b58, WfcHostList_PlaceKnob)

/* func_ov146_02299b80: once the knob's release has played, the knob at rest; 1 then, else 0. */
int WfcHostList_KnobReleased(WfcHostList *self)
{
    if (DualCellSprite_IsDone(wfc_host_list_knob_cells(self)) != 0) {
        PushButton_ShowUp(&self->knob_button);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov146_02299b80, WfcHostList_KnobReleased)

/* The pad: up and down held move the knob. */
extern PadState data_021fbe40;
#define WFC_HOST_LIST_PAD_UP 0x0040
#define WFC_HOST_LIST_PAD_DOWN 0x0080

/* func_ov146_02299ba8: up or down held move the knob 4 up or down (within 0-0x50); when it
 * moved, the scroll follows at once, the knob is placed and the scroll cues. */
void WfcHostList_KnobByKeys(WfcHostList *self)
{
    int old = self->knob;
    u16 held = data_021fbe40.held;

    if (held & WFC_HOST_LIST_PAD_UP) {
        self->knob -= 4;
        if (self->knob < 0) {
            self->knob = 0;
        }
    } else if (held & WFC_HOST_LIST_PAD_DOWN) {
        self->knob += 4;
        if (self->knob > WFC_HOST_LIST_KNOB_MAX) {
            self->knob = WFC_HOST_LIST_KNOB_MAX;
        }
    }

    if (old != self->knob) {
        WfcHostList_ScrollFromKnob(self);
        WfcHostList_PlaceKnob(self);
        PushButton_ScrollCue(&self->knob_button);
    }
}
CLEAN_AS(func_ov146_02299ba8, WfcHostList_KnobByKeys)

/* func_ov146_02299c34: the knob let go. */
void WfcHostList_ReleaseKnob(WfcHostList *self)
{
    PushButton_Release(&self->knob_button);
}
CLEAN_AS(func_ov146_02299c34, WfcHostList_ReleaseKnob)

/* func_ov146_02299c44: the knob to the pen's y: with `approach`, its centre (y less 0x40) is
 * approached by at most 8; else it follows the drag (y plus the drag's offset) at once; within
 * 0-0x50 either way. The scroll follows at once, the knob is placed, and the scroll cues each
 * time the knob has moved 4 or more since it last did. */
void WfcHostList_DragKnob(WfcHostList *self, int y, int approach)
{
    if (approach != 0) {
        y -= 0x40;
    } else {
        y += self->drag_offset;
    }
    if (y < 0) {
        y = 0;
    }
    if (y > WFC_HOST_LIST_KNOB_MAX) {
        y = WFC_HOST_LIST_KNOB_MAX;
    }

    if (approach != 0) {
        Approach_S32Again(&self->knob, y, 8);
    } else {
        self->knob = y;
    }
    WfcHostList_ScrollFromKnob(self);
    WfcHostList_PlaceKnob(self);

    int moved = self->cued_knob - self->knob;
    if (moved < 4 && moved > -4) {
        return;
    }
    PushButton_ScrollCue(&self->knob_button);
    self->cued_knob = self->knob;
}
CLEAN_AS(func_ov146_02299c44, WfcHostList_DragKnob)

/* func_ov146_02299cbc: when the pen at (x, y) is on the knob, the drag begins: its offset kept,
 * the knob pressed, the cue counted from here; 1 then, else 0. */
int WfcHostList_GrabKnob(WfcHostList *self, int x, int y)
{
    if (PushButton_Contains(&self->knob_button, x, y) == 0) {
        return 0;
    }
    self->drag_offset = self->knob - y;
    PushButton_Press(&self->knob_button);
    self->cued_knob = self->knob;
    return 1;
}
CLEAN_AS(func_ov146_02299cbc, WfcHostList_GrabKnob)

/* func_ov146_02299d04: the scroll 6 pixels nearer its target (not past it), and the knob after
 * it; 1 when it moved, 0 when it was there. */
int WfcHostList_StepScroll(WfcHostList *self)
{
    if (self->scroll == self->scroll_target) {
        return 0;
    }
    if (self->scroll > self->scroll_target) {
        self->scroll -= 6;
        if (self->scroll < self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    } else {
        self->scroll += 6;
        if (self->scroll > self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    }
    WfcHostList_SetScroll(self, self->scroll);
    WfcHostList_KnobFromScroll(self);
    return 1;
}
CLEAN_AS(func_ov146_02299d04, WfcHostList_StepScroll)

/* func_ov146_02299d84: the rows' screen built again: cleared with tile 16, then the 7 rows from
 * the top one, each copied from its slot of the base screen (lines 7 + 2 * slot) to its place
 * in the 32 lines (two per row, so wrapping every 16 rows); the screen to be queued.
 * QUIRK: the slot is the row modulo 7 by C's signed rule. */
void WfcHostList_BuildRowsScreen(WfcHostList *self)
{
    MIi_CpuClear16(16, self->rows_screen, sizeof(self->rows_screen));
    for (int i = 0; i < WFC_HOST_LIST_ROWS; i++) {
        int row = self->first_row + i;
        int slot = row % WFC_HOST_LIST_ROWS;
        const u16 *from = &self->screen[(slot * 2 + WFC_HOST_LIST_SLOT_FIRST_LINE) * WFC_HOST_LIST_SCREEN_LINE];
        u16 *to = &self->rows_screen[(row & 0xf) * WFC_HOST_LIST_ROW_TILES];
        MIi_CpuCopy16(from, to, WFC_HOST_LIST_ROW_TILES * sizeof(u16));
    }
    WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov146_02299d84, WfcHostList_BuildRowsScreen)

/* func_ov146_02299dec: the scroll set: the rows' layer scrolled to it (less 0x38), the top row
 * (scroll / 16), the rows' screen built, the rows' labels to be set again. */
void WfcHostList_SetScroll(WfcHostList *self, int scroll)
{
    self->scroll = scroll;
    DisplayLayer_SetScroll(WFC_HOST_LIST_ROWS_LAYER, 0, self->scroll - 0x38);
    self->first_row = (s16) (scroll >> 4);
    WfcHostList_BuildRowsScreen(self);
    WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_ROWS_DIRTY);
}
CLEAN_AS(func_ov146_02299dec, WfcHostList_SetScroll)

/* --- The friends --- */

/* func_ov146_02299e9c: whether friend `friend_index` can be chosen: it hosts a game (in the
 * live list) with fewer than four entries. 0 for an index of 32 or more. */
int WfcHostList_IsJoinable(WfcHostList *self, int friend_index)
{
    if (friend_index >= WFC_HOST_LIST_FRIENDS) {
        return 0;
    }
    const FriendStatus *status = wfc_host_list_live(WfcHostList_FriendList(self), friend_index);
    if (WfcHostList_IsHosting(self, status) == 0) {
        return 0;
    }
    return status->num_entry < WFC_HOST_LIST_MAX_ENTRIES;
}
CLEAN_AS(func_ov146_02299e9c, WfcHostList_IsJoinable)

/* func_ov146_02299ee8: whether a friend's status says it hosts a game (status 6) with status
 * data whose first character is not 0. The scene is not read. */
int WfcHostList_IsHosting(WfcHostList *self, const FriendStatus *status)
{
    (void) self;
    return status->status == WFC_HOST_LIST_STATUS_HOSTING && (status->data[0] != 0 || status->data[1] != 0);
}
CLEAN_AS(func_ov146_02299ee8, WfcHostList_IsHosting)

/* func_ov146_02299f08: the list made again from the scene's statuses: the friends kept as
 * hosting (in index order), each with the entries of its game; a friend still hosting in the
 * live list has its entries brought up to date first. The places after the last are emptied.
 * Answers whether any place of the list changed. */
int WfcHostList_RefreshList(WfcHostList *self)
{
    int changed = 0;
    int n = 0;
    FriendList *list = WfcHostList_FriendList(self);

    for (int i = 0; i < WFC_HOST_LIST_FRIENDS; i++) {
        if (self->hosts[i].status != WFC_HOST_LIST_STATUS_HOSTING) {
            continue;
        }
        if (self->list[n] != i) {
            changed = 1;
            self->list[n] = (u8) i;
        }
        const FriendStatus *live = wfc_host_list_live(list, i);
        if (WfcHostList_IsHosting(self, live) != 0) {
            self->hosts[i].num_entry = live->num_entry;
        }
        self->list_entries[n] = live->num_entry;
        n++;
    }
    for (; n < WFC_HOST_LIST_FRIENDS; n++) {
        if (self->list[n] != WFC_HOST_LIST_NONE) {
            changed = 1;
            self->list[n] = WFC_HOST_LIST_NONE;
            self->list_entries[n] = 0;
        }
    }
    return changed;
}
CLEAN_AS(func_ov146_02299f08, WfcHostList_RefreshList)

/* func_ov146_02299fbc: the scene's statuses brought up to date from the live list. A friend
 * hosting there fades in (to 20) when the scene has it as hosting, else its status is copied
 * and its fade starts from 0; a friend the scene has as hosting who no longer is fades out, and
 * at 0 the scene's status is cleared. When the count of friends hosting changed, it is shown
 * in full-width digits (one or two) in a label (style 8, tile 0x1f4, 2 cells, colours 9 and
 * 0). */
void WfcHostList_UpdateHosts(WfcHostList *self)
{
    FriendList *list = WfcHostList_FriendList(self);
    int count = 0;

    for (int i = 0; i < WFC_HOST_LIST_FRIENDS; i++) {
        const FriendStatus *live = wfc_host_list_live(list, i);
        FriendStatus *kept = &self->hosts[i];
        if (WfcHostList_IsHosting(self, live) != 0) {
            if (kept->status == WFC_HOST_LIST_STATUS_HOSTING) {
                if (self->fade[i] < WFC_HOST_LIST_FADE_FULL) {
                    self->fade[i]++;
                }
            } else {
                self->fade[i] = 0;
                MI_CpuCopy8(live, kept, sizeof(FriendStatus));
            }
            count++;
        } else if (kept->status == WFC_HOST_LIST_STATUS_HOSTING) {
            if (self->fade[i] != 0) {
                self->fade[i]--;
            } else {
                kept->status = 0;
            }
        }
    }

    if (count == self->host_count) {
        return;
    }
    self->host_count = (u8) count;
    TextLabel *label = WfcHostList_TakeLabel(self);
    u16 digits[3];
    if (self->host_count < 10) {
        digits[0] = (u16) (self->host_count + WFC_HOST_LIST_WIDE_ZERO);
        digits[1] = 0;
        digits[2] = 0;
    } else {
        digits[0] = (u16) (self->host_count / 10 + WFC_HOST_LIST_WIDE_ZERO);
        digits[1] = (u16) (self->host_count % 10 + WFC_HOST_LIST_WIDE_ZERO);
        digits[2] = 0;
    }
    TextLabel_SetFromWide(label, digits, (void *) (uintptr_t) 3);
    TextLabel_OpenStyledBox(label, 8, 0x1f4, 2, 9, 0, 1);
    TextLabel_Show(label, 0, 0);
}
CLEAN_AS(func_ov146_02299fbc, WfcHostList_UpdateHosts)

/* func_ov146_0229a0f8: the scene's statuses taken from the live list: emptied, then each friend
 * hosting copied, faded in (20); the others' fade 0. */
void WfcHostList_CopyHosts(WfcHostList *self)
{
    MI_CpuFill8(self->hosts, 0, sizeof(self->hosts));
    FriendList *list = WfcHostList_FriendList(self);
    for (int i = 0; i < WFC_HOST_LIST_FRIENDS; i++) {
        const FriendStatus *live = wfc_host_list_live(list, i);
        if (WfcHostList_IsHosting(self, live) != 0) {
            MI_CpuCopy8(live, &self->hosts[i], sizeof(FriendStatus));
            self->fade[i] = WFC_HOST_LIST_FADE_FULL;
        } else {
            self->fade[i] = 0;
        }
    }
}
CLEAN_AS(func_ov146_0229a0f8, WfcHostList_CopyHosts)

/* func_ov146_0229a174: the Wi-Fi Connection's friend list (NULL while not logged in). */
FriendList *WfcHostList_FriendList(WfcHostList *self)
{
    (void) self;
    return Wfc_GetFriendList();
}
CLEAN_AS(func_ov146_0229a174, WfcHostList_FriendList)

/* --- The labels --- */

/* func_ov146_0229a17c: the titles shown, on the first call only. */
void WfcHostList_ShowTitlesOnce(WfcHostList *self)
{
    if (self->titles_shown == 0) {
        WfcHostList_ShowTitles(self);
        self->titles_shown++;
    }
}
CLEAN_AS(func_ov146_0229a17c, WfcHostList_ShowTitlesOnce)

/* A title: menu message `message` in a label of style 8 at tile `tile` (6 cells, colours 15 and
 * 0), centred. */
static void wfc_host_list_show_title(WfcHostList *self, int message, int tile)
{
    TextLabel *label = WfcHostList_TakeLabel(self);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) message);
    TextLabel_OpenStyledBox2(label, 8, tile, 6, 0xf, 0, 0);
    TextLabel_Show(label, 1, 0);
}

/* func_ov146_0229a1a0: the three titles: menu messages 0x65, 0xc2 and 0xc1 at tiles 0x93, 0x8d
 * and 0x99. */
void WfcHostList_ShowTitles(WfcHostList *self)
{
    wfc_host_list_show_title(self, 0x65, 0x93);
    wfc_host_list_show_title(self, 0xc2, 0x8d);
    wfc_host_list_show_title(self, 0xc1, 0x99);
}
CLEAN_AS(func_ov146_0229a1a0, WfcHostList_ShowTitles)

/* func_ov146_0229a238: the labels of the rows on screen set again where the friend their slot
 * shows changed: a row past the list's 32 places only forgets its slot's friend; a row whose
 * place is empty gets two empty labels; a row of a friend gets the friend's town (menu message
 * 0x66 with the town's name from the status data's six characters at 0x10) and name (the six at
 * 0). Both labels are then opened in the row's slot and shown. The two texts the town's name
 * passes through are constructed on the first call. */
void WfcHostList_RefreshRowLabels(WfcHostList *self)
{
    if ((data_ov146_0229b78c & 1) == 0) {
        TownNameWideText_Construct(&data_ov146_0229b7a8);
        __register_global_object(&data_ov146_0229b7a8, (void *) (uintptr_t) func_02064158, data_ov146_0229b79c);
        data_ov146_0229b78c |= 1;
    }
    if ((data_ov146_0229b780 & 1) == 0) {
        TownNameText_Construct(&data_ov146_0229b7e4);
        __register_global_object(&data_ov146_0229b7e4, (void *) (uintptr_t) func_020641b0, data_ov146_0229b790);
        data_ov146_0229b780 |= 1;
    }

    /* QUIRK: the friend list is asked for and not used. */
    WfcHostList_FriendList(self);

    int row = self->first_row;
    int slot = row % WFC_HOST_LIST_ROWS;
    for (int i = 0; i < WFC_HOST_LIST_ROWS; i++) {
        if (row >= WFC_HOST_LIST_FRIENDS) {
            self->row_friend[slot] = WFC_HOST_LIST_NONE;
        } else {
            int friend_index = self->list[row];
            TextLabel *town = NULL;
            TextLabel *name = NULL;
            if (friend_index == self->row_friend[slot]) {
                /* the slot shows it already */
            } else if (friend_index >= WFC_HOST_LIST_FRIENDS) {
                town = WfcHostList_TakeLabel(self);
                TextBase_Clear(town);
                name = WfcHostList_TakeLabel(self);
                TextBase_Clear(name);
                self->row_friend[slot] = WFC_HOST_LIST_NONE;
            } else {
                const FriendStatus *host = &self->hosts[friend_index];
                self->row_friend[slot] = (u8) friend_index;
                town = WfcHostList_TakeLabel(self);
                TextBase_SetWide(&data_ov146_0229b7a8, host->data + WFC_HOST_LIST_TOWN_OFFSET, WFC_HOST_LIST_NAME_LENGTH);
                TextBase_WideToBytes((TextBase *) (void *) &data_ov146_0229b7e4,
                                     (WideTextBase *) (void *) &data_ov146_0229b7a8, 0, 0);
                MessageReader_SetPart(0, (int) (uintptr_t) &data_ov146_0229b7e4);
                TextLabel_LoadMenuMessage((int) (uintptr_t) town, WFC_HOST_LIST_TOWN_MESSAGE);
                name = WfcHostList_TakeLabel(self);
                TextLabel_SetFromWide(name, (const u16 *) (const void *) host->data,
                                      (void *) (uintptr_t) WFC_HOST_LIST_NAME_LENGTH);
            }
            if (town != NULL) {
                u8 color = (u8) (WFC_HOST_LIST_COLOR_OPEN - slot);
                TextLabel_OpenStyledBox2(town, 4, 0x11e + slot * 0x14, 0xa, color, 0xf, 0);
                TextLabel_Show(town, 0, 0);
                TextLabel_OpenStyledBox2(name, 4, 0x1d2 + slot * 0x10, 8, color, 0xf, 0);
                TextLabel_Show(name, 0, 0);
            }
        }
        row++;
        slot++;
        if (slot >= WFC_HOST_LIST_ROWS) {
            slot = 0;
        }
    }
}
CLEAN_AS(func_ov146_0229a238, WfcHostList_RefreshRowLabels)

/* func_ov146_0229a400: the labels' boxes closed; none taken. */
void WfcHostList_CloseLabels(WfcHostList *self)
{
    self->labels_used = 0;
    for (int i = 0; i < WFC_HOST_LIST_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov146_0229a400, WfcHostList_CloseLabels)

/* func_ov146_0229a42c: the next label free this frame.
 * QUIRK: once all 20 are taken, the last one is handed out again. */
TextLabel *WfcHostList_TakeLabel(WfcHostList *self)
{
    if (self->labels_used >= WFC_HOST_LIST_LABELS) {
        return &self->labels[WFC_HOST_LIST_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov146_0229a42c, WfcHostList_TakeLabel)
