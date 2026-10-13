/* func_020b00a8 @ 0x020b00a8, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b00a8(unsigned int a, unsigned int b, unsigned char *c)
{
    if (a < b) {
        if ((c[a >> 3] >> (a & 7)) & 1) {
            return 1;
        }
        return 0;
    }
    return 1;
}
