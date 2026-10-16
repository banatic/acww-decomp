/* Main's use of NitroSDK's file system: loading and unloading the main processor's overlays, and
 * reading part of a file of the ROM, which may be stored compressed in blocks.
 *
 * A file in blocks begins with "LZ77" (either byte order) and a word whose bits 0-3 give the
 * block size (0x20 << n bytes; bits 4-7 are all set) and bits 8-31 the plain size. A table of
 * the blocks' 16-bit end offsets follows, then the blocks, each a plain block (first word's
 * bits 4-7 clear, its size in bits 8-31, the bytes after the word) or LZ77-compressed for
 * MI_UncompressLZ8. The last block read is kept (data_021cc860, with its file's and block's
 * numbers), so reading on in the same block reads no more of the file. Such a file is at most
 * 0xffff bytes long. */
#ifndef CLEAN_MAIN_ROM_FILE_H
#define CLEAN_MAIN_ROM_FILE_H

#include "types.h"

/* NitroSDK's FSFile (0x48 bytes): the fields read here. */
typedef struct RomFileFs {
    u8 link_00[0x14];
    s32 error; /* 0x14 */
    u8 queue_18[8];
    u32 own_id;   /* 0x20: the file's number in its archive */
    u32 top;      /* 0x24: where the file starts in the archive */
    u32 bottom;   /* 0x28: where it ends */
    u32 position; /* 0x2c */
    u8 unk_30[0x18];
} RomFileFs;

/* NitroSDK's FSFileID. */
typedef struct RomFileId {
    void *archive;
    u32 file_id;
} RomFileId;

void RomFile_UnloadOverlay(int overlay);
void RomFile_LoadOverlay(int overlay);
void RomFile_ReadPart(RomFileFs *file, u8 *dst, int size, int offset);
void RomFile_ReadPartById(RomFileId id, u8 *dst, int size, int offset);
void RomFile_ReadPartByPath(const char *path, u8 *dst, int size, int offset);
int RomFile_Exists(const char *path);
int RomFile_Size(const char *path);

/* Reading whole files (the functions below RomFile_Size). A file compressed whole begins with
 * "LZ77" (either byte order) and a word that MI_UncompressLZ8 takes as its header: its bits
 * 8-31 are the plain size. It is read into a buffer of the root heap and unpacked from there;
 * when there is no room for it, a buffer as large as the root heap's largest block is used to
 * unpack it piece by piece. Any other file is copied as it is. The paths given as a format
 * are formatted into 0x80 bytes first. */

struct Heap;

int RomFile_OpenedSize(RomFileFs *file);
int RomFile_ReadFormatted(void *dst, int size, const char *format, ...);
void *RomFile_LoadFormatted(const char *format, ...);
void *RomFile_LoadFormattedOn(struct Heap *heap, int align, const char *format, ...);
void *RomFile_LoadFormattedV(struct Heap *heap, int align, u32 *size, const char *format, const void *args);
int RomFile_ReadOpened(RomFileFs *file, u8 *dst, u32 size);
int RomFile_Read(const char *path, void *dst, int size);
void *RomFile_LoadDefault(const char *path);
void *RomFile_Load(const char *path, struct Heap *heap, int align, u32 *size);
void RomFile_Open(RomFileFs *file, const char *path);
int RomFile_TryOpen(RomFileFs *file, const char *path);
int RomFile_LoadOverlayOf(int target, unsigned int overlay);

#endif
