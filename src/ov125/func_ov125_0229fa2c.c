/* func_ov125_0229fa2c @ 0x0229fa2c, 0x54 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char b);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);

void func_ov125_0229fa2c(unsigned char *self)
{
    int a;
    int b;
    a = func_ov002_02208ae4(self + 0x180);
    b = func_ov002_02208ad8(self + 0x180, *(self + 0x87e));
    func_ov002_0220a08c(self + 0x644, a, b, 2);
    *(self + 0x87f) = *(self + 0x8d);
    func_ov002_02208098(self, 5);
}
