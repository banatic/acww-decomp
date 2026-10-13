/* func_ov004_0223671c @ 0x0223671c, 0xec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct Actor {};
typedef void (Actor::*Action)();
extern "C" {
extern Action data_ov004_0225949c[];
extern void func_ov004_022355f4(void *);
extern void func_ov004_02235e58(void *);
extern void func_ov004_02235ddc(void *);
extern void func_ov004_02235c54(void *);
extern void func_ov004_02239700(void *);
extern void func_ov004_02239524(void *, int);
extern void func_ov004_0223592c(void *);
extern void func_ov004_022358c0(void *, int);
extern void func_ov004_02235870(void *);
extern int func_ov004_02236418(void *);
}
extern "C" void func_ov004_0223671c(unsigned char *self)
{
    func_ov004_022355f4(self);
    (((Actor *) self)->*data_ov004_0225949c[self[0x1ee]])();
    int kind = *(int *) (self + 0x15c);
    if (kind != 46 && kind != 45) {
        if (kind == 41 || kind == 55 || kind == 43) {
            func_ov004_02235e58(self);
        }
        func_ov004_02235ddc(self);
        func_ov004_02235c54(self);
    } else {
        if (*(int *) (self + 0x1b0) > 0x13dc2) {
            *(int *) (self + 0x1b0) = 0x13dc2;
        }
    }
    if (self[0x1ee] != 2 && self[0x1ee] != 6) {
        if (*(int *) (self + 0x15c) == 43 || *(int *) (self + 0x15c) == 55) {
            func_ov004_02239700(self);
            func_ov004_02239524(self, 0x71c);
        } else {
            func_ov004_02239700(self);
            func_ov004_02239524(self, 0xe38);
        }
        func_ov004_0223592c(self);
    }
    func_ov004_022358c0(self, 0x333);
    func_ov004_02235870(self);
    ++*(int *) (self + 0x158);
    func_ov004_02236418(self);
}
