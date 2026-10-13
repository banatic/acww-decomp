/* func_02026748 @ 0x02026748, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d190(unsigned short *s, int a, int b, unsigned char c);

int func_02026748(unsigned short *s, unsigned char *t)
{
    int r;

    *s = 0xfff1;
    r = func_0202d190(s, 2, 3, t[4]);
    if (r != 0) {
        return r;
    }
    r = func_0202d190(s, 0, 1, t[4]);
    if (r != 0) {
        return r;
    }
    r = 4;
    return func_0202d190(s, r, r, t[4]);
}
