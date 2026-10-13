/* func_ov140_0229a65c @ 0x0229a65c, 0x20 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

int func_ov140_0229a65c(unsigned char *p)
{
    unsigned char b = p[0x8dc];
    unsigned char t = (unsigned char) (b + 0xfa);
    if (t <= 2) {
        return 0xae;
    } else {
        return (b << 4) + 0x46;
    }
}
