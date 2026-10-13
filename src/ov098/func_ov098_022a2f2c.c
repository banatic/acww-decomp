/* func_ov098_022a2f2c @ 0x022a2f2c, 0x7c bytes, Thumb, module ov098
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022a2f2c {
    u8 pad_00[0xb6];
    u8 unk_B6;
} UnkStruct_022a2f2c;

extern int func_ov096_0229cbbc(UnkStruct_022a2f2c *self);
extern int func_ov096_0229f0dc(UnkStruct_022a2f2c *self, u8 kind);
extern int func_ov003_0222780c(int a, int b, void *p);
extern void func_ov098_022a2eb4(UnkStruct_022a2f2c *self, u8 idx);
extern void func_ov003_02219b38(int a);
extern void func_ov096_0229f860(UnkStruct_022a2f2c *self);

void func_ov098_022a2f2c(UnkStruct_022a2f2c *self)
{
    volatile u16 id;
    int a;
    int b;

    a = func_ov096_0229cbbc(self);
    b = func_ov096_0229f0dc(self, self->unk_B6);
    if (func_ov003_0222780c(a, b, (u8 *) self + 0x2e14) != 0) {
        u8 idx;
        id = (u16) b;
        {
            unsigned int ok = 0;
            u16 hi = id;
            u16 lo = id;
            if (lo >= 0x12e8 && hi <= 0x131f) {
                ok = 1;
            }
            idx = (u8) (ok > 0 ? hi - 0x12e8 : -1);
        }
        func_ov098_022a2eb4(self, idx);
        func_ov003_02219b38(1);
        func_ov096_0229f860(self);
    }
}
