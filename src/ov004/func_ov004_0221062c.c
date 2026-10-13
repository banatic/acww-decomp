/* func_ov004_0221062c @ 0x0221062c, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221062c {
    int unk_00;
    u16 unk_04;
};

extern void *func_ov004_0220e220(void *p);
extern struct UnkStruct_0221062c *func_ov004_0220da04(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9f8(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9e0(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9d4(void *p, int i);
extern struct UnkStruct_0221062c *func_ov004_0220d9ec(void *p, int i);

u16 func_ov004_0221062c(char *self, int k)
{
    int i;

    i = k & 1;
    if (func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9e0(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9d4(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    if (func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), i) != 0) {
        return func_ov004_0220d9ec(func_ov004_0220e220(self + 0x6cc), i)->unk_04;
    }
    return 0;
}
