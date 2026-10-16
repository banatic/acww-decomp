/* The three 8-bit texts (text_base.h) a letter of "/script/KOR/mail" is loaded into, one per
 * part (MailText_LoadMail, mail_text.h): the "super" line (22 characters, vtable data_020df240,
 * 0x28 bytes), the "msg" body (130 characters, vtable data_020df210) and the "ps" (34
 * characters, vtable data_020df228, 0x34 bytes). Their characters start at 0x12. A global
 * object of each is built at start-up (__sinit_020c5b40), and a villager's letter is written
 * from three on the stack (VillagerTalk_ShowLetter). */
#ifndef CLEAN_MAIN_MAIL_PART_TEXTS_H
#define CLEAN_MAIN_MAIL_PART_TEXTS_H

#include "text_label.h"
#include "types.h"

#define MAIL_SUPER_TEXT_CAPACITY 22
#define MAIL_MSG_TEXT_CAPACITY 130
#define MAIL_PS_TEXT_CAPACITY 34

typedef struct MailSuperText {
    const TextVtable *vtable; /* 0x00: data_020df240 */
    u32 length;               /* 0x04: the text base's */
    u8 attributes[0x0a];      /* 0x08: the text base's */
    char text[MAIL_SUPER_TEXT_CAPACITY];
} MailSuperText;

typedef struct MailMsgText {
    const TextVtable *vtable; /* 0x00: data_020df210 */
    u32 length;               /* 0x04: the text base's */
    u8 attributes[0x0a];      /* 0x08: the text base's */
    char text[MAIL_MSG_TEXT_CAPACITY];
} MailMsgText;

typedef struct MailPsText {
    const TextVtable *vtable; /* 0x00: data_020df228 */
    u32 length;               /* 0x04: the text base's */
    u8 attributes[0x0a];      /* 0x08: the text base's */
    char text[MAIL_PS_TEXT_CAPACITY];
} MailPsText;

int MailPsText_Buffer(int text);
int MailPsText_Capacity(void);
MailPsText *MailPsText_Delete(MailPsText *text);
MailPsText *MailPsText_Destruct(MailPsText *text);
MailPsText *MailPsText_Construct(MailPsText *text);

int MailMsgText_Buffer(int text);
int MailMsgText_Capacity(void);
MailMsgText *MailMsgText_Delete(MailMsgText *text);
MailMsgText *MailMsgText_Destruct(MailMsgText *text);
MailMsgText *MailMsgText_Construct(MailMsgText *text);

int MailSuperText_Buffer(int text);
int MailSuperText_Capacity(void);
MailSuperText *MailSuperText_Delete(MailSuperText *text);
MailSuperText *MailSuperText_Destruct(MailSuperText *text);
MailSuperText *MailSuperText_Construct(MailSuperText *text);

#endif
