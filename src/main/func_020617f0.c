/* func_020617f0 @ 0x020617f0, 0x224 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020617f0 {
    unsigned char pad_00[0xb4];
};

extern u16 data_021dc7a8[];
extern struct UnkStruct_020617f0 data_021f2fa8[];

extern unsigned int func_0204e414(void);
extern void func_02061a14(void *);
extern int func_0204df30(u32);
extern void *func_0209847c(u32);
extern void *func_02099734(void *);
extern int func_02098e8c(void *, u32);
extern u16 *func_02098f48(void *, u32);
extern void func_02061ac4(u16 *, u16 *);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_02098f0c(void *, u16 *, u32, int);
extern void *func_020996ac(void *);
extern int OS_UnlockByWord_IrqAndFiq(void *, u16 *, int);
extern u16 func_0203a6d4(u32);
extern int func_0203a694(u32, u16);
extern u16 *func_0203a674(struct UnkStruct_020617f0 *);

void func_020617f0(void)
{
    u32 n;
    u32 i;
    u32 i3;
    u32 j;
    u32 j0;
    u32 k;
    u32 k0;
    void *obj;
    int flag;
    int res;
    int z3;
    int z4;
    int z1;
    int z2;
    int za;
    int zb;
    int zc;
    int zd;
    int ze;
    int zf;
    u16 *p;
    u16 *q;
    u16 t[8];

    func_02061a14((void *) func_0204e414());
    for (n = 0; n < 5; n++) {
        func_02061a14((void *) func_0204df30(n));
    }

    z1 = 0;
    z2 = 0;
    z3 = 0;
    z4 = 0;
    j0 = 0;
    for (i = 0; i < 7; i++) {
        obj = func_0209847c(i);
        if (obj != 0) {
            for (j = j0; j < 15; j++) {
                flag = func_02098e8c(func_02099734(obj), j);
                p = func_02098f48(func_02099734(obj), j);
                t[0] = *p;
                func_02061ac4(&t[1], &t[0]);
                if (func_0204bcdc(&t[1]) != 0) {
                    res = (func_0204bc64(&t[1]) == func_0204bc64(&t[0])) ? 1 : z1;
                } else {
                    res = (t[1] == *(u16 *) (int) t) ? 1 : z2;
                }
                if (res == 0) {
                    if (flag == 0) {
                        func_02098f0c(func_02099734(obj), &t[1], j, z3);
                        OS_UnlockByWord_IrqAndFiq(func_020996ac(obj), &t[1], z4);
                    }
                }
            }
        }
    }

    za = 0;
    zb = 0;
    for (i = 0; i < 15; i++) {
        t[2] = func_0203a6d4(i);
        func_02061ac4(&t[3], &t[2]);
        if (func_0204bcdc(&t[2]) != 0) {
            res = (func_0204bc64(&t[2]) == func_0204bc64(&t[3])) ? 1 : za;
        } else {
            res = (t[2] == t[3]) ? 1 : zb;
        }
        if (res == 0) {
            func_0203a694(i, t[3]);
        }
    }

    zc = 0;
    zd = 0;
    for (i3 = 0; i3 < 15; i3++) {
        q = (u16 *) ((char *) &data_021dc7a8[i3] + 0x172c0);
        t[4] = *q;
        func_02061ac4(&t[5], &t[4]);
        if (func_0204bcdc(&t[4]) != 0) {
            res = (func_0204bc64(&t[4]) == func_0204bc64(&t[5])) ? 1 : zc;
        } else {
            res = (t[4] == t[5]) ? 1 : zd;
        }
        if (res == 0) {
            *q = t[5];
        }
    }

    ze = 0;
    zf = 0;
    k0 = 0;
    for (i = 0; i < 4; i++) {
        p = func_0203a674(&data_021f2fa8[i]);
        for (k = k0; k < 0x5a; k++) {
            t[6] = *p;
            func_02061ac4(&t[7], &t[6]);
            if (func_0204bcdc(&t[6]) != 0) {
                res = (func_0204bc64(&t[6]) == func_0204bc64(&t[7])) ? 1 : ze;
            } else {
                res = (t[6] == t[7]) ? 1 : zf;
            }
            if (res == 0) {
                *p = t[7];
            }
            p++;
        }
    }
}
