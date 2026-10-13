/* func_ov094_0229a850 @ 0x0229a850, 0x38 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a524(int, int);
extern void func_ov094_0229a530(int, int, int, int, int);

void func_ov094_0229a850(int a, int b, int c)
{
    int s = func_ov094_0229a524(a, 0);
    int i;
    for (i = 0; i <= 14; i++) {
        func_ov094_0229a530(a, s, i, b + 0x80, c + 0x60);
        s += 8;
    }
}
