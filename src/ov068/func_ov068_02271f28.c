/* func_ov068_02271f28 @ 0x02271f28, 0x28 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void);
extern int func_02056f28(void *ptr, int value);
extern void func_0200f888(void *ptr);

void func_ov068_02271f28(void *param)
{
    void *r4 = param;
    func_02010f5c();
    if (func_02056f28((char *) r4 + 0x2d0, 0x16)) {
        func_0200f888(r4);
    }
}
