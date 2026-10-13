/* func_0200c050 @ 0x0200c050, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern void func_0200c0d4(void *a, unsigned char b, unsigned char c);
extern void *func_02018fdc(unsigned char);
extern void func_0201a698(void *a, void *b, int c);
extern void func_02010a24(void *a, int b, int c, unsigned char d, int e, int f, int g, int h);

void func_0200c050(unsigned char *p0, unsigned char *p1)
{
    unsigned char *q;
    unsigned char *p4;
    unsigned char b2, b1;
    void *p;

    q = p1 + 0xc;
    b2 = q[1];
    b1 = p1[0xc];

    func_0200c0d4(p0 + 0x8f0, b2, b1);

    p4 = p0 + 0x7d4;
    p4[0] = b2;
    p4[1] = b1;

    p = func_02018fdc(b2);

    *(unsigned int *) (p0 + 0x908) = (unsigned int) p;
    p0[0x931] = b2;

    func_0201a698(p0 + 0x90c, p, 0);

    func_02010a24(p0, 0x12, 5, ((unsigned char *) p)[0x18], 0x1000, 0, 5, *(unsigned int *) p);
}
