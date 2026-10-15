/* func_ov003_022165e4 @ 0x022165e4, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int argument0);
extern int func_02056f28(void *ptr, int value);
extern void func_ov003_02216520(void *ptr);

void func_ov003_022165e4(void *self)
{
    func_02010f5c((int) self);
    if (func_02056f28((char *) self + 0x2d0, 8) != 0) {
        func_ov003_02216520(self);
    }
}
