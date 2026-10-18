/* The message reader's decoder: its checks and its tag handlers (message_decoder.h). */
#include "message_decoder.h"

#include <string.h>

#include "clean.h"
#include "message_query.h"
#include "message_tag.h"
#include "message_walker.h"
#include "text_codes.h"
#include "text_walker.h"

static_assert(sizeof(MessageTag) == 0x14, "tag");
static_assert(offsetof(MessageAttributes, unk_04) == 0x04, "attributes 4");
static_assert(offsetof(MessageAttributes, unk_09) == 0x09, "attributes 9");
static_assert(sizeof(MessageAttributes) == 0x0c, "attributes");
static_assert(offsetof(MessageDecoder, reader) == 0x24, "reader");
static_assert(offsetof(MessageDecoder, tag) == 0x28, "tag");
static_assert(offsetof(MessageDecoder, character) == 0x3c, "character");
static_assert(offsetof(MessageDecoder, length) == 0x40, "length");
static_assert(offsetof(MessageDecoder, inserted) == 0x44, "inserted");
static_assert(offsetof(MessageDecoder, convert_next) == 0x48, "convert next");
static_assert(sizeof(MessageDecoder) == 0x4c, "decoder");

/* The characters a decoded text may not start with. */
#define MESSAGE_DECODER_BAD_STARTS 15
/* The bytes of a tag's head, before its parameters. */
#define MESSAGE_DECODER_TAG_HEAD 6
/* The tags 4/15 to 4/25 name the reader's parts 0 to 10. */
#define MESSAGE_DECODER_FIRST_PART_KIND 15
/* The value of the attributes' 0x04 from a 0x0b/0 tag whose first parameter is too large. */
#define MESSAGE_DECODER_ATTRIBUTE_COUNT 3

/* The full-width digits and Latin letters, which a nickname may not take from its source. */
#define MESSAGE_DECODER_WIDE_DIGIT_0 0xff10
#define MESSAGE_DECODER_WIDE_DIGIT_9 0xff19
#define MESSAGE_DECODER_WIDE_UPPER_A 0xff21
#define MESSAGE_DECODER_WIDE_UPPER_Z 0xff3a
#define MESSAGE_DECODER_WIDE_LOWER_A 0xff41
#define MESSAGE_DECODER_WIDE_LOWER_Z 0xff5a

extern const s32 data_020e5294[MESSAGE_DECODER_BAD_STARTS];

/* The other form of a character (itself when it has none). */
extern int func_02050bdc_unk(int character);

typedef int MessageDecoderCharactersFunction(const void *object);

/* The characters of a text object, through its vtable (slot 3), as an address. */
static int message_decoder_characters(const void *object)
{
    const u32 *vtable = *(const u32 *const *) object;
    MessageDecoderCharactersFunction *characters = (MessageDecoderCharactersFunction *) (uintptr_t) vtable[3];
    return characters(object);
}

/* The characters of the nickname's source text. */
static int message_decoder_source(const MessageDecoder *decoder)
{
    return message_decoder_characters((const void *) (uintptr_t) decoder->reader->unk_18f0);
}

/* The bytes of the reader's text, `length` on. */
static s8 *message_decoder_text_at(const MessageDecoder *decoder, u32 length)
{
    return (s8 *) decoder->reader->text + length;
}

/* func_020b4cd8: whether the decoded text differs from the nickname's source text (compared
 * as bytes up to the first 0 byte, by strcmp). */
int MessageDecoder_DiffersFromSource(MessageDecoder *decoder)
{
    const char *source = (const char *) (uintptr_t) message_decoder_source(decoder);
    return strcmp(source, decoder->reader->text) != 0;
}
CLEAN_AS(func_020b4cd8, MessageDecoder_DiffersFromSource)

/* func_020b4d0c: whether the decoded text's first character is none of data_020e5294's. */
int MessageDecoder_StartsWell(MessageDecoder *decoder)
{
    int first = MessageQuery_CharacterAt((int) (uintptr_t) decoder->reader->text, 0);

    for (int i = 0; i < MESSAGE_DECODER_BAD_STARTS; i++) {
        if (data_020e5294[i] == first) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020b4d0c, MessageDecoder_StartsWell)

/* func_020b4d60: whether `character` differs from the last character put in the text. */
int MessageDecoder_DiffersFromLast(MessageDecoder *decoder, int character)
{
    return decoder->character != character;
}
CLEAN_AS(func_020b4d60, MessageDecoder_DiffersFromLast)

/* func_020b4d70: whether a character of the source text may go into a nickname: not 0 and
 * not a full-width digit or Latin letter. */
int MessageDecoder_CanInsert(int character)
{
    if (character == 0) {
        return 0;
    }
    if (character >= MESSAGE_DECODER_WIDE_DIGIT_0 && character <= MESSAGE_DECODER_WIDE_DIGIT_9) {
        return 0;
    }
    if (character >= MESSAGE_DECODER_WIDE_UPPER_A && character <= MESSAGE_DECODER_WIDE_UPPER_Z) {
        return 0;
    }
    if (character >= MESSAGE_DECODER_WIDE_LOWER_A && character <= MESSAGE_DECODER_WIDE_LOWER_Z) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_020b4d70, MessageDecoder_CanInsert)

/* func_020b4dc0 (tag 0x0b/3): the next character written is turned into its other form. */
void MessageDecoder_ConvertNext(MessageDecoder *decoder)
{
    decoder->convert_next = 1;
}
CLEAN_AS(func_020b4dc0, MessageDecoder_ConvertNext)

/* func_020b4dc8 (tag 0x0b/0): the text's attributes set from the tag's three first bytes; a
 * first byte of 3 or more gives -1. */
void MessageDecoder_SetAttributes(MessageDecoder *decoder)
{
    u8 bytes[3];

    MessageTag_ReadThreeBytes(&decoder->tag, &bytes[0], &bytes[1], &bytes[2]);
    MessageAttributes *attributes = (MessageAttributes *) (void *) decoder->reader->attributes;
    attributes->unk_04 = bytes[0] < MESSAGE_DECODER_ATTRIBUTE_COUNT ? (s32) bytes[0] : -1;
    attributes->unk_08 = bytes[1];
    attributes->unk_09 = bytes[2];
}
CLEAN_AS(func_020b4dc8, MessageDecoder_SetAttributes)

/* func_020b4e08 (tags 4/15 to 4/25): the reader's part the tag names walked in its place. */
void MessageDecoder_InsertPart(MessageDecoder *decoder)
{
    int part = MessageTag_PartIndex(&decoder->tag);
    MessageWalker_Enter((MessageWalker *) decoder, message_decoder_characters(decoder->reader->parts[part]));
}
CLEAN_AS(func_020b4e08, MessageDecoder_InsertPart)

/* func_020b4e38 (tag 0xff/2): with the request's first byte its parameters go into the text
 * (MessageDecoder_ExpandTag), else the tag is kept as it is (MessageDecoder_KeepTag). */
void MessageDecoder_CopyTag(MessageDecoder *decoder)
{
    if (decoder->expand_tags != 0) {
        MessageDecoder_ExpandTag(decoder);
    } else {
        MessageDecoder_KeepTag(decoder);
    }
}
CLEAN_AS(func_020b4e38, MessageDecoder_CopyTag)

/* func_020b4e58 (tag 0/10): the fixed text of func_02050c10 walked in the tag's place. */
void MessageDecoder_InsertText10(MessageDecoder *decoder)
{
    MessageWalker_Enter((MessageWalker *) decoder, TextCodes_RightParen());
}
CLEAN_AS(func_020b4e58, MessageDecoder_InsertText10)

/* func_020b4e70 (tag 0/9): the fixed text of func_02050c18 walked in the tag's place. */
void MessageDecoder_InsertText9(MessageDecoder *decoder)
{
    MessageWalker_Enter((MessageWalker *) decoder, TextCodes_LeftParen());
}
CLEAN_AS(func_020b4e70, MessageDecoder_InsertText9)

/* func_020b4e88 (tag 0/6): the fixed text of func_02050c30 walked in the tag's place. */
void MessageDecoder_InsertText6(MessageDecoder *decoder)
{
    MessageWalker_Enter((MessageWalker *) decoder, TextCodes_Ampersand());
}
CLEAN_AS(func_020b4e88, MessageDecoder_InsertText6)

/* `character` put in the text when it may be (and then the decoder notes an insertion), else
 * the decoding fails. */
static void message_decoder_insert(MessageDecoder *decoder, int character)
{
    if (MessageDecoder_CanInsert(character)) {
        decoder->character = character;
        MessageDecoder_PutCharacter(decoder);
        decoder->inserted = 1;
    } else {
        decoder->ok = 0;
    }
}

/* Character `index` of the nickname's source text, turned into its other form when asked. */
static void message_decoder_insert_source(MessageDecoder *decoder, int index)
{
    if (decoder->nickname == 0) {
        return;
    }
    int character = MessageQuery_CharacterAt(message_decoder_source(decoder), index);
    if (decoder->convert_next != 0) {
        character = func_02050bdc_unk(character);
        decoder->convert_next = 0;
    }
    message_decoder_insert(decoder, character);
}

/* func_020b4ea0 (tag 0/5): the last two characters of the nickname's source text, in their
 * order, when the request asks for the source's characters; the decoding fails when either
 * may not be inserted (the second-last is not looked at when the last may not). QUIRK: the
 * other form is applied to the last character only: the ROM tests the flag again for the
 * second-last, after clearing it. */
void MessageDecoder_InsertSourceEnd(MessageDecoder *decoder)
{
    if (decoder->nickname == 0) {
        return;
    }
    int source = message_decoder_source(decoder);
    int last = MessageQuery_CharacterFromEnd((const void *) (uintptr_t) source, 0);
    int before_last = MessageQuery_CharacterFromEnd((const void *) (uintptr_t) source, 1);
    if (decoder->convert_next != 0) {
        last = func_02050bdc_unk(last);
        decoder->convert_next = 0;
    }
    if (MessageDecoder_CanInsert(last) && MessageDecoder_CanInsert(before_last)) {
        decoder->character = before_last;
        MessageDecoder_PutCharacter(decoder);
        decoder->character = last;
        MessageDecoder_PutCharacter(decoder);
        decoder->inserted = 1;
    } else {
        decoder->ok = 0;
    }
}
CLEAN_AS(func_020b4ea0, MessageDecoder_InsertSourceEnd)

/* func_020b4f3c (tag 0/4): the third character of the nickname's source text. */
void MessageDecoder_InsertSourceThird(MessageDecoder *decoder)
{
    message_decoder_insert_source(decoder, 2);
}
CLEAN_AS(func_020b4f3c, MessageDecoder_InsertSourceThird)

/* func_020b4fa4 (tag 0/3): the second character of the nickname's source text. */
void MessageDecoder_InsertSourceSecond(MessageDecoder *decoder)
{
    message_decoder_insert_source(decoder, 1);
}
CLEAN_AS(func_020b4fa4, MessageDecoder_InsertSourceSecond)

/* func_020b500c (tag 0/2): the first character of the nickname's source text. */
void MessageDecoder_InsertSourceFirst(MessageDecoder *decoder)
{
    message_decoder_insert_source(decoder, 0);
}
CLEAN_AS(func_020b500c, MessageDecoder_InsertSourceFirst)

/* func_020b5074: the tag's parameters but the first put in the text when they fit (with room
 * to spare), else the decoding fails; either way the walk skips as many characters of the
 * message as the first parameter says. */
void MessageDecoder_ExpandTag(MessageDecoder *decoder)
{
    u32 skip;
    s32 end;
    const s8 *bytes;

    MessageTag_SplitParams(&decoder->tag, &skip, &end, &bytes);
    u32 count = decoder->tag.size - 1;
    int fits = MESSAGE_READER_TEXT_SIZE - decoder->length > count;
    MessageWalker_Skip((MessageWalker *) decoder, skip << 1);
    if (fits) {
        s8 *text = message_decoder_text_at(decoder, decoder->length);
        for (u32 i = 0; i < count; i++) {
            text[i] = bytes[i];
        }
        decoder->length += count;
    } else {
        decoder->ok = 0;
    }
}
CLEAN_AS(func_020b5074, MessageDecoder_ExpandTag)

/* func_020b50e0: the whole tag, head and parameters, copied into the text when it fits (with
 * room to spare), else the decoding fails. */
void MessageDecoder_KeepTag(MessageDecoder *decoder)
{
    const s8 *tag = decoder->tag.start;
    u32 count = decoder->tag.size + MESSAGE_DECODER_TAG_HEAD;

    if (MESSAGE_READER_TEXT_SIZE - decoder->length > count) {
        s8 *text = message_decoder_text_at(decoder, decoder->length);
        for (u32 i = 0; i < count; i++) {
            text[i] = tag[i];
        }
        decoder->length += count;
    } else {
        decoder->ok = 0;
    }
}
CLEAN_AS(func_020b50e0, MessageDecoder_KeepTag)

/* func_020b512c: the decoder's character put in the text as two bytes, low first, when more
 * than two bytes are left, else the decoding fails. */
void MessageDecoder_PutCharacter(MessageDecoder *decoder)
{
    u32 length = decoder->length;

    if (MESSAGE_READER_TEXT_SIZE - length > 2) {
        s8 *text = message_decoder_text_at(decoder, length);
        text[0] = (s8) decoder->character;
        text[1] = (s8) (decoder->character >> 8);
        decoder->length = length + 2;
    } else {
        decoder->ok = 0;
    }
}
CLEAN_AS(func_020b512c, MessageDecoder_PutCharacter)

/* func_020b5174 (the decoder's slot 6): the walk goes on while nothing failed. */
u8 MessageDecoder_WantsMore(MessageDecoder *decoder)
{
    return decoder->ok;
}
CLEAN_AS(func_020b5174, MessageDecoder_WantsMore)

/* The decoder's class and the walkers' base class (message_cursor.h). */
extern const u8 data_020e5278[];
extern const u8 data_020e3e68[];

/* The deleting destructors' delete (autoload_2/heap.h). */
void Heap_OperatorDeleteB(void *block);

typedef void MessageDecoderHandler(MessageDecoder *decoder);
typedef int MessageDecoderBufferFunction(void *file);

/* The tags' groups and kinds that have a handler. */
#define MESSAGE_DECODER_GROUP_SOURCE 0x00
#define MESSAGE_DECODER_GROUP_PART 0x04
#define MESSAGE_DECODER_GROUP_FORM 0x0b
#define MESSAGE_DECODER_GROUP_RAW 0xff
/* Slot 2 of the message file's vtable gives its buffer (MessageFile_Buffer). */
#define MESSAGE_DECODER_FILE_BUFFER_SLOT 2

/* The handler of the tag just read, or NULL when it has none. The ROM picks it as a C++ member
 * pointer from the constants at data_020e5134-data_020e518c, which all name these functions
 * directly (no virtual call, no adjustment). The group 4 test is asked only for group 4. */
static MessageDecoderHandler *message_decoder_handler(MessageDecoder *decoder)
{
    u32 kind = decoder->tag.kind;

    switch (decoder->tag.group) {
        case MESSAGE_DECODER_GROUP_SOURCE:
            switch (kind) {
                case 2:
                    return MessageDecoder_InsertSourceFirst;
                case 3:
                    return MessageDecoder_InsertSourceSecond;
                case 4:
                    return MessageDecoder_InsertSourceThird;
                case 5:
                    return MessageDecoder_InsertSourceEnd;
                case 6:
                    return MessageDecoder_InsertText6;
                case 9:
                    return MessageDecoder_InsertText9;
                case 10:
                    return MessageDecoder_InsertText10;
                default:
                    return NULL;
            }
        case MESSAGE_DECODER_GROUP_RAW:
            return kind == 2 ? MessageDecoder_CopyTag : NULL;
        case MESSAGE_DECODER_GROUP_PART:
            return MessageTag_IsPart(&decoder->tag) != 0 ? MessageDecoder_InsertPart : NULL;
        case MESSAGE_DECODER_GROUP_FORM:
            if (kind == 0) {
                return MessageDecoder_SetAttributes;
            }
            return kind == 3 ? MessageDecoder_ConvertNext : NULL;
        default:
            return NULL;
    }
}

/* func_020b517c (the decoder's slot 5): the tag at `position` read and handled; a tag without
 * a handler makes the decoding fail. */
void MessageDecoder_OnTag(MessageDecoder *decoder, int position)
{
    MessageTag_Read(&decoder->tag, position);
    MessageDecoderHandler *handler = message_decoder_handler(decoder);
    if (handler != NULL) {
        handler(decoder);
    } else {
        decoder->ok = 0;
    }
}
CLEAN_AS(func_020b517c, MessageDecoder_OnTag)

/* func_020b52dc (slot 4): a character of the message. It is first turned into its other form
 * when a 0x0b/3 tag asked; right after a character of the source text was inserted (for a
 * nickname) it must differ from that one, else the decoding fails; then it goes into the text
 * while nothing failed. */
void MessageDecoder_OnCharacter(MessageDecoder *decoder, unsigned int character)
{
    if (decoder->convert_next != 0) {
        character = (unsigned int) func_02050bdc_unk((int) character);
        decoder->convert_next = 0;
    }
    if (decoder->nickname != 0 && decoder->inserted != 0) {
        if (MessageDecoder_DiffersFromLast(decoder, (int) character) == 0) {
            decoder->ok = 0;
        }
        decoder->inserted = 0;
    }
    if (decoder->ok != 0) {
        decoder->character = (s32) character;
        MessageDecoder_PutCharacter(decoder);
    }
}
CLEAN_AS(func_020b52dc, MessageDecoder_OnCharacter)

/* func_020b5348 (slot 3): nothing at the end. */
void MessageDecoder_OnEnd(void) {}
CLEAN_AS(func_020b5348, MessageDecoder_OnEnd)

/* func_020b534c (slot 2): nothing when a text is set. */
void MessageDecoder_OnText(void) {}
CLEAN_AS(func_020b534c, MessageDecoder_OnText)

/* The buffer of the reader's message file, through its vtable, as an address. */
static int message_decoder_file_buffer(MessageReader *reader)
{
    void *file = reader->file;
    const u32 *vtable = *(const u32 *const *) file;
    MessageDecoderBufferFunction *buffer =
        (MessageDecoderBufferFunction *) (uintptr_t) vtable[MESSAGE_DECODER_FILE_BUFFER_SLOT];
    return buffer(file);
}

/* func_020b5350: the message in the reader's file buffer decoded into the reader's text, with
 * the request's two bytes; whether it went well. For a nickname the text must also start
 * well and differ from its source text (the first failing check ends the checks). */
u8 MessageDecoder_Decode(MessageDecoder *decoder, u8 expand_tags, u8 nickname)
{
    decoder->ok = 1;
    decoder->length = 0;
    decoder->expand_tags = expand_tags;
    decoder->nickname = nickname;
    decoder->convert_next = 0;
    decoder->character = 0;
    MessageWalker_Reset((MessageWalker *) decoder);
    MessageWalker_Start((MessageWalker *) decoder, message_decoder_file_buffer(decoder->reader));
    TextWalker_Run((MessageWalker *) decoder, 0);
    if (decoder->ok != 0 && decoder->nickname != 0) {
        if (MessageDecoder_StartsWell(decoder) == 0 || MessageDecoder_DiffersFromSource(decoder) == 0) {
            decoder->ok = 0;
        }
    }
    return decoder->ok;
}
CLEAN_AS(func_020b5350, MessageDecoder_Decode)

/* func_020b53d0 (slot 1): the decoder destroyed (MessageDecoder_Destruct) and freed. */
MessageDecoder *MessageDecoder_Delete(MessageDecoder *decoder)
{
    decoder->base.vtable = data_020e5278;
    decoder->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(decoder);
    Heap_OperatorDeleteB(decoder);
    return decoder;
}
CLEAN_AS(func_020b53d0, MessageDecoder_Delete)

/* func_020b53f8 (slot 0): the destructor: its vtable, the base class's, then the walkers' base
 * destructor. */
MessageDecoder *MessageDecoder_Destruct(MessageDecoder *decoder)
{
    decoder->base.vtable = data_020e5278;
    decoder->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(decoder);
    return decoder;
}
CLEAN_AS(func_020b53f8, MessageDecoder_Destruct)

/* func_020b5418: the constructor, for `reader`: nothing written, nothing to insert, no
 * request bytes, and the decoding going well. */
MessageDecoder *MessageDecoder_Construct(MessageDecoder *decoder, MessageReader *reader)
{
    MessageWalker_Construct((MessageWalker *) decoder);
    decoder->base.vtable = data_020e3e68;
    decoder->base.vtable = data_020e5278;
    decoder->reader = reader;
    MessageTag_Construct(&decoder->tag);
    decoder->character = 0;
    decoder->length = 0;
    decoder->inserted = 0;
    decoder->ok = 1;
    decoder->expand_tags = 0;
    decoder->nickname = 0;
    decoder->convert_next = 0;
    return decoder;
}
CLEAN_AS(func_020b5418, MessageDecoder_Construct)
