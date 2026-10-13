/* func_ov002_0220b2d0 @ 0x0220b2d0, 0x46 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0207094c(void *, int, int);
extern int func_02070a04(void *, int, int);
extern void func_02070adc(void *, int, int, int, int, int, int);

int func_ov002_0220b2d0(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_0207094c(self + 0x4, *(u8 *) (self + 0x77), a2);
    func_02070adc(self + 0x4, 0x8, ((u32) (*(int *) ((char *) *(int *) (self + 0x70) + 0x4) << 22) >> 22),
                  *(u8 *) (self + 0x74), a1, a2, 0x0);
    return func_02070a04(self + 0x4, 0x1, 0x0);
}
