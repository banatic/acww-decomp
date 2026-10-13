/* func_02058788 @ 0x02058788, 0x1dc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern UnkStruct_02058788 data_020cbaf0;
extern UnkStruct_02058788 data_021c9344;
extern int data_021c9354;
extern UnkStruct_02058788_2 data_021c93cc;
extern int data_021c93c0;

extern void func_0205967c(UnkStruct_02058788_3 *self, int *p);
extern void func_020e895c(int *dst, int a, int b);
extern void func_020ea6e0(int *v, int a);
extern void VEC_Add(int *dst, int *a, int *b);
extern void __register_global_object(UnkStruct_02058788_2 *a, void *cb, void *c);
extern int func_020b65c4(void);
extern void func_0204f7e0(int *dst, UnkStruct_02058788_2 *v);
extern void func_020012dc(void);

void func_02058788(UnkStruct_02058788_3 *self)
{
    int t;
    int u;
    UnkStruct_02058788_2 v;
    int lim;
    int d;
    int rx, ry, rz;

    lim = data_020cbaf0.unk_01;
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
        __register_global_object(&data_021c93cc, func_020012dc, &data_021c93c0);
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
