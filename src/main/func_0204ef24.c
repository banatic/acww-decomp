/* func_0204ef24 @ 0x0204ef24, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204ef74(int a, const unsigned short *b, const unsigned short *c, unsigned short *d, int e, int f);

int func_0204ef24(int a, const unsigned short *p, int c, int d)
{
    unsigned short local;
    int result;
    int flag;
    unsigned short v;

    result = 0;
    flag = result;
    v = *p;

    if (v >= 0x5000 && v <= 0x5021) {
        flag = 1;
    }

    if (flag) {
        local = 0xf030;
        result = func_0204ef74(a, p, p, &local, c, d);
    }
    return result;
}
