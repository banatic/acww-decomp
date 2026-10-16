/* The town's mail: the players' mailboxes, the letters waiting at the post office and their
 * delivery.
 *
 * A letter is 0x100 bytes. Its byte 0xfa holds its state in the low six bits (0: no letter, so
 * an empty place in a mailbox) and its halfword 0xfc the item it carries (0xfff1: none). Its
 * addressee starts at 4: a player of a town (func_02065f70) or a villager (func_02065f64).
 *
 * Each of the four players has a mailbox of ten letters (data_021ef8ec, MailBox). The post
 * office keeps ten more (data_021f20fc, MailPostOffice): letters that found no room, or came from
 * another console. They are handed out at the delivery hours, 9:00 and 17:00 (Mail_DeliverDue):
 * to a player of this town into the mailbox, to a villager (Mail_GiveToVillager); a letter for
 * no one here is thrown away. Mail_DeliverDue also posts the letter a player's record keeps for
 * a date, once that date has come.
 *
 * MailTask is the process (vtable data_020e30b8) that runs Mail_DeliverDue once, on its first
 * frame. */
#ifndef CLEAN_MAIN_MAIL_H
#define CLEAN_MAIN_MAIL_H

#include "autoload_2/process.h"
#include "types.h"

#define MAIL_LETTER_SIZE 0x100
#define MAILBOX_LETTERS 10
#define MAIL_PLAYERS 4

/* What Mail_FindPlayerAddressee and Mail_FindVillagerAddressee give when there is no one. */
#define MAIL_NOT_THAT_KIND (-1) /* the letter is not addressed to that kind of addressee */
#define MAIL_NOT_HERE (-2)      /* it is, but not to one of this town */

typedef struct MailLetter {
    u8 bytes[MAIL_LETTER_SIZE];
} MailLetter;

/* A player's mailbox (0xa04 bytes each, at data_021ef8ec). */
typedef struct MailBox {
    MailLetter letters[MAILBOX_LETTERS];
    u8 unk_a00[4];
} MailBox;

/* A date with an hour, in the order the records keep it. */
typedef struct MailTime {
    u8 day;
    u8 month;
    u8 year;
    u8 hour;
} MailTime;

/* The letters waiting at the post office (data_021f20fc). */
typedef struct MailPostOffice {
    MailLetter letters[MAILBOX_LETTERS];
    MailTime last_check; /* 0xa00: when Mail_DeliverDue last looked, to the hour */
    u16 flags;           /* 0xa04: MAIL_CHECKED */
} MailPostOffice;

/* MailPostOffice.flags: last_check holds a time. */
#define MAIL_CHECKED 1

/* The delivery process: a process with flags (MAIL_TASK_PENDING). */
typedef struct MailTask {
    Process base;
    u16 flags; /* 0x50 */
} MailTask;

/* MailTask.flags: the delivery has still to run. */
#define MAIL_TASK_PENDING 1

void Mail_DeliverWaiting(void);
void Mail_DeliverDue(void);
int Mail_PostOfficeHasRoom(void);
int Mail_HasDatedLetter(void *player);
void Mail_DoNothing(void);
int Mail_CountLetters(MailLetter *letters, int count);
int Mail_Compact(MailLetter *letters, int count);
int Mail_FindVillagerAddressee(MailLetter *letter);
int Mail_FindPlayerAddressee(MailLetter *letter);
int Mail_HasAddressee(MailLetter *letter);
int Mail_HoldAtPostOffice(MailLetter *letter, int advance);
void Mail_GiveToVillager(MailLetter *letter);
int Mail_Post(MailLetter *letter);
int Mail_PutInMailbox(MailLetter *letter, int player, int advance);
int Mail_IsMailboxFull(int player);
int Mail_DeliverHeld(void);

MailTask *MailTask_Destruct(MailTask *task);
MailTask *MailTask_DestructFree(MailTask *task);
void MailTask_ClearFlags(MailTask *task, u16 flags);
void MailTask_SetFlags(MailTask *task, u32 flags);
int MailTask_TestFlags(MailTask *task, u32 flags);
void MailTask_Deliver(MailTask *task);
int MailTask_Delete(void);
int MailTask_Draw(void);
int MailTask_Execute(MailTask *task);
int MailTask_Create(MailTask *task);
MailTask *MailTask_New(void);

#endif
