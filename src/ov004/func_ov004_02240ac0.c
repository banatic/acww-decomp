/* func_ov004_02240ac0 @ 0x02240ac0, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056fcc(void *, int, int, int, int);
extern void func_ov004_02240bac(void *, int, int);

int func_ov004_02240ac0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02240bac(self, 0x96, 0x46);
    return func_02056fcc(self + 0x14c, ((u32) (*(int *) (self + 0x150) << 4) >> 16), 0x1, 0x1000, 0x0);
}
