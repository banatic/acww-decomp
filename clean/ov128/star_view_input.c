/* The telescope's view (star_view.h): the panel naming the constellation under the screen's
 * middle, the pointing hand, and the sub states that scroll the sky by its arrows with the pen
 * or the d-pad. */
#include "star_view.h"

#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/constellations.h"
#include "main/display_layers.h"
#include "main/oam_buffer.h"
#include "main/state_flags.h"
#include "main/text_label.h"
#include "main/text_string.h"

static_assert(offsetof(Constellation, name) == 0x1e, "name");

/* The pad and the touch (main's bytes, as ov120's town_map.c reads them). */
extern PadState data_021fbe40;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c58; /* x, while the pen is down */
extern u8 data_021f6c54; /* y, while the pen is down */
extern u8 data_021f6c60; /* x where the pen last went down */
extern u8 data_021f6c5c; /* y where the pen last went down */

/* The name panel's y above 0x60 by `name_slide` (0x20, 0x11, 2, 0) and its cells by its width
 * in cells (2-13). */
extern const s32 data_ov128_0229c890[];
extern const OamEntry *const data_ov128_0229ca00[];
/* Where the pointer rests by each arrow (StarScopeArrow): y and x. */
extern const u8 data_ov128_0229c8c0[STAR_SCOPE_ARROWS];
extern const u8 data_ov128_0229c8c4[STAR_SCOPE_ARROWS];
/* The sky's grid: a column of 16 OBJs and a row of 16. */
extern const OamEntry data_ov128_0229cca0[];
extern const OamEntry data_ov128_0229cc20[];

/* The pad's keys (PadState). */
#define STAR_VIEW_KEY_A 0x0001
#define STAR_VIEW_KEY_B 0x0002
#define STAR_VIEW_KEY_START 0x0008
#define STAR_VIEW_KEY_RIGHT 0x0010
#define STAR_VIEW_KEY_LEFT 0x0020
#define STAR_VIEW_KEY_UP 0x0040
#define STAR_VIEW_KEY_DOWN 0x0080
#define STAR_VIEW_KEY_Y 0x0800

/* The two Hangul characters ("ja", "ri") that make a name a constellation's. */
#define STAR_VIEW_SUFFIX_0 0xc790
#define STAR_VIEW_SUFFIX_1 0xb9ac

/* The free pointer's box: the view scrolls by 4 when it is pushed past an edge. */
#define STAR_VIEW_FREE_LEFT 0x30
#define STAR_VIEW_FREE_RIGHT 0xd0
#define STAR_VIEW_FREE_TOP 0x20
#define STAR_VIEW_FREE_BOTTOM 0xa0
#define STAR_VIEW_FREE_STEP 4

/* The closing button's corner: a touch right of and below it closes. */
#define STAR_VIEW_BUTTON_X 0xc0
#define STAR_VIEW_BUTTON_Y 0xab

#define STAR_VIEW_MIDDLE_X 0x80
#define STAR_VIEW_MIDDLE_Y 0x60

static MenuScene *star_view_scene(StarView *self)
{
    return &self->base;
}

/* The pointer's class's slot 3: its update. */
static void star_view_animate_pointer(StarView *self)
{
    void (*const *vtable)(void *) = *(void (*const *const *)(void *))(void *) &self->pointer;
    vtable[3](&self->pointer);
}

static int star_view_asr(int value, int shift)
{
    return value >= 0 ? value >> shift : ~(~value >> shift);
}

/* The pen touched the screen this frame. */
static int star_view_touch_began(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* func_ov128_0229b804: a frame of the name panel: rising to the top, then shown; while no
 * constellation is pointed at it counts 20 frames down and sinks (StarView_HideName); sunk, the
 * wanted name is shown (StarView_ApplyName). */
void StarView_StepName(StarView *self)
{
    switch (self->name_state) {
        case STAR_VIEW_NAME_RISING:
            if (self->name_slide < STAR_VIEW_NAME_SLIDE_TOP) {
                self->name_slide++;
            } else {
                self->name_state = STAR_VIEW_NAME_SHOWN;
                self->name_timer = STAR_VIEW_NAME_HOLD;
            }
            break;
        case STAR_VIEW_NAME_SHOWN:
            if (self->pointed == STAR_VIEW_NONE) {
                if (self->name_timer != 0) {
                    self->name_timer--;
                } else {
                    StarView_HideName(self);
                }
            } else {
                self->name_timer = STAR_VIEW_NAME_HOLD;
            }
            break;
        case STAR_VIEW_NAME_SINKING:
            if (self->name_slide != 0) {
                self->name_slide--;
            } else {
                StarView_ApplyName(self);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov128_0229b804, StarView_StepName)

/* func_ov128_0229b88c: a constellation newly pointed at becomes the wanted one. */
void StarView_FollowPointed(StarView *self)
{
    if (self->pointed != STAR_VIEW_NONE && self->wanted != self->pointed) {
        self->wanted = self->pointed;
        StarView_ChangeName(self);
    }
}
CLEAN_AS(func_ov128_0229b88c, StarView_FollowPointed)

/* func_ov128_0229b8bc: none wanted, and the panel sinks. */
void StarView_HideName(StarView *self)
{
    self->wanted = STAR_VIEW_NONE;
    self->name_state = STAR_VIEW_NAME_SINKING;
}
CLEAN_AS(func_ov128_0229b8bc, StarView_HideName)

/* func_ov128_0229b8d4: the wanted name, when it is the one held, shown at once; else the panel
 * sinks first. */
void StarView_ChangeName(StarView *self)
{
    if (self->wanted != STAR_VIEW_NONE && self->wanted == self->named) {
        StarView_ApplyName(self);
        return;
    }
    self->name_state = STAR_VIEW_NAME_SINKING;
}
CLEAN_AS(func_ov128_0229b8d4, StarView_ChangeName)

/* func_ov128_0229b90c: the wanted constellation's panel risen (hidden for none). A name other
 * than the one held is made again: the constellation's name, trimmed, with the suffix, in a box
 * of sub OBJ characters from 0xc6 as wide as the text (at least 2 cells), centred. */
void StarView_ApplyName(StarView *self)
{
    if (self->wanted == STAR_VIEW_NONE) {
        self->name_state = STAR_VIEW_NAME_HIDDEN;
        return;
    }
    self->name_state = STAR_VIEW_NAME_RISING;
    if (self->wanted != self->named) {
        u16 text[10];
        Constellation *constellation = (Constellation *) (uintptr_t) Constellations_Get(self->wanted);
        int length;

        TextString_ClearChars(text, 8);
        TextString_CopyChars(constellation->name, text, CONSTELLATIONS_NAME_LENGTH);
        length = TextString_TrimmedLength(constellation->name, CONSTELLATIONS_NAME_LENGTH);
        TextString_CopyChars(constellation->name, text, length);
        text[length] = STAR_VIEW_SUFFIX_0;
        text[length + 1] = STAR_VIEW_SUFFIX_1;
        TextLabel_SetFromWide(&self->name_label, text, (void *) (uintptr_t) (length + 2));
        self->name_cells = (u8) star_view_asr(TextLabel_TextWidth(&self->name_label) + 7, 3);
        if (self->name_cells < STAR_VIEW_NAME_MIN_CELLS) {
            self->name_cells = STAR_VIEW_NAME_MIN_CELLS;
        }
        TextLabel_OpenStyledBox2(&self->name_label, LAYER_SUB_OBJ, 0xc6, self->name_cells, 0xf, 0, 0);
        TextLabel_Show(&self->name_label, 1, 0);
        self->named = self->wanted;
    }
}
CLEAN_AS(func_ov128_0229b90c, StarView_ApplyName)

/* func_ov128_0229b9f0: the name panel drawn, unless hidden, at the screen's middle and its
 * slide's height (priority 1).
 * REQUIRES: `name_cells` is 2-13 and `name_slide` 0-3, the tables' sizes; the game's are. */
void StarView_DrawName(StarView *self)
{
    const OamEntry *cells;
    int y;

    if (self->name_state == STAR_VIEW_NAME_HIDDEN) {
        return;
    }
    cells = data_ov128_0229ca00[self->name_cells - STAR_VIEW_NAME_MIN_CELLS];
    y = data_ov128_0229c890[self->name_slide] + STAR_VIEW_MIDDLE_Y;
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, cells, STAR_VIEW_MIDDLE_X, y, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov128_0229b9f0, StarView_DrawName)

/* func_ov128_0229ba54: the constellation of the piece in the sky's cell under the screen's
 * middle (at the view's bounce), when there is one; else `pointed` is kept. */
void StarView_FindPointed(StarView *self)
{
    int column;
    int row;
    int y = StarScope_Bounce(&self->scope) + STAR_VIEW_MIDDLE_Y;

    if (StarScope_SkyCellAt(&self->scope, STAR_VIEW_MIDDLE_X, y, &column, &row) != 0) {
        int piece = StarScope_PieceAtCell(column, row);
        if (piece != -1) {
            self->pointed = StarScope_ConstellationOfPiece((u16) piece);
        }
    }
}
CLEAN_AS(func_ov128_0229ba54, StarView_FindPointed)

/* func_ov128_0229bae0: the arrow of the d-pad's key held (left, right, up as the arrow drawn at
 * the top, down as the one at the bottom, in that order), else STAR_SCOPE_ARROWS. */
int StarView_HeldArrow(StarView *self)
{
    u16 held = data_021fbe40.held;

    (void) self;
    if (held & STAR_VIEW_KEY_LEFT) {
        return STAR_SCOPE_ARROW_LEFT;
    }
    if (held & STAR_VIEW_KEY_RIGHT) {
        return STAR_SCOPE_ARROW_RIGHT;
    }
    if (held & STAR_VIEW_KEY_UP) {
        return STAR_SCOPE_ARROW_DOWN;
    }
    if (held & STAR_VIEW_KEY_DOWN) {
        return STAR_SCOPE_ARROW_UP;
    }
    return STAR_SCOPE_ARROWS;
}
CLEAN_AS(func_ov128_0229bae0, StarView_HeldArrow)

/* func_ov128_0229bb20: after the view moved: its scroll within a 16-pixel step kept for the
 * grid, and the constellation under the middle looked for. */
void StarView_UpdateView(StarView *self)
{
    int x = StarScope_ScrollX(&self->scope);
    int y = StarScope_ScrollY(&self->scope);

    self->fine_x = x & 0xf;
    self->fine_y = y & 0xf;
    StarView_FindPointed(self);
}
CLEAN_AS(func_ov128_0229bb20, StarView_UpdateView)

/* func_ov128_0229bb60: the sky's grid drawn `y` down (priority 2): its column at the middle,
 * moved with the fine vertical scroll, and its row moved with the fine horizontal scroll and
 * the view's bounce. */
void StarView_DrawGrid(StarView *self, int y)
{
    int middle_y = y + STAR_VIEW_MIDDLE_Y;

    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, data_ov128_0229cca0, STAR_VIEW_MIDDLE_X, middle_y - self->fine_y, -1, 2, 0x1000,
                       0x1000, 0, -1, 0, 0);
    middle_y += StarScope_Bounce(&self->scope);
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, data_ov128_0229cc20, STAR_VIEW_MIDDLE_X - self->fine_x, middle_y, -1, 2, 0x1000,
                       0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov128_0229bb60, StarView_DrawGrid)

/* func_ov128_0229bbe4: the pointer's release played, back to this sub state after it
 * (STAR_VIEW_SUB_RELEASE). */
void StarView_ReleasePointer(StarView *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_RELEASE);
}
CLEAN_AS(func_ov128_0229bbe4, StarView_ReleasePointer)

/* func_ov128_0229bc10: the pointer's press played (STAR_VIEW_SUB_PRESS). */
void StarView_PressPointer(StarView *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_PRESS);
}
CLEAN_AS(func_ov128_0229bc10, StarView_PressPointer)

/* func_ov128_0229bc30: the pointer shows the first of its set (at rest) and is updated. */
void StarView_ShowPointer(StarView *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    star_view_animate_pointer(self);
}
CLEAN_AS(func_ov128_0229bc30, StarView_ShowPointer)

/* func_ov128_0229bc50: the pointer eased to (`x`, `y`) in 3 steps, back to this sub state
 * when it stops (STAR_VIEW_SUB_GLIDE). */
void StarView_GlideTo(StarView *self, int x, int y)
{
    Glider_EaseTo(&self->pointer, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_GLIDE);
}
CLEAN_AS(func_ov128_0229bc50, StarView_GlideTo)

/* func_ov128_0229bc88: the pointer turned to its set (set C by arrow 3, else set A) and glided
 * to the cursor. */
void StarView_GlideToCursor(StarView *self)
{
    int x;
    int y;

    if (StarView_TestFlags(self, STAR_VIEW_FLAG_FREE) != 0) {
        Glider_TurnToSetA(&self->pointer);
    } else if (self->pointer_spot == STAR_SCOPE_ARROW_DOWN) {
        Glider_TurnToSetC(&self->pointer);
    } else {
        Glider_TurnToSetA(&self->pointer);
    }
    x = StarView_CursorX(self);
    y = StarView_CursorY(self);
    StarView_GlideTo(self, x, y);
}
CLEAN_AS(func_ov128_0229bc88, StarView_GlideToCursor)

/* func_ov128_0229bce4: the pointer hidden (animation 0) and updated. */
void StarView_HidePointer(StarView *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    star_view_animate_pointer(self);
}
CLEAN_AS(func_ov128_0229bce4, StarView_HidePointer)

/* func_ov128_0229bd08: the cursor's y: the free pointer's, else its spot's.
 * REQUIRES: `pointer_spot` is below 4 (it is 1). */
int StarView_CursorY(StarView *self)
{
    if (StarView_TestFlags(self, STAR_VIEW_FLAG_FREE) != 0) {
        return self->cursor_y;
    }
    return data_ov128_0229c8c0[self->pointer_spot];
}
CLEAN_AS(func_ov128_0229bd08, StarView_CursorY)

/* func_ov128_0229bd38: the cursor's x. */
int StarView_CursorX(StarView *self)
{
    if (StarView_TestFlags(self, STAR_VIEW_FLAG_FREE) != 0) {
        return self->cursor_x;
    }
    return data_ov128_0229c8c4[self->pointer_spot];
}
CLEAN_AS(func_ov128_0229bd38, StarView_CursorX)

/* func_ov128_0229bd68: the pointer put at the cursor in its set (C by arrow 3, else A) and
 * shown at rest. */
void StarView_PlacePointer(StarView *self)
{
    int x = StarView_CursorX(self);
    int y = StarView_CursorY(self);

    Glider_PlaceAt(&self->pointer, x, y);
    if (StarView_TestFlags(self, STAR_VIEW_FLAG_FREE)) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    } else if (self->pointer_spot == STAR_SCOPE_ARROW_DOWN) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_C);
    } else {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    }
    StarView_ShowPointer(self);
}
CLEAN_AS(func_ov128_0229bd68, StarView_PlacePointer)

/* func_ov128_0229bdd4: the scene closes: the wipe out is the next state (run once the button's
 * press is over, STAR_VIEW_SUB_BUTTON), the name panel sinks and the pointer is hidden. */
void StarView_Close(StarView *self)
{
    MenuScene_SetState(star_view_scene(self), STAR_VIEW_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_BUTTON);
    StarView_ClearFlags(self, STAR_VIEW_FLAG_INTERACTIVE);
    StarView_HideName(self);
    StarView_HidePointer(self);
}
CLEAN_AS(func_ov128_0229bdd4, StarView_Close)

/* func_ov128_0229be00: on to the pen, or to the keys when main's state flag 2 is set. */
void StarView_EnterInput(StarView *self)
{
    if (StateFlags_IsClear2() != 0) {
        StarView_EnterTouch(self);
    } else {
        StarView_EnterKeys(self);
    }
}
CLEAN_AS(func_ov128_0229be00, StarView_EnterInput)

/* func_ov128_0229be20: on to the keys: the pointer at its spot, the usual key repeat. */
void StarView_EnterKeys(StarView *self)
{
    StarView_ClearFlags(self, STAR_VIEW_FLAG_FREE);
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_KEYS);
    StarView_PlacePointer(self);
    MenuScene_ResetKeyRepeat(star_view_scene(self));
}
CLEAN_AS(func_ov128_0229be20, StarView_EnterKeys)

/* func_ov128_0229be44: on to the pen: the pointer hidden. */
void StarView_EnterTouch(StarView *self)
{
    StarView_HidePointer(self);
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_TOUCH);
}
CLEAN_AS(func_ov128_0229be44, StarView_EnterTouch)

/* func_ov128_0229be5c (sub state 10): once the button's press is over, phase 1 (the wipe out). */
void StarView_SubButton(StarView *self)
{
    if (PanelSprite_StepPress(&self->button) == 0) {
        MenuScene_SetPhase(star_view_scene(self), STAR_VIEW_PHASE_STATES);
    }
}
CLEAN_AS(func_ov128_0229be5c, StarView_SubButton)

/* func_ov128_0229be78 (sub state 9): once the release has played, the pointer at rest and back
 * to the sub state it left. */
void StarView_SubRelease(StarView *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->pointer) != 0) {
        StarView_ShowPointer(self);
        MenuScene_SetSubState(star_view_scene(self), self->return_sub_state);
    }
}
CLEAN_AS(func_ov128_0229be78, StarView_SubRelease)

/* func_ov128_0229bea8 (sub state 8): once the press has played, the free pointer's release
 * (back to STAR_VIEW_SUB_FREE); without the free pointer it waits on. */
void StarView_SubPress(StarView *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->pointer) != 0) {
        if (StarView_TestFlags(self, STAR_VIEW_FLAG_FREE) != 0) {
            MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_FREE);
            StarView_ReleasePointer(self);
        }
    }
}
CLEAN_AS(func_ov128_0229bea8, StarView_SubPress)

/* func_ov128_0229bedc (sub state 7): once the pointer has stopped, back to the sub state it
 * left, which runs at once. */
void StarView_SubGlide(StarView *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(star_view_scene(self), self->return_sub_state);
        StarView_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov128_0229cbc019func_ov128_0229bedcEv, StarView_SubGlide)

/* func_ov128_0229bf0c (sub state 6): a step of the nudge; at its end back to the keys. */
void StarView_SubKeyNudge(StarView *self)
{
    if (StarScope_StepNudge(&self->scope) != 0) {
        MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_KEYS);
    }
    StarView_UpdateView(self);
}
CLEAN_AS(func_ov128_0229bf0c, StarView_SubKeyNudge)

/* func_ov128_0229bf34 (sub state 5): while the same key is held its arrow scrolls; else the
 * arrow held nudges once more (STAR_VIEW_SUB_KEY_NUDGE). */
void StarView_SubKeyHold(StarView *self)
{
    if (StarView_HeldArrow(self) != self->arrow) {
        MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_KEY_NUDGE);
        StarScope_Nudge(&self->scope, self->arrow);
    } else {
        StarScope_HoldArrow(&self->scope, self->arrow, 1);
    }
    StarView_UpdateView(self);
}
CLEAN_AS(func_ov128_0229bf34, StarView_SubKeyHold)

/* func_ov128_0229bf80 (sub state 4): the keys. A touch goes on to the pen; B or START closes;
 * a d-pad key holds its arrow (STAR_VIEW_SUB_KEY_HOLD). */
void StarView_SubKeys(StarView *self)
{
    u16 pressed;

    if (MenuScene_TakeTouch(star_view_scene(self)) != 0) {
        StarView_EnterTouch(self);
        return;
    }
    pressed = data_021fbe40.pressed;
    if ((pressed & STAR_VIEW_KEY_B) != 0 || (pressed & STAR_VIEW_KEY_START) != 0) {
        StarView_Close(self);
        return;
    }
    self->arrow = (u8) StarView_HeldArrow(self);
    if (self->arrow == STAR_SCOPE_ARROWS) {
        return;
    }
    StarScope_HoldArrow(&self->scope, self->arrow, 1);
    StarView_UpdateView(self);
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_KEY_HOLD);
}
CLEAN_AS(func_ov128_0229bf80, StarView_SubKeys)

/* func_ov128_0229bff0 (sub state 3): the free pointer. A touch goes on to the pen; A presses;
 * Y goes back to the arrows. The d-pad moves the pointer by 4; pushed past the edges of its box
 * it stays there and the view scrolls by 4 instead (vertically without a bounce). */
void StarView_SubFree(StarView *self)
{
    u16 pressed;
    u16 held;
    int old_x;
    int old_y;

    if (MenuScene_TakeTouch(star_view_scene(self)) != 0) {
        StarView_EnterTouch(self);
        return;
    }
    pressed = data_021fbe40.pressed;
    if (pressed & STAR_VIEW_KEY_A) {
        StarView_PressPointer(self);
        return;
    }
    if (pressed & STAR_VIEW_KEY_Y) {
        StarView_ClearFlags(self, STAR_VIEW_FLAG_FREE);
        MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_KEYS);
        StarView_GlideToCursor(self);
        return;
    }

    old_x = self->cursor_x;
    old_y = self->cursor_y;
    held = data_021fbe40.held;
    if (held & STAR_VIEW_KEY_LEFT) {
        self->cursor_x = old_x - STAR_VIEW_FREE_STEP;
    } else if (held & STAR_VIEW_KEY_RIGHT) {
        self->cursor_x = old_x + STAR_VIEW_FREE_STEP;
    }
    if (held & STAR_VIEW_KEY_UP) {
        self->cursor_y -= STAR_VIEW_FREE_STEP;
    } else if (held & STAR_VIEW_KEY_DOWN) {
        self->cursor_y += STAR_VIEW_FREE_STEP;
    }
    if (old_x == self->cursor_x && old_y == self->cursor_y) {
        return;
    }

    if (self->cursor_x < STAR_VIEW_FREE_LEFT) {
        self->cursor_x = STAR_VIEW_FREE_LEFT;
        StarScope_ScrollHorizontally(&self->scope, -STAR_VIEW_FREE_STEP);
        StarView_UpdateView(self);
    } else if (self->cursor_x > STAR_VIEW_FREE_RIGHT) {
        self->cursor_x = STAR_VIEW_FREE_RIGHT;
        StarScope_ScrollHorizontally(&self->scope, STAR_VIEW_FREE_STEP);
        StarView_UpdateView(self);
    }
    if (self->cursor_y < STAR_VIEW_FREE_TOP) {
        self->cursor_y = STAR_VIEW_FREE_TOP;
        StarScope_ScrollVertically(&self->scope, -STAR_VIEW_FREE_STEP, 0);
        StarView_UpdateView(self);
    } else if (self->cursor_y > STAR_VIEW_FREE_BOTTOM) {
        self->cursor_y = STAR_VIEW_FREE_BOTTOM;
        StarScope_ScrollVertically(&self->scope, STAR_VIEW_FREE_STEP, 0);
        StarView_UpdateView(self);
    }
    Glider_PlaceAt(&self->pointer, self->cursor_x, self->cursor_y);
}
CLEAN_AS(func_ov128_0229bff0, StarView_SubFree)

/* func_ov128_0229c144 (sub state 2): a step of the nudge after the pen let go of an arrow; at
 * its end, with the pen down again on an arrow (where it last went down) that arrow is held
 * (STAR_VIEW_SUB_PEN_HOLD), else back to the pen. */
void StarView_SubPenNudge(StarView *self)
{
    if (StarScope_StepNudge(&self->scope) == 0) {
        StarView_UpdateView(self);
        return;
    }
    if (data_021fbdd8 != 0) {
        self->arrow = (u8) StarScope_ArrowAt(&self->scope, data_021f6c60, data_021f6c5c);
        if (self->arrow != STAR_SCOPE_ARROWS) {
            StarScope_HoldArrow(&self->scope, self->arrow, 1);
            StarView_UpdateView(self);
            MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_PEN_HOLD);
            return;
        }
    }
    MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_TOUCH);
    StarView_UpdateView(self);
}
CLEAN_AS(func_ov128_0229c144, StarView_SubPenNudge)

/* func_ov128_0229c1bc (sub state 1): while the pen is down its arrow scrolls; let go, the arrow
 * nudges once more (STAR_VIEW_SUB_PEN_NUDGE). */
void StarView_SubPenHold(StarView *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_PEN_NUDGE);
        StarScope_Nudge(&self->scope, self->arrow);
    } else {
        StarScope_HoldArrow(&self->scope, self->arrow, 1);
    }
    StarView_UpdateView(self);
}
CLEAN_AS(func_ov128_0229c1bc, StarView_SubPenHold)

/* func_ov128_0229c208 (sub state 0): the pen. A button goes on to the keys; a touch on an arrow
 * holds it (STAR_VIEW_SUB_PEN_HOLD), one at the bottom right corner closes. */
void StarView_SubTouch(StarView *self)
{
    int x;
    int y;

    if (MenuScene_TakeButtons(star_view_scene(self), 0) != 0) {
        StarView_EnterKeys(self);
        return;
    }
    if (!star_view_touch_began()) {
        return;
    }
    x = data_021f6c58;
    y = data_021f6c54;
    self->arrow = (u8) StarScope_ArrowAt(&self->scope, x, y);
    if (self->arrow != STAR_SCOPE_ARROWS) {
        StarScope_HoldArrow(&self->scope, self->arrow, 1);
        StarView_UpdateView(self);
        MenuScene_SetSubState(star_view_scene(self), STAR_VIEW_SUB_PEN_HOLD);
        return;
    }
    if (x >= STAR_VIEW_BUTTON_X && y > STAR_VIEW_BUTTON_Y) {
        StarView_Close(self);
    }
}
CLEAN_AS(func_ov128_0229c208, StarView_SubTouch)
