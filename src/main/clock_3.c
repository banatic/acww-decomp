/* clock_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209df38 @ 0x0209df38, 0x2c bytes, Thumb
 * func_0209df04 @ 0x0209df04, 0x34 bytes, Thumb
 */

extern unsigned int data_021dc754[3];
extern unsigned int data_021dc744[3];
extern void func_0209e5b4(void *, void *);

void func_0209df38(unsigned char *p)
{
    unsigned int *const b = data_021dc754;
    unsigned int *a = data_021dc744;

    *(unsigned int *) p = 0;
    *(unsigned int *) (p + 4) = 0;
    p[5] = (unsigned char) a[0];
    p[4] = (unsigned char) a[1];
    p[3] = (unsigned char) a[2];
    p[2] = (unsigned char) b[0];
    p[1] = (unsigned char) b[1];
    p[0] = (unsigned char) b[2];
}

void func_0209df04(unsigned char *p)
{
    unsigned int stack[8];
    func_0209e5b4(stack, &stack[4]);
    *(unsigned int *) p = 0;
    *(unsigned int *) (p + 4) = 0;
    p[5] = (unsigned char) stack[0];
    p[4] = (unsigned char) stack[1];
    p[3] = (unsigned char) stack[2];
    p[2] = (unsigned char) stack[4];
    p[1] = (unsigned char) stack[5];
    p[0] = (unsigned char) stack[6];
}
