/* func_ov003_02223edc @ 0x02223edc, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    char pad_04[9];
    s8 unk_0D;
    s8 unk_0E;
    char pad_0F[1];
    char pad_10[0x10];
} UnkStruct_02223edc;
typedef struct {
    char pad_00[0xa];
    u8 unk_0A;
} UnkStruct_02223edc_2;
extern UnkStruct_02223edc data_ov003_0223cfa0[];
int func_ov003_02223ea8(UnkStruct_02223edc_2 *o);

int func_ov003_02223edc(UnkStruct_02223edc_2 *o)
{
    UnkStruct_02223edc *e = &data_ov003_0223cfa0[o->unk_0A];
    int v = e->unk_0D;
    if (v - 1 < 0) {
        e->unk_00 = 3;
    }
    e->unk_0D = (s8) (v - 1);
    e->unk_0E = (s8) (e->unk_0E + 1);
    return func_ov003_02223ea8(o);
}
