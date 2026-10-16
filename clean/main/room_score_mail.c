/* The "ev_happyroom" letters about the score of the player's house (room_score.h): the first
 * one, the judgement after each week, and the prizes of the totals 70000, 100000 and 150000. */
#include "room_score.h"

#include "clean.h"
#include "game_variables.h"
#include "mail.h"
#include "message_reader.h"
#include "message_texts.h"
#include "number_text.h"
#include "player_record.h"
#include "player_records.h"
#include "state_block.h"

#define ROOM_SCORE_MAIL_PLAYERS 4
#define ROOM_SCORE_MAIL_NO_ITEM 0xfff1
/* PlayerRecord_TestFlag: the record that gets the first letter, and the one that got it. */
#define ROOM_SCORE_MAIL_RECORD_WANTS 3
#define ROOM_SCORE_MAIL_RECORD_MEMBER 0xe
/* The first letter's message. */
#define ROOM_SCORE_MAIL_WELCOME 0x1b
/* The game variable (bank 0) that has the judgement sent to every player. */
#define ROOM_SCORE_MAIL_VARIABLE_ALL 0x22
/* The text slots of the judgement: the total, the group, the theme. */
#define ROOM_SCORE_MAIL_SLOT_TOTAL 1
#define ROOM_SCORE_MAIL_SLOT_GROUP 2
#define ROOM_SCORE_MAIL_SLOT_THEME 3
#define ROOM_SCORE_MAIL_THEMES 4
#define ROOM_SCORE_MAIL_TOTAL_DIGITS 10

/* The text objects of the judgement: a group's name (func_02062f64) and a label
 * (func_020a8228). */
typedef struct RoomScoreMailGroupName {
    u32 words[0x28 / 4];
} RoomScoreMailGroupName;
typedef struct RoomScoreMailLabel {
    u32 words[0x5c / 4];
} RoomScoreMailLabel;

extern const char data_020dd3d8[]; /* "ev_happyroom" */
extern const char data_020dd3e8[]; /* "st_furniture_letter" */
/* The letters' kind bytes (2) and papers (0x1f): the first letter's, the prizes', the
 * judgement's. */
extern u8 data_020dd388[], data_020dd398[];
extern u8 data_020dd38c[], data_020dd394[];
extern u8 data_020dd390[], data_020dd384[];
extern u32 data_021dc7a8[]; /* the state block (state_block.h) */
extern u8 data_021dc7bc[];  /* the town's four players' records */

extern void func_02066694(MailLetter *letter); /* construct */
extern void func_02066688(MailLetter *letter); /* destruct */
/* Write the letter: message `*message` of template `name`; *kind goes to byte 0xfb, *paper to
 * byte 0xf9. */
extern void func_02066024(MailLetter *letter, u8 *message, const char *name, u8 *kind, u8 *paper, void *player_name);
extern u16 func_02065ed0(MailLetter *letter, u16 item, int arg); /* attach an item */
extern int func_0203d7c4(int slot, void *text);                  /* set a message entry */
extern RoomScoreMailGroupName *func_02062f64(RoomScoreMailGroupName *text, int group);
extern RoomScoreMailGroupName *func_02062f4c(RoomScoreMailGroupName *text);
extern void *func_020a8228(RoomScoreMailLabel *label);
extern void *func_020a8210(RoomScoreMailLabel *label);

/* func_0205a2f0: the first letter (message 0x1b) to the current player when its record wants
 * it (flag 3) and has not had it (flag 0xe); posted, it marks the record as having had it.
 * Whether it was posted. */
int RoomScoreMail_SendWelcome(void)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL || PlayerRecord_TestFlag(record, ROOM_SCORE_MAIL_RECORD_WANTS) == 0 ||
        PlayerRecord_TestFlag(record, ROOM_SCORE_MAIL_RECORD_MEMBER) != 0) {
        return 0;
    }
    MailLetter letter;
    func_02066694(&letter);
    u8 message = ROOM_SCORE_MAIL_WELCOME;
    func_02066024(&letter, &message, data_020dd3d8, data_020dd388, data_020dd398, PlayerRecord_Player(record));
    if (Mail_Post(&letter) != 0) {
        PlayerRecord_SetFlag(record, ROOM_SCORE_MAIL_RECORD_MEMBER);
        func_02066688(&letter);
        return 1;
    }
    func_02066688(&letter);
    return 0;
}
CLEAN_AS(func_0205a2f0, RoomScoreMail_SendWelcome)

/* func_0205a41c: the next prize not sent yet (state flags 1, 2 and 11, in that order), when
 * `total` reaches it: 70000 message 0x18 with item 0x3854, 100000 message 0x19 with 0x3858,
 * 150000 message 0x1a with 0x385c. It goes to the first player of the town who has had the
 * first letter and whose mailbox is not full, posted or held at the post office; then its
 * flag is set. `room` is not used.
 * QUIRK: only the first prize not sent is looked at; a total that reaches a later one waits
 * for the next judgement. */
void RoomScoreMail_SendPrize(RoomScoreRoom *room, int total)
{
    (void) room;
    int message = -1;
    u32 flag = 1;
    u16 item = ROOM_SCORE_MAIL_NO_ITEM;

    if (StateBlock_TestFlag(data_021dc7a8, 1) == 0) {
        if (total >= 70000) {
            message = 0x18;
            flag = 1;
            item = 0x3854;
        }
    } else if (StateBlock_TestFlag(data_021dc7a8, 2) == 0) {
        if (total >= 100000) {
            message = 0x19;
            flag = 2;
            item = 0x3858;
        }
    } else if (StateBlock_TestFlag(data_021dc7a8, 11) == 0) {
        if (total >= 150000) {
            message = 0x1a;
            flag = 11;
            item = 0x385c;
        }
    }
    if (message == -1) {
        return;
    }

    for (int i = 0; i < ROOM_SCORE_MAIL_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record == NULL || PlayerRecord_HasPlayer(record) == 0 ||
            PlayerRecord_TestFlag(record, ROOM_SCORE_MAIL_RECORD_MEMBER) == 0 || Mail_IsMailboxFull(i) != 0) {
            continue;
        }
        MailLetter letter;
        func_02066694(&letter);
        u8 text = (u8) message;
        func_02066024(&letter, &text, data_020dd3d8, data_020dd38c, data_020dd394, PlayerRecord_Player(record));
        func_02065ed0(&letter, item, 1);
        if (Mail_Post(&letter) != 0 || Mail_HoldAtPostOffice(&letter, 0) != 0) {
            StateBlock_SetFlag(data_021dc7a8, flag);
            func_02066688(&letter);
            return;
        }
        func_02066688(&letter);
    }
}
CLEAN_AS(func_0205a41c, RoomScoreMail_SendPrize)

/* func_0205a554: the judgement, message `message`, with the total, the name of group `group`
 * and, for a theme below 4, its word of "st_furniture_letter" as its texts, posted to each
 * player of the town who has had the first letter (to every player while game variable 0x22
 * is set). 0 when the total could not be written. `room` is not used. */
int RoomScoreMail_SendJudgement(RoomScoreRoom *room, int message, int total, int group, int theme)
{
    (void) room;
    MessageText46 total_text;
    MessageText46_Construct(&total_text);
    if (NumberText_Format(&total_text, total, ROOM_SCORE_MAIL_TOTAL_DIGITS, 0, 0, 0) == 0) {
        MessageText46_Destruct(&total_text);
        return 0;
    }
    func_0203d7c4(ROOM_SCORE_MAIL_SLOT_TOTAL, &total_text);
    RoomScoreMailGroupName group_name;
    func_02062f64(&group_name, group);
    func_0203d7c4(ROOM_SCORE_MAIL_SLOT_GROUP, &group_name);
    if (theme < ROOM_SCORE_MAIL_THEMES) {
        RoomScoreMailLabel label;
        func_020a8228(&label);
        u8 word = (u8) theme;
        MessageReader_LoadDecoded(&label, &word, data_020dd3e8);
        func_0203d7c4(ROOM_SCORE_MAIL_SLOT_THEME, &label);
        func_020a8210(&label);
    }
    for (int i = 0; i < ROOM_SCORE_MAIL_PLAYERS; i++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7bc, i);
        if (record == NULL || PlayerRecord_HasPlayer(record) == 0) {
            continue;
        }
        if (*GameVariables_Slot(0, ROOM_SCORE_MAIL_VARIABLE_ALL) == 0 &&
            PlayerRecord_TestFlag(record, ROOM_SCORE_MAIL_RECORD_MEMBER) == 0) {
            continue;
        }
        MailLetter letter;
        func_02066694(&letter);
        u8 text = (u8) message;
        func_02066024(&letter, &text, data_020dd3d8, data_020dd390, data_020dd384, PlayerRecord_Player(record));
        Mail_Post(&letter);
        func_02066688(&letter);
    }
    func_02062f4c(&group_name);
    MessageText46_Destruct(&total_text);
    return 1;
}
CLEAN_AS(func_0205a554, RoomScoreMail_SendJudgement)
