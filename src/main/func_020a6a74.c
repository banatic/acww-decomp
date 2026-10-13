/* func_020a6a74 @ 0x020a6a74, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020a772c(u8 *p);
extern void func_020a76f8(u8 *p);
extern void func_020a76d0(u8 *p);
extern void func_020a7768(u8 *p);
extern void func_020a5bac(u8 *self, int idx);
extern void func_020a635c(u8 *self, int idx, int flag);
extern void func_020a617c(u8 *self, int idx, int flag);
extern int func_020a6364(u8 *self);
extern void func_020a6368(u8 *self, int flag);
extern int func_020a6338(u8 *self);
extern void func_020a633c(u8 *self, int flag);
extern int func_020a6230(u8 *self);
extern void func_020a6238(u8 *self, int flag);
extern int func_020a6284(u8 *self);
extern void func_020a6288(u8 *self, int flag);
extern int func_020a627c(u8 *self);
extern void func_020a6280(u8 *self, int flag);
extern int func_020a628c(u8 *self);
extern void func_020a6290(u8 *self, int flag);

void func_020a6a74(u8 *self, int idx)
{
    int off8;

    func_020a772c(self + 3 * idx);

    off8 = idx * 8;
    func_020a76f8(self + 0xc + off8);

    func_020a76d0(self + 0x2c + idx * 4);

    func_020a7768(self + 0x3c + off8);

    func_020a5bac(self, idx);
    func_020a635c(self, idx, 0);

    if (idx != 0) {
        func_020a617c(self, idx, 7);
    }

    if (idx == func_020a6364(self)) {
        func_020a6368(self, 4);
    }
    if (idx == func_020a6338(self)) {
        func_020a633c(self, 4);
    }
    if (idx == func_020a6230(self)) {
        func_020a6238(self, 4);
    }
    if (idx == func_020a6284(self)) {
        func_020a6288(self, 4);
    }
    if (idx == func_020a627c(self)) {
        func_020a6280(self, 4);
    }
    if (idx == func_020a628c(self)) {
        func_020a6290(self, 4);
    }
}
