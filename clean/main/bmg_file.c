/* A message file of the "MESGbmg1" format (bmg_file.h).
 *
 * REQUIRES: the values BmgFile_ReadU16 and BmgFile_ReadU32 are handed at aligned addresses,
 * as the headers and entries the game reads into are (the ARM9 reads an aligned halfword or a
 * rotated word at a misaligned address). */
#include "bmg_file.h"

#include <string.h>

#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "clean.h"
#include "rom_file.h"

static_assert(offsetof(BmgFile, path) == 0x05, "bmg path");
static_assert(offsetof(BmgFile, fs_file) == 0x44, "bmg fs file");
static_assert(offsetof(BmgFile, open) == 0x8c, "bmg open");
static_assert(offsetof(BmgFile, entry) == 0x90, "bmg entry");
static_assert(offsetof(BmgFile, text_size) == 0xa0, "bmg text size");
static_assert(sizeof(BmgFile) == 0xa4, "bmg file");
static_assert(sizeof(BmgEntry) == 0x0c, "bmg entry size");
static_assert(sizeof(BmgHeader) == 0x20, "bmg header");
static_assert(offsetof(BmgHeader, unk_1c) == 0x1c, "bmg header 0x1c");
static_assert(sizeof(BmgInfoHeader) == 0x14, "bmg inf1");
static_assert(sizeof(BmgDataHeader) == 0x0c, "bmg dat1");

/* The magics, read as big-endian words. */
#define BMG_MAGIC_MESG 0x4d455347u
#define BMG_MAGIC_BMG1 0x626d6731u
#define BMG_MAGIC_INF1 0x494e4631u
#define BMG_MAGIC_DAT1 0x44415431u

/* Where the INF1 section starts, and its entries in it. */
#define BMG_INFO_OFFSET 0x20
#define BMG_INFO_ENTRIES 0x10
/* The size of DAT1's head, before its data. */
#define BMG_DATA_HEAD 8
/* The sections a file has, and the most messages a file may have. */
#define BMG_SECTIONS 2
#define BMG_MAX_MESSAGES 0x100
/* The size of an entry with and without attributes. */
#define BMG_ENTRY_SIZE_ATTRIBUTES 0x0c
#define BMG_ENTRY_SIZE_OFFSET 4

/* The derived class's vtable slots: the buffer's address and its size. */
#define BMG_FILE_SLOT_BUFFER 2
#define BMG_FILE_SLOT_BUFFER_SIZE 3

extern const u8 data_020e3d34[]; /* the class's vtable */

/* The headers of the file a message is being loaded from. */
extern BmgHeader data_021f446c;
extern BmgInfoHeader data_021f4458;
extern BmgDataHeader data_021f4428;

/* A static object whose first byte is 0xff (set at start-up): the index of no message. */
extern u8 data_021f43ec;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void FS_InitFile(void *fs_file);
extern int FS_OpenFile(void *fs_file, const char *path);
extern int FS_CloseFile(void *fs_file);

typedef int BmgFileBuffer(BmgFile *file);
typedef unsigned int BmgFileBufferSize(BmgFile *file);

/* The address of a file's vtable slot. */
static uintptr_t bmg_file_slot(const BmgFile *file, int slot)
{
    return (uintptr_t) ((const u32 *) file->vtable)[slot];
}

/* Whether a step of BmgFile_LoadMessage passed: only bit 0 of its result counts. */
static int bmg_file_passed(int result)
{
    return (result & 1) != 0;
}

/* func_020a9530: the loaded message's entry, or NULL when the file's entries have no
 * attributes. */
void *BmgFile_Entry(BmgFile *file)
{
    if (file->has_attributes == 0) {
        return NULL;
    }
    return &file->entry;
}
CLEAN_AS(func_020a9530, BmgFile_Entry)

/* func_020a9540: the message's text read into the derived class's buffer, as much of it as
 * fits; 1. */
int BmgFile_ReadText(BmgFile *file)
{
    int buffer = ((BmgFileBuffer *) bmg_file_slot(file, BMG_FILE_SLOT_BUFFER))(file);
    unsigned int capacity = ((BmgFileBufferSize *) bmg_file_slot(file, BMG_FILE_SLOT_BUFFER_SIZE))(file);
    u32 text = file->text_offset + BMG_DATA_HEAD;
    u32 size = capacity < file->text_size ? capacity : file->text_size;
    u32 data = data_021f4458.size + BMG_INFO_OFFSET;
    RomFile_ReadPart((RomFileFs *) (void *) file->fs_file, (void *) (uintptr_t) buffer, (int) size, (int) (data + text));
    return 1;
}
CLEAN_AS(func_020a9540, BmgFile_ReadText)

/* func_020a958c: the message's entry read (with its attributes), and the next one's for the
 * text's size, which for the last message runs to the end of DAT1; 1. */
int BmgFile_ReadEntryWithAttributes(BmgFile *file)
{
    BmgEntry entries[2];
    unsigned int index = file->index;
    int last = data_021f4458.count - 1 == (int) index;
    int count = last ? 1 : 2;

    RomFile_ReadPart((RomFileFs *) (void *) file->fs_file, (u8 *) entries, count * (int) sizeof(BmgEntry),
                     (int) (index * sizeof(BmgEntry)) + BMG_INFO_ENTRIES + BMG_INFO_OFFSET);
    for (int i = 0; i < count; i++) {
        entries[i].text_offset = (u32) BmgFile_ReadU32((const s32 *) &entries[i].text_offset);
        for (int j = 0; j < 6; j++) {
            entries[i].attributes[j] = (u8) BmgFile_ReadU8(&entries[i].attributes[j]);
        }
    }

    file->text_offset = entries[0].text_offset;
    if (last) {
        file->text_size = data_021f4428.size - (file->text_offset + BMG_DATA_HEAD);
    } else {
        file->text_size = entries[1].text_offset - file->text_offset;
    }
    MI_CpuCopy8(entries, &file->entry, sizeof(BmgEntry));
    return 1;
}
CLEAN_AS(func_020a958c, BmgFile_ReadEntryWithAttributes)

/* func_020a967c: the message's entry read (an offset only), and the next one's for the text's
 * size, which for the last message runs to the end of DAT1; 1. */
int BmgFile_ReadEntryOffset(BmgFile *file)
{
    s32 offsets[2];
    unsigned int index = file->index;
    int last = data_021f4458.count - 1 == (int) index;

    RomFile_ReadPart((RomFileFs *) (void *) file->fs_file, (u8 *) offsets, last ? 4 : 8,
                     (int) (index * 4) + BMG_INFO_ENTRIES + BMG_INFO_OFFSET);
    file->text_offset = (u32) BmgFile_ReadU32(&offsets[0]);
    if (last) {
        file->text_size = data_021f4428.size - (file->text_offset + BMG_DATA_HEAD);
    } else {
        file->text_size = (u32) BmgFile_ReadU32(&offsets[1]) - file->text_offset;
    }
    file->entry.text_offset = file->text_offset;
    return 1;
}
CLEAN_AS(func_020a967c, BmgFile_ReadEntryOffset)

/* func_020a9708: DAT1's header read (after INF1); 1 when its magic is right. */
int BmgFile_ReadDataHeader(BmgFile *file)
{
    RomFile_ReadPart((RomFileFs *) (void *) file->fs_file, (u8 *) &data_021f4428, sizeof(BmgDataHeader),
                     (int) data_021f4458.size + BMG_INFO_OFFSET);
    data_021f4428.magic = BmgFile_ReadMagic(&data_021f4428.magic);
    data_021f4428.size = (u32) BmgFile_ReadU32((const s32 *) &data_021f4428.size);
    return data_021f4428.magic == BMG_MAGIC_DAT1;
}
CLEAN_AS(func_020a9708, BmgFile_ReadDataHeader)

/* func_020a9754: INF1's header read; 1 when its magic is right, the file has the message
 * (and at most 0x100), its entries have the size the file expects, and its 0x0c is 0. */
int BmgFile_ReadInfoHeader(BmgFile *file)
{
    RomFile_ReadPart((RomFileFs *) (void *) file->fs_file, (u8 *) &data_021f4458, sizeof(BmgInfoHeader), BMG_INFO_OFFSET);
    data_021f4458.magic = BmgFile_ReadMagic(&data_021f4458.magic);
    data_021f4458.size = (u32) BmgFile_ReadU32((const s32 *) &data_021f4458.size);
    data_021f4458.count = (u16) BmgFile_ReadU16(&data_021f4458.count);
    data_021f4458.entry_size = (u16) BmgFile_ReadU16(&data_021f4458.entry_size);
    data_021f4458.unk_0c = (u16) BmgFile_ReadU16(&data_021f4458.unk_0c);
    data_021f4458.unk_0e = (u8) BmgFile_ReadU8(&data_021f4458.unk_0e);

    int magic_ok = data_021f4458.magic == BMG_MAGIC_INF1;
    int count = data_021f4458.count;
    int has_message = count <= BMG_MAX_MESSAGES && file->index < count;
    int entry_size = file->has_attributes != 0 ? BMG_ENTRY_SIZE_ATTRIBUTES : BMG_ENTRY_SIZE_OFFSET;
    int size_ok = data_021f4458.entry_size == entry_size;
    int unk_ok = data_021f4458.unk_0c == 0;
    return magic_ok && has_message && size_ok && unk_ok;
}
CLEAN_AS(func_020a9754, BmgFile_ReadInfoHeader)

/* func_020a982c: the file's header read; 1 when it is a "MESGbmg1" file of two sections and
 * a size. */
int BmgFile_ReadHeader(BmgFile *file)
{
    RomFile_ReadPart((RomFileFs *) (void *) file->fs_file, (u8 *) &data_021f446c, sizeof(BmgHeader), 0);
    data_021f446c.magic = BmgFile_ReadMagic(&data_021f446c.magic);
    data_021f446c.type = BmgFile_ReadMagic(&data_021f446c.type);
    data_021f446c.size = (u32) BmgFile_ReadU32((const s32 *) &data_021f446c.size);
    data_021f446c.sections = (u32) BmgFile_ReadU32((const s32 *) &data_021f446c.sections);
    data_021f446c.encoding = (u8) BmgFile_ReadU8(&data_021f446c.encoding);
    data_021f446c.unk_1c = (u32) BmgFile_ReadU32((const s32 *) &data_021f446c.unk_1c);

    return data_021f446c.magic == BMG_MAGIC_MESG && data_021f446c.type == BMG_MAGIC_BMG1 && data_021f446c.size != 0 &&
           data_021f446c.sections == BMG_SECTIONS;
}
CLEAN_AS(func_020a982c, BmgFile_ReadHeader)

/* func_020a98e4: no message loaded: index 0, its entry and text cleared, and the three
 * headers. */
void BmgFile_Clear(BmgFile *file)
{
    file->index = 0;
    MI_CpuFill8(&file->entry, 0, sizeof(BmgEntry));
    file->text_offset = 0;
    file->text_size = 0;
    MI_CpuFill8(&data_021f446c, 0, sizeof(BmgHeader));
    MI_CpuFill8(&data_021f4458, 0, sizeof(BmgInfoHeader));
    MI_CpuFill8(&data_021f4428, 0, sizeof(BmgDataHeader));
}
CLEAN_AS(func_020a98e4, BmgFile_Clear)

/* func_020a9938: the message whose index is the byte at `index` loaded into the derived
 * class's buffer; 1 when every step passed (each runs only when the ones before did). */
int BmgFile_LoadMessage(BmgFile *file, const u8 *index)
{
    int ok;

    BmgFile_Clear(file);
    file->index = *index;

    ok = bmg_file_passed(BmgFile_ReadHeader(file));
    if (ok) {
        ok = bmg_file_passed(BmgFile_ReadInfoHeader(file));
    }
    if (ok) {
        ok = bmg_file_passed(BmgFile_ReadDataHeader(file));
    }
    if (ok) {
        if (file->has_attributes != 0) {
            ok = bmg_file_passed(BmgFile_ReadEntryWithAttributes(file));
        } else {
            ok = bmg_file_passed(BmgFile_ReadEntryOffset(file));
        }
    }
    if (ok) {
        ok = bmg_file_passed(BmgFile_ReadText(file));
    }
    return ok;
}
CLEAN_AS(func_020a9938, BmgFile_LoadMessage)

/* func_020a99d8: the file closed, when open; the index back to none. */
void BmgFile_Close(void *file)
{
    BmgFile *self = file;
    if (self->open != 0) {
        FS_CloseFile(self->fs_file);
        self->open = 0;
        self->index = data_021f43ec;
    }
}
CLEAN_AS(func_020a99d8, BmgFile_Close)

/* func_020a9a08: the file at `path` opened (its path kept, cut to 62 characters); 1 when it
 * opened. */
unsigned char BmgFile_Open(BmgFile *file, const char *path)
{
    strncpy(file->path, path, BMG_FILE_PATH_SIZE - 1);
    file->open = FS_OpenFile(file->fs_file, path) != 0 ? 1 : 0;
    return file->open;
}
CLEAN_AS(func_020a9a08, BmgFile_Open)

/* func_020a9a40: the destructor the derived classes call: the file closed. */
void *BmgFile_Destruct(void *file)
{
    ((BmgFile *) file)->vtable = data_020e3d34;
    BmgFile_Close(file);
    return file;
}
CLEAN_AS(func_020a9a40, BmgFile_Destruct)

/* func_020a9a58 (slot 1): the file destroyed (as BmgFile_Destruct) and freed. */
void *BmgFile_Delete(void *file)
{
    ((BmgFile *) file)->vtable = data_020e3d34;
    BmgFile_Close(file);
    Heap_OperatorDeleteB(file);
    return file;
}
CLEAN_AS(func_020a9a58, BmgFile_Delete)

/* func_020a9a78 (slot 0): the destructor, the same as BmgFile_Destruct. */
void *BmgFile_DestructSlot(void *file)
{
    ((BmgFile *) file)->vtable = data_020e3d34;
    BmgFile_Close(file);
    return file;
}
CLEAN_AS(func_020a9a78, BmgFile_DestructSlot)

/* func_020a9a90: a closed file with no message and an empty path; `has_attributes` says
 * whether the files it opens have entries of 0x0c bytes. */
BmgFile *BmgFile_Construct(BmgFile *file, unsigned char has_attributes)
{
    file->vtable = data_020e3d34;
    file->has_attributes = has_attributes;
    file->open = 0;
    file->index = data_021f43ec;
    file->text_offset = 0;
    file->text_size = 0;
    FS_InitFile(file->fs_file);
    MI_CpuFill8(file->path, 0, BMG_FILE_PATH_SIZE);
    return file;
}
CLEAN_AS(func_020a9a90, BmgFile_Construct)

/* func_020a9adc: a byte of the file. */
int BmgFile_ReadU8(const u8 *value)
{
    return *value;
}
CLEAN_AS(func_020a9adc, BmgFile_ReadU8)

/* func_020a9ae0: a halfword of the file (little-endian, as the DS). */
int BmgFile_ReadU16(const u16 *value)
{
    return *value;
}
CLEAN_AS(func_020a9ae0, BmgFile_ReadU16)

/* func_020a9ae4: a word of the file (little-endian, as the DS). */
int BmgFile_ReadU32(const s32 *value)
{
    return *value;
}
CLEAN_AS(func_020a9ae4, BmgFile_ReadU32)

/* func_020a9ae8: a magic of the file: its four bytes as a big-endian word (read a byte at a
 * time, at any address). */
unsigned int BmgFile_ReadMagic(const u32 *value)
{
    const u8 *bytes = (const u8 *) value;
    return ((u32) bytes[0] << 24) | ((u32) bytes[1] << 16) | ((u32) bytes[2] << 8) | bytes[3];
}
CLEAN_AS(func_020a9ae8, BmgFile_ReadMagic)
