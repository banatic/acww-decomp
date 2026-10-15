/* func_02052cac @ 0x02052cac, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_020e54a8;

extern int func_020b65c4(void);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *p, int a1, int a2, int a3);
extern void *func_0204d5c8(int a0);
extern u16 *func_0204f5e0(void *o, int x, int y, int ox, int oy, int f);
extern int func_02052e98(int a1, int a2, u8 v, int a0);
extern int func_02052e70(int a1, int a2, int a0);
extern void func_02052ee8(int a1, int a2, int a3, u8 p6, int a0);
extern int func_02060b48(int a0, u16 *code);
extern int func_02060b18(int a0);

typedef int (*VFn)(void *self, u8 a, u8 b);

int func_02052cac(int a0, int a1, int a2, int a3, u8 p5, u8 p6, u8 p7, u8 p8, volatile u8 p9)
{
    u16 code;
    u16 v;
    u8 t;
    void *obj;
    void *q;
    u16 *e;
    unsigned int cond;
    int ok;
    VFn *vt;
    int hx, hy;

    cond = (data_020e54a8 == 1);
    if (cond && func_020b65c4() == a0) {
        q = func_ov004_0223cc10(func_ov004_0223cd50(), a1, a2, a3);
        if (q != 0) {
            vt = *(VFn **) q;
            return vt[28](q, p5, p9);
        }
    }

    obj = func_0204d5c8(a0);
    if (obj != 0) {
        hx = a1 >> 4;
        hy = a2 >> 4;
        e = func_0204f5e0(obj, hx, hy, a1 - (hx << 4), a2 - (hy << 4), 0);
        if (e != 0) {
            ok = 0;
            if (*e >= 0x45dc && *e <= 0x47d7) {
                ok = 1;
            }
            if (ok != 0) {
                if (p6 != 0) {
                    func_02052e98(a1, a2, (u8) (p9 & 0xf), a0);
                } else {
                    func_02052e70(a1, a2, a0);
                }
            }
        }
    }

    func_02052ee8(a1, a2, a3, p6, a0);
    if (p7 != 0) {
        if (p6 != 0) {
            t = p9;
            if (t < 0x46) {
                v = (u16) (t + 0x1323);
            } else {
                v = 0x1323;
            }
            code = v;
            func_02060b48(a0, &code);
        } else if (p8 == 0) {
            func_02060b18(a0);
        }
    }
    return 1;
}
