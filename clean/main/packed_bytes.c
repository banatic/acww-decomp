/* Values stored byte by byte in packed data (packed_bytes.h). */
#include "packed_bytes.h"

#include "clean.h"

#define POINT_SIZE 5         /* the bytes of a packed point */
#define Z_BIAS 0x80000       /* added to z before it is packed, so that it fits 20 bits unsigned */
#define HALF_SIZE 2          /* the bytes of a 16-bit value */
#define SCENE_MASK 0x3f      /* a scene byte's low 6 bits */
#define SCENE_NUMBER_SHIFT 6 /* and the 2-bit number above them */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_02077868: the 16-bit value at `bytes` (a message's payload length). */
u16 PackedBytes_ReadU16(const u8 *bytes)
{
    u16 value;
    MI_CpuCopy8(bytes, &value, HALF_SIZE);
    return value;
}
CLEAN_AS(func_02077868, PackedBytes_ReadU16)

/* func_02077880: stores a 16-bit value at `bytes` (a message's payload length). */
void PackedBytes_WriteU16(u8 *bytes, PackedBytesHalf value)
{
    u16 half = (u16) value.value;
    MI_CpuCopy8(&half, bytes, HALF_SIZE);
}
CLEAN_AS(func_02077880, PackedBytes_WriteU16)

/* func_02077898: the 16-bit value at `bytes` (an item). */
u16 PackedBytes_ReadItem(const u8 *bytes)
{
    u16 item;
    MI_CpuCopy8(bytes, &item, HALF_SIZE);
    return item;
}
CLEAN_AS(func_02077898, PackedBytes_ReadItem)

/* func_020778b0: stores the low 16 bits of `item` at `bytes`. Some callers pass more
 * arguments, which are not read. */
void PackedBytes_WriteItem(u8 *bytes, int item, ...)
{
    u16 half = (u16) item;
    MI_CpuCopy8(&half, bytes, HALF_SIZE);
}
CLEAN_AS(func_020778b0, PackedBytes_WriteItem)

/* func_020778c8: the signed 16-bit value at `bytes`, widened to an int (a sequence number). */
int PackedBytes_ReadS16Wide(const u8 *bytes)
{
    s16 value;
    MI_CpuCopy8(bytes, &value, HALF_SIZE);
    return value;
}
CLEAN_AS(func_020778c8, PackedBytes_ReadS16Wide)

/* func_020778e0: stores a 16-bit value at `bytes`, as PackedBytes_WriteU16 does. */
void PackedBytes_WriteHalf(u8 *bytes, PackedBytesHalf value)
{
    u16 half = (u16) value.value;
    MI_CpuCopy8(&half, bytes, HALF_SIZE);
}
CLEAN_AS(func_020778e0, PackedBytes_WriteHalf)

/* func_020778f8: the signed 16-bit value at `bytes` (an angle, a record's value). */
s16 PackedBytes_ReadS16(const u8 *bytes)
{
    s16 value;
    MI_CpuCopy8(bytes, &value, HALF_SIZE);
    return value;
}
CLEAN_AS(func_020778f8, PackedBytes_ReadS16)

/* func_02077910: stores the low 16 bits of `value` at `bytes`. */
void PackedBytes_WriteS16(u8 *bytes, int value)
{
    u16 half = (u16) value;
    MI_CpuCopy8(&half, bytes, HALF_SIZE);
}
CLEAN_AS(func_02077910, PackedBytes_WriteS16)

/* func_02077928: a point (z less its bias, so signed) and a tagged value, from 8 bytes. */
void PackedBytes_UnpackPointAndValue(const u8 *packed, u32 *x, s32 *z, u32 *value, u8 *tag)
{
    PackedBytes_UnpackPoint(packed, x, (u32 *) z);
    *z -= Z_BIAS;
    PackedBytes_UnpackValue(packed + POINT_SIZE, value, tag);
}
CLEAN_AS(func_02077928, PackedBytes_UnpackPointAndValue)

/* func_02077950: a point (z biased) and a tagged value into 8 bytes. */
void PackedBytes_PackPointAndValue(u8 *packed, s32 x, s32 z, s32 value, u8 tag)
{
    PackedBytes_PackPoint(packed, x, (s32) ((u32) z + Z_BIAS));
    PackedBytes_PackValue(packed + POINT_SIZE, value, tag);
}
CLEAN_AS(func_02077950, PackedBytes_PackPointAndValue)

/* func_02077978: a point's x and z (20 bits each) from 5 bytes. z is written first. */
void PackedBytes_UnpackPoint(const u8 *packed, u32 *x, u32 *z)
{
    u8 x_high;
    PackedBytes_UnpackValue(packed + 2, z, &x_high);
    *x = (u32) (x_high & 0xf) << 16 | (u32) packed[0] << 8 | packed[1];
}
CLEAN_AS(func_02077978, PackedBytes_UnpackPoint)

/* func_020779b8: the low 20 bits of x and z into 5 bytes; x's bits 16-19 tag z. */
void PackedBytes_PackPoint(u8 *packed, s32 x, s32 z)
{
    packed[0] = (u8) ((u32) x >> 8);
    packed[1] = (u8) x;
    PackedBytes_PackValue(packed + 2, z, (u8) (((u32) x >> 16) & 0xf));
}
CLEAN_AS(func_020779b8, PackedBytes_PackPoint)

/* func_020779d8: a 20-bit value and its 4-bit tag (unless `tag` is NULL) from 3 bytes. The tag
 * is written first, and the bytes are read after it. */
void PackedBytes_UnpackValue(const u8 *packed, u32 *value, u8 *tag)
{
    if (tag != NULL) {
        *tag = (u8) (packed[0] >> 4);
    }
    *value = (u32) (packed[0] & 0xf) << 16 | (u32) packed[1] << 8 | packed[2];
}
CLEAN_AS(func_020779d8, PackedBytes_UnpackValue)

/* func_02077a14: the low 20 bits of `value` and the low 4 bits of `tag` into 3 bytes. */
void PackedBytes_PackValue(u8 *packed, s32 value, int tag)
{
    packed[0] = (u8) (((u32) tag << 4 & 0xf0) | ((u32) value >> 16 & 0xf));
    packed[1] = (u8) ((u32) value >> 8);
    packed[2] = (u8) value;
}
CLEAN_AS(func_02077a14, PackedBytes_PackValue)

/* func_02077a34: a scene byte's scene and (unless `number` is NULL) its 2-bit number. The
 * number is written first, and the byte is read after it. */
void PackedBytes_SplitScene(const u8 *packed, u8 *scene, u8 *number)
{
    if (number != NULL) {
        *number = (u8) (*packed >> SCENE_NUMBER_SHIFT);
    }
    *scene = *packed & SCENE_MASK;
}
CLEAN_AS(func_02077a34, PackedBytes_SplitScene)

/* func_02077a54: a scene byte from the low 6 bits of `scene` and the low 2 bits of `number`. */
void PackedBytes_JoinScene(u8 *packed, u8 scene, u8 number)
{
    *packed = (u8) ((number << SCENE_NUMBER_SHIFT & 0xc0) | (scene & SCENE_MASK));
}
CLEAN_AS(func_02077a54, PackedBytes_JoinScene)
