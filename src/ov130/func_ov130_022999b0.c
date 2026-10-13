/* func_ov130_022999b0 @ 0x022999b0, 0x10 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

int func_ov130_022999b0(unsigned short *p, unsigned short mask)
{
    if (*p & mask) {
        return 1;
    } else {
        return 0;
    }
}
