/* func_ov004_022233cc @ 0x022233cc, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022233cc;
typedef int (UnkStruct_022233cc::*PMF)(void);
struct Entry {
    int a;
    int b;
    PMF unk_08;
};
extern Entry data_ov004_0225806c[];
struct UnkStruct_022233cc {
    u8 pad_00[0x654];
    int unk_654;
    u8 pad_658[0x712 - 0x658];
    u8 unk_712;
};
extern "C" {
void *func_ov004_0222fd38(UnkStruct_022233cc *);
int _s32_div_f(void *, int);
void func_0201bfbc(UnkStruct_022233cc *, u8 *, int);
int func_ov004_022233cc(UnkStruct_022233cc *self)
{
    int r;
    self->unk_712 = (u8) _s32_div_f(func_ov004_0222fd38(self), 0x38);
    func_0201bfbc(self, &self->unk_712, 1);
    r = 0;
    if (data_ov004_0225806c[self->unk_654].unk_08) {
        r = (self->*data_ov004_0225806c[self->unk_654].unk_08)();
    }
    return r;
}
}
