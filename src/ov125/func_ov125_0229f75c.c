/* func_ov125_0229f75c @ 0x0229f75c, 0x10 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

void func_ov125_0229f75c(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x878);
    *p = (unsigned short) (*p | mask);
}
