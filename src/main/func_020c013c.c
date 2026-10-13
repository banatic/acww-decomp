/* func_020c013c @ 0x020c013c, 0x1e8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[8];
    int unk_08;
    unsigned char pad_0C[0x24 - 0xc];
    int unk_24;
    unsigned char pad_28[0x60 - 0x28];
    u32 unk_60;
    int unk_64;
} UnkStruct_020c013c;

typedef struct {
    u16 unk_00;
    u16 c1;
} UnkStruct_020c013c_2;

extern int data_020d22d0[];                  // 0x020d22d0
extern UnkStruct_020c013c_2 data_020d2344[]; // 0x020d2344
extern int data_021fba00;                    // 0x021fba00
typedef struct {
    int e[3];
} E12;
extern E12 data_021fa678[]; // 0x021fa678

extern int func_020c03f4(int mode, u32 v);
extern int FX_MulFunc(int a, int b);
extern void func_020bec14(void *o, int i, u16 *c);
extern void func_020bee4c(void *o, int v);

#define R5(c) ((int) ((((u32) ((c) << 27)) >> 27) << 12))
#define G5(c) ((int) ((((u32) ((c) << 22)) >> 27) << 12))
#define B5(c) ((int) ((((u32) ((c) << 17)) >> 27) << 12))

void func_020c013c(UnkStruct_020c013c *self)
{
    // DECLS
    int k;
    u32 g1c;
    u32 w;
    int *p0;
    u32 b1c;
    u32 q;
    int tb;
    u32 v;
    int i1;
    int t;
    int m;
    int q0;
    int a;
    u32 r1c;
    u32 b0c;
    u32 r0c;
    int q1;
    void *o;
    int *p1;
    int n;
    int bb;
    int idx;
    int q4;
    int i0;
    u32 g0c;
    int tg;
    int b;
    int q3;
    int q5;
    int rr;
    UnkStruct_020c013c_2 *e;
    int q2;
    int tr;
    int arg;
    int gg;
    int invT;
    // ENDDECLS
    u16 out[2];

    n = self->unk_64;
    if (n < 0x10) {
        t = 0;
    } else if (n < 0x1b) {
        t = ((n - 0x10) << 12) / 0xb;
    } else {
        t = 0x1000;
    }

    v = self->unk_60;
    idx = (int) ((v >> 8) & 3);
    a = func_020c03f4(idx, ((v >> 31) & 1) != 0);
    b = a + 1;

    i1 = i0 = 0;
    if (n >= 0xb) {
        m = n & 2;
        if (m == 0) {
            i0 = 1;
        }
        if (m != 0) {
            i1 = 1;
        } else {
            i1 = 0;
        }
    }
    p0 = &data_020d22d0[i0];
    p1 = &data_020d22d0[i1];

    if (idx >= 4) {
        return;
    }
    if (a >= 0xf) {
        return;
    }
    if (b >= 0xf) {
        return;
    }

    e = &data_020d2344[idx];
    invT = 0x1000 - t;

    tr = FX_MulFunc(R5(data_020d2344[idx].unk_00), invT);
    rr = tr + FX_MulFunc(R5(e->c1), t);
    tg = FX_MulFunc(G5(data_020d2344[idx].unk_00), invT);
    gg = tg + FX_MulFunc(G5(e->c1), t);
    tb = FX_MulFunc(B5(data_020d2344[idx].unk_00), invT);
    bb = tb + FX_MulFunc(B5(e->c1), t);

    q0 = FX_MulFunc(rr, *p0);
    q1 = FX_MulFunc(gg, *p0);
    q2 = FX_MulFunc(bb, *p0);
    q3 = FX_MulFunc(rr, *p1);
    q4 = FX_MulFunc(gg, *p1);
    q5 = FX_MulFunc(bb, *p1);

    g0c = (u32) ((q1 + 0x800) >> 12);
    b0c = (u32) ((q2 + 0x800) >> 12);
    r1c = (u32) ((q3 + 0x800) >> 12);
    g1c = (u32) ((q4 + 0x800) >> 12);
    b1c = (u32) ((q5 + 0x800) >> 12);
    r0c = (u32) ((q0 + 0x800) >> 12);

    if (r0c > 0x1f) {
        r0c = 0x1f;
    }
    if (g0c > 0x1f) {
        g0c = 0x1f;
    }
    if (b0c > 0x1f) {
        b0c = 0x1f;
    }
    if (r1c > 0x1f) {
        r1c = 0x1f;
    }
    if (g1c > 0x1f) {
        g1c = 0x1f;
    }
    if (b1c > 0x1f) {
        b1c = 0x1f;
    }

    out[0] = (u16) (r0c | (g0c << 5) | (b0c << 10));
    out[1] = (u16) (r1c | (g1c << 5) | (b1c << 10));

    k = self->unk_24;
    arg = self->unk_08;
    o = &data_021fba00;
    func_020bec14(o, a, &out[0]);
    func_020bec14(o, b, &out[1]);
    func_020bee4c(&data_021fa678[k], arg);
}
