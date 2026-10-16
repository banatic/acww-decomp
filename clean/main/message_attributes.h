/* A text's attributes (MessageAttributes of message_decoder.h, class data_020e3d24, 0x0c
 * bytes): a word that is -1 when not set and two bytes that are 0xff (data_021f43ec's) when
 * not set. Its vtable has only the destructor and the deleting destructor. */
#ifndef CLEAN_MAIN_MESSAGE_ATTRIBUTES_H
#define CLEAN_MAIN_MESSAGE_ATTRIBUTES_H

#include "message_decoder.h"
#include "types.h"

void MessageAttributes_Reset(MessageAttributes *attributes);
void MessageAttributes_Copy(MessageAttributes *dst, const MessageAttributes *src);
void *MessageAttributes_Delete(void *attributes);
void MessageAttributes_Destruct(MessageAttributes *attributes);
void MessageAttributes_Construct(MessageAttributes *attributes);

#endif
