/* A message file of the game's "MESGbmg1" format, and the reading of one message from it
 * (class data_020e3d34, 0xa4 bytes; the message file of message_texts.h and the talks'
 * derive from it).
 *
 * The file is opened by its path (BmgFile_Open) and a message loaded by its index
 * (BmgFile_LoadMessage): the file's header (0x20 bytes at 0), its INF1 section's header
 * (0x14 bytes at 0x20), its DAT1 section's header (after INF1), then the message's INF1 entry
 * are read and checked, and the message's text is read into the buffer the derived class's
 * vtable gives. The three headers are kept in globals while a message is loaded.
 *
 * The values of the file are little-endian, but its four-character magics are compared as
 * big-endian words ('MESG' is 0x4d455347). An INF1 entry is the offset of its text in the DAT1
 * section's data, followed (in files whose entries are 0x0c bytes, `has_attributes`) by six
 * bytes of attributes. A message's text runs to the next message's, or to the end of DAT1.
 *
 * The derived class's vtable: the destructor, the deleting destructor, slot 2 the address of
 * the buffer and slot 3 its size. */
#ifndef CLEAN_MAIN_BMG_FILE_H
#define CLEAN_MAIN_BMG_FILE_H

#include "types.h"

#define BMG_FILE_PATH_SIZE 0x3f
#define BMG_FILE_FS_FILE_SIZE 0x48

/* An INF1 entry (0x0c bytes with attributes, else only the offset). */
typedef struct BmgEntry {
    u32 text_offset;  /* 0x00: from the start of DAT1's data */
    u8 attributes[6]; /* 0x04 */
    u8 unk_0a[2];
} BmgEntry;

typedef struct BmgFile {
    const void *vtable;                /* 0x00: data_020e3d34, or a derived class's */
    u8 has_attributes;                 /* 0x04: the entries are 0x0c bytes (else 4) */
    char path[BMG_FILE_PATH_SIZE];     /* 0x05 */
    u8 fs_file[BMG_FILE_FS_FILE_SIZE]; /* 0x44: NitroSDK's FSFile */
    u8 open;                           /* 0x8c */
    u8 index;                          /* 0x8d: the message loaded */
    u8 unk_8e[2];
    BmgEntry entry;  /* 0x90: its INF1 entry */
    u32 text_offset; /* 0x9c: its text's offset in DAT1's data */
    u32 text_size;   /* 0xa0: and size in bytes */
} BmgFile;

/* The file's header (data_021f446c). */
typedef struct BmgHeader {
    u32 magic;    /* 0x00: 'MESG' */
    u32 type;     /* 0x04: 'bmg1' */
    u32 size;     /* 0x08 */
    u32 sections; /* 0x0c: 2 */
    u8 encoding;  /* 0x10 */
    u8 unk_11[11];
    u32 unk_1c; /* 0x1c */
} BmgHeader;

/* The INF1 section's header (data_021f4458). */
typedef struct BmgInfoHeader {
    u32 magic;      /* 0x00: 'INF1' */
    u32 size;       /* 0x04: the section's, header included */
    u16 count;      /* 0x08: the messages */
    u16 entry_size; /* 0x0a */
    u16 unk_0c;     /* 0x0c: 0 */
    u8 unk_0e;      /* 0x0e */
    u8 unk_0f[5];
} BmgInfoHeader;

/* The DAT1 section's header (data_021f4428; 0x0c bytes are read). */
typedef struct BmgDataHeader {
    u32 magic; /* 0x00: 'DAT1' */
    u32 size;  /* 0x04: the section's, its 8-byte head included */
    u32 unk_08;
} BmgDataHeader;

void *BmgFile_Entry(BmgFile *file);
int BmgFile_ReadText(BmgFile *file);
int BmgFile_ReadEntryWithAttributes(BmgFile *file);
int BmgFile_ReadEntryOffset(BmgFile *file);
int BmgFile_ReadDataHeader(BmgFile *file);
int BmgFile_ReadInfoHeader(BmgFile *file);
int BmgFile_ReadHeader(BmgFile *file);
void BmgFile_Clear(BmgFile *file);
int BmgFile_LoadMessage(BmgFile *file, const u8 *index);
void BmgFile_Close(void *file);
unsigned char BmgFile_Open(BmgFile *file, const char *path);
void *BmgFile_Destruct(void *file);
void *BmgFile_Delete(void *file);
void *BmgFile_DestructSlot(void *file);
BmgFile *BmgFile_Construct(BmgFile *file, unsigned char has_attributes);
int BmgFile_ReadU8(const u8 *value);
int BmgFile_ReadU16(const u16 *value);
int BmgFile_ReadU32(const s32 *value);
unsigned int BmgFile_ReadMagic(const u32 *value);

#endif
