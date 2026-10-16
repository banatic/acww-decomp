/* The message reader's decoder (the reader's first member, class data_020e5278; message_reader.h):
 * a walker (message_cursor.h) that goes through a message of the open file and writes its text
 * into the reader's text buffer, character by character (MessageDecoder_PutCharacter), acting
 * on the tags it meets (func_020b517c picks the handler by the tag's group and kind):
 *
 * - 0/2, 0/3, 0/4: the first, second or third character of the nickname's source text (the
 *   text MessageReader_LoadNickname hands over, at the reader's 0x18f0); 0/5: its last two;
 * - 0/6, 0/9, 0/10: one of three fixed texts, walked in place of the tag;
 * - 4/15 to 4/25: one of the reader's parts, walked likewise;
 * - 0x0b/0: the text's attributes set from the tag; 0x0b/3: the next character written (from
 *   the message or the source text) is first turned into its other form (func_02050bdc_unk);
 * - 0xff/2: kept as it is, or with the request's first byte its bytes put in the text
 *   (MessageDecoder_CopyTag).
 *
 * The source text's characters are inserted only with the request's second byte (the
 * nicknames); the decoding fails when one of them is 0 or a full-width digit or Latin letter,
 * when the message's next character repeats the last one inserted, when the text is full, or
 * when a tag has no handler. */
#ifndef CLEAN_MAIN_MESSAGE_DECODER_H
#define CLEAN_MAIN_MESSAGE_DECODER_H

#include "message_cursor.h"
#include "message_reader.h"
#include "types.h"

/* The tag being handled (0x14 bytes, func_020a8764 reads it from the message). */
typedef struct MessageTag {
    u32 group;        /* 0x00 */
    u32 kind;         /* 0x04 */
    u32 size;         /* 0x08: the bytes of its parameters */
    const s8 *params; /* 0x0c: its parameters, after its 6-byte head */
    const s8 *start;  /* 0x10: the tag itself */
} MessageTag;

/* The text's attributes (the reader's at 0xaf0, 0x0c bytes, func_020a9b50 builds them). */
typedef struct MessageAttributes {
    const void *vtable; /* 0x00 */
    s32 unk_04;         /* 0x04: 0 to 2 from a 0x0b/0 tag, else -1 */
    u8 unk_08;          /* 0x08 */
    u8 unk_09;          /* 0x09 */
    u8 unk_0a[2];
} MessageAttributes;

/* The decoder (0x4c bytes). */
typedef struct MessageDecoder {
    MessageWalker base;
    MessageReader *reader; /* 0x24: the reader it writes into */
    MessageTag tag;        /* 0x28 */
    s32 character;         /* 0x3c: the character being put in the text */
    u32 length;            /* 0x40: the bytes of the reader's text written so far */
    u8 inserted;           /* 0x44: set when a character of the source text was inserted */
    u8 ok;                 /* 0x45: cleared when a step fails */
    u8 expand_tags;        /* 0x46: the request's first byte (MessageDecoder_CopyTag) */
    u8 nickname;           /* 0x47: the request's second byte: insert the source's characters */
    u8 convert_next;       /* 0x48: turn the next inserted character into its other form */
    u8 unk_49[3];
} MessageDecoder;

int MessageDecoder_DiffersFromSource(MessageDecoder *decoder);
int MessageDecoder_StartsWell(MessageDecoder *decoder);
int MessageDecoder_DiffersFromLast(MessageDecoder *decoder, int character);
int MessageDecoder_CanInsert(int character);
void MessageDecoder_ConvertNext(MessageDecoder *decoder);
void MessageDecoder_SetAttributes(MessageDecoder *decoder);
void MessageDecoder_InsertPart(MessageDecoder *decoder);
void MessageDecoder_CopyTag(MessageDecoder *decoder);
void MessageDecoder_InsertText10(MessageDecoder *decoder);
void MessageDecoder_InsertText9(MessageDecoder *decoder);
void MessageDecoder_InsertText6(MessageDecoder *decoder);
void MessageDecoder_InsertSourceEnd(MessageDecoder *decoder);
void MessageDecoder_InsertSourceThird(MessageDecoder *decoder);
void MessageDecoder_InsertSourceSecond(MessageDecoder *decoder);
void MessageDecoder_InsertSourceFirst(MessageDecoder *decoder);
void MessageDecoder_ExpandTag(MessageDecoder *decoder);
void MessageDecoder_KeepTag(MessageDecoder *decoder);
void MessageDecoder_PutCharacter(MessageDecoder *decoder);
u8 MessageDecoder_WantsMore(MessageDecoder *decoder);

#endif
