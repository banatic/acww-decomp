/* func_ov004_02235870 @ 0x02235870, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02235e58(void *);

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
