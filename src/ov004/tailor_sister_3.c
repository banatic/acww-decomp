/* tailor_sister_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222353c @ 0x0222353c, 0x118 bytes, Thumb
 * func_ov004_022234e4 @ 0x022234e4, 0x58 bytes, Thumb
 * func_ov004_02223440 @ 0x02223440, 0xa4 bytes, Thumb
 * func_ov004_02223438 @ 0x02223438, 0x8 bytes, Thumb
 * func_ov004_02223430 @ 0x02223430, 0x8 bytes, Thumb
 */

#include "types.h"

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_ov004_0225445c;
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
extern void *func_ov004_02222f14(void *);
extern int func_0202edc8(void *self);
extern void func_0201c280(void *self, void *p);
extern void func_ov004_02222ec0(void *p, void *self);
extern void func_0202edfc(void *self, int a, int b);
extern void func_0201c3f4(void *self, int a);
extern void func_0203edf4(void *self, int a);
extern int func_0202ec58(void *self);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern short *func_0209d358(int a, int b);
extern int func_020a7278(void);
extern void func_ov004_02223388(void *self, int a);
extern int func_0201bfd8(void *self, void *p, int a);
extern int func_0202ea40(void *self, short *buf, int a);
extern char data_ov004_022543a8[];
extern char data_ov004_02254378[];

void *func_ov004_0222353c(void)
{
    u8 *p;

    p = (u8 *) func_020edf70(0x714);
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
        *(void **) p = &data_ov004_0225445c;
        func_ov004_02222f14(p + 0x658);
    }
    return p;
}

int func_ov004_022234e4(char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov004_02222ec0(self + 0x658, self);
    func_0202edfc(self, 0x119a, 0x2000);
    func_0201c3f4(self, 0);
    func_0203edf4(self, 0x3000);
    return 1;
}

int func_ov004_02223440(char *self)
{
    short buf[2];

    if (func_0202ec58(self) == 0) {
        return 0;
    }
    *(short *) (self + 0x70c) = *(short *) (self + 0x8e);
    *(int *) (self + 0x4e8) |= 2;
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020a7278() != 0) {
            func_ov004_02223388(self, 0);
        } else {
            func_0201bfd8(self, self + 0x712, 1);
            func_ov004_02223388(self, 4);
        }
    } else {
        func_ov004_02223388(self, 0);
        if (func_0202ea40(self, buf, 2) != 0) {
            *(char *) (self + 0x70e) = 1;
        }
    }
    return 1;
}

void *func_ov004_02223438(void)
{
    return data_ov004_022543a8;
}

void *func_ov004_02223430(void)
{
    return data_ov004_02254378;
}
