/* func_02044168 @ 0x02044168, 0x228 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pair {
    int a;
    int b;
};

extern int data_021c7c48;
extern int data_020caaf8[];
extern void *data_020ccf94;

extern int func_0204ba94(u16 *);
extern int func_0204b7a0(u16 *);
extern int func_02042c9c(int *, struct Pair *);
extern int func_02044540(void);
extern int func_0204b910(u16 *);
extern int func_02073d90(void *);
extern int func_020984d4(void);
extern int func_02042f20(int *, int, int, struct Pair *, int, int, int, int, int, int);

int func_02044168(int p0, u16 *pv, struct Pair *p2, int p3)
{
    int kind;
    int A;
    int R;
    struct Pair t1;
    struct Pair t2;
    u16 v;
    int idx;
    unsigned int ok;
    u16 w;
    int q;

    kind = 0;
    A = 0;
    R = -1;
    v = *pv;
    if (((v >= 0x26 && v <= 0x2a) || (v >= 0x5d && v <= 0x61) || (v >= 0x2f && v <= 0x56) || (v >= 0x57 && v <= 0x5b) ||
         (v >= 0x66 && v <= 0x68) || v == 0x69 || (v >= 0x6a && v <= 0x6c) || v == 0x6d || (v >= 0xc8 && v <= 0xcf)) &&
        func_0204ba94(pv) == 0) {
        idx = func_0204b7a0(pv) - 1;
        kind = 6;
        t1.a = p2->a;
        t1.b = p2->b;
        A = (u8) func_02042c9c(&data_021c7c48, &t1);
        if (p3 != 2) {
            if (A >= data_020caaf8[idx]) {
                ok = 0;
                w = *pv;
                if (w >= 0xc8 && w <= 0xcf) {
                    ok = 1;
                }
                if (ok > 0) {
                    v = (u16) (idx + 0xd0);
                } else if ((w >= 0x5d && w <= 0x61) || w == 0x6d) {
                    v = (u16) (idx + 0x62);
                } else if (w >= 0x2f && w <= 0x56) {
                    v = (u16) (idx + 0xff);
                } else {
                    v = (u16) (idx + 0x2b);
                }
            } else {
                ok = 0;
                w = *pv;
                if (w >= 0x26 && w <= 0x2a) {
                    ok = 1;
                }
                if (ok > 0 || (w >= 0x57 && w <= 0x5b) || (w >= 0x66 && w <= 0x68) || w == 0x69) {
                    v = (u16) (idx + 0x27);
                } else {
                    v = (u16) (idx + 0x5e);
                }
                if (w == 0x67 || w == 0x6b) {
                    if (func_02044540() != 0) {
                        kind = 7;
                    } else {
                        v = *pv;
                    }
                } else if ((w >= 0x2f && w <= 0x56) || (w >= 0xc8 && w <= 0xcf)) {
                    if (func_0204b910(pv) != 0) {
                        v = (u16) (*pv + 1);
                    } else {
                        v = *pv;
                    }
                } else if (w == 0x6d) {
                    v = w;
                }
            }
        }
    } else {
        ok = 0;
        w = *pv;
        if (w >= 0xe3 && w <= 0xe7) {
            ok = 1;
        }
        if (ok > 0) {
            kind = 0xd;
        } else if (w >= 0xe8 && w <= 0xfb) {
            kind = 0xc;
            if (func_02073d90(data_020ccf94) == 0) {
                q = (*pv - 0xe8) / 5;
                if (q == func_020984d4()) {
                    if (p3 != 2) {
                        kind = 0xe;
                    }
                }
            }
        } else {
            switch ((w & 0xf000) >> 12) {
                case 0:
                    if (w == 0x1b || w == 0x89) {
                        kind = 0x17;
                    }
                    break;
                case 1:
                case 3:
                case 4:
                    kind = 0xc;
                    break;
                case 2:
                    break;
            }
        }
    }
    if (kind != 0) {
        w = *pv;
        t2.a = p2->a;
        t2.b = p2->b;
        R = func_02042f20(&data_021c7c48, p0, kind, &t2, v, w, A, 0, p3, -1);
    }
    return R;
}
