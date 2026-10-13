/* func_0202c824 @ 0x0202c824, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Pair {
    u32 a;
    u32 b;
} Pair;

extern signed char data_020c8958[];

extern void *func_0209b91c(void *h);
extern int func_0209b914(void *h);
extern int func_0209bd44(void *x);
extern int func_0209bba0(void *x);
extern int func_0209bd04(void *x);
extern void *func_0209b908(void *h);
extern int func_020951bc(void *o);
extern int func_0209bc40(void *x);
extern int func_0209b8d0(int kind);
extern u16 *func_0209b8c4(void *h);
extern Pair *func_0209b8c8(void *h);
extern int func_0209e3ac(void *p2, Pair *pr, int m);
extern int func_0209e350(Pair *pr, void *p2);

int func_0202c824(void *p0, void *h, void *p2, u8 f)
{
    void *x;
    int idx;
    int kind;
    Pair *pr;
    int ok;
    int lim;
    u16 *q;
    int res;

    x = func_0209b91c(h);
    idx = func_0209b914(h);
    if (func_0209bd44(x) == 0) {
        goto fail;
    }
    if (func_0209bba0(x) != 0) {
        goto fail;
    }
    if (func_0209bd04(x) != 0) {
        goto fail;
    }
    if (idx == 0) {
        goto fail;
    }
    if (func_020951bc(func_0209b908(h)) == 0) {
        goto fail;
    }
    kind = func_0209bc40(x);
    if (idx >= func_0209b8d0(kind)) {
        goto fail;
    }

    if (kind == 0) {
        q = func_0209b8c4(h);
        ok = 0;
        if (*q >= 0x12b0 && *q <= 0x12e7) {
            ok = 1;
        }
        if (ok == 0) {
            goto pass;
        }
    }
    if (kind != 1) {
        goto fail;
    }
    q = func_0209b8c4(h);
    ok = 0;
    if (*q >= 0x12e8 && *q <= 0x131f) {
        ok = 1;
    }
    if (ok != 0) {
        goto fail;
    }

pass:
    pr = func_0209b8c8(h);
    if (f == 0) {
        return 1;
    }
    if (*(long long *) pr == 0) {
        goto fail;
    }
    res = func_0209e3ac(p2, pr, 0x3f);
    if (res == 1) {
        if (idx < 5) {
            lim = data_020c8958[idx];
        } else {
            lim = 0;
        }
        if (lim <= 0) {
            goto fail;
        }
        if (func_0209e350(pr, p2) < lim) {
            goto fail;
        }
        return 1;
    }
    if (res != -1) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
