/* func_ov004_02236a78 @ 0x02236a78, 0x15c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class Actor;
typedef void (Actor::*Method)();
extern "C" Method data_ov004_0225949c[];
extern "C" int func_02056f28(void *, int);
extern "C" void func_ov004_02239820(void *, int);
extern "C" void func_ov004_022368bc(void *);
extern "C" void func_ov004_02239700(void *);
extern "C" void func_ov004_02239524(void *, int);
extern "C" void func_ov004_0223592c(void *);
extern "C" void func_ov004_022358c0(void *, int);
extern "C" void func_ov004_02235870(void *);
extern "C" void func_ov004_02235c54(void *);
extern "C" void func_ov004_02235ddc(void *);
extern "C" int func_ov004_02236418(void *);
extern "C" void func_ov004_02236a78(unsigned char *self)
{
    if (!self[0x256]) {
        if (func_02056f28(self + 0x100, (unsigned short) (((*(unsigned int *) (self + 0x104) << 4) >> 16) - 1))) {
            self[0x256] = 1;
            func_ov004_02239820(self, 1);
        }
    }
    if (self[0x1ee] == 2) {
        self[0x255] = 0;
        if (func_02056f28(self + 0x100, (unsigned short) (((*(unsigned int *) (self + 0x104) << 4) >> 16) - 1))) {
            self[0x256] = 0;
            func_ov004_02239820(self, 0);
            self[0x255] = 1;
        }
    } else if (self[0x1ee] != 2 && self[0x255] == 0) {
        self[0x255] = 1;
    }
    if (self[0x255]) {
        (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
        func_ov004_022368bc(self);
        if (self[0x1ee] == 4) {
            func_ov004_02239700(self);
            func_ov004_02239524(self, 0x1554);
        }
    }
    if (self[0x1ee] != 6 && self[0x1ee] != 5) {
        func_ov004_0223592c(self);
    }
    if (!self[0x256]) {
        func_ov004_022358c0(self, 0xccd);
    } else {
        func_ov004_022358c0(self, 0x666);
    }
    func_ov004_02235870(self);
    func_ov004_02235c54(self);
    func_ov004_02235ddc(self);
    ++*(int *) (self + 0x158);
    if (func_ov004_02236418(self)) {
        self[0x256] = 0;
        func_ov004_02239820(self, 0);
        self[0x255] = 1;
    }
}
