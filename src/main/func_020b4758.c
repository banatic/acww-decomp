/* func_020b4758 @ 0x020b4758, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const char data_020d20b8[];
extern const char data_020d2078[];
extern const char data_020d207c[];

void func_020b4758(char *dst, int n, const char *src)
{
    int i;
    const char *nul;
    int one;
    int zero;
    const char *e;
    const char *p;
    char *q;
    int ch;
    int c0;
    int c1;
    int sc;

    i = 0;
    nul = 0;
    one = 1;
    zero = 0;
    goto test;
body:
    c1 = p[one];
    ch = ((c1 << 8) & 0xff) | c0;
    e = nul;
    sc = (signed char) ch;
    if (sc >= '0' && sc <= '9') {
        e = &data_020d20b8[(sc - '0') * 2];
    } else if (ch == 0x20) {
        e = data_020d2078;
    } else if (ch == 0x2c) {
        e = data_020d207c;
    }
    q = dst + i;
    q[1] = e[zero];
    dst[i] = e[one];
    i += 2;
test:
    p = src + i;
    c0 = src[i];
    if (c0 != 0) {
        goto body;
    }
    if (p[one] != 0) {
        goto body;
    }
    dst[i] = 0;
    dst = dst + i;
    dst[1] = 0;
}
