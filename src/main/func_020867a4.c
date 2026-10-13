/* func_020867a4 @ 0x020867a4, 0x3a bytes, Thumb, module main
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
    u8 pad_00[0x1e];
    u16 f0;
    u16 arr[6];
    u8 b0;
    u8 b1;
} Dst;

struct Blk {
    u16 v[6];
};

extern void func_02095238(void *);

void func_020867a4(Dst *dst, const Src *src)
{
    dst->f0 = src->f0;
    *(struct Blk *) ((char *) dst + 0x20) = *(struct Blk *) ((char *) src + 2);
    dst->b0 = src->b0;
    dst->b1 = src->b1;
    func_02095238(dst);
}
