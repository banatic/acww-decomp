/* func_ov003_0221a8e8 @ 0x0221a8e8, 0x310 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x5c];
    int px; // 0x5c
    int py; // 0x60
    int pz; // 0x64
    u8 pad_68[0x26c - 0x68];
    int unk_26C; // 0x26c
    u8 pad_270[0x2b4 - 0x270];
    int unk_2B4; // 0x2b4
    u8 pad_2B8[0x2bc - 0x2b8];
    int unk_2BC; // 0x2bc
    u8 pad_2C0[0x2e0 - 0x2c0];
    u8 unk_2E0; // 0x2e0
    u8 pad_2E1[0x2f0 - 0x2e1];
    int unk_2F0; // 0x2f0
    int unk_2F4; // 0x2f4
    u8 pad_2F8[0x328 - 0x2f8];
    u8 unk_328[0x374 - 0x328]; // 0x328
    int unk_374;               // 0x374
    union {
        u16 u;
        struct {
            u16 : 7;
            u16 b7 : 1;
            u16 : 8;
        } bits;
    } unk_378; // 0x378
    u8 pad_37A[0x394 - 0x37a];
    short unk_394; // 0x394
    u8 pad_396[0x39c - 0x396];
    int unk_39C; // 0x39c
    int unk_3A0; // 0x3a0
} UnkStruct_0221a8e8;

typedef struct {
    u8 pad_00[0x5c];
    int px;
    int py;
    int pz;
    u8 pad_68[0x8e - 0x68];
    short unk_8E;
} UnkStruct_0221a8e8_2;

extern short FX_SinCosTable_[];
extern UnkStruct_0221a8e8_2 *func_020961a8(int);
extern int func_020b6660(void);
extern int FX_MulFunc(int, int);
extern int FX_Div(int, int);
extern void func_020e8a94(short *, int, int, int);
extern u32 func_020e8ed8(int, int);
extern u32 func_020ea990(void *, void *);
extern int func_020e8b4c(int, int);
extern void func_020e8b60(int *, int, int, int);
extern void func_020eaca0(Vec *, Vec *, Vec *);
extern int func_020ea9c8(Vec *);
extern void func_020044b0(void *, int, int, int);

int func_ov003_0221a8e8(UnkStruct_0221a8e8 *a, Vec *outPos, short *outAngle, int *outDist, int e, int f6)
{
    int t1;
    int dx;
    int dz;
    short ang[2];
    Vec vv[2];
    Vec v3;
    Vec v4;
    UnkStruct_0221a8e8_2 *ent;
    u32 dist;
    int savedX;
    int savedZ;
    Vec *ep;
    int q;
    int u;
    int tz;
    short d;
    short d2;
    short lim;

    ent = func_020961a8(4);
    if (func_020b6660() == 0) {
        return 0;
    }
    if (ent == 0) {
        return 0;
    }
    if (a->unk_3A0 != 0 || a->unk_39C != 0) {
        return 0;
    }
    if (a->unk_26C < 0xa00) {
        return 0;
    }
    if (e > 0xc32) {
        e = 0xc32;
    }

    if (a->unk_2E0 != 0) {
        a->px += a->unk_2B4;
        a->pz += a->unk_2BC;
        a->unk_378.u |= 0x200;
    }

    ang[0] = (short) f6;
    if (a->unk_378.bits.b7 != 0) {
        ang[0] = a->unk_394;
        func_020e8a94(ang, f6, 5, 0x2000);
    }

    savedX = a->unk_2F0;
    savedZ = a->unk_2F4;
    if (a->unk_378.bits.b7 == 0) {
        a->unk_2F0 = savedX >> 4;
        a->unk_2F4 = a->unk_2F4 >> 4;
    }

    t1 = FX_MulFunc(FX_MulFunc(e, 0x1b6), a->unk_374);
    dx = FX_MulFunc(t1, FX_SinCosTable_[((u16) ang[0] >> 4) * 2]);
    dz = FX_MulFunc(t1, FX_SinCosTable_[((u16) ang[0] >> 4) * 2 + 1]);
    a->unk_2F0 += dx;
    a->unk_2F4 += dz;
    a->px += a->unk_2F0;
    a->pz += a->unk_2F4;

    ang[1] = ent->unk_8E;
    func_020e8a94(&ang[1], f6, 8, 0x2000);

    ep = (Vec *) &ent->px;
    vv[0].x = ep->x;
    vv[0].y = ep->y;
    vv[0].z = ep->z;
    vv[1].x = vv[0].x + dx;
    vv[1].y = vv[0].y;
    vv[1].z = vv[0].z + dz;

    dist = func_020e8ed8(a->px - vv[1].x, a->pz - vv[1].z);
    if (func_020ea990((char *) a + 0x68, &vv[1]) > (u32) (a->unk_26C + 0x1000)) {
        a->px -= a->unk_2F0;
        a->pz -= a->unk_2F4;
        a->unk_2F0 = savedX;
        a->unk_2F4 = savedZ;
        return 0;
    }

    d = func_020e8b4c(dist, f6);
    lim = a->unk_378.bits.b7 != 0 ? 0x471c : 0x1000;
    if (d > lim) {
        a->px -= a->unk_2F0;
        a->pz -= a->unk_2F4;
        a->unk_2F0 = savedX;
        a->unk_2F4 = savedZ;
        return 0;
    }

    d2 = func_020e8b4c(ang[1], ang[0]);
    if (d2 > 0x471c) {
        a->px -= a->unk_2F0;
        a->pz -= a->unk_2F4;
        a->unk_2F0 = savedX;
        a->unk_2F4 = savedZ;
        return 0;
    }

    func_020eaca0(&v3, (Vec *) &a->px, &vv[1]);
    *outAngle = (short) func_020e8ed8(v3.x, v3.z);
    outPos->x = vv[1].x;
    outPos->y = vv[1].y;
    outPos->z = vv[1].z;
    a->unk_378.u |= 0x40;
    a->unk_394 = ang[0];
    func_020044b0(a->unk_328, 0x820, 0x7f, 0);
    q = FX_Div(a->unk_26C - 0xa00, 0xa00);
    u = FX_MulFunc(0xc00, 0x1000 - q) + 0x200;
    func_020e8b60(&a->unk_374, 0x1000, u, 0x1000);
    tz = a->unk_2F4;
    v4.x = a->unk_2F0;
    v4.y = 0;
    v4.z = tz;
    *outDist = func_020ea9c8(&v4) >> 1;
    return 1;
}
