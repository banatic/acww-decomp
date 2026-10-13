/* func_020acc0c @ 0x020acc0c, 0x1c0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_020acc0c;
typedef struct {
    int w[12];
} Big48;

typedef struct {
    u8 pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
} UnkStruct_020acc0c_3;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020acc0c_2;

extern int func_020ad2c4(void);
extern void func_02034270(void *buf, UnkStruct_020acc0c *p, int a, int b);
extern int func_020341c8(void *buf, int a);
extern void func_0203423c(void *buf);
extern int func_020b66d8(void);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_020310c8(int a);
extern int func_0203f8d0(UnkStruct_020acc0c *out, UnkStruct_020acc0c *in);
extern void func_020e96c8(Big48 *g, int a, int b, int c);
extern void func_020e9774(Big48 *g, int a);
extern void func_02055e7c(void *g, UnkStruct_020acc0c_2 *w);

extern u8 data_020e54a8;
extern Big48 data_021fbe48;
extern Big48 data_021f4790;
extern UnkStruct_020acc0c_3 *data_021f471c;
extern int data_021f472c;
extern unsigned int data_020e40e0;

void func_020acc0c(UnkStruct_020acc0c *p, int amt, int a2, int a3)
{
    int ad;
    int y;
    char buf[0x40];
    char buf2[0x40];
    UnkStruct_020acc0c v1;
    UnkStruct_020acc0c v2;
    UnkStruct_020acc0c_2 w;
    int r4;
    unsigned int f;
    int d;
    int t;
    int u;
    int h;

    if (amt == 0) {
        return;
    }
    r4 = func_020ad2c4();
    y = 0;
    if (data_020e54a8 == 0) {
        f = 1;
    } else {
        f = y;
    }
    if (f != 0) {
        func_02034270(buf, p, 0, 0);
        y = func_020341c8(buf, 0);
        if (y > 0) {
            y = 0;
        }
        func_0203423c(buf);
    } else if (func_020b66d8() != 0) {
        func_02034270(buf2, p, 0, 0);
        y = func_020341c8(buf2, 0);
        func_0203423c(buf2);
    }
    d = p->y - y;
    if (d < 0) {
        ad = -d;
    } else {
        ad = d;
    }
    if (d != 0) {
        t = FX_Div(0x1f000, a2);
        r4 = r4 - (FX_MulFunc(ad, t) >> 12);
    }
    if (a3 != 0x1000) {
        r4 = (r4 * a3) >> 12;
    }
    if (r4 <= 1) {
        return;
    }
    if (d != 0) {
        t = FX_Div(0xfffff000, a2);
        u = FX_MulFunc(t, ad) + 0x1000;
        if (u >= 0xf33) {
            u = 0x1000;
        }
        amt = FX_MulFunc(amt, u);
    }
    if (amt <= 0) {
        return;
    }
    v1.x = p->x;
    v1.y = p->y;
    v1.z = p->z;
    v1.y = y + func_020310c8(0);
    h = func_0203f8d0(&v2, &v1);
    func_020e96c8(&data_021fbe48, v2.x, v2.y, v2.z);
    func_020e9774(&data_021fbe48, h);
    data_021f4790 = data_021fbe48;
    w.a = amt;
    w.b = 0x1000;
    w.c = amt;
    if (data_021f471c != 0) {
        data_021f471c->unk_0C &= 0xffe0ffff;
        data_021f471c->unk_0C |= (r4 & 0x1f) << 16;
        data_021f471c->unk_0C &= 0xc0ffffff;
        data_021f471c->unk_0C |= data_020e40e0 << 24;
        data_021f471c->unk_10 |= 0x3f1f0000;
    }
    func_02055e7c(&data_021f472c, &w);
    data_020e40e0 = data_020e40e0 + 1;
    if (data_020e40e0 > 0xb) {
        data_020e40e0 = 1;
    }
}
