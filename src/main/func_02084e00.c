/* func_02084e00 @ 0x02084e00, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02084e00(unsigned short *p, unsigned int bit, unsigned int idx)
{
    if (bit < 0x10 && idx < 0xe) {
        if (((p[idx] >> bit) & 1) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
