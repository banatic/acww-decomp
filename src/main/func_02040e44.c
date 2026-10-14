/* func_02040e44 @ 0x02040e44, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef union {
    unsigned int u;
    u8 b[4];
} Key;
typedef struct {
    int lo, hi;
} Date;
typedef struct {
    u8 pad_00[0x17228];
    u8 flag;
} Cfg;

extern Cfg data_021dc7a8;
extern void func_0209e474(Date *d);
extern void MI_CpuCopy8(const void *src, void *dst, int len);
extern int func_0209ded0(void);
extern void func_0209e29c(Date *d, int n);
extern void func_0209e140(Date *d, int n);
extern int func_02040a90(Key k);
extern void *func_020409c8(void *a, int k);
extern void func_020408b8(void *obj, int id, Date *m);

void func_02040e44(void *a, int *b, int *c, Date *d)
{
    struct {
        Key key;
        Date t1, t2, t3, t4;
    } w;
    Cfg *cfg;
    int *slot;
    int k;
    int diff;
    void *obj;

    if (*c <= 0) {
        return;
    }
    cfg = (Cfg *) ((int) &data_021dc7a8);
    k = cfg->flag;
    slot = &(b - 1)[k];
    if (*slot == 0) {
        return;
    }
    w.t1.lo = 0;
    w.t1.hi = 0;
    w.t2.lo = 0;
    w.t2.hi = 0;
    func_0209e474(&w.t2);
    MI_CpuCopy8(&w.t2, &w.t1, 8);
    diff = k - func_0209ded0();
    if (diff >= 0) {
        func_0209e29c(&w.t1, diff);
    } else {
        func_0209e140(&w.t1, -diff);
    }
    w.key.b[3] = ((u8 *) &w.t1)[4];
    w.key.b[2] = ((u8 *) &w.t1)[3];
    if (func_02040a90(w.key) != 0) {
        return;
    }
    obj = func_020409c8(a, k);
    if (obj == 0) {
        return;
    }
    w.t3.lo = 0;
    w.t3.hi = 0;
    *slot = 0;
    *c = *c - 1;
    MI_CpuCopy8(d, &w.t3, 8);
    func_0209e29c(&w.t3, k);
    MI_CpuCopy8(&w.t3, &w.t4, 8);
    func_020408b8(obj, 0x3d, &w.t4);
}
