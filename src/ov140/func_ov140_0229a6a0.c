/* func_ov140_0229a6a0 @ 0x0229a6a0, 0x3c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov140_0229a67c(unsigned char *);
extern int func_ov140_0229a65c(unsigned char *);
extern void func_ov002_0220a0b4(unsigned char *, int, int);
extern void func_ov002_0220a374(unsigned char *, int);
extern int func_ov140_0229a590(unsigned char *);

int func_ov140_0229a6a0(unsigned char *p)
{
    int a;
    int b;
    a = func_ov140_0229a67c(p);
    b = func_ov140_0229a65c(p);
    func_ov002_0220a0b4(p + 0x128c, a, b);
    func_ov002_0220a374(p + 0x128c, 7);
    return func_ov140_0229a590(p);
}
