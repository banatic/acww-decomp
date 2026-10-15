/* func_ov003_02212d2c @ 0x02212d2c, 0x39c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec;
typedef struct {
    int a[9];
    Vec pos;
} Blk;

typedef struct {
    u8 pad_00[0x5c];
    Vec pos; // 0x5c
    u8 pad_68[0xec - 0x68];
    u8 unk_EC[0x2d0 - 0xec];   // 0xec
    u8 unk_2D0[0x2d8 - 0x2d0]; // 0x2d0
    int unk_2D8;               // 0x2d8
    u8 pad_2DC[0x45c - 0x2dc];
    s16 unk_45C; // 0x45c
    s16 unk_45E; // 0x45e
    u8 pad_460[0x5a0 - 0x460];
    u8 unk_5A0[0x698 - 0x5a0]; // 0x5a0
    Blk unk_698;               // 0x698
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704; // 0x704
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[2]; // 0x7d4
    u8 pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0; // 0x7f0
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC; // 0x7fc
    int unk_800; // 0x800
    u8 pad_804[0x81c - 0x804];
    int unk_81C; // 0x81c
    u8 pad_820[0x8f0 - 0x820];
    u8 unk_8F0[4]; // 0x8f0
} UnkStruct_02212d2c;

extern int data_020ccf94;

extern int func_02056f94(void *);
extern void func_ov003_0222e6c4(u8, int);
extern int func_02008258(UnkStruct_02212d2c *, int);
extern int func_0200d4e8(UnkStruct_02212d2c *, int, int, int);
extern int func_02073908(int, int);
extern int func_0209a110(s16 *);
extern void func_020109fc(UnkStruct_02212d2c *, int, int, int);
extern void func_0205eae0(void *, int, int, int);
extern int func_0203f8d0(Vec *, Vec *);
extern int func_0206f728(int);
extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_0200f290(UnkStruct_02212d2c *, int);
extern void func_0200f268(UnkStruct_02212d2c *, int);
extern void func_0203ee08(UnkStruct_02212d2c *, void *);
extern int func_0203e19c(void);
extern int func_020644cc(int);
extern void func_ov003_0222eabc(u8, int);
extern void func_ov003_02213198(void *, int);
extern void func_ov003_022131a4(void *, int);
extern int func_ov003_02213174(void *);
extern int func_ov003_02213168(void *);
extern int func_ov003_0222ea84(u8);
extern int func_02011404(void *, int, int, int, int);
extern Vec *func_ov003_0222e970(u8);
extern void func_ov003_02219668(Blk *, int);
extern int func_ov003_0222d83c(u8, s16 *, Blk *, int);
extern int func_020e8ed8(int, int);
extern int func_020ea990(void *, void *);

void func_ov003_02212d2c(UnkStruct_02212d2c *a)
{
    int flag;
    int msg;
    int rnd;
    s16 arr[4];
    Vec v;
    Blk blk;
    Vec w;
    Vec v2;
    int kind;
    s16 ini;
    u32 t;
    Vec *pv;
    u8 *pf;
    u8 *base;
    int st;
    void *sub;
    u8 *pst;
    Vec *tv;
    int ang;
    int dy;
    Vec *pv2;
    int tx;
    int ty;
    int tz;

    flag = 0;
    pv = &a->pos;
    v.x = pv->x;
    v.y = pv->y;
    v.z = pv->z;
    kind = a->unk_800;
    if (a->unk_704 == 0x5d) {
        t = (u32) (a->unk_2D8 << 4) >> 16;
        if (t < 6) {
            ini = (s16) (0x64 - (t << 4));
        } else {
            ini = (s16) flag;
        }
    } else {
        ini = (s16) flag;
    }
    arr[1] = ini;
    arr[2] = ini;
    arr[3] = ini;

    blk = a->unk_698;
    func_ov003_02219668(&blk, 0);

    pf = a->unk_7D4;
    sub = a->unk_8F0;
    pst = pf + 1;
    msg = (u16) (pf[0] + 0x12b0);
    switch (pf[1]) {
        case 0:
            if (func_02056f94(a->unk_2D0) == 0) {
                break;
            }
            func_ov003_0222e6c4((u8) a->unk_800, 1);
            a->unk_7FC = func_02008258(a, a->unk_7F0);
            func_0200d4e8(a, 6, 1, -1);
            if (func_02073908(data_020ccf94, a->unk_800) != 0) {
                arr[0] = (s16) msg;
                func_0209a110(arr);
            }
            flag = 1;
            break;
        case 1:
            if (a->unk_704 == 0x5d) {
                if (func_02056f94(a->unk_2D0) == 0) {
                    break;
                }
                func_020109fc(a, 0x6c, 3, 3);
                func_0205eae0(a->unk_5A0, 0, 3, 0);
            }
            v.x -= 0x400;
            v.y += 0x1b34;
            v.z += 0x1400;
            func_0203f8d0(&v, &v);
            blk.pos.x = v.x;
            blk.pos.y = v.y;
            blk.pos.z = v.z;
            if (func_02073908(data_020ccf94, a->unk_800) != 0) {
                if (a->unk_81C == 5) {
                    if (func_0206f728(msg) == 0) {
                        break;
                    }
                    a->unk_81C = 6;
                    break;
                }
                if (a->unk_81C == 6) {
                    if (func_0206fbc0() == 0) {
                        break;
                    }
                    a->unk_81C = 0xf;
                    if (func_0206fc6c() != 0) {
                        if (func_0200f290(a, 0x11) != 0) {
                            func_0200f268(a, 0x11);
                            base = (u8 *) a;
                            if (a != 0) {
                                base = a->unk_EC;
                            }
                            func_0203ee08(a, base);
                        }
                        func_0203e19c();
                        a->unk_7FC = func_02008258(a, a->unk_7F0);
                        func_0200d4e8(a, 6, 1, -1);
                        return;
                    }
                } else if (a->unk_81C < 0xf) {
                    break;
                }
                rnd = (s16) (func_020644cc(0x2aaa) - 0x1555);
                func_ov003_0222eabc((u8) kind, rnd);
                func_ov003_02213198(sub, rnd);
                if (func_0200f290(a, 0x11) != 0) {
                    func_0200f268(a, 0x11);
                    base = (u8 *) a;
                    if (a != 0) {
                        base = a->unk_EC;
                    }
                    func_0203ee08(a, base);
                }
                func_0203e19c();
                *pst = 2;
                func_ov003_022131a4(sub, 2);
                func_020109fc(a, 0, 4, 4);
                return;
            }
            a->unk_7FC = func_02008258(a, a->unk_7F0);
            if (func_ov003_02213174(sub) != 2) {
                return;
            }
            func_ov003_0222eabc((u8) kind, func_ov003_02213168(sub));
            *pst = 2;
            func_020109fc(a, 0, 4, 4);
            return;
        case 2:
            if (func_ov003_0222ea84((u8) kind) != 3) {
                if (a->unk_45C == 0 && a->unk_45E == 0) {
                    a->unk_7FC = func_02008258(a, a->unk_7F0);
                    func_0200d4e8(a, 6, 1, -1);
                    return;
                }
                func_02011404(&a->unk_45C, 0, 0x400, 0x1770000, 0xc0000);
                func_02011404(&a->unk_45E, 0, 0x400, 0x1770000, 0xc0000);
                return;
            }
            tv = func_ov003_0222e970((u8) kind);
            pv2 = &a->pos;
            tx = pv2->x;
            v2.x = tx;
            ty = pv2->y;
            v2.y = ty;
            tz = pv2->z;
            v2.z = tz;
            v2.y = ty + 0x1b33;
            ang = func_020e8ed8(tv->x - tx, tv->z - tz);
            dy = func_020e8ed8(tv->y - v2.y, func_020ea990(tv, &v2));
            a->unk_45E = (s16) ang;
            if (dy >= 0x1800) {
                dy = 0x1800;
            }
            a->unk_45C = (s16) dy;
            return;
    }
    func_ov003_0222d83c((u8) kind, &arr[1], &blk, flag);
}
