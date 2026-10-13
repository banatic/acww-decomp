/* func_ov120_0229b2b0 @ 0x0229b2b0, 0x58 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229b400(int a);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_ov120_0229b244(int a, int b, unsigned char c);
extern void func_02070a04(int a, int b, int c);

void func_ov120_0229b2b0(int arg0, unsigned char *arg1)
{
    int i;
    int r;
    int v0 = 0;
    int v1 = 0;

    for (i = 0; i < 13; i++) {
        r = func_ov120_0229b400(arg0);
        func_02070adc(r, 6, 0x160 + i * 16, 8, 1, 0xf, v0);
        func_ov120_0229b244(arg0, r, arg1[i]);
        func_02070a04(r, v1, v1);
    }
}
