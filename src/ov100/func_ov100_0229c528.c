/* func_ov100_0229c528 @ 0x0229c528, 0x44 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229c5b0(int a, int b);
extern void func_02070adc(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
extern void func_0207094c(int a1, int a2);
extern void func_02070a04(int a1, int a2, int a3);

void func_ov100_0229c528(int a, int b)
{
    int x = 1;
    int ret;
    if (b != 0) {
        x = 15;
    }
    ret = func_ov100_0229c5b0(a, b);
    func_02070adc(ret, 4, 0x1d6, 6, x, 9, 0);
    func_0207094c(ret, 101);
    func_02070a04(ret, 1, 1);
}
