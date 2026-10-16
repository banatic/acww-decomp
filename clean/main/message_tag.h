/* The tags of the message texts (MessageTag, message_decoder.h): reading one from a message,
 * its parameter bytes, and the texts some tags carry after them.
 *
 * A tag in a message is a 6-byte head and its parameters: the halfword 0x1a, the tag's whole
 * size in bytes, its group (a byte) and its kind (a halfword), each read through the text
 * codec's byte and halfword readers (func_020a9adc, func_020a9ae0).
 *
 * Some tags are followed by texts the game sets into labels (func_020a8a34): they start two
 * bytes after the tag, and each takes its length plus two bytes. Those readers return the
 * bytes the texts take, the two before them included.
 *
 * The game also keeps a list of ready-made 0xff/0 tags of 8 bytes (data_020d1d70), one per
 * value of their first parameter byte; a 0xff/0 tag is a colour change in Nintendo's message
 * format, which is how the game uses these (around a name). */
#ifndef CLEAN_MAIN_MESSAGE_TAG_H
#define CLEAN_MAIN_MESSAGE_TAG_H

#include "message_decoder.h"
#include "types.h"

/* The start of a text a label holds (text_label.h): only its length is read here. */
typedef struct MessageTagText {
    const void *vtable;
    s32 length; /* 0x04 */
} MessageTagText;

int MessageTag_ColourTag(int colour);
unsigned char MessageTag_Colour(MessageTag *tag);
void MessageTag_SplitParams(MessageTag *tag, u32 *first, s32 *end, const s8 **rest);
int MessageTag_PartIndex(MessageTag *tag);
int MessageTag_IsPart(MessageTag *tag);
int MessageTag_ReadEightBytesTwoTexts(MessageTag *tag, u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f, u8 *g, u8 *h,
                                      MessageTagText *text0, MessageTagText *text1);
unsigned int MessageTag_TextsSize(MessageTag *tag);
int MessageTag_ReadFiveTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1, u8 *byte2,
                             MessageTagText *text2, u8 *byte3, MessageTagText *text3, u8 *byte4, MessageTagText *text4);
int MessageTag_ReadFourTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1, u8 *byte2,
                             MessageTagText *text2, u8 *byte3, MessageTagText *text3);
int MessageTag_ReadThreeTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1, u8 *byte2,
                              MessageTagText *text2);
unsigned int MessageTag_ReadTwoTexts(MessageTag *tag, u8 *byte0, MessageTagText *text0, u8 *byte1, MessageTagText *text1);
void MessageTag_GetFirstHalf(MessageTag *tag, u16 *out);
void MessageTag_ReadBytes(MessageTag *tag, u8 *out, int count);
void MessageTag_ReadFiveBytes(MessageTag *tag, u8 *byte0, u8 *byte1, u8 *byte2, u8 *byte3, u8 *byte4);
void MessageTag_ReadFourBytes(MessageTag *tag, u8 *byte0, u8 *byte1, u8 *byte2, u8 *byte3);
int MessageTag_ReadThreeBytes(MessageTag *tag, u8 *byte0, u8 *byte1, u8 *byte2);
void MessageTag_ReadTwoBytes(MessageTag *tag, u8 *byte0, u8 *byte1);
void MessageTag_GetFirstByte(MessageTag *tag, u8 *out);
void MessageTag_Destruct(void *tag);
void MessageTag_Construct(MessageTag *tag);
void MessageTag_Read(MessageTag *tag, int position);
int MessageTag_HalfAt(const u8 *bytes, int offset);
int MessageTag_ByteAt(const u8 *bytes, int offset);

#endif
