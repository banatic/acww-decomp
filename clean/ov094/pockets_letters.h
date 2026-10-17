/* Overlay 094's letters object (vtable data_ov094_0229c114, 0x28 bytes), the second of the
 * objects the pockets scenes keep (at 0xdb8 of ov096's PocketsScreen, 0xb2c of ov099's
 * PocketsView and ov100's PocketsBox, 0xd5c of ov105's LetterStorage). It is built like the grid
 * object (pockets_grid.h): three sets of bits by place (whether it holds a letter, whether it is
 * marked, whether it is dimmed), a lifted place and a pick-up whose size steps back to full.
 *
 * Its places take letters from lists of 0x100-byte letters (main/letter.h): the current
 * player's ten at places 0-9, a page of 25 at places 10-34 (ov105's letter storage), and ten at
 * places 0x23-0x2c (ov106). */
#ifndef CLEAN_OV094_POCKETS_LETTERS_H
#define CLEAN_OV094_POCKETS_LETTERS_H

#include "main/letter.h"
#include "pockets_grid.h" /* PocketsBits */
#include "types.h"

#define POCKETS_LETTERS_NO_PLACE 0x37
#define POCKETS_LETTERS_FULL_SIZE 10 /* `held_size`, in tenths */
#define POCKETS_LETTERS_PICKUP_STEPS 4
/* PocketsLetters_IconOf for a place without a letter. */
#define POCKETS_LETTERS_NO_ICON (-1)

typedef struct PocketsLetters {
    u32 vtable;         /* 0x00: data_ov094_0229c114 */
    Letter *letters;    /* 0x04: the list last given (PocketsLetters_SetList) */
    PocketsBits filled; /* 0x08: the place holds a letter */
    PocketsBits marked; /* 0x10 */
    PocketsBits dimmed; /* 0x18 */
    s32 priority;       /* 0x20: the OBJs' priority */
    u8 lifted;          /* 0x24: the place lifted, POCKETS_LETTERS_NO_PLACE for none */
    u8 lift;            /* 0x25: counts down, as the grid's */
    u8 pickup_step;     /* 0x26: steps of the pick-up left */
    u8 held_size;       /* 0x27: the held letter's size in tenths */
} PocketsLetters;

int PocketsLetterBits_Test(PocketsBits *bits, int bit);
void PocketsLetterBits_Clear(PocketsBits *bits, int bit);
void PocketsLetterBits_Set(PocketsBits *bits, int bit);
void PocketsLetterBits_ClearAll(PocketsBits *bits);
int PocketsLetters_PickUpSize(PocketsLetters *letters);
int PocketsLetters_StepPickUp(PocketsLetters *letters);
void PocketsLetters_EndPickUp(PocketsLetters *letters);
void PocketsLetters_StartPickUp(PocketsLetters *letters);
int PocketsLetters_IconOf(PocketsLetters *letters, const Letter *letter);
void PocketsLetters_SetList(PocketsLetters *letters, Letter *list, int first_place, int count);
void PocketsLetters_SetTenAt23(PocketsLetters *letters, Letter *list);

#endif
