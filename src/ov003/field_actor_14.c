/* field_actor_14: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022100ac @ 0x022100ac, 0x16 bytes, Thumb
 * func_ov003_022100a0 @ 0x022100a0, 0xa bytes, Thumb
 * func_ov003_02210094 @ 0x02210094, 0xa bytes, Thumb
 */

#include "types.h"

struct UnkStruct_022100a0 {
    int a;
    int b;
};

struct UnkStruct_02210094 {
    int a;
    int b;
};

void func_ov003_022100ac(void *r0, unsigned char r1, unsigned short r2, void *r3)
{
    ((unsigned char *) r0)[0xf] = r1;
    ((unsigned char *) r0)[0xe] = 0;
    *(unsigned short *) ((char *) r0 + 0xc) = r2;
    *(unsigned int *) r0 = *(unsigned int *) r3;
    *(unsigned int *) ((char *) r0 + 4) = *(unsigned int *) ((char *) r3 + 4);
    *(unsigned int *) ((char *) r0 + 8) = *(unsigned int *) ((char *) r3 + 8);
}

void func_ov003_022100a0(u8 *d, struct UnkStruct_022100a0 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}

void func_ov003_02210094(u8 *p, struct UnkStruct_02210094 *d)
{
    d->a = p[0];
    d->b = p[1];
}
