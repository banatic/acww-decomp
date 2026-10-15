/* func_020b9e80 @ 0x020b9e80, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a8c(unsigned char *);
extern int func_02057a7c(unsigned char *);
extern int func_020b9f80(unsigned int, unsigned int, int, int, int);

int func_020b9e80(unsigned int a0, unsigned char *a1, int a2, unsigned int a3)
{
    unsigned char *base;
    unsigned char *p;
    unsigned int off;
    unsigned short c;
    unsigned short v;
    unsigned char *q;
    int r1v;
    int r2v;

    base = a1;
    off = *(unsigned int *) (base + 8);
    base += off;
    p = base + 4;
    c = *(unsigned short *) (base + 10);
    v = *(unsigned short *) (p + c);
    off = *(unsigned int *) (p + c + v * a2 + 4);
    q = base + off;
    r1v = func_02057a8c(q);
    r2v = func_02057a7c(q);
    return func_020b9f80(a0, a3, r2v, r1v, 2);
}
