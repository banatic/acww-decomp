/* func_02011c88 @ 0x02011c88, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const unsigned char data_020d843c[];
extern const unsigned char data_020d845c[];
extern const unsigned char data_020d847c[];
extern const unsigned char data_020d849c[];
extern int func_02011ed4(void);

const unsigned char *func_02011c88(const unsigned char *p, int n)
{
    const unsigned char *a;
    const unsigned char *b;
    const unsigned char *c;
    const unsigned char *d;
    const unsigned char *result;

    if (n >= 4) {
        n = func_02011ed4();
    }

    a = data_020d843c;
    b = data_020d845c;
    c = data_020d847c;
    d = data_020d849c;
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
