/* func_020be628 @ 0x020be628, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200430c(void *);

void func_020be628(void *arg0)
{
    unsigned char *p;
    unsigned char *end;
    unsigned char *base;
    unsigned char *q;

    base = (unsigned char *) arg0;
    p = base;
    end = base + 0x60;
    q = base;
    while (p < end) {
        func_0200430c(p);
        p += 0xc;
    }
    q[0xc0] = 1;
}
