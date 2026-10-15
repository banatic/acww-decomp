/* func_ov139_022997f0 @ 0x022997f0, 0x96 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov139_02299744(int);
extern int func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

void func_ov139_022997f0(int param)
{
    int a;
    a = func_ov139_02299744(param);
    func_0207094c(a, 0x65);
    func_02070adc(a, 8, 0x93, 6, 15, 0, 0);
    func_02070a04(a, 1, 0);
    a = func_ov139_02299744(param);
    func_0207094c(a, 0xc2);
    func_02070adc(a, 8, 0x8d, 6, 15, 0, 0);
    func_02070a04(a, 1, 0);
    a = func_ov139_02299744(param);
    func_0207094c(a, 0xc1);
    func_02070adc(a, 8, 0x99, 6, 15, 0, 0);
    func_02070a04(a, 1, 0);
}
