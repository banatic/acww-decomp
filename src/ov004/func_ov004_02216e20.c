/* func_ov004_02216e20 @ 0x02216e20, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02217230(void *self);
extern int func_ov004_02217124(void *self, int k);
extern int func_ov004_0222c2b0(void);
void func_ov004_02216e20(void *self)
{
    if (func_ov004_02217230(self) == -1) {
        func_ov004_02217124(self, 8);
    } else if (func_ov004_0222c2b0() != 0) {
        func_ov004_02217124(self, 8);
    }
}
