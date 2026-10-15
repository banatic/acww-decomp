/* func_ov116_0229dfc0 @ 0x0229dfc0, 0x50 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229d1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern unsigned char *func_ov116_0229ddd0(void *);
extern void func_ov114_0229d52c(void *, int);
extern int func_ov116_0229dedc(void *);
extern int func_ov116_0229ded0(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov116_0229dfc0(char *p)
{
    if (func_ov114_0229d1dc(p + 0xf8)) {
        func_ov002_02208098(p, 2);
        func_ov116_0229ddd0(p);
    }
    func_ov114_0229d52c(p + 0xf8, *(int *) (p + 0x1424));
    {
        int a, b;
        a = func_ov116_0229dedc(p);
        b = func_ov116_0229ded0(p);
        func_ov002_0220a0b4(p + 0x94, a, b);
    }
}
