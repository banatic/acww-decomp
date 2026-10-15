/* func_020630bc @ 0x020630bc, 0x358 bytes, Thumb, module main
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

extern "C" {
extern u8 data_020de640[];
extern void func_02063e98(void *);
extern void func_02063e8c(void *);
extern void func_02063ccc(int *p, int a, int b);
extern void func_02063cc8(int *p);
extern void func_020638d4(u16 *out, int *inp, int v1, void *v2, int a5, int a6, int a7);
extern int func_02063f40(int i);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
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
