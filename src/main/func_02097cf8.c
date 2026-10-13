/* func_02097cf8 @ 0x02097cf8, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02097cf8(unsigned char *base, int bit)
{
    base += 4;
    base[bit >> 3] &= ~(1 << (bit & 7));
}
