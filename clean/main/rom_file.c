/* Overlays and parts of the ROM's files (rom_file.h). */
#include "rom_file.h"

#include "clean.h"

static_assert(sizeof(RomFileFs) == 0x48 && offsetof(RomFileFs, own_id) == 0x20 && offsetof(RomFileFs, bottom) == 0x28,
              "RomFileFs layout");

extern int FS_UnloadOverlay(int target, int overlay);
extern void FS_InitFile(RomFileFs *file);
extern int FS_OpenFileFast(RomFileFs *file, RomFileId id);
extern int FS_SeekFile(RomFileFs *file, s32 offset, int whence);
extern s32 FS_ReadFile(RomFileFs *file, void *dst, s32 size);
extern int FS_CloseFile(RomFileFs *file);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_UncompressLZ8(const void *src, void *dst);

/* Loads an overlay (FS_LoadOverlay). */
extern int func_02064d14(int target, unsigned int overlay);
/* Opens a file by its path; stops the game with a message when it cannot. */
extern void func_02064cd8(RomFileFs *file, const char *path);
/* Opens a file by its path; whether it opened. */
extern int func_02064cf8(RomFileFs *file, const char *path);
/* The plain size of an open file (its block header's for a file in blocks), -1 when it cannot
 * be read. */
extern int func_020648a0(RomFileFs *file);

/* The last block read: the file's number (cut to 16 bits) and the block's (cut to 8). */
extern u16 data_021cb654;
extern u8 data_021cb650;
/* The block table, the first entry 0, each next one where a block ends. */
extern u16 data_021cb660[];
/* A block as read, and as made plain. */
extern u32 data_021cb860[];
extern u8 data_021cc860[];

#define ROM_FILE_ARM9 0 /* the main processor, as the SDK's target */
#define ROM_FILE_SEEK_SET 0
#define ROM_FILE_READ_FAILED (-1)
#define ROM_FILE_MAGIC 0x37375a4c         /* "LZ77" */
#define ROM_FILE_MAGIC_SWAPPED 0x4c5a3737 /* "77ZL" */
#define ROM_FILE_KIND_MASK 0xf0
#define ROM_FILE_IN_BLOCKS 0xf0
#define ROM_FILE_PLAIN_BLOCK 0x00
#define ROM_FILE_MAX_SIZE 0xffff
#define ROM_FILE_MIN_BLOCK 0x20
#define ROM_FILE_HEADER_SIZE 8

/* func_02064640: unloads one of the main processor's overlays. */
void RomFile_UnloadOverlay(int overlay)
{
    FS_UnloadOverlay(ROM_FILE_ARM9, overlay);
}
CLEAN_AS(func_02064640, RomFile_UnloadOverlay)

/* func_0206464c: loads one of the main processor's overlays. */
void RomFile_LoadOverlay(int overlay)
{
    func_02064d14(ROM_FILE_ARM9, (unsigned int) overlay);
}
CLEAN_AS(func_0206464c, RomFile_LoadOverlay)

/* The block `block` of a file in blocks, read and made plain into data_021cc860, unless it is
 * the block read last. `data` is where the blocks start in the file. */
static void read_block(RomFileFs *file, u32 data, u32 block)
{
    if (file->own_id == data_021cb654 && block == data_021cb650) {
        return;
    }
    data_021cb654 = (u16) file->own_id;
    data_021cb650 = (u8) block;

    int start = data_021cb660[block];
    int length = data_021cb660[block + 1] - start;
    FS_SeekFile(file, (s32) (data + (u32) start), ROM_FILE_SEEK_SET);
    FS_ReadFile(file, data_021cb860, length);

    u32 header = data_021cb860[0];
    if ((header & ROM_FILE_KIND_MASK) == ROM_FILE_PLAIN_BLOCK) {
        MI_CpuCopy8(&data_021cb860[1], data_021cc860, header >> 8);
    } else {
        MI_UncompressLZ8(data_021cb860, data_021cc860);
    }
}

/* func_02064658: `size` bytes of the open file's plain contents from `offset` read to `dst`.
 * A file not in blocks is read as it is; one in blocks a block at a time (see rom_file.h).
 * Nothing is read when the header cannot be read, when the header word's bits 4-7 are not all
 * set or when the file is longer than 0xffff bytes.
 * QUIRK: the block table is read whole into data_021cb660 every time, without a check of its
 * size; the block numbers are unsigned, so a negative offset or end reads as a huge one. */
void RomFile_ReadPart(RomFileFs *file, u8 *dst, int size, int offset)
{
    u32 header[2];

    FS_SeekFile(file, 0, ROM_FILE_SEEK_SET);
    if (FS_ReadFile(file, header, ROM_FILE_HEADER_SIZE) == ROM_FILE_READ_FAILED) {
        return;
    }
    if (header[0] != ROM_FILE_MAGIC && header[0] != ROM_FILE_MAGIC_SWAPPED) {
        FS_SeekFile(file, offset, ROM_FILE_SEEK_SET);
        FS_ReadFile(file, dst, size);
        return;
    }

    u32 info = header[1];
    if ((info & ROM_FILE_KIND_MASK) != ROM_FILE_IN_BLOCKS) {
        return;
    }
    if (file->bottom - file->top > ROM_FILE_MAX_SIZE) {
        return;
    }
    u32 block_size = (u32) ROM_FILE_MIN_BLOCK << (info & 0xf);
    data_021cb660[0] = 0;
    u32 table_size = (((info >> 8) - 1) / block_size + 1) * 2;
    FS_ReadFile(file, &data_021cb660[1], (s32) table_size);
    u32 data = table_size + ROM_FILE_HEADER_SIZE;

    int end = offset + size;
    u32 last = (u32) (end - 1) / block_size + 1;
    for (u32 block = (u32) offset / block_size; block < last; block++) {
        u32 block_end = block_size * (block + 1);
        if ((u32) offset >= block_end) {
            continue;
        }
        u32 block_start = block_size * block;
        if ((u32) end <= block_start) {
            continue;
        }
        read_block(file, data, block);

        int skip = (int) ((u32) offset - block_start);
        if (skip < 0) {
            skip = 0;
        }
        int past = (int) (block_end - (u32) end);
        if (past < 0) {
            past = 0;
        }
        int count = (int) (block_size - (u32) skip - (u32) past);
        MI_CpuCopy8(data_021cc860 + skip, dst, (u32) count);
        dst += count;
    }
}
CLEAN_AS(func_02064658, RomFile_ReadPart)

/* func_020647ec: RomFile_ReadPart on the file `id`, when it opens. */
void RomFile_ReadPartById(RomFileId id, u8 *dst, int size, int offset)
{
    RomFileFs file;
    FS_InitFile(&file);
    if (FS_OpenFileFast(&file, id)) {
        RomFile_ReadPart(&file, dst, size, offset);
        FS_CloseFile(&file);
    }
}
CLEAN_AS(func_020647ec, RomFile_ReadPartById)

/* func_02064828: RomFile_ReadPart on the file at `path` (the game stops when it cannot be
 * opened). */
void RomFile_ReadPartByPath(const char *path, u8 *dst, int size, int offset)
{
    RomFileFs file;
    func_02064cd8(&file, path);
    RomFile_ReadPart(&file, dst, size, offset);
    FS_CloseFile(&file);
}
CLEAN_AS(func_02064828, RomFile_ReadPartByPath)

/* func_02064858: whether the file at `path` opens (it is closed again). */
int RomFile_Exists(const char *path)
{
    RomFileFs file;
    int opened = func_02064cf8(&file, path);
    if (opened) {
        FS_CloseFile(&file);
    }
    return opened;
}
CLEAN_AS(func_02064858, RomFile_Exists)

/* func_0206487c: the plain size of the file at `path` (the game stops when it cannot be
 * opened). */
int RomFile_Size(const char *path)
{
    RomFileFs file;
    func_02064cd8(&file, path);
    int size = func_020648a0(&file);
    FS_CloseFile(&file);
    return size;
}
CLEAN_AS(func_0206487c, RomFile_Size)
