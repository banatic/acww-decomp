/* func_ov003_02223ea8 @ 0x02223ea8, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    char pad_04[0x1c];
} UnkStruct_02223ea8;
typedef struct {
    char pad_00[0xa];
    u8 unk_0A;
    char pad_0B[1];
    int unk_0C;
} UnkStruct_02223ea8_2;
extern UnkStruct_02223ea8 data_ov003_0223cfa0[];
int func_02090d50(UnkStruct_02223ea8_2 *o);
void func_ov003_02223f6c(UnkStruct_02223ea8 *e, int k);

int func_ov003_02223ea8(UnkStruct_02223ea8_2 *o)
{
    int r = 1;
    UnkStruct_02223ea8 *e;
    func_02090d50(o);
    e = &data_ov003_0223cfa0[o->unk_0A];
    if (e->unk_00 == 3) {
        r = 0;
    } else {
        func_ov003_02223f6c(e, o->unk_0C);
    }
    return r;
}
