/* The host picker of overlay 140 (host_picker.h): its destructors, its flags, the labels, the
 * list's pages and rows, the cursor and its sprite, the frame's states and the scene's
 * slots. */
#include "host_picker.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/group_params.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_string.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov092/menu_dispatch.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(HostPicker, wipe_y) == 0x94, "wipe");
static_assert(offsetof(HostPicker, selected) == 0x9c && offsetof(HostPicker, page_palette) == 0xa8, "palettes");
static_assert(offsetof(HostPicker, screen) == 0xac && offsetof(HostPicker, flags) == 0x8ac, "screen");
static_assert(offsetof(HostPicker, row_used) == 0x8af && offsetof(HostPicker, order) == 0x8b5, "rows");
static_assert(offsetof(HostPicker, row_friend) == 0x8d5 && offsetof(HostPicker, steps) == 0x8db, "steps");
static_assert(offsetof(HostPicker, host_count) == 0x8df && offsetof(HostPicker, row_entries) == 0x8e0, "entries");
static_assert(offsetof(HostPicker, labels_used) == 0x8e6 && offsetof(HostPicker, rows) == 0x8e8, "res rows");
static_assert(offsetof(HostPicker, cursor_sprite) == 0x128c && offsetof(HostPicker, panel) == 0x12f0, "panel");
static_assert(offsetof(HostPicker, screen_task) == 0x14bc && sizeof(LayerTask) == 0x24, "task");
static_assert(offsetof(HostPicker, labels) == 0x1abc && sizeof(TextLabel) == 0x6c, "labels");
static_assert(sizeof(HostPicker) == 0x1c00, "size (func_ov140_0229b268)");

/* The scene's vtable. */
extern const u8 data_ov140_0229b404[];

/* The background's screen file, and the OBJ cells drawn: the frame of the rows, the selected
 * row's mark, the buttons' frame, and the icon of each number of a host's entries (0: none). */
extern const char data_ov140_0229b5b4[]; /* "menu/res/d0_bg.bsc" */
extern const OamEntry data_ov140_0229b3a4[];
extern const OamEntry data_ov140_0229b3cc[];
extern const OamEntry data_ov140_0229b464[];
extern const u32 data_ov140_0229b390[];

/* The text labels' destructor and constructor, as the game hands them to the vector helpers. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern void *func_02070be8(void *label);

/* The pad, and the pen (autoload_2/input.c): down, and gone down this frame; the touch. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */
#define HOST_PICKER_PAD_A 0x0001
#define HOST_PICKER_PAD_B 0x0002

/* An entry of the friend list (FriendStatus, autoload_2/network.h): 0x23 bytes from 0x180. */
#define HOST_PICKER_ENTRIES_OFFSET 0x180
#define HOST_PICKER_ENTRY_SIZE 0x23
#define HOST_PICKER_ENTRY_NAME 0x10      /* the first column's name, in the status data */
#define HOST_PICKER_ENTRY_STATUS 0x20    /* FriendStatus.status */
#define HOST_PICKER_ENTRY_NUM_ENTRY 0x22 /* FriendStatus.num_entry */
#define HOST_PICKER_STATUS_HOSTING 6
#define HOST_PICKER_FULL 4 /* entries of a town that takes no more */
#define HOST_PICKER_NO_ORDER 0xff
#define HOST_PICKER_NAME_LENGTH 6
#define HOST_PICKER_FADE_STEPS 5

/* The labels' look: the first digit of a full-width font, and the boxes of the page number,
 * the number of pages and the number of hosts. */
#define HOST_PICKER_DIGIT_0 0xff10
#define HOST_PICKER_BOX_PAGE 0x1f2
#define HOST_PICKER_BOX_LAST_PAGE 0x1f3
#define HOST_PICKER_BOX_HOSTS 0x1f4

/* What the parent (overlay 92's) is told when the scene wipes out: the menu closes. */
#define HOST_PICKER_PARENT_CLOSE 0x44

static MenuScene *host_scene(HostPicker *self)
{
    return &self->base;
}

static CellLayerSprite *host_sprite_cells(HostPicker *self)
{
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

static MenuDispatch *host_parent(HostPicker *self)
{
    return (MenuDispatch *) (void *) Process_GetParent((Process *) (void *) self);
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void host_update_sprite(Glider *sprite)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* Entry `index` of the friend list at `friends` (computed as an address: the list is NULL while
 * the connection is not logged in, and the index may pass its end). */
static const u8 *host_entry(u32 friends, int index)
{
    return (const u8 *) (uintptr_t) (friends + HOST_PICKER_ENTRIES_OFFSET + (u32) index * HOST_PICKER_ENTRY_SIZE);
}

/* The members' destructors, last member first, then the base's. The layer task has none. */
static void host_destroy_members(HostPicker *self)
{
    self->base.vtable = data_ov140_0229b404;
    __cxa_vec_cleanup(self->labels, HOST_PICKER_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->cursor_sprite);
    ResRows_Destroy(&self->rows);
    MenuScene_DestroyBase(host_scene(self));
}

/* func_ov140_02299ee0 (vtable slot 0x40) */
HostPicker *HostPicker_Destroy(HostPicker *self)
{
    host_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov140_02299ee0, HostPicker_Destroy)

/* func_ov140_02299f34 (vtable slot 0x44) */
HostPicker *HostPicker_Delete(HostPicker *self)
{
    host_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov140_02299f34, HostPicker_Delete)

/* func_ov140_02299f90 */
void HostPicker_ClearFlags(HostPicker *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov140_02299f90, HostPicker_ClearFlags)

/* func_ov140_02299fa0 */
void HostPicker_SetFlags(HostPicker *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov140_02299fa0, HostPicker_SetFlags)

/* func_ov140_02299fb0 */
int HostPicker_TestFlags(HostPicker *self, int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov140_02299fb0, HostPicker_TestFlags)

/* A one-digit number in a label of this frame, in box `box`, `cells` wide. */
static void host_show_digit(HostPicker *self, int digit, int box)
{
    u8 *label = HostPicker_TakeLabel(self);
    u16 text[2];
    text[0] = (u16) (digit + HOST_PICKER_DIGIT_0);
    text[1] = 0;
    TextLabel_SetFromWide(label, text, (void *) (uintptr_t) 2);
    TextLabel_OpenStyledBox((TextLabel *) (void *) label, 8, box, 1, 0xf, 0, 1);
    TextLabel_Show((TextLabel *) (void *) label, 0, 0);
}

/* func_ov140_02299fc8: the page number (from 0) drawn. */
void HostPicker_ShowPage(HostPicker *self)
{
    host_show_digit(self, self->page, HOST_PICKER_BOX_PAGE);
}
CLEAN_AS(func_ov140_02299fc8, HostPicker_ShowPage)

/* func_ov140_0229a020: the last page's number drawn. */
void HostPicker_ShowLastPage(HostPicker *self)
{
    host_show_digit(self, self->last_page, HOST_PICKER_BOX_LAST_PAGE);
}
CLEAN_AS(func_ov140_0229a020, HostPicker_ShowLastPage)

/* func_ov140_0229a078: the number of hosts drawn, in one or two digits.
 * QUIRK: from 100 the tens digit is past the font's digits (the list has 32 entries). */
void HostPicker_ShowHostCount(HostPicker *self)
{
    u8 *label = HostPicker_TakeLabel(self);
    u16 digits[3];
    u8 count = self->host_count;
    if (count < 10) {
        digits[0] = (u16) (count + HOST_PICKER_DIGIT_0);
        digits[1] = 0;
        digits[2] = 0;
    } else {
        digits[0] = (u16) (count / 10 + HOST_PICKER_DIGIT_0);
        digits[1] = (u16) (count % 10 + HOST_PICKER_DIGIT_0);
        digits[2] = 0;
    }
    TextLabel_SetFromWide(label, digits, (void *) (uintptr_t) 3);
    TextLabel_OpenStyledBox((TextLabel *) (void *) label, 8, HOST_PICKER_BOX_HOSTS, 2, 0xf, 0, 1);
    TextLabel_Show((TextLabel *) (void *) label, 0, 0);
}
CLEAN_AS(func_ov140_0229a078, HostPicker_ShowHostCount)

/* func_ov140_0229a100: the labels given back and their boxes closed. */
void HostPicker_CloseLabels(HostPicker *self)
{
    self->labels_used = 0;
    for (int i = 0; i < HOST_PICKER_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov140_0229a100, HostPicker_CloseLabels)

/* func_ov140_0229a12c: the next label of this frame; once the three are used, the last one
 * again. */
u8 *HostPicker_TakeLabel(HostPicker *self)
{
    if (self->labels_used < HOST_PICKER_LABELS) {
        self->labels_used++;
        return (u8 *) (void *) &self->labels[self->labels_used - 1];
    }
    return (u8 *) (void *) &self->labels[HOST_PICKER_LABELS - 1];
}
CLEAN_AS(func_ov140_0229a12c, HostPicker_TakeLabel)

/* func_ov140_0229a15c: NitroDWC's friend list, as an address (0 while not logged in). */
unsigned int HostPicker_FriendList(HostPicker *self)
{
    (void) self;
    return (unsigned int) (uintptr_t) Wfc_GetFriendList();
}
CLEAN_AS(func_ov140_0229a15c, HostPicker_FriendList)

/* func_ov140_0229a164: each row's colour at fade step `step` of 5 (5: shown, 0: gone): from
 * colour 8 of the rows' palette for a full town, 14 for the others. */
void HostPicker_FadeRows(HostPicker *self, int step)
{
    for (int row = 0; row < HOST_PICKER_ROWS; row++) {
        int color = self->row_entries[row] == HOST_PICKER_FULL ? 8 : 14;
        ResRows_FadeRow(&self->rows, row, step, HOST_PICKER_FADE_STEPS, color);
    }
}
CLEAN_AS(func_ov140_0229a164, HostPicker_FadeRows)

/* func_ov140_0229a1a4: whether the friend list's entry hosts a game and has a name. */
int HostPicker_IsHosting(int unused, const u8 *entry)
{
    (void) unused;
    return entry[HOST_PICKER_ENTRY_STATUS] == HOST_PICKER_STATUS_HOSTING && (entry[0] != 0 || entry[1] != 0);
}
CLEAN_AS(func_ov140_0229a1a4, HostPicker_IsHosting)

/* func_ov140_0229a1c4: the list set up: the hosts counted, the places in the list's order, the
 * first of six pages, and the three numbers drawn; the next page button lit when there are
 * more pages.
 * QUIRK: the last page is always 5, so the button is always lit. */
void HostPicker_InitList(HostPicker *self)
{
    u32 friends = HostPicker_FriendList(self);
    int count = 0;
    for (int i = 0; i < HOST_PICKER_FRIENDS; i++) {
        if (HostPicker_IsHosting((int) (uintptr_t) self, host_entry(friends, i)) != 0) {
            count++;
        }
        self->order[i] = (u8) i;
    }
    self->page = 0;
    self->last_page = 5;
    self->host_count = (u8) count;
    HostPicker_ShowLastPage(self);
    HostPicker_ShowHostCount(self);
    HostPicker_ShowPage(self);
    if (self->last_page != 0) {
        self->page_palette = HOST_PICKER_PAL_LIT;
    }
}
CLEAN_AS(func_ov140_0229a1c4, HostPicker_InitList)

/* func_ov140_0229a244: the number of friends that host a game. */
int HostPicker_CountHosts(HostPicker *self)
{
    u32 friends = HostPicker_FriendList(self);
    int count = 0;
    for (int i = 0; i < HOST_PICKER_FRIENDS; i++) {
        if (HostPicker_IsHosting((int) (uintptr_t) self, host_entry(friends, i))) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_ov140_0229a244, HostPicker_CountHosts)

/* func_ov140_0229a280: the page's rows filled from the list (the rows' palette marked first):
 * a place of the list with a host shows its two names (the status data's from 0x10, then from
 * 0) and keeps its entry and its entries; any other row is cleared.
 * QUIRK: the two names are one buffer of twelve characters that ResRows_SetRow reads whole (the
 * game keeps them in two arrays that sit one after the other on its stack). */
void HostPicker_FillRows(HostPicker *self)
{
    u16 names[2 * HOST_PICKER_NAME_LENGTH];

    HostPicker_MarkRows(self);
    TextString_ClearChars(names, HOST_PICKER_NAME_LENGTH);
    TextString_ClearChars(names + HOST_PICKER_NAME_LENGTH, HOST_PICKER_NAME_LENGTH);
    int place = self->page * HOST_PICKER_ROWS;
    u32 friends = HostPicker_FriendList(self);
    for (int row = 0; row < HOST_PICKER_ROWS; row++, place++) {
        if (place < HOST_PICKER_FRIENDS) {
            u8 index = self->order[place];
            const u8 *entry = host_entry(friends, index);
            if (index != HOST_PICKER_NO_ORDER && HostPicker_IsHosting((int) (uintptr_t) self, entry) != 0) {
                self->row_friend[row] = index;
                self->row_used[row] = 1;
                self->row_entries[row] = entry[HOST_PICKER_ENTRY_NUM_ENTRY];
                TextString_CopyChars((const u16 *) (const void *) (entry + HOST_PICKER_ENTRY_NAME), names,
                                     HOST_PICKER_NAME_LENGTH);
                TextString_CopyChars((const u16 *) (const void *) entry, names + HOST_PICKER_NAME_LENGTH,
                                     HOST_PICKER_NAME_LENGTH);
                ResRows_SetRow(&self->rows, row, names);
                continue;
            }
        }
        self->row_used[row] = 0;
        self->row_entries[row] = 0;
        ResRows_ClearRow(&self->rows, row);
    }
}
CLEAN_AS(func_ov140_0229a280, HostPicker_FillRows)

/* func_ov140_0229a384: each row's entries read again (0 for a place without a host); whether
 * any changed.
 * QUIRK: the places are read in the list's own order, not through `order` (the same while
 * `order` is as HostPicker_InitList sets it), and the last page's places 32-35 read past the
 * list. */
int HostPicker_RefreshEntries(HostPicker *self)
{
    int changed = 0;
    u32 friends = HostPicker_FriendList(self);
    int place = self->page * HOST_PICKER_ROWS;
    for (int row = 0; row < HOST_PICKER_ROWS; row++, place++) {
        const u8 *entry = host_entry(friends, place);
        int entries = 0;
        if (HostPicker_IsHosting((int) (uintptr_t) self, entry) != 0) {
            entries = entry[HOST_PICKER_ENTRY_NUM_ENTRY];
        }
        if (entries != self->row_entries[row]) {
            changed = 1;
            self->row_entries[row] = (u8) entries;
        }
    }
    return changed;
}
CLEAN_AS(func_ov140_0229a384, HostPicker_RefreshEntries)

/* func_ov140_0229a3fc: `row` selected (-1: none), the confirm button lit only with one. */
void HostPicker_Select(HostPicker *self, int row)
{
    self->selected = row;
    if (row == -1) {
        self->confirm_palette = HOST_PICKER_PAL_UNLIT;
    } else {
        self->confirm_palette = HOST_PICKER_PAL_LIT;
    }
}
CLEAN_AS(func_ov140_0229a3fc, HostPicker_Select)

/* func_ov140_0229a41c: the rows' two columns of the screen put in palette 7 (the rows'), and the
 * screen to be queued. */
void HostPicker_MarkRows(HostPicker *self)
{
    ScreenMap_SetPalette(self->screen, 6, 8, 0xf, 0x13, 7);
    ScreenMap_SetPalette(self->screen, 0x11, 8, 0x18, 0x13, 7);
    HostPicker_SetFlags(self, HOST_PICKER_FLAG_SCREEN);
}
CLEAN_AS(func_ov140_0229a41c, HostPicker_MarkRows)

/* func_ov140_0229a460: a changed screen queued to layer 6; once queued it is no longer marked. */
void HostPicker_QueueScreen(HostPicker *self)
{
    if (!HostPicker_TestFlags(self, HOST_PICKER_FLAG_SCREEN)) {
        return;
    }
    if (!LayerTask_QueueScreen(&self->screen_task, (int) (uintptr_t) self->screen, 6, sizeof(self->screen), 0)) {
        return;
    }
    HostPicker_ClearFlags(self, HOST_PICKER_FLAG_SCREEN);
}
CLEAN_AS(func_ov140_0229a460, HostPicker_QueueScreen)

/* func_ov140_0229a4a0: the cursor moved by the d-pad keys `keys`; whether it moved. Up and down
 * go along the rows, and down from the last row to the next page button; on the buttons, up
 * goes back to the last row and left and right move between them without wrapping. */
int HostPicker_MoveCursor(HostPicker *self, int keys)
{
    u8 before = self->cursor;
    if (before <= HOST_PICKER_LAST_ROW) {
        if (KeyRepeat_HasUp(keys)) {
            if (self->cursor != HOST_PICKER_FIRST_ROW) {
                self->cursor--;
            }
        } else if (KeyRepeat_HasDown(keys)) {
            if (self->cursor < HOST_PICKER_LAST_ROW) {
                self->cursor++;
            } else {
                self->cursor = HOST_PICKER_PAGE;
            }
        }
    } else {
        if (KeyRepeat_HasUp(keys)) {
            self->cursor = HOST_PICKER_LAST_ROW;
        } else if (KeyRepeat_HasLeft(keys)) {
            if (self->cursor > HOST_PICKER_PAGE) {
                self->cursor--;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            if (self->cursor < HOST_PICKER_CONFIRM) {
                self->cursor++;
            }
        }
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov140_0229a4a0, HostPicker_MoveCursor)

/* func_ov140_0229a544: the sprite shows the third look of its set (a press let go) and the
 * scene waits for it (sub state 4) before going back to this sub state. */
void HostPicker_PressAndReturn(HostPicker *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_PRESS_RELEASE);
}
CLEAN_AS(func_ov140_0229a544, HostPicker_PressAndReturn)

/* func_ov140_0229a570: the sprite shows the second look of its set (pressed) and, once it has,
 * the press is acted on (sub state 3). */
void HostPicker_PressToAct(HostPicker *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_PRESS_ACT);
}
CLEAN_AS(func_ov140_0229a570, HostPicker_PressToAct)

/* func_ov140_0229a590: the sprite shows the first look of its set and is updated. */
void HostPicker_ShowCursorSprite(HostPicker *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    host_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov140_0229a590, HostPicker_ShowCursorSprite)

/* func_ov140_0229a5b0: the sprite eases to (x, y) in three steps, with the move's sound unless
 * HOST_PICKER_FLAG_SILENT (then cleared), and the scene waits for it (sub state 2) before going
 * back to this sub state. Answers MenuScene_SetSubState's answer. */
u8 *HostPicker_GlideTo(HostPicker *self, int x, int y)
{
    if (HostPicker_TestFlags(self, HOST_PICKER_FLAG_SILENT) != 0) {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 0);
        HostPicker_ClearFlags(self, HOST_PICKER_FLAG_SILENT);
    } else {
        Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    }
    self->return_sub_state = self->base.sub_state;
    return MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov140_0229a5b0, HostPicker_GlideTo)

/* func_ov140_0229a614: the sprite glides to the cursor. Answers HostPicker_GlideTo's answer. */
int HostPicker_GlideToCursor(HostPicker *self)
{
    int x = HostPicker_CursorSpriteX(self);
    int y = HostPicker_CursorSpriteY(self);
    return (int) (uintptr_t) HostPicker_GlideTo(self, x, y);
}
CLEAN_AS(func_ov140_0229a614, HostPicker_GlideToCursor)

/* func_ov140_0229a638: the sprite hidden (no animation) and updated. */
void HostPicker_HideCursorSprite(HostPicker *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    host_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov140_0229a638, HostPicker_HideCursorSprite)

/* func_ov140_0229a65c: the sprite's y for the cursor: 0xae on the buttons, else 16 pixels a
 * row from 0x46. */
int HostPicker_CursorSpriteY(HostPicker *self)
{
    u8 cursor = self->cursor;
    if ((u8) (cursor - HOST_PICKER_PAGE) <= HOST_PICKER_CONFIRM - HOST_PICKER_PAGE) {
        return 0xae;
    }
    return (cursor << 4) + 0x46;
}
CLEAN_AS(func_ov140_0229a65c, HostPicker_CursorSpriteY)

/* func_ov140_0229a67c: the sprite's x for the cursor: each button's, else the rows' 0x24. */
int HostPicker_CursorSpriteX(HostPicker *self)
{
    switch (self->cursor) {
        case HOST_PICKER_CANCEL:
            return 0x6a;
        case HOST_PICKER_CONFIRM:
            return 0xab;
        case HOST_PICKER_PAGE:
            return 0x29;
        default:
            return 0x24;
    }
}
CLEAN_AS(func_ov140_0229a67c, HostPicker_CursorSpriteX)

/* func_ov140_0229a6a0: the sprite put at the cursor at once, with the looks of set B, and
 * shown. */
void HostPicker_PlaceSpriteAtCursor(HostPicker *self)
{
    int x = HostPicker_CursorSpriteX(self);
    int y = HostPicker_CursorSpriteY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    HostPicker_ShowCursorSprite(self);
}
CLEAN_AS(func_ov140_0229a6a0, HostPicker_PlaceSpriteAtCursor)

/* func_ov140_0229a6dc: the next page (after the last, the first): the rows fade out over five
 * frames (sub state 6), the page number drawn, the button pressed, the selection dropped;
 * sound 0xc. */
void HostPicker_NextPage(HostPicker *self)
{
    HostPicker_SetFlags(self, HOST_PICKER_FLAG_PAGING);
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_PAGE_OUT);
    self->steps = HOST_PICKER_FADE_STEPS;
    self->page++;
    if (self->page > self->last_page) {
        self->page = 0;
    }
    HostPicker_ShowPage(self);
    self->page_palette = HOST_PICKER_PAL_PRESSED;
    HostPicker_Select(self, -1);
    SoundSys_PlaySe(0xc);
}
CLEAN_AS(func_ov140_0229a6dc, HostPicker_NextPage)

/* func_ov140_0229a73c: cancelled: the button pressed, and after five frames (sub state 5) the
 * wipe out (state 3); sound 0x28. */
void HostPicker_Cancel(HostPicker *self)
{
    HostPicker_SetFlags(self, HOST_PICKER_FLAG_CANCELLED);
    self->cancel_palette = HOST_PICKER_PAL_PRESSED;
    self->steps = HOST_PICKER_FADE_STEPS;
    MenuScene_SetState(host_scene(self), HOST_PICKER_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_CLOSING);
    SoundSys_PlaySe(0x28);
}
CLEAN_AS(func_ov140_0229a73c, HostPicker_Cancel)

/* func_ov140_0229a774: confirmed: as HostPicker_Cancel with the confirm button; sound 0x27. */
void HostPicker_Confirm(HostPicker *self)
{
    HostPicker_ClearFlags(self, HOST_PICKER_FLAG_CANCELLED);
    self->confirm_palette = HOST_PICKER_PAL_PRESSED;
    self->steps = HOST_PICKER_FADE_STEPS;
    MenuScene_SetState(host_scene(self), HOST_PICKER_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_CLOSING);
    SoundSys_PlaySe(0x27);
}
CLEAN_AS(func_ov140_0229a774, HostPicker_Confirm)

/* func_ov140_0229a7ac: back to the list, by touch while the keys are not in use (state flag 2
 * clear), else by the keys. */
void HostPicker_Resume(HostPicker *self)
{
    if (StateFlags_IsClear2() != 0) {
        HostPicker_ResumeByTouch(self);
    } else {
        HostPicker_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov140_0229a7ac, HostPicker_Resume)

/* func_ov140_0229a7cc: the list by the keys (sub state 1): the sprite at the cursor, the key
 * repeat restarted. */
void HostPicker_ResumeByKeys(HostPicker *self)
{
    HostPicker_PlaceSpriteAtCursor(self);
    MenuScene_ResetKeyRepeat(host_scene(self));
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_KEYS);
}
CLEAN_AS(func_ov140_0229a7cc, HostPicker_ResumeByKeys)

/* func_ov140_0229a7e8: the list by touch (sub state 0), the sprite hidden. */
void HostPicker_ResumeByTouch(HostPicker *self)
{
    HostPicker_HideCursorSprite(self);
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_TOUCH);
}
CLEAN_AS(func_ov140_0229a7e8, HostPicker_ResumeByTouch)

/* func_ov140_0229a800 (sub state 7): the new page's rows fade in a step a frame; at the end the
 * next page button is lit again and the list is used by touch, or by the keys after the
 * press's release. */
void HostPicker_FadeRowsIn(HostPicker *self)
{
    if (self->steps < HOST_PICKER_FADE_STEPS) {
        HostPicker_FadeRows(self, self->steps);
        self->steps++;
        return;
    }
    HostPicker_FadeRows(self, HOST_PICKER_FADE_STEPS);
    self->page_palette = HOST_PICKER_PAL_LIT;
    if (StateFlags_IsClear2()) {
        HostPicker_ResumeByTouch(self);
    } else {
        MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_KEYS);
        HostPicker_PressAndReturn(self);
    }
    HostPicker_ClearFlags(self, HOST_PICKER_FLAG_PAGING);
}
CLEAN_AS(func_ov140_0229a800, HostPicker_FadeRowsIn)

/* func_ov140_0229a85c (sub state 6): the old page's rows fade out a step a frame; once gone the
 * rows are filled from the new page and fade in (sub state 7). */
void HostPicker_FadeRowsOut(HostPicker *self)
{
    if (self->steps > 1) {
        self->steps--;
        HostPicker_FadeRows(self, self->steps);
    } else {
        HostPicker_FadeRows(self, 0);
        HostPicker_FillRows(self);
        MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_PAGE_IN);
    }
}
CLEAN_AS(func_ov140_0229a85c, HostPicker_FadeRowsOut)

/* func_ov140_0229a894 (sub state 5): the steps counted down (answering what is left); then the
 * sprite hidden and the states run (phase 1), which wipe the scene out. */
int HostPicker_WaitToClose(HostPicker *self)
{
    if (self->steps != 0) {
        int left = self->steps - 1;
        self->steps = (u8) left;
        return left;
    }
    HostPicker_HideCursorSprite(self);
    return (int) (uintptr_t) MenuScene_SetPhase(host_scene(self), 1);
}
CLEAN_AS(func_ov140_0229a894, HostPicker_WaitToClose)

/* func_ov140_0229a8c0 (sub state 4): once the sprite's look has played, it shows its first look
 * again and the scene goes back to the sub state it came from; after a row was selected the
 * cursor goes on to the confirm button. */
void HostPicker_WaitPressRelease(HostPicker *self)
{
    if (CellLayerSprite_IsDone(host_sprite_cells(self)) == 0) {
        return;
    }
    HostPicker_ShowCursorSprite(self);
    MenuScene_SetSubState(host_scene(self), self->return_sub_state);
    if (HostPicker_TestFlags(self, HOST_PICKER_FLAG_SELECTED) == 0) {
        return;
    }
    HostPicker_ClearFlags(self, HOST_PICKER_FLAG_SELECTED);
    self->cursor = HOST_PICKER_CONFIRM;
    HostPicker_GlideToCursor(self);
}
CLEAN_AS(func_ov140_0229a8c0, HostPicker_WaitPressRelease)

/* func_ov140_0229a914 (sub state 3): once the press has played, it is acted on: a lit next page
 * or confirm button, the cancel button, or a row with a host whose town is not full (selected,
 * sound 0x29, the cursor then goes on to confirm, silently). Otherwise, and after a row, back
 * to the keys through the press's release.
 * REQUIRES: the cursor is a HostPickerPlace. */
void HostPicker_ActOnPress(HostPicker *self)
{
    if (CellLayerSprite_IsDone(host_sprite_cells(self)) == 0) {
        return;
    }
    u8 cursor = self->cursor;
    if (cursor == HOST_PICKER_PAGE) {
        if (self->page_palette == HOST_PICKER_PAL_LIT) {
            HostPicker_NextPage(self);
            return;
        }
    } else if (cursor == HOST_PICKER_CONFIRM) {
        if (self->confirm_palette == HOST_PICKER_PAL_LIT) {
            HostPicker_Confirm(self);
            return;
        }
    } else if (cursor == HOST_PICKER_CANCEL) {
        HostPicker_Cancel(self);
        return;
    } else if (self->row_used[cursor] != 0 && self->row_entries[cursor] != HOST_PICKER_FULL) {
        HostPicker_Select(self, cursor);
        SoundSys_PlaySe(0x29);
        HostPicker_SetFlags(self, HOST_PICKER_FLAG_SELECTED);
        HostPicker_SetFlags(self, HOST_PICKER_FLAG_SILENT);
    }
    MenuScene_SetSubState(host_scene(self), HOST_PICKER_SUB_KEYS);
    HostPicker_PressAndReturn(self);
}
CLEAN_AS(func_ov140_0229a914, HostPicker_ActOnPress)

/* Obj_ov140_0229b404::func_ov140_0229a9b4 (sub state 2): once the sprite has stopped, back to
 * the sub state it came from, which runs at once. */
void HostPicker_WaitCursorSprite(HostPicker *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(host_scene(self), self->return_sub_state);
        HostPicker_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov140_0229b40419func_ov140_0229a9b4Ev, HostPicker_WaitCursorSprite)

/* func_ov140_0229a9e4 (sub state 1): the list by the keys, after the hosts are read again. A
 * touch hands it to the pen; a move of the cursor glides the sprite; A presses and B cancels. */
void HostPicker_BrowseByKeys(HostPicker *self)
{
    HostPicker_RefreshHosts(self);
    if (MenuScene_TakeTouch(host_scene(self)) != 0) {
        HostPicker_ResumeByTouch(self);
        return;
    }
    if (HostPicker_MoveCursor(self, (int) MenuScene_LatchRepeatedKeys(host_scene(self))) != 0) {
        HostPicker_GlideToCursor(self);
        return;
    }
    if (data_021fbe40.pressed & HOST_PICKER_PAD_A) {
        HostPicker_PressToAct(self);
    } else if (data_021fbe40.pressed & HOST_PICKER_PAD_B) {
        HostPicker_Cancel(self);
        HostPicker_HideCursorSprite(self);
    }
}
CLEAN_AS(func_ov140_0229a9e4, HostPicker_BrowseByKeys)

/* func_ov140_0229aa4c (sub state 0): the list by touch, after the hosts are read again. A
 * button hands it to the keys; a touch this frame on a row (x 0x28-0xcf, y 0x40-0x9f) with a
 * host whose town is not full selects it (sound 0x29), and in the buttons' line (y 0xa6-0xb6)
 * presses cancel, or a lit confirm or next page button. */
void HostPicker_BrowseByTouch(HostPicker *self)
{
    HostPicker_RefreshHosts(self);
    if (MenuScene_TakeButtons(host_scene(self), 1) != 0) {
        HostPicker_ResumeByKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    int x = data_021f6c58;
    int y = (int) data_021f6c54 - 0x10;
    if (x >= 0x28 && x < 0xd0 && y >= 0x30 && y < 0x90) {
        int row = (y - 0x30) >> 4;
        if (self->row_used[row] != 0 && self->row_entries[row] != HOST_PICKER_FULL) {
            HostPicker_Select(self, row);
            SoundSys_PlaySe(0x29);
        }
    } else if (y >= 0x96 && y < 0xa7) {
        if (x >= 0x5e && x < 0x9a) {
            HostPicker_Cancel(self);
        } else if (x >= 0x9f && x < 0xdb) {
            if (self->confirm_palette == HOST_PICKER_PAL_LIT) {
                HostPicker_Confirm(self);
            }
        } else if (x >= 0x1d && x < 0x59) {
            if (self->page_palette == HOST_PICKER_PAL_LIT) {
                HostPicker_NextPage(self);
            }
        }
    }
}
CLEAN_AS(func_ov140_0229aa4c, HostPicker_BrowseByTouch)

/* func_ov140_0229ab28: the hosts read again: when their number changed, it is drawn and the
 * rows filled again; when only a row's entries changed, the rows' colours are set again. */
void HostPicker_RefreshHosts(HostPicker *self)
{
    int count = HostPicker_CountHosts(self);
    if (count != self->host_count) {
        self->host_count = (u8) count;
        HostPicker_ShowHostCount(self);
        HostPicker_FillRows(self);
        HostPicker_FadeRows(self, HOST_PICKER_FADE_STEPS);
    } else if (HostPicker_RefreshEntries(self)) {
        HostPicker_FadeRows(self, HOST_PICKER_FADE_STEPS);
    }
}
CLEAN_AS(func_ov140_0229ab28, HostPicker_RefreshHosts)

/* func_ov140_0229ab70: the rows' OBJ files loaded, and the panel's text colours. */
void HostPicker_LoadObjFiles(HostPicker *self)
{
    ResRows_LoadObjFiles(&self->rows);
    ButtonPanel_LoadTextColors(&self->panel);
}
CLEAN_AS(func_ov140_0229ab70, HostPicker_LoadObjFiles)

/* func_ov140_0229ab94: the rows' background loaded and cleared, the screen read and its rows
 * marked. */
void HostPicker_LoadBackground(HostPicker *self)
{
    ResRows_LoadBg(&self->rows);
    ResRows_ClearRows(&self->rows);
    RomFile_Read(data_ov140_0229b5b4, self->screen, sizeof(self->screen));
    HostPicker_MarkRows(self);
}
CLEAN_AS(func_ov140_0229ab94, HostPicker_LoadBackground)

/* func_ov140_0229abcc: the sub screen's background mode 0; layers 6, 4 and 3 at priority 2,
 * each with its control reset. */
void HostPicker_SetUpLayers(void)
{
    DisplayShadow_SetSubBgMode(0);
    DisplayLayer_SetPriority(6, 2);
    DisplayLayer_SetBgControl(6, 0, 0, 0);
    DisplayLayer_SetPriority(4, 2);
    DisplayLayer_SetBgControl(4, 0, 0, 0);
    DisplayLayer_SetPriority(3, 2);
    DisplayLayer_SetBgControl(3, 0, 0, 0);
}
CLEAN_AS(func_ov140_0229abcc, HostPicker_SetUpLayers)

/* func_ov140_0229ac18: the frame's end: the screen and the rows' palette queued when changed. */
void HostPicker_EndFrame(HostPicker *self)
{
    HostPicker_QueueScreen(self);
    ResRows_QueuePalette(&self->rows);
}
CLEAN_AS(func_ov140_0229ac18, HostPicker_EndFrame)

/* func_ov140_0229ac34: the frame's start: the screen's task ended, the panel's texts closed,
 * the rows' labels given back and the scene's labels closed. */
void HostPicker_BeginFrame(HostPicker *self)
{
    LayerTask_End(&self->screen_task);
    ButtonPanel_CloseTexts(&self->panel);
    ResRows_Teardown(&self->rows);
    HostPicker_CloseLabels(self);
}
CLEAN_AS(func_ov140_0229ac34, HostPicker_BeginFrame)

/* func_ov140_0229ac68 */
void HostPicker_EndInteractiveFrame(HostPicker *self)
{
    HostPicker_EndFrame(self);
}
CLEAN_AS(func_ov140_0229ac68, HostPicker_EndInteractiveFrame)

/* func_ov140_0229ac70: the frame's start, then the cursor sprite updated. */
void HostPicker_BeginInteractiveFrame(HostPicker *self)
{
    HostPicker_BeginFrame(self);
    host_update_sprite(&self->cursor_sprite);
}
CLEAN_AS(func_ov140_0229ac70, HostPicker_BeginInteractiveFrame)

/* func_ov140_0229ac8c: the members torn down: the panel's texts closed, the rows ended, the
 * screen's task ended and the labels closed. */
void HostPicker_Teardown(HostPicker *self)
{
    ButtonPanel_CloseTexts(&self->panel);
    ResRows_End(&self->rows);
    LayerTask_End(&self->screen_task);
    HostPicker_CloseLabels(self);
}
CLEAN_AS(func_ov140_0229ac8c, HostPicker_Teardown)

/* func_ov140_0229acc0: the setup: no flags, the rows opened on layer 6 (message 0x7f), every
 * row and place empty, nothing selected, the cancel button lit and the next page button not,
 * the cursor on the first row of the first page. */
void HostPicker_Setup(HostPicker *self)
{
    self->flags = 0;
    ResRows_Open(&self->rows, 6, 0x7f);
    for (int row = 0; row < HOST_PICKER_ROWS; row++) {
        self->row_used[row] = 0;
        self->row_entries[row] = 0;
    }
    for (int i = 0; i < HOST_PICKER_FRIENDS; i++) {
        self->order[i] = HOST_PICKER_NO_ORDER;
    }
    HostPicker_Select(self, -1);
    self->cancel_palette = HOST_PICKER_PAL_LIT;
    self->page_palette = HOST_PICKER_PAL_UNLIT;
    self->cursor = HOST_PICKER_FIRST_ROW;
    self->page = 0;
    self->last_page = 0;
}
CLEAN_AS(func_ov140_0229acc0, HostPicker_Setup)

/* func_ov140_0229ad4c: layer 6 scrolled with the wipe, and the wipe's y kept and answered. */
int HostPicker_ScrollWithWipe(HostPicker *self)
{
    MenuScene_ScrollWipe(host_scene(self), 6, 0, 0);
    int y = MenuScene_WipeOffsetY(host_scene(self));
    self->wipe_y = y;
    return y;
}
CLEAN_AS(func_ov140_0229ad4c, HostPicker_ScrollWithWipe)

/* func_ov140_0229ad6c (state 4): the wipe out stepped; at its end layer 6 hidden and the scene
 * deleted (phase 5, answering MenuScene_SetPhase's answer); before, the layer follows it
 * (answering the wipe's y). */
int HostPicker_WipeOut(HostPicker *self)
{
    if (MenuScene_StepWipe(host_scene(self), 0) != 0) {
        DisplayLayer_HideAndResetScroll(6);
        return (int) (uintptr_t) MenuScene_SetPhase(host_scene(self), 5);
    }
    return HostPicker_ScrollWithWipe(self);
}
CLEAN_AS(func_ov140_0229ad6c, HostPicker_WipeOut)

/* func_ov140_0229ad98 (state 3): the parent told the menu closes, the wipe out started on
 * window 2 (layer 8, margin 0x30), the layer following it; state 4. */
void HostPicker_StartWipeOut(HostPicker *self)
{
    MenuDispatch_SetMode(host_parent(self), HOST_PICKER_PARENT_CLOSE, 1);
    MenuScene_StartWipeOnWindow2(host_scene(self), 8, 0, 0, 0x30);
    HostPicker_ScrollWithWipe(self);
    MenuScene_SetState(host_scene(self), HOST_PICKER_STATE_WIPE_OUT);
}
CLEAN_AS(func_ov140_0229ad98, HostPicker_StartWipeOut)

/* func_ov140_0229add0 (state 2): the wipe in stepped; at its end the scene goes interactive
 * (phase 2) on the list. The layer follows the wipe. */
void HostPicker_WipeIn(HostPicker *self)
{
    if (MenuScene_StepWipeBack(host_scene(self), 0) != 0) {
        MenuScene_SetPhase(host_scene(self), 2);
        HostPicker_Resume(self);
    }
    HostPicker_ScrollWithWipe(self);
}
CLEAN_AS(func_ov140_0229add0, HostPicker_WipeIn)

/* func_ov140_0229adf8 (state 1): the list set up and its first page's rows filled and shown,
 * the wipe in started covered on window 2 (layer 8, 4 frames, margin 0x30), layer 6 shown and
 * following it, the scene drawn; state 2. */
void HostPicker_StartWipeIn(HostPicker *self)
{
    HostPicker_InitList(self);
    HostPicker_FillRows(self);
    HostPicker_FadeRows(self, HOST_PICKER_FADE_STEPS);
    MenuScene_StartWipeCoveredOnWindow2(host_scene(self), 8, 4, 0, 0x30);
    DisplayLayer_Show(6);
    HostPicker_ScrollWithWipe(self);
    HostPicker_SetFlags(self, HOST_PICKER_FLAG_DRAWN);
    MenuScene_SetState(host_scene(self), HOST_PICKER_STATE_WIPE_IN);
}
CLEAN_AS(func_ov140_0229adf8, HostPicker_StartWipeIn)

/* func_ov140_0229ae44 (state 0): the layers set up, the background and the OBJ files loaded,
 * the rows' headings made; state 1. */
void HostPicker_StartSetup(HostPicker *self)
{
    HostPicker_SetUpLayers();
    HostPicker_LoadBackground(self);
    HostPicker_LoadObjFiles(self);
    ResRows_MakeHeadings(&self->rows);
    MenuScene_SetState(host_scene(self), HOST_PICKER_STATE_START_WIPE_IN);
}
CLEAN_AS(func_ov140_0229ae44, HostPicker_StartSetup)

/* func_ov140_0229ae74 (vtable slot 0x5c, phase 5): main told whether a friend was picked and,
 * if so, which entry of the friend list; GroupParams' 0xc80 and 0xc88 cleared; the scene asks
 * to be deleted.
 * QUIRK: the byte before the row entries is handed when confirming with no row selected, which
 * the confirm button's palette does not let happen. */
int HostPicker_End(HostPicker *self)
{
    if (HostPicker_TestFlags(self, HOST_PICKER_FLAG_CANCELLED) != 0) {
        GroupParams_SetC4C(0);
    } else {
        GroupParams_SetC4C(1);
        GroupParams_SetArg(((const u8 *) (const void *) self)[offsetof(HostPicker, row_friend) + self->selected]);
    }
    GroupParams_ClearC80C88();
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov140_0229ae74, HostPicker_End)

/* func_ov140_0229aeb8 (vtable slot 0x58, phase 4): nothing. */
int HostPicker_Phase4Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov140_0229aeb8, HostPicker_Phase4Idle)

/* func_ov140_0229aebc (vtable slot 0x54, phase 3): nothing. */
int HostPicker_Phase3Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov140_0229aebc, HostPicker_Phase3Idle)

/* Obj_ov140_0229b404::func_ov140_0229aec0 (vtable slot 0x50, phase 2): a frame of the scene in
 * use: its start, its sub state and its end. Answers 1. */
int HostPicker_RunInteractive(HostPicker *self)
{
    HostPicker_BeginInteractiveFrame(self);
    HostPicker_RunSubState(self);
    HostPicker_EndInteractiveFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov140_0229b40419func_ov140_0229aec0Ev, HostPicker_RunInteractive)

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants. */
extern u32 data_ov140_0229b5e0; /* the sub states' guard */
extern u32 data_ov140_0229b5e4; /* the states' guard */
extern MemberPointer data_ov140_0229b5e8[HOST_PICKER_STATES];
extern MemberPointer data_ov140_0229b610[HOST_PICKER_SUB_STATES];
extern const MemberPointer data_ov140_0229b308, data_ov140_0229b318, data_ov140_0229b320, data_ov140_0229b328,
    data_ov140_0229b330, data_ov140_0229b338, data_ov140_0229b348, data_ov140_0229b350, data_ov140_0229b358,
    data_ov140_0229b360, data_ov140_0229b368, data_ov140_0229b370, data_ov140_0229b378;

/* Obj_ov140_0229b404::func_ov140_0229aedc: the sub state's function (HostPickerSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 8; the game reads past the table for others. */
void HostPicker_RunSubState(HostPicker *self)
{
    static const MemberPointer *const sub_states[HOST_PICKER_SUB_STATES] = {
        &data_ov140_0229b338, &data_ov140_0229b330, &data_ov140_0229b378, &data_ov140_0229b368,
        &data_ov140_0229b318, &data_ov140_0229b348, &data_ov140_0229b308, &data_ov140_0229b320,
    };
    MemberTable_InitOnce(&data_ov140_0229b5e0, data_ov140_0229b610, sub_states, HOST_PICKER_SUB_STATES);
    MemberPointer_CallVoid(&data_ov140_0229b610[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov140_0229b40419func_ov140_0229aedcEv, HostPicker_RunSubState)

/* func_ov140_0229af98 (vtable slot 0x4c, phase 1): a frame of the scene's states
 * (HostPickerState) between the frame's start and end, through the table of member functions
 * (filled once from its constants, before the frame's start). Answers 1.
 * REQUIRES: the state is below 5; the game reads past the table for others. */
int HostPicker_RunState(HostPicker *self)
{
    static const MemberPointer *const states[HOST_PICKER_STATES] = {
        &data_ov140_0229b370, &data_ov140_0229b328, &data_ov140_0229b360, &data_ov140_0229b358, &data_ov140_0229b350,
    };
    MemberTable_InitOnce(&data_ov140_0229b5e4, data_ov140_0229b5e8, states, HOST_PICKER_STATES);
    HostPicker_BeginFrame(self);
    MemberPointer_CallVoid(&data_ov140_0229b5e8[self->base.state], self);
    HostPicker_EndFrame(self);
    return 1;
}
CLEAN_AS(func_ov140_0229af98, HostPicker_RunState)

/* An OBJ cell of the scene drawn on the sub screen at (0x80, y), in `palette` (-1: its own). */
static void host_draw_cell(const OamEntry *cells, int y, int palette)
{
    OamBuffer_DrawCell(1, cells, 0x80, y, palette, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* func_ov140_0229b038 (vtable slot 0x24): the cursor sprite drawn while the keys are in use;
 * then, while the scene is drawn (else answers 0): the panel; the rows' frame, the selected
 * row's mark and the buttons' frame; the three buttons in their palettes; the rows; and, but
 * while the page changes, each row's icon of its host's entries. All are moved by the wipe's y
 * kept. Answers 1.
 * REQUIRES: a row's entries are 4 or fewer; the game reads past the icons' table for more. */
int HostPicker_Draw(HostPicker *self)
{
    if (StateFlags_Test2()) {
        Glider_DrawWrapped(&self->cursor_sprite);
    }
    if (!HostPicker_TestFlags(self, HOST_PICKER_FLAG_DRAWN)) {
        return 0;
    }
    ButtonPanel_Draw(&self->panel, self->panel_y);
    int y = self->wipe_y + 0x60;
    host_draw_cell(data_ov140_0229b3a4, y, -1);
    unsigned int rows = (unsigned int) (uintptr_t) &self->rows;
    const OamEntry *page_cells = (const OamEntry *) (uintptr_t) ResRows_Cells(rows, 5);
    const OamEntry *cancel_cells = (const OamEntry *) (uintptr_t) ResRows_Cells(rows, 6);
    const OamEntry *confirm_cells = (const OamEntry *) (uintptr_t) ResRows_Cells(rows, 7);
    if (self->selected != -1) {
        host_draw_cell(data_ov140_0229b3cc, y + self->selected * 0x10, -1);
    }
    host_draw_cell(data_ov140_0229b464, y, -1);
    host_draw_cell(page_cells, y, (int) self->page_palette);
    host_draw_cell(cancel_cells, y, (int) self->cancel_palette);
    host_draw_cell(confirm_cells, y, (int) self->confirm_palette);
    ResRows_DrawAt(&self->rows, 0, self->wipe_y);
    if (HostPicker_TestFlags(self, HOST_PICKER_FLAG_PAGING)) {
        return 1;
    }
    for (int row = 0; row < HOST_PICKER_ROWS; row++) {
        const OamEntry *icon = (const OamEntry *) (uintptr_t) data_ov140_0229b390[self->row_entries[row]];
        if (icon != NULL) {
            host_draw_cell(icon, y, -1);
        }
        y += 0x10;
    }
    return 1;
}
CLEAN_AS(func_ov140_0229b038, HostPicker_Draw)

/* func_ov140_0229b22c (vtable slot 0x0c): the scene closes: the parent told and the members
 * torn down. Answers 1. */
int HostPicker_Close(HostPicker *self)
{
    MenuDispatch_ChildClosed(host_parent(self));
    HostPicker_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov140_0229b22c, HostPicker_Close)

/* func_ov140_0229b248 (vtable slot 0x00): the scene starts: its setup, state 0 (set directly)
 * and phase 0. Answers 1. */
int HostPicker_Start(HostPicker *self)
{
    HostPicker_Setup(self);
    self->base.state = HOST_PICKER_STATE_START_SETUP;
    MenuScene_SetPhase(host_scene(self), 0);
    return 1;
}
CLEAN_AS(func_ov140_0229b248, HostPicker_Start)

/* func_ov140_0229b268 (named by the profile at 0x0229b310): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the labels by __cxa_vec_ctor. */
HostPicker *HostPicker_New(void)
{
    HostPicker *self = MenuScene_Alloc(sizeof(HostPicker));
    if (self != NULL) {
        MenuScene_Construct(&self->base);
        self->base.vtable = data_ov140_0229b404;
        ResRows_Construct(&self->rows);
        Glider0_Construct(&self->cursor_sprite);
        ButtonPanel_Construct(&self->panel);
        LayerTask_Construct(&self->screen_task);
        __cxa_vec_ctor(self->labels, HOST_PICKER_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                       (void (*)(void *))(uintptr_t) func_02070be8);
    }
    return self;
}
CLEAN_AS(func_ov140_0229b268, HostPicker_New)
