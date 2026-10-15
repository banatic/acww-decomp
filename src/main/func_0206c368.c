/* func_0206c368 @ 0x0206c368, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206d5e4(unsigned char *q, int v);
extern void func_0206c340(unsigned char *p);
unsigned char *func_0206c368(unsigned char *p, int q)
{
    unsigned int i;
    int zero = 0;
    *(int *) (p + 0x400) = zero;
    *(int *) (p + 0x410) = zero;
    p[0x43b] = zero;
    func_0206d5e4(p + 0x43c, q);
    func_0206c340(p);
    i = 0;
    goto tst;
bdy:
    *(int *) (p + i * 4 + 0x420) = zero;
    i++;
tst:
    if (i < 3) {
        goto bdy;
    }
    return p;
}
