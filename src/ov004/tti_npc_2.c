/* tti_npc_2: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02225cd4 @ 0x02225cd4, 0x10c bytes, Thumb
 * func_ov004_02225cac @ 0x02225cac, 0x28 bytes, Thumb
 * func_ov004_02225c68 @ 0x02225c68, 0x44 bytes, Thumb
 * func_ov004_02225c44 @ 0x02225c44, 0x24 bytes, Thumb
 * func_ov004_02225c3c @ 0x02225c3c, 0x8 bytes, Thumb
 * func_ov004_02225c34 @ 0x02225c34, 0x8 bytes, Thumb
 */

#include "types.h"

extern void func_02013c2c(void *argument0);
extern void func_0201489c(void *object);
extern int func_020169a8(int argument0);
extern void *func_02019eb0(void *argument0);
extern void *func_0201a430(void *argument0);
extern void func_0201a794(void *object);
extern void *func_0201a7ec(void *argument0);
extern void func_0201adec(char *argument0);
extern void func_0201af14(void *argument0);
extern int func_0201b324(int *argument0);
extern void func_0201b370(unsigned short *argument0);
extern void func_0201b394(int *argument0);
extern void *func_02032c64(void *argument0);
extern void *func_0203f130(void *argument0);
extern void *func_0205467c(void *argument0);
extern void *func_02082f60(void *argument0);
extern void *func_02089c88(void *argument0);
extern void *func_020edf70(int argument0);
extern void *func_020f55cc(void *argument0);
extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_ov004_02254a38;
extern int func_0202edc8(char *self);
extern void func_0201b38c(char *p, int a);
extern int func_0202ec58(void *);
extern void *data_ov004_02258200;
extern void func_ov004_02225ba4(void *, int);
extern int func_0202ec14(void *parameter0);
extern char data_ov004_02254a14[];
extern char data_ov004_022549e4[];

void *func_ov004_02225cd4(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_020edf70(0x65c);
    if (self != 0) {
        func_0203f130(self);
        *(void **) (self) = &data_020d8c64;
        *(u16 *) (self + 0xea) = 0xfff1;
        func_0205467c(self + 0xec);
        func_0201b394((int *) (self + 0x2a0));
        func_0201a430(self + 0x2ac);
        func_020169a8((int) (self + 0x334));
        func_0201b324((int *) (self + 0x350));
        func_0201af14(self + 0x3a8);
        func_0201b370((unsigned short *) (self + 0x3aa));
        func_0201adec(self + 0x3b0);
        func_0201a7ec(self + 0x418);
        func_0201a794(self + 0x420);
        func_02032c64(self + 0x49c);
        func_02089c88(self + 0x4cc);
        func_020f55cc(self + 0x514);
        func_02013c2c(self + 0x558);
        func_02019eb0(self + 0x564);
        func_0201489c(self + 0x618);
        *(void **) (self) = &data_020da088;
        func_02082f60(self + 0x640);
        *(void **) (self) = &data_ov004_02254a38;
    }
    return self;
}

int func_ov004_02225cac(char *self)
{
    int r;
    if (func_0202edc8(self) == 0) {
        r = 0;
    } else {
        func_0201b38c(self + 0x2a0, 0xff);
        r = 1;
    }
    return r;
}

int func_ov004_02225c68(u8 *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    data_ov004_02258200 = self;
    func_ov004_02225ba4(self, 0);
    *(int *) (self + 0x4e8) |= 2;
    self[0x510] = 0;
    return 1;
}

int func_ov004_02225c44(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    } else {
        (*(int *) &data_ov004_02258200) = 0;
        return 1;
    }
}

void *func_ov004_02225c3c(void)
{
    return data_ov004_02254a14;
}

void *func_ov004_02225c34(void)
{
    return data_ov004_022549e4;
}
