/* func_ov003_0222a938 @ 0x0222a938, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x3c];
    u8 unk_80;
    char pad_81[0x23];
} UnkStruct_0222a938;
extern UnkStruct_0222a938 data_ov003_0225f4dc[];

int func_ov003_0222a938(int i)
{
    if (i < 0 || i >= 4) {
        return 1;
    }
    {
        UnkStruct_0222a938 *e = &data_ov003_0225f4dc[i];
        if (e->unk_40 != 0) {
            return 1;
        }
    }
    return 0;
}
