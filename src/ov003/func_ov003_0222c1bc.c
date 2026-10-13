/* func_ov003_0222c1bc @ 0x0222c1bc, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x30];
    u8 unk_30;
    char pad_31[0x27];
    int unk_58;
    char pad_5C[4];
} UnkStruct_0222c1bc;
extern UnkStruct_0222c1bc data_ov003_0225f35c[];

int func_ov003_0222c1bc(int i)
{
    int r = 0;
    UnkStruct_0222c1bc *e;
    int s;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f35c[i];
    if (e->unk_30 == 1) {
        s = e->unk_58;
        if (s == 0) {
            r = 1;
        } else if (s == 0xf) {
            r = 2;
        }
    }
    return r;
}
