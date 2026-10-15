/* func_ov004_0222bcf4 @ 0x0222bcf4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0200f328(void *, int);
extern int func_02011340(void *);
extern int func_020b67ac(void);

void func_ov004_0222bcf4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (func_020b67ac() != 0x0 && a1 == 0xa && *(u8 *) (self + 0x7d4) == 0x0) {
        if (func_02011340(self) != 0x0) {
            func_0200f328(self, 0x4cd);
        } else {
            func_0200f328(self, 0x4cc);
        }
    }
}
