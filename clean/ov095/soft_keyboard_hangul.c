/* The software keyboard's Hangul composition (soft_keyboard.h). The Hangul page types
 * compatibility jamo (consonants 0x3131-0x314e, vowels 0x314f-0x3163); the jamo of the syllable
 * being typed are kept (`composition`) and each new one is tried on it
 * (SoftKeyboard_HangulAddJamo): a syllable of an initial consonant, a vowel (two may combine), and
 * a final consonant (two may combine) becomes the precomposed syllable 0xac00 + (initial * 21 +
 * vowel) * 28 + final, if it is one of the table's 2,355 (KS X 1001's set). */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "clean.h"
#include "soft_keyboard.h"

/* The syllables the keyboard can make. */
#define SOFT_KEYBOARD_SYLLABLES 0x933
extern const u16 data_ov095_0229d0f8[SOFT_KEYBOARD_SYLLABLES];

/* The SDK's copy (the C library's names are the PC's). */
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

#define SOFT_KEYBOARD_JAMO_FIRST 0x3131
#define SOFT_KEYBOARD_JAMO_COUNT 30 /* the consonants */
#define SOFT_KEYBOARD_VOWEL_FIRST 0x314f
#define SOFT_KEYBOARD_VOWEL_LAST 0x3163
#define SOFT_KEYBOARD_CONSONANT_LAST 0x314e

/* Each consonant's place as a final (1-27), 0 for one that cannot end a syllable. */
static const u8 soft_keyboard_final_index[SOFT_KEYBOARD_JAMO_COUNT] = {
    1, 2, 3, 4, 5, 6, 7, 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 18, 19, 20, 21, 22, 0, 23, 24, 25, 26, 27};

/* Each consonant's syllable as an initial (0xac00 + initial * 588), 0 for one that cannot start
 * a syllable. */
static const u16 soft_keyboard_initial_base[SOFT_KEYBOARD_JAMO_COUNT] = {
    0xac00, 0xae4c, 0,      0xb098, 0, 0,      0xb2e4, 0xb530, 0xb77c, 0,      0,      0,      0,      0,      0,
    0,      0xb9c8, 0xbc14, 0xbe60, 0, 0xc0ac, 0xc2f8, 0xc544, 0xc790, 0xc9dc, 0xcc28, 0xce74, 0xd0c0, 0xd30c, 0xd558};

/* func_ov095_0229b3a0: the backspace while composing: the composition's last jamo taken off and
 * the character before `position` made what is left (its one jamo, or the syllable of the rest);
 * 1. With one jamo or none left the composition is dropped; 0 then, and also at position 0.
 * QUIRK: a rest that composes into no syllable leaves 0 before the position. */
int SoftKeyboard_HangulBackspace(SoftKeyboard *kb, u16 *text, int position)
{
    u16 character;

    if (kb->composition_length <= 1) {
        SoftKeyboard_HangulReset(kb);
        return 0;
    }
    if (position == 0) {
        return 0;
    }
    kb->composition_length--;
    kb->composition[kb->composition_length] = 0;
    if (kb->composition_length <= 1) {
        character = kb->composition[0];
    } else {
        character = (u16) SoftKeyboard_HangulCompose(kb, kb->composition);
    }
    text[position - 1] = character;
    return 1;
}
CLEAN_AS(func_ov095_0229b3a0, SoftKeyboard_HangulBackspace)

/* func_ov095_0229b3ec: the composition dropped. */
void SoftKeyboard_HangulReset(SoftKeyboard *kb)
{
    int i;

    for (i = 0; i < SOFT_KEYBOARD_COMPOSITION; i++) {
        kb->composition[i] = 0;
    }
    kb->composition_length = 0;
}
CLEAN_AS(func_ov095_0229b3ec, SoftKeyboard_HangulReset)

/* func_ov095_0229b400: a jamo typed, by what SoftKeyboard_HangulAddJamo did: a new syllable
 * starts with it, it joins the syllable, or the syllable's last jamo and it start the next
 * one. The composition grows to at most 6.
 * REQUIRES: the composition is not empty for SOFT_KEYBOARD_COMPOSE_SPLIT (the ROM's code then
 * stores a register it never set), and holds at most 5 jamo (a syllable has at most 5). */
void SoftKeyboard_HangulPush(SoftKeyboard *kb, int jamo, int how)
{
    switch (how) {
        case SOFT_KEYBOARD_COMPOSE_NEW:
            SoftKeyboard_HangulReset(kb);
            kb->composition[kb->composition_length] = (u16) jamo;
            break;
        case SOFT_KEYBOARD_COMPOSE_REPLACE:
            kb->composition[kb->composition_length] = (u16) jamo;
            break;
        case SOFT_KEYBOARD_COMPOSE_SPLIT: {
            u16 last = 0;
            if (kb->composition_length > 0) {
                last = kb->composition[kb->composition_length - 1];
                SoftKeyboard_HangulReset(kb);
            }
            kb->composition[0] = last;
            kb->composition[1] = (u16) jamo;
            kb->composition_length = 2;
            return;
        }
        default:
            break;
    }
    if (kb->composition_length < SOFT_KEYBOARD_COMPOSITION) {
        kb->composition_length++;
    }
}
CLEAN_AS(func_ov095_0229b400, SoftKeyboard_HangulPush)

/* The compound vowel of `vowel` followed by `next`, 0 for none. */
static u16 soft_keyboard_compound_vowel(u16 vowel, u16 next)
{
    switch (vowel) {
        case 0x3157: /* o */
            switch (next) {
                case 0x314f:
                    return 0x3158;
                case 0x3150:
                    return 0x3159;
                case 0x3163:
                    return 0x315a;
            }
            return 0;
        case 0x315c: /* u */
            switch (next) {
                case 0x3153:
                    return 0x315d;
                case 0x3154:
                    return 0x315e;
                case 0x3163:
                    return 0x315f;
            }
            return 0;
        case 0x3161: /* eu */
            return next == 0x3163 ? 0x3162 : 0;
    }
    return 0;
}

/* The compound final of `final` followed by `next`, 0 for none. */
static u16 soft_keyboard_compound_final(u16 final, u16 next)
{
    switch (final) {
        case 0x3131: /* g */
            return next == 0x3145 ? 0x3133 : 0;
        case 0x3134: /* n */
            switch (next) {
                case 0x3148:
                    return 0x3135;
                case 0x314e:
                    return 0x3136;
            }
            return 0;
        case 0x3139: /* l */
            switch (next) {
                case 0x3131:
                    return 0x313a;
                case 0x3141:
                    return 0x313b;
                case 0x3142:
                    return 0x313c;
                case 0x3145:
                    return 0x313d;
                case 0x314c:
                    return 0x313e;
                case 0x314d:
                    return 0x313f;
                case 0x314e:
                    return 0x3140;
            }
            return 0;
        case 0x3142: /* b */
            return next == 0x3145 ? 0x3144 : 0;
    }
    return 0;
}

/* func_ov095_0229b454: the jamo (to a 0) read as one syllable into `parts`: the initial, the
 * vowel (two combined) and the final (two combined, 0 for none); 1 when they make one. */
int SoftKeyboard_HangulParse(SoftKeyboard *kb, const u16 *jamo, u16 *parts)
{
    int i;
    u16 compound;

    if (SoftKeyboard_IsConsonant(kb, jamo[0]) == 0) {
        return 0;
    }
    parts[0] = jamo[0];
    if (SoftKeyboard_IsVowel(kb, jamo[1]) == 0) {
        return 0;
    }
    parts[1] = jamo[1];
    i = 2;
    if (jamo[i] == 0) {
        return 1;
    }
    if (SoftKeyboard_IsVowel(kb, jamo[i]) != 0) {
        compound = soft_keyboard_compound_vowel(parts[1], jamo[i]);
        if (compound == 0) {
            return 0;
        }
        parts[1] = compound;
        i++;
    }
    if (jamo[i] == 0) {
        return 1;
    }
    if (SoftKeyboard_IsConsonant(kb, jamo[i]) == 0) {
        return 0;
    }
    if (SoftKeyboard_HangulFinalIndex(kb, jamo[i]) == 0) {
        return 0;
    }
    parts[2] = jamo[i];
    if (jamo[i + 1] == 0) {
        return 1;
    }
    if (SoftKeyboard_IsConsonant(kb, jamo[i + 1]) == 0) {
        return 0;
    }
    compound = soft_keyboard_compound_final(parts[2], jamo[i + 1]);
    if (compound == 0) {
        return 0;
    }
    parts[2] = compound;
    return jamo[i + 2] == 0;
}
CLEAN_AS(func_ov095_0229b454, SoftKeyboard_HangulParse)

/* func_ov095_0229b704: the syllable of the jamo (to a 0), 0 when they make none or one the
 * table lacks. */
int SoftKeyboard_HangulCompose(SoftKeyboard *kb, const u16 *jamo)
{
    u16 parts[6];
    int syllable;
    int i;

    memset(parts, 0, sizeof(parts));
    if (SoftKeyboard_HangulParse(kb, jamo, parts) == 0) {
        return 0;
    }
    syllable = SoftKeyboard_HangulJamoValue(kb, parts[0]);
    syllable = (u16) (syllable + SoftKeyboard_HangulJamoValue(kb, parts[1]));
    if (parts[2] != 0) {
        syllable = (u16) (syllable + SoftKeyboard_HangulFinalIndex(kb, parts[2]));
    }
    for (i = 0; i < SOFT_KEYBOARD_SYLLABLES; i++) {
        if (syllable == data_ov095_0229d0f8[i]) {
            return syllable;
        }
    }
    return 0;
}
CLEAN_AS(func_ov095_0229b704, SoftKeyboard_HangulCompose)

/* func_ov095_0229b784: a character tried on the composition. `carried` becomes the character
 * and `composed` 0; then for a jamo after a composition:
 * - the composition and it make a syllable: `composed` is it, `carried` 0; 1;
 * - else the composition's last jamo and it make one: `carried` is that, `composed` the
 *   syllable of the rest (0 for none); 2.
 * Otherwise 0.
 * REQUIRES: the composition holds at most 5 jamo. */
int SoftKeyboard_HangulAddJamo(SoftKeyboard *kb, u16 jamo)
{
    u16 trial[10];
    int syllable;

    kb->carried = jamo;
    kb->composed = 0;
    if (SoftKeyboard_IsJamo(kb, jamo) == 0) {
        return SOFT_KEYBOARD_COMPOSE_NEW;
    }
    if (kb->composition_length == 0) {
        return SOFT_KEYBOARD_COMPOSE_NEW;
    }
    memset(trial, 0, sizeof(trial));
    MIi_CpuCopy16(kb->composition, trial, sizeof(kb->composition));
    trial[SOFT_KEYBOARD_COMPOSITION] = 0;
    trial[kb->composition_length] = jamo;

    syllable = SoftKeyboard_HangulCompose(kb, trial);
    if (syllable != 0) {
        kb->carried = 0;
        kb->composed = (u16) syllable;
        return SOFT_KEYBOARD_COMPOSE_REPLACE;
    }
    syllable = SoftKeyboard_HangulCompose(kb, &trial[kb->composition_length - 1]);
    if (syllable != 0) {
        kb->carried = (u16) syllable;
        trial[kb->composition_length - 1] = 0;
        syllable = SoftKeyboard_HangulCompose(kb, trial);
        if (syllable != 0) {
            kb->composed = (u16) syllable;
        }
        return SOFT_KEYBOARD_COMPOSE_SPLIT;
    }
    return SOFT_KEYBOARD_COMPOSE_NEW;
}
CLEAN_AS(func_ov095_0229b784, SoftKeyboard_HangulAddJamo)

/* func_ov095_0229b810: a consonant's place as a final (1-27), 0 for another character. */
int SoftKeyboard_HangulFinalIndex(SoftKeyboard *kb, int jamo)
{
    u32 index = (u32) jamo - SOFT_KEYBOARD_JAMO_FIRST;

    (void) kb;
    if (index < SOFT_KEYBOARD_JAMO_COUNT) {
        return soft_keyboard_final_index[index];
    }
    return 0;
}
CLEAN_AS(func_ov095_0229b810, SoftKeyboard_HangulFinalIndex)

/* func_ov095_0229b8d8: what a jamo adds to a syllable: an initial consonant its syllable
 * (0xac00 + initial * 588), a vowel (or anything from 0x314f up) its distance from 0x314f
 * times 28, kept to 16 bits; 0 for anything else. */
int SoftKeyboard_HangulJamoValue(SoftKeyboard *kb, unsigned int jamo)
{
    u32 index = jamo - SOFT_KEYBOARD_JAMO_FIRST;

    (void) kb;
    if (index < SOFT_KEYBOARD_JAMO_COUNT) {
        return soft_keyboard_initial_base[index];
    }
    if (jamo < SOFT_KEYBOARD_VOWEL_FIRST) {
        return 0;
    }
    return (u16) ((jamo - SOFT_KEYBOARD_VOWEL_FIRST) * 28);
}
CLEAN_AS(func_ov095_0229b8d8, SoftKeyboard_HangulJamoValue)

/* func_ov095_0229b9e0 */
int SoftKeyboard_IsJamo(SoftKeyboard *kb, unsigned int character)
{
    return SoftKeyboard_IsVowel(kb, character) != 0 || SoftKeyboard_IsConsonant(kb, character) != 0;
}
CLEAN_AS(func_ov095_0229b9e0, SoftKeyboard_IsJamo)

/* func_ov095_0229ba0c */
int SoftKeyboard_IsConsonant(SoftKeyboard *kb, unsigned int character)
{
    (void) kb;
    return character >= SOFT_KEYBOARD_JAMO_FIRST && character <= SOFT_KEYBOARD_CONSONANT_LAST;
}
CLEAN_AS(func_ov095_0229ba0c, SoftKeyboard_IsConsonant)

/* func_ov095_0229ba28 */
int SoftKeyboard_IsVowel(SoftKeyboard *kb, unsigned int character)
{
    (void) kb;
    return character >= SOFT_KEYBOARD_VOWEL_FIRST && character <= SOFT_KEYBOARD_VOWEL_LAST;
}
CLEAN_AS(func_ov095_0229ba28, SoftKeyboard_IsVowel)
