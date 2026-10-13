/* func_ov003_0222409c @ 0x0222409c, 0x2e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int unk_00;
    u16 unk_04;
    u16 unk_06;
    short unk_08;
} UnkStruct_0222409c;
typedef struct {
    char pad_00[0xd];
    u8 unk_0D;
} UnkStruct_0222409c_2;
typedef struct {
    char pad_00[0x50];
    int unk_50;
    char pad_54[4];
    u16 unk_58;
    char pad_5A[0xe];
    u8 unk_68;
} UnkStruct_0222409c_3;
UnkStruct_0222409c *func_ov003_022240cc(UnkStruct_0222409c_2 *a);

void func_ov003_0222409c(UnkStruct_0222409c_2 *a, UnkStruct_0222409c_3 *b)
{
    UnkStruct_0222409c *x = func_ov003_022240cc(a);
    b->unk_68 = (u8) x->unk_04;
    b->unk_58 = x->unk_06;
    b->unk_50 = x->unk_08;
    a->unk_0D = (u8) x->unk_00;
}
