/* func_ov004_02237f38 @ 0x02237f38, 0x174 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Actor {};
typedef void (Actor::*Method)();
#define W(p, o) (*(int *) ((p) + (o)))
extern "C" {
extern Method data_ov004_0225949c[];
extern int func_ov004_02239424(void *, void *, void *, int);
extern void func_ov004_02238fe4(void *, void *, void *, int, int);
extern void func_ov004_0223592c(void *);
extern void func_ov004_022394c4(void *, int, int, int);
extern int func_ov004_02236418(void *);
extern int func_ov004_02239460(int, int);
void func_ov004_02237f38(u8 *self)
{
    func_ov004_02239424(self + 0x1c0, self + 0x1a8, self + 0x258, 0x1000);
    switch (self[0x255]) {
        case 1:
            if (func_ov004_02239460(0, 100) <= 8 || W(self, 0x1ac) >= 0x2000) {
                W(self, 0x21c) = 0;
                self[0x255] = 2;
            } else if (W(self, 0x1ac) == W(self, 0x1b8)) {
                W(self, 0x21c) = 0;
                self[0x255] = 0;
            }
            W(self, 0x110) = 0xb33;
            break;
        case 0:
            if (func_ov004_02239460(0, 100) <= 10) {
                W(self, 0x21c) = 0;
                self[0x255] = 1;
            }
            W(self, 0x110) = 0x1000;
            break;
        case 2:
            if (func_ov004_02239460(0, 100) <= 3 || W(self, 0x1ac) <= 0x1000) {
                W(self, 0x21c) = 0;
                self[0x255] = 1;
            }
            W(self, 0x110) = 0x666;
            break;
    }
    (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
    func_ov004_02238fe4(self + 0x1c4, self + 0x264, self + 0x268, 0x11c6, 150);
    if (self[0x1ee] != 2) {
        func_ov004_0223592c(self);
    }
    func_ov004_022394c4(self, 8, 81, self[0x255]);
    ++W(self, 0x21c);
    ++W(self, 0x158);
    func_ov004_02236418(self);
}
}
