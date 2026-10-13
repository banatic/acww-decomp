/* func_020ee59c @ 0x020ee59c, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xe];
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 pad_11[0x28 - 0x11];
    u8 unk_28[0x10];
    u8 unk_38[0x10];
} UnkStruct_020ee59c;

extern u8 data_021fd014;
extern int data_0213e7fc;
extern u8 data_021fd004;
extern u8 data_021fd024;

extern void func_020e8ce0(u8 *src, u8 *dst);
extern void func_020ee8a8(u8 *src, u8 *dst);

void func_020ee59c(UnkStruct_020ee59c *self, int mode)
{
    int t;

    if (mode != 2) {
        return;
    }
    func_020e8ce0(&data_021fd014, self->unk_28);
    t = !(data_0213e7fc != 3);
    if (t != 0) {
        self->unk_10 = 1;
        return;
    }
    func_020ee8a8(&data_021fd004, self->unk_28);
    func_020ee8a8(&data_021fd024, self->unk_38);
    self->unk_0E = 1;
}
