/* Overlay 094's letters object (pockets_letters.h): its sets of bits, the held letter's pick-up
 * and the places' letters. */
#include "pockets_letters.h"

#include "clean.h"
#include "main/player_pockets.h"

static_assert(offsetof(PocketsLetters, filled) == 0x08 && offsetof(PocketsLetters, dimmed) == 0x18, "letters bits");
static_assert(offsetof(PocketsLetters, priority) == 0x20 && offsetof(PocketsLetters, lifted) == 0x24, "letters");
static_assert(offsetof(PocketsLetters, held_size) == 0x27 && sizeof(PocketsLetters) == 0x28, "letters size");
static_assert(sizeof(Letter) == 0x100, "letter");

/* The held letter's sizes at pick-up steps 0 to 3 (2, 4, 6, 8 tenths). */
extern const u8 data_ov094_0229bddc[];

/* The first places of the ten letters PocketsLetters_SetTenAt23 is given. */
#define POCKETS_LETTERS_TEN_FIRST 0x23
#define POCKETS_LETTERS_TEN 10

/* func_ov094_0229b110. REQUIRES: `bit` in 0-63 (the places use 0-0x36). */
int PocketsLetterBits_Test(PocketsBits *bits, int bit)
{
    return (bits->words[bit >> 5] & (1u << (bit & 31))) != 0;
}
CLEAN_AS(func_ov094_0229b110, PocketsLetterBits_Test)

/* func_ov094_0229b134. REQUIRES: `bit` in 0-63. */
void PocketsLetterBits_Clear(PocketsBits *bits, int bit)
{
    bits->words[bit >> 5] &= ~(1u << (bit & 31));
}
CLEAN_AS(func_ov094_0229b134, PocketsLetterBits_Clear)

/* func_ov094_0229b154. REQUIRES: `bit` in 0-63. */
void PocketsLetterBits_Set(PocketsBits *bits, int bit)
{
    bits->words[bit >> 5] |= 1u << (bit & 31);
}
CLEAN_AS(func_ov094_0229b154, PocketsLetterBits_Set)

/* func_ov094_0229b174 */
void PocketsLetterBits_ClearAll(PocketsBits *bits)
{
    for (int i = 0; i < 2; i++) {
        bits->words[i] = 0;
    }
}
CLEAN_AS(func_ov094_0229b174, PocketsLetterBits_ClearAll)

/* func_ov094_0229b184: the held letter's size at this step of the pick-up; full size once the
 * steps are over. */
int PocketsLetters_PickUpSize(PocketsLetters *letters)
{
    u8 step = letters->pickup_step;

    if (step >= POCKETS_LETTERS_PICKUP_STEPS) {
        return POCKETS_LETTERS_FULL_SIZE;
    }
    return data_ov094_0229bddc[step];
}
CLEAN_AS(func_ov094_0229b184, PocketsLetters_PickUpSize)

/* func_ov094_0229b19c: a step of the pick-up (the held letter shrinks to 8, 6, 4 and 2 tenths);
 * 1 once it is over, the letter back at full size. */
int PocketsLetters_StepPickUp(PocketsLetters *letters)
{
    if (letters->pickup_step != 0) {
        letters->pickup_step--;
        letters->held_size = (u8) PocketsLetters_PickUpSize(letters);
        return 0;
    }
    PocketsLetters_EndPickUp(letters);
    return 1;
}
CLEAN_AS(func_ov094_0229b19c, PocketsLetters_StepPickUp)

/* func_ov094_0229b1d0: the held letter at full size. */
void PocketsLetters_EndPickUp(PocketsLetters *letters)
{
    letters->held_size = POCKETS_LETTERS_FULL_SIZE;
}
CLEAN_AS(func_ov094_0229b1d0, PocketsLetters_EndPickUp)

/* func_ov094_0229b1d8: a pick-up of four steps started, the letter at full size. */
void PocketsLetters_StartPickUp(PocketsLetters *letters)
{
    letters->pickup_step = POCKETS_LETTERS_PICKUP_STEPS;
    letters->held_size = POCKETS_LETTERS_FULL_SIZE;
}
CLEAN_AS(func_ov094_0229b1d8, PocketsLetters_StartPickUp)

/* func_ov094_0229b1e8: the icon of `letter`: POCKETS_LETTERS_NO_ICON when its state is 0 (no
 * letter), else two by state from state 1, the second of the two when it carries an item. */
int PocketsLetters_IconOf(PocketsLetters *letters, const Letter *letter)
{
    int state = Letter_State(letter);
    int icon;

    (void) letters;
    if (state == 0) {
        return POCKETS_LETTERS_NO_ICON;
    }
    icon = (state - 1) * 2;
    if (Letter_Item(letter) != PLAYER_POCKETS_NO_ITEM) {
        icon++;
    }
    return icon;
}
CLEAN_AS(func_ov094_0229b1e8, PocketsLetters_IconOf)

/* func_ov094_0229b220: `list` kept, and its first `count` letters put at the places from
 * `first_place`: each place is filled when its letter has an icon. */
void PocketsLetters_SetList(PocketsLetters *letters, Letter *list, int first_place, int count)
{
    const Letter *letter;

    letters->letters = list;
    letter = letters->letters;
    for (int i = 0; i < count; i++, letter++) {
        if (PocketsLetters_IconOf(letters, letter) != POCKETS_LETTERS_NO_ICON) {
            PocketsLetterBits_Set(&letters->filled, first_place + i);
        } else {
            PocketsLetterBits_Clear(&letters->filled, first_place + i);
        }
    }
}
CLEAN_AS(func_ov094_0229b220, PocketsLetters_SetList)

/* func_ov094_0229b274: the ten letters of `list` at places 0x23-0x2c. */
void PocketsLetters_SetTenAt23(PocketsLetters *letters, Letter *list)
{
    PocketsLetters_SetList(letters, list, POCKETS_LETTERS_TEN_FIRST, POCKETS_LETTERS_TEN);
}
CLEAN_AS(func_ov094_0229b274, PocketsLetters_SetTenAt23)
