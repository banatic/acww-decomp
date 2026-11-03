/* field_actor_room_states2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229d04 @ 0x02229d04, 0x20 bytes, Thumb
 * func_ov004_02229cf8 @ 0x02229cf8, 0xc bytes, Thumb
 */

#include "types.h"

extern void func_020109a0(void *, int, int, unsigned short d);
extern int func_ov004_02229d24(int, int, int);

void func_ov004_02229d04(char *self, void *message, int previous)
{
    // DECLS
    // ENDDECLS
    func_020109a0(self, 0x1d, 0x3, 0x0);
    *(u8 *) (self + 0x7d4) = 0x0;
    return;
}

void func_ov004_02229cf8(int a, int b)
{
    func_ov004_02229d24(a, 6, b);
}
