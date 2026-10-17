/* The friend code entry of overlay 133 (friend_code_entry.h): its destructors and flags, the
 * keypad's colours, the code's digits and their editing, the checks of a confirmed code, the
 * pointer sprite and the error message. */
#include "friend_code_entry.h"

#include "autoload_2/network.h"
#include "autoload_2/process.h"
#include "clean.h"
#include "main/cell_layer_sprite.h"
#include "main/group_params.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/screen_map.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/state_flags.h"
#include "ov002/key_repeat.h"
#include "ov090/menu_tabs.h"

static_assert(sizeof(MenuScene) == 0x94 && offsetof(FriendCodeEntry, wipe_y) == 0x94, "wipe_y");
static_assert(offsetof(FriendCodeEntry, flags) == 0x98 && offsetof(FriendCodeEntry, key) == 0x9c, "flags");
static_assert(offsetof(FriendCodeEntry, position) == 0x9f && offsetof(FriendCodeEntry, mark_from) == 0xa3, "cursor");
static_assert(offsetof(FriendCodeEntry, digits) == 0xa4 && offsetof(FriendCodeEntry, label) == 0xb0, "digits");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(FriendCodeEntry, pointer) == 0x11c, "label");
static_assert(sizeof(Glider) == 0x64 && offsetof(FriendCodeEntry, panel) == 0x180, "pointer");
static_assert(offsetof(FriendCodeEntry, tasks) == 0x34c && sizeof(LayerTask) == 0x24, "tasks");
static_assert(offsetof(FriendCodeEntry, keypad_screen) == 0x394 && offsetof(FriendCodeEntry, code_screen) == 0xb94, "screens");
static_assert(offsetof(FriendCodeEntry, error) == 0x1394 && sizeof(FriendCodeEntry) == 0x14b0, "size (func_ov133_0229c70c)");

/* The scene's vtable. */
extern const u8 data_ov133_0229c908[];

/* The keypad: the digit of keys 0-9; the left column of each key column on the keypad's screen,
 * and the row of each key; the key under each place of the touch grid (three by four places of
 * 32 x 16 pixels); the pointer's x and y at each key. */
extern const u8 data_ov133_0229c790[10];
extern const s32 data_ov133_0229c79c[3];
extern const s32 data_ov133_0229c814[FRIEND_CODE_KEYPAD_LAST + 1];
extern const u8 data_ov133_0229c7a8[FRIEND_CODE_KEYPAD_LAST + 1];
extern const s32 data_ov133_0229c7b4[FRIEND_CODE_KEYPAD_LAST + 1];
extern const s32 data_ov133_0229c7e4[FRIEND_CODE_KEYPAD_LAST + 1];

/* The pen's place: x. */
extern u8 data_021f6c58;

/* The network session (main/session.h). */
extern NetSession *data_020ccf94;

/* Overlay 130's: sound 0x2a (the clear key's). */
extern void func_ov130_02299dbc(void);

/* The label's destructor, handed to __cxa_vec_cleanup (the game's symbol). */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern TextLabel *func_02070be8(TextLabel *label);

/* The palettes of the keypad's keys: a digit's, the delete and clear keys', the lit key's. */
#define FRIEND_CODE_PALETTE_SPECIAL_KEY 1
#define FRIEND_CODE_PALETTE_DIGIT_KEY 2
#define FRIEND_CODE_PALETTE_LIT_KEY 3
/* ... and of the code's row: its digits, the marked ones. */
#define FRIEND_CODE_PALETTE_CODE 4
#define FRIEND_CODE_PALETTE_MARKED 8

/* The characters of the code's row: digit d is the four characters from 0x84 + 4 d (two on top,
 * two below), an empty place four times 0x176; the row's first character on the screen. */
#define FRIEND_CODE_DIGIT_CHARS 0x84
#define FRIEND_CODE_EMPTY_CHAR 0x176
#define FRIEND_CODE_ROW_FIRST (7 * SCREEN_MAP_WIDTH + 4)

/* The sounds. */
#define FRIEND_CODE_SOUND_REFUSED 0x34
#define FRIEND_CODE_SOUND_DELETED 0x35
#define FRIEND_CODE_SOUND_MARK_MOVED 0x15
#define FRIEND_CODE_SOUND_CURSOR_MOVED 0x0b
#define FRIEND_CODE_SOUND_CANCEL 0x28
#define FRIEND_CODE_SOUND_CONFIRM 0x29
#define FRIEND_CODE_SOUND_ERROR 0x73

/* The error messages of a confirmed code. */
#define FRIEND_CODE_ERROR_INVALID 0x19
#define FRIEND_CODE_ERROR_OWN_CODE 0x1d
#define FRIEND_CODE_ERROR_REGISTERED 0x14

/* A held key acts again after 13 frames, then every 2; a pressed key is lit 5 frames. */
#define FRIEND_CODE_REPEAT_FIRST 13
#define FRIEND_CODE_REPEAT_NEXT 2
#define FRIEND_CODE_LIT_FRAMES 5

static MenuScene *friend_code_scene(FriendCodeEntry *self)
{
    return &self->base;
}

static MenuTabs *friend_code_parent(FriendCodeEntry *self)
{
    return (MenuTabs *) (void *) Process_GetParent((Process *) (void *) self);
}

/* Digit `i` of the code: the game indexes it with bytes it keeps, which can stand past the
 * twelve (REQUIRES at the callers say when). */
static u8 *friend_code_digit(FriendCodeEntry *self, int i)
{
    return (u8 *) self + offsetof(FriendCodeEntry, digits) + i;
}

static int friend_code_is_marked(FriendCodeEntry *self)
{
    return self->mark_to != self->mark_from;
}

static int friend_code_at_button(FriendCodeEntry *self)
{
    return self->key == FRIEND_CODE_KEY_OK || self->key == FRIEND_CODE_KEY_BACK;
}

/* The pointer sprite's update through its class (vtable slot 3, Glider_Update for the base). */
static void friend_code_update_pointer(Glider *pointer)
{
    void (*const *vtable)(Glider *) = (void (*const *)(Glider *)) pointer->vtable;
    vtable[3](pointer);
}

/* The members' destructors, last member first, then the base's. */
static void friend_code_destroy_members(FriendCodeEntry *self)
{
    self->base.vtable = data_ov133_0229c908;
    ErrorMessage_Destruct(&self->error);
    ButtonPanel_Destroy(&self->panel);
    Glider0_Destroy(&self->pointer);
    __cxa_vec_cleanup(&self->label, 1, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    MenuScene_DestroyBase(friend_code_scene(self));
}

/* func_ov133_0229acc0 (vtable slot 0x40) */
FriendCodeEntry *FriendCodeEntry_Destroy(FriendCodeEntry *self)
{
    friend_code_destroy_members(self);
    return self;
}
CLEAN_AS(func_ov133_0229acc0, FriendCodeEntry_Destroy)

/* func_ov133_0229ad10 (vtable slot 0x44) */
FriendCodeEntry *FriendCodeEntry_Delete(FriendCodeEntry *self)
{
    friend_code_destroy_members(self);
    MenuScene_Free(self);
    return self;
}
CLEAN_AS(func_ov133_0229ad10, FriendCodeEntry_Delete)

/* func_ov133_0229ad68 */
void FriendCodeEntry_ClearFlags(FriendCodeEntry *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov133_0229ad68, FriendCodeEntry_ClearFlags)

/* func_ov133_0229ad78 */
void FriendCodeEntry_SetFlags(FriendCodeEntry *self, u16 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov133_0229ad78, FriendCodeEntry_SetFlags)

/* func_ov133_0229ad88 */
int FriendCodeEntry_TestFlags(FriendCodeEntry *self, unsigned int flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov133_0229ad88, FriendCodeEntry_TestFlags)

/* func_ov133_0229ad9c: key `key` in its own colours: the delete and clear keys', or a digit's. */
void FriendCodeEntry_UnlightKey(FriendCodeEntry *self, int key)
{
    int special = (u8) (key - FRIEND_CODE_KEY_DELETE) <= FRIEND_CODE_KEY_CLEAR - FRIEND_CODE_KEY_DELETE;
    FriendCodeEntry_ColourKey(self, key, special ? FRIEND_CODE_PALETTE_SPECIAL_KEY : FRIEND_CODE_PALETTE_DIGIT_KEY);
}
CLEAN_AS(func_ov133_0229ad9c, FriendCodeEntry_UnlightKey)

/* func_ov133_0229adb8: key `key` lit. */
void FriendCodeEntry_LightKey(FriendCodeEntry *self, int key)
{
    FriendCodeEntry_ColourKey(self, key, FRIEND_CODE_PALETTE_LIT_KEY);
}
CLEAN_AS(func_ov133_0229adb8, FriendCodeEntry_LightKey)

/* func_ov133_0229adc4: key `key`'s place on the keypad's screen in palette `palette` (the first
 * column's keys are a character wider), the screen to be loaded.
 * REQUIRES: 0 <= key <= 11; the game reads its tables on for others. */
void FriendCodeEntry_ColourKey(FriendCodeEntry *self, int key, int palette)
{
    int column = key % 3;
    int left = data_ov133_0229c79c[column];
    int right = column == 0 ? left + 4 : left + 3;
    int top = data_ov133_0229c814[key];
    ScreenMap_SetPalette(self->keypad_screen, left, top, right, top + 1, (u32) palette);
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_KEYPAD_DIRTY);
}
CLEAN_AS(func_ov133_0229adc4, FriendCodeEntry_ColourKey)

/* func_ov133_0229ae1c: no key lit: the keypad in the digits' palette, then the clear and delete
 * keys in their own. */
void FriendCodeEntry_UnlightKeypad(FriendCodeEntry *self)
{
    ScreenMap_SetPalette(self->keypad_screen, 9, 0xc, 0x15, 0x14, FRIEND_CODE_PALETTE_DIGIT_KEY);
    FriendCodeEntry_UnlightKey(self, FRIEND_CODE_KEY_CLEAR);
    FriendCodeEntry_UnlightKey(self, FRIEND_CODE_KEY_DELETE);
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_KEYPAD_DIRTY);
}
CLEAN_AS(func_ov133_0229ae1c, FriendCodeEntry_UnlightKeypad)

/* func_ov133_0229ae5c: a frame of a held key's repeat: whether it acts again now (then the next
 * time is 2 frames away). */
int FriendCodeEntry_RepeatDue(FriendCodeEntry *self)
{
    if (self->repeat == 0) {
        return 0;
    }
    self->repeat--;
    if (self->repeat != 0) {
        return 0;
    }
    self->repeat = FRIEND_CODE_REPEAT_NEXT;
    return 1;
}
CLEAN_AS(func_ov133_0229ae5c, FriendCodeEntry_RepeatDue)

/* func_ov133_0229ae8c */
void FriendCodeEntry_StopRepeat(FriendCodeEntry *self)
{
    self->repeat = 0;
}
CLEAN_AS(func_ov133_0229ae8c, FriendCodeEntry_StopRepeat)

/* func_ov133_0229ae94: the key pointed at pressed: lit alone for 5 frames, its repeat started
 * and its action done (FriendCodeEntry_UseKey); answers whether it may repeat. */
int FriendCodeEntry_PressKey(FriendCodeEntry *self)
{
    FriendCodeEntry_UnlightKeypad(self);
    self->lit_key = self->key;
    FriendCodeEntry_LightKey(self, self->lit_key);
    self->repeat = FRIEND_CODE_REPEAT_FIRST;
    self->lit_frames = FRIEND_CODE_LIT_FRAMES;
    return FriendCodeEntry_UseKey(self, 1);
}
CLEAN_AS(func_ov133_0229ae94, FriendCodeEntry_PressKey)

/* func_ov133_0229aed4: the frame's end for the screens: changed digits written, a moved cursor's
 * mark coloured (each then loads the code's screen); a screen to be loaded queued to its layer
 * (the keypad's to 4, the code's to 6), its flag cleared once the queue took it. */
void FriendCodeEntry_UpdateScreens(FriendCodeEntry *self)
{
    if (FriendCodeEntry_TestFlags(self, FRIEND_CODE_FLAG_DIGITS)) {
        FriendCodeEntry_WriteDigits(self);
        FriendCodeEntry_ClearFlags(self, FRIEND_CODE_FLAG_DIGITS);
        FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_CODE_DIRTY);
    }
    if (FriendCodeEntry_TestFlags(self, FRIEND_CODE_FLAG_CURSOR)) {
        FriendCodeEntry_ColourMark(self);
        FriendCodeEntry_ClearFlags(self, FRIEND_CODE_FLAG_CURSOR);
        FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_CODE_DIRTY);
    }
    if (FriendCodeEntry_TestFlags(self, FRIEND_CODE_FLAG_KEYPAD_DIRTY)) {
        if (LayerTask_QueueScreen(&self->tasks[0], (int) (uintptr_t) self->keypad_screen, 4, 0x800, 0)) {
            FriendCodeEntry_ClearFlags(self, FRIEND_CODE_FLAG_KEYPAD_DIRTY);
        }
    }
    if (FriendCodeEntry_TestFlags(self, FRIEND_CODE_FLAG_CODE_DIRTY)) {
        if (LayerTask_QueueScreen(&self->tasks[1], (int) (uintptr_t) self->code_screen, 6, 0x800, 0)) {
            FriendCodeEntry_ClearFlags(self, FRIEND_CODE_FLAG_CODE_DIRTY);
        }
    }
}
CLEAN_AS(func_ov133_0229aed4, FriendCodeEntry_UpdateScreens)

/* func_ov133_0229af90: the code's row (rows 7 and 8, columns 4-27, two a digit) in its palette,
 * then the marked digits, from the lower end of the mark to before the higher, in the marked
 * palette. */
void FriendCodeEntry_ColourMark(FriendCodeEntry *self)
{
    ScreenMap_SetPalette(self->code_screen, 4, 7, 0x1b, 8, FRIEND_CODE_PALETTE_CODE);
    int from = self->mark_from;
    int to = self->mark_to;
    if (to == from) {
        return;
    }
    int low = to > from ? from : to;
    int high = to > from ? to : from;
    ScreenMap_SetPalette(self->code_screen, low * 2 + 4, 7, high * 2 + 3, 8, FRIEND_CODE_PALETTE_MARKED);
}
CLEAN_AS(func_ov133_0229af90, FriendCodeEntry_ColourMark)

/* A character of the screen given `character`, its flips and palette kept. QUIRK: the game ORs
 * the whole value in, so a character past 0x3ff (digit bytes above 0xde) spills into them. */
static void friend_code_set_char(u16 *entry, int character)
{
    *entry = (u16) ((*entry & 0xfc00) | character);
}

/* func_ov133_0229afec: the code's digits written to its row as characters; the OK button's
 * sprite flag 4 set while the code is not full (its last place empty), cleared once it is. */
void FriendCodeEntry_WriteDigits(FriendCodeEntry *self)
{
    u16 *top = &self->code_screen[FRIEND_CODE_ROW_FIRST];
    for (int i = 0; i < FRIEND_CODE_DIGITS; i++) {
        u16 *bottom = top + SCREEN_MAP_WIDTH;
        if (self->digits[i] == FRIEND_CODE_NO_DIGIT) {
            friend_code_set_char(&top[0], FRIEND_CODE_EMPTY_CHAR);
            friend_code_set_char(&top[1], FRIEND_CODE_EMPTY_CHAR);
            friend_code_set_char(&bottom[0], FRIEND_CODE_EMPTY_CHAR);
            friend_code_set_char(&bottom[1], FRIEND_CODE_EMPTY_CHAR);
        } else {
            int first = self->digits[i] * 4 + FRIEND_CODE_DIGIT_CHARS;
            friend_code_set_char(&top[0], first);
            friend_code_set_char(&top[1], first + 1);
            friend_code_set_char(&bottom[0], first + 2);
            friend_code_set_char(&bottom[1], first + 3);
        }
        top += 2;
    }

    int full = self->digits[FRIEND_CODE_DIGITS - 1] != FRIEND_CODE_NO_DIGIT;
    if (ButtonPanel_HasSpriteFlag4(&self->panel, FRIEND_CODE_BUTTON_OK)) {
        if (full) {
            ButtonPanel_ClearSpriteFlag4(&self->panel, FRIEND_CODE_BUTTON_OK);
        }
    } else if (!full) {
        ButtonPanel_SetSpriteFlag4(&self->panel, FRIEND_CODE_BUTTON_OK);
    }
}
CLEAN_AS(func_ov133_0229afec, FriendCodeEntry_WriteDigits)

/* func_ov133_0229b0d4: the digits typed: the first empty place, 12 when full. */
int FriendCodeEntry_DigitCount(FriendCodeEntry *self)
{
    for (int i = 0; i < FRIEND_CODE_DIGITS; i++) {
        if (self->digits[i] == FRIEND_CODE_NO_DIGIT) {
            return i;
        }
    }
    return FRIEND_CODE_DIGITS;
}
CLEAN_AS(func_ov133_0229b0d4, FriendCodeEntry_DigitCount)

/* func_ov133_0229b0f0: `digit` typed at the cursor, over the mark when there is one (the digits
 * after it moved on, the last one dropped), the cursor after it; refused (with the sound) at the
 * code's end or, unmarked, when it is full. Answers whether it was typed.
 * REQUIRES: position <= 12; the game writes past the digits for others. */
int FriendCodeEntry_InsertDigit(FriendCodeEntry *self, u8 digit)
{
    if (self->position == FRIEND_CODE_DIGITS && !friend_code_is_marked(self)) {
        SoundSys_PlaySe(FRIEND_CODE_SOUND_REFUSED);
        return 0;
    }
    if (!friend_code_is_marked(self) && self->digits[FRIEND_CODE_DIGITS - 1] != FRIEND_CODE_NO_DIGIT) {
        SoundSys_PlaySe(FRIEND_CODE_SOUND_REFUSED);
        return 0;
    }
    if (friend_code_is_marked(self)) {
        FriendCodeEntry_DeleteMark(self);
    }
    for (int i = FRIEND_CODE_DIGITS - 1; i > self->position; i--) {
        self->digits[i] = self->digits[i - 1];
    }
    *friend_code_digit(self, self->position) = digit;
    FriendCodeEntry_SetCursor(self, (u8) (self->position + 1));
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_DIGITS);
    return 1;
}
CLEAN_AS(func_ov133_0229b0f0, FriendCodeEntry_InsertDigit)

/* func_ov133_0229b190: the marked digits deleted, those after them moved back and the places
 * freed emptied; the cursor at the mark's lower end. */
void FriendCodeEntry_DeleteMark(FriendCodeEntry *self)
{
    int from = self->mark_from;
    int to = self->mark_to;
    int low = to < from ? to : from;
    int high = to < from ? from : to;
    FriendCodeEntry_SetCursor(self, (u8) low);
    for (; high < FRIEND_CODE_DIGITS; low++, high++) {
        self->digits[low] = self->digits[high];
    }
    for (; low < FRIEND_CODE_DIGITS; low++) {
        self->digits[low] = FRIEND_CODE_NO_DIGIT;
    }
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_DIGITS);
}
CLEAN_AS(func_ov133_0229b190, FriendCodeEntry_DeleteMark)

/* func_ov133_0229b1e8: the delete key: the mark deleted, else the digit before the cursor (at
 * the code's start, the first digit, when there is one), the cursor one back; with the sound.
 * With nothing to delete answers 0, with the refusal's sound when `sound_when_empty`. */
int FriendCodeEntry_DeleteBack(FriendCodeEntry *self, int sound_when_empty)
{
    if (friend_code_is_marked(self)) {
        FriendCodeEntry_DeleteMark(self);
        SoundSys_PlaySe(FRIEND_CODE_SOUND_DELETED);
        return 1;
    }
    if (self->position == 0) {
        if (self->digits[0] == FRIEND_CODE_NO_DIGIT) {
            if (sound_when_empty) {
                SoundSys_PlaySe(FRIEND_CODE_SOUND_REFUSED);
            }
            return 0;
        }
        self->position = 1;
    }
    for (int i = self->position; i < FRIEND_CODE_DIGITS; i++) {
        self->digits[i - 1] = self->digits[i];
    }
    self->digits[FRIEND_CODE_DIGITS - 1] = FRIEND_CODE_NO_DIGIT;
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_DIGITS);
    FriendCodeEntry_SetCursor(self, (u8) (self->position - 1));
    SoundSys_PlaySe(FRIEND_CODE_SOUND_DELETED);
    return 1;
}
CLEAN_AS(func_ov133_0229b1e8, FriendCodeEntry_DeleteBack)

/* func_ov133_0229b280: every place emptied, the cursor at the start. */
void FriendCodeEntry_Clear(FriendCodeEntry *self)
{
    for (int i = 0; i < FRIEND_CODE_DIGITS; i++) {
        self->digits[i] = FRIEND_CODE_NO_DIGIT;
    }
    FriendCodeEntry_SetCursor(self, 0);
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_DIGITS);
}
CLEAN_AS(func_ov133_0229b280, FriendCodeEntry_Clear)

/* func_ov133_0229b2ac: the digits of the friend's code (empty when the friend has none), the
 * cursor at the start. */
void FriendCodeEntry_LoadCode(FriendCodeEntry *self)
{
    WifiFriendData *code = WifiFriend_GetFriendData(FriendCodeEntry_Friend(self));
    if (WifiFriendData_GetKeyDigits(code, (char *) self->digits)) {
        FriendCodeEntry_SetCursor(self, 0);
        FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_DIGITS);
    } else {
        FriendCodeEntry_Clear(self);
    }
}
CLEAN_AS(func_ov133_0229b2ac, FriendCodeEntry_LoadCode)

/* func_ov133_0229b2e4: the cursor and the mark's moving end at `position` (the mark's start
 * kept), the blink restarted shown; the sound when the end moved. */
void FriendCodeEntry_MarkTo(FriendCodeEntry *self, int position)
{
    self->position = (u8) position;
    self->blink = 0x10;
    if (self->mark_to != position) {
        SoundSys_PlaySe(FRIEND_CODE_SOUND_MARK_MOVED);
    }
    self->mark_to = (u8) position;
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_CURSOR);
}
CLEAN_AS(func_ov133_0229b2e4, FriendCodeEntry_MarkTo)

/* func_ov133_0229b320: the cursor at `position`, unmarked, the blink restarted shown. */
void FriendCodeEntry_SetCursor(FriendCodeEntry *self, u8 position)
{
    self->position = position;
    self->blink = 0x10;
    self->mark_to = position;
    self->mark_from = position;
    FriendCodeEntry_SetFlags(self, FRIEND_CODE_FLAG_CURSOR);
}
CLEAN_AS(func_ov133_0229b320, FriendCodeEntry_SetCursor)

/* func_ov133_0229b344: the cursor's place under the pen: 16 pixels a digit from x 24, at most
 * the digits typed. */
int FriendCodeEntry_PositionAtTouch(FriendCodeEntry *self)
{
    int x = data_021f6c58 - 0x18;
    if (x < 0) {
        x = 0;
    }
    int position = x >> 4;
    int count = FriendCodeEntry_DigitCount(self);
    return position > count ? count : position;
}
CLEAN_AS(func_ov133_0229b344, FriendCodeEntry_PositionAtTouch)

/* func_ov133_0229b36c: the cursor moved by the d-pad keys `keys` (left to the start, right up to
 * the digits typed), the pointer put at it; whether it moved. */
int FriendCodeEntry_MoveCursor(FriendCodeEntry *self, int keys)
{
    u8 before = self->position;
    if (KeyRepeat_HasLeft(keys)) {
        if (self->position != 0) {
            self->position--;
        }
    } else if (KeyRepeat_HasRight(keys)) {
        if (FriendCodeEntry_DigitCount(self) > self->position) {
            self->position++;
        }
    }
    if (before == self->position) {
        return 0;
    }
    int x = FriendCodeEntry_PointerX(self);
    int y = FriendCodeEntry_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    return 1;
}
CLEAN_AS(func_ov133_0229b36c, FriendCodeEntry_MoveCursor)

/* func_ov133_0229b3f8: the action of the key pointed at. The clear key empties the code (when
 * `first`, the press itself, with overlay 130's sound) and does not repeat (answers 0); the
 * delete key deletes; a digit's key types its digit, with sound 2c when typed. Answers 1 but for
 * the clear key. */
int FriendCodeEntry_UseKey(FriendCodeEntry *self, int first)
{
    u8 key = self->key;
    switch (key) {
        case FRIEND_CODE_KEY_CLEAR:
            if (first) {
                FriendCodeEntry_Clear(self);
                func_ov130_02299dbc();
            }
            self->repeat = 0;
            return 0;
        case FRIEND_CODE_KEY_DELETE:
            FriendCodeEntry_DeleteBack(self, 1);
            return 1;
        default:
            if (key <= FRIEND_CODE_KEY_0) {
                if (FriendCodeEntry_InsertDigit(self, data_ov133_0229c790[key])) {
                    SoundSys_PlaySound2c(NULL);
                }
            }
            return 1;
    }
}
CLEAN_AS(func_ov133_0229b3f8, FriendCodeEntry_UseKey)

/* func_ov133_0229b44c: A at the pointer's key. A key of the keypad is pressed: 1 when it may
 * repeat (sub state 7), else 2. The code's row: 0. OK: the code confirmed when the button is
 * enabled (1, else 0). Back: cancelled (1). */
int FriendCodeEntry_PressSelected(FriendCodeEntry *self)
{
    u8 key = self->key;
    if (key <= FRIEND_CODE_KEYPAD_LAST) {
        if (FriendCodeEntry_PressKey(self)) {
            MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_KEY_HELD);
            return 1;
        }
        return 2;
    }
    switch (key) {
        case FRIEND_CODE_KEY_CODE:
            break;
        case FRIEND_CODE_KEY_OK:
            if (ButtonPanel_HasSpriteFlag4(&self->panel, FRIEND_CODE_BUTTON_OK) == 0) {
                FriendCodeEntry_Confirm(self);
                return 1;
            }
            return 0;
        case FRIEND_CODE_KEY_BACK:
            FriendCodeEntry_Cancel(self);
            return 1;
    }
    return 0;
}
CLEAN_AS(func_ov133_0229b44c, FriendCodeEntry_PressSelected)

/* func_ov133_0229b4b0: cancelled: main told so (GroupParams_SetC4C(0)), the back button
 * pressed, the scene wiping out after the press (state 3, sub state 10), the menu back at the
 * roster, a friend being added cleared; the sound. */
void FriendCodeEntry_Cancel(FriendCodeEntry *self)
{
    GroupParams_SetC4C(0);
    ButtonPanel_Select(&self->panel, FRIEND_CODE_BUTTON_BACK);
    MenuScene_SetState(friend_code_scene(self), FRIEND_CODE_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_BUTTON_PRESS);
    FriendCodeEntry_SelectTab(self, FRIEND_CODE_TAB_ROSTER);
    if (GroupParams_Mode() == FRIEND_CODE_MODE_NEW) {
        WifiFriend_Clear(FriendCodeEntry_Friend(self));
    }
    SoundSys_PlaySe(FRIEND_CODE_SOUND_CANCEL);
}
CLEAN_AS(func_ov133_0229b4b0, FriendCodeEntry_Cancel)

/* The error `message` shown with the error sound. */
static void friend_code_refuse(FriendCodeEntry *self, int message)
{
    FriendCodeEntry_ShowError(self, message, 0);
    SoundSys_PlaySe(FRIEND_CODE_SOUND_ERROR);
}

/* func_ov133_0229b500: OK: the digits made into a code (with the player's account); refused with
 * an error message when they make none, when it is the player's own or another friend's code.
 * Else the friend given the code, main told so (GroupParams_SetC4C(1)), the OK button pressed,
 * the scene wiping out after the press (state 3, sub state 10) with the sound. A friend being
 * added goes on to its name entry (tab 12); else the menu is told the roster changed and goes
 * back to it, flag 0x200 set, and while online (the session has this system's slot, in network
 * modes 3 and 4) the friend is handed to the Wi-Fi connection: when that fails it is retried
 * each frame (sub state 12). */
void FriendCodeEntry_Confirm(FriendCodeEntry *self)
{
    WifiFriendData code;

    u8 *record = PlayerRecords_Current();
    WifiFriendData_Construct(&code);
    WifiFriendData_Clear(&code);
    if (WifiFriendData_SetFromKeyDigits(&code, self->digits, WifiAccount_GetUserData(PlayerRecord_WifiAccount(record))) == 0) {
        friend_code_refuse(self, FRIEND_CODE_ERROR_INVALID);
        WifiFriendData_Destruct(&code);
        return;
    }
    if (FriendCodeEntry_IsOwnCode(self)) {
        friend_code_refuse(self, FRIEND_CODE_ERROR_OWN_CODE);
        WifiFriendData_Destruct(&code);
        return;
    }
    if (FriendCodeEntry_IsOtherFriendsCode(self, &code)) {
        friend_code_refuse(self, FRIEND_CODE_ERROR_REGISTERED);
        WifiFriendData_Destruct(&code);
        return;
    }

    WifiFriend *friend = FriendCodeEntry_Friend(self);
    WifiFriendData *stored = WifiFriend_GetFriendData(friend);
    WifiFriendData_SetFromKeyDigits(stored, self->digits, WifiAccount_GetUserData(PlayerRecord_WifiAccount(record)));
    GroupParams_SetC4C(1);
    ButtonPanel_Select(&self->panel, FRIEND_CODE_BUTTON_OK);
    MenuScene_SetState(friend_code_scene(self), FRIEND_CODE_STATE_START_WIPE_OUT);
    MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_BUTTON_PRESS);
    SoundSys_PlaySe(FRIEND_CODE_SOUND_CONFIRM);
    if (GroupParams_Mode() == FRIEND_CODE_MODE_NEW) {
        FriendCodeEntry_SelectTab(self, FRIEND_CODE_TAB_NAME_ENTRY);
    } else {
        MenuTabs_MarkRosterChanged(friend_code_parent(self));
        FriendCodeEntry_SelectTab(self, FRIEND_CODE_TAB_ROSTER);
        StateFlags_Set200();
        NetSession *session = data_020ccf94;
        if (Session_IsSlotTaken(session, session->local_slot)) {
            switch (Net_GetMode()) {
                case 3:
                case 4: {
                    int index = GroupParams_Arg();
                    if (Wfc_SetFriend(index, WifiFriendData_GetData(WifiFriend_GetFriendData(friend))) == 0) {
                        MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_SET_FRIEND);
                        WifiFriendData_Destruct(&code);
                        return;
                    }
                    break;
                }
            }
        }
    }
    WifiFriendData_Destruct(&code);
}
CLEAN_AS(func_ov133_0229b500, FriendCodeEntry_Confirm)

/* func_ov133_0229b660: whether the digits, read as a decimal number, are the player's own key. */
int FriendCodeEntry_IsOwnCode(FriendCodeEntry *self)
{
    u8 *record = PlayerRecords_Current();
    u64 number = 0;
    for (int i = 0; i < FRIEND_CODE_DIGITS; i++) {
        number = number * 10 + self->digits[i];
    }
    return number == WifiAccount_GetUserKey(PlayerRecord_WifiAccount(record));
}
CLEAN_AS(func_ov133_0229b660, FriendCodeEntry_IsOwnCode)

/* func_ov133_0229b6b8: whether another friend of the roster (one set, not friend `arg`) has
 * `code`. */
int FriendCodeEntry_IsOtherFriendsCode(FriendCodeEntry *self, WifiFriendData *code)
{
    (void) self;
    u8 *record = PlayerRecords_Current();
    int skip = GroupParams_Arg();
    WifiFriend *friends = WifiFriendList_GetEntries(PlayerRecord_WifiFriends(record));
    for (int i = 0; i < WIFI_FRIENDS; i++) {
        if (WifiFriendData_IsSet(WifiFriend_GetFriendData(&friends[i])) && i != skip &&
            WifiFriendData_Matches(code, WifiFriend_GetFriendData(&friends[i]))) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov133_0229b6b8, FriendCodeEntry_IsOtherFriendsCode)

/* func_ov133_0229b714: friend `arg` of the current player's roster. */
WifiFriend *FriendCodeEntry_Friend(FriendCodeEntry *self)
{
    (void) self;
    WifiFriendList *list = PlayerRecord_WifiFriends(PlayerRecords_Current());
    int index = GroupParams_Arg();
    WifiFriend *friends = WifiFriendList_GetEntries(list);
    return &friends[index];
}
CLEAN_AS(func_ov133_0229b714, FriendCodeEntry_Friend)

/* func_ov133_0229b73c: the key at the touch (`x`, `y`), kept as the pointer's: a key of the
 * keypad (96 x 64 pixels from (80, 96)), else the code's row (y 64-80), else none (not kept). */
int FriendCodeEntry_KeyAtTouch(FriendCodeEntry *self, int x, int y)
{
    int dx = x - 0x50;
    int dy = y - 0x60;
    if (dx >= 0 && dx < 0x60 && dy >= 0 && dy < 0x40) {
        self->key = data_ov133_0229c7a8[(dx >> 5) + 3 * (dy >> 4)];
        return self->key;
    }
    if (y >= 0x40 && y <= 0x50) {
        self->key = FRIEND_CODE_KEY_CODE;
        return self->key;
    }
    return FRIEND_CODE_KEY_NONE;
}
CLEAN_AS(func_ov133_0229b73c, FriendCodeEntry_KeyAtTouch)

/* func_ov133_0229b790: the pointer's key moved by the d-pad keys `keys` (none: 0); whether it
 * moved. On the keypad left and right stay in the row (right from the last column goes to OK),
 * up from the top row goes to the code's row and down from the bottom row to Back. On the code's
 * row down goes to the top row's key under the pointer, left and right move the cursor (with the
 * sound, the mark dropped; the key does not change). OK: left to Back, up to the clear key. Back:
 * right to OK, up to the delete key. */
int FriendCodeEntry_MoveKey(FriendCodeEntry *self, int keys)
{
    u8 before = self->key;
    if (keys == 0) {
        return 0;
    }
    if (before <= FRIEND_CODE_KEYPAD_LAST) {
        if (KeyRepeat_HasLeft(keys)) {
            if (self->key % 3 > 0) {
                self->key--;
            }
        } else if (KeyRepeat_HasRight(keys)) {
            if (self->key % 3 < 2) {
                self->key++;
            } else {
                self->key = FRIEND_CODE_KEY_OK;
            }
        }
        if (self->key <= FRIEND_CODE_KEYPAD_LAST) {
            if (KeyRepeat_HasUp(keys)) {
                if (self->key <= 2) {
                    self->key = FRIEND_CODE_KEY_CODE;
                } else {
                    self->key = (u8) (self->key - 3);
                }
            } else if (KeyRepeat_HasDown(keys)) {
                if (self->key < FRIEND_CODE_KEY_0) {
                    self->key = (u8) (self->key + 3);
                } else {
                    self->key = FRIEND_CODE_KEY_BACK;
                }
            }
        }
    } else if (before == FRIEND_CODE_KEY_CODE) {
        if (KeyRepeat_HasDown(keys)) {
            int x = Glider_ScreenX(&self->pointer);
            if (x <= 0x70) {
                self->key = 0;
            } else if (x <= 0x90) {
                self->key = 1;
            } else {
                self->key = 2;
            }
        } else if (FriendCodeEntry_MoveCursor(self, keys)) {
            SoundSys_PlaySe(FRIEND_CODE_SOUND_CURSOR_MOVED);
            FriendCodeEntry_SetCursor(self, self->position);
        }
    } else if (before == FRIEND_CODE_KEY_OK) {
        if (KeyRepeat_HasLeft(keys)) {
            self->key = FRIEND_CODE_KEY_BACK;
        } else if (KeyRepeat_HasUp(keys)) {
            self->key = FRIEND_CODE_KEY_CLEAR;
        }
    } else if (before == FRIEND_CODE_KEY_BACK) {
        if (KeyRepeat_HasRight(keys)) {
            self->key = FRIEND_CODE_KEY_OK;
        } else if (KeyRepeat_HasUp(keys)) {
            self->key = FRIEND_CODE_KEY_DELETE;
        }
    }
    return before != self->key;
}
CLEAN_AS(func_ov133_0229b790, FriendCodeEntry_MoveKey)

/* func_ov133_0229b938: the pointer shown (the first of its set) and updated. */
void FriendCodeEntry_ShowPointer(FriendCodeEntry *self)
{
    Glider_ShowFirstOfSet(&self->pointer);
    friend_code_update_pointer(&self->pointer);
}
CLEAN_AS(func_ov133_0229b938, FriendCodeEntry_ShowPointer)

/* func_ov133_0229b958: the pointer pressed (the third of its set), until its press is over (sub
 * state 6). Answers MenuScene_SetSubState's pointer as an int. */
int FriendCodeEntry_PressPointer(FriendCodeEntry *self)
{
    Glider_ShowThirdOfSet(&self->pointer);
    return (int) (uintptr_t) MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_POINTER_PRESS);
}
CLEAN_AS(func_ov133_0229b958, FriendCodeEntry_PressPointer)

/* func_ov133_0229b978: A: at the code's row the mark moves with the d-pad while A is held (sub
 * state 9); elsewhere the pointer pressed (the second of its set), the key's action once the
 * press is over (sub state 5). */
void FriendCodeEntry_PressAtKey(FriendCodeEntry *self)
{
    if (self->key == FRIEND_CODE_KEY_CODE) {
        MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_MARK_KEYS);
    } else {
        Glider_ShowSecondOfSet(&self->pointer);
        MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_KEY_PRESS);
    }
}
CLEAN_AS(func_ov133_0229b978, FriendCodeEntry_PressAtKey)

/* func_ov133_0229b9a8: the pointer turned to the buttons' set (B) or the keys' (A) and eased to
 * its key in three steps, the sub state kept to come back to once it stops (sub state 4). */
void FriendCodeEntry_GlidePointer(FriendCodeEntry *self)
{
    if (friend_code_at_button(self)) {
        Glider_TurnToSetB(&self->pointer);
    } else {
        Glider_TurnToSetA(&self->pointer);
    }
    int x = FriendCodeEntry_PointerX(self);
    int y = FriendCodeEntry_PointerY(self);
    Glider_EaseTo(&self->pointer, x, y, 3, 1);
    self->return_sub_state = self->base.sub_state;
    MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_POINTER_GLIDE);
}
CLEAN_AS(func_ov133_0229b9a8, FriendCodeEntry_GlidePointer)

/* func_ov133_0229ba10: the pointer hidden (no animation) and updated. */
void FriendCodeEntry_HidePointer(FriendCodeEntry *self)
{
    Glider_SetAnim(&self->pointer, GLIDER_ANIM_NONE);
    friend_code_update_pointer(&self->pointer);
}
CLEAN_AS(func_ov133_0229ba10, FriendCodeEntry_HidePointer)

/* func_ov133_0229ba34: where the pointer points at its key: y (the code's row at 64, a button's
 * place by the panel; 96 for others). */
int FriendCodeEntry_PointerY(FriendCodeEntry *self)
{
    u8 key = self->key;
    if (key <= FRIEND_CODE_KEYPAD_LAST) {
        return data_ov133_0229c7e4[key];
    }
    switch (key) {
        case FRIEND_CODE_KEY_CODE:
            return 0x40;
        case FRIEND_CODE_KEY_OK:
            return ButtonPanel_ButtonY(&self->panel, FRIEND_CODE_BUTTON_OK);
        case FRIEND_CODE_KEY_BACK:
            return ButtonPanel_ButtonY(&self->panel, FRIEND_CODE_BUTTON_BACK);
    }
    return 0x60;
}
CLEAN_AS(func_ov133_0229ba34, FriendCodeEntry_PointerY)

/* func_ov133_0229ba84: ... x (at the code's row the cursor's, 16 pixels a digit from 32; 128 for
 * others). */
int FriendCodeEntry_PointerX(FriendCodeEntry *self)
{
    u8 key = self->key;
    if (key <= FRIEND_CODE_KEYPAD_LAST) {
        return data_ov133_0229c7b4[key];
    }
    switch (key) {
        case FRIEND_CODE_KEY_CODE:
            return (self->position << 4) + 0x20;
        case FRIEND_CODE_KEY_OK:
            return ButtonPanel_ButtonX(&self->panel, FRIEND_CODE_BUTTON_OK);
        case FRIEND_CODE_KEY_BACK:
            return ButtonPanel_ButtonX(&self->panel, FRIEND_CODE_BUTTON_BACK);
    }
    return 0x80;
}
CLEAN_AS(func_ov133_0229ba84, FriendCodeEntry_PointerX)

/* func_ov133_0229badc: the pointer put at its key with the buttons' animation (7) or the keys'
 * (1), and shown. */
void FriendCodeEntry_PlacePointer(FriendCodeEntry *self)
{
    int x = FriendCodeEntry_PointerX(self);
    int y = FriendCodeEntry_PointerY(self);
    Glider_PlaceAt(&self->pointer, x, y);
    if (friend_code_at_button(self)) {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_B);
    } else {
        Glider_SetAnim(&self->pointer, GLIDER_ANIM_SET_A);
    }
    FriendCodeEntry_ShowPointer(self);
}
CLEAN_AS(func_ov133_0229badc, FriendCodeEntry_PlacePointer)

/* func_ov133_0229bb34: a label for this frame: the scene has one, and answers it again once it
 * is in use. */
TextLabel *FriendCodeEntry_NextLabel(FriendCodeEntry *self)
{
    if (self->label_count < 1) {
        self->label_count++;
    }
    return &self->label;
}
CLEAN_AS(func_ov133_0229bb34, FriendCodeEntry_NextLabel)

/* func_ov133_0229bb64: no label in use, the label's box closed. */
void FriendCodeEntry_CloseLabels(FriendCodeEntry *self)
{
    self->label_count = 0;
    TextLabel_CloseBox(&self->label);
}
CLEAN_AS(func_ov133_0229bb64, FriendCodeEntry_CloseLabels)

/* func_ov133_0229bb78: error message `message` shown (`flag` handed on, not fatal), the pointer
 * hidden, until it closes (sub state 11). */
void FriendCodeEntry_ShowError(FriendCodeEntry *self, int message, int flag)
{
    u8 number = (u8) message;
    ErrorMessage_Open(&self->error, &number, flag, 0);
    MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_ERROR);
    FriendCodeEntry_HidePointer(self);
}
CLEAN_AS(func_ov133_0229bb78, FriendCodeEntry_ShowError)

/* func_ov133_0229bbb4: back to the input, by touch or by the keys as the player last used. */
void FriendCodeEntry_Resume(FriendCodeEntry *self)
{
    if (StateFlags_IsClear2()) {
        FriendCodeEntry_ResumeByTouch(self);
    } else {
        FriendCodeEntry_ResumeByKeys(self);
    }
}
CLEAN_AS(func_ov133_0229bbb4, FriendCodeEntry_Resume)

/* func_ov133_0229bbd4: back to the input by the keys: the pointer shown at its key, the key
 * repeat reset (sub state 3). */
void FriendCodeEntry_ResumeByKeys(FriendCodeEntry *self)
{
    FriendCodeEntry_PlacePointer(self);
    MenuScene_ResetKeyRepeat(friend_code_scene(self));
    MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_KEYS);
}
CLEAN_AS(func_ov133_0229bbd4, FriendCodeEntry_ResumeByKeys)

/* func_ov133_0229bbf0: back to the input by touch: the pointer hidden (sub state 0). Answers
 * MenuScene_SetSubState's pointer as an int. */
int FriendCodeEntry_ResumeByTouch(FriendCodeEntry *self)
{
    FriendCodeEntry_HidePointer(self);
    return (int) (uintptr_t) MenuScene_SetSubState(friend_code_scene(self), FRIEND_CODE_SUB_TOUCH);
}
CLEAN_AS(func_ov133_0229bbf0, FriendCodeEntry_ResumeByTouch)
