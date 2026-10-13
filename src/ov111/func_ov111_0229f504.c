/* func_ov111_0229f504 @ 0x0229f504, 0x20 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_ov111_0229f504(unsigned char *s)
{
    unsigned char c;
    c = s[0x9e];
    if (c == 0) {
        return 0;
    }
    return *(unsigned short *) (s + (c - 1) * 2 + 0x3d16);
}
