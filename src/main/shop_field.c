/* shop_field: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020afe94 @ 0x020afe94, 0xf0 bytes, Thumb
 * func_020afdc8 @ 0x020afdc8, 0xcc bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned short unk_00;
} UnkStruct_020afdc8;

typedef struct {
    void *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} UnkStruct_020afdc8_2;

extern u8 data_020e54a8;
extern int func_020b65c4(void);
extern int data_021c80bc;
extern u16 *func_0204f5e0(int a, int b, int c, int d, int e, int f);
extern int func_0204bc90(int object);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int a, int x, int y, int z);
extern int func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(int a, int b);
extern int func_ov004_0223bb14(int);
extern void func_0200467c(int a);
extern int func_0204bd08(u16 *p);
extern int func_0204f538(int a, void *b, int x, int y, int e);
extern int data_021f49f4;
extern UnkStruct_020afdc8 *func_02037e0c(void *obj, int x, int y, int k);
extern int func_0204bcdc(void *);
extern int func_0204bc64(UnkStruct_020afdc8 *e);

void func_020afe94(int x, int y, int p2, int p3)
{
    unsigned int ok;
    int g;
    u16 *q;
    int h;
    int hx;
    int hy;
    u16 v;

    ok = (data_020e54a8 == 0) ? 1 : 0;
    if (ok != 0) {
        return;
    }

    if (p2 != func_020b65c4()) {
        return;
    }

    g = data_021c80bc;
    hx = x >> 4;
    hy = y >> 4;
    q = func_0204f5e0(g, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    if (q == 0) {
        return;
    }

    if (func_0204bc90((int) q) != 0) {
        h = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
        if (h != 0) {
            func_ov004_0223bb14((int) func_ov004_0223cd78(func_ov004_0223ce84(), h));
        }
        if (p3 != 0) {
            func_0200467c(0x2e);
        }
        return;
    }

    if (func_0204bd08(q) == 0) {
        return;
    }

    ok = 0;
    v = *q;
    if (v >= 0x1000 && v <= 0x10ff) {
        ok = 1;
    }

    if (ok == 0) {
        ok = (v >= 0x151f && v <= 0x151f) ? 1 : 0;
        if (ok == 0) {
            func_0204f538(g, &data_021f49f4, x, y, 0);
        }
    }

    if (p3 != 0) {
        func_0200467c(0x2e);
    }
}

void func_020afdc8(UnkStruct_020afdc8 *self, int p1, int p2)
{
    void *obj;
    int y, x;
    UnkStruct_020afdc8 *e;
    int ok;
    int flag;
    unsigned int z = 0;

    flag = ((*(volatile unsigned char *) &data_020e54a8) == 0) ? 1 : 0;
    if (flag != 0) {
        return;
    }
    if (func_020b65c4() != p1) {
        return;
    }
    if ((*(UnkStruct_020afdc8_2 * *) &data_021c80bc) == 0) {
        return;
    }
    if ((*(UnkStruct_020afdc8_2 * *) &data_021c80bc)->unk_04 > z && (*(UnkStruct_020afdc8_2 * *) &data_021c80bc)->unk_08 > z && (*(UnkStruct_020afdc8_2 * *) &data_021c80bc)->unk_00 != 0) {
        obj = (*(UnkStruct_020afdc8_2 * *) &data_021c80bc)->unk_00;
    } else {
        obj = 0;
    }
    if (obj == 0) {
        return;
    }
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            e = func_02037e0c(obj, x, y, 0);
            if (e == 0) {
                continue;
            }
            if (func_0204bcdc(e) != 0) {
                int a = func_0204bc64(e);
                ok = (a == func_0204bc64(self)) ? 1 : 0;
            } else {
                ok = (e->unk_00 == self->unk_00) ? 1 : 0;
            }
            if (ok == 0) {
                continue;
            }
            func_020afe94(x, y, p1, p2);
            return;
        }
    }
}
