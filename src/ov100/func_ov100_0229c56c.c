/* func_ov100_0229c56c @ 0x0229c56c, 0x44 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229c5b0(int a, int b);
extern void func_02070adc(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void func_0207094c(int a0, int a1);
extern void func_02070a04(int a0, int a1, int a2);

void func_ov100_0229c56c(int a, int b)
{
    int r5;
    int x;

    r5 = 1;
    if (b) {
        r5 = 15;
    }
    x = func_ov100_0229c5b0(a, b);
    func_02070adc(x, 4, 0x1ca, 6, r5, 9, 0);
    func_0207094c(x, 0x21);
    func_02070a04(x, 1, 1);
}
