/* func_ov004_022377ec @ 0x022377ec, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02239474(int, int);
extern int func_ov004_02239bb4(void *, int, int);

int func_ov004_022377ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239bb4(self + 0x1a8, 0x266, *(short *) (self + 0x1c0));
    func_ov004_02239bb4(self + 0x1a8, 0x52, func_ov004_02239474(0x168, 0x0));
    *(u8 *) (self + 0x257) = 0x2;
    return 0x257;
}
