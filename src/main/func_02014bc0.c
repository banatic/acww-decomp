/* func_02014bc0 @ 0x02014bc0, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201596c(unsigned char *p, int n);
int func_02014bc0(unsigned char *p, long long *src)
{
    if (func_0201596c(p, 0xa) != 0) {
        *(long long *) (p + 0x8c) = *src;
        p[0xa5] = 0;
        return 1;
    }
    return 0;
}
