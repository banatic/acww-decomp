/* field_actor_68: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02217adc @ 0x02217adc, 0x114 bytes, Thumb
 * func_ov003_02217a6c @ 0x02217a6c, 0x70 bytes, Thumb
 * func_ov003_02217a38 @ 0x02217a38, 0x34 bytes, Thumb
 * func_ov003_022178cc @ 0x022178cc, 0x16c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x2d0];
    u32 unk_2D0;
    u32 unk_2D4;
    u8 pad_2D8[0x7d4 - 0x2d8];
    u8 unk_7D4[0x11c];
    u8 unk_8F0;
} UnkStruct_02217adc;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    s16 unk_0C;
    u8 unk_0E;
} ArgSub;

typedef struct {
    u8 pad_00[0xc];
    ArgSub sub;
} Arg;

struct UnkStruct_02217a6c {
    unsigned char b;
    char pad_01;
    short s;
};

typedef struct {
    char pad_00[0x5a4];
    unsigned int unk_5A4;
    char pad_5A8[0x23e];
    unsigned char unk_7E6;
} UnkStruct_02217a38;

typedef struct UnkStruct_022178cc {
    s32 state;  // 0x00
    u32 unk_04; // 0x04
    u32 unk_08; // 0x08
    s32 unk_0C; // 0x0c
    s16 unk_10; // 0x10
    u8 flags;   // 0x12
} UnkStruct_022178cc;

typedef struct UnkStruct_022178cc_2 {
    u8 pad_00[0x2d0];       // 0x000
    u8 unk_2D0[4];          // 0x2d0
    u8 pad_2D4[4];          // 0x2d4
    u32 unk_2D8;            // 0x2d8
    u8 pad_2DC[0x2c8];      // 0x2dc
    u32 unk_5A4;            // 0x5a4
    u8 pad_5A8[0x22c];      // 0x5a8
    UnkStruct_022178cc sub; // 0x7d4
    u8 pad_7E8[8];          // 0x7e8
    u32 unk_7F0;            // 0x7f0
    u8 pad_7F4[8];          // 0x7f4
    u32 unk_7FC;            // 0x7fc
} UnkStruct_022178cc_2;

extern void func_020110c4(void *out, void *self);
extern int func_02011368(void *self);
extern void func_0209971c(int val, void *ptr);
extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern unsigned int *func_0200f27c(void *self, int a);
extern void func_02056fcc(void *ptr, int a, int b, int c, int d);
extern void func_ov003_02217c3c(void *out, int a, u8 b, int c, int d, s16 e, int f);
extern void func_ov003_02217c14(void *out, u8 a, int b, int c, s16 d);
extern int func_0200f328(void *self, int a);
extern void func_ov003_02217bf0(int base, struct UnkStruct_02217a6c *out1, int *out2, int *out3, short *out4);
extern int func_ov003_02217c5c(int p1, int sel, unsigned char lowNib, int v14, int v18, short s, int const6, int p2);
extern void func_0200f268(void *, int);
extern int func_02056f28(void *a, int b);
extern void func_020108cc(void *self, int a, int b);
extern int func_02056f94(void *a);
extern u32 func_02008258(void *self, u32 a);
extern int func_0200c3b0(void *self, int a, int b, int c);
extern int func_0203e110(void);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_ov003_022188d0(void *self, u32 a, u32 b, s16 c, int d, int e);
extern int func_ov003_022186cc(void *self, int a, u32 b, u32 c, s16 d, int e, int f);

void func_ov003_02217adc(UnkStruct_02217adc *self, Arg *arg, int previous)
{
    ArgSub *p = &arg->sub;
    void *p7d4 = (char *) self + 0x7d4;
    void *p8f0;
    int var_10;
    int ret;
    u16 buf[4];
    int f0;
    u8 f4;
    int f1;
    int f2;
    s16 f3;

    func_020110c4(buf, self);
    ret = func_02011368(self);

    buf[1] = 0xfff1;
    func_0209971c(ret, &buf[1]);

    func_020109a0(self, 0x6b, 3, 0);
    func_0209971c(ret, buf);

    if ((p->unk_0E & 3) == 2) {
        u32 r1;
        func_0200f27c(self, 0);
        var_10 = 0;
        r1 = (self->unk_2D4 << 4) >> 16;
        func_02056fcc(&self->unk_2D0, r1, 3, 0x1000, (u16) (r1 - 1));
    } else {
        var_10 = 0x1000;
    }

    f0 = p->unk_00;
    f4 = p->unk_0E;
    f1 = p->unk_04;
    f2 = p->unk_08;
    f3 = p->unk_0C;

    func_ov003_02217c3c(p7d4, f0, f4, f1, f2, f3, var_10);

    p8f0 = (char *) self + 0x8f0;

    switch (f0) {
        case 0x39:
            f4 = (u8) (f4 | 0x10);
            break;
        case 0x10:
            f4 = (u8) (f4 | 0x20);
            break;
        case 2:
            f4 = (u8) (f4 | 0x30);
            break;
        case 0x38:
            break;
    }

    func_ov003_02217c14(p8f0, f4, f1, f2, f3);
    func_0200f328(self, 0x4f);
}

void func_ov003_02217a6c(int p1, int p2)
{
    struct UnkStruct_02217a6c local;
    int v14, v18;
    int sel;
    int key;

    func_ov003_02217bf0(p1 + 0x8f0, &local, &v14, &v18, &local.s);

    key = local.b & 0xf0;
    switch (key) {
        case 0x00:
            sel = 0x38;
            break;
        case 0x10:
            sel = 0x39;
            break;
        case 0x20:
            sel = 0x10;
            break;
        default:
            sel = 2;
            break;
    }

    func_ov003_02217c5c(p1, sel, local.b & 0x0f, v14, v18, local.s, 6, p2);
}

void func_ov003_02217a38(UnkStruct_02217a38 *self)
{
    if ((self->unk_7E6 & 3) == 2) {
        self->unk_5A4 = 0x1000;
    } else {
        self->unk_5A4 = 0;
        func_0200f268(self, 0);
    }
}

void func_ov003_022178cc(UnkStruct_022178cc_2 *self)
{
    UnkStruct_022178cc *sub = &self->sub;
    s32 *pCounter = &sub->unk_0C;
    s32 r7;

    if ((sub->flags & 3) == 2) {
        r7 = 0x1000;
        if (((self->unk_2D8 << 4) >> 16) < 8) {
            if (func_02056f28(&self->unk_2D0, 7) != 0) {
                func_020108cc(self, 0, 7);
            }
            if (*pCounter != 0x1000) {
                *pCounter += 0x249;
                if (*pCounter > 0x1000) {
                    *pCounter = 0x1000;
                }
            }
        }
    } else {
        r7 = 0;
        if (*pCounter != 0) {
            *pCounter -= 0x249;
            if (*pCounter < 0) {
                *pCounter = 0;
            }
        }
    }

    self->unk_5A4 = sub->unk_0C;

    if (func_02056f94(&self->unk_2D0) != 0 && r7 == *pCounter) {
        func_0200f27c(self, 1);
        switch (sub->state) {
            case 0x38:
                func_0200f268(self, 0);
                func_ov003_022188d0(self, sub->unk_04, sub->unk_08, sub->unk_10, 6, -1);
                break;
            case 0x39:
                func_0200f268(self, 0);
                func_ov003_022186cc(self, ((u32) (sub->flags & 0xc) << 22) >> 24, sub->unk_04, sub->unk_08, sub->unk_10, 6,
                                    -1);
                break;
            case 0x10:
                func_0200f268(self, 0);
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                func_0200c3b0(self, 3, 5, -1);
                break;
            case 2:
                func_0203e110();
                self->unk_7FC = func_02008258(self, self->unk_7F0);
                func_0200d4e8(self, 3, 1, -1);
                break;
            default:
                break;
        }
    }
}
