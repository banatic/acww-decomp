/* func_020728f8 @ 0x020728f8, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    unsigned long long v[0x40];
} Block512;
typedef struct {
    u16 v[6];
} Arr6;
typedef struct {
    u16 v[10];
} Arr10;

typedef struct {
    Block512 block;
    u16 unk_200;
    Arr6 arr202;
    u16 unk_20E;
    Arr6 arr210;
    s8 unk_21C;
    u8 unk_21D;
    Arr10 arr21e;
    u8 unk_232;
} UnkStruct_020728f8;

void func_020728f8(UnkStruct_020728f8 *dst, const UnkStruct_020728f8 *src)
{
    dst->block = src->block;
    dst->unk_200 = src->unk_200;
    dst->arr202 = src->arr202;
    dst->unk_20E = src->unk_20E;
    dst->arr210 = src->arr210;
    dst->unk_21C = src->unk_21C;
    dst->unk_21D = src->unk_21D;
    dst->arr21e = src->arr21e;
    dst->unk_232 = src->unk_232;
}
