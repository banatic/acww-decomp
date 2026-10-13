/* func_ov004_02220c94 @ 0x02220c94, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02220c94;
typedef void (UnkStruct_02220c94::*PMF)(void);
struct Entry {
    PMF unk_00;
    u8 flag;
};
extern Entry data_ov004_02257dd8[];
struct UnkStruct_02220c94 {
    u8 pad_00[0x1ac];
    int unk_1AC;
};
extern "C" {
void func_ov004_02220c94(UnkStruct_02220c94 *self)
{
    int i;
    i = self->unk_1AC;
    if (data_ov004_02257dd8[i].flag) {
        if (data_ov004_02257dd8[i].unk_00) {
            (self->*data_ov004_02257dd8[i].unk_00)();
        }
    }
}
}
