/* func_ov004_02211294 @ 0x02211294, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_02211294 {
    u16 pad_00[6];
    u16 unk_0C;
};

int func_ov004_02211294(struct UnkStruct_02211294 *self)
{
    int ok = 1;
    u16 v = self->unk_0C;
    int a = (v == 0x36) ? 1 : 0;
    if (a == 0) {
        int b = (v == 0x37) ? 1 : 0;
        if (b == 0) {
            ok = 0;
        }
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}
