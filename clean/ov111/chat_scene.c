/* The chat scene of overlay 111 (chat_scene.h): its destructors, the line's text class, its
 * flags, the keyboard's keys, the pointer, the line's editing and drawing, the sub states, the
 * states, the vtable's slots and the constructor. */
#include "chat_scene.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/player_actor_ops.h"
#include "main/player_actors.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/message_reader.h"
#include "main/quick_message.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_draw.h"
#include "main/text_string.h"
#include "ov002/key_repeat.h"
#include "ov004/member_pointer.h"
#include "ov090/menu_tabs.h"
#include "ov095/soft_keyboard.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(ChatScene, return_sub_state) == 0x98, "bytes");
static_assert(offsetof(ChatScene, cursor) == 0x9e && offsetof(ChatScene, reaction_wait) == 0xa2, "bytes");
static_assert(offsetof(ChatScene, flags) == 0xa4 && offsetof(ChatScene, box) == 0xa8, "flags");
static_assert(sizeof(LayerTask) == 0x24 && sizeof(TextLabel) == 0x6c, "keyboard members");
static_assert(offsetof(ChatKeyboard, map) == 0x2428 && sizeof(ChatKeyboard) == 0x3c28, "keyboard");
static_assert(sizeof(ChatKeyboard) == sizeof(SoftKeyboard), "keyboard");
static_assert(offsetof(ChatScene, keyboard) == 0xac && offsetof(ChatScene, message) == 0x3cd4, "keyboard");
static_assert(sizeof(ChatLine) == 0x30 && offsetof(ChatLine, chars) == 0x0e, "line");
static_assert(offsetof(ChatScene, line) == 0x3d08 && offsetof(ChatScene, pointer) == 0x3d38, "line");
static_assert(sizeof(Glider) == 0x64 && offsetof(ChatScene, error) == 0x3d9c, "error");
static_assert(sizeof(ErrorMessage) == 0x11c && offsetof(ChatScene, clipboard) == 0x3eb8, "clipboard");
static_assert(sizeof(ChatScene) == 0x3ed8, "size (func_ov111_022a0e08)");

/* The scene's vtable and the line's. */
extern const u8 data_ov111_022a1008[];
extern const TextVtable data_ov111_022a0ff0;

/* The send's four looks of the screen's rows 4-8 ("menu/chat2/b_cht.bsc", "b_cht_0.bsc",
 * "b_cht_1.bsc", "b_cht_2.bsc"), the screen's palette and its characters. */
extern const char *const data_ov111_022a0f78[4];
extern const char data_ov111_022a0f88[]; /* "menu/chat2/b_cht.bsc" */
extern const char data_ov111_022a1068[]; /* "menu/chat2/b_cht_bg.bpl" */
extern const char data_ov111_022a1080[]; /* "menu/chat2/b_cht.bch" */

/* The tables of member functions (ov004/member_pointer.h): their guards, the tables and the
 * constants they are filled from. */
extern u32 data_ov111_022a10a0; /* the sub states' guard */
extern u32 data_ov111_022a10a4; /* the states' guard */
extern MemberPointer data_ov111_022a10a8[CHAT_SCENE_STATES];
extern MemberPointer data_ov111_022a10d8[CHAT_SCENE_SUB_STATES];
extern const MemberPointer data_ov111_022a0ec0; /* ChatScene_WipeOut */
extern const MemberPointer data_ov111_022a0ec8; /* ChatScene_UpdateError */
extern const MemberPointer data_ov111_022a0ed0; /* ChatScene_StartWipeOut */
extern const MemberPointer data_ov111_022a0ed8; /* ChatScene_WipeIn */
extern const MemberPointer data_ov111_022a0ee8; /* ChatScene_RepeatBackspace */
extern const MemberPointer data_ov111_022a0ef0; /* ChatScene_PressKey */
extern const MemberPointer data_ov111_022a0ef8; /* ChatScene_SendAnimOut */
extern const MemberPointer data_ov111_022a0f00; /* ChatScene_SendAnimIn */
extern const MemberPointer data_ov111_022a0f08; /* ChatScene_WaitLRelease */
extern const MemberPointer data_ov111_022a0f10; /* ChatScene_MarkByKeys */
extern const MemberPointer data_ov111_022a0f18; /* ChatScene_LoadScreen */
extern const MemberPointer data_ov111_022a0f20; /* ChatScene_TextByKeys */
extern const MemberPointer data_ov111_022a0f28; /* ChatScene_WaitKeyRelease */
extern const MemberPointer data_ov111_022a0f30; /* ChatScene_RepeatKey */
extern const MemberPointer data_ov111_022a0f38; /* ChatScene_LoadKeyboard */
extern const MemberPointer data_ov111_022a0f40; /* ChatScene_WaitPointerGlide */
extern const MemberPointer data_ov111_022a0f48; /* ChatScene_KeyboardByKeys */
extern const MemberPointer data_ov111_022a0f50; /* ChatScene_MarkByDrag */
extern const MemberPointer data_ov111_022a0f58; /* ChatScene_RepeatTouchedKey */
extern const MemberPointer data_ov111_022a0f60; /* ChatScene_IdleByTouch */
extern const MemberPointer data_ov111_022a0f68; /* ChatScene_StartWipeIn */
extern const MemberPointer data_ov111_022a0f70; /* ChatScene_WaitRRelease */

/* The members' constructors and destructors handed to __cxa_vec_ctor / __cxa_vec_cleanup are
 * the game's symbols. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);

/* The pen: down, gone down this frame, and its place (autoload_2/input.c). */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58; /* x */
extern u8 data_021f6c54; /* y */

/* The pad (autoload_2/input.h). */
extern PadState data_021fbe40;
#define CHAT_SCENE_PAD_A 0x0001
#define CHAT_SCENE_PAD_B 0x0002
#define CHAT_SCENE_PAD_SELECT 0x0004
#define CHAT_SCENE_PAD_START 0x0008
#define CHAT_SCENE_PAD_R 0x0100
#define CHAT_SCENE_PAD_L 0x0200
#define CHAT_SCENE_PAD_X 0x0400
#define CHAT_SCENE_PAD_Y 0x0800

/* The heap the screen's files are read with. */
extern Heap *data_021fbe94;

/* The multiplayer session (main/session.h). */
extern NetSession *data_020ccf94;

/* The characters before a 0, at most `max` (main's). */
extern int func_02051c8c_unk(u16 *text, int max);

/* The SDK's copy. */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The keyboard's keys and modes the scene names. */
#define CHAT_SCENE_KEY_NEWLINE 0
#define CHAT_SCENE_KEY_CONVERT 6
#define CHAT_SCENE_KEY_COPY 0x0b
#define CHAT_SCENE_KEY_PASTE 0x0c
#define CHAT_SCENE_KEY_COPY_FACE 0x109  /* shown pressed by L */
#define CHAT_SCENE_KEY_PASTE_FACE 0x10a /* shown pressed by R */
#define CHAT_SCENE_KEY_MODE 9           /* the mode the keys' codes are read in */
#define CHAT_SCENE_KEYBOARD_STATE_MODE_TAB 9

/* The menu's tabs (ov090/menu_tabs.h). */
#define CHAT_SCENE_TAB_NONE (-1)
#define CHAT_SCENE_TAB_OWN MENU_TAB_4

/* The sounds the scene plays. */
#define CHAT_SCENE_SE_CURSOR 0x0b
#define CHAT_SCENE_SE_MARK 0x15
#define CHAT_SCENE_SE_SEND 0x32
#define CHAT_SCENE_SE_BUZZ 0x34
#define CHAT_SCENE_SE_DELETE 0x35

/* The keyboard is drawn at (0x80, the wipe's y + 0x60), its text cursor 0x38 above. */
#define CHAT_SCENE_KEYBOARD_X 0x80
#define CHAT_SCENE_KEYBOARD_Y 0x60
#define CHAT_SCENE_POINTER_TEXT_Y 0x28
#define CHAT_SCENE_BLINK_START 0x10
#define CHAT_SCENE_REACTION_WAIT 20
#define CHAT_SCENE_SEND_FRAMES 4
#define CHAT_SCENE_WIPE_MARGIN 0x30

static MenuScene *chat_scene(ChatScene *self)
{
    return &self->base;
}

static SoftKeyboard *chat_keyboard(ChatScene *self)
{
    return (SoftKeyboard *) (void *) &self->keyboard;
}

static u16 *chat_line(ChatScene *self)
{
    return self->line.chars;
}

/* The line from character `index` on. QUIRK: the cursor and the marked range are not bounded
 * by the line's 16 characters; past them this points beyond the line, as the game's address
 * does. */
static u16 *chat_line_at(ChatScene *self, unsigned int index)
{
    return (u16 *) (uintptr_t) ((uintptr_t) self->line.chars + 2u * index);
}

static TextBase *chat_message(ChatScene *self)
{
    return (TextBase *) (void *) self->message;
}

static Process *chat_parent(ChatScene *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* A member's virtual function at `slot` (a word of its vtable), taking the member. */
static u32 chat_virtual(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    return vtable[slot];
}

/* The pointer's update through its class (vtable slot 3). */
static void chat_update_pointer(ChatScene *self)
{
    ((void (*)(Glider *))(uintptr_t) chat_virtual(&self->pointer, 3))(&self->pointer);
}

/* The pen went down this frame. */
static int chat_pen_pressed(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* The marked range: its lower end and its length. */
static void chat_mark_range(ChatScene *self, int *low, int *length)
{
    u8 to = self->mark_to;
    u8 from = self->mark_from;
    if (from > to) {
        *low = to;
        *length = from - to;
    } else {
        *low = from;
        *length = to - from;
    }
}

/* --- The destructors and the line's text class --- */

/* The members' destructors, last member first, then the base's. The keyboard has none. */
static void chat_destroy_members(ChatScene *self)
{
    self->base.vtable = data_ov111_022a1008;
    ErrorMessage_Destruct(&self->error);
    Glider0_Destroy(&self->pointer);
    self->line.vtable = &data_ov111_022a0ff0;
    TextBase_WideDestruct(&self->line);
    QuickMessage_TextDestruct((struct QuickMessageText *) (void *) self->message);
    __cxa_vec_cleanup(self->keyboard.labels, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    MenuScene_DestroyBase(chat_scene(self));
}

/* func_ov111_0229eea0 (vtable slot 0x40): the destructor. */
ChatScene *ChatScene_Destroy(ChatScene *self)
{
    chat_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov111_0229eea0, ChatScene_Destroy)

/* func_ov111_0229ef08 (vtable slot 0x44): the deleting destructor. */
ChatScene *ChatScene_Delete(ChatScene *self)
{
    chat_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov111_0229ef08, ChatScene_Delete)

/* func_ov111_0229ef78 (the line's slot 0x00): the wide text base's destructor. */
ChatLine *ChatLine_Destruct(ChatLine *line)
{
    line->vtable = &data_ov111_022a0ff0;
    TextBase_WideDestruct(line);
    return line;
}
CLEAN_AS(func_ov111_0229ef78, ChatLine_Destruct)

/* func_ov111_0229ef90 (the line's slot 0x04): its destructor, then the line freed. */
ChatLine *ChatLine_Delete(ChatLine *line)
{
    line->vtable = &data_ov111_022a0ff0;
    TextBase_WideDestruct(line);
    Heap_OperatorDeleteB(line);
    return line;
}
CLEAN_AS(func_ov111_0229ef90, ChatLine_Delete)

/* func_ov111_0229efb0 (the line's slot 0x0c): its characters, 0x0e past the line. */
int ChatLine_Chars(int line)
{
    return (int) ((u32) line + (u32) offsetof(ChatLine, chars));
}
CLEAN_AS(func_ov111_0229efb0, ChatLine_Chars)

/* func_ov111_0229efb4 (the line's slot 0x08): its room, 16 characters. */
int ChatLine_Capacity(void)
{
    return CHAT_SCENE_LINE_CHARS;
}
CLEAN_AS(func_ov111_0229efb4, ChatLine_Capacity)

/* --- The flags --- */

/* func_ov111_0229efb8 */
void ChatScene_ClearFlags(ChatScene *self, unsigned short mask)
{
    self->flags &= (u16) ~mask;
}
CLEAN_AS(func_ov111_0229efb8, ChatScene_ClearFlags)

/* func_ov111_0229efc8 */
void ChatScene_SetFlags(ChatScene *self, unsigned short mask)
{
    self->flags |= mask;
}
CLEAN_AS(func_ov111_0229efc8, ChatScene_SetFlags)

/* func_ov111_0229efd8 */
int ChatScene_TestFlags(ChatScene *self, unsigned int mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov111_0229efd8, ChatScene_TestFlags)

/* --- The keyboard's keys and the pointer --- */

/* func_ov111_0229efec: the keys that depend on the line: the newline key always disabled; the
 * copy key while a range is marked; the paste key while text was copied; the conversion keys
 * disabled while a range is marked (key 6 then enabled again) or at the line's start, else
 * key 6 enabled for the character before the cursor. */
void ChatScene_UpdateKeys(ChatScene *self)
{
    SoftKeyboard *keyboard = chat_keyboard(self);

    SoftKeyboard_DisableSpecial(keyboard, CHAT_SCENE_KEY_NEWLINE);
    if (ChatScene_IsMarking(self)) {
        SoftKeyboard_EnableSpecial(keyboard, CHAT_SCENE_KEY_COPY);
    } else {
        SoftKeyboard_DisableSpecial(keyboard, CHAT_SCENE_KEY_COPY);
    }
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_COPIED)) {
        SoftKeyboard_EnableSpecial(keyboard, CHAT_SCENE_KEY_PASTE);
    } else {
        SoftKeyboard_DisableSpecial(keyboard, CHAT_SCENE_KEY_PASTE);
    }
    if (ChatScene_IsMarking(self)) {
        SoftKeyboard_DisableEditKeys(keyboard);
        SoftKeyboard_EnableSpecial(keyboard, CHAT_SCENE_KEY_CONVERT);
    } else if (self->cursor == 0) {
        SoftKeyboard_DisableEditKeys(keyboard);
    } else {
        SoftKeyboard_EnableBackspace(keyboard, ChatScene_CharBeforeCursor(self));
    }
}
CLEAN_AS(func_ov111_0229efec, ChatScene_UpdateKeys)

/* func_ov111_0229f084: the keyboard drawn on the sub screen's BG3. */
void ChatScene_DrawKeyboardLayer(ChatScene *self)
{
    SoftKeyboard_QueueScreen(chat_keyboard(self), LAYER_SUB_BG3);
}
CLEAN_AS(func_ov111_0229f084, ChatScene_DrawKeyboardLayer)

/* func_ov111_0229f090: the keyboard set up in `state` on the sub screen's BG3. */
void ChatScene_SetKeyboardState(ChatScene *self, int state)
{
    SoftKeyboard_LoadLayout(chat_keyboard(self), state, LAYER_SUB_BG3, 1);
}
CLEAN_AS(func_ov111_0229f090, ChatScene_SetKeyboardState)

/* func_ov111_0229f0a4: the pointer shows its first set, is updated, and the keyboard is used by
 * the buttons (sub state 3). */
void ChatScene_PointerFirstOfSet(ChatScene *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    chat_update_pointer(self);
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEYS);
}
CLEAN_AS(func_ov111_0229f0a4, ChatScene_PointerFirstOfSet)

/* func_ov111_0229f0cc: the pointer shows its third set (a key let go; sub state 7). */
void ChatScene_PointerThirdOfSet(ChatScene *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEY_RELEASE);
}
CLEAN_AS(func_ov111_0229f0cc, ChatScene_PointerThirdOfSet)

/* func_ov111_0229f0ec: the pointer shows its second set (a key pressed by A; sub state 5). */
void ChatScene_PointerSecondOfSet(ChatScene *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEY_PRESS);
}
CLEAN_AS(func_ov111_0229f0ec, ChatScene_PointerSecondOfSet)

/* func_ov111_0229f10c: the pointer put at once at the text cursor (CHAT_SCENE_FLAG_POINTER_ON_TEXT)
 * or at the keyboard's key, and updated. */
void ChatScene_PlacePointer(ChatScene *self)
{
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT)) {
        Glider_PlaceAt(&self->pointer, self->cursor_x + CHAT_SCENE_LINE_X, CHAT_SCENE_POINTER_TEXT_Y);
    } else {
        int x = SoftKeyboard_CursorX(chat_keyboard(self));
        int y = SoftKeyboard_CursorY(chat_keyboard(self));
        Glider_PlaceAt(&self->pointer, x, y);
    }
    chat_update_pointer(self);
}
CLEAN_AS(func_ov111_0229f10c, ChatScene_PlacePointer)

/* func_ov111_0229f164: the pointer eases to the text cursor (in 3 steps, then sub state 9) or
 * to the keyboard's key (in 2, then sub state 3), in sub state 4 meanwhile. */
void ChatScene_GlidePointer(ChatScene *self)
{
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT)) {
        Glider_EaseTo(&self->pointer, self->cursor_x + CHAT_SCENE_LINE_X, CHAT_SCENE_POINTER_TEXT_Y, 3, 1);
        self->return_sub_state = CHAT_SCENE_SUB_TEXT_KEYS;
    } else {
        int x = SoftKeyboard_CursorX(chat_keyboard(self));
        int y = SoftKeyboard_CursorY(chat_keyboard(self));
        Glider_EaseTo(&self->pointer, x, y, 2, 1);
        self->return_sub_state = CHAT_SCENE_SUB_KEYS;
    }
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov111_0229f164, ChatScene_GlidePointer)

/* func_ov111_0229f1d8: the pointer's animation stopped (0), and updated. */
void ChatScene_HidePointer(ChatScene *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    chat_update_pointer(self);
}
CLEAN_AS(func_ov111_0229f1d8, ChatScene_HidePointer)

/* func_ov111_0229f1fc: the pointer leaves the text: the keyboard's key place set by its mode,
 * the pointer put there in its first set, the keyboard used by the buttons. */
void ChatScene_PointAtKey(ChatScene *self)
{
    ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT);
    SoftKeyboard_PlaceCursorHome(chat_keyboard(self));
    int x = SoftKeyboard_CursorX(chat_keyboard(self));
    int y = SoftKeyboard_CursorY(chat_keyboard(self));
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    ChatScene_PointerFirstOfSet(self);
}
CLEAN_AS(func_ov111_0229f1fc, ChatScene_PointAtKey)

/* --- The buttons --- */

/* func_ov111_0229f24c: START sends the line; when it went, the pointer stops and the send's
 * look comes in (sub state 13). 1 when it went. */
int ChatScene_SendOnStart(ChatScene *self)
{
    if ((data_021fbe40.pressed & CHAT_SCENE_PAD_START) == 0) {
        return 0;
    }
    if (ChatScene_Send(self) != 0) {
        ChatScene_HidePointer(self);
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_SEND_IN);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov111_0229f24c, ChatScene_SendOnStart)

/* func_ov111_0229f288: L copies the marked range, while the copy key is enabled; its face shown
 * pressed until L is let go (sub state 11). 1 when it did. */
int ChatScene_CopyOnL(ChatScene *self)
{
    if ((data_021fbe40.pressed & CHAT_SCENE_PAD_L) == 0) {
        return 0;
    }
    if (SoftKeyboard_IsSpecialDisabled(chat_keyboard(self), CHAT_SCENE_KEY_COPY) != 0) {
        return 0;
    }
    ChatScene_RunCode(self, CHAT_SCENE_CODE_COPY);
    SoftKeyboard_ShowKeyPressed(chat_keyboard(self), CHAT_SCENE_KEY_COPY_FACE);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_WHILE_L);
    return 1;
}
CLEAN_AS(func_ov111_0229f288, ChatScene_CopyOnL)

/* func_ov111_0229f2ec: R pastes the copied text, while the paste key is enabled; its face shown
 * pressed and the pointer put at the cursor until R is let go (sub state 12). 1 when it did. */
int ChatScene_PasteOnR(ChatScene *self)
{
    if ((data_021fbe40.pressed & CHAT_SCENE_PAD_R) == 0) {
        return 0;
    }
    if (SoftKeyboard_IsSpecialDisabled(chat_keyboard(self), CHAT_SCENE_KEY_PASTE) != 0) {
        return 0;
    }
    ChatScene_RunCode(self, CHAT_SCENE_CODE_PASTE);
    SoftKeyboard_ShowKeyPressed(chat_keyboard(self), CHAT_SCENE_KEY_PASTE_FACE);
    ChatScene_PlacePointer(self);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_WHILE_R);
    return 1;
}
CLEAN_AS(func_ov111_0229f2ec, ChatScene_PasteOnR)

/* func_ov111_0229f358: B deletes (without a buzz) and repeats while held (sub state 8); with
 * nothing to delete it closes the menu. 1 when B was pressed. */
int ChatScene_BackspaceOnB(ChatScene *self)
{
    if ((data_021fbe40.pressed & CHAT_SCENE_PAD_B) == 0) {
        return 0;
    }
    if (ChatScene_Backspace(self, 0) != 0) {
        SoftKeyboard_StartRepeat(chat_keyboard(self));
        self->return_sub_state = self->base.sub_state;
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_BACKSPACE);
    } else {
        ChatScene_SwitchTab(self, MENU_TAB_CLOSE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov111_0229f358, ChatScene_BackspaceOnB)

/* func_ov111_0229f3ac: A presses the key the keyboard's cursor is on: the send key sends the
 * line (the pointer in its second set, the send's look coming in: sub state 13); any other key
 * is shown pressed and run when the pointer's press has played (sub state 5). 1 when it did. */
int ChatScene_PressOnA(ChatScene *self)
{
    if ((data_021fbe40.pressed & CHAT_SCENE_PAD_A) == 0) {
        return 0;
    }
    int key = SoftKeyboard_PressCursorKey(chat_keyboard(self));
    if (key == -1) {
        return 0;
    }
    if (SoftKeyboard_KeyCode(chat_keyboard(self), key, CHAT_SCENE_KEY_MODE) == CHAT_SCENE_CODE_SEND) {
        if (ChatScene_Send(self) == 0) {
            return 0;
        }
        Glider_ShowSecondOfSet(&self->pointer);
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_SEND_IN);
        return 1;
    }
    SoftKeyboard_ShowKeyPressed(chat_keyboard(self), key);
    ChatScene_PointerSecondOfSet(self);
    return 1;
}
CLEAN_AS(func_ov111_0229f3ac, ChatScene_PressOnA)

/* func_ov111_0229f430: the d-pad's repeated `keys` on the line: left moves the cursor back and
 * right on (1); right at the line's end gives 4 (back to the keys); up 2 and down 3 (left at
 * the start falls through to them); 0 for none. */
int ChatScene_MoveCursorByKeys(ChatScene *self, int keys)
{
    if (keys == 0) {
        return 0;
    }
    if (KeyRepeat_HasLeft(keys)) {
        if (self->cursor != 0) {
            self->cursor--;
            return 1;
        }
    } else if (KeyRepeat_HasRight(keys)) {
        int length = func_02051c8c_unk(chat_line(self), CHAT_SCENE_LINE_CHARS);
        if (self->cursor + 1 > length) {
            return 4;
        }
        self->cursor++;
        return 1;
    }
    if (KeyRepeat_HasUp(keys)) {
        return 2;
    }
    if (KeyRepeat_HasDown(keys)) {
        return 3;
    }
    return 0;
}
CLEAN_AS(func_ov111_0229f430, ChatScene_MoveCursorByKeys)

/* --- The line --- */

/* func_ov111_0229f4c4: no range marked. */
void ChatScene_ClearMark(ChatScene *self)
{
    self->mark_from = 0;
    self->mark_to = 0;
    ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_MARKING);
}
CLEAN_AS(func_ov111_0229f4c4, ChatScene_ClearMark)

/* func_ov111_0229f4dc: a range of at least one character is marked. */
int ChatScene_IsMarking(ChatScene *self)
{
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_MARKING) == 0 || self->mark_from == self->mark_to) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov111_0229f4dc, ChatScene_IsMarking)

/* func_ov111_0229f504: the character before the cursor, 0 at the line's start. */
unsigned short ChatScene_CharBeforeCursor(ChatScene *self)
{
    u8 cursor = self->cursor;
    if (cursor == 0) {
        return 0;
    }
    return *chat_line_at(self, cursor - 1u);
}
CLEAN_AS(func_ov111_0229f504, ChatScene_CharBeforeCursor)

/* func_ov111_0229f524: the cursor drawn after the characters before it, shown at once, and the
 * keys updated. */
void ChatScene_PlaceCursorAtChar(ChatScene *self)
{
    self->cursor_x = (u8) TextString_Width(chat_line(self), self->cursor);
    self->blink = CHAT_SCENE_BLINK_START;
    ChatScene_UpdateKeys(self);
}
CLEAN_AS(func_ov111_0229f524, ChatScene_PlaceCursorAtChar)

/* func_ov111_0229f554: the cursor put at the character under `cursor_x`, drawn before it,
 * shown at once, and the keys updated. */
void ChatScene_PlaceCursorAtX(ChatScene *self)
{
    u8 x = self->cursor_x;
    self->cursor_x = SoftKeyboard_TextColumnAt(chat_keyboard(self), chat_line(self), CHAT_SCENE_LINE_CHARS,
                                               CHAT_SCENE_LINE_WIDTH, x, &self->cursor);
    self->blink = CHAT_SCENE_BLINK_START;
    ChatScene_UpdateKeys(self);
}
CLEAN_AS(func_ov111_0229f554, ChatScene_PlaceCursorAtX)

/* func_ov111_0229f598: the cursor put at the character under the screen's x, the composition
 * dropped and the line redrawn. */
void ChatScene_MoveCursorToX(ChatScene *self, int x)
{
    self->cursor_x = (u8) (x - CHAT_SCENE_LINE_X);
    ChatScene_PlaceCursorAtX(self);
    SoftKeyboard_HangulReset(chat_keyboard(self));
    ChatScene_RedrawLine(self);
}
CLEAN_AS(func_ov111_0229f598, ChatScene_MoveCursorToX)

/* func_ov111_0229f5bc: the marked range's end follows the pen's x (0x18-0xc7), with sound 0x15
 * when it moved. */
void ChatScene_FollowPen(ChatScene *self)
{
    int x = data_021f6c58;
    if (x < CHAT_SCENE_LINE_X) {
        x = CHAT_SCENE_LINE_X;
    }
    if (x >= 0xc8) {
        x = 0xc7;
    }
    ChatScene_MoveCursorToX(self, x);
    if (self->mark_to != self->cursor) {
        SoundSys_PlaySe(CHAT_SCENE_SE_MARK);
    }
    self->mark_to = self->cursor;
}
CLEAN_AS(func_ov111_0229f5bc, ChatScene_FollowPen)

/* func_ov111_0229f600: the pen on the line (x 0x10-0xc7, y 0x24-0x3b) puts the cursor there
 * and starts marking from it. 1 when it was. */
int ChatScene_TouchLine(ChatScene *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;
    if (y < 0x24 || y >= 0x3c) {
        return 0;
    }
    if (x < 0x10 || x >= 0xc8) {
        return 0;
    }
    if (x < CHAT_SCENE_LINE_X) {
        x = CHAT_SCENE_LINE_X;
    }
    ChatScene_MoveCursorToX(self, x);
    ChatScene_SetFlags(self, CHAT_SCENE_FLAG_MARKING);
    self->mark_from = self->cursor;
    self->mark_to = self->cursor;
    return 1;
}
CLEAN_AS(func_ov111_0229f600, ChatScene_TouchLine)

/* func_ov111_0229f660: the line sent, unless the send's look is still fading: an empty line
 * buzzes; else the player's character acts (state 13), sound 0x32, and this system's balloon
 * is taken down for the new one. 1 when it went. */
int ChatScene_Send(ChatScene *self)
{
    if (self->send_fade != 0) {
        return 0;
    }
    if (func_02051c8c_unk(chat_line(self), CHAT_SCENE_LINE_CHARS) == 0) {
        ChatScene_Buzz(self);
        return 0;
    }
    PlayerActorOps_RequestState13();
    SoundSys_PlaySe(CHAT_SCENE_SE_SEND);
    ChatScene_DismissOwnMessage(self);
    return 1;
}
CLEAN_AS(func_ov111_0229f660, ChatScene_Send)

/* func_ov111_0229f6a8: the send button under the pen sends the line, unless the send's look is
 * still fading. 1 when it went. */
int ChatScene_TouchSend(ChatScene *self)
{
    if (self->send_fade != 0) {
        return 0;
    }
    if (SoftKeyboard_TouchChatF7(chat_keyboard(self)) != 0) {
        return ChatScene_Send(self);
    }
    return 0;
}
CLEAN_AS(func_ov111_0229f6a8, ChatScene_TouchSend)

/* func_ov111_0229f6d4: the key under the pen runs, is shown pressed and starts repeating; gives
 * what it did (ChatScene_RunCode), 0 when no key is there. The pressed keys are released
 * first. */
int ChatScene_TouchKey(ChatScene *self)
{
    SoftKeyboard_ReleasePressed(chat_keyboard(self));
    int key = SoftKeyboard_KeyAt(chat_keyboard(self), data_021f6c58, data_021f6c54);
    if (key != -1) {
        int result = ChatScene_RunCode(self, SoftKeyboard_KeyCode(chat_keyboard(self), key, CHAT_SCENE_KEY_MODE));
        SoftKeyboard_ShowKeyPressed(chat_keyboard(self), key);
        SoftKeyboard_StartRepeat(chat_keyboard(self));
        return result;
    }
    return 0;
}
CLEAN_AS(func_ov111_0229f6d4, ChatScene_TouchKey)

/* func_ov111_0229f730: a key's code run. The keyboard's own codes redraw the line and give
 * what the keyboard did. Of the commands (ChatSceneCode): backspace, the conversions, copy,
 * paste, the tab keys (each switching to its tab), the expression keys (once the last
 * expression's wait is over: the expression acted out, the pointer in its third set) and the
 * send key (nothing here); other commands give 0. Any other code is a character put in at the
 * cursor, with a buzz when it does not fit (QUIRK: its code is cut to 16 bits, and it still
 * gives 1). Gives ChatSceneCodeResult. */
int ChatScene_RunCode(ChatScene *self, int code)
{
    int result = SoftKeyboard_HandleCommand(chat_keyboard(self), code, LAYER_SUB_BG3);
    if (result != 0) {
        ChatScene_RedrawLine(self);
        return result;
    }
    if (SoftKeyboard_IsCommand(chat_keyboard(self), code) == 0) {
        if (ChatScene_InsertChar(self, (u16) code) == 0) {
            ChatScene_Buzz(self);
        }
        return CHAT_SCENE_CODE_DONE;
    }
    if (code >= CHAT_SCENE_CODE_TAB_FIRST && code <= CHAT_SCENE_CODE_TAB_LAST) {
        ChatScene_SwitchTab(self, code - CHAT_SCENE_CODE_TAB_FIRST, 0);
        return CHAT_SCENE_CODE_CHANGED;
    }
    if (code >= CHAT_SCENE_CODE_EXPRESSION_FIRST && code <= CHAT_SCENE_CODE_EXPRESSION_LAST) {
        if (self->reaction_wait != 0) {
            return CHAT_SCENE_CODE_IGNORED;
        }
        SoftKeyboard_PickEmotionByCode(chat_keyboard(self), code);
        ChatScene_Express(self);
        ChatScene_PointerThirdOfSet(self);
        return CHAT_SCENE_CODE_EXPRESSED;
    }
    switch (code) {
        case CHAT_SCENE_CODE_BACKSPACE:
            ChatScene_Backspace(self, 1);
            return CHAT_SCENE_CODE_DONE;
        case CHAT_SCENE_CODE_CONVERT_1:
            ChatScene_Convert1(self);
            return CHAT_SCENE_CODE_CHANGED;
        case CHAT_SCENE_CODE_CONVERT_2:
            ChatScene_Convert2(self);
            return CHAT_SCENE_CODE_CHANGED;
        case CHAT_SCENE_CODE_CONVERT_3:
            ChatScene_Convert3(self);
            return CHAT_SCENE_CODE_CHANGED;
        case CHAT_SCENE_CODE_COPY:
            ChatScene_Copy(self);
            return CHAT_SCENE_CODE_CHANGED;
        case CHAT_SCENE_CODE_PASTE:
            ChatScene_Paste(self);
            return CHAT_SCENE_CODE_CHANGED;
        case CHAT_SCENE_CODE_SEND:
            return CHAT_SCENE_CODE_DONE;
        default:
            return CHAT_SCENE_CODE_IGNORED;
    }
}
CLEAN_AS(func_ov111_0229f730, ChatScene_RunCode)

/* func_ov111_0229f854: sound 0x34, the buzz of what cannot be done. */
void ChatScene_Buzz(ChatScene *self)
{
    (void) self;
    SoundSys_PlaySe(CHAT_SCENE_SE_BUZZ);
}
CLEAN_AS(func_ov111_0229f854, ChatScene_Buzz)

/* func_ov111_0229f860: the copied text put in at the cursor (in place of the marked range),
 * one character at a time until one does not fit (a buzz when not even the first does); the
 * cursor drawn after it, the line redrawn, the keyboard's sound 23. Nothing without copied
 * text. The keyboard's flag 2 is set meanwhile. */
void ChatScene_Paste(ChatScene *self)
{
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_COPIED) == 0) {
        return;
    }
    SoftKeyboard_SetFlag02(chat_keyboard(self));
    if (ChatScene_IsMarking(self)) {
        self->cursor = SoftKeyboard_DeleteRange(chat_keyboard(self), chat_line(self), self->mark_from, self->mark_to,
                                                CHAT_SCENE_LINE_CHARS);
        ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_MARKING);
    }
    SoftKeyboard_HangulReset(chat_keyboard(self));
    int count = func_02051c8c_unk(self->clipboard, CHAT_SCENE_LINE_CHARS);
    for (int i = 0; i < count; i++) {
        if (SoftKeyboard_Insert(chat_keyboard(self), chat_line(self), self->clipboard[i], &self->cursor, CHAT_SCENE_LINE_CHARS,
                                CHAT_SCENE_LINE_WIDTH, 0, 0) == 0) {
            if (i == 0) {
                ChatScene_Buzz(self);
            }
            break;
        }
    }
    ChatScene_PlaceCursorAtChar(self);
    ChatScene_RedrawLine(self);
    SoftKeyboard_PlaySe23(chat_keyboard(self));
    SoftKeyboard_ClearFlag02(chat_keyboard(self));
}
CLEAN_AS(func_ov111_0229f860, ChatScene_Paste)

/* func_ov111_0229f92c: the marked range copied (the paste key enabled from then on), with the
 * keyboard's sound 22. Nothing without a range. */
void ChatScene_Copy(ChatScene *self)
{
    if (!ChatScene_IsMarking(self)) {
        return;
    }
    int low;
    int length;
    chat_mark_range(self, &low, &length);
    TextString_ClearChars(self->clipboard, CHAT_SCENE_LINE_CHARS);
    TextString_CopyChars(chat_line_at(self, (unsigned int) low), self->clipboard, length);
    ChatScene_SetFlags(self, CHAT_SCENE_FLAG_COPIED);
    SoftKeyboard_PlaySe22(chat_keyboard(self));
    ChatScene_UpdateKeys(self);
}
CLEAN_AS(func_ov111_0229f92c, ChatScene_Copy)

/* func_ov111_0229f994: the line emptied: the cursor at its start, shown at once, no range
 * marked, the keys updated and reset. */
void ChatScene_ClearLine(ChatScene *self)
{
    self->blink = CHAT_SCENE_BLINK_START;
    self->cursor_x = 0;
    self->cursor = 0;
    ChatScene_ClearMark(self);
    ChatScene_UpdateKeys(self);
    SoftKeyboard_ResetKeyLooks(chat_keyboard(self));
    TextString_ClearChars(chat_line(self), CHAT_SCENE_LINE_CHARS);
}
CLEAN_AS(func_ov111_0229f994, ChatScene_ClearLine)

/* The keyboard's conversion `which` (1-3) of a character, 0 for none. */
static int chat_convert(ChatScene *self, int which, int character)
{
    switch (which) {
        case 1:
            return SoftKeyboard_Convert1(chat_keyboard(self), character);
        case 2:
            return SoftKeyboard_Convert2(chat_keyboard(self), character);
        default:
            return SoftKeyboard_Convert3(chat_keyboard(self), character);
    }
}

/* The character before the cursor replaced by its conversion `which`; 0 when there is none
 * (no character, or no conversion). */
static int chat_try_convert(ChatScene *self, int which)
{
    int character = ChatScene_CharBeforeCursor(self);
    if (character == 0) {
        return 0;
    }
    int converted = chat_convert(self, which, character);
    if (converted == 0) {
        return 0;
    }
    return SoftKeyboard_ReplaceBefore(chat_keyboard(self), chat_line(self), converted, self->cursor) != 0;
}

/* A conversion's result: the cursor drawn again and the line redrawn, else a buzz. */
static void chat_after_convert(ChatScene *self, int converted)
{
    if (converted) {
        ChatScene_PlaceCursorAtChar(self);
        ChatScene_RedrawLine(self);
    } else {
        ChatScene_Buzz(self);
    }
}

/* func_ov111_0229f9d4: the third conversion (code 0x105). */
void ChatScene_Convert3(ChatScene *self)
{
    chat_after_convert(self, ChatScene_TryConvert3(self));
}
CLEAN_AS(func_ov111_0229f9d4, ChatScene_Convert3)

/* func_ov111_0229f9fc */
int ChatScene_TryConvert3(ChatScene *self)
{
    return chat_try_convert(self, 3);
}
CLEAN_AS(func_ov111_0229f9fc, ChatScene_TryConvert3)

/* func_ov111_0229fa50: the second conversion (code 0x104). */
void ChatScene_Convert2(ChatScene *self)
{
    chat_after_convert(self, ChatScene_TryConvert2(self));
}
CLEAN_AS(func_ov111_0229fa50, ChatScene_Convert2)

/* func_ov111_0229fa78 */
int ChatScene_TryConvert2(ChatScene *self)
{
    return chat_try_convert(self, 2);
}
CLEAN_AS(func_ov111_0229fa78, ChatScene_TryConvert2)

/* func_ov111_0229facc: the first conversion (code 0x103). */
void ChatScene_Convert1(ChatScene *self)
{
    chat_after_convert(self, ChatScene_TryConvert1(self));
}
CLEAN_AS(func_ov111_0229facc, ChatScene_Convert1)

/* func_ov111_0229faf4 */
int ChatScene_TryConvert1(ChatScene *self)
{
    return chat_try_convert(self, 1);
}
CLEAN_AS(func_ov111_0229faf4, ChatScene_TryConvert1)

/* func_ov111_0229fb48: the characters from `mark_from` to `mark_to` deleted, the cursor where
 * they began, no range marked. */
void ChatScene_DeleteMarked(ChatScene *self)
{
    u8 to = self->mark_to;
    u8 from = self->mark_from;
    u8 low = from > to ? to : from;
    u8 high = from > to ? from : to;
    self->cursor = SoftKeyboard_DeleteRange(chat_keyboard(self), chat_line(self), low, high, CHAT_SCENE_LINE_CHARS);
    ChatScene_ClearMark(self);
}
CLEAN_AS(func_ov111_0229fb48, ChatScene_DeleteMarked)

/* func_ov111_0229fb8c: a backspace: the marked range deleted (the composition dropped), else
 * the character being composed taken back or the character before the cursor deleted, else at
 * the line's start its first character deleted. Then sound 0x35, the line redrawn and the
 * cursor drawn again; 1. With an empty line nothing is deleted: a buzz when `buzz` is set,
 * and 0. */
int ChatScene_Backspace(ChatScene *self, int buzz)
{
    if (ChatScene_IsMarking(self)) {
        SoftKeyboard_HangulReset(chat_keyboard(self));
        ChatScene_DeleteMarked(self);
    } else if (self->cursor != 0) {
        if (SoftKeyboard_HangulBackspace(chat_keyboard(self), chat_line(self), self->cursor) == 0) {
            self->mark_from = self->cursor;
            self->mark_to = (u8) (self->cursor - 1);
            ChatScene_DeleteMarked(self);
        }
    } else if (self->line.chars[0] != 0) {
        self->mark_from = 0;
        self->mark_to = 1;
        ChatScene_DeleteMarked(self);
    } else {
        if (buzz != 0) {
            SoundSys_PlaySe(CHAT_SCENE_SE_BUZZ);
        }
        return 0;
    }
    SoundSys_PlaySe(CHAT_SCENE_SE_DELETE);
    ChatScene_RedrawLine(self);
    ChatScene_PlaceCursorAtChar(self);
    return 1;
}
CLEAN_AS(func_ov111_0229fb8c, ChatScene_Backspace)

/* func_ov111_0229fc38: a character put in at the cursor, in place of the marked range (the
 * composition then dropped); the cursor drawn after it and the line redrawn. 1 when it fit. */
int ChatScene_InsertChar(ChatScene *self, int character)
{
    if (ChatScene_IsMarking(self)) {
        ChatScene_DeleteMarked(self);
        SoftKeyboard_HangulReset(chat_keyboard(self));
    }
    if (SoftKeyboard_Insert(chat_keyboard(self), chat_line(self), character, &self->cursor, CHAT_SCENE_LINE_CHARS,
                            CHAT_SCENE_LINE_WIDTH, 0, 1) == 0) {
        return 0;
    }
    ChatScene_PlaceCursorAtChar(self);
    ChatScene_RedrawLine(self);
    return 1;
}
CLEAN_AS(func_ov111_0229fc38, ChatScene_InsertChar)

/* func_ov111_0229fc9c: this system's balloon taken down. */
void ChatScene_DismissOwnMessage(ChatScene *self)
{
    (void) self;
    QuickMessage_Dismiss((unsigned int) data_020ccf94->local_slot);
}
CLEAN_AS(func_ov111_0229fc9c, ChatScene_DismissOwnMessage)

/* func_ov111_0229fcb0: the line posted: the current player's name, the posted text's taboo
 * words filtered out, the quick message posted under this system's slot; then the line
 * emptied and redrawn. */
void ChatScene_PostMessage(ChatScene *self)
{
    PlayerIdText name;
    u8 *record = PlayerRecords_Current();

    PlayerIdText_Construct(&name);
    PlayerId_NameToText(PlayerRecord_Player(record), (TextBase *) (void *) &name);
    MessageReader_FilterTaboo(self->message);
    QuickMessage_Post(data_020ccf94->local_slot, &name, self->message);
    ChatScene_ClearLine(self);
    ChatScene_RedrawLine(self);
    PlayerIdText_Destruct(&name);
}
CLEAN_AS(func_ov111_0229fcb0, ChatScene_PostMessage)

/* func_ov111_0229fd08: the line drawn again: its text box made when it has none, the line
 * turned into the posted 8-bit text, and that text drawn by the box. */
void ChatScene_RedrawLine(ChatScene *self)
{
    ChatScene_EnsureBox(self);
    if (self->box == NULL) {
        return;
    }
    TextBase_WideToBytes(chat_message(self), (WideTextBase *) (void *) &self->line, 0, 0);
    /* the 8-bit text's characters, through its class (slot 3) */
    u32 chars = ((u32 (*)(void *))(uintptr_t) chat_virtual(self->message, 3))(self->message);
    self->box->base.text = (const char *) (uintptr_t) chars;
    TextDraw_RequestDraw(&self->box->base);
}
CLEAN_AS(func_ov111_0229fd08, ChatScene_RedrawLine)

/* func_ov111_0229fd58: the text box made when the scene has none: 21 tiles by 2 from VRAM
 * tile 0x13d, on the sub screen's BG0, colour 1 on 2, the marked range in colour 2 on 1. */
void ChatScene_EnsureBox(ChatScene *self)
{
    if (self->box != NULL) {
        return;
    }
    self->box = LabelBox_NewInVram(0x13d, 0x15, 2);
    if (self->box == NULL) {
        return;
    }
    self->box->base.layer = LAYER_SUB_BG0;
    self->box->base.screens = 1;
    self->box->base.rows_full_width = 0;
    self->box->base.background = 2;
    self->box->base.color = 1;
    if (ChatScene_IsMarking(self)) {
        int low;
        int length;
        chat_mark_range(self, &low, &length);
        TextDraw_SetMark(&self->box->base, 2, 1, low, length);
    }
}
CLEAN_AS(func_ov111_0229fd58, ChatScene_EnsureBox)

/* func_ov111_0229fdf0: the text box freed. */
void ChatScene_FreeBox(ChatScene *self)
{
    if (self->box != NULL) {
        LabelBox_Free(self->box);
        self->box = NULL;
    }
}
CLEAN_AS(func_ov111_0229fdf0, ChatScene_FreeBox)

/* func_ov111_0229fe0c: the keyboard's objects drawn at (0x80, the wipe's y + 0x60): the mode
 * tabs, the expressions, the send button (its look 7 while sending, fading in and out over two
 * frames), the text cursor while not sending (blinking every 16 frames) and the frame. */
void ChatScene_DrawKeyboard(ChatScene *self)
{
    int y = MenuScene_WipeOffsetY(chat_scene(self)) + CHAT_SCENE_KEYBOARD_Y;
    int look;

    SoftKeyboard_DrawTabRow(chat_keyboard(self), CHAT_SCENE_KEYBOARD_X, y, 2);
    SoftKeyboard_DrawEmotionTabs(chat_keyboard(self), CHAT_SCENE_KEYBOARD_X, y);
    if (self->send_frame != 0) {
        if (self->send_fade < 2) {
            self->send_fade++;
        }
        look = 7;
    } else {
        if (self->send_fade != 0) {
            self->send_fade--;
        }
        look = 6;
    }
    SoftKeyboard_DrawChatF7(chat_keyboard(self), CHAT_SCENE_KEYBOARD_X, y, look, self->send_fade);
    self->blink++;
    if (self->send_frame == 0 && (self->blink & 0x10) != 0) {
        SoftKeyboard_DrawCaret(chat_keyboard(self), self->cursor_x + CHAT_SCENE_LINE_X, y - 0x38, 2);
    }
    SoftKeyboard_DrawChatSideButtons(chat_keyboard(self), CHAT_SCENE_KEYBOARD_X, y);
}
CLEAN_AS(func_ov111_0229fe0c, ChatScene_DrawKeyboard)

/* func_ov111_0229fed8: the send's look `frame` (0 and 1 the screen's own, 2-4 "b_cht_0.bsc" to
 * "b_cht_2.bsc"): its rows 4-8 copied into the keyboard's map (frame 1 with palette 5 turned
 * to 6 there), and the map uploaded.
 * REQUIRES: `frame` is 0-4; the game reads past its table of four files for others. */
void ChatScene_ShowSendFrame(ChatScene *self, int frame)
{
    Heap *heap = data_021fbe94;
    u8 *file = RomFile_Load(frame == 0 ? data_ov111_022a0f78[0] : data_ov111_022a0f78[frame - 1], heap, -4, NULL);
    u16 *map = self->keyboard.map;

    MI_CpuCopy8(file + 0x100, (u8 *) map + 0x100, 0x140);
    if (frame == 1) {
        ScreenMap_ReplacePalette(map, 0, 4, 0x1f, 9, 5, 6);
    }
    Heap_Free(heap, file);
    SoftKeyboard_MarkScreenDirty(chat_keyboard(self));
}
CLEAN_AS(func_ov111_0229fed8, ChatScene_ShowSendFrame)

/* func_ov111_0229ff60: the scene's members ended: the text box freed, the keyboard ended and,
 * unless the menu is closing, the player's actors told (a call that does nothing). */
void ChatScene_Teardown(ChatScene *self)
{
    ChatScene_FreeBox(self);
    SoftKeyboard_Finish(chat_keyboard(self));
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_CLOSING) == 0) {
        PlayerActors_Nothing();
    }
}
CLEAN_AS(func_ov111_0229ff60, ChatScene_Teardown)

/* func_ov111_0229ff88: the scene set up: no flags, not sending, no expression's wait, the line
 * emptied, no text box, the keyboard set up in mode 0, the line kept by GroupParams copied in,
 * and whether the menu opened with this tab. */
void ChatScene_Setup(ChatScene *self)
{
    self->flags = 0;
    self->unk_99 = 0;
    self->send_frame = 0;
    self->send_fade = 0;
    self->reaction_wait = 0;
    ChatScene_ClearLine(self);
    self->box = NULL;
    SoftKeyboard_Init(chat_keyboard(self), 0);
    TextString_CopyChars(GroupParams_TextD48(), chat_line(self), CHAT_SCENE_LINE_CHARS);
    PlayerActorOps_Nothing();
    if (MenuTabs_IsOpening((MenuTabs *) (void *) chat_parent(self))) {
        ChatScene_SetFlags(self, CHAT_SCENE_FLAG_OPENING);
    }
}
CLEAN_AS(func_ov111_0229ff88, ChatScene_Setup)

/* --- The sub states --- */

/* func_ov111_0229fff4 (sub state 15): the error message, with the keyboard's pressed key
 * shown; once it has closed, the input again. */
void ChatScene_UpdateError(ChatScene *self)
{
    SoftKeyboard_StepPressed(chat_keyboard(self));
    if (ErrorMessage_Update(&self->error, 1) != 0) {
        ChatScene_EnterInput(self);
    }
}
CLEAN_AS(func_ov111_0229fff4, ChatScene_UpdateError)

/* An expression key touched this frame acts its expression out, once the last one's wait is
 * over (while the pen is in use). */
static void chat_express_by_touch(ChatScene *self)
{
    if (StateFlags_IsClear2() && chat_pen_pressed()) {
        if (self->reaction_wait == 0 && SoftKeyboard_TouchEmotion(chat_keyboard(self)) != 0) {
            ChatScene_Express(self);
        }
    }
}

/* func_ov111_022a001c (sub state 14): the send's look goes back a frame at a time (the line
 * posted at frame 3, the pointer in its third set at frame 1 while the buttons are in use);
 * then the line emptied and redrawn, and the input again: the pen's (sub state 0), the
 * pointer's release while its animation runs (sub state 7), or the buttons'. Expressions may
 * be touched meanwhile. */
void ChatScene_SendAnimOut(ChatScene *self)
{
    chat_express_by_touch(self);
    if (self->send_frame != 0) {
        if (self->send_frame == 3) {
            ChatScene_PostMessage(self);
        }
        self->send_frame--;
        ChatScene_ShowSendFrame(self, self->send_frame);
        if (self->send_frame == 1 && StateFlags_Test2()) {
            Glider_ShowThirdOfSet(&self->pointer);
        }
    } else {
        ChatScene_ClearLine(self);
        ChatScene_RedrawLine(self);
        if (StateFlags_IsClear2()) {
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TOUCH);
        } else if (CellLayerSprite_AnimNumber((CellLayerSprite *) (void *) &self->pointer) != 0) {
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEY_RELEASE);
        } else {
            ChatScene_EnterKeys(self);
        }
    }
}
CLEAN_AS(func_ov111_022a001c, ChatScene_SendAnimOut)

/* func_ov111_022a00f4 (sub state 13): the send's look comes in a frame at a time up to frame
 * 4, held 3 frames, then the composition dropped and the look goes (sub state 14). Expressions
 * may be touched meanwhile. */
void ChatScene_SendAnimIn(ChatScene *self)
{
    chat_express_by_touch(self);
    if (self->send_frame < CHAT_SCENE_SEND_FRAMES) {
        self->send_frame++;
        ChatScene_ShowSendFrame(self, self->send_frame);
        self->send_delay = 3;
    } else if (self->send_delay != 0) {
        self->send_delay--;
    } else {
        SoftKeyboard_HangulReset(chat_keyboard(self));
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_SEND_OUT);
    }
}
CLEAN_AS(func_ov111_022a00f4, ChatScene_SendAnimIn)

/* func_ov111_022a0198: the player's character acts out the expression chosen (state 14), and
 * the next one waits 20 frames. */
void ChatScene_Express(ChatScene *self)
{
    unsigned char kind = SoftKeyboard_PickedEmotion(chat_keyboard(self));
    PlayerActorOps_RequestState14(&kind);
    self->reaction_wait = CHAT_SCENE_REACTION_WAIT;
}
CLEAN_AS(func_ov111_022a0198, ChatScene_Express)

/* func_ov111_022a01bc: the input by the pen while it is in use, else by the buttons. */
void ChatScene_EnterInput(ChatScene *self)
{
    if (StateFlags_IsClear2()) {
        ChatScene_EnterTouch(self);
    } else {
        ChatScene_EnterKeys(self);
    }
}
CLEAN_AS(func_ov111_022a01bc, ChatScene_EnterInput)

/* func_ov111_022a01dc: the input by the buttons: the key repeat reset, the pointer at the
 * keyboard's key (sub state 3), the line redrawn and the keys updated. */
void ChatScene_EnterKeys(ChatScene *self)
{
    MenuScene_ResetKeyRepeat(chat_scene(self));
    ChatScene_PointAtKey(self);
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEYS);
    ChatScene_RedrawLine(self);
    ChatScene_UpdateKeys(self);
}
CLEAN_AS(func_ov111_022a01dc, ChatScene_EnterKeys)

/* func_ov111_022a0204: the input by the pen: the pointer stopped (sub state 0). */
void ChatScene_EnterTouch(ChatScene *self)
{
    ChatScene_HidePointer(self);
    MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TOUCH);
}
CLEAN_AS(func_ov111_022a0204, ChatScene_EnterTouch)

/* func_ov111_022a021c (sub state 12): once R is let go, back to `return_sub_state` with the
 * keys updated. */
void ChatScene_WaitRRelease(ChatScene *self)
{
    if ((data_021fbe40.held & CHAT_SCENE_PAD_R) == 0) {
        MenuScene_SetSubState(chat_scene(self), self->return_sub_state);
        ChatScene_UpdateKeys(self);
    }
}
CLEAN_AS(func_ov111_022a021c, ChatScene_WaitRRelease)

/* func_ov111_022a024c (sub state 11): once L is let go, back to `return_sub_state` with the
 * keys updated. */
void ChatScene_WaitLRelease(ChatScene *self)
{
    if ((data_021fbe40.held & CHAT_SCENE_PAD_L) == 0) {
        MenuScene_SetSubState(chat_scene(self), self->return_sub_state);
        ChatScene_UpdateKeys(self);
    }
}
CLEAN_AS(func_ov111_022a024c, ChatScene_WaitLRelease)

/* func_ov111_022a027c (sub state 10): while A is held, the d-pad moves the marked range's end
 * (the composition dropped, the pointer following, sound 0x15); let go, back to sub state 9,
 * with no range when none was marked. The line is redrawn and the keys updated each frame. */
void ChatScene_MarkByKeys(ChatScene *self)
{
    if ((data_021fbe40.held & CHAT_SCENE_PAD_A) == 0) {
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TEXT_KEYS);
        if (self->mark_from == self->mark_to) {
            ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_MARKING);
        }
    } else if (ChatScene_MoveCursorByKeys(self, (int) MenuScene_LatchRepeatedKeys(chat_scene(self))) == 1) {
        SoftKeyboard_HangulReset(chat_keyboard(self));
        ChatScene_PlaceCursorAtChar(self);
        self->mark_to = self->cursor;
        ChatScene_PlacePointer(self);
        SoundSys_PlaySe(CHAT_SCENE_SE_MARK);
    }
    ChatScene_RedrawLine(self);
    ChatScene_UpdateKeys(self);
}
CLEAN_AS(func_ov111_022a027c, ChatScene_MarkByKeys)

/* func_ov111_022a02f8 (sub state 9): the pointer at the text cursor. The pen takes over the
 * input. Left and right move the cursor (the composition dropped, no range, sound 0x0b); right
 * at the line's end, up (to the mode tab under the pointer) and down take the pointer back to
 * the keys. Else L copies, R pastes, B deletes (the pointer following the cursor), A starts
 * marking from the cursor (sub state 10) and START sends. */
void ChatScene_TextByKeys(ChatScene *self)
{
    if (MenuScene_TakeTouch(chat_scene(self)) != 0) {
        ChatScene_EnterTouch(self);
        return;
    }
    switch (ChatScene_MoveCursorByKeys(self, (int) MenuScene_LatchRepeatedKeys(chat_scene(self)))) {
        case 1:
            SoftKeyboard_HangulReset(chat_keyboard(self));
            ChatScene_ClearMark(self);
            ChatScene_PlaceCursorAtChar(self);
            ChatScene_RedrawLine(self);
            ChatScene_PlacePointer(self);
            SoundSys_PlaySe(CHAT_SCENE_SE_CURSOR);
            return;
        case 4:
            SoftKeyboard_CursorToChatF7(chat_keyboard(self));
            ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT);
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEYS);
            ChatScene_GlidePointer(self);
            return;
        case 2:
            SoftKeyboard_CursorToMenuTabAt(chat_keyboard(self), Glider_ScreenX(&self->pointer));
            ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT);
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEYS);
            Glider_TurnToSetC(&self->pointer);
            ChatScene_GlidePointer(self);
            return;
        case 3:
            SoftKeyboard_CursorToTabRowAtB(chat_keyboard(self), Glider_ScreenX(&self->pointer));
            ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT);
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEYS);
            ChatScene_GlidePointer(self);
            return;
        default:
            break;
    }
    if (ChatScene_CopyOnL(self) != 0) {
        return;
    }
    if (ChatScene_PasteOnR(self) != 0) {
        return;
    }
    u8 before = self->cursor;
    if (ChatScene_BackspaceOnB(self) != 0) {
        if (before != self->cursor) {
            ChatScene_PlacePointer(self);
        }
        return;
    }
    if ((data_021fbe40.pressed & CHAT_SCENE_PAD_A) != 0) {
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_MARK_KEYS);
        ChatScene_SetFlags(self, CHAT_SCENE_FLAG_MARKING);
        self->mark_from = self->cursor;
        self->mark_to = self->cursor;
        return;
    }
    ChatScene_SendOnStart(self);
}
CLEAN_AS(func_ov111_022a02f8, ChatScene_TextByKeys)

/* func_ov111_022a0460 (sub state 8): while B is held, each repeat deletes again (the pointer
 * following the cursor when it is on the text); let go, back to `return_sub_state`. */
void ChatScene_RepeatBackspace(ChatScene *self)
{
    if ((data_021fbe40.held & CHAT_SCENE_PAD_B) == 0) {
        MenuScene_SetSubState(chat_scene(self), self->return_sub_state);
    } else if (SoftKeyboard_StepRepeat(chat_keyboard(self)) != 0) {
        ChatScene_RunCode(self, CHAT_SCENE_CODE_BACKSPACE);
        if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT)) {
            ChatScene_PlacePointer(self);
        }
    }
}
CLEAN_AS(func_ov111_022a0460, ChatScene_RepeatBackspace)

/* func_ov111_022a04ac (sub state 7): once the pointer's release has played, the keyboard by
 * the buttons again. */
void ChatScene_WaitKeyRelease(ChatScene *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->pointer) != 0) {
        ChatScene_PointerFirstOfSet(self);
    }
}
CLEAN_AS(func_ov111_022a04ac, ChatScene_WaitKeyRelease)

/* func_ov111_022a04cc (sub state 6): while A is held, the held key runs again at each repeat
 * and is shown pressed; let go, the keys are released and the pointer's release plays. */
void ChatScene_RepeatKey(ChatScene *self)
{
    if ((data_021fbe40.held & CHAT_SCENE_PAD_A) == 0) {
        SoftKeyboard_ReleasePressed(chat_keyboard(self));
        ChatScene_PointerThirdOfSet(self);
    } else if (SoftKeyboard_StepRepeat(chat_keyboard(self)) != 0) {
        int key = SoftKeyboard_PressedKey(chat_keyboard(self));
        ChatScene_RunCode(self, SoftKeyboard_KeyCode(chat_keyboard(self), key, CHAT_SCENE_KEY_MODE));
        SoftKeyboard_ShowKeyPressed(chat_keyboard(self), key);
    }
}
CLEAN_AS(func_ov111_022a04cc, ChatScene_RepeatKey)

/* func_ov111_022a0530 (sub state 5): once the pointer's press has played, the key the cursor
 * is on runs. An expression stays (sub state 7 was set); a character or backspace with A still
 * held repeats (sub state 6, the key shown pressed); otherwise the keys are released and,
 * unless the keyboard answered 4, the pointer's release plays. */
void ChatScene_PressKey(ChatScene *self)
{
    if (CellLayerSprite_IsDone((CellLayerSprite *) (void *) &self->pointer) == 0) {
        return;
    }
    int key = SoftKeyboard_PressCursorKey(chat_keyboard(self));
    int result = ChatScene_RunCode(self, SoftKeyboard_KeyCode(chat_keyboard(self), key, CHAT_SCENE_KEY_MODE));
    if (result == CHAT_SCENE_CODE_EXPRESSED) {
        return;
    }
    if (result == CHAT_SCENE_CODE_DONE && (data_021fbe40.held & CHAT_SCENE_PAD_A) != 0) {
        SoftKeyboard_StartRepeat(chat_keyboard(self));
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEY_REPEAT);
        SoftKeyboard_ShowKeyPressed(chat_keyboard(self), key);
        return;
    }
    SoftKeyboard_ReleasePressed(chat_keyboard(self));
    if (result != 4) {
        ChatScene_PointerThirdOfSet(self);
    }
}
CLEAN_AS(func_ov111_022a0530, ChatScene_PressKey)

/* Obj_ov111_022a1008::func_ov111_022a05b0 (sub state 4): once the pointer stops, back to
 * `return_sub_state`, run at once. */
void ChatScene_WaitPointerGlide(ChatScene *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(chat_scene(self), self->return_sub_state);
        ChatScene_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov111_022a100819func_ov111_022a05b0Ev, ChatScene_WaitPointerGlide)

/* func_ov111_022a05dc (sub state 3): the keyboard by the buttons. The pen takes over the
 * input. The d-pad moves the keyboard's cursor, the pointer turning and gliding after it (to
 * the text cursor when the keyboard answers 4). Else A presses the key, B deletes, START sends,
 * and R and L switch to the menu's next and previous tab. */
void ChatScene_KeyboardByKeys(ChatScene *self)
{
    if (MenuScene_TakeTouch(chat_scene(self)) != 0) {
        ChatScene_EnterTouch(self);
        return;
    }
    int keys = (int) MenuScene_LatchRepeatedKeys(chat_scene(self));
    switch (SoftKeyboard_MoveCursor(chat_keyboard(self), keys)) {
        case 1:
            Glider_TurnToSetA(&self->pointer);
            ChatScene_GlidePointer(self);
            return;
        case 2:
            Glider_TurnToSetC(&self->pointer);
            ChatScene_GlidePointer(self);
            return;
        case 4:
            Glider_TurnToSetA(&self->pointer);
            ChatScene_SetFlags(self, CHAT_SCENE_FLAG_POINTER_ON_TEXT);
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TEXT_KEYS);
            ChatScene_GlidePointer(self);
            return;
        default:
            break;
    }
    if (ChatScene_PressOnA(self) != 0) {
        return;
    }
    if (ChatScene_BackspaceOnB(self) != 0) {
        return;
    }
    if (ChatScene_SendOnStart(self) != 0) {
        return;
    }
    u16 pressed = data_021fbe40.pressed;
    if (pressed & CHAT_SCENE_PAD_R) {
        ChatScene_SwitchTab(self, MenuTabs_NextTab(CHAT_SCENE_TAB_OWN), 0);
    } else if (pressed & CHAT_SCENE_PAD_L) {
        ChatScene_SwitchTab(self, MenuTabs_PreviousTab(CHAT_SCENE_TAB_OWN), 0);
    }
}
CLEAN_AS(func_ov111_022a05dc, ChatScene_KeyboardByKeys)

/* func_ov111_022a06c8 (sub state 2): the pen drags the marked range's end; let go, back to sub
 * state 0, with no range when none was marked. The line is redrawn each frame. */
void ChatScene_MarkByDrag(ChatScene *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TOUCH);
        if (self->mark_from == self->mark_to) {
            ChatScene_ClearFlags(self, CHAT_SCENE_FLAG_MARKING);
        }
    } else {
        ChatScene_FollowPen(self);
    }
    ChatScene_RedrawLine(self);
}
CLEAN_AS(func_ov111_022a06c8, ChatScene_MarkByDrag)

/* func_ov111_022a0708 (sub state 1): while the pen is down, the held key runs again at each
 * repeat and is shown pressed; lifted, back to sub state 0. */
void ChatScene_RepeatTouchedKey(ChatScene *self)
{
    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TOUCH);
        return;
    }
    if (SoftKeyboard_StepRepeat(chat_keyboard(self)) == 0) {
        return;
    }
    int key = SoftKeyboard_PressedKey(chat_keyboard(self));
    ChatScene_RunCode(self, SoftKeyboard_KeyCode(chat_keyboard(self), key, CHAT_SCENE_KEY_MODE));
    SoftKeyboard_ShowKeyPressed(chat_keyboard(self), key);
}
CLEAN_AS(func_ov111_022a0708, ChatScene_RepeatTouchedKey)

/* func_ov111_022a075c (sub state 0): the pen. A button takes the input to the buttons. While
 * the keyboard shows a pressed key nothing else happens. The pen going down runs the key under
 * it (a character or backspace then repeats: sub state 1), else changes the keyboard's mode
 * (its state 9), sends (sub state 13), acts an expression out, or starts marking on the line
 * (sub state 2). */
void ChatScene_IdleByTouch(ChatScene *self)
{
    if (MenuScene_TakeButtons(chat_scene(self), 1) != 0) {
        ChatScene_EnterKeys(self);
        return;
    }
    if (SoftKeyboard_StepPressed(chat_keyboard(self)) != 0) {
        return;
    }
    if (!chat_pen_pressed()) {
        return;
    }
    int result = ChatScene_TouchKey(self);
    if (result != 0) {
        if (result == CHAT_SCENE_CODE_DONE) {
            MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_KEY_TOUCH_HELD);
        }
        return;
    }
    if (SoftKeyboard_TouchPageTab(chat_keyboard(self)) != 0) {
        ChatScene_SetKeyboardState(self, CHAT_SCENE_KEYBOARD_STATE_MODE_TAB);
        ChatScene_RedrawLine(self);
        return;
    }
    if (ChatScene_TouchSend(self) != 0) {
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_SEND_IN);
        return;
    }
    if (self->reaction_wait == 0 && SoftKeyboard_TouchEmotion(chat_keyboard(self)) != 0) {
        ChatScene_Express(self);
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_TOUCH);
        return;
    }
    if (ChatScene_TouchLine(self) != 0) {
        ChatScene_UpdateKeys(self);
        MenuScene_SetSubState(chat_scene(self), CHAT_SCENE_SUB_MARK_DRAG);
    }
}
CLEAN_AS(func_ov111_022a075c, ChatScene_IdleByTouch)

/* --- The states --- */

/* func_ov111_022a082c (state 5): the wipe out; once over, the sub screen's BG3 hidden and the
 * scene deleted (phase 5). */
void ChatScene_WipeOut(ChatScene *self)
{
    if (MenuScene_StepWipe(chat_scene(self), 0) != 0) {
        DisplayLayer_Hide(LAYER_SUB_BG3);
        MenuScene_SetPhase(chat_scene(self), CHAT_SCENE_PHASE_DELETE);
    } else {
        MenuScene_ScrollWipe(chat_scene(self), LAYER_SUB_BG3, 0, 0);
    }
}
CLEAN_AS(func_ov111_022a082c, ChatScene_WipeOut)

/* func_ov111_022a085c (state 4): the wipe out started on window 2 (state 5). */
void ChatScene_StartWipeOut(ChatScene *self)
{
    MenuScene_StartWipeOnWindow2(chat_scene(self), LAYER_SUB_OBJ, 0, 0, CHAT_SCENE_WIPE_MARGIN);
    MenuScene_ScrollWipe(chat_scene(self), LAYER_SUB_BG3, 0, 0);
    self->base.state = CHAT_SCENE_STATE_WIPE_OUT;
}
CLEAN_AS(func_ov111_022a085c, ChatScene_StartWipeOut)

/* func_ov111_022a088c (state 3): the wipe in; once over, the input (phase 2). */
void ChatScene_WipeIn(ChatScene *self)
{
    if (MenuScene_StepWipeBack(chat_scene(self), 0) != 0) {
        MenuScene_SetPhase(chat_scene(self), CHAT_SCENE_PHASE_INTERACTIVE);
        ChatScene_EnterInput(self);
    }
    MenuScene_ScrollWipe(chat_scene(self), LAYER_SUB_BG3, 0, 0);
}
CLEAN_AS(func_ov111_022a088c, ChatScene_WipeIn)

/* func_ov111_022a08bc (state 2): the keyboard set up in the mode main keeps and drawn, the
 * scene drawn from now on, the covered wipe in started on window 2 with the sub screen's BG3
 * shown (state 3), and the line drawn. */
void ChatScene_StartWipeIn(ChatScene *self)
{
    SoftKeyboard_LoadSavedLayout(chat_keyboard(self), LAYER_SUB_BG3);
    ChatScene_DrawKeyboardLayer(self);
    ChatScene_SetFlags(self, CHAT_SCENE_FLAG_DRAWN);
    MenuScene_StartWipeCoveredOnWindow2(chat_scene(self), LAYER_SUB_OBJ, 3, 0, CHAT_SCENE_WIPE_MARGIN);
    DisplayLayer_Show(LAYER_SUB_BG3);
    MenuScene_ScrollWipe(chat_scene(self), LAYER_SUB_BG3, 0, 0);
    MenuScene_SetState(chat_scene(self), CHAT_SCENE_STATE_WIPE_IN);
    ChatScene_RedrawLine(self);
}
CLEAN_AS(func_ov111_022a08bc, ChatScene_StartWipeIn)

/* func_ov111_022a0910 (state 1): the expression keys' characters and the screen's files
 * loaded (state 2, run at once unless the menu is opening). */
void ChatScene_LoadScreen(ChatScene *self)
{
    SoftKeyboard_LoadEmotions(chat_keyboard(self));
    ChatScene_LoadScreenFiles(self);
    MenuScene_SetState(chat_scene(self), CHAT_SCENE_STATE_START_WIPE_IN);
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_OPENING) == 0) {
        ChatScene_StartWipeIn(self);
    }
}
CLEAN_AS(func_ov111_022a0910, ChatScene_LoadScreen)

/* func_ov111_022a0940 (state 0): the sub screen's BG3 set up and the keyboard's files loaded
 * (state 1, run at once unless the menu is opening). */
void ChatScene_LoadKeyboard(ChatScene *self)
{
    ChatScene_SetUpLayer();
    SoftKeyboard_LoadObjGraphics(chat_keyboard(self));
    MenuScene_SetState(chat_scene(self), CHAT_SCENE_STATE_LOAD_SCREEN);
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_OPENING) == 0) {
        ChatScene_LoadScreen(self);
    }
}
CLEAN_AS(func_ov111_022a0940, ChatScene_LoadKeyboard)

/* func_ov111_022a0970: the screen's palettes 1-9, its map (into the keyboard's, the keys then
 * updated and the map uploaded to the sub screen's BG3) and its characters 0x13d-0x1e9. */
void ChatScene_LoadScreenFiles(ChatScene *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov111_022a1068, heap, LAYER_SUB_BG3, 1, 1, 9);
    SoftKeyboard_ReadScreen(chat_keyboard(self), data_ov111_022a0f88);
    ChatScene_UpdateKeys(self);
    SoftKeyboard_LoadScreenNow(chat_keyboard(self), LAYER_SUB_BG3);
    DisplayLayer_LoadCharsFromFile(data_ov111_022a1080, heap, LAYER_SUB_BG3, 0x13d, 0x13d, 0x1e9);
}
CLEAN_AS(func_ov111_022a0970, ChatScene_LoadScreenFiles)

/* func_ov111_022a09d8: the sub screen's BG3 at priority 2, its control word 0. */
void ChatScene_SetUpLayer(void)
{
    DisplayLayer_SetPriority(LAYER_SUB_BG3, 2);
    DisplayLayer_SetBgControl(LAYER_SUB_BG3, 0, 0, 0);
}
CLEAN_AS(func_ov111_022a09d8, ChatScene_SetUpLayer)

/* --- The tab switch, the frame and the vtable's slots --- */

/* func_ov111_022a09f8: the menu switched to `tab` (none for -1 or this tab, 4): the pointer
 * stopped and the scene wiped out (state 4 in phase 1), the menu's closing noted (tab 7), and
 * the line kept by GroupParams for the next time (`keep_line`) or not. 1 when it switched.
 * The parent is looked up first in any case. */
int ChatScene_SwitchTab(ChatScene *self, int tab, int keep_line)
{
    Process *parent = chat_parent(self);
    if (tab == CHAT_SCENE_TAB_NONE || tab == CHAT_SCENE_TAB_OWN) {
        return 0;
    }
    MenuTabs_SelectTab((MenuTabs *) (void *) parent, (u8) tab);
    ChatScene_HidePointer(self);
    self->base.state = CHAT_SCENE_STATE_LEAVE;
    MenuScene_SetPhase(chat_scene(self), CHAT_SCENE_PHASE_STATES);
    if (tab == MENU_TAB_CLOSE) {
        ChatScene_SetFlags(self, CHAT_SCENE_FLAG_CLOSING);
    }
    if (keep_line != 0) {
        GroupParams_SetTextD48(chat_line(self));
    } else {
        GroupParams_ClearTextD48();
    }
    return 1;
}
CLEAN_AS(func_ov111_022a09f8, ChatScene_SwitchTab)

/* func_ov111_022a0a5c: the scene leaves when main asks the menu to close (the line kept; in
 * any sub state but 4 and 13-15), and in sub states 0, 3 and 9 for the bar's tab under the pen
 * (while it is in use) or SELECT (close), Y (tab 0) or X (tab 5). 1 when it left. */
int ChatScene_CheckLeave(ChatScene *self)
{
    StateFlags_CountMenuCloseDelay();
    if (StateFlags_MenuCloseAsked()) {
        u8 sub_state = self->base.sub_state;
        if (sub_state <= CHAT_SCENE_SUB_WHILE_R && sub_state != CHAT_SCENE_SUB_POINTER_GLIDE) {
            return ChatScene_SwitchTab(self, MENU_TAB_CLOSE, 1);
        }
    }
    u8 sub_state = self->base.sub_state;
    if (sub_state != CHAT_SCENE_SUB_TOUCH && sub_state != CHAT_SCENE_SUB_KEYS && sub_state != CHAT_SCENE_SUB_TEXT_KEYS) {
        return 0;
    }
    int tab = CHAT_SCENE_TAB_NONE;
    if (StateFlags_IsClear2()) {
        tab = MenuTabs_TabAtTouch();
    } else {
        u16 pressed = data_021fbe40.pressed;
        if (pressed & CHAT_SCENE_PAD_SELECT) {
            tab = MENU_TAB_CLOSE;
        } else if (pressed & CHAT_SCENE_PAD_Y) {
            tab = MENU_TAB_POCKETS;
        } else if (pressed & CHAT_SCENE_PAD_X) {
            tab = MENU_TAB_5;
        }
    }
    return ChatScene_SwitchTab(self, tab, 0);
}
CLEAN_AS(func_ov111_022a0a5c, ChatScene_CheckLeave)

/* func_ov111_022a0b20: the end of an input frame: the expression's wait counted down (at its
 * end the keyboard's expression is unchosen), and the keyboard drawn. */
void ChatScene_EndFrame(ChatScene *self)
{
    if (self->reaction_wait != 0) {
        self->reaction_wait--;
        if (self->reaction_wait == 0) {
            SoftKeyboard_DropEmotion(chat_keyboard(self));
        }
    }
    ChatScene_DrawKeyboardLayer(self);
}
CLEAN_AS(func_ov111_022a0b20, ChatScene_EndFrame)

/* func_ov111_022a0b58: the pointer's update through its class (vtable slot 3). */
void ChatScene_UpdatePointer(ChatScene *self)
{
    chat_update_pointer(self);
}
CLEAN_AS(func_ov111_022a0b58, ChatScene_UpdatePointer)

/* func_ov111_022a0b70 (vtable slot 0x18): a frame: the text box freed, then the base's frame.
 * Answers 1.
 * QUIRK: the box lives at most a frame: it is made again whenever the line is redrawn. */
int ChatScene_Update(ChatScene *self)
{
    ChatScene_FreeBox(self);
    MenuScene_Update(chat_scene(self));
    return 1;
}
CLEAN_AS(func_ov111_022a0b70, ChatScene_Update)

/* func_ov111_022a0b88 (vtable slot 0x5c, phase 5): the scene asks to be deleted. */
int ChatScene_RequestDelete(ChatScene *self)
{
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov111_022a0b88, ChatScene_RequestDelete)

/* func_ov111_022a0b98 (vtable slot 0x58, phase 4): nothing. */
int ChatScene_Phase4(void)
{
    return 1;
}
CLEAN_AS(func_ov111_022a0b98, ChatScene_Phase4)

/* func_ov111_022a0b9c (vtable slot 0x54, phase 3): nothing. */
int ChatScene_Phase3(void)
{
    return 1;
}
CLEAN_AS(func_ov111_022a0b9c, ChatScene_Phase3)

/* Obj_ov111_022a1008::func_ov111_022a0ba0 (vtable slot 0x50, phase 2): a frame of the input,
 * unless the scene leaves: the pointer updated, the sub state run, the frame ended. Answers
 * 1. */
int ChatScene_RunInteractive(ChatScene *self)
{
    if (ChatScene_CheckLeave(self) != 0) {
        return 1;
    }
    ChatScene_UpdatePointer(self);
    ChatScene_RunSubState(self);
    ChatScene_EndFrame(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov111_022a100819func_ov111_022a0ba0Ev, ChatScene_RunInteractive)

/* Obj_ov111_022a1008::func_ov111_022a0bcc: the sub state's function (ChatSceneSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 16; the game reads past the table for others. */
void ChatScene_RunSubState(ChatScene *self)
{
    static const MemberPointer *const sub_states[CHAT_SCENE_SUB_STATES] = {
        &data_ov111_022a0f60, &data_ov111_022a0f58, &data_ov111_022a0f50, &data_ov111_022a0f48,
        &data_ov111_022a0f40, &data_ov111_022a0ef0, &data_ov111_022a0f30, &data_ov111_022a0f28,
        &data_ov111_022a0ee8, &data_ov111_022a0f20, &data_ov111_022a0f10, &data_ov111_022a0f08,
        &data_ov111_022a0f70, &data_ov111_022a0f00, &data_ov111_022a0ef8, &data_ov111_022a0ec8,
    };
    MemberTable_InitOnce(&data_ov111_022a10a0, data_ov111_022a10d8, sub_states, CHAT_SCENE_SUB_STATES);
    MemberPointer_CallVoid(&data_ov111_022a10d8[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov111_022a100819func_ov111_022a0bccEv, ChatScene_RunSubState)

/* Obj_ov111_022a1008::func_ov111_022a0cf8 (vtable slot 0x4c, phase 1): the state's function
 * (ChatSceneState) through the table of member functions, filled once from its constants.
 * Answers 1.
 * REQUIRES: the state is below 6; the game reads past the table for others. */
int ChatScene_RunState(ChatScene *self)
{
    static const MemberPointer *const states[CHAT_SCENE_STATES] = {
        &data_ov111_022a0f38, &data_ov111_022a0f18, &data_ov111_022a0f68,
        &data_ov111_022a0ed8, &data_ov111_022a0ed0, &data_ov111_022a0ec0,
    };
    MemberTable_InitOnce(&data_ov111_022a10a4, data_ov111_022a10a8, states, CHAT_SCENE_STATES);
    MemberPointer_CallVoid(&data_ov111_022a10a8[self->base.state], self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov111_022a100819func_ov111_022a0cf8Ev, ChatScene_RunState)

/* func_ov111_022a0d9c (vtable slot 0x24): while the scene is drawn, the pointer (while the
 * buttons are in use) and the keyboard's objects. Answers 1. */
int ChatScene_Draw(ChatScene *self)
{
    if (ChatScene_TestFlags(self, CHAT_SCENE_FLAG_DRAWN) != 0) {
        if (StateFlags_Test2()) {
            Glider_DrawWrapped(&self->pointer);
        }
        ChatScene_DrawKeyboard(self);
    }
    return 1;
}
CLEAN_AS(func_ov111_022a0d9c, ChatScene_Draw)

/* func_ov111_022a0dcc (vtable slot 0x0c): the scene ends: the parent menu told and the members
 * ended. Answers 1. */
int ChatScene_End(ChatScene *self)
{
    MenuTabs_ChildClosed((MenuTabs *) (void *) chat_parent(self));
    ChatScene_Teardown(self);
    return 1;
}
CLEAN_AS(func_ov111_022a0dcc, ChatScene_End)

/* func_ov111_022a0de8 (vtable slot 0x00): the scene starts: its setup, state 0 in phase 1.
 * Answers 1. */
int ChatScene_Start(ChatScene *self)
{
    ChatScene_Setup(self);
    MenuScene_SetState(chat_scene(self), CHAT_SCENE_STATE_LOAD_KEYBOARD);
    MenuScene_SetPhase(chat_scene(self), CHAT_SCENE_PHASE_STATES);
    return 1;
}
CLEAN_AS(func_ov111_022a0de8, ChatScene_Start)

/* func_ov111_022a0e08 (named by the profile at 0x022a0ee0): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order (the keyboard's layer tasks and labels, the posted text, the line with its own vtable,
 * the pointer and the error message). The keyboard itself has no constructor. */
ChatScene *ChatScene_New(void)
{
    ChatScene *self = MenuScene_Alloc(sizeof(ChatScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov111_022a1008;
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct(&self->keyboard.tasks[i]);
    }
    __cxa_vec_ctor(self->keyboard.labels, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    QuickMessage_TextConstruct((struct QuickMessageText *) (void *) self->message);
    TextBase_WideConstruct(&self->line);
    self->line.vtable = &data_ov111_022a0ff0;
    Glider0_Construct(&self->pointer);
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov111_022a0e08, ChatScene_New)
