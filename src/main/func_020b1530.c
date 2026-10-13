/* func_020b1530 @ 0x020b1530, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b15b0(void);
extern int func_020b1974(int a, int b);

int func_020b1530(int arg)
{
    int x;
    x = func_020b15b0();
    if (func_020b1974(x, arg) == 0) {
        return 0;
    } else {
        return x + arg * 0x4A;
    }
}
