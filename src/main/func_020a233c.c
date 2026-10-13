/* func_020a233c @ 0x020a233c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020a233c(unsigned char *p)
{
    p[0x10d] = (unsigned char) ((p[0x10d] & ~0xf0) | 0x30);
    p[0x10d] = (unsigned char) ((p[0x10d] & ~0x0f) | 0x03);
    p[0x10e] = (unsigned char) ((p[0x10e] & ~0x0f) | 0x03);
    p[0x10e] = (unsigned char) ((p[0x10e] & ~0xf0) | 0x30);
    p[0xa0]++;
    return 3;
}
