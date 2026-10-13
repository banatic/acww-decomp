/* func_ov094_0229a9b4 @ 0x0229a9b4, 0x60 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a524(unsigned int a, unsigned int b);
extern int func_ov094_0229aaac(unsigned int a, unsigned int b);
extern int func_ov094_0229aa84(unsigned int a, unsigned int b);
extern void func_ov094_0229a34c(unsigned int a, unsigned int b);
extern void func_ov094_0229a36c(unsigned int a, unsigned int b);
extern void func_ov094_0229a958(unsigned int a, int b, int c, int d);

void func_ov094_0229a9b4(unsigned int param1, unsigned int param2)
{
    int r7;
    int r6;
    int sp0;
    volatile unsigned short v;

    r7 = func_ov094_0229a524(param1, param2);
    r6 = func_ov094_0229aaac(param1, param2);
    sp0 = func_ov094_0229aa84(param1, param2);
    v = r6;
    if (v == 0xfff1) {
        func_ov094_0229a34c(param1 + 0xa38, param2);
    } else {
        func_ov094_0229a36c(param1 + 0xa38, param2);
        func_ov094_0229a958(param1, r7, r6, sp0);
    }
}
