/* The message reader's message file and three text classes of main (message_texts.h). */
#include "message_texts.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(MessageFile, buffer) == 0xa4, "file buffer");
static_assert(sizeof(MessageFile) == 0xaa4, "file");
static_assert(offsetof(MessageText10, end) == 0x1c, "text10 end");
static_assert(sizeof(MessageText10) == 0x20, "text10");
static_assert(sizeof(MessageText46) == 0x40, "text46");
static_assert(sizeof(MessageText256) == 0x118, "text256");

/* The classes' vtables. */
extern const u8 data_020e51e8[]; /* the message file */
extern const u8 data_020e51b8[]; /* 10 characters */
extern const u8 data_020e51d0[]; /* 256 characters */
extern const u8 data_020e5218[]; /* 46 characters */

/* The file base: its constructor (with a first byte) and destructor. */
extern void *func_020a9a90(void *file, u8 first);
extern void *func_020a9a40(void *file);
/* The label base: constructed, destroyed; a label's text emptied. */
extern void *func_020a8cac(void *label);
extern void *func_020a8c38(void *label);
extern void func_020a8c1c(void *label);

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void __register_global_object(void *object, void *destruct, void *record);

/* The global 256-character text: whether it was built (bit 0), the object and its record in
 * the list of objects destroyed at exit. The destructor handed over is the game's own. */
extern u32 data_021f4c7c;
extern MessageText256 data_021f4c98;
extern u8 data_021f4c8c[];
extern void *func_020b55b8(void *text);

/* func_020b5470 (the file's slot 3): the size of its buffer. */
int MessageFile_Size(void)
{
    return MESSAGE_FILE_BUFFER_SIZE;
}
CLEAN_AS(func_020b5470, MessageFile_Size)

/* func_020b5478 (slot 2): the address of its buffer. */
int MessageFile_Buffer(int file)
{
    return file + (int) offsetof(MessageFile, buffer);
}
CLEAN_AS(func_020b5478, MessageFile_Buffer)

/* func_020b547c: its buffer cleared. */
void MessageFile_Clear(MessageFile *file)
{
    MI_CpuFill8(file->buffer, 0, MESSAGE_FILE_BUFFER_SIZE);
}
CLEAN_AS(func_020b547c, MessageFile_Clear)

/* func_020b5490 (slot 1): the file destroyed (MessageFile_Destruct) and freed. */
MessageFile *MessageFile_Delete(MessageFile *file)
{
    file->vtable = data_020e51e8;
    func_020a9a40(file);
    Heap_OperatorDeleteB(file);
    return file;
}
CLEAN_AS(func_020b5490, MessageFile_Delete)

/* func_020b54b0 (slot 0): the destructor: its vtable, then the file base's destructor. */
MessageFile *MessageFile_Destruct(MessageFile *file)
{
    file->vtable = data_020e51e8;
    func_020a9a40(file);
    return file;
}
CLEAN_AS(func_020b54b0, MessageFile_Destruct)

/* func_020b54c8: the constructor: the file base's (first byte 0), then its vtable. */
MessageFile *MessageFile_Construct(MessageFile *file)
{
    func_020a9a90(file, 0);
    file->vtable = data_020e51e8;
    return file;
}
CLEAN_AS(func_020b54c8, MessageFile_Construct)

/* func_020b54e4 (slot 3): the address of the characters. */
int MessageText10_Buffer(int text)
{
    return text + MESSAGE_TEXT_START;
}
CLEAN_AS(func_020b54e4, MessageText10_Buffer)

/* func_020b54e8 (slot 2): the capacity. */
int MessageText10_Capacity(void)
{
    return MESSAGE_TEXT10_CAPACITY;
}
CLEAN_AS(func_020b54e8, MessageText10_Capacity)

/* func_020b54ec (slot 1): destroyed (MessageText10_Destruct) and freed. */
MessageText10 *MessageText10_Delete(MessageText10 *text)
{
    text->vtable = data_020e51b8;
    func_020a8c38(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020b54ec, MessageText10_Delete)

/* func_020b550c (slot 0): the destructor. */
MessageText10 *MessageText10_Destruct(MessageText10 *text)
{
    text->vtable = data_020e51b8;
    func_020a8c38(text);
    return text;
}
CLEAN_AS(func_020b550c, MessageText10_Destruct)

/* func_020b5524: an empty text, with the 0 byte after its characters. */
MessageText10 *MessageText10_Construct(MessageText10 *text)
{
    func_020a8cac(text);
    text->vtable = data_020e51b8;
    text->end = 0;
    func_020a8c1c(text);
    return text;
}
CLEAN_AS(func_020b5524, MessageText10_Construct)

/* func_020b5548: the global 256-character text, built and registered for destruction at exit
 * the first time it is asked for. */
MessageText256 *MessageText256_Global(void)
{
    if ((data_021f4c7c & 1) == 0) {
        MessageText256_Construct(&data_021f4c98);
        __register_global_object(&data_021f4c98, (void *) (uintptr_t) func_020b55b8, data_021f4c8c);
        data_021f4c7c |= 1;
    }
    return &data_021f4c98;
}
CLEAN_AS(func_020b5548, MessageText256_Global)

/* func_020b558c (slot 3): the address of the characters. */
int MessageText256_Buffer(int text)
{
    return text + MESSAGE_TEXT_START;
}
CLEAN_AS(func_020b558c, MessageText256_Buffer)

/* func_020b5590 (slot 2): the capacity. */
int MessageText256_Capacity(void)
{
    return MESSAGE_TEXT256_CAPACITY;
}
CLEAN_AS(func_020b5590, MessageText256_Capacity)

/* func_020b5598 (slot 1): destroyed (MessageText256_Destruct) and freed. */
MessageText256 *MessageText256_Delete(MessageText256 *text)
{
    text->vtable = data_020e51d0;
    func_020a8c38(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020b5598, MessageText256_Delete)

/* func_020b55b8 (slot 0): the destructor. */
MessageText256 *MessageText256_Destruct(MessageText256 *text)
{
    text->vtable = data_020e51d0;
    func_020a8c38(text);
    return text;
}
CLEAN_AS(func_020b55b8, MessageText256_Destruct)

/* func_020b55d0: an empty text. */
MessageText256 *MessageText256_Construct(MessageText256 *text)
{
    func_020a8cac(text);
    text->vtable = data_020e51d0;
    func_020a8c1c(text);
    return text;
}
CLEAN_AS(func_020b55d0, MessageText256_Construct)

/* func_020b55f0 (slot 3): the address of the characters. */
int MessageText46_Buffer(int text)
{
    return text + MESSAGE_TEXT_START;
}
CLEAN_AS(func_020b55f0, MessageText46_Buffer)

/* func_020b55f4 (slot 2): the capacity. */
int MessageText46_Capacity(void)
{
    return MESSAGE_TEXT46_CAPACITY;
}
CLEAN_AS(func_020b55f4, MessageText46_Capacity)

/* func_020b55f8 (slot 1): destroyed (MessageText46_Destruct) and freed. */
MessageText46 *MessageText46_Delete(MessageText46 *text)
{
    text->vtable = data_020e5218;
    func_020a8c38(text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_020b55f8, MessageText46_Delete)

/* func_020b5618 (slot 0): the destructor. */
MessageText46 *MessageText46_Destruct(MessageText46 *text)
{
    text->vtable = data_020e5218;
    func_020a8c38(text);
    return text;
}
CLEAN_AS(func_020b5618, MessageText46_Destruct)

/* func_020b5630: an empty text. */
MessageText46 *MessageText46_Construct(MessageText46 *text)
{
    func_020a8cac(text);
    text->vtable = data_020e5218;
    func_020a8c1c(text);
    return text;
}
CLEAN_AS(func_020b5630, MessageText46_Construct)
