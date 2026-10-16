/* The letter waiting for the current player (part_1704c of the state block, data_021f37f4,
 * 0x104 bytes): a letter (mail.h) and the checksum byte the save keeps for it (card_save.c).
 * Mail_DeliverWaiting (mail.h) hands it to the current player and empties it. */
#ifndef CLEAN_MAIN_WAITING_LETTER_H
#define CLEAN_MAIN_WAITING_LETTER_H

#include "mail.h" /* MailLetter */
#include "types.h"

typedef struct WaitingLetter {
    MailLetter letter; /* its first word is the letter's vtable (data_020de760) */
    u8 checksum;       /* 0x100 */
    u8 pad_101[3];
} WaitingLetter;

MailLetter *WaitingLetter_Letter(WaitingLetter *waiting);
u8 WaitingLetter_Checksum(WaitingLetter *waiting);
void WaitingLetter_SetChecksum(WaitingLetter *waiting, u8 checksum);
int WaitingLetter_IsSet(WaitingLetter *waiting);
void WaitingLetter_Clear(WaitingLetter *waiting);
int WaitingLetter_Destruct(WaitingLetter *waiting);
WaitingLetter *WaitingLetter_Construct(WaitingLetter *waiting);

#endif
