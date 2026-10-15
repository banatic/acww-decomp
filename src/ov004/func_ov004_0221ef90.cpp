/* func_ov004_0221ef90 @ 0x0221ef90, 0x2c4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off
struct UnkStruct_0221ef90_2 {
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void *v3();
    virtual void *v4();
    virtual void *v5();
    virtual void *v6();
    virtual void *v7();
    virtual void *v8();
    virtual void *v9();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual void *v25();
};

struct UnkStruct_0221ef90 {
    int x, y, z;
};

extern "C" {
extern void *func_020961a8(int k);
extern int func_0203ec98(void);
extern int func_02014868(void *p);
extern int FX_MulFunc(int a, int b);
extern void func_0204f818(int *x, int *y, int *v);
extern void *func_ov004_0223cd50(void);
extern int func_ov004_0223cc5c(void *a, int x, int y, int k);
extern void *func_ov004_0223cc10(void *a, int x, int y, int k);
extern void *func_020b6590(void);
extern void *func_020b7524(void *a, int b, int c);
extern int func_020b758c(void *a, int *w);
extern int func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(int a, int b);
extern int func_ov004_0220e758(void *e, int *x, int *y, int a, int b);
extern int func_0207f318(void *a, int *p, void *b, void *c);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern u16 data_021fbe40[];
extern const short FX_SinCosTable_[];
}

static __inline int chk(u16 *p, u16 k)
{
    u16 t;
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t = k;
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) &t)) ? 1 : 0;
    }
    return (*p == k) ? 1 : 0;
}

extern "C" int func_ov004_0221ef90(void *self)
{
    // DECLS
    int t;
    int flag;
    void *p;
    struct UnkStruct_0221ef90 *qv;
    int idx;
    void *e;
    // ENDDECLS
    volatile u16 id;
    int x, y;
    int x2, y2;
    int tx, ty;
    int v[3];
    int w[3];

    p = func_020961a8(4);
    t = (data_021f6c38 != 0 && data_021f6c34 != 0) ? 1 : 0;
    flag = (t != 0) ? 1 : 0;
    if (*(u8 *) ((char *) self + 0xa54) != 2) {
        return 0;
    }
    if (p == 0 || func_0203ec98() != 0 || func_02014868((char *) self + 0x618) != 0 ||
        ((data_021fbe40[1] & 1) == 0 && flag == 0)) {
        return 0;
    }
    qv = (struct UnkStruct_0221ef90 *) ((char *) p + 0x5c);
    v[0] = qv->x;
    v[1] = qv->y;
    v[2] = qv->z;
    idx = ((int) *(u16 *) ((char *) p + 0x8e) >> 4) << 1;
    v[0] += FX_MulFunc(0x2000, FX_SinCosTable_[idx]);
    v[2] += FX_MulFunc(0x2000, FX_SinCosTable_[idx + 1]);
    x = 0;
    y = 0;
    func_0204f818(&x, &y, v);
    if (flag != 0) {
        if (func_ov004_0223cc5c(func_ov004_0223cd50(), x, y, 0) == -1) {
            return 0;
        }
        e = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
        if (e != 0) {
            if (e != func_020b7524(func_020b6590(), 0, 0)) {
                return 0;
            }
        } else {
            x2 = 0;
            y2 = 0;
            func_020b758c(func_020b6590(), w);
            func_0204f818(&x2, &y2, w);
            if (x2 != x || y2 != y) {
                return 0;
            }
        }
    }
    e = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, 0);
    if (e == 0) {
        return 0;
    }
    id = func_0204bc50(func_ov004_0220fde0(e), 0);
    tx = x;
    ty = y;
    func_ov004_0220e758(e, &tx, &ty, 0, 0);
    x = tx;
    y = ty;
    *(u16 *) ((char *) self + 0x898) = id;
    if (((UnkStruct_0221ef90_2 *) self)->v25() != 0 &&
        func_0207f318(((UnkStruct_0221ef90_2 *) self)->v25(), &x, *(void **) ((char *) self + 0xa58),
                      *(void **) ((char *) self + 0xa5c)) != 0 &&
        chk((u16 *) ((char *) self + 0x898), 0x409c) == 0 && chk((u16 *) ((char *) self + 0x898), 0x40a0) == 0 &&
        chk((u16 *) ((char *) self + 0x898), 0x3820) == 0) {
        *(int *) ((char *) self + 0x89c) = x;
        *(int *) ((char *) self + 0x8a0) = y;
    } else {
        *(int *) ((char *) self + 0x89c) = -1;
        *(int *) ((char *) self + 0x8a0) = -1;
    }
    return 1;
}
