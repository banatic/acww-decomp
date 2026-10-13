/* func_ov137_0229c574 @ 0x0229c574, 0x18 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

int func_ov137_0229c574(unsigned short *p, unsigned short mask)
{
    if ((p[0x15ba] & mask) != 0) {
        return 1;
    }
    return 0;
}
