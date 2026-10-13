/* func_ov004_022326dc @ 0x022326dc, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02232514(void *, void *, int, int);

int func_ov004_022326dc(char *self, int a1, int a2, int a3)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    *(u16 *) (frame) = a1;
    return func_ov004_02232514(self, frame, a2, a3);
}
