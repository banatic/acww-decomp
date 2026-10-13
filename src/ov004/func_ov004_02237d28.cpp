/* func_ov004_02237d28 @ 0x02237d28, 0x1c8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class Actor {};
typedef void (Actor::*Method)();
#define W(p, o) (*(int *) ((p) + (o)))
#define U(p, o) (*(unsigned int *) ((p) + (o)))
extern "C" {
extern Method data_ov004_0225949c[];
extern void func_ov004_022355f4(void *);
extern int func_02056f28(void *, u16), func_ov004_02239820(void *, int), func_ov004_02239460(int, int),
    func_ov004_02236418(void *);
extern void func_ov004_02239700(void *), func_ov004_02239524(void *, int), func_ov004_0223592c(void *),
    func_ov004_022358c0(void *, int), func_ov004_02235870(void *), func_ov004_02235c54(void *), func_ov004_02235ddc(void *);
void func_ov004_02237d28(u8 *self)
{
    unsigned int frame;
    u16 limit;
    func_ov004_022355f4(self);
    (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
    frame = (U(self, 0x104) << 4) >> 16;
    limit = frame - 1;
    if (W(self, 0x110) > 0x1000) {
        limit = frame - 2;
    }
    switch (self[0x256]) {
        case 0:
            if (self[0x40]) {
                self[0x255] = 1;
            }
            if (self[0x255] && func_02056f28(self + 0x100, limit)) {
                self[0x256] = 1;
                W(self, 0x210) <<= 1;
                func_ov004_02239820(self, 1);
                self[0x255] = 0;
            }
            break;
        case 1:
            if (func_02056f28(self + 0x100, limit)) {
                self[0x257] = func_ov004_02239460(60, 80);
                self[0x258] = 0;
                self[0x256] = 2;
                func_ov004_02239820(self, 2);
            }
            break;
        case 2:
            if (self[0x258] > self[0x257]) {
                if (func_02056f28(self + 0x100, limit)) {
                    self[0x256] = 3;
                    W(self, 0x210) >>= 1;
                    func_ov004_02239820(self, 3);
                }
            } else {
                ++self[0x258];
            }
            break;
        case 3:
            if (func_02056f28(self + 0x100, limit)) {
                self[0x256] = 0;
                func_ov004_02239820(self, 0);
            }
            break;
    }
    if (self[0x1ee] != 2 && self[0x1ee] != 6) {
        func_ov004_02239700(self);
        func_ov004_02239524(self, 0x1554);
        func_ov004_0223592c(self);
    }
    func_ov004_022358c0(self, 0x666);
    func_ov004_02235870(self);
    func_ov004_02235c54(self);
    func_ov004_02235ddc(self);
    ++W(self, 0x158);
    if (func_ov004_02236418(self)) {
        if (self[0x256] == 0) {
            self[0x255] = 1;
        } else {
            self[0x258] = 0;
        }
    }
}
}
