/* The order catalog's lists (order_catalog_list.h): its flags, the lists of item codes and their
 * counts, the list's scroll and the scroll bar's thumb, the screens and palettes it queues, the
 * picked item and the labels. */
#include "order_catalog_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/item_record.h"
#include "main/item_traits.h"
#include "main/name_texts.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/screen_map.h"
#include "main/text_base.h"
#include "ov004/room_preview.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(OrderCatalog, wipe_y) == 0x94, "wipe");
static_assert(offsetof(OrderCatalog, top_row) == 0xb4 && offsetof(OrderCatalog, flags) == 0xb6, "flags");
static_assert(offsetof(OrderCatalog, category) == 0xbc && offsetof(OrderCatalog, cursor) == 0xc0, "bytes");
static_assert(offsetof(OrderCatalog, counts) == 0xc4 && offsetof(OrderCatalog, listed) == 0xd6, "counts");
static_assert(offsetof(OrderCatalog, cursor_sprite) == 0xe8 && sizeof(Glider) == 0x64, "cursor sprite");
static_assert(offsetof(OrderCatalog, thumb_button) == 0x14c && sizeof(PushButton) == 0x48, "thumb");
static_assert(offsetof(OrderCatalog, panel) == 0x194 && offsetof(OrderCatalog, labels) == 0x360, "panel");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(OrderCatalog, tasks) == 0x948, "labels");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(OrderCatalog, list0) == 0x9d8, "tasks");
static_assert(offsetof(OrderCatalog, list1) == 0x11d8 && offsetof(OrderCatalog, list2) == 0x1260, "lists 1-2");
static_assert(offsetof(OrderCatalog, list3) == 0x12e8 && offsetof(OrderCatalog, list4) == 0x14e8, "lists 3-4");
static_assert(offsetof(OrderCatalog, list5) == 0x1528 && offsetof(OrderCatalog, list6) == 0x1668, "lists 5-6");
static_assert(offsetof(OrderCatalog, list7) == 0x16e8 && offsetof(OrderCatalog, list8) == 0x17e6, "lists 7-8");
static_assert(offsetof(OrderCatalog, shown) == 0x184e && offsetof(OrderCatalog, rows_screen) == 0x1860, "shown");
static_assert(offsetof(OrderCatalog, list_screen) == 0x2060 && offsetof(OrderCatalog, frame_screen) == 0x2860, "screens");
static_assert(offsetof(OrderCatalog, row_palette) == 0x3060 && offsetof(OrderCatalog, picked_palette) == 0x30a0, "palettes");
static_assert(sizeof(OrderCatalog) == 0x30e0, "size (func_ov142_0229c208)");

/* The pad (autoload_2/input.h): up and down move the thumb while A is held. */
extern PadState data_021fbe40;
#define ORDER_CATALOG_PAD_UP 0x0040
#define ORDER_CATALOG_PAD_DOWN 0x0080

/* 1 when the player is in a room (as catch_panel.c reads it). */
extern u8 data_020e54a8;

/* The table of the lists' addresses (ORDER_CATALOG_CATEGORIES DS addresses), filled once, and
 * bit 0 of its guard says it was. */
extern u32 data_ov142_0229c5e4;
extern u32 data_ov142_0229c5ec[];

/* The SDK's copy (the source first) and fill. */
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

/* The thumb's travel on the bar, its x and the bar's top (its place 0). */
#define ORDER_CATALOG_THUMB_RANGE 90
#define ORDER_CATALOG_THUMB_X 0x38
#define ORDER_CATALOG_THUMB_TOP 0x34

/* A row of the list is 16 pixels; the screen's ring of rows is 16 rows of two lines of 32
 * characters (0x80 bytes). */
#define ORDER_CATALOG_ROW_HEIGHT 16
#define ORDER_CATALOG_SCREEN_ROW_BYTES 0x80

/* The labels: the price (or message) at the order button, the counts and the rows. */
#define ORDER_CATALOG_PRICE_X 0x15d
#define ORDER_CATALOG_PRICE_Y 8
#define ORDER_CATALOG_MESSAGE_NOT_ORDERABLE 0x53

/* An address `offset` bytes from `base`, by the DS's address arithmetic (the game indexes its
 * arrays without bounds). */
static void *catalog_at(const void *base, int offset)
{
    return (void *) (uintptr_t) ((u32) (uintptr_t) base + (u32) offset);
}

static u16 *catalog_listed(OrderCatalog *self, int category)
{
    return catalog_at(self, (int) offsetof(OrderCatalog, listed) + 2 * category);
}

static DualCellSprite *catalog_thumb_sprite(OrderCatalog *self)
{
    /* The push button's base is main's dual cell sprite (push_button.h). */
    return (DualCellSprite *) (void *) &self->thumb_button;
}

/* func_ov142_02299648 */
void OrderCatalog_ClearFlags(OrderCatalog *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov142_02299648, OrderCatalog_ClearFlags)

/* func_ov142_02299658 */
void OrderCatalog_SetFlags(OrderCatalog *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov142_02299658, OrderCatalog_SetFlags)

/* func_ov142_02299668 */
int OrderCatalog_TestFlags(OrderCatalog *self, int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov142_02299668, OrderCatalog_TestFlags)

/* func_ov142_0229967c (each frame): the rows' fade stepped. Fading out it goes down to step 0,
 * where the highlighted tab's category is shown and the fade turns in; fading in it goes up to
 * step 3, where it stops (without applying it again). The step is applied while fading. */
void OrderCatalog_StepFade(OrderCatalog *self)
{
    switch (self->fade_state) {
        case ORDER_CATALOG_FADE_NONE:
            return;
        case ORDER_CATALOG_FADE_OUT:
            if (self->fade_step != 0) {
                self->fade_step = (u8) (self->fade_step - 1);
            } else {
                self->fade_state = ORDER_CATALOG_FADE_IN;
                OrderCatalog_ShowCategory(self, self->tab);
            }
            break;
        case ORDER_CATALOG_FADE_IN:
            if (self->fade_step < 3) {
                self->fade_step = (u8) (self->fade_step + 1);
            } else {
                self->fade_state = ORDER_CATALOG_FADE_NONE;
                return;
            }
            break;
        default:
            break;
    }
    OrderCatalog_ApplyFade(self, self->fade_step);
}
CLEAN_AS(func_ov142_0229967c, OrderCatalog_StepFade)

/* func_ov142_022996f0: the rows' two palettes copied and their colour 15 blended towards colour
 * 8 by `step` (3 the colour itself, 0 colour 8), then queued as layer 4's palettes 3 and 4. */
void OrderCatalog_ApplyFade(OrderCatalog *self, u32 step)
{
    MIi_CpuCopy16(self->row_palette, self->row_palette_shown, 0x20);
    MIi_CpuCopy16(self->picked_palette, self->picked_palette_shown, 0x20);
    self->row_palette_shown[15] = OrderCatalog_BlendColour(self, self->row_palette[15], self->row_palette[8], (int) step);
    self->picked_palette_shown[15] =
        OrderCatalog_BlendColour(self, self->picked_palette[15], self->picked_palette[8], (int) step);
    LayerTask_QueuePalette(&self->tasks[ORDER_CATALOG_TASK_ROW_PALETTE], (int) (uintptr_t) self->row_palette_shown, 4, 3);
    LayerTask_QueuePalette(&self->tasks[ORDER_CATALOG_TASK_PICKED_PALETTE], (int) (uintptr_t) self->picked_palette_shown, 4,
                           4);
}
CLEAN_AS(func_ov142_022996f0, OrderCatalog_ApplyFade)

/* func_ov142_02299794: the 15-bit colours `colour` and `faded` blended by `step` thirds of
 * `colour`: each component (colour's * step + faded's * (3 - step)) / 3.
 * QUIRK: each component is kept to 8 bits before it is put in place, so a step outside 0-3
 * spills into the next component (the game passes 0-3). */
u16 OrderCatalog_BlendColour(void *self, u16 colour, u16 faded, int step)
{
    (void) self;
    int rest = 3 - step;
    u8 blue = (u8) (((colour & 0x1f) * step + (faded & 0x1f) * rest) / 3);
    u8 green = (u8) ((((colour >> 5) & 0x1f) * step + ((faded >> 5) & 0x1f) * rest) / 3);
    u8 red = (u8) ((((colour >> 10) & 0x1f) * step + ((faded >> 10) & 0x1f) * rest) / 3);
    return (u16) (blue | (green << 5) | (red << 10));
}
CLEAN_AS(func_ov142_02299794, OrderCatalog_BlendColour)

/* func_ov142_02299830 (an arrow held): the list scrolled by a row towards the held arrow (to the
 * row's edge first when between rows), within its range. When it moved: the scroll set, made
 * the target, the thumb moved to it and its scroll cue played. */
void OrderCatalog_PageStep(OrderCatalog *self)
{
    int old = self->scroll;
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_UP_HELD) != 0) {
        int low = self->scroll & 0xf;
        self->scroll -= low != 0 ? low : ORDER_CATALOG_ROW_HEIGHT;
        if (self->scroll < 0) {
            self->scroll = 0;
        }
    } else {
        int low = self->scroll & 0xf;
        self->scroll += low != 0 ? ORDER_CATALOG_ROW_HEIGHT - low : ORDER_CATALOG_ROW_HEIGHT;
        if (self->scroll > self->scroll_max) {
            self->scroll = self->scroll_max;
        }
    }
    if (old != self->scroll) {
        OrderCatalog_SetScroll(self, self->scroll);
        self->scroll_target = self->scroll;
        OrderCatalog_ThumbFromScroll(self);
        PushButton_ScrollCue(&self->thumb_button);
    }
}
CLEAN_AS(func_ov142_02299830, OrderCatalog_PageStep)

/* func_ov142_02299908 */
void OrderCatalog_ReleaseArrows(OrderCatalog *self)
{
    OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_UP_HELD | ORDER_CATALOG_FLAG_DOWN_HELD);
}
CLEAN_AS(func_ov142_02299908, OrderCatalog_ReleaseArrows)

/* func_ov142_02299918 */
void OrderCatalog_HoldDownArrow(OrderCatalog *self)
{
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_DOWN_HELD);
}
CLEAN_AS(func_ov142_02299918, OrderCatalog_HoldDownArrow)

/* func_ov142_02299928 */
void OrderCatalog_HoldUpArrow(OrderCatalog *self)
{
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_UP_HELD);
}
CLEAN_AS(func_ov142_02299928, OrderCatalog_HoldUpArrow)

/* func_ov142_02299938 (back from the confirmation): the list scrolled to put the picked row at
 * the top, as far as it goes, the thumb moved to it, the bar shown or hidden by whether the
 * list scrolls, and the list no longer dimmed. */
void OrderCatalog_ScrollToPickedRow(OrderCatalog *self)
{
    int row = self->picked_row;
    int last = OrderCatalog_Count(self) - 8;
    if (last < 0) {
        last = 0;
    }
    if (row < 0) {
        row = 0;
    } else if (row > last) {
        row = last;
    }
    OrderCatalog_SetScroll(self, row * ORDER_CATALOG_ROW_HEIGHT);
    self->scroll_target = self->scroll;
    OrderCatalog_ThumbFromScroll(self);
    if (self->scroll_max == 0) {
        OrderCatalog_HideBar(self);
    } else {
        OrderCatalog_ShowBar(self);
    }
    OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_DIMMED);
}
CLEAN_AS(func_ov142_02299938, OrderCatalog_ScrollToPickedRow)

/* func_ov142_022999a4 (on to the confirmation): the picked item's category shown, the list
 * scrolled to put its row fourth from the top (unclamped), the thumb moved to it, the bar
 * hidden and the list dimmed. */
void OrderCatalog_ShowPickedPage(OrderCatalog *self)
{
    OrderCatalog_ShowCategory(self, self->picked_category);
    OrderCatalog_SetScroll(self, (self->picked_row - 3) * ORDER_CATALOG_ROW_HEIGHT);
    self->scroll_target = self->scroll;
    OrderCatalog_ThumbFromScroll(self);
    OrderCatalog_HideBar(self);
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_DIMMED);
}
CLEAN_AS(func_ov142_022999a4, OrderCatalog_ShowPickedPage)

/* func_ov142_022999ec: the bar hidden (its places in palette 3). */
void OrderCatalog_HideBar(OrderCatalog *self)
{
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_NO_BAR);
    OrderCatalog_SetBarPalette(self, 3);
}
CLEAN_AS(func_ov142_022999ec, OrderCatalog_HideBar)

/* func_ov142_02299a08: the bar shown (palette 2). */
void OrderCatalog_ShowBar(OrderCatalog *self)
{
    OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_NO_BAR);
    OrderCatalog_SetBarPalette(self, 2);
}
CLEAN_AS(func_ov142_02299a08, OrderCatalog_ShowBar)

/* func_ov142_02299a24: the bar's places in the frame's screen (columns 0x17-0x18, lines 4-0x13)
 * given `palette`, the screen to be queued. */
void OrderCatalog_SetBarPalette(OrderCatalog *self, int palette)
{
    ScreenMap_SetPalette(self->frame_screen, 0x17, 4, 0x18, 0x13, (u32) palette);
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_FRAME_SCREEN);
}
CLEAN_AS(func_ov142_02299a24, OrderCatalog_SetBarPalette)

/* func_ov142_02299a54: when the list scrolls, the thumb put at the scroll's share of its travel
 * and placed. */
void OrderCatalog_ThumbFromScroll(OrderCatalog *self)
{
    if (self->scroll_max > 0) {
        self->thumb = self->scroll * ORDER_CATALOG_THUMB_RANGE / self->scroll_max;
        OrderCatalog_PlaceThumb(self);
    }
}
CLEAN_AS(func_ov142_02299a54, OrderCatalog_ThumbFromScroll)

/* func_ov142_02299a80: the scroll set to the thumb's share of the list's range (within it) and
 * made the target. */
void OrderCatalog_ScrollFromThumb(OrderCatalog *self)
{
    int max = self->scroll_max;
    int scroll = self->thumb * max / ORDER_CATALOG_THUMB_RANGE;
    if (scroll < 0) {
        scroll = 0;
    }
    if (scroll > max) {
        scroll = max;
    }
    OrderCatalog_SetScroll(self, scroll);
    self->scroll_target = scroll;
}
CLEAN_AS(func_ov142_02299a80, OrderCatalog_ScrollFromThumb)

/* func_ov142_02299ab8: the thumb's sprite put at its place on the bar, moved with the wipe. */
void OrderCatalog_PlaceThumb(OrderCatalog *self)
{
    DualCellSprite_SetOffset(catalog_thumb_sprite(self), ORDER_CATALOG_THUMB_X,
                             self->wipe_y + (self->thumb - ORDER_CATALOG_THUMB_TOP));
}
CLEAN_AS(func_ov142_02299ab8, OrderCatalog_PlaceThumb)

/* func_ov142_02299ae0: once the thumb's release has played, the thumb shown at rest; whether. */
int OrderCatalog_ThumbReleased(OrderCatalog *self)
{
    if (DualCellSprite_IsDone(catalog_thumb_sprite(self))) {
        PushButton_ShowUp(&self->thumb_button);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov142_02299ae0, OrderCatalog_ThumbReleased)

/* func_ov142_02299b08: the thumb moved 4 by up or down held (up first), within its travel; when
 * it moved, the scroll follows, the thumb placed and its scroll cue played. */
void OrderCatalog_MoveThumbByPad(OrderCatalog *self)
{
    int old = self->thumb;
    if ((data_021fbe40.held & ORDER_CATALOG_PAD_UP) != 0) {
        self->thumb -= 4;
        if (self->thumb < 0) {
            self->thumb = 0;
        }
    } else if ((data_021fbe40.held & ORDER_CATALOG_PAD_DOWN) != 0) {
        self->thumb += 4;
        if (self->thumb > ORDER_CATALOG_THUMB_RANGE) {
            self->thumb = ORDER_CATALOG_THUMB_RANGE;
        }
    }
    if (old != self->thumb) {
        OrderCatalog_ScrollFromThumb(self);
        OrderCatalog_PlaceThumb(self);
        PushButton_ScrollCue(&self->thumb_button);
    }
}
CLEAN_AS(func_ov142_02299b08, OrderCatalog_MoveThumbByPad)

/* func_ov142_02299b94 */
void OrderCatalog_ReleaseThumb(OrderCatalog *self)
{
    PushButton_Release(&self->thumb_button);
}
CLEAN_AS(func_ov142_02299b94, OrderCatalog_ReleaseThumb)

/* func_ov142_02299ba4: the thumb taken to the touch's y: with `jump` (the bar's track pressed)
 * eased there by eighths from the bar's top, else at once, kept where it was grabbed; within its
 * travel. The scroll follows and the thumb is placed; the scroll cue plays each 4 places moved. */
void OrderCatalog_DragThumb(OrderCatalog *self, int y, int jump)
{
    if (jump != 0) {
        y -= ORDER_CATALOG_THUMB_TOP;
    } else {
        y += self->grab_offset;
    }
    if (y < 0) {
        y = 0;
    }
    if (y > ORDER_CATALOG_THUMB_RANGE) {
        y = ORDER_CATALOG_THUMB_RANGE;
    }
    if (jump != 0) {
        Approach_S32Again((int *) (void *) &self->thumb, y, 8);
    } else {
        self->thumb = y;
    }
    OrderCatalog_ScrollFromThumb(self);
    OrderCatalog_PlaceThumb(self);
    int moved = self->thumb_cued - self->thumb;
    if (moved >= 4 || moved <= -4) {
        PushButton_ScrollCue(&self->thumb_button);
        self->thumb_cued = self->thumb;
    }
}
CLEAN_AS(func_ov142_02299ba4, OrderCatalog_DragThumb)

/* func_ov142_02299c1c: a touch at (x, y) on the thumb grabs it (pressed, the offset kept);
 * whether it did. */
int OrderCatalog_GrabThumb(OrderCatalog *self, int x, int y)
{
    if (PushButton_Contains(&self->thumb_button, x, y) != 0) {
        self->grab_offset = self->thumb - y;
        PushButton_Press(&self->thumb_button);
        self->thumb_cued = self->thumb;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov142_02299c1c, OrderCatalog_GrabThumb)

/* func_ov142_0229a0f8: row `row` of list `category` picked (-1 for none); whether that changed
 * the pick. None: the price label cleared, nothing to order (palette 6) and, in a room, the
 * item shown there taken away. An item: message 0x53 and nothing to order when
 * ItemTraits_FlagBit4 is set, else its member price and the order button (palette 5); in a room
 * it is shown there. Either way the list's screen is to be queued (the picked row highlighted). */
int OrderCatalog_PickItem(OrderCatalog *self, int category, int row)
{
    int changed = 1;
    if (self->picked_category == category && self->picked_row == row) {
        changed = 0;
    }
    self->picked_category = (u8) category;
    self->picked_row = (s16) row;
    if (row == -1) {
        OrderCatalog_ClearPriceLabel(self);
        OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_ORDERABLE);
        self->order_palette = 6;
        if (data_020e54a8 == 1 && OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_PREVIEW) != 0) {
            OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_PREVIEW);
            RoomPreview_Clear(RoomPreview_Get());
        }
    } else {
        ItemCode item = *OrderCatalog_ItemAt(self, row);
        if (ItemTraits_FlagBit4(&item) != 0) {
            OrderCatalog_ShowNotOrderable(self);
            self->order_palette = 6;
            OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_ORDERABLE);
        } else {
            int price = ItemTraits_MemberPrice(&item);
            OrderCatalog_ShowPrice(self, price);
            OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_ORDERABLE);
            self->order_palette = 5;
        }
        if (data_020e54a8 == 1) {
            OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_PREVIEW);
            RoomPreview_Show(RoomPreview_Get(), &item);
        }
    }
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_LIST_SCREEN);
    return changed;
}
CLEAN_AS(func_ov142_0229a0f8, OrderCatalog_PickItem)

/* func_ov142_0229a3c0: the list's screen in palette 3 (5 dimmed), the picked row's two lines in
 * palette 4 when it is on screen, and queued as layer 4's screen; once queued, no longer to be. */
void OrderCatalog_QueueListScreen(OrderCatalog *self)
{
    int palette = OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_DIMMED) != 0 ? 5 : 3;
    ScreenMap_SetPalette(self->list_screen, 0, 0, 0x1f, 0x1f, (u32) palette);
    if (self->category == self->picked_category) {
        int picked = self->picked_row;
        int on_screen = picked - self->top_row;
        if (on_screen >= 0 && on_screen < ORDER_CATALOG_ROWS) {
            int line = (picked & 0xf) * 2;
            ScreenMap_SetPalette(self->list_screen, 0, line, 0x1f, line + 1, 4);
        }
    }
    if (LayerTask_QueueScreen(&self->tasks[ORDER_CATALOG_TASK_LIST_SCREEN], (int) (uintptr_t) self->list_screen, 4, 0x800,
                              0) != 0) {
        OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_LIST_SCREEN);
    }
}
CLEAN_AS(func_ov142_0229a3c0, OrderCatalog_QueueListScreen)

/* func_ov142_0229a45c (each frame): the scroll moved 6 towards its target (not past it), set
 * and the thumb moved to it. */
void OrderCatalog_StepScroll(OrderCatalog *self)
{
    if (self->scroll == self->scroll_target) {
        return;
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
    OrderCatalog_SetScroll(self, self->scroll);
    OrderCatalog_ThumbFromScroll(self);
}
CLEAN_AS(func_ov142_0229a45c, OrderCatalog_StepScroll)

/* func_ov142_0229a4d4: the list scrolled to `scroll`: the top and bottom flags, layer 4's
 * scroll (32 pixels above), the top row, the list's screen built and the rows' labels to be
 * set. */
void OrderCatalog_SetScroll(OrderCatalog *self, int scroll)
{
    OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_AT_TOP | ORDER_CATALOG_FLAG_AT_BOTTOM);
    if (scroll <= 0) {
        OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_AT_TOP);
    }
    if (scroll >= self->scroll_max) {
        OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_AT_BOTTOM);
    }
    self->scroll = scroll;
    DisplayLayer_SetScroll(4, 0, self->scroll - 0x20);
    self->top_row = (s16) (scroll >> 4);
    OrderCatalog_BuildListScreen(self);
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_ROWS);
}
CLEAN_AS(func_ov142_0229a4d4, OrderCatalog_SetScroll)

/* func_ov142_0229a540 (each frame's end): what is to be done: the list's screen queued, the
 * frame's screen queued as layer 6's (once queued, no longer to be), the rows' labels set and
 * the counts' labels set. */
void OrderCatalog_FlushChanges(OrderCatalog *self)
{
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_LIST_SCREEN)) {
        OrderCatalog_QueueListScreen(self);
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_FRAME_SCREEN)) {
        if (LayerTask_QueueScreen(&self->tasks[ORDER_CATALOG_TASK_FRAME_SCREEN], (int) (uintptr_t) self->frame_screen, 6,
                                  0x800, 0)) {
            OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_FRAME_SCREEN);
        }
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_ROWS)) {
        OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_ROWS);
        OrderCatalog_SetRowLabels(self);
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_COUNTS)) {
        OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_COUNTS);
        OrderCatalog_ShowCounts(self);
    }
}
CLEAN_AS(func_ov142_0229a540, OrderCatalog_FlushChanges)

/* func_ov142_0229a5cc: the list's screen built: cleared to 0x10, then the nine rows on screen
 * copied from the rows' screen, which holds nine rows (row n from its row n % 9) into the
 * ring of 16 (row n at its row n % 16); the screen is to be queued.
 * QUIRK: a negative top row reads before the rows' screen ((n + 9) % 9 stays negative for n
 * below -9); the scroll is never below 0. */
void OrderCatalog_BuildListScreen(OrderCatalog *self)
{
    int top = self->top_row;
    int from = (top + 9) % 9;
    int to = top & 0xf;
    MIi_CpuClear16(0x10, self->list_screen, 0x800);
    for (int i = 0; i < ORDER_CATALOG_ROWS; i++) {
        MIi_CpuCopy16(catalog_at(self->rows_screen, from * ORDER_CATALOG_SCREEN_ROW_BYTES),
                      catalog_at(self->list_screen, to * ORDER_CATALOG_SCREEN_ROW_BYTES), ORDER_CATALOG_SCREEN_ROW_BYTES);
        from++;
        if (from >= 9) {
            from = 0;
        }
        to = (to + 1) & 0xf;
    }
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_LIST_SCREEN);
}
CLEAN_AS(func_ov142_0229a5cc, OrderCatalog_BuildListScreen)

/* func_ov142_0229a644: the item code at row `row` (0 when negative) of the list shown. The table
 * of the lists' addresses is filled the first time, from this scene.
 * QUIRK: the table keeps the first scene's addresses while the overlay stays loaded.
 * REQUIRES: `category` < 9 (the game reads on past the table for others). */
u16 *OrderCatalog_ItemAt(OrderCatalog *self, int row)
{
    static const u16 list_offsets[ORDER_CATALOG_CATEGORIES] = {
        offsetof(OrderCatalog, list0), offsetof(OrderCatalog, list1), offsetof(OrderCatalog, list2),
        offsetof(OrderCatalog, list3), offsetof(OrderCatalog, list4), offsetof(OrderCatalog, list5),
        offsetof(OrderCatalog, list6), offsetof(OrderCatalog, list7), offsetof(OrderCatalog, list8),
    };
    if ((data_ov142_0229c5e4 & 1) == 0) {
        for (int i = 0; i < ORDER_CATALOG_CATEGORIES; i++) {
            data_ov142_0229c5ec[i] = (u32) (uintptr_t) self + list_offsets[i];
        }
        data_ov142_0229c5e4 |= 1;
    }
    if (row < 0) {
        row = 0;
    }
    const u32 *entry = catalog_at(data_ov142_0229c5ec, 4 * self->category);
    return (u16 *) (uintptr_t) (*entry + 2u * (u32) row);
}
CLEAN_AS(func_ov142_0229a644, OrderCatalog_ItemAt)

/* func_ov142_0229a6d8: the items in the list shown. */
s16 OrderCatalog_Count(OrderCatalog *self)
{
    return *(const s16 *) catalog_at(self, (int) offsetof(OrderCatalog, counts) + 2 * self->category);
}
CLEAN_AS(func_ov142_0229a6d8, OrderCatalog_Count)

/* func_ov142_0229a6e8: the items ItemTraits_FlagBit3 lists in the category shown. */
s16 OrderCatalog_Listed(OrderCatalog *self)
{
    return *(const s16 *) catalog_listed(self, self->category);
}
CLEAN_AS(func_ov142_0229a6e8, OrderCatalog_Listed)

/* func_ov142_0229a6f8: of the `count` item codes from `first`, those ItemTraits_FlagBit3 lists
 * counted in `category`'s listed items, and those of them the current player's item record has
 * put in `out`; answers how many it has. */
int OrderCatalog_CollectItems(OrderCatalog *self, u16 *out, u16 first, int count, int category)
{
    u8 *record = PlayerRecords_Current();
    u16 *listed = catalog_listed(self, category);
    int found = 0;
    u16 code = first;
    for (int i = 0; i < count; i++) {
        ItemCode item = code;
        if (ItemTraits_FlagBit3(&item) != 0) {
            *listed = (u16) (*listed + 1);
            if (ItemRecord_Has((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &item) != 0) {
                out[found] = code;
                found++;
            }
        }
        code = (u16) (code + 1);
    }
    return found;
}
CLEAN_AS(func_ov142_0229a6f8, OrderCatalog_CollectItems)

/* func_ov142_0229a76c: the same with every fourth code (an item with variants, or a pile). */
int OrderCatalog_CollectEveryFourth(OrderCatalog *self, u16 *out, u16 first, int count, int category)
{
    u8 *record = PlayerRecords_Current();
    u16 *listed = catalog_listed(self, category);
    int found = 0;
    u16 code = first;
    for (int i = 0; i < count; i++) {
        ItemCode item = code;
        if (ItemTraits_FlagBit3(&item) != 0) {
            *listed = (u16) (*listed + 1);
            if (ItemRecord_Has((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &item) != 0) {
                out[found] = code;
                found++;
            }
        }
        code = (u16) (code + 4);
    }
    return found;
}
CLEAN_AS(func_ov142_0229a76c, OrderCatalog_CollectEveryFourth)

/* func_ov142_0229a7e0: list 5, from its three ranges in turn. */
void OrderCatalog_ListCategory5(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_5] = 0;
    u32 total = (u32) OrderCatalog_CollectEveryFourth(self, self->list5, 0x3fa4, 0x40, ORDER_CATALOG_CATEGORY_5);
    total += (u32) OrderCatalog_CollectEveryFourth(self, catalog_at(self->list5, (int) (total * 2)), 0x40a4, 0x20,
                                                   ORDER_CATALOG_CATEGORY_5);
    total += (u32) OrderCatalog_CollectEveryFourth(self, catalog_at(self->list5, (int) (total * 2)), 0x4124, 0x40,
                                                   ORDER_CATALOG_CATEGORY_5);
    self->counts[ORDER_CATALOG_CATEGORY_5] = (u16) total;
}
CLEAN_AS(func_ov142_0229a7e0, OrderCatalog_ListCategory5)

/* func_ov142_0229a84c */
void OrderCatalog_ListCategory8(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_8] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_8] =
        (u16) OrderCatalog_CollectEveryFourth(self, self->list8, 0x450c, 0x34, ORDER_CATALOG_CATEGORY_8);
}
CLEAN_AS(func_ov142_0229a84c, OrderCatalog_ListCategory8)

/* func_ov142_0229a880 */
void OrderCatalog_ListCategory7(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_7] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_7] =
        (u16) OrderCatalog_CollectEveryFourth(self, self->list7, 0x45dc, 0x7f, ORDER_CATALOG_CATEGORY_7);
}
CLEAN_AS(func_ov142_0229a880, OrderCatalog_ListCategory7)

/* func_ov142_0229a8b4 */
void OrderCatalog_ListCategory6(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_6] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_6] =
        (u16) OrderCatalog_CollectEveryFourth(self, self->list6, 0x1003, 0x40, ORDER_CATALOG_CATEGORY_6);
}
CLEAN_AS(func_ov142_0229a8b4, OrderCatalog_ListCategory6)

/* func_ov142_0229a8e8 */
void OrderCatalog_ListCategory4(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_4] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_4] =
        (u16) OrderCatalog_CollectEveryFourth(self, self->list4, 0x3e24, 0x20, ORDER_CATALOG_CATEGORY_4);
}
CLEAN_AS(func_ov142_0229a8e8, OrderCatalog_ListCategory4)

/* func_ov142_0229a91c */
void OrderCatalog_ListCategory3(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_3] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_3] =
        (u16) OrderCatalog_CollectEveryFourth(self, self->list3, 0x3984, 0x100, ORDER_CATALOG_CATEGORY_3);
}
CLEAN_AS(func_ov142_0229a91c, OrderCatalog_ListCategory3)

/* func_ov142_0229a954 */
void OrderCatalog_ListCarpets(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_2] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_2] =
        (u16) OrderCatalog_CollectItems(self, self->list2, 0x1144, 0x44, ORDER_CATALOG_CATEGORY_2);
}
CLEAN_AS(func_ov142_0229a954, OrderCatalog_ListCarpets)

/* func_ov142_0229a988 */
void OrderCatalog_ListWallpaper(OrderCatalog *self)
{
    self->listed[ORDER_CATALOG_CATEGORY_1] = 0;
    self->counts[ORDER_CATALOG_CATEGORY_1] =
        (u16) OrderCatalog_CollectItems(self, self->list1, 0x1100, 0x44, ORDER_CATALOG_CATEGORY_1);
}
CLEAN_AS(func_ov142_0229a988, OrderCatalog_ListWallpaper)

/* Whether `code` is in a range another list (or no list) takes, which list 0 leaves out. */
static int catalog_left_out_of_list0(u16 code)
{
    static const u16 ranges[][2] = {
        {0x45dc, 0x47d7}, {0x4384, 0x4463}, {0x42a4, 0x4383}, {0x3e24, 0x3ea3}, {0x3984, 0x3d83},
        {0x450c, 0x45db}, {0x3fa4, 0x40a3}, {0x4124, 0x4223}, {0x40a4, 0x4123},
    };
    for (size_t i = 0; i < sizeof(ranges) / sizeof(ranges[0]); i++) {
        if (code >= ranges[i][0] && code <= ranges[i][1]) {
            return 1;
        }
    }
    return 0;
}

/* func_ov142_0229a9bc: list 0: every fourth code of the 0x6e9 from 0x3000 but those the other
 * lists take and 0x42a4-0x4463, as OrderCatalog_CollectEveryFourth counts and collects them.
 * QUIRK: the list is not bounded: 0x436 codes pass the ranges for its 0x400 entries, so a record
 * with more of them listed would write on into list 1. */
void OrderCatalog_ListCategory0(OrderCatalog *self)
{
    int found = 0;
    self->counts[ORDER_CATALOG_CATEGORY_0] = 0;
    self->listed[ORDER_CATALOG_CATEGORY_0] = 0;
    u16 code = 0x3000;
    u8 *record = PlayerRecords_Current();
    for (int i = 0; i < 0x6e9; i++) {
        ItemCode item = code;
        if (!catalog_left_out_of_list0(code) && ItemTraits_FlagBit3(&item) != 0) {
            self->listed[ORDER_CATALOG_CATEGORY_0] = (u16) (self->listed[ORDER_CATALOG_CATEGORY_0] + 1);
            if (ItemRecord_Has((ItemRecord *) (void *) PlayerRecord_ItemRecord(record), &item) != 0) {
                *(u16 *) catalog_at(self->list0, 2 * found) = code;
                found++;
            }
        }
        code = (u16) (code + 4);
    }
    self->counts[ORDER_CATALOG_CATEGORY_0] = (u16) found;
}
CLEAN_AS(func_ov142_0229a9bc, OrderCatalog_ListCategory0)

/* func_ov142_0229ab68: tab `tab` highlighted, and the rows fade out to show its category; nothing
 * when it is highlighted already. */
void OrderCatalog_StartFade(OrderCatalog *self, u8 tab)
{
    if (tab == self->tab) {
        return;
    }
    self->tab = tab;
    self->fade_state = ORDER_CATALOG_FADE_OUT;
}
CLEAN_AS(func_ov142_0229ab68, OrderCatalog_StartFade)

/* func_ov142_0229ab80: list `category` shown (its tab highlighted), from its top: its scroll's
 * range, the thumb at the top, the bar shown when it scrolls, and the counts to be set. Nothing
 * when it is shown already. */
void OrderCatalog_ShowCategory(OrderCatalog *self, u8 category)
{
    if (self->category == category) {
        return;
    }
    self->category = category;
    self->tab = category;
    self->scroll_max = (OrderCatalog_Count(self) - 8) * ORDER_CATALOG_ROW_HEIGHT;
    if (self->scroll_max < 0) {
        self->scroll_max = 0;
    }
    OrderCatalog_SetScroll(self, 0);
    self->scroll_target = 0;
    OrderCatalog_ThumbFromScroll(self);
    if (self->scroll_max == 0) {
        OrderCatalog_HideBar(self);
    } else {
        OrderCatalog_ShowBar(self);
    }
    OrderCatalog_PlaceThumb(self);
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_COUNTS);
}
CLEAN_AS(func_ov142_0229ab80, OrderCatalog_ShowCategory)

/* func_ov142_0229abfc: the price's place shown empty. */
void OrderCatalog_ClearPriceLabel(OrderCatalog *self)
{
    TextLabel *label = OrderCatalog_NextLabel(self);
    TextBase_Clear(label);
    TextLabel_OpenStyledBox2(label, 6, ORDER_CATALOG_PRICE_X, ORDER_CATALOG_PRICE_Y, 14, 4, 0);
    TextLabel_Show(label, 0, 0);
}
CLEAN_AS(func_ov142_0229abfc, OrderCatalog_ClearPriceLabel)

/* func_ov142_0229ac38: message 0x53 at the price's place, centred. */
void OrderCatalog_ShowNotOrderable(OrderCatalog *self)
{
    OrderCatalog_ShowMessage(self, ORDER_CATALOG_MESSAGE_NOT_ORDERABLE, ORDER_CATALOG_PRICE_X, ORDER_CATALOG_PRICE_Y, 14, 1);
}
CLEAN_AS(func_ov142_0229ac38, OrderCatalog_ShowNotOrderable)

/* func_ov142_0229ac58: message `message` of the menu's messages at (x, y) in style 6, colours
 * `colour` and 4, centred or from the left. */
void OrderCatalog_ShowMessage(OrderCatalog *self, int message, int x, int y, u8 colour, int centred)
{
    TextLabel *label = OrderCatalog_NextLabel(self);
    TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) message);
    TextLabel_OpenStyledBox2(label, 6, x, y, colour, 4, 0);
    TextLabel_Show(label, centred, 0);
}
CLEAN_AS(func_ov142_0229ac58, OrderCatalog_ShowMessage)

/* func_ov142_0229ac9c: `price` at the price's place (the other font), right-aligned. */
void OrderCatalog_ShowPrice(OrderCatalog *self, int price)
{
    TextLabel *label = OrderCatalog_NextLabel(self);
    TextLabel_Compose((int) (uintptr_t) label, price, 8, 0, 0, 1);
    TextLabel_OpenStyledBox2(label, 6, ORDER_CATALOG_PRICE_X, ORDER_CATALOG_PRICE_Y, 0xe, 4, 1);
    TextLabel_ShowRightAligned(label);
}
CLEAN_AS(func_ov142_0229ac9c, OrderCatalog_ShowPrice)

/* func_ov142_0229ace4: the list's count (right-aligned at 0x156) and the category's listed
 * items (at 0x15a). */
void OrderCatalog_ShowCounts(OrderCatalog *self)
{
    TextLabel *label = OrderCatalog_NextLabel(self);
    int count = OrderCatalog_Count(self);
    TextLabel_Compose((int) (uintptr_t) label, count, 3, 0, 0, 0);
    TextLabel_OpenStyledBox(label, 6, 0x156, 3, 0xe, 4, 0);
    TextLabel_ShowRightAligned(label);
    label = OrderCatalog_NextLabel(self);
    int listed = OrderCatalog_Listed(self);
    TextLabel_Compose((int) (uintptr_t) label, listed, 3, 0, 0, 0);
    TextLabel_OpenStyledBox(label, 6, 0x15a, 3, 0xe, 4, 0);
    TextLabel_Show(label, 0, 0);
}
CLEAN_AS(func_ov142_0229ace4, OrderCatalog_ShowCounts)

/* func_ov142_0229ad74: the nine rows' labels from the top row: a row past the list's ends is
 * cleared (no item kept), one whose item changed shows its name (main/name_texts.h); each row
 * n is kept at the ring's place n % 9 and drawn at 0x52 + 0x1a times it.
 * QUIRK: a top row below -9 puts its rows before `shown`; the scroll is never below 0. */
void OrderCatalog_SetRowLabels(OrderCatalog *self)
{
    NameText name;
    NameText_Construct(&name);
    int row = self->top_row;
    const u16 *item = OrderCatalog_ItemAt(self, row);
    int place = (row + 9) % 9;
    int count = OrderCatalog_Count(self);
    for (int i = 0; i < ORDER_CATALOG_ROWS; i++) {
        TextLabel *label = NULL;
        u16 *shown = catalog_at(self->shown, 2 * place);
        if (row < 0 || row >= count) {
            *shown = ORDER_CATALOG_NO_ITEM;
            label = OrderCatalog_NextLabel(self);
            TextBase_Clear(label);
        } else {
            if (*item != *shown) {
                *shown = *item;
                label = OrderCatalog_NextLabel(self);
                u16 code = *item;
                NameText_SetItem(&name, &code);
                TextBase_Copy((TextBase *) (void *) label, (TextBase *) (void *) &name);
            }
            item++;
        }
        if (label != NULL) {
            TextLabel_OpenStyledBox2(label, 4, place * 0x1a + 0x52, 0xd, 0xf, 8, 0);
            TextLabel_Show(label, 0, 0);
        }
        row++;
        place++;
        if (place >= 9) {
            place = 0;
        }
    }
    NameText_Destruct(&name);
}
CLEAN_AS(func_ov142_0229ad74, OrderCatalog_SetRowLabels)

/* func_ov142_0229ae60 (each frame's start): no labels handed out, and all their boxes closed. */
void OrderCatalog_CloseLabels(OrderCatalog *self)
{
    self->labels_used = 0;
    for (int i = 0; i < ORDER_CATALOG_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov142_0229ae60, OrderCatalog_CloseLabels)

/* func_ov142_0229ae8c: the next label of the frame.
 * QUIRK: once all 14 are handed out, the last one is handed out again. */
TextLabel *OrderCatalog_NextLabel(OrderCatalog *self)
{
    if (self->labels_used >= ORDER_CATALOG_LABELS) {
        return &self->labels[ORDER_CATALOG_LABELS - 1];
    }
    self->labels_used = (u8) (self->labels_used + 1);
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov142_0229ae8c, OrderCatalog_NextLabel)
