/* func_ov004_0221e880 @ 0x0221e880, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02014868(void *argument0);
extern void func_0201cc48(void *argument0);
extern int func_0203e020(int argument0);

int func_ov004_0221e880(char *self, char *a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02014868((void *) ((void *) (a1 + 0x618)));
    if (v1 == 0x0) {
        func_0201cc48(a1 + 0x83c);
        func_0203e020((int) (a1));
        *(u8 *) (self + 0xc) = 0x1;
        return 0x1;
    }
    return v1;
}
