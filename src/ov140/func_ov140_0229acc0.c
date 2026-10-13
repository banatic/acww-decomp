/* func_ov140_0229acc0 @ 0x0229acc0, 0x8c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov139_02299af8(u8 *p, int a, int b);
extern void func_ov140_0229a3fc(u8 *self, int a);

void func_ov140_0229acc0(u8 *self)
{
    int i;
    int j;

    *(u16 *) (self + 0x8ac) = 0;
    func_ov139_02299af8(self + 0x8e8, 6, 0x7f);
    for (i = 0; i < 6; i++) {
        (self + i)[0x8af] = 0;
        (self + i)[0x8e0] = 0;
    }
    for (j = 0; j < 0x20; j++) {
        (self + j)[0x8b5] = 0xff;
    }
    func_ov140_0229a3fc(self, -1);
    *(int *) (self + 0xa4) = 8;
    *(int *) (self + 0xa8) = 9;
    self[0x8dc] = 0;
    self[0x8dd] = 0;
    self[0x8de] = 0;
}
