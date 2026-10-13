/* func_ov004_02229774 @ 0x02229774, 0x4e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov004_022297c4(void *, int, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

typedef struct {
    double pad_00;
    char data[4];
} CType;

typedef char DType[16];

int func_ov004_02229774(void *p0, int p1, int p2, int p3, unsigned char p4, int p5, short p6)
{
    int a;
    CType c;
    DType d;
    int result;

    func_0200e92c(&c);
    func_0200e90c(&c, 0x24, p5, p6);
    a = p4;
    func_ov004_022297c4(&d, p1, p2, p3, a);
    result = func_0200e894(p0, &c);
    func_0200e91c(&c);
    return result;
}
