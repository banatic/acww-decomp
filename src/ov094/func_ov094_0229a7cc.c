/* func_ov094_0229a7cc @ 0x0229a7cc, 0x38 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a524(int a, int b);
extern void func_ov094_0229a530(int a, int b, int c, int d, int e);

void func_ov094_0229a7cc(int param1, int param2, int param3)
{
    int value;
    int i;
    value = func_ov094_0229a524(param1, 15);
    for (i = 15; i <= 29; i++) {
        func_ov094_0229a530(param1, value, i, param2 + 0x80, param3 + 0x60);
        value += 8;
    }
}
