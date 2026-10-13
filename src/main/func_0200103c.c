/* func_0200103c @ 0x0200103c, 0x38 bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_0200103c(void)
{
    unsigned char v;
    unsigned short r = 0;

    v = *(unsigned char *) 0x027ffe1d;
    if (v == 0x80) {
        r |= 0x40;
    } else if (v == 0x40) {
        r |= 0x80;
    }
    return r;
}
