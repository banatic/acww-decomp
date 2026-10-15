/* func_ov004_02225a60 @ 0x02225a60, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02016884(void *, int, void *);
extern int func_02019c20(void *, int, int, int, int, int);
extern int func_02019de8(void *);
extern void func_ov004_02225ba4(void *, int);
extern void *data_020c80f8;

int func_ov004_02225a60(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02016884(self + 0x334, 0x100, self + 0x2a0) != 0x0 && func_02019de8(self + 0x564) != 0x0) {
        func_02019c20(self + 0x564, 0x1, 0x101, 0x1, *(u16 *) ((char *) &data_020c80f8), 0x0);
    }
    if (func_02016884(self + 0x334, 0x101, self + 0x2a0) != 0x0 && func_02019de8(self + 0x564) != 0x0) {
        func_ov004_02225ba4(self, 0x0);
    }
    return 0x1;
}
