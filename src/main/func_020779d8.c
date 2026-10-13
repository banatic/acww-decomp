/* func_020779d8 @ 0x020779d8, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020779d8(const unsigned char *p, unsigned int *out, unsigned char *q)
{
    if (q) {
        *q = ((unsigned int) p[0] >> 4) & 0xF;
    }
    *out = (p[2] & 0xFF) | (((p[0] << 16) & 0x000F0000) | ((p[1] << 8) & 0x0000FF00));
}
