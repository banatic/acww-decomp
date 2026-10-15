/* func_ov142_0229ac9c @ 0x0229ac9c, 0x48 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_0229ae8c(int a);
extern int func_02070918(int a, int b, int c, int d, int e, int f);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_0207099c(int a);

void func_ov142_0229ac9c(int a, int b)
{
    int ret;

    ret = func_ov142_0229ae8c(a);
    func_02070918(ret, b, 8, 0, 0, 1);
    func_02070adc(ret, 6, 0x15d, 8, 0xe, 4, 1);
    func_0207099c(ret);
}
