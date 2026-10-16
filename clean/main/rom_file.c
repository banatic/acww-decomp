/* Overlays and parts of the ROM's files (rom_file.h). */
#include "rom_file.h"

#include <stdarg.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/c_library.h"
#include "main/debug_screen.h"

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
    RomFile_LoadOverlayOf(ROM_FILE_ARM9, (unsigned int) overlay);
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
    RomFile_Open(&file, path);
    RomFile_ReadPart(&file, dst, size, offset);
    FS_CloseFile(&file);
}
CLEAN_AS(func_02064828, RomFile_ReadPartByPath)

/* func_02064858: whether the file at `path` opens (it is closed again). */
int RomFile_Exists(const char *path)
{
    RomFileFs file;
    int opened = RomFile_TryOpen(&file, path);
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
    RomFile_Open(&file, path);
    int size = RomFile_OpenedSize(&file);
    FS_CloseFile(&file);
    return size;
}
CLEAN_AS(func_0206487c, RomFile_Size)

extern int FS_OpenFile(RomFileFs *file, const char *path);
extern int FS_LoadOverlay(int target, unsigned int overlay);
extern void DC_StoreAll(void);
extern void DC_FlushAll(void);
extern void MI_InitUncompContextLZ(void *context, void *dst, const void *header);
extern int MI_ReadUncompLZ8(void *context, const void *data, u32 size);

/* The root heap (the one made at start-up from the arena) and the current heap. */
extern Heap *data_021fbe8c;
extern Heap *data_021fbe94;
/* "File can't open. [%s]" */
extern const char data_020de6a4[];

/* The space a path given as a format is formatted into. */
#define ROM_FILE_PATH_SIZE 0x80
/* The alignment RomFile_LoadFormatted and RomFile_LoadDefault ask for. */
#define ROM_FILE_DEFAULT_ALIGN 4
/* The header word: what MI_UncompressLZ8 is given of a file compressed whole, before its data. */
#define ROM_FILE_INFO_SIZE 4

/* NitroSDK's MIUncompContextLZ. */
typedef struct RomFileUnpack {
    u32 unk_00[4];
} RomFileUnpack;

static int is_compressed(u32 magic)
{
    return magic == ROM_FILE_MAGIC || magic == ROM_FILE_MAGIC_SWAPPED;
}

/* func_020648a0: the plain size of an open file: for a file compressed whole or in blocks its
 * header word's, else its length; -1 when its header cannot be read or the file has an error.
 * The header is read from the start of the file and the position put back afterwards. */
int RomFile_OpenedSize(RomFileFs *file)
{
    u32 size = file->bottom - file->top;
    if (size >= ROM_FILE_HEADER_SIZE) {
        u32 position = file->position - file->top;
        u32 header[2];
        FS_SeekFile(file, 0, ROM_FILE_SEEK_SET);
        if (FS_ReadFile(file, header, ROM_FILE_HEADER_SIZE) == ROM_FILE_READ_FAILED) {
            return -1;
        }
        if (is_compressed(header[0])) {
            size = header[1] >> 8;
        }
        FS_SeekFile(file, (s32) position, ROM_FILE_SEEK_SET);
    }
    if (file->error != 0) {
        return -1;
    }
    return (int) size;
}
CLEAN_AS(func_020648a0, RomFile_OpenedSize)

/* func_0206490c: the file at the path `format` gives read into `dst` (RomFile_Read).
 * REQUIRES: a va_list that is the address of the arguments in memory (the ARM's, and the
 * 32-bit x86 one's), as CLib_VSNPrintf hands it to OS_VSNPrintf. */
int RomFile_ReadFormatted(void *dst, int size, const char *format, ...)
{
    char path[ROM_FILE_PATH_SIZE];
    va_list args;

    va_start(args, format);
    CLib_VSNPrintf(path, sizeof(path), format, (const void *) args);
    va_end(args);
    return RomFile_Read(path, dst, size);
}
CLEAN_AS(func_0206490c, RomFile_ReadFormatted)

/* func_0206493c: the file at the path `format` gives loaded on the current heap (aligned to 4).
 * REQUIRES: a va_list that is the address of the arguments in memory, as in
 * RomFile_ReadFormatted. */
void *RomFile_LoadFormatted(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    void *buffer = RomFile_LoadFormattedV(NULL, ROM_FILE_DEFAULT_ALIGN, NULL, format, (const void *) args);
    va_end(args);
    return buffer;
}
CLEAN_AS(func_0206493c, RomFile_LoadFormatted)

/* func_02064960: the file at the path `format` gives loaded on `heap` (NULL: the current heap).
 * REQUIRES: a va_list that is the address of the arguments in memory, as in
 * RomFile_ReadFormatted. */
void *RomFile_LoadFormattedOn(Heap *heap, int align, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    void *buffer = RomFile_LoadFormattedV(heap, align, NULL, format, (const void *) args);
    va_end(args);
    return buffer;
}
CLEAN_AS(func_02064960, RomFile_LoadFormattedOn)

/* func_02064980: `format` with `args` formatted into a path of at most 0x80 bytes, and that
 * file loaded (RomFile_Load). */
void *RomFile_LoadFormattedV(Heap *heap, int align, u32 *size, const char *format, const void *args)
{
    char path[ROM_FILE_PATH_SIZE];

    CLib_VSNPrintf(path, sizeof(path), format, args);
    return RomFile_Load(path, heap, align, size);
}
CLEAN_AS(func_02064980, RomFile_LoadFormattedV)

/* A file compressed whole, its header word at `info` already read (`length` is the file's
 * length), unpacked to `dst` through a buffer of the root heap, with the root heap's
 * HEAP_STOP_ON_FAILURE cleared meanwhile: the rest of the file read whole behind the header
 * word and unpacked at once, or, when the heap has no room for that, read into a buffer of the
 * heap's largest block a piece at a time and unpacked as it comes. Nothing is unpacked when
 * neither buffer can be had or the whole read fails. */
static void unpack_whole(RomFileFs *file, void *dst, const u32 *info, u32 length)
{
    Heap *root = data_021fbe8c;
    /* QUIRK: the flags are read by setting them to 0, then set again without the bit. */
    int flags = Heap_SetFlags(root, 0);
    Heap_SetFlags(root, flags & ~HEAP_STOP_ON_FAILURE);

    u8 *packed = Heap_Alloc(root, (int) (length - ROM_FILE_INFO_SIZE));
    if (packed != NULL) {
        MI_CpuCopy8(info, packed, ROM_FILE_INFO_SIZE);
        DC_StoreAll();
        DC_FlushAll();
        if (FS_ReadFile(file, packed + ROM_FILE_INFO_SIZE, (s32) (length - ROM_FILE_HEADER_SIZE)) != ROM_FILE_READ_FAILED) {
            MI_UncompressLZ8(packed, dst);
        }
    } else {
        int piece = Heap_GetLargestBlock(root);
        packed = Heap_Alloc(root, piece);
        if (packed != NULL) {
            RomFileUnpack unpack;
            MI_InitUncompContextLZ(&unpack, dst, info);
            /* QUIRK: only the end of the data (0) stops it; an error of the unpacking (a
             * negative result) reads on until the file runs out. */
            for (;;) {
                s32 read = FS_ReadFile(file, packed, piece);
                if (read == ROM_FILE_READ_FAILED) {
                    break;
                }
                if (MI_ReadUncompLZ8(&unpack, packed, (u32) read) == 0) {
                    break;
                }
            }
        }
    }
    if (packed != NULL) {
        Heap_Free(root, packed);
    }
    Heap_SetFlags(root, flags);
}

/* func_020649ac: the open file read whole into `dst`, then closed; its plain size, 0 when a
 * file stored as it is is longer than `size` (nothing is read then) or the file has an error.
 * QUIRK: when the header cannot be read the file's length is still the result.
 * BUG: a file compressed whole is unpacked without a check against `size`. */
int RomFile_ReadOpened(RomFileFs *file, u8 *dst, u32 size)
{
    u32 length = file->bottom - file->top;
    int result = (int) length;
    u32 header[2];

    if (length < ROM_FILE_HEADER_SIZE) {
        if (length <= size) {
            FS_ReadFile(file, dst, (s32) length);
        } else {
            result = 0;
        }
    } else if (FS_ReadFile(file, header, ROM_FILE_HEADER_SIZE) == ROM_FILE_READ_FAILED) {
        /* the length stays the result */
    } else if (is_compressed(header[0])) {
        result = (int) (header[1] >> 8);
        unpack_whole(file, dst, &header[1], length);
    } else if (length <= size) {
        MI_CpuCopy8(header, dst, ROM_FILE_HEADER_SIZE);
        FS_ReadFile(file, dst + ROM_FILE_HEADER_SIZE, (s32) (length - ROM_FILE_HEADER_SIZE));
    } else {
        result = 0;
    }

    if (file->error != 0) {
        result = 0;
    }
    FS_CloseFile(file);
    return result;
}
CLEAN_AS(func_020649ac, RomFile_ReadOpened)

/* func_02064af4: the file at `path` read whole into `dst` (RomFile_ReadOpened); the game stops
 * when it cannot be opened. */
int RomFile_Read(const char *path, void *dst, int size)
{
    RomFileFs file;
    RomFile_Open(&file, path);
    return RomFile_ReadOpened(&file, dst, (u32) size);
}
CLEAN_AS(func_02064af4, RomFile_Read)

/* func_02064b18: the file at `path` loaded on the current heap, aligned to 4. */
void *RomFile_LoadDefault(const char *path)
{
    return RomFile_Load(path, NULL, ROM_FILE_DEFAULT_ALIGN, NULL);
}
CLEAN_AS(func_02064b18, RomFile_LoadDefault)

/* func_02064b2c: the file at `path` read whole (a file compressed whole unpacked) into a
 * buffer allocated for it on `heap` (NULL: the current heap) with `align`; NULL when there is no
 * room, the read fails or the file has an error. Its plain size goes to *size when `size` is
 * not NULL. The game stops when the file cannot be opened.
 * QUIRK: when there is no room for a compressed file's plain contents, or its header cannot
 * be read, the size given is the file's length. */
void *RomFile_Load(const char *path, Heap *heap, int align, u32 *size)
{
    RomFileFs file;
    u32 header[2];
    u8 *buffer = NULL;

    if (heap == NULL) {
        heap = data_021fbe94;
    }
    RomFile_Open(&file, path);
    u32 length = file.bottom - file.top;

    if (length < ROM_FILE_HEADER_SIZE) {
        buffer = Heap_AllocAligned(heap, (int) length, align);
        if (buffer != NULL) {
            FS_ReadFile(&file, buffer, (s32) length);
        }
    } else if (FS_ReadFile(&file, header, ROM_FILE_HEADER_SIZE) == ROM_FILE_READ_FAILED) {
        /* nothing loaded */
    } else if (is_compressed(header[0])) {
        u32 plain = header[1] >> 8;
        buffer = Heap_AllocAligned(heap, (int) plain, align);
        if (buffer != NULL) {
            unpack_whole(&file, buffer, &header[1], length);
            length = plain;
        }
    } else {
        buffer = Heap_AllocAligned(heap, (int) length, align);
        if (buffer != NULL) {
            MI_CpuCopy8(header, buffer, ROM_FILE_HEADER_SIZE);
            if (FS_ReadFile(&file, buffer + ROM_FILE_HEADER_SIZE, (s32) (length - ROM_FILE_HEADER_SIZE)) ==
                ROM_FILE_READ_FAILED) {
                Heap_Free(heap, buffer);
                buffer = NULL;
            }
        }
    }

    if (size != NULL) {
        *size = length;
    }
    if (file.error != 0 && buffer != NULL) {
        Heap_Free(heap, buffer);
        buffer = NULL;
    }
    FS_CloseFile(&file);
    return buffer;
}
CLEAN_AS(func_02064b2c, RomFile_Load)

/* func_02064cd8: the file at `path` opened; the game stops with "File can't open. [path]" when
 * it cannot be. */
void RomFile_Open(RomFileFs *file, const char *path)
{
    if (RomFile_TryOpen(file, path) == 0) {
        Fatal_Printf(data_020de6a4, path);
    }
}
CLEAN_AS(func_02064cd8, RomFile_Open)

/* func_02064cf8: the file at `path` opened; whether it opened. */
int RomFile_TryOpen(RomFileFs *file, const char *path)
{
    FS_InitFile(file);
    return FS_OpenFile(file, path);
}
CLEAN_AS(func_02064cf8, RomFile_TryOpen)

/* func_02064d14: an overlay of processor `target` loaded (FS_LoadOverlay); whether it was. */
int RomFile_LoadOverlayOf(int target, unsigned int overlay)
{
    return FS_LoadOverlay(target, overlay);
}
CLEAN_AS(func_02064d14, RomFile_LoadOverlayOf)
