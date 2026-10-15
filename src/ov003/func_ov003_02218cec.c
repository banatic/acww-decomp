/* func_ov003_02218cec @ 0x02218cec, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02218cec {
    u8 pad_00[0x7d4];
    u8 b0;
    u8 b1;
    u8 pad_7D6[0x800 - 0x7d4 - 2];
    int unk_800;
} UnkStruct_02218cec;

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_02010f5c(UnkStruct_02218cec *self);
extern void func_ov003_02218dcc(UnkStruct_02218cec *self);
extern int func_0200f530(UnkStruct_02218cec *self, int *data);
extern void func_02010d64(UnkStruct_02218cec *self);
extern void func_ov003_02218d44(UnkStruct_02218cec *self);

void func_ov003_02218cec(UnkStruct_02218cec *self)
{
    int pos[2];
    u8 *xy;
    u8 y;

    if (func_02073908(data_020ccf94, self->unk_800)) {
        func_ov003_02218dcc(self);
    } else {
        func_02010f5c(self);
        xy = &self->b0;
        y = xy[1];
        pos[0] = xy[0];
        pos[1] = y;
        func_0200f530(self, pos);
    }
    func_02010d64(self);
    func_ov003_02218d44(self);
}
