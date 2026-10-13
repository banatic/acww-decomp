/* func_ov003_022240fc @ 0x022240fc, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int unk_00, unk_04, unk_08;
    u8 unk_0C, unk_0D, unk_0E, unk_0F;
    char pad_10[4];
    int unk_14, unk_18, unk_1C;
} UnkStruct_022240fc;
extern int data_ov003_0223ac00[];

void func_ov003_022240fc(UnkStruct_022240fc *o, int a1, int a2, int k, int a5, Vec3 *v, int flag)
{
    o->unk_00 = a1;
    o->unk_04 = a2;
    o->unk_0E = 0;
    o->unk_14 = v->x;
    o->unk_18 = v->y;
    o->unk_1C = v->z;
    o->unk_0F = (u8) k;
    if (flag == 0) {
        o->unk_08 = data_ov003_0223ac00[k];
    } else {
        o->unk_08 = 4;
    }
    o->unk_0C = (u8) a5;
}
