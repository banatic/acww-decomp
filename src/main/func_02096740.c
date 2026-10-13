/* func_02096740 @ 0x02096740, 0x304 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern unsigned char func_020b65c4(void);
extern unsigned char func_020a13ac(void);
extern u8 *func_0200338c(int a, int b);
extern unsigned char func_020a13d0(void);
extern int func_020a6ed0(void);
extern u8 *func_020961a8(int);
extern int func_020310c8(int);
extern int func_020961c0(void);
extern void func_020961f0(int, int);
extern void func_020952ac(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned char func_02073dd4(void *, int);
extern int func_02073908(void *, int);
extern int func_020952ec(void);
extern int func_02096518(int *, int, int);
extern int func_02096614(u8 *, int *, int *, int, int);
extern int func_0209658c(s16 *, int, int);
extern int DWC_Alloc(int, int);
extern u8 *func_02096254(int);
extern int *func_02096260(int);
extern int *func_02096244(int);
extern s16 *func_02096238(int);
extern void func_020ee470(void *);

int func_02096740(void)
{
    int s4;
    int s8;
    int sc;
    u8 *s10;
    int s14;
    int s18;
    int s1c;
    u8 a;
    u8 b;
    s16 c;
    s16 d[3];
    int e;
    int f;
    int g;
    u16 h[3];
    u16 ii[3];
    int j2;
    int k2;
    int l2;
    int m[3];
    int n[3];
    int o[3];

    void *gp;
    int q;
    int idx;
    unsigned int i;
    unsigned int i2;
    int tmpv;
    int last;
    int last2;
    unsigned int t;
    u8 *p;
    int *r;
    int *r2;

    gp = data_020ccf94;
    q = ((int *) gp)[0x64 / 4];

    if (func_020b65c4() == 0x2e) {
        goto end;
    }
    if (func_020b65c4() == 0xd || func_020b65c4() == 0x2f || func_020b65c4() == 0xe) {
        if (func_020a13ac() != 0) {
            return 1;
        }
        p = func_0200338c(0x72, 0);
        if (p == 0) {
            goto end;
        }
        t = (p[0xe] == 2) ? 1 : 0;
        if (t != 0) {
            goto end;
        }
        if (func_020b65c4() == 0xd || func_020b65c4() == 0x2f) {
            idx = func_020a13d0();
        } else {
            idx = func_020a6ed0();
        }
        if (idx >= 4) {
            goto end;
        }
        if (func_020961a8(idx) != 0) {
            goto end;
        }
        m[0] = 0;
        m[1] = 0;
        m[2] = 0;
        d[0] = 0;
        d[1] = 0;
        d[2] = 0;
        q = func_020310c8(0);
        if (func_020b65c4() == 0xd || func_020b65c4() == 0x2f) {
            m[0] = 0x10000;
            m[1] = q;
            m[2] = 0x5000;
            d[0] = 0;
            d[1] = 0;
            d[2] = 0;
        } else {
            m[0] = 0x10000;
            m[1] = q;
            m[2] = 0x11800;
            d[0] = 0;
            d[1] = -0x8000;
            d[2] = 0;
        }
        func_020961f0(idx, func_020961c0());
        func_020952ac((unsigned int) idx, (unsigned int) &m[0], (unsigned int) &d[0], 0x04000000);
        goto end;
    }

    if (func_02073dd4(gp, q) == 0) {
        goto end;
    }
    if (func_020961a8(4) == 0) {
        goto end;
    }
    s4 = func_020952ec();
    last = -1;
    s14 = 0;
    s8 = 0;
    sc = 0;
    s1c = 0;
    for (i = 0; i < 4; i++) {
        if (func_02073908(gp, i) != 0) {
            continue;
        }
        if (func_02073dd4(gp, i) == 0) {
            continue;
        }
        if (func_020961a8(i) != 0) {
            continue;
        }
        if (func_02096518(&e, last, i) != 0 && e < 0x93) {
            if (func_02096614(&a, &f, &g, last, i) != 0 && func_020b65c4() == a && func_0209658c(&c, last, i) != 0) {
                tmpv = func_020310c8(s8);
                n[0] = f;
                n[1] = tmpv;
                n[2] = g;
                h[0] = (u16) sc;
                h[1] = (u16) c;
                h[2] = (u16) sc;
                func_020961f0(i, func_020961c0());
                func_020952ac((unsigned int) i, (unsigned int) &n[0], (unsigned int) &h[0], 0x00800000);
                continue;
            }
        }
        if (DWC_Alloc(0x1b, s4) == 0) {
            continue;
        }
        s10 = func_02096254(i);
        r = func_02096260(i);
        if (*s10 != func_020b65c4()) {
            continue;
        }
        if (r[0] == 0x93) {
            continue;
        }
        r2 = func_02096244(i);
        o[0] = r2[0];
        o[1] = r2[1];
        o[2] = r2[2];
        tmpv = func_02096238(i)[s1c];
        ii[0] = (u16) s14;
        ii[1] = (u16) tmpv;
        ii[2] = (u16) s14;
        func_020961f0(i, func_020961c0());
        func_020952ac((unsigned int) i, (unsigned int) &o[0], (unsigned int) &ii[0],
                      (unsigned int) ((r[0] << 0x16) & 0x3fc00000));
    }

    s18 = 0;
    last2 = -1;
    for (i2 = 0; i2 < 4; i2++) {
        u8 *u;
        if (func_02073908(gp, i2) != 0) {
            continue;
        }
        if (DWC_Alloc(0x1b, s4) != 0) {
            continue;
        }
        u = func_020961a8(i2);
        if (u == 0) {
            continue;
        }
        t = (u[0xe] == 2) ? 1 : (unsigned int) s18;
        if (t != 0) {
            continue;
        }
        if (func_02096518(&j2, last2, i2) == 0) {
            goto kill1;
        }
        if (j2 >= 0x93) {
            func_020ee470(u);
            continue;
        }
        if (func_02096614(&b, &k2, &l2, last2, i2) == 0) {
            goto kill2;
        }
        if (func_020b65c4() == b) {
            continue;
        }
        func_020ee470(u);
        continue;
    kill2:
        func_020ee470(u);
        continue;
    kill1:
        func_020ee470(u);
    }
end:
    return 1;
}
