/* func_ov004_0220f450 @ 0x0220f450, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02055d80();
extern int func_ov004_0223cd78();
extern int func_ov004_0223ce84();
extern void *data_ov004_02247640;

int func_ov004_0220f450(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    v2 = func_ov004_0223cd78(func_ov004_0223ce84(self), self);
    if (v2 != -0x1) {
        return func_02055d80(self + 0x538, *(u8 *) ((char *) &data_ov004_02247640 + v2), v2);
    }
    return -0x1;
}
