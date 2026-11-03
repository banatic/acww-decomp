/* snowman_4: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221a538 @ 0x0221a538, 0xd0 bytes, Thumb
 * func_ov003_0221a4f0 @ 0x0221a4f0, 0x48 bytes, Thumb
 * func_ov003_0221a484 @ 0x0221a484, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct {
    s16 dx;
    s16 dy;
} UnkStruct_0221a538;

typedef struct {
    int a, b, c;
} Pt;

extern int data_021c80bc;
extern UnkStruct_0221a538 data_ov003_0223660c[];
extern u16 func_0204bb14(void *a);
extern void func_0204f818(int *x, int *y, void *pos);
extern void func_0204f794(Pt *p, int x, int y);
extern int func_ov003_0221a68c(Pt *p);
extern int func_020644cc(int n);
extern int func_ov003_0221a608(void *a, Pt *p, int c);
extern int func_0204f538(int a, unsigned short *b, int c, int d, int e);
extern int func_0204bcdc(unsigned short *arg);
extern int func_0204bc64(unsigned short *arg);
extern int func_0204bd08(unsigned short *arg);
extern void func_0203a76c(unsigned short value);

int func_ov003_0221a538(void *a, void *pos, int c)
{
    volatile u16 v;
    int x, y;
    Pt tmp;
    Pt tmp2;
    u8 mask;
    int n;
    unsigned int i;
    int k;
    int j;
    unsigned int m;

    if (data_021c80bc != 0) {
        v = func_0204bb14(a);
        func_0204f818(&x, &y, pos);
        mask = 0;
        n = 0;
        for (i = 0; i < 8; i++) {
            UnkStruct_0221a538 *e = &data_ov003_0223660c[i];
            func_0204f794(&tmp, x + e->dx, y + e->dy);
            if (func_ov003_0221a68c(&tmp) != 0) {
                mask = (u8) (mask | (1 << i));
                n++;
            }
        }
        if (n != 0) {
            k = func_020644cc(n);
            j = 0;
            for (m = 0; m < 8; m++) {
                if (((mask >> m) & 1) != 0) {
                    if (j == k) {
                        func_0204f794(&tmp2, x + data_ov003_0223660c[m].dx, y + data_ov003_0223660c[m].dy);
                        if (func_ov003_0221a608(a, &tmp2, c) != 0) {
                            return 1;
                        } else {
                            return 0;
                        }
                    }
                    j++;
                }
            }
        }
    }
    return 0;
}

int func_ov003_0221a4f0(int param)
{
    unsigned short s;
    int a, b;
    int v;

    v = data_021c80bc;
    if (v != 0) {
        func_0204f818(&a, &b, (void *) param);
        s = 0xfff1;
        if (func_0204f538(v, &s, a, b, 0) != 0) {
            return 1;
        }
    }
    return 0;
}

int func_ov003_0221a484(unsigned short *arg)
{
    int ret;
    if (func_0204bcdc(arg) != 0) {
        unsigned short local = 0xfff1;
        ret = (func_0204bc64(arg) == func_0204bc64(&local)) ? 1 : 0;
    } else {
        ret = (*arg == 0xfff1) ? 1 : 0;
    }
    if (ret == 0 && (func_0204bd08(arg) != 0 || func_0204bcdc(arg) != 0)) {
        func_0203a76c(*arg);
        return 1;
    }
    return 0;
}
