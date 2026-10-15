/* func_ov093_022990e8 @ 0x022990e8, 0x24e bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_dead_assignments off

typedef struct {
    short unk_00;
    short unk_02;
    u8 unk_04;
    char pad_05;
    u8 unk_06;
    char pad_07;
    char sub8[4];
} St;

extern void func_ov093_02298fa4(St *st, int n);
extern void func_ov093_0229939c(void *a, char *s, int n);
extern char *func_ov093_02299338(void *a, int n);
extern int func_ov093_02298fac(St *st, int n);
extern void func_ov093_02298f9c(St *st, int n);
extern void func_ov093_0229937c(void *a, char *s, int n, int m);
extern void *func_ov093_02299090(void *a);
extern int func_020a8a34(void *w, char *p);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_02070a04(void *w, int x, int y);
extern void func_02070adc(void *w, void *b, int x, int y, int p1, int p2, int p3);
extern void func_0207099c(void *w);

void func_ov093_022990e8(void *a, void *b, St *st)
{
    char *p;
    char *q;
    void *w;
    int f;
    int i;

    if (st->unk_02 < 0) {
        st->unk_02 = 0;
        st->unk_00 = 0;
        st->unk_04 = 0;
    } else if (st->unk_02 >= 0xcc) {
        if (st->unk_06 < 0xd) {
            st->unk_06 = st->unk_06 + 1;
        } else {
            func_ov093_02298fa4(st, 4);
        }
        func_ov093_0229939c(a, st->sub8, st->unk_00 & 0x1f);
        st->unk_00 = st->unk_00 + 1;
        return;
    }
    if (st->unk_04 >= 0x19) {
        st->unk_04 = 0;
    }
    p = func_ov093_02299338(a, st->unk_02);
    if (p == 0) {
        f = 1;
    } else {
        f = 0;
    }
    if (f == 0) {
        if (p[0] == 0xa || p[0] == 0) {
            f = 1;
            func_ov093_02298fa4(st, f);
        }
    }
    if (f != 0) {
        for (i = 0; i < 2; i++) {
            func_ov093_0229939c(a, st->sub8, st->unk_00 & 0x1f);
            st->unk_00 = st->unk_00 + 1;
        }
        st->unk_02 = st->unk_02 + 1;
        if (st->unk_06 < 0xd) {
            st->unk_06 = st->unk_06 + 1;
        } else {
            func_ov093_02298fa4(st, 4);
        }
        return;
    }
    st->unk_06 = 0;
    if (func_ov093_02298fac(st, 1) != 0) {
        func_ov093_02298f9c(st, 1);
        func_ov093_0229937c(a, st->sub8, st->unk_04, st->unk_00 & 0x1f);
        w = func_ov093_02299090(a);
        func_020a8a34(w, p);
        func_02070a98(w, (int) b, st->unk_04 * 0x10 + 0x11, 0x10, 1, 0, 0);
        func_02070a04(w, 0, 0);
        st->unk_04 = st->unk_04 + 1;
        st->unk_02 = st->unk_02 + 1;
        st->unk_00 = st->unk_00 + 1;
        q = func_ov093_02299338(a, st->unk_02);
        if (q == 0 || q[0] == 0xa || q[0] == 0) {
            st->unk_02 = st->unk_02 + 1;
            return;
        }
        func_ov093_0229937c(a, st->sub8, st->unk_04, st->unk_00 & 0x1f);
        w = func_ov093_02299090(a);
        func_020a8a34(w, q);
        func_02070a98(w, (int) b, st->unk_04 * 0x10 + 0x11, 0x10, 1, 0, 0);
        func_02070a04(w, 0, 0);
        st->unk_04 = st->unk_04 + 1;
        st->unk_02 = st->unk_02 + 1;
        st->unk_00 = st->unk_00 + 1;
        return;
    }
    {
        int m0 = st->unk_00 & 0x1f;
        func_ov093_0229937c(a, st->sub8, st->unk_04, m0);
    }
    st->unk_00 = st->unk_00 + 1;
    st->unk_04 = st->unk_04 + 1;
    func_ov093_0229937c(a, st->sub8, st->unk_04, st->unk_00 & 0x1f);
    st->unk_00 = st->unk_00 + 1;
    st->unk_04 = st->unk_04 + 1;
    w = func_ov093_02299090(a);
    func_020a8a34(w, p);
    func_02070adc(w, b, (st->unk_04 - 2) * 0x10 + 0x11, 0x10, 1, 0, 0);
    func_0207099c(w);
    st->unk_02 = st->unk_02 + 1;
}
