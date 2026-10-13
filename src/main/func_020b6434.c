/* func_020b6434 @ 0x020b6434, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b6434(unsigned char *p, unsigned char a, unsigned char b, unsigned char c)
{
    if (p[0] == 0x3f) {
        p[0] = a;
        p[0x14] = b;
        p[0x15] = c;
        p[1] = 1;
        return 1;
    }
    return 0;
}
