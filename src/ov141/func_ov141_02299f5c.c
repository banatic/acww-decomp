/* func_ov141_02299f5c @ 0x02299f5c, 0x10 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

void func_ov141_02299f5c(unsigned short *p, unsigned short mask)
{
    p = (unsigned short *) ((char *) p + 0x1a7c);
    *p &= ~mask;
}
