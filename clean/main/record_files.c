/* Three record files opened together (record_files.h). */
#include "record_files.h"

#include "clean.h"

static_assert(sizeof(FurnitureRecordFile) == 0x1c, "record file size");
static_assert(offsetof(FurnitureRecordFiles, dma) == 0x38, "third file");

/* A record file's own functions (main). */
extern void func_0206e808(FurnitureRecordFile *file); /* close it, freeing what was read */
extern void func_0206e83c(FurnitureRecordFile *file); /* free its whole copy, if any */
extern void func_0206e854(FurnitureRecordFile *file); /* read it whole */
extern int func_0206e890(FurnitureRecordFile *file, const char *path, int record_size, int records); /* open */

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
    func_0206e83c(&files->indoor);
    return 1;
}
CLEAN_AS(func_0206e6f0, RecordFiles_FreeSecond)

/* func_0206e704: unless `stream`, the second file read whole. Always 1. */
int RecordFiles_LoadSecond(FurnitureRecordFiles *files, int stream)
{
    if (!stream) {
        func_0206e854(&files->indoor);
    }
    return 1;
}
CLEAN_AS(func_0206e704, RecordFiles_LoadSecond)

/* func_0206e71c: the three closed. */
void RecordFiles_Close(FurnitureRecordFiles *files)
{
    func_0206e808(&files->always);
    func_0206e808(&files->indoor);
    func_0206e808(&files->dma);
}
CLEAN_AS(func_0206e71c, RecordFiles_Close)

/* func_0206e73c: the three opened with their record sizes, room for `records` records each,
 * and the first read whole. Always 1. */
int RecordFiles_Open(FurnitureRecordFiles *files, const char *path0, int size0, const char *path1, int size1,
                     const char *path2, int size2, int records)
{
    func_0206e890(&files->always, path0, size0, records);
    func_0206e890(&files->indoor, path1, size1, records);
    func_0206e890(&files->dma, path2, size2, records);
    func_0206e854(&files->always);
    return 1;
}
CLEAN_AS(func_0206e73c, RecordFiles_Open)
