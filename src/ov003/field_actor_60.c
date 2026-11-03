/* field_actor_60: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220f768 @ 0x0220f768, 0x4e bytes, Thumb
 * func_ov003_0220f744 @ 0x0220f744, 0x24 bytes, Thumb
 */

typedef struct {
    double pad_00;
    char data[4];
} CType;

typedef char DType[16];

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_ov003_0220f7b8(void *, int, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_ov003_0220f768(void *p0, int p1, int p2, int p3, unsigned char p4, int p5, short p6)
{
    int a;
    CType c;
    DType d;
    int result;

    func_0200e92c(&c);
    func_0200e90c(&c, 0x69, p5, p6);
    a = p4;
    func_ov003_0220f7b8(&d, p1, p2, p3, a);
    result = func_0200e894(p0, &c);
    func_0200e91c(&c);
    return result;
}

void func_ov003_0220f744(unsigned char *r0, unsigned short r1, unsigned int r2, unsigned int r3, unsigned char r4,
                         unsigned char r5)
{
    r0[0] = 0;
    *(unsigned short *) (r0 + 2) = r1;
    *(unsigned int *) (r0 + 4) = r2;
    *(unsigned int *) (r0 + 8) = r3;
    r0[12] = r4;
    r0[13] = r5;
}
