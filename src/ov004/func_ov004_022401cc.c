/* func_ov004_022401cc @ 0x022401cc, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02240f2c(void *argument0, short argument1, int argument2, short argument3, short argument4,
                               int argument5, int argument6);

int func_ov004_022401cc(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02240f2c(self, 0x28, 0x1e, 0x0, 0x0, 0x0, 0xf);
    if (*(u8 *) (self + 0x22) == 0x0) {
        *(int *) (self + 0x10) = 0x666;
        return 0x666;
    }
    return *(u8 *) (self + 0x22);
}
