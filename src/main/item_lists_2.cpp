/* item_lists_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02063414 @ 0x02063414, 0x3bc bytes, Thumb
 * func_020630bc @ 0x020630bc, 0x358 bytes, Thumb
 */

#include "types.h"

class Rng {
  public:
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual int pick(int);
};

extern "C" void func_02063e98(void *);
extern "C" void func_02063e8c(void *);
extern "C" int func_0204bcdc(u16 *);
extern "C" int func_0204bc64(u16 *);
extern "C" int func_0204c228(u16 *);
extern "C" int func_0204bd08(u16 *);
extern "C" int func_020627bc(u16 *);
extern "C" int func_02053c14(u16 *);
extern "C" int func_0204c260(u16 *);
extern "C" void *func_020996ac(void *);
extern "C" int func_0203cdcc(void *, u16 *);

extern "C" {
extern u8 data_020de640[];
extern void func_02063ccc(int *p, int a, int b);
extern void func_02063cc8(int *p);
extern void func_020638d4(u16 *out, int *inp, int v1, void *v2, int a5, int a6, int a7);
extern int func_02063f40(int i);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
}

extern "C" void func_02063414(u16 *out, int base, u32 n, u16 *list, u32 nlist, void *who, int mode, int want, Rng *rng,
                              int flt)
{
    int shift;
    Rng *rp;
    u32 i;
    int found;
    int all;
    int sel;
    u32 i2;
    int found2;
    u16 v[4];
    u8 work[8];
    int cnt;
    u32 j;
    int t;
    u16 k;
    int hit;
    int x;
    int y;
    int kind;

    func_02063e98(work);
    rp = rng;
    if (rp == 0) {
        rp = (Rng *) work;
    }

    v[0] = (u16) base;
    if (func_0204bcdc(&v[0]) != 0) {
        shift = 2;
    } else {
        shift = 0;
    }

    cnt = 0;
    t = 0;
    k = v[0];
    if (k >= 0x450c && k <= 0x45db) {
        t = 1;
    }
    if (t || (k >= 0x45dc && k <= 0x47d7) || (k >= 0x1323 && k <= 0x1368)) {
        flt = 0;
    }

    for (i = 0; i < n; i++) {
        v[2] = (u16) (base + (i << shift));
        found = 0;
        for (j = 0; j < nlist; j++) {
            if (func_0204bcdc(&v[2]) != 0) {
                hit = (func_0204bc64(&v[2]) == func_0204bc64(&list[j])) ? 1 : 0;
            } else {
                hit = (v[2] == list[j]) ? 1 : 0;
            }
            if (hit != 0) {
                found = 1;
                break;
            }
        }
        if (found != 0) {
            continue;
        }

        x = 0;
        if (v[2] >= 0x11a8 && v[2] <= 0x12a7) {
            x = 1;
        }
        if (x != 0) {
            if (want == 0xa) {
                y = 1;
            } else if (want == func_0204c228(&v[2])) {
                y = 1;
            } else {
                y = 0;
            }
        } else {
            y = 1;
        }
        if (y == 0) {
            continue;
        }

        kind = 0;
        if (func_0204bd08(&v[2]) != 0) {
            kind = func_020627bc(&v[2]);
        } else if (func_0204bcdc(&v[2]) != 0) {
            kind = func_02053c14(&v[2]);
        }
        if (kind == 0x19) {
            continue;
        }
        if (kind == 0x18) {
            continue;
        }
        if (flt != 0 && func_0204c260(&v[2]) != 0) {
            continue;
        }

        if (who != 0) {
            if (mode != 0) {
                if (func_0203cdcc(func_020996ac(who), &v[2]) != 0) {
                    cnt++;
                }
            } else {
                if (func_0203cdcc(func_020996ac(who), &v[2]) == 0) {
                    cnt++;
                }
            }
        } else {
            cnt++;
        }
    }

    all = 0;
    if (cnt == 0) {
        if (who != 0) {
            *out = 0xfff1;
            func_02063e8c(work);
            return;
        }
        all = 1;
        cnt = n;
    }
    sel = rp->pick(cnt);

    cnt = 0;
    for (i2 = 0; i2 < n; i2++) {
        v[3] = (u16) (base + (i2 << shift));
        found2 = 0;
        if (all == 0) {
            for (j = 0; j < nlist; j++) {
                if (func_0204bcdc(&v[3]) != 0) {
                    hit = (func_0204bc64(&v[3]) == func_0204bc64(&list[j])) ? 1 : 0;
                } else {
                    hit = (v[3] == list[j]) ? 1 : 0;
                }
                if (hit != 0) {
                    found2 = 1;
                    break;
                }
            }
        }
        if (found2 != 0) {
            continue;
        }

        x = 0;
        if (v[3] >= 0x11a8 && v[3] <= 0x12a7) {
            x = 1;
        }
        if (x != 0) {
            if (want == 0xa) {
                y = 1;
            } else if (want == func_0204c228(&v[3])) {
                y = 1;
            } else {
                y = 0;
            }
        } else {
            y = 1;
        }
        if (y == 0) {
            continue;
        }

        kind = 0;
        if (func_0204bd08(&v[3]) != 0) {
            kind = func_020627bc(&v[3]);
        } else if (func_0204bcdc(&v[3]) != 0) {
            kind = func_02053c14(&v[3]);
        }
        if (kind == 0x19) {
            continue;
        }
        if (kind == 0x18) {
            continue;
        }
        if (flt != 0 && func_0204c260(&v[3]) != 0) {
            continue;
        }

        if (who != 0) {
            if (mode != 0) {
                if (func_0203cdcc(func_020996ac(who), &v[3]) == 0) {
                    continue;
                }
                if (sel == cnt) {
                    *out = v[3];
                    func_02063e8c(work);
                    return;
                }
                cnt++;
            } else {
                if (func_0203cdcc(func_020996ac(who), &v[3]) != 0) {
                    continue;
                }
                if (sel == cnt) {
                    *out = v[3];
                    func_02063e8c(work);
                    return;
                }
                cnt++;
            }
        } else {
            if (sel == cnt) {
                *out = v[3];
                func_02063e8c(work);
                return;
            }
            cnt++;
        }
    }
    *out = 0xfff1;
    func_02063e8c(work);
}

extern "C" void func_020630bc(u16 *out, int p1, void *p2)
{
    Rng *rp;
    unsigned int sel;
    unsigned int acc;
    int pick2;
    u8 *pf;
    u16 v0, v1, v2, v3, v4, v5, v6, v7, v8;
    u16 s1;
    u16 s2;
    void *rngbuf;
    u8 flags[3];
    int t0[2], t1[2], t2[2], t3[2], t4[2], t5[2], t6[2], t7[2], t8[2];
    u16 w[3][3];
    int total, cnt, m, hit;
    unsigned int i, j, k;
    u16 *e;

    func_02063e98(&rngbuf);
    rp = p2 ? (Rng *) p2 : (Rng *) &rngbuf;
    flags[0] = data_020de640[0];
    flags[1] = data_020de640[1];
    flags[2] = data_020de640[2];
    __cxa_vec_ctor((void *) (w), 9, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);

    func_02063ccc(t0, 0, 1);
    func_020638d4(&v0, t0, p1, p2, 1, 1, 0);
    w[0][0] = v0;
    func_02063cc8(t0);

    func_02063ccc(t1, 4, 1);
    func_020638d4(&v1, t1, p1, p2, 1, 1, 0);
    w[0][1] = v1;
    func_02063cc8(t1);

    func_02063ccc(t2, 3, 1);
    func_020638d4(&v2, t2, p1, p2, 1, 1, 0);
    w[0][2] = v2;
    func_02063cc8(t2);

    func_02063ccc(t3, 0, 2);
    func_020638d4(&v3, t3, p1, p2, 1, 1, 0);
    w[1][0] = v3;
    func_02063cc8(t3);

    func_02063ccc(t4, 4, 2);
    func_020638d4(&v4, t4, p1, p2, 1, 1, 0);
    w[1][1] = v4;
    func_02063cc8(t4);

    func_02063ccc(t5, 3, 2);
    func_020638d4(&v5, t5, p1, p2, 1, 1, 0);
    w[1][2] = v5;
    func_02063cc8(t5);

    func_02063ccc(t6, 0, 3);
    func_020638d4(&v6, t6, p1, p2, 1, 1, 0);
    w[2][0] = v6;
    func_02063cc8(t6);

    func_02063ccc(t7, 4, 3);
    func_020638d4(&v7, t7, p1, p2, 1, 1, 0);
    w[2][1] = v7;
    func_02063cc8(t7);

    func_02063ccc(t8, 3, 3);
    func_020638d4(&v8, t8, p1, p2, 1, 1, 0);
    w[2][2] = v8;
    func_02063cc8(t8);

    for (;;) {
        total = 0;
        for (i = 0; i < 3; i++) {
            if (flags[i] != 0) {
                total += func_02063f40(i);
            }
        }
        if (total == 0) {
            break;
        }
        sel = (unsigned int) rp->pick(total);
        acc = 0;
        for (j = 0; j < 3; j++) {
            pf = &flags[j];
            if (flags[j] == 0) {
                continue;
            }
            acc += (unsigned int) func_02063f40(j);
            if (sel >= acc) {
                continue;
            }
            cnt = 0;
            for (k = 0; k < 3; k++) {
                e = &w[j][k];
                if (func_0204bcdc(e) != 0) {
                    s1 = 0xfff1;
                    hit = (func_0204bc64(e) == func_0204bc64(&s1)) ? 1 : 0;
                } else {
                    hit = (*e == 0xfff1) ? 1 : 0;
                }
                if (hit == 0) {
                    cnt++;
                }
            }
            if (cnt == 0) {
                *pf = 0;
                break;
            }
            pick2 = rp->pick(cnt);
            m = 0;
            for (k = 0; k < 3; k++) {
                e = &w[j][k];
                if (func_0204bcdc(e) != 0) {
                    s2 = 0xfff1;
                    hit = (func_0204bc64(e) == func_0204bc64(&s2)) ? 1 : 0;
                } else {
                    hit = (*e == 0xfff1) ? 1 : 0;
                }
                if (hit != 0) {
                    continue;
                }
                if (m == pick2) {
                    *out = *e;
                    __cxa_vec_cleanup((void *) (w), 9, 2, (void (*)(void *)) func_020051b0);
                    func_02063e8c(&rngbuf);
                    return;
                }
                m++;
            }
        }
    }
    *out = 0xfff1;
    __cxa_vec_cleanup((void *) (w), 9, 2, (void (*)(void *)) func_020051b0);
    func_02063e8c(&rngbuf);
}
