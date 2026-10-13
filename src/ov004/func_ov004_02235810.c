/* func_ov004_02235810 @ 0x02235810, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02235728(void *, void *, void *);
extern u8 data_ov004_02247924[];
extern int data_ov004_022594d4[];

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
