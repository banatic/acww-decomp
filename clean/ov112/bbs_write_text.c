/* The bulletin board writing scene of overlay 112 (bbs_write_scene.h): its destructors, the post
 * sent to the session, the dimmed screen and the date, the taboo filter, the pointer sprite,
 * the text cursor and the marked range, the scroll and its knob, and the text's lines. */
#include "bbs_write_scene.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "bbs_write_keyboard.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/display_shadow.h"
#include "main/letter_view.h"
#include "main/message_reader.h"
#include "main/session.h"
#include "main/session_link.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "ov002/key_repeat.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(BbsWriteScene, last_line) == 0x94, "last line");
static_assert(offsetof(BbsWriteScene, keyboard_y) == 0xa0 && offsetof(BbsWriteScene, flags) == 0xac, "flags");
static_assert(offsetof(BbsWriteScene, post_sequence) == 0xb4 && offsetof(BbsWriteScene, scroll) == 0xb6, "scroll");
static_assert(offsetof(BbsWriteScene, blink) == 0xbc && offsetof(BbsWriteScene, first_position) == 0xc0, "cursor");
static_assert(offsetof(BbsWriteScene, answer) == 0xc2 && offsetof(BbsWriteScene, text) == 0xc4, "text");
static_assert(offsetof(BbsWriteScene, clipboard) == 0x184 && offsetof(BbsWriteScene, error) == 0x244, "clipboard");
static_assert(offsetof(BbsWriteScene, chars_task) == 0x360 && offsetof(BbsWriteScene, keyboard) == 0x384, "keyboard");
static_assert(offsetof(BbsWriteScene, unk_268c) == 0x268c && offsetof(BbsWriteScene, unk_26d4) == 0x26d4, "labels");
static_assert(offsetof(BbsWriteScene, lines) == 0x3fac && offsetof(BbsWriteScene, scroll_button) == 0x4234, "lines");
static_assert(offsetof(BbsWriteScene, panel) == 0x427c && offsetof(BbsWriteScene, pointer) == 0x4448, "panel");
static_assert(offsetof(BbsWriteScene, filter_text) == 0x44ac && offsetof(BbsWriteScene, filter_wide) == 0x4580, "filter");
static_assert(offsetof(BbsWriteScene, screen) == 0x4650 && offsetof(BbsWriteScene, line_chars) == 0x4e50, "screen");
static_assert(offsetof(BbsWriteScene, line_start) == 0x6c50, "line starts");
static_assert(sizeof(BbsWriteScene) == 0x6c6c, "size (func_ov112_022a1e68)");

/* The buttons and the touch (main's). */
extern PadState data_021fbe40;
extern u8 data_021f6c58; /* the touch's x, while the pen is down */
extern u8 data_021f6c54; /* and its y */

#define BBS_WRITE_PAD_UP 0x40
#define BBS_WRITE_PAD_DOWN 0x80

/* The scene's vtable. */
extern const u8 data_ov112_022a20d0[];

/* The session (main/session.h) and the heap the post's message is built in. */
extern NetSession *data_020ccf94;
extern Heap *data_021c9b28;

/* The message the post is sent to the other players with: handler 0x16, kind 4, a 0 and then
 * the post's characters. */
#define BBS_WRITE_POST_HANDLER 0x16
#define BBS_WRITE_POST_KIND 4
#define BBS_WRITE_POST_MESSAGE_SIZE (1 + (int) sizeof(((BbsWriteScene *) 0)->text))

/* The labels' destructor is handed to __cxa_vec_cleanup, so it is the game's symbol. */
extern int **func_02070be8(void *label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The characters before a 0, at most `max` (main's). */
extern int func_02051c8c_unk(u16 *text, int max);

/* The text's layer (LAYER_SUB_BG1) and the characters its lines are drawn into. */
#define BBS_WRITE_TEXT_LAYER 4
#define BBS_WRITE_LINE_FIRST_CHAR 17
#define BBS_WRITE_LINE_LAST_CHAR 0x100

/* The marked characters' colours (TextLabel_SetBoxParams). */
#define BBS_WRITE_MARK_A 13
#define BBS_WRITE_MARK_B 14

static MenuScene *bbs_write_scene(BbsWriteScene *self)
{
    return &self->base;
}

static BbsLabel *bbs_write_filter_text(BbsWriteScene *self)
{
    return &self->filter_text;
}

static int bbs_write_keyboard_arg(BbsWriteScene *self)
{
    return (int) (uintptr_t) self->keyboard;
}

/* The pointer's update through its class (vtable slot 3). */
static void bbs_write_update_pointer(BbsWriteScene *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->pointer.vtable;
    vtable[3](&self->pointer);
}

static int bbs_write_clamp(int value, int max)
{
    if (value < 0) {
        value = 0;
    }
    if (value > max) {
        value = max;
    }
    return value;
}

/* --- The destructors --- */

/* The members' destructors, last member first, then the base's. */
static void bbs_write_destroy_members(BbsWriteScene *self)
{
    self->base.vtable = data_ov112_022a20d0;
    BbsWideText_Destruct(&self->filter_wide);
    BbsLabel_Destruct(bbs_write_filter_text(self));
    Glider0_Destroy(&self->pointer);
    ButtonPanel_Destroy(&self->panel);
    PushButton_Destroy(&self->scroll_button);
    __cxa_vec_cleanup(self->lines, BBS_WRITE_LINES, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    __cxa_vec_cleanup(self->unk_26d4, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    ErrorMessage_Destruct(&self->error);
    MenuScene_DestroyBase(bbs_write_scene(self));
}

/* func_ov112_0229eea0 (vtable slot 0x40): the destructor. */
BbsWriteScene *BbsWrite_Destroy(BbsWriteScene *self)
{
    bbs_write_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov112_0229eea0, BbsWrite_Destroy)

/* func_ov112_0229ef2c (vtable slot 0x44): the deleting destructor. */
BbsWriteScene *BbsWrite_Delete(BbsWriteScene *self)
{
    bbs_write_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov112_0229ef2c, BbsWrite_Delete)

/* --- The post sent to the other players --- */

/* func_ov112_0229efbc: 0 while a session is linked and has not reached the frame the post was
 * sent in, else 1. QUIRK: `post_sequence` is not set when no session was linked as the post was
 * made; it is then not read. */
int BbsWrite_PostDelivered(BbsWriteScene *self)
{
    if (Session_IsLinked(data_020ccf94) != 0 && Session_HasReachedSequence(self->post_sequence) == 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov112_0229efbc, BbsWrite_PostDelivered)

/* func_ov112_0229efe8: while a session is linked, the post sent to the other players as a
 * message built in a block from the back of the scenes' heap (a 0, then the post's 0xc0 bytes),
 * the session's frame of it kept. REQUIRES: the heap has the 0xc1 bytes (the original writes
 * at address 0 otherwise). */
void BbsWrite_SendPost(BbsWriteScene *self)
{
    if (Session_IsLinked(data_020ccf94) == 0) {
        return;
    }
    Heap *heap = data_021c9b28;
    u8 *message = Heap_AllocBack(heap, BBS_WRITE_POST_MESSAGE_SIZE);
    message[0] = 0;
    MI_CpuCopy8(self->text, message + 1, sizeof(self->text));
    NetSession *session = data_020ccf94;
    Session_BeginMessage(session);
    Session_AppendMessage(session, message, BBS_WRITE_POST_MESSAGE_SIZE);
    Session_EndMessage(session, BBS_WRITE_POST_HANDLER, BBS_WRITE_POST_KIND);
    self->post_sequence = Session_GetFrameSequence(session);
    Heap_Free(heap, message);
}
CLEAN_AS(func_ov112_0229efe8, BbsWrite_SendPost)

/* --- The dimmed screen and the date --- */

/* func_ov112_0229f058: the sub screen no longer dimmed outside window 1 (BbsWrite_BeginDim). */
void BbsWrite_EndDim(BbsWriteScene *self)
{
    DisplayShadow_EndSubObjWindowBrightness();
    ButtonPanel_ClearFlag2(&self->panel);
    DisplayShadow_DisableSubWindows(2);
}
CLEAN_AS(func_ov112_0229f058, BbsWrite_EndDim)

/* func_ov112_0229f078: the sub screen dimmed (brightness -6) outside window 1 (0x2c, 0x20) to
 * (0xd4, 0x80), which shows all its planes; the panel told. */
void BbsWrite_BeginDim(BbsWriteScene *self)
{
    DisplayShadow_BeginSubObjWindowBrightness();
    DisplayShadow_SetSubBrightness((u8) ~5);
    ButtonPanel_SetFlag2(&self->panel);
    DisplayShadow_SetSubWindow1Planes(0x1f, 0);
    DisplayShadow_EnableSubWindows(2);
    DisplayShadow_SetSubWindow1(0x2c, 0x20, 0xd4, 0x80);
}
CLEAN_AS(func_ov112_0229f078, BbsWrite_BeginDim)

/* func_ov112_0229f0b4: line label `line` given a box in style 4 (colours 15 and 10) that draws
 * from character `first_char` of the text's layer, and shown. REQUIRES: line below 6 (the
 * game passes 0-2). */
void BbsWrite_OpenDateLabel(BbsWriteScene *self, int line, int first_char, int p3, int p4)
{
    TextLabel *label = &self->lines[line];
    TextLabel_OpenStyledBox(label, 4, first_char, p3, 15, 10, p4);
    TextLabel_Show(label, 0, 0);
}
CLEAN_AS(func_ov112_0229f0b4, BbsWrite_OpenDateLabel)

/* func_ov112_0229f0ec: line label 2 emptied and drawn from character 0x11a. */
void BbsWrite_ClearDateLabel(BbsWriteScene *self)
{
    TextBase_Clear(&self->lines[2]);
    BbsWrite_OpenDateLabel(self, 2, 0x11a, 5, 0);
}
CLEAN_AS(func_ov112_0229f0ec, BbsWrite_ClearDateLabel)

/* A digit as the game's wide characters have them (0xff10 for 0). */
static u16 bbs_write_digit(int value)
{
    return (u16) (value + 0xff10);
}

/* func_ov112_0229f11c: today's date drawn in two of the line labels (borrowed before the text's
 * lines fill them): the year as "20" and two digits from character 0x111, the month's and the
 * day's two digits each from character 0x116. */
void BbsWrite_ShowDate(BbsWriteScene *self)
{
    Date today;
    u16 digits[5];

    Calendar_Today(&today);
    digits[0] = bbs_write_digit(2);
    digits[1] = bbs_write_digit(0);
    digits[2] = bbs_write_digit(today.year / 10);
    digits[3] = bbs_write_digit(today.year % 10);
    digits[4] = 0;
    TextLabel_SetFromWide(&self->lines[0], digits, (void *) (uintptr_t) 5);
    BbsWrite_OpenDateLabel(self, 0, 0x111, 4, 1);

    digits[0] = bbs_write_digit(today.month / 10);
    digits[1] = bbs_write_digit(today.month % 10);
    digits[2] = bbs_write_digit(today.day / 10);
    digits[3] = bbs_write_digit(today.day % 10);
    TextLabel_SetFromWide(&self->lines[1], digits, (void *) (uintptr_t) 5);
    BbsWrite_OpenDateLabel(self, 1, 0x116, 4, 1);
}
CLEAN_AS(func_ov112_0229f11c, BbsWrite_ShowDate)

/* func_ov112_0229f1f4: the post carried into 8-bit characters for the taboo filter and, when
 * the filter changed it, back into the post. */
void BbsWrite_FilterTaboo(BbsWriteScene *self)
{
    TextBase_SetWide(&self->filter_wide, self->text, BBS_POST_LENGTH);
    TextBase_WideToBytes((TextBase *) (void *) &self->filter_text, (WideTextBase *) (void *) &self->filter_wide, 0, 0);
    if (MessageReader_FilterTaboo(&self->filter_text) != 0) {
        TextBase_BytesToWide((WideTextBase *) (void *) &self->filter_wide, (TextBase *) (void *) &self->filter_text);
        TextString_CopyWideOut((TextObject *) (void *) &self->filter_wide, self->text, BBS_POST_LENGTH);
    }
}
CLEAN_AS(func_ov112_0229f1f4, BbsWrite_FilterTaboo)

/* --- The pointer --- */

/* func_ov112_0229f250 */
void BbsWrite_PointerFirstOfSet(BbsWriteScene *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    bbs_write_update_pointer(self);
}
CLEAN_AS(func_ov112_0229f250, BbsWrite_PointerFirstOfSet)

/* func_ov112_0229f270: the keyboard's pressed keys released, the pointer at the third of its
 * set, then back to the keyboard once it has played. */
void BbsWrite_BeginKeyReleased(BbsWriteScene *self)
{
    func_ov095_0229cce0(self->keyboard);
    Glider_ShowThirdOfSet(&self->pointer);
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEY_RELEASED);
}
CLEAN_AS(func_ov112_0229f270, BbsWrite_BeginKeyReleased)

/* func_ov112_0229f29c: the pointer at the second of its set (its press), the key acted on once
 * it has played. */
void BbsWrite_BeginKeyPressed(BbsWriteScene *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_KEY_PRESSED);
}
CLEAN_AS(func_ov112_0229f29c, BbsWrite_BeginKeyPressed)

/* func_ov112_0229f2bc: the pointer put at the text cursor (on the screen, so less the scroll
 * target) or at the keyboard's key. */
void BbsWrite_PlacePointer(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT) != 0) {
        Glider_PlaceAt(&self->pointer, self->cursor_x, self->cursor_y - self->scroll_target);
    } else {
        int x = func_ov095_02299b7c(self->keyboard);
        int y = func_ov095_02299b38(self->keyboard);
        Glider_PlaceAt(&self->pointer, x, y);
    }
    bbs_write_update_pointer(self);
}
CLEAN_AS(func_ov112_0229f2bc, BbsWrite_PlacePointer)

/* func_ov112_0229f328: the pointer eased to (x, y); then back to this sub state. */
void BbsWrite_GlidePointerTo(BbsWriteScene *self, int x, int y)
{
    Glider_EaseToByDistance(&self->pointer, x, y, 3, 2);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov112_0229f328, BbsWrite_GlidePointerTo)

/* func_ov112_0229f35c: the pointer eased to the text cursor (then the text by the buttons) or to
 * the keyboard's key (then the keyboard by the buttons). */
void BbsWrite_GlidePointer(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT) != 0) {
        Glider_EaseToByDistance(&self->pointer, self->cursor_x, self->cursor_y - self->scroll_target, 3, 2);
        self->return_sub_state = BBS_WRITE_SUB_TEXT_KEYS;
    } else {
        int x = func_ov095_02299b7c(self->keyboard);
        int y = func_ov095_02299b38(self->keyboard);
        Glider_EaseToByDistance(&self->pointer, x, y, 3, 2);
        self->return_sub_state = BBS_WRITE_SUB_KEYS;
    }
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov112_0229f35c, BbsWrite_GlidePointer)

/* func_ov112_0229f3e0 */
void BbsWrite_HidePointer(BbsWriteScene *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    bbs_write_update_pointer(self);
}
CLEAN_AS(func_ov112_0229f3e0, BbsWrite_HidePointer)

/* func_ov112_0229f404: the pointer put back on the keyboard's key. */
void BbsWrite_PointAtKey(BbsWriteScene *self)
{
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_POINTER_ON_TEXT);
    func_ov095_02299aec(self->keyboard);
    int x = func_ov095_02299b7c(self->keyboard);
    int y = func_ov095_02299b38(self->keyboard);
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    BbsWrite_PointerFirstOfSet(self);
}
CLEAN_AS(func_ov112_0229f404, BbsWrite_PointAtKey)

/* func_ov112_0229f45c: the panel's `button` pressed; the scene's `state` follows once its press
 * has played (BBS_WRITE_SUB_BUTTON). */
void BbsWrite_PressPanelButton(BbsWriteScene *self, unsigned char state, int button)
{
    MenuScene_SetState(bbs_write_scene(self), state);
    ButtonPanel_Select(&self->panel, button);
    MenuScene_SetSubState(bbs_write_scene(self), BBS_WRITE_SUB_BUTTON);
}
CLEAN_AS(func_ov112_0229f45c, BbsWrite_PressPanelButton)

/* --- The keyboard's keys and the text cursor --- */

/* func_ov112_0229f488: the keyboard's keys enabled as the cursor allows: the newline when one
 * fits at the cursor, copy with a mark, paste with copied text, and key 6 with a mark or a
 * character before the cursor past the signature (keys 3-5 off without one). */
void BbsWrite_UpdateKeys(BbsWriteScene *self)
{
    void *keyboard = self->keyboard;

    if (func_ov095_0229bc00(keyboard, self->text, BBS_WRITE_CODE_NEWLINE, &self->position, BBS_POST_LENGTH,
                            BBS_WRITE_LINE_CHARS, BBS_WRITE_LINES, BBS_WRITE_LINE_WIDTH, 1, 1) != 0) {
        func_ov095_0229ce84(keyboard, BBS_WRITE_KEY_NEWLINE);
    } else {
        func_ov095_0229cef4(keyboard, BBS_WRITE_KEY_NEWLINE);
    }
    if (BbsWrite_HasMark(self) != 0) {
        func_ov095_0229ce84(keyboard, BBS_WRITE_KEY_COPY);
    } else {
        func_ov095_0229cef4(keyboard, BBS_WRITE_KEY_COPY);
    }
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_COPIED) != 0) {
        func_ov095_0229ce84(keyboard, BBS_WRITE_KEY_PASTE);
    } else {
        func_ov095_0229cef4(keyboard, BBS_WRITE_KEY_PASTE);
    }
    if (BbsWrite_HasMark(self) != 0) {
        func_ov095_0229bee4(keyboard);
        func_ov095_0229ce84(keyboard, BBS_WRITE_KEY_6);
    } else if (self->position <= self->first_position) {
        func_ov095_0229bee4(keyboard);
    } else {
        func_ov095_0229bed8(keyboard, BbsWrite_CharBeforeCursor(self));
    }
}
CLEAN_AS(func_ov112_0229f488, BbsWrite_UpdateKeys)

/* func_ov112_0229f56c: the cursor moved by the d-pad's repeated keys: up and down to the line
 * above or below (at the cursor's x), left back to `first_position`, right up to the text's end.
 * Gives 1 when it moved. QUIRK: up stops at line 1, so the signature's line cannot be entered. */
int BbsWrite_MoveCursorByKeys(BbsWriteScene *self, int keys)
{
    if (keys == 0) {
        return 0;
    }
    u8 position = self->position;
    int line = BbsWrite_LineOf(self, position);
    int old_line = line;

    if (KeyRepeat_HasUp(keys) != 0) {
        if (line > 1) {
            line--;
        }
    } else if (KeyRepeat_HasDown(keys) != 0) {
        line++;
        if (line > self->last_line || line >= BBS_WRITE_LINES) {
            line--;
        }
    }
    s32 x = self->cursor_x;
    if (line != old_line) {
        position = BbsWrite_PositionAt(self, line, &x);
    }
    if (KeyRepeat_HasLeft(keys) != 0) {
        if (position > self->first_position) {
            position--;
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        int length = func_02051c8c_unk(self->text, BBS_POST_LENGTH);
        if (position + 1 <= length) {
            position++;
        }
    }
    if (position == self->position) {
        return 0;
    }
    BbsWrite_SetPosition(self, (char) position);
    return 1;
}
CLEAN_AS(func_ov112_0229f56c, BbsWrite_MoveCursorByKeys)

/* func_ov112_0229f630: the line that holds character `position`: the first whose next line
 * starts past it, else the last line (at most 5). REQUIRES: `last_line` at most 6 (the line
 * breaking gives at most 5). */
int BbsWrite_LineOf(BbsWriteScene *self, int position)
{
    int last = self->last_line;
    for (int line = 0; line < last; line++) {
        if (position < self->line_start[line + 1]) {
            return line;
        }
    }
    return last < BBS_WRITE_LINES ? last : BBS_WRITE_LINES - 1;
}
CLEAN_AS(func_ov112_0229f630, BbsWrite_LineOf)

/* func_ov112_0229f668: the cursor's place worked out from its character: its line's y, and the
 * x past the line's characters before it; then the scroll kept on it. QUIRK: the x is kept to a
 * byte. */
void BbsWrite_PlaceCursor(BbsWriteScene *self)
{
    int line = BbsWrite_LineOf(self, self->position);
    self->cursor_y = line * 16 + 0x28;
    int start = self->line_start[line];
    int width = TextString_Width(&self->text[start], self->position - start);
    self->cursor_x = (u8) (width + 0x30);
    BbsWrite_ScrollToCursor(self);
}
CLEAN_AS(func_ov112_0229f668, BbsWrite_PlaceCursor)

/* func_ov112_0229f6b8: the character before the cursor (0 at the text's start). */
unsigned short BbsWrite_CharBeforeCursor(BbsWriteScene *self)
{
    u8 position = self->position;
    if (position == 0) {
        return 0;
    }
    return self->text[position - 1];
}
CLEAN_AS(func_ov112_0229f6b8, BbsWrite_CharBeforeCursor)

/* func_ov112_0229f6d4: the cursor put at `position`, drawn at once (the blink restarts shown). */
void BbsWrite_SetPosition(BbsWriteScene *self, char position)
{
    self->position = (u8) position;
    self->blink = 0x10;
}
CLEAN_AS(func_ov112_0229f6d4, BbsWrite_SetPosition)

/* func_ov112_0229f6e4: the cursor shown at the text's first place past the signature (drawn at
 * 0x30, 0x38), no mark, the keyboard's keys reset and brought up to date, no composition. */
void BbsWrite_StartEditing(BbsWriteScene *self)
{
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_CURSOR_SHOWN);
    self->cursor_x = 0x30;
    self->cursor_y = 0x38;
    BbsWrite_SetPosition(self, (char) self->first_position);
    BbsWrite_EndMark(self);
    func_ov095_0229cd30(bbs_write_keyboard_arg(self));
    BbsWrite_UpdateKeys(self);
    func_ov095_0229b3ec(self->keyboard);
}
CLEAN_AS(func_ov112_0229f6e4, BbsWrite_StartEditing)

/* func_ov112_0229f730: the end of the mark follows the pen (its x from 0x30, its y on the
 * scrolled text). Gives 1 when the cursor moved. */
int BbsWrite_DragMark(BbsWriteScene *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;
    u8 old = self->position;

    if (x < 0x30) {
        x = 0x30;
    }
    y += self->scroll_target + 8;
    BbsWrite_TouchAt(self, x, y);
    self->mark_to = self->position;
    return self->position != old;
}
CLEAN_AS(func_ov112_0229f730, BbsWrite_DragMark)

/* func_ov112_0229f784 */
void BbsWrite_Nothing(BbsWriteScene *self)
{
    (void) self;
}
CLEAN_AS(func_ov112_0229f784, BbsWrite_Nothing)

/* func_ov112_0229f788: the pen put down on the text (y below 0x48, x 0x20-0xdf): the cursor
 * put there and a mark begun at it. Gives 1 then, else 0. */
int BbsWrite_StartTouch(BbsWriteScene *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    if (y >= 0x48) {
        return 0;
    }
    if (x < 0x20 || x >= 0xe0) {
        return 0;
    }
    y += self->scroll_target + 8;
    if (x < 0x30) {
        x = 0x30;
    }
    BbsWrite_TouchAt(self, x, y);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_MARKING);
    self->mark_from = self->position;
    self->mark_to = self->position;
    return 1;
}
CLEAN_AS(func_ov112_0229f788, BbsWrite_StartTouch)

/* func_ov112_0229f7f0: the cursor put at (x, y) of the text: y kept to 0x38-0x87 (lines 1-5),
 * the line at most the last one, the character under x. The scroll kept on it. */
void BbsWrite_TouchAt(BbsWriteScene *self, int x, int y)
{
    if (y < 0x38) {
        y = 0x38;
    }
    if (y >= 0x88) {
        y = 0x87;
    }
    self->cursor_x = x;
    self->cursor_y = y;
    int line = (self->cursor_y - 0x28) >> 4;
    if (line > self->last_line) {
        line = self->last_line;
    }
    self->cursor_y = line * 16 + 0x28;
    BbsWrite_SetPosition(self, (char) BbsWrite_PositionAt(self, line, &self->cursor_x));
    BbsWrite_ScrollToCursor(self);
}
CLEAN_AS(func_ov112_0229f7f0, BbsWrite_TouchAt)

/* func_ov112_0229f84c: the character of `line` under *x, and *x set to where the cursor is drawn
 * before it. REQUIRES: line at most 6. */
unsigned char BbsWrite_PositionAt(BbsWriteScene *self, int line, s32 *x)
{
    int start = self->line_start[line];
    unsigned char index;

    *x = func_ov095_0229bb34(bbs_write_keyboard_arg(self), &self->text[start], BBS_POST_LENGTH - start, BBS_WRITE_LINE_WIDTH,
                             (unsigned char) (*x - 0x30), &index) +
         0x30;
    return (unsigned char) (index + start);
}
CLEAN_AS(func_ov112_0229f84c, BbsWrite_PositionAt)

/* func_ov112_0229f89c: the marked characters deleted; the cursor where they began, no mark. */
void BbsWrite_DeleteMarked(BbsWriteScene *self)
{
    u8 to = self->mark_to;
    u8 from = self->mark_from;
    u8 low, high;

    if (from > to) {
        low = to;
        high = from;
    } else {
        low = from;
        high = to;
    }
    u8 position = (u8) func_ov095_0229bbc0(bbs_write_keyboard_arg(self), self->text, low, high, BBS_POST_LENGTH);
    BbsWrite_SetPosition(self, (char) position);
    BbsWrite_EndMark(self);
}
CLEAN_AS(func_ov112_0229f89c, BbsWrite_DeleteMarked)

/* func_ov112_0229f8e4 */
void BbsWrite_EndMark(BbsWriteScene *self)
{
    self->mark_from = 0;
    self->mark_to = 0;
    BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_MARKING);
}
CLEAN_AS(func_ov112_0229f8e4, BbsWrite_EndMark)

/* func_ov112_0229f900: a range of at least one character is marked. */
int BbsWrite_HasMark(BbsWriteScene *self)
{
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_MARKING) == 0 || self->mark_from == self->mark_to) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov112_0229f900, BbsWrite_HasMark)

/* --- The scroll and its knob --- */

/* func_ov112_0229f92c: the scroll moved 4 pixels while up or down is held (0-0x3c); the knob
 * cues when it moved. */
void BbsWrite_ScrollByKeys(BbsWriteScene *self)
{
    u8 scroll = self->scroll;
    int value = scroll;

    if (data_021fbe40.held & BBS_WRITE_PAD_UP) {
        value = scroll - 4;
    } else if (data_021fbe40.held & BBS_WRITE_PAD_DOWN) {
        value = scroll + 4;
    }
    value = bbs_write_clamp(value, BBS_WRITE_SCROLL_MAX);
    if (scroll != value) {
        PushButton_ScrollCue(&self->scroll_button);
    }
    BbsWrite_SetScroll(self, (unsigned char) value);
}
CLEAN_AS(func_ov112_0229f92c, BbsWrite_ScrollByKeys)

/* func_ov112_0229f984: the knob moved 2 pixels toward the pen on the scroll bar (its y less
 * 0x18, 0-0x28), the scroll after it. */
void BbsWrite_MoveKnobToTouch(BbsWriteScene *self)
{
    int target = bbs_write_clamp(data_021f6c54 - 0x18, 0x28);
    Approach_U8(&self->knob, (u8) target, 2);
    BbsWrite_SetKnob(self, self->knob);
}
CLEAN_AS(func_ov112_0229f984, BbsWrite_MoveKnobToTouch)

/* func_ov112_0229f9bc: the knob follows the pen dragging it since the drag began. */
void BbsWrite_DragKnob(BbsWriteScene *self)
{
    BbsWrite_SetKnob(self, self->drag_knob + (data_021f6c54 - self->drag_touch_y));
}
CLEAN_AS(func_ov112_0229f9bc, BbsWrite_DragKnob)

/* func_ov112_0229f9dc: the scroll put at once at one and a half times `knob` (0-0x3c); the knob
 * cues each 4 pixels of scroll. */
void BbsWrite_SetKnob(BbsWriteScene *self, int knob)
{
    int scroll = bbs_write_clamp((knob * 3) >> 1, BBS_WRITE_SCROLL_MAX);
    BbsWrite_SetScroll(self, (unsigned char) scroll);
    int since_cue = self->cue_scroll - scroll;
    if (since_cue >= 4 || since_cue <= -4) {
        PushButton_ScrollCue(&self->scroll_button);
        self->cue_scroll = (u8) scroll;
    }
}
CLEAN_AS(func_ov112_0229f9dc, BbsWrite_SetKnob)

/* func_ov112_0229fa2c: the pen is on the scroll bar (x 0xdd-0xed, y 0x18-0x40). */
int BbsWrite_TouchesBar(BbsWriteScene *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    (void) self;
    if (y - 8 < 0x10 || y - 8 > 0x38) {
        return 0;
    }
    if (x < 0xdd || x > 0xed) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov112_0229fa2c, BbsWrite_TouchesBar)

/* func_ov112_0229fa5c: a drag of the knob begun when the pen is on it. */
int BbsWrite_StartDrag(BbsWriteScene *self)
{
    if (PushButton_Contains(&self->scroll_button, data_021f6c58, data_021f6c54) != 0) {
        self->drag_touch_y = data_021f6c54;
        self->drag_knob = (u8) ((self->scroll * 2) / 3);
        self->cue_scroll = self->scroll;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov112_0229fa5c, BbsWrite_StartDrag)

/* func_ov112_0229fab4: the scroll target moved when the cursor stands less than 0x18 pixels
 * below the top of the view (to put it 0x18 below) or more than 0x40 (to put it 0x38 below).
 * QUIRK: the target is a byte, and is not bounded to 0-0x3c here. */
void BbsWrite_ScrollToCursor(BbsWriteScene *self)
{
    int below_top = self->cursor_y - self->scroll_target;

    if (below_top < 0x18) {
        BbsWrite_ScrollTo(self, (char) (self->cursor_y - 0x18));
    } else if (below_top > 0x40) {
        BbsWrite_ScrollTo(self, (char) (self->cursor_y - 0x38));
    }
}
CLEAN_AS(func_ov112_0229fab4, BbsWrite_ScrollToCursor)

/* func_ov112_0229fae8: the scroll moved 8 pixels toward its target (the scrolling ends once
 * there), the knob at two thirds of it. */
void BbsWrite_StepScroll(BbsWriteScene *self)
{
    if (self->scroll == self->scroll_target) {
        BbsWrite_ClearFlags(self, BBS_WRITE_FLAG_SCROLLING);
    } else if (self->scroll < self->scroll_target) {
        /* QUIRK: a byte: from 0xf8 on the step wraps past 0 and then stops at the target. */
        self->scroll = (u8) (self->scroll + 8);
        if (self->scroll > self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    } else if (self->scroll < 8) {
        self->scroll = self->scroll_target;
    } else {
        self->scroll = (u8) (self->scroll - 8);
        if (self->scroll < self->scroll_target) {
            self->scroll = self->scroll_target;
        }
    }
    self->knob = (u8) ((self->scroll * 2) / 3);
}
CLEAN_AS(func_ov112_0229fae8, BbsWrite_StepScroll)

/* func_ov112_0229fb70 */
int BbsWrite_IsScrolling(BbsWriteScene *self)
{
    return BbsWrite_TestFlags(self, BBS_WRITE_FLAG_SCROLLING);
}
CLEAN_AS(func_ov112_0229fb70, BbsWrite_IsScrolling)

/* func_ov112_0229fb7c: the scroll set to move to `target`. */
void BbsWrite_ScrollTo(BbsWriteScene *self, char target)
{
    self->scroll_target = (u8) target;
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_SCROLLING);
}
CLEAN_AS(func_ov112_0229fb7c, BbsWrite_ScrollTo)

/* func_ov112_0229fb8c: the scroll put at `scroll` at once, the knob after it. */
void BbsWrite_SetScroll(BbsWriteScene *self, unsigned char scroll)
{
    self->scroll = scroll;
    self->scroll_target = self->scroll;
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_SCROLLING);
    self->knob = (u8) ((self->scroll * 2) / 3);
}
CLEAN_AS(func_ov112_0229fb8c, BbsWrite_SetScroll)

/* --- The text's lines --- */

/* func_ov112_0229fbc0: the lines' characters queued for the text's layer (its characters
 * 17-0x100). */
void BbsWrite_QueueLineChars(BbsWriteScene *self)
{
    LayerTask_QueueChars(&self->chars_task, (int) (uintptr_t) self->line_chars, BBS_WRITE_TEXT_LAYER,
                         BBS_WRITE_LINE_FIRST_CHAR, BBS_WRITE_LINE_FIRST_CHAR, BBS_WRITE_LINE_LAST_CHAR);
}
CLEAN_AS(func_ov112_0229fbc0, BbsWrite_QueueLineChars)

/* func_ov112_0229fbf0 */
void BbsWrite_Idle(BbsWriteScene *self)
{
    (void) self;
}
CLEAN_AS(func_ov112_0229fbf0, BbsWrite_Idle)

/* func_ov112_0229fbf4: the line labels' boxes closed. */
void BbsWrite_CloseLineBoxes(BbsWriteScene *self)
{
    for (int line = 0; line < BBS_WRITE_LINES; line++) {
        TextLabel_CloseBox(&self->lines[line]);
    }
}
CLEAN_AS(func_ov112_0229fbf4, BbsWrite_CloseLineBoxes)

/* func_ov112_0229fc18 */
void BbsWrite_ShowLines(BbsWriteScene *self)
{
    for (int line = 0; line < BBS_WRITE_LINES; line++) {
        TextLabel_Show(&self->lines[line], 0, 0);
    }
}
CLEAN_AS(func_ov112_0229fc18, BbsWrite_ShowLines)

/* func_ov112_0229fc48: `count` characters from character `from` of the text marked in the line
 * labels that hold them (TextLabel_SetBoxParams with `a` and `b`), up to the first empty line.
 * QUIRK: once a line is marked, `from` goes on as a byte. */
void BbsWrite_MarkLines(BbsWriteScene *self, int a, int b, unsigned int from, unsigned int count)
{
    unsigned int start = 0;

    for (int line = 0; line < BBS_WRITE_LINES; line++) {
        int length = self->line_start[line + 1] - self->line_start[line];
        if (length == 0) {
            return;
        }
        if (from >= start) {
            unsigned int end = start + (unsigned int) length;
            if (from < end) {
                unsigned int take = end > from + count ? count : (unsigned int) length - (from - start);
                TextLabel_SetBoxParams(&self->lines[line], a, b, (int) (from - start), (int) take);
                from = (u8) end;
                count -= take;
                if (count == 0) {
                    return;
                }
            }
        }
        start += (unsigned int) length;
    }
}
CLEAN_AS(func_ov112_0229fc48, BbsWrite_MarkLines)

/* func_ov112_0229fcd4: the marked characters shown marked. */
void BbsWrite_ShowMark(BbsWriteScene *self)
{
    if (BbsWrite_HasMark(self) == 0) {
        return;
    }
    u8 to = self->mark_to;
    u8 from = self->mark_from;
    if (from > to) {
        BbsWrite_MarkLines(self, BBS_WRITE_MARK_A, BBS_WRITE_MARK_B, to, (unsigned int) (from - to));
    } else {
        BbsWrite_MarkLines(self, BBS_WRITE_MARK_A, BBS_WRITE_MARK_B, from, (unsigned int) (to - from));
    }
}
CLEAN_AS(func_ov112_0229fcd4, BbsWrite_ShowMark)

/* func_ov112_0229fd20: the text broken into its lines again and each line label set from its
 * line and drawn into its characters (colours 0xe and 0xd). Lines after the first show their
 * newline marks and the last line its end mark (an empty last line shows the end mark alone),
 * unless BBS_WRITE_FLAG_10 or the question is up. Then the mark shown, the lines to be shown
 * at the frame's end, the keyboard's keys brought up to date. */
void BbsWrite_Refresh(BbsWriteScene *self)
{
    u16 empty[1];
    int marks;

    LetterView_BreakLines(self->text, self->line_start, &self->last_line, BBS_POST_LENGTH, BBS_WRITE_LINE_CHARS,
                          BBS_WRITE_LINE_WIDTH, BBS_WRITE_LINES);
    if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_10) != 0) {
        marks = 0;
    } else if (BbsWrite_TestFlags(self, BBS_WRITE_FLAG_ASKING) != 0) {
        marks = 0;
    } else {
        marks = 1;
    }
    empty[0] = 0;
    for (int line = 0; line < BBS_WRITE_LINES; line++) {
        int start = self->line_start[line];
        int length = self->line_start[line + 1] - start;
        TextLabel *label = &self->lines[line];
        TextBase_Clear(label);
        if (length != 0) {
            TextLabel_SetFromWideConverted(label, &self->text[start], length, line == 0 ? 0 : marks,
                                           (u8) (line == self->last_line));
        } else if (marks != 0 && line == self->last_line) {
            TextLabel_SetFromWideConverted(label, empty, 1, marks, 1);
        }
    }
    for (int line = 0; line < BBS_WRITE_LINES; line++) {
        TextLabel_OpenBox(&self->lines[line], (int) (uintptr_t) self->line_chars[line], 0x14, 0xe, 0xd);
    }
    BbsWrite_ShowMark(self);
    BbsWrite_SetFlags(self, BBS_WRITE_FLAG_LINES_DIRTY);
    BbsWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov112_0229fd20, BbsWrite_Refresh)

/* --- The flags --- */

/* func_ov112_0229fe50 */
void BbsWrite_ClearFlags(BbsWriteScene *self, unsigned int mask)
{
    self->flags &= ~mask;
}
CLEAN_AS(func_ov112_0229fe50, BbsWrite_ClearFlags)

/* func_ov112_0229fe60 */
void BbsWrite_SetFlags(BbsWriteScene *self, unsigned int mask)
{
    self->flags |= mask;
}
CLEAN_AS(func_ov112_0229fe60, BbsWrite_SetFlags)

/* func_ov112_0229fe70 */
int BbsWrite_TestFlags(BbsWriteScene *self, int mask)
{
    return (self->flags & (u32) mask) != 0;
}
CLEAN_AS(func_ov112_0229fe70, BbsWrite_TestFlags)
