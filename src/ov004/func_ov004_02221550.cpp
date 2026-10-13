/* func_ov004_02221550 @ 0x02221550, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02221550;
typedef int (UnkStruct_02221550::*PMF)(void);
struct Entry {
    PMF unk_00;
    int a;
    int b;
};
extern Entry data_ov004_02257e90[];
struct UnkStruct_02221550 {
    u8 pad_00[0x910];
    int unk_910;
    int unk_914;
};
extern "C" {
void func_ov004_02221550(UnkStruct_02221550 *self, int i)
{
    int r;
    r = 1;
    if (data_ov004_02257e90[i].unk_00) {
        r = (self->*data_ov004_02257e90[i].unk_00)();
    }
    if (r != 0) {
        self->unk_914 = self->unk_910;
        self->unk_910 = i;
    }
}
}
