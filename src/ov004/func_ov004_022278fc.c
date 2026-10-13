/* func_ov004_022278fc @ 0x022278fc, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int n);
extern void func_0200f888(void *self);

void func_ov004_022278fc(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 1) || func_02056f28(self + 0x2d0, 6) || func_02056f28(self + 0x2d0, 0xb) ||
        func_02056f28(self + 0x2d0, 0x10)) {
        func_0200f888(self);
    }
}
