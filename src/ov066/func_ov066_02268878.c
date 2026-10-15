/* func_ov066_02268878 @ 0x02268878, 0x54 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern int func_ov066_02266e08(void);
extern void func_ov066_02269dcc(void);
extern void func_ov066_02266bf4(void);
extern void func_ov066_0226686c(int status);

struct Arg {
    u8 pad_00[2];
    u16 unk_02;
};

struct UnkStruct_02268878 {
    u8 pad_00[4];
    u32 unk_04;
};

extern struct UnkStruct_02268878 *data_ov066_0226bdec;

void func_ov066_02268878(struct Arg *arg)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }

    if (arg->unk_02 == 0) {
        struct UnkStruct_02268878 *p = data_ov066_0226bdec;
        p->unk_04 = 4;
        func_ov066_02269dcc();
        func_ov066_02266bf4();
        return;
    } else {
        func_ov066_0226686c(arg->unk_02);
        return;
    }
}
