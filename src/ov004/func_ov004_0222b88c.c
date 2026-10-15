/* func_ov004_0222b88c @ 0x0222b88c, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0222b9b4(void *, void *);
extern int func_ov004_0222b9d4(void *, int, int, int, int);

void func_ov004_0222b88c(char *self, int a1)
{
    // DECLS
    char frame[0x8];
    // ENDDECLS
    func_ov004_0222b9b4(self + 0x8f0, frame);
    func_ov004_0222b9d4(self, *(u8 *) (frame), 0x0, 0x6, a1);
    return;
}
