/* town_place: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02048e4c @ 0x02048e4c, 0x8 bytes, Thumb
 * func_02048e34 @ 0x02048e34, 0x16 bytes, Thumb
 * func_02048db8 @ 0x02048db8, 0x7c bytes, Thumb
 * func_02048d2c @ 0x02048d2c, 0x8c bytes, Thumb
 * func_02048cb8 @ 0x02048cb8, 0x74 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u16 unk_00;
} Entry;

typedef struct {
    int x;
    int y;
} Pair;

typedef struct Pair_02048d2c {
    int a;
    int b;
} Pair_02048d2c;

typedef struct {
    int a;
    int b;
} Pair_02048cb8;

extern int func_0204edd0(int, int, int);
extern Entry *func_0204f5e0(int ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204f800(int *out0, int *out1, int a, int b, int c, int d);
extern int func_020644cc(int);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_020b65c4(void);
extern int func_0204f538(void *, unsigned short *, int, int, int);
extern void func_0204f380(void *, int, int);
extern int func_0204f31c(void *, int, int);
extern void func_0205f9d4(int, int, int, unsigned short, int);

int func_02048e4c(int argument0, int argument1, int argument2)
{
    return func_0204edd0((int) argument0, (int) argument1, (int) argument2);
}

int func_02048e34(int argument0, int argument1, int argument2)
{
    int r4 = 0;
    if (func_0204edd0((int) argument0, (int) argument1, (int) argument2) != 0) {
        r4 = 1;
    }
    return r4;
}

int func_02048db8(int p0, Pair *out, int ctx, int cx, volatile int cz, int (*cb)(int, int, int))
{
    int czl;
    int count;
    int x, z;
    Entry *e;
    int out0, out1;

    count = 0;
    z = 0;
    czl = cz;
    for (; z < 16; z++) {
        for (x = 0; x < 16; x++) {
            e = func_0204f5e0(ctx, cx, czl, x, z, 0);
            if (e == 0) {
                continue;
            }
            if (e->unk_00 != 0xfff1) {
                continue;
            }
            func_0204f800(&out0, &out1, cx, czl, x, z);
            if (cb(ctx, out0, out1) != 0) {
                out->x = out0;
                out->y = out1;
                out++;
                count++;
            }
        }
    }
    return count;
}

inline Pair_02048d2c *inline_fn(Pair_02048d2c *arg0)
{
    return arg0;
}

int func_02048d2c(void *a0, void *obj, int count, Pair_02048d2c *arr, unsigned short arg5, int arg6)
{
    int ret = -1;
    Pair_02048d2c *ptr;
    Pair_02048d2c *p = arr;
    if (count > 0) {
        ret = func_020644cc(count);
        p = inline_fn(p + ret);
        if (func_02073d90(data_020ccf94) != 0) {
            goto update;
        }
        {
            unsigned short tmp = arg5;
            ptr = p;
            func_0204f538(obj, &tmp, p->a, p->b, 0);
            if (arg6 != 0) {
                func_0204f380(obj, p->a, ptr->b);
            } else {
                func_0204f31c(obj, p->a, p->b);
            }
        }
        goto end;
    update: {
        int v = func_020b65c4();
        func_0205f9d4((signed char) p->a, (signed char) p->b, v, arg5, arg6);
    }

    end:;
    }
    return ret;
}

int func_02048cb8(void *a0, void *a1, void *a2, int a3, unsigned short a4, int (*a5)(int, int, int), int a6)
{
    Pair_02048cb8 arr[0x100];
    Pair_02048cb8 *p = arr;
    int flag = 0;
    int x;

    do {
        p->a = 0;
        p->b = 0;
        p++;
    } while (p != arr + 0x100);

    x = func_02048db8((int) a0, (Pair *) arr, (int) a1, (int) a2, a3, a5);
    if (func_02048d2c(a0, a1, x, (Pair_02048d2c *) arr, a4, a6) >= 0) {
        flag = 1;
    }
    return flag;
}
