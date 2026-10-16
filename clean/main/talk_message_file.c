/* The message file of a talk (talk_message_file.h). */
#include "talk_message_file.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(TalkMessageFile, buffer) == 0xa4, "file buffer");
static_assert(sizeof(TalkMessageFile) == 0x8a4, "file");

/* The class's vtable. */
extern const u8 data_020def64[];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_0206d630 (vtable slot 3): the size of its buffer. */
int TalkMessageFile_Size(void)
{
    return TALK_MESSAGE_FILE_BUFFER_SIZE;
}
CLEAN_AS(func_0206d630, TalkMessageFile_Size)

/* func_0206d638 (vtable slot 2): the address of its buffer. */
int TalkMessageFile_Buffer(int file)
{
    return file + (int) offsetof(TalkMessageFile, buffer);
}
CLEAN_AS(func_0206d638, TalkMessageFile_Buffer)

/* func_0206d63c: its buffer cleared. */
void TalkMessageFile_Clear(TalkMessageFile *file)
{
    MI_CpuFill8(file->buffer, 0, TALK_MESSAGE_FILE_BUFFER_SIZE);
}
CLEAN_AS(func_0206d63c, TalkMessageFile_Clear)

/* func_0206d650 (vtable slot 1): destroyed (TalkMessageFile_Destruct) and freed. */
TalkMessageFile *TalkMessageFile_Delete(TalkMessageFile *file)
{
    file->base.vtable = data_020def64;
    BmgFile_Destruct(file);
    Heap_OperatorDeleteB(file);
    return file;
}
CLEAN_AS(func_0206d650, TalkMessageFile_Delete)

/* func_0206d670 (vtable slot 0): the destructor: its vtable, then the file base's destructor. */
TalkMessageFile *TalkMessageFile_Destruct(TalkMessageFile *file)
{
    file->base.vtable = data_020def64;
    BmgFile_Destruct(file);
    return file;
}
CLEAN_AS(func_0206d670, TalkMessageFile_Destruct)

/* func_0206d688: the constructor: the file base's (its entries with attributes), then its
 * vtable. */
TalkMessageFile *TalkMessageFile_Construct(TalkMessageFile *file)
{
    BmgFile_Construct(&file->base, 1);
    file->base.vtable = data_020def64;
    return file;
}
CLEAN_AS(func_0206d688, TalkMessageFile_Construct)
