/* func_0203cdcc @ 0x0203cdcc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_0203cdf8(int, unsigned char *, int);

int func_0203cdcc(int param1, int param2)
{
    unsigned char c;
    unsigned char *p;

    p = func_0203cdf8(param1, &c, param2);
    if (p != 0) {
        if (*p & c) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
