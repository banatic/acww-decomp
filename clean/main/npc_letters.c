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

/* The player record's flags: insurance letters are sent at all (0x17), two claims each paid
 * with NPC_LETTERS_INSURANCE_ITEM (0x19, 0x1a), and claims counted in PlayerField2416.claims
 * (0x18; the flag stays set). Flag 0x36 asks for the "sp_npc_missing" letter. */
#define NPC_LETTERS_FLAG_INSURED 0x17
#define NPC_LETTERS_FLAG_COUNTED 0x18
#define NPC_LETTERS_FLAG_CLAIM_A 0x19
#define NPC_LETTERS_FLAG_CLAIM_B 0x1a
#define NPC_LETTERS_FLAG_MISSING 0x36

/* The item a claim pays; n counted claims pay item NPC_LETTERS_COUNTED_ITEM_BASE + n, with
 * n * 100 written into the letter, n at most 10. */
#define NPC_LETTERS_INSURANCE_ITEM 0x1492
#define NPC_LETTERS_COUNTED_ITEM_BASE 0x1491
#define NPC_LETTERS_COUNTED_MAX 10
#define NPC_LETTERS_COUNTED_AMOUNT 100

/* The insurance messages: two for each claim (0-1, 2-3), two for counted claims (4-5) and
 * the one for the most (6). */
#define NPC_LETTERS_MESSAGE_CLAIM_A 0
#define NPC_LETTERS_MESSAGE_CLAIM_B 2
#define NPC_LETTERS_MESSAGE_COUNTED 4
#define NPC_LETTERS_MESSAGE_COUNTED_MAX 6

/* The letter parts the counted claims fill: the count and the amount. */
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

extern u32 func_020644cc(int bound); /* a random number below `bound` */
extern void *func_02094fd4(NpcLettersNameText *text);
extern void *func_02094fbc(NpcLettersNameText *text);
/* A letter: constructed, written (message *message of archive `name`, kind byte and paper,
 * for the player named), given an item, destructed. */
extern void func_02066694(MailLetter *letter);
extern void func_02066024(MailLetter *letter, u8 *message, const char *name, u8 *kind, u8 *paper, void *player_name);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int arg);
extern void func_02066688(MailLetter *letter);
extern void func_02063ccc(NpcLettersItemList *list, int kind, int group);
extern void func_020638d4(u16 *item, NpcLettersItemList *list, int a, int b, int c, int d, int e);
extern void func_02063cc8(NpcLettersItemList *list);

/* func_02088810: the insurance letters of the current player. With flag 0x17, each of the
 * claims 0x19 and 0x1a is paid with one letter (one of two messages) and cleared once it was
 * taken; with flag 0x18 and at least one claim counted in `field`, one letter pays for them
 * all (the count and the amount written into its parts 3 and 4) and the count is cleared once
 * it was taken.
 * QUIRK: the counts are read from the current player's object while the one cleared is
 * `field` (the caller passes the same). The count written into part 3 is not capped at 10. */
void NpcLetters_SendInsurance(PlayerField2416 *field)
{
    MessageText46 number;
    NpcLettersNameText name;
    u16 claim_a;
    u16 claim_b;
    u16 counted;

    MessageText46_Construct(&number);
    u8 *record = PlayerRecords_Current();
    func_02094fd4(&name);
    PlayerField2416 *own = (PlayerField2416 *) PlayerRecord_Field2416(record);

    if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_INSURED) != 0) {
        if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_CLAIM_A) != 0) {
            claim_a = NPC_LETTERS_INSURANCE_ITEM;
            int message = NPC_LETTERS_MESSAGE_CLAIM_A + (int) func_020644cc(2);
            if (NpcLetters_SendInsuranceLetter(field, message, &claim_a) != 0) {
                PlayerRecord_ClearFlag(record, NPC_LETTERS_FLAG_CLAIM_A);
            }
        }
        if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_CLAIM_B) != 0) {
            claim_b = NPC_LETTERS_INSURANCE_ITEM;
            int message = NPC_LETTERS_MESSAGE_CLAIM_B + (int) func_020644cc(2);
            if (NpcLetters_SendInsuranceLetter(field, message, &claim_b) != 0) {
                PlayerRecord_ClearFlag(record, NPC_LETTERS_FLAG_CLAIM_B);
            }
        }
    }

    if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_COUNTED) != 0 && PlayerField2416_Claims(own) >= 1) {
        NumberText_Format(&number, PlayerField2416_Claims(own), NPC_LETTERS_DIGITS, 0, 0, 0);
        MailText_SetPartText(NPC_LETTERS_PART_COUNT, &number);
        int message = NPC_LETTERS_MESSAGE_COUNTED + (int) func_020644cc(2);
        u32 claims = (u32) PlayerField2416_Claims(own);
        if (claims >= NPC_LETTERS_COUNTED_MAX) {
            claims = NPC_LETTERS_COUNTED_MAX;
            message = NPC_LETTERS_MESSAGE_COUNTED_MAX;
        }
        NumberText_Format(&number, (int) (claims * NPC_LETTERS_COUNTED_AMOUNT), NPC_LETTERS_DIGITS, 0, 0, 0);
        MailText_SetPartText(NPC_LETTERS_PART_AMOUNT, &number);
        counted = (u16) (claims + NPC_LETTERS_COUNTED_ITEM_BASE);
        if (NpcLetters_SendInsuranceLetter(field, message, &counted) != 0) {
            field->claims = 0;
        }
    }

    func_02094fbc(&name);
    MessageText46_Destruct(&number);
}
CLEAN_AS(func_02088810, NpcLetters_SendInsurance)

/* func_0208893c: an insurance letter of message `message` carrying *item, to the current
 * player, left at the post office; whether it was taken. `field` is not read. */
int NpcLetters_SendInsuranceLetter(PlayerField2416 *field, int message, u16 *item)
{
    (void) field;
    MailLetter letter;
    func_02066694(&letter);
    u8 *record = PlayerRecords_Current();
    u8 number = (u8) message;
    func_02066024(&letter, &number, data_020e1fdc, data_020e1f60, data_020e1f68, PlayerRecord_Player(record));
    func_02065ed0(&letter, *item, 1);
    int taken = Mail_HoldAtPostOffice(&letter, 0) != 0;
    func_02066688(&letter);
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
    if (PlayerRecord_TestFlag(record, NPC_LETTERS_FLAG_MISSING) == 0) {
        return;
    }

    MailLetter letter;
    func_02066694(&letter);
    u8 message = (u8) func_020644cc(NPC_LETTERS_MISSING_MESSAGES);
    Date today;
    Calendar_Today(&today);
    u8 paper = (u8) MomLetters_DrawPaper(NPC_LETTERS_MISSING_PAPER_SET, today.month);
    func_02066024(&letter, &message, data_020e1ff0, data_020e1f58, &paper, PlayerRecord_Player(record));

    NpcLettersItemList list;
    u16 item;
    func_02063ccc(&list, 0, NPC_LETTERS_MISSING_LIST_GROUP);
    func_020638d4(&item, &list, 0, 0, 1, 1, 0);
    func_02065ed0(&letter, item, 1);
    func_02063cc8(&list);

    if (Mail_HoldAtPostOffice(&letter, 0) != 0) {
        PlayerRecord_ClearFlag(record, NPC_LETTERS_FLAG_MISSING);
    }
    func_02066688(&letter);
}
CLEAN_AS(func_020889a8, NpcLetters_SendMissing)
