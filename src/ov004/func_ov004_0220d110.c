/* func_ov004_0220d110 @ 0x0220d110, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern int func_ov004_0220d258(int arg0);
extern char *func_ov004_0220d268(char *arg0);

void *func_ov004_0220d110(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self, 0x3, 0x1c, ((void (*)(void *)) func_ov004_0220d268), ((void (*)(void *)) func_ov004_0220d258));
    *(u8 *) (self + 0x54) = 0x0;
    return self;
}
