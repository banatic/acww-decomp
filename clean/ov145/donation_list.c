/* The museum donation list of overlay 145 (donation_list.h): its destructors, its flags, the
 * fade of the text colour, the cursor, the tabs, the list's rows and its scrolling. */
#include "donation_list.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "autoload_2/approach.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/group_params.h"
#include "main/museum_record.h"
#include "main/name_texts.h"
#include "main/player_id.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "main/text_base.h"
#include "ov002/key_repeat.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(DonationList, wipe_y) == 0x94, "wipe y");
static_assert(offsetof(DonationList, scroll) == 0x9c && offsetof(DonationList, handle_y) == 0xa8, "scroll");
static_assert(offsetof(DonationList, flags) == 0xb4 && offsetof(DonationList, counts) == 0xb8, "flags");
static_assert(offsetof(DonationList, tab) == 0xc0 && offsetof(DonationList, fade_mode) == 0xc6, "tab");
static_assert(sizeof(Glider) == 0x64 && offsetof(DonationList, cursor_sprite) == 0xc8, "cursor sprite");
static_assert(sizeof(PushButton) == 0x48 && offsetof(DonationList, handle) == 0x12c, "handle");
static_assert(offsetof(DonationList, panel) == 0x174 && offsetof(DonationList, labels) == 0x340, "panel");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(DonationList, list_task) == 0xad8, "labels");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(DonationList, fossils) == 0xb44, "tasks");
static_assert(offsetof(DonationList, fish) == 0xbac && offsetof(DonationList, insects) == 0xc1c, "fish");
static_assert(offsetof(DonationList, paintings) == 0xc8c && offsetof(DonationList, shown) == 0xcb4, "paintings");
static_assert(offsetof(DonationList, row_screen) == 0xcc6 && offsetof(DonationList, list_screen) == 0x14c6, "screens");
static_assert(offsetof(DonationList, frame_screen) == 0x1cc6 && offsetof(DonationList, palette_file) == 0x24c6, "frame");
static_assert(offsetof(DonationList, palette) == 0x24e6 && sizeof(DonationList) == 0x2508, "size (func_ov145_0229ace8)");
static_assert(sizeof(NameText) == 0x28 && sizeof(PlayerIdText) == 0x20, "row texts");

/* The item code of no item (main/item_code.h). */
#define DONATION_NO_ITEM 0xfff1

/* The scene's vtable. */
extern const u8 data_ov145_0229ae00[];

/* The museum's record (main/museum_record.h). */
extern MuseumRecord data_021f38f8;

/* The pad (autoload_2/input.h): up and down move the handle while A is held. */
extern PadState data_021fbe40;
#define DONATION_PAD_UP 0x40
#define DONATION_PAD_DOWN 0x80

/* The table of the tabs' lists DonationList_TabItems fills once (its guard's bit 0 says so). */
extern u32 data_ov145_0229afa0;
extern u32 data_ov145_0229afac[DONATION_TABS];

/* The labels' destructor, handed to __cxa_vec_cleanup (so the game's symbol). */
extern void func_02070be8(void *label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The SDK's 16-bit copy and fill. */
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

/* The list: layer 4, scrolled 0x18 pixels less than `scroll`; its texts' palette 3, rows
 * past the end of a short list in palette 4; the blank screen entry. */
#define DONATION_LIST_LAYER 4
#define DONATION_LIST_SCROLL_OFFSET 0x18
#define DONATION_TEXT_PALETTE 3
#define DONATION_EMPTY_PALETTE 4
#define DONATION_BLANK_ENTRY 0x10
#define DONATION_SCREEN_RING_ROWS 16
#define DONATION_ROW_ENTRIES 0x40 /* two tile rows of 32 */

/* The frame: layer 6. */
#define DONATION_FRAME_LAYER 6

/* The colours of the text that blend: from colour 7 of the file (level 0) to its colour 15
 * (DONATION_FADE_FULL), into colour 15. */
#define DONATION_COLOUR_FROM 7
#define DONATION_COLOUR_TO 15

/* The tabs' place: centred at x 0x94 - 36 * tab, y 0xad; touched in 32 pixels from x
 * 0x84 - 36 * tab and in y 0x9d-0xbc. */
#define DONATION_TAB_X 0x94
#define DONATION_TAB_Y 0xad
#define DONATION_TAB_STEP 0x24
#define DONATION_TAB_TOUCH_LEFT 0x84
#define DONATION_TAB_TOUCH_WIDTH 0x20
#define DONATION_TAB_TOUCH_TOP 0x9d
#define DONATION_TAB_TOUCH_BOTTOM 0xbd

/* The panel's close button, and the cursor's place when it is nowhere known. */
#define DONATION_CLOSE_BUTTON 6
#define DONATION_NOWHERE_X 0x80
#define DONATION_NOWHERE_Y 0x60

/* The handle: drawn at x 0x63 and y handle_y - 0x4b from the wipe's; the track's touch is 0x1d
 * pixels below the handle's y; it moves 4 a frame by the keys, 8 towards a touch of the
 * track, and sounds every 4 pixels. */
#define DONATION_HANDLE_X 0x63
#define DONATION_HANDLE_Y_OFFSET 0x4b
#define DONATION_TRACK_TOUCH_OFFSET 0x1d
#define DONATION_HANDLE_KEY_STEP 4
#define DONATION_HANDLE_TRACK_STEP 8
#define DONATION_HANDLE_CUE_DISTANCE 4
#define DONATION_SCROLL_STEP 4

/* The row texts: the item's name in a box of style 4 at 0x184 + 0x1a * place, 0xd wide; the
 * giver's at 0xf4 + 0x10 * place, 8 wide; colours 15 and 7. Message 0xcc of the menu's when
 * the giver has no name to show. */
#define DONATION_TEXT_STYLE 4
#define DONATION_NAME_BASE 0x184
#define DONATION_NAME_STEP 0x1a
#define DONATION_NAME_WIDTH 0xd
#define DONATION_GIVER_BASE 0xf4
#define DONATION_GIVER_STEP 0x10
#define DONATION_GIVER_WIDTH 8
#define DONATION_TEXT_COLOUR 0xf
#define DONATION_TEXT_SHADOW 7
#define DONATION_NO_GIVER_MESSAGE 0xcc

/* The sounds (main/sound.h): a tab chosen. */
#define DONATION_SOUND_TAB 0xc

static MenuScene *donation_base(DonationList *self)
{
    return &self->base;
}

static DualCellSprite *donation_handle_cells(DonationList *self)
{
    /* The handle's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->handle;
}

/* The cursor sprite's update through its class (vtable slot 3). */
static void donation_update_cursor_sprite(DonationList *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

/* func_ov145_022995a0 (vtable slot 0x40): the scene's vtable back, the labels, the panel, the
 * handle, the cursor sprite and the base destroyed (the layer tasks have no destructor). */
DonationList *DonationList_Destroy(DonationList *self)
{
    self->base.vtable = data_ov145_0229ae00;
    __cxa_vec_cleanup(self->labels, DONATION_LABELS, sizeof(TextLabel), func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    PushButton_Destroy(&self->handle);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(donation_base(self));
    return self;
}
CLEAN_AS(func_ov145_022995a0, DonationList_Destroy)

/* func_ov145_022995f0 (vtable slot 0x44): destroyed as above, then freed. */
DonationList *DonationList_Delete(DonationList *self)
{
    self->base.vtable = data_ov145_0229ae00;
    __cxa_vec_cleanup(self->labels, DONATION_LABELS, sizeof(TextLabel), func_02070be8);
    ButtonPanel_Destroy(&self->panel);
    PushButton_Destroy(&self->handle);
    Glider0_Destroy(&self->cursor_sprite);
    MenuScene_DestroyBase(donation_base(self));
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov145_022995f0, DonationList_Delete)

/* func_ov145_02299648 */
void DonationList_ClearFlags(DonationList *self, unsigned short flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov145_02299648, DonationList_ClearFlags)

/* func_ov145_02299658 */
void DonationList_SetFlags(DonationList *self, unsigned short flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov145_02299658, DonationList_SetFlags)

/* func_ov145_02299668: 1 when any of `flags` is set. */
int DonationList_TestFlags(DonationList *self, int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov145_02299668, DonationList_TestFlags)

/* func_ov145_0229967c: a frame of the fade (DonationListFade). Fading out, the level goes down
 * a step a frame; at 0 the fade turns to fading in and the selected tab is shown. Fading in, it
 * goes up to DONATION_FADE_FULL, where the fade ends (that frame blends nothing). Every other
 * frame of a fade blends the colour at the level.
 * QUIRK: a fade mode above 2 blends every frame and never ends; the game sets none. */
void DonationList_StepFade(DonationList *self)
{
    switch (self->fade_mode) {
        case DONATION_FADE_NONE:
            return;
        case DONATION_FADE_OUT:
            if (self->fade != 0) {
                self->fade--;
            } else {
                self->fade_mode = DONATION_FADE_IN;
                DonationList_ShowTab(self, self->selected_tab);
            }
            break;
        case DONATION_FADE_IN:
            if (self->fade < DONATION_FADE_FULL) {
                self->fade++;
            } else {
                self->fade_mode = DONATION_FADE_NONE;
                return;
            }
            break;
        default:
            break;
    }
    DonationList_BlendTextColour(self, self->fade);
}
CLEAN_AS(func_ov145_0229967c, DonationList_StepFade)

/* The red, green and blue (0-31) of a BGR555 colour. */
static int colour_red(u16 colour)
{
    return colour & 0x1f;
}

static int colour_green(u16 colour)
{
    return (colour & 0x3e0) >> 5;
}

static int colour_blue(u16 colour)
{
    return (colour & 0x7c00) >> 10;
}

/* func_ov145_022996f0: the file's palette copied to `palette` (MIi_CpuCopy16), its colour 15
 * made the blend of the file's colours 7 and 15 at `level` thirds of the way to 15 (each
 * channel truncated to 8 bits), and the palette queued for layer 4's palette 3. */
void DonationList_BlendTextColour(DonationList *self, int level)
{
    MIi_CpuCopy16(self->palette_file, self->palette, sizeof(self->palette));
    u16 from = self->palette_file[DONATION_COLOUR_FROM];
    u16 to = self->palette_file[DONATION_COLOUR_TO];
    int rest = DONATION_FADE_FULL - level;
    u8 red = (u8) ((colour_red(to) * level + colour_red(from) * rest) / DONATION_FADE_FULL);
    u8 green = (u8) ((colour_green(to) * level + colour_green(from) * rest) / DONATION_FADE_FULL);
    u8 blue = (u8) ((colour_blue(to) * level + colour_blue(from) * rest) / DONATION_FADE_FULL);
    self->palette[DONATION_COLOUR_TO] = (u16) (red | (green << 5) | (blue << 10));
    LayerTask_QueuePalette(&self->palette_task, (int) (uintptr_t) self->palette, DONATION_LIST_LAYER, DONATION_TEXT_PALETTE);
}
CLEAN_AS(func_ov145_022996f0, DonationList_BlendTextColour)

/* func_ov145_022997d0: the cursor moved by the keys the repeat took (`keys`). On a tab, left
 * goes to the next tab (up to 3), right to the one before or from tab 0 to the close button, and
 * up to the handle when the list scrolls. On the close button, up goes to the handle (when the
 * list scrolls) and left to tab 0; on the handle, down goes to the close button and left to tab
 * 0. Answers 1 when the cursor moved. */
int DonationList_MoveCursor(DonationList *self, u32 keys)
{
    u8 before = self->cursor;

    if (before < DONATION_PLACE_CLOSE) {
        if (KeyRepeat_HasLeft((int) keys)) {
            if (self->cursor < DONATION_TABS - 1) {
                self->cursor++;
            }
        } else if (KeyRepeat_HasRight((int) keys)) {
            if (self->cursor != 0) {
                self->cursor--;
            } else {
                self->cursor = DONATION_PLACE_CLOSE;
            }
        } else if (KeyRepeat_HasUp((int) keys)) {
            if (self->max_scroll > 0) {
                self->cursor = DONATION_PLACE_HANDLE;
            }
        }
    } else if (before == DONATION_PLACE_CLOSE) {
        if (KeyRepeat_HasUp((int) keys)) {
            if (self->max_scroll > 0) {
                self->cursor = DONATION_PLACE_HANDLE;
            }
        } else if (KeyRepeat_HasLeft((int) keys)) {
            self->cursor = DONATION_PLACE_TAB;
        }
    } else if (before == DONATION_PLACE_HANDLE) {
        if (KeyRepeat_HasDown((int) keys)) {
            self->cursor = DONATION_PLACE_CLOSE;
        } else if (KeyRepeat_HasLeft((int) keys)) {
            self->cursor = DONATION_PLACE_TAB;
        }
    }
    return before != self->cursor;
}
CLEAN_AS(func_ov145_022997d0, DonationList_MoveCursor)

/* func_ov145_022998c4: the tab under the touch at (x, y), or DONATION_NO_TAB. */
int DonationList_TabAtTouch(DonationList *self, int x, int y)
{
    (void) self;
    if (y >= DONATION_TAB_TOUCH_TOP && y < DONATION_TAB_TOUCH_BOTTOM) {
        for (int tab = 0; tab < DONATION_TABS; tab++) {
            int left = DONATION_TAB_TOUCH_LEFT - DONATION_TAB_STEP * tab;
            if (left <= x && x < left + DONATION_TAB_TOUCH_WIDTH) {
                return tab;
            }
        }
    }
    return DONATION_NO_TAB;
}
CLEAN_AS(func_ov145_022998c4, DonationList_TabAtTouch)

/* func_ov145_022998f0: a place chosen. A tab other than the selected one sounds and is selected
 * (the fade shows it); the close button starts the close; the handle is pressed (with its
 * sound) and moved by the keys (sub state 4). Answers 1 for the last two. */
int DonationList_Choose(DonationList *self, unsigned int place)
{
    if (place < DONATION_PLACE_CLOSE) {
        if (place != self->selected_tab) {
            SoundSys_PlaySe(DONATION_SOUND_TAB);
            DonationList_SelectTab(self, (unsigned char) place);
        }
        return 0;
    }
    switch (place) {
        case DONATION_PLACE_CLOSE:
            DonationList_StartClose(self);
            return 1;
        case DONATION_PLACE_HANDLE:
            PushButton_Press(&self->handle);
            PushButton_PressCue(&self->handle);
            MenuScene_SetSubState(donation_base(self), DONATION_SUB_HANDLE_KEYS);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov145_022998f0, DonationList_Choose)

/* func_ov145_02299954: another tab selected starts the fade out. */
void DonationList_SelectTab(DonationList *self, unsigned char tab)
{
    if (tab != self->selected_tab) {
        self->selected_tab = tab;
        self->fade_mode = DONATION_FADE_OUT;
    }
}
CLEAN_AS(func_ov145_02299954, DonationList_SelectTab)

/* func_ov145_0229996c: another tab's list shown, from its top: the scroll's range set by its
 * rows (8 fit), the list at 0 and the handle placed for it. */
void DonationList_ShowTab(DonationList *self, unsigned char tab)
{
    if (self->tab == tab) {
        return;
    }
    self->tab = tab;
    self->max_scroll = (DonationList_TabCount(self) - 8) * DONATION_ROW_HEIGHT;
    if (self->max_scroll < 0) {
        self->max_scroll = 0;
    }
    DonationList_SetScroll(self, 0);
    self->scroll_target = 0;
    DonationList_HandleFromScroll(self);
    DonationList_PlaceHandle(self);
}
CLEAN_AS(func_ov145_0229996c, DonationList_ShowTab)

/* func_ov145_022999c4: where row `row` (0 for a negative one) of the shown tab's list is. The
 * lists' addresses are kept in a static table of the overlay, filled the first time.
 * QUIRK: the table keeps the addresses of the scene it was filled for, until the overlay's
 * .bss is cleared (when the overlay is loaded again).
 * REQUIRES: `tab` is below 4 (the game reads past the table otherwise; tests/native/known.txt). */
u16 *DonationList_TabItems(DonationList *self, int row)
{
    if ((data_ov145_0229afa0 & 1) == 0) {
        data_ov145_0229afac[DONATION_TAB_PAINTINGS] = (u32) (uintptr_t) self->paintings;
        data_ov145_0229afac[DONATION_TAB_FISH] = (u32) (uintptr_t) self->fish;
        data_ov145_0229afac[DONATION_TAB_INSECTS] = (u32) (uintptr_t) self->insects;
        data_ov145_0229afac[DONATION_TAB_FOSSILS] = (u32) (uintptr_t) self->fossils;
        data_ov145_0229afa0 |= 1;
    }
    if (row < 0) {
        row = 0;
    }
    return (u16 *) (uintptr_t) data_ov145_0229afac[self->tab] + row;
}
CLEAN_AS(func_ov145_022999c4, DonationList_TabItems)

/* func_ov145_02299a24: the rows of the shown tab's list.
 * QUIRK: with `tab` 4 (set for a moment by DonationList_StartSetup) it reads the next two bytes,
 * `tab` and `selected_tab`. */
short DonationList_TabCount(DonationList *self)
{
    s16 count;
    memcpy(&count, (const u8 *) self + offsetof(DonationList, counts) + self->tab * sizeof(u16), sizeof(count));
    return count;
}
CLEAN_AS(func_ov145_02299a24, DonationList_TabCount)

/* func_ov145_02299a34: a frame of the scroll: 4 pixels towards its target, then the list and the
 * handle follow. */
void DonationList_StepScroll(DonationList *self)
{
    if (self->scroll == self->scroll_target) {
        return;
    }
    if (self->scroll > self->scroll_target) {
        self->scroll -= DONATION_SCROLL_STEP;
        if (self->scroll < self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    } else {
        self->scroll += DONATION_SCROLL_STEP;
        if (self->scroll > self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    }
    DonationList_SetScroll(self, self->scroll);
    DonationList_HandleFromScroll(self);
}
CLEAN_AS(func_ov145_02299a34, DonationList_StepScroll)

/* func_ov145_02299aac: the list's screen given its palettes (3, and 4 for the rows below a list
 * of fewer than 9) and queued for layer 4; once queued, its flag is cleared. */
void DonationList_UploadListScreen(DonationList *self)
{
    ScreenMap_SetPalette(self->list_screen, 0, 0, 31, 31, DONATION_TEXT_PALETTE);
    int count = DonationList_TabCount(self);
    if (count < DONATION_ROWS_IN_VIEW) {
        ScreenMap_SetPalette(self->list_screen, 0, count * 2, 31, 18, DONATION_EMPTY_PALETTE);
    }
    if (LayerTask_QueueScreen(&self->list_task, (int) (uintptr_t) self->list_screen, DONATION_LIST_LAYER,
                              sizeof(self->list_screen), 0) != 0) {
        DonationList_ClearFlags(self, DONATION_FLAG_LIST_DIRTY);
    }
}
CLEAN_AS(func_ov145_02299aac, DonationList_UploadListScreen)

/* func_ov145_02299b1c: the list's screen cleared to the blank entry, and the 9 rows from the
 * first one shown copied in from the row patterns (the 9 patterns in turn, row % 9) at their
 * places in the ring of 16 rows (row % 16); then queued (flag 8). */
void DonationList_BuildListScreen(DonationList *self)
{
    int pattern = (self->first_row + 9) % 9;
    int ring_row = self->first_row & (DONATION_SCREEN_RING_ROWS - 1);

    MIi_CpuClear16(DONATION_BLANK_ENTRY, self->list_screen, sizeof(self->list_screen));
    for (int i = 0; i < DONATION_ROWS_IN_VIEW; i++) {
        MIi_CpuCopy16(&self->row_screen[pattern * DONATION_ROW_ENTRIES], &self->list_screen[ring_row * DONATION_ROW_ENTRIES],
                      DONATION_ROW_ENTRIES * sizeof(u16));
        pattern++;
        if (pattern >= 9) {
            pattern = 0;
        }
        ring_row = (ring_row + 1) & (DONATION_SCREEN_RING_ROWS - 1);
    }
    DonationList_SetFlags(self, DONATION_FLAG_LIST_DIRTY);
}
CLEAN_AS(func_ov145_02299b1c, DonationList_BuildListScreen)

/* func_ov145_02299b94: the list scrolled to `scroll` pixels: layer 4 scrolled, the first row
 * shown set, the screen rebuilt and the texts to be refreshed (flag 4). */
void DonationList_SetScroll(DonationList *self, int scroll)
{
    self->scroll = scroll;
    DisplayLayer_SetScroll(DONATION_LIST_LAYER, 0, self->scroll - DONATION_LIST_SCROLL_OFFSET);
    /* the arithmetic shift of the ROM's code */
    self->first_row = (s16) (scroll >= 0 ? scroll / DONATION_ROW_HEIGHT : -((-(scroll + 1)) / DONATION_ROW_HEIGHT) - 1);
    DonationList_BuildListScreen(self);
    DonationList_SetFlags(self, DONATION_FLAG_TEXTS_DIRTY);
}
CLEAN_AS(func_ov145_02299b94, DonationList_SetScroll)

/* func_ov145_02299bd0: what the flags ask for at the frame's end: the list's screen queued
 * (flag 8), the frame's screen queued for layer 6 (flag 2, cleared once queued) and the texts
 * refreshed (flag 4, cleared first). */
void DonationList_UploadPending(DonationList *self)
{
    if (DonationList_TestFlags(self, DONATION_FLAG_LIST_DIRTY)) {
        DonationList_UploadListScreen(self);
    }
    if (DonationList_TestFlags(self, DONATION_FLAG_FRAME_DIRTY)) {
        if (LayerTask_QueueScreen(&self->frame_task, (int) (uintptr_t) self->frame_screen, DONATION_FRAME_LAYER,
                                  sizeof(self->frame_screen), 0) != 0) {
            DonationList_ClearFlags(self, DONATION_FLAG_FRAME_DIRTY);
        }
    }
    if (DonationList_TestFlags(self, DONATION_FLAG_TEXTS_DIRTY)) {
        DonationList_ClearFlags(self, DONATION_FLAG_TEXTS_DIRTY);
        DonationList_RefreshRows(self);
    }
}
CLEAN_AS(func_ov145_02299bd0, DonationList_UploadPending)

/* Two labels of a ring place opened and shown: the item's name and its giver's. */
static void donation_open_row(TextLabel *name, TextLabel *giver, int place)
{
    TextLabel_OpenStyledBox2(name, DONATION_TEXT_STYLE, place * DONATION_NAME_STEP + DONATION_NAME_BASE, DONATION_NAME_WIDTH,
                             DONATION_TEXT_COLOUR, DONATION_TEXT_SHADOW, 0);
    TextLabel_Show(name, 0, 0);
    TextLabel_OpenStyledBox2(giver, DONATION_TEXT_STYLE, place * DONATION_GIVER_STEP + DONATION_GIVER_BASE,
                             DONATION_GIVER_WIDTH, DONATION_TEXT_COLOUR, DONATION_TEXT_SHADOW, 0);
    TextLabel_Show(giver, 0, 0);
}

/* func_ov145_02299c40: the texts of the 9 rows from the first shown, each at its place in the
 * ring of 9 (row % 9). A row past either end of the list gets two empty labels (every time); a
 * row whose item is not the one its place shows gets the item's name and its giver's (or menu
 * message 0xcc when MuseumRecord_GiverName has none). Rows already shown get nothing. */
void DonationList_RefreshRows(DonationList *self)
{
    PlayerIdText giver_name;
    NameText item_name;

    PlayerIdText_Construct(&giver_name);
    NameText_Construct(&item_name);
    int row = self->first_row;
    const u16 *item = DonationList_TabItems(self, row);
    int place = (row + 9) % 9;
    int count = DonationList_TabCount(self);
    for (int i = 0; i < DONATION_ROWS_IN_VIEW; i++) {
        TextLabel *name = NULL;
        TextLabel *giver = NULL;
        if (row < 0 || row >= count) {
            self->shown[place] = DONATION_NO_ITEM;
            name = DonationList_NextLabel(self);
            TextBase_Clear(name);
            giver = DonationList_NextLabel(self);
            TextBase_Clear(giver);
        } else {
            if (*item != self->shown[place]) {
                u16 code;
                self->shown[place] = *item;
                name = DonationList_NextLabel(self);
                code = *item;
                NameText_SetItem(&item_name, &code);
                TextBase_Copy((TextBase *) (void *) name, (TextBase *) (void *) &item_name);
                giver = DonationList_NextLabel(self);
                code = *item;
                if (MuseumRecord_GiverName(&data_021f38f8, &giver_name, &code) != 0) {
                    TextBase_Copy((TextBase *) (void *) giver, (TextBase *) (void *) &giver_name);
                } else {
                    TextLabel_LoadMenuMessage(giver, (char) DONATION_NO_GIVER_MESSAGE);
                }
            }
            item++;
        }
        if (name != NULL) {
            donation_open_row(name, giver, place);
        }
        row++;
        place++;
        if (place >= DONATION_ROWS_IN_VIEW) {
            place = 0;
        }
    }
    NameText_Destruct(&item_name);
    PlayerIdText_Destruct(&giver_name);
}
CLEAN_AS(func_ov145_02299c40, DonationList_RefreshRows)

/* func_ov145_02299da4: none of the labels used yet this frame; all their boxes closed. */
void DonationList_CloseLabels(DonationList *self)
{
    self->labels_used = 0;
    for (int i = 0; i < DONATION_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov145_02299da4, DonationList_CloseLabels)

/* func_ov145_02299dd0: the next label of the frame; when all are used, the last one again. */
TextLabel *DonationList_NextLabel(DonationList *self)
{
    if (self->labels_used >= DONATION_LABELS) {
        return &self->labels[DONATION_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov145_02299dd0, DonationList_NextLabel)

/* func_ov145_02299e08: the cursor sprite's third animation of its set; once it ends, back to
 * the sub state this was called in (sub state 8). */
void DonationList_StartCursorAnim(DonationList *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_CURSOR_ANIM);
}
CLEAN_AS(func_ov145_02299e08, DonationList_StartCursorAnim)

/* func_ov145_02299e2c: the cursor sprite's second animation of its set: the place under the
 * cursor is chosen once it ends (sub state 7). */
void DonationList_StartPress(DonationList *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_PRESS);
}
CLEAN_AS(func_ov145_02299e2c, DonationList_StartPress)

/* func_ov145_02299e44: the cursor sprite's first animation of its set, and its update. */
void DonationList_ShowCursorFirstOfSet(DonationList *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    donation_update_cursor_sprite(self);
}
CLEAN_AS(func_ov145_02299e44, DonationList_ShowCursorFirstOfSet)

/* func_ov145_02299e60: the cursor sprite eased to (x, y) in 3 steps (with its cue); once there,
 * back to the sub state this was called in (sub state 6). */
void DonationList_GlideCursorTo(DonationList *self, int x, int y)
{
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_CURSOR_GLIDE);
}
CLEAN_AS(func_ov145_02299e60, DonationList_GlideCursorTo)

/* func_ov145_02299e90: the cursor sprite turned to its set B on the close button (else A) and
 * glided to the cursor. */
void DonationList_GlideToCursor(DonationList *self)
{
    if (self->cursor == DONATION_PLACE_CLOSE) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = DonationList_CursorX(self);
    int y = DonationList_CursorY(self);
    DonationList_GlideCursorTo(self, x, y);
}
CLEAN_AS(func_ov145_02299e90, DonationList_GlideToCursor)

/* func_ov145_02299ed0: the cursor sprite without an animation (hidden), and its update. */
void DonationList_HideCursorSprite(DonationList *self)
{
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_NONE);
    donation_update_cursor_sprite(self);
}
CLEAN_AS(func_ov145_02299ed0, DonationList_HideCursorSprite)

/* func_ov145_02299eec: the y of the cursor's place: the tabs', the close button's or the
 * handle's face. */
int DonationList_CursorY(DonationList *self)
{
    if (self->cursor < DONATION_PLACE_CLOSE) {
        return DONATION_TAB_Y;
    }
    switch (self->cursor) {
        case DONATION_PLACE_CLOSE:
            return ButtonPanel_ButtonY(&self->panel, DONATION_CLOSE_BUTTON);
        case DONATION_PLACE_HANDLE:
            return PushButton_FaceY(&self->handle);
        default:
            return DONATION_NOWHERE_Y;
    }
}
CLEAN_AS(func_ov145_02299eec, DonationList_CursorY)

/* func_ov145_02299f30: the x of the cursor's place. */
int DonationList_CursorX(DonationList *self)
{
    u8 cursor = self->cursor;
    if (cursor < DONATION_PLACE_CLOSE) {
        return DONATION_TAB_X - DONATION_TAB_STEP * cursor;
    }
    switch (cursor) {
        case DONATION_PLACE_CLOSE:
            return ButtonPanel_ButtonX(&self->panel, DONATION_CLOSE_BUTTON);
        case DONATION_PLACE_HANDLE:
            return PushButton_FaceX(&self->handle);
        default:
            return DONATION_NOWHERE_X;
    }
}
CLEAN_AS(func_ov145_02299f30, DonationList_CursorX)

/* func_ov145_02299f7c: the cursor sprite put at the cursor, in its set B on the close button
 * (else A), at the first animation of the set. */
void DonationList_ShowCursorSprite(DonationList *self)
{
    int x = DonationList_CursorX(self);
    int y = DonationList_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    if (self->cursor == DONATION_PLACE_CLOSE) {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    }
    DonationList_ShowCursorFirstOfSet(self);
}
CLEAN_AS(func_ov145_02299f7c, DonationList_ShowCursorSprite)

/* func_ov145_02299fc8: the insects given (group C). */
void DonationList_CollectInsects(DonationList *self)
{
    self->counts[DONATION_TAB_INSECTS] = (u16) DonationList_CollectEach(self, self->insects, MUSEUM_C_FIRST, MUSEUM_C_ITEMS);
}
CLEAN_AS(func_ov145_02299fc8, DonationList_CollectInsects)

/* func_ov145_02299fec: the fish given (group B). */
void DonationList_CollectFish(DonationList *self)
{
    self->counts[DONATION_TAB_FISH] = (u16) DonationList_CollectEach(self, self->fish, MUSEUM_B_FIRST, MUSEUM_B_ITEMS);
}
CLEAN_AS(func_ov145_02299fec, DonationList_CollectFish)

/* func_ov145_0229a010: the paintings given (group D). */
void DonationList_CollectPaintings(DonationList *self)
{
    self->counts[DONATION_TAB_PAINTINGS] =
        (u16) DonationList_CollectEvery4(self, self->paintings, MUSEUM_D_FIRST, MUSEUM_D_ITEMS);
}
CLEAN_AS(func_ov145_0229a010, DonationList_CollectPaintings)

/* func_ov145_0229a034: the fossils given (group A). */
void DonationList_CollectFossils(DonationList *self)
{
    self->counts[DONATION_TAB_FOSSILS] = (u16) DonationList_CollectEvery4(self, self->fossils, MUSEUM_A_FIRST, MUSEUM_A_ITEMS);
}
CLEAN_AS(func_ov145_0229a034, DonationList_CollectFossils)

/* func_ov145_0229a058: DonationList_Collect of codes 4 apart. */
int DonationList_CollectEvery4(DonationList *self, u16 *items, int first, int count)
{
    return DonationList_Collect(self, items, (unsigned short) first, count, 4);
}
CLEAN_AS(func_ov145_0229a058, DonationList_CollectEvery4)

/* func_ov145_0229a06c: DonationList_Collect of codes 1 apart. */
int DonationList_CollectEach(DonationList *self, u16 *items, int first, int count)
{
    return DonationList_Collect(self, items, (unsigned short) first, count, 1);
}
CLEAN_AS(func_ov145_0229a06c, DonationList_CollectEach)

/* func_ov145_0229a080: of the `count` codes from `first`, `step` apart (16-bit), those the
 * museum's record has as given, written in order to `items`. Answers how many. */
int DonationList_Collect(DonationList *self, u16 *items, unsigned short first, int count, int step)
{
    (void) self;
    int found = 0;
    u16 code = first;
    for (int i = 0; i < count; i++) {
        u16 item = code;
        if (MuseumRecord_IsGiven(&data_021f38f8, &item)) {
            items[found] = code;
            found++;
        }
        code = (u16) (code + step);
    }
    return found;
}
CLEAN_AS(func_ov145_0229a080, DonationList_Collect)

/* func_ov145_0229a0d0: when the list scrolls, the handle put where the scroll is, and drawn
 * there. */
void DonationList_HandleFromScroll(DonationList *self)
{
    if (self->max_scroll > 0) {
        self->handle_y = self->scroll * DONATION_HANDLE_RANGE / self->max_scroll;
        DonationList_PlaceHandle(self);
    }
}
CLEAN_AS(func_ov145_0229a0d0, DonationList_HandleFromScroll)

/* func_ov145_0229a0fc: the list scrolled at once to where the handle is (0 to max_scroll), and
 * that made the scroll's target. */
void DonationList_ScrollFromHandle(DonationList *self)
{
    int max_scroll = self->max_scroll;
    int scroll = self->handle_y * max_scroll / DONATION_HANDLE_RANGE;
    if (scroll < 0) {
        scroll = 0;
    }
    if (scroll > max_scroll) {
        scroll = max_scroll;
    }
    DonationList_SetScroll(self, scroll);
    self->scroll_target = scroll;
}
CLEAN_AS(func_ov145_0229a0fc, DonationList_ScrollFromHandle)

/* func_ov145_0229a134: the handle drawn at its y, moved with the wipe. */
void DonationList_PlaceHandle(DonationList *self)
{
    DualCellSprite_SetOffset(donation_handle_cells(self), DONATION_HANDLE_X,
                             self->wipe_y + (self->handle_y - DONATION_HANDLE_Y_OFFSET));
}
CLEAN_AS(func_ov145_0229a134, DonationList_PlaceHandle)

/* func_ov145_0229a15c: once the handle's animation has ended, the handle at rest. Answers 1
 * then. */
int DonationList_HandleReleased(DonationList *self)
{
    if (DualCellSprite_IsDone(donation_handle_cells(self))) {
        PushButton_ShowUp(&self->handle);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov145_0229a15c, DonationList_HandleReleased)

/* func_ov145_0229a184: the handle moved 4 pixels by up or down held (0 to 120); when it moved,
 * the list follows at once, the handle is drawn there and its scroll sound plays. */
void DonationList_MoveHandleByKeys(DonationList *self)
{
    int before = self->handle_y;
    if (data_021fbe40.held & DONATION_PAD_UP) {
        self->handle_y -= DONATION_HANDLE_KEY_STEP;
        if (self->handle_y < 0) {
            self->handle_y = 0;
        }
    } else if (data_021fbe40.held & DONATION_PAD_DOWN) {
        self->handle_y += DONATION_HANDLE_KEY_STEP;
        if (self->handle_y > DONATION_HANDLE_RANGE) {
            self->handle_y = DONATION_HANDLE_RANGE;
        }
    }
    if (before != self->handle_y) {
        DonationList_ScrollFromHandle(self);
        DonationList_PlaceHandle(self);
        PushButton_ScrollCue(&self->handle);
    }
}
CLEAN_AS(func_ov145_0229a184, DonationList_MoveHandleByKeys)

/* func_ov145_0229a210: the handle released (PushButton_Release's answer). */
int DonationList_ReleaseHandle(DonationList *self)
{
    return PushButton_Release(&self->handle);
}
CLEAN_AS(func_ov145_0229a210, DonationList_ReleaseHandle)

/* func_ov145_0229a220: the handle moved for the pen at y (0 to 120): on the track, it
 * approaches the pen 8 pixels a frame; dragged, it keeps its grab. The list follows at once,
 * the handle is drawn there, and its scroll sound plays each 4 pixels it has gone. */
void DonationList_MoveHandleTo(DonationList *self, int y, int on_track)
{
    int target;
    if (on_track) {
        target = y - DONATION_TRACK_TOUCH_OFFSET;
    } else {
        target = y + self->grab_dy;
    }
    if (target < 0) {
        target = 0;
    }
    if (target > DONATION_HANDLE_RANGE) {
        target = DONATION_HANDLE_RANGE;
    }
    if (on_track) {
        Approach_S32Again(&self->handle_y, target, DONATION_HANDLE_TRACK_STEP);
    } else {
        self->handle_y = target;
    }
    DonationList_ScrollFromHandle(self);
    DonationList_PlaceHandle(self);
    int gone = self->cued_y - self->handle_y;
    if (gone >= DONATION_HANDLE_CUE_DISTANCE || gone <= -DONATION_HANDLE_CUE_DISTANCE) {
        PushButton_ScrollCue(&self->handle);
        self->cued_y = self->handle_y;
    }
}
CLEAN_AS(func_ov145_0229a220, DonationList_MoveHandleTo)

/* func_ov145_0229a298: the handle grabbed when it is under the touch at (x, y): the grab kept,
 * the handle pressed. Answers 1 then. */
int DonationList_GrabHandle(DonationList *self, int x, int y)
{
    if (PushButton_Contains(&self->handle, x, y)) {
        self->grab_dy = self->handle_y - y;
        PushButton_Press(&self->handle);
        self->cued_y = self->handle_y;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov145_0229a298, DonationList_GrabHandle)

/* func_ov145_0229a2e0: the close: main told (GroupParams_SetC4C(1)), the panel's close button
 * pressed; the wipe out comes after the press (state 2, sub state 9). */
void DonationList_StartClose(DonationList *self)
{
    GroupParams_SetC4C(1);
    ButtonPanel_Select(&self->panel, DONATION_CLOSE_BUTTON);
    MenuScene_SetState(donation_base(self), DONATION_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(donation_base(self), DONATION_SUB_CLOSE_PRESS);
}
CLEAN_AS(func_ov145_0229a2e0, DonationList_StartClose)
