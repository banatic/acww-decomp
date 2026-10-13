/* func_ov066_0226a1b0 @ 0x0226a1b0, 0x74 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char *data_ov066_0226bdf4;

unsigned short func_ov066_0226a1b0(unsigned short x)
{
    unsigned short flags = *(unsigned short *) ((char *) data_ov066_0226bdf4 + 0x90);
    unsigned short cur = x;
    unsigned short i;
    i = 0;
    do {
        cur = (unsigned short) (cur + 1);
        if (cur > 14) {
            cur = 1;
        }
        if (flags & (1 << (cur - 1))) {
            return cur;
        }
    } while (++i < 14);
    return x;
}
