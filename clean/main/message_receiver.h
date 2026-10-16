/* A message receiver (class data_020e3d4c): what names a message to read, a file's name of up
 * to 25 characters and a message number in it. The message reader's requests
 * (MessageRequest, message_reader.h) and the letter texts' (MailTextRequest, mail_text.h)
 * derive from it; slot 2 of its vtable clears it, slot 3 (the folder) is left to them.
 *
 * Also the message part (class data_020e3d64, 0x5c bytes): a text of up to 72 8-bit characters
 * on the text base of the labels (text_label.h; func_020a8cac builds the base, func_020a8c38
 * destroys it, func_020a8c1c empties it). The message reader keeps eleven of them, and the
 * letter texts theirs. */
#ifndef CLEAN_MAIN_MESSAGE_RECEIVER_H
#define CLEAN_MAIN_MESSAGE_RECEIVER_H

#include "types.h"

#define MESSAGE_RECEIVER_NAME_SIZE 26
#define MESSAGE_PART_CAPACITY 72

/* The receiver (0x20 bytes). */
typedef struct MessageReceiver {
    const void *vtable;                    /* 0x00: data_020e3d4c, or a derived class's */
    char name[MESSAGE_RECEIVER_NAME_SIZE]; /* 0x04: the file's name */
    u8 message;                            /* 0x1e: the message's number in it */
    u8 unk_1f;
} MessageReceiver;

/* The message part (0x5c bytes). */
typedef struct MessagePart {
    const void *vtable; /* 0x00: data_020e3d64 */
    u32 length;         /* 0x04: the text base's */
    u8 attributes[0x0a];
    char text[MESSAGE_PART_CAPACITY]; /* 0x12 */
    u8 unk_5a[2];
} MessagePart;

void MessageReceiver_SetName(MessageReceiver *receiver, const char *name);
void MessageReceiver_Clear(MessageReceiver *receiver);
void MessageReceiver_DestructBase(MessageReceiver *receiver);
MessageReceiver *MessageReceiver_Delete(MessageReceiver *receiver);
void MessageReceiver_Destruct(MessageReceiver *receiver);
MessageReceiver *MessageReceiver_Construct(MessageReceiver *receiver);

void MessagePart_Clear(MessagePart *part);
int MessagePart_Buffer(MessagePart *part);
int MessagePart_Capacity(void);
MessagePart *MessagePart_Delete(MessagePart *part);
MessagePart *MessagePart_Destruct(MessagePart *part);
MessagePart *MessagePart_Construct(MessagePart *part);

#endif
