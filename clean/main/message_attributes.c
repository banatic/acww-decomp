/* A text's attributes (message_attributes.h). */
#include "message_attributes.h"

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"

static_assert(offsetof(MessageAttributes, unk_04) == 0x04, "attributes word");
static_assert(offsetof(MessageAttributes, unk_08) == 0x08, "attributes byte 8");
static_assert(offsetof(MessageAttributes, unk_09) == 0x09, "attributes byte 9");

extern const u8 data_020e3d24[]; /* the class's vtable */

/* A static object whose first byte is 0xff (set at start-up): a byte attribute not set. */
extern u8 data_021f43ec;

/* func_020a9b04: none set. */
void MessageAttributes_Reset(MessageAttributes *attributes)
{
    attributes->unk_04 = -1;
    attributes->unk_08 = data_021f43ec;
    attributes->unk_09 = data_021f43ec;
}
CLEAN_AS(func_020a9b04, MessageAttributes_Reset)

/* func_020a9b1c: `src`'s copied into `dst` (not the vtable). */
void MessageAttributes_Copy(MessageAttributes *dst, const MessageAttributes *src)
{
    dst->unk_04 = src->unk_04;
    dst->unk_08 = src->unk_08;
    dst->unk_09 = src->unk_09;
}
CLEAN_AS(func_020a9b1c, MessageAttributes_Copy)

/* func_020a9b2c (slot 1): destroyed and freed. */
void *MessageAttributes_Delete(void *attributes)
{
    ((MessageAttributes *) attributes)->vtable = data_020e3d24;
    Heap_OperatorDeleteB(attributes);
    return attributes;
}
CLEAN_AS(func_020a9b2c, MessageAttributes_Delete)

/* func_020a9b44 (slot 0): the destructor; only the vtable put back. */
void MessageAttributes_Destruct(MessageAttributes *attributes)
{
    attributes->vtable = data_020e3d24;
}
CLEAN_AS(func_020a9b44, MessageAttributes_Destruct)

/* func_020a9b50: none set. */
void MessageAttributes_Construct(MessageAttributes *attributes)
{
    attributes->vtable = data_020e3d24;
    attributes->unk_04 = -1;
    attributes->unk_08 = data_021f43ec;
    attributes->unk_09 = data_021f43ec;
}
CLEAN_AS(func_020a9b50, MessageAttributes_Construct)
