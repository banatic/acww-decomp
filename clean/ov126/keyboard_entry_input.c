/* The keyboard entry scene of overlay 126 (keyboard_entry.h): the buttons the input reacts to,
 * the pointer sprite, the panel, the keyboard's codes run on the text, the marked range and the
 * text cursor. */
#include "clean.h"
#include "keyboard_entry_calls.h"
#include "main/group_params.h"
#include "main/sound.h"
#include "main/text_string.h"
#include "ov002/key_repeat.h"

/* The characters before a 0, at most `max` (main's). */
extern int func_02051c8c_unk(u16 *text, int max);

/* --- The buttons --- */

/* func_ov126_0229fcd8: START pressed presses the panel's OK button (KeyboardEntry_PressOk);
 * 1 when START was pressed. */
int KeyboardEntry_PressStart(KeyboardEntry *self)
{
    if ((data_021fbe40.pressed & KEYBOARD_ENTRY_PAD_START) == 0) {
        return 0;
    }
    KeyboardEntry_PressOk(self);
    return 1;
}
CLEAN_AS(func_ov126_0229fcd8, KeyboardEntry_PressStart)

/* func_ov126_0229fcfc: L pressed copies the marked range, when the copy key is enabled: the L key
 * shown pressed, and the sub state is KEYBOARD_ENTRY_SUB_WHILE_L until L is let go.
 * QUIRK: answers 0 even then, so the caller goes on to the other buttons. */
int KeyboardEntry_PressL(KeyboardEntry *self)
{
    if ((data_021fbe40.pressed & KEYBOARD_ENTRY_PAD_L) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(keyboard_entry_keyboard(self), KEYBOARD_ENTRY_KEY_COPY)) {
        return 0;
    }
    KeyboardEntry_RunCode(self, KEYBOARD_ENTRY_CODE_COPY);
    func_ov095_0229c8e4(keyboard_entry_keyboard_arg(self), KEYBOARD_ENTRY_KEY_L);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_WHILE_L);
    return 0;
}
CLEAN_AS(func_ov126_0229fcfc, KeyboardEntry_PressL)

/* func_ov126_0229fd64: R pressed pastes, when the paste key is enabled: the R key shown pressed,
 * the pointer placed again, and the sub state is KEYBOARD_ENTRY_SUB_WHILE_R until R is let go.
 * QUIRK: answers 0 even then, as KeyboardEntry_PressL. */
int KeyboardEntry_PressR(KeyboardEntry *self)
{
    if ((data_021fbe40.pressed & KEYBOARD_ENTRY_PAD_R) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(keyboard_entry_keyboard(self), KEYBOARD_ENTRY_KEY_PASTE)) {
        return 0;
    }
    KeyboardEntry_RunCode(self, KEYBOARD_ENTRY_CODE_PASTE);
    func_ov095_0229c8e4(keyboard_entry_keyboard_arg(self), KEYBOARD_ENTRY_KEY_R);
    KeyboardEntry_PlacePointer(self);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_WHILE_R);
    return 0;
}
CLEAN_AS(func_ov126_0229fd64, KeyboardEntry_PressR)

/* func_ov126_0229fdd4: B held (not only pressed) deletes before the cursor; when something was
 * deleted the keyboard's repeat starts and the sub state is KEYBOARD_ENTRY_SUB_BACKSPACE until B
 * is let go, else KeyboardEntry_NothingToDelete. 1 when B is held. */
int KeyboardEntry_HoldB(KeyboardEntry *self)
{
    if ((data_021fbe40.held & KEYBOARD_ENTRY_PAD_B) == 0) {
        return 0;
    }
    if (KeyboardEntry_Backspace(self, 0) != 0) {
        func_ov095_0229bf3c(keyboard_entry_keyboard(self));
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_BACKSPACE);
    } else {
        KeyboardEntry_NothingToDelete(self);
    }
    return 1;
}
CLEAN_AS(func_ov126_0229fdd4, KeyboardEntry_HoldB)

/* func_ov126_0229fe28: A pressed on the keyboard's key, when it can be pressed (key 0x107 not
 * while the panel's OK button is dimmed): the key shown pressed, the pointer's press shown and
 * KEYBOARD_ENTRY_SUB_KEY_PRESS. 1 when the key is pressed.
 * QUIRK: the key's code is asked for and dropped; KeyboardEntry_KeyPress asks again. */
int KeyboardEntry_PressA(KeyboardEntry *self)
{
    if ((data_021fbe40.pressed & KEYBOARD_ENTRY_PAD_A) == 0) {
        return 0;
    }
    int key = func_ov095_02299a00(keyboard_entry_keyboard(self));
    if (key == -1) {
        return 0;
    }
    if (ButtonPanel_HasSpriteFlag4(&self->panel, KEYBOARD_ENTRY_BUTTON_OK) != 0 && key == KEYBOARD_ENTRY_KEY_107) {
        return 0;
    }
    func_ov095_0229c448(keyboard_entry_keyboard(self), key, KEYBOARD_ENTRY_KEY_MODE);
    func_ov095_0229c8e4(keyboard_entry_keyboard_arg(self), key);
    KeyboardEntry_BeginKeyPress(self);
    return 1;
}
CLEAN_AS(func_ov126_0229fe28, KeyboardEntry_PressA)

/* --- The pointer --- */

/* func_ov126_0229fea0: the pointer's first set of cells shown, and updated. */
void KeyboardEntry_PointerFirstOfSet(KeyboardEntry *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    keyboard_entry_update_pointer(self);
}
CLEAN_AS(func_ov126_0229fea0, KeyboardEntry_PointerFirstOfSet)

/* func_ov126_0229fec0: the keyboard's keys released, the pointer's third set shown, and back to
 * the keys (KEYBOARD_ENTRY_SUB_BACK_TO_KEYS). */
void KeyboardEntry_ReleaseToKeys(KeyboardEntry *self)
{
    func_ov095_0229cce0(keyboard_entry_keyboard(self));
    Glider_ShowThirdOfSet(&self->pointer);
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_BACK_TO_KEYS);
}
CLEAN_AS(func_ov126_0229fec0, KeyboardEntry_ReleaseToKeys)

/* func_ov126_0229feec: the pointer's second set shown, then KEYBOARD_ENTRY_SUB_KEY_PRESS. */
void KeyboardEntry_BeginKeyPress(KeyboardEntry *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_KEY_PRESS);
}
CLEAN_AS(func_ov126_0229feec, KeyboardEntry_BeginKeyPress)

/* func_ov126_0229ff0c: the pointer put at once at the text cursor or at the keyboard's key, and
 * updated. */
void KeyboardEntry_PlacePointer(KeyboardEntry *self)
{
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT) != 0) {
        Glider_PlaceAt(&self->pointer, self->cursor_x, KEYBOARD_ENTRY_CURSOR_Y);
    } else {
        int x = func_ov095_02299b7c(keyboard_entry_keyboard(self));
        int y = func_ov095_02299b38(keyboard_entry_keyboard(self));
        Glider_PlaceAt(&self->pointer, x, y);
    }
    keyboard_entry_update_pointer(self);
}
CLEAN_AS(func_ov126_0229ff0c, KeyboardEntry_PlacePointer)

/* func_ov126_0229ff68: the pointer glides to the text cursor (then KEYBOARD_ENTRY_SUB_TEXT_KEYS)
 * or to the keyboard's key (then KEYBOARD_ENTRY_SUB_KEYS), in KEYBOARD_ENTRY_SUB_POINTER_GLIDE. */
void KeyboardEntry_GlidePointer(KeyboardEntry *self)
{
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT)) {
        Glider_EaseToByDistance(&self->pointer, self->cursor_x, KEYBOARD_ENTRY_CURSOR_Y, 3, 2);
        self->return_sub_state = KEYBOARD_ENTRY_SUB_TEXT_KEYS;
    } else {
        int x = func_ov095_02299b7c(keyboard_entry_keyboard(self));
        int y = func_ov095_02299b38(keyboard_entry_keyboard(self));
        Glider_EaseToByDistance(&self->pointer, x, y, 3, 2);
        self->return_sub_state = KEYBOARD_ENTRY_SUB_KEYS;
    }
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov126_0229ff68, KeyboardEntry_GlidePointer)

/* func_ov126_0229ffdc: the pointer's animation 0 (at rest); gives its update's answer. */
int KeyboardEntry_RestPointer(KeyboardEntry *self)
{
    Glider_SetAnim(&self->pointer, 0);
    return keyboard_entry_update_pointer(self);
}
CLEAN_AS(func_ov126_0229ffdc, KeyboardEntry_RestPointer)

/* func_ov126_022a0000: the pointer at the keyboard's key (put at the key its mode starts on),
 * in animation 1 with its first set shown. */
void KeyboardEntry_PointAtKey(KeyboardEntry *self)
{
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_POINTER_ON_TEXT);
    func_ov095_02299aec(keyboard_entry_keyboard(self));
    int x = func_ov095_02299b7c(keyboard_entry_keyboard(self));
    int y = func_ov095_02299b38(keyboard_entry_keyboard(self));
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, 1);
    KeyboardEntry_PointerFirstOfSet(self);
}
CLEAN_AS(func_ov126_022a0000, KeyboardEntry_PointAtKey)

/* --- The panel --- */

/* func_ov126_022a0054: the panel's layout by its kind. */
void KeyboardEntry_SetPanelLayout(KeyboardEntry *self)
{
    switch (self->panel_kind) {
        case KEYBOARD_ENTRY_PANEL_OK_CANCEL:
            ButtonPanel_SetLayout6(&self->panel, 0xd8);
            break;
        case KEYBOARD_ENTRY_PANEL_OK:
            ButtonPanel_SetLayout5(&self->panel, 0x21);
            break;
        case KEYBOARD_ENTRY_PANEL_CANCEL:
            ButtonPanel_SetLayout5(&self->panel, 0x65);
            break;
        case KEYBOARD_ENTRY_PANEL_NONE:
            break;
    }
}
CLEAN_AS(func_ov126_022a0054, KeyboardEntry_SetPanelLayout)

/* func_ov126_022a00a4: the pen on the panel: the OK button when it is not dimmed, the cancel
 * button with the two buttons; 1 when one is pressed (KeyboardEntry_PressButton). */
int KeyboardEntry_TouchPanel(KeyboardEntry *self)
{
    if (self->panel_kind == KEYBOARD_ENTRY_PANEL_NONE) {
        return 0;
    }
    if (ButtonPanel_HasSpriteFlag4(&self->panel, KEYBOARD_ENTRY_BUTTON_OK) == 0 &&
        ButtonPanel_IsTouched(&self->panel, KEYBOARD_ENTRY_BUTTON_OK) != 0) {
        KeyboardEntry_PressButton(self, 0);
        return 1;
    }
    if (self->panel_kind != KEYBOARD_ENTRY_PANEL_OK_CANCEL) {
        return 0;
    }
    if (ButtonPanel_IsTouched(&self->panel, KEYBOARD_ENTRY_BUTTON_CANCEL) != 0) {
        KeyboardEntry_PressButton(self, 1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov126_022a00a4, KeyboardEntry_TouchPanel)

/* func_ov126_022a0110: the sound of a key that does nothing. */
void KeyboardEntry_Buzz(KeyboardEntry *self)
{
    (void) self;
    SoundSys_PlaySe(KEYBOARD_ENTRY_SE_BUZZ);
}
CLEAN_AS(func_ov126_022a0110, KeyboardEntry_Buzz)

/* --- The field --- */

/* func_ov126_022a011c: the marked range shown in the field, when there is one. */
void KeyboardEntry_ShowMarks(KeyboardEntry *self)
{
    if (KeyboardEntry_IsMarking(self) == 0) {
        return;
    }
    int first, count;
    if (self->mark_from > self->mark_to) {
        first = self->mark_to;
        count = self->mark_from - self->mark_to;
    } else {
        first = self->mark_from;
        count = self->mark_to - self->mark_from;
    }
    if (count != 0) {
        func_ov124_0229f2c8(keyboard_entry_field_arg(self), 7, 6, first, count);
    }
}
CLEAN_AS(func_ov126_022a011c, KeyboardEntry_ShowMarks)

/* func_ov126_022a0168: the field shown again with the text: with the hint, its cell after the
 * text's width; the box opened, the marks, the label shown; then the keys the text allows. */
void KeyboardEntry_ShowField(KeyboardEntry *self)
{
    func_ov124_0229f2dc(self->field, self->text, (void *) (uintptr_t) self->max_chars);
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_HINT) != 0) {
        int width = TextString_Width(self->text, self->max_chars);
        self->hint_x = width + 2 - self->field_width;
    }
    func_ov124_0229f320(keyboard_entry_field_arg(self));
    KeyboardEntry_ShowMarks(self);
    func_ov124_0229f2e4(keyboard_entry_field_arg(self));
    KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_FIELD_SHOWN);
    KeyboardEntry_UpdateKeys(self);
}
CLEAN_AS(func_ov126_022a0168, KeyboardEntry_ShowField)

/* --- The text edited --- */

/* func_ov126_022a01dc: a character typed in place of the marked range (whose deletion drops the
 * keyboard's composition); the field and the cursor follow. 1 when it fitted. */
int KeyboardEntry_Type(KeyboardEntry *self, int character)
{
    if (KeyboardEntry_IsMarking(self)) {
        KeyboardEntry_DeleteMarked(self);
        func_ov095_0229b3ec(keyboard_entry_keyboard(self));
    }
    int fitted = KeyboardEntry_PutCharacter(self, character);
    KeyboardEntry_ShowField(self);
    KeyboardEntry_PlaceCursor(self);
    return fitted;
}
CLEAN_AS(func_ov126_022a01dc, KeyboardEntry_Type)

/* func_ov126_022a0220: a character put at the cursor, if the text keeps within the field: the
 * cursor moves past it. 1 when it fitted. */
int KeyboardEntry_PutCharacter(KeyboardEntry *self, int character)
{
    u8 position = self->position;

    if (func_ov095_0229bcec(keyboard_entry_keyboard_arg(self), (int) (uintptr_t) self->text, character,
                            (int) (uintptr_t) &position, self->max_chars, self->field_width, 0, 1)) {
        KeyboardEntry_SetPosition(self, (char) position);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov126_022a0220, KeyboardEntry_PutCharacter)

/* func_ov126_022a027c: a deletion: the marked range, else the character being composed or the
 * character before the cursor, else at the start the character after it. With nothing to delete
 * gives 0, after the buzz with `buzz`; else the sound of a deletion, the field and the cursor
 * follow, 1. */
int KeyboardEntry_Backspace(KeyboardEntry *self, int buzz)
{
    if (KeyboardEntry_IsMarking(self)) {
        func_ov095_0229b3ec(keyboard_entry_keyboard(self));
        KeyboardEntry_DeleteMarked(self);
    } else if (self->position != 0) {
        if (func_ov095_0229b3a0(keyboard_entry_keyboard(self), self->text, self->position) == 0) {
            self->mark_from = self->position;
            self->mark_to = (u8) (self->position - 1);
            KeyboardEntry_DeleteMarked(self);
        }
    } else if (self->text[0] != 0) {
        self->mark_from = 0;
        self->mark_to = 1;
        KeyboardEntry_DeleteMarked(self);
    } else {
        if (buzz) {
            KeyboardEntry_Buzz(self);
        }
        return 0;
    }
    SoundSys_PlaySe(KEYBOARD_ENTRY_SE_DELETE);
    KeyboardEntry_ShowField(self);
    KeyboardEntry_PlaceCursor(self);
    return 1;
}
CLEAN_AS(func_ov126_022a027c, KeyboardEntry_Backspace)

/* func_ov126_022a032c: the character before the cursor converted by one of the three codes and
 * put in its place; the field and the cursor follow. 1 when converted.
 * QUIRK: another code keeps the character as it is and puts it back. */
int KeyboardEntry_Convert(KeyboardEntry *self, int code)
{
    int character = KeyboardEntry_CharacterBeforeCursor(self);
    if (character == 0) {
        return 0;
    }
    switch (code) {
        case KEYBOARD_ENTRY_CODE_CONVERT_1:
            character = func_ov095_0229bb9c(keyboard_entry_keyboard(self), character);
            break;
        case KEYBOARD_ENTRY_CODE_CONVERT_2:
            character = func_ov095_0229bb98(keyboard_entry_keyboard(self), character);
            break;
        case KEYBOARD_ENTRY_CODE_CONVERT_3:
            character = func_ov095_0229bb94(keyboard_entry_keyboard(self), character);
            break;
    }
    if (character == 0) {
        return 0;
    }
    if (func_ov095_0229bba0(keyboard_entry_keyboard_arg(self), self->text, character, self->position) == 0) {
        return 0;
    }
    KeyboardEntry_ShowField(self);
    KeyboardEntry_PlaceCursor(self);
    return 1;
}
CLEAN_AS(func_ov126_022a032c, KeyboardEntry_Convert)

/* func_ov126_022a03dc: a code of the keyboard run: the keyboard's own (its answer, after the
 * field is shown again); a command: deletion and conversions (a buzz when nothing converted),
 * copy, paste, OK and cancel (the panel's buttons pressed); else a character typed (a buzz when
 * it did not fit). Gives 1 for a character or a deletion, 3 for OK and cancel, 2 for the other
 * commands. */
int KeyboardEntry_RunCode(KeyboardEntry *self, int code)
{
    int result = 1;

    int own = func_ov095_0229ba44(keyboard_entry_keyboard(self), code, KEYBOARD_ENTRY_LAYER);
    if (own != 0) {
        KeyboardEntry_ShowField(self);
        return own;
    }
    if (func_ov095_0229bebc(keyboard_entry_keyboard_arg(self), code) != 0) {
        switch (code) {
            case KEYBOARD_ENTRY_CODE_BACKSPACE:
                KeyboardEntry_Backspace(self, 1);
                break;
            case KEYBOARD_ENTRY_CODE_CONVERT_1:
            case KEYBOARD_ENTRY_CODE_CONVERT_2:
            case KEYBOARD_ENTRY_CODE_CONVERT_3:
                if (KeyboardEntry_Convert(self, code) == 0) {
                    KeyboardEntry_Buzz(self);
                }
                result = 2;
                break;
            case KEYBOARD_ENTRY_CODE_COPY:
                KeyboardEntry_Copy(self);
                result = 2;
                break;
            case KEYBOARD_ENTRY_CODE_PASTE:
                KeyboardEntry_Paste(self);
                result = 2;
                break;
            case KEYBOARD_ENTRY_CODE_OK:
                KeyboardEntry_PressButton(self, 0);
                result = 3;
                break;
            case KEYBOARD_ENTRY_CODE_CANCEL:
                KeyboardEntry_PressButton(self, 1);
                result = 3;
                break;
            default:
                result = 2;
                break;
        }
    } else if (KeyboardEntry_Type(self, (u16) code) == 0) {
        KeyboardEntry_Buzz(self);
    }
    return result;
}
CLEAN_AS(func_ov126_022a03dc, KeyboardEntry_RunCode)

/* func_ov126_022a04e8: the key under the pen pressed: the keys released first, its code run,
 * the key shown pressed and its repeat started. Gives KeyboardEntry_RunCode's answer, 0 for no
 * key. */
int KeyboardEntry_TouchKey(KeyboardEntry *self)
{
    func_ov095_0229cce0(keyboard_entry_keyboard(self));
    int key = func_ov095_0229c54c(keyboard_entry_keyboard(self), data_021f6c58, data_021f6c54);
    if (key == -1) {
        return 0;
    }
    int result = KeyboardEntry_RunCode(self, func_ov095_0229c448(keyboard_entry_keyboard(self), key, KEYBOARD_ENTRY_KEY_MODE));
    func_ov095_0229c8e4(keyboard_entry_keyboard_arg(self), key);
    func_ov095_0229bf3c(keyboard_entry_keyboard(self));
    return result;
}
CLEAN_AS(func_ov126_022a04e8, KeyboardEntry_TouchKey)

/* func_ov126_022a054c: the copied text put at the cursor in place of the marked range, character
 * by character until one does not fit (a buzz when the first does not), with the keyboard's flag
 * 2 set meanwhile and its sound 23; the cursor and the field follow. Nothing without copied
 * text. */
void KeyboardEntry_Paste(KeyboardEntry *self)
{
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_COPIED) == 0) {
        return;
    }
    func_ov095_0229b394(keyboard_entry_keyboard_arg(self));
    func_ov095_0229b3ec(keyboard_entry_keyboard(self));
    if (KeyboardEntry_IsMarking(self) != 0) {
        KeyboardEntry_DeleteMarked(self);
    }
    int count = func_02051c8c_unk(self->clipboard, KEYBOARD_ENTRY_TEXT_CHARS);
    u8 position = self->position;
    for (int i = 0; i < count; i++) {
        if (func_ov095_0229bcec(keyboard_entry_keyboard_arg(self), (int) (uintptr_t) self->text, self->clipboard[i],
                                (int) (uintptr_t) &position, self->max_chars, self->field_width, 0, 0) == 0) {
            if (i == 0) {
                KeyboardEntry_Buzz(self);
            }
            break;
        }
    }
    func_ov095_022999e8(keyboard_entry_keyboard(self));
    KeyboardEntry_SetPosition(self, (char) position);
    KeyboardEntry_PlaceCursor(self);
    KeyboardEntry_ShowField(self);
    func_ov095_0229b388(keyboard_entry_keyboard_arg(self));
}
CLEAN_AS(func_ov126_022a054c, KeyboardEntry_Paste)

/* func_ov126_022a0614: the marked range copied (the clipboard cleared first), with the
 * keyboard's sound 22; the paste key follows. */
void KeyboardEntry_Copy(KeyboardEntry *self)
{
    if (KeyboardEntry_IsMarking(self) == 0) {
        return;
    }
    int first, count;
    if (self->mark_from > self->mark_to) {
        first = self->mark_to;
        count = self->mark_from - self->mark_to;
    } else {
        first = self->mark_from;
        count = self->mark_to - self->mark_from;
    }
    TextString_ClearChars(self->clipboard, KEYBOARD_ENTRY_TEXT_CHARS);
    TextString_CopyChars(&self->text[first], self->clipboard, count);
    KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_COPIED);
    func_ov095_022999f4(keyboard_entry_keyboard(self));
    KeyboardEntry_UpdateKeys(self);
}
CLEAN_AS(func_ov126_022a0614, KeyboardEntry_Copy)

/* --- The marked range --- */

/* func_ov126_022a0680: the range marked to the cursor; marking while it is not empty. */
void KeyboardEntry_MarkToPosition(KeyboardEntry *self)
{
    self->mark_to = self->position;
    if (self->mark_to != self->mark_from) {
        KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_MARKING);
    } else {
        KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_MARKING);
    }
}
CLEAN_AS(func_ov126_022a0680, KeyboardEntry_MarkToPosition)

/* func_ov126_022a06b4: an empty range at the cursor, not marking. */
void KeyboardEntry_MarkFromPosition(KeyboardEntry *self)
{
    self->mark_from = self->position;
    self->mark_to = self->position;
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_MARKING);
}
CLEAN_AS(func_ov126_022a06b4, KeyboardEntry_MarkFromPosition)

/* func_ov126_022a06d8: the marked range's characters deleted, the cursor at its start, the marks
 * cleared. */
void KeyboardEntry_DeleteMarked(KeyboardEntry *self)
{
    u8 low, high;
    if (self->mark_from > self->mark_to) {
        low = self->mark_to;
        high = self->mark_from;
    } else {
        low = self->mark_from;
        high = self->mark_to;
    }
    u8 position = (u8) func_ov095_0229bbc0(keyboard_entry_keyboard_arg(self), self->text, low, high, self->max_chars);
    KeyboardEntry_SetPosition(self, (char) position);
    KeyboardEntry_ClearMarks(self);
}
CLEAN_AS(func_ov126_022a06d8, KeyboardEntry_DeleteMarked)

/* func_ov126_022a0728 */
void KeyboardEntry_ClearMarks(KeyboardEntry *self)
{
    self->mark_from = 0;
    self->mark_to = 0;
    KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_MARKING);
}
CLEAN_AS(func_ov126_022a0728, KeyboardEntry_ClearMarks)

/* func_ov126_022a0740: marking, over at least one character. */
int KeyboardEntry_IsMarking(KeyboardEntry *self)
{
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_MARKING) == 0 || self->mark_from == self->mark_to) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov126_022a0740, KeyboardEntry_IsMarking)

/* --- The text cursor --- */

/* func_ov126_022a0768: the cursor moved by the repeated d-pad keys: left (3 at the start), right
 * up to the end of the text (4 past it), 1 when it moved; down gives 2, nothing 0. */
int KeyboardEntry_MoveByKeys(KeyboardEntry *self, int keys)
{
    if (keys == 0) {
        return 0;
    }
    u8 position = self->position;
    if (KeyRepeat_HasLeft(keys)) {
        if (position != 0) {
            KeyboardEntry_SetPosition(self, (char) (position - 1));
            return 1;
        }
        return 3;
    }
    if (KeyRepeat_HasRight(keys)) {
        int length = func_02051c8c_unk(self->text, self->max_chars);
        if (position + 1 <= length) {
            KeyboardEntry_SetPosition(self, (char) (position + 1));
            return 1;
        }
        return 4;
    }
    if (KeyRepeat_HasDown(keys)) {
        return 2;
    }
    return 0;
}
CLEAN_AS(func_ov126_022a0768, KeyboardEntry_MoveByKeys)

/* func_ov126_022a07e8: the pen on the text (y 0x28-0x38, x within 12 pixels of the field): the
 * cursor put there, an empty range started at it (KEYBOARD_ENTRY_SUB_MARK_DRAG), the keyboard's
 * composition dropped and the field shown again. 1 when on the text. */
int KeyboardEntry_TouchText(KeyboardEntry *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    if (y < 0x28 || y > 0x38) {
        return 0;
    }
    if (x < self->field_left - 0xc) {
        return 0;
    }
    if (x > self->field_right + 0xc) {
        return 0;
    }
    KeyboardEntry_PlaceCursorAtX(self, x);
    KeyboardEntry_MarkFromPosition(self);
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_MARK_DRAG);
    func_ov095_0229b3ec(keyboard_entry_keyboard(self));
    KeyboardEntry_ShowField(self);
    return 1;
}
CLEAN_AS(func_ov126_022a07e8, KeyboardEntry_TouchText)

/* func_ov126_022a0854: the cursor put at the character nearest x (x from the field's start,
 * at least 0, cut to a byte); the keys follow. */
void KeyboardEntry_PlaceCursorAtX(KeyboardEntry *self, int x)
{
    int offset = x - self->field_left;
    if (offset < 0) {
        offset = 0;
    }
    u8 position;
    u8 before = func_ov095_0229bb34(keyboard_entry_keyboard_arg(self), self->text, self->max_chars, self->field_width,
                                    (u8) offset, &position);
    self->cursor_x = before + self->field_left;
    KeyboardEntry_SetPosition(self, (char) position);
    KeyboardEntry_UpdateKeys(self);
}
CLEAN_AS(func_ov126_022a0854, KeyboardEntry_PlaceCursorAtX)

/* func_ov126_022a08c4: the cursor drawn after the text's characters before it.
 * QUIRK: their width is cut to a byte. */
void KeyboardEntry_PlaceCursor(KeyboardEntry *self)
{
    self->cursor_x = self->field_left;
    self->cursor_y = KEYBOARD_ENTRY_CURSOR_Y;
    self->cursor_x += (u8) TextString_Width(self->text, self->position);
}
CLEAN_AS(func_ov126_022a08c4, KeyboardEntry_PlaceCursor)

/* func_ov126_022a0904: the character before the cursor, 0 at the start. */
unsigned short KeyboardEntry_CharacterBeforeCursor(KeyboardEntry *self)
{
    if (self->position == 0) {
        return 0;
    }
    return self->text[self->position - 1];
}
CLEAN_AS(func_ov126_022a0904, KeyboardEntry_CharacterBeforeCursor)

/* func_ov126_022a0924: the cursor at `position`, shown at once (its blink restarted in the
 * shown half). */
void KeyboardEntry_SetPosition(KeyboardEntry *self, char position)
{
    self->position = (u8) position;
    self->blink = 0x10;
}
CLEAN_AS(func_ov126_022a0924, KeyboardEntry_SetPosition)

/* func_ov126_022a0934: the text cursor shown at the start, without marks; the keyboard's keys
 * reset and the keys the text allows. */
void KeyboardEntry_ShowCursor(KeyboardEntry *self)
{
    KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_CURSOR_SHOWN);
    self->cursor_x = self->field_left;
    self->cursor_y = KEYBOARD_ENTRY_CURSOR_Y;
    KeyboardEntry_SetPosition(self, 0);
    KeyboardEntry_ClearMarks(self);
    func_ov095_0229cd30(keyboard_entry_keyboard_arg(self));
    KeyboardEntry_UpdateKeys(self);
}
CLEAN_AS(func_ov126_022a0934, KeyboardEntry_ShowCursor)

/* func_ov126_022a0978: what the text allows: the OK button dimmed while the text is empty (with
 * an OK button), key 0 disabled, the copy key while marking, the paste key with copied text, and
 * key 6 (with keys 3-5) by the marks or the character before the cursor. */
void KeyboardEntry_UpdateKeys(KeyboardEntry *self)
{
    void *keyboard = keyboard_entry_keyboard(self);

    if (self->panel_kind == KEYBOARD_ENTRY_PANEL_OK_CANCEL || self->panel_kind == KEYBOARD_ENTRY_PANEL_OK) {
        if (TextString_TrimmedLength(self->text, self->max_chars) == 0) {
            ButtonPanel_SetSpriteFlag4(&self->panel, KEYBOARD_ENTRY_BUTTON_OK);
        } else {
            ButtonPanel_ClearSpriteFlag4(&self->panel, KEYBOARD_ENTRY_BUTTON_OK);
        }
    }
    func_ov095_0229cef4(keyboard, KEYBOARD_ENTRY_KEY_0);
    if (KeyboardEntry_IsMarking(self) != 0) {
        func_ov095_0229ce84(keyboard, KEYBOARD_ENTRY_KEY_COPY);
    } else {
        func_ov095_0229cef4(keyboard, KEYBOARD_ENTRY_KEY_COPY);
    }
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_COPIED) != 0) {
        func_ov095_0229ce84(keyboard, KEYBOARD_ENTRY_KEY_PASTE);
    } else {
        func_ov095_0229cef4(keyboard, KEYBOARD_ENTRY_KEY_PASTE);
    }
    if (KeyboardEntry_IsMarking(self) != 0) {
        func_ov095_0229bee4(keyboard);
        func_ov095_0229ce84(keyboard, KEYBOARD_ENTRY_KEY_6);
    } else if (self->position == 0) {
        func_ov095_0229bee4(keyboard);
    } else {
        func_ov095_0229bed8(keyboard, KeyboardEntry_CharacterBeforeCursor(self));
    }
}
CLEAN_AS(func_ov126_022a0978, KeyboardEntry_UpdateKeys)

/* --- The panel's buttons pressed --- */

/* func_ov126_022a0a50: B with nothing to delete: with the two buttons it presses cancel, with
 * the cancelling button that one (the pointer at rest first); else a buzz. 1 when pressed. */
int KeyboardEntry_NothingToDelete(KeyboardEntry *self)
{
    switch (self->panel_kind) {
        case KEYBOARD_ENTRY_PANEL_OK_CANCEL:
            KeyboardEntry_RestPointer(self);
            KeyboardEntry_PressButton(self, 1);
            return 1;
        case KEYBOARD_ENTRY_PANEL_CANCEL:
            KeyboardEntry_RestPointer(self);
            KeyboardEntry_PressButton(self, 0);
            return 1;
        default:
            KeyboardEntry_Buzz(self);
            return 0;
    }
}
CLEAN_AS(func_ov126_022a0a50, KeyboardEntry_NothingToDelete)

/* func_ov126_022a0a90: the OK button pressed (the pointer at rest first) when it is not dimmed
 * and the panel has it; else a buzz. 1 when pressed. */
int KeyboardEntry_PressOk(KeyboardEntry *self)
{
    if (ButtonPanel_HasSpriteFlag4(&self->panel, KEYBOARD_ENTRY_BUTTON_OK) != 0) {
        KeyboardEntry_Buzz(self);
        return 0;
    }
    if (self->panel_kind == KEYBOARD_ENTRY_PANEL_OK_CANCEL || self->panel_kind == KEYBOARD_ENTRY_PANEL_OK) {
        KeyboardEntry_RestPointer(self);
        KeyboardEntry_PressButton(self, 0);
        return 1;
    }
    KeyboardEntry_Buzz(self);
    return 0;
}
CLEAN_AS(func_ov126_022a0a90, KeyboardEntry_PressOk)

/* func_ov126_022a0ae0: the panel's OK button (cancelling with the cancelling kind) or its cancel
 * button selected, with its sound; its press then plays (KEYBOARD_ENTRY_SUB_PANEL_PRESS) and the
 * input finishes (KEYBOARD_ENTRY_STATE_FINISH). */
void KeyboardEntry_PressButton(KeyboardEntry *self, int cancel)
{
    if (cancel == 0) {
        ButtonPanel_Select(&self->panel, KEYBOARD_ENTRY_BUTTON_OK);
        if (self->panel_kind == KEYBOARD_ENTRY_PANEL_CANCEL) {
            KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED);
        } else {
            KeyboardEntry_ClearFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED);
        }
    } else {
        ButtonPanel_Select(&self->panel, KEYBOARD_ENTRY_BUTTON_CANCEL);
        KeyboardEntry_SetFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED);
    }
    if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_NEW_FRIEND) != 0) {
        if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED) != 0) {
            SoundSys_PlaySe(KEYBOARD_ENTRY_SE_CANCEL_FRIEND);
        } else if (GroupParams_Mode() == KEYBOARD_ENTRY_MODE_NEW_FRIEND_TEXT_18) {
            SoundSys_PlaySe(KEYBOARD_ENTRY_SE_OK);
        } else {
            SoundSys_PlaySe(KEYBOARD_ENTRY_SE_OK_FRIEND);
        }
    } else if (KeyboardEntry_TestFlags(self, KEYBOARD_ENTRY_FLAG_CANCELLED) != 0) {
        SoundSys_PlaySe(KEYBOARD_ENTRY_SE_CANCEL);
    } else {
        SoundSys_PlaySe(KEYBOARD_ENTRY_SE_OK);
    }
    self->base.state = KEYBOARD_ENTRY_STATE_FINISH;
    MenuScene_SetSubState(keyboard_entry_scene(self), KEYBOARD_ENTRY_SUB_PANEL_PRESS);
}
CLEAN_AS(func_ov126_022a0ae0, KeyboardEntry_PressButton)
