/* One file of fixed-size records (record_file.h). */
#include "record_file.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "backup_card.h"
#include "clean.h"
#include "rom_file.h"

static_assert(sizeof(FurnitureRecordFile) == 0x1c, "record file size");
static_assert(offsetof(FurnitureRecordFile, record_size) == 0x08, "record size");
static_assert(offsetof(FurnitureRecordFile, whole) == 0x10, "whole copy");
static_assert(offsetof(FurnitureRecordFile, cached) == 0x14, "cached block");
static_assert(offsetof(FurnitureRecordFile, cache) == 0x18, "cache");
static_assert(sizeof(RomFileId) == 8, "file id size");

/* The game's record of the save memory. */
extern BackupCard data_021c8188;

extern void FS_InitFile(RomFileFs *file);
extern int FS_OpenFileFast(RomFileFs *file, RomFileId id);
extern int FS_CloseFile(RomFileFs *file);
extern int FS_ConvertPathToFileID(void *id, const char *path);

static RomFileId record_file_id(const FurnitureRecordFile *file)
{
    RomFileId id;
    memcpy(&id, file->file_id, sizeof id);
    return id;
}

/* The file id's first word, its archive, cleared. */
static void clear_archive(FurnitureRecordFile *file)
{
    memset(file->file_id, 0, 4); /* a 32-bit pointer */
}

/* func_0206e778: the block of eight records holding record `index` read into the cache.
 * Nothing is read when the file cannot be opened.
 * QUIRK: the save memory's status is asked first and not looked at. */
void RecordFile_ReadBlock(FurnitureRecordFile *file, unsigned int index)
{
    RomFileFs fs;
    unsigned int block = index / RECORD_FILE_CACHE_RECORDS;

    BackupCard_Status(&data_021c8188);
    FS_InitFile(&fs);
    if (FS_OpenFileFast(&fs, record_file_id(file))) {
        u32 block_size = file->record_size * RECORD_FILE_CACHE_RECORDS;
        RomFile_ReadPart(&fs, file->cache, (int) block_size, (int) (block * block_size));
        FS_CloseFile(&fs);
    }
}
CLEAN_AS(func_0206e778, RecordFile_ReadBlock)

/* func_0206e7bc: record `index`, from the whole copy when there is one, else from the cache
 * (its block read first unless it is the one cached). NULL when the file has no cache. */
char *RecordFile_Record(FurnitureRecordFile *file, unsigned int index)
{
    unsigned int block = index / RECORD_FILE_CACHE_RECORDS;
    unsigned int in_block = index % RECORD_FILE_CACHE_RECORDS;

    if (file->whole != NULL) {
        return (char *) file->whole + file->record_size * index;
    }
    if ((u32) file->cached == block) {
        return (char *) file->cache + file->record_size * in_block;
    }
    if (file->cache == NULL) {
        return NULL;
    }
    RecordFile_ReadBlock(file, index);
    file->cached = (s32) block;
    return (char *) file->cache + file->record_size * in_block;
}
CLEAN_AS(func_0206e7bc, RecordFile_Record)

/* func_0206e808: the file closed: nothing cached, no records, and the whole copy and the
 * cache freed.
 * QUIRK: only the first word of the file id (its archive) is cleared. */
void RecordFile_Close(FurnitureRecordFile *file)
{
    clear_archive(file);
    file->cached = -1;
    file->records = 0;
    file->record_size = 0;
    if (file->whole != NULL) {
        Heap_FreeCurrent(file->whole);
        file->whole = NULL;
    }
    if (file->cache != NULL) {
        Heap_FreeCurrent(file->cache);
        file->cache = NULL;
    }
}
CLEAN_AS(func_0206e808, RecordFile_Close)

/* func_0206e83c: the whole copy freed, if there is one. */
void RecordFile_FreeWhole(FurnitureRecordFile *file)
{
    if (file->whole != NULL) {
        Heap_FreeCurrent(file->whole);
        file->whole = NULL;
    }
}
CLEAN_AS(func_0206e83c, RecordFile_FreeWhole)

/* func_0206e854: the whole file read into memory, allocated unless a copy is there already.
 * QUIRK: the save memory's status is asked first and not looked at.
 * BUG: a failed allocation is not noticed: the file is read to address 0. */
void RecordFile_ReadWhole(FurnitureRecordFile *file)
{
    u32 size = file->record_size * file->records;

    if (file->whole == NULL) {
        file->whole = Heap_AllocCurrent((int) size);
    }
    BackupCard_Status(&data_021c8188);
    RomFile_ReadPartById(record_file_id(file), file->whole, (int) size, 0);
}
CLEAN_AS(func_0206e854, RecordFile_ReadWhole)

/* func_0206e890: the file at `path` opened for `records` records of `record_size` bytes, and
 * its cache allocated. Always 1.
 * QUIRK: whether the path was found is not looked at, and the cached block is left as it was
 * (RecordFile_Construct and RecordFile_Close set it to none). */
int RecordFile_Open(FurnitureRecordFile *file, const char *path, int record_size, int records)
{
    file->record_size = (u32) record_size;
    file->records = (u32) records;
    FS_ConvertPathToFileID(file->file_id, path);
    file->cache = Heap_AllocCurrent((int) ((u32) record_size * RECORD_FILE_CACHE_RECORDS));
    return 1;
}
CLEAN_AS(func_0206e890, RecordFile_Open)

/* func_0206e8b4: the destructor: the file closed; the file's address is the answer. */
int RecordFile_Destruct(FurnitureRecordFile *file)
{
    RecordFile_Close(file);
    return (int) (uintptr_t) file;
}
CLEAN_AS(func_0206e8b4, RecordFile_Destruct)

/* func_0206e8c4: the constructor: nothing open, read or cached.
 * QUIRK: only the first word of the file id (its archive) is cleared. */
void RecordFile_Construct(FurnitureRecordFile *file)
{
    clear_archive(file);
    file->cached = -1;
    file->records = 0;
    file->whole = NULL;
    file->cache = NULL;
    file->record_size = 0;
}
CLEAN_AS(func_0206e8c4, RecordFile_Construct)
