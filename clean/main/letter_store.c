/* The letters a player keeps (letter_store.h). */
#include "letter_store.h"

#include "clean.h"

extern void func_02066650(MailLetter *letter); /* empty it */

/* func_02097f38: empty all 50 letters. */
void LetterStore_Clear(MailLetter *letters)
{
    for (int i = 0; i < LETTER_STORE_LETTERS; i++) {
        func_02066650(&letters[i]);
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
