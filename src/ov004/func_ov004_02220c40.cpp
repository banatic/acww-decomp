/* func_ov004_02220c40 @ 0x02220c40, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02220c40;
typedef void (UnkStruct_02220c40::*PMF)(void);
struct Entry {
    PMF unk_00;
    u8 flag;
};
extern Entry data_ov004_02257dd8[];
struct UnkStruct_02220c40 {
    u8 pad_00[0x1ac];
    int unk_1AC;
};
extern "C" {
void func_ov004_02220c34(UnkStruct_02220c40 *, int);
void func_ov004_02220c40(UnkStruct_02220c40 *self)
{
    int i;
    i = self->unk_1AC;
    if (data_ov004_02257dd8[i].flag == 0) {
        if (data_ov004_02257dd8[i].unk_00) {
            (self->*data_ov004_02257dd8[i].unk_00)();
            func_ov004_02220c34(self, 0);
        }
    }
}
}
