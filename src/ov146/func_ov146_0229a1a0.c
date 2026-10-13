/* func_ov146_0229a1a0 @ 0x0229a1a0, 0x96 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_0229a42c(int);
extern int func_0207094c(int, int);
extern int func_02070adc(int, int, int, int, int, int, int);
extern int func_02070a04(int, int, int);

void func_ov146_0229a1a0(int r0)
{
    int r4;
    int r5;
    int r1;
    int r2;
    int r3;
    int sp0;
    int sp4;
    int sp8;

    r4 = r0;
    r5 = func_ov146_0229a42c(r4);
    r1 = 0x65;
    func_0207094c(r5, r1);
    sp0 = 0xf;
    sp4 = 0;
    sp8 = 0;
    func_02070adc(r5, 8, 0x93, 6, sp0, sp4, sp8);
    func_02070a04(r5, 1, 0);

    r5 = func_ov146_0229a42c(r4);
    r1 = 0xc2;
    func_0207094c(r5, r1);
    sp0 = 0xf;
    sp4 = 0;
    sp8 = 0;
    func_02070adc(r5, 8, 0x8d, 6, sp0, sp4, sp8);
    func_02070a04(r5, 1, 0);

    r4 = func_ov146_0229a42c(r4);
    r1 = 0xc1;
    func_0207094c(r4, r1);
    sp0 = 0xf;
    sp4 = 0;
    sp8 = 0;
    func_02070adc(r4, 8, 0x99, 6, sp0, sp4, sp8);
    func_02070a04(r4, 1, 0);
}
