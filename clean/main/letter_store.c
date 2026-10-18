/* The letters a player keeps (letter_store.h). */
#include "letter_store.h"

#include "clean.h"
#include "letter.h"

/* func_02097f38: empty all 50 letters. */
void LetterStore_Clear(MailLetter *letters)
{
    for (int i = 0; i < LETTER_STORE_LETTERS; i++) {
        Letter_Clear((Letter *) &letters[i]);
    }
}
CLEAN_AS(func_02097f38, LetterStore_Clear)

/* func_02097f58: the first letter of page `page`; NULL outside 0-1. */
MailLetter *LetterStore_Page(MailLetter *letters, int page)
{
    if (page >= 0 && page < LETTER_STORE_PAGES) {
        return &letters[page * LETTER_STORE_PAGE_LETTERS];
    }
    return NULL;
}
CLEAN_AS(func_02097f58, LetterStore_Page)

/* The byte after the four players' letters in the block (func_020a1368): 2 once the block was
 * set up (its maker clears the block when the byte is anything else). */
#define LETTER_STORE_BLOCK_STATE 0xc800
#define LETTER_STORE_BLOCK_READY 2

/* func_0209e5d8 */
void LetterStore_MarkBlockReady(u8 *block)
{
    block[LETTER_STORE_BLOCK_STATE] = LETTER_STORE_BLOCK_READY;
}
CLEAN_AS(func_0209e5d8, LetterStore_MarkBlockReady)

/* func_0209e5e4: the state byte set to 0x1c, a value whose meaning is not known. */
void LetterStore_MarkBlock1C(u8 *block)
{
    block[LETTER_STORE_BLOCK_STATE] = 0x1c;
}
CLEAN_AS(func_0209e5e4, LetterStore_MarkBlock1C)

/* func_0209e5f0 */
int LetterStore_IsBlockReady(u8 *block)
{
    return block[LETTER_STORE_BLOCK_STATE] == LETTER_STORE_BLOCK_READY;
}
CLEAN_AS(func_0209e5f0, LetterStore_IsBlockReady)
