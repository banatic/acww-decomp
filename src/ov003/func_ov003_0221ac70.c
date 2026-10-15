/* func_ov003_0221ac70 @ 0x0221ac70, 0x324 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    u8 pad_00[0x34];
    int unk_34;
    u8 pad2[0x44 - 0x38];
} UnkStruct_0221ac70;

typedef struct {
    u8 pad_00[0x8];
    int unk_08; // 0x08
    u8 pad_0C[0x5c - 0xc];
    Vec pos;    // 0x5c
    Vec unk_68; // 0x68
    u8 pad2[0x26c - 0x74];
    int unk_26C;               // 0x26c
    int unk_270;               // 0x270
    u8 unk_274[0x278 - 0x274]; // 0x274
    int unk_278;               // 0x278
    u8 pad_27C[0x284 - 0x27c];
    u8 unk_284; // 0x284
    u8 pad_285[0x2a4 - 0x285];
    u8 unk_2A4[0x2ec - 0x2a4]; // 0x2a4
    int unk_2EC;               // 0x2ec
    int unk_2F0;               // 0x2f0
    int unk_2F4;               // 0x2f4
    u8 pad_2F8[0x328 - 0x2f8];
    u8 unk_328[0x369 - 0x328]; // 0x328
    u8 unk_369;                // 0x369
    u8 pad_36A[0x378 - 0x36a];
    union {
        u16 u;
        struct {
            u16 : 4;
            u16 b4 : 1;
            u16 b5 : 1;
            u16 b6 : 1;
            u16 : 3;
            u16 b10 : 1;
            u16 : 5;
        } bits;
    } unk_378; // 0x378
    u8 pad_37A[0x39c - 0x37a];
    int unk_39C; // 0x39c
    int unk_3A0; // 0x3a0
} UnkStruct_0221ac70_2;

extern int FX_Div(int, int);
extern int FX_MulFunc(int, int);
extern int VEC_Mag(Vec *);
extern int func_020e8ed8(int, int);
extern void func_020eaca0(Vec *, Vec *, Vec *);
extern void func_02031288(void *, Vec *, Vec *, int, int, UnkStruct_0221ac70_2 *, int);
extern int func_020044c0(void *, int, int, int);
extern void func_02089c20(void *, UnkStruct_0221ac70_2 *, int, int, int, int, int, int, int);
extern void func_02089fc8(void *);
extern int func_02034270(UnkStruct_0221ac70 *, Vec *, int, int);
extern void func_0203423c(UnkStruct_0221ac70 *);
extern int func_ov003_0221a8d4(UnkStruct_0221ac70_2 *);
extern void func_ov003_0221b064(UnkStruct_0221ac70_2 *, int, int);

void func_ov003_0221ac70(UnkStruct_0221ac70_2 *a)
{
    Vec v;
    UnkStruct_0221ac70 w2;
    int k;
    u32 hi;
    int lo;
    int st;
    int wm;
    int spd;
    int t2;
    int t14;
    int m;
    int ang;
    int d;
    int f;
    int r;
    int ok;
    int ok2;

    k = a->unk_378.bits.b4 != 0 ? 0xb : 0;
    if (a->unk_3A0 == 0 && a->unk_39C == 0) {
        a->pos.y -= 0x200;
    }
    func_02031288(a->unk_274, &a->pos, &a->unk_68, 0, a->unk_270, a, k);

    hi = a->unk_284;
    if (hi > a->unk_369) {
        if (a->unk_3A0 == 0 && a->unk_39C == 0) {
            func_020044c0(a->unk_328, 0x81d, 0x7f, 0);
        }
    }
    a->unk_369 = (u8) hi;

    lo = 0x20;
    if (a->unk_378.bits.b5 != 0) {
        lo |= 2;
    }
    st = 0x12;
    wm = (u8) a->unk_08;
    if (a->unk_39C == 0xb) {
        st = 0x11;
    }

    spd = FX_Div(0x41000, 0x64000);
    if (a->unk_26C < 0xa00) {
        spd = 0x1000;
    } else if (a->unk_26C < 0xe00) {
        spd = FX_Div((0x64 - ((0x23 * FX_Div(a->unk_26C - 0xa00, 0x400)) >> 12)) << 12, 0x64000);
    }
    d = a->unk_26C;
    t2 = FX_MulFunc(d, spd);
    func_02089c20(a->unk_2A4, a, t2, d * 2, lo, 0x2fc, st, wm, a->unk_2EC);
    func_02089fc8(a->unk_2A4);

    func_020eaca0(&v, &a->pos, &a->unk_68);
    m = VEC_Mag(&v);
    ang = (short) ((FX_Div(m, FX_MulFunc(0x323d, a->unk_26C)) >> 1) << 4);
    t14 = func_020e8ed8(v.x, v.z);

    if (func_ov003_0221a8d4(a) != 0) {
        f = VEC_Mag(&v);
        if (f == 0) {
            a->unk_2F0 = 0;
            a->unk_2F4 = 0;
        } else {
            ok = 0;
            if (a->unk_3A0 == 0 && a->unk_39C == 1) {
                ok = 1;
            }
            if (ok != 0) {
                r = f - FX_Div(0x2000, 0xa5000);
            } else if (a->unk_3A0 == 0 && a->unk_39C == 5) {
                r = f - 0x155;
            } else {
                wm = a->unk_278;
                if ((wm & 1) != 0) {
                    if (a->unk_378.bits.b6 != 0) {
                        r = f - 0x155;
                    } else {
                        r = f - 0x28;
                    }
                } else if ((wm & 2) != 0) {
                    r = f - 0xaa;
                } else {
                    r = f - FX_Div(0x2000, 0xa0000);
                }
            }
            if (r < 0) {
                r = 0;
            }
            if (r > 0x400) {
                r = 0x400;
            }
            f = FX_Div(r, f);
            a->unk_2F0 = FX_MulFunc(v.x, f);
            a->unk_2F4 = FX_MulFunc(v.z, f);
        }
    } else {
        a->unk_2F0 = 0;
        a->unk_2F4 = 0;
    }

    func_02034270(&w2, &a->pos, 0, 0);
    if (w2.unk_34 == 3) {
        if (a->unk_378.bits.b10 == 0) {
            a->unk_26C = FX_MulFunc(a->unk_26C, (m >> 7) + 0x1000);
            if (a->unk_26C > 0x1400) {
                a->unk_26C = 0x1400;
            }
        }
    } else {
        ok2 = 0;
        if (a->unk_3A0 == 0 && a->unk_39C == 2) {
            ok2 = 1;
        }
        if (ok2 == 0) {
            if (a->unk_3A0 != 0 || a->unk_39C != 6) {
                a->unk_26C = FX_MulFunc(a->unk_26C, 0x1000 - (m >> 9));
                if (a->unk_26C < 0x800) {
                    a->unk_26C = 0x800;
                }
            }
        }
    }
    func_ov003_0221b064(a, ang, t14);
    func_0203423c(&w2);
}
