/* func_ov133_0229badc @ 0x0229badc, 0x58 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov133_0229ba84(unsigned char *p);
extern int func_ov133_0229ba34(unsigned char *p);
extern void func_ov133_0229b938(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int val);

void func_ov133_0229badc(unsigned char *p)
{
    int a;
    int b;
    a = func_ov133_0229ba84(p);
    b = func_ov133_0229ba34(p);
    func_ov002_0220a0b4(p + 0x11c, a, b);
    if ((unsigned char) (p[0x9c] + 0xf3) <= 1) {
        func_ov002_0220a374(p + 0x11c, 7);
    } else {
        func_ov002_0220a374(p + 0x11c, 1);
    }
    func_ov133_0229b938(p);
}
