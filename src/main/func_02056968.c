/* func_02056968 @ 0x02056968, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020579f0(int, u8);
extern int func_020b9e80(int *, int, u8, int);

struct UnkStruct_02056968 {
    int unk_00;
    int unk_04;
    u8 pad_08[0x20 - 8];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 pad_23;
    u16 unk_24;
};

void func_02056968(struct UnkStruct_02056968 *s, int a, int b)
{
    int v = func_020579f0(b, s->unk_20);
    if (func_020b9e80(&s->unk_04, a, s->unk_22, v) == 0) {
        s->unk_21 = 0xff;
        s->unk_20 = 0xff;
        s->unk_24 = 0xffff;
    }
}
