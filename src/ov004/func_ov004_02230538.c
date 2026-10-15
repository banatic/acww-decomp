/* func_ov004_02230538 @ 0x02230538, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056f94(void *);
extern int func_ov004_0223080c(void *, int);
extern int func_ov045_02260618(void);

void func_ov004_02230538(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov045_02260618() == 0x7) {
        *(u8 *) (self + 0x6b0) = 0x0;
    }
    if (func_ov045_02260618() == 0x12) {
        *(u8 *) (self + 0x6b2) = 0x0;
    }
    if (func_ov045_02260618() == 0x13) {
        *(u8 *) (self + 0x6d4) = 0x1;
    }
    if (func_ov045_02260618() == 0x25) {
        *(u8 *) (self + 0x6d4) = 0x0;
    }
    if (func_02056f94(self + 0x49c) != 0x0) {
        func_ov004_0223080c(self, 0x0);
        return;
    }
}
