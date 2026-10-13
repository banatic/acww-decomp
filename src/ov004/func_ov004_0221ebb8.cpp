/* func_ov004_0221ebb8 @ 0x0221ebb8, 0x3a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221ebb8;
typedef void (UnkStruct_0221ebb8::*PMF)(int);
struct UnkStruct_0221ebb8_2 {
    u8 pad_00[8];
    PMF unk_08;
};
struct UnkStruct_0221ebb8 {
    int unk_00;
    UnkStruct_0221ebb8_2 *unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
};
extern "C" {
void func_ov004_0221ebb8(UnkStruct_0221ebb8 *self, int arg)
{
    if (self->unk_04) {
        (self->*(self->unk_04->unk_08))(arg);
    }
    if (self->unk_10 > 0) {
        self->unk_10--;
    }
}
}
