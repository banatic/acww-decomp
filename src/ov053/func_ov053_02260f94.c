/* func_ov053_02260f94 @ 0x02260f94, 0xfc bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} Entry12;

extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern void func_0201b044(void *p, Entry12 *e);
extern int func_02019d0c(void *p, int a, int b, int tv, int tv2, int c800, int z1, int z2, int z3, u16 halfw, int z4);
extern void func_ov053_02261524(void *self, int v);

extern Entry12 data_ov053_02261814[];
extern Entry12 data_ov053_0226181c[];
extern u16 data_020c80f8;

int func_ov053_02260f94(void *self)
{
    u8 *p = (u8 *) self;
    Entry12 buf;
    Entry12 *src;
    int idx, t1, t2;

    if (func_02019e00(p + 0x564) == 6) {
        idx = p[0x719];
        src = &data_ov053_02261814[idx];
        buf.a = src->a;
        buf.b = src->b;
        buf.c = src->c;
        func_0201b044(p + 0x350, &buf);
        if (func_02019de8(p + 0x564) != 0) {
            p[0x719] = p[0x719] + 1;
            idx = p[0x719];
            t2 = data_ov053_0226181c[idx].a;
            t1 = data_ov053_02261814[idx].a;
            func_02019d0c(p + 0x564, 6, 1, t1, t2, 0x800, 0, 0, 0, data_020c80f8, 0);
            if (p[0x719] >= 2) {
                func_ov053_02261524(self, 2);
            }
        }
    }

    if (func_02019e00(p + 0x564) == 3) {
        if (func_02019de8(p + 0x564) != 0) {
            idx = p[0x719];
            t2 = data_ov053_0226181c[idx].a;
            t1 = data_ov053_02261814[idx].a;
            func_02019d0c(p + 0x564, 6, 1, t1, t2, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    }

    return 1;
}
