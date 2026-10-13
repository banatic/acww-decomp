/* func_ov130_02299bd8 @ 0x02299bd8, 0x2e bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_02299af0(int, int, int, int);

void func_ov130_02299bd8(int a, int b, int c, int d, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        func_ov130_02299af0(a, b, c, d);
        c -= 2;
    }
}
