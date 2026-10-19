/* How a villager grades a letter a player sent (letter_grade.h). */
#include "letter_grade.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "message_reader.h"
#include "text_string.h"

static_assert(offsetof(LetterGradeMessage, text) == 0x12, "message characters");
static_assert(sizeof(LetterGradeMessage) == 0xa14, "message");
static_assert(offsetof(LetterGradeWide, text) == 0x0e, "wide characters");
static_assert(sizeof(LetterGradeWide) == 0xa14, "wide");

/* The keywords: up to 1000 of three characters (a shorter one ends with 0), their count, and a
 * 2-bit use count per keyword, four to a byte from the low bits. */
#define LETTER_GRADE_KEYWORD_LENGTH 3
#define LETTER_GRADE_KEYWORDS 1000
#define LETTER_GRADE_USES_SIZE 0xfa
#define LETTER_GRADE_MAX_USES 2
extern u16 data_021ce3f4[LETTER_GRADE_KEYWORDS * LETTER_GRADE_KEYWORD_LENGTH];
extern s32 data_021ce2f4;
extern u8 data_021ce2f8[LETTER_GRADE_USES_SIZE];

/* The characters that separate words: the ideographic space, the newline, 0 and the full-width
 * "!", "?", "," and ".". */
#define LETTER_GRADE_SEPARATORS 7
extern const u16 data_020ccf5c[LETTER_GRADE_SEPARATORS];

/* The keywords' message file, "st_mailcheck", and its messages. */
extern const char data_020df1f8[];
#define LETTER_GRADE_KEYWORD_MESSAGES 45

/* The classes' vtables. */
extern const TextVtable data_020df1e8; /* LetterGradeWide */
extern const TextVtable data_020df1d0; /* LetterGradeMessage */

/* The letter's body's length in characters. */
#define LETTER_GRADE_BODY_LENGTH LETTER_BODY_CHARS

/* The characters that end a keyword shorter than three, or a word. */
#define LETTER_GRADE_IDEOGRAPHIC_SPACE 0x3000
#define LETTER_GRADE_SPACE 0x20

/* The characters before a 0, at most `max`. */
extern int func_02051c8c_unk(u16 *text, int max);

static u16 *letter_grade_body(Letter *letter)
{
    return letter->body;
}

/* Whether a keyword's character ends it: a space of either width, or 0. */
static int letter_grade_keyword_ends(u16 character)
{
    return character == LETTER_GRADE_IDEOGRAPHIC_SPACE || character == LETTER_GRADE_SPACE || character == 0;
}

/* func_0206d6a4: whether the word at `word` (`left` characters are left in the text) begins
 * with the keyword starting at `keyword` in the table (an index of its characters): their
 * characters agree up to the keyword's end, or up to a space in the word, or over all three. */
int LetterGrade_MatchesKeyword(unsigned short *word, int left, int keyword)
{
    const u16 *key = &data_021ce3f4[keyword];
    for (int i = 0; i < LETTER_GRADE_KEYWORD_LENGTH; i++) {
        if (i >= left || word[i] != key[i]) {
            return letter_grade_keyword_ends(key[i]);
        }
        if (word[i] == LETTER_GRADE_IDEOGRAPHIC_SPACE || word[i] == LETTER_GRADE_SPACE) {
            return 1;
        }
    }
    return 1;
}
CLEAN_AS(func_0206d6a4, LetterGrade_MatchesKeyword)

/* func_0206d714: whether the word at `word` counts as a keyword: the first keyword it matches
 * is used once more, unless it already was twice (then it does not count). */
int LetterGrade_UseKeyword(unsigned short *word, int left)
{
    for (s32 i = 0; i < data_021ce2f4; i++) {
        if (LetterGrade_MatchesKeyword(word, left, i * LETTER_GRADE_KEYWORD_LENGTH)) {
            u8 *uses = &data_021ce2f8[i >> 2];
            int shift = (i & 3) * 2;
            int mask = 3 << shift;
            int used = (*uses & mask) >> shift;
            if (used >= LETTER_GRADE_MAX_USES) {
                return 0;
            }
            *uses = (u8) ((*uses & ~mask) | ((used + 1) << shift));
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0206d714, LetterGrade_UseKeyword)

/* func_0206d780: whether the character separates words. */
int LetterGrade_IsSeparator(unsigned short character)
{
    for (int i = 0; i < LETTER_GRADE_SEPARATORS; i++) {
        if (character == data_020ccf5c[i]) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0206d780, LetterGrade_IsSeparator)

/* func_0206d7a0: the characters of the letter's body before its 0. */
int LetterGrade_BodyLength(Letter *letter)
{
    return func_02051c8c_unk(letter_grade_body(letter), LETTER_GRADE_BODY_LENGTH);
}
CLEAN_AS(func_0206d7a0, LetterGrade_BodyLength)

/* func_0206d7ac: the letter graded (LETTER_GRADE_*) by the words of its body (a copy of it, up
 * to its 0) and how many of them count as keywords; the keywords' use counts start again from
 * 0. */
int LetterGrade_Grade(Letter *letter)
{
    u16 body[LETTER_GRADE_BODY_LENGTH];
    TextString_CopyChars(letter_grade_body(letter), body, LETTER_GRADE_BODY_LENGTH);
    int words = 0;
    int keywords = 0;
    int length = func_02051c8c_unk(body, LETTER_GRADE_BODY_LENGTH);
    memset(data_021ce2f8, 0, LETTER_GRADE_USES_SIZE);

    int after_separator = 1;
    for (int i = 0; i < length; i++) {
        int separator = LetterGrade_IsSeparator(body[i]);
        if (after_separator == 1 && separator == 0) {
            words++;
            if (LetterGrade_UseKeyword(&body[i], length - i) != 0) {
                keywords++;
            }
        }
        after_separator = separator;
    }

    if (words >= 3 && (words + 3) >> 2 <= keywords) {
        return LETTER_GRADE_GOOD;
    }
    if (words >= 2) {
        return LETTER_GRADE_BAD;
    }
    return LETTER_GRADE_NONE;
}
CLEAN_AS(func_0206d7ac, LetterGrade_Grade)

/* func_0206d83c: the keywords read from the 45 messages of "st_mailcheck": each line of a
 * message is one (its first three characters, the rest filled with 0; an empty line none).
 * QUIRK: a line of more than three characters is not skipped: its fourth character is, and the
 * characters after it are read as the next keyword.
 * BUG: the count goes on past the 1000 keywords kept, and LetterGrade_UseKeyword then reads
 * keywords and use counts past their tables (BUGFIX: the count stops at 1000). */
void LetterGrade_LoadKeywords(void)
{
    LetterGradeMessage message;
    LetterGradeWide wide;

    LetterGradeMessage_Construct(&message);
    LetterGradeWide_Construct(&wide);
    s32 count = 0;
    u16 *out = data_021ce3f4;
    data_021ce2f4 = 0;
    for (int i = 0; i < LETTER_GRADE_KEYWORD_MESSAGES; i++) {
        TextBase_Clear(&message);
        LetterGrade_LoadMessage(&message, data_020df1f8, (char) i);
        TextBase_BytesToWide((WideTextBase *) (void *) &wide, (TextBase *) (void *) &message);
        u16 *line = wide.text;
        while (*line != 0) {
            int n = TextString_LineLength(line, LETTER_GRADE_KEYWORD_LENGTH, 0);
            if (n != 0) {
                if (count < LETTER_GRADE_KEYWORDS) {
                    int j;
                    for (j = 0; j < n; j++) {
                        out[j] = line[j];
                    }
                    for (; j < LETTER_GRADE_KEYWORD_LENGTH; j++) {
                        out[j] = 0;
                    }
                    out += LETTER_GRADE_KEYWORD_LENGTH;
                }
#ifdef BUGFIX
                if (count < LETTER_GRADE_KEYWORDS) {
                    count++;
                }
#else
                count++;
#endif
            }
            line += n + 1;
        }
        data_021ce2f4 = count;
    }
    LetterGradeWide_Destruct(&wide);
    LetterGradeMessage_Destruct(&message);
}
CLEAN_AS(func_0206d83c, LetterGrade_LoadKeywords)

/* ---- The wide text of 1280 characters */

/* func_0206d920 (vtable slot 3): the address of the characters. */
int LetterGradeWide_Buffer(int text)
{
    return text + (int) offsetof(LetterGradeWide, text);
}
CLEAN_AS(func_0206d920, LetterGradeWide_Buffer)

/* func_0206d924 (vtable slot 2): the capacity. */
int LetterGradeWide_Capacity(void)
{
    return LETTER_GRADE_WIDE_CAPACITY;
}
CLEAN_AS(func_0206d924, LetterGradeWide_Capacity)

/* func_0206d92c (vtable slot 1): destroyed (LetterGradeWide_Destruct) and freed. */
LetterGradeWide *LetterGradeWide_Delete(LetterGradeWide *text)
{
    text->vtable = &data_020df1e8;
    TextBase_WideDestruct(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0206d92c, LetterGradeWide_Delete)

/* func_0206d94c (vtable slot 0): the destructor. */
LetterGradeWide *LetterGradeWide_Destruct(LetterGradeWide *text)
{
    text->vtable = &data_020df1e8;
    TextBase_WideDestruct(text);
    return text;
}
CLEAN_AS(func_0206d94c, LetterGradeWide_Destruct)

/* func_0206d964: the constructor: the wide text base's, then its vtable. */
LetterGradeWide *LetterGradeWide_Construct(LetterGradeWide *text)
{
    TextBase_WideConstruct(text);
    text->vtable = &data_020df1e8;
    return text;
}
CLEAN_AS(func_0206d964, LetterGradeWide_Construct)

/* func_0206d97c: message `message` of the file `name` read into the 8-bit text `text`; whether
 * it was. */
int LetterGrade_LoadMessage(void *text, const char *name, char message)
{
    unsigned char index = (unsigned char) message;
    return MessageReader_LoadMessage(text, &index, name);
}
CLEAN_AS(func_0206d97c, LetterGrade_LoadMessage)

/* ---- The 8-bit text of 2562 characters */

/* func_0206d994 (vtable slot 3): the address of the characters. */
int LetterGradeMessage_Buffer(int text)
{
    return text + (int) offsetof(LetterGradeMessage, text);
}
CLEAN_AS(func_0206d994, LetterGradeMessage_Buffer)

/* func_0206d998 (vtable slot 2): the capacity. */
int LetterGradeMessage_Capacity(void)
{
    return LETTER_GRADE_MESSAGE_CAPACITY;
}
CLEAN_AS(func_0206d998, LetterGradeMessage_Capacity)

/* func_0206d9a0 (vtable slot 1): destroyed (LetterGradeMessage_Destruct) and freed. */
LetterGradeMessage *LetterGradeMessage_Delete(LetterGradeMessage *text)
{
    text->vtable = &data_020df1d0;
    TextBase_Destruct((TextBase *) (void *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_0206d9a0, LetterGradeMessage_Delete)

/* func_0206d9c0 (vtable slot 0): the destructor. */
LetterGradeMessage *LetterGradeMessage_Destruct(LetterGradeMessage *text)
{
    text->vtable = &data_020df1d0;
    TextBase_Destruct((TextBase *) (void *) text);
    return text;
}
CLEAN_AS(func_0206d9c0, LetterGradeMessage_Destruct)

/* func_0206d9d8: an empty text: the 8-bit text base's constructor, its vtable, then emptied. */
LetterGradeMessage *LetterGradeMessage_Construct(LetterGradeMessage *text)
{
    TextBase_Construct(text);
    text->vtable = &data_020df1d0;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_0206d9d8, LetterGradeMessage_Construct)
