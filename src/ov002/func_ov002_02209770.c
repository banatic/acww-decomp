/* func_ov002_02209770 @ 0x02209770, 0x48 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209770 {
    u8 pad_00[0x1a];
    u8 unk_1A;
};

extern int func_02002d14(const void *d, void *g, int i, int a, int b, int c);
extern int func_02002c6c(const void *d, void *g, int i, int a, int b, int c);
extern void *data_021fbe94;
extern const char data_ov002_0220bbb8[];
extern const char data_ov002_0220bbcc[];

int func_ov002_02209770(struct UnkStruct_02209770 *self)
{
    void *g = data_021fbe94;

    func_02002d14(data_ov002_0220bbb8, g, self->unk_1A, 0xe, 0xe, 0xe);
    return func_02002c6c(data_ov002_0220bbcc, g, self->unk_1A, 0x26e, 0x26e, 0x27d);
}
