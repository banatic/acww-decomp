/* func_ov003_0221dc7c @ 0x0221dc7c, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0221dc7c {
    u8 pad_00[0x2b4];
    volatile int unk_2B4;
} UnkStruct_0221dc7c;

extern int data_021fbe94;
extern int data_021c9b1c;

extern int func_ov003_0221dcd8(UnkStruct_0221dc7c *self);
extern void *func_02064b2c(int, int, int, int);
extern int func_021077e8(void *);
extern int func_020560e0(int, int);
extern int func_020561cc(int, int);
extern void func_020e9898(void *);

void func_ov003_0221dc7c(UnkStruct_0221dc7c *self)
{
    void *p;

    p = func_02064b2c(func_ov003_0221dcd8(self), data_021fbe94, -4, 0);
    self->unk_2B4 = func_021077e8(p);
    if (func_020560e0(self->unk_2B4, 0) != 0) {
        self->unk_2B4 = func_020561cc(self->unk_2B4, data_021c9b1c);
    }
    func_020e9898(p);
}
