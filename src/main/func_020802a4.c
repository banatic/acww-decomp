/* func_020802a4 @ 0x020802a4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int, int);
extern void func_02081c14(int, int, int);

int func_020802a4(int a, int b, int c, int d)
{
    int ret = func_020807a8(a, d);
    if (ret != 0) {
        func_02081c14(ret, b, c);
    }
    return ret;
}
