/* func_020764f0 @ 0x020764f0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int a, int b, int c, int d);
extern int func_020a132c(int x);
extern int func_020a1240(int x, int y, int z);

int func_020764f0(int a, int b, int c, int d)
{
    int result = func_020b65c4(a, b, c, d);
    if (result != 46) {
        return result;
    }
    result = func_020a132c(result);
    if (result != 0) {
        result = func_020a1240(func_020a132c(result), d, 1);
    }
    return result;
}
