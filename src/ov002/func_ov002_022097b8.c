/* func_ov002_022097b8 @ 0x022097b8, 0x4c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022097b8 {
    u8 pad_00[0x1a];
    u8 unk_1A;
};

extern int func_02002d14(const void *d, void *g, int i, int a, int b, int c);
extern int func_02002c6c(const void *d, void *g, int i, int a, int b, int c);
extern void *data_021fbe94;
extern const char data_ov002_0220bbe0[];
extern const char data_ov002_0220bbfc[];

void func_ov002_022097b8(struct UnkStruct_022097b8 *self)
{
    void *g = data_021fbe94;

    func_02002d14(data_ov002_0220bbe0, g, self->unk_1A, 0, 3, 3);
    func_02002c6c(data_ov002_0220bbfc, g, self->unk_1A, 0x242, 0x242, 0x2d7);
}
