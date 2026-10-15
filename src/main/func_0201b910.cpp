/* func_0201b910 @ 0x0201b910, 0x3d8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[12];
} Buf48;

class UnkStruct_0201b910 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    u8 pad_04[0x5c - 0x04];
    Vec3 unk_5C;
    int unk_68;
    u8 pad_6C[0x8e - 0x6c];
    short unk_8E;
    u8 pad_90[0xc4 - 0x90];
    int unk_C4;
    u8 pad_C8[0xd0 - 0xc8];
    u16 unk_D0;
    u8 pad_D2[0xec - 0xd2];
    int unk_EC;
    u8 pad_F0[0x150 - 0xf0];
    Buf48 unk_150;
    u8 pad_180[0x190 - 0x180];
    int unk_190;
    u8 pad_194[0x2ac - 0x194];
    int unk_2AC;
    u8 pad_2B0[0x334 - 0x2b0];
    int unk_334;
    u8 pad_338[0x350 - 0x338];
    int unk_350;
    u8 pad_354[0x3a8 - 0x354];
    int unk_3A8;
    u8 pad_3AC[0x3b0 - 0x3ac];
    int unk_3B0;
    u8 pad_3B4[0x420 - 0x3b4];
    int unk_420;
    u8 pad_424[0x478 - 0x424];
    int unk_478;
    u8 pad_47C[0x49c - 0x47c];
    int unk_49C;
    u8 pad_4A0[0x4cc - 0x4a0];
    int unk_4CC;
    u8 pad_4D0[0x4e8 - 0x4d0];
    int unk_4E8;
    u8 pad_4EC[0x510 - 0x4ec];
    u8 unk_510;
    u8 pad_511[0x514 - 0x511];
    int unk_514;
    u8 pad_518[0x558 - 0x518];
    int unk_558;
    u8 pad_55C[0x561 - 0x55c];
    u8 unk_561;
    u8 pad_562[0x563 - 0x562];
    u8 unk_563;
    int unk_564;
    u8 pad_568[0x618 - 0x568];
    int unk_618;
    u8 pad_61C[0x628 - 0x61c];
    int unk_628;
    u8 unk_62C;
    u8 pad_62D[0x638 - 0x62d];
    int unk_638;
};

typedef struct {
    int w[4];
} Opaque16;

extern "C" {
extern u16 data_020c80f8;

extern void func_0201b2d8(int *a, UnkStruct_0201b910 *b);
extern int func_0201c0e0(UnkStruct_0201b910 *a);
extern int func_0201beb0(UnkStruct_0201b910 *a, int *b, int *c, Opaque16 *d);
extern int func_02019e00(int *a);
extern int func_02019d0c(int *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern int func_02019c6c(int *a, int b, int c);
extern void func_02019a84(int *a, int *b, int *c, int *d, short *e, short *f, Opaque16 *g);
extern void func_02019a2c(short *a, short *b, short *c, Opaque16 *d);
extern void func_020199f8(int *a, u8 *b, short *c, short *d, Opaque16 *e);
extern int func_02019c20(int *a, int b, int c, int d, int e, int f);
extern void func_020199d8(u16 *a, Opaque16 *b);
extern int func_020172d8(int *a, int b, u16 *c);
extern void func_02014688(int *a, UnkStruct_0201b910 *b);
extern void func_0201998c(int *a, UnkStruct_0201b910 *b);
extern int func_020164a0(int *a, int b);
extern void func_0201a48c(int *a, int *b, int c, int d, int e);
extern void func_0201b078(int *a, UnkStruct_0201b910 *b);
extern int func_020a7278(void);
extern void func_02031288(int *a, int *b, int *c, int d, int e, UnkStruct_0201b910 *f, int g);
extern int func_020310c8(int a);
extern void func_0201a838(int *a, UnkStruct_0201b910 *b);
extern void func_0201af0c(int *a);
extern void func_0201ae44(int *a, UnkStruct_0201b910 *b);
extern u16 func_0203f8d0(int *a, int *b);
extern void func_020031d4(UnkStruct_0201b910 *a, Buf48 *b);
extern int func_0201c014(UnkStruct_0201b910 *a);
extern void func_02089fc8(int *a);
extern void func_02089fe4(int *a);
extern void func_02016384(int *a, UnkStruct_0201b910 *b);
extern void func_020542e0(int *a);
extern void func_02004444(int *a, Vec3 *b);
extern void func_02012250(int a, UnkStruct_0201b910 *b);
extern void func_02013abc(int *a, UnkStruct_0201b910 *b);
extern void func_02019f1c(int *a, UnkStruct_0201b910 *b);
extern void func_02019948(int *a, UnkStruct_0201b910 *b);
extern void func_0201bf24(UnkStruct_0201b910 *a, int b);
}

extern "C" int func_0201b910(UnkStruct_0201b910 *self)
{
    u8 q0;
    short q2, q4, q6, q8;
    u16 qa;
    int a;
    int b;
    int c;
    int d;
    int e;
    Buf48 buf;
    Opaque16 obj;
    Vec3 vec;
    int k;
    Vec3 *p;

    func_0201b2d8(&self->unk_350, self);
    self->v26();
    if (self->unk_561 == 0) {
        return 1;
    }
    if (func_0201c0e0(self) == 0) {
        a = 0x16;
        b = 0;
        if (func_0201beb0(self, &a, &b, &obj) != 0) {
            if (b == 1 && (unsigned int) a <= 2) {
                if (func_02019e00(&self->unk_564) != 0x15) {
                    func_02019d0c(&self->unk_564, 0x15, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
                }
                if (a == 1 || a == 2) {
                    self->unk_564 = a;
                } else {
                    self->unk_564 = 0;
                }
            } else {
                k = a;
                if (k != func_02019e00(&self->unk_564)) {
                    c = 0;
                    q2 = 0;
                    q4 = 0;
                    d = 0;
                    q6 = 0;
                    q8 = 0;
                    b = 3;
                    switch (k) {
                        case 0:
                            func_02019c6c(&self->unk_564, 3, data_020c80f8);
                            break;
                        case 1:
                        case 2:
                            func_02019a84(&c, &c, &d, &d, &q2, &q6, &obj);
                            func_02019d0c(&self->unk_564, a, b, c, 0, q2, q4, d, 0, (u16) q6, 0);
                            break;
                        case 3:
                            func_02019a2c(&q2, &q4, &q6, &obj);
                            func_02019d0c(&self->unk_564, a, b, c, 0, q2, q4, d, 0, (u16) q6, 0);
                            break;
                        case 0xc:
                            e = 0x137;
                            q0 = 0;
                            func_020199f8(&e, &q0, &q6, &q8, &obj);
                            func_02019c20(&self->unk_564, b, e, q0, (u16) q6, (u16) q8);
                            break;
                        case 0x14:
                            qa = 0xfff1;
                            func_020199d8(&qa, &obj);
                            func_020172d8(&self->unk_564, b, &qa);
                            break;
                    }
                }
            }
        }
    }
    func_02014688(&self->unk_618, self);
    func_0201998c(&self->unk_564, self);
    func_0201a48c(&self->unk_420, &self->unk_478, self->unk_8E, func_020164a0(&self->unk_334, 0), (u16) (self->unk_190 >> 12));
    func_0201b078(&self->unk_350, self);
    if (func_020a7278() != 0 && self->unk_510 != 0 && self->unk_638 > 0) {
        func_02031288(&self->unk_49C, &self->unk_5C.x, &self->unk_68, self->unk_8E, self->unk_638, self, 0xf);
    }
    self->unk_5C.y = func_020310c8(0);
    func_0201a838(&self->unk_3B0, self);
    func_0201af0c(&self->unk_3A8);
    func_0201ae44(&self->unk_3A8, self);
    self->unk_D0 = func_0203f8d0(&self->unk_C4, &self->unk_5C.x);
    func_020031d4(self, &buf);
    self->unk_150 = buf;
    if (func_0201c014(self) != 0) {
        if ((self->unk_4E8 & 2) == 0) {
            if (func_020a7278() != 0) {
                self->unk_4E8 |= 2;
                self->unk_62C = 1;
            }
        }
    } else {
        if (self->unk_62C == 1) {
            if (func_020a7278() != 0) {
                self->unk_4E8 &= ~2;
                self->unk_62C = 0;
            }
        }
    }
    if (self->unk_510 != 0) {
        func_02089fc8(&self->unk_4CC);
    } else {
        func_02089fe4(&self->unk_4CC);
    }
    func_02016384(&self->unk_334, self);
    func_020542e0(&self->unk_EC);
    p = &self->unk_5C;
    vec.x = self->unk_5C.x;
    vec.y = p->y;
    vec.z = p->z;
    func_02004444(&self->unk_514, &vec);
    if (self->unk_628 != 0) {
        func_02012250(self->unk_628, self);
    }
    func_02013abc(&self->unk_558, self);
    func_02019f1c(&self->unk_2AC, self);
    func_02019948(&self->unk_564, self);
    if (self->unk_563 == 0) {
        func_0201bf24(self, 1);
    }
    return 1;
}
