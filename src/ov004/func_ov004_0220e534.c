/* func_ov004_0220e534 @ 0x0220e534, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020b3188(int, int, int, int);
extern void func_020b3220(int, int, int, int);

void func_ov004_0220e534(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x744) != 0x0) {
        if (*(char *) (self + 0x742) == a1) {
            func_020b3220(a2, a1, a2, *(char *) (self + 0x742));
        } else {
            if (*(char *) (self + 0x743) == a1) {
                func_020b3188(a2, a1, a2, 0x743);
            }
        }
    }
}
