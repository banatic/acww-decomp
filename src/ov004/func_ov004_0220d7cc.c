/* func_ov004_0220d7cc @ 0x0220d7cc, 0x22 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d7f0(char *argument0, unsigned int argument1);
extern void func_ov004_0220d870(void *argument0, char *argument1);

void func_ov004_0220d7cc(char *self, int a1)
{
    // DECLS
    u32 i;
    // ENDDECLS
    for (i = 0; i < 0x4; i++) {
        func_ov004_0220d870((void *) (func_ov004_0220d7f0(self, i)), (char *) (a1));
    }
}
