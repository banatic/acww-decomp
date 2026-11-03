/* aquarium_fish_kinds_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02237834 @ 0x02237834, 0x3c bytes, Thumb
 * func_ov004_022377ec @ 0x022377ec, 0x48 bytes, Thumb
 * func_ov004_02237794 @ 0x02237794, 0x58 bytes, Thumb
 * func_ov004_02237764 @ 0x02237764, 0x30 bytes, Thumb
 * func_ov004_0223771c @ 0x0223771c, 0x48 bytes, Thumb
 */

#include "types.h"

extern int func_ov004_02239460(int, int);
extern int func_ov004_02239474(int, int);
extern int func_ov004_02239bb4(void *, int, int);
extern void func_02055dc8(void *, void *, void *);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);
extern void func_ov004_0223766c(void *);
extern void func_ov004_02237630(void *);
extern void func_ov004_022358c0(void *, int);
extern int func_ov004_02236418(void *);

void func_ov004_02237834(char *self)
{
    if (func_ov004_02239460(0, 0x64) < 0xf) {
        *(char *) (self + 0x257) = 1;
        *(char *) (self + 0x258) = func_ov004_02239460(8, 0xd);
        *(int *) (self + 0x158) = 0;
    }
}

int func_ov004_022377ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239bb4(self + 0x1a8, 0x266, *(short *) (self + 0x1c0));
    func_ov004_02239bb4(self + 0x1a8, 0x52, func_ov004_02239474(0x168, 0x0));
    *(u8 *) (self + 0x257) = 0x2;
    return 0x257;
}

void func_ov004_02237794(char *self)
{
    func_ov004_02239bb4(self + 0x1a8, 0xcd, (s16) (-*(s16 *) (self + 0x1c0)));
    if (*(int *) (self + 0x158) % 4 == 1) {
        *(u8 *) (self + 0x257) = 1;
    }
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x258)) {
        *(u8 *) (self + 0x257) = 0;
    }
}

void func_ov004_02237764(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x1e8) = *(int *) (self + 0x15c);
    func_02055dc8(self + 0x64, (void *) func_ov004_0223653c, self);
    func_ov004_022354e0(self);
}

void func_ov004_0223771c(char *self)
{
    switch (*(u8 *) (self + 0x255)) {
        case 0:
            func_ov004_0223766c(self);
            break;
        case 1:
            func_ov004_02237630(self);
            break;
    }
    func_ov004_022358c0(self, 0x333);
    *(int *) (self + 0x158) += 1;
    func_ov004_02236418(self);
}
