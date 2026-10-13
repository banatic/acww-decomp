/* func_ov004_0221eb6c @ 0x0221eb6c, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221eb6c;
typedef int (UnkStruct_0221eb6c::*PMF)(int);
struct Entry {
    PMF unk_00;
    int a;
    int b;
};
extern Entry data_ov004_02257cb8[];
struct UnkStruct_0221eb6c {
    volatile int unk_00;
    Entry *unk_04;
    int unk_08;
    u8 unk_0C;
};
extern "C" {
void func_ov004_0221eb6c(UnkStruct_0221eb6c *self, int arg, int i)
{
    if (i >= 0 && i < 5) {
        self->unk_00 = i;
        self->unk_04 = &data_ov004_02257cb8[self->unk_00];
        self->unk_0C = 0;
        if (self->unk_04) {
            if (self->unk_04->unk_00) {
                (self->*(self->unk_04->unk_00))(arg);
            }
        }
    }
}
}
