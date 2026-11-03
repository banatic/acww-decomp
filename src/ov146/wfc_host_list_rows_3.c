/* wfc_host_list_rows_3: 3 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_0229a1a0 @ 0x0229a1a0, 0x96 bytes, Thumb
 * func_ov146_0229a17c @ 0x0229a17c, 0x24 bytes, Thumb
 * func_ov146_0229a174 @ 0x0229a174, 0x8 bytes, Thumb
 */

extern int func_ov146_0229a42c(int);
extern int func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);
extern unsigned int func_020eb844(void);

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

void func_ov146_0229a17c(unsigned char *p)
{
    if (p[0xb5] == 0) {
        func_ov146_0229a1a0((int) p);
        p[0xb5]++;
    }
}

unsigned int func_ov146_0229a174(void *receiver)
{
    return func_020eb844();
}
