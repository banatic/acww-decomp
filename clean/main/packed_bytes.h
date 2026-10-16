/* Values stored byte by byte in the packed data the systems of a multiplayer session exchange
 * (message headers, shared records, saved states of the field actors, overlay 3's records):
 *
 *   16-bit values, little-endian, copied two bytes at a time with MI_CpuCopy8 (several copies
 *   of the same routine, each used for one kind of value);
 *   a 20-bit value with a 4-bit tag in 3 bytes: the tag in the high nibble of byte 0, then the
 *   value's bits 16-19 in its low nibble, bits 8-15 and bits 0-7;
 *   a point in 5 bytes: x's bits 8-15 and 0-7, then z as a 20-bit value tagged with x's bits
 *   16-19 (so both are 20 bits);
 *   a scene (low 6 bits) and a 2-bit number (top 2 bits) in one byte: a message header's
 *   source byte (the sender's slot) or an item's scene and flag. */
#ifndef CLEAN_MAIN_PACKED_BYTES_H
#define CLEAN_MAIN_PACKED_BYTES_H

#include "types.h"

/* What PackedBytes_WriteU16 and PackedBytes_WriteHalf receive: the ROM's code takes three
 * words (r1-r3) and stores the first two bytes of them, which hold the 16-bit value the
 * callers put in the first. */
typedef struct PackedBytesHalf {
    u32 value; /* only its low 16 bits are stored */
    u32 unused_04;
    u32 unused_08;
} PackedBytesHalf;

u16 PackedBytes_ReadU16(const u8 *bytes);
void PackedBytes_WriteU16(u8 *bytes, PackedBytesHalf value);
u16 PackedBytes_ReadItem(const u8 *bytes);
void PackedBytes_WriteItem(u8 *bytes, int item, ...);
int PackedBytes_ReadS16Wide(const u8 *bytes);
void PackedBytes_WriteHalf(u8 *bytes, PackedBytesHalf value);
s16 PackedBytes_ReadS16(const u8 *bytes);
void PackedBytes_WriteS16(u8 *bytes, int value);

void PackedBytes_UnpackPointAndValue(const u8 *packed, u32 *x, s32 *z, u32 *value, u8 *tag);
void PackedBytes_PackPointAndValue(u8 *packed, s32 x, s32 z, s32 value, u8 tag);
void PackedBytes_UnpackPoint(const u8 *packed, u32 *x, u32 *z);
void PackedBytes_PackPoint(u8 *packed, s32 x, s32 z);
void PackedBytes_UnpackValue(const u8 *packed, u32 *value, u8 *tag);
void PackedBytes_PackValue(u8 *packed, s32 value, int tag);

void PackedBytes_SplitScene(const u8 *packed, u8 *scene, u8 *number);
void PackedBytes_JoinScene(u8 *packed, u8 scene, u8 number);

#endif
