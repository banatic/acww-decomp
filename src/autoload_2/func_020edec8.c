/* func_020edec8 @ 0x020edec8, 0x8c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xe];
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 pad_12[0x28 - 0x12];
    u8 unk_28[0x10];
} UnkStruct_020edec8;

extern int data_0213e7fc;
extern u8 data_021fd014;

extern void func_020ede60(UnkStruct_020edec8 *self);
extern int func_020e8ca8(u8 *src, u8 *dst);

void func_020edec8(UnkStruct_020edec8 *self)
{
    int t;
    int u;

    func_020ede60(self);
    if (self->unk_0F != 0) {
        return;
    }
    if (self->unk_10 != 0) {
        return;
    }
    t = !self->unk_0E;
    if (t == 0) {
        return;
    }
    u = !(data_0213e7fc != 2);
    if (u != 0) {
        self->unk_11 = 1;
        return;
    }
    func_020e8ca8(&data_021fd014, self->unk_28);
}
