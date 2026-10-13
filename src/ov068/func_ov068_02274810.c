/* func_ov068_02274810 @ 0x02274810, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020960f8(int, int);
extern void func_ov068_022749dc(int, int);

int func_ov068_02274810(int param)
{
    int result;
    int r4 = param;
    result = func_020960f8(0x28, 4);
    if (result != 0) {
        func_ov068_022749dc(r4, 2);
    }
    return 1;
}
