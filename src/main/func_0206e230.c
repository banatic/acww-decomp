/* func_0206e230 @ 0x0206e230, 0x9e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200277c(unsigned char *p);
extern void func_020029e8(unsigned char *p, int v);
extern void func_020028bc(unsigned char *p, int a, int b, int c);
extern void func_0200284c(unsigned char *p, int a, int b);
extern unsigned char *func_02066648(unsigned char *p);
extern void func_ov002_0220a448(unsigned char *p, unsigned char *q);
extern void func_0206e1d8(unsigned char *a, unsigned char *b);
extern void func_0206e114(unsigned char *a, unsigned char *b, int v);
extern void func_0206e03c(unsigned char *a, unsigned char *b, int v);
extern void func_0206dff8(unsigned char *a, unsigned char *b);
extern void func_0206e344(unsigned char *a, unsigned char *b);
extern void func_0206e2d0(unsigned char *a);

void func_0206e230(unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d, int e)
{
    int zero = 0;
    unsigned char *p = b + 0x58;

    func_0200277c(d);
    func_020029e8(d, 1);
    func_020028bc(d, zero, zero, zero);
    func_ov002_0220a448(func_02066648(b), d);
    func_0200284c(d, zero, zero);
    func_0200277c(c);
    func_020029e8(c, e);
    func_020028bc(c, zero, zero, zero);
    func_0206e1d8(a, b);
    func_0206e114(a, b, 0);
    func_0206e03c(a, p, 0);
    b += 0xd8;
    func_0206dff8(a, b);
    func_0206e344(a, c);
    func_0206e2d0(a);
    func_0200284c(c, zero, zero);
}
