/* func_ov094_0229a804 @ 0x0229a804, 0x4a bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a524(int a, int b);
extern int func_ov094_0229aba4(int a, unsigned char b);
extern void func_ov094_0229a530(int a, int b, int c, int d, int e);

void func_ov094_0229a804(int param0, int param1, int param2, int param3)
{
    int r5;
    int i;
    r5 = func_ov094_0229a524(param0, 0);
    for (i = 0; i <= 14; i++) {
        if (func_ov094_0229aba4(param0, i) + 0x18 > param3) {
            func_ov094_0229a530(param0, r5, i, param1 + 0x80, param2 + 0x60);
        }
        r5 += 8;
    }
}
