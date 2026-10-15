/* func_ov004_02227624 @ 0x02227624, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02227624 {
    u8 pad_00[0x2d8];
    unsigned int lo : 12;
    unsigned int mid : 16;
    unsigned int hi : 4;
    u8 pad_2DC[0x804 - 0x2dc];
    int arg;
};

extern u8 data_021c75b8;
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);

void func_ov004_02227624(struct UnkStruct_02227624 *self)
{
    int idle;

    idle = !data_021c75b8;
    if (idle != 0) {
        return;
    }
    if (self->mid >= 5) {
        func_020b6098(func_020b5e10(), self->arg);
    }
}
