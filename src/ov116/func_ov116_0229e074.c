/* func_ov116_0229e074 @ 0x0229e074, 0x4c bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229d2d8(char *p);
extern unsigned char *func_ov002_02208098(char *p, unsigned char value);
extern void func_ov114_0229d52c(char *p, unsigned int v);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern int func_ov116_0229dedc(char *p);
extern int func_ov116_0229ded0(char *p);

void func_ov116_0229e074(char *self)
{
    int res1, res2;
    if (func_ov114_0229d2d8(self + 0xf8)) {
        func_ov002_02208098(self, 7);
    }
    func_ov114_0229d52c(self + 0xf8, *(unsigned int *) (self + 0x1424));
    res1 = func_ov116_0229dedc(self);
    res2 = func_ov116_0229ded0(self);
    func_ov002_0220a0b4(self + 0x94, res1, res2);
}
