/* func_ov003_0222a578 @ 0x0222a578, 0xbc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    volatile u16 id;
    u16 pad_02;
    int pad_04;
} UnkStruct_0222a578;

typedef struct {
    u8 a;
    u8 pad_01;
    s16 b;
} UnkStruct_0222a578_2;

typedef struct {
    UnkStruct_0222a578_2 *p;
    int pad_04;
} UnkStruct_0222a578_3;

extern char *func_02060924(int a);
extern void func_02095764(UnkStruct_0222a578 *w, int x);
extern int func_ov003_0222799c(void *self, void *obj, int a, int b, int c);
extern int func_0200322c(void *self, void *obj);
extern int func_020e8b4c(int a, int b);
extern u8 data_020cb785[];
extern UnkStruct_0222a578_3 data_ov003_0223bf00[];

int func_ov003_0222a578(void *self, int p1, int p2, int p3)
{
    UnkStruct_0222a578 w;
    char *h;
    void *obj;
    UnkStruct_0222a578_3 *e;
    int ret, idx, k, q, lim;
    unsigned int ok;
    u16 lo, hi;

    ret = 0;
    h = func_02060924(0);
    if (h == 0) {
        return 0;
    }
    func_02095764(&w, p2);
    ok = 0;
    lo = w.id;
    hi = w.id;
    if (hi >= 0x1374 && lo <= 0x1374) {
        ok = 1;
    }
    if (ok) {
        idx = 0;
    } else if (lo >= 0x1375 && lo <= 0x1375) {
        idx = 1;
    } else {
        return 0;
    }
    obj = h + 8;
    k = data_020cb785[6 * p3];
    q = ((int) data_ov003_0223bf00[idx].p[k].a << 12) / 10;
    if (func_ov003_0222799c(self, obj, q, q, q) != 0) {
        lim = data_ov003_0223bf00[idx].p[k].b;
        if (func_020e8b4c(func_0200322c(self, obj), p1) <= lim) {
            ret = 1;
        }
    }
    return ret;
}
