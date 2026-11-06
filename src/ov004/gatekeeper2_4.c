/* gatekeeper2_4: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022258c4 @ 0x022258c4, 0x118 bytes, Thumb
 * func_ov004_0222585c @ 0x0222585c, 0x68 bytes, Thumb
 * func_ov004_022257e8 @ 0x022257e8, 0x74 bytes, Thumb
 * func_ov004_02225794 @ 0x02225794, 0x54 bytes, Thumb
 * func_ov004_02225788 @ 0x02225788, 0xc bytes, Thumb
 * func_ov004_0222577c @ 0x0222577c, 0xc bytes, Thumb
 */

#include "types.h"

extern void *data_020d8c64;
extern void *data_020da088;
extern void *data_ov004_02254918;
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
extern void *func_ov004_022254c4(void *);
extern void func_0201b388(void *, int);
extern void func_0201b38c(void *, int);
extern void func_0201c280(void *, void *);
extern void func_0201c3f4(void *, int);
extern int func_0202edc8(void *);
extern unsigned char func_020b65c4(void);
extern void func_ov004_02225470(void *, void *);
extern int func_0202ec58(void *self);
extern void *data_020ccf94;
extern int func_02073d90(void *a);
extern int func_0201c0e0(void *self);
extern void func_ov004_022256ec(void *self, int k);
extern int func_0202ec14(void *parameter0);
extern int func_02073dd4(void *g, int a);
extern int func_0207b3dc(void *q);
extern unsigned int func_0207b410(void *q);
extern void func_0209a77c(void *);
extern char data_021e5a2c;
extern unsigned int data_ov004_02254790;
extern unsigned int data_ov004_0225478c;

void *func_ov004_022258c4(void)
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
        *(void **) p = &data_ov004_02254918;
        func_ov004_022254c4(p + 0x658);
    }
    return p;
}

int func_ov004_0222585c(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_0202edc8(self) == 0x0) {
        return 0x0;
    } else {
        func_0201c280(self, self + 0x658);
        func_ov004_02225470(self + 0x658, self);
        func_0201c3f4(self, 0x100);
        func_0201b388(self + 0x2a0, 0xd9);
        func_0201b38c(self + 0x2a0, 0xd8);
        if (func_020b65c4() != 0xb) {
            *(u8 *) (self + 0x563) = 0x1;
        }
        return 0x1;
    }
}

int func_ov004_022257e8(void *self)
{
    int *f;

    if (func_0202ec58(self) == 0) {
        return 0;
    }
    *(short *) ((char *) self + 0x710) = *(short *) ((char *) self + 0x8e);
    f = (int *) ((char *) self + 0x4e8);
    *f = *f | 2;
    if (func_02073d90(data_020ccf94) != 0 && (int) func_020b65c4() == 0xb) {
        if (func_0201c0e0(self) != 0) {
            func_ov004_022256ec(self, 0);
        } else {
            func_ov004_022256ec(self, 4);
        }
    } else {
        func_ov004_022256ec(self, 0);
    }
    return 1;
}

int func_ov004_02225794(void *arg0)
{
    char *g;
    char *q;

    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    }
    g = (*(char **) &data_020ccf94);
    if (func_02073dd4(g, *(int *) (g + 0x64)) != 0) {
        if (func_02073d90(g) == 0) {
            q = &data_021e5a2c;
            if (func_0207b3dc(q) != -1) {
                func_0209a77c((void *) func_0207b410(q));
            }
        }
    }
    return 1;
}

unsigned int func_ov004_02225788(void)
{
    return data_ov004_02254790;
}

unsigned int func_ov004_0222577c(void)
{
    return data_ov004_0225478c;
}
