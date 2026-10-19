/* What the Nintendo Wi-Fi Connection delivers (wfc_session.h): a notice for the town's board
 * and a letter for the current player, each followed by its number and an HMAC. A number seen
 * before is not delivered again (the board keeps the last notice's, the player's record the
 * last letter's).
 *
 * The notice and the letter are C++ objects; the notice's constructor and destructor do
 * nothing, the letter's are the letter's own (func_02066694 and func_02066688, which set the
 * vtable of its first 0x100 bytes). */
#ifndef CLEAN_MAIN_WFC_DELIVERY_H
#define CLEAN_MAIN_WFC_DELIVERY_H

#include "main/bbs.h"
#include "main/mail.h"
#include "types.h"

#define WFC_DELIVERY_HMAC_SIZE 0x10

/* A notice (0xd2 bytes). */
typedef struct WfcNotice {
    u16 text[BBS_POST_LENGTH];       /* 0x00: what is posted */
    u16 number;                      /* 0xc0 */
    u8 hmac[WFC_DELIVERY_HMAC_SIZE]; /* 0xc2: of the notice with these bytes zero */
} WfcNotice;

/* A letter (0x114 bytes). */
typedef struct WfcLetter {
    Letter letter;                   /* 0x000 */
    u16 number;                      /* 0x100 */
    u8 hmac[WFC_DELIVERY_HMAC_SIZE]; /* 0x102: of the letter with these bytes zero */
    u8 pad_112[2];
} WfcLetter;

int WfcDelivery_PostNotice(WfcNotice *notice);
int WfcDelivery_NoticeHmac(WfcNotice *notice);
void WfcDelivery_DestructNotice(WfcNotice *notice);
void WfcDelivery_ConstructNotice(WfcNotice *notice);
int WfcDelivery_DeliverLetter(WfcLetter *letter);
u32 WfcDelivery_LetterHmac(u32 letter);
int WfcDelivery_DestructLetter(WfcLetter *letter);
int WfcDelivery_ConstructLetter(WfcLetter *letter);

#endif
