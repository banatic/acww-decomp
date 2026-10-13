/* func_ov003_02211e38 @ 0x02211e38, 0x320 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

struct UnkStruct_02211e38;
struct Vt {
    char pad_00[0x60];
    void (*unk_60)(struct UnkStruct_02211e38 *, short *);
};
struct UnkStruct_02211e38 {
    struct Vt *vt;
};

extern void *data_021c80bc;
extern short FX_SinCosTable_[];
extern void *data_020ccf94;

extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int k);
extern void func_ov003_022241a4(int *p);
extern void func_0200f268(void *self, int k);
extern void func_0201107c(void *self, int *p);
extern void func_0200fa8c(int *out, void *self);
extern void func_0204f818(volatile int *px, volatile int *pz, int *p);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_ov003_02224384(int h, int *pos, int k);
extern void func_0200f27c(void *self, int k);
extern void func_0200f328(void *self, int k);
extern void func_020110c4(short *p, void *self);
extern int func_02073908(void *a, int b);
extern int func_ov003_0221abf8(int h, int k);
extern int FX_MulFunc(int a, int b);
extern void func_020912d4(int a, int *v, short *p, int q);

void func_ov003_02211e38(char *self)
{
    short s[2];
    volatile int px, pz;
    int arr[2];
    int k;
    int pos[2];
    int m[3];
    u8 *p;
    int n0, n1;
    u16 *o;
    int lx, lz;
    int cx, cz;
    int j, h, g, f, e, d, c, b, a;
    int t;
    int b2, a2;
    int *q;
    int t1, idx, dz, t0, dx;
    struct UnkStruct_02211e38 *ob;

    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 5) == 0) {
        return;
    }
    p = (u8 *) (self + 0x7d4);
    if (p[2] != 0) {
        n1 = p[1];
        n0 = p[0];
        arr[0] = n0;
        arr[1] = n1;
        func_ov003_022241a4(arr);
        func_0200f268(self, 0x12);
        func_0200f268(self, 0x1c);
    }
    k = -0x333;
    func_0201107c(self, &k);
    func_0200fa8c(m, self);
    px = 0;
    pz = 0;
    func_0204f818(&px, &pz, m);
    lx = px;
    lz = pz;
    cx = lx >> 4;
    cz = lz >> 4;
    o = func_0204f5e0(data_021c80bc, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
    if (o != 0) {
        j = 1;
        h = 1;
        g = 1;
        f = 1;
        e = 1;
        d = 1;
        c = 1;
        b = 1;
        a = 0;
        if (*o >= 0x26 && *o <= 0x2a) {
            a = 1;
        }
        if (a == 0) {
            if (!(*o >= 0x5d && *o <= 0x61)) {
                b = 0;
            }
        }
        if (b == 0) {
            if (!(*o >= 0x2f && *o <= 0x56)) {
                c = 0;
            }
        }
        if (c == 0) {
            if (!(*o >= 0x57 && *o <= 0x5b)) {
                d = 0;
            }
        }
        if (d == 0) {
            if (!(*o >= 0x66 && *o <= 0x68)) {
                e = 0;
            }
        }
        if (e == 0) {
            if (*o != 0x69) {
                f = 0;
            }
        }
        if (f == 0) {
            if (!(*o >= 0x6a && *o <= 0x6c)) {
                g = 0;
            }
        }
        if (g == 0) {
            if (*o != 0x6d) {
                h = 0;
            }
        }
        if (h == 0) {
            if (!(*o >= 0xc8 && *o <= 0xcf)) {
                j = 0;
            }
        }
        if (j != 0) {
            pos[0] = px;
            pos[1] = pz;
            func_ov003_02224384(*(int *) (self + 0x800), pos, 1);
        }
    }
    func_0200f27c(self, 9);
    t = 0xf;
    if (o != 0) {
        t = (*o & 0xf000) >> 12;
    }
    switch (*(u8 *) (self + 0x16c)) {
        case 0:
            if (o != 0) {
                if (t <= 4) {
                    b2 = 1;
                    a2 = 0;
                    if (*o >= 0xe3 && *o <= 0xe7) {
                        a2 = 1;
                    }
                    if (a2 == 0) {
                        if (!(*o >= 0xe8 && *o <= 0xfb)) {
                            b2 = 0;
                        }
                    }
                    if (b2 == 0) {
                        if (!((*o >= 0x26 && *o <= 0x2a) || (*o >= 0x5d && *o <= 0x61) || (*o >= 0x2f && *o <= 0x56) ||
                              (*o >= 0x57 && *o <= 0x5b) || (*o >= 0x66 && *o <= 0x68) || *o == 0x69 ||
                              (*o >= 0x6a && *o <= 0x6c) || *o == 0x6d || (*o >= 0xc8 && *o <= 0xcf))) {
                            goto L_hit;
                        }
                    }
                }
                if (t == 0xa || (unsigned int) (t - 0xd) <= 1) {
                    goto L_hit;
                }
            }
            goto L_alt;
        L_hit:
            func_0200f328(self, 0x7df);
            break;
        L_alt:
            func_0200f328(self, 0x844);
            q = (int *) (self + 0x5c);
            m[0] = q[0];
            m[1] = q[1];
            m[2] = q[2];
            s[0] = *(short *) (self + 0x8e);
            idx = ((unsigned short) s[0] >> 4) * 2;
            t0 = FX_SinCosTable_[idx];
            t1 = FX_SinCosTable_[idx + 1];
            dz = FX_MulFunc(t1, 0xccd) - FX_MulFunc(t0, 0x800);
            dx = FX_MulFunc(t0, 0xccd) + FX_MulFunc(t1, 0x800);
            m[0] = m[0] + dx;
            m[2] = m[2] + dz;
            s[0] = s[0] - 0x2000;
            func_020912d4(5, m, s, 0);
            break;
        case 1:
            func_0200f328(self, 0x7df);
            break;
        case 2:
            func_0200f328(self, 0x7df);
            if (*(int *) (self + 0x168) == 0) {
                break;
            }
            func_020110c4(&s[1], self);
            ob = *(struct UnkStruct_02211e38 **) (self + 0x168);
            ob->vt->unk_60(ob, &s[1]);
            break;
        case 3:
            if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
                if (func_ov003_0221abf8(*(int *) (self + 0x168), 1) != 0) {
                    break;
                }
                func_0200f328(self, 0x7df);
            } else {
                func_0200f328(self, 0x7df);
            }
            break;
    }
    *(int *) (self + 0x168) = 0;
    *(u8 *) (self + 0x16c) = 0;
}
