/* The software keyboard's editing of its owner's text (soft_keyboard.h): a character put in at
 * the cursor, with the Hangul composition (a jamo typed may change the syllable before the
 * cursor), the checks that it fits, a range taken out, and the column under a pixel. */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/letter_view.h"
#include "main/text_string.h"
#include "soft_keyboard.h"

/* The heap the scenes load into (autoload_2/heap.c). */
extern Heap *data_021fbe94;

/* The length of a text of at most `max` characters, as the letter scene uses it (main; it has
 * no source of its own). */
extern int func_02051c8c_unk(u16 *text, int max);

/* The blank character a full text may end with. */
#define SOFT_KEYBOARD_BLANK 0x3000

/* The trial copy SoftKeyboard_InsertInLines breaks into lines, and its widest one. */
#define SOFT_KEYBOARD_TRIAL_BYTES 0xc0
#define SOFT_KEYBOARD_TRIAL_LINES 8
#define SOFT_KEYBOARD_NO_WIDTH_LIMIT 10000

/* func_ov095_0229bb34: the characters of the first line of `text` that fit in `width` (as
 * TextString_FitLine counts them) walked to the one whose middle is past pixel `x`: its index
 * into *index (unless null) and the pixels before it answered (both the line's when none is). */
u8 SoftKeyboard_TextColumnAt(SoftKeyboard *kb, const u16 *text, int length, int width, u8 x, u8 *index)
{
    int count;
    int pixels = 0;
    int i;

    (void) kb;
    TextString_FitLine(text, length, width, &count, 0);
    for (i = 0; i < count; i++) {
        int char_width = TextString_CharWidth(text[i]);
        if (pixels + (char_width >> 1) > x) {
            if (index != NULL) {
                *index = (u8) i;
            }
            return (u8) pixels;
        }
        pixels += char_width;
    }
    if (index != NULL) {
        *index = (u8) count;
    }
    return (u8) pixels;
}
CLEAN_AS(func_ov095_0229bb34, SoftKeyboard_TextColumnAt)

/* func_ov095_0229bb94: the conversion of codes 0x105 (the letter scene's): none, 0. */
int SoftKeyboard_Convert3(SoftKeyboard *kb, int character)
{
    (void) kb;
    (void) character;
    return 0;
}
CLEAN_AS(func_ov095_0229bb94, SoftKeyboard_Convert3)

/* func_ov095_0229bb98: the conversion of codes 0x104: none, 0. */
int SoftKeyboard_Convert2(SoftKeyboard *kb, int character)
{
    (void) kb;
    (void) character;
    return 0;
}
CLEAN_AS(func_ov095_0229bb98, SoftKeyboard_Convert2)

/* func_ov095_0229bb9c: the conversion of codes 0x103: none, 0. */
int SoftKeyboard_Convert1(SoftKeyboard *kb, int character)
{
    (void) kb;
    (void) character;
    return 0;
}
CLEAN_AS(func_ov095_0229bb9c, SoftKeyboard_Convert1)

/* func_ov095_0229bba0: the character before `position` replaced, with the typing sound; 0 at
 * position 0. */
int SoftKeyboard_ReplaceBefore(SoftKeyboard *kb, u16 *text, int character, int position)
{
    if (position == 0) {
        return 0;
    }
    text[position - 1] = (u16) character;
    SoftKeyboard_PlayTypeSound(kb, character);
    return 1;
}
CLEAN_AS(func_ov095_0229bba0, SoftKeyboard_ReplaceBefore)

/* func_ov095_0229bbc0: the characters between `from` and `to` (either way round) taken out of
 * the `length` of `text`, the rest moved up and the end filled with 0; answers the lower end. */
int SoftKeyboard_DeleteRange(SoftKeyboard *kb, u16 *text, int from, int to, int length)
{
    int low = from > to ? to : from;
    int high = from > to ? from : to;
    int i;

    (void) kb;
    for (i = 0; i + high < length; i++) {
        text[i + low] = text[i + high];
    }
    for (i = 1; i <= high - low; i++) {
        text[length - i] = 0;
    }
    return low;
}
CLEAN_AS(func_ov095_0229bbc0, SoftKeyboard_DeleteRange)

/* func_ov095_0229bc00: a character put in at *position of a text broken into lines as the
 * letter view breaks them (LetterView_BreakLines, `max_chars` to a line of `width` pixels,
 * `lines` lines): it is tried on a copy (from the heap's back). 1 when it fits: unless
 * `probe`, the text and *position are then updated and, with `sound` 1, the typing sound played
 * for the character before the position. Without room in the lines, TOO_WIDE is set (unless
 * PROBING); 0 also when the copy cannot be had. */
int SoftKeyboard_InsertInLines(SoftKeyboard *kb, u16 *text, u32 character, u8 *position, u32 length, u32 max_chars, u32 lines,
                               u32 width, u32 probe, u32 sound)
{
    Heap *heap = data_021fbe94;
    u16 *trial;
    u8 trial_position;
    s32 end_line;
    s32 line_start[SOFT_KEYBOARD_TRIAL_LINES];

    trial = Heap_AllocBack(heap, SOFT_KEYBOARD_TRIAL_BYTES);
    if (trial == NULL) {
        return 0;
    }
    TextString_CopyChars(text, trial, (int) length);
    trial_position = *position;
    if (SoftKeyboard_Insert(kb, trial, (int) character, &trial_position, (int) length, SOFT_KEYBOARD_NO_WIDTH_LIMIT,
                            (int) probe, 0) == 0) {
        Heap_Free(heap, trial);
        return 0;
    }
    if (LetterView_BreakLines(trial, line_start, &end_line, (int) length, (int) max_chars, (int) width, (int) lines) == 0) {
        Heap_Free(heap, trial);
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_PROBING) == 0) {
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_TOO_WIDE);
        }
        return 0;
    }
    if (probe == 0) {
        TextString_CopyChars(trial, text, (int) length);
        *position = trial_position;
        if (sound == 1 && trial_position != 0) {
            SoftKeyboard_PlayTypeSound(kb, text[trial_position - 1]);
        }
    }
    Heap_Free(heap, trial);
    return 1;
}
CLEAN_AS(func_ov095_0229bc00, SoftKeyboard_InsertInLines)

/* func_ov095_0229bcec: a character put in at *position (SoftKeyboard_InsertComposed). A `probe`
 * sets PROBING; else the full flags and PROBING are cleared first.
 * QUIRK: `width` is not used: the character is not held to a width. */
int SoftKeyboard_Insert(SoftKeyboard *kb, u16 *text, int character, u8 *position, int length, int width, int probe, int sound)
{
    (void) width;
    if (probe != 0) {
        SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_PROBING);
    } else {
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_TEXT_FULL);
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_TOO_WIDE);
        SoftKeyboard_ClearFlags(kb, SOFT_KEYBOARD_FLAG_PROBING);
    }
    return SoftKeyboard_InsertComposed(kb, text, character, position, length, probe, sound);
}
CLEAN_AS(func_ov095_0229bcec, SoftKeyboard_Insert)

/* func_ov095_0229bd40: a character typed at *position of the `length` of `text`, through the
 * composition (SoftKeyboard_HangulAddJamo): a new character is put in (and *position moved on),
 * a composed syllable replaces the one before the position; 0 when there is no room. Unless
 * `probe`, the composition takes the jamo (or is dropped for another character) and, with
 * `sound`, the typing sound is played.
 * REQUIRES: a composition stands right before *position (as typing leaves it). */
int SoftKeyboard_InsertComposed(SoftKeyboard *kb, u16 *text, int character, u8 *position, int length, int probe, int sound)
{
    int how = SoftKeyboard_HangulAddJamo(kb, (u16) character);
    int at = *position;

    if (how == SOFT_KEYBOARD_COMPOSE_NEW || how == SOFT_KEYBOARD_COMPOSE_SPLIT) {
        if (SoftKeyboard_InsertAt(kb, text, kb->carried, at, length, -1) == 0) {
            return 0;
        }
        (*position)++;
    }
    if (how == SOFT_KEYBOARD_COMPOSE_REPLACE || how == SOFT_KEYBOARD_COMPOSE_SPLIT) {
        text[at - 1] = kb->composed;
    }
    if (probe == 0) {
        if (SoftKeyboard_IsJamo(kb, (unsigned int) character) != 0) {
            SoftKeyboard_HangulPush(kb, character, how);
        } else {
            SoftKeyboard_HangulReset(kb);
        }
        if (sound != 0) {
            SoftKeyboard_PlayTypeSound(kb, character);
        }
    }
    return 1;
}
CLEAN_AS(func_ov095_0229bd40, SoftKeyboard_InsertComposed)

/* func_ov095_0229bdd4: `character` put in at `at` of the `length` of `text`, the rest moved on
 * (the last dropped), when it fits (SoftKeyboard_CanInsert). */
int SoftKeyboard_InsertAt(SoftKeyboard *kb, u16 *text, u16 character, int at, int length, int width)
{
    int i;

    if (SoftKeyboard_CanInsert(kb, text, character, at, length, width) == 0) {
        return 0;
    }
    for (i = length - 1; i > at; i--) {
        text[i] = text[i - 1];
    }
    text[at] = character;
    return 1;
}
CLEAN_AS(func_ov095_0229bdd4, SoftKeyboard_InsertAt)

/* func_ov095_0229be18: a character fits at `at`: not at the end, not into a text whose last
 * place holds a character other than the blank (TEXT_FULL otherwise), and with `width` from 0
 * up, the text and it no wider than that (TOO_WIDE otherwise). The flags are left as they are
 * while PROBING. */
int SoftKeyboard_CanInsert(SoftKeyboard *kb, u16 *text, int character, int at, int length, int width)
{
    int used;

    if (length == at) {
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_PROBING) == 0) {
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_TEXT_FULL);
        }
        return 0;
    }
    used = func_02051c8c_unk(text, length);
    if (used == length && text[used - 1] != SOFT_KEYBOARD_BLANK) {
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_PROBING) == 0) {
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_TEXT_FULL);
        }
        return 0;
    }
    if (width < 0) {
        return 1;
    }
    if (TextString_Width(text, length) + TextString_CharWidth(character) > width) {
        if (SoftKeyboard_TestFlags(kb, SOFT_KEYBOARD_FLAG_PROBING) == 0) {
            SoftKeyboard_SetFlags(kb, SOFT_KEYBOARD_FLAG_TOO_WIDE);
        }
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov095_0229be18, SoftKeyboard_CanInsert)
