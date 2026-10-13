/* func_ov004_0224379c @ 0x0224379c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02241894(void *, int);
extern void func_ov004_02243740(void *, int, int);
extern void func_ov004_02244e38(void *, void *);

void func_ov004_0224379c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x22) == 0x0) {
        func_ov004_02241894(self, *(u8 *) (self + 0x22));
        return;
    } else {
        if (*(short *) (self + 0x172) == 0x0) {
            func_ov004_02243740(self, 0x172, *(short *) (self + 0x172));
            func_ov004_02244e38(self, self + 0x2c8);
        } else {
            *(u8 *) (self + 0x9a) = 0x0;
            *(u16 *) (self + 0x172) = 0x0;
        }
        return;
    }
}
