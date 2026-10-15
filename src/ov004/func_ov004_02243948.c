/* func_ov004_02243948 @ 0x02243948, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_022437e0(void *, void *);
extern int func_ov004_02244be0(void *, int);
extern void func_ov004_02244f20(void *);

void func_ov004_02243948(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02244f20(self);
    func_ov004_02244be0(self, 0x0);
    if (*(short *) (self + 0x172) == 0x0) {
        func_ov004_022437e0(self, self + 0x168);
    } else {
        *(u16 *) (self + 0x172) = 0x0;
    }
}
