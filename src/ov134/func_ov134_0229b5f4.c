/* func_ov134_0229b5f4 @ 0x0229b5f4, 0x46 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229b680(int a0);
extern int func_0207094c(int a0, unsigned char a1);
extern void func_02070adc(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void func_020709c4(int a0, int a1, int a2);

void func_ov134_0229b5f4(int a0, int a1, int a2, int a3, unsigned char a4, int a5)
{
    int tmp;
    tmp = func_ov134_0229b680(a0);
    func_0207094c(tmp, a4);
    func_02070adc(tmp, a1, a2, a3, 15, 0, 0);
    func_020709c4(tmp, 1, -((a3 - a5) << 2));
}
