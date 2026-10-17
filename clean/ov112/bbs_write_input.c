/* The bulletin board writing scene of overlay 112 (bbs_write_scene.h): its input. The keyboard of
 * overlay 95 by the buttons or the pen, the text cursor moved by the d-pad, the keys' codes acted
 * on (typing, deleting, converting, copying, pasting), the scroll bar's knob, and the panel's
 * question whether to post (or to quit) and its answer. */
#include "bbs_write_scene.h"

#include <stdint.h>

#include "autoload_2/input.h"
#include "bbs_write_keyboard.h"
#include "clean.h"
#include "main/bbs.h"
#include "main/cell_layer_sprite.h"
#include "main/dual_cell_sprite.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_string.h"
#include "main/villager_part.h"
#include "ov002/key_repeat.h"

/* The buttons (main's PadState bits), and the pen: down, and down or up since the frame before. */
extern PadState data_021fbe40;
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* the touch's x, while the pen is down */
extern u8 data_021f6c54; /* and its y */

#define BBS_WRITE_PAD_A 0x0001
#define BBS_WRITE_PAD_B 0x0002
#define BBS_WRITE_PAD_START 0x0008
#define BBS_WRITE_PAD_R 0x0100
#define BBS_WRITE_PAD_L 0x0200
#define BBS_WRITE_PAD_Y 0x0800

/* The panel's buttons: the post and quit buttons under the text, and the question's answers. */
#define BBS_WRITE_BUTTON_QUIT 8
#define BBS_WRITE_BUTTON_POST 9
#define BBS_WRITE_BUTTON_YES 3
#define BBS_WRITE_BUTTON_NO 4

/* The characters before a 0, at most `max` (main's). */
extern int func_02051c8c_unk(u16 *text, int max);

static MenuScene *bbs_write_scene(BbsWriteScene *self)
{
    return &self->base;
}

static int bbs_write_keyboard_arg(BbsWriteScene *self)
{
    return (int) (uintptr_t) self->keyboard;
}

static CellLayerSprite *bbs_write_pointer_cells(BbsWriteScene *self)
{
    /* The pointer's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->pointer;
}

static DualCellSprite *bbs_write_button_cells(BbsWriteScene *self)
{
    /* The knob's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->scroll_button;
}

/* The pointer's update through its class (vtable slot 3). */
static void bbs_write_update_pointer(BbsWriteScene *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->pointer.vtable;
    vtable[3](&self->pointer);
}

static int bbs_write_pen_put_down(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The key held down (by A or the pen) acted on again. */
static void bbs_write_repeat_held_key(BbsWriteScene *self)
{
    int key = func_ov095_0229c548(self->keyboard);
    BbsWrite_Command(self, func_ov095_0229c448(self->keyboard, key, BBS_WRITE_CODE_MODE));
    func_ov095_0229c8e4(bbs_write_keyboard_arg(self), key);
}

/* --- Beginning the input --- */

/* func_ov112_0229fe84: the question's answer by the buttons, the pointer shown at its button 4
 * (no). */
void BbsWrite_BeginPanelKeys(BbsWriteScene *self)
{
    MenuScene_ResetKeyRepeat(bbs_write_scene(self));
    self->answer = 1;
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    bbs_write_update_pointer(self);
    int x = ButtonPanel_ButtonX(&self->panel, BBS_WRITE_BUTTON_NO);
    int y = ButtonPanel_ButtonY(&self->panel, BBS_WRITE_BUTTON_NO);
    Glider_PlaceAt(&self->pointer, x, y);
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_PANEL_KEYS);
}
CLEAN_AS(func_ov112_0229fe84, BbsWrite_BeginPanelKeys)

/* func_ov112_0229fee4: the question's answer by the pen, the pointer hidden. Gives the sub
 * state's address (as a number). */
int BbsWrite_BeginPanelTouch(BbsWriteScene *self)
{
    BbsWrite_HidePointer(self);
    return (int) (uintptr_t) MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_PANEL_TOUCH);
}
CLEAN_AS(func_ov112_0229fee4, BbsWrite_BeginPanelTouch)

/* func_ov112_0229fefc: the input by the pen (BbsWrite_BeginTouch) or by the buttons, as main's
 * state flag 2 says. Gives the sub state's address (as a number). */
int BbsWrite_BeginInput(BbsWriteScene *self)
{
    if (StateFlags_IsClear2()) {
        return (int) (uintptr_t) BbsWrite_BeginTouch(self);
    }
    return (int) (uintptr_t) BbsWrite_BeginKeys(self);
}
CLEAN_AS(func_ov112_0229fefc, BbsWrite_BeginInput)

/* func_ov112_0229ff1c: the keyboard by the buttons, the pointer on its key. */
unsigned char *BbsWrite_BeginKeys(BbsWriteScene *self)
{
    MenuScene_ResetKeyRepeat(bbs_write_scene(self));
    BbsWrite_PointAtKey(self);
    return MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEYS);
}
CLEAN_AS(func_ov112_0229ff1c, BbsWrite_BeginKeys)

/* func_ov112_0229ff38: the input by the pen, the pointer hidden. */
unsigned char *BbsWrite_BeginTouch(BbsWriteScene *self)
{
    BbsWrite_HidePointer(self);
    return MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_TOUCH);
}
CLEAN_AS(func_ov112_0229ff38, BbsWrite_BeginTouch)

/* func_ov112_0229ff50: sound 0x34 (what could not be done). */
void BbsWrite_PlaySound34(BbsWriteScene *self)
{
    (void) self;
    SoundSys_PlaySe(0x34);
}
CLEAN_AS(func_ov112_0229ff50, BbsWrite_PlaySound34)

/* --- Leaving, the question and its answers --- */

/* func_ov112_0229ff5c: main asked the menu to close: sound 0x28, the cursor and the pointer
 * hidden, the scroll back to the top, and the scene closes (state 12) as when quitting. */
void BbsWrite_CloseOnRequest(BbsWriteScene *self)
{
    SoundSys_PlaySe(0x28);
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_CURSOR_SHOWN);
    BbsWrite_HidePointer(self);
    BbsWrite_ScrollTo(self, 0);
    MenuScene_SetState(bbs_write_scene(self), BBS_WRITE_STATE_CLOSE);
    MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_STATES);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_QUITTING);
}
CLEAN_AS(func_ov112_0229ff5c, BbsWrite_CloseOnRequest)

/* func_ov112_0229ffa0: "no": sound 0x29 to the quit question, 0x2a to the post question; the
 * panel's button 4 pressed, then back to the writing (state 6). */
void BbsWrite_AnswerNo(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_QUITTING) != 0) {
        SoundSys_PlaySe(0x29);
    } else {
        SoundSys_PlaySe(0x2a);
    }
    BbsWrite_PressPanelButton(self, BBS_WRITE_STATE_ANSWER_NO, BBS_WRITE_BUTTON_NO);
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_ASKING);
}
CLEAN_AS(func_ov112_0229ffa0, BbsWrite_AnswerNo)

/* func_ov112_0229ffdc: "yes": the panel's button 3 pressed, then the scene ends (state 10). To
 * the quit question, sound 0x28; to the post question the text is posted on the board, sound
 * 0x27, the post sent to the session and the current player's villager part marked (type 18). */
void BbsWrite_AnswerYes(BbsWriteScene *self)
{
    BbsWrite_PressPanelButton(self, BBS_WRITE_STATE_ANSWER_YES, BBS_WRITE_BUTTON_YES);
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_QUITTING) != 0) {
        SoundSys_PlaySe(0x28);
    } else {
        Bbs_PostText(self->text);
        SoundSys_PlaySe(0x27);
        BbsWrite_SendPost(self);
        VillagerPart_MarkType18((VillagerPart *) (void *) PlayerRecord_VillagerPart(PlayerRecords_Current()));
    }
}
CLEAN_AS(func_ov112_0229ffdc, BbsWrite_AnswerYes)

/* func_ov112_022a0028: the quit question asked (sound 0x2a, the panel's button 8 pressed, then
 * state 2); no mark, the lines drawn again. */
void BbsWrite_AskQuit(BbsWriteScene *self)
{
    SoundSys_PlaySe(0x2a);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_QUITTING);
    BbsWrite_PressPanelButton(self, BBS_WRITE_STATE_ASK, BBS_WRITE_BUTTON_QUIT);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_ASKING);
    BbsWrite_EndMark(self);
    BbsWrite_Refresh(self);
}
CLEAN_AS(func_ov112_022a0028, BbsWrite_AskQuit)

/* func_ov112_022a0068: the post question asked (sound 0x29, the panel's button 9 pressed, then
 * state 2); the taboo words filtered out of the text, no mark, the lines drawn again. */
void BbsWrite_AskPost(BbsWriteScene *self)
{
    SoundSys_PlaySe(0x29);
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_QUITTING);
    BbsWrite_PressPanelButton(self, BBS_WRITE_STATE_ASK, BBS_WRITE_BUTTON_POST);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_ASKING);
    BbsWrite_FilterTaboo(self);
    BbsWrite_EndMark(self);
    BbsWrite_Refresh(self);
}
CLEAN_AS(func_ov112_022a0068, BbsWrite_AskPost)

/* --- The text: typing, deleting, copying --- */

/* func_ov112_022a00ac: the copied text put in at the cursor (over the marked characters), one
 * character at a time until one does not fit; sound 0x34 when not even the first did. */
void BbsWrite_Paste(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_COPIED) == 0) {
        return;
    }
    if (BbsWrite_HasMark(self) != 0) {
        BbsWrite_DeleteMarked(self);
    }
    func_ov095_0229b3ec(self->keyboard);
    func_ov095_0229b394(bbs_write_keyboard_arg(self));
    int count = func_02051c8c_unk(self->clipboard, BBS_POST_LENGTH);
    for (int i = 0; i < count; i++) {
        if (BbsWrite_InsertChar(self, self->clipboard[i], 0) == 0) {
            if (i == 0) {
                BbsWrite_PlaySound34(self);
            }
            break;
        }
    }
    func_ov095_022999e8(self->keyboard);
    BbsWrite_Refresh(self);
    BbsWrite_PlaceCursor(self);
    func_ov095_0229b388(bbs_write_keyboard_arg(self));
}
CLEAN_AS(func_ov112_022a00ac, BbsWrite_Paste)

/* func_ov112_022a0144: the marked characters copied, the paste key enabled. */
void BbsWrite_Copy(BbsWriteScene *self)
{
    if (BbsWrite_HasMark(self) == 0) {
        return;
    }
    u8 to = self->mark_to;
    u8 from = self->mark_from;
    unsigned int first, count;
    if (from > to) {
        first = to;
        count = (unsigned int) (from - to);
    } else {
        first = from;
        count = (unsigned int) (to - from);
    }
    TextString_ClearChars(self->clipboard, BBS_POST_LENGTH);
    TextString_CopyChars(&self->text[first], self->clipboard, (int) count);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_COPIED);
    func_ov095_022999f4(self->keyboard);
    BbsWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov112_022a0144, BbsWrite_Copy)

/* func_ov112_022a01b0: the character before the cursor converted by one of the keyboard's
 * conversions (a code other than the three keeps it as it is); 0 when there is none or it
 * cannot be, else the lines and the cursor brought up to date and 1. */
int BbsWrite_ConvertChar(BbsWriteScene *self, int code)
{
    int character = BbsWrite_CharBeforeCursor(self);
    if (character == 0) {
        return 0;
    }
    switch (code) {
        case BBS_WRITE_CODE_CONVERT_1:
            character = func_ov095_0229bb9c(self->keyboard, character);
            break;
        case BBS_WRITE_CODE_CONVERT_2:
            character = func_ov095_0229bb98(self->keyboard, character);
            break;
        case BBS_WRITE_CODE_CONVERT_3:
            character = func_ov095_0229bb94(self->keyboard, character);
            break;
        default:
            break;
    }
    if (character == 0) {
        return 0;
    }
    if (func_ov095_0229bba0(bbs_write_keyboard_arg(self), self->text, character, self->position) == 0) {
        return 0;
    }
    BbsWrite_Refresh(self);
    BbsWrite_PlaceCursor(self);
    return 1;
}
CLEAN_AS(func_ov112_022a01b0, BbsWrite_ConvertChar)

/* func_ov112_022a0258: a character typed: over the marked characters (the composition dropped),
 * then the lines and the cursor brought up to date. Gives 1 when it was put in. */
int BbsWrite_TypeChar(BbsWriteScene *self, int code)
{
    if (BbsWrite_HasMark(self) != 0) {
        BbsWrite_DeleteMarked(self);
        func_ov095_0229b3ec(self->keyboard);
    }
    int result = BbsWrite_InsertChar(self, code, 1);
    BbsWrite_Refresh(self);
    BbsWrite_PlaceCursor(self);
    return result;
}
CLEAN_AS(func_ov112_022a0258, BbsWrite_TypeChar)

/* func_ov112_022a029c: a character put in at the cursor, which moves past it, when it fits in the
 * six lines. Gives 1 then, else 0. */
int BbsWrite_InsertChar(BbsWriteScene *self, int code, int notify)
{
    u8 position = self->position;
    if (func_ov095_0229bc00(self->keyboard, self->text, code, &position, BBS_POST_LENGTH, BBS_WRITE_LINE_CHARS,
                            BBS_WRITE_LINES, BBS_WRITE_LINE_WIDTH, 0, notify) != 0) {
        BbsWrite_SetPosition(self, (char) position);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov112_022a029c, BbsWrite_InsertChar)

/* func_ov112_022a02f4: a deletion: the marked characters, else the character being composed or
 * the one before the cursor; at `first_position` the one after it. Then sound 0x35, the lines
 * and the cursor brought up to date; gives 1. With nothing to delete gives 0 (sound 0x34 with
 * `sound_on_fail`). */
int BbsWrite_Backspace(BbsWriteScene *self, int sound_on_fail)
{
    if (BbsWrite_HasMark(self) != 0) {
        func_ov095_0229b3ec(self->keyboard);
        BbsWrite_DeleteMarked(self);
    } else if (self->position > self->first_position) {
        if (func_ov095_0229b3a0(self->keyboard, self->text, self->position) == 0) {
            self->mark_from = self->position;
            self->mark_to = (u8) (self->position - 1);
            BbsWrite_DeleteMarked(self);
        }
    } else if (self->text[self->first_position] != 0) {
        self->mark_from = self->first_position;
        self->mark_to = (u8) (self->first_position + 1);
        BbsWrite_DeleteMarked(self);
    } else {
        if (sound_on_fail != 0) {
            BbsWrite_PlaySound34(self);
        }
        return 0;
    }
    SoundSys_PlaySe(0x35);
    BbsWrite_Refresh(self);
    BbsWrite_PlaceCursor(self);
    return 1;
}
CLEAN_AS(func_ov112_022a02f4, BbsWrite_Backspace)

/* func_ov112_022a03ac: a key's code acted on. Gives what the keyboard gave for its own codes,
 * else 1 for a character or a deletion, 2 for a newline and the other commands, 3 for the post
 * and quit questions. Sound 0x34 when a character could not be put in or converted. */
int BbsWrite_Command(BbsWriteScene *self, int code)
{
    int result = 1;
    int own = func_ov095_0229ba44(self->keyboard, code, BBS_WRITE_KEYBOARD_LAYER);

    if (own != 0) {
        BbsWrite_Refresh(self);
        return own;
    }
    if (func_ov095_0229bebc(self->keyboard, code) != 0) {
        switch (code) {
            case BBS_WRITE_CODE_BACKSPACE:
                BbsWrite_Backspace(self, 1);
                break;
            case BBS_WRITE_CODE_CONVERT_1:
            case BBS_WRITE_CODE_CONVERT_2:
            case BBS_WRITE_CODE_CONVERT_3:
                if (BbsWrite_ConvertChar(self, code) == 0) {
                    BbsWrite_PlaySound34(self);
                }
                result = 2;
                break;
            case BBS_WRITE_CODE_COPY:
                BbsWrite_Copy(self);
                result = 2;
                break;
            case BBS_WRITE_CODE_PASTE:
                BbsWrite_Paste(self);
                result = 2;
                break;
            case BBS_WRITE_CODE_POST:
                BbsWrite_AskPost(self);
                result = 3;
                break;
            case BBS_WRITE_CODE_QUIT:
                BbsWrite_AskQuit(self);
                result = 3;
                break;
            default:
                result = 2;
                break;
        }
    } else {
        /* QUIRK: the code is cut to 16 bits as a character. */
        if (BbsWrite_TypeChar(self, (u16) code) == 0) {
            BbsWrite_PlaySound34(self);
        }
        if (code == BBS_WRITE_CODE_NEWLINE) {
            result = 2;
        }
    }
    return result;
}
CLEAN_AS(func_ov112_022a03ac, BbsWrite_Command)

/* func_ov112_022a04b8: the key under the pen pressed and its code acted on (gives
 * BbsWrite_Command's result), its repeat started; 0 when no key is there. */
int BbsWrite_TouchKey(BbsWriteScene *self)
{
    func_ov095_0229cce0(self->keyboard);
    int key = func_ov095_0229c54c(self->keyboard, data_021f6c58, data_021f6c54);
    if (key == -1) {
        return 0;
    }
    int result = BbsWrite_Command(self, func_ov095_0229c448(self->keyboard, key, BBS_WRITE_CODE_MODE));
    func_ov095_0229c8e4(bbs_write_keyboard_arg(self), key);
    func_ov095_0229bf3c(self->keyboard);
    return result;
}
CLEAN_AS(func_ov112_022a04b8, BbsWrite_TouchKey)

/* --- The buttons --- */

/* func_ov112_022a051c: Start pressed: the post question. */
int BbsWrite_PostKey(BbsWriteScene *self)
{
    if ((data_021fbe40.pressed & BBS_WRITE_PAD_START) == 0) {
        return 0;
    }
    BbsWrite_HidePointer(self);
    BbsWrite_AskPost(self);
    return 1;
}
CLEAN_AS(func_ov112_022a051c, BbsWrite_PostKey)

/* func_ov112_022a0548: L pressed: the marked characters copied, when the copy key is enabled;
 * then until L is let go. */
int BbsWrite_CopyKey(BbsWriteScene *self)
{
    if ((data_021fbe40.pressed & BBS_WRITE_PAD_L) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(self->keyboard, BBS_WRITE_KEY_COPY) != 0) {
        return 0;
    }
    BbsWrite_Command(self, BBS_WRITE_CODE_COPY);
    func_ov095_0229c8e4(bbs_write_keyboard_arg(self), BBS_WRITE_KEY_L);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_WHILE_L);
    return 1;
}
CLEAN_AS(func_ov112_022a0548, BbsWrite_CopyKey)

/* func_ov112_022a05b0: R pressed: the copied text pasted, when the paste key is enabled; then
 * until R is let go. */
int BbsWrite_PasteKey(BbsWriteScene *self)
{
    if ((data_021fbe40.pressed & BBS_WRITE_PAD_R) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(self->keyboard, BBS_WRITE_KEY_PASTE) != 0) {
        return 0;
    }
    BbsWrite_Command(self, BBS_WRITE_CODE_PASTE);
    func_ov095_0229c8e4(bbs_write_keyboard_arg(self), BBS_WRITE_KEY_R);
    BbsWrite_PlacePointer(self);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_WHILE_R);
    return 1;
}
CLEAN_AS(func_ov112_022a05b0, BbsWrite_PasteKey)

/* func_ov112_022a0620: Y pressed: the pointer moves from the key to the text cursor or back.
 * QUIRK: the sub state set with the pointer's turn is replaced at once by
 * BbsWrite_GlidePointer's. */
int BbsWrite_SwitchPointerKey(BbsWriteScene *self)
{
    if ((data_021fbe40.pressed & BBS_WRITE_PAD_Y) == 0) {
        return 0;
    }
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT) != 0) {
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT);
    } else {
        BbsWrite_SetFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT);
        BbsWrite_ScrollToCursor(self);
    }
    if (func_ov095_0229cda4(self->keyboard, -1) != 0) {
        if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT) != 0) {
            Glider_TurnToSetA(&self->pointer);
            MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_TEXT_KEYS);
        } else {
            Glider_TurnToSetB(&self->pointer);
            MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEYS);
        }
    }
    BbsWrite_GlidePointer(self);
    return 1;
}
CLEAN_AS(func_ov112_022a0620, BbsWrite_SwitchPointerKey)

/* func_ov112_022a06b8: B held: a character deleted, and again while it stays held; with nothing
 * to delete, the quit question. QUIRK: B is read held, not pressed. */
int BbsWrite_BackspaceKey(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_B) == 0) {
        return 0;
    }
    if (BbsWrite_Backspace(self, 0) != 0) {
        func_ov095_0229bf3c(self->keyboard);
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_BACKSPACE_REPEAT);
    } else {
        BbsWrite_HidePointer(self);
        BbsWrite_AskQuit(self);
    }
    return 1;
}
CLEAN_AS(func_ov112_022a06b8, BbsWrite_BackspaceKey)

/* func_ov112_022a0710: A pressed on a key that can be pressed: the key shown pressed; its code
 * is acted on once the pointer's press has played (BBS_WRITE_SUB_KEY_PRESSED). */
int BbsWrite_PressKeyByA(BbsWriteScene *self)
{
    if ((data_021fbe40.pressed & BBS_WRITE_PAD_A) == 0) {
        return 0;
    }
    int key = func_ov095_02299a00(self->keyboard);
    if (key == -1) {
        return 0;
    }
    /* QUIRK: the key's code is looked up and not used. */
    func_ov095_0229c448(self->keyboard, key, BBS_WRITE_CODE_MODE);
    func_ov095_0229c8e4(bbs_write_keyboard_arg(self), key);
    BbsWrite_BeginKeyPressed(self);
    return 1;
}
CLEAN_AS(func_ov112_022a0710, BbsWrite_PressKeyByA)

/* --- The sub states --- */

/* func_ov112_022a0768 (BBS_WRITE_SUB_ERROR): the error message shown; once it is done, the
 * input. */
void BbsWrite_RunError(BbsWriteScene *self)
{
    func_ov095_0229bf48(self->keyboard);
    if (ErrorMessage_Update(&self->error, 1) != 0) {
        BbsWrite_BeginInput(self);
    }
}
CLEAN_AS(func_ov112_022a0768, BbsWrite_RunError)

/* func_ov112_022a0798 (BBS_WRITE_SUB_BUTTON): while the panel's button is pressed, a shown
 * pointer follows its press; once the press is over the pointer hidden and the scene's state
 * runs (phase 1). */
void BbsWrite_RunButton(BbsWriteScene *self)
{
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        if (CellLayerSprite_AnimNumber(bbs_write_pointer_cells(self)) != 0) {
            int frame = ButtonPanel_SelectedPressFrame(&self->panel);
            int x = ButtonPanel_ButtonX(&self->panel, -1);
            int y = ButtonPanel_ButtonY(&self->panel, -1);
            Glider_PlaceAt(&self->pointer, frame + x, frame + y);
        }
    } else {
        BbsWrite_HidePointer(self);
        MenuScene_SetPhase(bbs_write_scene(self), BBS_WRITE_PHASE_STATES);
    }
}
CLEAN_AS(func_ov112_022a0798, BbsWrite_RunButton)

/* func_ov112_022a0804 (BBS_WRITE_SUB_PANEL_PRESSED): once the pointer's press has played, the
 * answer pointed at. */
void BbsWrite_RunPanelPressed(BbsWriteScene *self)
{
    if (CellLayerSprite_IsDone(bbs_write_pointer_cells(self)) != 0) {
        if (self->answer != 0) {
            BbsWrite_AnswerNo(self);
        } else {
            BbsWrite_AnswerYes(self);
        }
    }
}
CLEAN_AS(func_ov112_022a0804, BbsWrite_RunPanelPressed)

/* func_ov112_022a0838 (BBS_WRITE_SUB_PANEL_KEYS): the question's answer by the buttons: A
 * presses the one pointed at, left and right move the pointer between buttons 3 (yes) and 4
 * (no); then B answers no and Start yes. The pen switches to the answer by the pen. */
void BbsWrite_RunPanelKeys(BbsWriteScene *self)
{
    if (MenuScene_TakeTouch(bbs_write_scene(self)) != 0) {
        BbsWrite_BeginPanelTouch(self);
        return;
    }
    if (data_021fbe40.pressed & BBS_WRITE_PAD_A) {
        Glider_ShowSecondOfSet(&self->pointer);
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_PANEL_PRESSED);
        return;
    }
    u8 old = self->answer;
    int keys = (int) MenuScene_LatchRepeatedKeys(bbs_write_scene(self));
    if (KeyRepeat_HasLeft(keys) != 0) {
        if (self->answer != 0) {
            self->answer--;
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (self->answer < 1) {
            self->answer++;
        }
    }
    if (old != self->answer) {
        int button = self->answer != 0 ? BBS_WRITE_BUTTON_NO : BBS_WRITE_BUTTON_YES;
        int x = ButtonPanel_ButtonX(&self->panel, button);
        int y = ButtonPanel_ButtonY(&self->panel, button);
        BbsWrite_GlidePointerTo(self, x, y);
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & BBS_WRITE_PAD_B) {
        BbsWrite_HidePointer(self);
        BbsWrite_AnswerNo(self);
        return;
    }
    if (pressed & BBS_WRITE_PAD_START) {
        BbsWrite_HidePointer(self);
        BbsWrite_AnswerYes(self);
    }
}
CLEAN_AS(func_ov112_022a0838, BbsWrite_RunPanelKeys)

/* func_ov112_022a0950 (BBS_WRITE_SUB_SCROLL_RELEASE): once the knob is back up, the pointer back
 * to the keyboard. */
void BbsWrite_RunScrollRelease(BbsWriteScene *self)
{
    if (DualCellSprite_IsDone(bbs_write_button_cells(self)) != 0) {
        BbsWrite_BeginKeyReleased(self);
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_POINTER_ON_BUTTON);
    }
}
CLEAN_AS(func_ov112_022a0950, BbsWrite_RunScrollRelease)

/* func_ov112_022a097c (BBS_WRITE_SUB_SCROLL_HELD): while A is held the d-pad scrolls; when it is
 * let go, the knob released. */
void BbsWrite_RunScrollHeld(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_A) == 0) {
        PushButton_Release(&self->scroll_button);
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_SCROLL_RELEASE);
        BbsWrite_Nothing(self);
    } else {
        BbsWrite_ScrollByKeys(self);
    }
}
CLEAN_AS(func_ov112_022a097c, BbsWrite_RunScrollHeld)

/* func_ov112_022a09b8 (BBS_WRITE_SUB_SCROLL_PRESS) */
void BbsWrite_RunScrollPress(BbsWriteScene *self)
{
    if (DualCellSprite_IsDone(bbs_write_button_cells(self)) != 0) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_SCROLL_HELD);
    }
}
CLEAN_AS(func_ov112_022a09b8, BbsWrite_RunScrollPress)

/* func_ov112_022a09dc (BBS_WRITE_SUB_WHILE_R): once R is let go, back to the sub state before,
 * the keys brought up to date. */
void BbsWrite_RunWhileR(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_R) != 0) {
        return;
    }
    MenuScene_SetSubState(bbs_write_scene(self), self->return_sub_state);
    BbsWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov112_022a09dc, BbsWrite_RunWhileR)

/* func_ov112_022a0a0c (BBS_WRITE_SUB_WHILE_L) */
void BbsWrite_RunWhileL(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_L) != 0) {
        return;
    }
    MenuScene_SetSubState(bbs_write_scene(self), self->return_sub_state);
    BbsWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov112_022a0a0c, BbsWrite_RunWhileL)

/* func_ov112_022a0a3c (BBS_WRITE_SUB_MARK_KEYS): while A is held the d-pad moves the end of the
 * mark (sound 0x15); when it is let go, an empty mark ends. */
void BbsWrite_RunMarkKeys(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_A) == 0) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_TEXT_KEYS);
        if (self->mark_from == self->mark_to) {
            BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_MARKING);
        }
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(bbs_write_scene(self));
    if (BbsWrite_MoveCursorByKeys(self, keys) != 0) {
        self->mark_to = self->position;
        BbsWrite_Refresh(self);
        BbsWrite_PlaceCursor(self);
        BbsWrite_PlacePointer(self);
        SoundSys_PlaySe(0x15);
    }
}
CLEAN_AS(func_ov112_022a0a3c, BbsWrite_RunMarkKeys)

/* func_ov112_022a0ab0 (BBS_WRITE_SUB_TEXT_KEYS): the pointer at the text cursor, by the buttons:
 * the d-pad moves the cursor (ending the mark, sound 0xb), Y goes back to the keys, B deletes,
 * A begins a mark, L copies, R pastes, Start asks to post. QUIRK: after A begins a mark, L, R
 * and Start are still read in the same frame. */
void BbsWrite_RunTextKeys(BbsWriteScene *self)
{
    if (MenuScene_TakeTouch(bbs_write_scene(self)) != 0) {
        BbsWrite_BeginTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(bbs_write_scene(self));
    if (BbsWrite_MoveCursorByKeys(self, keys) != 0) {
        BbsWrite_EndMark(self);
        BbsWrite_PlaceCursor(self);
        BbsWrite_PlacePointer(self);
        BbsWrite_UpdateKeys(self);
        SoundSys_PlaySe(0xb);
        return;
    }
    if (BbsWrite_SwitchPointerKey(self) != 0) {
        return;
    }
    u8 old = self->position;
    if (BbsWrite_BackspaceKey(self) != 0) {
        if (old != self->position) {
            BbsWrite_PlacePointer(self);
        }
        return;
    }
    if (data_021fbe40.pressed & BBS_WRITE_PAD_A) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_MARK_KEYS);
        BbsWrite_SetFlags(self, BBS_WRITE_FLAG_MARKING);
        self->mark_from = self->position;
        self->mark_to = self->position;
    }
    if (BbsWrite_CopyKey(self) != 0) {
        return;
    }
    if (BbsWrite_PasteKey(self) != 0) {
        return;
    }
    BbsWrite_PostKey(self);
}
CLEAN_AS(func_ov112_022a0ab0, BbsWrite_RunTextKeys)

/* func_ov112_022a0b84 (BBS_WRITE_SUB_BACKSPACE_REPEAT): while B is held, a character deleted
 * each time the repeat is due (the pointer kept on the cursor); with nothing left to delete,
 * the quit question. */
void BbsWrite_RunBackspaceRepeat(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_B) == 0) {
        MenuScene_SetSubState(bbs_write_scene(self), self->return_sub_state);
        return;
    }
    if (func_ov095_0229bf0c(self->keyboard) == 0) {
        return;
    }
    if (BbsWrite_Backspace(self, 0) != 0) {
        if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT) != 0) {
            BbsWrite_PlacePointer(self);
        }
    } else {
        BbsWrite_HidePointer(self);
        BbsWrite_AskQuit(self);
    }
}
CLEAN_AS(func_ov112_022a0b84, BbsWrite_RunBackspaceRepeat)

/* func_ov112_022a0be8 (BBS_WRITE_SUB_KEY_RELEASED): once the pointer's animation has played,
 * the keyboard by the buttons. */
void BbsWrite_RunKeyReleased(BbsWriteScene *self)
{
    if (CellLayerSprite_IsDone(bbs_write_pointer_cells(self)) != 0) {
        BbsWrite_PointerFirstOfSet(self);
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEYS);
    }
}
CLEAN_AS(func_ov112_022a0be8, BbsWrite_RunKeyReleased)

/* func_ov112_022a0c10 (BBS_WRITE_SUB_KEY_REPEAT): while A is held, the key held down acted on
 * again each time the repeat is due. */
void BbsWrite_RunKeyRepeat(BbsWriteScene *self)
{
    if ((data_021fbe40.held & BBS_WRITE_PAD_A) == 0) {
        BbsWrite_BeginKeyReleased(self);
        return;
    }
    if (func_ov095_0229bf0c(self->keyboard) != 0) {
        bbs_write_repeat_held_key(self);
    }
}
CLEAN_AS(func_ov112_022a0c10, BbsWrite_RunKeyRepeat)

/* func_ov112_022a0c6c (BBS_WRITE_SUB_KEY_PRESSED): once the pointer's press has played, the key
 * pressed by A acted on. The scroll key presses the knob (and ends the mark); a key still held
 * repeats; otherwise back to the keyboard. QUIRK: with a mark, the lines are drawn again before
 * the mark ends, so they still show it marked. */
void BbsWrite_RunKeyPressed(BbsWriteScene *self)
{
    if (CellLayerSprite_IsDone(bbs_write_pointer_cells(self)) == 0) {
        return;
    }
    int key = func_ov095_02299a00(self->keyboard);
    int code = func_ov095_0229c448(self->keyboard, key, BBS_WRITE_CODE_MODE);
    if (code == BBS_WRITE_CODE_SCROLL) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_SCROLL_PRESS);
        PushButton_Press(&self->scroll_button);
        PushButton_PressCue(&self->scroll_button);
        if (BbsWrite_HasMark(self) != 0) {
            BbsWrite_Refresh(self);
        }
        BbsWrite_EndMark(self);
        BbsWrite_SetFlags(self, BBS_WRITE_FLAG_POINTER_ON_BUTTON);
        return;
    }
    int result = BbsWrite_Command(self, code);
    if (result == 1 && (data_021fbe40.held & BBS_WRITE_PAD_A) != 0) {
        func_ov095_0229bf3c(self->keyboard);
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEY_REPEAT);
        func_ov095_0229c8e4(bbs_write_keyboard_arg(self), key);
    } else if (result != 3) {
        if (result == 4) {
            func_ov095_0229cce0(self->keyboard);
        } else {
            BbsWrite_BeginKeyReleased(self);
        }
    }
}
CLEAN_AS(func_ov112_022a0c6c, BbsWrite_RunKeyPressed)

/* func_ov112_022a0d40 (BBS_WRITE_SUB_POINTER_GLIDE): once the pointer stops, the sub state to
 * return to, run at once. */
void BbsWrite_RunPointerGlide(BbsWriteScene *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(bbs_write_scene(self), self->return_sub_state);
        BbsWrite_RunSubState(self);
    }
}
CLEAN_AS(func_ov112_022a0d40, BbsWrite_RunPointerGlide)

/* func_ov112_022a0d6c (BBS_WRITE_SUB_KEYS): the keyboard by the buttons: the d-pad moves its
 * cursor, and past its edge the pointer turns to the text; else A, B, Y, L, R and Start, the
 * first that acts. The pen switches to the input by the pen. */
void BbsWrite_RunKeys(BbsWriteScene *self)
{
    if (MenuScene_TakeTouch(bbs_write_scene(self)) != 0) {
        BbsWrite_BeginTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(bbs_write_scene(self));
    switch (func_ov095_02299a54(self->keyboard, keys)) {
        case 1:
            Glider_TurnToSetA(&self->pointer);
            BbsWrite_GlidePointer(self);
            break;
        case 2:
            Glider_TurnToSetC(&self->pointer);
            BbsWrite_GlidePointer(self);
            break;
        case 3:
            Glider_TurnToSetB(&self->pointer);
            BbsWrite_GlidePointer(self);
            break;
        default:
            if (BbsWrite_PressKeyByA(self) != 0) {
                return;
            }
            if (BbsWrite_BackspaceKey(self) != 0) {
                return;
            }
            if (BbsWrite_SwitchPointerKey(self) != 0) {
                return;
            }
            if (BbsWrite_CopyKey(self) != 0) {
                return;
            }
            if (BbsWrite_PasteKey(self) != 0) {
                return;
            }
            BbsWrite_PostKey(self);
            break;
    }
}
CLEAN_AS(func_ov112_022a0d6c, BbsWrite_RunKeys)

/* func_ov112_022a0e24 (BBS_WRITE_SUB_PANEL_TOUCH): the question's answer by the pen: the panel's
 * button 3 (yes) or 4 (no) touched. The buttons switch to the answer by the buttons. */
void BbsWrite_RunPanelTouch(BbsWriteScene *self)
{
    if (MenuScene_TakeButtons(bbs_write_scene(self), 1) != 0) {
        BbsWrite_BeginPanelKeys(self);
        return;
    }
    if (!bbs_write_pen_put_down()) {
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, BBS_WRITE_BUTTON_YES) != 0) {
        BbsWrite_AnswerYes(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, BBS_WRITE_BUTTON_NO) != 0) {
        BbsWrite_AnswerNo(self);
    }
}
CLEAN_AS(func_ov112_022a0e24, BbsWrite_RunPanelTouch)

/* func_ov112_022a0e90 (BBS_WRITE_SUB_KEY_TOUCH_HELD): while the pen is down the key it holds
 * acted on again each time the repeat is due. */
void BbsWrite_RunKeyTouchHeld(BbsWriteScene *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_TOUCH);
        return;
    }
    if (func_ov095_0229bf0c(self->keyboard) != 0) {
        bbs_write_repeat_held_key(self);
    }
}
CLEAN_AS(func_ov112_022a0e90, BbsWrite_RunKeyTouchHeld)

/* func_ov112_022a0eec (BBS_WRITE_SUB_MARK_DRAG): while the pen is down the end of the mark
 * follows it (sound 0x15 when it moves); when it is lifted, an empty mark ends. The scroll and
 * the lines kept on the cursor. */
void BbsWrite_RunMarkDrag(BbsWriteScene *self)
{
    int moved;

    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_TOUCH);
        if (self->mark_from == self->mark_to) {
            BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_MARKING);
        }
        moved = 1;
    } else {
        moved = BbsWrite_DragMark(self);
        if (moved != 0) {
            SoundSys_PlaySe(0x15);
        }
    }
    if (moved != 0) {
        BbsWrite_ScrollToCursor(self);
        BbsWrite_Refresh(self);
    }
}
CLEAN_AS(func_ov112_022a0eec, BbsWrite_RunMarkDrag)

/* func_ov112_022a0f4c (BBS_WRITE_SUB_BAR_TOUCH): the cursor's blink restarted hidden; while the
 * pen is down on the scroll bar the knob moves toward it, when it is lifted the knob released. */
void BbsWrite_RunBarTouch(BbsWriteScene *self)
{
    self->blink = 0;
    if (data_021fbdd8 == 0) {
        BbsWrite_Nothing(self);
        PushButton_Release(&self->scroll_button);
        BbsWrite_BeginTouch(self);
    } else {
        BbsWrite_MoveKnobToTouch(self);
    }
}
CLEAN_AS(func_ov112_022a0f4c, BbsWrite_RunBarTouch)

/* func_ov112_022a0f88 (BBS_WRITE_SUB_KNOB_DRAG): the cursor's blink restarted hidden; while the
 * pen is down the knob follows it, when it is lifted the knob released. */
void BbsWrite_RunKnobDrag(BbsWriteScene *self)
{
    self->blink = 0;
    if (data_021fbdd8 == 0) {
        BbsWrite_Nothing(self);
        PushButton_Release(&self->scroll_button);
        BbsWrite_BeginTouch(self);
    } else {
        BbsWrite_DragKnob(self);
    }
}
CLEAN_AS(func_ov112_022a0f88, BbsWrite_RunKnobDrag)

/* func_ov112_022a0fc4 (BBS_WRITE_SUB_TOUCH): the pen put down on the panel's buttons 9 (post)
 * and 8 (quit), on the keyboard's mode tabs, on the text (a mark begun), on the knob (a drag
 * begun), on the scroll bar, or below y 0x48 on a key (once the key pressed before is no longer
 * shown). The buttons switch to the keyboard by the buttons. */
void BbsWrite_RunTouch(BbsWriteScene *self)
{
    if (MenuScene_TakeButtons(bbs_write_scene(self), 1) != 0) {
        BbsWrite_BeginKeys(self);
        return;
    }
    int key_shown = 0;
    if (func_ov095_0229bf48(self->keyboard) != 0) {
        key_shown = 1;
    }
    if (!bbs_write_pen_put_down()) {
        return;
    }
    int y = data_021f6c54;
    if (ButtonPanel_IsTouched(&self->panel, BBS_WRITE_BUTTON_POST) != 0) {
        BbsWrite_AskPost(self);
        return;
    }
    if (ButtonPanel_IsTouched(&self->panel, BBS_WRITE_BUTTON_QUIT) != 0) {
        BbsWrite_AskQuit(self);
        return;
    }
    if (func_ov095_0229aff0(self->keyboard) != 0) {
        func_ov095_0229c22c(self->keyboard, 9, BBS_WRITE_KEYBOARD_LAYER, 1);
        BbsWrite_Refresh(self);
        return;
    }
    if (BbsWrite_StartTouch(self) != 0) {
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_MARK_DRAG);
        func_ov095_0229b3ec(self->keyboard);
        BbsWrite_Refresh(self);
        return;
    }
    if (BbsWrite_StartDrag(self) != 0) {
        PushButton_Press(&self->scroll_button);
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KNOB_DRAG);
        BbsWrite_EndMark(self);
        BbsWrite_Refresh(self);
        return;
    }
    if (BbsWrite_TouchesBar(self) != 0) {
        PushButton_Press(&self->scroll_button);
        MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_BAR_TOUCH);
        BbsWrite_EndMark(self);
        BbsWrite_Refresh(self);
        return;
    }
    if (y >= 0x48 && key_shown == 0) {
        if (BbsWrite_TouchKey(self) == 1) {
            MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEY_TOUCH_HELD);
        }
    }
}
CLEAN_AS(func_ov112_022a0fc4, BbsWrite_RunTouch)
