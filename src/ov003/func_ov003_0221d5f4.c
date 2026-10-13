/* func_ov003_0221d5f4 @ 0x0221d5f4, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0207cec0(void *base, int index);
extern void *func_02080b64(void *base);
extern int data_021e5a2c;

struct Param {
    u8 pad_00[0x136];
    u16 unk_136;
};

struct UnkStruct_0221d5f4 {
    unsigned char b : 5;
};

u8 func_ov003_0221d5f4(struct Param *p)
{
    void *base = (void *) &data_021e5a2c;
    int flag = 0;
    u16 val = p->unk_136;
    int idx;

    if (val >= 0x5001 && val <= 0x5008) {
        flag = 1;
    }

    if (flag) {
        idx = val - 0x5001;
    } else {
        idx = -1;
    }

    return (u8) (((struct UnkStruct_0221d5f4 *) func_02080b64(func_0207cec0(base, idx)))->b & 3);
}
