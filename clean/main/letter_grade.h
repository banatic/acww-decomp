/* How a villager grades a letter a player sent (villager_mail.h): by the words of its body and
 * how many of them begin like the keywords of the message file "st_mailcheck".
 *
 * When the text process starts (TextDraw_ProcessCreate) the keywords are read from the file's
 * 45 messages, each line of a message giving one of up to three characters (LetterGrade_LoadKeywords);
 * up to 1000 are kept at data_021ce3f4, three characters each, with their count at
 * data_021ce2f4. Grading a letter (LetterGrade_Grade) counts the words of its 64-character body
 * (runs of characters other than the separators of data_020ccf5c) and the words that match a
 * keyword, each keyword counting for at most two words (a 2-bit use count per keyword at
 * data_021ce2f8).
 *
 * The keywords' messages are read through an 8-bit text of 2562 characters (vtable
 * data_020df1d0, LetterGradeMessage) and turned into a wide text of 1280 characters (vtable
 * data_020df1e8, LetterGradeWide). */
#ifndef CLEAN_MAIN_LETTER_GRADE_H
#define CLEAN_MAIN_LETTER_GRADE_H

#include "mail.h"
#include "text_base.h"
#include "types.h"

/* What LetterGrade_Grade makes of a letter (the VILLAGER_MAIL_GRADE_* of villager_mail.h). */
#define LETTER_GRADE_NONE 0 /* fewer than two words */
#define LETTER_GRADE_BAD 1  /* two words or more, but too few keywords */
#define LETTER_GRADE_GOOD 2 /* three words or more, at least a quarter of them keywords */

#define LETTER_GRADE_MESSAGE_CAPACITY 2562 /* 8-bit characters */
#define LETTER_GRADE_WIDE_CAPACITY 1280    /* 16-bit characters */

typedef struct LetterGradeMessage {
    const TextVtable *vtable; /* 0x00: data_020df1d0 */
    u32 length;               /* 0x04: the text base's */
    u8 attributes[0x0a];      /* 0x08: the text base's */
    char text[LETTER_GRADE_MESSAGE_CAPACITY];
} LetterGradeMessage;

typedef struct LetterGradeWide {
    const TextVtable *vtable; /* 0x00: data_020df1e8 */
    u8 attributes[0x0a];      /* 0x04: the wide text base's */
    u16 text[LETTER_GRADE_WIDE_CAPACITY];
    u16 unk_a0e[3];
} LetterGradeWide;

int LetterGrade_MatchesKeyword(unsigned short *word, int left, int keyword);
int LetterGrade_UseKeyword(unsigned short *word, int left);
int LetterGrade_IsSeparator(unsigned short character);
int LetterGrade_BodyLength(Letter *letter);
int LetterGrade_Grade(Letter *letter);
void LetterGrade_LoadKeywords(void);
int LetterGrade_LoadMessage(int text, int name, char message);

int LetterGradeWide_Buffer(int text);
int LetterGradeWide_Capacity(void);
LetterGradeWide *LetterGradeWide_Delete(LetterGradeWide *text);
LetterGradeWide *LetterGradeWide_Destruct(LetterGradeWide *text);
LetterGradeWide *LetterGradeWide_Construct(LetterGradeWide *text);

int LetterGradeMessage_Buffer(int text);
int LetterGradeMessage_Capacity(void);
LetterGradeMessage *LetterGradeMessage_Delete(LetterGradeMessage *text);
LetterGradeMessage *LetterGradeMessage_Destruct(LetterGradeMessage *text);
LetterGradeMessage *LetterGradeMessage_Construct(LetterGradeMessage *text);

#endif
