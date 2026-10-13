/* func_ov116_0229dda8 @ 0x0229dda8, 0x10 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

void func_ov116_0229dda8(unsigned short *p, unsigned short mask)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x1428);
    *q = (unsigned short) (*q | mask);
}
