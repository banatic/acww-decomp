/* The letter writing scene of overlay 122 (letter_write_scene.h): its destructors, its flags,
 * the taboo filter and the defaults kept at the end, the pointer sprite, the scroll, and the
 * text cursor: where it is drawn, where a touch or the d-pad puts it, and the marked range. */
#include "letter_write_scene.h"

#include "autoload_2/input.h"
#include "clean.h"
#include "main/message_reader.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "ov002/key_repeat.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(LetterWriteScene, cursor_x) == 0x9c, "cursor");
static_assert(offsetof(LetterWriteScene, flags) == 0xa8 && offsetof(LetterWriteScene, position) == 0xac, "flags");
static_assert(offsetof(LetterWriteScene, scroll) == 0xb2 && offsetof(LetterWriteScene, button) == 0xb8, "bytes");
static_assert(offsetof(LetterWriteScene, letter) == 0xbc && offsetof(LetterWriteScene, keyboard) == 0xc0, "letter");
static_assert(offsetof(LetterWriteScene, labels) == 0x2410 && offsetof(LetterWriteScene, view) == 0x3ce8, "view");
static_assert(offsetof(LetterWriteScene, scroll_button) == 0x4010 && offsetof(LetterWriteScene, pointer) == 0x4058, "button");
static_assert(offsetof(LetterWriteScene, filter_text) == 0x40bc && offsetof(LetterWriteScene, filter_wide) == 0x4150,
              "filter");
static_assert(offsetof(LetterWriteScene, shown_header) == 0x41e0 && offsetof(LetterWriteScene, choice) == 0x42b0, "choice");
static_assert(offsetof(LetterWriteScene, panel) == 0x4698 && offsetof(LetterWriteScene, error) == 0x4864, "panel");
static_assert(sizeof(LetterWriteScene) == 0x4980, "size (func_ov122_022a24bc)");
static_assert(offsetof(Letter, header) == 0x44 && offsetof(Letter, header_line) == 0xf8, "letter");

/* The buttons, and the touch (main's bytes). */
extern PadState data_021fbe40;
extern u8 data_021f6c58; /* the touch's x, while the pen is down */
extern u8 data_021f6c54; /* and its y */

#define LETTER_WRITE_KEY_UP 0x40
#define LETTER_WRITE_KEY_DOWN 0x80

/* The scene's vtable. */
extern const u8 data_ov122_022a2738[];

/* The labels' destructor is handed to __cxa_vec_cleanup, so it is the game's symbol. */
extern int **func_02070be8(void *label);
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The panel's button and the sound of each button LetterWrite_PressButton presses. */
extern const unsigned char data_ov122_022a2584[];
extern const unsigned short data_ov122_022a258c[];

/* The keyboard of overlay 95 (no Clean version yet). */
extern void func_ov095_0229cce0(void *keyboard); /* releases its pressed keys */
extern void func_ov095_02299aec(void *keyboard); /* sets its key place by its mode */
extern int func_ov095_02299b7c(void *keyboard);  /* the key's x */
extern int func_ov095_02299b38(void *keyboard);  /* the key's y */
extern void func_ov095_0229cd30(int keyboard);   /* resets its keys */
/* Deletes the characters from `from` to `to` of a text of `length`, filling the end with 0;
 * gives the lower of the two. */
extern int func_ov095_0229bbc0(int unused, unsigned short *text, int from, int to, int length);
/* The character of a text of `length` characters (at most `limit` pixels wide) whose middle is
 * past `x` pixels, into *index; gives the pixels before it. */
extern unsigned char func_ov095_0229bb34(int unused, const unsigned short *text, int length, int limit, unsigned char x,
                                         unsigned char *index);

/* The overlay's own functions outside this file. */
extern unsigned char *func_ov122_022a0054(void *self); /* the pointer hidden, sub state 0 */
extern void func_ov122_022a14c0(void *self);           /* the keyboard's keys shown by the cursor */

/* The characters before a 0, at most `max` (main's). */
extern int func_02051c8c_unk(u16 *text, int max);

static MenuScene *letter_write_scene(LetterWriteScene *self)
{
    return &self->base;
}

static PagedChoice *letter_write_choice(LetterWriteScene *self)
{
    return (PagedChoice *) (void *) self->choice;
}

static int letter_write_keyboard_arg(LetterWriteScene *self)
{
    return (int) (uintptr_t) self->keyboard;
}

/* The pointer's update through its class (vtable slot 3). */
static void letter_write_update_pointer(LetterWriteScene *self)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) self->pointer.vtable;
    vtable[3](&self->pointer);
}

/* The header from character `index` on. QUIRK: `header_line` is not bounded by the header's
 * ten characters; past them this points into the body, as the game's address does. */
static u16 *letter_write_header_from(Letter *letter, unsigned int index)
{
    return (u16 *) (uintptr_t) ((uintptr_t) letter->header + 2u * index);
}

/* --- The destructors and the flags --- */

/* The members' destructors, last member first, then the base's. */
static void letter_write_destroy_members(LetterWriteScene *self)
{
    self->base.vtable = data_ov122_022a2738;
    ErrorMessage_Destruct(&self->error);
    ButtonPanel_Destroy(&self->panel);
    PagedChoice_Destroy(letter_write_choice(self));
    LetterBodyText_Destruct(&self->filter_wide);
    MailMsgText_Destruct(&self->filter_text);
    Glider0_Destroy(&self->pointer);
    PushButton_Destroy(&self->scroll_button);
    LetterView_Destruct(&self->view);
    __cxa_vec_cleanup(self->labels, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    MenuScene_DestroyBase(letter_write_scene(self));
}

/* func_ov122_0229eea0: the destructor. */
LetterWriteScene *LetterWrite_Destroy(LetterWriteScene *self)
{
    letter_write_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov122_0229eea0, LetterWrite_Destroy)

/* func_ov122_0229ef30: the deleting destructor. */
LetterWriteScene *LetterWrite_Delete(LetterWriteScene *self)
{
    letter_write_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov122_0229ef30, LetterWrite_Delete)

/* func_ov122_0229efc8 */
void LetterWrite_ClearFlags(LetterWriteScene *self, unsigned short mask)
{
    self->flags &= (u16) ~mask;
}
CLEAN_AS(func_ov122_0229efc8, LetterWrite_ClearFlags)

/* func_ov122_0229efd8 */
void LetterWrite_SetFlags(LetterWriteScene *self, unsigned short mask)
{
    self->flags |= mask;
}
CLEAN_AS(func_ov122_0229efd8, LetterWrite_SetFlags)

/* func_ov122_0229efe8 */
int LetterWrite_TestFlags(LetterWriteScene *self, unsigned short mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov122_0229efe8, LetterWrite_TestFlags)

/* --- What the scene does with the letter at its end --- */

/* func_ov122_0229effc: the taboo words filtered out of the header, the footer and the body. */
void LetterWrite_FilterTaboo(LetterWriteScene *self)
{
    LetterWrite_FilterTabooText(self, self->letter->header, LETTER_HEADER_CHARS);
    LetterWrite_FilterTabooText(self, self->letter->footer, LETTER_FOOTER_CHARS);
    LetterWrite_FilterTabooText(self, self->letter->body, LETTER_BODY_CHARS);
}
CLEAN_AS(func_ov122_0229effc, LetterWrite_FilterTaboo)

/* func_ov122_0229f034: one text carried into 8-bit characters for the taboo filter and, when the
 * filter changed it, back into the text. */
void LetterWrite_FilterTabooText(LetterWriteScene *self, u16 *text, int count)
{
    TextBase_SetWide(&self->filter_wide, text, count);
    TextBase_WideToBytes((TextBase *) (void *) &self->filter_text, (WideTextBase *) (void *) &self->filter_wide, 0, 0);
    if (MessageReader_FilterTaboo(&self->filter_text) != 0) {
        TextBase_BytesToWide((WideTextBase *) (void *) &self->filter_wide, (TextBase *) (void *) &self->filter_text);
        TextString_CopyWideOut((TextObject *) (void *) &self->filter_wide, text, count);
    }
}
CLEAN_AS(func_ov122_0229f034, LetterWrite_FilterTabooText)

/* func_ov122_0229f088: the letter's header and footer kept as the current player's defaults. */
void LetterWrite_SaveDefaults(LetterWriteScene *self)
{
    u8 *defaults = PlayerPockets_LetterDefaults(PlayerRecord_Pockets(PlayerRecords_Current()));
    LetterDefaults_Save((LetterDefaults *) (void *) defaults, self->letter);
}
CLEAN_AS(func_ov122_0229f088, LetterWrite_SaveDefaults)

/* --- The choice, the panel and the pointer --- */

/* func_ov122_0229f0a8: the choice closed, with sound 0x28, its row given up. */
void LetterWrite_CloseChoice(LetterWriteScene *self)
{
    SoundSys_PlaySe(0x28);
    self->choice_row = 0x0f;
    PagedChoice_RequestClose(letter_write_choice(self), 1);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_CLOSING);
    LetterWrite_HidePointer(self);
}
CLEAN_AS(func_ov122_0229f0a8, LetterWrite_CloseChoice)

/* func_ov122_0229f0dc: the choice opened at `choice_page`. */
void LetterWrite_OpenChoicePage(LetterWriteScene *self, int wipe)
{
    PagedChoice_OpenPageCentered(letter_write_choice(self), self->choice_page, wipe);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_OPENING);
}
CLEAN_AS(func_ov122_0229f0dc, LetterWrite_OpenChoicePage)

/* func_ov122_0229f104: the pointer moved to the choice's row in two steps; the choice by the
 * buttons after. */
void LetterWrite_GlideToChoiceRow(LetterWriteScene *self)
{
    int x = PagedChoice_TextX(letter_write_choice(self));
    int y = PagedChoice_RowY(letter_write_choice(self), self->choice_row);
    Glider_MoveTo(&self->pointer, x, y, 2);
    self->return_sub_state = LETTER_WRITE_SUB_CHOICE_KEYS;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov122_0229f104, LetterWrite_GlideToChoiceRow)

/* func_ov122_0229f150 */
void LetterWrite_PointerFirstOfSet(LetterWriteScene *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    letter_write_update_pointer(self);
}
CLEAN_AS(func_ov122_0229f150, LetterWrite_PointerFirstOfSet)

/* func_ov122_0229f170: the keyboard's pressed keys released, the pointer at the third of its set. */
void LetterWrite_BeginSub0A(LetterWriteScene *self)
{
    func_ov095_0229cce0(self->keyboard);
    Glider_ShowThirdOfSet(&self->pointer);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_0A);
}
CLEAN_AS(func_ov122_0229f170, LetterWrite_BeginSub0A)

/* func_ov122_0229f194 */
void LetterWrite_BeginSub08(LetterWriteScene *self)
{
    Glider_ShowSecondOfSet(&self->pointer);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_08);
}
CLEAN_AS(func_ov122_0229f194, LetterWrite_BeginSub08)

/* func_ov122_0229f1b4: the pointer put at the text cursor (on the screen, so less the scroll
 * target) or at the keyboard's key. */
void LetterWrite_PlacePointer(LetterWriteScene *self)
{
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT)) {
        Glider_PlaceAt(&self->pointer, self->cursor_x, self->cursor_y - self->scroll_target);
    } else {
        int x = func_ov095_02299b7c(self->keyboard);
        int y = func_ov095_02299b38(self->keyboard);
        Glider_PlaceAt(&self->pointer, x, y);
    }
    letter_write_update_pointer(self);
}
CLEAN_AS(func_ov122_0229f1b4, LetterWrite_PlacePointer)

/* func_ov122_0229f21c: the pointer eased to (x, y); then back to this sub state. */
void LetterWrite_GlidePointerTo(LetterWriteScene *self, int x, int y)
{
    Glider_EaseToByDistance(&self->pointer, x, y, 3, 2);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov122_0229f21c, LetterWrite_GlidePointerTo)

/* func_ov122_0229f250: the pointer eased to the text cursor (then sub state 12) or to the
 * keyboard's key (then the keyboard by the buttons). */
void LetterWrite_GlidePointer(LetterWriteScene *self)
{
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT)) {
        Glider_EaseToByDistance(&self->pointer, self->cursor_x, self->cursor_y - self->scroll_target, 3, 2);
        self->return_sub_state = LETTER_WRITE_SUB_0C;
    } else {
        int x = func_ov095_02299b7c(self->keyboard);
        int y = func_ov095_02299b38(self->keyboard);
        Glider_EaseToByDistance(&self->pointer, x, y, 3, 2);
        self->return_sub_state = LETTER_WRITE_SUB_KEYS;
    }
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov122_0229f250, LetterWrite_GlidePointer)

/* func_ov122_0229f2d0 */
void LetterWrite_HidePointer(LetterWriteScene *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    letter_write_update_pointer(self);
}
CLEAN_AS(func_ov122_0229f2d0, LetterWrite_HidePointer)

/* func_ov122_0229f2f4: the pointer put back on the keyboard's key. */
void LetterWrite_PointAtKey(LetterWriteScene *self)
{
    int x, y;

    LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT);
    func_ov095_02299aec(self->keyboard);
    x = func_ov095_02299b7c(self->keyboard);
    y = func_ov095_02299b38(self->keyboard);
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    LetterWrite_PointerFirstOfSet(self);
}
CLEAN_AS(func_ov122_0229f2f4, LetterWrite_PointAtKey)

/* func_ov122_0229f348: the panel's button for `index` pressed, with its sound.
 * REQUIRES: index below 5 (the tables' length; the game passes 0-4). */
void LetterWrite_PressButton(LetterWriteScene *self, int index)
{
    ButtonPanel_Select(&self->panel, data_ov122_022a2584[index]);
    self->button = (u8) index;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_BUTTON);
    SoundSys_PlaySe(data_ov122_022a258c[index]);
}
CLEAN_AS(func_ov122_0229f348, LetterWrite_PressButton)

/* func_ov122_0229f388 */
void LetterWrite_PlaySound34(LetterWriteScene *self)
{
    (void) self;
    SoundSys_PlaySe(0x34);
}
CLEAN_AS(func_ov122_0229f388, LetterWrite_PlaySound34)

/* --- The scroll --- */

/* func_ov122_0229f394: the scroll target moved so that the cursor stands 24 to 48 pixels below
 * the top of the view. QUIRK: the target is a byte, and is not bounded to 0-0x58 here. */
void LetterWrite_ScrollToCursor(LetterWriteScene *self)
{
    int below_top = self->cursor_y - self->scroll_target;

    if (below_top < 24) {
        LetterWrite_ScrollTo(self, (unsigned char) (self->cursor_y - 24));
    } else if (below_top > 48) {
        LetterWrite_ScrollTo(self, (unsigned char) (self->cursor_y - 48));
    }
}
CLEAN_AS(func_ov122_0229f394, LetterWrite_ScrollToCursor)

/* func_ov122_0229f3c8: the scroll moved 8 pixels toward its target; the scrolling ends once
 * there. */
void LetterWrite_StepScroll(LetterWriteScene *self)
{
    if (self->scroll == self->scroll_target) {
        LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_SCROLLING);
        return;
    }
    if (self->scroll < self->scroll_target) {
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
}
CLEAN_AS(func_ov122_0229f3c8, LetterWrite_StepScroll)

/* func_ov122_0229f444 */
int LetterWrite_IsScrolling(LetterWriteScene *self)
{
    return LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_SCROLLING);
}
CLEAN_AS(func_ov122_0229f444, LetterWrite_IsScrolling)

/* func_ov122_0229f454: the scroll set to move to `target`. */
void LetterWrite_ScrollTo(LetterWriteScene *self, unsigned char target)
{
    self->scroll_target = target;
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_SCROLLING);
}
CLEAN_AS(func_ov122_0229f454, LetterWrite_ScrollTo)

/* func_ov122_0229f468: the scroll put at `scroll` at once. */
void LetterWrite_SetScroll(LetterWriteScene *self, int scroll)
{
    self->scroll = (u8) scroll;
    self->scroll_target = self->scroll;
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_SCROLLING);
}
CLEAN_AS(func_ov122_0229f468, LetterWrite_SetScroll)

static int letter_write_clamp_scroll(int scroll)
{
    if (scroll < 0) {
        scroll = 0;
    }
    if (scroll > LETTER_WRITE_SCROLL_MAX) {
        scroll = LETTER_WRITE_SCROLL_MAX;
    }
    return scroll;
}

/* func_ov122_0229f488: the scroll moved 4 pixels while up or down is held; the scroll button
 * cues when it moved. */
void LetterWrite_ScrollByKeys(LetterWriteScene *self)
{
    u8 scroll = self->scroll;
    int value = scroll;

    if (data_021fbe40.held & LETTER_WRITE_KEY_UP) {
        value = scroll - 4;
    } else if (data_021fbe40.held & LETTER_WRITE_KEY_DOWN) {
        value = scroll + 4;
    }
    value = letter_write_clamp_scroll(value);
    if (value != scroll) {
        PushButton_ScrollCue(&self->scroll_button);
    }
    LetterWrite_SetScroll(self, value);
}
CLEAN_AS(func_ov122_0229f488, LetterWrite_ScrollByKeys)

/* func_ov122_0229f4e0: the scroll follows the pen dragging the scroll button: 4 pixels for each
 * 2 pixels of the pen since the drag began. The button cues each 4 pixels of scroll. */
void LetterWrite_DragScroll(LetterWriteScene *self)
{
    int moved = (data_021f6c54 - self->drag_touch_y) >> 1;
    int scroll = letter_write_clamp_scroll(self->drag_scroll + moved * 4);
    int since_cue;

    LetterWrite_SetScroll(self, scroll);
    since_cue = self->cue_scroll - scroll;
    if (since_cue >= 4 || since_cue <= -4) {
        PushButton_ScrollCue(&self->scroll_button);
        self->cue_scroll = (u8) scroll;
    }
}
CLEAN_AS(func_ov122_0229f4e0, LetterWrite_DragScroll)

/* func_ov122_0229f540: a drag of the scroll button begun when the pen is on it. */
int LetterWrite_StartDrag(LetterWriteScene *self)
{
    if (PushButton_Contains(&self->scroll_button, data_021f6c58, data_021f6c54)) {
        self->drag_touch_y = data_021f6c54;
        self->drag_scroll = self->scroll;
        self->cue_scroll = self->scroll;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov122_0229f540, LetterWrite_StartDrag)

/* --- The cursor --- */

/* func_ov122_0229f590: the cursor put at `position`, drawn at once (the blink restarts shown). */
void LetterWrite_SetPosition(LetterWriteScene *self, unsigned char position)
{
    self->position = position;
    self->blink = 0x10;
}
CLEAN_AS(func_ov122_0229f590, LetterWrite_SetPosition)

/* func_ov122_0229f5a0: the cursor's character in the header: after the name it counts from
 * `header_line`. */
unsigned char LetterWrite_HeaderPosition(LetterWriteScene *self)
{
    if (self->part == LETTER_WRITE_PART_HEADER_AFTER) {
        return (unsigned char) (self->position + self->letter->header_line);
    }
    return self->position;
}
CLEAN_AS(func_ov122_0229f5a0, LetterWrite_HeaderPosition)

/* func_ov122_0229f5c8: the characters of the cursor's part (0 for no part). */
int LetterWrite_PartCapacity(LetterWriteScene *self)
{
    switch (self->part) {
        case LETTER_WRITE_PART_HEADER:
        case LETTER_WRITE_PART_HEADER_AFTER:
            return LETTER_HEADER_CHARS;
        case LETTER_WRITE_PART_BODY:
            return LETTER_BODY_CHARS;
        case LETTER_WRITE_PART_FOOTER:
            return LETTER_FOOTER_CHARS;
    }
    return 0;
}
CLEAN_AS(func_ov122_0229f5c8, LetterWrite_PartCapacity)

/* func_ov122_0229f5f8: the address of the text of the cursor's part, the whole header for both
 * of its parts (0 for no part). */
int LetterWrite_PartTextAddress(LetterWriteScene *self)
{
    switch (self->part) {
        case LETTER_WRITE_PART_HEADER:
        case LETTER_WRITE_PART_HEADER_AFTER:
            return (int) (uintptr_t) self->letter->header;
        case LETTER_WRITE_PART_BODY:
            return (int) (uintptr_t) self->letter->body;
        case LETTER_WRITE_PART_FOOTER:
            return (int) (uintptr_t) self->letter->footer;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov122_0229f5f8, LetterWrite_PartTextAddress)

/* func_ov122_0229f634: the text of the cursor's part, from `header_line` after the name (NULL
 * for no part). */
u16 *LetterWrite_PartText(LetterWriteScene *self)
{
    switch (self->part) {
        case LETTER_WRITE_PART_HEADER:
            return self->letter->header;
        case LETTER_WRITE_PART_HEADER_AFTER:
            return letter_write_header_from(self->letter, self->letter->header_line);
        case LETTER_WRITE_PART_BODY:
            return self->letter->body;
        case LETTER_WRITE_PART_FOOTER:
            return self->letter->footer;
        default:
            return NULL;
    }
}
CLEAN_AS(func_ov122_0229f634, LetterWrite_PartText)

/* func_ov122_0229f684: the cursor moved by the d-pad's repeated keys. Up and down move between
 * the header (line -1), the body's lines (0-3) and the footer (line 4); left and right move by
 * a character, from the end of the header's first part to its second and back. When the part
 * would change and `across_parts` is 0, nothing moves. Gives 1 when the cursor moved.
 * REQUIRES: `part` is a LetterWritePart: with another, right reads a length the ROM's code
 * never set (here: no room to move). */
int LetterWrite_MoveCursorByKeys(LetterWriteScene *self, int keys, int across_parts)
{
    u8 part;
    u8 position;
    s32 x;
    int line;
    int start;
    int end_line;
    int length = 0;

    if (keys == 0) {
        return 0;
    }

    part = self->part;
    position = self->position;
    end_line = (int) LetterView_EndLine(&self->view);

    switch (part) {
        case LETTER_WRITE_PART_HEADER:
        case LETTER_WRITE_PART_HEADER_AFTER:
            line = -1;
            start = line;
            if (KeyRepeat_HasDown(keys)) {
                line = 0;
            }
            break;
        case LETTER_WRITE_PART_BODY:
            line = (self->cursor_y - 0x40) >> 4;
            start = line;
            if (KeyRepeat_HasUp(keys)) {
                line--;
            } else if (KeyRepeat_HasDown(keys)) {
                line++;
                if (line > end_line) {
                    line = 4;
                }
            }
            break;
        case LETTER_WRITE_PART_FOOTER:
            line = 4;
            start = line;
            if (KeyRepeat_HasUp(keys)) {
                line--;
            }
            break;
        default:
            line = 0;
            start = line;
            break;
    }

    x = self->cursor_x;
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_NO_HEADER) && line == -1) {
        line = 0;
    }

    /* A new line: the character under the cursor's x there. */
    if (line != start) {
        if (line == -1) {
            position = LetterWrite_HeaderPositionAt(self, x, &part);
        } else if (line >= 4) {
            part = LETTER_WRITE_PART_FOOTER;
            position = (u8) LetterWrite_FooterPositionAt(self, &x);
        } else {
            part = LETTER_WRITE_PART_BODY;
            position = LetterWrite_BodyPositionAt(self, line, &x);
        }
    }

    if (KeyRepeat_HasLeft(keys)) {
        if (position != 0) {
            position = (u8) (position - 1);
        } else if (part == LETTER_WRITE_PART_HEADER_AFTER) {
            position = self->letter->header_line;
            part = LETTER_WRITE_PART_HEADER;
        }
    } else if (KeyRepeat_HasRight(keys)) {
        switch (part) {
            case LETTER_WRITE_PART_HEADER:
                length = self->letter->header_line;
                break;
            case LETTER_WRITE_PART_HEADER_AFTER:
                length = func_02051c8c_unk(self->letter->header, LETTER_HEADER_CHARS) - self->letter->header_line;
                break;
            case LETTER_WRITE_PART_BODY:
                length = func_02051c8c_unk(self->letter->body, LETTER_BODY_CHARS);
                break;
            case LETTER_WRITE_PART_FOOTER:
                length = func_02051c8c_unk(self->letter->footer, LETTER_FOOTER_CHARS);
                break;
        }
        if (position + 1 <= length) {
            position = (u8) (position + 1);
        } else if (part == LETTER_WRITE_PART_HEADER) {
            position = 0;
            part = LETTER_WRITE_PART_HEADER_AFTER;
        }
    }

    if (part != self->part && across_parts == 0) {
        return 0;
    }
    if (part == self->part && position == self->position) {
        return 0;
    }
    self->part = part;
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);
    LetterWrite_SetPosition(self, position);
    return 1;
}
CLEAN_AS(func_ov122_0229f684, LetterWrite_MoveCursorByKeys)

/* func_ov122_0229f89c: the marked characters deleted from the cursor's part; the cursor at the
 * first of them. Deleting before the name moves the name back; after it, the range counts
 * from `header_line`.
 * REQUIRES: `part` is a LetterWritePart (with another the deletion writes to address 0). */
void LetterWrite_DeleteMarked(LetterWriteScene *self)
{
    unsigned int from = self->mark_from;
    unsigned int to = self->mark_to;
    unsigned int low, high;
    int text;
    int length;
    u8 position;

    if (from > to) {
        low = to;
        high = from;
    } else {
        low = from;
        high = to;
    }

    text = LetterWrite_PartTextAddress(self);
    length = LetterWrite_PartCapacity(self);

    switch (self->part) {
        case LETTER_WRITE_PART_HEADER:
            self->letter->header_line = (u8) (self->letter->header_line - (high - low));
            break;
        case LETTER_WRITE_PART_HEADER_AFTER: {
            u8 line = self->letter->header_line;
            low += line;
            high += line;
            break;
        }
        default:
            break;
    }

    position = (u8) func_ov095_0229bbc0(letter_write_keyboard_arg(self), (unsigned short *) (uintptr_t) text, (int) low,
                                        (int) high, length);
    if (self->part == LETTER_WRITE_PART_HEADER_AFTER) {
        position = (u8) (position - self->letter->header_line);
    }
    LetterWrite_SetPosition(self, position);
    LetterWrite_EndMark(self);
}
CLEAN_AS(func_ov122_0229f89c, LetterWrite_DeleteMarked)

/* func_ov122_0229f940 */
void LetterWrite_EndMark(LetterWriteScene *self)
{
    self->mark_from = 0;
    self->mark_to = 0;
    LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_MARKING);
}
CLEAN_AS(func_ov122_0229f940, LetterWrite_EndMark)

/* func_ov122_0229f958: a range of at least one character is marked. */
int LetterWrite_HasMark(LetterWriteScene *self)
{
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_MARKING) == 0 || self->mark_from == self->mark_to) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov122_0229f958, LetterWrite_HasMark)

/* func_ov122_0229f980: the character before the cursor (0 at its part's start).
 * REQUIRES: `part` is a LetterWritePart when `position` is not 0. */
unsigned short LetterWrite_CharBeforeCursor(LetterWriteScene *self)
{
    if (self->position == 0) {
        return 0;
    }
    return LetterWrite_PartText(self)[self->position - 1];
}
CLEAN_AS(func_ov122_0229f980, LetterWrite_CharBeforeCursor)

/* func_ov122_0229f9a8: the cursor's place on the letter worked out from its character, then the
 * scroll kept on it. */
void LetterWrite_PlaceCursor(LetterWriteScene *self)
{
    switch (self->part) {
        case LETTER_WRITE_PART_HEADER:
        case LETTER_WRITE_PART_HEADER_AFTER:
            LetterWrite_PlaceCursorInHeader(self);
            break;
        case LETTER_WRITE_PART_BODY:
            LetterWrite_PlaceCursorInBody(self);
            break;
        case LETTER_WRITE_PART_FOOTER:
            LetterWrite_PlaceCursorInFooter(self);
            break;
    }
    LetterWrite_ScrollToCursor(self);
}
CLEAN_AS(func_ov122_0229f9a8, LetterWrite_PlaceCursor)

/* func_ov122_0229f9e8: in the footer, which ends at x 0xd0 (0x30 + 0xa0): the characters before
 * the cursor plus the room the footer leaves on its left. Gives the y, 0x88.
 * QUIRK: the characters' width is cut to a byte (with the 0x30) before the room is added. */
int LetterWrite_PlaceCursorInFooter(LetterWriteScene *self)
{
    int before = TextString_Width(self->letter->footer, self->position);
    int width;

    self->cursor_x = (u8) (before + 0x30);
    width = TextString_Width(self->letter->footer, LETTER_FOOTER_CHARS);
    self->cursor_x = self->cursor_x + (0xa0 - width);
    self->cursor_y = 0x88;
    return 0x88;
}
CLEAN_AS(func_ov122_0229f9e8, LetterWrite_PlaceCursorInFooter)

/* func_ov122_0229fa34: in the body: on the line that holds the cursor's character, after the
 * characters of that line before it. QUIRK: x is cut to a byte. */
void LetterWrite_PlaceCursorInBody(LetterWriteScene *self)
{
    int line = LetterView_LineOf(&self->view, self->position);
    s32 start;

    self->cursor_y = line * 16 + 0x40;
    start = LetterView_LineStarts(&self->view)[line];
    self->cursor_x = (u8) (TextString_Width(self->letter->body + start, self->position - start) + 0x30);
}
CLEAN_AS(func_ov122_0229fa34, LetterWrite_PlaceCursorInBody)

/* func_ov122_0229fa90: in the header's line as the view shows it: after the name, the name's
 * characters count too. QUIRK: x is cut to a byte. */
void LetterWrite_PlaceCursorInHeader(LetterWriteScene *self)
{
    int shown = self->position;

    if (self->part == LETTER_WRITE_PART_HEADER_AFTER) {
        int name_length = (int) LetterView_NameLength(&self->view);
        shown += self->letter->header_line + name_length;
    }
    self->cursor_x = (u8) (TextString_Width(self->shown_header, shown) + 0x30);
    self->cursor_y = 0x28;
}
CLEAN_AS(func_ov122_0229fa90, LetterWrite_PlaceCursorInHeader)

/* func_ov122_0229fae8: the cursor put where the letter is touched at (x, y): above y 0x3c the
 * header (unless LETTER_WRITE_FLAG_NO_HEADER), below 0x84 the footer, else the body (y kept in
 * 0x40-0x7f); then the scroll kept on it. */
void LetterWrite_TouchAt(LetterWriteScene *self, int x, int y, int below_to_footer)
{
    if (!LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_NO_HEADER) && y < 0x3c) {
        self->cursor_x = x;
        LetterWrite_EnterHeader(self);
    } else if (y < 0x84) {
        if (y < 0x40) {
            y = 0x40;
        } else if (y >= 0x80) {
            y = 0x7f;
        }
        self->cursor_x = x;
        self->cursor_y = y;
        LetterWrite_EnterBody(self, below_to_footer);
    } else {
        self->cursor_x = x;
        LetterWrite_EnterFooter(self);
    }
    LetterWrite_ScrollToCursor(self);
}
CLEAN_AS(func_ov122_0229fae8, LetterWrite_TouchAt)

/* func_ov122_0229fb54: the end of the marked range follows the pen, within the cursor's part (a
 * pen past the header's part puts it at that part's end). Gives 1 when the cursor moved. */
int LetterWrite_DragMark(LetterWriteScene *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;
    u8 old_position = self->position;
    u8 part;

    if (x < 0x30) {
        x = 0x30;
    }
    y += self->scroll_target;
    part = self->part;

    switch (part) {
        case LETTER_WRITE_PART_HEADER:
        case LETTER_WRITE_PART_HEADER_AFTER:
            self->cursor_x = x;
            LetterWrite_EnterHeader(self);
            if (self->part == part) {
                break;
            }
            self->part = part;
            LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);
            if (part == LETTER_WRITE_PART_HEADER) {
                LetterWrite_SetPosition(self, self->letter->header_line);
            } else {
                LetterWrite_SetPosition(self, 0);
            }
            LetterWrite_PlaceCursorInHeader(self);
            break;
        case LETTER_WRITE_PART_BODY:
            self->cursor_x = x;
            self->cursor_y = y;
            LetterWrite_EnterBody(self, 0);
            break;
        case LETTER_WRITE_PART_FOOTER:
            self->cursor_x = x;
            LetterWrite_EnterFooter(self);
            break;
    }

    self->mark_to = self->position;
    return self->position != old_position ? 1 : 0;
}
CLEAN_AS(func_ov122_0229fb54, LetterWrite_DragMark)

/* func_ov122_0229fc2c */
void LetterWrite_Nothing(LetterWriteScene *self)
{
    (void) self;
}
CLEAN_AS(func_ov122_0229fc2c, LetterWrite_Nothing)

/* func_ov122_0229fc30: the pen put down on the letter (x 0x20-0xdf, the y below 0x50 on the
 * screen): the cursor put there and a mark begun at it. Gives 1 when it was on the letter. */
int LetterWrite_StartTouch(LetterWriteScene *self)
{
    int x = data_021f6c58;
    int y = data_021f6c54;

    /* QUIRK: the y is a byte, never below 0. */
    if (y < 0) {
        return 0;
    }
    if (y > 0x4f) {
        y = 0x4f;
    }
    y += self->scroll_target;
    if (x < 0x20 || x >= 0xe0) {
        return 0;
    }
    if (x < 0x30) {
        x = 0x30;
    }
    LetterWrite_TouchAt(self, x, y, 1);
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_MARKING);
    self->mark_from = self->position;
    self->mark_to = self->position;
    return 1;
}
CLEAN_AS(func_ov122_0229fc30, LetterWrite_StartTouch)

/* func_ov122_0229fc9c: the footer's character under *x, and *x set to where the cursor is drawn
 * before it. Left of the footer (which is right-aligned) the first. */
int LetterWrite_FooterPositionAt(LetterWriteScene *self, s32 *x)
{
    u8 index;
    u8 at = (u8) (*x - 0x30);
    int room = 0xa0 - TextString_Width(self->letter->footer, LETTER_FOOTER_CHARS);

    if (room > at) {
        index = 0;
        *x = room + 0x30;
    } else {
        int before = func_ov095_0229bb34(letter_write_keyboard_arg(self), self->letter->footer, LETTER_FOOTER_CHARS, 0xa0,
                                         (u8) (at - room), &index);
        *x = room + before + 0x30;
    }
    return index;
}
CLEAN_AS(func_ov122_0229fc9c, LetterWrite_FooterPositionAt)

/* func_ov122_0229fcfc: the cursor put in the footer, under `cursor_x`. */
void LetterWrite_EnterFooter(LetterWriteScene *self)
{
    int position;

    self->part = LETTER_WRITE_PART_FOOTER;
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);
    self->cursor_y = 0x88;
    position = LetterWrite_FooterPositionAt(self, &self->cursor_x);
    LetterWrite_SetPosition(self, (unsigned char) position);
}
CLEAN_AS(func_ov122_0229fcfc, LetterWrite_EnterFooter)

/* func_ov122_0229fd34: the character of body line `line` under *x, and *x set to where the
 * cursor is drawn before it. */
unsigned char LetterWrite_BodyPositionAt(LetterWriteScene *self, int line, s32 *x)
{
    s32 start = LetterView_LineStarts(&self->view)[line];
    u8 index;
    int before =
        func_ov095_0229bb34(letter_write_keyboard_arg(self), self->letter->body + start, 0x28, 0xa0, (u8) (*x - 0x30), &index);

    *x = before + 0x30;
    return (unsigned char) (index + start);
}
CLEAN_AS(func_ov122_0229fd34, LetterWrite_BodyPositionAt)

/* func_ov122_0229fd88: the cursor put in the body, at (`cursor_x`, `cursor_y`), on the last line
 * written at most. With `below_to_footer`, a touch below the last line written goes to the
 * footer instead when that line is less than 8 pixels below the top of the view. */
void LetterWrite_EnterBody(LetterWriteScene *self, int below_to_footer)
{
    int line;
    int end_line;
    unsigned char position;

    self->part = LETTER_WRITE_PART_BODY;
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);

    if (self->cursor_y < 0x40) {
        self->cursor_y = 0x40;
    }
    if (self->cursor_y >= 0x80) {
        self->cursor_y = 0x7f;
    }

    line = (self->cursor_y - 0x40) >> 4;
    end_line = (int) LetterView_EndLine(&self->view);
    if (line > end_line) {
        line = end_line;
    } else {
        below_to_footer = 0;
    }
    self->cursor_y = line * 16 + 0x40;

    if (below_to_footer != 0 && self->cursor_y - self->scroll < 8) {
        LetterWrite_EnterFooter(self);
        return;
    }

    position = LetterWrite_BodyPositionAt(self, line, &self->cursor_x);
    LetterWrite_SetPosition(self, position);
}
CLEAN_AS(func_ov122_0229fd88, LetterWrite_EnterBody)

/* func_ov122_0229fe28: the header's character under x, as the view shows the header: before
 * the middle of the name, the first part (at most its end, `header_line`); from it on, the
 * second (counted after the name). *part is set to which. */
u8 LetterWrite_HeaderPositionAt(LetterWriteScene *self, int x, u8 *part)
{
    u8 index;
    int line;
    int after_name;
    int middle;

    func_ov095_0229bb34(letter_write_keyboard_arg(self), self->shown_header, LETTER_WRITE_SHOWN_HEADER_CHARS, 0xa0,
                        (u8) (x - 0x30), &index);

    line = self->letter->header_line;
    after_name = (int) LetterView_NameLength(&self->view) + line;
    middle = (line + after_name) >> 1;

    if (index < middle) {
        *part = LETTER_WRITE_PART_HEADER;
        if (index > line) {
            index = (u8) line;
        }
    } else {
        *part = LETTER_WRITE_PART_HEADER_AFTER;
        if (index < after_name) {
            index = 0;
        } else {
            index = (u8) (index - after_name);
        }
    }
    return index;
}
CLEAN_AS(func_ov122_0229fe28, LetterWrite_HeaderPositionAt)

/* func_ov122_0229fea4: the cursor put in the header, under `cursor_x`. */
void LetterWrite_EnterHeader(LetterWriteScene *self)
{
    u8 position = LetterWrite_HeaderPositionAt(self, self->cursor_x, &self->part);

    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);
    LetterWrite_SetPosition(self, position);
    LetterWrite_PlaceCursorInHeader(self);
}
CLEAN_AS(func_ov122_0229fea4, LetterWrite_EnterHeader)

/* func_ov122_0229fedc: the cursor shown at the body's start, no mark, the keyboard reset. */
void LetterWrite_Start(LetterWriteScene *self)
{
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_CURSOR_SHOWN);
    self->cursor_x = 0x30;
    self->cursor_y = 0x40;
    self->part = LETTER_WRITE_PART_BODY;
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);
    LetterWrite_SetPosition(self, 0);
    LetterWrite_EndMark(self);
    func_ov095_0229cd30(letter_write_keyboard_arg(self));
    func_ov122_022a14c0(self);
}
CLEAN_AS(func_ov122_0229fedc, LetterWrite_Start)

/* --- Sub states begun --- */

/* func_ov122_0229ff2c: the choice by the buttons, the pointer at its last row. */
void LetterWrite_BeginChoiceKeys(LetterWriteScene *self)
{
    int x, y;

    MenuScene_ResetKeyRepeat(letter_write_scene(self));
    LetterWrite_PointAtKey(self);
    self->choice_row = (u8) (PagedChoice_RowCount(letter_write_choice(self)) - 1);
    x = PagedChoice_TextX(letter_write_choice(self));
    y = PagedChoice_RowY(letter_write_choice(self), self->choice_row);
    Glider_PlaceAt(&self->pointer, x, y);
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_B);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_KEYS);
}
CLEAN_AS(func_ov122_0229ff2c, LetterWrite_BeginChoiceKeys)

/* func_ov122_0229ff94 */
void LetterWrite_BeginChoiceTouch(LetterWriteScene *self)
{
    LetterWrite_HidePointer(self);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_TOUCH);
}
CLEAN_AS(func_ov122_0229ff94, LetterWrite_BeginChoiceTouch)

/* func_ov122_0229ffac: the panel by the buttons, the pointer at its button 4. */
void LetterWrite_BeginPanelKeys(LetterWriteScene *self)
{
    int x, y;

    MenuScene_ResetKeyRepeat(letter_write_scene(self));
    LetterWrite_PointAtKey(self);
    x = ButtonPanel_ButtonX(&self->panel, 4);
    y = ButtonPanel_ButtonY(&self->panel, 4);
    Glider_PlaceAt(&self->pointer, x, y);
    self->choice_row = 1;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_PANEL_KEYS);
}
CLEAN_AS(func_ov122_0229ffac, LetterWrite_BeginPanelKeys)

/* func_ov122_022a0000 */
void LetterWrite_BeginSub04(LetterWriteScene *self)
{
    LetterWrite_HidePointer(self);
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_04);
}
CLEAN_AS(func_ov122_022a0000, LetterWrite_BeginSub04)

/* func_ov122_022a0018: the input by the pen (func_ov122_022a0054) or by the buttons, as main's
 * state flag 2 says. */
unsigned char *LetterWrite_BeginInput(LetterWriteScene *self)
{
    if (StateFlags_IsClear2()) {
        return func_ov122_022a0054(self);
    }
    return LetterWrite_BeginKeys(self);
}
CLEAN_AS(func_ov122_022a0018, LetterWrite_BeginInput)

/* func_ov122_022a0038: the keyboard by the buttons, the pointer on its key. */
unsigned char *LetterWrite_BeginKeys(LetterWriteScene *self)
{
    MenuScene_ResetKeyRepeat(letter_write_scene(self));
    LetterWrite_PointAtKey(self);
    return MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_KEYS);
}
CLEAN_AS(func_ov122_022a0038, LetterWrite_BeginKeys)
