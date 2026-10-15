/* func_ov110_0229c4f8 @ 0x0229c4f8, 0x44 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov110_0229c53c(int a);
extern void func_02070adc(void *p, int a, int b, int c, int d, int e, int f);
extern int func_0207094c(void *p, int x);
extern void func_02070a04(void *p, int x, int y);

void func_ov110_0229c4f8(int a, int b)
{
    int flags;
    void *p;
    flags = 1;
    if (b) {
        flags = 0xf;
    }
    p = func_ov110_0229c53c(a);
    func_02070adc(p, 4, 0x1ca, 6, flags, 9, 0);
    func_0207094c(p, 0x88);
    func_02070a04(p, 1, 1);
}
