/* The insurance letters and the "sp_npc_missing" letter (npc_letters.h). */
#include "npc_letters.h"

#include "calendar.h"
#include "clean.h"
#include "mail.h"
#include "mail_text.h"
#include "message_texts.h"
#include "mom_letters.h"
#include "number_text.h"
#include "player_record.h"
#include "player_records.h"
#include "item_lists.h"
#include "letter.h"
#include "main_random.h"
#include "player_id.h"

/* The player record's flags: insurance letters are sent at all (0x17), a bee sting (0x19, set
 * by overlay 3's field actor when stung) and a fall (0x1a), each paid with
 * NPC_LETTERS_INSURANCE_ITEM, and the cover for forged paintings (0x18; the flag stays set),
 * which pays for those claimed in PlayerField2416.forgery_claims. Flag 0x36 asks for the
 * "sp_npc_missing" letter, the lost child's and its mother's thanks. */
#define NPC_LETTERS_FLAG_INSURED 0x17
#define NPC_LETTERS_FLAG_FORGERY_COVER 0x18
#define NPC_LETTERS_FLAG_STING_CLAIM 0x19
#define NPC_LETTERS_FLAG_FALL_CLAIM 0x1a
#define NPC_LETTERS_FLAG_LOST_CHILD_THANKS 0x36

/* The item a sting or a fall pays; n forged paintings claimed pay item
 * NPC_LETTERS_FORGERY_ITEM_BASE + n, with n * 100 written into the letter, n at most 10. */
#define NPC_LETTERS_INSURANCE_ITEM 0x1492
#define NPC_LETTERS_FORGERY_ITEM_BASE 0x1491
#define NPC_LETTERS_FORGERIES_MAX 10
#define NPC_LETTERS_FORGERY_AMOUNT 100

/* The insurance messages: two for a bee sting (0-1), two for a fall (2-3), two for forged
 * paintings (4-5) and the one for many of them (6). */
#define NPC_LETTERS_MESSAGE_STING 0
#define NPC_LETTERS_MESSAGE_FALL 2
#define NPC_LETTERS_MESSAGE_FORGERIES 4
#define NPC_LETTERS_MESSAGE_FORGERIES_MANY 6

/* The letter parts the forgeries' letter fills: the count and the amount. */
#define NPC_LETTERS_PART_COUNT 3
#define NPC_LETTERS_PART_AMOUNT 4
#define NPC_LETTERS_DIGITS 10

/* The paper set and the item list of the "sp_npc_missing" letter, and its messages. */
#define NPC_LETTERS_MISSING_PAPER_SET 3
#define NPC_LETTERS_MISSING_LIST_GROUP 0x1b
#define NPC_LETTERS_MISSING_MESSAGES 3

/* A player's name as text (0x24 bytes): built by func_02094fd4, destroyed by func_02094fbc;
 * the one built here is not used. */
typedef struct NpcLettersNameText {
    u32 words[0x24 / 4];
} NpcLettersNameText;

/* A list of items (func_02063ccc constructs it, func_02063cc8 destructs it). */
typedef struct NpcLettersItemList {
    int kind;
    int group;
} NpcLettersItemList;

extern const char data_020e1fdc[]; /* "sp_npc_insurance" */
extern const char data_020e1ff0[]; /* "sp_npc_missing" */
/* The letters' kind byte and paper: the insurance letters' (7, 0x1e) and the
 * "sp_npc_missing" letter's kind (0x0d). */
extern u8 data_020e1f60[];
extern u8 data_020e1f68[];
extern u8 data_020e1f58[];

/* func_02088810: the insurance letters of the current player. With flag 0x17, each of the
 * claims for a sting (0x19) and a fall (0x1a) is paid with one letter (one of two messages)
 * and cleared once it was taken; with flag 0x18 (the forgery cover) and at least one forged
 * painting claimed in `field`, one letter pays for them all (the count and the amount written
 * into its parts 3 and 4) and the count is cleared once it was taken.
 * QUIRK: the counts are read from the current player's object while the one cleared is
 * `field` (the caller passes the same). The count written into part 3 is not capped at 10. */
void NpcLetters_SendInsurance(PlayerField2416 *field)
{
    MessageText46 number;
    NpcLettersNameText name;
    u16 sting;
    u16 fall;
    u16 counted;

    MessageText46_Construct(&number);
    u8 *record = PlayerRecords_Current();
    PlayerIdText_Construct((PlayerIdText *) &name);
    PlayerField2416 *own = (PlayerField2416 *) PlayerRecord_Field2416(record);

    if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_INSURED) != 0) {
        if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_STING_CLAIM) != 0) {
            sting = NPC_LETTERS_INSURANCE_ITEM;
            int message = NPC_LETTERS_MESSAGE_STING + (int) MainRandom_Below(2);
            if (NpcLetters_SendInsuranceLetter(field, message, &sting) != 0) {
                PlayerRecord_ClearFlag(record, NPC_LETTERS_FLAG_STING_CLAIM);
            }
        }
        if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_FALL_CLAIM) != 0) {
            fall = NPC_LETTERS_INSURANCE_ITEM;
            int message = NPC_LETTERS_MESSAGE_FALL + (int) MainRandom_Below(2);
            if (NpcLetters_SendInsuranceLetter(field, message, &fall) != 0) {
                PlayerRecord_ClearFlag(record, NPC_LETTERS_FLAG_FALL_CLAIM);
            }
        }
    }

    if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_FORGERY_COVER) != 0 && PlayerField2416_ForgeryClaims(own) >= 1) {
        NumberText_Format(&number, PlayerField2416_ForgeryClaims(own), NPC_LETTERS_DIGITS, 0, 0, 0);
        MailText_SetPartText(NPC_LETTERS_PART_COUNT, &number);
        int message = NPC_LETTERS_MESSAGE_FORGERIES + (int) MainRandom_Below(2);
        u32 claims = (u32) PlayerField2416_ForgeryClaims(own);
        if (claims >= NPC_LETTERS_FORGERIES_MAX) {
            claims = NPC_LETTERS_FORGERIES_MAX;
            message = NPC_LETTERS_MESSAGE_FORGERIES_MANY;
        }
        NumberText_Format(&number, (int) (claims * NPC_LETTERS_FORGERY_AMOUNT), NPC_LETTERS_DIGITS, 0, 0, 0);
        MailText_SetPartText(NPC_LETTERS_PART_AMOUNT, &number);
        counted = (u16) (claims + NPC_LETTERS_FORGERY_ITEM_BASE);
        if (NpcLetters_SendInsuranceLetter(field, message, &counted) != 0) {
            field->forgery_claims = 0;
        }
    }

    PlayerIdText_Destruct((PlayerIdText *) &name);
    MessageText46_Destruct(&number);
}
CLEAN_AS(func_02088810, NpcLetters_SendInsurance)

/* func_0208893c: an insurance letter of message `message` carrying *item, to the current
 * player, left at the post office; whether it was taken. `field` is not read. */
int NpcLetters_SendInsuranceLetter(PlayerField2416 *field, int message, u16 *item)
{
    (void) field;
    Letter letter;
    Letter_Construct(&letter);
    u8 *record = PlayerRecords_Current();
    u8 number = (u8) message;
    Letter_WriteSpecialToPlayer(&letter, &number, data_020e1fdc, data_020e1f60, data_020e1f68, PlayerRecord_Player(record));
    Letter_SetItem(&letter, *item, 1);
    int taken = Mail_HoldAtPostOffice(&letter, 0) != 0;
    Letter_Destruct(&letter);
    return taken;
}
CLEAN_AS(func_0208893c, NpcLetters_SendInsuranceLetter)

/* func_020889a8: with the current player's flag 0x36, the "sp_npc_missing" letter (one of
 * three messages, on a paper of this month's from set 3, with an item drawn from item list
 * 0x1b) left at the post office; the flag is cleared once it was taken. */
void NpcLetters_SendMissing(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return;
    }
    if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_LOST_CHILD_THANKS) == 0) {
        return;
    }

    Letter letter;
    Letter_Construct(&letter);
    u8 message = (u8) MainRandom_Below(NPC_LETTERS_MISSING_MESSAGES);
    Date today;
    Calendar_Today(&today);
    u8 paper = (u8) MomLetters_PickPaper(NPC_LETTERS_MISSING_PAPER_SET, today.month);
    Letter_WriteSpecialToPlayer(&letter, &message, data_020e1ff0, data_020e1f58, &paper, PlayerRecord_Player(record));

    NpcLettersItemList list;
    u16 item;
    ItemList_Construct((ItemList *) &list, 0, NPC_LETTERS_MISSING_LIST_GROUP);
    ItemLists_Pick(&item, (ItemList *) &list, 0, 0, 1, 1, 0);
    Letter_SetItem(&letter, item, 1);
    ItemList_Destruct(&list);

    if (Mail_HoldAtPostOffice(&letter, 0) != 0) {
        PlayerRecord_ClearFlag(record, NPC_LETTERS_FLAG_LOST_CHILD_THANKS);
    }
    Letter_Destruct(&letter);
}
CLEAN_AS(func_020889a8, NpcLetters_SendMissing)
