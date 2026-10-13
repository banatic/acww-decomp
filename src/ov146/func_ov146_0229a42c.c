/* func_ov146_0229a42c @ 0x0229a42c, 0x38 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

char *func_ov146_0229a42c(char *p)
{
    if (*(unsigned char *) (p + 0xb4) >= 0x14) {
        return p + 0x1e34;
    } else {
        (*(unsigned char *) (p + 0xb4))++;
        return p + 0x1630 + (*(unsigned char *) (p + 0xb4) - 1) * 108;
    }
}
