/* func_ov004_0220f218 @ 0x0220f218, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bc50(int argument0, int argument1);
extern int func_ov004_0220f240(int argument0);

int func_ov004_0220f218(char *self, char *a1, int a2)
{
    // DECLS
    int v3;
    // ENDDECLS
    v3 = func_0204bc50(*(int *) (a1 + 0x284), func_ov004_0220f240((int) ((int) (a2))));
    *(u16 *) (self) = v3;
    return v3;
}
