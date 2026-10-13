/* func_02057988 @ 0x02057988, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

char *func_02057988(char *p, int i)
{
    unsigned short h1;
    char *q;
    unsigned short h2;
    char *r;
    int offset;
    char *base;
    unsigned short val;
    char *addr;
    unsigned short f;

    if (i == -1) {
        return 0;
    }

    h1 = *(unsigned short *) (p + 0x34);
    q = p + h1;
    h2 = *(unsigned short *) (q + 6);
    r = q + h2;
    offset = *(int *) (p + 0x38);
    base = p + offset;
    val = *(unsigned short *) r;
    addr = r + (val * i);
    f = *(unsigned short *) (addr + 4);
    return base + (f << 3);
}
