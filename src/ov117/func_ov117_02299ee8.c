/* func_ov117_02299ee8 @ 0x02299ee8, 0xa4 bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204e414(void *p);
extern int func_0204f3e4(int a, void *b, void *c, void *d, void *e, void *f, void *g, int h, int i);
extern void func_0204f800(void *a, void *b, u32 c, u32 d, u32 e, u32 f);
extern int func_020b3b50(void *p);
extern void func_020b3c58(int a, void *b, void *c, void *d, void *e);
extern void func_ov117_0229a2a4(void *a, int b, u32 c, u32 d, int e);

void func_ov117_02299ee8(void *self)
{
    u16 local_14;
    u32 local_18;
    u32 local_1c;
    u32 local_20;
    u32 local_24;
    u32 local_28;
    u32 local_2c;
    int local_30;
    int local_34;
    u32 local_38;
    u32 local_3c;
    int v;
    int ret3;

    v = func_0204e414(self);
    if (v == 0) {
        return;
    }

    local_14 = 0x500b;
    if (!func_0204f3e4(v, &local_20, &local_24, &local_28, &local_2c, &local_14, &local_14, 0, 0)) {
        return;
    }

    func_0204f800(&local_18, &local_1c, local_20, local_24, local_28, local_2c);

    local_18 <<= 1;
    local_1c <<= 1;
    local_18 += 1;
    local_1c += 1;

    ret3 = func_020b3b50(&local_14);
    if (ret3 == 0) {
        goto skip;
    }

    func_020b3c58(ret3, &local_30, &local_34, &local_38, &local_3c);
    local_18 += local_30 >> 11;
    local_1c += local_34 >> 11;

skip:
    func_ov117_0229a2a4(self, 0x10, local_18, local_1c, 0);
}
