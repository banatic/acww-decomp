/* The order catalog's cursor (order_catalog_cursor.h): its moves by the d-pad and by touch, its
 * sprite, what each place does, the order and its confirmation, and the sub states. */
#include "order_catalog_cursor.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/group_params.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "order_catalog_list.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov004/room_preview.h"

/* The pad (autoload_2/input.h) and the pen (as menu_scene.c reads it), and the touch. */
extern PadState data_021fbe40;
#define ORDER_CATALOG_PAD_A 0x0001
#define ORDER_CATALOG_PAD_B 0x0002
#define ORDER_CATALOG_PAD_START 0x0008
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c58, data_021f6c54;

/* 1 when the player is in a room (as catch_panel.c reads it). */
extern u8 data_020e54a8;

/* The panel's buttons (ov002/button_panel.h) the scene uses: quit, and the confirmation's. */
#define ORDER_CATALOG_BUTTON_ACCEPT 3
#define ORDER_CATALOG_BUTTON_DECLINE 4
#define ORDER_CATALOG_BUTTON_QUIT 6

/* The sounds (main/sound.h). */
#define ORDER_CATALOG_SOUND_TAB 0xc
#define ORDER_CATALOG_SOUND_PICK 0x29 /* also the accept */
#define ORDER_CATALOG_SOUND_DECLINE 0x2a
#define ORDER_CATALOG_SOUND_ORDER 0x59

/* The cursor sprite's place at the tabs (x, and the first tab's y), the rows (x, and the first
 * row's y less the scroll within a row) and the other places. */
#define ORDER_CATALOG_TAB_X 0x17
#define ORDER_CATALOG_TAB_Y 0x1f
#define ORDER_CATALOG_ROW_X 0x40
#define ORDER_CATALOG_ROW_Y 0x28
#define ORDER_CATALOG_ORDER_X 0xe8
#define ORDER_CATALOG_ORDER_Y 0x57
#define ORDER_CATALOG_ARROW_X 0xc0
#define ORDER_CATALOG_UP_Y 0x23
#define ORDER_CATALOG_DOWN_Y 0x9b

static MenuScene *catalog_scene(OrderCatalog *self)
{
    return &self->base;
}

static CellLayerSprite *catalog_cursor_cells(OrderCatalog *self)
{
    /* The cursor sprite's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->cursor_sprite;
}

/* The cursor sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void catalog_update_cursor_sprite(OrderCatalog *self)
{
    Glider *sprite = &self->cursor_sprite;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) sprite->vtable;
    vtable[3](sprite);
}

static int catalog_is_row(u8 place)
{
    return place >= ORDER_CATALOG_PLACE_ROW && place <= ORDER_CATALOG_PLACE_LAST_ROW;
}

/* func_ov142_02299c64: the cursor moved by the d-pad keys `keys`; whether it moved or the list
 * scrolled. At the tabs: up and down along them, right into the list. In the list: left to the
 * tabs, right to the bar (or the buttons); up and down along the rows, scrolling the list's
 * target by a row (to the row's edge first) at its first and last rows. At the bar: up and down
 * along its thumb and arrows, right to the order button, left back to the list. At the buttons:
 * up and down between them, left to the bar (or the list). */
int OrderCatalog_MoveCursorByKeys(OrderCatalog *self, int keys)
{
    u8 old = self->cursor;
    if (keys == 0) {
        return 0;
    }
    if (old <= ORDER_CATALOG_PLACE_LAST_TAB) {
        if (KeyRepeat_HasRight(keys)) {
            OrderCatalog_CursorRightFromTabs(self);
        } else if (KeyRepeat_HasUp(keys)) {
            if (self->cursor != ORDER_CATALOG_PLACE_TAB) {
                self->cursor = (u8) (self->cursor - 1);
            }
        } else if (KeyRepeat_HasDown(keys)) {
            if (self->cursor < ORDER_CATALOG_PLACE_LAST_TAB) {
                self->cursor = (u8) (self->cursor + 1);
            }
        }
    } else if (catalog_is_row(old)) {
        if (KeyRepeat_HasLeft(keys)) {
            OrderCatalog_CursorToTabs(self);
        } else if (KeyRepeat_HasRight(keys)) {
            OrderCatalog_CursorRightFromList(self);
        } else if (KeyRepeat_HasUp(keys)) {
            if (self->cursor > ORDER_CATALOG_PLACE_ROW) {
                self->cursor = (u8) (self->cursor - 1);
                if (self->cursor == ORDER_CATALOG_PLACE_ROW) {
                    int within = self->scroll_target & 0xf;
                    if (within != 0) {
                        self->scroll_target -= within;
                    }
                }
            } else if (self->scroll_target >= 0x10) {
                self->scroll_target -= 0x10;
                return 1;
            }
        } else if (KeyRepeat_HasDown(keys)) {
            int max = self->scroll_max;
            if (max == 0) {
                if (self->cursor < OrderCatalog_Count(self) + 8) {
                    self->cursor = (u8) (self->cursor + 1);
                }
            } else if (self->cursor < ORDER_CATALOG_PLACE_ROW + 7) {
                self->cursor = (u8) (self->cursor + 1);
            } else {
                int target = self->scroll_target;
                int within = target & 0xf;
                if (within != 0) {
                    self->scroll_target += 0x10 - within;
                    return 1;
                }
                if (target <= max - 0x10) {
                    self->scroll_target += 0x10;
                    return 1;
                }
            }
        }
    } else {
        switch (old) {
            case ORDER_CATALOG_PLACE_QUIT:
                if (KeyRepeat_HasLeft(keys)) {
                    OrderCatalog_CursorLeftFromButtons(self);
                } else if (KeyRepeat_HasUp(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_ORDER;
                }
                break;
            case ORDER_CATALOG_PLACE_ORDER:
                if (KeyRepeat_HasLeft(keys)) {
                    OrderCatalog_CursorLeftFromButtons(self);
                } else if (KeyRepeat_HasDown(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_QUIT;
                }
                break;
            case ORDER_CATALOG_PLACE_THUMB:
                if (KeyRepeat_HasUp(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_UP;
                } else if (KeyRepeat_HasDown(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_DOWN;
                } else if (KeyRepeat_HasRight(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_ORDER;
                } else if (KeyRepeat_HasLeft(keys)) {
                    OrderCatalog_CursorLeftFromBar(self);
                }
                break;
            case ORDER_CATALOG_PLACE_UP:
                if (KeyRepeat_HasDown(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_THUMB;
                } else if (KeyRepeat_HasRight(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_ORDER;
                } else if (KeyRepeat_HasLeft(keys)) {
                    OrderCatalog_CursorLeftFromBar(self);
                }
                break;
            case ORDER_CATALOG_PLACE_DOWN:
                if (KeyRepeat_HasUp(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_THUMB;
                } else if (KeyRepeat_HasRight(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_ORDER;
                } else if (KeyRepeat_HasLeft(keys)) {
                    OrderCatalog_CursorLeftFromBar(self);
                } else if (KeyRepeat_HasDown(keys)) {
                    self->cursor = ORDER_CATALOG_PLACE_QUIT;
                }
                break;
            default:
                break;
        }
    }
    return old != self->cursor;
}
CLEAN_AS(func_ov142_02299c64, OrderCatalog_MoveCursorByKeys)

/* func_ov142_02299f5c: the cursor to the tab at the cursor sprite's height (a height on a tab's
 * lower edge counts for the tab above). */
void OrderCatalog_CursorToTabs(OrderCatalog *self)
{
    int y = Glider_ScreenY(&self->cursor_sprite);
    if ((y & 0xf) == 0) {
        y--;
    }
    if (y < 0x18) {
        y = 0x18;
    }
    if (y >= 0xa8) {
        y = 0xa7;
    }
    self->cursor = (u8) ((y - 0x18) >> 4);
}
CLEAN_AS(func_ov142_02299f5c, OrderCatalog_CursorToTabs)

/* func_ov142_02299f8c: the cursor left from the bar: into the list, else (it is empty) to the
 * tabs. */
void OrderCatalog_CursorLeftFromBar(OrderCatalog *self)
{
    if (OrderCatalog_CursorToList(self) == 0) {
        OrderCatalog_CursorToTabs(self);
    }
}
CLEAN_AS(func_ov142_02299f8c, OrderCatalog_CursorLeftFromBar)

/* func_ov142_02299fa4: the cursor right from the tabs: into the list, else past it. */
int OrderCatalog_CursorRightFromTabs(OrderCatalog *self)
{
    int moved = OrderCatalog_CursorToList(self);
    if (moved != 0) {
        return moved;
    }
    return OrderCatalog_CursorRightFromList(self);
}
CLEAN_AS(func_ov142_02299fa4, OrderCatalog_CursorRightFromTabs)

/* func_ov142_02299fbc: the cursor into the list at the row at the cursor sprite's height (the
 * last row shown when below it); whether the list has a row. A list scrolled between rows is
 * scrolled to the row's edge: back when the cursor is at the first row, on (the cursor a row
 * up) when at the last one. */
int OrderCatalog_CursorToList(OrderCatalog *self)
{
    int rows = OrderCatalog_Count(self);
    if (rows == 0) {
        return 0;
    }
    if (rows > ORDER_CATALOG_ROWS) {
        rows = ORDER_CATALOG_ROWS;
    }
    int y = Glider_ScreenY(&self->cursor_sprite);
    if (y < 0x20) {
        y = 0x20;
    }
    if (y >= 0xa0) {
        y = 0x9f;
    }
    int within = self->scroll_target & 0xf;
    int row = (y - (0x20 - within)) >> 4;
    if (row >= rows) {
        row = rows - 1;
    }
    self->cursor = (u8) (row + ORDER_CATALOG_PLACE_ROW);
    if (within != 0) {
        if (row == 0) {
            self->scroll_target -= within;
        } else if (row == rows - 1) {
            self->cursor = (u8) (self->cursor - 1);
            self->scroll_target += 0x10 - (self->scroll_target & 0xf);
        }
    }
    return 1;
}
CLEAN_AS(func_ov142_02299fbc, OrderCatalog_CursorToList)

/* func_ov142_0229a05c: the cursor left from the buttons: to the bar, or past it when the list
 * does not scroll. */
void OrderCatalog_CursorLeftFromButtons(OrderCatalog *self)
{
    if (self->scroll_max == 0) {
        OrderCatalog_CursorLeftFromBar(self);
    } else {
        OrderCatalog_CursorToBar(self);
    }
}
CLEAN_AS(func_ov142_0229a05c, OrderCatalog_CursorLeftFromButtons)

/* func_ov142_0229a07c: the cursor right from the list: to the bar, or to the buttons when the
 * list does not scroll; answers the place. */
int OrderCatalog_CursorRightFromList(OrderCatalog *self)
{
    if (self->scroll_max == 0) {
        return OrderCatalog_CursorToButtons(self);
    }
    return OrderCatalog_CursorToBar(self);
}
CLEAN_AS(func_ov142_0229a07c, OrderCatalog_CursorRightFromList)

/* func_ov142_0229a09c: the cursor to the bar's place at the cursor sprite's height: the up
 * arrow, the down arrow or the thumb; answers it. */
int OrderCatalog_CursorToBar(OrderCatalog *self)
{
    if (Glider_ScreenY(&self->cursor_sprite) < 0x2b) {
        self->cursor = ORDER_CATALOG_PLACE_UP;
        return ORDER_CATALOG_PLACE_UP;
    }
    if (Glider_ScreenY(&self->cursor_sprite) > 0x93) {
        self->cursor = ORDER_CATALOG_PLACE_DOWN;
        return ORDER_CATALOG_PLACE_DOWN;
    }
    self->cursor = ORDER_CATALOG_PLACE_THUMB;
    return ORDER_CATALOG_PLACE_THUMB;
}
CLEAN_AS(func_ov142_0229a09c, OrderCatalog_CursorToBar)

/* func_ov142_0229a0d4: the cursor to the button at the cursor sprite's height; answers it. */
int OrderCatalog_CursorToButtons(OrderCatalog *self)
{
    if (Glider_ScreenY(&self->cursor_sprite) > 0x89) {
        self->cursor = ORDER_CATALOG_PLACE_QUIT;
        return ORDER_CATALOG_PLACE_QUIT;
    }
    self->cursor = ORDER_CATALOG_PLACE_ORDER;
    return ORDER_CATALOG_PLACE_ORDER;
}
CLEAN_AS(func_ov142_0229a0d4, OrderCatalog_CursorToButtons)

/* func_ov142_0229a1fc: the place touched at (x, y): the quit button, the order button (when
 * there is something to order), a tab, a row of the list that has an item, or none. */
int OrderCatalog_TouchedPlace(OrderCatalog *self, int x, int y)
{
    if (ButtonPanel_IsTouched(&self->panel, ORDER_CATALOG_BUTTON_QUIT)) {
        return ORDER_CATALOG_PLACE_QUIT;
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_ORDERABLE)) {
        if (x >= 0xc4 && x < 0xe8 && y >= 0x4d && y < 0x71) {
            return ORDER_CATALOG_PLACE_ORDER;
        }
    }
    if (x <= 0x1b) {
        if (y >= 0x18 && y < 0xa8) {
            return (u8) ((y - 0x18) >> 4);
        }
        return ORDER_CATALOG_PLACE_NONE;
    }
    if (x >= 0x38 && x <= 0x9c && y >= 0x20 && y < 0xa0) {
        int within = (int) ((u32) self->scroll_target & 0xf);
        int row = (y - (0x20 - within)) >> 4;
        if (row >= OrderCatalog_Count(self)) {
            return ORDER_CATALOG_PLACE_NONE;
        }
        return (u8) (row + ORDER_CATALOG_PLACE_ROW);
    }
    return ORDER_CATALOG_PLACE_NONE;
}
CLEAN_AS(func_ov142_0229a1fc, OrderCatalog_TouchedPlace)

/* func_ov142_0229a298: what place `place` does; whether it started something (the caller then
 * leaves the cursor be). Quit, the order (with something to order), the thumb pressed (moved by
 * the keys, sub state 5), accept, decline, an arrow held (unless the list is at that end, sub
 * state 7). A tab not highlighted plays its sound and fades the rows to its category; a row
 * with no fade going on picks its item (the sound when that changed the pick). */
int OrderCatalog_RunAction(OrderCatalog *self, int place)
{
    switch (place) {
        case ORDER_CATALOG_PLACE_QUIT:
            OrderCatalog_Quit(self);
            return 1;
        case ORDER_CATALOG_PLACE_ORDER:
            if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_ORDERABLE) != 0) {
                OrderCatalog_Order(self);
                return 1;
            }
            return 0;
        case ORDER_CATALOG_PLACE_THUMB:
            PushButton_Press(&self->thumb_button);
            PushButton_PressCue(&self->thumb_button);
            MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_THUMB_KEYS);
            return 1;
        case ORDER_CATALOG_PLACE_ACCEPT:
            OrderCatalog_Accept(self);
            return 1;
        case ORDER_CATALOG_PLACE_DECLINE:
            OrderCatalog_Decline(self);
            return 1;
        case ORDER_CATALOG_PLACE_UP:
            if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_AT_TOP) != 0) {
                return 0;
            }
            OrderCatalog_HoldUpArrow(self);
            MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_ARROW_KEYS);
            return 1;
        case ORDER_CATALOG_PLACE_DOWN:
            if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_AT_BOTTOM) != 0) {
                return 0;
            }
            OrderCatalog_HoldDownArrow(self);
            MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_ARROW_KEYS);
            return 1;
        default:
            if ((u32) place <= ORDER_CATALOG_PLACE_LAST_TAB) {
                if (self->tab != place) {
                    SoundSys_PlaySe(ORDER_CATALOG_SOUND_TAB);
                    OrderCatalog_StartFade(self, (u8) place);
                }
                return 0;
            }
            if ((u32) place >= ORDER_CATALOG_PLACE_ROW && (u32) place <= ORDER_CATALOG_PLACE_LAST_ROW) {
                if (self->fade_state != ORDER_CATALOG_FADE_NONE) {
                    return 0;
                }
                if (OrderCatalog_PickItem(self, self->category, (s16) (self->top_row + (place - ORDER_CATALOG_PLACE_ROW))) !=
                    0) {
                    SoundSys_PlaySe(ORDER_CATALOG_SOUND_PICK);
                }
            }
            return 0;
    }
}
CLEAN_AS(func_ov142_0229a298, OrderCatalog_RunAction)

/* func_ov142_0229aec4: the cursor sprite let up (the third of its set) and the sub state kept to
 * go back to once that has played (sub state 10). */
void OrderCatalog_ResumeAfterPress(OrderCatalog *self)
{
    Glider_ShowThirdOfSet(&self->cursor_sprite);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_PRESS_END);
}
CLEAN_AS(func_ov142_0229aec4, OrderCatalog_ResumeAfterPress)

/* func_ov142_0229aee8: the cursor sprite pressed (the second of its set), its place to act once
 * that has played (sub state 9). */
void OrderCatalog_PressCursor(OrderCatalog *self)
{
    Glider_ShowSecondOfSet(&self->cursor_sprite);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_PRESS);
}
CLEAN_AS(func_ov142_0229aee8, OrderCatalog_PressCursor)

/* func_ov142_0229af00: the cursor sprite shown (the first of its set) and updated. */
void OrderCatalog_ShowCursorSprite(OrderCatalog *self)
{
    Glider_ShowFirstOfSet(&self->cursor_sprite);
    catalog_update_cursor_sprite(self);
}
CLEAN_AS(func_ov142_0229af00, OrderCatalog_ShowCursorSprite)

/* func_ov142_0229af1c: the cursor sprite eased to (x, y) in three steps, the sub state kept to
 * come back to once it stops (sub state 8). */
void OrderCatalog_GlideCursorTo(OrderCatalog *self, int x, int y)
{
    Glider_EaseTo(&self->cursor_sprite, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_SPRITE_MOVE);
}
CLEAN_AS(func_ov142_0229af1c, OrderCatalog_GlideCursorTo)

/* func_ov142_0229af4c: the cursor sprite turned (set B at the quit button and the rows, else
 * set A) and eased to the cursor's place. */
void OrderCatalog_GlideCursor(OrderCatalog *self)
{
    u8 cursor = self->cursor;
    if (cursor == ORDER_CATALOG_PLACE_QUIT || catalog_is_row(cursor)) {
        Glider_TurnToSetB(&self->cursor_sprite);
    } else {
        Glider_TurnToSetA(&self->cursor_sprite);
    }
    int x = OrderCatalog_CursorX(self);
    int y = OrderCatalog_CursorY(self);
    OrderCatalog_GlideCursorTo(self, x, y);
}
CLEAN_AS(func_ov142_0229af4c, OrderCatalog_GlideCursor)

/* func_ov142_0229af94: the cursor sprite hidden (no animation) and updated. */
void OrderCatalog_HideCursorSprite(OrderCatalog *self)
{
    Glider_SetAnim(&self->cursor_sprite, 0);
    catalog_update_cursor_sprite(self);
}
CLEAN_AS(func_ov142_0229af94, OrderCatalog_HideCursorSprite)

/* func_ov142_0229afb0: the y of the cursor sprite at the cursor's place (0x60 for any other). */
int OrderCatalog_CursorY(OrderCatalog *self)
{
    u8 cursor = self->cursor;
    if (cursor <= ORDER_CATALOG_PLACE_LAST_TAB) {
        return cursor * 16 + ORDER_CATALOG_TAB_Y;
    }
    if (catalog_is_row(cursor)) {
        return (cursor - ORDER_CATALOG_PLACE_ROW) * 16 + ORDER_CATALOG_ROW_Y - (int) ((u32) self->scroll_target & 0xf);
    }
    switch (cursor) {
        case ORDER_CATALOG_PLACE_QUIT:
            return ButtonPanel_ButtonY(&self->panel, ORDER_CATALOG_BUTTON_QUIT);
        case ORDER_CATALOG_PLACE_ORDER:
            return ORDER_CATALOG_ORDER_Y;
        case ORDER_CATALOG_PLACE_THUMB:
            return PushButton_FaceY(&self->thumb_button);
        case ORDER_CATALOG_PLACE_ACCEPT:
            return ButtonPanel_ButtonY(&self->panel, ORDER_CATALOG_BUTTON_ACCEPT);
        case ORDER_CATALOG_PLACE_DECLINE:
            return ButtonPanel_ButtonY(&self->panel, ORDER_CATALOG_BUTTON_DECLINE);
        case ORDER_CATALOG_PLACE_UP:
            return ORDER_CATALOG_UP_Y;
        case ORDER_CATALOG_PLACE_DOWN:
            return ORDER_CATALOG_DOWN_Y;
        default:
            return 0x60;
    }
}
CLEAN_AS(func_ov142_0229afb0, OrderCatalog_CursorY)

/* func_ov142_0229b04c: ... its x (0x80 for any other). */
int OrderCatalog_CursorX(OrderCatalog *self)
{
    u8 cursor = self->cursor;
    if (cursor <= ORDER_CATALOG_PLACE_LAST_TAB) {
        return ORDER_CATALOG_TAB_X;
    }
    if (catalog_is_row(cursor)) {
        return ORDER_CATALOG_ROW_X;
    }
    switch (cursor) {
        case ORDER_CATALOG_PLACE_QUIT:
            return ButtonPanel_ButtonX(&self->panel, ORDER_CATALOG_BUTTON_QUIT);
        case ORDER_CATALOG_PLACE_ORDER:
            return ORDER_CATALOG_ORDER_X;
        case ORDER_CATALOG_PLACE_THUMB:
            return PushButton_FaceX(&self->thumb_button);
        case ORDER_CATALOG_PLACE_ACCEPT:
            return ButtonPanel_ButtonX(&self->panel, ORDER_CATALOG_BUTTON_ACCEPT);
        case ORDER_CATALOG_PLACE_DECLINE:
            return ButtonPanel_ButtonX(&self->panel, ORDER_CATALOG_BUTTON_DECLINE);
        case ORDER_CATALOG_PLACE_UP:
        case ORDER_CATALOG_PLACE_DOWN:
            return ORDER_CATALOG_ARROW_X;
        default:
            return 0x80;
    }
}
CLEAN_AS(func_ov142_0229b04c, OrderCatalog_CursorX)

/* func_ov142_0229b0d4: the cursor sprite put at the cursor's place, with animation 1, and
 * shown. */
void OrderCatalog_PlaceCursorSprite(OrderCatalog *self)
{
    int x = OrderCatalog_CursorX(self);
    int y = OrderCatalog_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
    Glider_SetAnim(&self->cursor_sprite, GLIDER_ANIM_SET_A);
    OrderCatalog_ShowCursorSprite(self);
}
CLEAN_AS(func_ov142_0229b0d4, OrderCatalog_PlaceCursorSprite)

/* func_ov142_0229b10c: the scene quit: main told nothing was ordered (GroupParams_SetC4C(0)),
 * the panel's quit button pressed (sub state 13) and the scene to close. */
void OrderCatalog_Quit(OrderCatalog *self)
{
    GroupParams_SetC4C(0);
    ButtonPanel_Select(&self->panel, ORDER_CATALOG_BUTTON_QUIT);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_PANEL_PRESSED);
    OrderCatalog_Close(self);
}
CLEAN_AS(func_ov142_0229b10c, OrderCatalog_Quit)

/* func_ov142_0229b138: the picked item ordered: the order button in palette 7, the cursor
 * sprite hidden, the panel wiped out for the confirmation (state 4, phase 1), the picked item's
 * page shown dimmed, and the order's sound. */
void OrderCatalog_Order(OrderCatalog *self)
{
    self->order_palette = 7;
    OrderCatalog_HideCursorSprite(self);
    MenuScene_SetState(catalog_scene(self), ORDER_CATALOG_STATE_CONFIRM_OUT);
    MenuScene_SetPhase(catalog_scene(self), 1);
    MenuScene_StartWipe(catalog_scene(self), 0, 0);
    OrderCatalog_ShowPickedPage(self);
    SoundSys_PlaySe(ORDER_CATALOG_SOUND_ORDER);
}
CLEAN_AS(func_ov142_0229b138, OrderCatalog_Order)

/* func_ov142_0229b174: the scene to close (state 2); in a room the item shown there is taken
 * away. */
void OrderCatalog_Close(OrderCatalog *self)
{
    MenuScene_SetState(catalog_scene(self), ORDER_CATALOG_STATE_START_WIPE_OUT);
    if (data_020e54a8 == 1 && OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_PREVIEW) != 0) {
        OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_PREVIEW);
        RoomPreview_Clear(RoomPreview_Get());
    }
}
CLEAN_AS(func_ov142_0229b174, OrderCatalog_Close)

/* func_ov142_0229b1b8: the confirmation, by touch or by the keys as the player last used. */
void OrderCatalog_ResumeConfirm(OrderCatalog *self)
{
    if (StateFlags_IsClear2()) {
        OrderCatalog_ConfirmByTouchStart(self);
    } else {
        OrderCatalog_ConfirmByKeysStart(self);
    }
}
CLEAN_AS(func_ov142_0229b1b8, OrderCatalog_ResumeConfirm)

/* func_ov142_0229b1d8: the confirmation by the keys: the cursor at decline, its sprite there,
 * the key repeat reset (sub state 12). */
void OrderCatalog_ConfirmByKeysStart(OrderCatalog *self)
{
    self->cursor = ORDER_CATALOG_PLACE_DECLINE;
    OrderCatalog_PlaceCursorSprite(self);
    MenuScene_ResetKeyRepeat(catalog_scene(self));
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_CONFIRM);
}
CLEAN_AS(func_ov142_0229b1d8, OrderCatalog_ConfirmByKeysStart)

/* func_ov142_0229b1fc: the confirmation by touch: the cursor sprite hidden (sub state 11). */
void OrderCatalog_ConfirmByTouchStart(OrderCatalog *self)
{
    OrderCatalog_HideCursorSprite(self);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_TOUCH_CONFIRM);
}
CLEAN_AS(func_ov142_0229b1fc, OrderCatalog_ConfirmByTouchStart)

/* func_ov142_0229b214: back to the catalog, by touch or by the keys as the player last used;
 * the cursor no longer kept. */
void OrderCatalog_Resume(OrderCatalog *self)
{
    if (StateFlags_IsClear2()) {
        OrderCatalog_ResumeByTouch(self);
    } else {
        OrderCatalog_ResumeByKeys(self);
    }
    OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_KEEP_CURSOR);
}
CLEAN_AS(func_ov142_0229b214, OrderCatalog_Resume)

/* func_ov142_0229b23c: the catalog by the keys: the cursor kept once (after a decline) or at
 * the first tab, its sprite there, the key repeat reset (sub state 4). */
void OrderCatalog_ResumeByKeys(OrderCatalog *self)
{
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_KEEP_CURSOR)) {
        OrderCatalog_ClearFlags(self, ORDER_CATALOG_FLAG_KEEP_CURSOR);
    } else {
        self->cursor = ORDER_CATALOG_PLACE_TAB;
    }
    OrderCatalog_PlaceCursorSprite(self);
    MenuScene_ResetKeyRepeat(catalog_scene(self));
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_BROWSE);
}
CLEAN_AS(func_ov142_0229b23c, OrderCatalog_ResumeByKeys)

/* func_ov142_0229b278: the catalog by touch: the cursor sprite hidden (sub state 0). */
void OrderCatalog_ResumeByTouch(OrderCatalog *self)
{
    OrderCatalog_HideCursorSprite(self);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_TOUCH_BROWSE);
}
CLEAN_AS(func_ov142_0229b278, OrderCatalog_ResumeByTouch)

/* func_ov142_0229b290 (sub state 13): while the panel's selected button is pressed, the cursor
 * sprite (when it shows) follows the press; once it is over, the sprite is hidden and the
 * states run (phase 1). */
void OrderCatalog_FollowPanelPress(OrderCatalog *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel)) {
        if (CellLayerSprite_AnimNumber(catalog_cursor_cells(self))) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->cursor_sprite, frame + x, frame + y);
        }
    } else {
        OrderCatalog_HideCursorSprite(self);
        MenuScene_SetPhase(catalog_scene(self), 1);
    }
}
CLEAN_AS(func_ov142_0229b290, OrderCatalog_FollowPanelPress)

/* func_ov142_0229b2f8: the order declined: the sound, the panel's decline button pressed, the
 * panel wiped out back to the catalog (state 6, set directly), the cursor kept at the order
 * button, the button in palette 5, the list scrolled to the picked row. */
void OrderCatalog_Decline(OrderCatalog *self)
{
    SoundSys_PlaySe(ORDER_CATALOG_SOUND_DECLINE);
    ButtonPanel_Select(&self->panel, ORDER_CATALOG_BUTTON_DECLINE);
    self->base.state = ORDER_CATALOG_STATE_BACK_OUT;
    MenuScene_StartWipe(catalog_scene(self), 0, 0);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_PANEL_PRESSED);
    OrderCatalog_SetFlags(self, ORDER_CATALOG_FLAG_KEEP_CURSOR);
    self->cursor = ORDER_CATALOG_PLACE_ORDER;
    self->order_palette = 5;
    OrderCatalog_ScrollToPickedRow(self);
}
CLEAN_AS(func_ov142_0229b2f8, OrderCatalog_Decline)

/* func_ov142_0229b350: the order accepted: the sound, the panel's accept button pressed, main
 * told an item is ordered (GroupParams_SetC4C(1)) and which (GroupParams_SetItemB), and the
 * scene to close. */
void OrderCatalog_Accept(OrderCatalog *self)
{
    SoundSys_PlaySe(ORDER_CATALOG_SOUND_PICK);
    ButtonPanel_Select(&self->panel, ORDER_CATALOG_BUTTON_ACCEPT);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_PANEL_PRESSED);
    GroupParams_SetC4C(1);
    GroupParams_SetItemB(*OrderCatalog_ItemAt(self, self->picked_row));
    OrderCatalog_Close(self);
}
CLEAN_AS(func_ov142_0229b350, OrderCatalog_Accept)

/* func_ov142_0229b394 (sub state 12): the confirmation by the keys. A touch goes on by touch.
 * Left and right (repeated) move the cursor to accept and decline; else A presses the cursor
 * sprite, START accepts and B declines.
 * QUIRK: START and B together both accept and decline. */
void OrderCatalog_ConfirmByKeys(OrderCatalog *self)
{
    if (MenuScene_TakeTouch(catalog_scene(self))) {
        OrderCatalog_ConfirmByTouchStart(self);
        return;
    }
    u8 old = self->cursor;
    MenuScene_LatchRepeatedKeys(catalog_scene(self));
    if (MenuScene_RepeatedLeft(catalog_scene(self))) {
        self->cursor = ORDER_CATALOG_PLACE_ACCEPT;
    } else if (MenuScene_RepeatedRight(catalog_scene(self))) {
        self->cursor = ORDER_CATALOG_PLACE_DECLINE;
    }
    if (old != self->cursor) {
        OrderCatalog_GlideCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & ORDER_CATALOG_PAD_A) != 0) {
        OrderCatalog_PressCursor(self);
        return;
    }
    if ((pressed & ORDER_CATALOG_PAD_START) != 0) {
        OrderCatalog_HideCursorSprite(self);
        OrderCatalog_Accept(self);
    }
    if ((data_021fbe40.pressed & ORDER_CATALOG_PAD_B) != 0) {
        OrderCatalog_HideCursorSprite(self);
        OrderCatalog_Decline(self);
    }
}
CLEAN_AS(func_ov142_0229b394, OrderCatalog_ConfirmByKeys)

/* func_ov142_0229b43c (sub state 11): the confirmation by touch. A button goes on by the keys;
 * a touch that went down or up this frame on the panel's accept or decline button does it. */
void OrderCatalog_ConfirmByTouch(OrderCatalog *self)
{
    if (MenuScene_TakeButtons(catalog_scene(self), 1)) {
        OrderCatalog_ConfirmByKeysStart(self);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        if (ButtonPanel_IsTouched(&self->panel, ORDER_CATALOG_BUTTON_ACCEPT)) {
            OrderCatalog_Accept(self);
        } else if (ButtonPanel_IsTouched(&self->panel, ORDER_CATALOG_BUTTON_DECLINE)) {
            OrderCatalog_Decline(self);
        }
    }
}
CLEAN_AS(func_ov142_0229b43c, OrderCatalog_ConfirmByTouch)

/* func_ov142_0229b4a8 (sub state 10): once the cursor sprite's let up has played, it is shown
 * and the sub state kept comes back. */
void OrderCatalog_WaitPressEnd(OrderCatalog *self)
{
    if (CellLayerSprite_IsDone(catalog_cursor_cells(self))) {
        OrderCatalog_ShowCursorSprite(self);
        MenuScene_SetSubState(catalog_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov142_0229b4a8, OrderCatalog_WaitPressEnd)

/* func_ov142_0229b4cc (sub state 9): once the cursor sprite's press has played, its place acts;
 * when that started nothing, back to the browse by the keys with the sprite let up. */
void OrderCatalog_WaitPressThenAct(OrderCatalog *self)
{
    if (CellLayerSprite_IsDone(catalog_cursor_cells(self))) {
        if (OrderCatalog_RunAction(self, self->cursor) == 0) {
            MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_BROWSE);
            OrderCatalog_ResumeAfterPress(self);
        }
    }
}
CLEAN_AS(func_ov142_0229b4cc, OrderCatalog_WaitPressThenAct)

/* Obj_ov142_0229c3e8::func_ov142_0229b500 (sub state 8): once the cursor sprite stops, the sub
 * state kept is run again, this frame. */
void OrderCatalog_WaitCursorSprite(OrderCatalog *self)
{
    if (Glider_IsMoving(&self->cursor_sprite) == 0) {
        MenuScene_SetSubState(catalog_scene(self), self->return_sub_state);
        OrderCatalog_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov142_0229c3e819func_ov142_0229b500Ev, OrderCatalog_WaitCursorSprite)

/* func_ov142_0229b528 (sub state 7): while A is held the list steps towards the held arrow;
 * then the arrows are let go, back to the browse by the keys with the sprite let up. */
void OrderCatalog_HoldArrowByKeys(OrderCatalog *self)
{
    if ((data_021fbe40.held & ORDER_CATALOG_PAD_A) != 0) {
        OrderCatalog_PageStep(self);
    } else {
        OrderCatalog_ReleaseArrows(self);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_BROWSE);
        OrderCatalog_ResumeAfterPress(self);
    }
}
CLEAN_AS(func_ov142_0229b528, OrderCatalog_HoldArrowByKeys)

/* func_ov142_0229b55c (sub state 6): once the thumb's release has played, back to the browse by
 * the keys with the sprite let up; the cursor sprite follows the thumb. */
void OrderCatalog_WaitThumbRelease(OrderCatalog *self)
{
    if (OrderCatalog_ThumbReleased(self) != 0) {
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_BROWSE);
        OrderCatalog_ResumeAfterPress(self);
    }
    int x = OrderCatalog_CursorX(self);
    int y = OrderCatalog_CursorY(self);
    Glider_PlaceAt(&self->cursor_sprite, x, y);
}
CLEAN_AS(func_ov142_0229b55c, OrderCatalog_WaitThumbRelease)

/* func_ov142_0229b59c (sub state 5): while A is held, up and down move the thumb and the cursor
 * sprite follows it; then the thumb is let go (sub state 6). */
void OrderCatalog_MoveThumbByKeys(OrderCatalog *self)
{
    if ((data_021fbe40.held & ORDER_CATALOG_PAD_A) != 0) {
        OrderCatalog_MoveThumbByPad(self);
        int x = OrderCatalog_CursorX(self);
        int y = OrderCatalog_CursorY(self);
        Glider_PlaceAt(&self->cursor_sprite, x, y);
    } else {
        OrderCatalog_ReleaseThumb(self);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_THUMB_RELEASE);
    }
}
CLEAN_AS(func_ov142_0229b59c, OrderCatalog_MoveThumbByKeys)

/* func_ov142_0229b5e8 (sub state 4): the catalog by the keys. A touch goes on by touch. A move
 * of the cursor glides its sprite there; else A presses the sprite, B quits and START orders
 * (with something to order). */
void OrderCatalog_BrowseByKeys(OrderCatalog *self)
{
    if (MenuScene_TakeTouch(catalog_scene(self))) {
        OrderCatalog_ResumeByTouch(self);
        return;
    }
    if (OrderCatalog_MoveCursorByKeys(self, (int) MenuScene_LatchRepeatedKeys(catalog_scene(self)))) {
        OrderCatalog_GlideCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & ORDER_CATALOG_PAD_A) != 0) {
        OrderCatalog_PressCursor(self);
        return;
    }
    if ((pressed & ORDER_CATALOG_PAD_B) != 0) {
        OrderCatalog_HideCursorSprite(self);
        OrderCatalog_Quit(self);
        return;
    }
    if ((pressed & ORDER_CATALOG_PAD_START) != 0) {
        if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_ORDERABLE)) {
            OrderCatalog_HideCursorSprite(self);
            OrderCatalog_Order(self);
        }
    }
}
CLEAN_AS(func_ov142_0229b5e8, OrderCatalog_BrowseByKeys)

/* func_ov142_0229b670 (sub state 3): while the pen is down the list steps towards the held
 * arrow; then the arrows are let go (sub state 0). */
void OrderCatalog_HoldArrowByTouch(OrderCatalog *self)
{
    if (data_021fbdd8 != 0) {
        OrderCatalog_PageStep(self);
        return;
    }
    OrderCatalog_ReleaseArrows(self);
    MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_TOUCH_BROWSE);
}
CLEAN_AS(func_ov142_0229b670, OrderCatalog_HoldArrowByTouch)

/* func_ov142_0229b698 (sub state 2): while the pen is down on the bar's track the thumb eases to
 * it; then the thumb is let go (sub state 0). */
void OrderCatalog_PressTrackByTouch(OrderCatalog *self)
{
    if (data_021fbdd8 != 0) {
        OrderCatalog_DragThumb(self, data_021f6c54, 1);
    } else {
        OrderCatalog_ReleaseThumb(self);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_TOUCH_BROWSE);
    }
}
CLEAN_AS(func_ov142_0229b698, OrderCatalog_PressTrackByTouch)

/* func_ov142_0229b6cc (sub state 1): while the pen is down the grabbed thumb follows it; then it
 * is let go (sub state 0). */
void OrderCatalog_DragThumbByTouch(OrderCatalog *self)
{
    if (data_021fbdd8 != 0) {
        OrderCatalog_DragThumb(self, data_021f6c54, 0);
    } else {
        OrderCatalog_ReleaseThumb(self);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_TOUCH_BROWSE);
    }
}
CLEAN_AS(func_ov142_0229b6cc, OrderCatalog_DragThumbByTouch)

/* func_ov142_0229b700 (sub state 0): the catalog by touch. A button goes on by the keys. A touch
 * that went down or up this frame acts at its place; else, with the bar shown, it grabs the
 * thumb (sub state 1), holds an arrow that is not at its end (sub state 3) or presses the bar's
 * track between them (sub state 2). */
void OrderCatalog_BrowseByTouch(OrderCatalog *self)
{
    if (MenuScene_TakeButtons(catalog_scene(self), 1) != 0) {
        OrderCatalog_ResumeByKeys(self);
        return;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;
    int place = OrderCatalog_TouchedPlace(self, x, y);
    if (place != ORDER_CATALOG_PLACE_NONE) {
        OrderCatalog_RunAction(self, place);
        return;
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_NO_BAR) != 0) {
        return;
    }
    if (OrderCatalog_GrabThumb(self, x, y) != 0) {
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_THUMB_DRAG);
        return;
    }
    if (x < 0xb8 || x >= 0xc8) {
        return;
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_AT_TOP) == 0 && y >= 0x19 && y < 0x29) {
        OrderCatalog_HoldUpArrow(self);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_ARROW_TOUCH);
        return;
    }
    if (OrderCatalog_TestFlags(self, ORDER_CATALOG_FLAG_AT_BOTTOM) == 0 && y >= 0x95 && y < 0xa5) {
        OrderCatalog_HoldDownArrow(self);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_ARROW_TOUCH);
        return;
    }
    if (y >= 0x2c && y <= 0x86) {
        PushButton_Press(&self->thumb_button);
        MenuScene_SetSubState(catalog_scene(self), ORDER_CATALOG_SUB_TRACK_PRESS);
    }
}
CLEAN_AS(func_ov142_0229b700, OrderCatalog_BrowseByTouch)

/* The table of member functions of the sub states (ov004/member_pointer.h): its guard, the
 * table and its constants. */
extern u32 data_ov142_0229c5e8;
extern MemberPointer data_ov142_0229c650[ORDER_CATALOG_SUB_STATES];
extern const MemberPointer data_ov142_0229c2a8, data_ov142_0229c2b0, data_ov142_0229c2b8, data_ov142_0229c2c0,
    data_ov142_0229c2d0, data_ov142_0229c2d8, data_ov142_0229c2e0, data_ov142_0229c2e8, data_ov142_0229c2f0,
    data_ov142_0229c2f8, data_ov142_0229c300, data_ov142_0229c308, data_ov142_0229c310, data_ov142_0229c320;

/* Obj_ov142_0229c3e8::func_ov142_0229bd90: the sub state's function (OrderCatalogSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 14; the game reads past the table for others. */
void OrderCatalog_RunSubState(OrderCatalog *self)
{
    static const MemberPointer *const sub_states[ORDER_CATALOG_SUB_STATES] = {
        &data_ov142_0229c310, &data_ov142_0229c308, &data_ov142_0229c2b8, &data_ov142_0229c300, &data_ov142_0229c2b0,
        &data_ov142_0229c2e8, &data_ov142_0229c2e0, &data_ov142_0229c2d8, &data_ov142_0229c2d0, &data_ov142_0229c320,
        &data_ov142_0229c2c0, &data_ov142_0229c2f8, &data_ov142_0229c2f0, &data_ov142_0229c2a8,
    };
    MemberTable_InitOnce(&data_ov142_0229c5e8, data_ov142_0229c650, sub_states, ORDER_CATALOG_SUB_STATES);
    MemberPointer_CallVoid(&data_ov142_0229c650[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov142_0229c3e819func_ov142_0229bd90Ev, OrderCatalog_RunSubState)
