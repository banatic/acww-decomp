/* The tags of the message texts (message_tag.h). */
#include "message_tag.h"

#include "clean.h"
#include "bmg_file.h"
#include "select_bmg.h"
#include "text_base.h"

/* The bytes of a tag's head, before its parameters. */
#define MESSAGE_TAG_HEAD 6
/* The tags 4/15 to 4/25 name the parts 0 to 10 of the text's owner. */
#define MESSAGE_TAG_FIRST_PART_KIND 15
#define MESSAGE_TAG_LAST_PART_KIND 25
/* The texts after a tag start this many bytes after it, and each takes this many bytes more
 * than its length. */
#define MESSAGE_TAG_TEXT_GAP 2
/* The bytes between two ready-made colour tags in data_020d1d70. */
#define MESSAGE_TAG_COLOUR_TAG_STRIDE 10
/* The bytes of a message part (message_receiver.h). */
#define MESSAGE_TAG_PART_SIZE 0x5c

static_assert(offsetof(MessageTag, size) == 0x08, "size");
static_assert(offsetof(MessageTag, params) == 0x0c, "params");
static_assert(offsetof(MessageTagText, length) == 0x04, "text length");

/* The ready-made 0xff/0 tags: the head 1a 00 08 ff 00 00, the parameters (the colour and 0),
 * then two bytes of padding. */
extern const u8 data_020d1d70[][MESSAGE_TAG_COLOUR_TAG_STRIDE];

static const u8 *message_tag_params(const MessageTag *tag)
{
    return (const u8 *) tag->params;
}

/* The address of the tag's end. */
static int message_tag_end(const MessageTag *tag)
{
    return (int) ((uintptr_t) tag->params + tag->size);
}

/* func_020a82f8: the address of the ready-made tag of `colour`. */
int MessageTag_ColourTag(int colour)
{
    return (int) (uintptr_t) data_020d1d70[colour];
}
CLEAN_AS(func_020a82f8, MessageTag_ColourTag)

/* func_020a8308: the colour of a 0xff/0 tag, its first byte.
 * QUIRK: colour 6 reads as 5 (the ready-made tag of 6 is that of 5 too). */
unsigned char MessageTag_Colour(MessageTag *tag)
{
    u8 colour;
    MessageTag_GetFirstByte(tag, &colour);
    if (colour == 6) {
        colour = 5;
    }
    return colour;
}
CLEAN_AS(func_020a8308, MessageTag_Colour)

/* func_020a8328: the first parameter byte, the address of the tag's end and that of the
 * parameters after the first. */
void MessageTag_SplitParams(MessageTag *tag, u32 *first, s32 *end, const s8 **rest)
{
    *first = (u32) MessageTag_ByteAt(message_tag_params(tag), 0);
    *end = message_tag_end(tag);
    *rest = tag->params + 1;
}
CLEAN_AS(func_020a8328, MessageTag_SplitParams)

/* func_020a8354: the part a 4/15-25 tag names. */
int MessageTag_PartIndex(MessageTag *tag)
{
    return (int) tag->kind - MESSAGE_TAG_FIRST_PART_KIND;
}
CLEAN_AS(func_020a8354, MessageTag_PartIndex)

/* func_020a835c: whether the kind is one of a part (15 to 25). */
int MessageTag_IsPart(MessageTag *tag)
{
    s32 kind = (s32) tag->kind;
    return kind >= MESSAGE_TAG_FIRST_PART_KIND && kind <= MESSAGE_TAG_LAST_PART_KIND;
}
CLEAN_AS(func_020a835c, MessageTag_IsPart)

/* The `count` texts after the tag set into `texts`; the bytes they take, the gap before them
 * included. */
static int message_tag_read_texts(const MessageTag *tag, MessageTagText *const *texts, int count)
{
    int position = message_tag_end(tag) + MESSAGE_TAG_TEXT_GAP;
    int total = MESSAGE_TAG_TEXT_GAP;
    for (int i = 0; i < count; i++) {
        TextBase_SetLine((TextBase *) texts[i], (const char *) (uintptr_t) position);
        int size = texts[i]->length + MESSAGE_TAG_TEXT_GAP;
        total += size;
        position += size;
    }
    return total;
}

/* func_020a8370: eight parameter bytes and two texts. */
int MessageTag_ReadEightBytesTwoTexts(MessageTag *tag, u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f, u8 *g, u8 *h,
                                      MessageTagText *text0, MessageTagText *text1)
{
    u8 bytes[8];
    MessageTag_ReadBytes(tag, bytes, 8);
    /* Written in this order (it decides the result when the outputs overlap). */
    *a = bytes[0];
    *c = bytes[2];
    *e = bytes[4];
    *g = bytes[6];
    *b = bytes[1];
    *d = bytes[3];
    *f = bytes[5];
    *h = bytes[7];
    MessageTagText *texts[2] = {text0, text1};
    return message_tag_read_texts(tag, texts, 2);
}
CLEAN_AS(func_020a8370, MessageTag_ReadEightBytesTwoTexts)

/* func_020a83ec: the bytes the texts after the tag take, read into a message part of its own:
 * two texts after a tag of kind 0 or 4, three after 1 or 5, four after 2 or 6, five after 3
 * or 7, none after the others. */
unsigned int MessageTag_TextsSize(MessageTag *tag)
{
    unsigned int kind = tag->kind;
    unsigned int count = kind < 8 ? (kind & 3) + 2 : 0;
    union {
        MessageTagText text;
        u8 bytes[MESSAGE_TAG_PART_SIZE];
    } part;

    SelectBmgText_Construct((SelectBmgText *) &part);
    unsigned int total = MESSAGE_TAG_TEXT_GAP;
    int position = message_tag_end(tag) + MESSAGE_TAG_TEXT_GAP;
    for (unsigned int i = 0; i < count; i++) {
        TextBase_SetLine((TextBase *) &part, (const char *) (uintptr_t) position);
        int size = part.text.length + MESSAGE_TAG_TEXT_GAP;
        total += (unsigned int) size;
        position += size;
    }
    SelectBmgText_Destruct((SelectBmgText *) &part);
    return total;
}
CLEAN_AS(func_020a83ec, MessageTag_TextsSize)

/* func_020a8460: five parameter bytes, each with a text. */
int MessageTag_ReadFiveTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1, u8 *byte2,
                             MessageTagText *text2, u8 *byte3, MessageTagText *text3, u8 *byte4, MessageTagText *text4)
{
    u8 bytes[5];
    MessageTag_ReadFiveBytes(tag, &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4]);
    *byte0 = bytes[0];
    *byte1 = bytes[1];
    *byte2 = bytes[2];
    *byte3 = bytes[3];
    *byte4 = bytes[4];
    MessageTagText *texts[5] = {text0, text1, text2, text3, text4};
    return message_tag_read_texts(tag, texts, 5);
}
CLEAN_AS(func_020a8460, MessageTag_ReadFiveTexts)

/* func_020a84e4: four parameter bytes, each with a text. */
int MessageTag_ReadFourTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1, u8 *byte2,
                             MessageTagText *text2, u8 *byte3, MessageTagText *text3)
{
    u8 bytes[4];
    MessageTag_ReadFourBytes(tag, &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
    *byte0 = bytes[0];
    *byte1 = bytes[1];
    *byte2 = bytes[2];
    *byte3 = bytes[3];
    MessageTagText *texts[4] = {text0, text1, text2, text3};
    return message_tag_read_texts(tag, texts, 4);
}
CLEAN_AS(func_020a84e4, MessageTag_ReadFourTexts)

/* func_020a855c: three parameter bytes, each with a text. */
int MessageTag_ReadThreeTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1, u8 *byte2,
                              MessageTagText *text2)
{
    u8 bytes[3];
    MessageTag_ReadThreeBytes(tag, &bytes[0], &bytes[1], &bytes[2]);
    *byte0 = bytes[0];
    *byte1 = bytes[1];
    *byte2 = bytes[2];
    MessageTagText *texts[3] = {text0, text1, text2};
    return message_tag_read_texts(tag, texts, 3);
}
CLEAN_AS(func_020a855c, MessageTag_ReadThreeTexts)

/* func_020a85c4: two parameter bytes, each with a text. */
unsigned int MessageTag_ReadTwoTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1)
{
    u8 bytes[2];
    MessageTag_ReadTwoBytes(tag, &bytes[0], &bytes[1]);
    *byte0 = bytes[0];
    *byte1 = bytes[1];
    MessageTagText *texts[2] = {text0, text1};
    return (unsigned int) message_tag_read_texts(tag, texts, 2);
}
CLEAN_AS(func_020a85c4, MessageTag_ReadTwoTexts)

/* func_020a861c: the first parameter halfword. */
void MessageTag_GetFirstHalf(MessageTag *tag, u16 *out)
{
    *out = (u16) MessageTag_HalfAt(message_tag_params(tag), 0);
}
CLEAN_AS(func_020a861c, MessageTag_GetFirstHalf)

/* func_020a8630: the first `count` parameter bytes. */
void MessageTag_ReadBytes(MessageTag *tag, u8 *out, int count)
{
    for (int i = 0; i < count; i++) {
        out[i] = (u8) MessageTag_ByteAt(message_tag_params(tag), i);
    }
}
CLEAN_AS(func_020a8630, MessageTag_ReadBytes)

/* func_020a8658: the first five parameter bytes. */
void MessageTag_ReadFiveBytes(MessageTag *tag, u8 *byte0, u8 *byte1, u8 *byte2, u8 *byte3, u8 *byte4)
{
    *byte0 = (u8) MessageTag_ByteAt(message_tag_params(tag), 0);
    *byte1 = (u8) MessageTag_ByteAt(message_tag_params(tag), 1);
    *byte2 = (u8) MessageTag_ByteAt(message_tag_params(tag), 2);
    *byte3 = (u8) MessageTag_ByteAt(message_tag_params(tag), 3);
    *byte4 = (u8) MessageTag_ByteAt(message_tag_params(tag), 4);
}
CLEAN_AS(func_020a8658, MessageTag_ReadFiveBytes)

/* func_020a86a4: the first four parameter bytes. */
void MessageTag_ReadFourBytes(MessageTag *tag, u8 *byte0, u8 *byte1, u8 *byte2, u8 *byte3)
{
    *byte0 = (u8) MessageTag_ByteAt(message_tag_params(tag), 0);
    *byte1 = (u8) MessageTag_ByteAt(message_tag_params(tag), 1);
    *byte2 = (u8) MessageTag_ByteAt(message_tag_params(tag), 2);
    *byte3 = (u8) MessageTag_ByteAt(message_tag_params(tag), 3);
}
CLEAN_AS(func_020a86a4, MessageTag_ReadFourBytes)

/* func_020a86e4: the first three parameter bytes; the third is also returned. */
int MessageTag_ReadThreeBytes(MessageTag *tag, u8 *byte0, u8 *byte1, u8 *byte2)
{
    *byte0 = (u8) MessageTag_ByteAt(message_tag_params(tag), 0);
    *byte1 = (u8) MessageTag_ByteAt(message_tag_params(tag), 1);
    int third = MessageTag_ByteAt(message_tag_params(tag), 2);
    *byte2 = (u8) third;
    return third;
}
CLEAN_AS(func_020a86e4, MessageTag_ReadThreeBytes)

/* func_020a8718: the first two parameter bytes. */
void MessageTag_ReadTwoBytes(MessageTag *tag, u8 *byte0, u8 *byte1)
{
    *byte0 = (u8) MessageTag_ByteAt(message_tag_params(tag), 0);
    *byte1 = (u8) MessageTag_ByteAt(message_tag_params(tag), 1);
}
CLEAN_AS(func_020a8718, MessageTag_ReadTwoBytes)

/* func_020a873c: the first parameter byte. */
void MessageTag_GetFirstByte(MessageTag *tag, u8 *out)
{
    *out = (u8) MessageTag_ByteAt(message_tag_params(tag), 0);
}
CLEAN_AS(func_020a873c, MessageTag_GetFirstByte)

/* func_020a8750: the destructor; nothing to do. */
void MessageTag_Destruct(void *tag)
{
    (void) tag;
}
CLEAN_AS(func_020a8750, MessageTag_Destruct)

/* func_020a8754: the constructor; group and kind -1, no parameters (`start` is left as it
 * is). */
void MessageTag_Construct(MessageTag *tag)
{
    tag->group = (u32) -1;
    tag->kind = (u32) -1;
    tag->size = 0;
    tag->params = NULL;
}
CLEAN_AS(func_020a8754, MessageTag_Construct)

/* func_020a8764: the tag at `position` in a message. The head's first halfword (0x1a) is read
 * and not checked. */
void MessageTag_Read(MessageTag *tag, int position)
{
    const u8 *head = (const u8 *) (uintptr_t) position;
    MessageTag_HalfAt(head, 0);
    int size = MessageTag_ByteAt(head, 2);
    int group = MessageTag_ByteAt(head, 3);
    int kind = MessageTag_HalfAt(head, 4);
    tag->group = (u32) group;
    tag->kind = (u32) kind;
    tag->size = (u32) (size - MESSAGE_TAG_HEAD);
    tag->params = (const s8 *) (uintptr_t) (position + MESSAGE_TAG_HEAD);
    tag->start = (const s8 *) (uintptr_t) position;
}
CLEAN_AS(func_020a8764, MessageTag_Read)

/* func_020a87a8: the halfword at `offset` (little-endian, at any alignment), through the
 * codec's halfword reader. */
int MessageTag_HalfAt(const u8 *bytes, int offset)
{
    const u8 *at = bytes + offset;
    u16 half = (u16) (at[0] | at[1] << 8);
    return BmgFile_ReadU16(&half);
}
CLEAN_AS(func_020a87a8, MessageTag_HalfAt)

/* func_020a87c8: the byte at `offset`, through the codec's byte reader. */
int MessageTag_ByteAt(const u8 *bytes, int offset)
{
    u8 byte = bytes[offset];
    return BmgFile_ReadU8(&byte);
}
CLEAN_AS(func_020a87c8, MessageTag_ByteAt)
