/* func_ov068_0226f854 @ 0x0226f854, 0x3d8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    u8 b[0x40];
} UnkStruct_0226f854;

typedef struct {
    u8 pad_00[0x5c];
    Vec pos; // 0x5c
    u8 pad_68[0x70 - 0x68];
    int unk_70; // 0x70
    u8 pad_74[0x26c - 0x74];
    int unk_26C; // 0x26c
    int unk_270; // 0x270
    u8 pad_274[0x280 - 0x274];
    s16 unk_280[2]; // 0x280
    u8 unk_284;     // 0x284
    u8 pad_285[0x2f0 - 0x285];
    int unk_2F0; // 0x2f0
    int unk_2F4; // 0x2f4
    u8 pad_2F8[0x36c - 0x2f8];
    int unk_36C; // 0x36c
    int unk_370; // 0x370
    u8 pad_374[0x378 - 0x374];
    union {
        u16 u;
        struct {
            u16 f01 : 2;
            u16 f23 : 2;
            u16 : 2;
            u16 f6 : 1;
            u16 : 1;
            u16 f8 : 1;
            u16 : 7;
        } b;
    } unk_378; // 0x378
    u8 pad_37A[0x39c - 0x37a];
    int unk_39C; // 0x39c
    int unk_3A0; // 0x3a0
} UnkStruct_0226f854_2;

extern int data_021c80bc;
extern u8 data_021f3b56[];

extern int FX_MulFunc(int, int);
extern int FX_Div(int, int);
extern int func_020ea9e4(Vec *, Vec *);
extern int func_020ea990(Vec *, Vec *);
extern int func_020e8ed8(int, int);
extern int func_020e8b4c(int, int);
extern UnkStruct_0226f854_2 *func_ov003_02236128(UnkStruct_0226f854_2 *);
extern void func_0204f818(int *, int *, Vec *);
extern u16 *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204c71c(u16 *);
extern int func_02031acc(int, int);
extern int func_ov068_0226fd28(int);
extern int func_020b060c(u8 *, int, int, int);
extern void func_020b0400(void);
extern int func_ov003_0221abf8(void *object, int flag);
extern int func_ov003_0221a35c(UnkStruct_0226f854_2 *, int);
extern void func_ov068_0226fd80(UnkStruct_0226f854_2 *);
extern int func_02034270(UnkStruct_0226f854 *, Vec *, int, int);
extern int func_020341c8(UnkStruct_0226f854 *, int);
extern void func_0203423c(UnkStruct_0226f854 *);
extern void func_0204f7e0(Vec *, Vec *);
extern u16 *func_0204f5a8(int, Vec *, int);

void func_ov068_0226f854(UnkStruct_0226f854_2 *self)
{
    // DECLS
    int map;
    int dist;
    int rad;
    u16 tile;
    int gx;
    int gy;
    int lx;
    int ly;
    int qx;
    int qy;
    UnkStruct_0226f854 w1;
    UnkStruct_0226f854 w2;
    Vec v;
    UnkStruct_0226f854_2 *other;
    int t;
    int sp;
    int res;
    int idx;
    int n;
    int ang;
    int ok;
    u16 *rec;
    // ENDDECLS

    map = data_021c80bc;
    self->unk_270 = self->unk_26C;
    t = self->unk_2F4;
    sp = FX_MulFunc(self->unk_2F0, self->unk_2F0) + FX_MulFunc(t, t);
    if (self->unk_3A0 != 0) {
        goto walk;
    }
    if (self->unk_39C != 0) {
        goto walk;
    }
    if (sp <= 0) {
        goto walk;
    }
    if (self->unk_26C < 0xa00) {
        goto walk;
    }
    if (self->unk_378.b.f6 == 0) {
        goto walk;
    }
    other = func_ov003_02236128(self);
    if (other == 0) {
        goto walk;
    }
    if (other->unk_26C < 0xa00) {
        goto walk;
    }
    dist = func_020ea9e4(&self->pos, &other->pos);
    rad = FX_Div(0, 0x64000) + 0x400;
    func_0204f818(&gx, &gy, &other->pos);
    tile = 0xfff1;
    if (map != 0) {
        lx = gx;
        ly = gy;
        qx = lx >> 4;
        qy = ly >> 4;
        rec = func_0204f5e0(map, qx, qy, lx - (qx << 4), ly - (qy << 4), 0);
        if (rec != 0) {
            tile = rec[0];
        }
    }
    if (func_0204c71c(&tile) != 0) {
        goto walk;
    }
    if (other == 0) {
        goto walk;
    }
    if (dist >= rad + (self->unk_26C + other->unk_26C)) {
        goto walk;
    }
    if (other->unk_3A0 != 0) {
        goto walk;
    }
    if (other->unk_39C != 0) {
        goto walk;
    }
    res = func_02031acc(gx, gy);
    if (res != 0 && res != 1) {
        goto walk;
    }
    n = func_ov068_0226fd28(FX_Div(self->unk_26C, other->unk_26C));
    res = func_020b060c(data_021f3b56, self->unk_26C, other->unk_26C, n);
    if (res == -1) {
        goto walk;
    }
    other->unk_378.b.f01 = (u16) res;
    self->unk_378.b.f01 = other->unk_378.b.f01;
    other->unk_378.b.f23 = (u16) n;
    self->unk_378.b.f23 = other->unk_378.b.f23;
    other->unk_378.b.f8 = 1;
    self->unk_378.b.f8 = other->unk_378.b.f8;
    func_ov003_0221a35c(self, 8);
    func_ov003_0221a35c(other, 7);
    if (n != 0) {
        return;
    }
    func_020b0400();
    return;

walk:
    func_ov068_0226fd80(self);
    func_02034270(&w1, &self->pos, 0, 0);
    if (func_020341c8(&w1, 0) < 0) {
        func_ov003_0221a35c(self, 1);
        func_0203423c(&w1);
        return;
    }
    func_02034270(&w2, &self->pos, 1, 0);
    if (*(int *) ((u8 *) &w2 + 0x30) == 1) {
        switch (*(int *) ((u8 *) &w2 + 0x34)) {
            case 0x16:
            case 0x17:
                func_ov003_0221a35c(self, 5);
                func_0203423c(&w2);
                func_0203423c(&w1);
                return;
        }
    }
    func_0203423c(&w2);
    if (map != 0) {
        func_0204f7e0(&v, &self->pos);
        rec = func_0204f5a8(map, &self->pos, 0);
        if (rec != 0) {
            ok = 0;
            if (rec[0] >= 0xfc && rec[0] <= 0xfd) {
                ok = 1;
            }
            if (ok != 0) {
                if (func_020ea990(&v, &self->pos) < 0x1000) {
                    other = func_ov003_02236128(self);
                    if (other != 0 && other->unk_3A0 == 0 && other->unk_39C == 4) {
                        if (func_020ea990(&other->pos, &self->pos) > other->unk_26C + self->unk_26C) {
                            if (func_ov003_0221a35c(self, 4) != 0) {
                                func_0203423c(&w1);
                                return;
                            }
                        }
                        goto after;
                    }
                    if (func_ov003_0221a35c(self, 4) != 0) {
                        func_0203423c(&w1);
                        return;
                    }
                }
            }
        }
    }
after:
    self->unk_36C = self->unk_2F0;
    self->unk_370 = self->pos.z - self->unk_70;
    if (self->unk_3A0 != 0) {
        goto done;
    }
    if (self->unk_39C != 0) {
        goto done;
    }
    if (self->unk_378.b.f6 != 0) {
        goto done;
    }
    t = self->unk_370;
    sp = FX_MulFunc(self->unk_36C, self->unk_36C) + FX_MulFunc(t, t);
    if (sp < FX_Div(0x12c000, 0x2710000)) {
        goto done;
    }
    n = self->unk_284;
    if (n == 0) {
        goto done;
    }
    ang = func_020e8ed8(self->unk_36C, self->unk_370);
    for (idx = 0; (u32) idx < (u32) n; idx++) {
        if (func_020e8b4c((short) (self->unk_280[idx] + 0x8000), ang) < 0x1000) {
            if (func_ov003_0221abf8(self, 1) != 0) {
                func_0203423c(&w1);
                return;
            }
        }
    }
done:
    func_0203423c(&w1);
}
