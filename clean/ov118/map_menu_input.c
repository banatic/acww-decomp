/* The town map of the menu (map_menu.h): the keys' focus and the pointer, the touches, and the
 * sub states the menu runs while it is in use. */
#include "map_menu.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/dual_cell_sprite.h"
#include "main/sound.h"
#include "ov002/key_repeat.h"
#include "ov090/menu_tabs.h"

/* The pad, and the pen: down, gone down this frame, its place (autoload_2/input.c). */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

#define MAP_MENU_PAD_A 0x0001
#define MAP_MENU_PAD_RIGHT 0x0010
#define MAP_MENU_PAD_LEFT 0x0020
#define MAP_MENU_PAD_UP 0x0040
#define MAP_MENU_PAD_DOWN 0x0080
#define MAP_MENU_PAD_R 0x0100
#define MAP_MENU_PAD_L 0x0200

/* The sounds: a list button, a row and a mark (both panned by the mark, MapMenu_PlayAtMark). */
#define MAP_MENU_SE_BUTTON 0x36
#define MAP_MENU_SE_ROW 0x37
#define MAP_MENU_SE_MARK 0x38

/* The free pointer's field: x 0x18-0x98, y 0x30-0xb0 (above it the bar of tabs, right of it the
 * list); it moves 4 pixels a frame. */
#define MAP_MENU_POINTER_LEFT 0x18
#define MAP_MENU_POINTER_RIGHT 0x98
#define MAP_MENU_POINTER_TOP 0x30
#define MAP_MENU_POINTER_BOTTOM 0xb0
#define MAP_MENU_POINTER_STEP 4

/* The list's first row's top, on the screen. */
#define MAP_MENU_LIST_TOP 0x50

/* The knob's travel on the bar, and where the pen's y lands on it from the track. */
#define MAP_MENU_KNOB_TRAVEL 0x58
#define MAP_MENU_TRACK_TOP 0x54

/* The cursor's animations (ov002/glide.h, GliderAnim) on the bar and elsewhere. */
#define MAP_MENU_CURSOR_ANIM_TABS 13
#define MAP_MENU_CURSOR_ANIM_SCREEN 1

static MenuScene *map_menu_scene(MapMenu *self)
{
    return &self->base;
}

/* The knob, as main's sprite of two cell animations it is built on. */
static DualCellSprite *map_menu_knob_sprite(MapMenu *self)
{
    return (DualCellSprite *) (void *) &self->knob_button;
}

/* The cursor, as main's layered sprite it is built on. */
static CellLayerSprite *map_menu_cursor_sprite(MapMenu *self)
{
    return (CellLayerSprite *) (void *) &self->cursor;
}

/* The cursor's update through its class (vtable slot 3, Glider_Update for the base). */
static void map_menu_update_cursor(MapMenu *self)
{
    Glider *cursor = &self->cursor;
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) cursor->vtable;
    vtable[3](cursor);
}

static int map_menu_focus_is_row(int focus)
{
    return focus >= MAP_MENU_FOCUS_ROW && focus <= MAP_MENU_FOCUS_LAST_ROW;
}

/* func_ov118_0229a4b8: the focus (or the free pointer) is pressed: answers 1 when the menu goes
 * on in another sub state, 2 when the shown list was switched, else 0.
 * - The pointer selects the mark under it (sound 0x38).
 * - The knob is pressed and held (sub state 7), the pointer following it.
 * - A list button switches to its list (sound 0x36), when it is not the shown one.
 * - A place of the bar switches to its tab (MapMenu_SelectTab).
 * - A row is selected (sound 0x37).
 * QUIRK: a row is the one shown at `shown_top`; within the frame the list was switched in, that
 * is 0xff and the selection wraps round to a mark. */
int MapMenu_Activate(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_POINTER) != 0) {
        MapMenu_Select(self, (unsigned char) (self->pointed_mark + MAP_MENU_SELECT_MARK));
        MapMenu_PlayAtMark(self, MAP_MENU_SE_MARK);
        return 0;
    }
    u8 focus = self->focus;
    if (focus == MAP_MENU_FOCUS_KNOB) {
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_KNOB_PRESS);
        PushButton_Press(&self->knob_button);
        MapMenu_SetFlags(self, MAP_MENU_FLAG_ON_KNOB);
        PushButton_PressCue(&self->knob_button);
        return 1;
    }
    if (focus == MAP_MENU_FOCUS_RESIDENTS) {
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES) != 0) {
            MapMenu_Select(self, MAP_MENU_SELECT_NONE);
            MapMenu_ShowResidents(self);
            SoundSys_PlaySe(MAP_MENU_SE_BUTTON);
            return 2;
        }
        return 0;
    }
    if (focus == MAP_MENU_FOCUS_PLACES) {
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES) == 0) {
            MapMenu_Select(self, MAP_MENU_SELECT_NONE);
            MapMenu_ShowPlaces(self);
            SoundSys_PlaySe(MAP_MENU_SE_BUTTON);
            return 2;
        }
        return 0;
    }
    if (focus <= MAP_MENU_FOCUS_LAST_TAB) {
        return MapMenu_SelectTab(self, focus) != 0 ? 1 : 0;
    }
    if (map_menu_focus_is_row(focus)) {
        MapMenu_Select(self, (unsigned char) (self->shown_top + (focus - MAP_MENU_FOCUS_ROW) + MAP_MENU_SELECT_ROW));
        MapMenu_PlayAtMark(self, MAP_MENU_SE_ROW);
        return 0;
    }
    return 0;
}
CLEAN_AS(func_ov118_0229a4b8, MapMenu_Activate)

/* The free pointer starts at (x, y): answer 2 of MapMenu_MoveFocus. */
static int map_menu_to_pointer(MapMenu *self, int x, int y)
{
    self->pointer_x = (u8) x;
    self->pointer_y = (u8) y;
    return 2;
}

/* func_ov118_0229a5bc: the focus moved by the latched keys `keys`. Answers 1 when it moved, 2
 * when it left for the free pointer (at the place set), 3 when the list scrolls instead, else 0.
 * - On the bar: left and right along it; down to the map's pointer below tabs 0-3, else to the
 *   residents' button (tabs 5-7) or the places' (tab 4).
 * - On the buttons: up to tab 5, down to the first row; left from the places' button to the
 *   pointer, else to the places' button; right to the knob (when the list scrolls) or the
 *   residents' button.
 * - On a row: right to the knob when the list scrolls; up and down, scrolling past the first
 *   and the sixth row, up from the top to the places' button; left to the pointer.
 * - On the knob: up to the residents' button; left to the row beside it. */
int MapMenu_MoveFocus(MapMenu *self, u32 keys)
{
    int keys_int = (int) keys;
    u8 before = self->focus;

    if (before <= MAP_MENU_FOCUS_LAST_TAB) {
        if (KeyRepeat_HasDown(keys_int) != 0) {
            if (self->focus <= 3) {
                int x = Glider_ScreenX(&self->cursor);
                map_menu_to_pointer(self, x, MAP_MENU_POINTER_TOP);
                Glider_TurnToSetA(&self->cursor);
                return 2;
            }
            self->focus = self->focus >= 5 ? MAP_MENU_FOCUS_RESIDENTS : MAP_MENU_FOCUS_PLACES;
            Glider_TurnToSetA(&self->cursor);
        } else if (KeyRepeat_HasLeft(keys_int) != 0) {
            if (self->focus != 0) {
                self->focus--;
            }
        } else if (KeyRepeat_HasRight(keys_int) != 0) {
            if (self->focus < MAP_MENU_FOCUS_LAST_TAB) {
                self->focus++;
            }
        }
    } else if (map_menu_focus_is_row(before)) {
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS) != 0 && KeyRepeat_HasRight(keys_int) != 0) {
            self->focus = MAP_MENU_FOCUS_KNOB;
        } else if (KeyRepeat_HasUp(keys_int) != 0) {
            if (self->focus > MAP_MENU_FOCUS_ROW) {
                self->focus--;
            } else if (self->scroll_target >> 4 > 0) {
                MapMenu_ScrollTo(self, self->scroll_target - MAP_MENU_ROW_HEIGHT);
                return 3;
            } else {
                self->focus = MAP_MENU_FOCUS_PLACES;
            }
        } else if (KeyRepeat_HasDown(keys_int) != 0) {
            int last = MapMenu_ShownCount(self) - 1;
            if (self->focus < MAP_MENU_FOCUS_LAST_ROW) {
                if (self->focus < last + MAP_MENU_FOCUS_ROW) {
                    self->focus++;
                }
            } else if ((self->scroll_target >> 4) + (MAP_MENU_VISIBLE_ROWS - 1) < last) {
                MapMenu_ScrollTo(self, self->scroll_target + MAP_MENU_ROW_HEIGHT);
                return 3;
            }
        } else if (KeyRepeat_HasLeft(keys_int) != 0) {
            return map_menu_to_pointer(self, MAP_MENU_POINTER_RIGHT, Glider_ScreenY(&self->cursor));
        }
    } else if (before == MAP_MENU_FOCUS_KNOB) {
        if (KeyRepeat_HasUp(keys_int) != 0) {
            self->focus = MAP_MENU_FOCUS_RESIDENTS;
        } else if (KeyRepeat_HasLeft(keys_int) != 0) {
            int y = PushButton_FaceY(&self->knob_button);
            if (y < MAP_MENU_LIST_TOP) {
                y = MAP_MENU_LIST_TOP;
            }
            if (y >= MAP_MENU_LIST_TOP + MAP_MENU_VISIBLE_ROWS * MAP_MENU_ROW_HEIGHT) {
                y = MAP_MENU_LIST_TOP + MAP_MENU_VISIBLE_ROWS * MAP_MENU_ROW_HEIGHT - 1;
            }
            self->focus = (u8) (((y - MAP_MENU_LIST_TOP) >> 4) + MAP_MENU_FOCUS_ROW);
        }
    } else if (before == MAP_MENU_FOCUS_RESIDENTS || before == MAP_MENU_FOCUS_PLACES) {
        if (KeyRepeat_HasUp(keys_int) != 0) {
            self->focus = MAP_MENU_TAB;
            Glider_TurnToSetC(&self->cursor);
        } else if (KeyRepeat_HasDown(keys_int) != 0) {
            self->focus = MAP_MENU_FOCUS_ROW;
        } else if (KeyRepeat_HasLeft(keys_int) != 0) {
            if (self->focus == MAP_MENU_FOCUS_PLACES) {
                return map_menu_to_pointer(self, MAP_MENU_POINTER_RIGHT, Glider_ScreenY(&self->cursor));
            }
            self->focus = MAP_MENU_FOCUS_PLACES;
        } else if (KeyRepeat_HasRight(keys_int) != 0) {
            if (self->focus == MAP_MENU_FOCUS_RESIDENTS && MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS) != 0) {
                self->focus = MAP_MENU_FOCUS_KNOB;
            } else {
                self->focus = MAP_MENU_FOCUS_RESIDENTS;
            }
        }
    }
    return before != self->focus ? 1 : 0;
}
CLEAN_AS(func_ov118_0229a5bc, MapMenu_MoveFocus)

/* func_ov118_0229a854: the cursor shows the first animation of its set, updated at once. */
void MapMenu_ShowCursor(MapMenu *self)
{
    Glider_ShowFirstOfSet(&self->cursor);
    map_menu_update_cursor(self);
}
CLEAN_AS(func_ov118_0229a854, MapMenu_ShowCursor)

/* func_ov118_0229a874: the cursor comes back up (sub state 6). */
void MapMenu_ReleaseCursor(MapMenu *self)
{
    Glider_ShowThirdOfSet(&self->cursor);
    MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_RELEASE);
}
CLEAN_AS(func_ov118_0229a874, MapMenu_ReleaseCursor)

/* func_ov118_0229a894: the cursor presses (sub state 5). */
void MapMenu_PressCursor(MapMenu *self)
{
    Glider_ShowSecondOfSet(&self->cursor);
    MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_PRESS);
}
CLEAN_AS(func_ov118_0229a894, MapMenu_PressCursor)

/* func_ov118_0229a8b4: the cursor goes to the focus: at once after MAP_MENU_FLAG_PLACE_NOW,
 * else gliding there in 3 steps while the menu waits (sub state 4, then back to this one). */
void MapMenu_MoveCursor(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACE_NOW) != 0) {
        int x = MapMenu_CursorX(self);
        int y = MapMenu_CursorY(self);
        Glider_PlaceAt(&self->cursor, x, y);
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_PLACE_NOW);
    } else {
        int x = MapMenu_CursorX(self);
        int y = MapMenu_CursorY(self);
        Glider_EaseTo(&self->cursor, x, y, 3, 1);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_GLIDE);
    }
}
CLEAN_AS(func_ov118_0229a8b4, MapMenu_MoveCursor)

/* func_ov118_0229a92c: the cursor shows nothing, updated at once. */
void MapMenu_HideCursor(MapMenu *self)
{
    Glider_SetAnim(&self->cursor, GLIDER_ANIM_NONE);
    map_menu_update_cursor(self);
}
CLEAN_AS(func_ov118_0229a92c, MapMenu_HideCursor)

/* func_ov118_0229a950: the cursor's y for the focus: the pointer's, the bar's 8, the buttons'
 * 0x40, a row's middle (16 pixels each from 0x58), the knob's face; 0x60 for anything else. */
int MapMenu_CursorY(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_POINTER) != 0) {
        return self->pointer_y;
    }
    u8 focus = self->focus;
    if (map_menu_focus_is_row(focus)) {
        return (focus - MAP_MENU_FOCUS_ROW) * MAP_MENU_ROW_HEIGHT + 0x58;
    }
    if (focus == MAP_MENU_FOCUS_RESIDENTS || focus == MAP_MENU_FOCUS_PLACES) {
        return 0x40;
    }
    if (focus <= MAP_MENU_FOCUS_LAST_TAB) {
        return 8;
    }
    if (focus == MAP_MENU_FOCUS_KNOB) {
        return PushButton_FaceY(&self->knob_button);
    }
    return 0x60;
}
CLEAN_AS(func_ov118_0229a950, MapMenu_CursorY)

/* func_ov118_0229a9ac: the cursor's x for the focus: the pointer's, the rows' 0xa0, the bar's
 * place (MenuTabs_TabX), the buttons' 0xd8 and 0xb4, the knob's face; 0x80 for anything else. */
int MapMenu_CursorX(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_POINTER)) {
        return self->pointer_x;
    }
    u8 focus = self->focus;
    if (map_menu_focus_is_row(focus)) {
        return 0xa0;
    }
    if (focus <= MAP_MENU_FOCUS_LAST_TAB) {
        return MenuTabs_TabX(focus);
    }
    if (focus == MAP_MENU_FOCUS_RESIDENTS) {
        return 0xd8;
    }
    if (focus == MAP_MENU_FOCUS_PLACES) {
        return 0xb4;
    }
    if (focus == MAP_MENU_FOCUS_KNOB) {
        return PushButton_FaceX(&self->knob_button);
    }
    return 0x80;
}
CLEAN_AS(func_ov118_0229a9ac, MapMenu_CursorX)

/* func_ov118_0229aa0c: the cursor put at the focus at once (the knob's focus, while the list
 * does not scroll, moved to the residents' button); a row's focus rounds the scroll's target to
 * a whole row; the cursor's animation for the bar or the screen, shown. */
void MapMenu_PlaceCursor(MapMenu *self)
{
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS) == 0) {
        if (self->focus == MAP_MENU_FOCUS_KNOB) {
            self->focus = MAP_MENU_FOCUS_RESIDENTS;
        }
    }
    int x = MapMenu_CursorX(self);
    int y = MapMenu_CursorY(self);
    Glider_PlaceAt(&self->cursor, x, y);
    if (map_menu_focus_is_row(self->focus)) {
        MapMenu_ScrollTo(self, self->scroll & ~0xf);
    }
    if (self->focus <= MAP_MENU_FOCUS_LAST_TAB) {
        Glider_SetAnim(&self->cursor, MAP_MENU_CURSOR_ANIM_TABS);
    } else {
        Glider_SetAnim(&self->cursor, MAP_MENU_CURSOR_ANIM_SCREEN);
    }
    MapMenu_ShowCursor(self);
}
CLEAN_AS(func_ov118_0229aa0c, MapMenu_PlaceCursor)

/* func_ov118_0229ab64: the pen went down on the list button that is not the shown list's (the
 * residents' at x 0xcd-0xe5, the places' at 0xaa-0xc2, y 0x33-0x4b): nothing selected, that
 * list shown from its top. Answers whether it was. */
int MapMenu_TouchListButton(MapMenu *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (y < 0x33 || y > 0x4b) {
        return 0;
    }
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES)) {
        if (x < 0xcd || x > 0xe5) {
            return 0;
        }
        MapMenu_Select(self, MAP_MENU_SELECT_NONE);
        MapMenu_ShowResidents(self);
    } else {
        if (x < 0xaa || x > 0xc2) {
            return 0;
        }
        MapMenu_Select(self, MAP_MENU_SELECT_NONE);
        MapMenu_ShowPlaces(self);
    }
    MapMenu_JumpTo(self, 0);
    self->shown_top = 0xff;
    return 1;
}
CLEAN_AS(func_ov118_0229ab64, MapMenu_TouchListButton)

/* func_ov118_0229abe0: while the knob is held, up and down (held) move the scroll's target by 4
 * pixels, within the list; the scroll is put there, with the knob's sound when it moved. */
void MapMenu_KnobKeys(MapMenu *self)
{
    int scroll = self->scroll_target;
    u16 held = data_021fbe40.held;
    if (held & MAP_MENU_PAD_UP) {
        scroll -= 4;
    } else if (held & MAP_MENU_PAD_DOWN) {
        scroll += 4;
    }
    int max = (int) MapMenu_MaxScroll(self);
    if (scroll < 0) {
        scroll = 0;
    } else if (scroll > max) {
        scroll = max;
    }
    if (scroll != self->scroll_target) {
        PushButton_ScrollCue(&self->knob_button);
    }
    MapMenu_JumpTo(self, (unsigned short) scroll);
}
CLEAN_AS(func_ov118_0229abe0, MapMenu_KnobKeys)

/* func_ov118_0229ac44: the knob dragged to `place` on the bar (0-0x58), the scroll put to match;
 * its sound each 4 pixels it moves. */
void MapMenu_DragKnobTo(MapMenu *self, int place)
{
    int knob = place;
    if (knob < 0) {
        knob = 0;
    } else if (knob > MAP_MENU_KNOB_TRAVEL) {
        knob = MAP_MENU_KNOB_TRAVEL;
    }
    int moved = knob - self->knob_cued;
    if (moved >= 4 || moved <= -4) {
        PushButton_ScrollCue(&self->knob_button);
        self->knob_cued = (u8) knob;
    }
    int scroll = knob * (int) MapMenu_MaxScroll(self) / MAP_MENU_KNOB_TRAVEL;
    MapMenu_JumpTo(self, (unsigned short) scroll);
}
CLEAN_AS(func_ov118_0229ac44, MapMenu_DragKnobTo)

/* func_ov118_0229aca0: while the list scrolls, the pen went down on the knob (it is taken, sub
 * state 1) or elsewhere on its track (x 0xe9-0xf4, y 0x57-0xad: sub state 2). Answers whether
 * it was. */
int MapMenu_TouchKnob(MapMenu *self)
{
    if (!MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS)) {
        return 0;
    }
    u8 x = data_021f6c58;
    u8 y = data_021f6c54;
    if (PushButton_Contains(&self->knob_button, x, y)) {
        self->grab_y = y;
        self->grab_knob = self->knob;
        self->knob_cued = self->grab_knob;
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_DRAG_KNOB);
        return 1;
    }
    if (x > 0xe8 && x < 0xf5 && y > 0x56 && y < 0xae) {
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_TRACK);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov118_0229aca0, MapMenu_TouchKnob)

/* func_ov118_0229b0e8: the pen went down on a mark: it is selected. Answers whether it was. */
int MapMenu_TouchMark(MapMenu *self)
{
    int mark = MapMenu_MarkAt(self, data_021f6c58, data_021f6c54);
    if (mark == MAP_MENU_NO_MARK) {
        return 0;
    }
    MapMenu_Select(self, (unsigned char) (mark + MAP_MENU_SELECT_MARK));
    return 1;
}
CLEAN_AS(func_ov118_0229b0e8, MapMenu_TouchMark)

/* func_ov118_0229b310: the pen went down on a row of the list (x 0x98-0xe8, y 0x50-0xaf): that
 * row is selected; not the sixth of the places, which has none. Answers whether it was.
 * QUIRK: a row past the residents' last is selected too. */
int MapMenu_TouchRow(MapMenu *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (x < 0x98 || x > 0xe8) {
        return 0;
    }
    if (y < MAP_MENU_LIST_TOP || y >= MAP_MENU_LIST_TOP + MAP_MENU_VISIBLE_ROWS * MAP_MENU_ROW_HEIGHT) {
        return 0;
    }
    int row = (y + (self->scroll - MAP_MENU_LIST_TOP)) >> 4;
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_PLACES) && row == MAP_MENU_PLACES) {
        return 0;
    }
    MapMenu_Select(self, (unsigned char) (row + MAP_MENU_SELECT_ROW));
    return 1;
}
CLEAN_AS(func_ov118_0229b310, MapMenu_TouchRow)

/* func_ov118_0229b834: the pointer leaves the map for the focus: nothing selected or lit, back
 * to the keys' sub state, the cursor to the focus. */
void MapMenu_LeavePointer(MapMenu *self)
{
    MapMenu_Select(self, MAP_MENU_SELECT_NONE);
    MapMenu_HighlightRow(self, MAP_MENU_NO_ROW);
    MapMenu_ClearFlags(self, MAP_MENU_FLAG_POINTER);
    MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_KEYS);
    MapMenu_MoveCursor(self);
}
CLEAN_AS(func_ov118_0229b834, MapMenu_LeavePointer)

/* func_ov118_0229b868: the menu goes over to the keys: the knob at rest, the cursor at the
 * focus, the key repeat reset; the pointer's sub state or the focus's. */
void MapMenu_EnterKeys(MapMenu *self)
{
    DualCellSprite_SetState(map_menu_knob_sprite(self), DUAL_CELL_SPRITE_STILL);
    MapMenu_PlaceCursor(self);
    MenuScene_ResetKeyRepeat(map_menu_scene(self));
    if (MapMenu_TestFlags(self, MAP_MENU_FLAG_POINTER) != 0) {
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_POINTER);
    } else {
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_KEYS);
    }
}
CLEAN_AS(func_ov118_0229b868, MapMenu_EnterKeys)

/* func_ov118_0229b8b0: the menu goes over to the pen: the cursor hidden, sub state 0. */
void MapMenu_EnterTouch(MapMenu *self)
{
    MapMenu_HideCursor(self);
    MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_TOUCH);
}
CLEAN_AS(func_ov118_0229b8b0, MapMenu_EnterTouch)

/* func_ov118_0229b8c8 (sub state 10): the free pointer. A touch goes over to the pen; A over a
 * mark presses; R and L switch to the next and previous tab. The d-pad (held) moves it 4 pixels
 * a frame: above y 0x30 the focus goes to the bar's place above it, right of x 0x98 to the
 * places' button (above y 0x50) or the row beside it (at most the list's last); else it stops at
 * x 0x18 and y 0xb0, and the mark under it is noted. */
void MapMenu_SubPointer(MapMenu *self)
{
    if (MenuScene_TakeTouch(map_menu_scene(self)) != 0) {
        MapMenu_EnterTouch(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & MAP_MENU_PAD_A) != 0 && self->pointed_mark != MAP_MENU_NO_MARK) {
        MapMenu_PressCursor(self);
        return;
    }
    if ((pressed & MAP_MENU_PAD_R) != 0) {
        MapMenu_SelectTab(self, MenuTabs_NextTab(MAP_MENU_TAB));
        return;
    }
    if ((pressed & MAP_MENU_PAD_L) != 0) {
        MapMenu_SelectTab(self, MenuTabs_PreviousTab(MAP_MENU_TAB));
        return;
    }

    int old_x = self->pointer_x;
    int old_y = self->pointer_y;
    int x = old_x;
    int y = old_y;
    u16 held = data_021fbe40.held;
    if ((held & MAP_MENU_PAD_UP) != 0) {
        y = old_y - MAP_MENU_POINTER_STEP;
    } else if ((held & MAP_MENU_PAD_DOWN) != 0) {
        y = old_y + MAP_MENU_POINTER_STEP;
    }
    if (y < MAP_MENU_POINTER_TOP) {
        self->focus = (u8) MenuTabs_TabAtX(old_x);
        Glider_TurnToSetC(&self->cursor);
        MapMenu_LeavePointer(self);
        return;
    }
    if (y > MAP_MENU_POINTER_BOTTOM) {
        y = MAP_MENU_POINTER_BOTTOM;
    }
    if ((held & MAP_MENU_PAD_LEFT) != 0) {
        x -= MAP_MENU_POINTER_STEP;
    } else if ((held & MAP_MENU_PAD_RIGHT) != 0) {
        x += MAP_MENU_POINTER_STEP;
    }
    if (x < MAP_MENU_POINTER_LEFT) {
        x = MAP_MENU_POINTER_LEFT;
    } else if (x > MAP_MENU_POINTER_RIGHT) {
        if (y < MAP_MENU_LIST_TOP) {
            self->focus = MAP_MENU_FOCUS_PLACES;
        } else {
            int row = (y - MAP_MENU_LIST_TOP) >> 4;
            if (row >= MapMenu_ShownCount(self)) {
                row = MapMenu_ShownCount(self) - 1;
            }
            self->focus = (u8) (row + MAP_MENU_FOCUS_ROW);
        }
        MapMenu_LeavePointer(self);
        return;
    }
    if (x == old_x && y == old_y) {
        return;
    }
    self->pointer_x = (u8) x;
    self->pointer_y = (u8) y;
    self->pointed_mark = (u8) MapMenu_MarkAt(self, self->pointer_x, self->pointer_y);
    Glider_PlaceAt(&self->cursor, self->pointer_x, self->pointer_y);
}
CLEAN_AS(func_ov118_0229b8c8, MapMenu_SubPointer)

/* func_ov118_0229ba34 (sub state 9): once the knob has come back up, the cursor does too and
 * stops following the knob. */
void MapMenu_SubKnobRelease(MapMenu *self)
{
    if (DualCellSprite_IsDone(map_menu_knob_sprite(self))) {
        MapMenu_ReleaseCursor(self);
        MapMenu_ClearFlags(self, MAP_MENU_FLAG_ON_KNOB);
    }
}
CLEAN_AS(func_ov118_0229ba34, MapMenu_SubKnobRelease)

/* func_ov118_0229ba60 (sub state 8): the knob held with A: up and down scroll; A let go
 * releases it (sub state 9). */
void MapMenu_SubKnobHeld(MapMenu *self)
{
    if ((data_021fbe40.held & MAP_MENU_PAD_A) == 0) {
        DualCellSprite_SetState(map_menu_knob_sprite(self), DUAL_CELL_SPRITE_PLAY_B);
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_KNOB_RELEASE);
    } else {
        MapMenu_KnobKeys(self);
    }
}
CLEAN_AS(func_ov118_0229ba60, MapMenu_SubKnobHeld)

/* func_ov118_0229ba98 (sub state 7): once the knob's press has played, it is held (sub
 * state 8). */
void MapMenu_SubKnobPress(MapMenu *self)
{
    if (DualCellSprite_IsDone(map_menu_knob_sprite(self))) {
        MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_KNOB_HELD);
    }
}
CLEAN_AS(func_ov118_0229ba98, MapMenu_SubKnobPress)

/* func_ov118_0229babc (sub state 6): once the cursor has come back up, it is shown and the
 * pointer's or the focus's sub state goes on. */
void MapMenu_SubRelease(MapMenu *self)
{
    if (CellLayerSprite_IsDone(map_menu_cursor_sprite(self)) != 0) {
        MapMenu_ShowCursor(self);
        if (MapMenu_TestFlags(self, MAP_MENU_FLAG_POINTER) != 0) {
            MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_POINTER);
        } else {
            MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_KEYS);
        }
    }
}
CLEAN_AS(func_ov118_0229babc, MapMenu_SubRelease)

/* func_ov118_0229bb00 (sub state 5): once the cursor's press has played, the focus is pressed
 * (MapMenu_Activate) and the cursor comes back up, unless the menu went on elsewhere; a switched
 * list is shown from its top. */
void MapMenu_SubPress(MapMenu *self)
{
    if (CellLayerSprite_IsDone(map_menu_cursor_sprite(self)) == 0) {
        return;
    }
    int result = MapMenu_Activate(self);
    if (result == 1) {
        return;
    }
    if (result == 2) {
        MapMenu_JumpTo(self, 0);
        self->shown_top = 0xff;
        MapMenu_ReleaseCursor(self);
    } else {
        MapMenu_ReleaseCursor(self);
    }
}
CLEAN_AS(func_ov118_0229bb00, MapMenu_SubPress)

/* Obj_ov118_0229cc08::func_ov118_0229bb48 (sub state 4): once the cursor's glide is over, the
 * sub state it was started from goes on, this frame. */
void MapMenu_SubGlide(MapMenu *self)
{
    if (Glider_IsMoving(&self->cursor) == 0) {
        MenuScene_SetSubState(map_menu_scene(self), self->return_sub_state);
        MapMenu_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov118_0229cc0819func_ov118_0229bb48Ev, MapMenu_SubGlide)

/* func_ov118_0229bb74 (sub state 3): the keys' focus. A touch goes over to the pen. A move of
 * the focus glides the cursor there (to a row, the scroll rounded to a whole row while the list
 * scrolls); a move to the map starts the free pointer (sub state 10) with nothing selected and
 * the mark under it noted; a scroll glides the cursor along. Else A presses, R and L switch to
 * the next and previous tab. */
void MapMenu_SubKeys(MapMenu *self)
{
    if (MenuScene_TakeTouch(map_menu_scene(self))) {
        MapMenu_EnterTouch(self);
        return;
    }
    switch (MapMenu_MoveFocus(self, MenuScene_LatchRepeatedKeys(map_menu_scene(self)))) {
        case 1:
            if (MapMenu_TestFlags(self, MAP_MENU_FLAG_SCROLLS)) {
                if (map_menu_focus_is_row(self->focus)) {
                    MapMenu_ScrollTo(self, self->scroll & ~0xf);
                }
            }
            MapMenu_MoveCursor(self);
            break;
        case 2:
            MapMenu_Select(self, MAP_MENU_SELECT_NONE);
            MapMenu_HighlightRow(self, MAP_MENU_NO_ROW);
            self->pointed_mark = (u8) MapMenu_MarkAt(self, self->pointer_x, self->pointer_y);
            MapMenu_SetFlags(self, MAP_MENU_FLAG_POINTER);
            MenuScene_SetSubState(map_menu_scene(self), MAP_MENU_SUB_POINTER);
            MapMenu_MoveCursor(self);
            break;
        case 3:
            MapMenu_MoveCursor(self);
            break;
        default: {
            u16 pressed = data_021fbe40.pressed;
            if (pressed & MAP_MENU_PAD_A) {
                MapMenu_PressCursor(self);
            } else if (pressed & MAP_MENU_PAD_R) {
                MapMenu_SelectTab(self, MenuTabs_NextTab(MAP_MENU_TAB));
            } else if (pressed & MAP_MENU_PAD_L) {
                MapMenu_SelectTab(self, MenuTabs_PreviousTab(MAP_MENU_TAB));
            }
            break;
        }
    }
}
CLEAN_AS(func_ov118_0229bb74, MapMenu_SubKeys)

/* func_ov118_0229bc7c (sub state 2): the pen held on the knob's track: the knob moves towards
 * the pen's y by 8 pixels a frame. When the pen is up the knob is let go and the menu goes back
 * to the pen's sub state 0 (the knob moves once more all the same). */
void MapMenu_SubTrack(MapMenu *self)
{
    if (data_021fbdd8 == 0) {
        DualCellSprite_SetState(map_menu_knob_sprite(self), DUAL_CELL_SPRITE_PLAY_B);
        MapMenu_EnterTouch(self);
    }
    int knob = self->knob;
    Approach_S32Again(&knob, data_021f6c54 - MAP_MENU_TRACK_TOP, 8);
    MapMenu_DragKnobTo(self, knob);
}
CLEAN_AS(func_ov118_0229bc7c, MapMenu_SubTrack)

/* func_ov118_0229bccc (sub state 1): the knob dragged by the pen, from where it was taken.
 * When the pen is up it is let go and the menu goes back to sub state 0 (the knob moves once
 * more all the same). */
void MapMenu_SubDragKnob(MapMenu *self)
{
    if (data_021fbdd8 == 0) {
        DualCellSprite_SetState(map_menu_knob_sprite(self), DUAL_CELL_SPRITE_PLAY_B);
        MapMenu_EnterTouch(self);
    }
    MapMenu_DragKnobTo(self, self->grab_knob + (data_021f6c54 - self->grab_y));
}
CLEAN_AS(func_ov118_0229bccc, MapMenu_SubDragKnob)

/* func_ov118_0229bd14 (sub state 0): the pen. A button goes over to the keys. When the pen went
 * down: on a list button (sound 0x36), on the knob or its track (the knob pressed), on a mark
 * (sound 0x38) or on a row (sound 0x37), in that order. */
void MapMenu_SubTouch(MapMenu *self)
{
    if (MenuScene_TakeButtons(map_menu_scene(self), 1) != 0) {
        MapMenu_EnterKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    if (MapMenu_TouchListButton(self) != 0) {
        SoundSys_PlaySe(MAP_MENU_SE_BUTTON);
        return;
    }
    if (MapMenu_TouchKnob(self) != 0) {
        PushButton_Press(&self->knob_button);
        return;
    }
    if (MapMenu_TouchMark(self) != 0) {
        MapMenu_PlayAtMark(self, MAP_MENU_SE_MARK);
        return;
    }
    if (MapMenu_TouchRow(self) != 0) {
        MapMenu_PlayAtMark(self, MAP_MENU_SE_ROW);
        return;
    }
}
CLEAN_AS(func_ov118_0229bd14, MapMenu_SubTouch)

/* func_ov118_0229c438: a switch to the bar's `tab` (-1 for none; this menu's own tab is
 * none either): the bar's menu told (MenuTabs_SelectTab) and the menu leaves (state 7, phase 1).
 * Answers whether it switched. */
int MapMenu_SelectTab(MapMenu *self, int tab)
{
    Process *parent = Process_GetParent((Process *) (void *) self);
    if (tab == -1 || tab == MAP_MENU_TAB) {
        return 0;
    }
    MenuTabs_SelectTab((MenuTabs *) (void *) parent, (u8) tab);
    self->base.state = MAP_MENU_STATE_LEAVE;
    MenuScene_SetPhase(map_menu_scene(self), MAP_MENU_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov118_0229c438, MapMenu_SelectTab)
