/* The input of overlay 146's scene (wfc_host_list.h): the cursor and its pointer, what A, B and
 * the pen do, the choice and the quit, and the scene's sub states. */
#include "wfc_host_list.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/input.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/group_params.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"

/* The pad (autoload_2/input.h). */
extern PadState data_021fbe40;
#define WFC_HOST_LIST_PAD_A 0x0001
#define WFC_HOST_LIST_PAD_B 0x0002

/* The touch (main's bytes, as ov102's storage_scene.c reads them) and the pen (as
 * menu_scene.c reads it). */
extern u8 data_021f6c58, data_021f6c54;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* The scene's sounds (main/sound.h): a friend chosen in the list, the scene ended by the go
 * button and by the quit button. */
#define WFC_HOST_LIST_SOUND_PICK 0x29
#define WFC_HOST_LIST_SOUND_GO 0x27
#define WFC_HOST_LIST_SOUND_QUIT 0x28

/* The frames between the choice or the quit and the wipe out. */
#define WFC_HOST_LIST_CLOSE_DELAY 5

/* The pointer's glides: their steps. */
#define WFC_HOST_LIST_GLIDE_STEPS 3

/* The rows' place on screen: the first at y 0x38, 16 pixels each, the last reachable by the keys
 * the sixth (cursor 8). */
#define WFC_HOST_LIST_ROWS_TOP 0x38
#define WFC_HOST_LIST_LAST_KEY_ROW 8

static MenuScene *wfc_host_list_input_base(WfcHostList *self)
{
    return &self->base;
}

static CellLayerSprite *wfc_host_list_pointer_cells(WfcHostList *self)
{
    /* The pointer's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->pointer;
}

/* The pointer's update through its class (vtable slot 3), and what it leaves as its result. */
static int wfc_host_list_update_pointer(WfcHostList *self)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) (const void *) &self->pointer;
    return ((int (*)(void *))(uintptr_t) vtable[3])(&self->pointer);
}

/* The scroll target brought down to a whole row. */
static void wfc_host_list_align_target(WfcHostList *self)
{
    int part = self->scroll_target & 0xf;
    if (part != 0) {
        self->scroll_target -= part;
    }
}

static int wfc_host_list_is_row(unsigned int cursor)
{
    return cursor >= WFC_HOST_LIST_CURSOR_FIRST_ROW && cursor <= 9;
}

/* --- The cursor --- */

/* func_ov146_022997ec: from the scroll bar to the rows (the go button when no friend hosts): the
 * row at the pointer's height, which is kept within the rows' 0x38-0xa7.
 * QUIRK: with the target 15 past a whole row and the pointer at 0xa7 this gives cursor 10, below
 * the rows. */
void WfcHostList_CursorFromPointer(WfcHostList *self)
{
    if (self->host_count == 0) {
        self->cursor = WFC_HOST_LIST_CURSOR_GO;
        return;
    }
    int y = Glider_ScreenY(&self->pointer);
    if (y < WFC_HOST_LIST_ROWS_TOP) {
        y = WFC_HOST_LIST_ROWS_TOP;
    }
    if (y > 0xa7) {
        y = 0xa7;
    }
    y -= WFC_HOST_LIST_ROWS_TOP - (self->scroll_target & 0xf);
    self->cursor = (u8) ((y >> 4) + WFC_HOST_LIST_CURSOR_FIRST_ROW);
}
CLEAN_AS(func_ov146_022997ec, WfcHostList_CursorFromPointer)

/* func_ov146_02299838: the cursor to the last row the keys reach, the target down to a whole
 * row. */
void WfcHostList_CursorToLastRow(WfcHostList *self)
{
    self->cursor = WFC_HOST_LIST_LAST_KEY_ROW;
    wfc_host_list_align_target(self);
}
CLEAN_AS(func_ov146_02299838, WfcHostList_CursorToLastRow)

/* func_ov146_0229985c: the cursor moved by the d-pad's repeated keys (`keys`, as
 * MenuScene_LatchRepeatedKeys returns them).
 *
 * - In the rows: right to the bar; up a row (at the top row the list scrolls up a row, or to
 *   its top, instead); down a row (from the sixth row the list scrolls down a row instead,
 *   while it can), and from the last friend to the quit button.
 * - On the quit button: up to the last row (when a friend hosts), right to the go button.
 * - On the go button: up to the last row (to the bar when no friend hosts), left to the quit
 *   button, right to the bar.
 * - On the bar: down to the go button, left to the row at the pointer.
 *
 * Answers 1 when the cursor or the target moved. */
int WfcHostList_MoveCursorByKeys(WfcHostList *self, u32 keys)
{
    unsigned int was = self->cursor;

    if (wfc_host_list_is_row(was)) {
        if (KeyRepeat_HasRight((int) keys) != 0) {
            self->cursor = WFC_HOST_LIST_CURSOR_BAR;
        } else if (KeyRepeat_HasUp((int) keys) != 0) {
            if (self->cursor > WFC_HOST_LIST_CURSOR_FIRST_ROW) {
                self->cursor--;
                if (self->cursor == WFC_HOST_LIST_CURSOR_FIRST_ROW) {
                    wfc_host_list_align_target(self);
                }
                return 1;
            }
            int target = self->scroll_target;
            if (target >= 0x10) {
                self->scroll_target -= 0x10;
                return 1;
            }
            if (target > 0) {
                self->scroll_target = 0;
                return 1;
            }
        } else if (KeyRepeat_HasDown((int) keys) != 0) {
            u8 cursor = self->cursor;
            if (cursor - WFC_HOST_LIST_CURSOR_FIRST_ROW + self->first_row >= self->host_count - 1) {
                self->cursor = WFC_HOST_LIST_CURSOR_QUIT;
            } else if (cursor < WFC_HOST_LIST_LAST_KEY_ROW) {
                self->cursor++;
            } else {
                int target = self->scroll_target;
                int part = target & 0xf;
                if (part != 0) {
                    self->scroll_target += 0x10 - part;
                    return 1;
                }
                if (target <= WFC_HOST_LIST_SCROLL_MAX - 0x10) {
                    self->scroll_target += 0x10;
                    return 1;
                }
                self->cursor = WFC_HOST_LIST_CURSOR_QUIT;
            }
        }
    } else {
        switch (was) {
            case WFC_HOST_LIST_CURSOR_QUIT:
                if (KeyRepeat_HasUp((int) keys) != 0) {
                    if (self->host_count != 0) {
                        WfcHostList_CursorToLastRow(self);
                    }
                } else if (KeyRepeat_HasRight((int) keys) != 0) {
                    self->cursor = WFC_HOST_LIST_CURSOR_GO;
                }
                break;
            case WFC_HOST_LIST_CURSOR_GO:
                if (KeyRepeat_HasUp((int) keys) != 0) {
                    if (self->host_count != 0) {
                        WfcHostList_CursorToLastRow(self);
                    } else {
                        self->cursor = WFC_HOST_LIST_CURSOR_BAR;
                    }
                } else if (KeyRepeat_HasLeft((int) keys) != 0) {
                    self->cursor = WFC_HOST_LIST_CURSOR_QUIT;
                } else if (KeyRepeat_HasRight((int) keys) != 0) {
                    self->cursor = WFC_HOST_LIST_CURSOR_BAR;
                }
                break;
            case WFC_HOST_LIST_CURSOR_BAR:
                if (KeyRepeat_HasDown((int) keys) != 0) {
                    self->cursor = WFC_HOST_LIST_CURSOR_GO;
                } else if (KeyRepeat_HasLeft((int) keys) != 0) {
                    WfcHostList_CursorFromPointer(self);
                }
                break;
            default:
                break;
        }
    }
    return was != self->cursor;
}
CLEAN_AS(func_ov146_0229985c, WfcHostList_MoveCursorByKeys)

/* func_ov146_02299a4c: A at the cursor `cursor`.
 *
 * - A row: its friend, when it can be chosen, is chosen (with sound 0x29), and the pointer is to
 *   glide quietly to the go button. Answers 0.
 * - The bar: the knob pressed (its cue), the knob then moved by the keys (sub state 4).
 * - The go button: the choice, while a joinable friend is chosen; else answers 0.
 * - The quit button: the quit.
 *
 * Answers 1 when it acted, else 0. */
int WfcHostList_Activate(WfcHostList *self, unsigned int cursor)
{
    if (wfc_host_list_is_row(cursor)) {
        int place = (int) ((unsigned int) self->first_row + cursor - WFC_HOST_LIST_CURSOR_FIRST_ROW);
        if (place >= WFC_HOST_LIST_FRIENDS) {
            return 0;
        }
        u8 friend_index = self->list[place];
        if (WfcHostList_IsJoinable(self, friend_index) != 0) {
            self->chosen = friend_index;
            SoundSys_PlaySe(WFC_HOST_LIST_SOUND_PICK);
            WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_CHOSE_ROW);
            WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_QUIET_GLIDE);
        }
        return 0;
    }

    switch (cursor) {
        case WFC_HOST_LIST_CURSOR_BAR:
            PushButton_Press(&self->knob_button);
            PushButton_PressCue(&self->knob_button);
            MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_KNOB_KEYS);
            return 1;
        case WFC_HOST_LIST_CURSOR_GO:
            if (self->go_palette == WFC_HOST_LIST_BUTTON_UP) {
                WfcHostList_Choose(self);
                return 1;
            }
            return 0;
        case WFC_HOST_LIST_CURSOR_QUIT:
            WfcHostList_Quit(self);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov146_02299a4c, WfcHostList_Activate)

/* --- The pointer --- */

/* func_ov146_0229a464: the pointer's press played (the third animation of its set), then back
 * to this sub state (sub state 8). */
void WfcHostList_PressPointer(WfcHostList *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_POINTER_PRESS);
}
CLEAN_AS(func_ov146_0229a464, WfcHostList_PressPointer)

/* func_ov146_0229a490: A pressed: the pointer's second animation, then A acts once it has
 * played (sub state 7). */
void WfcHostList_PressA(WfcHostList *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_ACTIVATE);
}
CLEAN_AS(func_ov146_0229a490, WfcHostList_PressA)

/* func_ov146_0229a4b0: the pointer's first animation of its set, and the pointer updated;
 * answers what the update leaves. */
int WfcHostList_ShowPointerFirst(WfcHostList *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    return wfc_host_list_update_pointer(self);
}
CLEAN_AS(func_ov146_0229a4b0, WfcHostList_ShowPointerFirst)

/* func_ov146_0229a4d0: the pointer eases to (x, y) in 3 steps, with its sound unless the quiet
 * flag was set (which it clears), then back to this sub state once it stops (sub state 6). */
void WfcHostList_GlidePointerTo(WfcHostList *self, int x, int y)
{
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_QUIET_GLIDE) != 0) {
        Glider_EaseTo(&self->pointer, x, y, WFC_HOST_LIST_GLIDE_STEPS, 0);
        WfcHostList_ClearFlags(self, WFC_HOST_LIST_FLAG_QUIET_GLIDE);
    } else {
        Glider_EaseTo(&self->pointer, x, y, WFC_HOST_LIST_GLIDE_STEPS, 1);
    }
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov146_0229a4d0, WfcHostList_GlidePointerTo)

/* func_ov146_0229a534: the pointer turned (set A at the bar, set B elsewhere) and gliding to the
 * cursor. */
void WfcHostList_MoveCursor(WfcHostList *self)
{
    if (self->cursor == WFC_HOST_LIST_CURSOR_BAR) {
        Glider_TurnToSetA(&self->pointer);
    } else {
        Glider_TurnToSetB(&self->pointer);
    }
    int x = WfcHostList_PointerX(self);
    int y = (int) WfcHostList_PointerY(self);
    WfcHostList_GlidePointerTo(self, x, y);
}
CLEAN_AS(func_ov146_0229a534, WfcHostList_MoveCursor)

/* func_ov146_0229a578: the pointer without an animation (hidden), and updated. */
void WfcHostList_HidePointer(WfcHostList *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    wfc_host_list_update_pointer(self);
}
CLEAN_AS(func_ov146_0229a578, WfcHostList_HidePointer)

/* func_ov146_0229a59c: the pointer's y for the cursor: a row's, by the target's part of a row;
 * the buttons' 0xad; the knob's face; else the screen's centre. */
unsigned int WfcHostList_PointerY(WfcHostList *self)
{
    unsigned int cursor = self->cursor;
    if (wfc_host_list_is_row(cursor)) {
        return 0x40 + (cursor - WFC_HOST_LIST_CURSOR_FIRST_ROW) * 16 - ((unsigned int) self->scroll_target & 0xf);
    }
    switch (cursor) {
        case WFC_HOST_LIST_CURSOR_QUIT:
        case WFC_HOST_LIST_CURSOR_GO:
            return 0xad;
        case WFC_HOST_LIST_CURSOR_BAR:
            return (unsigned int) PushButton_FaceY(&self->knob_button);
        default:
            return 0x60;
    }
}
CLEAN_AS(func_ov146_0229a59c, WfcHostList_PointerY)

/* func_ov146_0229a5e8: the pointer's x for the cursor: the rows' 0x1c, the quit button's 0x47,
 * the go button's 0x99, the knob's face; else the screen's centre. */
int WfcHostList_PointerX(WfcHostList *self)
{
    unsigned int cursor = self->cursor;
    if (wfc_host_list_is_row(cursor)) {
        return 0x1c;
    }
    switch (cursor) {
        case WFC_HOST_LIST_CURSOR_QUIT:
            return 0x47;
        case WFC_HOST_LIST_CURSOR_GO:
            return 0x99;
        case WFC_HOST_LIST_CURSOR_BAR:
            return PushButton_FaceX(&self->knob_button);
        default:
            return 0x80;
    }
}
CLEAN_AS(func_ov146_0229a5e8, WfcHostList_PointerX)

/* func_ov146_0229a62c: the pointer put at the cursor at once (at the top row the target first
 * down to a whole row), in set A at the bar, else set B, its first animation. */
void WfcHostList_PlacePointer(WfcHostList *self)
{
    if (self->cursor == WFC_HOST_LIST_CURSOR_FIRST_ROW) {
        wfc_host_list_align_target(self);
    }
    int x = WfcHostList_PointerX(self);
    int y = (int) WfcHostList_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    if (self->cursor == WFC_HOST_LIST_CURSOR_BAR) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    } else {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_B);
    }
    WfcHostList_ShowPointerFirst(self);
}
CLEAN_AS(func_ov146_0229a62c, WfcHostList_PlacePointer)

/* --- The end of the choice --- */

/* func_ov146_0229a6a4: the quit: main told nothing was chosen (GroupParams_SetC4C(0)), the quit
 * button pressed, sound 0x28; the scene closes after the delay (state 2 when sub state 9 is
 * done). */
void WfcHostList_Quit(WfcHostList *self)
{
    GroupParams_SetC4C(0);
    self->quit_palette = WFC_HOST_LIST_BUTTON_PRESSED;
    self->close_delay = WFC_HOST_LIST_CLOSE_DELAY;
    MenuScene_SetState(wfc_host_list_input_base(self), WFC_HOST_LIST_STATE_CLOSE);
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_CLOSE_DELAY);
    SoundSys_PlaySe(WFC_HOST_LIST_SOUND_QUIT);
}
CLEAN_AS(func_ov146_0229a6a4, WfcHostList_Quit)

/* func_ov146_0229a6dc: the choice: main told a friend was chosen (GroupParams_SetC4C(1)) and
 * which (GroupParams_SetArg), the go button pressed, the list no longer read, sound 0x27; the
 * scene closes after the delay. */
void WfcHostList_Choose(WfcHostList *self)
{
    GroupParams_SetC4C(1);
    GroupParams_SetArg(self->chosen);
    self->go_palette = WFC_HOST_LIST_BUTTON_PRESSED;
    WfcHostList_SetFlags(self, WFC_HOST_LIST_FLAG_LIST_FROZEN);
    self->close_delay = WFC_HOST_LIST_CLOSE_DELAY;
    MenuScene_SetState(wfc_host_list_input_base(self), WFC_HOST_LIST_STATE_CLOSE);
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_CLOSE_DELAY);
    SoundSys_PlaySe(WFC_HOST_LIST_SOUND_GO);
}
CLEAN_AS(func_ov146_0229a6dc, WfcHostList_Choose)

/* --- The input's start --- */

/* func_ov146_0229a724: the input begins by the pen or by the buttons, as main's state flag 2
 * says. */
void WfcHostList_BeginInput(WfcHostList *self)
{
    if (StateFlags_IsClear2()) {
        WfcHostList_BeginTouch(self);
    } else {
        WfcHostList_BeginKeys(self);
    }
}
CLEAN_AS(func_ov146_0229a724, WfcHostList_BeginInput)

/* func_ov146_0229a744: the input by the buttons: the pointer at the cursor, the usual key
 * repeat (sub state 3). */
void WfcHostList_BeginKeys(WfcHostList *self)
{
    WfcHostList_PlacePointer(self);
    MenuScene_ResetKeyRepeat(wfc_host_list_input_base(self));
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_KEYS);
}
CLEAN_AS(func_ov146_0229a744, WfcHostList_BeginKeys)

/* func_ov146_0229a760: the input by the pen: the pointer hidden (sub state 0). */
void WfcHostList_BeginTouch(WfcHostList *self)
{
    WfcHostList_HidePointer(self);
    MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_TOUCH);
}
CLEAN_AS(func_ov146_0229a760, WfcHostList_BeginTouch)

/* --- The sub states --- */

/* func_ov146_0229a778 (WFC_HOST_LIST_SUB_CLOSE_DELAY): the delay counted down; then the pointer
 * hidden and the states run again (phase 1). */
void WfcHostList_RunCloseDelay(WfcHostList *self)
{
    if (self->close_delay != 0) {
        self->close_delay--;
        return;
    }
    WfcHostList_HidePointer(self);
    MenuScene_SetPhase(wfc_host_list_input_base(self), WFC_HOST_LIST_PHASE_STATES);
}
CLEAN_AS(func_ov146_0229a778, WfcHostList_RunCloseDelay)

/* func_ov146_0229a7a4 (WFC_HOST_LIST_SUB_POINTER_PRESS): once the pointer's animation has
 * played, its first animation and back to `return_sub_state`; after a row chosen by A, the
 * cursor goes to the go button. */
void WfcHostList_RunPointerPress(WfcHostList *self)
{
    if (CellLayerSprite_IsDone(wfc_host_list_pointer_cells(self)) == 0) {
        return;
    }
    WfcHostList_ShowPointerFirst(self);
    MenuScene_SetSubState(wfc_host_list_input_base(self), self->return_sub_state);
    if (WfcHostList_TestFlags(self, WFC_HOST_LIST_FLAG_CHOSE_ROW) != 0) {
        WfcHostList_ClearFlags(self, WFC_HOST_LIST_FLAG_CHOSE_ROW);
        self->cursor = WFC_HOST_LIST_CURSOR_GO;
        WfcHostList_MoveCursor(self);
    }
}
CLEAN_AS(func_ov146_0229a7a4, WfcHostList_RunPointerPress)

/* func_ov146_0229a7f4 (WFC_HOST_LIST_SUB_ACTIVATE): once the pointer's animation has played, A
 * acts at the cursor; when that did nothing of its own, back to the keys with the pointer's
 * press. */
void WfcHostList_RunActivate(WfcHostList *self)
{
    if (CellLayerSprite_IsDone(wfc_host_list_pointer_cells(self)) == 0) {
        return;
    }
    if (WfcHostList_Activate(self, self->cursor) == 0) {
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_KEYS);
        WfcHostList_PressPointer(self);
    }
}
CLEAN_AS(func_ov146_0229a7f4, WfcHostList_RunActivate)

/* Obj_ov146_0229b680::func_ov146_0229a82c (WFC_HOST_LIST_SUB_POINTER_GLIDE): once the pointer
 * stops, back to `return_sub_state`, which runs at once. */
void WfcHostList_RunPointerGlide(WfcHostList *self)
{
    if (Glider_IsMoving(&self->pointer) != 0) {
        return;
    }
    MenuScene_SetSubState(wfc_host_list_input_base(self), self->return_sub_state);
    WfcHostList_RunSubState(self);
}
CLEAN_AS(_ZN18Obj_ov146_0229b68019func_ov146_0229a82cEv, WfcHostList_RunPointerGlide)

/* func_ov146_0229a858 (WFC_HOST_LIST_SUB_KNOB_RELEASE): once the knob's release has played, back
 * to the keys with the pointer's press; the pointer kept at the cursor (the knob's face). */
void WfcHostList_RunKnobRelease(WfcHostList *self)
{
    if (WfcHostList_KnobReleased(self) != 0) {
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_KEYS);
        WfcHostList_PressPointer(self);
    }
    int x = WfcHostList_PointerX(self);
    int y = (int) WfcHostList_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
}
CLEAN_AS(func_ov146_0229a858, WfcHostList_RunKnobRelease)

/* func_ov146_0229a89c (WFC_HOST_LIST_SUB_KNOB_KEYS): while A is held, up and down move the knob
 * and the pointer stays at its face; once A is let go, the knob is released (sub state 5). */
void WfcHostList_RunKnobKeys(WfcHostList *self)
{
    if (data_021fbe40.held & WFC_HOST_LIST_PAD_A) {
        WfcHostList_KnobByKeys(self);
        int x = WfcHostList_PointerX(self);
        int y = (int) WfcHostList_PointerY(self);
        Glider_PlaceAt(&self->pointer, x, y);
    } else {
        WfcHostList_ReleaseKnob(self);
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_KNOB_RELEASE);
    }
}
CLEAN_AS(func_ov146_0229a89c, WfcHostList_RunKnobKeys)

/* func_ov146_0229a8ec (WFC_HOST_LIST_SUB_KEYS): a touch turns to the pen's input; the d-pad
 * moves the cursor; A presses; B quits. */
void WfcHostList_RunKeys(WfcHostList *self)
{
    if (MenuScene_TakeTouch(wfc_host_list_input_base(self)) != 0) {
        WfcHostList_BeginTouch(self);
        return;
    }
    if (WfcHostList_MoveCursorByKeys(self, MenuScene_LatchRepeatedKeys(wfc_host_list_input_base(self))) != 0) {
        WfcHostList_MoveCursor(self);
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & WFC_HOST_LIST_PAD_A) {
        WfcHostList_PressA(self);
    } else if (pressed & WFC_HOST_LIST_PAD_B) {
        WfcHostList_HidePointer(self);
        WfcHostList_Quit(self);
    }
}
CLEAN_AS(func_ov146_0229a8ec, WfcHostList_RunKeys)

/* func_ov146_0229a950 (WFC_HOST_LIST_SUB_BAR_TOUCH): while the pen is down the knob approaches
 * it; once it is up, the knob released and back to the pen's input. */
void WfcHostList_RunBarTouch(WfcHostList *self)
{
    if (data_021fbdd8 != 0) {
        WfcHostList_DragKnob(self, data_021f6c54, 1);
    } else {
        WfcHostList_ReleaseKnob(self);
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_TOUCH);
    }
}
CLEAN_AS(func_ov146_0229a950, WfcHostList_RunBarTouch)

/* func_ov146_0229a984 (WFC_HOST_LIST_SUB_KNOB_DRAG): while the pen is down the knob follows it;
 * once it is up, the knob released and back to the pen's input. */
void WfcHostList_RunKnobDrag(WfcHostList *self)
{
    if (data_021fbdd8 != 0) {
        WfcHostList_DragKnob(self, data_021f6c54, 0);
    } else {
        WfcHostList_ReleaseKnob(self);
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_TOUCH);
    }
}
CLEAN_AS(func_ov146_0229a984, WfcHostList_RunKnobDrag)

/* func_ov146_0229a9b8 (WFC_HOST_LIST_SUB_TOUCH): a button pressed turns to the buttons' input.
 * When the pen went down this frame, at its place:
 *
 * - the quit button (x 0x39-0x74, y 0xa9-0xbc) quits; the go button (x 0x8b-0xc6) chooses while
 *   it is enabled;
 * - a row (x 0x18-0xe0, y 0x38-0x97) chooses its friend when it can be chosen and is not the
 *   chosen one (with sound 0x29);
 * - the knob starts its drag (sub state 1);
 * - the bar (x 0xe6-0xee, y 0x38-0x88) presses the knob, which then approaches the pen (sub
 *   state 2). */
void WfcHostList_RunTouch(WfcHostList *self)
{
    if (MenuScene_TakeButtons(wfc_host_list_input_base(self), 1) != 0) {
        WfcHostList_BeginKeys(self);
        return;
    }
    if (!(data_021fbdd8 != 0 && data_021fbddc != 0)) {
        return;
    }
    int x = data_021f6c58;
    int y = data_021f6c54;

    if (y >= 0xa9 && y <= 0xbc && x >= 0x39) {
        if (x < 0x75) {
            WfcHostList_Quit(self);
            return;
        }
        if (x >= 0x8b && x < 0xc7 && self->go_palette == WFC_HOST_LIST_BUTTON_UP) {
            WfcHostList_Choose(self);
            return;
        }
    }

    if (x >= 0x18 && x <= 0xe0 && y >= WFC_HOST_LIST_ROWS_TOP && y < 0x98) {
        int place = self->first_row + ((y - (WFC_HOST_LIST_ROWS_TOP - (self->scroll_target & 0xf))) >> 4);
        if (place < WFC_HOST_LIST_FRIENDS) {
            u8 friend_index = self->list[place];
            if (WfcHostList_IsJoinable(self, friend_index) != 0 && self->chosen != friend_index) {
                self->chosen = friend_index;
                SoundSys_PlaySe(WFC_HOST_LIST_SOUND_PICK);
            }
        }
        return;
    }

    if (WfcHostList_GrabKnob(self, x, y) != 0) {
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_KNOB_DRAG);
        return;
    }

    if (x >= 0xe6 && x <= 0xee && y >= WFC_HOST_LIST_ROWS_TOP && y <= 0x88) {
        PushButton_Press(&self->knob_button);
        MenuScene_SetSubState(wfc_host_list_input_base(self), WFC_HOST_LIST_SUB_BAR_TOUCH);
    }
}
CLEAN_AS(func_ov146_0229a9b8, WfcHostList_RunTouch)
