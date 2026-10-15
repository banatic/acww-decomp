/* func_ov004_02224acc @ 0x02224acc, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02224acc {
    u8 pad_00[0xec];
    u8 sub[0x718 - 0xec];
    u8 a[0x748 - 0x718];
    u8 b[4];
};

extern int func_0201b790(struct UnkStruct_02224acc *self);
extern int func_02055d0c(void *dst, void *src, int n);
extern void func_ov004_0222de98(void);

int func_ov004_02224acc(struct UnkStruct_02224acc *self)
{
    if (!func_0201b790(self)) {
        return 0;
    }
    func_02055d0c(&self->sub, &self->a, 0xe);
    func_02055d0c(&self->sub, &self->b, 0xb);
    func_ov004_0222de98();
    return 1;
}
