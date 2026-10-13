/* func_02037d64 @ 0x02037d64, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02037d9c(int);

int func_02037d64(int a, int b)
{
    int r4;
    r4 = b;
    r4 = r4 & func_02037d9c(a);
    if (r4 != 0) {
        return 1;
    } else {
        return 0;
    }
}
