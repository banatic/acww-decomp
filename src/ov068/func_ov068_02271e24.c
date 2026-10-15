/* func_ov068_02271e24 @ 0x02271e24, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int argument0);
extern int func_02056f28(void *ptr, int size);
extern void func_0200f888(void *ptr);

void func_ov068_02271e24(void *param)
{
    void *r4 = param;
    func_02010f5c((int) param);
    if (func_02056f28((char *) r4 + 0x2d0, 8) != 0) {
        func_0200f888(r4);
    }
}
