/* func_02086760 @ 0x02086760, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Src {
    u16 f0;
    u16 arr[6];
    u8 b0;
    u8 b1;
} Src;

typedef struct Dst {
    u8 pad_00[0x2e];
    u16 f0;
    u16 arr[6];
    u8 b0;
    u8 b1;
} Dst;

struct Blk {
    u16 v[6];
};

void func_02086760(Dst *dst, const Src *src)
{
    u16 *pSrc;
    u16 *pDst;
    int count;

    dst->f0 = src->f0;
    *(struct Blk *) ((char *) dst + 0x30) = *(struct Blk *) ((char *) src + 2);
    dst->b0 = src->b0;
    dst->b1 = src->b1;
}