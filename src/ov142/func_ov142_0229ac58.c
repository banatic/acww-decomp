/* func_ov142_0229ac58 @ 0x0229ac58, 0x42 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229ae8c(int a0, int a1, int a2, int a3);
extern void func_0207094c(int a, int b);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(int a, int b, int c);

void func_ov142_0229ac58(int a0, int a1, int a2, int a3, unsigned char a4, int a5)
{
    int t;
    t = func_ov142_0229ae8c(a0, a1, a2, a3);
    func_0207094c(t, a1);
    func_02070adc(t, 6, a2, a3, a4, 4, 0);
    func_02070a04(t, a5, 0);
}
