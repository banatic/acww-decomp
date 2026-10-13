/* func_ov130_02299b88 @ 0x02299b88, 0x50 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov130_02299af0(int, int, int, int);

void func_ov130_02299b88(int a, int b, int c, int d, int e)
{
    int i;

    for (i = 0; i < e; i++) {
        if (b == 0) {
            func_ov130_02299af0(a, 11, c, d);
        } else {
            func_ov130_02299af0(a, b % 10, c, d);
            b = b / 10;
        }
        c -= 2;
    }
}
