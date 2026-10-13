/* func_ov004_0220e73c @ 0x0220e73c, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0223e7b4(void *, void *);

int func_ov004_0220e73c(char *self, int a1)
{
    // DECLS
    char frame[0xc];
    // ENDDECLS
    *(u16 *) (frame) = 0x0;
    *(u16 *) (frame + 0x2) = a1;
    *(u16 *) (frame + 0x4) = 0x0;
    return func_ov004_0223e7b4(self, frame);
}
