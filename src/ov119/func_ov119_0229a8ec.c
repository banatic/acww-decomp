/* func_ov119_0229a8ec @ 0x0229a8ec, 0x7c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

void func_ov119_0229a8ec(int unused, unsigned short *p, unsigned short val)
{
    *p &= 0xfffffc00;
    *p |= val;
    if (val != 0x10) {
        val = (unsigned short) (val + 1);
    }

    *(p + 1) &= 0xfffffc00;
    *(p + 1) |= val;
    if (val != 0x10) {
        val = (unsigned short) (val + 1);
    }

    *((unsigned short *) ((char *) p + 0x40)) &= 0xfffffc00;
    *((unsigned short *) ((char *) p + 0x40)) |= val;
    if (val != 0x10) {
        val = (unsigned short) (val + 1);
    }

    *((unsigned short *) ((char *) p + 0x42)) &= 0xfffffc00;
    *((unsigned short *) ((char *) p + 0x42)) |= val;
}
