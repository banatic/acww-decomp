/* func_ov002_02209874 @ 0x02209874, 0x78 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209874 {
    u8 pad_00[0x19];
    u8 unk_19;
};

extern int func_0208a808(void *w);
extern int func_0208a804(void *w);
extern int func_0208a7f0(void *w);
extern int func_ov002_02209318(struct UnkStruct_02209874 *self);
extern int func_ov002_02209324(struct UnkStruct_02209874 *self);
extern void func_ov002_02209804(struct UnkStruct_02209874 *self, int x, int y);

void func_ov002_02209874(struct UnkStruct_02209874 *self, void *w)
{
    int px;
    int py;
    int h;
    int hw;
    int t;

    self->unk_19 = 0;
    px = func_0208a808(w) + 0x80;
    py = func_0208a804(w) + 0x60;
    h = func_ov002_02209318(self);
    hw = func_0208a7f0(w) >> 1;
    t = px + hw;
    if (t > 0x100) {
        px -= t - 0x100;
    } else {
        t = px - hw;
        if (t < 0) {
            px -= t;
        }
    }
    px -= 2;
    px -= func_ov002_02209324(self) >> 1;
    t = py - h;
    if (t < 0xa) {
        py += 0x10;
    } else {
        py = t;
    }
    func_ov002_02209804(self, px, py);
}
