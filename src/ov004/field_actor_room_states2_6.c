/* field_actor_room_states2_6: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222a488 @ 0x0222a488, 0xc bytes, Thumb
 * func_ov004_0222a46c @ 0x0222a46c, 0x1c bytes, Thumb
 * func_ov004_0222a450 @ 0x0222a450, 0x1c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0222a488 {
    int a;
    int b;
    u16 c;
    u8 d;
};

extern void func_020779b8(char *p, int a1, int a2);
extern void func_02077910(char *p, int a3);
extern void func_02077978(void *parameter0, unsigned int *parameter1, int parameter2);
extern int func_020778f8(int);

void func_ov004_0222a488(struct UnkStruct_0222a488 *s, int a, int b, u16 c)
{
    s->a = a;
    s->b = b;
    s->c = c;
    s->d = 0;
}

void func_ov004_0222a46c(char *p, int a1, int a2, int a3)
{
    func_020779b8(p, a1, a2);
    func_02077910(p + 5, a3);
}

void func_ov004_0222a450(int a1, int a2, int a3, short *a4)
{
    int r5 = a1;
    short *r4 = a4;
    func_02077978((void *) (a1), (unsigned int *) (a2), (int) (a3));
    *r4 = (short) func_020778f8(r5 + 5);
}
