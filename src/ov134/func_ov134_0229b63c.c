/* func_ov134_0229b63c @ 0x0229b63c, 0x44 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229b680(int a);
extern int func_0207094c(int a, int b);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(int a, int b, int c);

void func_ov134_0229b63c(int p0, int p1, int p2, int p3, unsigned char p4, int p5, unsigned char p6, unsigned char p7)
{
    int result;

    result = func_ov134_0229b680(p0);
    func_0207094c(result, p4);
    func_02070adc(result, p1, p2, p3, p6, p7, 0);
    func_02070a04(result, p5, 0);
}
