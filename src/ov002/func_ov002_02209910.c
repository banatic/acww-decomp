/* func_ov002_02209910 @ 0x02209910, 0x44 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209910 {
    u8 pad_00[0x19];
    u8 unk_19;
};

extern int func_ov002_02209324(struct UnkStruct_02209910 *self);
extern int func_ov002_02209318(struct UnkStruct_02209910 *self);
extern void func_ov002_0220984c(struct UnkStruct_02209910 *self, int x, int y);

void func_ov002_02209910(struct UnkStruct_02209910 *self, int x, int y)
{
    int w;
    int h;
    int nx;
    int ny;

    w = func_ov002_02209324(self);
    h = func_ov002_02209318(self);
    nx = x - w + 0x20;
    if (nx > 0) {
        self->unk_19 = 1;
    } else {
        nx = x - 0x10;
        self->unk_19 = 0;
    }
    ny = y - h - 4;
    if (ny < 0xa) {
        ny = 0xa;
    }
    func_ov002_0220984c(self, nx, ny);
}
