/* func_02063414 @ 0x02063414, 0x3bc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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
