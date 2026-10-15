/* func_ov133_0229c050 @ 0x0229c050, 0x54 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov130_0229a3f0(int v);
extern void *func_ov133_0229bb34(char *self);
extern int func_0207094c(void *w, int a);
extern void func_02070adc(void *w, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *w, int a, int b);
extern void func_ov002_0220af94(void *receiver);

void func_ov133_0229c050(char *self)
{
    void *w;

    func_ov130_0229a3f0(7);
    w = func_ov133_0229bb34(self);
    func_0207094c(w, 0xd7);
    func_02070adc(w, 8, 0x14c, 0xe, 0xf, 0, 0);
    func_02070a04(w, 1, 0);
    func_ov002_0220af94(self + 0x180);
}
