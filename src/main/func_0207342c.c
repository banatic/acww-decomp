/* func_0207342c @ 0x0207342c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020734a4(int a);
extern unsigned char *func_020734c8(int a);
extern void func_020734b4(int a);
extern void MI_CpuCopy8(unsigned char *dst, unsigned char *src, int n);
extern void func_02077a34(unsigned char *out, unsigned char *src1, unsigned char *src2);
extern int func_02077868(unsigned char *s);
extern void func_02076168(unsigned char a0, unsigned char *a1, int a2, unsigned char a3, unsigned char a4, unsigned char a5);

void func_0207342c(int a)
{
    unsigned int r;
    unsigned int i;
    unsigned char *p;
    unsigned char buf[6];
    unsigned char out[6];

    r = func_020734a4(a);
    if (r == 0) {
        return;
    }

    i = 0;
    p = func_020734c8(a);

    while (i < r) {
        unsigned char b1;
        int r6;

        MI_CpuCopy8(p, &buf[2], 5);
        p += 5;
        i += 5;

        func_02077a34(out, buf, &buf[1]);
        b1 = buf[1];
        r6 = func_02077868(&buf[2]);
        func_02076168(buf[4], p, r6, buf[5], buf[0], b1);
        p += r6;
        i += r6;
    }

    func_020734b4(a);
}
