/* func_ov068_022741e4 @ 0x022741e4, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099e9c(void *ptr);
extern void func_0209a050(int index);
extern int func_0209a000(void *ptr, int val);

void func_ov068_022741e4(int unused, int flag)
{
    short a;
    short b;
    int index;
    if (flag != 0) {
        return;
    }
    a = 0x3530;
    if ((index = func_02099e9c(&a)) == -1) {
        return;
    }
    func_0209a050(index);
    b = 0x4a34;
    func_0209a000(&b, 0);
}
