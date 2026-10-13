/* func_02078248 @ 0x02078248, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02078248(unsigned char *p, int n)
{
    if (n < 0 || n >= 4) {
        return;
    }
    p[0xc3] |= (unsigned char) (1 << n);
}
