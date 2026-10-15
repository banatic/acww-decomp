/* func_02011cd8 @ 0x02011cd8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_020d84b8[];
extern const unsigned char data_020d84d8[];
extern const unsigned char data_020d84f8[];
extern const unsigned char data_020d8518[];
extern int func_02011ed4(void);

const unsigned char *func_02011cd8(const unsigned char *p, int n)
{
    const unsigned char *a;
    const unsigned char *b;
    const unsigned char *c;
    const unsigned char *d;
    const unsigned char *result;

    if (n >= 4) {
        n = func_02011ed4();
    }

    a = data_020d84b8;
    b = data_020d84d8;
    c = data_020d84f8;
    d = data_020d8518;
    result = d;

    if (n == 2) {
        result = b;
    } else if (n == 3) {
        result = a;
    } else if (p[0x255] != 0) {
        result = c;
    }

    return result;
}
