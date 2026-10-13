/* func_ov068_0226fc2c @ 0x0226fc2c, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

int func_ov068_0226fc2c(unsigned short *p)
{
    unsigned short *q = (unsigned short *) ((char *) p + 0x378);
    *q |= 0x10;
    *q &= ~0x20;
    return 1;
}
