/* func_02042c9c @ 0x02042c9c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02042c9c(unsigned char *p, int *q)
{
    int a;
    int c;
    int r4;
    int shift;

    a = q[0];
    c = q[1];
    r4 = ((a - 16) >> 2) + ((c - 16) << 4);
    shift = (a & 3) << 1;
    if (r4 < 0 || r4 >= 0x400) {
        r4 = 0;
        shift = 0;
    }
    return ((p + r4)[0x6c] >> shift) & 3;
}
