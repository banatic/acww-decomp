/* func_ov004_02232968 @ 0x02232968, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_022327a0(void *, void *, int, int);

int func_ov004_02232968(char *self, int a1, int a2, int a3)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    *(u16 *) (frame) = a1;
    return func_ov004_022327a0(self, frame, a2, a3);
}
