/* Three record files opened together (record_files.h). */
#include "record_files.h"

#include "clean.h"
#include "record_file.h"

static_assert(sizeof(FurnitureRecordFile) == 0x1c, "record file size");
static_assert(offsetof(FurnitureRecordFiles, dma) == 0x38, "third file");

/* func_0206e6e4: the third file. */
int RecordFiles_Third(int files)
{
    return (int) ((u32) files + offsetof(FurnitureRecordFiles, dma));
}
CLEAN_AS(func_0206e6e4, RecordFiles_Third)

/* func_0206e6e8: the second file. */
int RecordFiles_Second(int files)
{
    return (int) ((u32) files + offsetof(FurnitureRecordFiles, indoor));
}
CLEAN_AS(func_0206e6e8, RecordFiles_Second)

/* func_0206e6ec: the first file. */
FurnitureRecordFile *RecordFiles_First(FurnitureRecordFiles *files)
{
    return &files->always;
}
CLEAN_AS(func_0206e6ec, RecordFiles_First)

/* func_0206e6f0: the second file's whole copy freed. Always 1. */
int RecordFiles_FreeSecond(FurnitureRecordFiles *files)
{
    RecordFile_FreeWhole(&files->indoor);
    return 1;
}
CLEAN_AS(func_0206e6f0, RecordFiles_FreeSecond)

/* func_0206e704: unless `stream`, the second file read whole. Always 1. */
int RecordFiles_LoadSecond(FurnitureRecordFiles *files, int stream)
{
    if (!stream) {
        RecordFile_ReadWhole(&files->indoor);
    }
    return 1;
}
CLEAN_AS(func_0206e704, RecordFiles_LoadSecond)

/* func_0206e71c: the three closed. */
void RecordFiles_Close(FurnitureRecordFiles *files)
{
    RecordFile_Close(&files->always);
    RecordFile_Close(&files->indoor);
    RecordFile_Close(&files->dma);
}
CLEAN_AS(func_0206e71c, RecordFiles_Close)

/* func_0206e73c: the three opened with their record sizes, room for `records` records each,
 * and the first read whole. Always 1. */
int RecordFiles_Open(FurnitureRecordFiles *files, const char *path0, int size0, const char *path1, int size1,
                     const char *path2, int size2, int records)
{
    RecordFile_Open(&files->always, path0, size0, records);
    RecordFile_Open(&files->indoor, path1, size1, records);
    RecordFile_Open(&files->dma, path2, size2, records);
    RecordFile_ReadWhole(&files->always);
    return 1;
}
CLEAN_AS(func_0206e73c, RecordFiles_Open)
