/* The keyboard entry scene of overlay 126 (keyboard_entry.h): how the input and the question
 * begin (by the pen or by the buttons, as state flag 2 says), and the sub states of the input
 * (KeyboardEntrySubState). */
#include "clean.h"
#include "keyboard_entry_calls.h"
#include "main/cell_layer_sprite.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov095/soft_keyboard.h"

/* The pointer's base is main's cell layer sprite (ov002/glide.h). */
static CellLayerSprite *keyboard_entry_pointer_cells(KeyboardEntry *self)
{
    return (CellLayerSprite *) (void *) &self->pointer;
}

/* --- The beginnings --- */

/* func_ov126_022a0b90: the question's buttons (layout 9) by the pen, or by the buttons when
 * state flag 2 is set. */
void KeyboardEntry_BeginAsk(KeyboardEntry *self)
{
    if (StateFlags_IsClear2() != 0) {
        KeyboardEntry_BeginAskTouch(self);
    } else {
        KeyboardEntry_BeginAskKeys(self);
    }
}
CLEAN_AS(func_ov126_022a0b90, KeyboardEntry_BeginAsk)

/* func_ov126_022a0bb0: the question by the buttons: the key repeat reset, then
 * KEYBOARD_ENTRY_SUB_ASK_KEYS. Gives MenuScene_SetSubState's answer. */
int KeyboardEntry_BeginAskKeys(KeyboardEntry *self)
{
    MenuScene_ResetKeyRepeat(keyboard_entry_scene(self));
    return (int) (uintptr_t) MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_ASK_KEYS);
}
CLEAN_AS(func_ov126_022a0bb0, KeyboardEntry_BeginAskKeys)

/* func_ov126_022a0bc8: the question by the pen: the pointer at rest, then
 * KEYBOARD_ENTRY_SUB_ASK_TOUCH. Gives MenuScene_SetSubState's answer. */
int KeyboardEntry_BeginAskTouch(KeyboardEntry *self)
{
    KeyboardEntry_RestPointer(self);
    return (int) (uintptr_t) MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_ASK_TOUCH);
}
CLEAN_AS(func_ov126_022a0bc8, KeyboardEntry_BeginAskTouch)

/* func_ov126_022a0be0: the input by the pen, or by the buttons when state flag 2 is set. */
int KeyboardEntry_BeginInput(KeyboardEntry *self)
{
    if (StateFlags_IsClear2() != 0) {
        return (int) (uintptr_t) KeyboardEntry_BeginTouch(self);
    }
    return (int) (uintptr_t) KeyboardEntry_BeginKeys(self);
}
CLEAN_AS(func_ov126_022a0be0, KeyboardEntry_BeginInput)

/* func_ov126_022a0c00: the input by the buttons: the key repeat reset, the pointer at the
 * keyboard's key, KEYBOARD_ENTRY_SUB_KEYS. */
u8 *KeyboardEntry_BeginKeys(KeyboardEntry *self)
{
    MenuScene_ResetKeyRepeat(keyboard_entry_scene(self));
    KeyboardEntry_PointAtKey(self);
    return MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_KEYS);
}
CLEAN_AS(func_ov126_022a0c00, KeyboardEntry_BeginKeys)

/* func_ov126_022a0c1c: the input by the pen: the pointer at rest, KEYBOARD_ENTRY_SUB_TOUCH. */
u8 *KeyboardEntry_BeginTouch(KeyboardEntry *self)
{
    KeyboardEntry_RestPointer(self);
    return MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_TOUCH);
}
CLEAN_AS(func_ov126_022a0c1c, KeyboardEntry_BeginTouch)

/* --- The sub states, from the last --- */

/* func_ov126_022a0c34 (KEYBOARD_ENTRY_SUB_ERROR): the error message, then the input again. */
void KeyboardEntry_Error(KeyboardEntry *self)
{
    SoftKeyboard_StepPressed(keyboard_entry_keyboard(self));
    if (ErrorMessage_Update(&self->error, 1)) {
        KeyboardEntry_BeginInput(self);
    }
}
CLEAN_AS(func_ov126_022a0c34, KeyboardEntry_Error)

/* func_ov126_022a0c64 (KEYBOARD_ENTRY_SUB_PANEL_PRESS): the selected button's press plays, the
 * pointer (while animated) following the button as it is pressed; when it is over, the pointer
 * at rest and phase 1, which runs the state the press chose. */
void KeyboardEntry_PanelPress(KeyboardEntry *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(keyboard_entry_pointer_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->pointer, frame + x, frame + y);
        }
    } else {
        KeyboardEntry_RestPointer(self);
        MenuScene_SetPhase(keyboard_entry_scene(self), KEYBOARD_ENTRY_PHASE_STATES);
    }
}
CLEAN_AS(func_ov126_022a0c64, KeyboardEntry_PanelPress)

/* func_ov126_022a0cd0 (KEYBOARD_ENTRY_SUB_WHILE_R): once R is let go, back to the sub state it
 * was pressed in; the keys follow. */
void KeyboardEntry_WhileR(KeyboardEntry *self)
{
    if ((data_021fbe40.held & KEYBOARD_ENTRY_PAD_R) != 0) {
        return;
    }
    MenuScene_SetSubState(keyboard_entry_scene(self), self->return_sub_state);
    KeyboardEntry_UpdateKeys(self);
}
CLEAN_AS(func_ov126_022a0cd0, KeyboardEntry_WhileR)

/* func_ov126_022a0d00 (KEYBOARD_ENTRY_SUB_WHILE_L): as KeyboardEntry_WhileR, for L. */
void KeyboardEntry_WhileL(KeyboardEntry *self)
{
    if ((data_021fbe40.held & KEYBOARD_ENTRY_PAD_L) != 0) {
        return;
    }
    MenuScene_SetSubState(keyboard_entry_scene(self), self->return_sub_state);
    KeyboardEntry_UpdateKeys(self);
}
CLEAN_AS(func_ov126_022a0d00, KeyboardEntry_WhileL)

/* func_ov126_022a0d30 (KEYBOARD_ENTRY_SUB_BACKSPACE): while B is held, another deletion each time
 * the keyboard's repeat is due (the pointer placed again when at the text cursor; with nothing
 * left, KeyboardEntry_NothingToDelete); once let go, back to the sub state B was held in. */
void KeyboardEntry_BackspaceRepeat(KeyboardEntry *self)
{
    if ((data_021fbe40.held & KEYBOARD_ENTRY_PAD_B) == 0) {
        MenuScene_SetSubState(keyboard_entry_scene(self), self->return_sub_state);
        return;
    }
    if (SoftKeyboard_StepRepeat(keyboard_entry_keyboard(self)) == 0) {
        return;
    }
    if (KeyboardEntry_Backspace(self, 0) != 0) {
        if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT) != 0) {
            KeyboardEntry_PlacePointer(self);
        }
    } else {
        KeyboardEntry_NothingToDelete(self);
    }
}
CLEAN_AS(func_ov126_022a0d30, KeyboardEntry_BackspaceRepeat)

/* func_ov126_022a0d8c (KEYBOARD_ENTRY_SUB_BACK_TO_KEYS): once the pointer's cells are done, its
 * first set shown and the keys again (KEYBOARD_ENTRY_SUB_KEYS). */
void KeyboardEntry_BackToKeys(KeyboardEntry *self)
{
    if (CellLayerSprite_IsDone(keyboard_entry_pointer_cells(self)) != 0) {
        KeyboardEntry_PointerFirstOfSet(self);
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_KEYS);
    }
}
CLEAN_AS(func_ov126_022a0d8c, KeyboardEntry_BackToKeys)

/* The code of the key held down run, and the key shown pressed. */
static void keyboard_entry_repeat_held_key(KeyboardEntry *self)
{
    int key = SoftKeyboard_PressedKey(keyboard_entry_keyboard(self));
    KeyboardEntry_RunCode(self, SoftKeyboard_KeyCode(keyboard_entry_keyboard(self), key, KEYBOARD_ENTRY_KEY_MODE));
    SoftKeyboard_ShowKeyPressed(keyboard_entry_keyboard(self), key);
}

/* func_ov126_022a0db4 (KEYBOARD_ENTRY_SUB_KEY_REPEAT): while A is held, the key's code again each
 * time its repeat is due; once let go, back to the keys (KeyboardEntry_ReleaseToKeys). */
void KeyboardEntry_KeyRepeat(KeyboardEntry *self)
{
    if ((data_021fbe40.held & KEYBOARD_ENTRY_PAD_A) == 0) {
        KeyboardEntry_ReleaseToKeys(self);
        return;
    }
    if (SoftKeyboard_StepRepeat(keyboard_entry_keyboard(self)) != 0) {
        keyboard_entry_repeat_held_key(self);
    }
}
CLEAN_AS(func_ov126_022a0db4, KeyboardEntry_KeyRepeat)

/* func_ov126_022a0e10 (KEYBOARD_ENTRY_SUB_KEY_PRESS): once the pointer's cells are done, the code
 * of the key A pressed run: a character or a deletion with A still held starts the repeat
 * (KEYBOARD_ENTRY_SUB_KEY_REPEAT, the key shown pressed); an answer of 4 only releases the keys
 * and 3 (OK, cancel) leaves the sub state the press set; else back to the keys. */
void KeyboardEntry_KeyPress(KeyboardEntry *self)
{
    if (CellLayerSprite_IsDone(keyboard_entry_pointer_cells(self)) == 0) {
        return;
    }
    int key = SoftKeyboard_PressCursorKey(keyboard_entry_keyboard(self));
    int result =
        KeyboardEntry_RunCode(self, SoftKeyboard_KeyCode(keyboard_entry_keyboard(self), key, KEYBOARD_ENTRY_KEY_MODE));
    if (result == 1 && (data_021fbe40.held & KEYBOARD_ENTRY_PAD_A) != 0) {
        SoftKeyboard_StartRepeat(keyboard_entry_keyboard(self));
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_KEY_REPEAT);
        SoftKeyboard_ShowKeyPressed(keyboard_entry_keyboard(self), key);
        return;
    }
    if (result == 4) {
        SoftKeyboard_ReleasePressed(keyboard_entry_keyboard(self));
    } else if (result != 3) {
        KeyboardEntry_ReleaseToKeys(self);
    }
}
CLEAN_AS(func_ov126_022a0e10, KeyboardEntry_KeyPress)

/* Obj_ov126_022a20c8::func_ov126_022a0e98 (KEYBOARD_ENTRY_SUB_POINTER_GLIDE): once the pointer
 * stops, the sub state it glided for, run at once. */
void KeyboardEntry_PointerGlide(KeyboardEntry *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(keyboard_entry_scene(self), self->return_sub_state);
        KeyboardEntry_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov126_022a20c819func_ov126_022a0e98Ev, KeyboardEntry_PointerGlide)

/* func_ov126_022a0ec4 (KEYBOARD_ENTRY_SUB_MARK_KEYS): while A is held, the d-pad moves the cursor
 * and the range marked follows it (the composition dropped, the field shown again, the pointer
 * placed, the marking sound); once let go, KEYBOARD_ENTRY_SUB_TEXT_KEYS. */
void KeyboardEntry_MarkKeys(KeyboardEntry *self)
{
    if ((data_021fbe40.held & KEYBOARD_ENTRY_PAD_A) == 0) {
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_TEXT_KEYS);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(keyboard_entry_scene(self));
    if (KeyboardEntry_MoveByKeys(self, keys) == 1) {
        SoftKeyboard_HangulReset(keyboard_entry_keyboard(self));
        KeyboardEntry_MarkToPosition(self);
        KeyboardEntry_PlaceCursor(self);
        KeyboardEntry_ShowField(self);
        KeyboardEntry_PlacePointer(self);
        SoundSys_PlaySe(KEYBOARD_ENTRY_SE_MARK);
    }
}
CLEAN_AS(func_ov126_022a0ec4, KeyboardEntry_MarkKeys)

/* func_ov126_022a0f20: from the text cursor back to the keyboard: the pointer glides to its key,
 * then KEYBOARD_ENTRY_SUB_KEYS. */
void KeyboardEntry_TextToKeys(KeyboardEntry *self)
{
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT);
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_KEYS);
    KeyboardEntry_GlidePointer(self);
}
CLEAN_AS(func_ov126_022a0f20, KeyboardEntry_TextToKeys)

/* func_ov126_022a0f40 (KEYBOARD_ENTRY_SUB_TEXT_KEYS): the pointer at the text cursor, by the
 * buttons. A touch hands the input to the pen. Left and right move the cursor (without marks; the
 * moving sound), down goes back to the key below the pointer. Else B held deletes (the pointer
 * placed again when the cursor moved); else L, R and START, and A pressed starts marking
 * (KEYBOARD_ENTRY_SUB_MARK_KEYS). */
void KeyboardEntry_TextKeys(KeyboardEntry *self)
{
    if (MenuScene_TakeTouch(keyboard_entry_scene(self)) != 0) {
        KeyboardEntry_BeginTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(keyboard_entry_scene(self));
    switch (KeyboardEntry_MoveByKeys(self, keys)) {
        case 1:
            SoftKeyboard_HangulReset(keyboard_entry_keyboard(self));
            KeyboardEntry_ClearMarks(self);
            KeyboardEntry_PlaceCursor(self);
            KeyboardEntry_ShowField(self);
            KeyboardEntry_PlacePointer(self);
            SoundSys_PlaySe(KEYBOARD_ENTRY_SE_MOVE);
            break;
        case 2: {
            int x = Glider_ScreenX(&self->pointer);
            SoftKeyboard_CursorToTabRowAt(keyboard_entry_keyboard(self), x);
            KeyboardEntry_TextToKeys(self);
            break;
        }
        default: {
            u8 before = self->position;
            if (KeyboardEntry_HoldB(self) != 0) {
                if (before != self->position) {
                    KeyboardEntry_PlacePointer(self);
                }
                break;
            }
            /* KeyboardEntry_PressL and KeyboardEntry_PressR always give 0. */
            if (KeyboardEntry_PressL(self) == 0 && KeyboardEntry_PressR(self) == 0 && KeyboardEntry_PressStart(self) == 0 &&
                (data_021fbe40.pressed & KEYBOARD_ENTRY_PAD_A) != 0) {
                MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_MARK_KEYS);
                KeyboardEntry_MarkFromPosition(self);
            }
            break;
        }
    }
}
CLEAN_AS(func_ov126_022a0f40, KeyboardEntry_TextKeys)

/* func_ov126_022a1020 (KEYBOARD_ENTRY_SUB_ASK_KEYS): a touch hands the question to the pen. */
void KeyboardEntry_AskKeys(KeyboardEntry *self)
{
    if (MenuScene_TakeTouch(keyboard_entry_scene(self)) != 0) {
        KeyboardEntry_BeginAskTouch(self);
    }
}
CLEAN_AS(func_ov126_022a1020, KeyboardEntry_AskKeys)

/* func_ov126_022a1038 (KEYBOARD_ENTRY_SUB_KEYS): the keyboard by the buttons. A touch hands the
 * input to the pen. The d-pad moves the keyboard's cursor: when it leaves the keys (1-3) the
 * pointer turns and glides to the key; at 4 it turns and glides to the text cursor
 * (KEYBOARD_ENTRY_SUB_TEXT_KEYS after the glide). Else A, B, L, R and START, the first that
 * acts. */
void KeyboardEntry_Keys(KeyboardEntry *self)
{
    if (MenuScene_TakeTouch(keyboard_entry_scene(self))) {
        KeyboardEntry_BeginTouch(self);
        return;
    }
    u32 keys = MenuScene_LatchRepeatedKeys(keyboard_entry_scene(self));
    switch (SoftKeyboard_MoveCursor(keyboard_entry_keyboard(self), (int) keys)) {
        case 1:
            Glider_TurnToSetA(&self->pointer);
            KeyboardEntry_GlidePointer(self);
            break;
        case 2:
            Glider_TurnToSetC(&self->pointer);
            KeyboardEntry_GlidePointer(self);
            break;
        case 3:
            Glider_TurnToSetB(&self->pointer);
            KeyboardEntry_GlidePointer(self);
            break;
        case 4:
            Glider_TurnToSetA(&self->pointer);
            KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT);
            /* QUIRK: the glide sets its own sub state over this one. */
            MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_TEXT_KEYS);
            KeyboardEntry_GlidePointer(self);
            break;
        default:
            if (KeyboardEntry_PressA(self) || KeyboardEntry_HoldB(self) || KeyboardEntry_PressL(self) ||
                KeyboardEntry_PressR(self) || KeyboardEntry_PressStart(self)) {
                return;
            }
            break;
    }
}
CLEAN_AS(func_ov126_022a1038, KeyboardEntry_Keys)

/* func_ov126_022a1108 (KEYBOARD_ENTRY_SUB_ASK_TOUCH): the question by the pen. A button hands it
 * to the buttons; yes (button 3) finishes the input (KEYBOARD_ENTRY_STATE_FINISH) and no (button
 * 4) goes back to it (KEYBOARD_ENTRY_STATE_BACK), each once its press has played. */
void KeyboardEntry_AskTouch(KeyboardEntry *self)
{
    if (MenuScene_TakeButtons(keyboard_entry_scene(self), 1) != 0) {
        KeyboardEntry_BeginAskKeys(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, KEYBOARD_ENTRY_BUTTON_YES) != 0) {
        ButtonPanel_Select(&self->panel, KEYBOARD_ENTRY_BUTTON_YES);
        self->base.state = KEYBOARD_ENTRY_STATE_FINISH;
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_PANEL_PRESS);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, KEYBOARD_ENTRY_BUTTON_NO) != 0) {
        ButtonPanel_Select(&self->panel, KEYBOARD_ENTRY_BUTTON_NO);
        self->base.state = KEYBOARD_ENTRY_STATE_BACK;
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_PANEL_PRESS);
    }
}
CLEAN_AS(func_ov126_022a1108, KeyboardEntry_AskTouch)

/* func_ov126_022a117c (KEYBOARD_ENTRY_SUB_KEY_TOUCH_HELD): while the pen is down, the key's code
 * again each time its repeat is due; once it is up, KEYBOARD_ENTRY_SUB_TOUCH. */
void KeyboardEntry_KeyTouchHeld(KeyboardEntry *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_TOUCH);
        return;
    }
    if (SoftKeyboard_StepRepeat(keyboard_entry_keyboard(self)) != 0) {
        keyboard_entry_repeat_held_key(self);
    }
}
CLEAN_AS(func_ov126_022a117c, KeyboardEntry_KeyTouchHeld)

/* func_ov126_022a11d8 (KEYBOARD_ENTRY_SUB_MARK_DRAG): while the pen is down, the cursor follows
 * it and the range is marked to it (the field shown again, the marking sound) when it moved; once
 * up, KEYBOARD_ENTRY_SUB_TOUCH. */
void KeyboardEntry_MarkDrag(KeyboardEntry *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_TOUCH);
        return;
    }
    u8 before = self->position;
    KeyboardEntry_PlaceCursorAtX(self, data_021f6c58);
    if (before == self->position) {
        return;
    }
    KeyboardEntry_MarkToPosition(self);
    KeyboardEntry_ShowField(self);
    SoundSys_PlaySe(KEYBOARD_ENTRY_SE_MARK);
}
CLEAN_AS(func_ov126_022a11d8, KeyboardEntry_MarkDrag)

/* func_ov126_022a1228 (KEYBOARD_ENTRY_SUB_TOUCH): the input by the pen. A button hands it to the
 * buttons. When the pen has just come down: the panel, the text, a mode tab of the keyboard (its
 * mode changed, the field shown again), else below y 0x48 a key, when the keyboard shows no
 * pressed key: a character or a deletion holds it (KEYBOARD_ENTRY_SUB_KEY_TOUCH_HELD). */
void KeyboardEntry_Touch(KeyboardEntry *self)
{
    if (MenuScene_TakeButtons(keyboard_entry_scene(self), 1) != 0) {
        KeyboardEntry_BeginKeys(self);
        return;
    }
    int pressed_shown = SoftKeyboard_StepPressed(keyboard_entry_keyboard(self));
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        return;
    }
    if (KeyboardEntry_TouchPanel(self) != 0) {
        return;
    }
    if (KeyboardEntry_TouchText(self) != 0) {
        return;
    }
    if (SoftKeyboard_TouchPageTab(keyboard_entry_keyboard(self)) != 0) {
        SoftKeyboard_LoadLayout(keyboard_entry_keyboard(self), 9, KEYBOARD_ENTRY_LAYER, 1);
        KeyboardEntry_ShowField(self);
        return;
    }
    if (data_021f6c54 < 0x48 || pressed_shown != 0) {
        return;
    }
    if (KeyboardEntry_TouchKey(self) == 1) {
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_KEY_TOUCH_HELD);
    }
}
CLEAN_AS(func_ov126_022a1228, KeyboardEntry_Touch)
