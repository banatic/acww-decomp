/* tile_request_grant_2: 2 functions, module main
 * mwccarm 1.2/base -O1,s
 * func_0204558c @ 0x0204558c, 0xe4 bytes, Thumb
 * func_02045440 @ 0x02045440, 0x14c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, z;
} Pt;

typedef struct {
    int a, b;
} UnkStruct_02045440;

typedef struct {
    int a, b, c;
} O12;

typedef struct {
    u8 unk_00, unk_01;
    u16 unk_02;
    u16 unk_04;
} UnkStruct_02045440_2;

extern unsigned int func_0204e414(void);
extern unsigned short func_02045670(int unused, int id);
extern int func_020456b0(void *unused, Pt *p, int i, int ctx);
extern int func_02046024(int a, Pt *p, int r, int s, int a5, int a6, int a7, int a8, int a9, int a10);
extern int data_020ca67c[];
extern u8 data_020ca640[];
extern void func_02063ccc(UnkStruct_02045440 *o, int a, int b);
extern void func_020638d4(volatile u16 *out, UnkStruct_02045440 *o, int a, int b, int c, int d, int e);
extern void func_02063cc8(UnkStruct_02045440 *o);
extern void func_0204f794(O12 *o, int x, int z);
extern int func_ov003_02223078(void *c, O12 *o);

void func_0204558c(u8 *self, int b, int id)
{
    unsigned int ctx;
    int r;
    int n;
    int i;
    int t;
    int bb;
    int k;
    int tz;
    u8 *q;
    volatile u16 v0, v1, v2;
    Pt pt;
    Pt pt2;

    pt.x = 0;
    pt.z = 0;
    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    switch (id) {
        case 0xcc:
            n = 2;
            break;
        default:
            n = 3;
            break;
    }
    r = func_02045670((int) self, id);
    for (i = 0; i < n; i++) {
        v2 = *(u16 *) (self + 2);
        t = v2;
        v1 = (u16) t;
        k = data_020ca67c[i];
        bb = data_020ca640[k];
        v0 = (u16) t;
        pt.x = ((int) v0 >> 8) + ((bb >> 4) - 8);
        pt.z = (v1 & 0xff) + ((bb & 0xf) - 8);
        if (func_020456b0(self, &pt, i, ctx) != 0) {
            pt2.x = pt.x;
            pt2.z = pt.z;
            func_02046024((u8) b, &pt2, r, 0xfff1, 0, 0, 0, (u8) i, 0, -1);
            tz = pt.z;
            q = self + i * 2;
            q[7] = (u8) pt.x;
            q[6] = (u8) tz;
        } else {
            *(u16 *) (self + i * 2 + 6) = 0xffff;
        }
    }
    *(u16 *) (self + 0xc) = (u16) r;
}

void func_02045440(u8 *self, UnkStruct_02045440_2 *e, void *c)
{
    void *ctx;
    volatile u16 vA, vB, vC, vD, vE, vF, vG, vH, vI;
    Pt pt;
    UnkStruct_02045440 oA;
    Pt pt2;
    O12 oB;
    unsigned int one;
    unsigned int ok;
    unsigned int a, b;
    int t;
    int res;
    int u;
    int idx;
    int k;
    int bb;
    u8 tx, tz;

    vA = 0xfff1;
    pt.x = 0;
    pt.z = 0;
    ctx = (void *) func_0204e414();
    if (ctx == 0) {
        return;
    }
    vA = e->unk_04;
    one = 1;
    ok = 0;
    a = vA;
    b = vA;
    if (b >= 0x66 && a <= 0x68) {
        ok = one;
    }
    if (ok == 0) {
        if (!(a >= 0x6a && a <= 0x6c)) {
            one = 0;
        }
    }
    if (one != 0) {
        t = e->unk_04;
        if (t == 0x68 || t == 0x6c) {
            res = 0x1492;
        } else {
            vB = 0xfff1;
            func_02063ccc(&oA, 0, 0);
            func_020638d4(&vC, &oA, 0, 0, 1, 1, 0);
            vB = vC;
            func_02063cc8(&oA);
            res = vB;
        }
    } else {
        res = 0x1492;
    }
    vH = e->unk_02;
    u = vH;
    vE = (u16) u;
    vD = (u16) u;
    func_0204f794(&oB, (int) vD >> 8, vE & 0xff);
    idx = func_ov003_02223078(c, &oB);
    vI = *(u16 *) (self + 2);
    u = vI;
    vG = (u16) u;
    k = data_020ca67c[idx];
    bb = data_020ca640[k];
    vF = (u16) u;
    pt.x = ((int) vF >> 8) + ((bb >> 4) - 8);
    pt.z = (vG & 0xff) + ((bb & 0xf) - 8);
    if (func_020456b0((void *) self, &pt, idx, (int) ctx) != 0) {
        pt2.x = pt.x;
        pt2.z = pt.z;
        func_02046024((u8) (int) c, &pt2, res, 0xfff1, 0, 0, 0, 0, 0, -1);
        tz = (u8) pt.z;
        tx = (u8) pt.x;
        self[7] = tx;
        self[6] = tz;
    } else {
        *(u16 *) (self + 6) = 0xffff;
    }
    *(u16 *) (self + 0xc) = (u16) res;
}
