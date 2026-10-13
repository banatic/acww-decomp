/* func_02008270 @ 0x02008270, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020082a0(int, int);
extern int func_02032c8c(int);

int func_02008270(int a, int b, int c)
{
    int x = func_020082a0(a, b);
    if (x != 0) {
        int y = func_020082a0(a, c);
        if (x == 0) {
            return func_02032c8c(a + 0x7a4);
        }
        return y;
    }
    return x;
}
