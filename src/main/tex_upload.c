/* tex_upload: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020578ec @ 0x020578ec, 0x1e bytes, Thumb
 * func_020578d4 @ 0x020578d4, 0x18 bytes, Thumb
 * func_020577c8 @ 0x020577c8, 0x10c bytes, Thumb
 * func_02057778 @ 0x02057778, 0x50 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char data[0x1c];
} Struct1C;

typedef struct Res {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[0x2c - 0xc];
    u32 unk_2C;
    u8 pad_30[0x34 - 0x30];
    u16 unk_34;
    u8 pad_36[0x42 - 0x36];
    u16 unk_42;
} Res;

extern void *func_020ba01c(void *p);
extern void func_020b9ec4(void *ptr);
extern int func_02057ac0(int a);
extern int func_020579f0(Res *r, int i);
extern int func_02057988(Res *r, int i);
extern int func_02057918(Res *r, int i);
extern int func_020b9f80(void *p, int a, int b, int c, int d);
extern int func_020b9f30(void *p, int a, int b, int c, int d);
extern int func_02057a40(int, const char *);
extern int func_020579b8(int, const char *);

Struct1C *func_020578ec(Struct1C *param)
{
    Struct1C *p;
    Struct1C *end;

    p = param;
    end = param + 2;
    do {
        func_020ba01c(p);
        p++;
    } while (p != end);
    return param;
}

void *func_020578d4(void *ptr)
{
    func_020b9ec4(ptr);
    func_020b9ec4((char *) ptr + 0x1c);
    return ptr;
}

int func_020577c8(void *p0, Res *rs, int i2, int i3, Res *rs2, int i5, u32 i6)
{
    u8 *a;
    u8 *b;
    u8 *c;
    u8 *d;
    u32 v;
    u32 j5, j6;
    int h;
    int e;
    int f;

    {
        u8 *p = (u8 *) rs + 0x3c;
        u16 stride;
        u32 off = rs->unk_42;
        stride = *(u16 *) (p + off);
        a = p + off + 4 + stride * i2;
    }
    {
        u8 *p = (u8 *) rs + rs->unk_34;
        u16 stride;
        u32 off = *(u16 *) (p + 6);
        stride = *(u16 *) (p + off);
        b = p + off + 4 + stride * i3;
    }

    j5 = i5;
    c = 0;
    if (j5 != -1) {
        u8 *p = (u8 *) rs2 + 0x3c;
        u16 stride;
        u32 off = *(u16 *) ((u8 *) rs2 + 0x42);
        stride = *(u16 *) (p + off);
        c = p + off + 4 + stride * j5;
    }

    j6 = i6;
    if (j6 == -1) {
        d = 0;
    } else {
        u8 *p = (u8 *) rs2 + rs2->unk_34;
        u16 stride;
        u32 off = *(u16 *) (p + 6);
        stride = *(u16 *) (p + off);
        d = p + off + 4 + stride * j6;
    }

    if (a != 0) {
        func_02057ac0(*(int *) a);
        v = *(u32 *) a + (u16) rs->unk_08;
        if (c != 0) {
            h = func_020579f0(rs2, i5);
            e = func_02057ac0(*(int *) c);
            v = v & 0xffff;
            if (func_020b9f80(p0, h, v << 3, e, 2) == 0) {
                return 0;
            }
        }
        if (b != 0) {
            if (d != 0) {
                e = func_02057988(rs2, i6);
                f = func_02057918(rs2, i6);
                if (func_020b9f30((u8 *) p0 + 0x1c, e, (*(u16 *) b + (u16) rs->unk_2C) << 3, f, 3) == 0) {
                    func_020b9ec4(p0);
                    return 0;
                }
            }
        }
    }
    return 1;
}

int func_02057778(int a, int b, const char *c, const char *d, int e, int f, int g)
{
    int x, y;

    if (c != 0) {
        x = func_02057a40(b, c);
    } else {
        x = -1;
    }

    if (d != 0) {
        y = func_020579b8(b, d);
    } else {
        y = -1;
    }

    return func_020577c8((void *) a, (Res *) b, x, y, (Res *) e, f, g);
}
