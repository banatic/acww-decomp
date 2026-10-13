/* func_ov141_02299f6c @ 0x02299f6c, 0x10 bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

void func_ov141_02299f6c(unsigned short *p, unsigned short val)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x1a7c);
    *q = *q | val;
}
