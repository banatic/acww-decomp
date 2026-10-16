/* The message receiver and the message part (message_receiver.h). */
#include "message_receiver.h"

#include <string.h>

#include "clean.h"

static_assert(offsetof(MessageReceiver, name) == 0x04, "receiver name");
static_assert(offsetof(MessageReceiver, message) == 0x1e, "receiver message");
static_assert(sizeof(MessageReceiver) == 0x20, "receiver");
static_assert(offsetof(MessagePart, text) == 0x12, "part text");
static_assert(sizeof(MessagePart) == 0x5c, "part");

extern const u8 data_020e3d4c[]; /* the receiver's vtable */
extern const u8 data_020e3d64[]; /* the message part's vtable */
/* A byte nothing writes (0): what a cleared receiver's message number is set to. */
extern u8 data_021f43ec;

extern void MI_CpuFill8(void *dst, int value, unsigned int size);
/* What most of the game frees with (autoload_2/heap.h). */
extern void func_020edb3c(void *block);
/* The labels' text base: built, destroyed, emptied (text_label.h). */
extern void *func_020a8cac(void *text);
extern void *func_020a8c38(void *text);
extern void func_020a8c1c(void *text);

/* func_020a8164: the file's name set to `name`.
 * QUIRK: at most 25 characters are copied and the 26th byte is left as it is (0 from
 * MessageReceiver_Clear), so a longer name is cut short. */
void MessageReceiver_SetName(MessageReceiver *receiver, const char *name)
{
    strncpy(receiver->name, name, MESSAGE_RECEIVER_NAME_SIZE - 1);
}
CLEAN_AS(func_020a8164, MessageReceiver_SetName)

/* func_020a8170 (vtable slot 2): no name and message number 0. */
void MessageReceiver_Clear(MessageReceiver *receiver)
{
    receiver->message = data_021f43ec;
    MI_CpuFill8(receiver->name, 0, MESSAGE_RECEIVER_NAME_SIZE);
}
CLEAN_AS(func_020a8170, MessageReceiver_Clear)

/* func_020a8188: the destructor's other entry (not in the vtable); the vtable put back. */
void MessageReceiver_DestructBase(MessageReceiver *receiver)
{
    receiver->vtable = data_020e3d4c;
}
CLEAN_AS(func_020a8188, MessageReceiver_DestructBase)

/* func_020a8194 (vtable slot 1): destroyed and freed. */
MessageReceiver *MessageReceiver_Delete(MessageReceiver *receiver)
{
    receiver->vtable = data_020e3d4c;
    func_020edb3c(receiver);
    return receiver;
}
CLEAN_AS(func_020a8194, MessageReceiver_Delete)

/* func_020a81ac (vtable slot 0): the destructor; the vtable put back. */
void MessageReceiver_Destruct(MessageReceiver *receiver)
{
    receiver->vtable = data_020e3d4c;
}
CLEAN_AS(func_020a81ac, MessageReceiver_Destruct)

/* func_020a81b8: the constructor; a cleared receiver. */
MessageReceiver *MessageReceiver_Construct(MessageReceiver *receiver)
{
    receiver->vtable = data_020e3d4c;
    receiver->message = data_021f43ec;
    MI_CpuFill8(receiver->name, 0, MESSAGE_RECEIVER_NAME_SIZE);
    return receiver;
}
CLEAN_AS(func_020a81b8, MessageReceiver_Construct)

/* func_020a81e0: the text emptied. */
void MessagePart_Clear(MessagePart *part)
{
    func_020a8c1c(part);
}
CLEAN_AS(func_020a81e0, MessagePart_Clear)

/* func_020a81e8 (vtable slot 3): the address of the characters. */
int MessagePart_Buffer(MessagePart *part)
{
    return (int) (uintptr_t) part->text;
}
CLEAN_AS(func_020a81e8, MessagePart_Buffer)

/* func_020a81ec (vtable slot 2): the capacity in characters. */
int MessagePart_Capacity(void)
{
    return MESSAGE_PART_CAPACITY;
}
CLEAN_AS(func_020a81ec, MessagePart_Capacity)

/* func_020a81f0 (vtable slot 1): destroyed and freed. */
MessagePart *MessagePart_Delete(MessagePart *part)
{
    part->vtable = data_020e3d64;
    func_020a8c38(part);
    func_020edb3c(part);
    return part;
}
CLEAN_AS(func_020a81f0, MessagePart_Delete)

/* func_020a8210 (vtable slot 0): the destructor. */
MessagePart *MessagePart_Destruct(MessagePart *part)
{
    part->vtable = data_020e3d64;
    func_020a8c38(part);
    return part;
}
CLEAN_AS(func_020a8210, MessagePart_Destruct)

/* func_020a8228: the constructor; an empty text. */
MessagePart *MessagePart_Construct(MessagePart *part)
{
    func_020a8cac(part);
    part->vtable = data_020e3d64;
    MessagePart_Clear(part);
    return part;
}
CLEAN_AS(func_020a8228, MessagePart_Construct)
