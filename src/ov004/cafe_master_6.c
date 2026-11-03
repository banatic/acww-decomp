/* cafe_master_6: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02224c68 @ 0x02224c68, 0x118 bytes, Thumb
 * func_ov004_02224bdc @ 0x02224bdc, 0x8c bytes, Thumb
 * func_ov004_02224b30 @ 0x02224b30, 0xac bytes, Thumb
 * func_ov004_02224b0c @ 0x02224b0c, 0x24 bytes, Thumb
 * func_ov004_02224acc @ 0x02224acc, 0x40 bytes, Thumb
 * func_ov004_02224ac4 @ 0x02224ac4, 0x8 bytes, Thumb
 * func_ov004_02224abc @ 0x02224abc, 0x8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02224acc {
    u8 pad_00[0xec];
    u8 sub[0x718 - 0xec];
    u8 a[0x748 - 0x718];
    u8 b[4];
};

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_ov004_022546e0;
extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov004_02224598(void *);
extern int func_0202edc8(void *self);
extern void func_0201c280(void *self, void *p);
extern void func_ov004_02224544(void *p, void *self);
extern void func_0201c3f4(void *self, int a);
extern void func_0203edf4(void *self, int a);
extern void func_0201af28(void *p, int a, int b, int c, int d);
extern void func_0201b38c(void *p, int a);
extern void func_0201b388(void *p, int a);
extern void func_0201b384(void *p, int a);
extern int func_0202ec58(void *self);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern short *func_0209d358(int a, int b);
extern int func_020a7278(void);
extern void func_ov004_022249b4(void *self, int a);
extern int func_02073dd4(char *g, int a);
extern int func_02003348(int a, int b, void *c, void *d, int e);
extern char *data_ov004_022580dc;
extern int data_ov004_02247760;
extern int data_ov004_02247758;
extern int func_0202ec14(void *parameter0);
extern int func_0201b790(struct UnkStruct_02224acc *self);
extern int func_02055d0c(void *dst, void *src, int n);
extern void func_ov004_0222de98(void);
extern char data_ov004_022545fc[];
extern char data_ov004_022545cc[];

void *func_ov004_02224c68(void)
{
    u8 *p;

    p = (u8 *) func_020edf70(0x780);
    if (p) {
        func_0203f130(p);
        *(void **) p = &data_020d8c64;
        *(u16 *) (p + 0xea) = 0xfff1;
        func_0205467c(p + 0xec);
        func_0201b394(p + 0x2a0);
        func_0201a430(p + 0x2ac);
        func_020169a8(p + 0x334);
        func_0201b324(p + 0x350);
        func_0201af14(p + 0x3a8);
        func_0201b370(p + 0x3aa);
        func_0201adec(p + 0x3b0);
        func_0201a7ec(p + 0x418);
        func_0201a794(p + 0x420);
        func_02032c64(p + 0x49c);
        func_02089c88(p + 0x4cc);
        func_020f55cc(p + 0x514);
        func_02013c2c(p + 0x558);
        func_02019eb0(p + 0x564);
        func_0201489c(p + 0x618);
        *(void **) p = &data_020da088;
        func_02082f60(p + 0x640);
        *(void **) p = &data_ov004_022546e0;
        func_ov004_02224598(p + 0x658);
    }
    return p;
}

int func_ov004_02224bdc(char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov004_02224544(self + 0x658, self);
    func_0201c3f4(self, 0x100);
    func_0203edf4(self, 0x5000);
    func_0201af28(self + 0x350, 2, 0x166, 0xcc, 0x133);
    func_0201b38c(self + 0x2a0, 0xf2);
    func_0201b388(self + 0x2a0, 0xf4);
    func_0201b384(self + 0x2a0, 0xf4);
    return 1;
}

int func_ov004_02224b30(char *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    data_ov004_022580dc = self;
    *(short *) (self + 0x714) = *(short *) (self + 0x8e);
    *(int *) (self + 0x4e8) |= 2;
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020a7278() != 0) {
            func_ov004_022249b4(self, 0);
        } else {
            func_ov004_022249b4(self, 5);
        }
    } else {
        func_ov004_022249b4(self, 0);
    }
    if (func_02073dd4(data_020ccf94, *(int *) (data_020ccf94 + 0x64)) == 0) {
        func_02003348(0x66, 0xd01d, &data_ov004_02247760, &data_ov004_02247758, 0);
    }
    return 1;
}

int func_ov004_02224b0c(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    } else {
        (*(int *) &data_ov004_022580dc) = 0;
        return 1;
    }
}

int func_ov004_02224acc(struct UnkStruct_02224acc *self)
{
    if (!func_0201b790(self)) {
        return 0;
    }
    func_02055d0c(&self->sub, &self->a, 0xe);
    func_02055d0c(&self->sub, &self->b, 0xb);
    func_ov004_0222de98();
    return 1;
}

void *func_ov004_02224ac4(void)
{
    return data_ov004_022545fc;
}

void *func_ov004_02224abc(void)
{
    return data_ov004_022545cc;
}
