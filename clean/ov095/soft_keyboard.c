/* The software keyboard of overlay 95 (soft_keyboard.h): its flags, its set up and end, the
 * layouts it loads, the commands it acts on itself, the pressed key's timers and its drawing. */
#include "soft_keyboard.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/group_params.h"
#include "main/layer_load_task.h"
#include "main/motion_slots.h"
#include "main/oam_buffer.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/rom_file.h"
#include "main/sound.h"

static_assert(offsetof(SoftKeyboard, composition_length) == 0x0c && offsetof(SoftKeyboard, flags) == 0x14, "composition");
static_assert(offsetof(SoftKeyboard, page) == 0x16 && offsetof(SoftKeyboard, layout) == 0x1b, "page");
static_assert(offsetof(SoftKeyboard, disabled) == 0x20 && offsetof(SoftKeyboard, key) == 0x28, "keys");
static_assert(offsetof(SoftKeyboard, movable_x) == 0x34 && offsetof(SoftKeyboard, emotion_numbers) == 0x3c, "places");
static_assert(offsetof(SoftKeyboard, kind) == 0x42 && offsetof(SoftKeyboard, controls) == 0x44, "kind");
static_assert(offsetof(SoftKeyboard, key_chars) == 0x48 && offsetof(SoftKeyboard, chars_task) == 0x2308, "chars");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(SoftKeyboard, screen_task) == 0x232c, "tasks");
static_assert(offsetof(SoftKeyboard, screen) == 0x2428 && offsetof(SoftKeyboard, emotion_chars) == 0x2c28, "screen");

/* The SDK's copy (the C library's names are the PC's). */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The touch, in pixels of the sub screen (main's bytes). */
extern u8 data_021f6c58, data_021f6c54;

/* The OBJs are drawn on the sub screen, 0x80 and 0x60 being its centre. */
#define SOFT_KEYBOARD_SCREEN_SUB 1
#define SOFT_KEYBOARD_TOUCH_X() ((int) data_021f6c58 - 0x80)
#define SOFT_KEYBOARD_TOUCH_Y() ((int) data_021f6c54 - 0x60)

/* The cells: the controls of kind 0 and of the others; key 0xf7's two; the caret; the side
 * buttons, of the others and of kind 0; the emotion tabs (a back, an icon and a frame each)
 * and their touch areas. */
extern OamEntry data_ov095_0229e6b4[];
extern OamEntry data_ov095_0229e6e4[];
extern OamEntry data_ov095_0229e380[];
extern OamEntry data_ov095_0229e390[];
extern OamEntry data_ov095_0229e388[];
extern OamEntry data_ov095_0229e714[];
extern OamEntry data_ov095_0229e744[];
extern OamEntry data_ov095_0229e664[];
extern OamEntry data_ov095_0229e68c[];
extern OamEntry data_ov095_0229e814[SOFT_KEYBOARD_EMOTIONS * 3];
extern OamEntry data_ov095_0229e834[];

/* The cell of each page's keys (null for pages 0 and 3), and the one used for those. */
extern OamEntry *data_ov095_0229e424[SOFT_KEYBOARD_PAGES];
extern OamEntry data_ov095_0229ea84[];

/* The files: each layout's characters ("menu/chat2/key%d.bch"), its screen for kind 0
 * ("b_chtk%d.bsc", "b_cht.bsc") and for the others ("b_key%d.bsc"); the palettes
 * "b_cht_bg.bpl"; the OBJs' "b_cht_obj.bpl", "b_cht_obj_0.bch" and "b_cht_obj_1.bch"; the
 * emotions' "ten0.bch"; the letter's "menu/letter/b_ltr.bch". */
extern const char *const data_ov095_0229e5f8[SOFT_KEYBOARD_LAYOUTS];
extern const char *const data_ov095_0229e61c[SOFT_KEYBOARD_LAYOUTS];
extern const char *const data_ov095_0229e640[SOFT_KEYBOARD_LAYOUTS];
extern const char data_ov095_0229ee74[];
extern const char data_ov095_0229ee08[];
extern const char data_ov095_0229ee24[];
extern const char data_ov095_0229ee40[];
extern const char data_ov095_0229edf4[];
extern const char data_ov095_0229ee5c[];

/* The part of a layout's screen file copied into the screen (rows 9 to 22). */
#define SOFT_KEYBOARD_SCREEN_FILE_OFFSET 0x240
#define SOFT_KEYBOARD_SCREEN_FILE_BYTES 0x380

/* The characters of the layout, in the layer's characters 0x1ea-0x2ff. */
#define SOFT_KEYBOARD_KEY_CHARS_FIRST 0x1ea
#define SOFT_KEYBOARD_KEY_CHARS_LAST 0x2ff

/* An emotion's characters: two rows of two in "ten0.bch" (16 to a row of 0x400 bytes), loaded
 * into the sub OBJ characters from 0x109, two per emotion. */
#define SOFT_KEYBOARD_EMOTION_FIRST_CHAR 0x109
#define SOFT_KEYBOARD_EMOTION_LOWER_ROW 0x400

/* The sounds. */
#define SOFT_KEYBOARD_SE_SWITCH 0x18

/* --- Flags and sounds --- */

/* func_ov095_022999a0 */
void SoftKeyboard_ClearFlags(SoftKeyboard *kb, int mask)
{
    kb->flags = (u16) (kb->flags & ~mask);
}
CLEAN_AS(func_ov095_022999a0, SoftKeyboard_ClearFlags)

/* func_ov095_022999a8 */
void SoftKeyboard_SetFlags(SoftKeyboard *kb, int mask)
{
    kb->flags = (u16) (kb->flags | mask);
}
CLEAN_AS(func_ov095_022999a8, SoftKeyboard_SetFlags)

/* func_ov095_022999b0: 1 when any of `mask` is set. */
int SoftKeyboard_TestFlags(SoftKeyboard *kb, unsigned int mask)
{
    return (kb->flags & mask) != 0;
}
CLEAN_AS(func_ov095_022999b0, SoftKeyboard_TestFlags)

/* func_ov095_022999c0: the typing sound, once a frame (whatever the character). */
void SoftKeyboard_PlayTypeSound(SoftKeyboard *kb, int character)
{
    (void) character;
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_TYPED) == 0) {
        SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_TYPED);
        SoundSys_PlaySound2c(NULL);
    }
}
CLEAN_AS(func_ov095_022999c0, SoftKeyboard_PlayTypeSound)

/* func_ov095_022999e8 */
void SoftKeyboard_PlaySe23(SoftKeyboard *kb)
{
    (void) kb;
    SoundSys_PlaySe(23);
}
CLEAN_AS(func_ov095_022999e8, SoftKeyboard_PlaySe23)

/* func_ov095_022999f4 */
void SoftKeyboard_PlaySe22(SoftKeyboard *kb)
{
    (void) kb;
    SoundSys_PlaySe(22);
}
CLEAN_AS(func_ov095_022999f4, SoftKeyboard_PlaySe22)

/* func_ov095_0229b388 */
void SoftKeyboard_ClearFlag02(SoftKeyboard *kb)
{
    SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_02);
}
CLEAN_AS(func_ov095_0229b388, SoftKeyboard_ClearFlag02)

/* func_ov095_0229b394 */
void SoftKeyboard_SetFlag02(SoftKeyboard *kb)
{
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_02);
}
CLEAN_AS(func_ov095_0229b394, SoftKeyboard_SetFlag02)

/* func_ov095_0229bf70 */
void SoftKeyboard_MarkScreenDirty(SoftKeyboard *kb)
{
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov095_0229bf70, SoftKeyboard_MarkScreenDirty)

/* func_ov095_0229c050 */
void SoftKeyboard_SetFlag08(SoftKeyboard *kb)
{
    SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_08);
}
CLEAN_AS(func_ov095_0229c050, SoftKeyboard_SetFlag08)

/* --- Drawing --- */

/* func_ov095_0229ae84: the side buttons, in their palettes. */
void SoftKeyboard_DrawSideButtons(SoftKeyboard *kb, int x, int y)
{
    OamBuffer_DrawCell(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e714, x, y, kb->side_palette[0], 1, 0x1000, 0x1000, 0, -1, 0,
                       0);
    OamBuffer_DrawCell(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e744, x, y, kb->side_palette[1], 1, 0x1000, 0x1000, 0, -1, 0,
                       0);
}
CLEAN_AS(func_ov095_0229ae84, SoftKeyboard_DrawSideButtons)

/* func_ov095_0229aeec: kind 0's side buttons, in their palettes. */
void SoftKeyboard_DrawChatSideButtons(SoftKeyboard *kb, int x, int y)
{
    OamBuffer_DrawCell(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e664, x, y, kb->side_palette[0], 2, 0x1000, 0x1000, 0, -1, 0,
                       0);
    OamBuffer_DrawCell(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e68c, x, y, kb->side_palette[1], 2, 0x1000, 0x1000, 0, -1, 0,
                       0);
}
CLEAN_AS(func_ov095_0229aeec, SoftKeyboard_DrawChatSideButtons)

/* func_ov095_0229af58: the owner's text caret at (x, y). The keyboard is not used. */
int SoftKeyboard_DrawCaret(SoftKeyboard *kb, int x, int y, int priority)
{
    (void) kb;
    return OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e388, x, y, -1, priority, NULL);
}
CLEAN_AS(func_ov095_0229af58, SoftKeyboard_DrawCaret)

/* func_ov095_0229b090: key 0xf7, its face `dy` pixels below its frame. The keyboard is not
 * used. */
void SoftKeyboard_DrawChatF7(SoftKeyboard *kb, int x, int y, int palette, int dy)
{
    (void) kb;
    OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e380, x, y + dy, palette, 2, NULL);
    OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, data_ov095_0229e390, x, y, -1, 2, NULL);
}
CLEAN_AS(func_ov095_0229b090, SoftKeyboard_DrawChatF7)

/* func_ov095_0229b0d8: the emotion tabs, the picked one 2 pixels lower with its icon in
 * palette 11. */
void SoftKeyboard_DrawEmotionTabs(SoftKeyboard *kb, int x, int y)
{
    int i;

    for (i = 0; i < kb->emotion_count; i++) {
        int palette = -1;
        int tab_y = y;
        if (kb->emotion == i) {
            palette = 0xb;
            tab_y = y + 2;
        }
        OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, &data_ov095_0229e814[i], x, tab_y, -1, 2, NULL);
        OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, &data_ov095_0229e814[i + SOFT_KEYBOARD_EMOTIONS], x, tab_y, palette,
                                2, NULL);
        OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, &data_ov095_0229e814[i + SOFT_KEYBOARD_EMOTIONS * 2], x, y, -1, 2,
                                NULL);
    }
}
CLEAN_AS(func_ov095_0229b0d8, SoftKeyboard_DrawEmotionTabs)

/* func_ov095_0229b16c: the cell of the page's keys (also the one whose palettes show them
 * pressed or disabled); pages 0 and 3 use the Hangul page's, a page past 4 has none. */
OamEntry *SoftKeyboard_KeyLooks(SoftKeyboard *kb)
{
    OamEntry *looks;

    if (kb->page >= SOFT_KEYBOARD_PAGES) {
        return NULL;
    }
    looks = data_ov095_0229e424[kb->page];
    if (looks != NULL) {
        return looks;
    }
    return data_ov095_0229ea84;
}
CLEAN_AS(func_ov095_0229b16c, SoftKeyboard_KeyLooks)

/* func_ov095_0229b18c */
void SoftKeyboard_DrawKeys(SoftKeyboard *kb, int x, int y)
{
    OamBuffer_DrawCell(SOFT_KEYBOARD_SCREEN_SUB, SoftKeyboard_KeyLooks(kb), x, y, -1, 3, 0x1000, 0x1000, 0, -1, 0, 0);
}
CLEAN_AS(func_ov095_0229b18c, SoftKeyboard_DrawKeys)

/* func_ov095_0229b1c8: the page tabs (the current page's 2 pixels lower in palette 11, the
 * others in 10), the tab row's cell, then the keys (8 pixels higher outside kind 0's layout). */
void SoftKeyboard_DrawTabRow(SoftKeyboard *kb, int x, int y, int priority)
{
    int current;
    int i;

    switch (kb->page) {
        case SOFT_KEYBOARD_PAGE_ENGLISH:
            current = 1;
            break;
        case SOFT_KEYBOARD_PAGE_SYMBOLS:
            current = 2;
            break;
        default:
            current = 0;
            break;
    }
    for (i = 0; i < 3; i++) {
        if (current == i) {
            OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, &kb->controls[i], x, y + 2, 0xb, priority, NULL);
        } else {
            OamBuffer_DrawObjAffine(SOFT_KEYBOARD_SCREEN_SUB, &kb->controls[i], x, y, 0xa, priority, NULL);
        }
    }
    OamBuffer_DrawCell(SOFT_KEYBOARD_SCREEN_SUB, &kb->controls[3], x, y, -1, priority, 0x1000, 0x1000, 0, -1, 0, 0);
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) == 0) {
        y -= 8;
    }
    SoftKeyboard_DrawKeys(kb, x, y);
}
CLEAN_AS(func_ov095_0229b1c8, SoftKeyboard_DrawTabRow)

/* func_ov095_0229bf7c: the screen queued for loading into `layer` when it changed (and marked
 * clean once queued); the frame's flags 0x02 and TYPED cleared. */
void SoftKeyboard_QueueScreen(SoftKeyboard *kb, unsigned int layer)
{
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY) != 0) {
        if (LayerTask_QueueScreen(&kb->screen_task, (int) (uintptr_t) kb->screen, (int) layer, SOFT_KEYBOARD_SCREEN_SIZE, 0) !=
            0) {
            SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
        }
    }
    SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_02);
    SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_TYPED);
}
CLEAN_AS(func_ov095_0229bf7c, SoftKeyboard_QueueScreen)

/* func_ov095_0229bfd8: the screen loaded into `layer` now. */
void SoftKeyboard_LoadScreenNow(SoftKeyboard *kb, int layer)
{
    DisplayLayer_LoadScreen(kb->screen, layer, SOFT_KEYBOARD_SCREEN_SIZE, 0);
    SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_SCREEN_DIRTY);
}
CLEAN_AS(func_ov095_0229bfd8, SoftKeyboard_LoadScreenNow)

/* func_ov095_0229c000: the screen read from the file `path`. */
int SoftKeyboard_ReadScreen(SoftKeyboard *kb, const char *path)
{
    return RomFile_Read(path, kb->screen, SOFT_KEYBOARD_SCREEN_SIZE);
}
CLEAN_AS(func_ov095_0229c000, SoftKeyboard_ReadScreen)

/* func_ov095_0229c01c: the letter's characters ("menu/letter/b_ltr.bch", from its character
 * 0x13d) into `layer`'s characters 0x1eb-0x1f0. The keyboard is not used. */
int SoftKeyboard_LoadLetterChars(SoftKeyboard *kb, int layer)
{
    (void) kb;
    return DisplayLayer_LoadCharsFromFile(data_ov095_0229ee5c, data_021fbe94, layer, 0x13d, 0x1eb, 0x1f0);
}
CLEAN_AS(func_ov095_0229c01c, SoftKeyboard_LoadLetterChars)

/* func_ov095_0229b324: the OBJs' palettes (4-14) and characters (0xc0-0x13f, 0x180-0x1ff) on
 * the sub screen. The keyboard is not used. */
int SoftKeyboard_LoadObjGraphics(SoftKeyboard *kb)
{
    Heap *heap = data_021fbe94;

    (void) kb;
    DisplayLayer_LoadPalettesFromFile(data_ov095_0229ee08, heap, LAYER_SUB_OBJ, 4, 4, 0xe);
    DisplayLayer_LoadCharsFromFile(data_ov095_0229ee24, heap, LAYER_SUB_OBJ, 0xc0, 0xc0, 0x13f);
    return DisplayLayer_LoadCharsFromFile(data_ov095_0229ee40, heap, LAYER_SUB_OBJ, 0x180, 0x180, 0x1ff);
}
CLEAN_AS(func_ov095_0229b324, SoftKeyboard_LoadObjGraphics)

/* func_ov095_0229b280: the current player's motion slots taken as the emotion tabs, and each
 * one's icon loaded into the sub OBJ characters (two upper and two lower ones).
 * QUIRK: the first `count` slots are taken, filled or not (the count is of the filled ones),
 * and an empty slot's icon (0xff) is read from far past "ten0.bch"'s 0x1000 bytes. */
void SoftKeyboard_LoadEmotions(SoftKeyboard *kb)
{
    int i;

    kb->emotion_count = (u8) MotionSlots_Count();
    for (i = 0; i < kb->emotion_count; i++) {
        kb->emotion_numbers[i] = (u8) MotionSlots_Get(i);
    }
    RomFile_Read(data_ov095_0229edf4, kb->emotion_chars, SOFT_KEYBOARD_EMOTION_CHARS_SIZE);
    for (i = 0; i < kb->emotion_count; i++) {
        int icon = kb->emotion_numbers[i] - 1;
        int offset = (icon & 0xf) * 0x40 + (icon >> 4) * 0x800;
        u32 chars = (u32) (uintptr_t) kb->emotion_chars + (u32) offset;
        int first = i * 2 + SOFT_KEYBOARD_EMOTION_FIRST_CHAR;

        DisplayLayer_LoadChars(chars, LAYER_SUB_OBJ, (u32) first, (u32) first, (u32) (first + 1));
        DisplayLayer_LoadChars(chars + SOFT_KEYBOARD_EMOTION_LOWER_ROW, LAYER_SUB_OBJ, (u32) (first + 0x20),
                               (u32) (first + 0x20), (u32) (first + 0x21));
    }
}
CLEAN_AS(func_ov095_0229b280, SoftKeyboard_LoadEmotions)

/* --- The emotion tabs and the pen on the tabs --- */

/* func_ov095_0229af84: the motion of the emotion tab picked, 0xff for none. */
u8 SoftKeyboard_PickedEmotion(SoftKeyboard *kb)
{
    unsigned int tab = kb->emotion;

    if (tab >= SOFT_KEYBOARD_EMOTIONS) {
        return 0xff;
    }
    return kb->emotion_numbers[tab];
}
CLEAN_AS(func_ov095_0229af84, SoftKeyboard_PickedEmotion)

/* func_ov095_0229af98: the emotion tab of a code picked; answers the keyboard. */
SoftKeyboard *SoftKeyboard_PickEmotionByCode(SoftKeyboard *kb, int code)
{
    kb->emotion = (u8) (code - SOFT_KEYBOARD_CODE_EMOTION_FIRST);
    return kb;
}
CLEAN_AS(func_ov095_0229af98, SoftKeyboard_PickEmotionByCode)

/* func_ov095_0229afa4 */
void SoftKeyboard_DropEmotion(SoftKeyboard *kb)
{
    kb->emotion = SOFT_KEYBOARD_NO_EMOTION;
}
CLEAN_AS(func_ov095_0229afa4, SoftKeyboard_DropEmotion)

/* func_ov095_0229afac: the emotion tab under the pen picked: 1, or 0 for none. */
int SoftKeyboard_TouchEmotion(SoftKeyboard *kb)
{
    int tab =
        OamBuffer_FindObjAt(data_ov095_0229e834, kb->emotion_count, SOFT_KEYBOARD_TOUCH_X(), SOFT_KEYBOARD_TOUCH_Y(), 0, 0);

    if (tab == -1) {
        return 0;
    }
    kb->emotion = (u8) tab;
    return 1;
}
CLEAN_AS(func_ov095_0229afac, SoftKeyboard_TouchEmotion)

/* func_ov095_0229aff0: the page of the page tab under the pen taken, with sound 0x18: 1, or 0
 * when there is none or it is the page already. */
int SoftKeyboard_TouchPageTab(SoftKeyboard *kb)
{
    int tab = OamBuffer_FindObjAt(kb->controls, 3, SOFT_KEYBOARD_TOUCH_X(), SOFT_KEYBOARD_TOUCH_Y(), 2, 2);
    int page;

    if (tab == -1) {
        return 0;
    }
    switch (tab) {
        case 0:
            page = SOFT_KEYBOARD_PAGE_HANGUL;
            break;
        case 1:
            page = SOFT_KEYBOARD_PAGE_ENGLISH;
            break;
        case 2:
            page = SOFT_KEYBOARD_PAGE_SYMBOLS;
            break;
        default:
            page = tab;
            break;
    }
    if (page == kb->page) {
        return 0;
    }
    kb->page = (u8) page;
    SoundSys_PlaySe(SOFT_KEYBOARD_SE_SWITCH);
    return 1;
}
CLEAN_AS(func_ov095_0229aff0, SoftKeyboard_TouchPageTab)

/* func_ov095_0229b058: the pen is on key 0xf7. The keyboard is not used. */
int SoftKeyboard_TouchChatF7(SoftKeyboard *kb)
{
    (void) kb;
    return OamBuffer_ObjContains(data_ov095_0229e380, SOFT_KEYBOARD_TOUCH_X(), SOFT_KEYBOARD_TOUCH_Y(), 0, 0) != 0;
}
CLEAN_AS(func_ov095_0229b058, SoftKeyboard_TouchChatF7)

/* --- Commands --- */

/* func_ov095_0229bebc: the code is a command (0x100-0x123). */
int SoftKeyboard_IsCommand(SoftKeyboard *kb, int code)
{
    (void) kb;
    return code >= SOFT_KEYBOARD_CODE_COMMAND_FIRST && code < SOFT_KEYBOARD_CODE_COMMAND_END;
}
CLEAN_AS(func_ov095_0229bebc, SoftKeyboard_IsCommand)

/* func_ov095_0229ba44: a key's code acted on: a newline ends the composition; the shift, caps
 * and page commands are done here (with sound 0x18) and, like 0x101, 0x102 and 0x121-0x123,
 * answer 2. Any other code answers 0 and lets a one-shot shift go. */
int SoftKeyboard_HandleCommand(SoftKeyboard *kb, int code, int layer)
{
    if (code == SOFT_KEYBOARD_CODE_NEWLINE) {
        SoftKeyboard_HangulReset(kb);
    }
    if (SoftKeyboard_IsCommand(kb, code) == 0) {
        SoftKeyboard_ReleaseShift(kb, layer);
        return 0;
    }
    switch (code) {
        case SOFT_KEYBOARD_CODE_101:
        case SOFT_KEYBOARD_CODE_102:
            return 2;
        case SOFT_KEYBOARD_CODE_SHIFT:
            SoftKeyboard_ToggleShift(kb, (unsigned int) layer);
            SoundSys_PlaySe(SOFT_KEYBOARD_SE_SWITCH);
            return 2;
        case SOFT_KEYBOARD_CODE_CAPS:
            SoftKeyboard_ToggleCaps(kb, layer);
            SoundSys_PlaySe(SOFT_KEYBOARD_SE_SWITCH);
            return 2;
        case SOFT_KEYBOARD_CODE_PAGE_HANGUL:
        case SOFT_KEYBOARD_CODE_PAGE_ENGLISH:
        case SOFT_KEYBOARD_CODE_PAGE_SYMBOLS:
            SoftKeyboard_SwitchPage(kb, code, layer);
            SoundSys_PlaySe(SOFT_KEYBOARD_SE_SWITCH);
            return 2;
        case SOFT_KEYBOARD_CODE_121:
        case SOFT_KEYBOARD_CODE_122:
        case SOFT_KEYBOARD_CODE_123:
            return 2;
        default:
            break;
    }
    SoftKeyboard_ReleaseShift(kb, layer);
    return 0;
}
CLEAN_AS(func_ov095_0229ba44, SoftKeyboard_HandleCommand)

/* func_ov095_0229c104: a one-shot shift let go: back to the lower case. */
void SoftKeyboard_ReleaseShift(SoftKeyboard *kb, int layer)
{
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT) != 0) {
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT);
        SoftKeyboard_LoadLayout(kb, SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER, (unsigned int) layer, 1);
    }
}
CLEAN_AS(func_ov095_0229c104, SoftKeyboard_ReleaseShift)

/* func_ov095_0229c134: the shift key: up to the upper case for one character, or back. */
void SoftKeyboard_ToggleShift(SoftKeyboard *kb, unsigned int layer)
{
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT) != 0) {
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT);
        SoftKeyboard_LoadLayout(kb, SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER, layer, 1);
    } else {
        SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT);
        SoftKeyboard_LoadLayout(kb, SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER, layer, 1);
    }
}
CLEAN_AS(func_ov095_0229c134, SoftKeyboard_ToggleShift)

/* func_ov095_0229c178: the caps key: the case turned over and kept. A shift down counts as
 * the lower case, so it gives the upper case for good. */
void SoftKeyboard_ToggleCaps(SoftKeyboard *kb, int layer)
{
    if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT) != 0) {
        kb->layout = SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER;
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT);
    }
    switch (kb->layout) {
        case SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER:
            SoftKeyboard_LoadLayout(kb, SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER, (unsigned int) layer, 1);
            break;
        case SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER:
            SoftKeyboard_LoadLayout(kb, SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER, (unsigned int) layer, 1);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov095_0229c178, SoftKeyboard_ToggleCaps)

/* func_ov095_0229c1c4: a page tab's code: that page, in the layout main keeps for it. */
void SoftKeyboard_SwitchPage(SoftKeyboard *kb, int code, int layer)
{
    switch (code) {
        case SOFT_KEYBOARD_CODE_PAGE_HANGUL:
            kb->page = SOFT_KEYBOARD_PAGE_HANGUL;
            break;
        case SOFT_KEYBOARD_CODE_PAGE_ENGLISH:
            kb->page = SOFT_KEYBOARD_PAGE_ENGLISH;
            break;
        case SOFT_KEYBOARD_CODE_PAGE_SYMBOLS:
            kb->page = SOFT_KEYBOARD_PAGE_SYMBOLS;
            break;
    }
    SoftKeyboard_LoadLayout(kb, SOFT_KEYBOARD_LAYOUT_SAVED, (unsigned int) layer, 1);
}
CLEAN_AS(func_ov095_0229c1c4, SoftKeyboard_SwitchPage)

/* --- Layouts --- */

/* func_ov095_0229c22c: `layout` (SOFT_KEYBOARD_LAYOUT_SAVED: the page's layout main keeps) made
 * the page's and kept by main (a one-shot shift's upper case is kept as the lower case).
 * Without `keep` the background's palettes 1-4, 7 and 9 are loaded into `layer`. Unless `keep`
 * and that layout is loaded already, its characters are read and queued for `layer`, its screen
 * copied in, the keys it lacks disabled and the others enabled, and the composition dropped.
 * The keys' looks are reset in any case.
 * REQUIRES: the layout asked for, or kept for the page, is 0-8. */
void SoftKeyboard_LoadLayout(SoftKeyboard *kb, int layout, unsigned int layer, int keep)
{
    Heap *heap;
    const char *path;
    u8 *file;

    if (layout == SOFT_KEYBOARD_LAYOUT_SAVED) {
        layout = GroupParams_C90(kb->page);
    }
    if (layout == SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER && SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_SHIFT) != 0) {
        GroupParams_SetC90(kb->page, SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER);
    } else {
        GroupParams_SetC90(kb->page, (u8) layout);
    }

    heap = data_021fbe94;
    if (keep == 0) {
        DisplayLayer_LoadPalettesFromFile(data_ov095_0229ee74, heap, (int) layer, 1, 1, 4);
        DisplayLayer_LoadPalettesFromFile(data_ov095_0229ee74, heap, (int) layer, 1, 7, 7);
        DisplayLayer_LoadPalettesFromFile(data_ov095_0229ee74, heap, (int) layer, 1, 9, 9);
    }

    if (kb->layout != layout || keep == 0) {
        RomFile_Read(data_ov095_0229e5f8[layout], kb->key_chars, SOFT_KEYBOARD_KEY_CHARS_SIZE);
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT) != 0) {
            path = data_ov095_0229e61c[layout];
        } else {
            path = data_ov095_0229e640[layout];
        }
        file = RomFile_Load(path, heap, -4, NULL);
        MI_CpuCopy8(file + SOFT_KEYBOARD_SCREEN_FILE_OFFSET, (u8 *) kb->screen + SOFT_KEYBOARD_SCREEN_FILE_OFFSET,
                    SOFT_KEYBOARD_SCREEN_FILE_BYTES);
        SoftKeyboard_MarkScreenDirty(kb);
        Heap_Free(heap, file);
        LayerTask_QueueChars(&kb->chars_task, (int) (uintptr_t) kb->key_chars, (int) layer, SOFT_KEYBOARD_KEY_CHARS_FIRST,
                             SOFT_KEYBOARD_KEY_CHARS_FIRST, SOFT_KEYBOARD_KEY_CHARS_LAST);

        kb->layout = (u8) layout;
        switch (kb->layout) {
            case 0:
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_1);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_2);
                break;
            case 1:
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_1);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_2);
                break;
            case SOFT_KEYBOARD_LAYOUT_ENGLISH_LOWER:
            case SOFT_KEYBOARD_LAYOUT_ENGLISH_UPPER:
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6A);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6C);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6D);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_SHIFT);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_CAPS);
                break;
            case 4:
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6A);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6C);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6D);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_SHIFT);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_CAPS);
                break;
            case 5:
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6A);
                SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6C);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_6D);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_SHIFT);
                SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_CAPS);
                break;
            default:
                break;
        }
        SoftKeyboard_HangulReset(kb);
    }
    SoftKeyboard_ResetKeyLooks(kb);
}
CLEAN_AS(func_ov095_0229c22c, SoftKeyboard_LoadLayout)

/* func_ov095_0229c208: the current layout loaded again into `layer` (with its palettes), and
 * the screen queued. */
void SoftKeyboard_Restore(SoftKeyboard *kb, unsigned int layer)
{
    SoftKeyboard_LoadLayout(kb, kb->layout, layer, 0);
    SoftKeyboard_QueueScreen(kb, layer);
}
CLEAN_AS(func_ov095_0229c208, SoftKeyboard_Restore)

/* func_ov095_0229c420: the page main keeps taken, in the layout main keeps for it, loaded
 * into `layer` with its palettes. */
void SoftKeyboard_LoadSavedLayout(SoftKeyboard *kb, int layer)
{
    kb->page = GroupParams_C60();
    SoftKeyboard_LoadLayout(kb, GroupParams_C90(kb->page), (unsigned int) layer, 0);
}
CLEAN_AS(func_ov095_0229c420, SoftKeyboard_LoadSavedLayout)

/* --- Set up and end --- */

/* func_ov095_0229c084: the keyboard set up for an owner of `kind`, on the Hangul page with no
 * layout loaded; kind 0 gets its own layout and controls. The keyboard's click (SoundSys's
 * byte 0x71) is off for a current player whose byte 0x1c is 0, else on. */
void SoftKeyboard_Init(SoftKeyboard *kb, int kind)
{
    u8 *record;

    kb->disabled = 0;
    kb->layout = SOFT_KEYBOARD_LAYOUT_SAVED;
    kb->pressed_key = SOFT_KEYBOARD_KEY_NONE;
    kb->flags = 0;
    kb->emotion = SOFT_KEYBOARD_NO_EMOTION;
    kb->emotion_count = 0;
    kb->key = SOFT_KEYBOARD_KEY_NONE;
    kb->key_x = 100;
    kb->key_y = 100;
    SoftKeyboard_HangulReset(kb);
    if (kind == SOFT_KEYBOARD_KIND_CHAT) {
        SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_CHAT_LAYOUT);
        kb->controls = data_ov095_0229e6b4;
    } else {
        kb->controls = data_ov095_0229e6e4;
    }
    kb->kind = (u8) kind;
    kb->side_palette[0] = SOFT_KEYBOARD_PALETTE_NORMAL;
    kb->side_palette[1] = SOFT_KEYBOARD_PALETTE_NORMAL;
    kb->page = SOFT_KEYBOARD_PAGE_HANGUL;

    record = PlayerRecords_Current();
    if (record != NULL) {
        if (PlayerId_Byte1c((const s8 *) (void *) PlayerRecord_Player(record)) == 0) {
            SoundSys_SetByte71(0);
            return;
        }
    }
    SoundSys_SetByte71(1);
}
CLEAN_AS(func_ov095_0229c084, SoftKeyboard_Init)

/* func_ov095_0229c05c: the layer tasks ended and the page kept by main. */
void SoftKeyboard_Finish(SoftKeyboard *kb)
{
    LayerTask_End(&kb->chars_task);
    LayerTask_End(&kb->screen_task);
    GroupParams_SetC60(kb->page);
}
CLEAN_AS(func_ov095_0229c05c, SoftKeyboard_Finish)

/* --- The pressed key and the repeat --- */

/* func_ov095_0229bed8: the backspace enabled (whatever the character). */
void SoftKeyboard_EnableBackspace(SoftKeyboard *kb, int character)
{
    (void) character;
    SoftKeyboard_EnableSpecial(kb, SOFT_KEYBOARD_SPECIAL_BACKSPACE);
}
CLEAN_AS(func_ov095_0229bed8, SoftKeyboard_EnableBackspace)

/* func_ov095_0229bee4: the backspace and keys 3-5 disabled. */
void SoftKeyboard_DisableEditKeys(SoftKeyboard *kb)
{
    SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_BACKSPACE);
    SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_3);
    SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_4);
    SoftKeyboard_DisableSpecial(kb, SOFT_KEYBOARD_SPECIAL_5);
}
CLEAN_AS(func_ov095_0229bee4, SoftKeyboard_DisableEditKeys)

/* func_ov095_0229bf0c: a frame of a key held: it stays shown pressed, and 1 when its repeat
 * is due (then every second frame). */
int SoftKeyboard_StepRepeat(SoftKeyboard *kb)
{
    if (kb->pressed_timer > 1) {
        kb->pressed_timer--;
    }
    if (kb->repeat_timer != 0) {
        kb->repeat_timer--;
        return 0;
    }
    kb->repeat_timer = 1;
    return 1;
}
CLEAN_AS(func_ov095_0229bf0c, SoftKeyboard_StepRepeat)

/* func_ov095_0229bf3c: a key pressed: shown 5 frames, repeated after 13 while held. */
void SoftKeyboard_StartRepeat(SoftKeyboard *kb)
{
    kb->pressed_timer = 5;
    kb->repeat_timer = 13;
}
CLEAN_AS(func_ov095_0229bf3c, SoftKeyboard_StartRepeat)

/* func_ov095_0229bf48: a frame of the pressed key shown: 1 for its first frames; when the
 * time is up its look is released. */
int SoftKeyboard_StepPressed(SoftKeyboard *kb)
{
    if (kb->pressed_timer != 0) {
        kb->pressed_timer--;
        if (kb->pressed_timer >= 4) {
            return 1;
        }
        if (kb->pressed_timer == 0) {
            SoftKeyboard_ReleasePressed(kb);
        }
    }
    return 0;
}
CLEAN_AS(func_ov095_0229bf48, SoftKeyboard_StepPressed)
