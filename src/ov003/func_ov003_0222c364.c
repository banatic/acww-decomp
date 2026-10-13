/* func_ov003_0222c364 @ 0x0222c364, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x30];
    u8 unk_30;
    char pad_31[0x27];
    int unk_58;
    char pad_5C[4];
} UnkStruct_0222c364;
extern UnkStruct_0222c364 data_ov003_0225f35c[];
int func_ov003_0222c16c(UnkStruct_0222c364 *e);
int func_ov003_0222c364(int i)
{
    UnkStruct_0222c364 *e;
    int st;
    if (i < 0 || i >= 4) {
        return 0;
    }
    e = &data_ov003_0225f35c[i];
    st = *(u8 *) ((char *) e + 0x30);
    if (st == 0 || (st == 2 && e->unk_58 > 0x64) || func_ov003_0222c16c(e) != 0) {
        return 0;
    }
    return 1;
}
