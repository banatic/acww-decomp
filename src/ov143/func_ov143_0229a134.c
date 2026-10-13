/* func_ov143_0229a134 @ 0x0229a134, 0x36 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_0229a0b0(void *self);
extern int func_ov143_0229a030(void *self);
extern void func_ov002_0220a0b4(void *addr, int a, int b);
extern void func_ov002_0220a374(void *addr, int val);
extern void func_ov143_02299f84(void *self);

void func_ov143_0229a134(void *self)
{
    int a;
    int b;

    a = func_ov143_0229a0b0(self);
    b = func_ov143_0229a030(self);
    func_ov002_0220a0b4((char *) self + 0xac, a, b);
    func_ov002_0220a374((char *) self + 0xac, 1);
    func_ov143_02299f84(self);
}
