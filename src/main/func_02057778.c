/* func_02057778 @ 0x02057778, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a40(int, const char *);
extern int func_020579b8(int, const char *);
extern int func_020577c8(int, int, int, int, int, int, int);

int func_02057778(int a, int b, const char *c, const char *d, int e, int f, int g)
{
    int x, y;

    if (c != 0) {
        x = func_02057a40(b, c);
    } else {
        x = -1;
    }

    if (d != 0) {
        y = func_020579b8(b, d);
    } else {
        y = -1;
    }

    return func_020577c8(a, b, x, y, e, f, g);
}
