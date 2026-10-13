/* func_ov142_02299668 @ 0x02299668, 0x12 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

int func_ov142_02299668(unsigned short *p, int mask)
{
    int r = p[0x5b] & mask;
    if (r != 0) {
        return 1;
    } else {
        return 0;
    }
}
