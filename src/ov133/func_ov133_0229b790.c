/* func_ov133_0229b790 @ 0x0229b790, 0x1a8 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define CUR(s) (*(vu8 *) ((s) + 0x9c))

extern int func_ov002_022088ac(void *pad);
extern int func_ov002_0220889c(void *pad);
extern int func_ov002_022088cc(void *pad);
extern int func_ov002_022088bc(void *pad);
extern int func_ov002_02209f00(u8 *p);
extern int func_ov133_0229b36c(u8 *self, void *pad);
extern void func_0200467c(int cmd);
extern void func_ov133_0229b320(u8 *self, u8 v);

int func_ov133_0229b790(u8 *self, void *pad)
{
    u8 prev = CUR(self);
    int y;

    if (pad == 0) {
        return 0;
    }
    if (prev <= 0xb) {
        if (func_ov002_022088ac(pad)) {
            if (CUR(self) % 3 > 0) {
                CUR(self) = CUR(self) - 1;
            }
        } else if (func_ov002_0220889c(pad)) {
            if (CUR(self) % 3 < 2) {
                CUR(self) = CUR(self) + 1;
            } else {
                CUR(self) = 0xd;
            }
        }
        if (CUR(self) <= 0xb) {
            if (func_ov002_022088cc(pad)) {
                if (CUR(self) <= 2) {
                    CUR(self) = 0xc;
                } else {
                    CUR(self) = CUR(self) - 3;
                }
            } else if (func_ov002_022088bc(pad)) {
                u8 c = CUR(self);

                if (c < 9 || c > 0xb) {
                    CUR(self) = CUR(self) + 3;
                } else {
                    CUR(self) = 0xe;
                }
            }
        }
    } else if (prev == 0xc) {
        if (func_ov002_022088bc(pad)) {
            y = func_ov002_02209f00(self + 0x11c);
            if (y <= 0x70) {
                CUR(self) = 0;
            } else if (y <= 0x90) {
                CUR(self) = 1;
            } else {
                CUR(self) = 2;
            }
        } else if (func_ov133_0229b36c(self, pad)) {
            func_0200467c(0xb);
            func_ov133_0229b320(self, *(u8 *) (self + 0x9f));
        }
    } else if (prev == 0xd) {
        if (func_ov002_022088ac(pad)) {
            CUR(self) = 0xe;
        } else if (func_ov002_022088cc(pad)) {
            CUR(self) = 0xb;
        }
    } else if (prev == 0xe) {
        if (func_ov002_0220889c(pad)) {
            CUR(self) = 0xd;
        } else if (func_ov002_022088cc(pad)) {
            CUR(self) = 0xa;
        }
    }
    if (prev != CUR(self)) {
        return 1;
    }
    return 0;
}
