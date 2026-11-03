/* field_actor_room_states_23: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229760 @ 0x02229760, 0x14 bytes, Thumb
 * func_ov004_0222973c @ 0x0222973c, 0x22 bytes, Thumb
 * func_ov004_02229718 @ 0x02229718, 0x22 bytes, Thumb
 */

#include "types.h"

extern void func_02077910(void *, int);
extern void func_020779b8(void *, int, int);
extern void func_02077978(char *p, int b, int c);
extern short func_020778f8(char *p);

void func_ov004_02229760(void *p, int a, int b, short c, unsigned char d)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
    *(short *) ((char *) p + 8) = c;
    *((unsigned char *) p + 0xa) = d;
}

void func_ov004_0222973c(char *self, int a1, int a2, int a3, u8 flag)
{
    // DECLS
    // ENDDECLS
    func_020779b8(self, a1, a2);
    func_02077910(self + 0x5, a3);
    *(u8 *) (self + 0x7) = flag;
}

void func_ov004_02229718(char *p, int b, int c, short *out, u8 *out2)
{
    func_02077978(p, b, c);
    *out = func_020778f8(p + 5);
    *out2 = *(u8 *) (p + 7);
}
