/* func_ov119_0229bacc @ 0x0229bacc, 0x40 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229bb44(int a);
extern int func_0207094c(int a, int b);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(int a, int b, int c);

void func_ov119_0229bacc(int param0, int param1)
{
    int result = func_ov119_0229bb44(param0);
    func_0207094c(result, param1);
    func_02070adc(result, 8, 0x160, 0xd, 0xf, 0, 0);
    func_02070a04(result, 1, 0);
}
