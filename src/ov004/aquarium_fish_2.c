/* aquarium_fish_2: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022358bc @ 0x022358bc, 0x2 bytes, Thumb
 * func_ov004_022358b8 @ 0x022358b8, 0x2 bytes, Thumb
 * func_ov004_02235870 @ 0x02235870, 0x48 bytes, Thumb
 * func_ov004_02235810 @ 0x02235810, 0x60 bytes, Thumb
 */

#include "types.h"

extern void func_ov004_02235e58(void *);
extern void func_ov004_02235728(void *, void *, void *);
extern u8 data_ov004_02247924[];
extern int data_ov004_022594d4[];

void func_ov004_022358bc(void) {}

void func_ov004_022358b8(void) {}

void func_ov004_02235870(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1ee) != 0x1) {
        if (*(int *) (self + 0x1a8) <= 0x5000 || *(int *) (self + 0x1a8) >= 0x1e000) {
            func_ov004_02235e58(self);
            if (*(u8 *) (self + 0x1ee) == 0x6) {
                *(u8 *) (self + 0x1ee) = 0x2;
            }
        }
        return;
    }
}

void func_ov004_02235810(char *self, int unused, unsigned k)
{
    void *loc;
    if (*(void **) (self + 0x4c) != 0) {
        loc = *(void **) (self + 0x4c);
        if (k >= 0x38) {
            *(u8 *) ((char *) loc + 0x1ea) |= 0x20;
        } else if (data_ov004_02247924[k * 0x11] != 0 || k < 0x23) {
            int *e = &data_ov004_022594d4[k];
            func_ov004_02235728(self, &loc, e);
            func_ov004_02235728(self, e, &loc);
        }
    }
}
