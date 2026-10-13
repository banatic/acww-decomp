/* func_020734d0 @ 0x020734d0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0207356c(unsigned int);
extern unsigned char *func_02073590(unsigned int);
extern void MI_CpuCopy8(const unsigned char *src, unsigned char *dst, unsigned int n);
extern void func_02077a34(unsigned char *out, const unsigned char *in1, const unsigned char *in2);
extern int func_020b65c4(void);
extern unsigned int func_02077868(const unsigned char *data);
extern void func_02076168(unsigned char a, unsigned char *b, unsigned int c, unsigned char d, unsigned char e,
                          unsigned char f);
extern void func_0207357c(unsigned int);

void func_020734d0(unsigned int arg0)
{
    unsigned int limit;
    unsigned char buf[12];
    unsigned char *p;
    unsigned int i;
    unsigned int n;
    unsigned char c1;

    limit = func_0207356c(arg0);
    if (limit == 0) {
        return;
    }

    p = func_02073590(arg0);

    MI_CpuCopy8(p, buf + 2, 5);
    func_02077a34(buf + 6, buf, buf + 1);
    if (buf[0] != func_020b65c4()) {
        return;
    }

    i = 0;
    while (i < limit) {
        MI_CpuCopy8(p, buf + 2, 5);
        p += 5;
        i += 5;
        func_02077a34(buf + 6, buf, buf + 1);
        c1 = buf[1];
        n = func_02077868(buf + 2);
        func_02076168(buf[4], p, n, buf[5], buf[0], c1);
        p += n;
        i += n;
    }

    func_0207357c(arg0);
}
