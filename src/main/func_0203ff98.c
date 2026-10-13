/* func_0203ff98 @ 0x0203ff98, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 v;
} UnkStruct_0203ff98;

typedef struct {
    u16 a;
    u16 b;
    unsigned char unk_04[12];
    unsigned char unk_10[12];
} Src;
typedef struct {
    u16 a;
    u16 b;
    UnkStruct_0203ff98 p1;
    UnkStruct_0203ff98 p2;
} Dst;

extern UnkStruct_0203ff98 func_0204019c(void *s, void *c, UnkStruct_0203ff98 p, int n);
extern UnkStruct_0203ff98 func_02040180(void *s, void *c, UnkStruct_0203ff98 p, int n);

int func_0203ff98(Dst *dst, Src *src, void *c, UnkStruct_0203ff98 p)
{
    UnkStruct_0203ff98 r1, r2;
    int ok = 0;
    u32 hi;
    int n;
    hi = p.v & 0xffff0000;
    n = src->a;
    dst->a = (u16) n;
    dst->b = src->b;
    r1 = func_0204019c(src->unk_04, c, p, n);
    dst->p1 = r1;
    if (dst->p1.v != 0 && (dst->p1.v & 0xffff0000) <= hi) {
        r2 = func_02040180(src->unk_10, c, p, n);
        dst->p2 = r2;
        if (dst->p2.v != 0 && (dst->p2.v & 0xffff0000) >= hi) {
            ok = 1;
        }
    }
    return ok;
}
