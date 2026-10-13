/* func_ov002_02209954 @ 0x02209954, 0x30 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_02209954 {
    u8 pad_00[0x19];
    u8 unk_19;
};

extern int func_ov002_02209324(struct UnkStruct_02209954 *self);
extern int func_ov002_02209318(struct UnkStruct_02209954 *self);
extern void func_ov002_0220984c(struct UnkStruct_02209954 *self, int x, int y);

void func_ov002_02209954(struct UnkStruct_02209954 *self, int x, int y)
{
    int w;
    int h;
    int nx;
    int ny;

    x += 0x80;
    y += 0x60;
    w = func_ov002_02209324(self);
    h = func_ov002_02209318(self);
    nx = x - (w >> 1);
    ny = y - (h >> 1);
    func_ov002_0220984c(self, nx, ny);
}
