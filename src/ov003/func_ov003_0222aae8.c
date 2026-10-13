/* func_ov003_0222aae8 @ 0x0222aae8, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x3c];
    u8 unk_80;
    char pad_81[0x23];
} UnkStruct_0222aae8;
extern UnkStruct_0222aae8 data_ov003_0225f4dc[];

int func_ov003_0222aae8(char *p)
{
    s8 k;
    if (p == 0) {
        return 0;
    }
    k = *(s8 *) (p + 0x227);
    if (k == -1) {
        return 0;
    }
    {
        UnkStruct_0222aae8 *e = &data_ov003_0225f4dc[k];
        e->unk_40 = 4;
    }
    return 1;
}
