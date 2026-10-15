/* func_ov004_0221ad0c @ 0x0221ad0c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02003348(int p1, int p2, void *p3, void *p4, int p5);
extern u16 data_ov004_02253238;
extern int data_ov004_022577d0;

struct UnkStruct_0221ad0c {
    u16 a, b, c;
};

void func_ov004_0221ad0c(void *self, int a, u16 b, u16 c)
{
    struct UnkStruct_0221ad0c s;
    data_ov004_02253238 = c;
    data_ov004_022577d0 = a;
    s.a = 0;
    s.b = b;
    s.c = 0;
    func_02003348(0x17, 0, self, &s, 0);
}
