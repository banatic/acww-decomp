/* shop_display_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0224657c @ 0x0224657c, 0x1a bytes, Thumb
 * func_ov004_022464f0 @ 0x022464f0, 0x8c bytes, Thumb
 * func_ov004_02246378 @ 0x02246378, 0x178 bytes, Thumb
 * func_ov004_0224632c @ 0x0224632c, 0x4c bytes, Thumb
 * func_ov004_0224627c @ 0x0224627c, 0xb0 bytes, Thumb
 */

#include "types.h"

extern int func_020b65c4(void);
extern void func_ov004_02246598(char *self);
extern int func_020b6744(unsigned int code);
extern int func_020af83c(void *a, void *b);
extern int func_020adf8c(void *a, void *b);
extern int func_020ae8cc(void *a, void *b);
extern unsigned char data_021f395c[];
extern unsigned char data_021f3b30[];
extern unsigned char data_021f3b44[];
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern u16 func_0204bc50(int a, int b);
extern void __register_global_object(void *o, void *destructor, void *n);
extern void func_020051b0(void *p);
extern void *func_0204f5e0(void *g, int qx, int qy, int rx, int ry, int k);
extern int func_0204bc90(void *p);
extern int func_0204bd08(void *p);
extern void *func_ov004_0223cd50(void);
extern u16 *func_ov004_0223cc10(void *a, int x, int y, int k);
extern int func_ov004_0220fde0(void *p);
extern void *data_021c80bc;
extern u16 data_ov004_0225ff04;
extern u16 data_ov004_0225ff08;
extern int data_ov004_0225ff10;
extern int data_ov004_0225ff14;
extern int data_ov004_0225ff18;
extern int data_ov004_0225ff24;
extern long *func_ov004_022468b0(void);
extern void *func_020af854(void *a, int b, unsigned short *c);
extern int func_ov004_02246848(unsigned short *t);

int func_ov004_0224657c(char *self)
{
    if (func_020b65c4() != 0x1f) {
        func_ov004_02246598(self);
    }
    return 1;
}

int func_ov004_022464f0(unsigned short *p)
{
    int k, f;

    k = func_020b65c4();
    if (func_020b6744((unsigned int) k) != 0) {
        return func_020af83c((void *) data_021f395c, p) == -1 ? 0 : 1;
    }
    if (k == 0xa) {
        k = 1;
        f = 0;
        if (*p >= 0x3e04 && *p <= 0x3e23) {
            f = k;
        }
        if (f == 0) {
            if (func_020ae8cc((void *) data_021f3b44, p) == -1) {
                k = 0;
            }
        }
        return k;
    }
    return func_020adf8c((void *) data_021f3b30, p) == -1 ? 0 : 1;
}

u16 *func_ov004_02246378(int x, int y)
{
    // DECLS
    u16 *it;
    u16 *e;
    int qx;
    int qy;
    int t1;
    int ok;
    // ENDDECLS
    u16 buf[6];

    if ((data_ov004_0225ff14 & 1) == 0) {
        data_ov004_0225ff04 = 0xfff1;
        __register_global_object(&data_ov004_0225ff04, ((void *) &func_020051b0), &data_ov004_0225ff24);
        data_ov004_0225ff14 |= 1;
    }
    if (data_021c80bc != 0) {
        qx = x >> 4;
        qy = y >> 4;
        it = (u16 *) func_0204f5e0(data_021c80bc, qx, qy, x - (qx << 4), y - (qy << 4), 0);
        if (it != 0) {
            if (func_0204bcdc(it) != 0) {
                buf[1] = 0xfff1;
                t1 = func_0204bc64(it);
                ok = (t1 == func_0204bc64(&buf[1])) ? 1 : 0;
            } else {
                ok = (*it == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                if (func_0204bc90(it) != 0) {
                    e = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
                    if (e == 0) {
                        return &data_ov004_0225ff04;
                    }
                    if ((data_ov004_0225ff10 & 1) == 0) {
                        data_ov004_0225ff08 = 0xfff1;
                        __register_global_object(&data_ov004_0225ff08, ((void *) &func_020051b0), &data_ov004_0225ff18);
                        data_ov004_0225ff10 |= 1;
                    }
                    data_ov004_0225ff08 = func_0204bc50(func_ov004_0220fde0(e), 0);
                    if (func_ov004_022464f0((unsigned short *) (&data_ov004_0225ff08)) != 0) {
                        return &data_ov004_0225ff08;
                    }
                } else if (func_0204bd08(it) != 0) {
                    if (func_0204bcdc(it) != 0) {
                        buf[2] = 0x1547;
                        t1 = func_0204bc64(it);
                        ok = (t1 == func_0204bc64(&buf[2])) ? 1 : 0;
                    } else {
                        ok = (*it == 0x1547) ? 1 : 0;
                    }
                    if (ok == 0 && func_ov004_022464f0((unsigned short *) it) != 0) {
                        return it;
                    }
                }
            }
        }
    }
    return &data_ov004_0225ff04;
}

// The row base is computed inside the inner loop.
int func_ov004_0224632c(int a, int b)
{
    long *base = func_ov004_022468b0();
    int n = 0, y, x;
    long *row;
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            row = (long *) ((char *) base + y * 0x40);
            if (row[x] == 0x22) {
                if (x == a && y == b) {
                    return n;
                }
                n++;
            }
        }
    }
    return -1;
}

int func_ov004_0224627c(int *oj, int *oi, int sel)
{
    unsigned short t[2];
    int *base;
    int key;
    int want;
    int seen;
    unsigned int k;
    int i;
    int j;
    int *row;

    base = (int *) func_ov004_022468b0();
    t[0] = 0xfff1;
    func_020af854((void *) data_021f395c, sel, &t[0]);
    key = func_ov004_02246848(&t[0]);
    want = 0;
    for (k = 0; k < 0x25; k++) {
        t[1] = 0xfff1;
        func_020af854((void *) data_021f395c, k, &t[1]);
        if (sel == k) {
            break;
        }
        if (key == func_ov004_02246848(&t[1])) {
            want++;
        }
    }
    seen = 0;
    for (i = 0; i < 0x10; i++) {
        for (j = 0, row = base + i * 0x10; j < 0x10; j++) {
            if (key == row[j]) {
                if (seen == want) {
                    *oj = j;
                    *oi = i;
                    return 1;
                }
                seen++;
            }
        }
    }
    *oi = -1;
    *oj = *oi;
    return 0;
}
