/* Main's message reader (data_021f4dac, built by a static constructor and destroyed at exit):
 * it opens the message file ("<folder>/<name>.bmg") a request names, finds the request's
 * message in it and decodes the message's text into its buffer, which then goes to the
 * request's text when it has one.
 *
 * Two uses are here:
 *
 * - the nicknames: message n of "st_nickn" read into a text (MessageReader_LoadNickname);
 * - the forbidden words, the lines of message 0 of "st_taboo": a text is run through the
 *   reader's cursor, which looks at each place for a line that matches there (character by
 *   character, a character also matching the one func_02050bdc_unk turns it into) and moves
 *   on by the match or by one character (MessageReader_FilterTaboo).
 *
 * A request is a message receiver (the class of data_020e3d4c: a name of up to 25 characters
 * at 4, a message number at 0x1e) of class data_020e5200, whose folder is one of
 * "/script/KOR/string" and "/script/KOR/2d". */
#ifndef CLEAN_MAIN_MESSAGE_READER_H
#define CLEAN_MAIN_MESSAGE_READER_H

#include "types.h"

#define MESSAGE_READER_TEXT_SIZE 0xa00
#define MESSAGE_READER_PARTS 11
#define MESSAGE_READER_ITEMS 16

/* What to read (0x2c bytes, class data_020e5200). */
typedef struct MessageRequest {
    const void *vtable; /* 0x00: slot 3 gives the folder (MessageRequest_Folder) */
    char name[26];      /* 0x04: the file's name */
    u8 message;         /* 0x1e: the message's number in it */
    u8 unk_1f;
    s32 folder;  /* 0x20: 0 for "/script/KOR/string", 1 for "/script/KOR/2d" */
    void *text;  /* 0x24: the text the message goes to, or NULL */
    u8 decode_a; /* 0x28: handed to the decoder (func_020b5350) */
    u8 decode_b; /* 0x29: likewise */
    u8 unk_2a[2];
} MessageRequest;

/* The reader (0x1b64 bytes). */
typedef struct MessageReader {
    u8 decoder[0x4c];                     /* 0x0000: func_020b5418 builds it, for the reader */
    u8 file[0xaf0 - 0x4c];                /* 0x004c: the open message file */
    u8 attributes[0x0c];                  /* 0x0af0: the decoded text's, copied to the text's at 8 */
    char text[MESSAGE_READER_TEXT_SIZE];  /* 0x0afc: the decoded text, line by line */
    u8 parts[MESSAGE_READER_PARTS][0x5c]; /* 0x14fc */
    u32 unk_18f0;                         /* 0x18f0 */
    u8 cursor[0x34];                      /* 0x18f4: walks the text being filtered */
    u8 cursor_done;                       /* 0x1928: set when the cursor reached the end */
    u8 cursor_rest[0x1934 - 0x1929];      /* 0x1929 */
    u8 line_walker[0x24];                 /* 0x1934: walks a line of `text` */
    const char *line;                     /* 0x1958: the line being matched */
    s32 line_want;                        /* 0x195c: 1 while the walker is to hand a character */
    s32 line_character;                   /* 0x1960: the character it handed, 0 for none */
    u8 items[MESSAGE_READER_ITEMS][0x20]; /* 0x1964 */
} MessageReader;

int MessageRequest_Folder(MessageRequest *request);
MessageRequest *MessageRequest_Delete(MessageRequest *request);
MessageRequest *MessageRequest_Destruct(MessageRequest *request);
MessageRequest *MessageRequest_Construct(MessageRequest *request);
MessageReader *MessageReader_Destruct(MessageReader *reader);
MessageReader *MessageReader_Construct(MessageReader *reader);
int MessageReader_SameCharacter(int character, int wanted);
int MessageReader_MatchLine(MessageReader *reader);
int MessageReader_FilterText(MessageReader *reader);
void *MessageReader_StartTabooFilter(MessageReader *reader, void *text);
int MessageReader_Load(MessageReader *reader, MessageRequest *request);
void MessageReader_Clear(MessageReader *reader);
int MessageReader_FilterTaboo(void *text);
int MessageReader_LoadNickname(void *text, void *context, unsigned char *message);

/* Loading a message by group: a general message, into a part of the reader, from the menu
 * files, decoded, or plain. */
void MessageReader_LoadGeneral(void *text, int index, int decoded);
void *MessageReader_SetPart(int index, int source);
int MessageReader_LoadMenuMessage(void *text, unsigned char *message, const char *name);
void *MessageReader_LoadDecoded(void *text, unsigned char *message, const char *name);
int MessageReader_LoadMessage(void *text, unsigned char *message, const char *name);

#endif
