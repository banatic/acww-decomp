/* func_ov004_02239024 @ 0x02239024, 0x1cc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Actor {};
typedef void (Actor::*Method)();
#define W(p, o) (*(int *) ((p) + (o)))
extern "C" {
extern Method data_ov004_0225949c[];
extern void func_ov004_02238fb4(void *), func_ov004_02238fe4(short *, u8 *, int *, int, int);
extern int func_ov004_02239460(int, int), func_02056f28(void *, int);
extern void func_ov004_0223592c(void *), func_ov004_022394c4(void *, int, int, int), func_ov004_02238e70(void *),
    func_ov004_02238c38(void *, void *);
void func_ov004_02239024(u8 *self)
{
    if (self[0x252] != self[0x1e8] && self[0x1e8] != W(self, 0x15c)) {
        self[0x252] = self[0x1e8];
        self[0x280] = 4;
        W(self, 0x278) = 0xcd;
        self[0x281] = 1;
    }
    if (self[0x281] == 0) {
        (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
    } else {
        func_ov004_02238fb4(self);
    }
    func_ov004_02238fe4((short *) (self + 0x1c4), self + 0x284, (int *) (self + 0x288), 0x2aac, 0x12c);
    switch (self[0x255]) {
        case 1:
            if (func_ov004_02239460(0, 250) <= 1 || W(self, 0x1ac) >= 0x2b33) {
                if (func_02056f28(self + 0x100, 1)) {
                    W(self, 0x21c) = 0;
                    self[0x255] = 2;
                }
            } else if (W(self, 0x1ac) == W(self, 0x1b8)) {
                W(self, 0x21c) = 0;
                self[0x255] = 0;
            }
            W(self, 0x110) = 0x666;
            break;
        case 0:
            if (func_ov004_02239460(0, 100) <= 10) {
                W(self, 0x21c) = 0;
                self[0x255] = 1;
            }
            W(self, 0x110) = 0x800;
            break;
        case 2:
            if (func_ov004_02239460(0, 250) <= 1 || W(self, 0x1ac) <= 0x800) {
                W(self, 0x21c) = 0;
                self[0x255] = 1;
            }
            W(self, 0x110) = 0x4cd;
            break;
    }
    if (self[0x1ee] != 2) {
        func_ov004_0223592c(self);
    }
    func_ov004_022394c4(self, 8, 40, self[0x255]);
    ++W(self, 0x21c);
    ++W(self, 0x158);
    func_ov004_02238e70(self);
    func_ov004_02238c38(self, self + 0x26c);
}
}
