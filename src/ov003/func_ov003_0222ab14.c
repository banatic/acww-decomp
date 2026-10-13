/* func_ov003_0222ab14 @ 0x0222ab14, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x3c];
    u8 unk_80;
    char pad_81[0x23];
} UnkStruct_0222ab14;
extern UnkStruct_0222ab14 data_ov003_0225f4dc[];

int func_ov003_0222ab14(char *p)
{
    int r = 0;
    s8 k;
    if (p == 0) {
        return r;
    }
    k = *(s8 *) (p + 0x227);
    if (k == -1) {
        return r;
    }
    {
        UnkStruct_0222ab14 *e = &data_ov003_0225f4dc[k];
        if (e->unk_80 != 0) {
            r = 1;
        }
    }
    return r;
}
