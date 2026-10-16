/* Questions about a 16-bit message text, answered by walking it (class data_020e3e44, a walker
 * of message_cursor.h): its length, its character at an index, where a line starts and where a
 * tag of a given group and kind is. One query object serves the whole game (data_021f4548,
 * built at start-up); each question resets it, sets what to look for, walks the text and
 * reads the answer if the walk found it.
 *
 * The walker's virtual functions do the work: slot 2 when the text is set, 3 at its end, 4
 * for each character, 5 for each tag; slot 6 stops the walk once the answer is found. */
#ifndef CLEAN_MAIN_MESSAGE_QUERY_H
#define CLEAN_MAIN_MESSAGE_QUERY_H

#include "message_cursor.h"
#include "message_decoder.h"
#include "types.h"

/* What a query looks for. */
enum MessageQueryMode {
    MESSAGE_QUERY_TAG = 0,       /* the tag of a group and kind */
    MESSAGE_QUERY_CHARACTER = 1, /* the character at an index */
    MESSAGE_QUERY_UNUSED = 2,    /* nothing (no question uses it) */
    MESSAGE_QUERY_LENGTH = 3,    /* the number of characters */
    MESSAGE_QUERY_LINE = 4       /* the start of a line */
};

/* The query (0x5c bytes). */
typedef struct MessageQuery {
    MessageWalker base;
    s32 mode;       /* 0x24: enum MessageQueryMode */
    MessageTag tag; /* 0x28: the last tag met */
    u32 character;  /* 0x3c: the last character met */
    u32 want_group; /* 0x40: the tag looked for (-1 for none) */
    u32 want_kind;  /* 0x44 */
    s32 index;      /* 0x48: the index of the character looked for */
    s32 count;      /* 0x4c: the characters met */
    s32 line;       /* 0x50: the line looked for */
    s32 lines;      /* 0x54: the newlines met */
    u8 done;        /* 0x58: the answer is found */
    u8 unk_59[3];
} MessageQuery;

void MessageQuery_CheckTag(MessageQuery *query);
void MessageQuery_CountLine(MessageQuery *query);
void MessageQuery_CountCharacter(MessageQuery *query);
void MessageQuery_CountToIndex(MessageQuery *query);
void MessageQuery_Reset(MessageQuery *query);
int MessageQuery_WantsMore(const MessageQuery *query);
void MessageQuery_OnTag(MessageQuery *query, int position);
void MessageQuery_OnCharacter(MessageQuery *query, unsigned int character);
void MessageQuery_OnEnd(MessageQuery *query);
void MessageQuery_OnText(MessageQuery *query);
int MessageQuery_Line(int text, int line);
int MessageQuery_Length(int text);
int MessageQuery_CharacterFromEnd(const void *text, int index);
int MessageQuery_CharacterAt(int text, int index);
int MessageQuery_FindTag(int text, int group, int kind);
MessageQuery *MessageQuery_Delete(MessageQuery *query);
MessageQuery *MessageQuery_Destruct(MessageQuery *query);
MessageQuery *MessageQuery_Construct(MessageQuery *query);

#endif
