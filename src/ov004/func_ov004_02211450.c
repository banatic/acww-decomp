/* func_ov004_02211450 @ 0x02211450, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02211480(char *arg0);
extern void func_ov004_022114cc(char *arg0);
extern int func_ov004_022114f8(char *arg0);

void func_ov004_02211450(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x1c) = (void *) func_ov004_022114f8;
    *(u8 *) (self + 0x90) = 0x2;
    *(void **) (self + 0x14) = (void *) func_ov004_02211480;
    *(u8 *) (self + 0x8e) = 0x2;
    *(void **) (self + 0x24) = (void *) func_ov004_022114cc;
    *(u8 *) (self + 0x92) = 0x1;
}
