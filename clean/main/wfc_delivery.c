/* The notice and the letter the Nintendo Wi-Fi Connection delivers (wfc_delivery.h). */
#include "wfc_delivery.h"

#include "clean.h"
#include "player_record.h"
#include "player_records.h"
#include "letter.h"

static_assert(offsetof(WfcNotice, number) == 0xc0, "WfcNotice layout");
static_assert(offsetof(WfcNotice, hmac) == 0xc2, "WfcNotice layout");
static_assert(sizeof(WfcNotice) == 0xd2, "WfcNotice size");
static_assert(offsetof(WfcLetter, number) == 0x100, "WfcLetter layout");
static_assert(offsetof(WfcLetter, hmac) == 0x102, "WfcLetter layout");
static_assert(sizeof(WfcLetter) == 0x114, "WfcLetter size");

/* The town's board. */
extern Bbs data_021eed68;

/* func_0203f5a4: a notice whose number is not the board's last posted, the number kept; 1 when
 * posted. */
int WfcDelivery_PostNotice(WfcNotice *notice)
{
    Bbs *bbs = &data_021eed68;
    u16 number = notice->number;

    if (number == Bbs_GetLastNotice(bbs)) {
        return 0;
    }
    Bbs_SetLastNotice(bbs, (s16) number);
    Bbs_PostText(notice->text);
    return 1;
}
CLEAN_AS(func_0203f5a4, WfcDelivery_PostNotice)

/* func_0203f5d8: where the notice's HMAC is. */
int WfcDelivery_NoticeHmac(WfcNotice *notice)
{
    return (int) (uintptr_t) notice->hmac;
}
CLEAN_AS(func_0203f5d8, WfcDelivery_NoticeHmac)

/* func_0203f5dc: the notice's destructor. */
void WfcDelivery_DestructNotice(WfcNotice *notice)
{
    (void) notice;
}
CLEAN_AS(func_0203f5dc, WfcDelivery_DestructNotice)

/* func_0203f5e0: the notice's constructor. */
void WfcDelivery_ConstructNotice(WfcNotice *notice)
{
    (void) notice;
}
CLEAN_AS(func_0203f5e0, WfcDelivery_ConstructNotice)

/* func_0203f5e4: a letter whose number is not the current player's last, copied, addressed to
 * that player and put in the player's mailbox; once it is in, the number is kept and 1. */
int WfcDelivery_DeliverLetter(WfcLetter *letter)
{
    Letter copy;
    int delivered = 0;

    Letter_Construct(&copy);
    u8 *record = PlayerRecords_Current();
    if (letter->number != PlayerRecord_MailMark(record)) {
        Letter_Assign(&copy, &letter->letter);
        int player = PlayerRecord_Number(record);
        Letter_AddressToPlayer(&copy, player);
        Letter_MarkDelivered(&copy);
        if (Mail_PutInMailbox(&copy, player, 0) != 0) {
            PlayerRecord_SetMailMark(record, letter->number);
            delivered = 1;
        }
    }
    Letter_Destruct(&copy);
    return delivered;
}
CLEAN_AS(func_0203f5e4, WfcDelivery_DeliverLetter)

/* func_0203f658: where the letter at `letter` has its HMAC. */
u32 WfcDelivery_LetterHmac(u32 letter)
{
    return letter + offsetof(WfcLetter, hmac);
}
CLEAN_AS(func_0203f658, WfcDelivery_LetterHmac)

/* func_0203f664: the letter's destructor; its address. */
int WfcDelivery_DestructLetter(WfcLetter *letter)
{
    Letter_Destruct(&letter->letter);
    return (int) (uintptr_t) letter;
}
CLEAN_AS(func_0203f664, WfcDelivery_DestructLetter)

/* func_0203f674: the letter's constructor; its address. */
int WfcDelivery_ConstructLetter(WfcLetter *letter)
{
    Letter_Construct(&letter->letter);
    return (int) (uintptr_t) letter;
}
CLEAN_AS(func_0203f674, WfcDelivery_ConstructLetter)
