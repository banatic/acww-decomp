/* func_0209b69c @ 0x0209b69c, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_0209b69c(unsigned char *p, int n)
{
    int v = p[0x2e] + n;
    if (v > 14) {
        v = 14;
    }
    p[0x2e] = v;
    return p[0x2e];
}
