/* func_ov004_02238804 @ 0x02238804, 0x168 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Actor {};
typedef void (Actor::*Method)();
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define B(p, o) (*(signed char *) ((p) + (o)))
extern "C" {
extern Method data_ov004_0225949c[];
extern int func_020e89dc(short *, int, int);
extern void func_ov004_02239bb4(void *, int, int), func_ov004_022398a8(void *, u16), func_020e88dc(int *, int, int),
    func_ov004_02239858(void *), func_ov004_022358c0(void *, int);
void func_ov004_02238804(u8 *self, int low, int high)
{
    if (W(self, 0x1a8) <= (low + 2) * 0x1000) {
        if (func_020e89dc((short *) (self + 0x1c0), 0x4000, 0x444)) {
            W(self, 0x1a8) += 0x133;
        }
        func_ov004_02239bb4(self + 0x1a8, 0x133, S(self, 0x1c0));
        W(self, 0x110) = 0x1000;
        B(self, 0x1fe) = 3;
        func_ov004_022398a8(self, (u16) B(self, 0x1fe));
    } else if (W(self, 0x1a8) >= (high - 2) * 0x1000) {
        if (func_020e89dc((short *) (self + 0x1c0), -0x4000, 0x444)) {
            W(self, 0x1a8) -= 0x133;
        }
        func_ov004_02239bb4(self + 0x1a8, 0x133, S(self, 0x1c0));
        W(self, 0x110) = 0x1000;
        B(self, 0x1fe) = 10;
        func_ov004_022398a8(self, (u16) B(self, 0x1fe));
    } else {
        if (B(self, 0x1fe) == 3) {
            func_020e89dc((short *) (self + 0x1c0), 0x4000, 0x444);
        } else if (B(self, 0x1fe) == 10) {
            func_020e89dc((short *) (self + 0x1c0), -0x4000, 0x444);
        }
        (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
        if ((unsigned) (W(self, 0x15c) - 53) <= 1) {
            func_020e88dc((int *) (self + 0x1b0), 0x10800, 0xcd);
        } else if (W(self, 0x15c) == 52) {
            func_020e88dc((int *) (self + 0x1b0), 0x10000, 0xcd);
        }
        func_ov004_02239858(self);
        func_ov004_022358c0(self, 0x333);
    }
}
}
