/* func_ov132_0229ad60 @ 0x0229ad60, 0x10 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

void func_ov132_0229ad60(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x1500);
    *p = (unsigned short) (*p | mask);
}
