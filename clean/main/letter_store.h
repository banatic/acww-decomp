/* The letters a player keeps: 50 for each of the town's four players, 0x3200 bytes each, in a
 * block that data_021f3c3c points to at 0xc4 (func_020a1368; func_020989e0 finds a player's
 * part). They are seen as two pages of 25 letters (LetterStore_Page). */
#ifndef CLEAN_MAIN_LETTER_STORE_H
#define CLEAN_MAIN_LETTER_STORE_H

#include "mail.h"

#define LETTER_STORE_PAGES 2
#define LETTER_STORE_PAGE_LETTERS 25
#define LETTER_STORE_LETTERS (LETTER_STORE_PAGES * LETTER_STORE_PAGE_LETTERS)

void LetterStore_Clear(Letter *letters);
Letter *LetterStore_Page(Letter *letters, int page);
void LetterStore_MarkBlockReady(u8 *block);
void LetterStore_MarkBlock1C(u8 *block);
int LetterStore_IsBlockReady(u8 *block);

#endif
