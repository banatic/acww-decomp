/* obj_020dd33c_modes_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02058788 @ 0x02058788, 0x1dc bytes, Thumb
 * func_020586b0 @ 0x020586b0, 0xd8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 unk_00, unk_01;
} UnkStruct_02058788;

typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_02058788_2;

typedef struct {
    u8 pad_00[0x60];
    int unk_60, unk_64, unk_68, unk_6C, unk_70, unk_74, unk_78, unk_7C, unk_80, unk_84, unk_88, unk_8C, unk_90, unk_94, unk_98;
    u8 pad_9C[0xc];
    int unk_A8, unk_AC, unk_B0;
    u8 pad_B4[0x18];
    u8 *unk_CC;
    u8 pad_D0[4];
    u8 unk_D4;
    u8 unk_D5;
    u16 unk_D6;
} UnkStruct_02058788_3;

struct UnkStruct_020586b0 {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x60 - 0x52];
    u32 unk_60;
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u8 pad_78[0x90 - 0x78];
    u32 unk_90;
    u32 unk_94;
    u32 unk_98;
    u8 pad_9C[0xa8 - 0x9c];
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0xd4 - 0xb4];
    u8 unk_D4;
    u8 _paddr[0xd6 - 0xd5];
    u16 unk_D6;
    u8 _padr2[0xdc - 0xd8];
    u32 unk_DC;
};

extern UnkStruct_02058788 data_021c9344;
extern int data_021c9354;
extern UnkStruct_02058788_2 data_021c93cc;
extern int data_021c93c0;
extern void func_0205967c(UnkStruct_02058788_3 *self, int *p);
extern int func_020e895c(int *dst, int a, int b);
extern void func_020ea6e0(int *v, int a);
extern void VEC_Add(int *dst, int *a, int *b);
extern void __register_global_object(void *, void *, void *);
extern int func_020b65c4(void);
extern void func_0204f7e0(int *dst, UnkStruct_02058788_2 *v);
extern void func_020012dc(void *);
extern const u8 data_020cbaf0[];
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_02059674(void *self, int a);

void func_02058788(UnkStruct_02058788_3 *self)
{
    int t;
    int u;
    UnkStruct_02058788_2 v;
    int lim;
    int d;
    int rx, ry, rz;

    lim = (*(UnkStruct_02058788 *) data_020cbaf0).unk_01;
    if (self->unk_D6 >= lim) {
        return;
    }
    t = self->unk_A8;
    func_0205967c(self, &self->unk_60);
    func_020e895c(&t, 0x1000, 0x200);
    u = t;
    self->unk_A8 = u;
    self->unk_AC = u;
    self->unk_B0 = u;
    func_020e895c(&self->unk_84, self->unk_6C, self->unk_90);
    func_020e895c(&self->unk_88, self->unk_70, self->unk_94);
    func_020e895c(&self->unk_8C, self->unk_74, self->unk_98);
    if (self->unk_CC != 0) {
        self->unk_78 = self->unk_84;
        self->unk_7C = self->unk_88;
        self->unk_80 = self->unk_8C;
        func_020ea6e0(&self->unk_78, *(short *) (self->unk_CC + 0x8e));
    }
    VEC_Add(&self->unk_60, &self->unk_78, &self->unk_60);
    self->unk_D6 = (u16) (self->unk_D6 + 1);
    if (self->unk_D6 < lim) {
        return;
    }
    if ((data_021c9354 & 1) == 0) {
        data_021c93cc.unk_00 = 0x10000;
        data_021c93cc.unk_04 = 0;
        data_021c93cc.unk_08 = 0x17000;
        __register_global_object((void *) (&data_021c93cc), (((void *) func_020012dc)), (void *) (&data_021c93c0));
        data_021c9354 |= 1;
    }
    v.unk_00 = 0;
    v.unk_04 = 0;
    v.unk_08 = 0x2000;
    if (func_020b65c4() == 0x10) {
        self->unk_6C = data_021c93cc.unk_00;
        self->unk_70 = data_021c93cc.unk_04;
        self->unk_74 = data_021c93cc.unk_08;
    } else {
        func_020ea6e0(&v.unk_00, *(short *) (self->unk_CC + 0x8e));
        VEC_Add(&v.unk_00, (int *) (self->unk_CC + 0x5c), &v.unk_00);
        func_0204f7e0(&self->unk_6C, &v);
    }
    self->unk_70 = self->unk_70 + 0x1000;
    d = data_021c9344.unk_01;
    rz = (self->unk_74 - self->unk_68) / d;
    if (rz < 0) {
        rz = -rz;
    }
    ry = (self->unk_70 - self->unk_64) / d;
    if (ry < 0) {
        ry = -ry;
    }
    rx = (self->unk_6C - self->unk_60) / d;
    if (rx < 0) {
        rx = -rx;
    }
    self->unk_90 = rx;
    self->unk_94 = ry;
    self->unk_98 = rz;
    self->unk_D4 = 2;
}

void func_020586b0(struct UnkStruct_020586b0 *self)
{
    u32 v;
    u8 limit;
    unsigned int cond;

    limit = data_020cbaf0[2];
    if ((int) self->unk_D6 >= (int) limit) {
        return;
    }

    v = self->unk_A8;
    func_020e895c((int *) (&v), 0x1000, 0x200);
    {
        u32 w = v;
        self->unk_A8 = w;
        self->unk_AC = w;
        self->unk_B0 = w;
    }

    func_020e895c((int *) (&self->unk_60), self->unk_6C, self->unk_90);
    func_020e895c((int *) (&self->unk_64), self->unk_70, self->unk_94);
    func_020e895c((int *) (&self->unk_68), self->unk_74, self->unk_98);

    self->unk_D6 = (u16) (self->unk_D6 + 1);
    if ((int) self->unk_D6 < (int) limit) {
        return;
    }

    cond = 0;
    if ((unsigned) self->unk_50 >= 0x1492u && (unsigned) self->unk_50 <= 0x14fdu) {
        cond = 1;
    }
    if (cond > 0) {
        func_020044c0(&self->unk_DC, 0x70, 0x7f, 0);
    }

    self->unk_D4 = 3;
    func_02059674(self, 0);
}
