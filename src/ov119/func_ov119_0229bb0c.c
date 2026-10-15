/* func_ov119_0229bb0c @ 0x0229bb0c, 0x38 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229bb44(unsigned char *parameter0);
extern int func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

void func_ov119_0229bb0c(unsigned char *arg0)
{
    int r4;
    int sp[4];

    r4 = func_ov119_0229bb44((unsigned char *) arg0);
    func_0207094c(r4, 0xd6);
    sp[0] = 0xf;
    sp[1] = 0;
    sp[2] = 0;
    func_02070adc(r4, 8, 0xca, 6, sp[0], sp[1], sp[2]);
    func_02070a04(r4, 1, 0);
}
