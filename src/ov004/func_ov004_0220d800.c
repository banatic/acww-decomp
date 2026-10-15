/* func_ov004_0220d800 @ 0x0220d800, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d7f0(char *argument0, unsigned int argument1);
extern void *func_ov004_0220d938(char *argument0);

void func_ov004_0220d800(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x4; i++) {
        func_ov004_0220d938((char *) (func_ov004_0220d7f0(self, i)));
    }
}
