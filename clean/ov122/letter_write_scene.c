/* The letter writing scene of overlay 122 (letter_write_scene.h): its destructors, its flags,
 * the taboo filter and the defaults kept at the end, the pointer sprite, the scroll, and the
 * text cursor: where it is drawn, where a touch or the d-pad puts it, and the marked range. */
#include "letter_write_scene.h"

#include "autoload_2/input.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/dual_cell_sprite.h"
#include "main/group_params.h"
#include "main/layer_load_task.h"
#include "main/message_reader.h"
#include "main/oam_buffer.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "main/text_base.h"
#include "main/text_string.h"
#include "ov002/key_repeat.h"
#include "ov002/paper.h"
#include "ov004/member_pointer.h"

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
static_assert(offsetof(LetterWriteScene, unk_a4) == 0xa4 && offsetof(LetterWriteScene, clipboard) == 0x4230, "clipboard");
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
    LetterWrite_UpdateKeys(self);
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

/* func_ov122_022a0018: the input by the pen (LetterWrite_BeginTouch) or by the buttons, as main's
 * state flag 2 says. */
unsigned char *LetterWrite_BeginInput(LetterWriteScene *self)
{
    if (StateFlags_IsClear2()) {
        return LetterWrite_BeginTouch(self);
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

/* --- The keyboard of overlay 95, the scene's input and its sub states --- */

/* The buttons (main's PadState bits). */
#define LETTER_WRITE_PAD_A 0x0001
#define LETTER_WRITE_PAD_B 0x0002
#define LETTER_WRITE_PAD_START 0x0008
#define LETTER_WRITE_PAD_R 0x0100
#define LETTER_WRITE_PAD_L 0x0200
#define LETTER_WRITE_PAD_Y 0x0800

/* The pen: down, and down or up since the frame before. */
extern u8 data_021fbdd8;
extern u8 data_021fbddc;

/* The heap the scene loads its files with. */
extern Heap *data_021fbe94;

/* The scene's files: the palettes, the keyboard's screen and the characters. */
extern const char data_ov122_022a2798[]; /* "menu/chat2/b_cht_bg.bpl" */
extern const char data_ov122_022a27b0[]; /* "menu/chat2/b_key0.bsc" */
extern const char data_ov122_022a27c8[]; /* "menu/chat2/b_cht.bch" */

/* The panel's buttons at the panel cursor's two places ({3, 4}). */
extern const u8 data_ov122_022a2580[];

/* The keyboard (overlay 95; no Clean version yet). Its keys are numbered; a key has a code
 * (func_ov095_0229c448) and can be disabled (a bit of its word 0x20). */
extern void func_ov095_022999e8(void *keyboard); /* sound 23 */
extern void func_ov095_022999f4(void *keyboard); /* sound 22 */
/* The key its cursor is on, -1 when that key cannot be pressed now. */
extern int func_ov095_02299a00(void *keyboard);
/* The cursor moved by the d-pad keys: 1-3 when it leaves the keys toward the text (the
 * pointer's turn), 0 or 4 otherwise. */
extern int func_ov095_02299a54(void *keyboard, int keys);
extern int func_ov095_0229aff0(void *keyboard); /* a mode tab under the pen: the mode changed, 1 */
extern int func_ov095_0229b324(void *keyboard); /* its screen's files loaded */
extern void func_ov095_0229b388(int keyboard);  /* its flag 2 cleared */
extern void func_ov095_0229b394(int keyboard);  /* its flag 2 set */
/* A character being composed taken back (0 when there was none to take back). */
extern int func_ov095_0229b3a0(void *keyboard, u16 *text, int position);
extern void func_ov095_0229b3ec(void *keyboard); /* the composition dropped */
/* A code of the keyboard's own (the modes, the composition): what it did, 0 for none. */
extern int func_ov095_0229ba44(void *keyboard, int code, int layer);
extern int func_ov095_0229bb94(void *keyboard, int character); /* the conversions: 0 for none */
extern int func_ov095_0229bb98(void *keyboard, int character);
extern int func_ov095_0229bb9c(void *keyboard, int character);
/* The character before `position` replaced. */
extern int func_ov095_0229bba0(int keyboard, unsigned short *text, int character, int position);
/* A character put into the body at *position, its lines broken as the view breaks them; with
 * `test_only` the text is left as it was. 1 when it fits. */
extern int func_ov095_0229bc00(void *keyboard, u16 *text, int character, u8 *position, int length, int max_chars, int lines,
                               int width, int test_only, int notify);
/* A character put into a one-line text at *position, at most `width` pixels wide. */
extern int func_ov095_0229bcec(void *keyboard, u16 *text, int character, u8 *position, int length, int width, int p6,
                               int notify);
extern int func_ov095_0229bebc(void *keyboard, int code);            /* the code is a command (0x100-0x123) */
extern void func_ov095_0229bed8(void *keyboard, int character);      /* key 6 enabled */
extern void func_ov095_0229bee4(void *keyboard);                     /* keys 6, 3, 4 and 5 disabled */
extern int func_ov095_0229bf0c(void *keyboard);                      /* a held key's repeat is due */
extern void func_ov095_0229bf3c(void *keyboard);                     /* a held key's repeat started */
extern int func_ov095_0229bf48(void *keyboard);                      /* the pressed key shown: 1 while it shows */
extern void func_ov095_0229bf7c(void *keyboard, unsigned int layer); /* drawn */
extern void func_ov095_0229bfd8(void *keyboard, int layer);
extern int func_ov095_0229c000(void *keyboard, const char *path);
extern void func_ov095_0229c050(int keyboard); /* its flag 8 set */
extern void func_ov095_0229c05c(void *keyboard);
extern void func_ov095_0229c084(void *keyboard, int mode);
extern void func_ov095_0229c22c(void *keyboard, int state, unsigned int layer, int p3);
extern int func_ov095_0229c448(void *keyboard, int key, unsigned int mode); /* the key's code */
extern int func_ov095_0229c548(void *keyboard);                             /* the key held down */
extern int func_ov095_0229c54c(void *keyboard, int x, u8 y);                /* the key at (x, y), or -1 */
extern void func_ov095_0229c8e4(int keyboard, int key);                     /* the key shown pressed */
extern int func_ov095_0229cda4(void *keyboard, int key);                    /* the key (-1: the cursor's) is 0x104-0x108 */
extern void func_ov095_0229ce84(void *keyboard, int key);                   /* the key enabled */
extern void func_ov095_0229cef4(void *keyboard, int key);                   /* the key disabled */
extern int func_ov095_0229cf64(void *keyboard, int key);                    /* the key is disabled */

#define LETTER_WRITE_KEY_NEWLINE 0 /* the keyboard's keys the scene enables */
#define LETTER_WRITE_KEY_6 6
#define LETTER_WRITE_KEY_COPY 11
#define LETTER_WRITE_KEY_PASTE 12
#define LETTER_WRITE_KEY_L 0x109 /* the keys shown pressed by L and R */
#define LETTER_WRITE_KEY_R 0x10a

static CellLayerSprite *letter_write_pointer_cells(LetterWriteScene *self)
{
    /* The pointer's base is main's cell layer sprite (glide.h). */
    return (CellLayerSprite *) (void *) &self->pointer;
}

static DualCellSprite *letter_write_button_cells(LetterWriteScene *self)
{
    /* The scroll button's base is main's second sprite class (push_button.h). */
    return (DualCellSprite *) (void *) &self->scroll_button;
}

static const LetterViewLetter *letter_write_view_letter(LetterWriteScene *self)
{
    return (const LetterViewLetter *) (const void *) self->letter;
}

/* func_ov122_022a0054: the input by the pen, the pointer hidden. */
unsigned char *LetterWrite_BeginTouch(LetterWriteScene *self)
{
    LetterWrite_HidePointer(self);
    return MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_TOUCH);
}
CLEAN_AS(func_ov122_022a0054, LetterWrite_BeginTouch)

/* func_ov122_022a006c: Start pressed: the panel's button 1. */
int LetterWrite_StartKey(LetterWriteScene *self)
{
    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_START) == 0) {
        return 0;
    }
    LetterWrite_HidePointer(self);
    LetterWrite_PressButton1(self);
    return 1;
}
CLEAN_AS(func_ov122_022a006c, LetterWrite_StartKey)

/* func_ov122_022a0098: L pressed: the marked characters copied, when the copy key is enabled;
 * then until L is let go. */
int LetterWrite_CopyKey(LetterWriteScene *self)
{
    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_L) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(self->keyboard, LETTER_WRITE_KEY_COPY) != 0) {
        return 0;
    }
    LetterWrite_Command(self, LETTER_WRITE_CODE_COPY);
    func_ov095_0229c8e4(letter_write_keyboard_arg(self), LETTER_WRITE_KEY_L);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_WHILE_L);
    return 1;
}
CLEAN_AS(func_ov122_022a0098, LetterWrite_CopyKey)

/* func_ov122_022a00fc: R pressed: the copied text pasted, when the paste key is enabled; then
 * until R is let go. */
int LetterWrite_PasteKey(LetterWriteScene *self)
{
    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_R) == 0) {
        return 0;
    }
    if (func_ov095_0229cf64(self->keyboard, LETTER_WRITE_KEY_PASTE) != 0) {
        return 0;
    }
    LetterWrite_Command(self, LETTER_WRITE_CODE_PASTE);
    func_ov095_0229c8e4(letter_write_keyboard_arg(self), LETTER_WRITE_KEY_R);
    LetterWrite_PlacePointer(self);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_WHILE_R);
    return 1;
}
CLEAN_AS(func_ov122_022a00fc, LetterWrite_PasteKey)

/* func_ov122_022a0168: Y pressed: the pointer moves from the key to the text cursor or back.
 * QUIRK: the sub state set with the pointer's turn is replaced at once by
 * LetterWrite_GlidePointer's. */
int LetterWrite_SwitchPointerKey(LetterWriteScene *self)
{
    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_Y) == 0) {
        return 0;
    }
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT)) {
        LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT);
    } else {
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT);
        LetterWrite_ScrollToCursor(self);
    }
    if (func_ov095_0229cda4(self->keyboard, -1) != 0) {
        if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT)) {
            Glider_TurnToSetA(&self->pointer);
            MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_0C);
        } else {
            Glider_TurnToSetB(&self->pointer);
            MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_KEYS);
        }
    }
    LetterWrite_GlidePointer(self);
    return 1;
}
CLEAN_AS(func_ov122_022a0168, LetterWrite_SwitchPointerKey)

/* func_ov122_022a0204: B held: a character deleted, and again while it stays held.
 * QUIRK: B is read held, not pressed. */
int LetterWrite_BackspaceKey(LetterWriteScene *self)
{
    if ((data_021fbe40.held & LETTER_WRITE_PAD_B) == 0) {
        return 0;
    }
    LetterWrite_Command(self, LETTER_WRITE_CODE_BACKSPACE);
    func_ov095_0229bf3c(self->keyboard);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_BACKSPACE_REPEAT);
    return 1;
}
CLEAN_AS(func_ov122_022a0204, LetterWrite_BackspaceKey)

/* func_ov122_022a024c: A pressed on a key that can be pressed: the key shown pressed; its code
 * is acted on once the pointer's press has played (LETTER_WRITE_SUB_08). */
int LetterWrite_PressKeyByA(LetterWriteScene *self)
{
    int key;

    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_A) == 0) {
        return 0;
    }
    key = func_ov095_02299a00(self->keyboard);
    if (key == -1) {
        return 0;
    }
    /* QUIRK: the key's code is looked up and not used. */
    func_ov095_0229c448(self->keyboard, key, 9);
    func_ov095_0229c8e4(letter_write_keyboard_arg(self), key);
    LetterWrite_BeginSub08(self);
    return 1;
}
CLEAN_AS(func_ov122_022a024c, LetterWrite_PressKeyByA)

/* func_ov122_022a02a0 (LETTER_WRITE_SUB_ERROR): the error message shown; once it is done, the
 * input. Gives the sub state's address then (as a number), else the message's 0. */
int LetterWrite_RunError(LetterWriteScene *self)
{
    int done;

    func_ov095_0229bf48(self->keyboard);
    done = ErrorMessage_Update(&self->error, 1);
    if (done != 0) {
        return (int) (uintptr_t) LetterWrite_BeginInput(self);
    }
    return done;
}
CLEAN_AS(func_ov122_022a02a0, LetterWrite_RunError)

/* func_ov122_022a02c8 (LETTER_WRITE_SUB_BUTTON): once the pointer's press has played, the
 * panel's button plays its press with the pointer on it; then what the button does: 0 the
 * choice, 1 the taboo filter and state 6, 3 main's menu, 4 state 8. */
void LetterWrite_RunButton(LetterWriteScene *self)
{
    if (CellLayerSprite_AnimNumber(letter_write_pointer_cells(self)) != 0 &&
        CellLayerSprite_IsDone(letter_write_pointer_cells(self)) == 0) {
        return;
    }
    if (ButtonPanel_StepSelectedPress(&self->panel) != 0) {
        int frame, x;

        if (CellLayerSprite_AnimNumber(letter_write_pointer_cells(self)) == 0) {
            return;
        }
        frame = ButtonPanel_SelectedPressFrame(&self->panel);
        x = ButtonPanel_ButtonX(&self->panel, -1);
        Glider_PlaceAt(&self->pointer, frame + x, frame + ButtonPanel_ButtonY(&self->panel, -1));
        return;
    }
    switch (self->button) {
        case 0:
            self->next_state = LETTER_WRITE_STATE_CHOICE;
            LetterWrite_Leave(self);
            break;
        case 1:
            self->next_state = LETTER_WRITE_STATE_PANEL_MESSAGE;
            LetterWrite_FilterTaboo(self);
            LetterWrite_Leave(self);
            break;
        case 3:
            LetterWrite_SwitchTab(self, 0);
            break;
        case 4:
            self->base.state = LETTER_WRITE_STATE_08;
            MenuScene_SetPhase(letter_write_scene(self), 1);
            LetterWrite_Refresh(self, 1, 1);
            break;
    }
    LetterWrite_HidePointer(self);
}
CLEAN_AS(func_ov122_022a02c8, LetterWrite_RunButton)

/* func_ov122_022a03b0 (LETTER_WRITE_SUB_CHOICE_CLOSING): once the choice is closed, the row
 * picked applied to the letter: 1 a new addressee (the view's name and the whole letter
 * redrawn), 2 the choice's next page, 3 main's menu when it asked to close; else back to the
 * keyboard. */
void LetterWrite_RunChoiceClosing(LetterWriteScene *self)
{
    if (PagedChoice_IsIdle(letter_write_choice(self)) == 0) {
        return;
    }
    switch (PagedChoice_Apply(letter_write_choice(self), self->letter, self->choice_row)) {
        case 1:
            LetterView_SetName(&self->view, letter_write_view_letter(self));
            LetterWrite_Refresh(self, 1, 0);
            self->base.state = LETTER_WRITE_STATE_BACK;
            MenuScene_SetPhase(letter_write_scene(self), 1);
            break;
        case 2:
            self->choice_page = (u8) (self->choice_page + 1);
            if ((unsigned int) self->choice_page >= (unsigned int) PagedChoice_PageCount(letter_write_choice(self))) {
                self->choice_page = 0;
            }
            LetterWrite_OpenChoicePage(self, 0);
            break;
        case 3:
            if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_CLOSE_ASKED)) {
                LetterWrite_ExitMenu(self);
            } else {
                self->base.state = LETTER_WRITE_STATE_BACK;
                MenuScene_SetPhase(letter_write_scene(self), 1);
            }
            break;
        default:
            self->base.state = LETTER_WRITE_STATE_BACK;
            MenuScene_SetPhase(letter_write_scene(self), 1);
            break;
    }
}
CLEAN_AS(func_ov122_022a03b0, LetterWrite_RunChoiceClosing)

/* func_ov122_022a0488 (LETTER_WRITE_SUB_CHOICE_PICKED): once the picked row has been shown,
 * the choice closed. */
void LetterWrite_RunChoicePicked(LetterWriteScene *self)
{
    if (PagedChoice_CountDown(letter_write_choice(self)) != 0) {
        PagedChoice_RequestClose(letter_write_choice(self), 0);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_CLOSING);
        LetterWrite_HidePointer(self);
    }
}
CLEAN_AS(func_ov122_022a0488, LetterWrite_RunChoicePicked)

/* func_ov122_022a04bc (LETTER_WRITE_SUB_CHOICE_OPENING): once the choice is shown, the choice
 * by the buttons or by the pen, as main's state flag 2 says. */
void LetterWrite_RunChoiceOpening(LetterWriteScene *self)
{
    if (PagedChoice_IsShown(letter_write_choice(self)) != 0) {
        if (StateFlags_Test2()) {
            LetterWrite_BeginChoiceKeys(self);
        } else {
            LetterWrite_BeginChoiceTouch(self);
        }
    }
}
CLEAN_AS(func_ov122_022a04bc, LetterWrite_RunChoiceOpening)

/* func_ov122_022a04ec (LETTER_WRITE_SUB_CHOICE_ROW_PRESS): once the pointer's press has played,
 * the row picked. */
void LetterWrite_RunChoiceRowPress(LetterWriteScene *self)
{
    if (CellLayerSprite_IsDone(letter_write_pointer_cells(self)) != 0) {
        PagedChoice_PickRow(letter_write_choice(self), self->choice_row);
        self->choice_row = (u8) PagedChoice_Decide(letter_write_choice(self), self->choice_page, self->choice_row);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_PICKED);
    }
}
CLEAN_AS(func_ov122_022a04ec, LetterWrite_RunChoiceRowPress)

/* func_ov122_022a053c (LETTER_WRITE_SUB_CHOICE_KEYS): the choice by the buttons: the d-pad
 * moves the row, A picks it, B closes the choice; main's asking to close closes it too. */
void LetterWrite_RunChoiceKeys(LetterWriteScene *self)
{
    int keys;
    u16 pressed;

    if (StateFlags_MenuCloseAsked()) {
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_CLOSE_ASKED);
        LetterWrite_CloseChoice(self);
        return;
    }
    if (MenuScene_TakeTouch(letter_write_scene(self))) {
        LetterWrite_BeginChoiceTouch(self);
        return;
    }
    keys = (int) MenuScene_LatchRepeatedKeys(letter_write_scene(self));
    if (PagedChoice_MoveCursor(letter_write_choice(self), keys, &self->choice_row, 0)) {
        LetterWrite_GlideToChoiceRow(self);
    }
    pressed = data_021fbe40.pressed;
    if (pressed & LETTER_WRITE_PAD_A) {
        Glider_ShowSecondOfSet(&self->pointer);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_ROW_PRESS);
    } else if (pressed & LETTER_WRITE_PAD_B) {
        LetterWrite_CloseChoice(self);
    }
}
CLEAN_AS(func_ov122_022a053c, LetterWrite_RunChoiceKeys)

/* func_ov122_022a05d0 (LETTER_WRITE_SUB_PANEL_KEYS): the panel by the buttons: left and right
 * move the pointer between its buttons 3 and 4 (`choice_row` 0 and 1), A presses the one
 * pointed at, Start button 3 and B button 4. */
void LetterWrite_RunPanelKeys(LetterWriteScene *self)
{
    int keys;
    u8 old;

    if (MenuScene_TakeTouch(letter_write_scene(self)) != 0) {
        LetterWrite_BeginSub04(self);
        return;
    }
    keys = (int) MenuScene_LatchRepeatedKeys(letter_write_scene(self));
    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_A) != 0) {
        switch (self->choice_row) {
            case 0:
                LetterWrite_PressButton(self, 3);
                break;
            case 1:
                LetterWrite_PressButton(self, 4);
                break;
        }
        Glider_ShowSecondOfSet(&self->pointer);
        return;
    }
    old = self->choice_row;
    if (KeyRepeat_HasLeft(keys) != 0) {
        if (self->choice_row != 0) {
            self->choice_row = (u8) (self->choice_row - 1);
        }
    } else if (KeyRepeat_HasRight(keys) != 0) {
        if (self->choice_row < 1) {
            self->choice_row = (u8) (self->choice_row + 1);
        }
    }
    if (old != self->choice_row) {
        u8 row = self->choice_row;
        int x = ButtonPanel_ButtonX(&self->panel, data_ov122_022a2580[row]);
        int y = ButtonPanel_ButtonY(&self->panel, data_ov122_022a2580[row]);
        LetterWrite_GlidePointerTo(self, x, y);
    } else {
        u16 pressed = data_021fbe40.pressed;
        if ((pressed & LETTER_WRITE_PAD_START) != 0) {
            LetterWrite_HidePointer(self);
            LetterWrite_PressButton(self, 3);
        } else if ((pressed & LETTER_WRITE_PAD_B) != 0) {
            LetterWrite_HidePointer(self);
            LetterWrite_PressButton(self, 4);
        }
    }
}
CLEAN_AS(func_ov122_022a05d0, LetterWrite_RunPanelKeys)

/* func_ov122_022a06e8 (LETTER_WRITE_SUB_SCROLL_RELEASE): once the scroll button is back up, the
 * pointer back to the keyboard. */
void LetterWrite_RunScrollRelease(LetterWriteScene *self)
{
    if (DualCellSprite_IsDone(letter_write_button_cells(self))) {
        LetterWrite_BeginSub0A(self);
        LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_POINTER_ON_BUTTON);
    }
}
CLEAN_AS(func_ov122_022a06e8, LetterWrite_RunScrollRelease)

/* func_ov122_022a0714 (LETTER_WRITE_SUB_SCROLL_HELD): while A is held the d-pad scrolls; when
 * it is let go, the scroll button released. */
void LetterWrite_RunScrollHeld(LetterWriteScene *self)
{
    if ((data_021fbe40.held & LETTER_WRITE_PAD_A) == 0) {
        PushButton_Release(&self->scroll_button);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_SCROLL_RELEASE);
        LetterWrite_Nothing(self);
    } else {
        LetterWrite_ScrollByKeys(self);
    }
}
CLEAN_AS(func_ov122_022a0714, LetterWrite_RunScrollHeld)

/* func_ov122_022a0750 (LETTER_WRITE_SUB_SCROLL_PRESS) */
void LetterWrite_RunScrollPress(LetterWriteScene *self)
{
    if (DualCellSprite_IsDone(letter_write_button_cells(self))) {
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_SCROLL_HELD);
    }
}
CLEAN_AS(func_ov122_022a0750, LetterWrite_RunScrollPress)

/* func_ov122_022a0774 (LETTER_WRITE_SUB_WHILE_R): once R is let go, back to the sub state
 * before, the keys brought up to date. */
void LetterWrite_RunWhileR(LetterWriteScene *self)
{
    if ((data_021fbe40.held & LETTER_WRITE_PAD_R) != 0) {
        return;
    }
    MenuScene_SetSubState(letter_write_scene(self), self->return_sub_state);
    LetterWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov122_022a0774, LetterWrite_RunWhileR)

/* func_ov122_022a07a4 (LETTER_WRITE_SUB_WHILE_L) */
void LetterWrite_RunWhileL(LetterWriteScene *self)
{
    if ((data_021fbe40.held & LETTER_WRITE_PAD_L) != 0) {
        return;
    }
    MenuScene_SetSubState(letter_write_scene(self), self->return_sub_state);
    LetterWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov122_022a07a4, LetterWrite_RunWhileL)

/* func_ov122_022a07d4 (LETTER_WRITE_SUB_MARK_KEYS): while A is held the d-pad moves the end of
 * the mark within the cursor's part; when it is let go, an empty mark ends. */
void LetterWrite_RunMarkKeys(LetterWriteScene *self)
{
    if ((data_021fbe40.held & LETTER_WRITE_PAD_A) == 0) {
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_0C);
        if (self->mark_from == self->mark_to) {
            LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_MARKING);
        }
    } else {
        int keys = (int) MenuScene_LatchRepeatedKeys(letter_write_scene(self));
        if (LetterWrite_MoveCursorByKeys(self, keys, 0) != 0) {
            self->mark_to = self->position;
            LetterWrite_Refresh(self, 0, 1);
            LetterWrite_PlaceCursor(self);
            LetterWrite_PlacePointer(self);
            SoundSys_PlaySe(0x15);
        }
    }
}
CLEAN_AS(func_ov122_022a07d4, LetterWrite_RunMarkKeys)

/* func_ov122_022a0848 (LETTER_WRITE_SUB_0C): the pointer at the text cursor, by the buttons:
 * the d-pad moves the cursor (ending the mark), Y goes back to the keys, B deletes, A begins a
 * mark, L copies, R pastes, Start presses the panel's button 1. */
void LetterWrite_RunTextKeys(LetterWriteScene *self)
{
    int keys;
    s32 x, y;

    if (MenuScene_TakeTouch(letter_write_scene(self)) != 0) {
        LetterWrite_BeginTouch(self);
        return;
    }
    keys = (int) MenuScene_LatchRepeatedKeys(letter_write_scene(self));
    if (LetterWrite_MoveCursorByKeys(self, keys, 1) != 0) {
        LetterWrite_EndMark(self);
        LetterWrite_PlaceCursor(self);
        LetterWrite_PlacePointer(self);
        LetterWrite_UpdateKeys(self);
        SoundSys_PlaySe(0xb);
        return;
    }
    if (LetterWrite_SwitchPointerKey(self) != 0) {
        return;
    }
    x = self->cursor_x;
    y = self->cursor_y;
    if (LetterWrite_BackspaceKey(self) != 0) {
        if (x != self->cursor_x || y != self->cursor_y) {
            LetterWrite_PlacePointer(self);
        }
        return;
    }
    if ((data_021fbe40.pressed & LETTER_WRITE_PAD_A) != 0) {
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_MARK_KEYS);
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_MARKING);
        self->mark_from = self->position;
        self->mark_to = self->position;
    }
    if (LetterWrite_CopyKey(self) != 0) {
        return;
    }
    if (LetterWrite_PasteKey(self) != 0) {
        return;
    }
    LetterWrite_StartKey(self);
}
CLEAN_AS(func_ov122_022a0848, LetterWrite_RunTextKeys)

/* func_ov122_022a0928 (LETTER_WRITE_SUB_BACKSPACE_REPEAT): while B is held, a character deleted
 * each time the repeat is due (the pointer kept on the cursor). */
void LetterWrite_RunBackspaceRepeat(LetterWriteScene *self)
{
    if ((data_021fbe40.held & LETTER_WRITE_PAD_B) == 0) {
        MenuScene_SetSubState(letter_write_scene(self), self->return_sub_state);
    } else if (func_ov095_0229bf0c(self->keyboard) != 0) {
        LetterWrite_Command(self, LETTER_WRITE_CODE_BACKSPACE);
        if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_POINTER_ON_TEXT)) {
            LetterWrite_PlacePointer(self);
        }
    }
}
CLEAN_AS(func_ov122_022a0928, LetterWrite_RunBackspaceRepeat)

/* func_ov122_022a0974 (LETTER_WRITE_SUB_0A): once the pointer's animation has played, the
 * keyboard by the buttons. */
void LetterWrite_RunKeyReleased(LetterWriteScene *self)
{
    if (CellLayerSprite_IsDone(letter_write_pointer_cells(self))) {
        LetterWrite_PointerFirstOfSet(self);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_KEYS);
    }
}
CLEAN_AS(func_ov122_022a0974, LetterWrite_RunKeyReleased)

/* func_ov122_022a099c (LETTER_WRITE_SUB_KEY_REPEAT): while A is held, the key held down acted
 * on again each time the repeat is due. */
void LetterWrite_RunKeyRepeat(LetterWriteScene *self)
{
    int key;

    if ((data_021fbe40.held & LETTER_WRITE_PAD_A) == 0) {
        LetterWrite_BeginSub0A(self);
        return;
    }
    if (func_ov095_0229bf0c(self->keyboard) != 0) {
        key = func_ov095_0229c548(self->keyboard);
        LetterWrite_Command(self, func_ov095_0229c448(self->keyboard, key, 9));
        func_ov095_0229c8e4(letter_write_keyboard_arg(self), key);
    }
}
CLEAN_AS(func_ov122_022a099c, LetterWrite_RunKeyRepeat)

/* func_ov122_022a09f4 (LETTER_WRITE_SUB_08): once the pointer's press has played, the key
 * pressed by A acted on. The scroll key presses the scroll button (and ends the mark); a key
 * still held repeats; otherwise back to the keyboard. */
void LetterWrite_RunKeyPressed(LetterWriteScene *self)
{
    int key;
    int code;
    int result;

    if (CellLayerSprite_IsDone(letter_write_pointer_cells(self)) == 0) {
        return;
    }
    key = func_ov095_02299a00(self->keyboard);
    code = func_ov095_0229c448(self->keyboard, key, 9);
    if (code == LETTER_WRITE_CODE_SCROLL) {
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_SCROLL_PRESS);
        PushButton_Press(&self->scroll_button);
        PushButton_PressCue(&self->scroll_button);
        if (LetterWrite_HasMark(self) != 0) {
            LetterWrite_EndMark(self);
            LetterWrite_Refresh(self, 1, 1);
        } else {
            LetterWrite_EndMark(self);
        }
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_POINTER_ON_BUTTON);
        return;
    }
    result = LetterWrite_Command(self, code);
    if (result == 1 && (data_021fbe40.held & LETTER_WRITE_PAD_A) != 0) {
        func_ov095_0229bf3c(self->keyboard);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_KEY_REPEAT);
        func_ov095_0229c8e4(letter_write_keyboard_arg(self), key);
    } else if (result != 3) {
        if (result == 4) {
            func_ov095_0229cce0(self->keyboard);
        } else {
            LetterWrite_BeginSub0A(self);
        }
    }
}
CLEAN_AS(func_ov122_022a09f4, LetterWrite_RunKeyPressed)

/* Obj_ov122_022a2738::func_ov122_022a0ad0 (LETTER_WRITE_SUB_POINTER_GLIDE): once the pointer
 * stops, the sub state to return to, run at once. */
void LetterWrite_RunPointerGlide(LetterWriteScene *self)
{
    if (Glider_IsMoving(&self->pointer) == 0) {
        MenuScene_SetSubState(letter_write_scene(self), self->return_sub_state);
        LetterWrite_RunSubState(self);
    }
}
CLEAN_AS(_ZN18Obj_ov122_022a273819func_ov122_022a0ad0Ev, LetterWrite_RunPointerGlide)

/* func_ov122_022a0afc (LETTER_WRITE_SUB_KEYS): the keyboard by the buttons: the d-pad moves its
 * cursor, and past its edge the pointer turns to the text; else A, B, Y, L, R and Start, the
 * first that acts. Without a header, a repeated left on key 0x104 is dropped. */
void LetterWrite_RunKeys(LetterWriteScene *self)
{
    u8 keys;

    if (MenuScene_TakeTouch(letter_write_scene(self)) != 0) {
        LetterWrite_BeginTouch(self);
        return;
    }
    keys = (u8) MenuScene_LatchRepeatedKeys(letter_write_scene(self));
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_NO_HEADER) == 1) {
        if (func_ov095_02299a00(self->keyboard) == 0x104) {
            if (MenuScene_RepeatedLeft(letter_write_scene(self)) != 0) {
                keys = (u8) (keys & ~KEY_REPEAT_LEFT);
            }
        }
    }
    switch (func_ov095_02299a54(self->keyboard, keys)) {
        case 1:
            Glider_TurnToSetA(&self->pointer);
            LetterWrite_GlidePointer(self);
            break;
        case 2:
            Glider_TurnToSetC(&self->pointer);
            LetterWrite_GlidePointer(self);
            break;
        case 3:
            Glider_TurnToSetB(&self->pointer);
            LetterWrite_GlidePointer(self);
            break;
        default:
            if (LetterWrite_PressKeyByA(self) != 0) {
                return;
            }
            if (LetterWrite_BackspaceKey(self) != 0) {
                return;
            }
            if (LetterWrite_SwitchPointerKey(self) != 0) {
                return;
            }
            if (LetterWrite_CopyKey(self) != 0) {
                return;
            }
            if (LetterWrite_PasteKey(self) != 0) {
                return;
            }
            LetterWrite_StartKey(self);
            break;
    }
}
CLEAN_AS(func_ov122_022a0afc, LetterWrite_RunKeys)

/* --- The text: typing, deleting, copying --- */

/* func_ov122_022a0be4: a key's code acted on. Gives what the keyboard gave for its own codes,
 * else 1 for a character or a deletion, 2 for a newline and the commands that change the text,
 * 3 for the panel's buttons. Sound 0x34 when a character could not be put in or converted. */
int LetterWrite_Command(LetterWriteScene *self, int code)
{
    int result = 1;
    int own = func_ov095_0229ba44(self->keyboard, code, 6);

    if (own != 0) {
        LetterWrite_Refresh(self, 0, 1);
        return own;
    }
    if (func_ov095_0229bebc(self->keyboard, code)) {
        switch (code) {
            case LETTER_WRITE_CODE_BACKSPACE:
                LetterWrite_Backspace(self, 1);
                break;
            case LETTER_WRITE_CODE_CONVERT_1:
            case LETTER_WRITE_CODE_CONVERT_2:
            case LETTER_WRITE_CODE_CONVERT_3:
                if (LetterWrite_ConvertChar(self, code) == 0) {
                    LetterWrite_PlaySound34(self);
                }
                result = 2;
                break;
            case LETTER_WRITE_CODE_BUTTON_1:
                LetterWrite_PressButton1(self);
                result = 3;
                break;
            case LETTER_WRITE_CODE_BUTTON_0:
                LetterWrite_PressButton0(self);
                result = 3;
                break;
            case LETTER_WRITE_CODE_COPY:
                LetterWrite_Copy(self);
                result = 2;
                break;
            case LETTER_WRITE_CODE_PASTE:
                LetterWrite_Paste(self);
                result = 2;
                break;
        }
    } else {
        /* QUIRK: the code is cut to 16 bits as a character. */
        if (LetterWrite_TypeChar(self, (u16) code) == 0) {
            LetterWrite_PlaySound34(self);
        }
        if (code == LETTER_WRITE_CODE_NEWLINE) {
            result = 2;
        }
    }
    return result;
}
CLEAN_AS(func_ov122_022a0be4, LetterWrite_Command)

/* func_ov122_022a0cec: the copied text put in at the cursor (over the marked characters), one
 * character at a time until one does not fit; sound 0x34 when not even the first did. */
void LetterWrite_Paste(LetterWriteScene *self)
{
    int count;
    int i;

    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_COPIED) == 0) {
        return;
    }
    if (LetterWrite_HasMark(self) != 0) {
        LetterWrite_DeleteMarked(self);
    }
    func_ov095_0229b3ec(self->keyboard);
    func_ov095_0229b394(letter_write_keyboard_arg(self));
    count = func_02051c8c_unk(self->clipboard, LETTER_BODY_CHARS);
    for (i = 0; i < count; i++) {
        if (LetterWrite_InsertChar(self, self->clipboard[i], 0) == 0) {
            if (i == 0) {
                LetterWrite_PlaySound34(self);
            }
            break;
        }
    }
    func_ov095_022999e8(self->keyboard);
    LetterWrite_Refresh(self, 0, 1);
    LetterWrite_PlaceCursor(self);
    func_ov095_0229b388(letter_write_keyboard_arg(self));
}
CLEAN_AS(func_ov122_022a0cec, LetterWrite_Paste)

/* func_ov122_022a0d84: the marked characters copied, the paste key enabled.
 * REQUIRES: `part` is a LetterWritePart (with another the copy reads from address 0). */
void LetterWrite_Copy(LetterWriteScene *self)
{
    u8 from, to;
    int first, count;
    u16 *text;

    if (LetterWrite_HasMark(self) == 0) {
        return;
    }
    to = self->mark_to;
    from = self->mark_from;
    if (from > to) {
        first = to;
        count = from - to;
    } else {
        first = from;
        count = to - from;
    }
    TextString_ClearChars(self->clipboard, LETTER_BODY_CHARS);
    text = LetterWrite_PartText(self);
    TextString_CopyChars(text + first, self->clipboard, count);
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_COPIED);
    func_ov095_022999f4(self->keyboard);
    LetterWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov122_022a0d84, LetterWrite_Copy)

/* func_ov122_022a0dec: the panel's button 0 (the choice). */
void LetterWrite_PressButton0(LetterWriteScene *self)
{
    LetterWrite_PressButton(self, 0);
}
CLEAN_AS(func_ov122_022a0dec, LetterWrite_PressButton0)

/* func_ov122_022a0df8: the panel's button 1 (the writing done). */
void LetterWrite_PressButton1(LetterWriteScene *self)
{
    LetterWrite_PressButton(self, 1);
}
CLEAN_AS(func_ov122_022a0df8, LetterWrite_PressButton1)

/* func_ov122_022a0e04: the writing left (LETTER_WRITE_STATE_LEAVE): the scroll back to the top,
 * the cursor hidden, no mark, no composition, the whole letter given to the view, the pointer
 * hidden. */
void LetterWrite_Leave(LetterWriteScene *self)
{
    self->base.state = LETTER_WRITE_STATE_LEAVE;
    MenuScene_SetPhase(letter_write_scene(self), 1);
    LetterWrite_ScrollTo(self, 0);
    LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_CURSOR_SHOWN);
    LetterWrite_EndMark(self);
    func_ov095_0229b3ec(self->keyboard);
    LetterWrite_Refresh(self, 1, 0);
    LetterWrite_HidePointer(self);
}
CLEAN_AS(func_ov122_022a0e04, LetterWrite_Leave)

/* func_ov122_022a0e4c: a character typed: over the marked characters, then the view and the
 * cursor brought up to date. Gives 1 when it was put in. */
int LetterWrite_TypeChar(LetterWriteScene *self, int code)
{
    int result;

    if (LetterWrite_HasMark(self)) {
        LetterWrite_DeleteMarked(self);
        func_ov095_0229b3ec(self->keyboard);
    }
    result = LetterWrite_InsertChar(self, code, 1);
    LetterWrite_Refresh(self, 0, 1);
    LetterWrite_PlaceCursor(self);
    return result;
}
CLEAN_AS(func_ov122_022a0e4c, LetterWrite_TypeChar)

/* func_ov122_022a0e90: a character put in at the cursor, which moves past it. The body takes
 * newlines and is broken into its four lines; the header and the footer are one line of 0xa0
 * pixels. Typing before the name moves the name on. Gives 1 when it was put in. */
int LetterWrite_InsertChar(LetterWriteScene *self, int code, int notify)
{
    u8 position = LetterWrite_HeaderPosition(self);
    u8 old = position;
    u16 *text = (u16 *) (uintptr_t) LetterWrite_PartTextAddress(self);
    int capacity = LetterWrite_PartCapacity(self);

    if (self->part == LETTER_WRITE_PART_BODY) {
        if (func_ov095_0229bc00(self->keyboard, text, code, &position, LETTER_BODY_CHARS, 0x28, 4, 0xa0, 0, notify) == 0) {
            return 0;
        }
        LetterWrite_SetPosition(self, position);
        return 1;
    }
    if (code == LETTER_WRITE_CODE_NEWLINE) {
        return 0;
    }
    if (func_ov095_0229bcec(self->keyboard, text, code, &position, capacity, 0xa0, 0, 1) == 0) {
        return 0;
    }
    switch (self->part) {
        case LETTER_WRITE_PART_HEADER:
            if (old != position) {
                self->letter->header_line = (u8) (self->letter->header_line + position - old);
            }
            break;
        case LETTER_WRITE_PART_HEADER_AFTER:
            position = (u8) (position - self->letter->header_line);
            break;
        default:
            break;
    }
    LetterWrite_SetPosition(self, position);
    return 1;
}
CLEAN_AS(func_ov122_022a0e90, LetterWrite_InsertChar)

/* func_ov122_022a0f78: the character before the cursor converted by one of the keyboard's
 * three conversions. Gives 1 when it was.
 * QUIRK: in this ROM all three conversions give 0, so this gives 0. The ROM's code also stores
 * the part's capacity and 10000 as two stack arguments the replacing function does not read. */
int LetterWrite_ConvertChar(LetterWriteScene *self, int code)
{
    int character = LetterWrite_CharBeforeCursor(self);
    unsigned char position;
    int text;

    if (character == 0) {
        return 0;
    }
    switch (code) {
        case LETTER_WRITE_CODE_CONVERT_1:
            character = func_ov095_0229bb9c(self->keyboard, character);
            break;
        case LETTER_WRITE_CODE_CONVERT_2:
            character = func_ov095_0229bb98(self->keyboard, character);
            break;
        case LETTER_WRITE_CODE_CONVERT_3:
            character = func_ov095_0229bb94(self->keyboard, character);
            break;
        default:
            break;
    }
    if (character == 0) {
        return 0;
    }
    position = LetterWrite_HeaderPosition(self);
    text = LetterWrite_PartTextAddress(self);
    LetterWrite_PartCapacity(self);
    if (func_ov095_0229bba0(letter_write_keyboard_arg(self), (unsigned short *) (uintptr_t) text, character, position) == 0) {
        return 0;
    }
    LetterWrite_Refresh(self, 0, 1);
    LetterWrite_PlaceCursor(self);
    return 1;
}
CLEAN_AS(func_ov122_022a0f78, LetterWrite_ConvertChar)

/* func_ov122_022a1030: a deletion: the marked characters, else the character being composed or
 * the one before the cursor; at the start of a part the one after it. Then sound 0x35, the view
 * and the cursor brought up to date; gives 1. With nothing to delete gives 0 (sound 0x34 with
 * `sound_on_fail`).
 * REQUIRES: `part` is a LetterWritePart (with another the text read is at address 0). */
int LetterWrite_Backspace(LetterWriteScene *self, int sound_on_fail)
{
    if (LetterWrite_HasMark(self) != 0) {
        func_ov095_0229b3ec(self->keyboard);
        LetterWrite_DeleteMarked(self);
    } else if (self->position != 0) {
        u16 *text = LetterWrite_PartText(self);
        if (func_ov095_0229b3a0(self->keyboard, text, self->position) == 0) {
            self->mark_from = self->position;
            self->mark_to = (u8) (self->position - 1);
            LetterWrite_DeleteMarked(self);
        }
    } else {
        u16 *text = LetterWrite_PartText(self);
        u8 part = self->part;
        int nothing;

        /* Nothing after the cursor: the header's first part is empty, or the second part
         * starts after all ten characters, or the text ends there. */
        if (part == LETTER_WRITE_PART_HEADER && self->letter->header_line == 0) {
            nothing = 1;
        } else if (part == LETTER_WRITE_PART_HEADER_AFTER && self->letter->header_line == LETTER_HEADER_CHARS) {
            nothing = 1;
        } else {
            nothing = text[0] == 0;
        }
        if (nothing) {
            if (sound_on_fail != 0) {
                LetterWrite_PlaySound34(self);
            }
            return 0;
        }
        self->mark_from = 0;
        self->mark_to = 1;
        LetterWrite_DeleteMarked(self);
    }
    SoundSys_PlaySe(0x35);
    LetterWrite_Refresh(self, 0, 1);
    LetterWrite_PlaceCursor(self);
    return 1;
}
CLEAN_AS(func_ov122_022a1030, LetterWrite_Backspace)

/* --- The pen --- */

static int letter_write_pen_put_down(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* func_ov122_022a1110: the key under the pen pressed and its code acted on (gives
 * LetterWrite_Command's result), its repeat started; 0 when no key is there. */
int LetterWrite_TouchKey(LetterWriteScene *self)
{
    int key;
    int result;

    func_ov095_0229cce0(self->keyboard);
    key = func_ov095_0229c54c(self->keyboard, data_021f6c58, data_021f6c54);
    if (key == -1) {
        return 0;
    }
    result = LetterWrite_Command(self, func_ov095_0229c448(self->keyboard, key, 9));
    func_ov095_0229c8e4(letter_write_keyboard_arg(self), key);
    func_ov095_0229bf3c(self->keyboard);
    return result;
}
CLEAN_AS(func_ov122_022a1110, LetterWrite_TouchKey)

/* func_ov122_022a116c (LETTER_WRITE_SUB_CHOICE_TOUCH): the choice by the pen: a row touched is
 * picked, a touch elsewhere closes the choice; main's asking to close closes it too. */
void LetterWrite_RunChoiceTouch(LetterWriteScene *self)
{
    int row;

    if (StateFlags_MenuCloseAsked()) {
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_CLOSE_ASKED);
        LetterWrite_CloseChoice(self);
        return;
    }
    if (MenuScene_TakeButtons(letter_write_scene(self), 1)) {
        LetterWrite_BeginChoiceKeys(self);
        return;
    }
    if (!letter_write_pen_put_down()) {
        return;
    }
    row = PagedChoice_RowAtOrNone(letter_write_choice(self), data_021f6c58, data_021f6c54);
    if (row >= 0) {
        PagedChoice_PickRow(letter_write_choice(self), row);
        self->choice_row = (u8) PagedChoice_Decide(letter_write_choice(self), self->choice_page, (u8) row);
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_CHOICE_PICKED);
    } else {
        LetterWrite_CloseChoice(self);
    }
}
CLEAN_AS(func_ov122_022a116c, LetterWrite_RunChoiceTouch)

/* func_ov122_022a1220 (LETTER_WRITE_SUB_04): the panel by the pen: its buttons 3 and 4. */
void LetterWrite_RunPanelTouch(LetterWriteScene *self)
{
    if (MenuScene_TakeButtons(letter_write_scene(self), 1) != 0) {
        LetterWrite_BeginPanelKeys(self);
    } else if (letter_write_pen_put_down()) {
        if (ButtonPanel_IsTouched(&self->panel, 3) != 0) {
            LetterWrite_PressButton(self, 3);
        } else if (ButtonPanel_IsTouched(&self->panel, 4) != 0) {
            LetterWrite_PressButton(self, 4);
        }
    }
}
CLEAN_AS(func_ov122_022a1220, LetterWrite_RunPanelTouch)

/* func_ov122_022a1290 (LETTER_WRITE_SUB_MARK_DRAG): while the pen is down the end of the mark
 * follows it (sound 0x15 when it moves); when it is lifted, an empty mark ends. The scroll and
 * the view kept on the cursor. */
void LetterWrite_RunMarkDrag(LetterWriteScene *self)
{
    int moved;

    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_TOUCH);
        if (self->mark_from == self->mark_to) {
            LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_MARKING);
        }
        moved = 1;
    } else {
        moved = LetterWrite_DragMark(self);
        if (moved != 0) {
            SoundSys_PlaySe(0x15);
        }
    }
    if (moved != 0) {
        LetterWrite_ScrollToCursor(self);
        LetterWrite_Refresh(self, 0, 1);
    }
}
CLEAN_AS(func_ov122_022a1290, LetterWrite_RunMarkDrag)

/* func_ov122_022a12f0 (LETTER_WRITE_SUB_SCROLL_DRAG): the cursor's blink restarted hidden;
 * while the pen is down the scroll follows it, when it is lifted the scroll button released. */
void LetterWrite_RunScrollDrag(LetterWriteScene *self)
{
    self->blink = 0;
    if (data_021fbdd8 == 0) {
        LetterWrite_Nothing(self);
        PushButton_Release(&self->scroll_button);
        LetterWrite_BeginTouch(self);
    } else {
        LetterWrite_DragScroll(self);
    }
}
CLEAN_AS(func_ov122_022a12f0, LetterWrite_RunScrollDrag)

/* func_ov122_022a132c (LETTER_WRITE_SUB_KEY_TOUCH_HELD): while the pen is down the key it
 * holds acted on again each time the repeat is due. */
void LetterWrite_RunKeyTouchHeld(LetterWriteScene *self)
{
    int key;

    if (data_021fbdd8 == 0) {
        MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_TOUCH);
        return;
    }
    if (func_ov095_0229bf0c(self->keyboard) != 0) {
        key = func_ov095_0229c548(self->keyboard);
        LetterWrite_Command(self, func_ov095_0229c448(self->keyboard, key, 9));
        func_ov095_0229c8e4(letter_write_keyboard_arg(self), key);
    }
}
CLEAN_AS(func_ov122_022a132c, LetterWrite_RunKeyTouchHeld)

/* func_ov122_022a1380 (LETTER_WRITE_SUB_TOUCH): the pen put down on the panel's buttons 9 and
 * 0 (the latter only with a header), on the keyboard's mode tabs, on the letter (y below 0x48:
 * a mark begun), on the scroll button (x from 0xe0: a drag begun), or on a key (once the key
 * pressed before is no longer shown). The buttons switch to the keyboard by the buttons. */
void LetterWrite_RunTouch(LetterWriteScene *self)
{
    int key_shown;
    int x, y;

    if (MenuScene_TakeButtons(letter_write_scene(self), 1)) {
        LetterWrite_BeginKeys(self);
        return;
    }
    key_shown = 0;
    if (func_ov095_0229bf48(self->keyboard)) {
        key_shown = 1;
    }
    if (!letter_write_pen_put_down()) {
        return;
    }
    x = data_021f6c58;
    y = data_021f6c54;
    if (ButtonPanel_IsTouched(&self->panel, 9)) {
        LetterWrite_PressButton1(self);
        return;
    }
    if (!LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_NO_HEADER)) {
        if (ButtonPanel_IsTouched(&self->panel, 0)) {
            LetterWrite_PressButton0(self);
            return;
        }
    }
    if (func_ov095_0229aff0(self->keyboard)) {
        func_ov095_0229c22c(self->keyboard, 9, 6, 1);
        LetterWrite_Refresh(self, 0, 1);
        return;
    }
    if (y < 0x48) {
        if (x < 0xe0) {
            if (LetterWrite_StartTouch(self)) {
                MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_MARK_DRAG);
                func_ov095_0229b3ec(self->keyboard);
                LetterWrite_Refresh(self, 1, 1);
                return;
            }
        } else if (LetterWrite_StartDrag(self)) {
            PushButton_Press(&self->scroll_button);
            MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_SCROLL_DRAG);
            LetterWrite_EndMark(self);
            LetterWrite_Refresh(self, 1, 1);
            return;
        }
    }
    if (y >= 0x48 && key_shown == 0) {
        if (LetterWrite_TouchKey(self) == 1) {
            MenuScene_SetSubState(letter_write_scene(self), LETTER_WRITE_SUB_KEY_TOUCH_HELD);
        }
    }
}
CLEAN_AS(func_ov122_022a1380, LetterWrite_RunTouch)

/* --- The view and the keyboard brought up to date --- */

/* func_ov122_022a14c0: the keyboard's keys enabled as the cursor allows: the newline when one
 * fits in the body at the cursor, copy with a mark, paste with copied text, and key 6 with a
 * mark or a character before the cursor (keys 3-5 off without one). */
void LetterWrite_UpdateKeys(LetterWriteScene *self)
{
    if (self->part == LETTER_WRITE_PART_BODY) {
        u8 position = self->position;
        if (func_ov095_0229bc00(self->keyboard, self->letter->body, LETTER_WRITE_CODE_NEWLINE, &position, LETTER_BODY_CHARS,
                                0x28, 4, 0xa0, 1, 1)) {
            func_ov095_0229ce84(self->keyboard, LETTER_WRITE_KEY_NEWLINE);
        } else {
            func_ov095_0229cef4(self->keyboard, LETTER_WRITE_KEY_NEWLINE);
        }
    } else {
        func_ov095_0229cef4(self->keyboard, LETTER_WRITE_KEY_NEWLINE);
    }

    if (LetterWrite_HasMark(self)) {
        func_ov095_0229ce84(self->keyboard, LETTER_WRITE_KEY_COPY);
    } else {
        func_ov095_0229cef4(self->keyboard, LETTER_WRITE_KEY_COPY);
    }

    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_COPIED)) {
        func_ov095_0229ce84(self->keyboard, LETTER_WRITE_KEY_PASTE);
    } else {
        func_ov095_0229cef4(self->keyboard, LETTER_WRITE_KEY_PASTE);
    }

    if (LetterWrite_HasMark(self)) {
        func_ov095_0229bee4(self->keyboard);
        func_ov095_0229ce84(self->keyboard, LETTER_WRITE_KEY_6);
    } else if (self->position == 0) {
        func_ov095_0229bee4(self->keyboard);
    } else {
        func_ov095_0229bed8(self->keyboard, LetterWrite_CharBeforeCursor(self));
    }
}
CLEAN_AS(func_ov122_022a14c0, LetterWrite_UpdateKeys)

/* func_ov122_022a15b8: the view given the letter's texts again, all three (`whole`) or the
 * cursor's part's; the marked characters shown marked; the keys brought up to date. */
void LetterWrite_Refresh(LetterWriteScene *self, int whole, int editing)
{
    int first = 0;
    int count;
    int style;

    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_1000);
    if (whole != 0) {
        LetterView_SetGreeting(&self->view, letter_write_view_letter(self), self->shown_header);
        LetterView_SetBody(&self->view, self->letter->body, editing);
        LetterView_SetSignature(&self->view, self->letter->footer);
    } else {
        switch (self->part) {
            case LETTER_WRITE_PART_HEADER:
            case LETTER_WRITE_PART_HEADER_AFTER:
                LetterView_SetGreeting(&self->view, letter_write_view_letter(self), self->shown_header);
                break;
            case LETTER_WRITE_PART_BODY:
                LetterView_SetBody(&self->view, self->letter->body, editing);
                break;
            case LETTER_WRITE_PART_FOOTER:
                LetterView_SetSignature(&self->view, self->letter->footer);
                break;
        }
    }

    if (LetterWrite_HasMark(self)) {
        style = 0;
        if (self->mark_from > self->mark_to) {
            first = self->mark_to;
            count = self->mark_from - self->mark_to;
        } else {
            first = self->mark_from;
            count = self->mark_to - self->mark_from;
        }
    } else {
        style = 1;
        count = 0;
    }

    if (count != 0) {
        switch (self->part) {
            case LETTER_WRITE_PART_HEADER:
                LetterView_MarkGreeting(&self->view, first, count, style);
                break;
            case LETTER_WRITE_PART_HEADER_AFTER: {
                /* After the name, counted as the view shows the header. */
                int line = self->letter->header_line;
                int shown = first + line + (int) LetterView_NameLength(&self->view);
                LetterView_MarkGreeting(&self->view, shown, count, style);
                break;
            }
            case LETTER_WRITE_PART_BODY:
                LetterView_MarkBody(&self->view, (unsigned int) first, (unsigned int) count, style);
                break;
            case LETTER_WRITE_PART_FOOTER:
                LetterView_MarkSignature(&self->view, first, count, style);
                break;
        }
    }
    LetterWrite_UpdateKeys(self);
}
CLEAN_AS(func_ov122_022a15b8, LetterWrite_Refresh)

/* --- Setting up, drawing and leaving --- */

/* func_ov122_022a1718: the panel's message 0x22 shown. */
void LetterWrite_ShowPanelMessage(LetterWriteScene *self)
{
    ButtonPanel_SetLayout7(&self->panel, 0x22);
    ButtonPanel_SetWindowFlag5b(&self->panel);
}
CLEAN_AS(func_ov122_022a1718, LetterWrite_ShowPanelMessage)

/* func_ov122_022a1738: the panel's layout: one button without a header, else two. */
void LetterWrite_SetPanelLayout(LetterWriteScene *self)
{
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_NO_HEADER)) {
        ButtonPanel_SetLayout1(&self->panel);
    } else {
        ButtonPanel_SetLayout2Wide(&self->panel);
    }
}
CLEAN_AS(func_ov122_022a1738, LetterWrite_SetPanelLayout)

/* func_ov122_022a1764 */
void LetterWrite_LoadKeyboardScreen(LetterWriteScene *self)
{
    func_ov095_0229b324(self->keyboard);
}
CLEAN_AS(func_ov122_022a1764, LetterWrite_LoadKeyboardScreen)

/* func_ov122_022a1770: the scene's graphics loaded: its palettes and characters on the sub
 * screen's background 3, the keyboard's screen, the letter's paper on background 1 and the view
 * on background 0; then the letter given to the view whole and drawn. */
void LetterWrite_LoadScreens(LetterWriteScene *self)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadPalettesFromFile(data_ov122_022a2798, heap, LAYER_SUB_BG3, 1, 1, 9);
    func_ov095_0229c000(self->keyboard, data_ov122_022a27b0);
    LetterWrite_UpdateKeys(self);
    func_ov095_0229bfd8(self->keyboard, LAYER_SUB_BG3);
    DisplayLayer_LoadCharsFromFile(data_ov122_022a27c8, heap, LAYER_SUB_BG3, 0x13d, 0x13d, 0x1e9);
    Paper_LoadBackground(Letter_Paper(self->letter), LAYER_SUB_BG1);
    LetterView_LoadScreen(&self->view, LAYER_SUB_BG0);
    LetterWrite_Refresh(self, 1, 1);
    LetterView_Redraw(&self->view);
}
CLEAN_AS(func_ov122_022a1770, LetterWrite_LoadScreens)

/* func_ov122_022a1808: the sub screen's backgrounds 3 (priority 1), 1 and 0 (priority 3) set
 * up. */
void LetterWrite_SetLayers(void)
{
    DisplayLayer_SetPriority(LAYER_SUB_BG3, 1);
    DisplayLayer_SetBgControl(LAYER_SUB_BG3, 0, 0, 0);
    DisplayLayer_SetPriority(LAYER_SUB_BG1, 3);
    DisplayLayer_SetBgControl(LAYER_SUB_BG1, 0, 0, 0);
    DisplayLayer_SetPriority(LAYER_SUB_BG0, 3);
    DisplayLayer_SetBgControl(LAYER_SUB_BG0, 0, 0, 0);
}
CLEAN_AS(func_ov122_022a1808, LetterWrite_SetLayers)

/* func_ov122_022a1850: run after each frame's state (LetterWrite_RunState); does nothing. */
void LetterWrite_Idle(LetterWriteScene *self)
{
    (void) self;
}
CLEAN_AS(func_ov122_022a1850, LetterWrite_Idle)

/* func_ov122_022a1854: run before each frame's state (LetterWrite_RunState). */
void LetterWrite_ClosePanelTexts(LetterWriteScene *self)
{
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov122_022a1854, LetterWrite_ClosePanelTexts)

/* func_ov122_022a1864: the view, the keyboard and the choice drawn. */
void LetterWrite_Draw(LetterWriteScene *self)
{
    LetterView_Redraw(&self->view);
    func_ov095_0229bf7c(self->keyboard, LAYER_SUB_BG3);
    PagedChoice_Update(letter_write_choice(self));
    LetterWrite_Idle(self);
}
CLEAN_AS(func_ov122_022a1864, LetterWrite_Draw)

/* An object's update through its class (vtable slot 3). */
static int letter_write_update_object(const void *const *vtable_field, void *object)
{
    int (*const *vtable)(void *) = (int (*const *)(void *)) *vtable_field;
    return vtable[3](object);
}

/* func_ov122_022a1898: the panel's texts closed, the scroll button and the pointer updated;
 * gives the pointer's update's result. */
int LetterWrite_UpdateSprites(LetterWriteScene *self)
{
    LetterWrite_ClosePanelTexts(self);
    letter_write_update_object(&self->scroll_button.vtable, &self->scroll_button);
    return letter_write_update_object(&self->pointer.vtable, &self->pointer);
}
CLEAN_AS(func_ov122_022a1898, LetterWrite_UpdateSprites)

/* func_ov122_022a18c4: what the keyboard, the view, the choice and the panel hold let go. */
void LetterWrite_Release(LetterWriteScene *self)
{
    func_ov095_0229c05c(self->keyboard);
    LetterView_ReleaseBoxes(&self->view);
    PagedChoice_Dismiss(letter_write_choice(self));
    ButtonPanel_CloseTexts(&self->panel);
}
CLEAN_AS(func_ov122_022a18c4, LetterWrite_Release)

/* func_ov122_022a18f8: the scene set up for the letter of main's group parameters: the keyboard
 * (mode 1), the view with the addressee's name, the scroll at 0x10, the scroll button up, the
 * choice on background 3. Without an addressee, no header. */
void LetterWrite_Setup(LetterWriteScene *self)
{
    self->letter = (Letter *) GroupParams_Pointer();
    func_ov095_0229c084(self->keyboard, 1);
    LetterView_Init(&self->view, LAYER_SUB_BG0);
    LetterView_SetName(&self->view, letter_write_view_letter(self));
    LetterWrite_SetScroll(self, 0x10);
    LetterWrite_ScrollTo(self, 0x10);
    self->flags = 0;
    DualCellSprite_SetState(letter_write_button_cells(self), 1);
    PagedChoice_Init(letter_write_choice(self), LAYER_SUB_BG3, 1, NULL);
    PagedChoice_BuildPages(letter_write_choice(self));
    self->unk_a4 = 0;
    if (Letter_HasNoAddressee(self->letter) != 0) {
        func_ov095_0229c050(letter_write_keyboard_arg(self));
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_NO_HEADER);
    }
}
CLEAN_AS(func_ov122_022a18f8, LetterWrite_Setup)

/* func_ov122_022a1998 (LETTER_WRITE_STATE_WIPE_OUT): the wipe stepped, the three backgrounds
 * moved with it; once it is done they are hidden and the scene's phase is 5. */
void LetterWrite_StepWipeOut(LetterWriteScene *self)
{
    if (MenuScene_StepWipe(letter_write_scene(self), 0)) {
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG3);
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG1);
        DisplayLayer_HideAndResetScroll(LAYER_SUB_BG0);
        MenuScene_SetPhase(letter_write_scene(self), 5);
    } else {
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG1, 0, 0);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG0, 0, 0);
        self->unk_94 = MenuScene_WipeOffsetY(letter_write_scene(self));
        self->unk_98 = self->unk_94;
    }
}
CLEAN_AS(func_ov122_022a1998, LetterWrite_StepWipeOut)

/* func_ov122_022a1a04 (state 13): once the scroll has stopped, the wipe out started. */
void LetterWrite_StartWipeOut(LetterWriteScene *self)
{
    if (LetterWrite_IsScrolling(self) == 0) {
        MenuScene_StartWipeOnWindow2(letter_write_scene(self), 11, 0, 0, 0x30);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG1, 0, 0);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG0, 0, 0);
        MenuScene_SetState(letter_write_scene(self), LETTER_WRITE_STATE_WIPE_OUT);
    }
}
CLEAN_AS(func_ov122_022a1a04, LetterWrite_StartWipeOut)

/* --- The states, the vtable's slots and the constructor --- */

/* The margin of the wipes on window 2. */
#define LETTER_WRITE_WIPE_MARGIN 0x30

/* The keyboard of overlay 95: set up again in its current mode and drawn on a layer, set up in
 * the mode main keeps (GroupParams) on a layer, its mode tabs drawn at (x, y), its two frame
 * cells drawn at (x, y), the place it keeps for the scroll button's face (its words 0xd and
 * 0xe), and the text cursor's cell drawn at (x, y) (its first argument unused). */
extern void func_ov095_0229c208(void *keyboard, unsigned int layer);
extern void func_ov095_0229c420(void *keyboard, int layer);
extern void func_ov095_0229b1c8(void *keyboard, int x, int y, int priority);
extern void func_ov095_0229ae84(void *keyboard, void *x, void *y);
extern void func_ov095_02299b30(int *keyboard, int x, int y);
extern int func_ov095_0229af58(int unused, int x, int y, int priority);

/* The parent, overlay 90's menu (as ov096's pockets_screen.c calls it): switched to a tab (7 closes
 * the menu), and told the scene closes. */
#define LETTER_WRITE_TAB_NONE (-1)
#define LETTER_WRITE_TAB_CLOSE 7
#define LETTER_WRITE_TAB_8 8 /* never switched to */
extern void func_ov090_022993cc(Process *parent, u32 tab);
extern u8 func_ov090_0229936c(Process *parent);
extern void func_ov090_022990d0(Process *parent); /* its bytes 0x94 and 0x91 = 1 */

/* The cells drawn by the draw: one above the keyboard and one over it while the keys are in use. */
extern const OamEntry data_ov122_022a2700[];
extern const OamEntry data_ov122_022a25b0[];

/* The labels' constructor, handed to __cxa_vec_ctor with their destructor (the game's symbols). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void *func_02070c08(void *label);

/* The tables of member functions (ov004/member_pointer.h): the guards, the tables and their
 * constants (the symbol table names the sub states' table's second part, from sub state 0x10,
 * data_ov122_022a28e0). */
extern u32 data_ov122_022a27e0; /* the sub states' guard */
extern u32 data_ov122_022a27e4; /* the states' guard */
extern MemberPointer data_ov122_022a27e8[LETTER_WRITE_STATES];
extern MemberPointer data_ov122_022a2860[LETTER_WRITE_SUB_STATES];
extern const MemberPointer data_ov122_022a25a0, data_ov122_022a25a8, data_ov122_022a25b8, data_ov122_022a25c0,
    data_ov122_022a25c8, data_ov122_022a25d0, data_ov122_022a25d8, data_ov122_022a25e0, data_ov122_022a25e8,
    data_ov122_022a25f0, data_ov122_022a25f8, data_ov122_022a2600, data_ov122_022a2608, data_ov122_022a2610,
    data_ov122_022a2618, data_ov122_022a2620, data_ov122_022a2628, data_ov122_022a2630, data_ov122_022a2638,
    data_ov122_022a2640, data_ov122_022a2648, data_ov122_022a2650, data_ov122_022a2658, data_ov122_022a2660,
    data_ov122_022a2668, data_ov122_022a2670, data_ov122_022a2678, data_ov122_022a2680, data_ov122_022a2688,
    data_ov122_022a2690, data_ov122_022a2698, data_ov122_022a26a0, data_ov122_022a26a8, data_ov122_022a26b8,
    data_ov122_022a26c0, data_ov122_022a26c8, data_ov122_022a26d0, data_ov122_022a26d8, data_ov122_022a26e0,
    data_ov122_022a26e8, data_ov122_022a26f0, data_ov122_022a26f8;

static Process *letter_write_parent(LetterWriteScene *self)
{
    return Process_GetParent((Process *) (void *) self);
}

/* An object drawn through its class (vtable slot 2). */
static void letter_write_draw_object(void *object)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[2])(object);
}

/* func_ov122_022a1a58 (LETTER_WRITE_STATE_CHOICE): the choice's first page opened, its graphics
 * loaded and wiping in; phase 2. */
void LetterWrite_OpenChoice(LetterWriteScene *self)
{
    self->choice_page = 0;
    PagedChoice_LoadChoiceGraphics(letter_write_choice(self));
    LetterWrite_OpenChoicePage(self, 1);
    MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_2);
}
CLEAN_AS(func_ov122_022a1a58, LetterWrite_OpenChoice)

/* func_ov122_022a1a84 (state 11): the keyboard wipes in; when done, the input starts again
 * (LetterWrite_Start, phase 2, LetterWrite_BeginInput). The keyboard's layer follows the wipe,
 * whose y is kept and given. */
int LetterWrite_KeyboardWipeIn(LetterWriteScene *self)
{
    if (MenuScene_StepWipeBack(letter_write_scene(self), 0) != 0) {
        LetterWrite_Start(self);
        MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_2);
        LetterWrite_BeginInput(self);
    }
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
    self->unk_94 = MenuScene_WipeOffsetY(letter_write_scene(self));
    return self->unk_94;
}
CLEAN_AS(func_ov122_022a1a84, LetterWrite_KeyboardWipeIn)

/* func_ov122_022a1ac4 (LETTER_WRITE_STATE_BACK): the keyboard back: set up again in its mode on
 * background 3 (priority 1), shown and wiping in on window 2, the panel's layout set and the
 * panel following the wipe (state 11). */
void LetterWrite_StartKeyboardWipeIn(LetterWriteScene *self)
{
    func_ov095_0229c208(self->keyboard, LAYER_SUB_BG3);
    DisplayLayer_SetPriority(LAYER_SUB_BG3, 1);
    MenuScene_StartWipeCoveredOnWindow2(letter_write_scene(self), 8, 0, 0, LETTER_WRITE_WIPE_MARGIN);
    DisplayLayer_Show(LAYER_SUB_BG3);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
    LetterWrite_SetPanelLayout(self);
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_01);
    self->unk_94 = MenuScene_WipeOffsetY(letter_write_scene(self));
    self->base.state = LETTER_WRITE_STATE_KEYBOARD_WIPE_IN;
}
CLEAN_AS(func_ov122_022a1ac4, LetterWrite_StartKeyboardWipeIn)

/* func_ov122_022a1b24 (state 9): the panel slides down 0x20 pixels a frame; from 0xa0 on it is
 * no longer drawn by `unk_98` and the keyboard comes back (LETTER_WRITE_STATE_BACK). */
void LetterWrite_SlidePanelOut(LetterWriteScene *self)
{
    if (self->unk_98 < 0xa0) {
        self->unk_98 += 0x20;
    } else {
        LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_02);
        self->base.state = LETTER_WRITE_STATE_BACK;
    }
}
CLEAN_AS(func_ov122_022a1b24, LetterWrite_SlidePanelOut)

/* func_ov122_022a1b50 (LETTER_WRITE_STATE_08): the panel at 0, then it slides out (state 9). */
void LetterWrite_StartPanelSlideOut(LetterWriteScene *self)
{
    self->unk_98 = 0;
    self->base.state = LETTER_WRITE_STATE_PANEL_SLIDE_OUT;
}
CLEAN_AS(func_ov122_022a1b50, LetterWrite_StartPanelSlideOut)

/* func_ov122_022a1b60 (state 7): the panel slides up 0x20 pixels a frame; once at 0, phase 2 and
 * its buttons by the pen (LetterWrite_BeginSub04) while state flag 2 is clear, else by the
 * buttons (LetterWrite_BeginPanelKeys). */
void LetterWrite_SlidePanelIn(LetterWriteScene *self)
{
    if (self->unk_98 > 0x20) {
        self->unk_98 -= 0x20;
        return;
    }
    self->unk_98 = 0;
    MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_2);
    if (StateFlags_IsClear2()) {
        LetterWrite_BeginSub04(self);
    } else {
        LetterWrite_BeginPanelKeys(self);
    }
}
CLEAN_AS(func_ov122_022a1b60, LetterWrite_SlidePanelIn)

/* func_ov122_022a1ba4 (LETTER_WRITE_STATE_PANEL_MESSAGE): once the scroll has stopped, the
 * panel's message 0x22 shown and drawn by `unk_98` from 0xc0, sliding in (state 7). */
void LetterWrite_StartPanelMessage(LetterWriteScene *self)
{
    if (LetterWrite_IsScrolling(self) == 0) {
        LetterWrite_ShowPanelMessage(self);
        LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_02);
        self->unk_98 = 0xc0;
        self->base.state = LETTER_WRITE_STATE_PANEL_SLIDE_IN;
    }
}
CLEAN_AS(func_ov122_022a1ba4, LetterWrite_StartPanelMessage)

/* func_ov122_022a1bd4 (state 5): the keyboard wipes out; when done, its layer hidden and its
 * scroll reset, the panel no longer drawn by `unk_94`, and the state is `next_state`. Else the
 * keyboard's layer follows the wipe, whose y is kept. */
void LetterWrite_KeyboardWipeOut(LetterWriteScene *self)
{
    if (MenuScene_StepWipe(letter_write_scene(self), 0) != 0) {
        DisplayLayer_Hide(LAYER_SUB_BG3);
        DisplayLayer_SetScroll(LAYER_SUB_BG3, 0, 0);
        LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_01);
        self->base.state = self->next_state;
    } else {
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
        self->unk_94 = MenuScene_WipeOffsetY(letter_write_scene(self));
    }
}
CLEAN_AS(func_ov122_022a1bd4, LetterWrite_KeyboardWipeOut)

/* func_ov122_022a1c24 (LETTER_WRITE_STATE_LEAVE): while the screen is dimmed the letter scrolls
 * back to the top; else the keyboard starts to wipe out on window 2 (state 5). */
void LetterWrite_LeaveKeyboard(LetterWriteScene *self)
{
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_DIMMED) == 0) {
        MenuScene_StartWipeOnWindow2(letter_write_scene(self), 8, 0, 0, LETTER_WRITE_WIPE_MARGIN);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
        self->base.state = LETTER_WRITE_STATE_KEYBOARD_WIPE_OUT;
    } else {
        LetterWrite_ScrollTo(self, 0);
    }
}
CLEAN_AS(func_ov122_022a1c24, LetterWrite_LeaveKeyboard)

/* func_ov122_022a1c68 (state 3): the letter wipes out; when done, its two backgrounds hidden and
 * their scroll reset, phase 5. Else they follow the wipe, whose y is kept for the panel. */
void LetterWrite_LetterWipeOut(LetterWriteScene *self)
{
    if (MenuScene_StepWipe(letter_write_scene(self), 0) != 0) {
        DisplayLayer_Hide(LAYER_SUB_BG1);
        DisplayLayer_Hide(LAYER_SUB_BG0);
        DisplayLayer_SetScroll(LAYER_SUB_BG1, 0, 0);
        DisplayLayer_SetScroll(LAYER_SUB_BG0, 0, 0);
        MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_RUN);
    } else {
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG1, 0, 0);
        MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG0, 0, 0);
        self->unk_98 = MenuScene_WipeOffsetY(letter_write_scene(self));
    }
}
CLEAN_AS(func_ov122_022a1c68, LetterWrite_LetterWipeOut)

/* func_ov122_022a1cc8 (LETTER_WRITE_STATE_TAB_SWITCH): the letter starts to wipe out on window
 * 2 (state 3). */
void LetterWrite_StartLetterWipeOut(LetterWriteScene *self)
{
    MenuScene_StartWipeOnWindow2(letter_write_scene(self), 3, 0, 0, LETTER_WRITE_WIPE_MARGIN);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG1, 0, 0);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG0, 0, 0);
    MenuScene_SetState(letter_write_scene(self), LETTER_WRITE_STATE_LETTER_WIPE_OUT);
}
CLEAN_AS(func_ov122_022a1cc8, LetterWrite_StartLetterWipeOut)

/* func_ov122_022a1d04 (state 1): the scene wipes in; when done, phase 2 and the input starts
 * (LetterWrite_Start, LetterWrite_BeginInput). The keyboard follows the wipe, the letter 16
 * pixels above it; the wipe's y kept. */
void LetterWrite_WipeIn(LetterWriteScene *self)
{
    if (MenuScene_StepWipeBack(letter_write_scene(self), 0) != 0) {
        MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_2);
        LetterWrite_Start(self);
        LetterWrite_BeginInput(self);
    }
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG1, 0, -0x10);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG0, 0, -0x10);
    self->unk_94 = MenuScene_WipeOffsetY(letter_write_scene(self));
}
CLEAN_AS(func_ov122_022a1d04, LetterWrite_WipeIn)

/* func_ov122_022a1d60 (state 0): the backgrounds set up and the screens loaded, the keyboard set
 * up in the mode main keeps and drawn on background 3, the three backgrounds shown and wiping in
 * on window 2 (the letter 16 pixels above the keyboard), the keyboard's screen loaded, the
 * panel's layout set and the panel following the wipe (state 1). */
void LetterWrite_StartWipeIn(LetterWriteScene *self)
{
    LetterWrite_SetLayers();
    LetterWrite_LoadScreens(self);
    func_ov095_0229c420(self->keyboard, LAYER_SUB_BG3);
    func_ov095_0229bf7c(self->keyboard, LAYER_SUB_BG3);
    MenuScene_StartWipeCoveredOnWindow2(letter_write_scene(self), 0xb, 0, 0, LETTER_WRITE_WIPE_MARGIN);
    DisplayLayer_Show(LAYER_SUB_BG3);
    DisplayLayer_Show(LAYER_SUB_BG1);
    DisplayLayer_Show(LAYER_SUB_BG0);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG3, 0, 0);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG1, 0, -0x10);
    MenuScene_ScrollWipe(letter_write_scene(self), LAYER_SUB_BG0, 0, -0x10);
    LetterWrite_LoadKeyboardScreen(self);
    LetterWrite_SetPanelLayout(self);
    LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_01);
    self->unk_94 = MenuScene_WipeOffsetY(letter_write_scene(self));
    MenuScene_SetState(letter_write_scene(self), LETTER_WRITE_STATE_WIPE_IN);
}
CLEAN_AS(func_ov122_022a1d60, LetterWrite_StartWipeIn)

/* func_ov122_022a1e00: the menu closes (the parent switched to tab 7), the letter scrolled back
 * to the top without its text cursor, the scene wipes out (state 13) after phase 1; the pointer
 * hidden and the taboo words filtered out. */
void LetterWrite_ExitMenu(LetterWriteScene *self)
{
    func_ov090_022993cc(letter_write_parent(self), LETTER_WRITE_TAB_CLOSE);
    LetterWrite_ScrollTo(self, 0);
    LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_CURSOR_SHOWN);
    self->base.state = LETTER_WRITE_STATE_EXIT;
    MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_1);
    LetterWrite_HidePointer(self);
    LetterWrite_FilterTaboo(self);
}
CLEAN_AS(func_ov122_022a1e00, LetterWrite_ExitMenu)

/* func_ov122_022a1e40: the menu switches to `tab`: the parent told, main's value C50 kept across
 * it, the letter wipes out (state 2) after phase 1. Whether it switched: not for no tab or tab
 * 8.
 * QUIRK: the parent is asked for before the tab is checked, and gets the tab's low byte. */
int LetterWrite_SwitchTab(LetterWriteScene *self, int tab)
{
    Process *parent = letter_write_parent(self);
    if (tab == LETTER_WRITE_TAB_NONE || tab == LETTER_WRITE_TAB_8) {
        return 0;
    }
    u8 kept = GroupParams_C50();
    func_ov090_022993cc(parent, (u8) tab);
    GroupParams_SetC50((char) kept);
    self->base.state = LETTER_WRITE_STATE_TAB_SWITCH;
    MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_1);
    return 1;
}
CLEAN_AS(func_ov122_022a1e40, LetterWrite_SwitchTab)

/* func_ov122_022a1e90: the menu close's delay counted; when main asked the menu to close in a
 * sub state that may be left (0-4, 6, 9 and 0x0b-0x13), the menu closes (LetterWrite_ExitMenu)
 * and the answer is 1, else 0. */
int LetterWrite_CloseOnRequest(LetterWriteScene *self)
{
    StateFlags_CountMenuCloseDelay();
    if (!StateFlags_MenuCloseAsked()) {
        return 0;
    }
    switch (self->base.sub_state) {
        case LETTER_WRITE_SUB_TOUCH:
        case LETTER_WRITE_SUB_KEY_TOUCH_HELD:
        case LETTER_WRITE_SUB_SCROLL_DRAG:
        case LETTER_WRITE_SUB_MARK_DRAG:
        case LETTER_WRITE_SUB_04:
        case LETTER_WRITE_SUB_KEYS:
        case LETTER_WRITE_SUB_KEY_REPEAT:
        case LETTER_WRITE_SUB_BACKSPACE_REPEAT:
        case LETTER_WRITE_SUB_0C:
        case LETTER_WRITE_SUB_MARK_KEYS:
        case LETTER_WRITE_SUB_WHILE_L:
        case LETTER_WRITE_SUB_WHILE_R:
        case LETTER_WRITE_SUB_SCROLL_PRESS:
        case LETTER_WRITE_SUB_SCROLL_HELD:
        case LETTER_WRITE_SUB_SCROLL_RELEASE:
        case LETTER_WRITE_SUB_PANEL_KEYS:
            LetterWrite_ExitMenu(self);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov122_022a1e90, LetterWrite_CloseOnRequest)

/* func_ov122_022a1ef4 (vtable slot 0x5c, phase 4): the header and the footer kept as the
 * player's defaults, then the scene asks to be deleted. Answers 1. */
int LetterWrite_End(LetterWriteScene *self)
{
    LetterWrite_SaveDefaults(self);
    Process_RequestDelete((Process *) (void *) self);
    return 1;
}
CLEAN_AS(func_ov122_022a1ef4, LetterWrite_End)

/* func_ov122_022a1f0c (vtable slot 0x58, phase 1): nothing. */
int LetterWrite_Phase1Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov122_022a1f0c, LetterWrite_Phase1Idle)

/* func_ov122_022a1f10 (vtable slot 0x54, phase 0): nothing. */
int LetterWrite_Phase0Idle(void)
{
    return 1;
}
CLEAN_AS(func_ov122_022a1f10, LetterWrite_Phase0Idle)

/* Obj_ov122_022a2738::func_ov122_022a1f14 (vtable slot 0x50, phase 2): a frame of the scene in
 * use, unless the menu closes on main's request: the sprites updated, the sub state, then the
 * view, the keyboard and the choice drawn. Answers 1. */
int LetterWrite_RunInteractive(LetterWriteScene *self)
{
    if (LetterWrite_CloseOnRequest(self) != 0) {
        return 1;
    }
    LetterWrite_UpdateSprites(self);
    LetterWrite_RunSubState(self);
    LetterWrite_Draw(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov122_022a273819func_ov122_022a1f14Ev, LetterWrite_RunInteractive)

/* Obj_ov122_022a2738::func_ov122_022a1f40: the sub state's function (LetterWriteSubState)
 * through the table of member functions, filled once from its constants.
 * REQUIRES: the sub state is below 0x1b; the game reads past the table for others. */
void LetterWrite_RunSubState(LetterWriteScene *self)
{
    static const MemberPointer *const sub_states[LETTER_WRITE_SUB_STATES] = {
        &data_ov122_022a2670, &data_ov122_022a2678, &data_ov122_022a2668, &data_ov122_022a2660, &data_ov122_022a2658,
        &data_ov122_022a25e0, &data_ov122_022a2648, &data_ov122_022a25d8, &data_ov122_022a2638, &data_ov122_022a25d0,
        &data_ov122_022a2628, &data_ov122_022a2620, &data_ov122_022a2618, &data_ov122_022a25b8, &data_ov122_022a2608,
        &data_ov122_022a25f0, &data_ov122_022a2688, &data_ov122_022a2680, &data_ov122_022a25e8, &data_ov122_022a25a8,
        &data_ov122_022a2640, &data_ov122_022a25a0, &data_ov122_022a25c8, &data_ov122_022a25c0, &data_ov122_022a25f8,
        &data_ov122_022a2600, &data_ov122_022a2650,
    };
    MemberTable_InitOnce(&data_ov122_022a27e0, data_ov122_022a2860, sub_states, LETTER_WRITE_SUB_STATES);
    MemberPointer_CallVoid(&data_ov122_022a2860[self->base.sub_state], self);
}
CLEAN_AS(_ZN18Obj_ov122_022a273819func_ov122_022a1f40Ev, LetterWrite_RunSubState)

/* Obj_ov122_022a2738::func_ov122_022a2110 (vtable slot 0x4c, the run phase): a frame of the
 * scene's states (LetterWriteState) through the table of member functions (filled once from
 * its constants), after the panel's texts are closed and before LetterWrite_Idle. Answers 1.
 * REQUIRES: the state is below 0x0f; the game reads past the table for others. */
int LetterWrite_RunState(LetterWriteScene *self)
{
    static const MemberPointer *const states[LETTER_WRITE_STATES] = {
        &data_ov122_022a26f0, &data_ov122_022a26f8, &data_ov122_022a2630, &data_ov122_022a26e8, &data_ov122_022a26e0,
        &data_ov122_022a26d8, &data_ov122_022a26d0, &data_ov122_022a26c8, &data_ov122_022a26c0, &data_ov122_022a26b8,
        &data_ov122_022a2610, &data_ov122_022a26a8, &data_ov122_022a26a0, &data_ov122_022a2698, &data_ov122_022a2690,
    };
    MemberTable_InitOnce(&data_ov122_022a27e4, data_ov122_022a27e8, states, LETTER_WRITE_STATES);
    LetterWrite_ClosePanelTexts(self);
    MemberPointer_CallVoid(&data_ov122_022a27e8[self->base.state], self);
    LetterWrite_Idle(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov122_022a273819func_ov122_022a2110Ev, LetterWrite_RunState)

/* func_ov122_022a223c (vtable slot 0x24): the scene's draw.
 *
 * - The choice drawn.
 * - With the keyboard drawn (LETTER_WRITE_FLAG_01), at 0x60 below the wipe's y (`unk_94`): a
 *   cell above it, its mode tabs and its frame, and, with the keys in use, a cell over it.
 * - While the letter scrolls, a step of the scroll and the letter's two backgrounds scrolled by
 *   it; past 0x40 the screen is dimmed outside window 0 of the sub screen (once), else no longer.
 * - With the keyboard drawn, the scroll button placed by the wipe and the scroll (its face kept
 *   by the keyboard) and drawn through its class (slot 2).
 * - With the keys in use, the pointer (following the scroll button's face with
 *   LETTER_WRITE_FLAG_POINTER_ON_BUTTON) drawn.
 * - The panel at `unk_94` with LETTER_WRITE_FLAG_01 and at `unk_98` with LETTER_WRITE_FLAG_02.
 * - With the text cursor shown, the blink counted and the cursor drawn at its place in the
 *   letter, less the scroll, while bit 4 of the count is set.
 *
 * Answers 1. */
int LetterWrite_DrawScene(LetterWriteScene *self)
{
    PagedChoice_Draw(letter_write_choice(self));

    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_01) != 0) {
        int y = (int) ((u32) self->unk_94 + 0x60);
        OamBuffer_DrawCell(1, data_ov122_022a2700, 0x80, (int) ((u32) y - 0x10), -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
        func_ov095_0229b1c8(self->keyboard, 0x80, y, 1);
        func_ov095_0229ae84(self->keyboard, (void *) (uintptr_t) 0x80, (void *) (uintptr_t) (u32) y);
        if (StateFlags_Test2()) {
            OamBuffer_DrawObjAffine(1, data_ov122_022a25b0, 0x80, y, -1, 1, NULL);
        }
    }

    if (LetterWrite_IsScrolling(self) != 0) {
        LetterWrite_StepScroll(self);
        DisplayLayer_SetScroll(LAYER_SUB_BG1, 0, self->scroll);
        DisplayLayer_SetScroll(LAYER_SUB_BG0, 0, self->scroll);
        if (self->scroll > 0x40) {
            if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_DIMMED) == 0) {
                LetterWrite_SetFlags(self, LETTER_WRITE_FLAG_DIMMED);
                DisplayShadow_EnableSubWindows(1);
                DisplayShadow_SetSubWindow0Planes(0x1d, 1);
                DisplayShadow_SetSubOutsidePlanes(0x1f);
                DisplayShadow_SetWindow(2, 0, 0xb0, 0xfe, 0xc0);
            }
        } else if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_DIMMED) != 0) {
            LetterWrite_ClearFlags(self, LETTER_WRITE_FLAG_DIMMED);
            DisplayShadow_DisableSubWindows(1);
        }
    }

    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_01) != 0) {
        int y = (int) ((u32) self->unk_94 - 0x58) + (self->scroll >> 1);
        DualCellSprite_SetOffset(letter_write_button_cells(self), 100, y);
        int face_x = PushButton_FaceX(&self->scroll_button);
        int face_y = PushButton_FaceY(&self->scroll_button);
        func_ov095_02299b30((int *) (void *) self->keyboard, face_x, face_y);
        letter_write_draw_object(&self->scroll_button);
    }

    if (StateFlags_Test2()) {
        if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_POINTER_ON_BUTTON) != 0) {
            int face_x = PushButton_FaceX(&self->scroll_button);
            int face_y = PushButton_FaceY(&self->scroll_button);
            Glider_PlaceAt(&self->pointer, face_x, face_y);
        }
        Glider_DrawWrapped(&self->pointer);
    }

    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_01) != 0) {
        ButtonPanel_Draw(&self->panel, self->unk_94);
    }
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_02) != 0) {
        ButtonPanel_Draw(&self->panel, self->unk_98);
    }
    if (LetterWrite_TestFlags(self, LETTER_WRITE_FLAG_CURSOR_SHOWN) != 0) {
        int x = self->cursor_x;
        int y = (int) ((u32) self->cursor_y - self->scroll);
        self->blink = (u8) (self->blink + 1);
        if (self->blink & 0x10) {
            func_ov095_0229af58(letter_write_keyboard_arg(self), x, y, 3);
        }
    }
    return 1;
}
CLEAN_AS(func_ov122_022a223c, LetterWrite_DrawScene)

/* func_ov122_022a2474 (vtable slot 0x0c): the scene closes: the parent told (both ways), then
 * what the scene's members hold let go. Answers 1. */
int LetterWrite_Close(LetterWriteScene *self)
{
    Process *parent = letter_write_parent(self);
    func_ov090_0229936c(parent);
    func_ov090_022990d0(parent);
    LetterWrite_Release(self);
    return 1;
}
CLEAN_AS(func_ov122_022a2474, LetterWrite_Close)

/* func_ov122_022a249c (vtable slot 0x00): the scene starts: its setup, state 0 and phase 1.
 * Answers 1. */
int LetterWrite_Begin(LetterWriteScene *self)
{
    LetterWrite_Setup(self);
    MenuScene_SetState(letter_write_scene(self), LETTER_WRITE_STATE_START);
    MenuScene_SetPhase(letter_write_scene(self), MENU_SCENE_PHASE_1);
    return 1;
}
CLEAN_AS(func_ov122_022a249c, LetterWrite_Begin)

/* func_ov122_022a24bc (named by the profile at 0x022a26b0): a new scene from the menu scenes'
 * heap (NULL when it has no room): the base, the scene's vtable and its members constructed in
 * order, the two labels by __cxa_vec_ctor. The keyboard at 0xc0 has no constructor. */
LetterWriteScene *LetterWrite_New(void)
{
    LetterWriteScene *self = MenuScene_Alloc(sizeof(LetterWriteScene));
    if (self == NULL) {
        return NULL;
    }
    MenuScene_Construct(&self->base);
    self->base.vtable = data_ov122_022a2738;
    for (int i = 0; i < 2; i++) {
        LayerTask_Construct((LayerTask *) (void *) self->unk_23c8[i]);
    }
    __cxa_vec_ctor(self->labels, 2, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    LetterView_Construct(&self->view);
    PushButton_Construct(&self->scroll_button);
    Glider0_Construct(&self->pointer);
    MailMsgText_Construct(&self->filter_text);
    LetterBodyText_Construct(&self->filter_wide);
    PagedChoice_Construct(letter_write_choice(self));
    ButtonPanel_Construct(&self->panel);
    ErrorMessage_Construct(&self->error);
    return self;
}
CLEAN_AS(func_ov122_022a24bc, LetterWrite_New)
