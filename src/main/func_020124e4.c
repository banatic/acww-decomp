/* func_020124e4 @ 0x020124e4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082c98(int, int, int, int);
extern int func_0205eae0(int, int, int, int);

int func_020124e4(int a, int b, int c, int d)
{
    int ret = func_02082c98(a + 4, b, c, d);
    if (ret) {
        ret = func_0205eae0(ret, b, c, d);
    }
    return ret;
}
