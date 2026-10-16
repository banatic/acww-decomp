/* Parts of the save written to the game card's save memory (backup_card.h) on their own,
 * without the whole state block. The card holds two copies of the state block (0x173fc bytes
 * each) and the block of letters kept (letter_store.h, 0xc804 bytes), at the offsets of
 * data_020d1c20 (CARD_SAVE_*); a part goes to the same offset in each copy as it has in the
 * state block, and to both copies.
 *
 * Each write is synchronous (BackupCard_Write) and the functions give 1 as soon as one fails,
 * else 0. */
#ifndef CLEAN_MAIN_CARD_SAVE_H
#define CLEAN_MAIN_CARD_SAVE_H

#include "types.h"

enum CardSavePart {
    CARD_SAVE_COPY_0 = 0,  /* offset 0 */
    CARD_SAVE_COPY_1 = 1,  /* offset 0x173fc */
    CARD_SAVE_LETTERS = 2, /* offset 0x337fc */
};

int CardSave_WriteExchangeBlock(void);
int CardSave_WriteFriendRoster(void);
int CardSave_WriteAccount(void);
int CardSave_WriteClearedMarks(void);
int CardSave_ClearByte3FFFC(void);
int CardSave_SameSerial(void);

#endif
