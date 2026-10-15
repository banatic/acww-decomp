/* func_ov003_022132bc @ 0x022132bc, 0x658 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O2,s
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
    u16 unk_00, unk_02;
    s16 unk_04, unk_06, unk_08;
    u16 unk_0A;
    int pa;
    int pb;
} Msg;
typedef struct {
    u8 pad_00[4];
    int unk_04;
    int unk_08;
} T12c;

typedef struct {
    u8 pad_00[0x5c];
    Vec unk_5C;
    u8 pad_68[0x8e - 0x68];
    s16 unk_8E;
    u8 pad_90[0xec - 0x90];
    u8 unk_EC[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d4 - 0x130];
    unsigned int unk_2D4;
    unsigned int unk_2D8;
    u8 pad_2DC[0x45c - 0x2dc];
    s16 unk_45C;
    s16 unk_45E;
    u8 pad_460[0x698 - 0x460];
    Blk unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    u8 unk_7D4[0x1c];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x81c - 0x804];
    int unk_81C;
    u8 pad_820[0x8f0 - 0x820];
    u8 unk_8F0[4];
} UnkStruct_022132bc;

extern void *data_020ccf94;
extern const int data_ov003_02238144;

extern int func_0200faf0(UnkStruct_022132bc *, int);
extern int func_02073908(void *, int);
extern int func_ov003_0222e5fc(int);
extern void func_ov003_02219668(Blk *, void *);
extern int func_0203f7d0(Vec *, Vec *);
extern int func_020912d4(int, Vec *, int, int);
extern void func_ov003_0222e898(int, int);
extern void func_02091278(int, Vec *, int, int);
extern int func_02008258(UnkStruct_022132bc *, int);
extern int func_ov003_02213a8c(void *);
extern int func_ov003_02213a80(void *);
extern void func_ov003_0222eabc(int, int);
extern void func_020109fc(UnkStruct_022132bc *, int, int, int);
extern int func_0203e1c4(void);
extern void func_0203ee14(UnkStruct_022132bc *self, void *arg);
extern unsigned int *func_0200f27c(UnkStruct_022132bc *, int);
extern void func_020a8164(void *, const void *);
extern int func_0203cbd0(u16 *);
extern void func_0203ae98(void);
extern int func_0200f290(UnkStruct_022132bc *, int);
extern void func_02035638(int);
extern void func_0200f268(UnkStruct_022132bc *, int);
extern void func_02035624(int);
extern void func_02035684(int, int, int);
extern void func_020356c4(int, int, int, int);
extern int func_0203cc1c(void);
extern int func_02099fe8(void);
extern int func_02043368(int a, int *point, unsigned char *result);
extern void func_0203ee08(UnkStruct_022132bc *, void *);
extern int func_0203e19c(void);
extern int func_ov003_022131c8(UnkStruct_022132bc *, int, int, int, int);
extern int func_0203b144(void);
extern void func_0209129c(int);
extern int func_020644cc(int);
extern void func_ov003_02213ab4(void *, int);
extern void func_ov003_02213ac0(void *, int);
extern int func_ov003_0222ea84(u8);
extern int func_0200d4e8(UnkStruct_022132bc *, int, int, int);
extern int func_0200c9a8(UnkStruct_022132bc *, int, int, int);
extern int func_02011404(s16 *, int, int, int, int);
extern Vec *func_ov003_0222e970(u8);
extern int func_020e8ed8(int, int);
extern int func_020ea990(Vec *, Vec *);
extern void *func_020094a0(UnkStruct_022132bc *, int, int, int, int, int);
extern int func_ov003_0222d83c(int, s16 *, Blk *, int);

void func_ov003_022132bc(UnkStruct_022132bc *self)
{
    u8 *pb;
    void *sub;
    int kind;
    u8 *ptr7;
    int f800;
    int b8;
    void *gg;
    Msg msg;
    Blk blk1;
    Vec v68;
    Blk blk2;
    Vec w;
    Vec vb0;
    Vec vbc;
    u8 *st;
    unsigned int u;
    int u1;
    int d;
    s16 t;
    int state2;
    int n;
    void *bp;
    Vec *q;
    Vec *pv;
    int h;

    pb = self->unk_7D4;
    sub = self->unk_8F0;
    kind = pb[6];
    st = pb + 9;
    ptr7 = pb + 7;
    b8 = pb[8];
    if (kind == 0) {
        func_0200faf0(self, 0x400);
    }
    f800 = self->unk_800;
    if (*st == 0) {
        if (func_02073908(data_020ccf94, f800) != 0) {
            *st = 1;
        } else {
            *st = 9;
            if (*ptr7 != 0xff) {
                func_ov003_0222e5fc(*ptr7);
            }
        }
        if (b8 == 0x18 || b8 == 0x30 || (u8) (b8 + 0xce) <= 1) {
            blk1 = self->unk_698;
            func_ov003_02219668(&blk1, 0);
            v68.x = blk1.pos.x;
            v68.y = blk1.pos.y;
            v68.z = blk1.pos.z;
            func_0203f7d0(&v68, &v68);
            *(int *) pb = func_020912d4(0x25, &v68, 0, 0);
        }
        func_ov003_0222e898(b8, (u8) f800);
    }
    blk2 = self->unk_698;
    w.x = 0x4cd;
    w.y = 0;
    w.z = 0;
    if (self->unk_704 != 0x5c) {
        w.x = w.x + 0x333;
        w.y = w.y + 0x19a;
        w.z = w.z - 0x19a;
    } else {
        u1 = (self->unk_2D8 << 4) >> 16;
        if (u1 >= 0x24) {
            d = (int) ((u1 - 0x23) * 0x19a) / (int) (((self->unk_2D4 << 4) >> 16) - 0x24);
            w.x = w.x + d * 2;
            w.y = w.y + d;
            w.z = w.z - d;
        }
    }
    func_ov003_02219668(&blk2, &w);
    if (*(int *) pb != -1) {
        vb0.x = blk2.pos.x;
        vb0.y = blk2.pos.y;
        vb0.z = blk2.pos.z;
        func_0203f7d0(&vb0, &vb0);
        func_02091278(*(int *) pb, &vb0, 0, 0);
    }
    msg.unk_04 = 0;
    msg.unk_06 = 0;
    msg.unk_08 = 0;
    if (((self->unk_2D8 << 4) >> 16) < 0x17 && self->unk_704 == 0x5c) {
        goto post;
    }
    gg = data_020ccf94;
    if (func_02073908(gg, self->unk_800) == 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        if (*st < 6 || *st == 9) {
            if (func_ov003_02213a8c(sub) == 6) {
                func_ov003_0222eabc((u8) f800, func_ov003_02213a80(sub));
                func_020109fc(self, 0, 3, 3);
                *st = 7;
            }
        }
    }
    msg.unk_04 = 0x64;
    msg.unk_06 = 0x64;
    msg.unk_08 = 0x64;
    if (self->unk_704 == 0x5c) {
        u = (self->unk_2D8 << 4) >> 16;
        if (u <= 0x21) {
            t = (s16) ((u - 0x17) * 0xa);
            if (t >= 0x64) {
                t = 0x64;
            }
            msg.unk_04 = t;
            msg.unk_06 = t;
            msg.unk_08 = t;
        }
    }
    switch (*st) {
        case 0:
            break;
        case 1:
            if (func_0203e1c4() == 0) {
                break;
            }
            *st = 2;
            bp = (char *) self;
            if (self != 0) {
                bp = (char *) bp + 0xec;
            }
            func_0203ee14(self, bp);
            func_0200f27c(self, 0x11);
            func_020a8164(self->unk_EC, &data_ov003_02238144);
            self->unk_10A = (u8) b8;
            msg.unk_02 = (u16) (b8 + 0x12b0);
            func_0203cbd0(&msg.unk_02);
            self->unk_12C->unk_08 = 1;
            func_0203ae98();
            if (func_0200f290(self, 0x1a) != 0) {
                func_02035638(0x3f);
                func_0200f268(self, 0x1a);
            }
            func_02035624(0x12);
            func_02035684(0xc, 0, 0xe);
            func_020356c4(0xd, 0x39, 0x7f, 1);
            break;
        case 2:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            if (func_0203cc1c() != 0 && pb[10] == 0) {
                *st = 8;
                self->unk_81C = 0xd;
            } else {
                *st = 3;
                self->unk_81C = 8;
            }
            break;
        case 3:
            if (func_02099fe8() == -1) {
                msg.pa = 0;
                msg.pb = 0;
                if (func_02043368(0x10, &msg.pa, 0) != 0) {
                    *st = 4;
                    self->unk_81C = 0;
                    return;
                }
                *st = 5;
                self->unk_81C = 1;
                return;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            bp = (char *) self;
            if (self != 0) {
                bp = (char *) bp + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_0203e19c();
            func_ov003_022131c8(self, b8, 0, 6, -1);
            func_0203b144();
            break;
        case 4:
            if (self->unk_81C >= 0xf) {
                *st = 5;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            bp = (char *) self;
            if (self != 0) {
                bp = (char *) bp + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_ov003_022131c8(self, b8, 1, 6, -1);
            func_0203b144();
            break;
        case 5:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            if (*(int *) pb != -1) {
                func_0209129c(*(int *) pb);
            }
            n = (s16) (func_020644cc(0x2aaa) - 0x1555);
            func_ov003_0222eabc((u8) f800, n);
            func_ov003_02213ab4(sub, n);
            bp = (char *) self;
            if (self != 0) {
                bp = (char *) bp + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_0203e19c();
            func_020109fc(self, 0, 3, 3);
            *st = 6;
            func_ov003_02213ac0(sub, 6);
            func_0203b144();
            return;
        case 6:
            if (func_ov003_0222ea84(f800) != 3) {
                if (self->unk_45C != 0) {
                    goto Lzero;
                }
                if (self->unk_45E != 0) {
                    goto Lzero;
                }
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                switch (kind) {
                    case 2:
                        if (func_02073908(gg, self->unk_800) != 0) {
                            if (func_0200f290(self, 0x11) != 0) {
                                func_0200f268(self, 0x11);
                                bp = (char *) self;
                                if (self != 0) {
                                    bp = (char *) bp + 0xec;
                                }
                                func_0203ee08(self, bp);
                            }
                            func_0203e19c();
                        }
                        // fallthrough
                    case 0:
                    case 3:
                        func_0200d4e8(self, 3, 1, -1);
                        return;
                    case 1:
                        func_0200c9a8(self, 3, 5, -1);
                        return;
                }
                return;
            Lzero:
                func_02011404(&self->unk_45C, 0, 0x400, 0x1770000, 0xc0000);
                func_02011404(&self->unk_45E, 0, 0x400, 0x1770000, 0xc0000);
                return;
            } else {
                q = func_ov003_0222e970(f800);
                pv = &self->unk_5C;
                vbc.x = pv->x;
                vbc.y = pv->y;
                vbc.z = pv->z;
                vbc.y += 0x1b33;
                n = func_020e8ed8(q->x - vbc.x, q->z - vbc.z);
                h = func_020ea990(q, &vbc);
                h = func_020e8ed8(q->y - vbc.y, h);
                if (h >= 0x1800) {
                    h = 0x1800;
                }
                n = (s16) (n - self->unk_8E);
                func_02011404(&self->unk_45C, h, 0x400, 0x1770000, 0xc0000);
                func_02011404(&self->unk_45E, n, 0x400, 0x1770000, 0xc0000);
                return;
            }
        case 7:
            state2 = func_ov003_0222ea84(f800);
            if (state2 == 3 || state2 == 0) {
                *st = 6;
            }
            return;
        case 8:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            bp = (char *) self;
            if (self != 0) {
                bp = (char *) bp + 0xec;
            }
            func_0203ee08(self, bp);
            func_0200f268(self, 0x11);
            func_0203e19c();
            func_020094a0(self, 0, b8, *ptr7, 6, -1);
            return;
    }
post:
    func_ov003_0222d83c((u8) f800, &msg.unk_04, &blk2, 0);
}
