/* func_ov118_0229b8c8 @ 0x0229b8c8, 0x16c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40[];

extern int func_ov002_02208014(u8 *self);
extern void func_ov118_0229b8b0(u8 *self);
extern void func_ov118_0229a894(u8 *self);
extern int func_ov090_02299078(int a);
extern int func_ov090_02299098(int a);
extern void func_ov118_0229c438(u8 *self, int a);
extern int func_ov090_02298f84(int a);
extern void func_ov002_0220a254(u8 *p);
extern void func_ov118_0229b834(u8 *self);
extern int func_ov118_0229b390(u8 *self);
extern int func_ov118_0229b088(u8 *self, int a, int b);
extern void func_ov002_0220a0b4(u8 *p, int a, int b);

void func_ov118_0229b8c8(u8 *self)
{
    int trg;
    int x;
    int y;
    int held;
    int ox;
    int oy;
    // ENDDECLS

    if (func_ov002_02208014(self) != 0) {
        func_ov118_0229b8b0(self);
        return;
    }
    trg = data_021fbe40[1];
    if ((trg & 1) != 0 && self[0xad] != 0xe) {
        func_ov118_0229a894(self);
        return;
    }
    if ((trg & 0x100) != 0) {
        func_ov118_0229c438(self, func_ov090_02299078(5));
        return;
    }
    if ((trg & 0x200) != 0) {
        func_ov118_0229c438(self, func_ov090_02299098(5));
        return;
    }
    ox = self[0xae];
    x = ox;
    oy = self[0xaf];
    y = oy;
    held = data_021fbe40[0];
    if ((held & 0x40) != 0) {
        y = oy - 4;
    } else if ((held & 0x80) != 0) {
        y = oy + 4;
    }
    if (y < 0x30) {
        self[0xac] = (u8) func_ov090_02298f84(ox);
        func_ov002_0220a254(self + 0x6c0);
        func_ov118_0229b834(self);
        return;
    }
    if (y > 0xb0) {
        y = 0xb0;
    }
    if ((held & 0x20) != 0) {
        x = x - 4;
    } else if ((held & 0x10) != 0) {
        x = x + 4;
    }
    if (x < 0x18) {
        x = 0x18;
    } else if (x > 0x98) {
        if (y < 0x50) {
            self[0xac] = 9;
        } else {
            y = (y - 0x50) >> 4;
            if (y >= func_ov118_0229b390(self)) {
                y = func_ov118_0229b390(self) - 1;
            }
            y = y + 0xa;
            self[0xac] = (u8) y;
        }
        func_ov118_0229b834(self);
        return;
    }
    if (x == ox && y == oy) {
        return;
    }
    self[0xae] = (u8) x;
    self[0xaf] = (u8) y;
    self[0xad] = (u8) func_ov118_0229b088(self, self[0xae], self[0xaf]);
    func_ov002_0220a0b4(self + 0x6c0, self[0xae], self[0xaf]);
}
