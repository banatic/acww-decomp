/* func_ov004_02228438 @ 0x02228438, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0200f268(void *, int);
extern int func_02056f94(void *);
extern void func_ov004_022283cc(void *, int, int, int);

void func_ov004_02228438(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x704) != 0x1a && *(int *) (self + 0x704) != 0x0 && func_02056f94(self + 0x2d0) != 0x0) {
        func_0200f268(self, 0x2);
        func_ov004_022283cc(self, *(u8 *) (self + 0x7de), 0x6, -0x1);
        return;
    }
}
